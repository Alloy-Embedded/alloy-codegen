"""Tests for synthesised IR rows.

Added by ``adopt-canonical-device-v2-1`` Phase 3.
"""

from __future__ import annotations

from pathlib import Path

import pytest

from alloy_codegen.canonical_device_v2_1 import parse_device
from alloy_codegen.ir.synthesised import (
    InterruptBinding,
    RouteOperation,
    SignalEndpoint,
    SynthesisedDevice,
    VectorSlot,
    build_synthesised,
)

_REPO_ROOT = Path(__file__).resolve().parents[1]
_HANDCRAFTED_DIR = (
    _REPO_ROOT.parent
    / "alloy-data-extractor"
    / "proposals"
    / "canonical-v2-handcrafted"
)


def _hand_yaml(name: str) -> Path:
    path = _HANDCRAFTED_DIR / name
    if not path.is_file():
        pytest.skip(f"Hand-crafted reference {name} not present.")
    return path


def _synth(name: str) -> SynthesisedDevice:
    return build_synthesised(parse_device(_hand_yaml(name).read_text(encoding="utf-8")))


# ---------------------------------------------------------------------------
# Determinism
# ---------------------------------------------------------------------------


@pytest.mark.parametrize(
    "name",
    ["stm32f103c8t6.yml", "atmega328p.yml", "esp32-wroom32.yml",
     "nrf52840.yml", "rp2040.yml"],
)
def test_synthesis_is_deterministic(name: str) -> None:
    a = _synth(name)
    b = _synth(name)
    assert a == b


# ---------------------------------------------------------------------------
# STM32 — RCC clock-enable + reset routes
# ---------------------------------------------------------------------------


def test_stm32_emits_clock_enable_per_peripheral() -> None:
    syn = _synth("stm32f103c8t6.yml")
    enables = [
        op for op in syn.route_operations
        if op.kind == "set-bit" and op.target_ref_kind == "clock-gate"
    ]
    # GPIOA + GPIOB + GPIOC + GPIOD + 3× USART + 2× SPI + 2× I2C +
    # 4× TIMER + 2× ADC + DMA1 = 17 enables
    assert len(enables) >= 15
    assert any(op.target_ref_id == "gate:usart1" for op in enables)
    assert any(op.target_ref_id == "gate:dma1" for op in enables)


def test_stm32_emits_reset_pulse_per_peripheral() -> None:
    syn = _synth("stm32f103c8t6.yml")
    asserts  = [op for op in syn.route_operations if op.kind == "set-bit"
                and op.target_ref_kind == "reset"]
    releases = [op for op in syn.route_operations if op.kind == "clear-bit"
                and op.target_ref_kind == "reset"]
    assert len(asserts) == len(releases)
    assert any(op.target_ref_id == "reset:spi1" for op in asserts)


def test_stm32_route_operation_carries_register_ids() -> None:
    syn = _synth("stm32f103c8t6.yml")
    op = next(o for o in syn.route_operations
              if o.subject_id == "gpioa" and "clock-enable" in o.operation_id)
    assert op.register_id is not None
    assert op.register_field_id is not None
    assert op.value_int == 1
    assert op.value_ref_kind == "int"


# ---------------------------------------------------------------------------
# Interrupt bindings + vector slots
# ---------------------------------------------------------------------------


@pytest.mark.parametrize(
    "name",
    ["stm32f103c8t6.yml", "atmega328p.yml", "esp32-wroom32.yml",
     "nrf52840.yml", "rp2040.yml"],
)
def test_every_chip_emits_interrupt_bindings(name: str) -> None:
    syn = _synth(name)
    assert len(syn.interrupt_bindings) >= 1
    for b in syn.interrupt_bindings:
        assert isinstance(b, InterruptBinding)
        assert b.peripheral
        assert b.interrupt
        assert b.line >= 0


def test_nrf52_shared_irq_carries_mutex_group() -> None:
    """Nordic's UARTE0 and SPIM0/TWIM0 share IRQ 3 via mutex_group."""
    syn = _synth("nrf52840.yml")
    irq3 = [b for b in syn.interrupt_bindings if b.line == 3]
    # uarte0 + spim0 + twim0 all hit line 3 — at least one carries
    # the shared_group tag.
    assert any(b.shared_group is not None for b in irq3)


def test_stm32_vector_slots_classify_correctly() -> None:
    syn = _synth("stm32f103c8t6.yml")
    by_slot = {v.slot: v for v in syn.vector_slots}
    # USART1 IRQ at slot 37 in the v2.1 hand-crafted YAML.
    assert by_slot[37].kind == "peripheral-irq"
    assert by_slot[37].interrupt == "USART1_IRQHandler"


def test_avr_vector_slot_zero_is_reset() -> None:
    syn = _synth("atmega328p.yml")
    slot0 = next(v for v in syn.vector_slots if v.slot == 0)
    assert slot0.kind == "reset"
    assert slot0.symbol_name == "__vector_default"


def test_esp32_matrix_emits_matrix_source_slots() -> None:
    syn = _synth("esp32-wroom32.yml")
    # ESP32 declares interrupts.matrix=true with 10 peripheral_sources
    # in the hand-crafted YAML.
    assert len(syn.vector_slots) >= 1
    assert all(s.kind == "matrix-source" for s in syn.vector_slots)


# ---------------------------------------------------------------------------
# Signal endpoints
# ---------------------------------------------------------------------------


@pytest.mark.parametrize(
    "name,expected_signal",
    [
        ("stm32f103c8t6.yml", "endpoint:usart1:tx"),
        ("nrf52840.yml",      "endpoint:uarte0:tx"),
        ("esp32-wroom32.yml", "endpoint:uart0:tx"),
        ("rp2040.yml",        "endpoint:uart0:tx"),
        ("atmega328p.yml",    "endpoint:usart0:tx"),
    ],
)
def test_uart_tx_signal_endpoint_emitted(name: str, expected_signal: str) -> None:
    syn = _synth(name)
    assert any(e.endpoint_id == expected_signal for e in syn.signal_endpoints)


def test_adc_channel_endpoints_carry_analog_direction() -> None:
    """SAADC channels on nRF52 emit endpoints with direction=analog."""
    syn = _synth("nrf52840.yml")
    saadc_endpoints = [e for e in syn.signal_endpoints if e.peripheral == "saadc"]
    assert any(e.direction == "analog" for e in saadc_endpoints)


# ---------------------------------------------------------------------------
# Aggregate health
# ---------------------------------------------------------------------------


def test_synthesised_device_has_only_typed_rows() -> None:
    """Every row of every collection is a typed dataclass."""
    syn = _synth("stm32f103c8t6.yml")
    for op in syn.route_operations:    assert isinstance(op, RouteOperation)
    for b in syn.interrupt_bindings:    assert isinstance(b, InterruptBinding)
    for v in syn.vector_slots:          assert isinstance(v, VectorSlot)
    for e in syn.signal_endpoints:      assert isinstance(e, SignalEndpoint)
