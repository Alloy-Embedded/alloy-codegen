from __future__ import annotations

import json
from dataclasses import replace

from alloy_codegen.context import ExecutionContext
from alloy_codegen.emission import build_device_coverage
from alloy_codegen.ir.model import PeripheralInstance
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit
from alloy_codegen.stages.normalize import run as run_normalize


def test_foundational_families_emit_publishability_reports(
    execution_context: ExecutionContext,
    microchip_execution_context: ExecutionContext,
    nxp_execution_context: ExecutionContext,
) -> None:
    family_contexts: tuple[tuple[PipelineScope, ExecutionContext], ...] = (
        (PipelineScope(vendor="st", family="stm32g0"), execution_context),
        (PipelineScope(vendor="st", family="stm32f4"), execution_context),
        (PipelineScope(vendor="microchip", family="same70"), microchip_execution_context),
        (PipelineScope(vendor="nxp", family="imxrt1060"), nxp_execution_context),
    )

    for scope, context in family_contexts:
        result = run_emit(scope, context)
        family_dir = f"{scope.resolved_vendor()}/{scope.resolved_family()}"
        artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}

        summary_artifact = artifacts[f"{family_dir}/reports/validation-summary.json"]
        coverage_artifact = artifacts[f"{family_dir}/reports/coverage.json"]

        summary_payload = json.loads(summary_artifact.content)
        coverage_payload = json.loads(coverage_artifact.content)

        assert summary_payload["vendor"] == scope.resolved_vendor()
        assert summary_payload["family"] == scope.resolved_family()
        assert summary_payload["device_count"] >= 1
        assert summary_payload["devices"]
        assert all("publishable" in device for device in summary_payload["devices"])
        assert coverage_payload["vendor"] == scope.resolved_vendor()
        assert coverage_payload["family"] == scope.resolved_family()
        assert coverage_payload["devices"]
        assert all("domains" in device for device in coverage_payload["devices"])
        assert all("counts" in device for device in coverage_payload["devices"])


def test_stm32g0_publishability_report_shows_all_devices_publishable(
    execution_context: ExecutionContext,
) -> None:
    result = run_emit(PipelineScope(vendor="st", family="stm32g0"), execution_context)
    artifacts = {artifact.path: artifact for artifact in result.payload.artifacts}
    coverage_payload = json.loads(artifacts["st/stm32g0/reports/coverage.json"].content)
    device_map = {device["device"]: device for device in coverage_payload["devices"]}

    assert coverage_payload["all_devices_publishable"] is True
    assert device_map["stm32g0b1re"]["publishable"] is True
    assert device_map["stm32g0b1re"]["domains"]["dma"] is True
    assert device_map["stm32g0b1re"]["counts"]["dma_controllers"] == 1
    assert device_map["stm32g0b1re"]["counts"]["dma_routes"] == 2


def test_dma_coverage_uses_normalized_dma_descriptors_not_name_heuristics(
    nxp_execution_context: ExecutionContext,
) -> None:
    result = run_normalize(PipelineScope(vendor="nxp", family="imxrt1060"), nxp_execution_context)
    device = result.payload.devices[0]
    provenance = device.peripherals[0].provenance
    device_with_dma_named_peripherals = replace(
        device,
        peripherals=(
            *device.peripherals,
            PeripheralInstance(
                name="DMA0",
                ip_name="dma",
                ip_version=None,
                instance=0,
                base_address=0x400E8000,
                rcc_enable_signal=None,
                rcc_reset_signal=None,
                provenance=provenance,
            ),
            PeripheralInstance(
                name="DMAMUX1",
                ip_name="dmamux",
                ip_version=None,
                instance=1,
                base_address=0x400EC000,
                rcc_enable_signal=None,
                rcc_reset_signal=None,
                provenance=provenance,
            ),
        ),
    )

    coverage = build_device_coverage(device_with_dma_named_peripherals)

    assert coverage["domains"]["dma"] is True
    assert coverage["publishable"] is True
