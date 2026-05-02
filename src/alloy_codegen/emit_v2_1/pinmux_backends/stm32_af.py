"""STM32 alternate-function backend — ``alloy.pinmux.stm32-af-v1``.

STM32 chips drive pin function selection through ``GPIOx.AFRL`` /
``GPIOx.AFRH`` 4-bit AF numbers (0..15).  The number determines
which on-chip peripheral signal the pad routes to.

Today's admitted YAMLs carry the **pad candidate** for each
``(peripheral, signal)`` triple but **not the AF number** — that
field is queued for an alloy-devices-yml enrichment pass.  This
backend therefore returns ``code=None`` until the YAML schema
gains an ``af:`` field on each ``PinOptionFixed`` row.

The package-conditional alternate-pin annotation (e.g. STM32 G0's
``PA12 [PA10]`` — the pad is PA12 by default but on UFQFPN28 the
chip routes the function through PA10) is preserved through
:attr:`PinRoute.alternate_pin`; the emitter publishes both the
canonical row and an alternate-route table the runtime resolves
at boot.
"""

from __future__ import annotations

from alloy_codegen.emit_v2_1.pinmux_backends._protocol import PinOption
from alloy_codegen.ir.synthesised.pin_routes import PinRoute
from alloy_codegen.ir.v2_1 import (
    PeripheralInstance,
    PinOptionFixed,
)

SCHEMA_ID = "alloy.pinmux.stm32-af-v1"


def _strip_pin_label(raw: str) -> tuple[str, str | None]:
    """Normalise an STM32 pad label to a canonical pin id and an
    optional alternate-pin annotation.

    Examples:

    * ``PA2``                           → ``("PA2", None)``
    * ``PA12 [PA10]``                   → ``("PA12", "PA10")``
    * ``PC15-OSC32_OUT (PC15)``         → ``("PC15", None)``
    * ``PA9 [PA11]``                    → ``("PA9", "PA11")``
    * ``PA14-BOOT0``                    → ``("PA14", None)``
    """
    raw = raw.strip()
    alternate: str | None = None
    # STM32 G0 alternate-pin annotation: ``Pxy [Pwz]``.
    if "[" in raw and "]" in raw:
        head, tail = raw.split("[", 1)
        alt, _ = tail.split("]", 1)
        raw = head.strip()
        alternate = alt.strip()
    # Drop the trailing function annotation: ``PA14-BOOT0``,
    # ``PC15-OSC32_OUT``, ``PC14-OSC32_IN`` etc.  Keep the prefix
    # up to the first '-'.
    if "-" in raw:
        raw = raw.split("-", 1)[0].strip()
    # Drop a parenthesised disambiguation: ``PC15 (PC15)``.
    if " (" in raw:
        raw = raw.split(" (", 1)[0].strip()
    return raw, alternate


class _Stm32AfBackend:
    schema_id = SCHEMA_ID

    def encode(
        self,
        peripheral: PeripheralInstance,
        signal: str,
        option: PinOption,
    ) -> PinRoute:
        if not isinstance(option, PinOptionFixed):
            # STM32 admits Fixed-AF only.  Future imxrt-style
            # daisy-chained sources arrive here as Matrix/Psel and
            # need their own backend.
            raise ValueError(
                f"stm32-af backend cannot encode option type "
                f"{type(option).__name__} (peripheral={peripheral.id}, "
                f"signal={signal})"
            )
        pin_id, alternate = _strip_pin_label(option.pin)
        # Until alloy-devices-yml carries an `af:` field on the
        # PinOptionFixed row, ``option.func`` is always None for
        # STM32; we surface that as ``code=None`` and let consumers
        # rely on the typed (peripheral, signal, pin) shape until
        # the AF data lands.
        return PinRoute(
            peripheral_id=peripheral.id,
            signal_id=signal,
            pin_id=_canonicalise_pin_id(pin_id),
            backend_schema_id=SCHEMA_ID,
            code=option.func,           # None today; populated post-enrichment
            alternate_pin=alternate,
        )


def _canonicalise_pin_id(raw: str) -> str:
    """Lower-case ``PA2`` → ``pa2`` so the typed enum entries
    match Python identifier conventions and survive C symbol
    sanitisation."""
    return raw.lower()


STM32_AF_BACKEND = _Stm32AfBackend()
"""Singleton — registered under ``alloy.pinmux.stm32-af-v1``."""

__all__ = ["STM32_AF_BACKEND", "SCHEMA_ID"]
