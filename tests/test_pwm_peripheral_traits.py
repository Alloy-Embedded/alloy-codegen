"""Tests for the family-shaped PWM peripheral trait surface.

Covers the contract added by the ``extend-pwm-coverage-all-mcus``
change.  Phase A wires the STM32-family TIMx PWM emitter; subsequent
phases extend coverage to Espressif (B), iMXRT (C), AVR-DA + SAME70
(D).
"""

from __future__ import annotations

import re

import pytest

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _emit_pwm_hpp(context: ExecutionContext, device: str) -> str:
    result = run_emit(PipelineScope(device=device), context)
    artifact = next(
        a
        for a in result.payload.artifacts
        if a.path.endswith(f"/{device}/driver_semantics/pwm.hpp")
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


# ---------------------------------------------------------------------------
# Phase B: Espressif MCPWM
# ---------------------------------------------------------------------------


def test_mcpwm_traits_block_emits_for_esp32s3(
    espressif_execution_context: ExecutionContext,
) -> None:
    content = _emit_pwm_hpp(espressif_execution_context, "esp32s3")
    assert "enum class RuntimeMcpwmId : std::uint8_t" in content
    primary = _struct_block(content, "McpwmTraits")
    assert "static constexpr bool kPresent = false;" in primary
    assert "static constexpr std::array<std::uint16_t, 0> kGpioMatrixSignals = {};" in primary
    assert "MCPWM0 = 1," in content
    assert "MCPWM1 = 2," in content


def test_mcpwm_traits_absent_on_esp32c3(
    espressif_execution_context: ExecutionContext,
) -> None:
    """ESP32-C3 ships no MCPWM controller — only the primary template
    fires, no specializations and no ID-enum entries beyond None."""
    content = _emit_pwm_hpp(espressif_execution_context, "esp32c3")
    assert "enum class RuntimeMcpwmId : std::uint8_t" in content
    assert "MCPWM0 = " not in content
    assert "MCPWM1 = " not in content


# ---------------------------------------------------------------------------
# Phase C: iMXRT FlexPWM
# ---------------------------------------------------------------------------


@pytest.mark.parametrize("device", ["mimxrt1062", "mimxrt1064"])
def test_flex_pwm_traits_block_emits_for_imxrt(
    nxp_execution_context: ExecutionContext, device: str
) -> None:
    content = _emit_pwm_hpp(nxp_execution_context, device)
    assert "enum class RuntimeFlexPwmId : std::uint8_t" in content
    primary = _struct_block(content, "FlexPwmTraits")
    assert "static constexpr bool kPresent = false;" in primary
    assert "static constexpr std::uint8_t kSubmoduleCount = 0u;" in primary
    for ctrl in ("PWM1", "PWM2", "PWM3", "PWM4"):
        assert f"{ctrl} = " in content
        assert f"FlexPwmTraits<RuntimeFlexPwmId::{ctrl}>" in content


# ---------------------------------------------------------------------------
# Phase D: AVR-DA TCA + SAME70 PWM/TC
# ---------------------------------------------------------------------------


def test_avr_da_tca_pwm_traits_block_emits(
    microchip_avr_da_execution_context: ExecutionContext,
) -> None:
    content = _emit_pwm_hpp(microchip_avr_da_execution_context, "avr128da32")
    assert "enum class RuntimeAvrDaTcaPwmId : std::uint8_t" in content
    primary = _struct_block(content, "AvrDaTcaPwmTraits")
    assert "static constexpr bool kPresent = false;" in primary
    assert "static constexpr std::array<PinId, 0> kDefaultChannelPins = {};" in primary
    assert "TCA0 = 1," in content
    assert "AvrDaTcaPwmTraits<RuntimeAvrDaTcaPwmId::TCA0>" in content
    # default PORTMUX-A pad list must appear in the specialization
    assert "PinId::PA0" in content


def test_same70_pwm_traits_block_emits(
    microchip_execution_context: ExecutionContext,
) -> None:
    content = _emit_pwm_hpp(microchip_execution_context, "atsame70q21b")
    assert "enum class RuntimeSame70PwmKind : std::uint8_t" in content
    assert "Pwm = 1," in content
    assert "Tc = 2," in content
    assert "enum class RuntimeSame70PwmId : std::uint8_t" in content
    primary = _struct_block(content, "Same70PwmTraits")
    assert "static constexpr bool kPresent = false;" in primary
    assert "RuntimeSame70PwmKind kKind = RuntimeSame70PwmKind::None;" in primary
    # SAM E70 ships PWM0/PWM1 plus TC0..TC3
    for ctrl in ("PWM0", "PWM1", "TC0", "TC1", "TC2", "TC3"):
        assert f"{ctrl} = " in content
        assert f"Same70PwmTraits<RuntimeSame70PwmId::{ctrl}>" in content
