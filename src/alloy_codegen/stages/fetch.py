"""Fetch stage bootstrap implementation."""

from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.manifests import SourceManifest, SourceRecord
from alloy_codegen.reporting import FetchBundle
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.cmsis_svd import fetch_records as fetch_svd_records
from alloy_codegen.sources.esp_idf import fetch_records as fetch_espressif_records
from alloy_codegen.sources.microchip_dfp import fetch_records as fetch_microchip_dfp_records
from alloy_codegen.sources.nxp_mcux import fetch_records as fetch_nxp_mcux_records
from alloy_codegen.sources.pico_sdk import fetch_records as fetch_pico_sdk_records
from alloy_codegen.sources.stm32_open_pin_data import fetch_records as fetch_pin_records
from alloy_codegen.stages.common import StageResult


def _fetch_records_for_scope(
    execution_context: ExecutionContext,
    validated_scope: PipelineScope,
) -> tuple[dict[str, str], ...]:
    vendor = validated_scope.resolved_vendor()
    family = validated_scope.resolved_family()
    if vendor == "espressif":
        return fetch_espressif_records(execution_context, validated_scope)
    if vendor == "st":
        return (
            *fetch_svd_records(execution_context, validated_scope),
            *fetch_pin_records(execution_context, validated_scope),
        )
    if vendor == "microchip" and family in {"same70", "avr-da"}:
        return fetch_microchip_dfp_records(execution_context, validated_scope)
    if vendor == "nxp" and family == "imxrt1060":
        return fetch_nxp_mcux_records(execution_context, validated_scope)
    if vendor == "raspberrypi" and family == "rp2040":
        return fetch_pico_sdk_records(execution_context, validated_scope)
    return ()


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
