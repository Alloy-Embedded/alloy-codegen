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
    than a hard error, matching the prior cascade's fall-through.

    extract-alloy-devices-data-repo: when every device in the scope
    has a canonical YAML committed to the alloy-devices-yml
    submodule, fetch synthesises a record per device pointing at
    the YAML and skips the vendor adapter entirely.  This is what
    lets the pipeline run hermetically against the data repo
    without configuring any upstream source root.
    """
    from alloy_codegen.sources import alloy_devices_yml as _adyml

    vendor = validated_scope.resolved_vendor()
    family = validated_scope.resolved_family()

    devices = validated_scope.resolved_device_names()
    yaml_records: list[dict[str, str]] = []
    legacy_devices: list[str] = []
    for device in devices:
        path = _adyml.resolve_device_yaml(vendor=vendor, family=family, device=device)
        if path is None:
            legacy_devices.append(device)
            continue
        revision = _adyml.submodule_revision() or "unknown"
        yaml_records.append(
            {
                "source_id": "alloy-devices-yml",
                "target_device": device,
                "origin_url": "https://github.com/Alloy-Embedded/alloy-devices-yml",
                "revision": f"git-sha:{revision}",
                "local_path": str(path),
                "upstream_path": str(path.relative_to(_adyml.DATA_REPO_ROOT)),
            }
        )

    if not legacy_devices:
        # Every device admitted via YAML; no adapter fetch needed.
        return tuple(yaml_records)

    # Mixed scope: fall through to the adapter for legacy devices.
    try:
        adapter = resolve_vendor_adapter(vendor, family)
    except StageExecutionError:
        return tuple(yaml_records)
    legacy_records = adapter.fetch(execution_context, validated_scope)
    return (*yaml_records, *legacy_records)


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
