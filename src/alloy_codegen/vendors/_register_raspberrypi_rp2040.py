"""Vendor adapter registration for Raspberry Pi RP2040."""

from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.pico_sdk import fetch_records as fetch_pico_sdk_records

from .registry import VendorAdapter, register_vendor_adapter


def _fetch(execution_context: ExecutionContext, scope: PipelineScope) -> tuple[dict[str, str], ...]:
    return fetch_pico_sdk_records(execution_context, scope)


def _normalize(
    *,
    execution_context: ExecutionContext,
    device_name: str,
    vendor: str,
    family: str,
) -> CanonicalDeviceIR:
    from alloy_codegen.stages.normalize import _build_rp2040_device_ir

    return _build_rp2040_device_ir(
        execution_context=execution_context,
        device_name=device_name,
        vendor=vendor,
        family=family,
    )


@register_vendor_adapter("raspberrypi", "rp2040")
def _build() -> VendorAdapter:
    return VendorAdapter(vendor="raspberrypi", family="rp2040", fetch=_fetch, normalize=_normalize)
