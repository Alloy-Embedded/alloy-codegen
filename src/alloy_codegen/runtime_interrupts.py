"""Generated runtime interrupt contract."""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import (
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _enum_rows,
    _std_array_lines,
)
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
    _runtime_lite_peripheral_names,
)

INTERRUPTS_HEADER = "interrupts.hpp"


def runtime_interrupts_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(family_dir, device.identity.device, INTERRUPTS_HEADER)
        for device in devices
        if device.interrupts
    )


def emit_runtime_interrupts_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    interrupt_enum_map = {
        interrupt.name: _enum_identifier(interrupt.name)
        for interrupt in sorted(device.interrupts, key=lambda item: item.name)
    }
    # Only reference peripherals that exist in the runtime-lite PeripheralId enum
    runtime_peripheral_names = _runtime_lite_peripheral_names(device)

    descriptor_row_lines: list[str] = []
    for binding in sorted(
        device.interrupt_bindings,
        key=lambda item: (item.peripheral or "", item.line),
    ):
        if binding.peripheral not in runtime_peripheral_names:
            continue
        interrupt_ref = (
            f"InterruptId::{interrupt_enum_map[binding.interrupt]}"
            if binding.interrupt in interrupt_enum_map
            else "InterruptId::none"
        )
        peripheral_ref = f"PeripheralId::{binding.peripheral}"
        vector_slot_val = binding.vector_slot if binding.vector_slot is not None else 0xFFFF
        descriptor_row_lines.append(
            f"  {{{interrupt_ref}, {peripheral_ref}, {binding.line}u, {vector_slot_val}u}},"
        )

    body = "\n".join(
        [
            "enum class InterruptId : std::uint16_t {",
            "  none,",
            *_enum_rows(interrupt_enum_map, empty_identifier=None),
            "};",
            "",
            "struct InterruptDescriptor {",
            "  InterruptId interrupt_id;",
            "  PeripheralId peripheral_id;",
            "  std::uint16_t line;",
            "  std::uint16_t vector_slot;",
            "};",
            *_std_array_lines(
                type_name="InterruptDescriptor",
                variable_name="kInterruptDescriptors",
                row_lines=descriptor_row_lines,
            ),
        ]
    )

    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "peripheral_instances.hpp"',
            "",
            _cpp_namespace_block(_runtime_device_namespace_components(device), body),
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(family_dir, device.identity.device, INTERRUPTS_HEADER),
        content=content,
    )
