"""Fetch stage bootstrap implementation."""

from __future__ import annotations

from alloy_codegen.bootstrap import BOOTSTRAP_FAMILY
from alloy_codegen.context import ExecutionContext
from alloy_codegen.manifests import SourceManifest, SourceRecord
from alloy_codegen.reporting import FetchBundle
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.cmsis_svd import fetch_records as fetch_svd_records
from alloy_codegen.sources.stm32_open_pin_data import fetch_records as fetch_pin_records
from alloy_codegen.stages.common import StageResult


def run(scope: PipelineScope, context: ExecutionContext | None = None) -> StageResult:
    """Run the bootstrap fetch stage."""
    execution_context = context or ExecutionContext.default()
    validated_scope = scope.validate_supported()
    records = (
        *fetch_svd_records(execution_context, validated_scope),
        *fetch_pin_records(execution_context, validated_scope),
    )
    source_manifest = SourceManifest(
        manifest_kind="source-manifest-v1",
        bootstrap_family=BOOTSTRAP_FAMILY,
        targets=validated_scope.resolved_device_names(),
        sources=tuple(
            SourceRecord(
                source_id=record["source_id"],
                target_device=record["target_device"],
                origin_url=record["origin_url"],
                revision=record["revision"],
                local_path=record["local_path"],
                upstream_path=record["upstream_path"],
                scope=validated_scope.to_dict(),
            )
            for record in records
        ),
    )
    return StageResult(
        stage="fetch",
        scope=validated_scope,
        status="completed",
        payload=FetchBundle(source_manifest=source_manifest),
    )
