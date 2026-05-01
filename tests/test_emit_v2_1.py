"""Tests for the v2.1 demo emitters (Phase 4 proof-of-life)."""

from __future__ import annotations

from pathlib import Path

import pytest

from alloy_codegen.canonical_device_v2_1 import parse_device
from alloy_codegen.emit_v2_1 import emit_linker_script, emit_vector_table
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


@pytest.mark.parametrize(
    "name",
    ["stm32f103c8t6.yml", "atmega328p.yml", "esp32-wroom32.yml",
     "nrf52840.yml", "rp2040.yml"],
)
def test_linker_script_emits_for_every_chip(name: str) -> None:
    device = parse_device(_hand_yaml(name).read_text(encoding="utf-8"))
    text = emit_linker_script(device)
    assert "ENTRY(Reset_Handler)" in text
    assert "MEMORY {" in text
    assert device.identity.device in text
    # At least the primary code region is mapped.
    assert "ORIGIN" in text and "LENGTH" in text


def test_linker_script_marks_harvard_program_space_on_avr() -> None:
    device = parse_device(_hand_yaml("atmega328p.yml").read_text(encoding="utf-8"))
    text = emit_linker_script(device)
    assert "Harvard program space" in text
    assert "Harvard data space" in text


def test_linker_script_marks_xip_backing_on_rp2040() -> None:
    device = parse_device(_hand_yaml("rp2040.yml").read_text(encoding="utf-8"))
    text = emit_linker_script(device)
    assert "XIP-mapped external QSPI flash" in text


def test_linker_script_keeps_factory_rom_uncompiled() -> None:
    """ESP32 declares a 384 KB factory ROM; the script lists it but
    flags it as no-section-placement."""
    device = parse_device(_hand_yaml("esp32-wroom32.yml").read_text(encoding="utf-8"))
    text = emit_linker_script(device)
    assert "factory-rom" in text
    assert "no section placement" in text


@pytest.mark.parametrize(
    "name",
    ["stm32f103c8t6.yml", "atmega328p.yml", "nrf52840.yml", "rp2040.yml"],
)
def test_vector_table_emits_c_array_for_fixed_chips(name: str) -> None:
    device = parse_device(_hand_yaml(name).read_text(encoding="utf-8"))
    syn = build_synthesised(device)
    text = emit_vector_table(device, syn)
    assert "_vector_table" in text
    assert "extern void " in text
    assert "__attribute__((section(\".isr_vector\")" in text


def test_vector_table_marks_matrix_chip_as_runtime_routed() -> None:
    device = parse_device(_hand_yaml("esp32-wroom32.yml").read_text(encoding="utf-8"))
    syn = build_synthesised(device)
    text = emit_vector_table(device, syn)
    assert "runtime interrupt matrix" in text
    assert "_vector_table" not in text  # no fixed table for matrix chips


def test_vector_table_includes_provenance_in_header() -> None:
    """Generated artifacts cite their schema + provenance."""
    device = parse_device(_hand_yaml("stm32f103c8t6.yml").read_text(encoding="utf-8"))
    syn = build_synthesised(device)
    text = emit_vector_table(device, syn)
    assert "alloy.device.v2.1" in text
    assert device.provenance.primary in text
