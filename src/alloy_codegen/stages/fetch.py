"""Fetch stage bootstrap implementation."""

from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.manifests import SourceManifest, SourceRecord
from alloy_codegen.reporting import FetchBundle
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.common import StageResult
from alloy_codegen.vendors import resolve_vendor_adapter


def _fetch_records_for_scope(
    execution_context: ExecutionContext,
    validated_scope: PipelineScope,
) -> tuple[dict[str, str], ...]:
    """add-vendor-adapter-registry: dispatch via the central registry.

    Returns an empty tuple when no adapter is registered — callers
    treat that as "scope has no fetchable upstream sources" rather
    than a hard error, matching the prior cascade's fall-through."""
    vendor = validated_scope.resolved_vendor()
    family = validated_scope.resolved_family()
    try:
        adapter = resolve_vendor_adapter(vendor, family)
    except StageExecutionError:
        return ()
    return adapter.fetch(execution_context, validated_scope)


def run(scope: PipelineScope, context: ExecutionContext | None = None) -> StageResult:
    """Run the bootstrap fetch stage."""
    execution_context = context or ExecutionContext.default()
    validated_scope = scope.validate_supported()
    records = _fetch_records_for_scope(execution_context, validated_scope)
    source_manifest = SourceManifest(
        manifest_kind="source-manifest-v1",
        bootstrap_family=validated_scope.resolved_family(),
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
