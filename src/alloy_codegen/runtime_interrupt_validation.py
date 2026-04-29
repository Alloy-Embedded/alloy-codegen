"""Generated runtime interrupt-slot validation contract.

Projects ``device.interrupt_bindings`` + ``device.vector_slots``
into a C++20 concept so HAL drivers can constrain templates with
``ValidInterruptSlot<Peripheral, VectorIndex>`` and refuse
malformed IRQ wiring at compile time.

Added by ``add-additional-validity-concepts``.
"""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import _cpp_artifact, _cpp_namespace_block, _enum_identifier
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
)

INTERRUPT_VALIDATION_HEADER = "interrupt_validation.hpp"


def runtime_interrupt_validation_required_paths(
    *, family_dir: str, devices: tuple[CanonicalDeviceIR, ...]
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(
            family_dir, device.identity.device, INTERRUPT_VALIDATION_HEADER
        )
        for device in devices
        if any(b.vector_slot is not None for b in device.interrupt_bindings)
    )


def emit_runtime_interrupt_validation_header(
    *, family_dir: str, device: CanonicalDeviceIR
) -> EmittedArtifact | None:
    bindings = tuple(
        sorted(
            (b for b in device.interrupt_bindings if b.vector_slot is not None),
            key=lambda b: (b.vector_slot or 0, b.peripheral, b.interrupt),
        )
    )
    if not bindings:
        return None

    peripherals = sorted({b.peripheral for b in bindings})
    peripheral_lines = [
        "enum class IrqPeripheral : std::uint16_t {",
        *(f"  {_enum_identifier(p)} = {i}u," for i, p in enumerate(peripherals)),
        "};",
        "",
    ]

    primary_template_lines = [
        "template<IrqPeripheral Peripheral, std::uint32_t VectorIndex>",
        "struct InterruptSlotValid : std::false_type {};",
        "",
    ]

    specialisation_lines: list[str] = []
    table_rows: list[str] = []
    for b in bindings:
        peri_ref = "IrqPeripheral::" + _enum_identifier(b.peripheral)
        vector_idx = b.vector_slot or 0
        line = b.line
        symbol = b.symbol_name or ""
        shared = b.shared_group or ""
        specialisation_lines.extend(
            [
                "template<>",
                f"struct InterruptSlotValid<{peri_ref}, {vector_idx}u> : std::true_type {{",
                f"  static constexpr int kIrqLine = {line};",
                f'  static constexpr const char* kSymbolName = "{symbol}";',
                f'  static constexpr const char* kSharedGroup = "{shared}";',
                "};",
                "",
            ]
        )
        table_rows.append(f"  {{{peri_ref}, {vector_idx}u, {line}}},")

    concept_lines = [
        "template<IrqPeripheral Peripheral, std::uint32_t VectorIndex>",
        "concept ValidInterruptSlot = InterruptSlotValid<Peripheral, VectorIndex>::value;",
        "",
    ]

    table_struct_lines = [
        "struct InterruptSlotEntry {",
        "  IrqPeripheral peripheral;",
        "  std::uint32_t vector_index;",
        "  int irq_line;",
        "};",
        "",
        f"inline constexpr std::array<InterruptSlotEntry, {len(table_rows)}> "
        "kInterruptSlots = {{",
        *table_rows,
        "}};",
        "",
        "constexpr bool is_valid_interrupt_slot(IrqPeripheral peripheral, "
        "std::uint32_t vector_index) noexcept {",
        "  for (auto const& entry : kInterruptSlots) {",
        "    if (entry.peripheral == peripheral && entry.vector_index == vector_index) {",
        "      return true;",
        "    }",
        "  }",
        "  return false;",
        "}",
    ]

    body = "\n".join(
        [
            *peripheral_lines,
            *primary_template_lines,
            *specialisation_lines,
            *concept_lines,
            *table_struct_lines,
        ]
    )

    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            "#include <type_traits>",
            "",
            _cpp_namespace_block(_runtime_device_namespace_components(device), body),
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir, device.identity.device, INTERRUPT_VALIDATION_HEADER
        ),
        content=content,
    )


__all__ = [
    "INTERRUPT_VALIDATION_HEADER",
    "emit_runtime_interrupt_validation_header",
    "runtime_interrupt_validation_required_paths",
]
