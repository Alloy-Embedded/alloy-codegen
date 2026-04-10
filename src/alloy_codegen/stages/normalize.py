"""Normalize stage bootstrap implementation."""

from __future__ import annotations

import re

from alloy_codegen.bootstrap import IR_SCHEMA_VERSION
from alloy_codegen.context import ExecutionContext
from alloy_codegen.ir.model import (
    CanonicalDeviceIR,
    DeviceIdentity,
    DmaRequestDefinition,
    InterruptDefinition,
    MemoryRegion,
    PackageDefinition,
    PeripheralInstance,
    PinDefinition,
    PinSignal,
    Provenance,
)
from alloy_codegen.patches import (
    DevicePatch,
    DmaRequestPatch,
    MemoryPatch,
    PeripheralPatch,
    PinPatch,
    PinSignalPatch,
    load_device_patch,
)
from alloy_codegen.reporting import NormalizationBundle
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.cmsis_svd import parse_raw_device_document, resolve_svd_path
from alloy_codegen.sources.raw import RawDeviceDocument
from alloy_codegen.stages.common import StageResult
from alloy_codegen.stages.patch import run as run_patch

INSTANCE_PATTERN = re.compile(r"^(?P<ip>[A-Z]+?)(?P<instance>\d+)$")


def _infer_ip_metadata(peripheral_name: str) -> tuple[str, int]:
    if peripheral_name.startswith("GPIO") and len(peripheral_name) == 5:
        return ("gpio", ord(peripheral_name[-1]) - ord("A"))
    match = INSTANCE_PATTERN.match(peripheral_name)
    if match is not None:
        return (match.group("ip").lower(), int(match.group("instance")))
    return (peripheral_name.lower(), 0)


def _memory_to_ir(memory: MemoryPatch, provenance: Provenance) -> MemoryRegion:
    return MemoryRegion(
        name=memory.name,
        kind=memory.kind,
        base_address=memory.base_address,
        size_bytes=memory.size_bytes,
        access=memory.access,
        provenance=provenance,
    )


def _pin_signal_to_ir(signal: PinSignalPatch, provenance: Provenance) -> PinSignal:
    return PinSignal(
        function=signal.function,
        peripheral=signal.peripheral,
        signal=signal.signal,
        af_number=signal.af_number,
        provenance=provenance,
    )


def _pin_to_ir(pin: PinPatch, provenance: Provenance) -> PinDefinition:
    return PinDefinition(
        name=pin.name,
        port=pin.port,
        number=pin.number,
        signals=tuple(_pin_signal_to_ir(signal, provenance) for signal in pin.signals),
        provenance=provenance,
    )


def _peripheral_patch_map(
    patch: DevicePatch,
) -> dict[str, PeripheralPatch]:
    return {peripheral.name: peripheral for peripheral in patch.peripherals}


def _peripheral_to_ir(
    *,
    peripheral_name: str,
    base_address: int,
    patch_metadata: PeripheralPatch | None,
    provenance: Provenance,
) -> PeripheralInstance:
    ip_name, instance = _infer_ip_metadata(peripheral_name)
    return PeripheralInstance(
        name=peripheral_name,
        ip_name=ip_name,
        instance=instance,
        base_address=base_address,
        rcc_enable_signal=None if patch_metadata is None else patch_metadata.rcc_enable_signal,
        rcc_reset_signal=None if patch_metadata is None else patch_metadata.rcc_reset_signal,
        provenance=provenance,
    )


def _dma_request_to_ir(
    request: DmaRequestPatch,
    provenance: Provenance,
) -> DmaRequestDefinition:
    return DmaRequestDefinition(
        controller=request.controller,
        request_line=request.request_line,
        peripheral=request.peripheral,
        signal=request.signal,
        provenance=provenance,
    )


def build_canonical_ir(raw: RawDeviceDocument, patch: DevicePatch) -> CanonicalDeviceIR:
    """Build canonical IR from a raw SVD document plus patch metadata."""
    patch_ids = (
        (patch.family_patch_id, patch.patch_id)
        if patch.family_patch_id is not None
        else (patch.patch_id,)
    )
    provenance = Provenance(
        source_id="cmsis-svd-data",
        source_path=patch.svd_file,
        patch_ids=patch_ids,
    )
    peripheral_patches = _peripheral_patch_map(patch)
    return CanonicalDeviceIR(
        schema_version=IR_SCHEMA_VERSION,
        identity=DeviceIdentity(
            vendor="st",
            family="stm32g0",
            device=patch.device,
            package=patch.package,
            core=patch.core,
            summary=patch.summary,
        ),
        memories=tuple(_memory_to_ir(memory, provenance) for memory in patch.memories),
        packages=(
            PackageDefinition(
                name=patch.package,
                pin_count=patch.pin_count,
                provenance=provenance,
            ),
        ),
        pins=tuple(_pin_to_ir(pin, provenance) for pin in patch.pins),
        peripherals=tuple(
            _peripheral_to_ir(
                peripheral_name=peripheral.name,
                base_address=peripheral.base_address,
                patch_metadata=peripheral_patches.get(peripheral.name),
                provenance=provenance,
            )
            for peripheral in raw.peripherals
        ),
        interrupts=tuple(
            InterruptDefinition(
                name=interrupt.name,
                line=interrupt.line,
                peripheral=interrupt.peripheral,
                provenance=provenance,
            )
            for interrupt in raw.interrupts
        ),
        dma_requests=tuple(
            _dma_request_to_ir(request, provenance) for request in patch.dma_requests
        ),
        provenance=provenance,
    )


def run(scope: PipelineScope, context: ExecutionContext | None = None) -> StageResult:
    """Run the bootstrap normalize stage."""
    execution_context = context or ExecutionContext.default()
    patch_result = run_patch(scope, execution_context)
    devices: list[CanonicalDeviceIR] = []
    for device_name in patch_result.scope.resolved_device_names():
        patch = load_device_patch(execution_context, device_name)
        raw = parse_raw_device_document(resolve_svd_path(execution_context, device_name))
        devices.append(build_canonical_ir(raw, patch))
    return StageResult(
        stage="normalize",
        scope=patch_result.scope,
        status="completed",
        payload=NormalizationBundle(
            source_manifest=patch_result.payload.source_manifest,
            patch_manifest=patch_result.payload.patch_manifest,
            devices=tuple(devices),
        ),
    )
