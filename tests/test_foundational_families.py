from __future__ import annotations

import json
import shutil
from collections.abc import Iterable

from alloy_codegen.bootstrap import registered_device_names
from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit
from alloy_codegen.stages.publish import run as run_publish


def _family_contexts(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> tuple[tuple[PipelineScope, ExecutionContext], ...]:
    return (
        (PipelineScope(vendor="st", family="stm32g0"), execution_context),
        (PipelineScope(vendor="st", family="stm32f4"), execution_context),
        (PipelineScope(vendor="microchip", family="same70"), microchip_execution_context),
        (PipelineScope(vendor="nxp", family="imxrt1060"), nxp_execution_context),
    )


def _common_family_artifact_paths(family_dir: str) -> tuple[str, ...]:
    return (
        f"{family_dir}/artifact-manifest.json",
        f"{family_dir}/metadata/family-index.json",
        f"{family_dir}/metadata/family-connectivity.json",
        f"{family_dir}/metadata/ip-blocks.json",
        f"{family_dir}/metadata/capabilities.json",
        f"{family_dir}/metadata/packages.json",
        f"{family_dir}/metadata/connectors.json",
        f"{family_dir}/metadata/system-descriptors.json",
        f"{family_dir}/reports/validation-report.json",
        f"{family_dir}/reports/validation-summary.json",
        f"{family_dir}/reports/coverage.json",
        f"{family_dir}/generated/connector_tables.hpp",
        f"{family_dir}/generated/interrupt_map.hpp",
        f"{family_dir}/generated/memory_map.hpp",
        f"{family_dir}/generated/package_map.hpp",
        f"{family_dir}/generated/clock_tree_lite.hpp",
        f"{family_dir}/generated/dma_map.hpp",
        f"{family_dir}/generated/rcc_map.hpp",
    )


def _device_artifact_paths(
    family_dir: str,
    device_names: Iterable[str],
) -> tuple[str, ...]:
    paths: list[str] = []
    for device_name in device_names:
        paths.extend(
            (
                f"{family_dir}/metadata/devices/{device_name}.json",
                f"{family_dir}/generated/devices/{device_name}/device_descriptor.hpp",
                f"{family_dir}/generated/devices/{device_name}/pins.hpp",
                f"{family_dir}/generated/devices/{device_name}/peripheral_instances.hpp",
                f"{family_dir}/generated/devices/{device_name}/capability_overlays.hpp",
                f"{family_dir}/generated/devices/{device_name}/register_map.hpp",
                f"{family_dir}/generated/devices/{device_name}/startup_descriptors.hpp",
                f"{family_dir}/generated/devices/{device_name}/startup_vectors.cpp",
            )
        )
    return tuple(paths)


def test_foundational_families_emit_same_descriptor_contract(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> None:
    for scope, context in _family_contexts(
        execution_context,
        microchip_execution_context,
        nxp_execution_context,
    ):
        result = run_emit(scope, context)
        family_dir = f"{scope.resolved_vendor()}/{scope.resolved_family()}"
        device_names = registered_device_names(scope.resolved_vendor(), scope.resolved_family())
        artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}

        assert result.stage == "emit"
        assert result.status == "completed"
        for path in _common_family_artifact_paths(family_dir):
            assert path in artifacts, f"missing common family artifact: {path}"
        for path in _device_artifact_paths(family_dir, device_names):
            assert path in artifacts, f"missing device artifact: {path}"

        validation_summary = json.loads(
            artifacts[f"{family_dir}/reports/validation-summary.json"].content
        )
        coverage = json.loads(artifacts[f"{family_dir}/reports/coverage.json"].content)
        assert validation_summary["draft_system_descriptor_domains"] == []
        assert coverage["vendor"] == scope.resolved_vendor()
        assert coverage["family"] == scope.resolved_family()
        assert len(coverage["devices"]) == len(device_names)
        assert all("publishable" in device for device in coverage["devices"])
        assert all("domains" in device for device in coverage["devices"])
        assert all("counts" in device for device in coverage["devices"])
        assert coverage["all_devices_publishable"] == all(
            bool(device["publishable"]) for device in coverage["devices"]
        )


def test_foundational_families_publish_with_same_generic_workflow(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> None:
    for scope, context in _family_contexts(
        execution_context,
        microchip_execution_context,
        nxp_execution_context,
    ):
        result = run_publish(scope, context)
        family_dir = f"{scope.resolved_vendor()}/{scope.resolved_family()}"
        device_names = registered_device_names(scope.resolved_vendor(), scope.resolved_family())

        assert result.stage == "publish"
        assert result.status == "completed"
        assert result.payload.publication_mode == "published"
        assert result.payload.consumer_verification is not None
        assert result.payload.consumer_verification.succeeded is True
        assert result.payload.draft_system_descriptor_domains == ()

        publication_root = context.publication_root
        assert (publication_root / family_dir / "artifact-manifest.json").exists()
        assert (publication_root / family_dir / "reports" / "validation-report.json").exists()
        assert (publication_root / family_dir / "reports" / "validation-summary.json").exists()
        assert (publication_root / family_dir / "reports" / "coverage.json").exists()
        for device_name in device_names:
            assert (
                publication_root
                / family_dir
                / "generated"
                / "devices"
                / device_name
                / "device_descriptor.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "devices"
                / device_name
                / "pins.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "devices"
                / device_name
                / "peripheral_instances.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "devices"
                / device_name
                / "capability_overlays.hpp"
            ).exists()
            assert (
                publication_root
                / family_dir
                / "generated"
                / "devices"
                / device_name
                / "register_map.hpp"
            ).exists()


def test_foundational_families_remain_complete_across_repeat_publish_cycles(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> None:
    for scope, context in _family_contexts(
        execution_context,
        microchip_execution_context,
        nxp_execution_context,
    ):
        result_a = run_publish(scope, context)
        family_dir = f"{scope.resolved_vendor()}/{scope.resolved_family()}"
        coverage_a = json.loads(
            (context.publication_root / family_dir / "reports" / "coverage.json").read_text(
                encoding="utf-8"
            )
        )
        summary_a = json.loads(
            (
                context.publication_root / family_dir / "reports" / "validation-summary.json"
            ).read_text(encoding="utf-8")
        )

        shutil.rmtree(context.artifact_root)
        shutil.rmtree(context.publication_root)

        result_b = run_publish(scope, context)
        coverage_b = json.loads(
            (context.publication_root / family_dir / "reports" / "coverage.json").read_text(
                encoding="utf-8"
            )
        )
        summary_b = json.loads(
            (
                context.publication_root / family_dir / "reports" / "validation-summary.json"
            ).read_text(encoding="utf-8")
        )

        assert result_a.status == "completed"
        assert result_b.status == "completed"
        assert (
            result_a.payload.target_artifact_revision
            == result_b.payload.target_artifact_revision
        )
        assert (
            result_a.payload.publication_record.content_sha256
            == result_b.payload.publication_record.content_sha256
        )
        assert coverage_a == coverage_b
        assert summary_a == summary_b
        assert coverage_b["all_devices_publishable"] is True
        assert all(bool(device["publishable"]) for device in coverage_b["devices"])
        assert summary_b["draft_system_descriptor_domains"] == []
