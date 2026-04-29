"""Tests for the Timer Tier 2/3/4 trait surface added by
``add-timer-tier-2-3-4-data``.

After ``reduce-cpp-header-bloat-via-shared-luts`` the per-instance
specialisation only carries the variable-length arrays; scalar
flags + max-{prescaler,auto-reload} live in
``kTimerHardwareLut[Index]`` referenced by the inherited
``TimerTraitsBase<Index>``.  The helpers below resolve the LUT
row for a peripheral so the tests can keep asserting on the
same logical facts.
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
    """Return the per-instance body of ``TimerSemanticTraits<P>``.

    Accepts both legacy direct-specialisation form and the
    inheritance form added by
    ``reduce-cpp-header-bloat-via-shared-luts``.
    """
    pattern = (
        rf"struct TimerSemanticTraits<PeripheralId::{re.escape(peripheral)}>"
        r"(?:\s*:\s*TimerTraitsBase<\d+>)?\s*\{(.*?)\n}};"
    )
    match = re.search(pattern, content, re.DOTALL)
    assert match is not None, f"missing TimerSemanticTraits<PeripheralId::{peripheral}>"
    return match.group(1)


def _lut_row_for(content: str, peripheral: str) -> str:
    inherit = re.search(
        rf"struct TimerSemanticTraits<PeripheralId::{re.escape(peripheral)}>"
        r"\s*:\s*TimerTraitsBase<(\d+)>",
        content,
    )
    assert inherit is not None, f"no TimerTraitsBase inheritance for {peripheral}"
    index = int(inherit.group(1))
    lut = re.search(r"kTimerHardwareLut\s*=\s*\{\{(.*?)\}\};", content, re.DOTALL)
    assert lut is not None, "missing kTimerHardwareLut definition"
    rows = [line.strip() for line in lut.group(1).splitlines() if line.strip().startswith("{")]
    assert index < len(rows), (
        f"{peripheral} index {index} out of range for {len(rows)}-row LUT"
    )
    return rows[index]


def test_stm32g0_tim1_advertises_full_itr_matrix(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_timer_hpp(execution_context, "stm32g071rb")
    block = _spec_block(content, "TIM1")
    lut_row = _lut_row_for(content, "TIM1")
    # max_prescaler + max_auto_reload are positional u32s in the LUT row.
    assert lut_row.count("65535u") >= 2, (
        f"TIM1 LUT row should carry both max_prescaler=65535 and "
        f"max_auto_reload=65535; got: {lut_row}"
    )
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
    # supports_dma_burst + supports_repetition_counter resolve to true
    # via the LUT row's positional booleans.  Three flags total
    # (supports_dma_burst, supports_repetition_counter,
    # supports_xor_input); TIM1 has the first two true and the
    # third false, so we expect ≥2 ``true`` tokens in the row.
    assert lut_row.count("true") >= 2, (
        f"TIM1 LUT row should carry ≥2 supports_* trues; got: {lut_row}"
    )


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
