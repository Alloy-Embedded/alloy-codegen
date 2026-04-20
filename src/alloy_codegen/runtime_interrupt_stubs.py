"""Generated runtime interrupt-stub contract."""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import (
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _std_array_lines,
)
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
)

INTERRUPT_STUBS_HEADER = "interrupt_stubs.hpp"


def runtime_interrupt_stubs_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(
            family_dir,
            device.identity.device,
            INTERRUPT_STUBS_HEADER,
        )
        for device in devices
        if device.interrupts
    )


def emit_runtime_interrupt_stubs_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    interrupt_enum_map = {
        interrupt.name: _enum_identifier(interrupt.name)
        for interrupt in sorted(device.interrupts, key=lambda item: item.name)
    }
    startup_symbol_names = {
        vector_slot.symbol_name
        for vector_slot in device.vector_slots
        if vector_slot.slot > 0 and vector_slot.interrupt is not None
    }
    startup_symbol_enum_map = {
        symbol_name: _enum_identifier(symbol_name) for symbol_name in sorted(startup_symbol_names)
    }
    vector_slot_by_interrupt = {
        vector_slot.interrupt: vector_slot
        for vector_slot in device.vector_slots
        if vector_slot.slot > 0 and vector_slot.interrupt is not None
    }

    descriptor_row_lines: list[str] = []
    trait_lines: list[str] = [
        "template<InterruptId Id>",
        "struct InterruptStubTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::none;",
        "  static constexpr std::uint16_t kLine = 0xFFFFu;",
        "  static constexpr std::uint16_t kVectorSlot = 0xFFFFu;",
        "};",
        "",
    ]
    declaration_lines: list[str] = ['extern "C" {', "void Default_Handler();"]
    for interrupt in sorted(device.interrupts, key=lambda item: (item.line, item.name)):
        vector_slot = vector_slot_by_interrupt.get(interrupt.name)
        if vector_slot is None:
            continue
        interrupt_ref = f"InterruptId::{interrupt_enum_map[interrupt.name]}"
        symbol_ref = f"StartupSymbolId::{startup_symbol_enum_map[vector_slot.symbol_name]}"
        descriptor_row_lines.append(
            f"  {{{interrupt_ref}, {symbol_ref}, {interrupt.line}u, {vector_slot.slot}u}},"
        )
        trait_lines.extend(
            [
                "template<>",
                f"struct InterruptStubTraits<{interrupt_ref}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr StartupSymbolId kSymbolId = {symbol_ref};",
                f"  static constexpr std::uint16_t kLine = {interrupt.line}u;",
                f"  static constexpr std::uint16_t kVectorSlot = {vector_slot.slot}u;",
                "};",
                "",
            ]
        )
        declaration_lines.append(f"void {vector_slot.symbol_name}() __attribute__((weak));")
    declaration_lines.append("}")

    body = "\n".join(
        [
            "struct InterruptStubDescriptor {",
            "  InterruptId interrupt_id;",
            "  StartupSymbolId symbol_id;",
            "  std::uint16_t line;",
            "  std::uint16_t vector_slot;",
            "};",
            *_std_array_lines(
                type_name="InterruptStubDescriptor",
                variable_name="kInterruptStubs",
                row_lines=descriptor_row_lines,
            ),
            "",
            *trait_lines,
        ]
    )

    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "interrupts.hpp"',
            '#include "startup.hpp"',
            "",
            *declaration_lines,
            "",
            _cpp_namespace_block(_runtime_device_namespace_components(device), body),
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            INTERRUPT_STUBS_HEADER,
        ),
        content=content,
    )


__all__ = [
    "INTERRUPT_STUBS_HEADER",
    "emit_runtime_interrupt_stubs_header",
    "runtime_interrupt_stubs_required_paths",
]
