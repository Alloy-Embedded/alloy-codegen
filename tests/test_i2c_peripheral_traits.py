"""Tests for the populated I2cPeripheralTraits surface.

Covers the contract added by the ``fill-i2c-semantic-gaps`` change.
Phase A wires the STM32-family normalizer; subsequent phases extend
coverage to Espressif (B), RP2040 (C), AVR-DA (D).

Detailed per-controller assertions on STM32 are intentionally limited
because the ``execution_context`` fixture ships a *minimal* SVD slice
that does not include the I2C peripherals — exercising the populated
specialization end-to-end against the real upstream sources is left
to ``test_rp2040_i2c_traits.py`` / ``test_espressif_i2c_traits.py`` in
later phases.
"""

from __future__ import annotations

import re

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _emit_i2c_hpp(context: ExecutionContext, device: str) -> str:
    result = run_emit(PipelineScope(device=device), context)
    artifact = next(
        a for a in result.payload.artifacts if a.path.endswith(f"/{device}/driver_semantics/i2c.hpp")
    )
    return artifact.content


def _struct_block(content: str, header: str) -> str:
    match = re.search(rf"struct {re.escape(header)} \{{(.*?)\n}};", content, re.DOTALL)
    assert match is not None, f"missing struct: {header}"
    return match.group(1)


def test_primary_i2c_peripheral_traits_carries_zero_defaults(
    execution_context: ExecutionContext,
) -> None:
    """Every emitted i2c.hpp declares the new ``I2cPeripheralTraits``
    primary template with zero defaults so non-I2C-bearing families
    remain zero-cost."""
    content = _emit_i2c_hpp(execution_context, "stm32g071rb")

    primary = _struct_block(content, "I2cPeripheralTraits")
    assert "static constexpr bool kPresent = false;" in primary
    assert "static constexpr std::uint32_t kBaseAddress = 0u;" in primary
    assert "static constexpr bool kSupportsFastModePlus = false;" in primary
    assert "static constexpr std::array<std::string_view, 0> kValidSdaPins = {};" in primary
    assert "static constexpr std::array<std::string_view, 0> kValidSclPins = {};" in primary
    assert "static constexpr std::uint16_t kInSdaSignal = 0xFFFFu;" in primary


def test_runtime_i2c_ctrl_id_enum_is_emitted(
    execution_context: ExecutionContext,
) -> None:
    """The ``RuntimeI2cCtrlId`` enum is emitted alongside the trait
    template — even when the slice doesn't expose I2C peripherals,
    the enum class declaration with the ``None = 0`` sentinel is
    always present so consumers compile against a stable surface."""
    content = _emit_i2c_hpp(execution_context, "stm32g071rb")
    assert "enum class RuntimeI2cCtrlId : std::uint8_t" in content
    assert "None = 0," in content
