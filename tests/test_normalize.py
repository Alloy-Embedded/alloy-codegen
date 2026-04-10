from __future__ import annotations

import json
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.normalize import run


def test_normalize_matches_bootstrap_fixture(execution_context: ExecutionContext) -> None:
    fixture_path = (
        Path(__file__).parent / "fixtures" / "stm32g0" / "stm32g071rb.canonical.json"
    )
    expected = json.loads(fixture_path.read_text())

    result = run(PipelineScope(device="stm32g071rb"), execution_context)

    assert result.payload.devices[0].to_dict() == expected
