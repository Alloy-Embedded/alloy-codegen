"""Fetch stage bootstrap implementation.

After ``consume-alloy-devices-yml-as-canonical-input`` the only
upstream source is the ``alloy-devices-yml`` submodule mounted at
``data/devices/``.  Fetch records describe each device's YAML
file path so downstream stages and manifests can record what was
consumed.  No remote-vendor parsing happens in this repo.
"""

from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.manifests import SourceManifest, SourceRecord
from alloy_codegen.reporting import FetchBundle
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.common import StageResult


def _fetch_records_for_scope(
    execution_context: ExecutionContext,
    validated_scope: PipelineScope,
) -> tuple[dict[str, str], ...]:
    """Synthesise one source record per device from the
    canonical-YAML data repo.  Raises if any device's YAML is
    missing — admission is YAML-only after
    ``consume-alloy-devices-yml-as-canonical-input``."""
    del execution_context  # No upstream parsing happens here anymore.
    from alloy_codegen.sources import alloy_devices_yml as _adyml

    vendor = validated_scope.resolved_vendor()
    family = validated_scope.resolved_family()

    records: list[dict[str, str]] = []
    revision = _adyml.submodule_revision() or "unknown"
    for device in validated_scope.resolved_device_names():
        path = _adyml.resolve_device_yaml(vendor=vendor, family=family, device=device)
        if path is None:
            missing = _adyml.device_yaml_path(vendor=vendor, family=family, device=device)
            raise StageExecutionError(
                f"canonical device YAML missing at {missing}.  "
                "Admit the device by committing its YAML to the "
                "alloy-devices-yml data repo (this codegen repo is "
                "consumer-only after consume-alloy-devices-yml-as-canonical-input)."
            )
        records.append(
            {
                "source_id": "alloy-devices-yml",
                "target_device": device,
                "origin_url": "https://github.com/Alloy-Embedded/alloy-devices-yml",
                "revision": f"git-sha:{revision}",
                "local_path": str(path),
                "upstream_path": str(path.relative_to(_adyml.DATA_REPO_ROOT)),
            }
        )
    return tuple(records)


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
