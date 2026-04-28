# ruff: noqa: E501

"""Normalize stage — YAML-only consumer.

After ``consume-alloy-devices-yml-as-canonical-input`` Phase 3,
every admitted device's ``CanonicalDeviceIR`` is read directly
from the ``alloy-devices-yml`` submodule mounted at
``data/devices/``, with no post-load enrichment.  The patch
overlay system that used to layer in tier 2/3/4 fields,
multicore facts, USB controllers, etc., is gone — those fields
are now baked into the canonical YAML itself, produced by the
``alloy-data-extractor`` ETL pipeline.
"""

from __future__ import annotations

from alloy_codegen.connector_model import ensure_connector_descriptors
from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.manifests import PatchManifest
from alloy_codegen.reporting import NormalizationBundle
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.common import StageResult
from alloy_codegen.stages.fetch import run as run_fetch


def run(scope: PipelineScope, context: ExecutionContext | None = None) -> StageResult:
    """Run the normalize stage — pure YAML consumer.

    For every device in ``scope`` the device's canonical YAML is
    located in the ``alloy-devices-yml`` submodule and parsed
    into a :class:`CanonicalDeviceIR`.  Missing YAML raises an
    actionable :class:`StageExecutionError`.
    """
    execution_context = context or ExecutionContext.default()
    fetch_result = run_fetch(scope, execution_context)
    vendor = fetch_result.scope.resolved_vendor()
    family = fetch_result.scope.resolved_family()

    from alloy_codegen.sources import alloy_devices_yml as _adyml

    devices: list[CanonicalDeviceIR] = []
    for device_name in fetch_result.scope.resolved_device_names():
        if not _adyml.is_available(vendor=vendor, family=family, device=device_name):
            yaml_path = _adyml.device_yaml_path(
                vendor=vendor, family=family, device=device_name
            )
            raise StageExecutionError(
                f"canonical device YAML missing at {yaml_path}.  "
                "Admit the device by committing its YAML to the "
                "alloy-devices-yml data repo (this codegen repo is "
                "consumer-only after consume-alloy-devices-yml-as-canonical-input)."
            )
        devices.append(
            _adyml.load_canonical_device(vendor=vendor, family=family, device=device_name)
        )

    # The patch manifest is now a stable no-op marker — every IR
    # field that used to come through patches is baked into the
    # canonical YAML.  Kept on the bundle for backwards compat with
    # downstream stages that snapshot it.
    empty_patch_manifest = PatchManifest(
        manifest_kind="patch-manifest-v1",
        bootstrap_family=fetch_result.scope.resolved_family(),
        targets=fetch_result.scope.resolved_device_names(),
        applied_patches=(),
    )
    return StageResult(
        stage="normalize",
        scope=fetch_result.scope,
        status="completed",
        payload=NormalizationBundle(
            source_manifest=fetch_result.payload.source_manifest,
            patch_manifest=empty_patch_manifest,
            devices=tuple(ensure_connector_descriptors(device) for device in devices),
        ),
    )
