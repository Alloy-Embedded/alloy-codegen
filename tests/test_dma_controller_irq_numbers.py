"""Regression test for the DMA controller `kIrqNumbers` surface
added by ``add-irq-vector-traits`` Phase 1.4 (deferred follow-up).

RP2040's DMA block ships two NVIC vectors (DMA_IRQ_0 = line 11,
DMA_IRQ_1 = line 12), both shared by every channel via the
INTE0/INTE1 routing mux.  ``DmaControllerHwTraits<RuntimeDmaCtrlId::DMA>``
SHALL surface them in ``kIrqNumbers`` so consumer code can branch
on the available IRQ lines without re-deriving from
``device.interrupts``.
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


def test_rp2040_dma_controller_surfaces_two_irq_numbers(
    rp2040_execution_context: ExecutionContext,
) -> None:
    content = _emit_dma_hpp(rp2040_execution_context, "rp2040")
    spec = re.search(
        r"struct DmaControllerHwTraits<RuntimeDmaCtrlId::DMA> \{(.*?)\n\};",
        content,
        re.DOTALL,
    )
    assert spec is not None, "missing populated DmaControllerHwTraits<DMA> specialisation"
    block = spec.group(1)
    assert "std::array<std::uint32_t, 2> kIrqNumbers = {{11u, 12u}};" in block


def test_rp2040_dma_primary_template_emits_zero_irq_numbers(
    rp2040_execution_context: ExecutionContext,
) -> None:
    content = _emit_dma_hpp(rp2040_execution_context, "rp2040")
    primary = re.search(
        r"template<RuntimeDmaCtrlId Id>\nstruct DmaControllerHwTraits \{(.*?)\n\};",
        content,
        re.DOTALL,
    )
    assert primary is not None
    assert "std::array<std::uint32_t, 0> kIrqNumbers = {};" in primary.group(1)
