from __future__ import annotations

import json
from pathlib import Path

import pytest

from alloy_codegen.bootstrap import (
    BOOTSTRAP_FAMILY,
    bootstrap_device_names,
    registered_device_names,
)
from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.normalize import run

G0_FIXTURE_DIR = Path(__file__).parent / "fixtures" / BOOTSTRAP_FAMILY
F4_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "stm32f4"
SAME70_FIXTURE_DIR = Path(__file__).parent / "fixtures" / "same70"


@pytest.mark.parametrize("device_name", bootstrap_device_names())
def test_normalize_matches_bootstrap_fixture(
    device_name: str,
    execution_context: ExecutionContext,
) -> None:
    fixture_path = G0_FIXTURE_DIR / f"{device_name}.canonical.json"
    expected = json.loads(fixture_path.read_text())

    result = run(PipelineScope(device=device_name), execution_context)

    assert result.payload.devices[0].to_dict() == expected


@pytest.mark.parametrize("device_name", registered_device_names("st", "stm32f4"))
def test_normalize_matches_stm32f4_fixture(
    device_name: str,
    execution_context: ExecutionContext,
) -> None:
    fixture_path = F4_FIXTURE_DIR / f"{device_name}.canonical.json"
    expected = json.loads(fixture_path.read_text())

    result = run(PipelineScope(device=device_name), execution_context)

    assert result.payload.devices[0].to_dict() == expected


def test_normalize_f4_uses_correct_family_identity(
    execution_context: ExecutionContext,
) -> None:
    result = run(PipelineScope(device="stm32f401re"), execution_context)
    device = result.payload.devices[0]

    assert device.identity.vendor == "st"
    assert device.identity.family == "stm32f4"
    assert device.schema_version == "1.1.0"


def test_normalize_g0_and_f4_use_same_schema_version(
    execution_context: ExecutionContext,
) -> None:
    g0_result = run(PipelineScope(device="stm32g071rb"), execution_context)
    f4_result = run(PipelineScope(device="stm32f401re"), execution_context)

    g0_version = g0_result.payload.devices[0].schema_version
    f4_version = f4_result.payload.devices[0].schema_version
    assert g0_version == f4_version


@pytest.mark.parametrize("device_name", registered_device_names("microchip", "same70"))
def test_normalize_matches_same70_fixture(
    device_name: str,
    microchip_execution_context: ExecutionContext,
) -> None:
    fixture_path = SAME70_FIXTURE_DIR / f"{device_name}.canonical.json"
    expected = json.loads(fixture_path.read_text())

    result = run(PipelineScope(device=device_name), microchip_execution_context)

    assert result.payload.devices[0].to_dict() == expected


def test_normalize_same70_uses_correct_family_identity(
    microchip_execution_context: ExecutionContext,
) -> None:
    result = run(PipelineScope(device="atsame70q21b"), microchip_execution_context)
    device = result.payload.devices[0]

    assert device.identity.vendor == "microchip"
    assert device.identity.family == "same70"
    assert device.schema_version == "1.1.0"


def test_normalize_g0_and_same70_use_same_schema_version(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
) -> None:
    g0_result = run(PipelineScope(device="stm32g071rb"), execution_context)
    same70_result = run(PipelineScope(device="atsame70q21b"), microchip_execution_context)

    g0_version = g0_result.payload.devices[0].schema_version
    same70_version = same70_result.payload.devices[0].schema_version
    assert g0_version == same70_version
