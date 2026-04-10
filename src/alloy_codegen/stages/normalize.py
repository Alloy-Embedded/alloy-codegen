"""Normalize stage bootstrap implementation."""

from __future__ import annotations

import re

from alloy_codegen.bootstrap import BOOTSTRAP_FAMILY, BOOTSTRAP_VENDOR, IR_SCHEMA_VERSION
from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
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
from alloy_codegen.sources.raw import RawDeviceDocument, RawPinDataDocument
from alloy_codegen.sources.stm32_open_pin_data import (
    parse_ip_version_table,
    parse_raw_pin_data_document,
    resolve_gpio_modes_path,
    resolve_mcu_path,
)
from alloy_codegen.stages.common import StageResult
from alloy_codegen.stages.patch import run as run_patch

INSTANCE_PATTERN = re.compile(r"^(?P<ip>[A-Z]+?)(?P<instance>\d+)$")
RAW_PERIPHERAL_ALIASES = {
    "ADC": "ADC1",
    "DMA": "DMA1",
    "DMAMUX": "DMAMUX1",
    "LPUART": "LPUART1",
}


def _canonical_peripheral_name(peripheral_name: str) -> str:
    return RAW_PERIPHERAL_ALIASES.get(peripheral_name, peripheral_name)


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
    ip_version: str | None,
    provenance: Provenance,
) -> PeripheralInstance:
    ip_name, instance = _infer_ip_metadata(peripheral_name)
    return PeripheralInstance(
        name=peripheral_name,
        ip_name=ip_name,
        ip_version=ip_version,
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


def _default_pin_signal(*, port: str, number: int, provenance: Provenance) -> PinSignal:
    return PinSignal(
        function="gpio",
        peripheral=f"GPIO{port}",
        signal=f"IN{number}",
        af_number=None,
        provenance=provenance,
    )


def _alternate_signal_to_ir(
    *,
    signal_name: str,
    af_number: int,
    discovered_peripherals: set[str],
    provenance: Provenance,
) -> PinSignal | None:
    if "_" not in signal_name:
        return None
    peripheral_name, signal = signal_name.split("_", maxsplit=1)
    if peripheral_name not in discovered_peripherals:
        return None
    return PinSignal(
        function=signal_name.lower(),
        peripheral=peripheral_name,
        signal=signal,
        af_number=af_number,
        provenance=provenance,
    )


def _build_pins_from_source(
    *,
    pin_data: RawPinDataDocument,
    discovered_peripherals: set[str],
    allowed_signal_peripherals: set[str],
    provenance: Provenance,
) -> tuple[PinDefinition, ...]:
    pins: list[PinDefinition] = []
    for raw_pin in pin_data.pins:
        signals: list[PinSignal] = [
            _default_pin_signal(port=raw_pin.port, number=raw_pin.number, provenance=provenance)
        ]
        seen_keys = {
            (signals[0].function, signals[0].peripheral, signals[0].signal, signals[0].af_number)
        }
        for raw_signal in raw_pin.signals:
            signal = _alternate_signal_to_ir(
                signal_name=raw_signal.signal_name,
                af_number=raw_signal.af_number,
                discovered_peripherals=discovered_peripherals,
                provenance=provenance,
            )
            if signal is None:
                continue
            if signal.peripheral not in allowed_signal_peripherals:
                continue
            key = (signal.function, signal.peripheral, signal.signal, signal.af_number)
            if key in seen_keys:
                continue
            seen_keys.add(key)
            signals.append(signal)

        pins.append(
            PinDefinition(
                name=raw_pin.name,
                port=raw_pin.port,
                number=raw_pin.number,
                signals=tuple(signals),
                provenance=provenance,
            )
        )
    return tuple(pins)


def build_canonical_ir(
    raw: RawDeviceDocument,
    patch: DevicePatch,
    pin_data: RawPinDataDocument,
    ip_version_table: dict[str, str] | None = None,
    *,
    vendor: str = BOOTSTRAP_VENDOR,
    family: str = BOOTSTRAP_FAMILY,
) -> CanonicalDeviceIR:
    """Build canonical IR from raw SVD plus STM32 open pin data and patch metadata."""
    patch_ids = (
        (patch.family_patch_id, patch.patch_id)
        if patch.family_patch_id is not None
        else (patch.patch_id,)
    )
    if pin_data.package_name != patch.package:
        raise StageExecutionError(
            f"Pin data package mismatch for {patch.device}: "
            f"pin-data={pin_data.package_name}, patch={patch.package}."
        )
    if pin_data.package_pin_count is not None and pin_data.package_pin_count != patch.pin_count:
        raise StageExecutionError(
            f"Pin data pin-count mismatch for {patch.device}: "
            f"pin-data={pin_data.package_pin_count}, patch={patch.pin_count}."
        )

    svd_provenance = Provenance(
        source_id="cmsis-svd-data",
        source_path=patch.svd_file,
        patch_ids=patch_ids,
    )
    pin_provenance = Provenance(
        source_id="stm32-open-pin-data",
        source_path=patch.pin_data_file,
        patch_ids=patch_ids,
    )
    patch_provenance = Provenance(
        source_id="bootstrap-patch",
        source_path=f"patches/{vendor}/{family}/devices/{patch.device}.json",
        patch_ids=patch_ids,
    )
    peripheral_patches = _peripheral_patch_map(patch)
    discovered_peripherals = {
        _canonical_peripheral_name(peripheral.name) for peripheral in raw.peripherals
    }
    allowed_signal_peripherals = {
        peripheral.name
        for peripheral in patch.peripherals
        if peripheral.rcc_enable_signal is not None
    }
    return CanonicalDeviceIR(
        schema_version=IR_SCHEMA_VERSION,
        identity=DeviceIdentity(
            vendor=vendor,
            family=family,
            device=patch.device,
            package=patch.package,
            core=patch.core,
            summary=patch.summary,
        ),
        memories=tuple(_memory_to_ir(memory, patch_provenance) for memory in patch.memories),
        packages=(
            PackageDefinition(
                name=patch.package,
                pin_count=patch.pin_count,
                provenance=pin_provenance,
            ),
        ),
        pins=_build_pins_from_source(
            pin_data=pin_data,
            discovered_peripherals=discovered_peripherals,
            allowed_signal_peripherals=allowed_signal_peripherals,
            provenance=pin_provenance,
        ),
        peripherals=tuple(
            _peripheral_to_ir(
                peripheral_name=_canonical_peripheral_name(peripheral.name),
                base_address=peripheral.base_address,
                patch_metadata=peripheral_patches.get(_canonical_peripheral_name(peripheral.name)),
                ip_version=None
                if ip_version_table is None
                else ip_version_table.get(_canonical_peripheral_name(peripheral.name)),
                provenance=svd_provenance,
            )
            for peripheral in raw.peripherals
        ),
        interrupts=tuple(
            InterruptDefinition(
                name=interrupt.name,
                line=interrupt.line,
                peripheral=(
                    None
                    if interrupt.peripheral is None
                    else _canonical_peripheral_name(interrupt.peripheral)
                ),
                provenance=svd_provenance,
            )
            for interrupt in raw.interrupts
        ),
        dma_requests=tuple(
            _dma_request_to_ir(request, patch_provenance) for request in patch.dma_requests
        ),
        provenance=pin_provenance,
    )


def run(scope: PipelineScope, context: ExecutionContext | None = None) -> StageResult:
    """Run the bootstrap normalize stage."""
    execution_context = context or ExecutionContext.default()
    patch_result = run_patch(scope, execution_context)
    devices: list[CanonicalDeviceIR] = []
    vendor = patch_result.scope.resolved_vendor()
    family = patch_result.scope.resolved_family()
    for device_name in patch_result.scope.resolved_device_names():
        patch = load_device_patch(execution_context, device_name, vendor=vendor, family=family)
        mcu_path = resolve_mcu_path(execution_context, device_name, vendor=vendor, family=family)
        raw = parse_raw_device_document(
            resolve_svd_path(execution_context, device_name, vendor=vendor, family=family)
        )
        pin_data = parse_raw_pin_data_document(
            mcu_path=mcu_path,
            gpio_modes_path=resolve_gpio_modes_path(
                execution_context, device_name, vendor=vendor, family=family
            ),
        )
        ip_version_table = parse_ip_version_table(mcu_path)
        devices.append(
            build_canonical_ir(raw, patch, pin_data, ip_version_table, vendor=vendor, family=family)
        )
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
