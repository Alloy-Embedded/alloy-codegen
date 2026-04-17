"""Generated runtime startup contract."""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import (
    _collect_runtime_semantics_catalog,
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _enum_ref,
    _enum_rows,
    _semantic_enum_ref,
    _std_array_lines,
)
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
)

STARTUP_HEADER = "startup.hpp"


def runtime_startup_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(family_dir, device.identity.device, STARTUP_HEADER)
        for device in devices
        if device.vector_slots or device.startup_descriptors
    )


def emit_runtime_startup_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    memory_region_enum_map = {
        memory.name: _enum_identifier(memory.name)
        for memory in sorted(device.memories, key=lambda item: item.base_address)
    }
    startup_descriptor_enum_map = {
        descriptor.descriptor_id: _enum_identifier(descriptor.descriptor_id)
        for descriptor in sorted(device.startup_descriptors, key=lambda item: item.descriptor_id)
    }
    startup_symbol_names = {vector_slot.symbol_name for vector_slot in device.vector_slots} | {
        descriptor.symbol
        for descriptor in device.startup_descriptors
        if descriptor.symbol is not None
    }
    startup_symbol_enum_map = {
        symbol_name: _enum_identifier(symbol_name) for symbol_name in sorted(startup_symbol_names)
    }
    interrupt_binding_ids = {
        binding.interrupt: binding.binding_id for binding in device.interrupt_bindings
    }
    interrupt_binding_enum_map = {
        binding.binding_id: _enum_identifier(binding.binding_id)
        for binding in device.interrupt_bindings
    }

    vector_slot_row_lines: list[str] = []
    for vector_slot in sorted(device.vector_slots, key=lambda item: item.slot):
        symbol_ref = _enum_ref(
            "StartupSymbolId",
            startup_symbol_enum_map,
            vector_slot.symbol_name,
        )
        binding_ref = _enum_ref(
            "InterruptBindingId",
            interrupt_binding_enum_map,
            interrupt_binding_ids.get(vector_slot.interrupt),
        )
        kind_ref = _semantic_enum_ref(
            "VectorKindId",
            semantics_catalog["vector_kind_enum_map"],
            vector_slot.kind,
        )
        vector_slot_row_lines.append(
            f"  {{{vector_slot.slot}, {symbol_ref}, {binding_ref}, {kind_ref}}},"
        )

    startup_descriptor_row_lines: list[str] = []
    for descriptor in sorted(device.startup_descriptors, key=lambda item: item.descriptor_id):
        descriptor_ref = _enum_ref(
            "StartupDescriptorId",
            startup_descriptor_enum_map,
            descriptor.descriptor_id,
        )
        kind_ref = _semantic_enum_ref(
            "StartupKindId",
            semantics_catalog["startup_kind_enum_map"],
            descriptor.kind,
        )
        source_region_ref = _enum_ref(
            "StartupMemoryRegionId",
            memory_region_enum_map,
            descriptor.source_region,
        )
        target_region_ref = _enum_ref(
            "StartupMemoryRegionId",
            memory_region_enum_map,
            descriptor.target_region,
        )
        symbol_ref = _enum_ref(
            "StartupSymbolId",
            startup_symbol_enum_map,
            descriptor.symbol,
        )
        startup_descriptor_row_lines.append(
            "  {"
            f"{descriptor_ref}, "
            f"{kind_ref}, "
            f"{source_region_ref}, "
            f"{target_region_ref}, "
            f"{symbol_ref}"
            "},"
        )

    body = "\n".join(
        [
            "enum class StartupMemoryRegionId : std::uint16_t {",
            "  none,",
            *_enum_rows(memory_region_enum_map, empty_identifier=None),
            "};",
            "",
            "enum class StartupSymbolId : std::uint16_t {",
            "  none,",
            *_enum_rows(startup_symbol_enum_map, empty_identifier=None),
            "};",
            "",
            "enum class StartupDescriptorId : std::uint16_t {",
            "  none,",
            *_enum_rows(startup_descriptor_enum_map, empty_identifier=None),
            "};",
            "",
            "enum class InterruptBindingId : std::uint16_t {",
            "  none,",
            *_enum_rows(interrupt_binding_enum_map, empty_identifier=None),
            "};",
            "",
            "struct VectorSlotDescriptor {",
            "  int slot;",
            "  StartupSymbolId symbol_id;",
            "  InterruptBindingId interrupt_binding_id;",
            "  VectorKindId kind_id;",
            "};",
            *_std_array_lines(
                type_name="VectorSlotDescriptor",
                variable_name="kVectorSlots",
                row_lines=vector_slot_row_lines,
            ),
            "",
            "struct StartupDescriptor {",
            "  StartupDescriptorId descriptor_id;",
            "  StartupKindId kind_id;",
            "  StartupMemoryRegionId source_region_id;",
            "  StartupMemoryRegionId target_region_id;",
            "  StartupSymbolId symbol_id;",
            "};",
            *_std_array_lines(
                type_name="StartupDescriptor",
                variable_name="kStartupDescriptors",
                row_lines=startup_descriptor_row_lines,
            ),
        ]
    )

    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../types.hpp"',
            "",
            _cpp_namespace_block(_runtime_device_namespace_components(device), body),
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, STARTUP_HEADER),
        content=content,
    )
