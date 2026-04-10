from __future__ import annotations

import json

from alloy_codegen.context import ExecutionContext
from alloy_codegen.scope import PipelineScope
from alloy_codegen.stages.emit import run as run_emit


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
