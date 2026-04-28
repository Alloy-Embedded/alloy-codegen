"""Generated runtime interrupt-slot validation contract.

Projects ``device.interrupt_bindings`` into a C++20 concept so HAL
drivers can constrain templates with
``ValidInterruptSlot<PeripheralId, VectorSlot>`` and refuse mismatched
(peripheral, vector-slot) wiring at compile time.

Added by ``add-additional-validity-concepts``.
"""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import (
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
)
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
    _runtime_lite_peripheral_names,
)

INTERRUPT_VALIDATION_HEADER = "interrupt_validation.hpp"


def runtime_interrupt_validation_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(
            family_dir, device.identity.device, INTERRUPT_VALIDATION_HEADER
        )
        for device in devices
        if any(b.vector_slot is not None for b in device.interrupt_bindings)
    )


def emit_runtime_interrupt_validation_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact | None:
    # Restrict to bindings whose ``peripheral`` is carried by the
    # device's typed ``PeripheralId`` enum.  Bindings rooted on
    # peripherals not present as runtime instances (e.g. ESP32
    # ``DPORT``) are silently skipped — the header is purely
    # additive and must compile even when only a subset of the IR
    # bindings can be projected.
    known_peripherals = _runtime_lite_peripheral_names(device)
    bindings = tuple(
        sorted(
            (
                b
                for b in device.interrupt_bindings
                if b.vector_slot is not None and b.peripheral in known_peripherals
            ),
            key=lambda item: (item.peripheral, item.vector_slot or 0, item.interrupt),
        )
    )
    if not bindings:
        return None

    primary_template_lines = [
        "template<PeripheralId Peripheral, std::uint16_t VectorSlot>",
        "struct InterruptSlotValid : std::false_type {};",
        "",
    ]

    specialisation_lines: list[str] = []
    table_rows: list[str] = []
    for binding in bindings:
        peripheral_ref = f"PeripheralId::{_enum_identifier(binding.peripheral)}"
        slot = binding.vector_slot
        line = binding.line
        symbol = binding.symbol_name or binding.interrupt
        specialisation_lines.extend(
            [
                "template<>",
                f"struct InterruptSlotValid<{peripheral_ref}, {slot}u> : std::true_type {{",
                f"  static constexpr std::uint16_t kIrqLine = {line}u;",
                f'  static constexpr char const* kSymbolName = "{symbol}";',
                "};",
                "",
            ]
        )
        table_rows.append(f"  {{{peripheral_ref}, {slot}u, {line}u}},")

    concept_lines = [
        "template<PeripheralId Peripheral, std::uint16_t VectorSlot>",
        "concept ValidInterruptSlot = InterruptSlotValid<Peripheral, VectorSlot>::value;",
        "",
        "namespace detail {",
        "template<PeripheralId Peripheral, std::uint16_t VectorSlot>",
        "inline constexpr bool kInvalidInterruptSlot = false;",
        "}  // namespace detail",
        "",
    ]

    table_struct_lines = [
        "struct InterruptSlotEntry {",
        "  PeripheralId peripheral;",
        "  std::uint16_t vector_slot;",
        "  std::uint16_t irq_line;",
        "};",
        "",
        f"inline constexpr std::array<InterruptSlotEntry, {len(table_rows)}> "
        "kInterruptSlots = {{",
        *table_rows,
        "}};",
        "",
        "constexpr bool is_valid_interrupt_slot(PeripheralId peripheral, "
        "std::uint16_t vector_slot) noexcept {",
        "  for (auto const& entry : kInterruptSlots) {",
        "    if (entry.peripheral == peripheral && entry.vector_slot == vector_slot) {",
        "      return true;",
        "    }",
        "  }",
        "  return false;",
        "}",
    ]

    body = "\n".join(
        [
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
            '#include "../../types.hpp"',
            '#include "peripheral_instances.hpp"',
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
