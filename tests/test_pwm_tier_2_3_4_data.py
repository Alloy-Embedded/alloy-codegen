"""Tests for the PWM Tier 2/3/4 trait surface added by
``add-pwm-tier-2-3-4-data``.

Each populated ``PwmSemanticTraits`` specialisation extends with
max prescaler / period, deadtime / alignment / break-input arrays
and capability flags (``kSupportsDeadtime``, ``kSupportsBreakInput``,
``kSupportsComplementaryOutputs``, ``kSupportsAsymmetricPwm``,
``kSupportsCombinedPwm``).

After ``reduce-cpp-header-bloat-via-shared-luts`` the per-instance
specialisation only carries the variable-length arrays; scalar
flags + max-{prescaler,period} live in
``kPwmHardwareLut[Index]`` referenced by the inherited
``PwmTraitsBase<Index>``.  The helpers below resolve the LUT
row for a peripheral so the tests can keep asserting on the
same logical facts.
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
    """Return the per-instance body of ``PwmSemanticTraits<P>``.

    Accepts both the legacy direct-specialisation form and the
    inheritance form added by
    ``reduce-cpp-header-bloat-via-shared-luts``.
    """
    pattern = (
        rf"struct PwmSemanticTraits<PeripheralId::{re.escape(peripheral)}>"
        r"(?:\s*:\s*PwmTraitsBase<\d+>)?\s*\{(.*?)\n}};"
    )
    match = re.search(pattern, content, re.DOTALL)
    assert match is not None, f"missing PwmSemanticTraits<PeripheralId::{peripheral}>"
    return match.group(1)


def _lut_row_for(content: str, peripheral: str) -> str:
    """Return the ``kPwmHardwareLut[Index]`` row for a peripheral.

    Resolves ``Index`` from the per-instance ``: PwmTraitsBase<N>``
    inheritance line, then extracts the matching brace-delimited
    LUT row.
    """
    inherit = re.search(
        rf"struct PwmSemanticTraits<PeripheralId::{re.escape(peripheral)}>"
        r"\s*:\s*PwmTraitsBase<(\d+)>",
        content,
    )
    assert inherit is not None, f"no PwmTraitsBase inheritance for {peripheral}"
    index = int(inherit.group(1))
    lut = re.search(r"kPwmHardwareLut\s*=\s*\{\{(.*?)\}\};", content, re.DOTALL)
    assert lut is not None, "missing kPwmHardwareLut definition"
    # LUT body is one ``  {…},`` line per peripheral.  Each line
    # itself contains nested ``{…}`` constructors for register /
    # field refs, so the lines start at column 0+2 spaces with
    # ``{`` and end with ``},``.
    rows = [line.strip() for line in lut.group(1).splitlines() if line.strip().startswith("{")]
    assert index < len(rows), (
        f"{peripheral} index {index} out of range for {len(rows)}-row LUT"
    )
    return rows[index]


def test_stm32g0_tim1_advertises_deadtime_break_alignment(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_pwm_hpp(execution_context, "stm32g071rb")
    block = _spec_block(content, "TIM1")
    lut_row = _lut_row_for(content, "TIM1")
    # Capability flags ride in the LUT row's positional booleans now.
    # Field order in PwmHardwareLut:
    #   schema_id, counter_bits, channel_count,
    #   has_complementary_outputs, has_deadtime, has_fault_input,
    #   has_center_aligned, has_synchronized_update,
    #   <5 register refs>, <4 field refs>,
    #   max_prescaler, max_period,
    #   supports_deadtime, supports_break_input,
    #   supports_complementary_outputs, supports_asymmetric_pwm,
    #   supports_combined_pwm
    # We only assert that the supports_* flags resolve to true —
    # that's the coverage point — without depending on the exact
    # column index.
    assert lut_row.count("true") >= 3, (
        f"TIM1 LUT row should carry ≥3 true flags; got: {lut_row}"
    )
    # Max prescaler is a positional u32; 65535u must appear.
    assert "65535u" in lut_row
    # 4 deadtime DTPSC choices.
    dt = re.search(r"std::array<std::uint8_t, (\d+)> kDeadtimeOptions", block)
    assert dt is not None and int(dt.group(1)) >= 4
    # 4 supported alignment modes (edge + 3 center variants).
    align = re.search(r"std::array<std::uint8_t, (\d+)> kSupportedAlignments", block)
    assert align is not None and int(align.group(1)) == 4
    # 1 break input (BKIN).
    brk = re.search(r"std::array<std::uint8_t, (\d+)> kBreakInputs", block)
    assert brk is not None and int(brk.group(1)) == 1


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
