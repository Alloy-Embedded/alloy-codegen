"""Patch loading for bootstrap device metadata."""

from __future__ import annotations

import json
from dataclasses import dataclass
from pathlib import Path

from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError


@dataclass(frozen=True, slots=True)
class MemoryPatch:
    """Memory metadata supplied by a patch document."""

    name: str
    kind: str
    base_address: int
    size_bytes: int
    access: str


@dataclass(frozen=True, slots=True)
class PinSignalPatch:
    """One curated signal attached to a pin."""

    function: str
    peripheral: str | None
    signal: str | None
    af_number: int | None


@dataclass(frozen=True, slots=True)
class PinPatch:
    """Curated pin metadata supplied by a patch document."""

    name: str
    port: str | None
    number: int
    signals: tuple[PinSignalPatch, ...]


@dataclass(frozen=True, slots=True)
class PeripheralPatch:
    """Curated peripheral metadata supplied by a patch document."""

    name: str
    rcc_enable_signal: str | None
    rcc_reset_signal: str | None


@dataclass(frozen=True, slots=True)
class PackagePatch:
    """Family-level package metadata."""

    name: str
    pin_count: int


@dataclass(frozen=True, slots=True)
class PinCatalogEntry:
    """Family-level pin identity metadata."""

    name: str
    port: str | None
    number: int
    packages: tuple[str, ...]


@dataclass(frozen=True, slots=True)
class PinSignalCatalogEntry:
    """Family-level named alternate-function signal entry."""

    signal_id: str
    pin_name: str
    signal: PinSignalPatch


@dataclass(frozen=True, slots=True)
class FamilyPatchCatalog:
    """Family-level curated catalog used by device overlays."""

    patch_id: str
    packages: tuple[PackagePatch, ...]
    pins: tuple[PinCatalogEntry, ...]
    peripherals: tuple[PeripheralPatch, ...]
    pin_signals: tuple[PinSignalCatalogEntry, ...]
    dma_requests: tuple[DmaRequestCatalogEntry, ...]


@dataclass(frozen=True, slots=True)
class DmaRequestPatch:
    """Curated DMA routing metadata supplied by a patch document."""

    controller: str
    request_line: str
    peripheral: str | None
    signal: str | None


@dataclass(frozen=True, slots=True)
class DmaRequestCatalogEntry:
    """Family-level named DMA route entry."""

    request_id: str
    request: DmaRequestPatch


@dataclass(frozen=True, slots=True)
class DevicePatch:
    """Patch document for one bootstrap device."""

    patch_id: str
    family_patch_id: str | None
    device: str
    svd_file: str
    pin_data_file: str
    package: str
    pin_count: int
    core: str
    summary: str
    memories: tuple[MemoryPatch, ...]
    peripherals: tuple[PeripheralPatch, ...]
    pins: tuple[PinPatch, ...]
    dma_requests: tuple[DmaRequestPatch, ...]

    def to_dict(self) -> dict[str, object]:
        return {
            "patch_id": self.patch_id,
            "family_patch_id": self.family_patch_id,
            "device": self.device,
            "svd_file": self.svd_file,
            "pin_data_file": self.pin_data_file,
            "package": self.package,
            "pin_count": self.pin_count,
            "core": self.core,
            "summary": self.summary,
            "memories": [
                {
                    "name": memory.name,
                    "kind": memory.kind,
                    "base_address": memory.base_address,
                    "size_bytes": memory.size_bytes,
                    "access": memory.access,
                }
                for memory in self.memories
            ],
            "peripherals": [
                {
                    "name": peripheral.name,
                    "rcc_enable_signal": peripheral.rcc_enable_signal,
                    "rcc_reset_signal": peripheral.rcc_reset_signal,
                }
                for peripheral in self.peripherals
            ],
            "pins": [
                {
                    "name": pin.name,
                    "port": pin.port,
                    "number": pin.number,
                    "signals": [
                        {
                            "function": signal.function,
                            "peripheral": signal.peripheral,
                            "signal": signal.signal,
                            "af_number": signal.af_number,
                        }
                        for signal in pin.signals
                    ],
                }
                for pin in self.pins
            ],
            "dma_requests": [
                {
                    "controller": request.controller,
                    "request_line": request.request_line,
                    "peripheral": request.peripheral,
                    "signal": request.signal,
                }
                for request in self.dma_requests
            ],
        }


def family_patch_file_path(context: ExecutionContext, *, vendor: str, family: str) -> Path:
    """Resolve the family-level patch catalog path."""
    return context.patch_root / vendor / family / "family.json"


def patch_file_path(
    context: ExecutionContext, device_name: str, *, vendor: str, family: str
) -> Path:
    """Resolve the patch path for one device."""
    return context.patch_root / vendor / family / "devices" / f"{device_name}.json"


def _parse_pin_signal(payload: dict[str, object]) -> PinSignalPatch:
    return PinSignalPatch(
        function=str(payload["function"]),
        peripheral=str(payload["peripheral"]) if payload.get("peripheral") is not None else None,
        signal=str(payload["signal"]) if payload.get("signal") is not None else None,
        af_number=int(payload["af_number"]) if payload.get("af_number") is not None else None,
    )


def _default_gpio_signal(*, port: str | None, number: int) -> PinSignalPatch | None:
    if port is None:
        return None
    return PinSignalPatch(
        function="gpio",
        peripheral=f"GPIO{port}",
        signal=f"IN{number}",
        af_number=None,
    )


def _parse_peripheral_patch(payload: dict[str, object]) -> PeripheralPatch:
    return PeripheralPatch(
        name=str(payload["name"]),
        rcc_enable_signal=(
            str(payload["rcc_enable_signal"])
            if payload.get("rcc_enable_signal") is not None
            else None
        ),
        rcc_reset_signal=(
            str(payload["rcc_reset_signal"])
            if payload.get("rcc_reset_signal") is not None
            else None
        ),
    )


def _parse_package_patch(payload: dict[str, object]) -> PackagePatch:
    return PackagePatch(
        name=str(payload["name"]),
        pin_count=int(payload["pin_count"]),
    )


def _parse_pin_catalog_entry(payload: dict[str, object]) -> PinCatalogEntry:
    return PinCatalogEntry(
        name=str(payload["name"]),
        port=str(payload["port"]) if payload.get("port") is not None else None,
        number=int(payload["number"]),
        packages=tuple(str(package) for package in payload.get("packages", ())),
    )


def _parse_pin_signal_catalog_entry(payload: dict[str, object]) -> PinSignalCatalogEntry:
    return PinSignalCatalogEntry(
        signal_id=str(payload["signal_id"]),
        pin_name=str(payload["pin_name"]),
        signal=_parse_pin_signal(payload),
    )


def _parse_dma_request_patch(payload: dict[str, object]) -> DmaRequestPatch:
    return DmaRequestPatch(
        controller=str(payload["controller"]),
        request_line=str(payload["request_line"]),
        peripheral=str(payload["peripheral"]) if payload.get("peripheral") is not None else None,
        signal=str(payload["signal"]) if payload.get("signal") is not None else None,
    )


def _parse_dma_request_catalog_entry(payload: dict[str, object]) -> DmaRequestCatalogEntry:
    return DmaRequestCatalogEntry(
        request_id=str(payload["request_id"]),
        request=_parse_dma_request_patch(payload),
    )


def load_family_patch_catalog(
    context: ExecutionContext, *, vendor: str, family: str
) -> FamilyPatchCatalog:
    """Load the family patch catalog for the given vendor/family."""
    patch_path = family_patch_file_path(context, vendor=vendor, family=family)
    if not patch_path.exists():
        raise StageExecutionError(f"Missing family patch catalog: {patch_path}")

    payload = json.loads(patch_path.read_text())
    return FamilyPatchCatalog(
        patch_id=payload["patch_id"],
        packages=tuple(_parse_package_patch(item) for item in payload.get("packages", ())),
        pins=tuple(_parse_pin_catalog_entry(item) for item in payload.get("pins", ())),
        peripherals=tuple(
            _parse_peripheral_patch(item) for item in payload.get("peripherals", ())
        ),
        pin_signals=tuple(
            _parse_pin_signal_catalog_entry(item) for item in payload.get("pin_signals", ())
        ),
        dma_requests=tuple(
            _parse_dma_request_catalog_entry(item) for item in payload.get("dma_requests", ())
        ),
    )


def _resolve_peripheral_patch(
    *,
    item: object,
    catalog: dict[str, PeripheralPatch],
) -> PeripheralPatch:
    if isinstance(item, str):
        if item not in catalog:
            raise StageExecutionError(f"Unknown peripheral reference in patch overlay: {item}")
        return catalog[item]

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid peripheral patch entry: {item!r}")

    name = str(item["name"])
    base = catalog.get(name)
    if base is None:
        return _parse_peripheral_patch(item)

    return PeripheralPatch(
        name=name,
        rcc_enable_signal=(
            str(item["rcc_enable_signal"])
            if item.get("rcc_enable_signal") is not None
            else base.rcc_enable_signal
        ),
        rcc_reset_signal=(
            str(item["rcc_reset_signal"])
            if item.get("rcc_reset_signal") is not None
            else base.rcc_reset_signal
        ),
    )


def _resolve_package_patch(
    *,
    package_name: str,
    catalog: dict[str, PackagePatch],
) -> PackagePatch:
    package = catalog.get(package_name)
    if package is None:
        raise StageExecutionError(f"Unknown package reference in patch overlay: {package_name}")
    return package


def _normalize_alternate_signal_entries(
    *,
    payload: dict[str, object],
    port: str | None,
    number: int,
    pin_name: str,
    signal_catalog: dict[str, PinSignalCatalogEntry] | None = None,
) -> tuple[PinSignalPatch, ...]:
    signal_refs = payload.get("signal_refs", ())
    if not isinstance(signal_refs, list | tuple):
        raise StageExecutionError(f"Invalid pin signal reference list for {payload['name']!r}.")

    alternate_signal_entries = payload.get("alternate_signals")
    if alternate_signal_entries is None:
        alternate_signal_entries = payload.get("signals", ())
    if not isinstance(alternate_signal_entries, list | tuple):
        raise StageExecutionError(f"Invalid pin signal list for {payload['name']!r}.")

    default_gpio = _default_gpio_signal(port=port, number=number)
    alternate_signals: list[PinSignalPatch] = []
    for signal_ref in signal_refs:
        if signal_catalog is None:
            raise StageExecutionError(
                f"Pin signal reference requires a family catalog: {signal_ref!r}"
            )
        if not isinstance(signal_ref, str):
            raise StageExecutionError(
                f"Invalid pin signal reference for {payload['name']!r}: {signal_ref!r}"
            )
        catalog_entry = signal_catalog.get(signal_ref)
        if catalog_entry is None:
            raise StageExecutionError(f"Unknown pin signal reference: {signal_ref}")
        if catalog_entry.pin_name != pin_name:
            raise StageExecutionError(
                f"Pin signal reference {signal_ref!r} targets {catalog_entry.pin_name}, "
                f"not {pin_name}."
            )
        if default_gpio is not None and catalog_entry.signal == default_gpio:
            continue
        alternate_signals.append(catalog_entry.signal)

    for entry in alternate_signal_entries:
        if not isinstance(entry, dict):
            raise StageExecutionError(
                f"Invalid pin signal entry for {payload['name']!r}: {entry!r}"
            )
        signal = _parse_pin_signal(entry)
        if default_gpio is not None and signal == default_gpio:
            continue
        alternate_signals.append(signal)
    return tuple(alternate_signals)


def _resolve_pin_patch(
    *,
    payload: dict[str, object],
    package_name: str,
    catalog: dict[str, PinCatalogEntry],
    signal_catalog: dict[str, PinSignalCatalogEntry],
) -> PinPatch:
    pin_name = str(payload["name"])
    base_entry = catalog.get(pin_name)
    if base_entry is None:
        raise StageExecutionError(f"Unknown pin reference in patch overlay: {pin_name}")
    if base_entry.packages and package_name not in base_entry.packages:
        raise StageExecutionError(
            f"Pin {pin_name} is not declared for package {package_name} in the family catalog."
        )

    port = str(payload["port"]) if payload.get("port") is not None else base_entry.port
    number = int(payload["number"]) if payload.get("number") is not None else base_entry.number
    alternate_signals = _normalize_alternate_signal_entries(
        payload=payload,
        port=port,
        number=number,
        pin_name=pin_name,
        signal_catalog=signal_catalog,
    )
    default_signal = _default_gpio_signal(port=port, number=number)
    signals = alternate_signals if default_signal is None else (default_signal, *alternate_signals)
    return PinPatch(
        name=pin_name,
        port=port,
        number=number,
        signals=signals,
    )


def _resolve_pin_count(
    *,
    payload: dict[str, object],
    package: PackagePatch,
) -> int:
    if "pin_count" not in payload:
        return package.pin_count

    declared_pin_count = int(payload["pin_count"])
    if declared_pin_count != package.pin_count:
        raise StageExecutionError(
            f"Pin count mismatch for package {package.name}: "
            f"overlay={declared_pin_count}, catalog={package.pin_count}."
    )
    return declared_pin_count


def _resolve_dma_request(
    *,
    item: object,
    catalog: dict[str, DmaRequestCatalogEntry],
) -> DmaRequestPatch:
    if isinstance(item, str):
        catalog_entry = catalog.get(item)
        if catalog_entry is None:
            raise StageExecutionError(f"Unknown DMA request reference in patch overlay: {item}")
        return catalog_entry.request

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid DMA request patch entry: {item!r}")
    return _parse_dma_request_patch(item)


def _parse_pin_patch(payload: dict[str, object]) -> PinPatch:
    port = str(payload["port"]) if payload.get("port") is not None else None
    number = int(payload["number"])
    alternate_signals = _normalize_alternate_signal_entries(
        payload=payload,
        port=port,
        number=number,
        pin_name=str(payload["name"]),
    )
    default_signal = _default_gpio_signal(port=port, number=number)
    signals = alternate_signals if default_signal is None else (default_signal, *alternate_signals)
    return PinPatch(
        name=str(payload["name"]),
        port=port,
        number=number,
        signals=signals,
    )


def load_device_patch(
    context: ExecutionContext, device_name: str, *, vendor: str, family: str
) -> DevicePatch:
    """Load one device patch document."""
    patch_path = patch_file_path(context, device_name, vendor=vendor, family=family)
    if not patch_path.exists():
        raise StageExecutionError(f"Missing patch document: {patch_path}")

    family_catalog = load_family_patch_catalog(context, vendor=vendor, family=family)
    package_catalog_by_name = {package.name: package for package in family_catalog.packages}
    pin_catalog_by_name = {pin.name: pin for pin in family_catalog.pins}
    signal_catalog_by_id = {signal.signal_id: signal for signal in family_catalog.pin_signals}
    dma_catalog_by_id = {request.request_id: request for request in family_catalog.dma_requests}
    catalog_by_name = {peripheral.name: peripheral for peripheral in family_catalog.peripherals}
    payload = json.loads(patch_path.read_text())
    package = _resolve_package_patch(
        package_name=payload["package"],
        catalog=package_catalog_by_name,
    )
    return DevicePatch(
        patch_id=payload["patch_id"],
        family_patch_id=family_catalog.patch_id,
        device=payload["device"],
        svd_file=payload["svd_file"],
        pin_data_file=payload["pin_data_file"],
        package=package.name,
        pin_count=_resolve_pin_count(payload=payload, package=package),
        core=payload["core"],
        summary=payload["summary"],
        memories=tuple(
            MemoryPatch(
                name=item["name"],
                kind=item["kind"],
                base_address=item["base_address"],
                size_bytes=item["size_bytes"],
                access=item["access"],
            )
            for item in payload["memories"]
        ),
        peripherals=tuple(
            {
                peripheral.name: peripheral
                for peripheral in (
                    *family_catalog.peripherals,
                    *(
                        _resolve_peripheral_patch(item=item, catalog=catalog_by_name)
                        for item in payload.get("peripherals", ())
                    ),
                )
            }.values()
        ),
        pins=tuple(
            (
                _resolve_pin_patch(
                    payload=item,
                    package_name=package.name,
                    catalog=pin_catalog_by_name,
                    signal_catalog=signal_catalog_by_id,
                )
                if "port" not in item or "number" not in item
                else _parse_pin_patch(item)
            )
            for item in payload.get("pins", ())
        ),
        dma_requests=tuple(
            _resolve_dma_request(
                item=item,
                catalog=dma_catalog_by_id,
            )
            for item in payload.get("dma_requests", payload.get("dma_request_refs", ()))
        ),
    )
