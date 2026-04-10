"""Publish stage bootstrap implementation."""

from __future__ import annotations

from alloy_codegen.bootstrap import BOOTSTRAP_FAMILY, PUBLICATION_TARGET_REPOSITORY
from alloy_codegen.consumer_verification import verify_alloy_smoke_consumer
from alloy_codegen.context import ExecutionContext
from alloy_codegen.emission import emit_publication_summary, materialize_artifacts
from alloy_codegen.publication import (
    compute_target_artifact_revision,
    emit_publication_record,
    prepare_staging_root,
    promote_staging_root,
)
from alloy_codegen.reporting import PublicationPlan
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.common import StageResult
from alloy_codegen.stages.emit import run as run_emit
from alloy_codegen.stages.validate import run as run_validate


def run(scope: PipelineScope, context: ExecutionContext | None = None) -> StageResult:
    """Run the bootstrap publish stage."""
    execution_context = context or ExecutionContext.default()
    validate_result = run_validate(scope, execution_context)
    if not validate_result.payload.report.is_passing:
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
            ),
            warnings=("Validation did not pass; publication is blocked.",),
        )

    emit_result = run_emit(scope, execution_context)
    staging_root = prepare_staging_root(execution_context.publication_root)
    staged_artifacts = materialize_artifacts(
        artifact_root=staging_root,
        artifacts=emit_result.payload.artifacts,
    )
    consumer_verification = verify_alloy_smoke_consumer(
        scope=emit_result.scope,
        alloy_root=execution_context.alloy_root,
        publication_root=staging_root,
        build_root=execution_context.artifact_root,
    )
    if not consumer_verification.succeeded:
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
                consumer_verification=consumer_verification,
            ),
            warnings=("Alloy smoke consumer failed to build from staged artifacts.",),
        )

    target_artifact_revision = compute_target_artifact_revision(staged_artifacts)
    publication_record = emit_publication_record(
        family_dir=f"st/{BOOTSTRAP_FAMILY}",
        scope=emit_result.scope,
        target_repository=PUBLICATION_TARGET_REPOSITORY,
        publication_mode="published",
        target_artifact_revision=target_artifact_revision,
        artifact_manifest=emit_result.payload.artifact_manifest,
        validation_report=validate_result.payload.report,
        published_artifacts=staged_artifacts,
        consumer_verification=consumer_verification,
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
        family_dir=f"st/{BOOTSTRAP_FAMILY}",
        target_repository=PUBLICATION_TARGET_REPOSITORY,
        publication_mode="published",
        artifact_manifest=emit_result.payload.artifact_manifest,
        artifacts=published_bundle,
        publication_root=str(execution_context.publication_root),
        target_artifact_revision=target_artifact_revision,
        consumer_verification=consumer_verification,
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
            consumer_verification=consumer_verification,
            publication_record=published_record,
            publication_summary=materialized_summary,
        ),
        warnings=(),
    )
