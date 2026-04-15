"""Runtime-lite C++ emission helpers.

The runtime-lite contract is separate from the reflection-heavy generated
headers. It is intentionally shaped around compile-time traits and compact
operation packs so Alloy can consume it without family-wide table scans in the
hot path.
"""

from __future__ import annotations

from alloy_codegen.connector_model import canonical_peripheral_class
from alloy_codegen.ir.model import (
    CanonicalDeviceIR,
    ConnectionCandidate,
    DmaBindingDescriptor,
    DmaControllerDescriptor,
)
from alloy_codegen.reporting import EmittedArtifact

from .emission import (
    _collect_runtime_semantics_catalog,
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _enum_rows,
    _semantic_enum_map,
    _semantic_enum_ref,
    _std_array_lines,
)

RUNTIME_LITE_PERIPHERAL_CLASSES = frozenset(
    {"gpio", "uart", "spi", "i2c", "dma", "dma-router", "timer", "pwm", "adc", "dac"}
)
_RUNTIME_LITE_TIMING_CLASS_ALIASES = {
    "gpt": "timer",
    "pit": "timer",
}


def runtime_lite_peripheral_class_name(ip_name: str) -> str:
    class_name = canonical_peripheral_class(ip_name)
    return _RUNTIME_LITE_TIMING_CLASS_ALIASES.get(class_name, class_name)


def _runtime_lite_semantics_catalog(devices: tuple[CanonicalDeviceIR, ...]) -> dict[str, object]:
    catalog = dict(_collect_runtime_semantics_catalog(devices))
    peripheral_class_values = set(catalog["peripheral_class_enum_map"])
    peripheral_class_values.update(
        runtime_lite_peripheral_class_name(peripheral.ip_name)
        for device in devices
        for peripheral in device.peripherals
    )
    catalog["peripheral_class_enum_map"] = _semantic_enum_map(
        peripheral_class_values,
        prefix="class",
    )
    return catalog


def _runtime_generated_path(family_dir: str, name: str) -> str:
    return f"{family_dir}/generated/runtime/{name}"


def _device_runtime_generated_path(family_dir: str, device_name: str, name: str) -> str:
    return f"{family_dir}/generated/runtime/devices/{device_name}/{name}"


def _runtime_namespace_components(device: CanonicalDeviceIR) -> tuple[str, str, str, str]:
    return (
        _enum_identifier(device.identity.vendor).lower(),
        _enum_identifier(device.identity.family).lower(),
        "generated",
        "runtime",
    )


def _runtime_device_namespace_components(
    device: CanonicalDeviceIR,
) -> tuple[str, str, str, str, str, str]:
    return (
        *_runtime_namespace_components(device),
        "devices",
        _enum_identifier(device.identity.device),
    )


def _runtime_lite_startup_control_peripheral_names(device: CanonicalDeviceIR) -> set[str]:
    if not device.startup_descriptors:
        return set()

    family_key = (device.identity.vendor, device.identity.family)
    if family_key == ("microchip", "same70"):
        return {"WDT", "RSWDT"}
    return set()


def _runtime_lite_peripherals(device: CanonicalDeviceIR):
    startup_control_peripherals = _runtime_lite_startup_control_peripheral_names(device)
    return tuple(
        peripheral
        for peripheral in sorted(device.peripherals, key=lambda item: item.name)
        if runtime_lite_peripheral_class_name(peripheral.ip_name) in RUNTIME_LITE_PERIPHERAL_CLASSES
        or peripheral.name in startup_control_peripherals
    )


def _runtime_lite_peripheral_names(device: CanonicalDeviceIR) -> set[str]:
    return {peripheral.name for peripheral in _runtime_lite_peripherals(device)}


def _runtime_lite_candidates(device: CanonicalDeviceIR) -> tuple[ConnectionCandidate, ...]:
    runtime_peripherals = _runtime_lite_peripheral_names(device)
    return tuple(
        candidate
        for candidate in sorted(device.connection_candidates, key=lambda item: item.candidate_id)
        if candidate.peripheral in runtime_peripherals
    )


def _runtime_lite_operation_ids(device: CanonicalDeviceIR) -> set[str]:
    return {
        operation_id
        for candidate in _runtime_lite_candidates(device)
        for operation_id in candidate.operation_ids
    }


def _runtime_lite_groups(device: CanonicalDeviceIR):
    runtime_candidate_ids = {
        candidate.candidate_id for candidate in _runtime_lite_candidates(device)
    }
    runtime_peripherals = _runtime_lite_peripheral_names(device)
    return tuple(
        group
        for group in sorted(device.connection_groups, key=lambda item: item.group_id)
        if group.peripheral in runtime_peripherals
        and set(group.candidate_ids).issubset(runtime_candidate_ids)
    )


def _runtime_lite_dma_bindings(device: CanonicalDeviceIR) -> tuple[DmaBindingDescriptor, ...]:
    runtime_peripherals = _runtime_lite_peripheral_names(device)
    return tuple(
        binding
        for binding in sorted(
            device.dma_bindings,
            key=lambda item: (
                item.peripheral,
                item.signal or "",
                item.controller,
                item.request_line,
            ),
        )
        if binding.peripheral in runtime_peripherals
    )


def _runtime_lite_dma_controllers(device: CanonicalDeviceIR) -> tuple[DmaControllerDescriptor, ...]:
    controller_names = {binding.controller for binding in _runtime_lite_dma_bindings(device)}
    return tuple(
        controller
        for controller in sorted(device.dma_controllers, key=lambda item: item.controller)
        if controller.controller in controller_names
    )


def _clock_bindings_by_peripheral(device: CanonicalDeviceIR) -> dict[str, object]:
    runtime_peripherals = _runtime_lite_peripheral_names(device)
    return {
        binding.peripheral: binding
        for binding in device.peripheral_clock_bindings
        if binding.peripheral in runtime_peripherals
    }


def _runtime_lite_gate_ids(device: CanonicalDeviceIR) -> set[str]:
    return {
        binding.clock_gate_id
        for binding in _clock_bindings_by_peripheral(device).values()
        if binding.clock_gate_id is not None
    }


def _runtime_lite_reset_ids(device: CanonicalDeviceIR) -> set[str]:
    return {
        binding.reset_id
        for binding in _clock_bindings_by_peripheral(device).values()
        if binding.reset_id is not None
    }


def _runtime_lite_selector_ids(device: CanonicalDeviceIR) -> set[str]:
    return {
        binding.selector_id
        for binding in _clock_bindings_by_peripheral(device).values()
        if binding.selector_id is not None
    }


def _runtime_lite_system_clock_register_keys(
    device: CanonicalDeviceIR,
) -> set[tuple[str, str]]:
    if not device.system_clock_profiles:
        return set()
    family_key = (device.identity.vendor, device.identity.family)
    if family_key == ("st", "stm32g0"):
        return {
            ("RCC", "CR"),
            ("RCC", "CFGR"),
            ("RCC", "PLLCFGR"),
            ("FLASH", "ACR"),
        }
    if family_key == ("st", "stm32f4"):
        return {
            ("RCC", "CR"),
            ("RCC", "PLLCFGR"),
            ("RCC", "CFGR"),
            ("FLASH", "ACR"),
        }
    if family_key == ("microchip", "same70"):
        return {
            ("PMC", "CKGR_MOR"),
            ("PMC", "CKGR_PLLAR"),
            ("PMC", "MCKR"),
            ("PMC", "SR"),
            ("EFC", "EEFC_FMR"),
        }
    if family_key == ("nxp", "imxrt1060"):
        return {
            ("CCM", "CACRR"),
            ("CCM", "CBCDR"),
            ("CCM", "CBCMR"),
            ("CCM", "CDHIPR"),
            ("CCM_ANALOG", "PLL_ARM"),
            ("DCDC", "REG0"),
            ("DCDC", "REG3"),
        }
    return set()


def _runtime_lite_system_clock_field_keys(
    device: CanonicalDeviceIR,
) -> set[tuple[str, str, str]]:
    if not device.system_clock_profiles:
        return set()
    family_key = (device.identity.vendor, device.identity.family)
    if family_key == ("st", "stm32g0"):
        return {
            ("RCC", "CR", "HSION"),
            ("RCC", "CR", "HSIRDY"),
            ("RCC", "CR", "PLLON"),
            ("RCC", "CR", "PLLRDY"),
            ("RCC", "CFGR", "SW"),
            ("RCC", "CFGR", "SWS"),
            ("RCC", "PLLCFGR", "PLLSRC"),
            ("RCC", "PLLCFGR", "PLLM"),
            ("RCC", "PLLCFGR", "PLLN"),
            ("RCC", "PLLCFGR", "PLLREN"),
            ("RCC", "PLLCFGR", "PLLR"),
            ("FLASH", "ACR", "LATENCY"),
        }
    if family_key == ("st", "stm32f4"):
        return {
            ("RCC", "CR", "HSEON"),
            ("RCC", "CR", "HSERDY"),
            ("RCC", "CR", "PLLON"),
            ("RCC", "CR", "PLLRDY"),
            ("RCC", "PLLCFGR", "PLLM"),
            ("RCC", "PLLCFGR", "PLLN"),
            ("RCC", "PLLCFGR", "PLLP"),
            ("RCC", "PLLCFGR", "PLLSRC"),
            ("RCC", "PLLCFGR", "PLLQ"),
            ("RCC", "CFGR", "SW"),
            ("RCC", "CFGR", "SWS"),
            ("RCC", "CFGR", "HPRE"),
            ("RCC", "CFGR", "PPRE1"),
            ("RCC", "CFGR", "PPRE2"),
            ("FLASH", "ACR", "LATENCY"),
        }
    if family_key == ("microchip", "same70"):
        return {
            ("PMC", "CKGR_MOR", "MOSCXTEN"),
            ("PMC", "CKGR_MOR", "MOSCRCEN"),
            ("PMC", "CKGR_MOR", "MOSCRCF"),
            ("PMC", "CKGR_MOR", "MOSCXTST"),
            ("PMC", "CKGR_MOR", "KEY"),
            ("PMC", "CKGR_MOR", "MOSCSEL"),
            ("PMC", "CKGR_PLLAR", "DIVA"),
            ("PMC", "CKGR_PLLAR", "PLLACOUNT"),
            ("PMC", "CKGR_PLLAR", "MULA"),
            ("PMC", "CKGR_PLLAR", "ONE"),
            ("PMC", "MCKR", "CSS"),
            ("PMC", "MCKR", "PRES"),
            ("PMC", "MCKR", "MDIV"),
            ("PMC", "SR", "MOSCXTS"),
            ("PMC", "SR", "LOCKA"),
            ("PMC", "SR", "MCKRDY"),
            ("PMC", "SR", "MOSCSELS"),
            ("PMC", "SR", "MOSCRCS"),
            ("EFC", "EEFC_FMR", "FWS"),
        }
    if family_key == ("nxp", "imxrt1060"):
        return {
            ("CCM", "CACRR", "ARM_PODF"),
            ("CCM", "CBCDR", "IPG_PODF"),
            ("CCM", "CBCDR", "AHB_PODF"),
            ("CCM", "CBCDR", "PERIPH_CLK_SEL"),
            ("CCM", "CBCDR", "PERIPH_CLK2_PODF"),
            ("CCM", "CBCMR", "PERIPH_CLK2_SEL"),
            ("CCM", "CBCMR", "PRE_PERIPH_CLK_SEL"),
            ("CCM", "CDHIPR", "AHB_PODF_BUSY"),
            ("CCM", "CDHIPR", "PERIPH2_CLK_SEL_BUSY"),
            ("CCM", "CDHIPR", "PERIPH_CLK_SEL_BUSY"),
            ("CCM", "CDHIPR", "ARM_PODF_BUSY"),
            ("CCM_ANALOG", "PLL_ARM", "DIV_SELECT"),
            ("CCM_ANALOG", "PLL_ARM", "POWERDOWN"),
            ("CCM_ANALOG", "PLL_ARM", "ENABLE"),
            ("CCM_ANALOG", "PLL_ARM", "BYPASS"),
            ("CCM_ANALOG", "PLL_ARM", "LOCK"),
            ("DCDC", "REG0", "STS_DC_OK"),
            ("DCDC", "REG3", "TRG"),
        }
    return set()


def _runtime_lite_register_ids(device: CanonicalDeviceIR) -> set[str]:
    runtime_peripherals = _runtime_lite_peripheral_names(device)
    operation_ids = _runtime_lite_operation_ids(device)
    gate_ids = _runtime_lite_gate_ids(device)
    reset_ids = _runtime_lite_reset_ids(device)
    selector_ids = _runtime_lite_selector_ids(device)
    system_clock_register_keys = _runtime_lite_system_clock_register_keys(device)

    gate_by_id = {gate.gate_id: gate for gate in device.clock_gates if gate.gate_id in gate_ids}
    reset_by_id = {reset.reset_id: reset for reset in device.resets if reset.reset_id in reset_ids}
    selector_by_id = {
        selector.selector_id: selector
        for selector in device.clock_selectors
        if selector.selector_id in selector_ids
    }
    operation_by_id = {
        operation.operation_id: operation
        for operation in device.route_operations
        if operation.operation_id in operation_ids
    }
    register_ids = {
        register.register_id
        for register in device.registers
        if register.peripheral in runtime_peripherals
        or (register.peripheral, register.name.upper()) in system_clock_register_keys
    }
    register_ids.update(
        gate.register_id for gate in gate_by_id.values() if gate.register_id is not None
    )
    register_ids.update(
        reset.register_id for reset in reset_by_id.values() if reset.register_id is not None
    )
    register_ids.update(
        selector.register_id
        for selector in selector_by_id.values()
        if selector.register_id is not None
    )
    register_ids.update(
        operation.register_id
        for operation in operation_by_id.values()
        if operation.register_id is not None
    )
    return register_ids


def _runtime_lite_field_ids(device: CanonicalDeviceIR) -> set[str]:
    runtime_peripherals = _runtime_lite_peripheral_names(device)
    operation_ids = _runtime_lite_operation_ids(device)
    gate_ids = _runtime_lite_gate_ids(device)
    reset_ids = _runtime_lite_reset_ids(device)
    selector_ids = _runtime_lite_selector_ids(device)
    system_clock_field_keys = _runtime_lite_system_clock_field_keys(device)

    gate_by_id = {gate.gate_id: gate for gate in device.clock_gates if gate.gate_id in gate_ids}
    reset_by_id = {reset.reset_id: reset for reset in device.resets if reset.reset_id in reset_ids}
    selector_by_id = {
        selector.selector_id: selector
        for selector in device.clock_selectors
        if selector.selector_id in selector_ids
    }
    operation_by_id = {
        operation.operation_id: operation
        for operation in device.route_operations
        if operation.operation_id in operation_ids
    }
    field_ids = {
        register_field.field_id
        for register_field in device.register_fields
        if register_field.peripheral in runtime_peripherals
        or (
            register_field.peripheral,
            register_field.register_name.upper(),
            register_field.name.upper(),
        )
        in system_clock_field_keys
    }
    field_ids.update(
        gate.register_field_id for gate in gate_by_id.values() if gate.register_field_id is not None
    )
    field_ids.update(
        reset.register_field_id
        for reset in reset_by_id.values()
        if reset.register_field_id is not None
    )
    field_ids.update(
        selector.register_field_id
        for selector in selector_by_id.values()
        if selector.register_field_id is not None
    )
    field_ids.update(
        operation.register_field_id
        for operation in operation_by_id.values()
        if operation.register_field_id is not None
    )
    return field_ids


def _runtime_lite_register_rows(device: CanonicalDeviceIR):
    register_ids = _runtime_lite_register_ids(device)
    return tuple(
        register
        for register in sorted(
            device.registers,
            key=lambda item: (item.peripheral, item.offset_bytes, item.name),
        )
        if register.register_id in register_ids
    )


def _runtime_lite_register_field_rows(device: CanonicalDeviceIR):
    field_ids = _runtime_lite_field_ids(device)
    return tuple(
        register_field
        for register_field in sorted(
            device.register_fields,
            key=lambda item: (
                item.peripheral,
                item.register_name,
                item.bit_offset,
                item.name,
            ),
        )
        if register_field.field_id in field_ids
    )


def _runtime_lite_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    paths = [_runtime_generated_path(family_dir, "types.hpp")]
    for device in devices:
        device_name = device.identity.device
        paths.extend(
            (
                _device_runtime_generated_path(family_dir, device_name, "peripheral_instances.hpp"),
                _device_runtime_generated_path(family_dir, device_name, "pins.hpp"),
                _device_runtime_generated_path(family_dir, device_name, "registers.hpp"),
                _device_runtime_generated_path(family_dir, device_name, "register_fields.hpp"),
                _device_runtime_generated_path(family_dir, device_name, "clock_bindings.hpp"),
                _device_runtime_generated_path(family_dir, device_name, "system_clock.hpp"),
                _device_runtime_generated_path(family_dir, device_name, "dma_bindings.hpp"),
                _device_runtime_generated_path(family_dir, device_name, "routes.hpp"),
            )
        )
    return tuple(paths)


def emit_runtime_lite_types_header(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    if not devices:
        raise ValueError("Runtime-lite emission requires at least one device.")
    semantics_catalog = _runtime_lite_semantics_catalog(devices)
    first_device = devices[0]
    enum_specs = (
        ("BackendSchemaId", semantics_catalog["backend_schema_enum_map"]),
        ("PeripheralClassId", semantics_catalog["peripheral_class_enum_map"]),
        ("SignalId", semantics_catalog["signal_enum_map"]),
        ("PortId", semantics_catalog["port_enum_map"]),
        ("AccessKindId", semantics_catalog["access_kind_enum_map"]),
        ("RouteKindId", semantics_catalog["route_kind_enum_map"]),
        ("OperationKindId", semantics_catalog["operation_kind_enum_map"]),
        ("OperationSubjectKindId", semantics_catalog["operation_subject_kind_enum_map"]),
        ("ActiveLevelId", semantics_catalog["active_level_enum_map"]),
    )
    body_lines: list[str] = []
    for enum_name, enum_map in enum_specs:
        body_lines.extend(
            [
                f"enum class {enum_name} : std::uint16_t {{",
                "  none,",
                *_enum_rows(enum_map, empty_identifier=None),
                "};",
                "",
            ]
        )
    namespace_block = _cpp_namespace_block(
        _runtime_namespace_components(first_device), "\n".join(body_lines)
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <cstdint>",
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(path=_runtime_generated_path(family_dir, "types.hpp"), content=content)


def emit_runtime_lite_peripheral_instances_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    semantics_catalog = _runtime_lite_semantics_catalog((device,))
    runtime_peripherals = _runtime_lite_peripherals(device)
    bindings = _clock_bindings_by_peripheral(device)
    gate_enum_map = {
        gate_id: _enum_identifier(gate_id) for gate_id in sorted(_runtime_lite_gate_ids(device))
    }
    reset_enum_map = {
        reset_id: _enum_identifier(reset_id) for reset_id in sorted(_runtime_lite_reset_ids(device))
    }
    selector_enum_map = {
        selector_id: _enum_identifier(selector_id)
        for selector_id in sorted(_runtime_lite_selector_ids(device))
    }
    peripheral_enum_rows = [
        f"  {_enum_identifier(peripheral.name)}," for peripheral in runtime_peripherals
    ]
    trait_lines: list[str] = [
        "template<PeripheralId Id>",
        "struct PeripheralInstanceTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::none;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr int kInstance = -1;",
        "  static constexpr std::uintptr_t kBaseAddress = 0u;",
        "  static constexpr ClockGateId kClockGateId = ClockGateId::none;",
        "  static constexpr ResetId kResetId = ResetId::none;",
        "  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;",
        "};",
        "",
    ]
    peripheral_id_rows: list[str] = []
    for peripheral in runtime_peripherals:
        binding = bindings.get(peripheral.name)
        peripheral_id = _enum_identifier(peripheral.name)
        trait_name = f"PeripheralInstanceTraits<PeripheralId::{peripheral_id}>"
        clock_gate_ref = (
            "ClockGateId::none"
            if binding is None or binding.clock_gate_id is None
            else f"ClockGateId::{gate_enum_map[binding.clock_gate_id]}"
        )
        reset_ref = (
            "ResetId::none"
            if binding is None or binding.reset_id is None
            else f"ResetId::{reset_enum_map[binding.reset_id]}"
        )
        selector_ref = (
            "ClockSelectorId::none"
            if binding is None or binding.selector_id is None
            else f"ClockSelectorId::{selector_enum_map[binding.selector_id]}"
        )
        peripheral_base_address = f"0x{peripheral.base_address:08X}u"
        trait_lines.extend(
            [
                "template<>",
                f"struct {trait_name} {{",
                "  static constexpr bool kPresent = true;",
                "  static constexpr PeripheralClassId kPeripheralClassId = "
                + _semantic_enum_ref(
                    "PeripheralClassId",
                    semantics_catalog["peripheral_class_enum_map"],
                    runtime_lite_peripheral_class_name(peripheral.ip_name),
                )
                + ";",
                "  static constexpr BackendSchemaId kSchemaId = "
                + _semantic_enum_ref(
                    "BackendSchemaId",
                    semantics_catalog["backend_schema_enum_map"],
                    peripheral.backend_schema_id,
                )
                + ";",
                f"  static constexpr int kInstance = {peripheral.instance};",
                f"  static constexpr std::uintptr_t kBaseAddress = {peripheral_base_address};",
                f"  static constexpr ClockGateId kClockGateId = {clock_gate_ref};",
                f"  static constexpr ResetId kResetId = {reset_ref};",
                f"  static constexpr ClockSelectorId kSelectorId = {selector_ref};",
                "};",
                "",
            ]
        )
        peripheral_id_rows.append(f"  PeripheralId::{peripheral_id},")
    body_lines = [
        "enum class PeripheralId : std::uint16_t {",
        "  none,",
        *peripheral_enum_rows,
        "};",
        "",
        "enum class ClockGateId : std::uint16_t {",
        "  none,",
        *_enum_rows(gate_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class ResetId : std::uint16_t {",
        "  none,",
        *_enum_rows(reset_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class ClockSelectorId : std::uint16_t {",
        "  none,",
        *_enum_rows(selector_enum_map, empty_identifier=None),
        "};",
        "",
        *trait_lines,
        *_std_array_lines(
            type_name="PeripheralId",
            variable_name="kRuntimePeripherals",
            row_lines=peripheral_id_rows,
        ),
    ]
    namespace_block = _cpp_namespace_block(
        _runtime_device_namespace_components(device),
        "\n".join(body_lines),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../types.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            "peripheral_instances.hpp",
        ),
        content=content,
    )


def emit_runtime_lite_pins_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    pins = sorted(device.pins, key=lambda item: item.name)
    pin_enum_rows = [f"  {_enum_identifier(pin.name)}," for pin in pins]
    trait_lines: list[str] = [
        "template<PinId Id>",
        "struct PinTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr PortId kPortId = PortId::none;",
        "  static constexpr int kPinNumber = -1;",
        "};",
        "",
    ]
    pin_rows = []
    for pin in pins:
        trait_lines.extend(
            [
                "template<>",
                f"struct PinTraits<PinId::{_enum_identifier(pin.name)}> {{",
                "  static constexpr bool kPresent = true;",
                "  static constexpr PortId kPortId = "
                + _semantic_enum_ref(
                    "PortId",
                    semantics_catalog["port_enum_map"],
                    pin.port,
                )
                + ";",
                f"  static constexpr int kPinNumber = {pin.number};",
                "};",
                "",
            ]
        )
        pin_rows.append(f"  PinId::{_enum_identifier(pin.name)},")
    body_lines = [
        "enum class PinId : std::uint16_t {",
        "  none,",
        *pin_enum_rows,
        "};",
        "",
        *trait_lines,
        *_std_array_lines(
            type_name="PinId",
            variable_name="kPins",
            row_lines=pin_rows,
        ),
    ]
    namespace_block = _cpp_namespace_block(
        _runtime_device_namespace_components(device),
        "\n".join(body_lines),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../types.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, "pins.hpp"),
        content=content,
    )


def emit_runtime_lite_registers_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    registers = _runtime_lite_register_rows(device)
    base_address_by_peripheral = {
        peripheral.name: peripheral.base_address for peripheral in device.peripherals
    }
    register_enum_rows = [f"  {_enum_identifier(register.register_id)}," for register in registers]
    trait_lines: list[str] = [
        "template<RegisterId Id>",
        "struct RegisterTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr std::uintptr_t kBaseAddress = 0u;",
        "  static constexpr std::uint32_t kOffsetBytes = 0u;",
        "  static constexpr AccessKindId kAccessId = AccessKindId::none;",
        "  static constexpr int kSizeBits = -1;",
        "};",
        "",
    ]
    register_rows = []
    for register in registers:
        register_id = _enum_identifier(register.register_id)
        base_address = f"0x{base_address_by_peripheral[register.peripheral]:08X}u"
        size_bits = -1 if register.size_bits is None else register.size_bits
        trait_name = f"RegisterTraits<RegisterId::{register_id}>"
        trait_lines.extend(
            [
                "template<>",
                f"struct {trait_name} {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr std::uintptr_t kBaseAddress = {base_address};",
                f"  static constexpr std::uint32_t kOffsetBytes = {register.offset_bytes}u;",
                "  static constexpr AccessKindId kAccessId = "
                + _semantic_enum_ref(
                    "AccessKindId",
                    semantics_catalog["access_kind_enum_map"],
                    register.access,
                )
                + ";",
                f"  static constexpr int kSizeBits = {size_bits};",
                "};",
                "",
            ]
        )
        register_rows.append(f"  RegisterId::{register_id},")
    body_lines = [
        "enum class RegisterId : std::uint16_t {",
        "  none,",
        *register_enum_rows,
        "};",
        "",
        *trait_lines,
        *_std_array_lines(
            type_name="RegisterId",
            variable_name="kRegisters",
            row_lines=register_rows,
        ),
    ]
    namespace_block = _cpp_namespace_block(
        _runtime_device_namespace_components(device),
        "\n".join(body_lines),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../types.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, "registers.hpp"),
        content=content,
    )


def emit_runtime_lite_register_fields_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    register_fields = _runtime_lite_register_field_rows(device)
    field_enum_rows = [f"  {_enum_identifier(field.field_id)}," for field in register_fields]
    trait_lines: list[str] = [
        "template<FieldId Id>",
        "struct RegisterFieldTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr RegisterId kRegisterId = RegisterId::none;",
        "  static constexpr std::uint16_t kBitOffset = 0u;",
        "  static constexpr std::uint16_t kBitWidth = 0u;",
        "  static constexpr AccessKindId kAccessId = AccessKindId::none;",
        "};",
        "",
    ]
    field_rows = []
    for register_field in register_fields:
        field_id = _enum_identifier(register_field.field_id)
        register_id = _enum_identifier(register_field.register_id)
        trait_name = f"RegisterFieldTraits<FieldId::{field_id}>"
        trait_lines.extend(
            [
                "template<>",
                f"struct {trait_name} {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr RegisterId kRegisterId = RegisterId::{register_id};",
                f"  static constexpr std::uint16_t kBitOffset = {register_field.bit_offset}u;",
                f"  static constexpr std::uint16_t kBitWidth = {register_field.bit_width}u;",
                "  static constexpr AccessKindId kAccessId = "
                + _semantic_enum_ref(
                    "AccessKindId",
                    semantics_catalog["access_kind_enum_map"],
                    register_field.access,
                )
                + ";",
                "};",
                "",
            ]
        )
        field_rows.append(f"  FieldId::{field_id},")
    body_lines = [
        "enum class FieldId : std::uint16_t {",
        "  none,",
        *field_enum_rows,
        "};",
        "",
        *trait_lines,
        *_std_array_lines(
            type_name="FieldId",
            variable_name="kRegisterFields",
            row_lines=field_rows,
        ),
    ]
    namespace_block = _cpp_namespace_block(
        _runtime_device_namespace_components(device),
        "\n".join(body_lines),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../types.hpp"',
            '#include "registers.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            "register_fields.hpp",
        ),
        content=content,
    )


def emit_runtime_lite_clock_bindings_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    bindings = _clock_bindings_by_peripheral(device)
    gate_by_id = {
        gate.gate_id: gate
        for gate in device.clock_gates
        if gate.gate_id in _runtime_lite_gate_ids(device)
    }
    reset_by_id = {
        reset.reset_id: reset
        for reset in device.resets
        if reset.reset_id in _runtime_lite_reset_ids(device)
    }
    selector_by_id = {
        selector.selector_id: selector
        for selector in device.clock_selectors
        if selector.selector_id in _runtime_lite_selector_ids(device)
    }
    gate_enum_map = {gate_id: _enum_identifier(gate_id) for gate_id in sorted(gate_by_id)}
    reset_enum_map = {reset_id: _enum_identifier(reset_id) for reset_id in sorted(reset_by_id)}
    selector_enum_map = {
        selector_id: _enum_identifier(selector_id) for selector_id in sorted(selector_by_id)
    }
    gate_trait_lines: list[str] = [
        "template<ClockGateId Id>",
        "struct ClockGateTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr RegisterId kRegisterId = RegisterId::none;",
        "  static constexpr FieldId kFieldId = FieldId::none;",
        "};",
        "",
    ]
    for gate_id in sorted(gate_by_id):
        gate = gate_by_id[gate_id]
        trait_name = f"ClockGateTraits<ClockGateId::{gate_enum_map[gate_id]}>"
        register_ref = (
            "RegisterId::none"
            if gate.register_id is None
            else f"RegisterId::{_enum_identifier(gate.register_id)}"
        )
        field_ref = (
            "FieldId::none"
            if gate.register_field_id is None
            else f"FieldId::{_enum_identifier(gate.register_field_id)}"
        )
        gate_trait_lines.extend(
            [
                "template<>",
                f"struct {trait_name} {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr RegisterId kRegisterId = {register_ref};",
                f"  static constexpr FieldId kFieldId = {field_ref};",
                "};",
                "",
            ]
        )
    reset_trait_lines: list[str] = [
        "template<ResetId Id>",
        "struct ResetTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr RegisterId kRegisterId = RegisterId::none;",
        "  static constexpr FieldId kFieldId = FieldId::none;",
        "  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::none;",
        "};",
        "",
    ]
    for reset_id in sorted(reset_by_id):
        reset = reset_by_id[reset_id]
        trait_name = f"ResetTraits<ResetId::{reset_enum_map[reset_id]}>"
        register_ref = (
            "RegisterId::none"
            if reset.register_id is None
            else f"RegisterId::{_enum_identifier(reset.register_id)}"
        )
        field_ref = (
            "FieldId::none"
            if reset.register_field_id is None
            else f"FieldId::{_enum_identifier(reset.register_field_id)}"
        )
        reset_trait_lines.extend(
            [
                "template<>",
                f"struct {trait_name} {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr RegisterId kRegisterId = {register_ref};",
                f"  static constexpr FieldId kFieldId = {field_ref};",
                "  static constexpr ActiveLevelId kActiveLevelId = "
                + _semantic_enum_ref(
                    "ActiveLevelId",
                    semantics_catalog["active_level_enum_map"],
                    reset.active_level,
                )
                + ";",
                "};",
                "",
            ]
        )
    selector_trait_lines: list[str] = [
        "template<ClockSelectorId Id>",
        "struct ClockSelectorTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr RegisterId kRegisterId = RegisterId::none;",
        "  static constexpr FieldId kFieldId = FieldId::none;",
        "};",
        "",
    ]
    for selector_id in sorted(selector_by_id):
        selector = selector_by_id[selector_id]
        trait_name = f"ClockSelectorTraits<ClockSelectorId::{selector_enum_map[selector_id]}>"
        register_ref = (
            "RegisterId::none"
            if selector.register_id is None
            else f"RegisterId::{_enum_identifier(selector.register_id)}"
        )
        field_ref = (
            "FieldId::none"
            if selector.register_field_id is None
            else f"FieldId::{_enum_identifier(selector.register_field_id)}"
        )
        selector_trait_lines.extend(
            [
                "template<>",
                f"struct {trait_name} {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr RegisterId kRegisterId = {register_ref};",
                f"  static constexpr FieldId kFieldId = {field_ref};",
                "};",
                "",
            ]
        )
    binding_trait_lines: list[str] = [
        "template<PeripheralId Id>",
        "struct PeripheralClockBindingTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr ClockGateId kClockGateId = ClockGateId::none;",
        "  static constexpr ResetId kResetId = ResetId::none;",
        "  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;",
        "};",
        "",
    ]
    binding_rows = []
    for peripheral in _runtime_lite_peripherals(device):
        binding = bindings.get(peripheral.name)
        peripheral_id = _enum_identifier(peripheral.name)
        trait_name = f"PeripheralClockBindingTraits<PeripheralId::{peripheral_id}>"
        gate_ref = (
            "ClockGateId::none"
            if binding is None or binding.clock_gate_id is None
            else f"ClockGateId::{gate_enum_map[binding.clock_gate_id]}"
        )
        reset_ref = (
            "ResetId::none"
            if binding is None or binding.reset_id is None
            else f"ResetId::{reset_enum_map[binding.reset_id]}"
        )
        selector_ref = (
            "ClockSelectorId::none"
            if binding is None or binding.selector_id is None
            else f"ClockSelectorId::{selector_enum_map[binding.selector_id]}"
        )
        binding_trait_lines.extend(
            [
                "template<>",
                f"struct {trait_name} {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr ClockGateId kClockGateId = {gate_ref};",
                f"  static constexpr ResetId kResetId = {reset_ref};",
                f"  static constexpr ClockSelectorId kSelectorId = {selector_ref};",
                "};",
                "",
            ]
        )
        binding_rows.append(f"  PeripheralId::{peripheral_id},")
    body_lines = [
        *gate_trait_lines,
        *reset_trait_lines,
        *selector_trait_lines,
        *binding_trait_lines,
        *_std_array_lines(
            type_name="PeripheralId",
            variable_name="kClockBoundPeripherals",
            row_lines=binding_rows,
        ),
    ]
    namespace_block = _cpp_namespace_block(
        _runtime_device_namespace_components(device),
        "\n".join(body_lines),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../types.hpp"',
            '#include "peripheral_instances.hpp"',
            '#include "registers.hpp"',
            '#include "register_fields.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            "clock_bindings.hpp",
        ),
        content=content,
    )


def emit_runtime_lite_dma_bindings_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    bindings = _runtime_lite_dma_bindings(device)
    controllers = _runtime_lite_dma_controllers(device)
    peripherals_by_name = {peripheral.name: peripheral for peripheral in device.peripherals}
    binding_enum_rows = [f"  {_enum_identifier(binding.binding_id)}," for binding in bindings]
    controller_enum_map = {
        controller.controller: _enum_identifier(controller.controller) for controller in controllers
    }
    request_line_enum_map = {
        binding.request_line: _enum_identifier(binding.request_line) for binding in bindings
    }
    route_enum_map = {binding.route_id: _enum_identifier(binding.route_id) for binding in bindings}
    conflict_enum_map = {
        binding.conflict_group: _enum_identifier(binding.conflict_group)
        for binding in bindings
        if binding.conflict_group is not None
    }
    controller_trait_lines: list[str] = [
        "template<DmaControllerId Id>",
        "struct ControllerTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr PeripheralId kPeripheralId = PeripheralId::none;",
        "  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;",
        "  static constexpr int kChannelCount = -1;",
        "  static constexpr int kRequestCount = -1;",
        "};",
        "",
    ]
    for controller in controllers:
        peripheral = peripherals_by_name.get(controller.controller)
        schema_id = None if peripheral is None else peripheral.backend_schema_id
        controller_id = controller_enum_map[controller.controller]
        channel_count = controller.channel_count if controller.channel_count is not None else -1
        request_count = controller.request_count if controller.request_count is not None else -1
        controller_trait_lines.extend(
            [
                "template<>",
                f"struct ControllerTraits<DmaControllerId::{controller_id}> {{",
                "  static constexpr bool kPresent = true;",
                "  static constexpr PeripheralId kPeripheralId = "
                + (
                    "PeripheralId::none"
                    if peripheral is None
                    else f"PeripheralId::{_enum_identifier(peripheral.name)}"
                )
                + ";",
                "  static constexpr BackendSchemaId kSchemaId = "
                + _semantic_enum_ref(
                    "BackendSchemaId",
                    semantics_catalog["backend_schema_enum_map"],
                    schema_id,
                )
                + ";",
                f"  static constexpr int kChannelCount = {channel_count};",
                f"  static constexpr int kRequestCount = {request_count};",
                "};",
                "",
            ]
        )

    binding_trait_lines: list[str] = [
        "template<PeripheralId Peripheral, SignalId Signal>",
        "struct BindingTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr DmaBindingId kBindingId = DmaBindingId::none;",
        "  static constexpr DmaControllerId kControllerId = DmaControllerId::none;",
        "  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::none;",
        "  static constexpr DmaRouteId kRouteId = DmaRouteId::none;",
        "  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;",
        "  static constexpr int kChannelIndex = -1;",
        "  static constexpr int kRequestValue = -1;",
        "  static constexpr int kChannelSelector = -1;",
        "};",
        "",
    ]
    binding_rows: list[str] = []
    for binding in bindings:
        signal_ref = _semantic_enum_ref(
            "SignalId",
            semantics_catalog["signal_enum_map"],
            binding.signal,
        )
        binding_id = _enum_identifier(binding.binding_id)
        channel_index = binding.channel_index if binding.channel_index is not None else -1
        request_value = binding.request_value if binding.request_value is not None else -1
        channel_selector = binding.channel_selector if binding.channel_selector is not None else -1
        binding_trait_lines.extend(
            [
                "template<>",
                "struct BindingTraits<"
                f"PeripheralId::{_enum_identifier(binding.peripheral)}, {signal_ref}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr DmaBindingId kBindingId = DmaBindingId::{binding_id};",
                "  static constexpr DmaControllerId kControllerId = "
                f"DmaControllerId::{controller_enum_map[binding.controller]};",
                "  static constexpr DmaRequestLineId kRequestLineId = "
                f"DmaRequestLineId::{request_line_enum_map[binding.request_line]};",
                "  static constexpr DmaRouteId kRouteId = "
                f"DmaRouteId::{route_enum_map[binding.route_id]};",
                "  static constexpr DmaConflictGroupId kConflictGroupId = "
                + (
                    "DmaConflictGroupId::none"
                    if binding.conflict_group is None
                    else f"DmaConflictGroupId::{conflict_enum_map[binding.conflict_group]}"
                )
                + ";",
                f"  static constexpr int kChannelIndex = {channel_index};",
                f"  static constexpr int kRequestValue = {request_value};",
                f"  static constexpr int kChannelSelector = {channel_selector};",
                "};",
                "",
            ]
        )
        binding_rows.append(
            "  {"
            f"DmaBindingId::{binding_id}, "
            f"PeripheralId::{_enum_identifier(binding.peripheral)}, "
            f"{signal_ref}, "
            f"DmaControllerId::{controller_enum_map[binding.controller]}, "
            f"DmaRequestLineId::{request_line_enum_map[binding.request_line]}, "
            f"DmaRouteId::{route_enum_map[binding.route_id]}, "
            + (
                "DmaConflictGroupId::none"
                if binding.conflict_group is None
                else f"DmaConflictGroupId::{conflict_enum_map[binding.conflict_group]}"
            )
            + ", "
            f"{channel_index}, "
            f"{request_value}, "
            f"{channel_selector}"
            "},"
        )

    controller_rows = [
        f"  DmaControllerId::{controller_enum_map[controller.controller]},"
        for controller in controllers
    ]
    body_lines = [
        "enum class DmaBindingId : std::uint16_t {",
        "  none,",
        *binding_enum_rows,
        "};",
        "",
        "enum class DmaControllerId : std::uint16_t {",
        "  none,",
        *_enum_rows(controller_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class DmaRequestLineId : std::uint16_t {",
        "  none,",
        *_enum_rows(request_line_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class DmaRouteId : std::uint16_t {",
        "  none,",
        *_enum_rows(route_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class DmaConflictGroupId : std::uint16_t {",
        "  none,",
        *_enum_rows(conflict_enum_map, empty_identifier=None),
        "};",
        "",
        "struct DmaBindingDescriptor {",
        "  DmaBindingId binding_id;",
        "  PeripheralId peripheral_id;",
        "  SignalId signal_id;",
        "  DmaControllerId controller_id;",
        "  DmaRequestLineId request_line_id;",
        "  DmaRouteId route_id;",
        "  DmaConflictGroupId conflict_group_id;",
        "  std::int32_t channel_index;",
        "  std::int32_t request_value;",
        "  std::int32_t channel_selector;",
        "};",
        "",
        *binding_trait_lines,
        *controller_trait_lines,
        *_std_array_lines(
            type_name="DmaBindingDescriptor",
            variable_name="kDmaBindings",
            row_lines=binding_rows,
        ),
        "",
        *_std_array_lines(
            type_name="DmaControllerId",
            variable_name="kDmaControllers",
            row_lines=controller_rows,
        ),
    ]
    namespace_block = _cpp_namespace_block(
        _runtime_device_namespace_components(device),
        "\n".join(body_lines),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../types.hpp"',
            '#include "peripheral_instances.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            "dma_bindings.hpp",
        ),
        content=content,
    )


def emit_runtime_lite_routes_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    runtime_candidates = _runtime_lite_candidates(device)
    runtime_groups = _runtime_lite_groups(device)
    operation_by_id = {operation.operation_id: operation for operation in device.route_operations}
    gate_enum_map = {
        gate_id: _enum_identifier(gate_id) for gate_id in sorted(_runtime_lite_gate_ids(device))
    }
    reset_enum_map = {
        reset_id: _enum_identifier(reset_id) for reset_id in sorted(_runtime_lite_reset_ids(device))
    }
    route_enum_map = {
        candidate.candidate_id: _enum_identifier(candidate.candidate_id)
        for candidate in runtime_candidates
    }
    group_enum_map = {group.group_id: _enum_identifier(group.group_id) for group in runtime_groups}
    route_descriptor_rows = []
    route_trait_lines: list[str] = [
        "struct RouteOperation {",
        "  BackendSchemaId schema_id;",
        "  OperationKindId kind_id;",
        "  OperationSubjectKindId subject_kind_id;",
        "  RegisterId register_id;",
        "  FieldId field_id;",
        "  PinId pin_id;",
        "  ClockGateId clock_gate_id;",
        "  ResetId reset_id;",
        "  int value_int;",
        "};",
        "",
        "enum class RouteId : std::uint16_t {",
        "  none,",
        *_enum_rows(route_enum_map, empty_identifier=None),
        "};",
        "",
        "struct RouteDescriptor {",
        "  RouteId route_id;",
        "  PinId pin_id;",
        "  PeripheralId peripheral_id;",
        "  SignalId signal_id;",
        "  RouteKindId route_kind_id;",
        "};",
        "",
        "template<PinId Pin, PeripheralId Peripheral, SignalId Signal>",
        "struct RouteTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr RouteId kRouteId = RouteId::none;",
        "  static constexpr RouteKindId kRouteKindId = RouteKindId::none;",
        "  static constexpr std::array<RouteOperation, 0> kOperations = {};",
        "};",
        "",
    ]
    for candidate in runtime_candidates:
        pin_ref = f"PinId::{_enum_identifier(candidate.pin)}"
        peripheral_ref = f"PeripheralId::{_enum_identifier(candidate.peripheral)}"
        signal_ref = _semantic_enum_ref(
            "SignalId",
            semantics_catalog["signal_enum_map"],
            candidate.signal,
        )
        route_kind_ref = _semantic_enum_ref(
            "RouteKindId",
            semantics_catalog["route_kind_enum_map"],
            candidate.route_kind,
        )
        route_descriptor_rows.append(
            "  {"
            f"RouteId::{route_enum_map[candidate.candidate_id]}, "
            f"{pin_ref}, "
            f"{peripheral_ref}, "
            f"{signal_ref}, "
            f"{route_kind_ref}"
            "},"
        )
        operation_rows = []
        for operation_id in candidate.operation_ids:
            operation = operation_by_id[operation_id]
            schema_ref = _semantic_enum_ref(
                "BackendSchemaId",
                semantics_catalog["backend_schema_enum_map"],
                operation.schema_id,
            )
            kind_ref = _semantic_enum_ref(
                "OperationKindId",
                semantics_catalog["operation_kind_enum_map"],
                operation.kind,
            )
            subject_ref = _semantic_enum_ref(
                "OperationSubjectKindId",
                semantics_catalog["operation_subject_kind_enum_map"],
                operation.subject_kind,
            )
            register_ref = (
                "RegisterId::none"
                if operation.register_id is None
                else f"RegisterId::{_enum_identifier(operation.register_id)}"
            )
            field_ref = (
                "FieldId::none"
                if operation.register_field_id is None
                else f"FieldId::{_enum_identifier(operation.register_field_id)}"
            )
            pin_target_ref = (
                "PinId::none"
                if operation.target_ref_kind != "pin" or operation.target_ref_id is None
                else f"PinId::{_enum_identifier(operation.target_ref_id)}"
            )
            clock_gate_ref = (
                "ClockGateId::none"
                if operation.target_ref_kind != "clock-gate" or operation.target_ref_id is None
                else f"ClockGateId::{gate_enum_map[operation.target_ref_id]}"
            )
            reset_ref = (
                "ResetId::none"
                if operation.target_ref_kind != "reset" or operation.target_ref_id is None
                else f"ResetId::{reset_enum_map[operation.target_ref_id]}"
            )
            operation_rows.append(
                "    {"
                f"{schema_ref}, "
                f"{kind_ref}, "
                f"{subject_ref}, "
                f"{register_ref}, "
                f"{field_ref}, "
                f"{pin_target_ref}, "
                f"{clock_gate_ref}, "
                f"{reset_ref}, "
                f"{0 if operation.value_int is None else operation.value_int}"
                "},"
            )
        route_trait_lines.extend(
            [
                "template<>",
                f"struct RouteTraits<{pin_ref}, {peripheral_ref}, {signal_ref}> {{",
                "  static constexpr bool kPresent = true;",
                "  static constexpr RouteId kRouteId = "
                f"RouteId::{route_enum_map[candidate.candidate_id]};",
                f"  static constexpr RouteKindId kRouteKindId = {route_kind_ref};",
                "  static constexpr std::array<RouteOperation, "
                + f"{len(operation_rows)}> kOperations = {{{{",
                *operation_rows,
                "  }};",
                "};",
                "",
            ]
        )

    group_trait_lines: list[str] = [
        "enum class ConnectionGroupId : std::uint16_t {",
        "  none,",
        *_enum_rows(group_enum_map, empty_identifier=None),
        "};",
        "",
        "template<PeripheralId Peripheral, SignalId... Signals>",
        "struct ConnectionGroupTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::none;",
        "  static constexpr std::array<RouteId, 0> kRoutes = {};",
        "};",
        "",
    ]
    group_descriptor_rows = []
    for group in runtime_groups:
        route_ids = [
            f"RouteId::{route_enum_map[candidate_id]}"
            for candidate_id in group.candidate_ids
            if candidate_id in route_enum_map
        ]
        signal_refs = [
            _semantic_enum_ref("SignalId", semantics_catalog["signal_enum_map"], signal)
            for signal in group.signals
        ]
        if not route_ids:
            continue
        peripheral_ref = f"PeripheralId::{_enum_identifier(group.peripheral)}"
        group_trait_lines.extend(
            [
                "template<>",
                f"struct ConnectionGroupTraits<{peripheral_ref}, {', '.join(signal_refs)}> {{",
                "  static constexpr bool kPresent = true;",
                "  static constexpr ConnectionGroupId kGroupId = "
                f"ConnectionGroupId::{group_enum_map[group.group_id]};",
                f"  static constexpr std::array<RouteId, {len(route_ids)}> kRoutes = {{{{",
                *[f"    {route_id}," for route_id in route_ids],
                "  }};",
                "};",
                "",
            ]
        )
        group_descriptor_rows.append(
            "  {"
            f"ConnectionGroupId::{group_enum_map[group.group_id]}, "
            f"{peripheral_ref}, "
            f"{len(route_ids)}u"
            "},"
        )

    body_lines = [
        *route_trait_lines,
        *_std_array_lines(
            type_name="RouteDescriptor",
            variable_name="kRuntimeRoutes",
            row_lines=route_descriptor_rows,
        ),
        "",
        *group_trait_lines,
        "struct ConnectionGroupDescriptor {",
        "  ConnectionGroupId group_id;",
        "  PeripheralId peripheral_id;",
        "  std::uint16_t route_count;",
        "};",
        *_std_array_lines(
            type_name="ConnectionGroupDescriptor",
            variable_name="kRuntimeConnectionGroups",
            row_lines=group_descriptor_rows,
        ),
        "",
    ]
    namespace_block = _cpp_namespace_block(
        _runtime_device_namespace_components(device),
        "\n".join(body_lines),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../types.hpp"',
            '#include "clock_bindings.hpp"',
            '#include "peripheral_instances.hpp"',
            '#include "pins.hpp"',
            '#include "register_fields.hpp"',
            '#include "registers.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, "routes.hpp"),
        content=content,
    )


__all__ = [
    "RUNTIME_LITE_PERIPHERAL_CLASSES",
    "emit_runtime_lite_clock_bindings_header",
    "emit_runtime_lite_dma_bindings_header",
    "emit_runtime_lite_peripheral_instances_header",
    "emit_runtime_lite_pins_header",
    "emit_runtime_lite_register_fields_header",
    "emit_runtime_lite_registers_header",
    "emit_runtime_lite_routes_header",
    "emit_runtime_lite_types_header",
    "runtime_lite_peripheral_class_name",
    "runtime_lite_required_paths",
]


def runtime_lite_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return _runtime_lite_required_paths(family_dir=family_dir, devices=devices)
