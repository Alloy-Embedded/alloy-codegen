from __future__ import annotations

import json
from pathlib import Path

import pytest

from alloy_codegen.bootstrap import BOOTSTRAP_FAMILY, bootstrap_device_names
from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.normalize import run

FIXTURE_DIR = Path(__file__).parent / "fixtures" / BOOTSTRAP_FAMILY


@pytest.mark.parametrize("device_name", bootstrap_device_names())
def test_normalize_matches_bootstrap_fixture(
    device_name: str,
    execution_context: ExecutionContext,
) -> None:
    fixture_path = FIXTURE_DIR / f"{device_name}.canonical.json"
    expected = json.loads(fixture_path.read_text())

    result = run(PipelineScope(device=device_name), execution_context)

    assert result.payload.devices[0].to_dict() == expected
