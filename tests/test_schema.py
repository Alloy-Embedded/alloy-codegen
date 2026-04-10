from __future__ import annotations

import json
from pathlib import Path

from alloy_codegen.bootstrap import IR_SCHEMA_VERSION
from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.normalize import run as run_normalize

SCHEMAS_DIR = Path(__file__).resolve().parents[1] / "schemas"


def test_canonical_ir_schema_is_present_and_named() -> None:
    schema_path = SCHEMAS_DIR / "canonical-device-ir-v1.schema.json"
    schema = json.loads(schema_path.read_text())

    assert schema["title"] == "CanonicalDeviceIR"
    assert "identity" in schema["properties"]
    assert "ip_blocks" in schema["properties"]
    assert "connection_candidates" in schema["properties"]
    assert "connection_groups" in schema["properties"]
    assert "vector_slots" in schema["properties"]
    assert "startup_descriptors" in schema["properties"]
    assert "clock_nodes" in schema["properties"]
    assert schema["$defs"]["pin_definition"]["required"] == [
        "name",
        "port",
        "number",
        "signals",
        "provenance",
    ]


def test_ir_schema_version_constant_is_pinned() -> None:
    # IR_SCHEMA_VERSION must not change without a schema file rename; pinning it
    # here means any bump requires updating this test deliberately.
    assert IR_SCHEMA_VERSION == "1.1.0"


def test_ir_schema_file_name_encodes_major_version() -> None:
    major = IR_SCHEMA_VERSION.split(".")[0]
    expected_name = f"canonical-device-ir-v{major}.schema.json"
    assert (SCHEMAS_DIR / expected_name).exists(), (
        f"Schema file '{expected_name}' not found. "
        "Rename the schema file when the major version changes."
    )


def test_normalized_ir_carries_schema_version(execution_context: ExecutionContext) -> None:
    result = run_normalize(PipelineScope(device="stm32g071rb"), execution_context)
    assert result.payload.devices[0].schema_version == IR_SCHEMA_VERSION
