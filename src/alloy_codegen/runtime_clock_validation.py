"""Generated runtime clock-source validation contract.

Projects ``device.peripheral_clock_bindings`` into a C++20
concept so HAL drivers can constrain templates with
``ValidClockSource<Peripheral, SourceId>`` and refuse invalid
clock-source choices at compile time.

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

CLOCK_VALIDATION_HEADER = "clock_validation.hpp"


def _binding_source_id(binding) -> str | None:
    """A binding 'source' is its selector_id (for selector-based
    clocks) or its clock_gate_id (for fixed-source clocks).  When
    both are absent, the binding contributes nothing — skip."""
    return binding.selector_id or binding.clock_gate_id or None


def runtime_clock_validation_required_paths(
    *, family_dir: str, devices: tuple[CanonicalDeviceIR, ...]
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(
            family_dir, device.identity.device, CLOCK_VALIDATION_HEADER
        )
        for device in devices
        if any(_binding_source_id(b) for b in device.peripheral_clock_bindings)
    )


def emit_runtime_clock_validation_header(
    *, family_dir: str, device: CanonicalDeviceIR
) -> EmittedArtifact | None:
    bindings = tuple(
        b for b in device.peripheral_clock_bindings if _binding_source_id(b)
    )
    if not bindings:
        return None
    bindings = tuple(sorted(bindings, key=lambda b: (b.peripheral, _binding_source_id(b) or "")))

    peripherals = sorted({b.peripheral for b in bindings})
    peripheral_lines = [
        "enum class ClockedPeripheral : std::uint16_t {",
        *(f"  {_enum_identifier(p)} = {i}u," for i, p in enumerate(peripherals)),
        "};",
        "",
    ]

    sources = sorted({_binding_source_id(b) for b in bindings if _binding_source_id(b)})  # type: ignore[arg-type]
    source_lines = [
        "enum class ClockSource : std::uint16_t {",
        *(f"  {_enum_identifier(s)} = {i}u," for i, s in enumerate(sources)),
        "};",
        "",
    ]

    primary_template_lines = [
        "template<ClockedPeripheral Peripheral, ClockSource Source>",
        "struct ClockSourceValid : std::false_type {};",
        "",
    ]

    specialisation_lines: list[str] = []
    table_rows: list[str] = []
    for b in bindings:
        source_id = _binding_source_id(b)
        if source_id is None:
            continue
        peri_ref = "ClockedPeripheral::" + _enum_identifier(b.peripheral)
        src_ref = "ClockSource::" + _enum_identifier(source_id)
        gate_id = b.clock_gate_id or ""
        reset_id = b.reset_id or ""
        specialisation_lines.extend(
            [
                "template<>",
                f"struct ClockSourceValid<{peri_ref}, {src_ref}> : std::true_type {{",
                f'  static constexpr const char* kClockGateId = "{gate_id}";',
                f'  static constexpr const char* kResetId = "{reset_id}";',
                "};",
                "",
            ]
        )
        table_rows.append(f"  {{{peri_ref}, {src_ref}}},")

    concept_lines = [
        "template<ClockedPeripheral Peripheral, ClockSource Source>",
        "concept ValidClockSource = ClockSourceValid<Peripheral, Source>::value;",
        "",
    ]

    table_struct_lines = [
        "struct ClockBindingEntry {",
        "  ClockedPeripheral peripheral;",
        "  ClockSource source;",
        "};",
        "",
        f"inline constexpr std::array<ClockBindingEntry, {len(table_rows)}> "
        "kClockBindings = {{",
        *table_rows,
        "}};",
        "",
        "constexpr bool is_valid_clock_source(ClockedPeripheral peripheral, "
        "ClockSource source) noexcept {",
        "  for (auto const& entry : kClockBindings) {",
        "    if (entry.peripheral == peripheral && entry.source == source) {",
        "      return true;",
        "    }",
        "  }",
        "  return false;",
        "}",
    ]

    body = "\n".join(
        [
            *peripheral_lines,
            *source_lines,
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
            family_dir, device.identity.device, CLOCK_VALIDATION_HEADER
        ),
        content=content,
    )


__all__ = [
    "CLOCK_VALIDATION_HEADER",
    "emit_runtime_clock_validation_header",
    "runtime_clock_validation_required_paths",
]
