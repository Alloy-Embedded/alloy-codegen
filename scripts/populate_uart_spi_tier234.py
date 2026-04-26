"""One-shot population of UART/SPI Tier 2/3/4 silicon facts across all families.

Idempotent: re-running overwrites the blocks with the same content.
"""

from __future__ import annotations

import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def _load(path: Path) -> dict:
    return json.loads(path.read_text())


def _save(path: Path, payload: dict) -> None:
    path.write_text(json.dumps(payload, indent=2) + "\n")


# ---------------------------------------------------------------------------
# STM32F4 — USART1/USART2 + SPI1.  Older USART (no FIFO), SPI has DFF (8/16).
# ---------------------------------------------------------------------------


def stm32f4_uart_blocks(periph: str) -> dict:
    return {
        "uart_baud_clock_sources": [
            {"peripheral": periph, "source": "pclk", "field_value": 0},
        ],
        "uart_baud_oversampling_options": [
            {"peripheral": periph, "ratio": 16, "field_value": 0},
            {"peripheral": periph, "ratio": 8, "field_value": 1},
        ],
        # F4 USART has no FIFO trigger options.
        "uart_data_bits_options": [
            {"peripheral": periph, "bits": 8, "m0_value": 0, "m1_value": 0},
            {"peripheral": periph, "bits": 9, "m0_value": 1, "m1_value": 0},
        ],
        "uart_parity_options": [
            {"peripheral": periph, "parity": "none", "pce_value": 0, "ps_value": 0},
            {"peripheral": periph, "parity": "even", "pce_value": 1, "ps_value": 0},
            {"peripheral": periph, "parity": "odd", "pce_value": 1, "ps_value": 1},
        ],
        "uart_stop_bits_options": [
            {"peripheral": periph, "stop_bits_q8": 128, "field_value": 1},
            {"peripheral": periph, "stop_bits_q8": 256, "field_value": 0},
            {"peripheral": periph, "stop_bits_q8": 384, "field_value": 3},
            {"peripheral": periph, "stop_bits_q8": 512, "field_value": 2},
        ],
        "uart_mode_flags": [
            {
                "peripheral": periph,
                "supports_lin": True,
                "supports_irda": True,
                "supports_smartcard": True,
                "supports_half_duplex": True,
                "supports_synchronous": True,
                "supports_auto_baud": False,
                "supports_wake_from_stop": False,
            }
        ],
        "uart_max_baud_hz": 10_500_000,
    }


def stm32f4_spi_blocks(periph: str) -> dict:
    return {
        "spi_baud_prescaler_options": [
            {"peripheral": periph, "divisor": 2 << i, "field_value": i} for i in range(8)
        ],
        "spi_frame_size_options": [
            {"peripheral": periph, "bits": 8, "field_value": 0},
            {"peripheral": periph, "bits": 16, "field_value": 1},
        ],
        # F4 SPI has no FIFO threshold field.
        "spi_mode_flags": [
            {
                "peripheral": periph,
                "supports_crc": True,
                "supports_ti_frame": True,
                "supports_motorola_frame": True,
                "supports_i2s_submode": True,
                "supports_bidirectional_3wire": True,
                "supports_lsb_first": True,
                "supports_nss_hw_management": True,
            }
        ],
    }


# ---------------------------------------------------------------------------
# AVR-DA — USART0/1 + SPI0.  No DMA, no FIFO, fixed 8-bit SPI.
# ---------------------------------------------------------------------------


def avrda_uart_blocks(periph: str) -> dict:
    return {
        "uart_baud_clock_sources": [
            {"peripheral": periph, "source": "clk_per", "field_value": 0},
        ],
        "uart_baud_oversampling_options": [
            {"peripheral": periph, "ratio": 16, "field_value": 0},
            {"peripheral": periph, "ratio": 8, "field_value": 1},
        ],
        "uart_data_bits_options": [
            {"peripheral": periph, "bits": 5, "m0_value": 0, "m1_value": 0},
            {"peripheral": periph, "bits": 6, "m0_value": 1, "m1_value": 0},
            {"peripheral": periph, "bits": 7, "m0_value": 2, "m1_value": 0},
            {"peripheral": periph, "bits": 8, "m0_value": 3, "m1_value": 0},
            {"peripheral": periph, "bits": 9, "m0_value": 6, "m1_value": 0},
        ],
        "uart_parity_options": [
            {"peripheral": periph, "parity": "none", "pce_value": 0, "ps_value": 0},
            {"peripheral": periph, "parity": "even", "pce_value": 2, "ps_value": 0},
            {"peripheral": periph, "parity": "odd", "pce_value": 3, "ps_value": 0},
        ],
        "uart_stop_bits_options": [
            {"peripheral": periph, "stop_bits_q8": 256, "field_value": 0},
            {"peripheral": periph, "stop_bits_q8": 512, "field_value": 1},
        ],
        "uart_mode_flags": [
            {
                "peripheral": periph,
                "supports_lin": False,
                "supports_irda": False,
                "supports_smartcard": False,
                "supports_half_duplex": False,
                "supports_synchronous": True,
                "supports_auto_baud": True,
                "supports_wake_from_stop": False,
            }
        ],
        "uart_max_baud_hz": 3_000_000,  # CLK_PER 24 MHz / 8 in DOUBLEX mode
    }


def avrda_spi_blocks(periph: str) -> dict:
    return {
        "spi_baud_prescaler_options": [
            {"peripheral": periph, "divisor": 4, "field_value": 0},
            {"peripheral": periph, "divisor": 16, "field_value": 1},
            {"peripheral": periph, "divisor": 64, "field_value": 2},
            {"peripheral": periph, "divisor": 128, "field_value": 3},
        ],
        "spi_frame_size_options": [
            {"peripheral": periph, "bits": 8, "field_value": 0},
        ],
        "spi_mode_flags": [
            {
                "peripheral": periph,
                "supports_crc": False,
                "supports_ti_frame": False,
                "supports_motorola_frame": True,
                "supports_i2s_submode": False,
                "supports_bidirectional_3wire": False,
                "supports_lsb_first": True,
                "supports_nss_hw_management": True,
            }
        ],
    }


# ---------------------------------------------------------------------------
# iMXRT1060 — LPUART1..8 + LPSPI1..4.  DMA bindings auto-derive.
# ---------------------------------------------------------------------------


def imxrt_lpuart_blocks(periph: str) -> dict:
    return {
        "uart_baud_clock_sources": [
            {"peripheral": periph, "source": "lpuart_clk_root", "field_value": 0},
        ],
        "uart_baud_oversampling_options": [
            {"peripheral": periph, "ratio": ratio, "field_value": ratio - 4} for ratio in (16, 32)
        ],
        "uart_data_bits_options": [
            {"peripheral": periph, "bits": 7, "m0_value": 0, "m1_value": 1},
            {"peripheral": periph, "bits": 8, "m0_value": 0, "m1_value": 0},
            {"peripheral": periph, "bits": 9, "m0_value": 1, "m1_value": 0},
            {"peripheral": periph, "bits": 10, "m0_value": 0, "m1_value": 2},
        ],
        "uart_parity_options": [
            {"peripheral": periph, "parity": "none", "pce_value": 0, "ps_value": 0},
            {"peripheral": periph, "parity": "even", "pce_value": 1, "ps_value": 0},
            {"peripheral": periph, "parity": "odd", "pce_value": 1, "ps_value": 1},
        ],
        "uart_stop_bits_options": [
            {"peripheral": periph, "stop_bits_q8": 256, "field_value": 0},
            {"peripheral": periph, "stop_bits_q8": 512, "field_value": 1},
        ],
        "uart_mode_flags": [
            {
                "peripheral": periph,
                "supports_lin": True,
                "supports_irda": True,
                "supports_smartcard": False,
                "supports_half_duplex": True,
                "supports_synchronous": False,
                "supports_auto_baud": False,
                "supports_wake_from_stop": True,
            }
        ],
        "uart_max_baud_hz": 24_000_000,
    }


def imxrt_lpspi_blocks(periph: str) -> dict:
    return {
        "spi_baud_prescaler_options": [
            {"peripheral": periph, "divisor": 1 << i, "field_value": i} for i in range(8)
        ],
        "spi_frame_size_options": [
            {"peripheral": periph, "bits": bits, "field_value": bits - 1} for bits in (4, 8, 16, 32)
        ],
        "spi_mode_flags": [
            {
                "peripheral": periph,
                "supports_crc": False,
                "supports_ti_frame": False,
                "supports_motorola_frame": True,
                "supports_i2s_submode": False,
                "supports_bidirectional_3wire": False,
                "supports_lsb_first": True,
                "supports_nss_hw_management": True,
            }
        ],
    }


# ---------------------------------------------------------------------------
# RP2040 — UART0/1 (PL011) + SPI0/1 (PL022).  Family-level blocks.
# ---------------------------------------------------------------------------


def rp2040_uart_blocks(periph: str) -> dict:
    return {
        "uart_baud_clock_sources": [
            {"peripheral": periph, "source": "clk_peri", "field_value": 0},
        ],
        "uart_baud_oversampling_options": [
            {"peripheral": periph, "ratio": 16, "field_value": 0},
        ],
        "uart_fifo_trigger_options": [
            {"peripheral": periph, "fraction_q8": 32, "field_value": 0},
            {"peripheral": periph, "fraction_q8": 64, "field_value": 1},
            {"peripheral": periph, "fraction_q8": 128, "field_value": 2},
            {"peripheral": periph, "fraction_q8": 192, "field_value": 3},
            {"peripheral": periph, "fraction_q8": 224, "field_value": 4},
        ],
        "uart_data_bits_options": [
            {"peripheral": periph, "bits": bits, "m0_value": bits - 5, "m1_value": 0}
            for bits in (5, 6, 7, 8)
        ],
        "uart_parity_options": [
            {"peripheral": periph, "parity": "none", "pce_value": 0, "ps_value": 0},
            {"peripheral": periph, "parity": "even", "pce_value": 1, "ps_value": 1},
            {"peripheral": periph, "parity": "odd", "pce_value": 1, "ps_value": 0},
        ],
        "uart_stop_bits_options": [
            {"peripheral": periph, "stop_bits_q8": 256, "field_value": 0},
            {"peripheral": periph, "stop_bits_q8": 512, "field_value": 1},
        ],
        "uart_mode_flags": [
            {
                "peripheral": periph,
                "supports_lin": False,
                "supports_irda": True,
                "supports_smartcard": False,
                "supports_half_duplex": True,
                "supports_synchronous": False,
                "supports_auto_baud": False,
                "supports_wake_from_stop": False,
            }
        ],
        "uart_max_baud_hz": 7_812_500,
    }


def rp2040_spi_blocks(periph: str) -> dict:
    return {
        "spi_baud_prescaler_options": [
            {"peripheral": periph, "divisor": 1 << i, "field_value": i} for i in range(1, 9)
        ],
        "spi_frame_size_options": [
            {"peripheral": periph, "bits": bits, "field_value": bits - 1} for bits in range(4, 17)
        ],
        "spi_mode_flags": [
            {
                "peripheral": periph,
                "supports_crc": False,
                "supports_ti_frame": True,
                "supports_motorola_frame": True,
                "supports_i2s_submode": False,
                "supports_bidirectional_3wire": False,
                "supports_lsb_first": False,
                "supports_nss_hw_management": True,
            }
        ],
    }


# ---------------------------------------------------------------------------
# ESP32 family — per-family overlays on family.json (one set per silicon).
# ---------------------------------------------------------------------------


def esp_uart_blocks(periph: str, *, supports_lin: bool) -> dict:
    return {
        "uart_baud_clock_sources": [
            {"peripheral": periph, "source": "apb", "field_value": 0},
            {"peripheral": periph, "source": "ref_tick", "field_value": 1},
            {"peripheral": periph, "source": "xtal", "field_value": 2},
            {"peripheral": periph, "source": "rc_fast", "field_value": 3},
        ],
        "uart_baud_oversampling_options": [
            {"peripheral": periph, "ratio": 16, "field_value": 0},
        ],
        "uart_data_bits_options": [
            {"peripheral": periph, "bits": bits, "m0_value": bits - 5, "m1_value": 0}
            for bits in (5, 6, 7, 8)
        ],
        "uart_parity_options": [
            {"peripheral": periph, "parity": "none", "pce_value": 0, "ps_value": 0},
            {"peripheral": periph, "parity": "even", "pce_value": 1, "ps_value": 0},
            {"peripheral": periph, "parity": "odd", "pce_value": 1, "ps_value": 1},
        ],
        "uart_stop_bits_options": [
            {"peripheral": periph, "stop_bits_q8": 256, "field_value": 1},
            {"peripheral": periph, "stop_bits_q8": 384, "field_value": 2},
            {"peripheral": periph, "stop_bits_q8": 512, "field_value": 3},
        ],
        "uart_mode_flags": [
            {
                "peripheral": periph,
                "supports_lin": supports_lin,
                "supports_irda": True,
                "supports_smartcard": False,
                "supports_half_duplex": True,
                "supports_synchronous": False,
                "supports_auto_baud": True,
                "supports_wake_from_stop": True,
            }
        ],
        "uart_max_baud_hz": 5_000_000,
    }


def esp_spi_blocks(periph: str) -> dict:
    return {
        "spi_baud_prescaler_options": [
            {"peripheral": periph, "divisor": 1 << i, "field_value": i} for i in range(1, 9)
        ],
        "spi_frame_size_options": [
            {"peripheral": periph, "bits": bits, "field_value": bits - 1} for bits in (4, 8, 16, 32)
        ],
        "spi_mode_flags": [
            {
                "peripheral": periph,
                "supports_crc": False,
                "supports_ti_frame": False,
                "supports_motorola_frame": True,
                "supports_i2s_submode": False,
                "supports_bidirectional_3wire": True,
                "supports_lsb_first": True,
                "supports_nss_hw_management": True,
            }
        ],
    }


# ---------------------------------------------------------------------------
# Apply blocks
# ---------------------------------------------------------------------------


KEYS_UART = (
    "uart_baud_clock_sources",
    "uart_baud_oversampling_options",
    "uart_fifo_trigger_options",
    "uart_data_bits_options",
    "uart_parity_options",
    "uart_stop_bits_options",
    "uart_mode_flags",
    "uart_max_baud_hz",
)
KEYS_SPI = (
    "spi_baud_prescaler_options",
    "spi_frame_size_options",
    "spi_fifo_threshold_options",
    "spi_mode_flags",
)


def apply_blocks(payload: dict, *blocks: dict) -> None:
    """Merge multiple block dicts into ``payload`` (extending list fields,
    overwriting scalars).  Idempotent w.r.t. duplicate per-peripheral entries
    is *not* guaranteed — caller must avoid populating the same peripheral
    twice."""
    # Reset known keys so re-runs replace, not accumulate.
    for key in KEYS_UART + KEYS_SPI:
        payload.pop(key, None)
    for block in blocks:
        for key, value in block.items():
            if isinstance(value, list):
                payload.setdefault(key, []).extend(value)
            else:
                payload[key] = value


def main() -> None:
    # STM32F4 devices.
    for dev in ("stm32f401re.json", "stm32f405rg.json"):
        path = ROOT / "patches" / "st" / "stm32f4" / "devices" / dev
        payload = _load(path)
        apply_blocks(
            payload,
            stm32f4_uart_blocks("USART1"),
            stm32f4_uart_blocks("USART2"),
            stm32f4_spi_blocks("SPI1"),
        )
        _save(path, payload)
        print(f"  populated {path.relative_to(ROOT)}")

    # AVR-DA — per-device.json (mirrors how adc_resolution_options is stored).
    for dev in ("avr128da32.json",):
        path = ROOT / "patches" / "microchip" / "avr-da" / "devices" / dev
        payload = _load(path)
        apply_blocks(
            payload,
            avrda_uart_blocks("USART0"),
            avrda_uart_blocks("USART1"),
            avrda_spi_blocks("SPI0"),
        )
        _save(path, payload)
        print(f"  populated {path.relative_to(ROOT)}")

    # iMXRT1060 — per-device.json.
    for dev in ("mimxrt1062.json", "mimxrt1064.json"):
        path = ROOT / "patches" / "nxp" / "imxrt1060" / "devices" / dev
        payload = _load(path)
        blocks: list[dict] = []
        for i in range(1, 9):
            blocks.append(imxrt_lpuart_blocks(f"LPUART{i}"))
        for i in range(1, 5):
            blocks.append(imxrt_lpspi_blocks(f"LPSPI{i}"))
        apply_blocks(payload, *blocks)
        _save(path, payload)
        print(f"  populated {path.relative_to(ROOT)}")

    # RP2040 — per-device.json.
    for dev in ("rp2040.json", "pico.json"):
        path = ROOT / "patches" / "raspberrypi" / "rp2040" / "devices" / dev
        payload = _load(path)
        apply_blocks(
            payload,
            rp2040_uart_blocks("UART0"),
            rp2040_uart_blocks("UART1"),
            rp2040_spi_blocks("SPI0"),
            rp2040_spi_blocks("SPI1"),
        )
        _save(path, payload)
        print(f"  populated {path.relative_to(ROOT)}")

    # ESP32 — per-device.json.
    esp_specs = [
        ("esp32", ["esp32.json", "esp32-wroom32.json"], ["UART0"], ["SPI0"], False),
        ("esp32c3", ["esp32c3.json"], ["UART0", "UART1"], ["SPI2"], False),
        ("esp32s3", ["esp32s3.json"], ["UART0", "UART1", "UART2"], ["SPI2", "SPI3"], True),
    ]
    for family, devs, uarts, spis, lin in esp_specs:
        for dev in devs:
            path = ROOT / "patches" / "espressif" / family / "devices" / dev
            payload = _load(path)
            blocks = [esp_uart_blocks(u, supports_lin=lin) for u in uarts]
            blocks.extend(esp_spi_blocks(s) for s in spis)
            apply_blocks(payload, *blocks)
            _save(path, payload)
            print(f"  populated {path.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
