"""Vendor adapter registration for Microchip AVR-DA."""

from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.microchip_dfp import fetch_records as fetch_microchip_dfp_records

from .registry import VendorAdapter, register_vendor_adapter


def _fetch(execution_context: ExecutionContext, scope: PipelineScope) -> tuple[dict[str, str], ...]:
    return fetch_microchip_dfp_records(execution_context, scope)


def _normalize(
    *,
    execution_context: ExecutionContext,
    device_name: str,
    vendor: str,
    family: str,
) -> CanonicalDeviceIR:
    from alloy_codegen.stages.normalize import _build_avr_da_device_ir

    return _build_avr_da_device_ir(
        execution_context=execution_context,
        device_name=device_name,
        vendor=vendor,
        family=family,
    )


@register_vendor_adapter("microchip", "avr-da")
def _build() -> VendorAdapter:
    return VendorAdapter(vendor="microchip", family="avr-da", fetch=_fetch, normalize=_normalize)
