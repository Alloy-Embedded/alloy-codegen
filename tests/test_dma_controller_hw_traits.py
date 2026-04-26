"""Tests for the DMA controller HW trait surface added by
``fill-dma-controller-hw-traits``.

The emitted ``dma.hpp`` SHALL extend every populated
``DmaControllerHwTraits<DmaControllerId>`` specialisation with
channel count, max transfer count, supported burst sizes /
data widths, priority level count, and capability flags
(`kSupportsCircular`, `kSupportsDoubleBuffer`,
`kSupportsMemToMem`, `kSupportsDescriptorChaining`,
`kSupportsByteSwap`, `kSupportsScatterGather`).
"""

from __future__ import annotations

import re

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _emit_dma_hpp(context: ExecutionContext, device: str) -> str:
    result = run_emit(PipelineScope(device=device), context)
    suffix = f"/{device}/driver_semantics/dma.hpp"
    artifact = next(a for a in result.payload.artifacts if a.path.endswith(suffix))
    return artifact.content


def _spec_block(content: str, controller: str) -> str:
    pattern = (
        rf"struct DmaControllerHwTraits<RuntimeDmaCtrlId::{re.escape(controller)}> \{{(.*?)\n}};"
    )
    match = re.search(pattern, content, re.DOTALL)
    assert match is not None, f"missing DmaControllerHwTraits<{controller}>"
    return match.group(1)


def test_rp2040_dma_advertises_12_channels_byte_swap_scatter_gather(
    rp2040_execution_context: ExecutionContext,
) -> None:
    content = _emit_dma_hpp(rp2040_execution_context, "rp2040")
    block = _spec_block(content, "DMA")
    assert "kChannelCount = 12u" in block
    assert "kSupportsByteSwap = true" in block
    assert "kSupportsScatterGather = true" in block
    burst = re.search(r"std::array<std::uint8_t, (\d+)> kSupportedBurstSizes", block)
    assert burst is not None and int(burst.group(1)) >= 1


def test_stm32g0_dma1_advertises_7_channels_4_priority_levels(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_dma_hpp(execution_context, "stm32g071rb")
    block = _spec_block(content, "DMA1")
    assert "kChannelCount = 7u" in block
    assert "kPriorityLevelCount = 4u" in block
    assert "kMaxTransferCount = 0x0000ffffu" in block
    assert "kSupportsCircular = true" in block
    assert "kSupportsByteSwap = false" in block


def test_stm32g0_dma_primary_template_safe_defaults(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_dma_hpp(execution_context, "stm32g071rb")
    primary = re.search(
        r"template<RuntimeDmaCtrlId Id>\nstruct DmaControllerHwTraits \{(.*?)\n\};",
        content,
        re.DOTALL,
    )
    assert primary is not None
    body = primary.group(1)
    assert "kChannelCount = 0u" in body
    assert "kPriorityLevelCount = 0u" in body
    assert "std::array<std::uint8_t, 0> kSupportedBurstSizes = {};" in body
    assert "std::array<std::uint8_t, 0> kSupportedDataWidths = {};" in body
    assert "kSupportsCircular = false" in body
    assert "kSupportsScatterGather = false" in body
