"""Vendor adapter registration for Microchip SAM E70."""

from __future__ import annotations

import dataclasses

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
    from alloy_codegen.stages.normalize import (
        _build_microchip_device_ir,
        _build_same70_pwm_peripherals,
    )

    same70_ir = _build_microchip_device_ir(
        execution_context=execution_context,
        device_name=device_name,
        vendor=vendor,
        family=family,
    )
    same70_pwm = _build_same70_pwm_peripherals(peripherals=same70_ir.peripherals)
    if same70_pwm:
        same70_ir = dataclasses.replace(same70_ir, same70_pwm_peripherals=same70_pwm)
    return same70_ir


@register_vendor_adapter("microchip", "same70")
def _build() -> VendorAdapter:
    return VendorAdapter(vendor="microchip", family="same70", fetch=_fetch, normalize=_normalize)
