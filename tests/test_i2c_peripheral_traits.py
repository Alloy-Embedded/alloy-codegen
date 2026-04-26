"""Tests for the populated I2cPeripheralTraits surface.

Covers the contract added by the ``fill-i2c-semantic-gaps`` change.
Phase A wires the STM32-family normalizer; subsequent phases extend
coverage to Espressif (B), RP2040 (C), AVR-DA (D).

Detailed per-controller assertions on STM32 are intentionally limited
because the ``execution_context`` fixture ships a *minimal* SVD slice
that does not include the I2C peripherals — exercising the populated
specialization end-to-end against the real upstream sources is left
to ``test_rp2040_i2c_traits.py`` / ``test_espressif_i2c_traits.py`` in
later phases.
"""

from __future__ import annotations

import re

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _emit_i2c_hpp(context: ExecutionContext, device: str) -> str:
    result = run_emit(PipelineScope(device=device), context)
    artifact = next(
        a for a in result.payload.artifacts if a.path.endswith(f"/{device}/driver_semantics/i2c.hpp")
    )
    return artifact.content


def _struct_block(content: str, header: str) -> str:
    match = re.search(rf"struct {re.escape(header)} \{{(.*?)\n}};", content, re.DOTALL)
    assert match is not None, f"missing struct: {header}"
    return match.group(1)


def test_primary_i2c_peripheral_traits_carries_zero_defaults(
    execution_context: ExecutionContext,
) -> None:
    """Every emitted i2c.hpp declares the new ``I2cPeripheralTraits``
    primary template with zero defaults so non-I2C-bearing families
    remain zero-cost."""
    content = _emit_i2c_hpp(execution_context, "stm32g071rb")

    primary = _struct_block(content, "I2cPeripheralTraits")
    assert "static constexpr bool kPresent = false;" in primary
    assert "static constexpr std::uint32_t kBaseAddress = 0u;" in primary
    assert "static constexpr bool kSupportsFastModePlus = false;" in primary
    assert "static constexpr std::array<PinId, 0> kValidSdaPins = {};" in primary
    assert "static constexpr std::array<PinId, 0> kValidSclPins = {};" in primary
    assert "static constexpr std::uint16_t kInSdaSignal = 0xFFFFu;" in primary


def test_runtime_i2c_ctrl_id_enum_is_emitted(
    execution_context: ExecutionContext,
) -> None:
    """The ``RuntimeI2cCtrlId`` enum is emitted alongside the trait
    template — even when the slice doesn't expose I2C peripherals,
    the enum class declaration with the ``None = 0`` sentinel is
    always present so consumers compile against a stable surface."""
    content = _emit_i2c_hpp(execution_context, "stm32g071rb")
    assert "enum class RuntimeI2cCtrlId : std::uint8_t" in content
    assert "None = 0," in content


# --- Phase B: Espressif (ESP32 classic / C3 / S3) ------------------------


def test_esp32c3_i2c0_records_io_matrix_signal_indices(
    espressif_execution_context: ExecutionContext,
) -> None:
    """ESP32-C3 has a single I2C peripheral.  Pads route via the GPIO
    matrix — `valid_sda_pins` / `valid_scl_pins` stay empty (AllGpios
    sentinel) and the IO-matrix signal indices come from
    `gpio_sig_map.h`."""
    content = _emit_i2c_hpp(espressif_execution_context, "esp32c3")

    i2c0 = _struct_block(content, "I2cPeripheralTraits<RuntimeI2cCtrlId::I2C0>")
    assert "static constexpr bool kPresent = true;" in i2c0
    assert "static constexpr std::uint32_t kBaseAddress = 0x60013000u;" in i2c0
    # AllGpios sentinel: empty pad arrays.
    assert "static constexpr std::array<PinId, 0> kValidSdaPins = {};" in i2c0
    assert "static constexpr std::array<PinId, 0> kValidSclPins = {};" in i2c0
    # ESP32-C3 IO matrix indices: I2CEXT0_SDA = 15, I2CEXT0_SCL = 14.
    assert "static constexpr std::uint16_t kInSdaSignal = 15u;" in i2c0
    assert "static constexpr std::uint16_t kInSclSignal = 14u;" in i2c0
    # Fast Mode Plus is S3-only.
    assert "static constexpr bool kSupportsFastModePlus = false;" in i2c0


def test_esp32s3_marks_fast_mode_plus(
    espressif_execution_context: ExecutionContext,
) -> None:
    """Only ESP32-S3 silicon supports I2C Fast Mode Plus per datasheet
    §28.  Verify both controllers carry the flag."""
    content = _emit_i2c_hpp(espressif_execution_context, "esp32s3")

    for ctrl in ("I2C0", "I2C1"):
        block = _struct_block(content, f"I2cPeripheralTraits<RuntimeI2cCtrlId::{ctrl}>")
        assert "static constexpr bool kSupportsFastModePlus = true;" in block, ctrl


def test_esp32_classic_records_two_controllers(
    espressif_execution_context: ExecutionContext,
) -> None:
    """ESP32 classic has I2C0 + I2C1.  Pin-signal data may be sparse in
    the test SVD slice; we assert the base addresses and that
    Fast Mode Plus is `false`."""
    content = _emit_i2c_hpp(espressif_execution_context, "esp32")

    i2c0 = _struct_block(content, "I2cPeripheralTraits<RuntimeI2cCtrlId::I2C0>")
    assert "static constexpr std::uint32_t kBaseAddress = 0x3ff53000u;" in i2c0
    assert "static constexpr bool kSupportsFastModePlus = false;" in i2c0

    i2c1 = _struct_block(content, "I2cPeripheralTraits<RuntimeI2cCtrlId::I2C1>")
    assert "static constexpr std::uint32_t kBaseAddress = 0x3ff67000u;" in i2c1
    assert "static constexpr bool kSupportsFastModePlus = false;" in i2c1


# --- Phase C: RP2040 -----------------------------------------------------


def test_rp2040_i2c0_records_datasheet_pin_constraints_and_dreqs(
    rp2040_execution_context: ExecutionContext,
) -> None:
    """RP2040 I2C0 datasheet (Table 2-5) constrains SDA to pads
    {GP0, GP4, GP8, GP12, GP16, GP20, GP24, GP28} and SCL to
    {GP1, GP5, GP9, GP13, GP17, GP21, GP25, GP29}.  Datasheet Table
    2-7: I2C0_TX = DREQ 32, I2C0_RX = DREQ 33."""
    content = _emit_i2c_hpp(rp2040_execution_context, "rp2040")

    i2c0 = _struct_block(content, "I2cPeripheralTraits<RuntimeI2cCtrlId::I2C0>")
    assert "static constexpr bool kPresent = true;" in i2c0
    assert "static constexpr std::uint8_t kDmaReqTx = 32u;" in i2c0
    assert "static constexpr std::uint8_t kDmaReqRx = 33u;" in i2c0
    for pad in ("GP0", "GP4", "GP8", "GP12", "GP16", "GP20", "GP24", "GP28"):
        assert f'PinId::{pad}' in i2c0
    for pad in ("GP1", "GP5", "GP9", "GP13", "GP17", "GP21", "GP25", "GP29"):
        assert f'PinId::{pad}' in i2c0


def test_rp2040_i2c1_records_distinct_constraints_and_dreqs(
    rp2040_execution_context: ExecutionContext,
) -> None:
    """RP2040 I2C1 SDA pads = {GP2, GP6, GP10, GP14, GP18, GP26}; SCL =
    {GP3, GP7, GP11, GP15, GP19, GP27}; DREQ TX=34, RX=35."""
    content = _emit_i2c_hpp(rp2040_execution_context, "rp2040")

    i2c1 = _struct_block(content, "I2cPeripheralTraits<RuntimeI2cCtrlId::I2C1>")
    assert "static constexpr std::uint8_t kDmaReqTx = 34u;" in i2c1
    assert "static constexpr std::uint8_t kDmaReqRx = 35u;" in i2c1
    for pad in ("GP2", "GP6", "GP10", "GP14", "GP18", "GP26"):
        assert f'PinId::{pad}' in i2c1


# --- Phase D: Microchip AVR-DA -------------------------------------------


def test_avr128da32_twi0_records_default_pin_placement(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    """AVR-DA exposes I2C as ``TWI0``.  Default placement on the
    avr128da32 (per ATDF + datasheet §28): SDA = PA2, SCL = PA3.
    PORTMUX alt-pin support is deferred — ``kPortmuxAlt = false`` for
    Phase D."""
    content = _emit_i2c_hpp(microchip_avr_da_execution_context, "avr128da32")

    twi0 = _struct_block(content, "I2cPeripheralTraits<RuntimeI2cCtrlId::TWI0>")
    assert "static constexpr bool kPresent = true;" in twi0
    assert 'PinId::PA2' in twi0
    assert 'PinId::PA3' in twi0
    assert "static constexpr bool kPortmuxAlt = false;" in twi0
    assert "static constexpr bool kSupportsFastModePlus = false;" in twi0
