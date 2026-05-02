"""Tests for the core v2.1 emitters: peripheral_traits + runtime_init."""

from __future__ import annotations

from pathlib import Path

import pytest

from alloy_codegen.canonical_device_v2_1 import parse_device
from alloy_codegen.emit_v2_1 import (
    emit_peripheral_traits,
    emit_runtime_init,
)
from alloy_codegen.ir.synthesised import build_synthesised

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


def _bundle(name: str):
    text = _hand_yaml(name).read_text(encoding="utf-8")
    device = parse_device(text)
    return device, build_synthesised(device)


# ---------------------------------------------------------------------------
# peripheral_traits.h
# ---------------------------------------------------------------------------


@pytest.mark.parametrize(
    "name",
    ["stm32f103c8t6.yml", "atmega328p.yml", "esp32-wroom32.yml",
     "nrf52840.yml", "rp2040.yml"],
)
def test_peripheral_traits_emits_header_for_every_chip(name: str) -> None:
    device, syn = _bundle(name)
    text = emit_peripheral_traits(device, syn)
    assert "#ifndef" in text and "#define" in text and "#endif" in text
    assert f"namespace alloy::{device.identity.vendor}" in text
    assert "#include <cstdint>" in text


def test_peripheral_traits_emits_kBaseAddress_per_instance() -> None:
    device, syn = _bundle("stm32f103c8t6.yml")
    text = emit_peripheral_traits(device, syn)
    # Every peripheral with a base address surfaces a kBaseAddress line.
    for per in device.peripherals:
        if per.base is not None:
            assert "kBaseAddress" in text


def test_peripheral_traits_field_constants_have_bit_position() -> None:
    """spi.cr1.spe sits at bit 6 in the hand-crafted STM32 template."""
    device, syn = _bundle("stm32f103c8t6.yml")
    text = emit_peripheral_traits(device, syn)
    assert "namespace cr1_spe" in text
    assert "constexpr unsigned bit  = 6;" in text


def test_peripheral_traits_emit_enum_values_when_declared() -> None:
    """SPI BR field carries enum values div_2..div_256."""
    device, syn = _bundle("stm32f103c8t6.yml")
    text = emit_peripheral_traits(device, syn)
    assert "enum class value : unsigned" in text
    assert "div_2 = 0," in text
    assert "div_256 = 7," in text


def test_peripheral_traits_marks_irq_per_peripheral() -> None:
    device, syn = _bundle("stm32f103c8t6.yml")
    text = emit_peripheral_traits(device, syn)
    # USART2 is at NVIC line 38 in the hand-crafted YAML.
    assert "kIrqLines[]" in text
    assert "USART2_IRQHandler" in text


def test_peripheral_traits_carries_provenance_in_header_comment() -> None:
    device, syn = _bundle("stm32f103c8t6.yml")
    text = emit_peripheral_traits(device, syn)
    assert device.provenance.primary in text
    assert "alloy.device.v2.1" in text


# ---------------------------------------------------------------------------
# runtime_init.c
# ---------------------------------------------------------------------------


@pytest.mark.parametrize(
    "name",
    ["stm32f103c8t6.yml", "atmega328p.yml", "esp32-wroom32.yml",
     "nrf52840.yml", "rp2040.yml"],
)
def test_runtime_init_emits_for_every_chip(name: str) -> None:
    device, syn = _bundle(name)
    text = emit_runtime_init(device, syn)
    assert "AlloyRouteOperation" in text
    assert "alloy_runtime_apply_op" in text
    assert "alloy_runtime_init_peripherals" in text


def test_runtime_init_table_size_matches_synthesised_count() -> None:
    """One row in kRouteOperations[] per RouteOperation."""
    device, syn = _bundle("stm32f103c8t6.yml")
    text = emit_runtime_init(device, syn)
    # Each row is exactly one ``    { "operation:...` initializer.
    row_count = text.count("    { \"operation:")
    assert row_count == len(syn.route_operations)


def test_runtime_init_emits_one_fn_per_clock_profile() -> None:
    device, syn = _bundle("stm32f103c8t6.yml")
    text = emit_runtime_init(device, syn)
    for profile in device.clock.profiles:
        # Function name is sanitised — matches alloy_clock_apply_<id>.
        safe_id = profile.id.replace("-", "_")
        assert f"alloy_clock_apply_{safe_id}" in text


def test_runtime_init_handles_chips_without_route_operations() -> None:
    """AVR has no rcc.en / rst entries; emitter must produce a valid
    empty table (NULL pointer + 0 count)."""
    device, syn = _bundle("atmega328p.yml")
    assert len(syn.route_operations) == 0
    text = emit_runtime_init(device, syn)
    assert "kRouteOperations = NULL" in text
    assert "kRouteOperationCount = 0" in text


def test_runtime_init_carries_provenance_in_header_comment() -> None:
    device, syn = _bundle("rp2040.yml")
    text = emit_runtime_init(device, syn)
    assert device.provenance.primary in text
    assert "alloy.device.v2.1" in text
