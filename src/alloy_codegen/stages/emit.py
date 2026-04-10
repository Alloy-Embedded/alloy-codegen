"""Emit stage bootstrap implementation."""

from __future__ import annotations

from alloy_codegen.bootstrap import (
    ARTIFACT_LAYOUT_VERSION,
    BOOTSTRAP_FAMILY,
    CPP_CONTRACT_VERSION,
    IR_SCHEMA_VERSION,
    PIPELINE_NAME,
    PUBLICATION_TARGET_REPOSITORY,
)
from alloy_codegen.context import ExecutionContext
from alloy_codegen.emission import (
    emit_artifact_manifest,
    emit_device_metadata,
    emit_family_connectivity,
    emit_family_index,
    emit_gpio_header,
    emit_pin_functions_header,
    emit_register_map_header,
    emit_startup_source,
    emit_validation_report,
    materialize_artifacts,
)
from alloy_codegen.manifests import ArtifactManifest
from alloy_codegen.reporting import EmissionPlan, EmittedArtifact
from alloy_codegen.scope import PipelineScope
from alloy_codegen.serialization import canonical_json_sha256
from alloy_codegen.stages.common import StageResult
from alloy_codegen.stages.validate import run as run_validate
from alloy_codegen.version import __version__


def run(scope: PipelineScope, context: ExecutionContext | None = None) -> StageResult:
    """Run the bootstrap emit stage."""
    execution_context = context or ExecutionContext.default()
    validate_result = run_validate(scope, execution_context)
    source_manifest = validate_result.payload.source_manifest
    patch_manifest = validate_result.payload.patch_manifest
    devices = validate_result.payload.devices
    validation_report = validate_result.payload.report
    artifact_manifest = ArtifactManifest.for_scope(
        generator_version=__version__,
        ir_schema_version=IR_SCHEMA_VERSION,
        scope=validate_result.scope,
        source_manifest=source_manifest,
        patch_manifest=patch_manifest,
        canonical_ir_sha256=canonical_json_sha256(devices),
        validation_report_id=validation_report.report_id,
        validation_report_sha256=canonical_json_sha256(validation_report.to_dict()),
        pipeline_name=PIPELINE_NAME,
        artifact_layout_version=ARTIFACT_LAYOUT_VERSION,
        cpp_contract_version=CPP_CONTRACT_VERSION,
        target_repository=PUBLICATION_TARGET_REPOSITORY,
    )

    family_dir = f"st/{BOOTSTRAP_FAMILY}"
    artifacts: list[EmittedArtifact] = [
        emit_artifact_manifest(family_dir=family_dir, artifact_manifest=artifact_manifest),
        emit_validation_report(family_dir=family_dir, report=validation_report),
        emit_family_index(family_dir=family_dir, devices=devices),
        emit_family_connectivity(family_dir=family_dir, devices=devices),
    ]
    for device in devices:
        artifacts.extend(
            (
                emit_device_metadata(family_dir=family_dir, device=device),
                emit_register_map_header(family_dir=family_dir, device=device),
                emit_pin_functions_header(family_dir=family_dir, device=device),
                emit_startup_source(family_dir=family_dir, device=device),
            )
        )
    gpio_names = sorted(
        {
            peripheral.name
            for device in devices
            for peripheral in device.peripherals
            if peripheral.ip_name == "gpio"
        }
    )
    for gpio_name in gpio_names:
        artifacts.append(
            emit_gpio_header(
                family_dir=family_dir,
                devices=devices,
                peripheral_name=gpio_name,
            )
        )
    materialized_artifacts = materialize_artifacts(
        artifact_root=execution_context.artifact_root,
        artifacts=tuple(artifacts),
    )

    return StageResult(
        stage="emit",
        scope=validate_result.scope,
        status="completed",
        payload=EmissionPlan(
            artifact_manifest=artifact_manifest,
            artifacts=materialized_artifacts,
        ),
    )
