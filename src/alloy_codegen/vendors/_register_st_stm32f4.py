"""Vendor adapter registration for ST STM32F4."""

from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.cmsis_svd import fetch_records as fetch_svd_records
from alloy_codegen.sources.modm_devices import (
    apply_modm_enrichment,
)
from alloy_codegen.sources.modm_devices import (
    fetch_records as fetch_modm_records,
)
from alloy_codegen.sources.modm_devices import (
    load_enrichment as load_modm_enrichment,
)
from alloy_codegen.sources.stm32_open_pin_data import fetch_records as fetch_pin_records

from .registry import VendorAdapter, register_vendor_adapter


def _fetch(execution_context: ExecutionContext, scope: PipelineScope) -> tuple[dict[str, str], ...]:
    return (
        *fetch_svd_records(execution_context, scope),
        *fetch_pin_records(execution_context, scope),
        *fetch_modm_records(execution_context, scope),
    )


def _normalize(
    *,
    execution_context: ExecutionContext,
    device_name: str,
    vendor: str,
    family: str,
) -> CanonicalDeviceIR:
    from alloy_codegen.stages.normalize import _build_st_device_ir

    device = _build_st_device_ir(
        execution_context=execution_context,
        device_name=device_name,
        vendor=vendor,
        family=family,
    )
    enrichment = load_modm_enrichment(
        execution_context, vendor=vendor, family=family, device=device_name
    )
    return apply_modm_enrichment(device, enrichment)  # type: ignore[return-value]


@register_vendor_adapter("st", "stm32f4")
def _build() -> VendorAdapter:
    return VendorAdapter(vendor="st", family="stm32f4", fetch=_fetch, normalize=_normalize)
