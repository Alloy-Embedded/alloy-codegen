"""Tests for the family-shaped PWM peripheral trait surface.

Covers the contract added by the ``extend-pwm-coverage-all-mcus``
change.  Phase A wires the STM32-family TIMx PWM emitter; subsequent
phases extend coverage to Espressif (B), iMXRT (C), AVR-DA + SAME70
(D).
"""

from __future__ import annotations

import re

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _emit_pwm_hpp(context: ExecutionContext, device: str) -> str:
    result = run_emit(PipelineScope(device=device), context)
    artifact = next(
        a for a in result.payload.artifacts if a.path.endswith(f"/{device}/driver_semantics/pwm.hpp")
    )
    return artifact.content


def _struct_block(content: str, header: str) -> str:
    match = re.search(rf"struct {re.escape(header)} \{{(.*?)\n}};", content, re.DOTALL)
    assert match is not None, f"missing struct: {header}"
    return match.group(1)


def test_primary_stm_timer_pwm_traits_carries_zero_defaults(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_pwm_hpp(execution_context, "stm32g071rb")

    primary = _struct_block(content, "StmTimerPwmTraits")
    assert "static constexpr bool kPresent = false;" in primary
    assert "static constexpr std::uint32_t kBaseAddress = 0u;" in primary
    assert "static constexpr RuntimeStmTimerKind kKind = RuntimeStmTimerKind::None;" in primary
    assert "static constexpr std::uint8_t kChannelCount = 0u;" in primary
    assert "static constexpr std::array<PinId, 0> kValidCh1Pins = {};" in primary
    assert "static constexpr bool kSupportsComplementary = false;" in primary
    assert "static constexpr bool kSupportsBrake = false;" in primary


def test_runtime_stm_timer_kind_enum_is_emitted(
    execution_context: ExecutionContext,
) -> None:
    """The typed `RuntimeStmTimerKind` enum is emitted alongside the
    trait template — string literals are forbidden in runtime C++
    output, so consumer code branches on the typed enum."""
    content = _emit_pwm_hpp(execution_context, "stm32g071rb")
    assert "enum class RuntimeStmTimerKind : std::uint8_t" in content
    assert "Advanced = 1," in content
    assert "General = 2," in content


def test_runtime_stm_timer_pwm_id_enum_lists_admitted_timers(
    execution_context: ExecutionContext,
) -> None:
    """The `RuntimeStmTimerPwmId` enum lists every TIMx that flowed
    through `_build_st_timer_pwm_peripherals` (basic timers TIM6/TIM7
    are filtered out — they have no PWM output capability)."""
    content = _emit_pwm_hpp(execution_context, "stm32g071rb")
    assert "enum class RuntimeStmTimerPwmId : std::uint8_t" in content
    assert "None = 0," in content
    # TIM6 / TIM7 (basic timers without output channels) MUST NOT appear.
    assert "TIM6 = " not in content
    assert "TIM7 = " not in content
