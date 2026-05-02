"""Espressif ESP32 / C3 / S3 clock-gate truth tables.

Each chip carries one or more *gate register groups* — pairs of
``(enable_register, reset_register)`` whose fields are named
``<peri>_clk_en`` / ``<peri>_rst`` (or, on the CPU-side ESP32-C3 / S3
``cpu_peri_*`` group, the prefix-suffix-flipped form
``clk_en_<peri>`` / ``rst_en_<peri>``).  The synthesiser
(:mod:`alloy_codegen.ir.synthesised.builder._synthesise_esp32_rcc`)
walks each group, strips the suffix, applies the chip's
``field_aliases`` map to handle legacy / vendor-quirk names
(``uart_*`` → ``uart0``, ``crypto_aes_*`` → ``aes`` …), and emits
``en`` / ``rst`` paths shaped like ``<template>.<reg>.<field>``.

The PCR self-contained group on ESP32-C3 / S3 is handled specially:
gates live inside the peripheral's *own* register block
(``pcr.<peri>_conf_reg.<peri>_clk_en`` /
``pcr.<peri>_conf0_reg.<peri>_clk_en`` for UART), so the bus tag is
``PCR`` and the field discovery is regex-driven instead of alias-
driven.

Reference manuals consulted:
    * ESP32 Technical Reference Manual v5.4, §3.2 (System & Memory)
    * ESP32-C3 Technical Reference Manual v1.1, §6 (System Register)
    * ESP32-S3 Technical Reference Manual v1.3, §6 (SYSTEM)
    * ESP32-C3 / S3 PCR section: §6.4 (Peripheral Clock Reset)
"""

from __future__ import annotations

from typing import NamedTuple


class GateRegisterGroup(NamedTuple):
    """One pair of (enable, reset) registers inside a template.

    ``en_suffix`` and ``rst_suffix`` describe how peripheral names
    appear inside the field id:

    * ``"_clk_en"`` / ``"_rst"`` — suffix form (typical):
      ``perip_clk_en.uart_clk_en`` strips to ``"uart"``.
    * ``"clk_en_"`` / ``"rst_en_"`` — prefix form (CPU-side C3/S3):
      ``cpu_peri_clk_en.clk_en_assist_debug`` strips to
      ``"assist_debug"``.

    ``prefix_form`` flips the strip direction: ``True`` → strip from
    the head, ``False`` → strip from the tail.
    """

    en_register: str
    rst_register: str
    en_suffix: str
    rst_suffix: str
    prefix_form: bool = False


# ----------------------------------------------------------------------
# ESP32 (original) — all gates in DPORT
# ----------------------------------------------------------------------

ESP32_DPORT_GROUPS: tuple[GateRegisterGroup, ...] = (
    GateRegisterGroup(
        en_register="perip_clk_en",
        rst_register="perip_rst_en",
        en_suffix="_clk_en",
        rst_suffix="_rst",
    ),
)

# Map a stripped field-name → canonical peripheral id (or list of ids
# for shared gates).  Only entries that don't match an existing
# peripheral id directly need to appear here.
ESP32_FIELD_ALIASES: dict[str, str | tuple[str, ...]] = {
    # `uart_clk_en` is the legacy name for UART0 (UART1/2 use the
    # numbered form).
    "uart": "uart0",
    # I²C: ESP32 has the legacy `_ext0` / `_ext1` infix suffix.
    "i2c0_ext0": "i2c0",
    "i2c_ext1": "i2c1",
    # Timer groups: `timergroup` / `timergroup1`.
    "timergroup": "timg0",
    "timergroup1": "timg1",
    # SPI: SPI0 and SPI1 share a single gate bit (`spi01_clk_en`).
    "spi01": ("spi0", "spi1"),
    # TWAI is an instance, just renamed.
    "twai": "twai0",
    # UHCI is an instance, just renamed.  Both already match by
    # default (uhci0/uhci1) — no alias needed.
}

# Field stems we deliberately ignore (no peripheral on the chip):
#   * `wdg` is the legacy global watchdog (lives inside timg).
#   * `peri` / `peri_clk_en` / `core_rst` / `uart_mem` are not per-
#     peripheral gates.
#   * `pwm0..pwm3` are the legacy MCPWM channel-pair gates; the
#     mapping to `mcpwm0` / `mcpwm1` is non-obvious (PWM0/PWM1 →
#     MCPWM0, PWM2/PWM3 → MCPWM1?) and needs RM verification before
#     wire-up.  TODO: revisit once mcpwm HAL needs it.
#   * `timers` is the global gate covering timg0+timg1 (redundant
#     with timergroup/timergroup1).
#   * `spi_dma` is the SPI DMA controller (a separate template, not
#     a per-SPI gate).
ESP32_SKIP_STEMS: frozenset[str] = frozenset(
    {
        "wdg",
        "peri",
        "peri_clk_en",
        "core_rst",
        "uart_mem",
        "timers",
        "spi_dma",
        "pwm0",
        "pwm1",
        "pwm2",
        "pwm3",
    }
)


# ----------------------------------------------------------------------
# ESP32-C3 — gates split across SYSTEM and PCR templates
# ----------------------------------------------------------------------

ESP32C3_SYSTEM_GROUPS: tuple[GateRegisterGroup, ...] = (
    GateRegisterGroup(
        en_register="perip_clk_en0",
        rst_register="perip_rst_en0",
        en_suffix="_clk_en",
        rst_suffix="_rst",
    ),
    GateRegisterGroup(
        en_register="perip_clk_en1",
        rst_register="perip_rst_en1",
        en_suffix="_clk_en",
        rst_suffix="_rst",
    ),
    # CPU-side peripherals — note the prefix-form ``clk_en_`` /
    # ``rst_en_`` (the suffix is the peripheral name).
    GateRegisterGroup(
        en_register="cpu_peri_clk_en",
        rst_register="cpu_peri_rst_en",
        en_suffix="clk_en_",
        rst_suffix="rst_en_",
        prefix_form=True,
    ),
)

ESP32C3_FIELD_ALIASES: dict[str, str | tuple[str, ...]] = {
    "uart": "uart0",
    # I²C external mux infix.
    "i2c_ext0": "i2c0",
    # Crypto block instances.
    "crypto_aes": "aes",
    "crypto_ds": "ds",
    "crypto_hmac": "hmac",
    "crypto_rsa": "rsa",
    "crypto_sha": "sha",
    # Timer groups.
    "timergroup": "timg0",
    "timergroup1": "timg1",
    # SPI shared gate.
    "spi01": ("spi0", "spi1"),
    # TWAI / DMA / UART2 — direct id matches; no alias needed.
    "twai": "twai0",
}

ESP32C3_SKIP_STEMS: frozenset[str] = frozenset(
    {
        "wdg",
        "peri",
        "peri_clk_en",
        "uart_mem",
        "timers",
        "spi2_dma",
        "spi3_dma",
        "spi4",  # not present on C3
        "ext1",
        "adc2_arb",
        "tsens",
        "lcd_cam",
        "sdio_host",
        "dedicated_gpio",
        "pwm0",
        "pwm1",
        "pwm2",
        "pwm3",
        "pcnt",  # ESP32-C3 has no PCNT peripheral despite a stub field
    }
)


# ----------------------------------------------------------------------
# ESP32-S3 — same layout as C3, plus a few extra peripherals.
# ----------------------------------------------------------------------

ESP32S3_SYSTEM_GROUPS: tuple[GateRegisterGroup, ...] = ESP32C3_SYSTEM_GROUPS

ESP32S3_FIELD_ALIASES: dict[str, str | tuple[str, ...]] = {
    "uart": "uart0",
    "i2c_ext0": "i2c0",
    "i2c_ext1": "i2c1",
    "crypto_aes": "aes",
    "crypto_ds": "ds",
    "crypto_hmac": "hmac",
    "crypto_rsa": "rsa",
    "crypto_sha": "sha",
    "timergroup": "timg0",
    "timergroup1": "timg1",
    "spi01": ("spi0", "spi1"),
    "twai": "twai0",
    # USB block: the SYSTEM gate names the OTG controller "usb",
    # which on S3 maps to the usb_wrap peripheral — but we leave it
    # to the inline ``rcc:`` block on the YAML to disambiguate
    # (usb_device has its own gate).  Default alias here keeps the
    # USB OTG mapping conservative.
    "usb": "usb_wrap",
}

ESP32S3_SKIP_STEMS: frozenset[str] = frozenset(
    {
        "wdg",
        "peri",
        "peri_clk_en",
        "uart_mem",
        "timers",
        "spi2_dma",
        "spi3_dma",
        "spi4",  # not present on S3
        "adc2_arb",
        "tsens",
        "sdio_host",
        "dedicated_gpio",
        "pwm0",
        "pwm1",
        "pwm2",
        "pwm3",
    }
)


# ----------------------------------------------------------------------
# PCR self-contained group (ESP32-C3 / S3 only).
# ----------------------------------------------------------------------

# Regex used to spot ``<peri>_conf_reg`` / ``<peri>_conf0_reg`` style
# register names inside the ``pcr`` template.
PCR_REGISTER_PATTERN = r"^(?P<peri>[a-z0-9_]+?)_conf\d?_reg$"

# Inside such a register, fields are named ``<peri>_clk_en`` /
# ``<peri>_rst_en``.  We want both.
PCR_FIELD_CLK_PATTERN = r"^(?P<peri>[a-z0-9_]+?)_clk_en$"
PCR_FIELD_RST_PATTERN = r"^(?P<peri>[a-z0-9_]+?)_rst_en$"


# ----------------------------------------------------------------------
# Top-level dispatch table consumed by the synthesiser.
# ----------------------------------------------------------------------


class ChipGateConfig(NamedTuple):
    """Per-chip configuration: which template + which alias map."""

    template: str
    groups: tuple[GateRegisterGroup, ...]
    aliases: dict[str, str | tuple[str, ...]]
    skip: frozenset[str]
    bus: str  # value emitted as ``extra["bus"]``


# Keyed by ``(family, chip_id)``.  The synthesiser dispatches on
# ``device.identity.family`` and the per-chip device id — multiple
# entries per chip describe layered groups (e.g., esp32c3 has
# both ``system`` and ``pcr`` templates).
ESPRESSIF_CHIP_GATES: dict[tuple[str, str], tuple[ChipGateConfig, ...]] = {
    ("esp32", "esp32"): (
        ChipGateConfig(
            template="dport",
            groups=ESP32_DPORT_GROUPS,
            aliases=ESP32_FIELD_ALIASES,
            skip=ESP32_SKIP_STEMS,
            bus="DPORT",
        ),
    ),
    ("esp32", "esp32-wroom32"): (
        ChipGateConfig(
            template="dport",
            groups=ESP32_DPORT_GROUPS,
            aliases=ESP32_FIELD_ALIASES,
            skip=ESP32_SKIP_STEMS,
            bus="DPORT",
        ),
    ),
    ("esp32c3", "esp32c3"): (
        ChipGateConfig(
            template="system",
            groups=ESP32C3_SYSTEM_GROUPS,
            aliases=ESP32C3_FIELD_ALIASES,
            skip=ESP32C3_SKIP_STEMS,
            bus="SYSTEM",
        ),
    ),
    ("esp32s3", "esp32s3"): (
        ChipGateConfig(
            template="system",
            groups=ESP32S3_SYSTEM_GROUPS,
            aliases=ESP32S3_FIELD_ALIASES,
            skip=ESP32S3_SKIP_STEMS,
            bus="SYSTEM",
        ),
    ),
}


# Families with PCR self-contained gates (independent of SYSTEM).
ESPRESSIF_PCR_FAMILIES: frozenset[str] = frozenset({"esp32c3", "esp32s3"})


__all__ = [
    "ChipGateConfig",
    "ESPRESSIF_CHIP_GATES",
    "ESPRESSIF_PCR_FAMILIES",
    "GateRegisterGroup",
    "PCR_FIELD_CLK_PATTERN",
    "PCR_FIELD_RST_PATTERN",
    "PCR_REGISTER_PATTERN",
]
