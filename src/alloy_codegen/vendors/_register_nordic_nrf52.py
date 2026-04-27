"""Vendor adapter registration for Nordic nRF52 (via Zephyr DTS).

Added by ``ingest-zephyr-dts-as-source``.  This is the first
admission through the cross-vendor Zephyr-DTS adapter.  Renesas
/ TI / Infineon / Ambiq follow the same shape: a per-vendor
``_register_<vendor>_<family>.py`` module + an entry in
``alloy_codegen.sources.zephyr_dts.COMPATIBLE_MAPS``.
"""

from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.zephyr_dts import fetch_records as fetch_zephyr_dts_records

from .registry import VendorAdapter, register_vendor_adapter


def _fetch(
    execution_context: ExecutionContext, scope: PipelineScope
) -> tuple[dict[str, str], ...]:
    return fetch_zephyr_dts_records(execution_context, scope)


def _normalize(
    *,
    execution_context: ExecutionContext,
    device_name: str,
    vendor: str,
    family: str,
) -> CanonicalDeviceIR:
    # Lazy-imported to avoid the registry pulling in the full
    # normalize stage at module import time.
    from alloy_codegen.stages.normalize import _build_zephyr_dts_device_ir

    return _build_zephyr_dts_device_ir(
        execution_context=execution_context,
        device_name=device_name,
        vendor=vendor,
        family=family,
    )


@register_vendor_adapter("nordic", "nrf52")
def _build() -> VendorAdapter:
    return VendorAdapter(
        vendor="nordic", family="nrf52", fetch=_fetch, normalize=_normalize
    )
