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
    address_space: str | None = None


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
    ip_version: str | None


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
class RegisterFieldPatch:
    """Curated register-field metadata used when upstream sources omit bitfields."""

    peripheral: str
    register_name: str
    name: str
    bit_offset: int
    bit_width: int
    access: str | None


@dataclass(frozen=True, slots=True)
class RegisterPatch:
    """Curated register metadata used when upstream sources omit control blocks."""

    peripheral: str
    name: str
    offset_bytes: int
    access: str | None
    size_bits: int | None
    base_address: int | None = None


@dataclass(frozen=True, slots=True)
class DmaControllerPatch:
    """Curated DMA controller metadata supplied by a patch document."""

    controller: str
    channel_count: int | None
    version: str | None


@dataclass(frozen=True, slots=True)
class ClockNodePatch:
    """Curated clock-tree node metadata supplied by a patch document."""

    node_id: str
    kind: str
    parent: str | None
    selector: str | None


@dataclass(frozen=True, slots=True)
class ClockSelectorPatch:
    """Curated clock source-selector metadata supplied by a patch document."""

    selector_id: str
    parent_options: tuple[str, ...]
    register_target: str | None


@dataclass(frozen=True, slots=True)
class ClockGatePatch:
    """Curated clock-gate metadata supplied by a patch document."""

    gate_id: str
    peripheral: str | None
    enable_signal: str
    parent_node: str | None


@dataclass(frozen=True, slots=True)
class ResetPatch:
    """Curated reset descriptor metadata supplied by a patch document."""

    reset_id: str
    peripheral: str | None
    reset_signal: str
    active_level: str | None


@dataclass(frozen=True, slots=True)
class PeripheralClockBindingPatch:
    """Curated peripheral-to-clock/reset binding metadata."""

    peripheral: str
    clock_gate_id: str | None
    reset_id: str | None
    selector_id: str | None


@dataclass(frozen=True, slots=True)
class SystemClockProfilePatch:
    """Curated system clock bring-up profile metadata."""

    profile_id: str
    kind: str
    source_kind: str
    sysclk_hz: int
    hclk_hz: int | None = None
    apb1_hz: int | None = None
    apb2_hz: int | None = None
    pclk_hz: int | None = None
    source_hz: int | None = None
    ahb_prescaler: int | None = None
    apb1_prescaler: int | None = None
    apb2_prescaler: int | None = None
    oscillator_startup_cycles: int | None = None
    mck_prescaler: int | None = None
    cpu_prescaler: int | None = None
    ipg_prescaler: int | None = None
    pll_m: int | None = None
    pll_n: int | None = None
    pll_p: int | None = None
    pll_q: int | None = None
    pll_r: int | None = None
    flash_latency: int | None = None


@dataclass(frozen=True, slots=True)
class FamilyPatchCatalog:
    """Family-level curated catalog used by device overlays."""

    patch_id: str
    packages: tuple[PackagePatch, ...]
    pins: tuple[PinCatalogEntry, ...]
    peripherals: tuple[PeripheralPatch, ...]
    pin_signals: tuple[PinSignalCatalogEntry, ...]
    registers: tuple[RegisterPatch, ...]
    register_fields: tuple[RegisterFieldPatch, ...]
    clock_nodes: tuple[ClockNodePatch, ...]
    clock_selectors: tuple[ClockSelectorPatch, ...]
    clock_gates: tuple[ClockGatePatch, ...]
    resets: tuple[ResetPatch, ...]
    peripheral_clock_bindings: tuple[PeripheralClockBindingPatch, ...]
    system_clock_profiles: tuple[SystemClockProfilePatch, ...]
    dma_controllers: tuple[DmaControllerPatch, ...]
    dma_requests: tuple[DmaRequestCatalogEntry, ...]


@dataclass(frozen=True, slots=True)
class DmaRequestPatch:
    """Curated DMA routing metadata supplied by a patch document."""

    controller: str
    request_line: str
    peripheral: str | None
    signal: str | None
    channel_index: int | None = None
    request_value: int | None = None
    channel_selector: int | None = None


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
    svd_file: str | None
    pin_data_file: str | None
    package: str
    pin_count: int
    core: str
    summary: str
    memories: tuple[MemoryPatch, ...]
    peripherals: tuple[PeripheralPatch, ...]
    registers: tuple[RegisterPatch, ...]
    register_fields: tuple[RegisterFieldPatch, ...]
    pins: tuple[PinPatch, ...]
    clock_nodes: tuple[ClockNodePatch, ...]
    clock_selectors: tuple[ClockSelectorPatch, ...]
    clock_gates: tuple[ClockGatePatch, ...]
    resets: tuple[ResetPatch, ...]
    peripheral_clock_bindings: tuple[PeripheralClockBindingPatch, ...]
    system_clock_profiles: tuple[SystemClockProfilePatch, ...]
    dma_controllers: tuple[DmaControllerPatch, ...]
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
            "registers": [
                {
                    "peripheral": register.peripheral,
                    "name": register.name,
                    "offset_bytes": register.offset_bytes,
                    "access": register.access,
                    "size_bits": register.size_bits,
                    "base_address": register.base_address,
                }
                for register in self.registers
            ],
            "register_fields": [
                {
                    "peripheral": field.peripheral,
                    "register_name": field.register_name,
                    "name": field.name,
                    "bit_offset": field.bit_offset,
                    "bit_width": field.bit_width,
                    "access": field.access,
                }
                for field in self.register_fields
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
            "clock_nodes": [
                {
                    "node_id": node.node_id,
                    "kind": node.kind,
                    "parent": node.parent,
                    "selector": node.selector,
                }
                for node in self.clock_nodes
            ],
            "clock_selectors": [
                {
                    "selector_id": selector.selector_id,
                    "parent_options": list(selector.parent_options),
                    "register_target": selector.register_target,
                }
                for selector in self.clock_selectors
            ],
            "clock_gates": [
                {
                    "gate_id": gate.gate_id,
                    "peripheral": gate.peripheral,
                    "enable_signal": gate.enable_signal,
                    "parent_node": gate.parent_node,
                }
                for gate in self.clock_gates
            ],
            "resets": [
                {
                    "reset_id": reset.reset_id,
                    "peripheral": reset.peripheral,
                    "reset_signal": reset.reset_signal,
                    "active_level": reset.active_level,
                }
                for reset in self.resets
            ],
            "peripheral_clock_bindings": [
                {
                    "peripheral": binding.peripheral,
                    "clock_gate_id": binding.clock_gate_id,
                    "reset_id": binding.reset_id,
                    "selector_id": binding.selector_id,
                }
                for binding in self.peripheral_clock_bindings
            ],
            "system_clock_profiles": [
                {
                    "profile_id": profile.profile_id,
                    "kind": profile.kind,
                    "source_kind": profile.source_kind,
                    "sysclk_hz": profile.sysclk_hz,
                    "hclk_hz": profile.hclk_hz,
                    "apb1_hz": profile.apb1_hz,
                    "apb2_hz": profile.apb2_hz,
                    "pclk_hz": profile.pclk_hz,
                    "source_hz": profile.source_hz,
                    "ahb_prescaler": profile.ahb_prescaler,
                    "apb1_prescaler": profile.apb1_prescaler,
                    "apb2_prescaler": profile.apb2_prescaler,
                    "oscillator_startup_cycles": profile.oscillator_startup_cycles,
                    "mck_prescaler": profile.mck_prescaler,
                    "cpu_prescaler": profile.cpu_prescaler,
                    "ipg_prescaler": profile.ipg_prescaler,
                    "pll_m": profile.pll_m,
                    "pll_n": profile.pll_n,
                    "pll_p": profile.pll_p,
                    "pll_q": profile.pll_q,
                    "pll_r": profile.pll_r,
                    "flash_latency": profile.flash_latency,
                }
                for profile in self.system_clock_profiles
            ],
            "dma_controllers": [
                {
                    "controller": controller.controller,
                    "channel_count": controller.channel_count,
                    "version": controller.version,
                }
                for controller in self.dma_controllers
            ],
            "dma_requests": [
                {
                    "controller": request.controller,
                    "request_line": request.request_line,
                    "peripheral": request.peripheral,
                    "signal": request.signal,
                    "channel_index": request.channel_index,
                    "request_value": request.request_value,
                    "channel_selector": request.channel_selector,
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
        ip_version=(str(payload["ip_version"]) if payload.get("ip_version") is not None else None),
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


def _parse_register_field_patch(payload: dict[str, object]) -> RegisterFieldPatch:
    return RegisterFieldPatch(
        peripheral=str(payload["peripheral"]),
        register_name=str(payload["register_name"]),
        name=str(payload["name"]),
        bit_offset=int(payload["bit_offset"]),
        bit_width=int(payload.get("bit_width", 1)),
        access=str(payload["access"]) if payload.get("access") is not None else None,
    )


def _parse_register_patch(payload: dict[str, object]) -> RegisterPatch:
    return RegisterPatch(
        peripheral=str(payload["peripheral"]),
        name=str(payload["name"]),
        offset_bytes=int(payload["offset_bytes"]),
        access=str(payload["access"]) if payload.get("access") is not None else None,
        size_bits=int(payload["size_bits"]) if payload.get("size_bits") is not None else None,
        base_address=(
            int(payload["base_address"]) if payload.get("base_address") is not None else None
        ),
    )


def _parse_dma_request_patch(payload: dict[str, object]) -> DmaRequestPatch:
    return DmaRequestPatch(
        controller=str(payload["controller"]),
        request_line=str(payload["request_line"]),
        peripheral=str(payload["peripheral"]) if payload.get("peripheral") is not None else None,
        signal=str(payload["signal"]) if payload.get("signal") is not None else None,
        channel_index=(
            int(payload["channel_index"]) if payload.get("channel_index") is not None else None
        ),
        request_value=(
            int(payload["request_value"]) if payload.get("request_value") is not None else None
        ),
        channel_selector=(
            int(payload["channel_selector"])
            if payload.get("channel_selector") is not None
            else None
        ),
    )


def _parse_dma_request_catalog_entry(payload: dict[str, object]) -> DmaRequestCatalogEntry:
    return DmaRequestCatalogEntry(
        request_id=str(payload["request_id"]),
        request=_parse_dma_request_patch(payload),
    )


def _parse_dma_controller_patch(payload: dict[str, object]) -> DmaControllerPatch:
    return DmaControllerPatch(
        controller=str(payload["controller"]),
        channel_count=(
            int(payload["channel_count"]) if payload.get("channel_count") is not None else None
        ),
        version=str(payload["version"]) if payload.get("version") is not None else None,
    )


def _parse_clock_node_patch(payload: dict[str, object]) -> ClockNodePatch:
    return ClockNodePatch(
        node_id=str(payload["node_id"]),
        kind=str(payload["kind"]),
        parent=str(payload["parent"]) if payload.get("parent") is not None else None,
        selector=str(payload["selector"]) if payload.get("selector") is not None else None,
    )


def _parse_clock_selector_patch(payload: dict[str, object]) -> ClockSelectorPatch:
    return ClockSelectorPatch(
        selector_id=str(payload["selector_id"]),
        parent_options=tuple(str(option) for option in payload.get("parent_options", ())),
        register_target=(
            str(payload["register_target"]) if payload.get("register_target") is not None else None
        ),
    )


def _parse_clock_gate_patch(payload: dict[str, object]) -> ClockGatePatch:
    return ClockGatePatch(
        gate_id=str(payload["gate_id"]),
        peripheral=str(payload["peripheral"]) if payload.get("peripheral") is not None else None,
        enable_signal=str(payload["enable_signal"]),
        parent_node=str(payload["parent_node"]) if payload.get("parent_node") is not None else None,
    )


def _parse_reset_patch(payload: dict[str, object]) -> ResetPatch:
    return ResetPatch(
        reset_id=str(payload["reset_id"]),
        peripheral=str(payload["peripheral"]) if payload.get("peripheral") is not None else None,
        reset_signal=str(payload["reset_signal"]),
        active_level=(
            str(payload["active_level"]) if payload.get("active_level") is not None else None
        ),
    )


def _parse_peripheral_clock_binding_patch(
    payload: dict[str, object],
) -> PeripheralClockBindingPatch:
    return PeripheralClockBindingPatch(
        peripheral=str(payload["peripheral"]),
        clock_gate_id=(
            str(payload["clock_gate_id"]) if payload.get("clock_gate_id") is not None else None
        ),
        reset_id=str(payload["reset_id"]) if payload.get("reset_id") is not None else None,
        selector_id=(
            str(payload["selector_id"]) if payload.get("selector_id") is not None else None
        ),
    )


def _parse_system_clock_profile_patch(payload: dict[str, object]) -> SystemClockProfilePatch:
    return SystemClockProfilePatch(
        profile_id=str(payload["profile_id"]),
        kind=str(payload["kind"]),
        source_kind=str(payload["source_kind"]),
        sysclk_hz=int(payload["sysclk_hz"]),
        hclk_hz=int(payload["hclk_hz"]) if payload.get("hclk_hz") is not None else None,
        apb1_hz=int(payload["apb1_hz"]) if payload.get("apb1_hz") is not None else None,
        apb2_hz=int(payload["apb2_hz"]) if payload.get("apb2_hz") is not None else None,
        pclk_hz=int(payload["pclk_hz"]) if payload.get("pclk_hz") is not None else None,
        source_hz=int(payload["source_hz"]) if payload.get("source_hz") is not None else None,
        ahb_prescaler=(
            int(payload["ahb_prescaler"]) if payload.get("ahb_prescaler") is not None else None
        ),
        apb1_prescaler=(
            int(payload["apb1_prescaler"]) if payload.get("apb1_prescaler") is not None else None
        ),
        apb2_prescaler=(
            int(payload["apb2_prescaler"]) if payload.get("apb2_prescaler") is not None else None
        ),
        oscillator_startup_cycles=(
            int(payload["oscillator_startup_cycles"])
            if payload.get("oscillator_startup_cycles") is not None
            else None
        ),
        mck_prescaler=(
            int(payload["mck_prescaler"]) if payload.get("mck_prescaler") is not None else None
        ),
        cpu_prescaler=(
            int(payload["cpu_prescaler"]) if payload.get("cpu_prescaler") is not None else None
        ),
        ipg_prescaler=(
            int(payload["ipg_prescaler"]) if payload.get("ipg_prescaler") is not None else None
        ),
        pll_m=int(payload["pll_m"]) if payload.get("pll_m") is not None else None,
        pll_n=int(payload["pll_n"]) if payload.get("pll_n") is not None else None,
        pll_p=int(payload["pll_p"]) if payload.get("pll_p") is not None else None,
        pll_q=int(payload["pll_q"]) if payload.get("pll_q") is not None else None,
        pll_r=int(payload["pll_r"]) if payload.get("pll_r") is not None else None,
        flash_latency=(
            int(payload["flash_latency"]) if payload.get("flash_latency") is not None else None
        ),
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
        peripherals=tuple(_parse_peripheral_patch(item) for item in payload.get("peripherals", ())),
        pin_signals=tuple(
            _parse_pin_signal_catalog_entry(item) for item in payload.get("pin_signals", ())
        ),
        registers=tuple(_parse_register_patch(item) for item in payload.get("registers", ())),
        register_fields=tuple(
            _parse_register_field_patch(item) for item in payload.get("register_fields", ())
        ),
        clock_nodes=tuple(_parse_clock_node_patch(item) for item in payload.get("clock_nodes", ())),
        clock_selectors=tuple(
            _parse_clock_selector_patch(item) for item in payload.get("clock_selectors", ())
        ),
        clock_gates=tuple(_parse_clock_gate_patch(item) for item in payload.get("clock_gates", ())),
        resets=tuple(_parse_reset_patch(item) for item in payload.get("resets", ())),
        peripheral_clock_bindings=tuple(
            _parse_peripheral_clock_binding_patch(item)
            for item in payload.get("peripheral_clock_bindings", ())
        ),
        system_clock_profiles=tuple(
            _parse_system_clock_profile_patch(item)
            for item in payload.get("system_clock_profiles", ())
        ),
        dma_controllers=tuple(
            _parse_dma_controller_patch(item) for item in payload.get("dma_controllers", ())
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
        ip_version=(
            str(item["ip_version"]) if item.get("ip_version") is not None else base.ip_version
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


def _resolve_dma_controller(
    *,
    item: object,
    catalog: dict[str, DmaControllerPatch],
) -> DmaControllerPatch:
    if isinstance(item, str):
        controller = catalog.get(item)
        if controller is None:
            raise StageExecutionError(f"Unknown DMA controller reference in patch overlay: {item}")
        return controller

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid DMA controller patch entry: {item!r}")

    controller_name = str(item["controller"])
    base = catalog.get(controller_name)
    if base is None:
        return _parse_dma_controller_patch(item)

    return DmaControllerPatch(
        controller=controller_name,
        channel_count=(
            int(item["channel_count"])
            if item.get("channel_count") is not None
            else base.channel_count
        ),
        version=str(item["version"]) if item.get("version") is not None else base.version,
    )


def _resolve_clock_node(
    *,
    item: object,
    catalog: dict[str, ClockNodePatch],
) -> ClockNodePatch:
    if isinstance(item, str):
        node = catalog.get(item)
        if node is None:
            raise StageExecutionError(f"Unknown clock node reference in patch overlay: {item}")
        return node

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid clock node patch entry: {item!r}")

    node_id = str(item["node_id"])
    base = catalog.get(node_id)
    if base is None:
        return _parse_clock_node_patch(item)

    return ClockNodePatch(
        node_id=node_id,
        kind=str(item["kind"]) if item.get("kind") is not None else base.kind,
        parent=str(item["parent"]) if item.get("parent") is not None else base.parent,
        selector=str(item["selector"]) if item.get("selector") is not None else base.selector,
    )


def _resolve_clock_selector(
    *,
    item: object,
    catalog: dict[str, ClockSelectorPatch],
) -> ClockSelectorPatch:
    if isinstance(item, str):
        selector = catalog.get(item)
        if selector is None:
            raise StageExecutionError(f"Unknown clock selector reference in patch overlay: {item}")
        return selector

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid clock selector patch entry: {item!r}")

    selector_id = str(item["selector_id"])
    base = catalog.get(selector_id)
    if base is None:
        return _parse_clock_selector_patch(item)

    return ClockSelectorPatch(
        selector_id=selector_id,
        parent_options=(
            tuple(str(option) for option in item["parent_options"])
            if item.get("parent_options") is not None
            else base.parent_options
        ),
        register_target=(
            str(item["register_target"])
            if item.get("register_target") is not None
            else base.register_target
        ),
    )


def _resolve_clock_gate(
    *,
    item: object,
    catalog: dict[str, ClockGatePatch],
) -> ClockGatePatch:
    if isinstance(item, str):
        gate = catalog.get(item)
        if gate is None:
            raise StageExecutionError(f"Unknown clock gate reference in patch overlay: {item}")
        return gate

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid clock gate patch entry: {item!r}")

    gate_id = str(item["gate_id"])
    base = catalog.get(gate_id)
    if base is None:
        return _parse_clock_gate_patch(item)

    return ClockGatePatch(
        gate_id=gate_id,
        peripheral=(
            str(item["peripheral"]) if item.get("peripheral") is not None else base.peripheral
        ),
        enable_signal=(
            str(item["enable_signal"])
            if item.get("enable_signal") is not None
            else base.enable_signal
        ),
        parent_node=(
            str(item["parent_node"]) if item.get("parent_node") is not None else base.parent_node
        ),
    )


def _resolve_reset(
    *,
    item: object,
    catalog: dict[str, ResetPatch],
) -> ResetPatch:
    if isinstance(item, str):
        reset = catalog.get(item)
        if reset is None:
            raise StageExecutionError(f"Unknown reset reference in patch overlay: {item}")
        return reset

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid reset patch entry: {item!r}")

    reset_id = str(item["reset_id"])
    base = catalog.get(reset_id)
    if base is None:
        return _parse_reset_patch(item)

    return ResetPatch(
        reset_id=reset_id,
        peripheral=(
            str(item["peripheral"]) if item.get("peripheral") is not None else base.peripheral
        ),
        reset_signal=(
            str(item["reset_signal"]) if item.get("reset_signal") is not None else base.reset_signal
        ),
        active_level=(
            str(item["active_level"]) if item.get("active_level") is not None else base.active_level
        ),
    )


def _resolve_peripheral_clock_binding(
    *,
    item: object,
    catalog: dict[str, PeripheralClockBindingPatch],
) -> PeripheralClockBindingPatch:
    if isinstance(item, str):
        binding = catalog.get(item)
        if binding is None:
            raise StageExecutionError(
                f"Unknown peripheral clock binding reference in patch overlay: {item}"
            )
        return binding

    if not isinstance(item, dict):
        raise StageExecutionError(f"Invalid peripheral clock binding patch entry: {item!r}")

    peripheral = str(item["peripheral"])
    base = catalog.get(peripheral)
    if base is None:
        return _parse_peripheral_clock_binding_patch(item)

    return PeripheralClockBindingPatch(
        peripheral=peripheral,
        clock_gate_id=(
            str(item["clock_gate_id"])
            if item.get("clock_gate_id") is not None
            else base.clock_gate_id
        ),
        reset_id=str(item["reset_id"]) if item.get("reset_id") is not None else base.reset_id,
        selector_id=(
            str(item["selector_id"]) if item.get("selector_id") is not None else base.selector_id
        ),
    )


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
    clock_node_catalog_by_id = {node.node_id: node for node in family_catalog.clock_nodes}
    clock_selector_catalog_by_id = {
        selector.selector_id: selector for selector in family_catalog.clock_selectors
    }
    clock_gate_catalog_by_id = {gate.gate_id: gate for gate in family_catalog.clock_gates}
    reset_catalog_by_id = {reset.reset_id: reset for reset in family_catalog.resets}
    peripheral_clock_binding_catalog_by_peripheral = {
        binding.peripheral: binding for binding in family_catalog.peripheral_clock_bindings
    }
    dma_controller_catalog_by_name = {
        controller.controller: controller for controller in family_catalog.dma_controllers
    }
    dma_catalog_by_id = {request.request_id: request for request in family_catalog.dma_requests}
    catalog_by_name = {peripheral.name: peripheral for peripheral in family_catalog.peripherals}
    register_field_catalog_by_key = {
        (field.peripheral, field.register_name, field.name): field
        for field in family_catalog.register_fields
    }
    register_catalog_by_key = {
        (register.peripheral, register.name): register for register in family_catalog.registers
    }
    payload = json.loads(patch_path.read_text())
    package = _resolve_package_patch(
        package_name=payload["package"],
        catalog=package_catalog_by_name,
    )
    return DevicePatch(
        patch_id=payload["patch_id"],
        family_patch_id=family_catalog.patch_id,
        device=payload["device"],
        svd_file=str(payload["svd_file"]) if payload.get("svd_file") is not None else None,
        pin_data_file=(
            str(payload["pin_data_file"]) if payload.get("pin_data_file") is not None else None
        ),
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
                address_space=item.get("address_space"),
            )
            for item in payload.get("memories", ())
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
        registers=tuple(
            {
                (register.peripheral, register.name): register
                for register in (
                    *family_catalog.registers,
                    *(
                        register_catalog_by_key.get(
                            (str(item["peripheral"]), str(item["name"])),
                            _parse_register_patch(item),
                        )
                        for item in payload.get("registers", ())
                    ),
                )
            }.values()
        ),
        register_fields=tuple(
            {
                (field.peripheral, field.register_name, field.name): field
                for field in (
                    *family_catalog.register_fields,
                    *(
                        register_field_catalog_by_key.get(
                            (
                                str(item["peripheral"]),
                                str(item["register_name"]),
                                str(item["name"]),
                            ),
                            _parse_register_field_patch(item),
                        )
                        for item in payload.get("register_fields", ())
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
        clock_nodes=tuple(
            {
                node.node_id: node
                for node in (
                    *family_catalog.clock_nodes,
                    *(
                        _resolve_clock_node(item=item, catalog=clock_node_catalog_by_id)
                        for item in payload.get("clock_nodes", payload.get("clock_node_refs", ()))
                    ),
                )
            }.values()
        ),
        clock_selectors=tuple(
            {
                selector.selector_id: selector
                for selector in (
                    *family_catalog.clock_selectors,
                    *(
                        _resolve_clock_selector(
                            item=item,
                            catalog=clock_selector_catalog_by_id,
                        )
                        for item in payload.get(
                            "clock_selectors",
                            payload.get("clock_selector_refs", ()),
                        )
                    ),
                )
            }.values()
        ),
        clock_gates=tuple(
            {
                gate.gate_id: gate
                for gate in (
                    *family_catalog.clock_gates,
                    *(
                        _resolve_clock_gate(item=item, catalog=clock_gate_catalog_by_id)
                        for item in payload.get("clock_gates", payload.get("clock_gate_refs", ()))
                    ),
                )
            }.values()
        ),
        resets=tuple(
            {
                reset.reset_id: reset
                for reset in (
                    *family_catalog.resets,
                    *(
                        _resolve_reset(item=item, catalog=reset_catalog_by_id)
                        for item in payload.get("resets", payload.get("reset_refs", ()))
                    ),
                )
            }.values()
        ),
        peripheral_clock_bindings=tuple(
            {
                binding.peripheral: binding
                for binding in (
                    *family_catalog.peripheral_clock_bindings,
                    *(
                        _resolve_peripheral_clock_binding(
                            item=item,
                            catalog=peripheral_clock_binding_catalog_by_peripheral,
                        )
                        for item in payload.get(
                            "peripheral_clock_bindings",
                            payload.get("peripheral_clock_binding_refs", ()),
                        )
                    ),
                )
            }.values()
        ),
        system_clock_profiles=tuple(
            {
                profile.profile_id: profile
                for profile in (
                    *family_catalog.system_clock_profiles,
                    *(
                        _parse_system_clock_profile_patch(item)
                        for item in payload.get("system_clock_profiles", ())
                    ),
                )
            }.values()
        ),
        dma_controllers=tuple(
            {
                controller.controller: controller
                for controller in (
                    *family_catalog.dma_controllers,
                    *(
                        _resolve_dma_controller(
                            item=item,
                            catalog=dma_controller_catalog_by_name,
                        )
                        for item in payload.get(
                            "dma_controllers",
                            payload.get("dma_controller_refs", ()),
                        )
                    ),
                )
            }.values()
        ),
        dma_requests=tuple(
            _resolve_dma_request(
                item=item,
                catalog=dma_catalog_by_id,
            )
            for item in payload.get("dma_requests", payload.get("dma_request_refs", ()))
        ),
    )
