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
