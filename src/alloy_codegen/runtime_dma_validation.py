"""Generated runtime DMA-binding validation contract.

Projects ``device.dma_bindings`` into a C++20 concept so HAL
drivers can constrain templates with
``ValidDmaBinding<Peripheral, ChannelId>`` and refuse invalid
DMA wiring at compile time.

Mirrors the shape of :mod:`runtime_pin_validation` — primary
template is ``: std::false_type {}``, per-binding full
specialisations carry a ``: std::true_type {}`` plus the
controller / route metadata.

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

DMA_VALIDATION_HEADER = "dma_validation.hpp"


def runtime_dma_validation_required_paths(
    *, family_dir: str, devices: tuple[CanonicalDeviceIR, ...]
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(
            family_dir, device.identity.device, DMA_VALIDATION_HEADER
        )
        for device in devices
        if device.dma_bindings
    )


def emit_runtime_dma_validation_header(
    *, family_dir: str, device: CanonicalDeviceIR
) -> EmittedArtifact | None:
    bindings = tuple(
        sorted(
            device.dma_bindings,
            key=lambda b: (b.peripheral, b.controller, b.request_line, b.binding_id),
        )
    )
    if not bindings:
        return None

    # Closed PeripheralId enum (just the peripherals that own a binding).
    peripherals = sorted({b.peripheral for b in bindings})
    peripheral_lines = [
        "enum class DmaPeripheral : std::uint16_t {",
        *(f"  {_enum_identifier(p)} = {i}u," for i, p in enumerate(peripherals)),
        "};",
        "",
    ]

    controllers = sorted({b.controller for b in bindings})
    controller_lines = [
        "enum class DmaController : std::uint8_t {",
        *(f"  {_enum_identifier(c)} = {i}u," for i, c in enumerate(controllers)),
        "};",
        "",
    ]

    request_lines = sorted({b.request_line for b in bindings})
    request_line_enum = [
        "enum class DmaRequestLine : std::uint16_t {",
        *(f"  {_enum_identifier(r)} = {i}u," for i, r in enumerate(request_lines)),
        "};",
        "",
    ]

    primary_template_lines = [
        "template<DmaPeripheral Peripheral, DmaController Controller, DmaRequestLine Request>",
        "struct DmaBindingValid : std::false_type {};",
        "",
    ]

    specialisation_lines: list[str] = []
    table_rows: list[str] = []
    for b in bindings:
        peri_ref = "DmaPeripheral::" + _enum_identifier(b.peripheral)
        ctrl_ref = "DmaController::" + _enum_identifier(b.controller)
        req_ref = "DmaRequestLine::" + _enum_identifier(b.request_line)
        channel_idx = b.channel_index if b.channel_index is not None else -1
        request_value = b.request_value if b.request_value is not None else -1
        specialisation_lines.extend(
            [
                "template<>",
                f"struct DmaBindingValid<{peri_ref}, {ctrl_ref}, {req_ref}> : std::true_type {{",
                f"  static constexpr int kChannelIndex = {channel_idx};",
                f"  static constexpr int kRequestValue = {request_value};",
                "};",
                "",
            ]
        )
        table_rows.append(
            f"  {{{peri_ref}, {ctrl_ref}, {req_ref}, "
            f"{channel_idx}, {request_value}}},"
        )

    concept_lines = [
        "template<DmaPeripheral Peripheral, DmaController Controller, DmaRequestLine Request>",
        "concept ValidDmaBinding = DmaBindingValid<Peripheral, Controller, Request>::value;",
        "",
    ]

    table_struct_lines = [
        "struct DmaBindingEntry {",
        "  DmaPeripheral peripheral;",
        "  DmaController controller;",
        "  DmaRequestLine request_line;",
        "  int channel_index;",
        "  int request_value;",
        "};",
        "",
        f"inline constexpr std::array<DmaBindingEntry, {len(table_rows)}> "
        "kDmaBindings = {{",
        *table_rows,
        "}};",
        "",
        "constexpr bool is_valid_dma_binding(DmaPeripheral peripheral, "
        "DmaController controller, DmaRequestLine request_line) noexcept {",
        "  for (auto const& entry : kDmaBindings) {",
        "    if (entry.peripheral == peripheral && entry.controller == controller "
        "&& entry.request_line == request_line) {",
        "      return true;",
        "    }",
        "  }",
        "  return false;",
        "}",
    ]

    body = "\n".join(
        [
            *peripheral_lines,
            *controller_lines,
            *request_line_enum,
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
            family_dir, device.identity.device, DMA_VALIDATION_HEADER
        ),
        content=content,
    )


__all__ = [
    "DMA_VALIDATION_HEADER",
    "emit_runtime_dma_validation_header",
    "runtime_dma_validation_required_paths",
]
