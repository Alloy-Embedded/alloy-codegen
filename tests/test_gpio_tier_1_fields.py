"""Tests for the STM32 GPIO Tier-1 field surface added by
``fill-gpio-tier-1-fields``.

The four primary configuration fields (`kModeField`, `kSpeedField`,
`kOutputTypeField`, `kPullField`) MUST resolve to non-`kInvalidFieldRef`
records on STM32 for every admitted pin so the alloy GPIO HAL can
generate compile-time register writes without falling back to vendor
headers.  Other-vendor specialisations stay byte-stable.
"""

from __future__ import annotations

import re

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


def _emit_gpio_hpp(context: ExecutionContext, device: str) -> str:
    result = run_emit(PipelineScope(device=device), context)
    suffix = f"/{device}/driver_semantics/gpio.hpp"
    artifact = next(a for a in result.payload.artifacts if a.path.endswith(suffix))
    return artifact.content


def _spec_block(content: str, pin_id: str) -> str:
    pattern = rf"struct GpioSemanticTraits<PinId::{re.escape(pin_id)}> \{{(.*?)\n}};"
    match = re.search(pattern, content, re.DOTALL)
    assert match is not None, f"missing specialisation for PinId::{pin_id}"
    return match.group(1)


def test_stm32g0_pa0_surfaces_valid_tier1_fields(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_gpio_hpp(execution_context, "stm32g071rb")
    block = _spec_block(content, "PA0")
    # All four Tier-1 field refs must be valid (non-kInvalidFieldRef).
    for field in ("kModeField", "kOutputTypeField", "kPullField", "kSpeedField"):
        assert f"{field} = kInvalidFieldRef" not in block, (
            f"{field} on PA0 must be valid after fill-gpio-tier-1-fields"
        )
    # MODE field on PA0 lives in MODER at offset 0x00, bit 0, width 2.
    assert "register_gpioa_moder" in block.lower() or "0x50000000u, 0u" in block
    assert "kModeField = RuntimeFieldRef{" in block
    # bit_offset 0 width 2 for PA0
    mode_match = re.search(r"kModeField = RuntimeFieldRef\{[^}]*\}, (\d+)u, (\d+)u, true\}", block)
    assert mode_match is not None, "could not parse PA0 kModeField"
    assert mode_match.group(1) == "0"
    assert mode_match.group(2) == "2"


def test_stm32g0_pa2_kspeedfield_resolves_to_ospeedr(
    execution_context: ExecutionContext,
) -> None:
    content = _emit_gpio_hpp(execution_context, "stm32g071rb")
    block = _spec_block(content, "PA2")
    assert "kSpeedField = kInvalidFieldRef" not in block
    # OSPEEDR offset is 0x08; PA2 → bit_offset 4 (line_index 2 * 2).
    speed_match = re.search(
        r"kSpeedField = RuntimeFieldRef\{[^}]*0x50000000u, 8u[^}]*\}, (\d+)u, (\d+)u, true\}",
        block,
    )
    assert speed_match is not None, "PA2 kSpeedField did not resolve to OSPEEDR"
    assert speed_match.group(1) == "4"
    assert speed_match.group(2) == "2"


def test_stm32g0_primary_template_kspeedfield_default_invalid(
    execution_context: ExecutionContext,
) -> None:
    """The unspecialised primary template must still ship
    `kSpeedField = kInvalidFieldRef` so non-STM32 specialisations
    inherit the safe default."""
    content = _emit_gpio_hpp(execution_context, "stm32g071rb")
    primary_match = re.search(
        r"template<PinId Id>\nstruct GpioSemanticTraits \{(.*?)\n\};",
        content,
        re.DOTALL,
    )
    assert primary_match is not None
    assert "kSpeedField = kInvalidFieldRef" in primary_match.group(1)


def test_microchip_same70_gpio_unchanged_kspeedfield_invalid(
    microchip_execution_context: ExecutionContext,
) -> None:
    """SAM E70 GPIO specialisations stay invalid for `kSpeedField`
    (not a SAM concept) — the change is STM32-scoped."""
    content = _emit_gpio_hpp(microchip_execution_context, "atsame70q21b")
    primary_match = re.search(
        r"template<PinId Id>\nstruct GpioSemanticTraits \{(.*?)\n\};",
        content,
        re.DOTALL,
    )
    assert primary_match is not None
    assert "kSpeedField = kInvalidFieldRef" in primary_match.group(1)
