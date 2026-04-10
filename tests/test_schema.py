from __future__ import annotations

import json
from pathlib import Path


def test_canonical_ir_schema_is_present_and_named() -> None:
    schema_path = (
        Path(__file__).resolve().parents[1] / "schemas" / "canonical-device-ir-v1.schema.json"
    )
    schema = json.loads(schema_path.read_text())

    assert schema["title"] == "CanonicalDeviceIR"
    assert "identity" in schema["properties"]
    assert schema["properties"]["pins"]["items"]["required"] == [
        "name",
        "port",
        "number",
        "signals",
        "provenance",
    ]
