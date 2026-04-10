"""Patch stage bootstrap implementation."""

from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.manifests import PatchManifest, PatchRecord
from alloy_codegen.patches import load_device_patch
from alloy_codegen.reporting import PatchBundle
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.common import StageResult
from alloy_codegen.stages.fetch import run as run_fetch


def run(scope: PipelineScope, context: ExecutionContext | None = None) -> StageResult:
    """Run the bootstrap patch stage."""
    execution_context = context or ExecutionContext.default()
    fetch_result = run_fetch(scope, execution_context)
    source_manifest = fetch_result.payload.source_manifest
    vendor = fetch_result.scope.resolved_vendor()
    family = fetch_result.scope.resolved_family()
    device_patches = tuple(
        load_device_patch(execution_context, device_name, vendor=vendor, family=family)
        for device_name in fetch_result.scope.resolved_device_names()
    )
    patch_manifest = PatchManifest(
        manifest_kind="patch-manifest-v1",
        bootstrap_family=family,
        targets=source_manifest.targets,
        applied_patches=tuple(
            PatchRecord(
                patch_id=patch.patch_id,
                description=(
                    f"Bootstrap overlay patch for {patch.device}"
                    + (
                        f" using family catalog {patch.family_patch_id}."
                        if patch.family_patch_id is not None
                        else "."
                    )
                ),
            )
            for patch in device_patches
        ),
    )
    return StageResult(
        stage="patch",
        scope=fetch_result.scope,
        status="completed",
        payload=PatchBundle(
            source_manifest=source_manifest,
            patch_manifest=patch_manifest,
            device_patches=tuple(patch.to_dict() for patch in device_patches),
        ),
    )
