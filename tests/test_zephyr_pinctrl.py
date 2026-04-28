"""Tests for the Zephyr pinctrl decoder.

Added by ``decode-zephyr-pinctrl-into-connection-candidates``.
"""

from __future__ import annotations

import dataclasses
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
if str(SRC) not in sys.path:
    sys.path.insert(0, str(SRC))

from alloy_codegen.context import ExecutionContext  # noqa: E402
from alloy_codegen.sources.zephyr_pinctrl import (  # noqa: E402
    PINCTRL_DECODERS,
    PinctrlAssignment,
    decode_nordic,
    decode_stm32,
    decoder_for_vendor,
)

# ---------------------------------------------------------------------------
# Nordic NRF_PSEL decoder
# ---------------------------------------------------------------------------


def test_decode_nordic_uart_tx_yields_p0_06_uart_tx() -> None:
    """Spec scenario: NRF_PSEL(UART_TX, 0, 6) → P0_06 UART0 TX."""
    # 0 << 16 | 0 << 5 | 6 = 0x06
    assignments = decode_nordic(peripheral_label="uart0", cells=[0x06])
    assert len(assignments) == 1
    a = assignments[0]
    assert a.pin == "P0_06"
    assert a.peripheral == "UART0"
    assert a.signal == "TX"
    assert a.route_kind == "alternate-function"


def test_decode_nordic_uart_rx_decodes_function_index_one() -> None:
    # 1 << 16 | 0 << 5 | 8 = 0x10008
    assignments = decode_nordic(peripheral_label="uart0", cells=[0x10008])
    assert assignments[0].pin == "P0_08"
    assert assignments[0].signal == "RX"


def test_decode_nordic_spi_signals() -> None:
    # NRF_FUN_SPIM_SCK(4), NRF_FUN_SPIM_MOSI(5), NRF_FUN_SPIM_MISO(6)
    cells = [0x40013, 0x50014, 0x60015]
    assignments = decode_nordic(peripheral_label="spi0", cells=cells)
    signals = [(a.pin, a.signal) for a in assignments]
    assert signals == [("P0_19", "SCK"), ("P0_20", "MOSI"), ("P0_21", "MISO")]


def test_decode_nordic_skips_unknown_function() -> None:
    """Unknown function indices log + skip rather than raising."""
    # 9999 << 16 — undefined function; decoder silently drops.
    assignments = decode_nordic(peripheral_label="uart0", cells=[0x270F0006])
    assert assignments == ()


def test_decode_nordic_high_port() -> None:
    """Port 1 pin 5: 0 << 16 | 1 << 5 | 5 = 0x25."""
    assignments = decode_nordic(peripheral_label="uart1", cells=[0x25])
    assert assignments[0].pin == "P1_05"


# ---------------------------------------------------------------------------
# STM32 decoder (string form)
# ---------------------------------------------------------------------------


def test_decode_stm32_string_form_yields_pa9_usart1_tx() -> None:
    """Spec scenario: <STM32_PINMUX 'PA9', AF7_USART1> equivalent
    string ``"PA9:USART1:TX:7"`` → PinctrlAssignment(pin=PA9,
    peripheral=USART1, signal=TX, af=7)."""
    assignments = decode_stm32(peripheral_label="usart1", cells=["PA9:USART1:TX:7"])
    assert len(assignments) == 1
    a = assignments[0]
    assert a.pin == "PA9"
    assert a.peripheral == "USART1"
    assert a.signal == "TX"
    assert a.af_number == 7


def test_decode_stm32_skips_malformed_strings() -> None:
    assignments = decode_stm32(peripheral_label="usart1", cells=["not-a-valid-cell"])
    assert assignments == ()


# ---------------------------------------------------------------------------
# Vendor registry
# ---------------------------------------------------------------------------


def test_pinctrl_decoders_registry_has_nordic_and_stm32() -> None:
    assert "nordic" in PINCTRL_DECODERS
    assert "stm32" in PINCTRL_DECODERS


def test_decoder_for_unknown_vendor_returns_none() -> None:
    assert decoder_for_vendor("acme") is None


def test_decoder_for_nxp_raises_not_implemented_when_called() -> None:
    """Spec scenario: unsupported pinctrl encodings (NXP IOMUX
    today) raise / skip rather than producing garbage."""
    decoder = PINCTRL_DECODERS["nxp"]
    with pytest.raises(NotImplementedError, match="NXP IOMUX"):
        decoder(peripheral_label="LPUART1", cells=[])


# ---------------------------------------------------------------------------
# End-to-end: nrf52840 admission produces a populated IR
# ---------------------------------------------------------------------------


def test_nrf52840_pipeline_populates_connection_candidates() -> None:
    """Headline spec scenario: the Nordic nRF52840 fixture's
    pinctrl groups produce a non-empty ``connection_candidates``
    tuple in the resolved IR — which feeds the existing
    pin_validation.hpp emitter."""
    from alloy_codegen.stages.normalize import _build_zephyr_dts_device_ir

    ctx = ExecutionContext.default().with_overrides(
        source_overrides={"zephyr-dts": str(ROOT / "tests/fixtures/zephyr-dts")},
        artifact_root="/tmp/_zp_a",
        publication_root="/tmp/_zp_p",
    )
    ir = _build_zephyr_dts_device_ir(
        execution_context=ctx,
        device_name="nrf52840",
        vendor="nordic",
        family="nrf52",
    )
    assert len(ir.connection_candidates) >= 7
    by_pair = {(c.pin, c.peripheral, c.signal) for c in ir.connection_candidates}
    assert ("P0_06", "UART0", "tx") in by_pair
    assert ("P0_08", "UART0", "rx") in by_pair


def test_nrf52840_pipeline_emits_pin_validation_header() -> None:
    """The ValidPinAssignment specialisation for
    P0_06 / UART0_TX SHALL appear in the emitted
    pin_validation.hpp."""
    from alloy_codegen.runtime_pin_validation import emit_runtime_pin_validation_header
    from alloy_codegen.stages.normalize import _build_zephyr_dts_device_ir

    ctx = ExecutionContext.default().with_overrides(
        source_overrides={"zephyr-dts": str(ROOT / "tests/fixtures/zephyr-dts")},
        artifact_root="/tmp/_zp_a",
        publication_root="/tmp/_zp_p",
    )
    ir = _build_zephyr_dts_device_ir(
        execution_context=ctx,
        device_name="nrf52840",
        vendor="nordic",
        family="nrf52",
    )
    artifact = emit_runtime_pin_validation_header(family_dir="nordic/nrf52", device=ir)
    assert artifact is not None
    assert "PinAssignmentValid<PinId::P0_06" in artifact.content
    assert "PeripheralSignal::UART0_TX" in artifact.content
    assert "concept ValidPinAssignment" in artifact.content


def test_pinctrl_assignment_is_frozen_dataclass() -> None:
    a = PinctrlAssignment(
        pin="P0_06",
        peripheral="UART0",
        signal="TX",
        af_number=0,
        route_kind="alternate-function",
    )
    with pytest.raises((AttributeError, dataclasses.FrozenInstanceError)):
        a.pin = "P0_07"  # type: ignore[misc]
