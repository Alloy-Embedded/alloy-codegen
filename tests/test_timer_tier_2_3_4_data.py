"""Tests for the Timer Tier 2/3/4 trait surface added by
``add-timer-tier-2-3-4-data``.

The emitted ``timer.hpp`` SHALL extend every populated
``TimerSemanticTraits`` specialisation with max prescaler / auto-reload,
trigger-source array, master-output (TRGO) array, and capability flags
(`kSupportsDmaBurst`, `kSupportsRepetitionCounter`, `kSupportsXorInput`).
"""

from __future__ import annotations

import re

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _emit_timer_hpp(context: ExecutionContext, device: str) -> str:
    result = run_emit(PipelineScope(device=device), context)
    suffix = f"/{device}/driver_semantics/timer.hpp"
    artifact = next(a for a in result.payload.artifacts if a.path.endswith(suffix))
    return artifact.content


def _spec_block(content: str, peripheral: str) -> str:
    pattern = rf"struct TimerSemanticTraits<PeripheralId::{re.escape(peripheral)}> \{{(.*?)\n}};"
    match = re.search(pattern, content, re.DOTALL)
    assert match is not None, f"missing TimerSemanticTraits<PeripheralId::{peripheral}>"
    return match.group(1)


def test_stm32g0_tim1_advertises_full_itr_matrix(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_timer_hpp(execution_context, "stm32g071rb")
    block = _spec_block(content, "TIM1")
    assert "kMaxPrescaler = 65535u" in block
    assert "kMaxAutoReload = 65535u" in block
    # 8-entry trigger array (ITR0..ITR3, TI1F_ED, TI1FP1, TI2FP2, ETRF).
    trigger_match = re.search(
        r"std::array<std::uint8_t, (\d+)> kTriggerSources",
        block,
    )
    assert trigger_match is not None
    assert int(trigger_match.group(1)) >= 4
    # 8-entry master-output (MMS) array (Reset/Enable/Update/ComparePulse/OC1..4Ref).
    master_match = re.search(
        r"std::array<std::uint8_t, (\d+)> kMasterOutputModes",
        block,
    )
    assert master_match is not None
    assert int(master_match.group(1)) >= 8
    assert "kSupportsRepetitionCounter = true" in block
    assert "kSupportsDmaBurst = true" in block


def test_stm32g0_timer_primary_template_safe_defaults(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_timer_hpp(execution_context, "stm32g071rb")
    primary = re.search(
        r"template<PeripheralId Id>\nstruct TimerSemanticTraits \{(.*?)\n\};",
        content,
        re.DOTALL,
    )
    assert primary is not None
    body = primary.group(1)
    assert "kMaxPrescaler = 0u" in body
    assert "kMaxAutoReload = 0u" in body
    assert "std::array<std::uint8_t, 0> kTriggerSources = {};" in body
    assert "std::array<std::uint8_t, 0> kMasterOutputModes = {};" in body
    assert "kSupportsDmaBurst = false" in body
    assert "kSupportsRepetitionCounter = false" in body
    assert "kSupportsXorInput = false" in body
