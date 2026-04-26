"""Populate ``peripheral_max_clock_hz`` per device.json from datasheet
ceilings (added by ``add-kernel-clock-traits``).  Idempotent.
"""

from __future__ import annotations

import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def _entries(*pairs: tuple[str, int]) -> list[dict]:
    return [{"peripheral": p, "max_clock_hz": hz} for p, hz in pairs]


# Per-family per-peripheral input clock ceilings.  When a family has
# multiple devices with the same peripherals, the same map is shared.
PER_DEVICE = {
    # STM32G0 — single PCLK, max 64 MHz.
    "patches/st/stm32g0/devices/stm32g071rb.json": _entries(
        ("USART1", 64_000_000),
        ("USART2", 64_000_000),
        ("SPI1", 64_000_000),
        ("I2C1", 64_000_000),
        ("I2C2", 64_000_000),
    ),
    "patches/st/stm32g0/devices/stm32g030f6.json": _entries(
        ("USART2", 64_000_000),
        ("SPI1", 64_000_000),
    ),
    "patches/st/stm32g0/devices/stm32g0b1re.json": _entries(
        ("USART1", 64_000_000),
        ("USART2", 64_000_000),
        ("USART3", 64_000_000),
        ("USART4", 64_000_000),
        ("SPI1", 64_000_000),
        ("I2C1", 64_000_000),
        ("I2C2", 64_000_000),
    ),
    # STM32F4 — APB2 84 MHz (USART1/USART6/SPI1), APB1 42 MHz (rest).
    "patches/st/stm32f4/devices/stm32f401re.json": _entries(
        ("USART1", 84_000_000),
        ("USART2", 42_000_000),
        ("USART6", 84_000_000),
        ("SPI1", 84_000_000),
        ("SPI2", 42_000_000),
        ("I2C1", 42_000_000),
    ),
    "patches/st/stm32f4/devices/stm32f405rg.json": _entries(
        ("USART1", 84_000_000),
        ("USART2", 42_000_000),
        ("USART3", 42_000_000),
        ("USART6", 84_000_000),
        ("SPI1", 84_000_000),
        ("SPI2", 42_000_000),
        ("SPI3", 42_000_000),
        ("I2C1", 42_000_000),
        ("I2C2", 42_000_000),
        ("I2C3", 42_000_000),
    ),
    # SAME70 — peripheral clock max 150 MHz.
    "patches/microchip/same70/devices/atsame70n21b.json": _entries(
        *((f"USART{i}", 150_000_000) for i in range(3)),
        *((f"UART{i}", 150_000_000) for i in range(5)),
        ("SPI0", 150_000_000),
        ("SPI1", 150_000_000),
    ),
    "patches/microchip/same70/devices/atsame70q21b.json": _entries(
        *((f"USART{i}", 150_000_000) for i in range(3)),
        *((f"UART{i}", 150_000_000) for i in range(5)),
        ("SPI0", 150_000_000),
        ("SPI1", 150_000_000),
    ),
    # iMXRT1060 — LPUART_CLK_ROOT 80 MHz; LPSPI 60 MHz.
    "patches/nxp/imxrt1060/devices/mimxrt1062.json": _entries(
        *((f"LPUART{i}", 80_000_000) for i in range(1, 9)),
        *((f"LPSPI{i}", 60_000_000) for i in range(1, 5)),
    ),
    "patches/nxp/imxrt1060/devices/mimxrt1064.json": _entries(
        *((f"LPUART{i}", 80_000_000) for i in range(1, 9)),
        *((f"LPSPI{i}", 60_000_000) for i in range(1, 5)),
    ),
    # AVR-DA — CLK_PER 24 MHz peak.
    "patches/microchip/avr-da/devices/avr128da32.json": _entries(
        ("USART0", 24_000_000),
        ("USART1", 24_000_000),
        ("SPI0", 24_000_000),
    ),
    # RP2040 — peri_clk 125 MHz.
    "patches/raspberrypi/rp2040/devices/rp2040.json": _entries(
        ("UART0", 125_000_000),
        ("UART1", 125_000_000),
        ("SPI0", 125_000_000),
        ("SPI1", 125_000_000),
    ),
    "patches/raspberrypi/rp2040/devices/pico.json": _entries(
        ("UART0", 125_000_000),
        ("UART1", 125_000_000),
        ("SPI0", 125_000_000),
        ("SPI1", 125_000_000),
    ),
    # ESP32 family — APB 80 MHz.
    "patches/espressif/esp32/devices/esp32.json": _entries(
        ("UART0", 80_000_000),
        ("SPI0", 80_000_000),
    ),
    "patches/espressif/esp32/devices/esp32-wroom32.json": _entries(
        ("UART0", 80_000_000),
        ("SPI0", 80_000_000),
    ),
    "patches/espressif/esp32c3/devices/esp32c3.json": _entries(
        ("UART0", 80_000_000),
        ("UART1", 80_000_000),
        ("SPI2", 80_000_000),
    ),
    "patches/espressif/esp32s3/devices/esp32s3.json": _entries(
        ("UART0", 80_000_000),
        ("UART1", 80_000_000),
        ("UART2", 80_000_000),
        ("SPI2", 80_000_000),
        ("SPI3", 80_000_000),
    ),
}


def main() -> None:
    for relpath, entries in PER_DEVICE.items():
        path = ROOT / relpath
        payload = json.loads(path.read_text())
        payload["peripheral_max_clock_hz"] = entries
        path.write_text(json.dumps(payload, indent=2) + "\n")
        print(f"  populated {relpath}")


if __name__ == "__main__":
    main()
