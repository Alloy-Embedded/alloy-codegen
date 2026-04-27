"""Vendor adapter registration for Espressif (ESP32 / ESP32-C3 / ESP32-S3)."""

from __future__ import annotations

from alloy_codegen.context import ExecutionContext
from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.esp_idf import fetch_records as fetch_espressif_records

from .registry import VendorAdapter, register_vendor_adapter


def _fetch(
    execution_context: ExecutionContext, scope: PipelineScope
) -> tuple[dict[str, str], ...]:
    return fetch_espressif_records(execution_context, scope)


def _normalize(
    *,
    execution_context: ExecutionContext,
    device_name: str,
    vendor: str,
    family: str,
) -> CanonicalDeviceIR:
    from alloy_codegen.stages.normalize import _build_esp32_device_ir

    return _build_esp32_device_ir(
        execution_context=execution_context,
        device_name=device_name,
        vendor=vendor,
        family=family,
    )


def _make(family: str) -> VendorAdapter:
    return VendorAdapter(vendor="espressif", family=family, fetch=_fetch, normalize=_normalize)


@register_vendor_adapter("espressif", "esp32")
def _build_esp32() -> VendorAdapter:
    return _make("esp32")


@register_vendor_adapter("espressif", "esp32c3")
def _build_esp32c3() -> VendorAdapter:
    return _make("esp32c3")


@register_vendor_adapter("espressif", "esp32s3")
def _build_esp32s3() -> VendorAdapter:
    return _make("esp32s3")
