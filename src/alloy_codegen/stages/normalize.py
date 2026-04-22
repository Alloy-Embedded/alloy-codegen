"""Normalize stage bootstrap implementation."""

from __future__ import annotations

import re

from alloy_codegen.bootstrap import BOOTSTRAP_FAMILY, BOOTSTRAP_VENDOR, IR_SCHEMA_VERSION
from alloy_codegen.connector_model import ensure_connector_descriptors
from alloy_codegen.context import ExecutionContext
from alloy_codegen.errors import StageExecutionError
from alloy_codegen.ir.model import (
    CanonicalDeviceIR,
    ClockGateDescriptor,
    ClockNodeLite,
    ClockSelectorLite,
    DeviceIdentity,
    DmaControllerDescriptor,
    DmaRequestDefinition,
    InterruptDefinition,
    MemoryRegion,
    PackageDefinition,
    PackagePad,
    PeripheralClockBinding,
    PeripheralInstance,
    PinConstraint,
    PinDefinition,
    PinSignal,
    Provenance,
    RegisterDescriptor,
    RegisterFieldDescriptor,
    ResetDescriptor,
    SystemClockProfile,
)
from alloy_codegen.patches import (
    ClockGatePatch,
    ClockNodePatch,
    ClockSelectorPatch,
    DevicePatch,
    DmaControllerPatch,
    DmaRequestPatch,
    FamilyPatchCatalog,
    MemoryPatch,
    PeripheralClockBindingPatch,
    PeripheralPatch,
    PinPatch,
    PinSignalPatch,
    RegisterFieldPatch,
    RegisterPatch,
    ResetPatch,
    SystemClockProfilePatch,
    load_device_patch,
    load_family_patch_catalog,
)
from alloy_codegen.reporting import NormalizationBundle
from alloy_codegen.scope import PipelineScope
from alloy_codegen.sources.cmsis_svd import parse_raw_device_document, resolve_svd_path
from alloy_codegen.sources.microchip_dfp import (
    merge_source_patch,
    resolve_atdf_path,
    select_device_files,
)
from alloy_codegen.sources.microchip_dfp import (
    parse_dma_request_patches as parse_microchip_dma_request_patches,
)
from alloy_codegen.sources.microchip_dfp import (
    parse_ip_version_table as parse_microchip_ip_version_table,
)
from alloy_codegen.sources.microchip_dfp import (
    parse_memory_patches as parse_microchip_memory_patches,
)
from alloy_codegen.sources.microchip_dfp import (
    parse_peripheral_patches as parse_microchip_peripheral_patches,
)
from alloy_codegen.sources.microchip_dfp import (
    parse_raw_pin_data_document as parse_microchip_pin_data_document,
)
from alloy_codegen.sources.microchip_dfp import (
    resolve_svd_path as resolve_microchip_svd_path,
)
from alloy_codegen.sources.nxp_mcux import (
    PAD_NUMBER_PATTERN as NXP_PAD_NUMBER_PATTERN,
)
from alloy_codegen.sources.nxp_mcux import (
    SDK_SOURCE_ID as NXP_SDK_SOURCE_ID,
)
from alloy_codegen.sources.nxp_mcux import (
    SVD_SOURCE_ID as NXP_SVD_SOURCE_ID,
)
from alloy_codegen.sources.nxp_mcux import (
    NxpIomuxcEntry,
    parse_iomuxc_entries,
    resolve_iomuxc_header_path,
)
from alloy_codegen.sources.nxp_mcux import (
    resolve_svd_path as resolve_nxp_svd_path,
)
from alloy_codegen.sources.pico_sdk import (
    resolve_svd_path as resolve_pico_svd_path,
)
from alloy_codegen.sources.raw import (
    RawDeviceDocument,
    RawInterrupt,
    RawPackagePadEntry,
    RawPeripheral,
    RawPinDataDocument,
    RawRegister,
    RawRegisterField,
)
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
    # "ADC" and "DMA" (no instance suffix) are intentionally excluded here so
    # that RP2040, which genuinely names its peripherals "ADC" and "DMA", is not
    # silently remapped to "ADC1"/"DMA1".  STM32/NXP upstream SVDs already carry
    # numbered names (ADC1, DMA1, …) so no alias is needed for those families.
    "DMAMUX": "DMAMUX1",
    "LPUART": "LPUART1",
    "PIOA": "GPIOA",
    "PIOB": "GPIOB",
    "PIOC": "GPIOC",
    "PIOD": "GPIOD",
    "PIOE": "GPIOE",
}
ANALOG_IP_NAMES = {"adc", "dac", "comp", "opamp"}
DEBUG_SIGNAL_TOKENS = ("SWD", "JTAG", "TRACE", "TMS", "TCK", "TDI", "TDO", "SWCLK", "SWDIO")
WAKEUP_SIGNAL_TOKENS = ("WKUP",)


def _sanitize_token(value: str) -> str:
    return "".join(character.lower() if character.isalnum() else "-" for character in value).strip(
        "-"
    )


def _canonical_peripheral_name(peripheral_name: str) -> str:
    return RAW_PERIPHERAL_ALIASES.get(peripheral_name, peripheral_name)


def _infer_ip_metadata(peripheral_name: str) -> tuple[str, int]:
    if (
        peripheral_name.startswith("GPIO")
        and len(peripheral_name) == 5
        and peripheral_name[-1].isalpha()
    ):
        # ST-style: GPIOA, GPIOB, ... → instance 0, 1, ...
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
        address_space=memory.address_space,
    )


def _clock_node_to_ir(node: ClockNodePatch, provenance: Provenance) -> ClockNodeLite:
    return ClockNodeLite(
        node_id=node.node_id,
        kind=node.kind,
        parent=node.parent,
        selector=node.selector,
        provenance=provenance,
    )


def _clock_selector_to_ir(
    selector: ClockSelectorPatch,
    provenance: Provenance,
) -> ClockSelectorLite:
    return ClockSelectorLite(
        selector_id=selector.selector_id,
        parent_options=selector.parent_options,
        register_target=selector.register_target,
        provenance=provenance,
    )


def _clock_gate_to_ir(gate: ClockGatePatch, provenance: Provenance) -> ClockGateDescriptor:
    return ClockGateDescriptor(
        gate_id=gate.gate_id,
        peripheral=gate.peripheral,
        enable_signal=gate.enable_signal,
        parent_node=gate.parent_node,
        provenance=provenance,
    )


def _reset_to_ir(reset: ResetPatch, provenance: Provenance) -> ResetDescriptor:
    return ResetDescriptor(
        reset_id=reset.reset_id,
        peripheral=reset.peripheral,
        reset_signal=reset.reset_signal,
        active_level=reset.active_level,
        provenance=provenance,
    )


def _peripheral_clock_binding_to_ir(
    binding: PeripheralClockBindingPatch,
    provenance: Provenance,
) -> PeripheralClockBinding:
    return PeripheralClockBinding(
        peripheral=binding.peripheral,
        clock_gate_id=binding.clock_gate_id,
        reset_id=binding.reset_id,
        selector_id=binding.selector_id,
        provenance=provenance,
    )


def _system_clock_profile_to_ir(
    profile: SystemClockProfilePatch,
    provenance: Provenance,
) -> SystemClockProfile:
    return SystemClockProfile(
        profile_id=profile.profile_id,
        kind=profile.kind,
        source_kind=profile.source_kind,
        sysclk_hz=profile.sysclk_hz,
        hclk_hz=profile.hclk_hz,
        apb1_hz=profile.apb1_hz,
        apb2_hz=profile.apb2_hz,
        pclk_hz=profile.pclk_hz,
        source_hz=profile.source_hz,
        ahb_prescaler=profile.ahb_prescaler,
        apb1_prescaler=profile.apb1_prescaler,
        apb2_prescaler=profile.apb2_prescaler,
        oscillator_startup_cycles=profile.oscillator_startup_cycles,
        mck_prescaler=profile.mck_prescaler,
        cpu_prescaler=profile.cpu_prescaler,
        ipg_prescaler=profile.ipg_prescaler,
        pll_m=profile.pll_m,
        pll_n=profile.pll_n,
        pll_p=profile.pll_p,
        pll_q=profile.pll_q,
        pll_r=profile.pll_r,
        flash_latency=profile.flash_latency,
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


def _package_pad_to_ir(
    raw_pad: RawPackagePadEntry,
    *,
    package_name: str,
    provenance: Provenance,
) -> PackagePad:
    return PackagePad(
        pad_id=raw_pad.pad_id,
        package=package_name,
        position_label=raw_pad.position_label,
        physical_index=raw_pad.physical_index,
        pad_kind=raw_pad.pad_kind,
        bonded_pin=raw_pad.bonded_pin,
        provenance=provenance,
        bonding_state=raw_pad.bonding_state,
    )


def _normalize_interrupts(
    raw_interrupts: tuple[RawInterrupt, ...],
    *,
    provenance: Provenance,
    peripheral_aliases: dict[str, str] | None = None,
) -> tuple[InterruptDefinition, ...]:
    alias_map = peripheral_aliases or {}
    interrupts_by_line: dict[int, list[RawInterrupt]] = {}
    for interrupt in raw_interrupts:
        interrupts_by_line.setdefault(interrupt.line, []).append(interrupt)

    normalized_interrupts: list[InterruptDefinition] = []
    for line, entries in interrupts_by_line.items():
        primary = entries[0]
        primary_name = primary.name
        alias_names = tuple(
            dict.fromkeys(entry.name for entry in entries[1:] if entry.name != primary_name)
        )
        normalized_interrupts.append(
            InterruptDefinition(
                name=primary_name,
                line=line,
                peripheral=(
                    None
                    if primary.peripheral is None
                    else alias_map.get(
                        _canonical_peripheral_name(primary.peripheral),
                        _canonical_peripheral_name(primary.peripheral),
                    )
                ),
                provenance=provenance,
                alias_names=alias_names,
            )
        )
    return tuple(normalized_interrupts)


def _deduplicate_raw_peripherals(
    raw_peripherals: tuple[RawPeripheral, ...],
    *,
    preferred_names: set[str],
) -> tuple[tuple[RawPeripheral, ...], dict[str, str]]:
    selected_by_base: dict[int, RawPeripheral] = {}
    order: list[int] = []
    alias_map: dict[str, str] = {}
    for peripheral in raw_peripherals:
        canonical_name = _canonical_peripheral_name(peripheral.name)
        candidate = RawPeripheral(
            name=canonical_name,
            base_address=peripheral.base_address,
            registers=peripheral.registers,
        )
        existing = selected_by_base.get(candidate.base_address)
        if existing is None:
            selected_by_base[candidate.base_address] = candidate
            order.append(candidate.base_address)
            alias_map[candidate.name] = candidate.name
            continue
        existing_preferred = existing.name in preferred_names
        candidate_preferred = candidate.name in preferred_names
        if candidate_preferred and not existing_preferred:
            alias_map[existing.name] = candidate.name
            selected_by_base[candidate.base_address] = candidate
        alias_map[candidate.name] = selected_by_base[candidate.base_address].name
    for selected in selected_by_base.values():
        alias_map[selected.name] = selected.name
    return tuple(selected_by_base[base_address] for base_address in order), alias_map


def _add_pin_constraint(
    *,
    constraints: list[PinConstraint],
    seen_ids: set[str],
    pin: str,
    kind: str,
    value: str | None,
    provenance: Provenance,
) -> None:
    constraint_id = f"constraint:{pin}:{kind}"
    if constraint_id in seen_ids:
        return
    seen_ids.add(constraint_id)
    constraints.append(
        PinConstraint(
            constraint_id=constraint_id,
            pin=pin,
            kind=kind,
            value=value,
            provenance=provenance,
        )
    )


def _signal_tokens(pin: PinDefinition) -> tuple[str, ...]:
    return tuple(
        signal.signal.upper()
        for signal in pin.signals
        if signal.signal is not None and signal.peripheral is not None
    )


def _non_gpio_signals(pin: PinDefinition) -> tuple[PinSignal, ...]:
    return tuple(
        signal
        for signal in pin.signals
        if signal.peripheral is not None and not signal.peripheral.startswith("GPIO")
    )


def _is_debug_signal(signal_name: str) -> bool:
    normalized = signal_name.upper()
    return any(token in normalized for token in DEBUG_SIGNAL_TOKENS)


def _is_wakeup_signal(signal_name: str) -> bool:
    normalized = signal_name.upper()
    return any(token in normalized for token in WAKEUP_SIGNAL_TOKENS)


def _derive_pin_constraints(
    *,
    package_pads: tuple[PackagePad, ...],
    pins: tuple[PinDefinition, ...],
    provenance: Provenance,
) -> tuple[PinConstraint, ...]:
    pin_names = {pin.name for pin in pins}
    constraints: list[PinConstraint] = []
    seen_ids: set[str] = set()

    for pad in package_pads:
        if pad.bonded_pin is None or pad.bonded_pin not in pin_names:
            continue
        if pad.pad_kind == "io":
            continue
        _add_pin_constraint(
            constraints=constraints,
            seen_ids=seen_ids,
            pin=pad.bonded_pin,
            kind=pad.pad_kind,
            value=pad.position_label,
            provenance=provenance,
        )

    for pin in pins:
        non_gpio_signals = _non_gpio_signals(pin)
        if not non_gpio_signals:
            continue

        analog_signals = tuple(
            signal
            for signal in non_gpio_signals
            if signal.peripheral is not None
            and _infer_ip_metadata(signal.peripheral)[0] in ANALOG_IP_NAMES
        )
        if analog_signals:
            analog_kind = (
                "analog-only" if len(analog_signals) == len(non_gpio_signals) else "analog-capable"
            )
            _add_pin_constraint(
                constraints=constraints,
                seen_ids=seen_ids,
                pin=pin.name,
                kind=analog_kind,
                value=",".join(
                    sorted(
                        {
                            signal.signal.lower()
                            for signal in analog_signals
                            if signal.signal is not None
                        }
                    )
                )
                or None,
                provenance=provenance,
            )

        signal_tokens = _signal_tokens(pin)
        wakeup_signals = tuple(
            sorted({signal for signal in signal_tokens if _is_wakeup_signal(signal)})
        )
        if wakeup_signals:
            _add_pin_constraint(
                constraints=constraints,
                seen_ids=seen_ids,
                pin=pin.name,
                kind="wakeup-capable",
                value=",".join(wakeup_signals),
                provenance=provenance,
            )

        debug_signals = tuple(
            sorted({signal for signal in signal_tokens if _is_debug_signal(signal)})
        )
        if debug_signals:
            debug_kind = (
                "debug-only"
                if all(
                    signal.signal is not None and _is_debug_signal(signal.signal)
                    for signal in non_gpio_signals
                )
                else "debug-shared"
            )
            _add_pin_constraint(
                constraints=constraints,
                seen_ids=seen_ids,
                pin=pin.name,
                kind=debug_kind,
                value=",".join(debug_signals),
                provenance=provenance,
            )

    return tuple(sorted(constraints, key=lambda item: item.constraint_id))


def _peripheral_patch_map(
    patch: DevicePatch,
) -> dict[str, PeripheralPatch]:
    return {peripheral.name: peripheral for peripheral in patch.peripherals}


def _filter_clock_patch_descriptors(
    *,
    patch: DevicePatch,
    peripheral_names: set[str],
) -> tuple[
    tuple[ClockNodePatch, ...],
    tuple[ClockSelectorPatch, ...],
    tuple[ClockGatePatch, ...],
    tuple[ResetPatch, ...],
    tuple[PeripheralClockBindingPatch, ...],
]:
    clock_gates = tuple(
        gate
        for gate in patch.clock_gates
        if gate.peripheral is None or gate.peripheral in peripheral_names
    )
    resets = tuple(
        reset
        for reset in patch.resets
        if reset.peripheral is None or reset.peripheral in peripheral_names
    )
    bindings = tuple(
        binding
        for binding in patch.peripheral_clock_bindings
        if binding.peripheral in peripheral_names
    )
    selector_ids = {
        selector_id
        for selector_id in (
            *(node.selector for node in patch.clock_nodes),
            *(binding.selector_id for binding in bindings),
        )
        if selector_id is not None
    }
    clock_selectors = tuple(
        selector for selector in patch.clock_selectors if selector.selector_id in selector_ids
    )
    referenced_nodes = {"clock-root"}
    referenced_nodes.update(
        node_id
        for node_id in (
            *(gate.parent_node for gate in clock_gates),
            *(
                parent_option
                for selector in clock_selectors
                for parent_option in selector.parent_options
            ),
        )
        if node_id is not None
    )
    clock_nodes = tuple(
        node
        for node in patch.clock_nodes
        if node.node_id in referenced_nodes or node.selector in selector_ids
    )
    return clock_nodes, clock_selectors, clock_gates, resets, bindings


def _peripheral_to_ir(
    *,
    peripheral_name: str,
    base_address: int,
    patch_metadata: PeripheralPatch | None,
    ip_version: str | None,
    provenance: Provenance,
) -> PeripheralInstance:
    ip_name, instance = _infer_ip_metadata(peripheral_name)
    effective_ip_version = ip_version
    if effective_ip_version is None and patch_metadata is not None:
        effective_ip_version = patch_metadata.ip_version
    return PeripheralInstance(
        name=peripheral_name,
        ip_name=ip_name,
        ip_version=effective_ip_version,
        backend_schema_id=None,
        instance=instance,
        base_address=base_address,
        rcc_enable_signal=None if patch_metadata is None else patch_metadata.rcc_enable_signal,
        rcc_reset_signal=None if patch_metadata is None else patch_metadata.rcc_reset_signal,
        provenance=provenance,
    )


def _register_to_ir(
    *,
    peripheral_name: str,
    raw_register: RawRegister,
    provenance: Provenance,
) -> RegisterDescriptor:
    return RegisterDescriptor(
        register_id=f"register:{_sanitize_token(peripheral_name)}:{_sanitize_token(raw_register.name)}",
        peripheral=peripheral_name,
        name=raw_register.name,
        offset_bytes=raw_register.offset_bytes,
        access=raw_register.access,
        size_bits=raw_register.size_bits,
        provenance=provenance,
    )


def _register_field_to_ir(
    *,
    peripheral_name: str,
    register_id: str,
    register_name: str,
    raw_field: RawRegisterField,
    provenance: Provenance,
) -> RegisterFieldDescriptor:
    return RegisterFieldDescriptor(
        field_id=(
            "field:"
            f"{_sanitize_token(peripheral_name)}:"
            f"{_sanitize_token(register_name)}:"
            f"{_sanitize_token(raw_field.name)}"
        ),
        register_id=register_id,
        peripheral=peripheral_name,
        register_name=register_name,
        name=raw_field.name,
        bit_offset=raw_field.bit_offset,
        bit_width=raw_field.bit_width,
        access=raw_field.access,
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
        channel_index=request.channel_index,
        request_value=request.request_value,
        channel_selector=request.channel_selector,
    )


def _dma_controller_to_ir(
    controller: DmaControllerPatch,
    provenance: Provenance,
) -> DmaControllerDescriptor:
    return DmaControllerDescriptor(
        controller=controller.controller,
        version=controller.version,
        channel_count=controller.channel_count,
        request_count=None,
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


def _registers_from_raw_peripherals(
    raw_peripherals: tuple[RawPeripheral, ...],
    *,
    provenance: Provenance,
) -> tuple[RegisterDescriptor, ...]:
    registers: list[RegisterDescriptor] = []
    for peripheral in raw_peripherals:
        canonical_peripheral = _canonical_peripheral_name(peripheral.name)
        seen_offsets: set[int] = set()
        for raw_register in sorted(
            peripheral.registers,
            key=lambda item: (item.offset_bytes, item.name),
        ):
            if raw_register.offset_bytes in seen_offsets:
                continue
            seen_offsets.add(raw_register.offset_bytes)
            registers.append(
                _register_to_ir(
                    peripheral_name=canonical_peripheral,
                    raw_register=raw_register,
                    provenance=provenance,
                )
            )
    return tuple(registers)


def _merge_patch_registers(
    raw_peripherals: tuple[RawPeripheral, ...],
    *,
    patch_registers: tuple[RegisterPatch, ...] = (),
) -> tuple[RawPeripheral, ...]:
    if patch_registers == ():
        return raw_peripherals

    by_name: dict[str, RawPeripheral] = {}
    order: list[str] = []
    for peripheral in raw_peripherals:
        canonical_name = _canonical_peripheral_name(peripheral.name)
        if canonical_name in by_name:
            continue
        by_name[canonical_name] = RawPeripheral(
            name=canonical_name,
            base_address=peripheral.base_address,
            registers=peripheral.registers,
        )
        order.append(canonical_name)

    for patch_register in patch_registers:
        canonical_name = _canonical_peripheral_name(patch_register.peripheral)
        raw_register = RawRegister(
            name=patch_register.name,
            offset_bytes=patch_register.offset_bytes,
            access=patch_register.access,
            size_bits=patch_register.size_bits,
        )
        existing = by_name.get(canonical_name)
        if existing is None:
            if patch_register.base_address is None:
                raise StageExecutionError(
                    "Patch register for missing peripheral requires base_address: "
                    f"{patch_register.peripheral}.{patch_register.name}"
                )
            by_name[canonical_name] = RawPeripheral(
                name=canonical_name,
                base_address=patch_register.base_address,
                registers=(raw_register,),
            )
            order.append(canonical_name)
            continue
        if (
            patch_register.base_address is not None
            and patch_register.base_address != existing.base_address
        ):
            raise StageExecutionError(
                "Patch register base_address mismatch for peripheral "
                f"{patch_register.peripheral}: "
                f"{patch_register.base_address:#x} != {existing.base_address:#x}"
            )
        if any(
            register.name.upper() == patch_register.name.upper()
            or register.offset_bytes == patch_register.offset_bytes
            for register in existing.registers
        ):
            continue
        by_name[canonical_name] = RawPeripheral(
            name=existing.name,
            base_address=existing.base_address,
            registers=tuple(
                sorted(
                    (*existing.registers, raw_register),
                    key=lambda item: (item.offset_bytes, item.name),
                )
            ),
        )

    return tuple(by_name[name] for name in order)


def _register_fields_from_raw_peripherals(
    raw_peripherals: tuple[RawPeripheral, ...],
    *,
    provenance: Provenance,
    patch_fields: tuple[RegisterFieldPatch, ...] = (),
    patch_provenance: Provenance | None = None,
) -> tuple[RegisterFieldDescriptor, ...]:
    fields: list[RegisterFieldDescriptor] = []
    seen_keys: set[tuple[str, str, str]] = set()
    register_keys: set[tuple[str, str]] = set()
    for peripheral in raw_peripherals:
        canonical_peripheral = _canonical_peripheral_name(peripheral.name)
        seen_offsets: set[int] = set()
        for raw_register in sorted(
            peripheral.registers,
            key=lambda item: (item.offset_bytes, item.name),
        ):
            if raw_register.offset_bytes in seen_offsets:
                continue
            seen_offsets.add(raw_register.offset_bytes)
            register = _register_to_ir(
                peripheral_name=canonical_peripheral,
                raw_register=raw_register,
                provenance=provenance,
            )
            register_keys.add((canonical_peripheral, raw_register.name))
            seen_field_names: set[str] = set()
            for raw_field in sorted(
                raw_register.fields,
                key=lambda item: (item.bit_offset, item.name),
            ):
                if raw_field.name in seen_field_names:
                    continue
                seen_field_names.add(raw_field.name)
                seen_keys.add((canonical_peripheral, raw_register.name, raw_field.name))
                fields.append(
                    _register_field_to_ir(
                        peripheral_name=canonical_peripheral,
                        register_id=register.register_id,
                        register_name=raw_register.name,
                        raw_field=raw_field,
                        provenance=provenance,
                    )
                )
    effective_patch_provenance = patch_provenance or provenance
    for patch_field in patch_fields:
        register_key = (patch_field.peripheral, patch_field.register_name)
        field_key = (*register_key, patch_field.name)
        if field_key in seen_keys:
            continue
        if register_key not in register_keys:
            continue
        seen_keys.add(field_key)
        fields.append(
            RegisterFieldDescriptor(
                field_id=(
                    "field:"
                    f"{_sanitize_token(patch_field.peripheral)}:"
                    f"{_sanitize_token(patch_field.register_name)}:"
                    f"{_sanitize_token(patch_field.name)}"
                ),
                register_id=(
                    "register:"
                    f"{_sanitize_token(patch_field.peripheral)}:"
                    f"{_sanitize_token(patch_field.register_name)}"
                ),
                peripheral=patch_field.peripheral,
                register_name=patch_field.register_name,
                name=patch_field.name,
                bit_offset=patch_field.bit_offset,
                bit_width=patch_field.bit_width,
                access=patch_field.access,
                provenance=effective_patch_provenance,
            )
        )
    return tuple(fields)


def build_canonical_ir(
    raw: RawDeviceDocument,
    patch: DevicePatch,
    pin_data: RawPinDataDocument,
    ip_version_table: dict[str, str] | None = None,
    *,
    vendor: str = BOOTSTRAP_VENDOR,
    family: str = BOOTSTRAP_FAMILY,
    svd_source_id: str = "cmsis-svd-data",
    pin_source_id: str = "stm32-open-pin-data",
    patch_source_id: str = "bootstrap-patch",
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
        source_id=svd_source_id,
        source_path=patch.svd_file,
        patch_ids=patch_ids,
    )
    pin_provenance = Provenance(
        source_id=pin_source_id,
        source_path=patch.pin_data_file,
        patch_ids=patch_ids,
    )
    patch_provenance = Provenance(
        source_id=patch_source_id,
        source_path=f"patches/{vendor}/{family}/devices/{patch.device}.json",
        patch_ids=patch_ids,
    )
    raw_peripherals = _merge_patch_registers(raw.peripherals, patch_registers=patch.registers)
    peripheral_patches = _peripheral_patch_map(patch)
    discovered_peripherals = {
        _canonical_peripheral_name(peripheral.name) for peripheral in raw_peripherals
    }
    (
        clock_nodes,
        clock_selectors,
        clock_gates,
        resets,
        peripheral_clock_bindings,
    ) = _filter_clock_patch_descriptors(
        patch=patch,
        peripheral_names=discovered_peripherals,
    )
    allowed_signal_peripherals = {
        peripheral.name
        for peripheral in patch.peripherals
        if peripheral.rcc_enable_signal is not None
    }
    pins = _build_pins_from_source(
        pin_data=pin_data,
        discovered_peripherals=discovered_peripherals,
        allowed_signal_peripherals=allowed_signal_peripherals,
        provenance=pin_provenance,
    )
    package_pads = tuple(
        _package_pad_to_ir(
            raw_pad,
            package_name=patch.package,
            provenance=pin_provenance,
        )
        for raw_pad in pin_data.package_pads
    )
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
        registers=_registers_from_raw_peripherals(raw_peripherals, provenance=svd_provenance),
        register_fields=_register_fields_from_raw_peripherals(
            raw_peripherals,
            provenance=svd_provenance,
            patch_fields=patch.register_fields,
            patch_provenance=patch_provenance,
        ),
        pins=pins,
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
            for peripheral in raw_peripherals
        ),
        interrupts=_normalize_interrupts(raw.interrupts, provenance=svd_provenance),
        dma_controllers=tuple(
            _dma_controller_to_ir(controller, patch_provenance)
            for controller in patch.dma_controllers
        ),
        dma_requests=tuple(
            _dma_request_to_ir(request, patch_provenance) for request in patch.dma_requests
        ),
        provenance=pin_provenance,
        package_pads=package_pads,
        pin_constraints=_derive_pin_constraints(
            package_pads=package_pads,
            pins=pins,
            provenance=pin_provenance,
        ),
        clock_nodes=tuple(_clock_node_to_ir(node, patch_provenance) for node in clock_nodes),
        clock_selectors=tuple(
            _clock_selector_to_ir(selector, patch_provenance) for selector in clock_selectors
        ),
        clock_gates=tuple(_clock_gate_to_ir(gate, patch_provenance) for gate in clock_gates),
        resets=tuple(_reset_to_ir(reset, patch_provenance) for reset in resets),
        system_clock_profiles=tuple(
            _system_clock_profile_to_ir(profile, patch_provenance)
            for profile in patch.system_clock_profiles
        ),
        peripheral_clock_bindings=tuple(
            _peripheral_clock_binding_to_ir(binding, patch_provenance)
            for binding in peripheral_clock_bindings
        ),
    )


def _build_st_device_ir(
    *,
    execution_context: ExecutionContext,
    device_name: str,
    vendor: str,
    family: str,
) -> CanonicalDeviceIR:
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
    return build_canonical_ir(
        raw,
        patch,
        pin_data,
        ip_version_table,
        vendor=vendor,
        family=family,
    )


def _build_microchip_device_ir(
    *,
    execution_context: ExecutionContext,
    device_name: str,
    vendor: str,
    family: str,
) -> CanonicalDeviceIR:
    patch = load_device_patch(execution_context, device_name, vendor=vendor, family=family)
    selected = select_device_files(execution_context, device_name, vendor=vendor, family=family)
    atdf_path = resolve_atdf_path(execution_context, device_name, vendor=vendor, family=family)
    raw = parse_raw_device_document(
        resolve_microchip_svd_path(execution_context, device_name, vendor=vendor, family=family)
    )
    pin_data = parse_microchip_pin_data_document(atdf_path=atdf_path, package_name=patch.package)
    effective_patch = merge_source_patch(
        patch,
        selected=selected,
        source_memories=parse_microchip_memory_patches(atdf_path),
        source_peripherals=parse_microchip_peripheral_patches(atdf_path),
        source_dma_requests=parse_microchip_dma_request_patches(atdf_path),
        pin_count=pin_data.package_pin_count or patch.pin_count,
    )
    ip_version_table = parse_microchip_ip_version_table(atdf_path)
    return build_canonical_ir(
        raw,
        effective_patch,
        pin_data,
        ip_version_table,
        vendor=vendor,
        family=family,
        svd_source_id="microchip-dfp-extract",
        pin_source_id="microchip-dfp-extract",
    )


def _nxp_signal_to_ir(
    *,
    signal_name: str,
    af_number: int,
    discovered_peripherals: set[str],
    provenance: Provenance,
) -> PinSignal | None:
    """Convert one NXP IOMUXC signal name into a canonical PinSignal."""
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


def _build_nxp_pins(
    *,
    iomuxc_entries: tuple[NxpIomuxcEntry, ...],
    discovered_peripherals: set[str],
    provenance: Provenance,
) -> tuple[PinDefinition, ...]:
    """Build canonical PinDefinition tuples from parsed NXP IOMUXC entries."""
    pad_groups: dict[str, list[NxpIomuxcEntry]] = {}
    for entry in iomuxc_entries:
        pad_groups.setdefault(entry.pad_name, []).append(entry)

    pins: list[PinDefinition] = []
    for pad_name, entries in sorted(pad_groups.items()):
        number_match = NXP_PAD_NUMBER_PATTERN.search(pad_name)
        if number_match is None:
            continue
        number = int(number_match.group(1))

        signals: list[PinSignal] = []
        seen_keys: set[tuple[str | None, str | None, str | None, int | None]] = set()
        for entry in sorted(entries, key=lambda e: e.mux_mode):
            signal = _nxp_signal_to_ir(
                signal_name=entry.signal_name,
                af_number=entry.mux_mode,
                discovered_peripherals=discovered_peripherals,
                provenance=provenance,
            )
            if signal is None:
                continue
            key = (signal.function, signal.peripheral, signal.signal, signal.af_number)
            if key in seen_keys:
                continue
            seen_keys.add(key)
            signals.append(signal)

        if not signals:
            continue

        pins.append(
            PinDefinition(
                name=pad_name,
                port=None,
                number=number,
                signals=tuple(signals),
                provenance=provenance,
            )
        )
    return tuple(pins)


def _build_nxp_package_pads(
    *,
    iomuxc_entries: tuple[NxpIomuxcEntry, ...],
    package_name: str,
    provenance: Provenance,
) -> tuple[PackagePad, ...]:
    pad_rows: dict[str, NxpIomuxcEntry] = {}
    for entry in iomuxc_entries:
        pad_rows.setdefault(entry.pad_name, entry)

    return tuple(
        PackagePad(
            pad_id=pad_name,
            package=package_name,
            position_label=pad_name,
            physical_index=None,
            pad_kind="io",
            bonded_pin=pad_name,
            provenance=provenance,
            bonding_state="bonded",
        )
        for pad_name, _entry in sorted(pad_rows.items())
    )


def build_nxp_canonical_ir(
    raw: RawDeviceDocument,
    patch: DevicePatch,
    iomuxc_entries: tuple[NxpIomuxcEntry, ...],
    *,
    vendor: str,
    family: str,
    svd_upstream_path: str | None = None,
    sdk_upstream_path: str | None = None,
    svd_source_id: str = NXP_SVD_SOURCE_ID,
    sdk_source_id: str = NXP_SDK_SOURCE_ID,
) -> CanonicalDeviceIR:
    """Build canonical IR by merging NXP mcux-soc-svd and mcux-sdk sources."""
    patch_ids: tuple[str, ...] = (
        (patch.family_patch_id, patch.patch_id)
        if patch.family_patch_id is not None
        else (patch.patch_id,)
    )
    svd_provenance = Provenance(
        source_id=svd_source_id,
        source_path=svd_upstream_path,
        patch_ids=patch_ids,
    )
    sdk_provenance = Provenance(
        source_id=sdk_source_id,
        source_path=sdk_upstream_path,
        patch_ids=patch_ids,
    )
    patch_provenance = Provenance(
        source_id="bootstrap-patch",
        source_path=f"patches/{vendor}/{family}/devices/{patch.device}.json",
        patch_ids=patch_ids,
    )
    raw_peripherals = _merge_patch_registers(raw.peripherals, patch_registers=patch.registers)
    peripheral_patches = _peripheral_patch_map(patch)
    discovered_peripherals = {_canonical_peripheral_name(p.name) for p in raw_peripherals}
    (
        clock_nodes,
        clock_selectors,
        clock_gates,
        resets,
        peripheral_clock_bindings,
    ) = _filter_clock_patch_descriptors(
        patch=patch,
        peripheral_names=discovered_peripherals,
    )
    # Only emit pin signals for peripherals that have clock-gate configuration.
    # This ensures referenced-peripherals-have-rcc-enable always passes for the
    # produced pin set, even when the upstream SVD contains many more peripherals
    # than the family patch covers.
    clock_configured_peripherals = {
        p.name for p in patch.peripherals if p.rcc_enable_signal is not None
    }
    pins = _build_nxp_pins(
        iomuxc_entries=iomuxc_entries,
        discovered_peripherals=discovered_peripherals & clock_configured_peripherals,
        provenance=sdk_provenance,
    )
    # Restrict package pads to only pads that produced at least one pin signal,
    # so the package-pads-reference-known-pins validation invariant is maintained.
    pin_names_with_signals = {pin.name for pin in pins}
    package_pads = tuple(
        pad
        for pad in _build_nxp_package_pads(
            iomuxc_entries=iomuxc_entries,
            package_name=patch.package,
            provenance=sdk_provenance,
        )
        if pad.bonded_pin in pin_names_with_signals
    )
    dedup_peripherals, peripheral_aliases = _deduplicate_raw_peripherals(
        raw_peripherals,
        preferred_names={
            *(_canonical_peripheral_name(p.name) for p in patch.peripherals),
            *(
                _canonical_peripheral_name(interrupt.peripheral)
                for interrupt in raw.interrupts
                if interrupt.peripheral is not None
            ),
        },
    )
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
        memories=tuple(_memory_to_ir(m, patch_provenance) for m in patch.memories),
        packages=(
            PackageDefinition(
                name=patch.package,
                pin_count=patch.pin_count,
                provenance=sdk_provenance,
            ),
        ),
        registers=_registers_from_raw_peripherals(dedup_peripherals, provenance=svd_provenance),
        register_fields=_register_fields_from_raw_peripherals(
            dedup_peripherals,
            provenance=svd_provenance,
            patch_fields=patch.register_fields,
            patch_provenance=patch_provenance,
        ),
        pins=pins,
        peripherals=tuple(
            _peripheral_to_ir(
                peripheral_name=_canonical_peripheral_name(p.name),
                base_address=p.base_address,
                patch_metadata=peripheral_patches.get(_canonical_peripheral_name(p.name)),
                ip_version=None,
                provenance=svd_provenance,
            )
            for p in dedup_peripherals
        ),
        interrupts=_normalize_interrupts(
            raw.interrupts,
            provenance=svd_provenance,
            peripheral_aliases=peripheral_aliases,
        ),
        dma_controllers=tuple(
            _dma_controller_to_ir(controller, patch_provenance)
            for controller in patch.dma_controllers
        ),
        dma_requests=tuple(_dma_request_to_ir(r, patch_provenance) for r in patch.dma_requests),
        provenance=sdk_provenance,
        package_pads=package_pads,
        pin_constraints=_derive_pin_constraints(
            package_pads=package_pads,
            pins=pins,
            provenance=sdk_provenance,
        ),
        clock_nodes=tuple(_clock_node_to_ir(node, patch_provenance) for node in clock_nodes),
        clock_selectors=tuple(
            _clock_selector_to_ir(selector, patch_provenance) for selector in clock_selectors
        ),
        clock_gates=tuple(_clock_gate_to_ir(gate, patch_provenance) for gate in clock_gates),
        resets=tuple(_reset_to_ir(reset, patch_provenance) for reset in resets),
        system_clock_profiles=tuple(
            _system_clock_profile_to_ir(profile, patch_provenance)
            for profile in patch.system_clock_profiles
        ),
        peripheral_clock_bindings=tuple(
            _peripheral_clock_binding_to_ir(binding, patch_provenance)
            for binding in peripheral_clock_bindings
        ),
    )


def _build_nxp_device_ir(
    *,
    execution_context: ExecutionContext,
    device_name: str,
    vendor: str,
    family: str,
) -> CanonicalDeviceIR:
    from alloy_codegen.sources.nxp_mcux import _upstream_name as nxp_upstream_name

    patch = load_device_patch(execution_context, device_name, vendor=vendor, family=family)
    upstream = nxp_upstream_name(device_name)
    svd_path = resolve_nxp_svd_path(execution_context, device_name, vendor=vendor, family=family)
    iomuxc_path = resolve_iomuxc_header_path(
        execution_context, device_name, vendor=vendor, family=family
    )
    raw = parse_raw_device_document(svd_path)
    iomuxc_entries = parse_iomuxc_entries(iomuxc_path)
    return build_nxp_canonical_ir(
        raw,
        patch,
        iomuxc_entries,
        vendor=vendor,
        family=family,
        svd_upstream_path=f"{upstream}/{upstream}.xml",
        sdk_upstream_path=f"devices/{upstream}/drivers/fsl_iomuxc.h",
    )


def _build_rp2040_pins(
    *,
    family_catalog: FamilyPatchCatalog,
    allowed_peripherals: set[str],
    package: str,
    provenance: Provenance,
) -> tuple[PinDefinition, ...]:
    """Build canonical PinDefinitions from RP2040 family catalog pin signals.

    Pins with no matching signals after filtering are silently skipped, matching
    the NXP pattern where pads with no signal assignments are excluded.  Pins
    whose ``packages`` list does not include *package* are also excluded, which
    lets board-level device entries (e.g. "pico") restrict the visible pin set
    to only those physically accessible on the board header.
    """
    signals_by_pin: dict[str, list[PinSignalPatch]] = {}
    for entry in family_catalog.pin_signals:
        if entry.signal.peripheral is None or entry.signal.peripheral in allowed_peripherals:
            signals_by_pin.setdefault(entry.pin_name, []).append(entry.signal)

    pins: list[PinDefinition] = []
    for pin_entry in sorted(family_catalog.pins, key=lambda p: p.number):
        # Skip pins not present in this package (e.g., board-internal GP23/GP24/GP29 on Pico).
        if pin_entry.packages and package not in pin_entry.packages:
            continue
        pin_signals = signals_by_pin.get(pin_entry.name, [])
        if not pin_signals:
            continue
        pins.append(
            PinDefinition(
                name=pin_entry.name,
                port=pin_entry.port,
                number=pin_entry.number,
                signals=tuple(_pin_signal_to_ir(sig, provenance) for sig in pin_signals),
                provenance=provenance,
            )
        )
    return tuple(pins)


def build_rp2040_canonical_ir(
    raw: RawDeviceDocument,
    patch: DevicePatch,
    family_catalog: FamilyPatchCatalog,
    *,
    vendor: str,
    family: str,
    svd_source_id: str = "pico-sdk",
) -> CanonicalDeviceIR:
    """Build canonical IR from pico-sdk SVD and RP2040 family patch catalog.

    Unlike STM32/Microchip paths there is no separate pin-data XML.  Pin
    signals come entirely from the family patch catalog, which encodes the
    RP2040 FUNCSEL table.  ADC analog inputs (GP26-GP29) have af_number=null
    by design; the validation layer exempts known analog peripheral classes
    from the alternate-functions-explicit rule.
    """
    patch_ids: tuple[str, ...] = (
        (patch.family_patch_id, patch.patch_id)
        if patch.family_patch_id is not None
        else (patch.patch_id,)
    )
    svd_provenance = Provenance(
        source_id=svd_source_id,
        source_path=patch.svd_file,
        patch_ids=patch_ids,
    )
    patch_provenance = Provenance(
        source_id="bootstrap-patch",
        source_path=f"patches/{vendor}/{family}/devices/{patch.device}.json",
        patch_ids=patch_ids,
    )
    raw_peripherals = _merge_patch_registers(raw.peripherals, patch_registers=patch.registers)
    peripheral_patches = _peripheral_patch_map(patch)
    discovered_peripherals = {_canonical_peripheral_name(p.name) for p in raw_peripherals}
    (
        clock_nodes,
        clock_selectors,
        clock_gates,
        resets,
        peripheral_clock_bindings,
    ) = _filter_clock_patch_descriptors(patch=patch, peripheral_names=discovered_peripherals)

    # Emit pin signals only for peripherals that have rcc_enable_signal configured
    # (i.e., UART0/1, SPI0/1, I2C0/1, ADC — not PIO, TIMER, WATCHDOG, etc.).
    # This ensures the referenced-peripherals-have-rcc-enable validation passes.
    rcc_enable_peripherals = {p.name for p in patch.peripherals if p.rcc_enable_signal is not None}
    pins = _build_rp2040_pins(
        family_catalog=family_catalog,
        allowed_peripherals=discovered_peripherals & rcc_enable_peripherals,
        package=patch.package,
        provenance=svd_provenance,
    )
    # RP2040 has no dedicated package-pad data source.  Derive package pads from
    # the set of pins that produced at least one signal (same pattern as NXP).
    # Only include pads for pins that belong to this package (respects board-level
    # restrictions such as the Pico's "pico" package excluding GP23/GP24/GP29).
    pin_names_with_signals = {pin.name for pin in pins}
    package_pads = tuple(
        PackagePad(
            pad_id=pin_entry.name,
            package=patch.package,
            position_label=pin_entry.name,
            physical_index=None,
            pad_kind="io",
            bonded_pin=pin_entry.name,
            provenance=svd_provenance,
            bonding_state="bonded",
        )
        for pin_entry in sorted(family_catalog.pins, key=lambda p: p.number)
        if pin_entry.name in pin_names_with_signals
        and (not pin_entry.packages or patch.package in pin_entry.packages)
    )
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
        memories=tuple(_memory_to_ir(m, patch_provenance) for m in patch.memories),
        packages=(
            PackageDefinition(
                name=patch.package,
                pin_count=patch.pin_count,
                provenance=svd_provenance,
            ),
        ),
        registers=_registers_from_raw_peripherals(raw_peripherals, provenance=svd_provenance),
        register_fields=_register_fields_from_raw_peripherals(
            raw_peripherals,
            provenance=svd_provenance,
            patch_fields=patch.register_fields,
            patch_provenance=patch_provenance,
        ),
        pins=pins,
        peripherals=tuple(
            _peripheral_to_ir(
                peripheral_name=_canonical_peripheral_name(p.name),
                base_address=p.base_address,
                patch_metadata=peripheral_patches.get(_canonical_peripheral_name(p.name)),
                ip_version=None,
                provenance=svd_provenance,
            )
            for p in raw_peripherals
        ),
        interrupts=_normalize_interrupts(raw.interrupts, provenance=svd_provenance),
        dma_controllers=tuple(
            _dma_controller_to_ir(ctrl, patch_provenance) for ctrl in patch.dma_controllers
        ),
        dma_requests=tuple(_dma_request_to_ir(r, patch_provenance) for r in patch.dma_requests),
        provenance=svd_provenance,
        package_pads=package_pads,
        pin_constraints=_derive_pin_constraints(
            package_pads=package_pads,
            pins=pins,
            provenance=svd_provenance,
        ),
        clock_nodes=tuple(_clock_node_to_ir(n, patch_provenance) for n in clock_nodes),
        clock_selectors=tuple(_clock_selector_to_ir(s, patch_provenance) for s in clock_selectors),
        clock_gates=tuple(_clock_gate_to_ir(g, patch_provenance) for g in clock_gates),
        resets=tuple(_reset_to_ir(r, patch_provenance) for r in resets),
        system_clock_profiles=tuple(
            _system_clock_profile_to_ir(p, patch_provenance) for p in patch.system_clock_profiles
        ),
        peripheral_clock_bindings=tuple(
            _peripheral_clock_binding_to_ir(b, patch_provenance) for b in peripheral_clock_bindings
        ),
    )


def _build_rp2040_device_ir(
    *,
    execution_context: ExecutionContext,
    device_name: str,
    vendor: str,
    family: str,
) -> CanonicalDeviceIR:
    patch = load_device_patch(execution_context, device_name, vendor=vendor, family=family)
    family_catalog = load_family_patch_catalog(execution_context, vendor=vendor, family=family)
    svd_path = resolve_pico_svd_path(execution_context, device_name, vendor=vendor, family=family)
    raw = parse_raw_device_document(svd_path)
    return build_rp2040_canonical_ir(
        raw,
        patch,
        family_catalog,
        vendor=vendor,
        family=family,
    )


def run(scope: PipelineScope, context: ExecutionContext | None = None) -> StageResult:
    """Run the bootstrap normalize stage."""
    execution_context = context or ExecutionContext.default()
    patch_result = run_patch(scope, execution_context)
    devices: list[CanonicalDeviceIR] = []
    vendor = patch_result.scope.resolved_vendor()
    family = patch_result.scope.resolved_family()
    for device_name in patch_result.scope.resolved_device_names():
        if vendor == "st":
            devices.append(
                _build_st_device_ir(
                    execution_context=execution_context,
                    device_name=device_name,
                    vendor=vendor,
                    family=family,
                )
            )
            continue
        if vendor == "microchip" and family == "same70":
            devices.append(
                _build_microchip_device_ir(
                    execution_context=execution_context,
                    device_name=device_name,
                    vendor=vendor,
                    family=family,
                )
            )
            continue
        if vendor == "nxp" and family == "imxrt1060":
            devices.append(
                _build_nxp_device_ir(
                    execution_context=execution_context,
                    device_name=device_name,
                    vendor=vendor,
                    family=family,
                )
            )
            continue
        if vendor == "raspberrypi" and family == "rp2040":
            devices.append(
                _build_rp2040_device_ir(
                    execution_context=execution_context,
                    device_name=device_name,
                    vendor=vendor,
                    family=family,
                )
            )
            continue
        raise StageExecutionError(f"Unsupported normalize path for {vendor}/{family}.")
    return StageResult(
        stage="normalize",
        scope=patch_result.scope,
        status="completed",
        payload=NormalizationBundle(
            source_manifest=patch_result.payload.source_manifest,
            patch_manifest=patch_result.payload.patch_manifest,
            devices=tuple(ensure_connector_descriptors(device) for device in devices),
        ),
    )
