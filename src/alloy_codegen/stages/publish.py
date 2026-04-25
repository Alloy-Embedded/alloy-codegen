"""Publish stage bootstrap implementation."""

from __future__ import annotations

from alloy_codegen.artifact_contract import (
    find_runtime_cpp_string_violations,
    find_runtime_lite_contract_violations,
)
from alloy_codegen.bootstrap import PUBLICATION_TARGET_REPOSITORY
from alloy_codegen.consumer_verification import verify_runtime_lite_smoke_consumer
from alloy_codegen.context import ExecutionContext
from alloy_codegen.emission import (
    build_coverage_payload,
    emit_publication_summary,
    materialize_artifacts,
)
from alloy_codegen.publication import (
    compute_target_artifact_revision,
    emit_publication_record,
    find_capability_regressions,
    prepare_staging_root,
    promote_staging_root,
)
from alloy_codegen.reporting import PublicationPlan
from alloy_codegen.runtime_readme import emit_devices_readme
from alloy_codegen.runtime_reports import find_runtime_report_violations
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.common import StageResult
from alloy_codegen.stages.emit import run as run_emit
from alloy_codegen.stages.validate import run as run_validate


def run(scope: PipelineScope, context: ExecutionContext | None = None) -> StageResult:
    """Run the bootstrap publish stage."""
    execution_context = context or ExecutionContext.default()
    validate_result = run_validate(scope, execution_context)
    coverage_payload = build_coverage_payload(
        devices=validate_result.payload.devices,
        report=validate_result.payload.report,
    )
    draft_system_descriptor_domains = validate_result.payload.report.draft_system_descriptor_domains
    incomplete_devices = tuple(
        str(device_payload["device"])
        for device_payload in coverage_payload["devices"]
        if not bool(device_payload["publishable"])
    )
    if not validate_result.payload.report.is_passing:
        blocked_by_draft_domains = bool(draft_system_descriptor_domains)
        warning = (
            "Publication is blocked by draft system descriptor domains: "
            f"{', '.join(draft_system_descriptor_domains)}."
            if blocked_by_draft_domains
            else "Validation did not pass; publication is blocked."
        )
        return StageResult(
            stage="publish",
            scope=validate_result.scope,
            status="failed",
            payload=PublicationPlan(
                target_repository=PUBLICATION_TARGET_REPOSITORY,
                publication_mode="blocked",
                artifact_root=str(execution_context.artifact_root),
                publication_root=str(execution_context.publication_root),
                artifact_manifest=None,
                artifacts=(),
                draft_system_descriptor_domains=draft_system_descriptor_domains,
            ),
            warnings=(warning,),
        )
    if not bool(coverage_payload["all_devices_publishable"]):
        warning = (
            "Publication is blocked because the requested scope is not fully publishable: "
            + ", ".join(incomplete_devices)
            + "."
        )
        return StageResult(
            stage="publish",
            scope=validate_result.scope,
            status="failed",
            payload=PublicationPlan(
                target_repository=PUBLICATION_TARGET_REPOSITORY,
                publication_mode="blocked",
                artifact_root=str(execution_context.artifact_root),
                publication_root=str(execution_context.publication_root),
                artifact_manifest=None,
                artifacts=(),
                draft_system_descriptor_domains=draft_system_descriptor_domains,
            ),
            warnings=(warning,),
        )

    emit_result = run_emit(scope, execution_context)
    runtime_contract_violations = find_runtime_cpp_string_violations(emit_result.payload.artifacts)
    if runtime_contract_violations:
        sample = "; ".join(runtime_contract_violations[:3])
        if len(runtime_contract_violations) > 3:
            sample = f"{sample}; ..."
        return StageResult(
            stage="publish",
            scope=emit_result.scope,
            status="failed",
            payload=PublicationPlan(
                target_repository=PUBLICATION_TARGET_REPOSITORY,
                publication_mode="blocked",
                artifact_root=str(execution_context.artifact_root),
                publication_root=str(execution_context.publication_root),
                artifact_manifest=emit_result.payload.artifact_manifest,
                artifacts=emit_result.payload.artifacts,
                draft_system_descriptor_domains=draft_system_descriptor_domains,
            ),
            warnings=(
                "Publication is blocked because runtime-generated C++ artifacts still contain "
                f"semantic string literals: {sample}",
            ),
        )
    runtime_lite_violations = find_runtime_lite_contract_violations(
        family_dir=f"{emit_result.scope.resolved_vendor()}/{emit_result.scope.resolved_family()}",
        devices=validate_result.payload.devices,
        artifacts=emit_result.payload.artifacts,
    )
    if runtime_lite_violations:
        sample = "; ".join(runtime_lite_violations[:3])
        if len(runtime_lite_violations) > 3:
            sample = f"{sample}; ..."
        return StageResult(
            stage="publish",
            scope=emit_result.scope,
            status="failed",
            payload=PublicationPlan(
                target_repository=PUBLICATION_TARGET_REPOSITORY,
                publication_mode="blocked",
                artifact_root=str(execution_context.artifact_root),
                publication_root=str(execution_context.publication_root),
                artifact_manifest=emit_result.payload.artifact_manifest,
                artifacts=emit_result.payload.artifacts,
                draft_system_descriptor_domains=draft_system_descriptor_domains,
            ),
            warnings=(
                "Publication is blocked because runtime-lite artifacts are incomplete or still "
                f"depend on reflection payloads: {sample}",
            ),
        )
    runtime_report_violations = find_runtime_report_violations(
        family_dir=f"{emit_result.scope.resolved_vendor()}/{emit_result.scope.resolved_family()}",
        devices=validate_result.payload.devices,
    )
    if runtime_report_violations:
        sample = "; ".join(runtime_report_violations[:3])
        if len(runtime_report_violations) > 3:
            sample = f"{sample}; ..."
        return StageResult(
            stage="publish",
            scope=emit_result.scope,
            status="failed",
            payload=PublicationPlan(
                target_repository=PUBLICATION_TARGET_REPOSITORY,
                publication_mode="blocked",
                artifact_root=str(execution_context.artifact_root),
                publication_root=str(execution_context.publication_root),
                artifact_manifest=emit_result.payload.artifact_manifest,
                artifacts=emit_result.payload.artifacts,
                draft_system_descriptor_domains=draft_system_descriptor_domains,
            ),
            warnings=(
                "Publication is blocked because runtime provenance/explainability coverage is "
                f"incomplete: {sample}",
            ),
        )
    staging_root = prepare_staging_root(execution_context.publication_root)
    # Inject the auto-generated alloy-devices README at the publication root.
    # The emitter is a pure function over DEVICE_REGISTRY + family/device
    # patches, so every parallel publish job materialises byte-identical
    # content — the workflow's git-status diff trivially detects when the
    # README really changed (see add-publication-scale-features).
    publish_artifacts = (
        *emit_result.payload.artifacts,
        emit_devices_readme(execution_context),
    )
    staged_artifacts = materialize_artifacts(
        artifact_root=staging_root,
        artifacts=publish_artifacts,
    )
    capability_regressions = find_capability_regressions(
        publication_root=execution_context.publication_root,
        staging_root=staging_root,
        family_dir=f"{emit_result.scope.resolved_vendor()}/{emit_result.scope.resolved_family()}",
    )
    if capability_regressions:
        sample = "; ".join(capability_regressions[:3])
        if len(capability_regressions) > 3:
            sample = f"{sample}; ..."
        return StageResult(
            stage="publish",
            scope=emit_result.scope,
            status="failed",
            payload=PublicationPlan(
                target_repository=PUBLICATION_TARGET_REPOSITORY,
                publication_mode="blocked",
                artifact_root=str(execution_context.artifact_root),
                publication_root=str(execution_context.publication_root),
                artifact_manifest=emit_result.payload.artifact_manifest,
                artifacts=emit_result.payload.artifacts,
                draft_system_descriptor_domains=draft_system_descriptor_domains,
            ),
            warnings=(
                "Publication is blocked because capability regression was detected against the "
                f"previous published contract: {sample}",
            ),
        )
    runtime_lite_consumer_verification = verify_runtime_lite_smoke_consumer(
        scope=emit_result.scope,
        alloy_root=execution_context.alloy_root,
        publication_root=staging_root,
        build_root=execution_context.artifact_root,
    )
    if not runtime_lite_consumer_verification.succeeded:
        return StageResult(
            stage="publish",
            scope=emit_result.scope,
            status="failed",
            payload=PublicationPlan(
                target_repository=PUBLICATION_TARGET_REPOSITORY,
                publication_mode="blocked",
                artifact_root=str(execution_context.artifact_root),
                publication_root=str(execution_context.publication_root),
                artifact_manifest=emit_result.payload.artifact_manifest,
                artifacts=emit_result.payload.artifacts,
                consumer_verification=runtime_lite_consumer_verification,
                draft_system_descriptor_domains=draft_system_descriptor_domains,
            ),
            warnings=("Alloy runtime-lite smoke consumer failed to build from staged artifacts.",),
        )
    target_artifact_revision = compute_target_artifact_revision(staged_artifacts)
    publication_record = emit_publication_record(
        family_dir=f"{emit_result.scope.resolved_vendor()}/{emit_result.scope.resolved_family()}",
        scope=emit_result.scope,
        target_repository=PUBLICATION_TARGET_REPOSITORY,
        publication_mode="published",
        target_artifact_revision=target_artifact_revision,
        artifact_manifest=emit_result.payload.artifact_manifest,
        validation_report=validate_result.payload.report,
        published_artifacts=staged_artifacts,
        consumer_verification=runtime_lite_consumer_verification,
    )
    materialize_artifacts(
        artifact_root=staging_root,
        artifacts=(publication_record,),
    )
    promote_staging_root(
        staging_root=staging_root,
        publication_root=execution_context.publication_root,
    )
    published_artifacts = materialize_artifacts(
        artifact_root=execution_context.publication_root,
        artifacts=emit_result.payload.artifacts,
    )
    published_record = materialize_artifacts(
        artifact_root=execution_context.publication_root,
        artifacts=(publication_record,),
    )[0]
    published_bundle = (*published_artifacts, published_record)
    publication_summary = emit_publication_summary(
        family_dir=f"{emit_result.scope.resolved_vendor()}/{emit_result.scope.resolved_family()}",
        target_repository=PUBLICATION_TARGET_REPOSITORY,
        publication_mode="published",
        artifact_manifest=emit_result.payload.artifact_manifest,
        artifacts=published_bundle,
        publication_root=str(execution_context.publication_root),
        target_artifact_revision=target_artifact_revision,
        consumer_verification=runtime_lite_consumer_verification,
    )
    materialized_summary = materialize_artifacts(
        artifact_root=execution_context.artifact_root,
        artifacts=(publication_summary,),
    )[0]
    return StageResult(
        stage="publish",
        scope=emit_result.scope,
        status="completed",
        payload=PublicationPlan(
            target_repository=PUBLICATION_TARGET_REPOSITORY,
            publication_mode="published",
            artifact_root=str(execution_context.artifact_root),
            publication_root=str(execution_context.publication_root),
            artifact_manifest=emit_result.payload.artifact_manifest,
            artifacts=(*emit_result.payload.artifacts, materialized_summary),
            published_artifacts=published_bundle,
            target_artifact_revision=target_artifact_revision,
            consumer_verification=runtime_lite_consumer_verification,
            publication_record=published_record,
            publication_summary=materialized_summary,
            draft_system_descriptor_domains=draft_system_descriptor_domains,
        ),
        warnings=(),
    )
