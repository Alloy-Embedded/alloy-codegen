"""Regression tests for ``add-additional-validity-concepts``.

Each test asserts that the per-device validity-concept header
contains the expected primary template + at least one populated
specialisation projected from the canonical IR.
"""

from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run


def test_emit_dma_validation_header_for_stm32g071rb(
    execution_context: ExecutionContext,
) -> None:
    """``dma_validation.hpp`` projects ``device.dma_bindings`` into a
    ``ValidDmaBinding<PeripheralId, DmaChannelId>`` concept."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    key = "st/stm32g0/generated/runtime/devices/stm32g071rb/dma_validation.hpp"
    assert key in arts
    content = arts[key].content

    assert "enum class DmaChannelId : std::uint16_t {" in content
    assert (
        "template<PeripheralId Peripheral, DmaChannelId Channel>\n"
        "struct DmaBindingValid : std::false_type {};" in content
    )
    # USART1 RX is bound to DMA1 channel 1 (request line DMA1_CH1).
    assert (
        "struct DmaBindingValid<PeripheralId::USART1, DmaChannelId::DMA1_DMA1_CH1>"
        " : std::true_type {" in content
    )
    assert "concept ValidDmaBinding = DmaBindingValid<Peripheral, Channel>::value;" in content
    assert "inline constexpr std::array<DmaBindingEntry," in content
    assert "constexpr bool is_valid_dma_binding(" in content


def test_emit_clock_validation_header_for_stm32g071rb(
    execution_context: ExecutionContext,
) -> None:
    """``clock_validation.hpp`` projects ``peripheral_clock_bindings`` into
    a ``ValidClockSource<PeripheralId, ClockGateId>`` concept."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    key = "st/stm32g0/generated/runtime/devices/stm32g071rb/clock_validation.hpp"
    assert key in arts
    content = arts[key].content

    assert (
        "template<PeripheralId Peripheral, ClockGateId Source>\n"
        "struct ClockSourceValid : std::false_type {};" in content
    )
    assert (
        "struct ClockSourceValid<PeripheralId::ADC1, ClockGateId::gate_adc1>"
        " : std::true_type {" in content
    )
    assert "concept ValidClockSource = ClockSourceValid<Peripheral, Source>::value;" in content


def test_emit_interrupt_validation_header_for_stm32g071rb(
    execution_context: ExecutionContext,
) -> None:
    """``interrupt_validation.hpp`` projects ``interrupt_bindings`` into a
    ``ValidInterruptSlot<PeripheralId, VectorSlot>`` concept."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    key = "st/stm32g0/generated/runtime/devices/stm32g071rb/interrupt_validation.hpp"
    assert key in arts
    content = arts[key].content

    assert (
        "template<PeripheralId Peripheral, std::uint16_t VectorSlot>\n"
        "struct InterruptSlotValid : std::false_type {};" in content
    )
    # DMA1 channel 1 lives at vector slot 25 on stm32g071rb.
    assert "struct InterruptSlotValid<PeripheralId::DMA1, 25u> : std::true_type {" in content
    assert (
        "concept ValidInterruptSlot = InterruptSlotValid<Peripheral, VectorSlot>::value;" in content
    )


def test_emit_i2c_speed_validation_header_for_stm32g071rb(
    execution_context: ExecutionContext,
) -> None:
    """``i2c_speed_validation.hpp`` projects ``i2c_speed_options`` into a
    ``consteval`` predicate exposed as ``ValidI2cSpeed<PeripheralId, SpeedHz>``."""
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    arts = {a.path: a for a in result.payload.artifacts}
    key = "st/stm32g0/generated/runtime/devices/stm32g071rb/i2c_speed_validation.hpp"
    assert key in arts
    content = arts[key].content

    assert (
        "consteval bool is_valid_i2c_speed(PeripheralId peripheral, "
        "std::uint32_t speed_hz) noexcept {" in content
    )
    assert "if (peripheral == PeripheralId::I2C1) {" in content
    assert "100000u" in content
    assert "400000u" in content
    assert "1000000u" in content
    assert "concept ValidI2cSpeed = is_valid_i2c_speed(Peripheral, SpeedHz);" in content
    assert "inline constexpr std::array<I2cSpeedEntry," in content
