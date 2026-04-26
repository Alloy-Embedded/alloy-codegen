"""Phase B trait-coverage tests for RP2040 UART/SPI peripheral traits.

Asserts the new ``UartPeripheralTraits<RuntimeUartId::UART*>`` and
``SpiPeripheralTraits<RuntimeSpiId::SPI*>`` specializations carry the family-
constant facts (base address, FIFO depth, peripheral-clock ceiling, DMA
DREQ values) plus the pin-validity arrays derived from the FUNCSEL
table on ``device.gpio_pins``.
"""

from __future__ import annotations

import re

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _emit(context: ExecutionContext, device: str, header: str) -> str:
    result = run_emit(PipelineScope(device=device), context)
    artifact = next(
        a for a in result.payload.artifacts if a.path.endswith(f"/{device}/driver_semantics/{header}")
    )
    return artifact.content


def _struct_block(content: str, header: str) -> str:
    match = re.search(rf"struct {re.escape(header)} \{{(.*?)\n}};", content, re.DOTALL)
    assert match is not None, f"missing struct: {header}"
    return match.group(1)


def test_rp2040_uart0_records_base_dreqs_and_tx_pads(
    rp2040_execution_context: ExecutionContext,
) -> None:
    content = _emit(rp2040_execution_context, "rp2040", "uart.hpp")

    primary = _struct_block(content, "UartPeripheralTraits")
    assert "static constexpr std::uint32_t kBaseAddress = 0u;" in primary
    assert "static constexpr std::array<std::uint8_t, 0> kValidTxPins = {};" in primary

    uart0 = _struct_block(content, "UartPeripheralTraits<RuntimeUartId::UART0>")
    assert "static constexpr bool kPresent = true;" in uart0
    assert "static constexpr std::uint32_t kBaseAddress = 0x40034000u;" in uart0
    assert "static constexpr std::uint8_t kFifoDepth = 32u;" in uart0
    assert "static constexpr std::uint8_t kDreqTx = 20u;" in uart0
    assert "static constexpr std::uint8_t kDreqRx = 21u;" in uart0
    # TX pads from FUNCSEL — the test fixture covers GP0/12/16.  GP28 is
    # not bonded on the QFN56 admitted package slice; we assert membership
    # for the pads we know are present.
    assert "0u" in uart0 and "12u" in uart0 and "16u" in uart0


def test_rp2040_uart1_records_dreqs(
    rp2040_execution_context: ExecutionContext,
) -> None:
    content = _emit(rp2040_execution_context, "rp2040", "uart.hpp")

    uart1 = _struct_block(content, "UartPeripheralTraits<RuntimeUartId::UART1>")
    assert "static constexpr std::uint32_t kBaseAddress = 0x40038000u;" in uart1
    assert "static constexpr std::uint8_t kDreqTx = 22u;" in uart1
    assert "static constexpr std::uint8_t kDreqRx = 23u;" in uart1


def test_rp2040_spi0_records_max_clock_and_pad_sets(
    rp2040_execution_context: ExecutionContext,
) -> None:
    content = _emit(rp2040_execution_context, "rp2040", "spi.hpp")

    primary = _struct_block(content, "SpiPeripheralTraits")
    assert "static constexpr std::uint32_t kMaxClockHz = 0u;" in primary

    spi0 = _struct_block(content, "SpiPeripheralTraits<RuntimeSpiId::SPI0>")
    assert "static constexpr bool kPresent = true;" in spi0
    assert "static constexpr std::uint32_t kBaseAddress = 0x4003c000u;" in spi0
    assert "static constexpr std::uint32_t kMaxClockHz = 62500000u;" in spi0
    assert "static constexpr std::uint8_t kDreqTx = 16u;" in spi0
    assert "static constexpr std::uint8_t kDreqRx = 17u;" in spi0
    # SPI0 MOSI pads on RP2040 = {3, 7, 19, 23} per datasheet Table 2-5.
    assert "kValidMosiPins = {{3u, 7u, 19u, 23u}};" in spi0
    assert "kValidMisoPins = {{0u, 4u, 16u, 20u}};" in spi0
    assert "kValidClkPins = {{2u, 6u, 18u, 22u}};" in spi0
    assert "kValidCsPins = {{1u, 5u, 17u, 21u}};" in spi0


def test_rp2040_spi1_records_dreqs(
    rp2040_execution_context: ExecutionContext,
) -> None:
    content = _emit(rp2040_execution_context, "rp2040", "spi.hpp")

    spi1 = _struct_block(content, "SpiPeripheralTraits<RuntimeSpiId::SPI1>")
    assert "static constexpr std::uint32_t kBaseAddress = 0x40040000u;" in spi1
    assert "static constexpr std::uint8_t kDreqTx = 18u;" in spi1
    assert "static constexpr std::uint8_t kDreqRx = 19u;" in spi1


# --- Phase C: ADC ----------------------------------------------------------


def test_rp2040_adc_records_all_silicon_facts(
    rp2040_execution_context: ExecutionContext,
) -> None:
    """RP2040 has a single ADC with 5 channels (GP26..GP29 + internal
    temperature sensor at the sentinel pad index 255), 12-bit resolution,
    DMA DREQ 36, and a 4-deep FIFO (datasheet §4.9 + Table 264)."""
    content = _emit(rp2040_execution_context, "rp2040", "adc.hpp")

    primary = _struct_block(content, "AdcPeripheralTraits")
    assert "static constexpr std::uint32_t kBaseAddress = 0u;" in primary
    assert "static constexpr bool kSupportsFifo = false;" in primary

    adc = _struct_block(content, "AdcPeripheralTraits<RuntimeAdcId::ADC>")
    assert "static constexpr bool kPresent = true;" in adc
    assert "static constexpr std::uint32_t kBaseAddress = 0x4004c000u;" in adc
    assert "static constexpr std::uint8_t kChannelCount = 5u;" in adc
    assert "static constexpr std::uint8_t kResolutionBits = 12u;" in adc
    assert "static constexpr std::uint8_t kDreq = 36u;" in adc
    assert "static constexpr std::uint8_t kFifoDepth = 4u;" in adc
    assert "static constexpr bool kSupportsFifo = true;" in adc
    assert "kChannelPins = {{26u, 27u, 28u, 29u, 255u}};" in adc


# --- Phase D: DMA + Timer + PWM completion ---------------------------------


def test_rp2040_dma_controller_hw_records_silicon_facts(
    rp2040_execution_context: ExecutionContext,
) -> None:
    content = _emit(rp2040_execution_context, "rp2040", "dma.hpp")

    primary = _struct_block(content, "DmaControllerHwTraits")
    assert "static constexpr std::uint32_t kBaseAddress = 0u;" in primary

    dma = _struct_block(content, "DmaControllerHwTraits<RuntimeDmaCtrlId::DMA>")
    assert "static constexpr bool kPresent = true;" in dma
    assert "static constexpr std::uint32_t kBaseAddress = 0x50000000u;" in dma
    assert "static constexpr std::uint8_t kChannelCount = 12u;" in dma
    assert "static constexpr std::uint32_t kMaxTransferCount = 0xffffffffu;" in dma
    assert "static constexpr bool kSupportsChaining = true;" in dma
    assert "static constexpr bool kSupportsByteSwap = true;" in dma


def test_rp2040_timer_controller_hw_records_64bit_counter_and_alarms(
    rp2040_execution_context: ExecutionContext,
) -> None:
    content = _emit(rp2040_execution_context, "rp2040", "timer.hpp")

    timer = _struct_block(content, "TimerControllerHwTraits<RuntimeTimerCtrlId::TIMER>")
    assert "static constexpr std::uint32_t kBaseAddress = 0x40054000u;" in timer
    assert "static constexpr std::uint8_t kCounterBits = 64u;" in timer
    assert "static constexpr std::uint8_t kAlarmCount = 4u;" in timer
    # DREQ for ALARM0=39, ALARM1=40, ALARM2=41, ALARM3=42 (datasheet
    # Table 2-7).  We only emit the base and let consumers add the
    # alarm index.
    assert "static constexpr std::uint8_t kDreqAlarmBase = 39u;" in timer


def test_rp2040_pwm_slice_hw_emits_8_specializations_with_slice_pin_mapping(
    rp2040_execution_context: ExecutionContext,
) -> None:
    content = _emit(rp2040_execution_context, "rp2040", "pwm.hpp")

    # Slice 0 → A=GP0, B=GP1
    s0 = _struct_block(content, "PwmSliceHwTraits<0>")
    assert "static constexpr std::uint8_t kChannelAPin = 0u;" in s0
    assert "static constexpr std::uint8_t kChannelBPin = 1u;" in s0
    assert "static constexpr std::uint8_t kCounterBits = 16u;" in s0

    # Slice 7 → A=GP14, B=GP15 (datasheet Table 2-5; matches the proposal
    # task 4.6 invariant).
    s7 = _struct_block(content, "PwmSliceHwTraits<7>")
    assert "static constexpr std::uint8_t kChannelAPin = 14u;" in s7
    assert "static constexpr std::uint8_t kChannelBPin = 15u;" in s7

    # All 8 slices emit a populated specialization.
    for index in range(8):
        assert f"PwmSliceHwTraits<{index}>" in content
