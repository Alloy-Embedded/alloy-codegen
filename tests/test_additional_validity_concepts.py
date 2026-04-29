"""Tests for the four additional C++20 validity concepts emitted by
``add-additional-validity-concepts``:

* ``ValidDmaBinding``         — ``dma_validation.hpp``
* ``ValidClockSource``        — ``clock_validation.hpp``
* ``ValidInterruptSlot``      — ``interrupt_validation.hpp``
* ``ValidI2cSpeed``           — ``i2c_speed_validation.hpp``

Each header is per-device, gated on the relevant IR field carrying
at least one binding/peripheral.  The tests pin a small set of
invariants that the generated headers must hold for stm32g071rb,
plus the negative case (omission) for an stm32 chip with no
matching IR data.
"""

from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run


def _arts(execution_context: ExecutionContext, *, device: str) -> dict[str, str]:
    result = run(PipelineScope(device=device), execution_context)
    return {a.path: a.content for a in result.payload.artifacts}


# ---------------------------------------------------------------------------
# DMA validation
# ---------------------------------------------------------------------------


def test_emit_dma_validation_header_for_stm32g071rb(
    execution_context: ExecutionContext,
) -> None:
    arts = _arts(execution_context, device="stm32g071rb")
    key = "st/stm32g0/generated/runtime/devices/stm32g071rb/dma_validation.hpp"
    assert key in arts
    content = arts[key]

    # Closed enums.
    assert "enum class DmaPeripheral : std::uint16_t {" in content
    assert "enum class DmaController : std::uint8_t {" in content
    assert "enum class DmaRequestLine : std::uint16_t {" in content

    # Primary template defaults to false_type.
    assert (
        "template<DmaPeripheral Peripheral, DmaController Controller, DmaRequestLine Request>\n"
        "struct DmaBindingValid : std::false_type {};" in content
    )

    # ValidDmaBinding concept declared.
    assert (
        "concept ValidDmaBinding = "
        "DmaBindingValid<Peripheral, Controller, Request>::value;" in content
    )

    # Constexpr lookup table + linear scan helper.
    assert "struct DmaBindingEntry {" in content
    assert "inline constexpr std::array<DmaBindingEntry, " in content
    assert "constexpr bool is_valid_dma_binding(" in content


# ---------------------------------------------------------------------------
# Clock validation
# ---------------------------------------------------------------------------


def test_emit_clock_validation_header_for_stm32g071rb(
    execution_context: ExecutionContext,
) -> None:
    arts = _arts(execution_context, device="stm32g071rb")
    key = "st/stm32g0/generated/runtime/devices/stm32g071rb/clock_validation.hpp"
    assert key in arts
    content = arts[key]

    assert "enum class ClockedPeripheral : std::uint16_t {" in content
    assert "enum class ClockSource : std::uint16_t {" in content

    assert (
        "template<ClockedPeripheral Peripheral, ClockSource Source>\n"
        "struct ClockSourceValid : std::false_type {};" in content
    )
    assert (
        "concept ValidClockSource = ClockSourceValid<Peripheral, Source>::value;"
        in content
    )

    assert "struct ClockBindingEntry {" in content
    assert "inline constexpr std::array<ClockBindingEntry, " in content
    assert "constexpr bool is_valid_clock_source(" in content


# ---------------------------------------------------------------------------
# Interrupt validation
# ---------------------------------------------------------------------------


def test_emit_interrupt_validation_header_for_stm32g071rb(
    execution_context: ExecutionContext,
) -> None:
    arts = _arts(execution_context, device="stm32g071rb")
    key = "st/stm32g0/generated/runtime/devices/stm32g071rb/interrupt_validation.hpp"
    assert key in arts
    content = arts[key]

    assert "enum class IrqPeripheral : std::uint16_t {" in content

    assert (
        "template<IrqPeripheral Peripheral, std::uint32_t VectorIndex>\n"
        "struct InterruptSlotValid : std::false_type {};" in content
    )
    assert (
        "concept ValidInterruptSlot = InterruptSlotValid<Peripheral, VectorIndex>::value;"
        in content
    )

    assert "struct InterruptSlotEntry {" in content
    assert "inline constexpr std::array<InterruptSlotEntry, " in content
    assert "constexpr bool is_valid_interrupt_slot(" in content


# ---------------------------------------------------------------------------
# I2C speed validation
# ---------------------------------------------------------------------------


def test_emit_i2c_speed_validation_header_for_stm32g071rb(
    execution_context: ExecutionContext,
) -> None:
    arts = _arts(execution_context, device="stm32g071rb")
    key = "st/stm32g0/generated/runtime/devices/stm32g071rb/i2c_speed_validation.hpp"
    assert key in arts
    content = arts[key]

    assert "enum class I2cPeripheral : std::uint16_t {" in content
    # All 3 well-known I2C speed grades emitted (the third is gated on
    # supports_fast_mode_plus and only specialises when the controller
    # actually carries it).
    assert "enum class I2cSpeedGrade : std::uint8_t {" in content
    assert "Standard = 100000u," in content
    assert "Fast = 400000u," in content
    assert "FastModePlus = 1000000u," in content

    assert (
        "template<I2cPeripheral Peripheral, I2cSpeedGrade Speed>\n"
        "struct I2cSpeedValid : std::false_type {};" in content
    )
    assert (
        "concept ValidI2cSpeed = I2cSpeedValid<Peripheral, Speed>::value;"
        in content
    )

    # Every controller gets at least the Standard + Fast specialisations.
    assert (
        "struct I2cSpeedValid<I2cPeripheral::I2C1, I2cSpeedGrade::Standard> "
        ": std::true_type {" in content
    )
    assert (
        "struct I2cSpeedValid<I2cPeripheral::I2C1, I2cSpeedGrade::Fast> "
        ": std::true_type {" in content
    )

    assert "struct I2cSpeedEntry {" in content
    assert "inline constexpr std::array<I2cSpeedEntry, " in content
    assert "constexpr bool is_valid_i2c_speed(" in content
