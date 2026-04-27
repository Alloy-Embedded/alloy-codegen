"""Vendor adapter registration for ST STM32G0."""

from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.cmsis_svd import fetch_records as fetch_svd_records
from alloy_codegen.sources.stm32_open_pin_data import fetch_records as fetch_pin_records

from .registry import VendorAdapter, register_vendor_adapter


def _fetch(
    execution_context: ExecutionContext, scope: PipelineScope
) -> tuple[dict[str, str], ...]:
    return (
        *fetch_svd_records(execution_context, scope),
        *fetch_pin_records(execution_context, scope),
    )


def _normalize(
    *,
    execution_context: ExecutionContext,
    device_name: str,
    vendor: str,
    family: str,
) -> CanonicalDeviceIR:
    # Late import: stages.normalize imports the registry, so referring
    # back to its private builder at registration time would cycle.
    from alloy_codegen.stages.normalize import _build_st_device_ir

    return _build_st_device_ir(
        execution_context=execution_context,
        device_name=device_name,
        vendor=vendor,
        family=family,
    )


@register_vendor_adapter("st", "stm32g0")
def _build() -> VendorAdapter:
    return VendorAdapter(vendor="st", family="stm32g0", fetch=_fetch, normalize=_normalize)
