"""Validate stage bootstrap implementation."""

from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.reporting import ValidationBundle
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.common import StageResult
from alloy_codegen.stages.normalize import run as run_normalize
from alloy_codegen.validation import build_validation_report


def run(scope: PipelineScope, context: ExecutionContext | None = None) -> StageResult:
    """Run the bootstrap validate stage."""
    execution_context = context or ExecutionContext.default()
    normalize_result = run_normalize(scope, execution_context)
    report = build_validation_report(
        scope=normalize_result.scope,
        source_manifest=normalize_result.payload.source_manifest,
        patch_manifest=normalize_result.payload.patch_manifest,
        devices=normalize_result.payload.devices,
    )
    return StageResult(
        stage="validate",
        scope=normalize_result.scope,
        status="completed" if report.is_passing else "failed",
        payload=ValidationBundle(
            source_manifest=normalize_result.payload.source_manifest,
            patch_manifest=normalize_result.payload.patch_manifest,
            devices=normalize_result.payload.devices,
            report=report,
        ),
    )
