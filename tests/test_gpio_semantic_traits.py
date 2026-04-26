"""Tests for the populated GpioSemanticTraits AF fields.

Covers the contract added by the ``fill-gpio-semantic-gaps`` change. The
test scope is currently STM32G0 (Phase A); each subsequent phase will add
its family's coverage here.

The ``execution_context`` fixture provides a *minimal* stm32-open-pin-data
slice (only a subset of pins; see ``tests/fixtures/stm32-open-pin-data``),
so these assertions intentionally target pins that are present in that
slice (PA0, PB6) rather than the canonical Nucleo LED pin PA5 (which is
covered end-to-end via the regenerated golden ``gpio.hpp``).
"""

from __future__ import annotations

import re

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _emit_gpio_hpp(context: ExecutionContext, device: str) -> str:
    result = run_emit(PipelineScope(device=device), context)
    artifact = next(
        a for a in result.payload.artifacts if a.path.endswith(f"/{device}/driver_semantics/gpio.hpp")
    )
    return artifact.content


def _struct_block(content: str, header: str) -> str:
    match = re.search(rf"struct {re.escape(header)} \{{(.*?)\n}};", content, re.DOTALL)
    assert match is not None, f"missing struct: {header}"
    return match.group(1)


def test_primary_template_carries_zero_defaulted_af_fields(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_gpio_hpp(execution_context, "stm32g071rb")

    primary = _struct_block(content, "GpioSemanticTraits")
    assert "static constexpr std::uint32_t kPortOffset = 0u;" in primary
    assert "static constexpr std::uint32_t kPinIndex = 0u;" in primary
    assert "static constexpr std::uint8_t kMaxAltFunction = 0u;" in primary
    assert "static constexpr std::array<std::uint8_t, 0> kValidAltFunctions = {};" in primary


def test_stm32g071rb_pa0_specialization_records_port_topology(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_gpio_hpp(execution_context, "stm32g071rb")

    pa0 = _struct_block(content, "GpioSemanticTraits<PinId::PA0>")
    assert "static constexpr bool kPresent = true;" in pa0
    assert "static constexpr std::uint32_t kPortOffset = 0u;" in pa0  # GPIOA base
    assert "static constexpr std::uint32_t kPinIndex = 0u;" in pa0


def test_stm32g071rb_pb6_specialization_records_distinct_port_offset(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_gpio_hpp(execution_context, "stm32g071rb")

    pb6 = _struct_block(content, "GpioSemanticTraits<PinId::PB6>")
    # GPIOB is +0x400 from GPIOA on STM32 (4 KiB stride).
    assert "static constexpr std::uint32_t kPortOffset = 0x00000400u;" in pb6
    assert "static constexpr std::uint32_t kPinIndex = 6u;" in pb6
    # PB6 has at least one alternate function in the test OPD slice.
    assert "kValidAltFunctions = {{0u}};" in pb6


def test_stm32g071rb_emits_at_least_one_present_specialization(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_gpio_hpp(execution_context, "stm32g071rb")
    assert content.count("kPresent = true;") >= 1
