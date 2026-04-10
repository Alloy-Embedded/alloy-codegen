from __future__ import annotations

import json
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run


def _load_json_fixture(path: Path) -> dict[str, object]:
    return json.loads(path.read_text(encoding="utf-8"))


def _normalize_manifest_payload(
    payload: dict[str, object],
    *,
    fixture_source_root: Path,
) -> dict[str, object]:
    normalized = json.loads(json.dumps(payload))
    source_manifest = normalized["source_manifest"]
    for source in source_manifest["sources"]:
        local_path = Path(source["local_path"])
        source["local_path"] = str(local_path.relative_to(fixture_source_root))
    return normalized


def test_emit_includes_metadata_artifacts_with_content(
    execution_context: ExecutionContext,
) -> None:
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}

    assert result.stage == "emit"
    assert result.payload.artifact_manifest.manifest_kind == "artifact-manifest-v1"

    manifest_artifact = artifacts["st/stm32g0/artifact-manifest.json"]
    validation_artifact = artifacts["st/stm32g0/validation-report.json"]
    family_index_artifact = artifacts["st/stm32g0/family-index.json"]
    connectivity_artifact = artifacts["st/stm32g0/family-connectivity.json"]
    device_artifact = artifacts["st/stm32g0/stm32g071rb/device.json"]
    register_map_artifact = artifacts["st/stm32g0/stm32g071rb/register_map.hpp"]
    pin_functions_artifact = artifacts["st/stm32g0/stm32g071rb/pin_functions.hpp"]
    startup_artifact = artifacts["st/stm32g0/stm32g071rb/startup.cpp"]
    gpioa_artifact = artifacts["st/stm32g0/generated/peripherals/gpioa.hpp"]

    for artifact in (
        manifest_artifact,
        validation_artifact,
        family_index_artifact,
        connectivity_artifact,
        device_artifact,
    ):
        assert artifact.artifact_kind in {"canonical-metadata", "validation-report"}
        assert artifact.content is not None
        assert artifact.content_sha256 is not None
        assert artifact.content_bytes and artifact.content_bytes > 0
        assert artifact.materialized_path is not None
        assert Path(artifact.materialized_path).exists()

    manifest_payload = json.loads(manifest_artifact.content)
    validation_payload = json.loads(validation_artifact.content)
    family_index_payload = json.loads(family_index_artifact.content)
    connectivity_payload = json.loads(connectivity_artifact.content)
    device_payload = json.loads(device_artifact.content)

    assert manifest_payload["manifest_kind"] == "artifact-manifest-v1"
    assert manifest_payload["validation_report_id"] == "bootstrap-validation-v1"
    assert len(manifest_payload["canonical_ir_sha256"]) == 64
    assert len(manifest_payload["validation_report_sha256"]) == 64
    assert manifest_payload["source_manifest"]["manifest_kind"] == "source-manifest-v1"
    assert manifest_payload["patch_manifest"]["manifest_kind"] == "patch-manifest-v1"
    assert manifest_payload["build_metadata"]["target_repository"] == "alloy-devices"
    assert manifest_payload["build_metadata"]["artifact_layout_version"] == "alloy-devices-v1"
    assert validation_payload["report_id"] == "bootstrap-validation-v1"
    assert family_index_payload["device_count"] == 1
    assert family_index_payload["devices"][0]["device"] == "stm32g071rb"
    assert (
        family_index_payload["devices"][0]["metadata_path"]
        == "st/stm32g0/stm32g071rb/device.json"
    )
    assert any(pin["name"] == "PA0" for pin in connectivity_payload["pins"])
    assert device_payload["identity"]["device"] == "stm32g071rb"

    for artifact in (
        register_map_artifact,
        pin_functions_artifact,
        startup_artifact,
        gpioa_artifact,
    ):
        assert artifact.artifact_kind == "generated-cpp"
        assert artifact.content is not None
        assert artifact.content_sha256 is not None
        assert artifact.materialized_path is not None
        assert Path(artifact.materialized_path).exists()

    assert "kPeripheralBases" in register_map_artifact.content
    assert "kPinFunctions" in pin_functions_artifact.content
    assert "kInterruptTable" in startup_artifact.content
    assert "kPeripheral" in gpioa_artifact.content


def test_emit_matches_golden_artifacts(
    execution_context: ExecutionContext,
    fixture_source_root: Path,
) -> None:
    result = run(PipelineScope(device="stm32g071rb"), execution_context)
    artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}
    fixture_root = Path(__file__).parent / "fixtures" / "emitted" / "stm32g0"

    manifest_payload = json.loads(artifacts["st/stm32g0/artifact-manifest.json"].content)
    validation_payload = json.loads(artifacts["st/stm32g0/validation-report.json"].content)

    assert _normalize_manifest_payload(
        manifest_payload,
        fixture_source_root=fixture_source_root,
    ) == _load_json_fixture(fixture_root / "stm32g071rb" / "artifact-manifest.json")
    assert validation_payload == _load_json_fixture(
        fixture_root / "stm32g071rb" / "validation-report.json"
    )
    assert artifacts["st/stm32g0/stm32g071rb/register_map.hpp"].content == (
        fixture_root / "stm32g071rb" / "register_map.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/stm32g071rb/pin_functions.hpp"].content == (
        fixture_root / "stm32g071rb" / "pin_functions.hpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/stm32g071rb/startup.cpp"].content == (
        fixture_root / "stm32g071rb" / "startup.cpp"
    ).read_text(encoding="utf-8")
    assert artifacts["st/stm32g0/generated/peripherals/gpioa.hpp"].content == (
        fixture_root / "generated" / "peripherals" / "gpioa.hpp"
    ).read_text(encoding="utf-8")


def test_emit_stage_is_byte_stable(execution_context: ExecutionContext) -> None:
    scope = PipelineScope()
    result_a = json.dumps(run(scope, execution_context).to_dict(), sort_keys=True)
    result_b = json.dumps(run(scope, execution_context).to_dict(), sort_keys=True)

    assert result_a == result_b
