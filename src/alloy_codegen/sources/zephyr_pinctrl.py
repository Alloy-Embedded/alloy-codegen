"""Per-vendor Zephyr DTS pinctrl decoders.

Added by ``decode-zephyr-pinctrl-into-connection-candidates``.

Zephyr device trees encode pinmux per peripheral via a
``pinctrl-0`` phandle pointing at a group node whose properties
(``psels`` for Nordic, cell tuples for STM32, ``pinmux`` for
NXP) describe pin/peripheral/signal/AF triples.  This module
turns those vendor-specific encodings into a uniform
:class:`PinctrlAssignment` tuple the IR can consume.

Public surface:

* :class:`PinctrlAssignment` — the canonical decoded record.
* :func:`PINCTRL_DECODERS[vendor]` — vendor → decoder callable.
* :func:`decode_pinctrl_for_node(...)` — adapter helper that
  walks a peripheral node's ``pinctrl-0`` phandle and returns
  every decoded pin assignment, calling the right per-vendor
  decoder.

The proposal explicitly defers NXP IOMUX to a follow-up
(``nxp-zephyr-pinctrl-decoder``); the registry slot for
``"nxp"`` raises :class:`NotImplementedError` with a clear
pointer.
"""

from __future__ import annotations

import re
from collections.abc import Callable, Iterable
from dataclasses import dataclass
from typing import Any

from devicetree import dtlib


@dataclass(frozen=True, slots=True)
class PinctrlAssignment:
    """One decoded pin/peripheral/signal route.

    Uniform shape across vendors so the downstream
    ``connection_candidates`` projection is single-path.
    """

    pin: str  # e.g. "P0_06" (Nordic) or "PA9" (STM32)
    peripheral: str  # e.g. "UART0" / "USART1"
    signal: str  # e.g. "TX", "RX", "SCK", "MOSI"
    af_number: int
    route_kind: str = "alternate-function"


# ---------------------------------------------------------------------------
# Nordic — NRF_PSEL macro decoder
#
# After Zephyr's preprocessor expansion, ``NRF_PSEL(fun, port, pin)``
# resolves to a 32-bit cell:
#     (NRF_FUN_<fun> << 16) | (port << 5) | pin
# where the function constants come from
# ``zephyr/include/zephyr/dt-bindings/pinctrl/nrf-pinctrl.h``.
# ---------------------------------------------------------------------------


# Mapping from NRF_FUN_<fun> integer constants to (peripheral_kind, signal).
# ``peripheral_kind`` is the controller class; the concrete instance
# (UART0 vs UART1, SPI0 vs SPI1, …) comes from the parent peripheral
# node's label (which the adapter passes in alongside the cells).
_NRF_FUN_TO_SIGNAL: dict[int, tuple[str, str]] = {
    0: ("uart", "TX"),  # NRF_FUN_UART_TX
    1: ("uart", "RX"),
    2: ("uart", "RTS"),
    3: ("uart", "CTS"),
    4: ("spim", "SCK"),
    5: ("spim", "MOSI"),
    6: ("spim", "MISO"),
    7: ("spis", "SCK"),
    8: ("spis", "MOSI"),
    9: ("spis", "MISO"),
    10: ("spis", "CSN"),
    11: ("twim", "SCL"),
    12: ("twim", "SDA"),
    13: ("twis", "SCL"),
    14: ("twis", "SDA"),
    15: ("pwm", "OUT0"),
    16: ("pwm", "OUT1"),
    17: ("pwm", "OUT2"),
    18: ("pwm", "OUT3"),
    19: ("saadc", "AIN0"),
    20: ("saadc", "AIN1"),
    21: ("saadc", "AIN2"),
    22: ("saadc", "AIN3"),
}


def _decode_nrf_psel(cell: int) -> tuple[str, int, int]:
    """Decode one packed NRF_PSEL cell.

    Returns ``(signal_kind, port, pin)`` where ``signal_kind``
    is the upper-cased function name (e.g. ``"UART_TX"``).
    """
    fun = (cell >> 16) & 0xFFFF
    port = (cell >> 5) & 0x7
    pin = cell & 0x1F
    if fun not in _NRF_FUN_TO_SIGNAL:
        raise ValueError(f"unknown NRF_FUN {fun}; pinctrl cell {hex(cell)}")
    kind, signal = _NRF_FUN_TO_SIGNAL[fun]
    return (f"{kind.upper()}_{signal}", port, pin)


def decode_nordic(
    *,
    peripheral_label: str,
    cells: Iterable[int],
) -> tuple[PinctrlAssignment, ...]:
    """Decode every ``psels`` cell on a Nordic pinctrl group.

    ``peripheral_label`` is the label of the peripheral node that
    references this group (e.g. ``"UART0"``, ``"SPI0"``).  Used
    as the canonical peripheral name in the resulting
    :class:`PinctrlAssignment` records.
    """
    assignments: list[PinctrlAssignment] = []
    for cell in cells:
        try:
            _signal_kind, port, pin = _decode_nrf_psel(cell)
        except ValueError:
            continue  # Unknown function — log + skip.
        # Recover (kind, signal) directly from the function map for
        # cleaner naming on the assignment record.
        fun = (cell >> 16) & 0xFFFF
        kind, signal = _NRF_FUN_TO_SIGNAL[fun]
        del kind  # absorbed into peripheral_label
        assignments.append(
            PinctrlAssignment(
                pin=f"P{port}_{pin:02d}",
                peripheral=peripheral_label.upper(),
                signal=signal,
                af_number=0,  # Nordic uses pin-routing, not AFs; 0 is canonical.
                route_kind="alternate-function",
            )
        )
    return tuple(assignments)


# ---------------------------------------------------------------------------
# STM32 — <STM32_PINMUX 'PA9', AF7_USART1> cell pair decoder
#
# Real Zephyr STM32 DTS uses two cells per assignment — pin label
# string + AF constant.  After preprocessor: numeric pin-port encoding
# + numeric AF + peripheral identifier.  For our v1 fixture we
# accept the structured "<pin>:<peripheral>:<signal>:<af>" string
# form so contributors can author tests without a full Zephyr
# preprocessor pipeline.
# ---------------------------------------------------------------------------


_STM32_STRING_RE = re.compile(
    r"^(?P<pin>P[A-Z]\d+):(?P<peripheral>[A-Z][A-Z0-9_]*):"
    r"(?P<signal>[A-Z][A-Z0-9_]*):(?P<af>\d+)$"
)


def decode_stm32(
    *,
    peripheral_label: str,
    cells: Iterable[Any],
) -> tuple[PinctrlAssignment, ...]:
    """Decode STM32 pinctrl cells.

    For v1 supports the structured-string form
    ``"PA9:USART1:TX:7"`` used in test fixtures.  Real Zephyr
    STM32 DTS uses paired numeric cells; that decoder lands as
    a drop-in extension here without changing call sites.
    """
    del peripheral_label  # stm32 cells carry the peripheral inline
    assignments: list[PinctrlAssignment] = []
    for cell in cells:
        if not isinstance(cell, str):
            continue
        match = _STM32_STRING_RE.match(cell)
        if match is None:
            continue
        assignments.append(
            PinctrlAssignment(
                pin=match.group("pin"),
                peripheral=match.group("peripheral"),
                signal=match.group("signal"),
                af_number=int(match.group("af")),
                route_kind="alternate-function",
            )
        )
    return tuple(assignments)


# ---------------------------------------------------------------------------
# Per-vendor registry
# ---------------------------------------------------------------------------


def _decode_nxp_unimplemented(**_kwargs: Any) -> tuple[PinctrlAssignment, ...]:
    raise NotImplementedError(
        "NXP IOMUX pinctrl decoder is deferred to a follow-up "
        "change (nxp-zephyr-pinctrl-decoder).  iMXRT pin assignments "
        "today come from the IOMUX header parser, not Zephyr DTS."
    )


PINCTRL_DECODERS: dict[str, Callable[..., tuple[PinctrlAssignment, ...]]] = {
    "nordic": decode_nordic,
    "stm32": decode_stm32,
    "nxp": _decode_nxp_unimplemented,
}


def decoder_for_vendor(
    vendor: str,
) -> Callable[..., tuple[PinctrlAssignment, ...]] | None:
    """Return the decoder for a vendor, or ``None`` if unknown.

    Soft lookup so the adapter can log + skip rather than failing
    when a new vendor's DTS lands before a decoder does.
    """
    return PINCTRL_DECODERS.get(vendor)


# ---------------------------------------------------------------------------
# DTS walker
# ---------------------------------------------------------------------------


def decode_pinctrl_for_node(
    *,
    peripheral_node: dtlib.Node,
    peripheral_label: str,
    pinctrl_node: dtlib.Node,
    vendor: str,
) -> tuple[PinctrlAssignment, ...]:
    """Decode every pin assignment referenced by a peripheral's
    ``pinctrl-0`` phandle.

    ``pinctrl_node`` is the resolved phandle target — a group
    node whose children carry per-state ``psels`` (Nordic) or
    cell pairs (STM32).
    """
    decoder = decoder_for_vendor(vendor)
    if decoder is None:
        return ()
    del peripheral_node  # unused for now; kept for STM32-AF future use
    assignments: list[PinctrlAssignment] = []

    if vendor == "nordic":
        for child in pinctrl_node.nodes.values():
            psels = child.props.get("psels")
            if psels is None:
                continue
            try:
                cells = psels.to_nums()
            except dtlib.DTError:
                continue
            assignments.extend(decoder(peripheral_label=peripheral_label, cells=cells))
    elif vendor == "stm32":
        for child in pinctrl_node.nodes.values():
            cells_prop = child.props.get("pin-assignments")
            if cells_prop is None:
                continue
            try:
                cells = cells_prop.to_strings()
            except dtlib.DTError:
                continue
            assignments.extend(decoder(peripheral_label=peripheral_label, cells=cells))

    return tuple(assignments)


__all__ = [
    "PINCTRL_DECODERS",
    "PinctrlAssignment",
    "decode_nordic",
    "decode_pinctrl_for_node",
    "decode_stm32",
    "decoder_for_vendor",
]
