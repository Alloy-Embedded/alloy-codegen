"""Vendor adapter registration for NXP iMXRT1060."""

from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.nxp_mcux import fetch_records as fetch_nxp_mcux_records

from .registry import VendorAdapter, register_vendor_adapter


def _fetch(execution_context: ExecutionContext, scope: PipelineScope) -> tuple[dict[str, str], ...]:
    return fetch_nxp_mcux_records(execution_context, scope)


def _normalize(
    *,
    execution_context: ExecutionContext,
    device_name: str,
    vendor: str,
    family: str,
) -> CanonicalDeviceIR:
    from alloy_codegen.stages.normalize import _build_nxp_device_ir

    return _build_nxp_device_ir(
        execution_context=execution_context,
        device_name=device_name,
        vendor=vendor,
        family=family,
    )


@register_vendor_adapter("nxp", "imxrt1060")
def _build() -> VendorAdapter:
    return VendorAdapter(vendor="nxp", family="imxrt1060", fetch=_fetch, normalize=_normalize)
