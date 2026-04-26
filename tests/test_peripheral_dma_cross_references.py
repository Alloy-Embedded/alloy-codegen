"""Tests for the peripheral->DMA cross-reference arrays added by
``add-peripheral-dma-cross-references``.

The spec requires every emitted ``<peripheral>.hpp`` to expose a
populated ``kDmaBindings`` constexpr array of ``DmaBindingRef`` records
when the peripheral instance has admitted DMA bindings, and to ship
``std::array<DmaBindingRef, 0>{}`` on the unspecialised primary template.
"""

from __future__ import annotations

import re

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _emit_header(context: ExecutionContext, device: str, name: str) -> str:
    result = run_emit(PipelineScope(device=device), context)
    artifact = next(
        a for a in result.payload.artifacts
        if a.path.endswith(f"/{device}/driver_semantics/{name}")
    )
    return artifact.content


def _struct_block(content: str, header: str) -> str:
    match = re.search(rf"struct {re.escape(header)} \{{(.*?)\n}};", content, re.DOTALL)
    assert match is not None, f"missing struct: {header}"
    return match.group(1)


def test_uart_usart1_surfaces_tx_rx_dma_bindings_on_stm32g0(
    execution_context: ExecutionContext,
) -> None:
    """STM32G0 USART1 has both TX and RX bindings admitted via the
    family bootstrap patch — the populated specialisation must surface
    a `kDmaBindings` array of size 2 with one Tx + one Rx entry."""
    content = _emit_header(execution_context, "stm32g071rb", "uart.hpp")
    assert "static constexpr std::array<DmaBindingRef, 2> kDmaBindings = {{" in content
    assert "DmaBindingDirection::Tx" in content
    assert "DmaBindingDirection::Rx" in content
    # Both entries reference the same DMA controller id used by dma_bindings.hpp.
    assert "DmaControllerId::DMA1" in content


def test_uart_primary_template_emits_zero_dma_bindings(
    execution_context: ExecutionContext,
) -> None:
    """The unspecialised primary template carries an empty
    `std::array<DmaBindingRef, 0>` so consumer code branching on
    `kDmaBindings.size() > 0` compiles even when no binding is admitted."""
    content = _emit_header(execution_context, "stm32g071rb", "uart.hpp")
    primary = _struct_block(content, "UartSemanticTraits")
    assert "static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};" in primary


def test_spi_primary_template_emits_zero_dma_bindings(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_header(execution_context, "stm32g071rb", "spi.hpp")
    primary = _struct_block(content, "SpiSemanticTraits")
    assert "static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};" in primary


def test_common_hpp_defines_dma_binding_ref_struct(
    execution_context: ExecutionContext,
) -> None:
    """The shared `DmaBindingRef` record + `DmaBindingDirection` enum
    live in `common.hpp` so every peripheral header reuses the same
    type."""
    content = _emit_header(execution_context, "stm32g071rb", "common.hpp")
    assert "enum class DmaBindingDirection : std::uint8_t" in content
    assert "struct DmaBindingRef {" in content
    assert "DmaControllerId controller_id" in content
    assert "DmaBindingId binding_id" in content
