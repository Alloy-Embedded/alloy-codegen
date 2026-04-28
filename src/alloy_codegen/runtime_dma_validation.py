"""Generated runtime DMA-binding validation contract.

Projects ``device.dma_bindings`` into a C++20 concept so HAL drivers can
constrain templates with ``ValidDmaBinding<PeripheralId, DmaChannelId>``
and refuse invalid (peripheral, DMA channel) wiring at compile time.

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

DMA_VALIDATION_HEADER = "dma_validation.hpp"


def runtime_dma_validation_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(family_dir, device.identity.device, DMA_VALIDATION_HEADER)
        for device in devices
        if device.dma_bindings
    )


def emit_runtime_dma_validation_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact | None:
    # Restrict to bindings whose ``peripheral`` is exposed via the
    # typed ``PeripheralId`` enum (built from ``device.peripherals``).
    # Bindings referencing peripherals outside that enum (e.g. virtual
    # subsystems on Espressif) are silently skipped — emitting a
    # specialisation referencing a missing enumerator would break the
    # smoke compile.
    known_peripherals = _runtime_lite_peripheral_names(device)
    bindings = tuple(
        sorted(
            (b for b in device.dma_bindings if b.peripheral in known_peripherals),
            key=lambda item: (
                item.peripheral,
                item.controller,
                item.request_line,
                item.signal or "",
            ),
        )
    )
    if not bindings:
        return None

    # Closed DmaChannelId enum: one entry per distinct (controller,
    # request_line) pair across the device's DMA bindings.
    channel_pairs = sorted(
        {(binding.controller, binding.request_line) for binding in bindings},
        key=lambda pair: _enum_identifier(f"{pair[0]}_{pair[1]}").upper(),
    )
    channel_lines = [
        "enum class DmaChannelId : std::uint16_t {",
        "  none = 0u,",
        *(
            f"  {_enum_identifier(f'{controller}_{request_line}').upper()} = {index + 1}u,"
            for index, (controller, request_line) in enumerate(channel_pairs)
        ),
        "};",
        "",
    ]

    primary_template_lines = [
        "template<PeripheralId Peripheral, DmaChannelId Channel>",
        "struct DmaBindingValid : std::false_type {};",
        "",
    ]

    specialisation_lines: list[str] = []
    table_rows: list[str] = []
    for binding in bindings:
        peripheral_ref = f"PeripheralId::{_enum_identifier(binding.peripheral)}"
        channel_ref = "DmaChannelId::" + _enum_identifier(
            f"{binding.controller}_{binding.request_line}"
        ).upper()
        channel_index = binding.channel_index if binding.channel_index is not None else 0
        request_value = binding.request_value if binding.request_value is not None else 0
        specialisation_lines.extend(
            [
                "template<>",
                f"struct DmaBindingValid<{peripheral_ref}, {channel_ref}> : std::true_type {{",
                f"  static constexpr std::uint8_t kChannelIndex = {channel_index}u;",
                f"  static constexpr std::uint16_t kRequestValue = {request_value}u;",
                "};",
                "",
            ]
        )
        table_rows.append(
            f"  {{{peripheral_ref}, {channel_ref}, {channel_index}u, {request_value}u}},"
        )

    concept_lines = [
        "template<PeripheralId Peripheral, DmaChannelId Channel>",
        "concept ValidDmaBinding = DmaBindingValid<Peripheral, Channel>::value;",
        "",
        "namespace detail {",
        "template<PeripheralId Peripheral, DmaChannelId Channel>",
        "inline constexpr bool kInvalidDmaBinding = false;",
        "}  // namespace detail",
        "",
    ]

    table_struct_lines = [
        "struct DmaBindingEntry {",
        "  PeripheralId peripheral;",
        "  DmaChannelId channel;",
        "  std::uint8_t channel_index;",
        "  std::uint16_t request_value;",
        "};",
        "",
        f"inline constexpr std::array<DmaBindingEntry, {len(table_rows)}> "
        "kDmaBindingEntries = {{",
        *table_rows,
        "}};",
        "",
        "constexpr bool is_valid_dma_binding(PeripheralId peripheral, "
        "DmaChannelId channel) noexcept {",
        "  for (auto const& entry : kDmaBindingEntries) {",
        "    if (entry.peripheral == peripheral && entry.channel == channel) {",
        "      return true;",
        "    }",
        "  }",
        "  return false;",
        "}",
    ]

    body = "\n".join(
        [
            *channel_lines,
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
            family_dir, device.identity.device, DMA_VALIDATION_HEADER
        ),
        content=content,
    )


__all__ = [
    "DMA_VALIDATION_HEADER",
    "emit_runtime_dma_validation_header",
    "runtime_dma_validation_required_paths",
]
