"""Populate I2C Tier 2/3/4 silicon facts (speeds + TIMINGR presets +
mode flags) per device.json.  Idempotent.  Added by
``add-i2c-tier-2-3-4-data``."""

from __future__ import annotations

import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


# STM32 V2 I2C TIMINGR values from the reference manual application
# note (computed for analog filter on / digital filter off).  Values
# here are illustrative — alloy HAL consumers can override per board.
STM32_TIMINGR_64MHZ = {
    100_000: 0x10707EBB,  # standard mode 100 kHz @ 64 MHz
    400_000: 0x00602173,  # fast mode 400 kHz @ 64 MHz
    1_000_000: 0x00300619,  # fast-mode plus 1 MHz @ 64 MHz
}
STM32_TIMINGR_42MHZ = {
    100_000: 0x10805E89,
    400_000: 0x00B0122A,
}


def stm32g0_i2c_blocks(periph: str) -> dict:
    return {
        "i2c_speed_options": [
            {"peripheral": periph, "speed_hz": 100_000, "mode": "standard"},
            {"peripheral": periph, "speed_hz": 400_000, "mode": "fast"},
            {"peripheral": periph, "speed_hz": 1_000_000, "mode": "fast_plus"},
        ],
        "i2c_timing_presets": [
            {
                "peripheral": periph,
                "speed_hz": speed,
                "source_clock_hz": 64_000_000,
                "timingr_value": value,
            }
            for speed, value in STM32_TIMINGR_64MHZ.items()
        ],
        "i2c_mode_flags": [
            {
                "peripheral": periph,
                "supports_smbus": True,
                "supports_pmbus": False,
                "supports_dma": True,
                "supports_slave": True,
                "supports_dual_address": True,
                "supports_general_call": True,
                "supports_7bit_addressing": True,
                "supports_10bit_addressing": True,
            }
        ],
    }


def stm32f4_i2c_blocks(periph: str) -> dict:
    return {
        "i2c_speed_options": [
            {"peripheral": periph, "speed_hz": 100_000, "mode": "standard"},
            {"peripheral": periph, "speed_hz": 400_000, "mode": "fast"},
        ],
        "i2c_timing_presets": [
            {
                "peripheral": periph,
                "speed_hz": speed,
                "source_clock_hz": 42_000_000,
                "timingr_value": value,
            }
            for speed, value in STM32_TIMINGR_42MHZ.items()
        ],
        "i2c_mode_flags": [
            {
                "peripheral": periph,
                "supports_smbus": True,
                "supports_pmbus": False,
                "supports_dma": True,
                "supports_slave": True,
                "supports_dual_address": True,
                "supports_general_call": True,
                "supports_7bit_addressing": True,
                "supports_10bit_addressing": True,
            }
        ],
    }


def same70_i2c_blocks(periph: str) -> dict:
    return {
        "i2c_speed_options": [
            {"peripheral": periph, "speed_hz": 100_000, "mode": "standard"},
            {"peripheral": periph, "speed_hz": 400_000, "mode": "fast"},
            {"peripheral": periph, "speed_hz": 1_000_000, "mode": "fast_plus"},
        ],
        # SAME70 TWIHS uses CWGR (clock-waveform-generator) instead of
        # STM32 TIMINGR; we surface the speeds + flags but skip presets
        # (consumers compute CWGR from peripheral_clock at runtime).
        "i2c_mode_flags": [
            {
                "peripheral": periph,
                "supports_smbus": False,
                "supports_pmbus": False,
                "supports_dma": True,
                "supports_slave": True,
                "supports_dual_address": False,
                "supports_general_call": True,
                "supports_7bit_addressing": True,
                "supports_10bit_addressing": True,
            }
        ],
    }


def imxrt_i2c_blocks(periph: str) -> dict:
    return {
        "i2c_speed_options": [
            {"peripheral": periph, "speed_hz": 100_000, "mode": "standard"},
            {"peripheral": periph, "speed_hz": 400_000, "mode": "fast"},
            {"peripheral": periph, "speed_hz": 1_000_000, "mode": "fast_plus"},
        ],
        "i2c_mode_flags": [
            {
                "peripheral": periph,
                "supports_smbus": False,
                "supports_pmbus": False,
                "supports_dma": True,
                "supports_slave": True,
                "supports_dual_address": False,
                "supports_general_call": True,
                "supports_7bit_addressing": True,
                "supports_10bit_addressing": True,
            }
        ],
    }


def avrda_twi_blocks(periph: str) -> dict:
    return {
        "i2c_speed_options": [
            {"peripheral": periph, "speed_hz": 100_000, "mode": "standard"},
            {"peripheral": periph, "speed_hz": 400_000, "mode": "fast"},
        ],
        "i2c_mode_flags": [
            {
                "peripheral": periph,
                "supports_smbus": False,
                "supports_pmbus": False,
                "supports_dma": False,
                "supports_slave": True,
                "supports_dual_address": False,
                "supports_general_call": True,
                "supports_7bit_addressing": True,
                "supports_10bit_addressing": False,
            }
        ],
    }


def esp32_i2c_blocks(periph: str) -> dict:
    return {
        "i2c_speed_options": [
            {"peripheral": periph, "speed_hz": 100_000, "mode": "standard"},
            {"peripheral": periph, "speed_hz": 400_000, "mode": "fast"},
            {"peripheral": periph, "speed_hz": 800_000, "mode": "fast_plus"},
        ],
        "i2c_mode_flags": [
            {
                "peripheral": periph,
                "supports_smbus": False,
                "supports_pmbus": False,
                "supports_dma": False,
                "supports_slave": True,
                "supports_dual_address": False,
                "supports_general_call": False,
                "supports_7bit_addressing": True,
                "supports_10bit_addressing": True,
            }
        ],
    }


def rp2040_i2c_blocks(periph: str) -> dict:
    return {
        "i2c_speed_options": [
            {"peripheral": periph, "speed_hz": 100_000, "mode": "standard"},
            {"peripheral": periph, "speed_hz": 400_000, "mode": "fast"},
            {"peripheral": periph, "speed_hz": 1_000_000, "mode": "fast_plus"},
        ],
        "i2c_mode_flags": [
            {
                "peripheral": periph,
                "supports_smbus": False,
                "supports_pmbus": False,
                "supports_dma": True,
                "supports_slave": True,
                "supports_dual_address": False,
                "supports_general_call": True,
                "supports_7bit_addressing": True,
                "supports_10bit_addressing": True,
            }
        ],
    }


KEYS = ("i2c_speed_options", "i2c_timing_presets", "i2c_mode_flags")


def _load(path: Path) -> dict:
    return json.loads(path.read_text())


def _save(path: Path, payload: dict) -> None:
    path.write_text(json.dumps(payload, indent=2) + "\n")


def apply(payload: dict, *blocks: dict) -> None:
    for k in KEYS:
        payload.pop(k, None)
    for block in blocks:
        for key, value in block.items():
            payload.setdefault(key, []).extend(value)


PER_DEVICE = {
    "patches/st/stm32g0/devices/stm32g071rb.json": [
        stm32g0_i2c_blocks(p) for p in ("I2C1", "I2C2")
    ],
    "patches/st/stm32g0/devices/stm32g030f6.json": [stm32g0_i2c_blocks(p) for p in ("I2C1",)],
    "patches/st/stm32g0/devices/stm32g0b1re.json": [
        stm32g0_i2c_blocks(p) for p in ("I2C1", "I2C2")
    ],
    "patches/st/stm32f4/devices/stm32f401re.json": [stm32f4_i2c_blocks("I2C1")],
    "patches/st/stm32f4/devices/stm32f405rg.json": [
        stm32f4_i2c_blocks(p) for p in ("I2C1", "I2C2", "I2C3")
    ],
    "patches/microchip/avr-da/devices/avr128da32.json": [avrda_twi_blocks("TWI0")],
}


def main() -> None:
    for relpath, blocks in PER_DEVICE.items():
        path = ROOT / relpath
        if not path.exists():
            print(f"  skip (missing): {relpath}")
            continue
        payload = _load(path)
        apply(payload, *blocks)
        _save(path, payload)
        print(f"  populated {relpath}")


if __name__ == "__main__":
    main()
