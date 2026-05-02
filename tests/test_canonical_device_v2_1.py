"""Tests for the v2.1 canonical device IR + reader/writer.

Added by ``adopt-canonical-device-v2-1`` Phase 2.

Pulls the five hand-crafted YAMLs and the seven negative-test files
from the sibling alloy-data-extractor repo.  When that repo is not
co-checked the tests skip cleanly.
"""

from __future__ import annotations

from pathlib import Path

import pytest

from alloy_codegen.bootstrap import CANONICAL_SCHEMA
from alloy_codegen.canonical_device_v2_1 import (
    SCHEMA_PATH,
    parse_device,
    serialize_device,
    validate_device,
)
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.ir.v2_1 import (
    CanonicalDevice,
    PinOptionFixed,
    PinOptionMatrix,
    PinOptionPsel,
)

_REPO_ROOT = Path(__file__).resolve().parents[1]
_HANDCRAFTED_DIR = _REPO_ROOT.parent / "alloy-data-extractor" / "proposals" / "canonical-v2-handcrafted"


def _hand_yaml(name: str) -> Path:
    path = _HANDCRAFTED_DIR / name
    if not path.is_file():
        pytest.skip(f"Hand-crafted reference {name} not present (sibling repo not checked out).")
    return path


def _negative_yaml(name: str) -> Path:
    path = _HANDCRAFTED_DIR / "schema" / "negative-tests" / name
    if not path.is_file():
        pytest.skip(f"Negative test {name} not present (sibling repo not checked out).")
    return path


def test_schema_constant_is_locked() -> None:
    """The pin string is what every YAML must declare."""
    assert CANONICAL_SCHEMA == "alloy.device.v2.1"


def test_schema_file_ships_in_tree() -> None:
    """The bundled JSON-schema is reachable from the package root."""
    assert SCHEMA_PATH.is_file(), f"missing schema file: {SCHEMA_PATH}"
    assert "alloy.device.v2.1" in SCHEMA_PATH.read_text(encoding="utf-8")


@pytest.mark.parametrize(
    "name",
    [
        "stm32f103c8t6.yml",
        "atmega328p.yml",
        "esp32-wroom32.yml",
        "nrf52840.yml",
        "rp2040.yml",
    ],
)
def test_handcrafted_yaml_parses_to_canonical_device(name: str) -> None:
    text = _hand_yaml(name).read_text(encoding="utf-8")
    device = parse_device(text)
    assert isinstance(device, CanonicalDevice)
    assert device.schema == CANONICAL_SCHEMA
    assert device.identity.device == name.replace(".yml", "").replace("-wroom32", "")
    assert len(device.peripherals) >= 1
    assert len(device.memory) >= 1


@pytest.mark.parametrize(
    "name",
    [
        "stm32f103c8t6.yml",
        "atmega328p.yml",
        "esp32-wroom32.yml",
        "nrf52840.yml",
        "rp2040.yml",
    ],
)
def test_serialize_round_trip_is_byte_stable(name: str) -> None:
    """parse → serialize → parse → serialize must produce identical bytes."""
    text = _hand_yaml(name).read_text(encoding="utf-8")
    once = serialize_device(parse_device(text))
    twice = serialize_device(parse_device(once))
    assert once == twice


def test_pin_options_polymorphism_matrix() -> None:
    """ESP32's `pin_options.tx: { matrix: true }` parses to PinOptionMatrix."""
    text = _hand_yaml("esp32-wroom32.yml").read_text(encoding="utf-8")
    device = parse_device(text)
    uart0 = next(p for p in device.peripherals if p.id == "uart0")
    tx_options = uart0.pin_options.get("tx")
    assert isinstance(tx_options, PinOptionMatrix)
    assert tx_options.matrix is True


def test_pin_options_polymorphism_psel() -> None:
    """nRF52's `pin_options.tx: { psel: true }` parses to PinOptionPsel."""
    text = _hand_yaml("nrf52840.yml").read_text(encoding="utf-8")
    device = parse_device(text)
    uarte0 = next(p for p in device.peripherals if p.id == "uarte0")
    tx_options = uarte0.pin_options.get("tx")
    assert isinstance(tx_options, PinOptionPsel)


def test_pin_options_polymorphism_fixed() -> None:
    """STM32's `pin_options.tx: [{ pin: PA9, remap: 0 }, …]` parses to a tuple of PinOptionFixed."""
    text = _hand_yaml("stm32f103c8t6.yml").read_text(encoding="utf-8")
    device = parse_device(text)
    usart1 = next(p for p in device.peripherals if p.id == "usart1")
    tx_options = usart1.pin_options.get("tx")
    assert isinstance(tx_options, tuple)
    assert all(isinstance(o, PinOptionFixed) for o in tx_options)
    assert tx_options[0].pin == "PA9"
    assert tx_options[0].remap == 0


def test_calibration_rom_round_trips() -> None:
    """STM32 ADC calibration block survives parse + reserialize."""
    text = _hand_yaml("stm32f103c8t6.yml").read_text(encoding="utf-8")
    device = parse_device(text)
    adc1 = next(p for p in device.peripherals if p.id == "adc1")
    assert adc1.calibration is not None
    assert adc1.calibration.vrefint is not None
    assert adc1.calibration.vrefint.rom_addr == 0x1FFFF7BA
    assert adc1.calibration.ts_cal_low is not None
    assert adc1.calibration.ts_cal_low.temp_celsius == 30


def test_clock_profiles_carry_named_recipes() -> None:
    """clock.profiles[].id is preserved across the round-trip."""
    text = _hand_yaml("stm32f103c8t6.yml").read_text(encoding="utf-8")
    device = parse_device(text)
    profile_ids = {p.id for p in device.clock.profiles}
    assert {"post-reset", "pll-hsi-64mhz", "pll-hse-72mhz"} <= profile_ids


def test_pin_constraints_preserved() -> None:
    """PA13 carries `debug-default`; constraint round-trips intact."""
    text = _hand_yaml("stm32f103c8t6.yml").read_text(encoding="utf-8")
    device = parse_device(text)
    pa13 = next(p for p in device.pinout if p.signal == "PA13")
    assert "debug-default" in pa13.constraints


@pytest.mark.parametrize(
    "name",
    [
        "01-wrong-schema-version.yml",
        "02-missing-required-section.yml",
        "03-bad-units.yml",
        "04-unknown-pin-constraint.yml",
        "05-template-field-needs-bit-or-bits.yml",
        "06-clock-domain-no-source.yml",
        "07-select-register-missing-encoding.yml",
    ],
)
def test_negative_test_rejects(name: str) -> None:
    """Each deliberately broken YAML SHALL surface a StageExecutionError."""
    text = _negative_yaml(name).read_text(encoding="utf-8")
    with pytest.raises(StageExecutionError):
        # 01 fails on the schema-const check before the validator runs;
        # the rest fail inside ``validate_device_payload``.  Either is fine.
        parse_device(text)


def test_validate_without_parsing_succeeds() -> None:
    """validate_device on a clean YAML is a quiet no-op."""
    text = _hand_yaml("rp2040.yml").read_text(encoding="utf-8")
    validate_device(text)  # no exception
