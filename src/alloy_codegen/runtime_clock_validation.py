"""Generated runtime clock-source validation contract.

Projects ``device.peripheral_clock_bindings`` into a C++20 concept so HAL
drivers can constrain templates with
``ValidClockSource<PeripheralId, ClockGateId>`` and refuse invalid
(peripheral, clock-gate) pairings at compile time.

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

CLOCK_VALIDATION_HEADER = "clock_validation.hpp"


def runtime_clock_validation_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(family_dir, device.identity.device, CLOCK_VALIDATION_HEADER)
        for device in devices
        if any(b.clock_gate_id for b in device.peripheral_clock_bindings)
    )


def emit_runtime_clock_validation_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact | None:
    # Only bindings whose ``peripheral`` and ``clock_gate_id`` are
    # carried by the device's typed enums (``PeripheralId``,
    # ``ClockGateId``, ``ClockSelectorId``) project safely; the others
    # would reference enumerators that ``peripheral_instances.hpp``
    # never declares.  Filter them out so the header always compiles.
    known_peripherals = _runtime_lite_peripheral_names(device)
    known_gates = {g.gate_id for g in device.clock_gates}
    known_selectors = {s.selector_id for s in device.clock_selectors}
    bindings = tuple(
        sorted(
            (
                b
                for b in device.peripheral_clock_bindings
                if b.clock_gate_id in known_gates
                and b.peripheral in known_peripherals
                and (b.selector_id is None or b.selector_id in known_selectors)
            ),
            key=lambda item: (item.peripheral, item.clock_gate_id or ""),
        )
    )
    if not bindings:
        return None

    primary_template_lines = [
        "template<PeripheralId Peripheral, ClockGateId Source>",
        "struct ClockSourceValid : std::false_type {};",
        "",
    ]

    specialisation_lines: list[str] = []
    table_rows: list[str] = []
    for binding in bindings:
        peripheral_ref = f"PeripheralId::{_enum_identifier(binding.peripheral)}"
        gate_ref = f"ClockGateId::{_enum_identifier(binding.clock_gate_id)}"
        selector_ref = (
            "ClockSelectorId::none"
            if binding.selector_id is None
            else f"ClockSelectorId::{_enum_identifier(binding.selector_id)}"
        )
        specialisation_lines.extend(
            [
                "template<>",
                f"struct ClockSourceValid<{peripheral_ref}, {gate_ref}> : std::true_type {{",
                f"  static constexpr ClockSelectorId kSelectorId = {selector_ref};",
                "};",
                "",
            ]
        )
        table_rows.append(f"  {{{peripheral_ref}, {gate_ref}, {selector_ref}}},")

    concept_lines = [
        "template<PeripheralId Peripheral, ClockGateId Source>",
        "concept ValidClockSource = ClockSourceValid<Peripheral, Source>::value;",
        "",
        "namespace detail {",
        "template<PeripheralId Peripheral, ClockGateId Source>",
        "inline constexpr bool kInvalidClockSource = false;",
        "}  // namespace detail",
        "",
    ]

    table_struct_lines = [
        "struct ClockSourceEntry {",
        "  PeripheralId peripheral;",
        "  ClockGateId source;",
        "  ClockSelectorId selector;",
        "};",
        "",
        f"inline constexpr std::array<ClockSourceEntry, {len(table_rows)}> "
        "kClockSources = {{",
        *table_rows,
        "}};",
        "",
        "constexpr bool is_valid_clock_source(PeripheralId peripheral, "
        "ClockGateId source) noexcept {",
        "  for (auto const& entry : kClockSources) {",
        "    if (entry.peripheral == peripheral && entry.source == source) {",
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
            family_dir, device.identity.device, CLOCK_VALIDATION_HEADER
        ),
        content=content,
    )


__all__ = [
    "CLOCK_VALIDATION_HEADER",
    "emit_runtime_clock_validation_header",
    "runtime_clock_validation_required_paths",
]
