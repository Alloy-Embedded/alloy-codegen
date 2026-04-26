"""Tests for the PWM Tier 2/3/4 trait surface added by
``add-pwm-tier-2-3-4-data``.

Each populated ``PwmSemanticTraits`` specialisation extends with
max prescaler / period, deadtime / alignment / break-input arrays
and capability flags (`kSupportsDeadtime`, `kSupportsBreakInput`,
`kSupportsComplementaryOutputs`, `kSupportsAsymmetricPwm`,
`kSupportsCombinedPwm`).
"""

from __future__ import annotations

import re

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _emit_pwm_hpp(context: ExecutionContext, device: str) -> str:
    result = run_emit(PipelineScope(device=device), context)
    suffix = f"/{device}/driver_semantics/pwm.hpp"
    artifact = next(a for a in result.payload.artifacts if a.path.endswith(suffix))
    return artifact.content


def _spec_block(content: str, peripheral: str) -> str:
    pattern = rf"struct PwmSemanticTraits<PeripheralId::{re.escape(peripheral)}> \{{(.*?)\n}};"
    match = re.search(pattern, content, re.DOTALL)
    assert match is not None, f"missing PwmSemanticTraits<PeripheralId::{peripheral}>"
    return match.group(1)


def test_stm32g0_tim1_advertises_deadtime_break_alignment(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_pwm_hpp(execution_context, "stm32g071rb")
    block = _spec_block(content, "TIM1")
    assert "kSupportsDeadtime = true" in block
    assert "kSupportsBreakInput = true" in block
    assert "kSupportsComplementaryOutputs = true" in block
    # 4 deadtime DTPSC choices.
    dt = re.search(r"std::array<std::uint8_t, (\d+)> kDeadtimeOptions", block)
    assert dt is not None and int(dt.group(1)) >= 4
    # 4 supported alignment modes (edge + 3 center variants).
    align = re.search(r"std::array<std::uint8_t, (\d+)> kSupportedAlignments", block)
    assert align is not None and int(align.group(1)) == 4
    # 1 break input (BKIN).
    brk = re.search(r"std::array<std::uint8_t, (\d+)> kBreakInputs", block)
    assert brk is not None and int(brk.group(1)) == 1
    # Max prescaler = 65535 from the matching timer prescaler patch.
    assert "kMaxPrescaler = 65535u" in block


def test_stm32g0_pwm_primary_template_safe_defaults(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_pwm_hpp(execution_context, "stm32g071rb")
    primary = re.search(
        r"template<PeripheralId Id>\nstruct PwmSemanticTraits \{(.*?)\n\};",
        content,
        re.DOTALL,
    )
    assert primary is not None
    body = primary.group(1)
    assert "kMaxPrescaler = 0u" in body
    assert "kMaxPeriod = 0u" in body
    assert "std::array<std::uint8_t, 0> kDeadtimeOptions = {};" in body
    assert "std::array<std::uint8_t, 0> kSupportedAlignments = {};" in body
    assert "std::array<std::uint8_t, 0> kBreakInputs = {};" in body
    assert "kSupportsDeadtime = false" in body
    assert "kSupportsBreakInput = false" in body
    assert "kSupportsComplementaryOutputs = false" in body
    assert "kSupportsAsymmetricPwm = false" in body
    assert "kSupportsCombinedPwm = false" in body
