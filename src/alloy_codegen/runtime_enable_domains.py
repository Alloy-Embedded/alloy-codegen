"""Generated runtime enable-domain contract."""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import _cpp_artifact, _cpp_namespace_block, _enum_identifier, _std_array_lines
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
    _runtime_lite_gate_ids,
)

ENABLE_DOMAINS_HEADER = "enable_domains.hpp"


def runtime_enable_domains_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(
            family_dir,
            device.identity.device,
            ENABLE_DOMAINS_HEADER,
        )
        for device in devices
        if _runtime_lite_gate_ids(device)
    )


def emit_runtime_enable_domains_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    gate_ids = _runtime_lite_gate_ids(device)
    gates = {gate.gate_id: gate for gate in device.clock_gates if gate.gate_id in gate_ids}

    def _enable_domain_ref(gate_id: str) -> str:
        return f"EnableDomainId::{_enum_identifier(gate_id)}"

    def _clock_gate_ref(gate_id: str) -> str:
        return f"ClockGateId::{_enum_identifier(gate_id)}"

    def _peripheral_ref(peripheral_name: str | None) -> str:
        if peripheral_name is None:
            return "PeripheralId::none"
        return f"PeripheralId::{_enum_identifier(peripheral_name)}"

    def _clock_node_ref(node_id: str | None) -> str:
        if node_id is None:
            return "ClockNodeId::none"
        return f"ClockNodeId::{_enum_identifier(node_id)}"

    def _register_ref(register_id: str | None) -> str:
        if register_id is None:
            return "RegisterId::none"
        return f"RegisterId::{_enum_identifier(register_id)}"

    def _field_ref(field_id: str | None) -> str:
        if field_id is None:
            return "FieldId::none"
        return f"FieldId::{_enum_identifier(field_id)}"

    descriptor_rows: list[str] = []
    trait_lines: list[str] = [
        "template<EnableDomainId Id>",
        "struct EnableDomainTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr PeripheralId kPeripheralId = PeripheralId::none;",
        "  static constexpr ClockGateId kClockGateId = ClockGateId::none;",
        "  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::none;",
        "  static constexpr RegisterId kRegisterId = RegisterId::none;",
        "  static constexpr FieldId kFieldId = FieldId::none;",
        "};",
        "",
        "template<PeripheralId Id>",
        "struct PeripheralEnableDomainTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::none;",
        "};",
        "",
    ]
    for gate_id, gate in sorted(gates.items()):
        enable_domain_ref = _enable_domain_ref(gate_id)
        clock_gate_ref = _clock_gate_ref(gate_id)
        peripheral_ref = _peripheral_ref(gate.peripheral)
        clock_node_ref = _clock_node_ref(gate.parent_node)
        register_ref = _register_ref(gate.register_id)
        field_ref = _field_ref(gate.register_field_id)
        descriptor_rows.append(
            "  {"
            f"{enable_domain_ref}, "
            f"{peripheral_ref}, "
            f"{clock_gate_ref}, "
            f"{clock_node_ref}, "
            f"{register_ref}, "
            f"{field_ref}"
            "},"
        )
        trait_lines.extend(
            [
                "template<>",
                f"struct EnableDomainTraits<{enable_domain_ref}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr PeripheralId kPeripheralId = {peripheral_ref};",
                f"  static constexpr ClockGateId kClockGateId = {clock_gate_ref};",
                f"  static constexpr ClockNodeId kParentClockNodeId = {clock_node_ref};",
                f"  static constexpr RegisterId kRegisterId = {register_ref};",
                f"  static constexpr FieldId kFieldId = {field_ref};",
                "};",
                "",
            ]
        )
        if gate.peripheral is not None:
            trait_lines.extend(
                [
                    "template<>",
                    f"struct PeripheralEnableDomainTraits<{peripheral_ref}> {{",
                    "  static constexpr bool kPresent = true;",
                    f"  static constexpr EnableDomainId kEnableDomainId = {enable_domain_ref};",
                    "};",
                    "",
                ]
            )

    body = "\n".join(
        [
            "using EnableDomainId = ClockGateId;",
            "",
            "struct EnableDomainDescriptor {",
            "  EnableDomainId enable_domain_id;",
            "  PeripheralId peripheral_id;",
            "  ClockGateId clock_gate_id;",
            "  ClockNodeId parent_clock_node_id;",
            "  RegisterId register_id;",
            "  FieldId field_id;",
            "};",
            *_std_array_lines(
                type_name="EnableDomainDescriptor",
                variable_name="kEnableDomains",
                row_lines=descriptor_rows,
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
            '#include "../../types.hpp"',
            '#include "clock_bindings.hpp"',
            '#include "clock_graph.hpp"',
            '#include "peripheral_instances.hpp"',
            '#include "register_fields.hpp"',
            '#include "registers.hpp"',
            "",
            _cpp_namespace_block(_runtime_device_namespace_components(device), body),
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            ENABLE_DOMAINS_HEADER,
        ),
        content=content,
    )


__all__ = [
    "ENABLE_DOMAINS_HEADER",
    "emit_runtime_enable_domains_header",
    "runtime_enable_domains_required_paths",
]
