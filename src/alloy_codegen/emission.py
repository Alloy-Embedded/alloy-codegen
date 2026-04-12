"""Deterministic metadata emission helpers."""

from __future__ import annotations

import json
from pathlib import Path

from alloy_codegen.connector_model import canonical_peripheral_class
from alloy_codegen.ir.model import (
    CanonicalDeviceIR,
    DmaRequestDefinition,
    PeripheralInstance,
    PinDefinition,
)
from alloy_codegen.manifests import ArtifactManifest
from alloy_codegen.reporting import ConsumerVerification, EmittedArtifact, ValidationReport
from alloy_codegen.serialization import canonical_json_sha256, canonical_json_text, to_primitive


def _text_artifact(
    *,
    path: str,
    artifact_kind: str,
    payload: object,
) -> EmittedArtifact:
    content = canonical_json_text(payload)
    content_bytes = len(content.encode("utf-8"))
    content_sha256 = canonical_json_sha256(payload)
    return EmittedArtifact(
        path=path,
        artifact_kind=artifact_kind,
        content=content,
        content_sha256=content_sha256,
        content_bytes=content_bytes,
    )


def _cpp_artifact(*, path: str, content: str) -> EmittedArtifact:
    content_bytes = len(content.encode("utf-8"))
    content_sha256 = canonical_json_sha256({"content": content})
    return EmittedArtifact(
        path=path,
        artifact_kind="generated-cpp",
        content=content,
        content_sha256=content_sha256,
        content_bytes=content_bytes,
    )


def _identifier(value: str) -> str:
    sanitized = "".join(character if character.isalnum() else "_" for character in value)
    if sanitized and sanitized[0].isdigit():
        return f"_{sanitized}"
    return sanitized


def _enum_identifier(value: str) -> str:
    identifier = _identifier(value)
    if not identifier:
        return "Unknown"
    if identifier[0].isdigit():
        identifier = f"_{identifier}"
    return identifier


def _namespace_components(device: CanonicalDeviceIR) -> tuple[str, str, str, str, str]:
    return (
        _identifier(device.identity.vendor),
        _identifier(device.identity.family),
        "generated",
        "devices",
        _identifier(device.identity.device),
    )


def _cpp_namespace_block(namespaces: tuple[str, ...], body: str) -> str:
    lines = [f"namespace {name} {{" for name in namespaces]
    lines.append(body)
    lines.extend("}" for _ in namespaces)
    return "\n".join(lines)


def _quoted(value: str | None) -> str:
    return "nullptr" if value is None else json.dumps(value)


def _runtime_ref_kind_enum(kind: str | None) -> str:
    mapping = {
        None: "none",
        "package": "package",
        "package-pad": "package_pad",
        "peripheral": "peripheral",
        "state": "state",
        "pin": "pin",
        "constraint": "constraint",
        "selector": "selector",
        "ip-block": "ip_block",
        "capability": "capability",
        "clock-gate": "clock_gate",
        "reset": "reset",
        "register": "register_ref",
        "register-field": "register_field_ref",
        "int": "integer",
    }
    return f"RuntimeRefDomain::{mapping.get(kind, 'other')}"


def _clock_gate_enum_ref(device_name: str, gate_id: str | None) -> str:
    if gate_id is None:
        return "ClockGateId::none"
    return f"ClockGateId::{_enum_identifier(f'{device_name}_{gate_id}')}"


def _reset_enum_ref(device_name: str, reset_id: str | None) -> str:
    if reset_id is None:
        return "ResetId::none"
    return f"ResetId::{_enum_identifier(f'{device_name}_{reset_id}')}"


def _selector_enum_ref(device_name: str, selector_id: str | None) -> str:
    if selector_id is None:
        return "ClockSelectorId::none"
    return f"ClockSelectorId::{_enum_identifier(f'{device_name}_{selector_id}')}"


def _file_component(value: str) -> str:
    return _identifier(value).strip("_").lower()


def _family_manifest_path(family_dir: str) -> str:
    return f"{family_dir}/artifact-manifest.json"


def _family_metadata_path(family_dir: str, name: str) -> str:
    return f"{family_dir}/metadata/{name}"


def _family_report_path(family_dir: str, name: str) -> str:
    return f"{family_dir}/reports/{name}"


def _device_metadata_path(family_dir: str, device_name: str) -> str:
    return f"{family_dir}/metadata/devices/{device_name}.json"


def _device_generated_path(family_dir: str, device_name: str, name: str) -> str:
    return f"{family_dir}/generated/devices/{device_name}/{name}"


def _std_array_lines(
    *,
    type_name: str,
    variable_name: str,
    row_lines: list[str],
) -> list[str]:
    if not row_lines:
        return [f"inline constexpr std::array<{type_name}, 0> {variable_name} = {{}};"]
    return [
        f"inline constexpr std::array<{type_name}, {len(row_lines)}> {variable_name} = {{{{",
        *row_lines,
        "}};",
    ]


def _enum_rows(
    enum_map: dict[object, str],
    *,
    empty_identifier: str | None = "none",
) -> list[str]:
    rows = [f"  {identifier}," for identifier in enum_map.values()]
    if rows:
        return rows
    if empty_identifier is None:
        return []
    return [f"  {empty_identifier},"]


def _enum_index_map(enum_map: dict[object, str], *, start: int = 1) -> dict[object, int]:
    return {key: index for index, key in enumerate(enum_map.keys(), start=start)}


def _enum_ref(enum_name: str, enum_map: dict[object, str], key: object | None) -> str:
    if key is None:
        return f"{enum_name}::none"
    return f"{enum_name}::{enum_map[key]}"


def _device_ref_key(device_name: str, ref_id: str | None) -> tuple[str, str] | None:
    if ref_id is None:
        return None
    return (device_name, ref_id)


def _device_enum_ref(
    enum_name: str,
    enum_map: dict[object, str],
    device_name: str,
    ref_id: str | None,
) -> str:
    return _enum_ref(enum_name, enum_map, _device_ref_key(device_name, ref_id))


def _selector_numeric_value(selector_id: str | None) -> int:
    if selector_id is None or not selector_id.startswith("selector:"):
        return -1
    raw_value = selector_id.split(":", 1)[1]
    try:
        return int(raw_value, 0)
    except ValueError:
        return -1


def _semantic_enum_map(values: set[str], *, prefix: str | None = None) -> dict[str, str]:
    return {
        value: _enum_identifier(f"{prefix}_{value}" if prefix else value)
        for value in sorted(values)
    }


def _semantic_enum_ref(enum_name: str, enum_map: dict[str, str], value: str | None) -> str:
    if value is None:
        return f"{enum_name}::none"
    return f"{enum_name}::{enum_map[value]}"


def _runtime_signal_values(devices: tuple[CanonicalDeviceIR, ...]) -> set[str]:
    values: set[str] = set()
    for device in devices:
        for pin in device.pins:
            for signal in pin.signals:
                values.add(signal.function)
                if signal.signal is not None:
                    values.add(signal.signal)
        for endpoint in device.signal_endpoints:
            values.add(endpoint.signal)
        for candidate in device.connection_candidates:
            values.add(candidate.signal)
        for group in device.connection_groups:
            values.update(group.signals)
        for dma_request in device.dma_requests:
            if dma_request.signal is not None:
                values.add(dma_request.signal)
        for dma_binding in device.dma_bindings:
            if dma_binding.signal is not None:
                values.add(dma_binding.signal)
    return values


def _runtime_signal_role_values(devices: tuple[CanonicalDeviceIR, ...]) -> set[str]:
    return {
        signal_role
        for device in devices
        for ip_block in device.ip_blocks
        for signal_role in ip_block.signal_roles
    }


def _collect_runtime_semantics_catalog(devices: tuple[CanonicalDeviceIR, ...]) -> dict[str, object]:
    ip_block_id_values = {
        f"{ip_block.ip_name}@{ip_block.ip_version}"
        for device in devices
        for ip_block in device.ip_blocks
    }
    capability_id_values = {
        capability.capability_id for device in devices for capability in device.capabilities
    }
    backend_schema_values = (
        {
            peripheral.backend_schema_id
            for device in devices
            for peripheral in device.peripherals
            if peripheral.backend_schema_id is not None
        }
        | {
            operation.schema_id
            for device in devices
            for operation in device.route_operations
            if operation.schema_id is not None
        }
        | {
            ip_block.backend_schema_id
            for device in devices
            for ip_block in device.ip_blocks
            if ip_block.backend_schema_id is not None
        }
    )
    peripheral_class_values = (
        {
            canonical_peripheral_class(peripheral.ip_name)
            for device in devices
            for peripheral in device.peripherals
        }
        | {ip_block.peripheral_class for device in devices for ip_block in device.ip_blocks}
        | {capability.peripheral_class for device in devices for capability in device.capabilities}
        | {endpoint.peripheral_class for device in devices for endpoint in device.signal_endpoints}
    )
    capability_scope_values = {
        capability.scope for device in devices for capability in device.capabilities
    }
    capability_key_values = {
        f"{capability.name}={capability.value}"
        for device in devices
        for capability in device.capabilities
    }
    route_kind_values = {
        candidate.route_kind for device in devices for candidate in device.connection_candidates
    }
    requirement_kind_values = {
        requirement.kind for device in devices for requirement in device.route_requirements
    }
    operation_kind_values = {
        operation.kind for device in devices for operation in device.route_operations
    }
    operation_subject_kind_values = {
        operation.subject_kind
        for device in devices
        for operation in device.route_operations
        if operation.subject_kind is not None
    }
    memory_kind_values = {memory.kind for device in devices for memory in device.memories}
    startup_kind_values = {
        descriptor.kind for device in devices for descriptor in device.startup_descriptors
    }
    vector_kind_values = {
        vector_slot.kind for device in devices for vector_slot in device.vector_slots
    }
    package_pad_kind_values = {
        package_pad.pad_kind for device in devices for package_pad in device.package_pads
    }
    bonding_state_values = {
        package_pad.bonding_state for device in devices for package_pad in device.package_pads
    }
    constraint_kind_values = {
        constraint.kind for device in devices for constraint in device.pin_constraints
    }
    active_level_values = {reset.active_level for device in devices for reset in device.resets}
    core_values = {device.identity.core for device in devices}
    port_values = {pin.port for device in devices for pin in device.pins if pin.port is not None}
    pin_function_values = {
        signal.function for device in devices for pin in device.pins for signal in pin.signals
    }
    signal_values = _runtime_signal_values(devices)
    signal_role_values = _runtime_signal_role_values(devices)
    direction_values = {
        endpoint.direction
        for device in devices
        for endpoint in device.signal_endpoints
        if endpoint.direction is not None
    }
    register_profile_values = {
        ip_block.register_profile
        for device in devices
        for ip_block in device.ip_blocks
        if ip_block.register_profile is not None
    }
    clock_node_kind_values = {node.kind for device in devices for node in device.clock_nodes}
    runtime_profile_source_kind_values = {"peripheral", "route-operation"}
    startup_role_values = {
        role for device in devices for memory in device.memories for role in memory.startup_roles
    }
    access_kind_values = {
        access
        for device in devices
        for access in (
            [register.access for register in device.registers]
            + [field.access for field in device.register_fields]
            + [memory.access for memory in device.memories]
        )
        if access is not None
    }
    constraint_value_values = {
        constraint.value
        for device in devices
        for constraint in device.pin_constraints
        if constraint.value is not None
    }
    return {
        "ip_block_id_enum_map": _semantic_enum_map(ip_block_id_values, prefix="ip_block"),
        "capability_id_enum_map": _semantic_enum_map(
            capability_id_values,
            prefix="capability_id",
        ),
        "backend_schema_enum_map": _semantic_enum_map(backend_schema_values, prefix="schema"),
        "peripheral_class_enum_map": _semantic_enum_map(
            peripheral_class_values,
            prefix="class",
        ),
        "capability_scope_enum_map": _semantic_enum_map(
            capability_scope_values,
            prefix="capability_scope",
        ),
        "capability_key_enum_map": _semantic_enum_map(
            capability_key_values,
            prefix="capability",
        ),
        "route_kind_enum_map": _semantic_enum_map(route_kind_values, prefix="route_kind"),
        "requirement_kind_enum_map": _semantic_enum_map(
            requirement_kind_values,
            prefix="requirement_kind",
        ),
        "operation_kind_enum_map": _semantic_enum_map(
            operation_kind_values,
            prefix="operation_kind",
        ),
        "operation_subject_kind_enum_map": _semantic_enum_map(
            operation_subject_kind_values,
            prefix="operation_subject",
        ),
        "memory_kind_enum_map": _semantic_enum_map(memory_kind_values, prefix="memory_kind"),
        "startup_kind_enum_map": _semantic_enum_map(
            startup_kind_values,
            prefix="startup_kind",
        ),
        "vector_kind_enum_map": _semantic_enum_map(vector_kind_values, prefix="vector_kind"),
        "package_pad_kind_enum_map": _semantic_enum_map(
            package_pad_kind_values,
            prefix="package_pad_kind",
        ),
        "bonding_state_enum_map": _semantic_enum_map(
            bonding_state_values,
            prefix="bonding_state",
        ),
        "constraint_kind_enum_map": _semantic_enum_map(
            constraint_kind_values,
            prefix="constraint_kind",
        ),
        "active_level_enum_map": _semantic_enum_map(active_level_values, prefix="active_level"),
        "core_enum_map": _semantic_enum_map(core_values, prefix="core"),
        "port_enum_map": _semantic_enum_map(port_values, prefix="port"),
        "pin_function_enum_map": _semantic_enum_map(
            pin_function_values,
            prefix="pin_function",
        ),
        "access_kind_enum_map": _semantic_enum_map(
            access_kind_values,
            prefix="access_kind",
        ),
        "constraint_value_enum_map": _semantic_enum_map(
            constraint_value_values,
            prefix="constraint_value",
        ),
        "signal_enum_map": _semantic_enum_map(signal_values, prefix="signal"),
        "signal_role_enum_map": _semantic_enum_map(
            signal_role_values,
            prefix="signal_role",
        ),
        "direction_enum_map": _semantic_enum_map(direction_values, prefix="direction"),
        "register_profile_enum_map": _semantic_enum_map(
            register_profile_values,
            prefix="register_profile",
        ),
        "clock_node_kind_enum_map": _semantic_enum_map(
            clock_node_kind_values,
            prefix="clock_node_kind",
        ),
        "runtime_profile_source_kind_enum_map": _semantic_enum_map(
            runtime_profile_source_kind_values,
            prefix="runtime_profile_source",
        ),
        "startup_role_enum_map": _semantic_enum_map(
            startup_role_values,
            prefix="startup_role",
        ),
    }


def _collect_runtime_ref_catalog(devices: tuple[CanonicalDeviceIR, ...]) -> dict[str, object]:
    device_rows = sorted({device.identity.device for device in devices})
    peripheral_rows = sorted(
        {
            (device.identity.device, peripheral.name)
            for device in devices
            for peripheral in device.peripherals
        }
    )
    package_rows = sorted(
        {
            (device.identity.device, package.name)
            for device in devices
            for package in device.packages
        }
    )
    package_pad_rows = sorted(
        {
            (device.identity.device, package_pad.pad_id)
            for device in devices
            for package_pad in device.package_pads
        }
    )
    pin_rows = sorted(
        {
            (device.identity.device, pin.name, pin.port, pin.number)
            for device in devices
            for pin in device.pins
        }
    )
    constraint_rows = sorted(
        {
            (
                device.identity.device,
                constraint.constraint_id,
                constraint.pin,
                constraint.kind,
                constraint.value,
            )
            for device in devices
            for constraint in device.pin_constraints
        }
    )
    selector_rows = sorted(
        {
            (device.identity.device, selector_id, _selector_numeric_value(selector_id))
            for device in devices
            for selector_id in (
                [candidate.route_selector for candidate in device.connection_candidates]
                + [
                    requirement.target_ref_id
                    for requirement in device.route_requirements
                    if requirement.target_ref_kind == "selector"
                ]
                + [
                    requirement.value_ref_id
                    for requirement in device.route_requirements
                    if requirement.value_ref_kind == "selector"
                ]
                + [
                    operation.target_ref_id
                    for operation in device.route_operations
                    if operation.target_ref_kind == "selector"
                ]
                + [
                    operation.value_ref_id
                    for operation in device.route_operations
                    if operation.value_ref_kind == "selector"
                ]
            )
            if selector_id is not None
        }
    )
    ip_block_rows = sorted(
        {
            (ip_block.ip_name, ip_block.ip_version)
            for device in devices
            for ip_block in device.ip_blocks
        }
    )
    capability_rows = sorted(
        {
            (device.identity.device, capability.capability_id)
            for device in devices
            for capability in device.capabilities
        }
    )
    register_rows = sorted(
        {
            (
                device.identity.device,
                register.register_id,
                register.peripheral,
                register.name,
                register.offset_bytes,
            )
            for device in devices
            for register in device.registers
        }
    )
    register_field_rows = sorted(
        {
            (
                device.identity.device,
                register_field.field_id,
                register_field.register_id,
                register_field.peripheral,
                register_field.name,
                register_field.bit_offset,
                register_field.bit_width,
            )
            for device in devices
            for register_field in device.register_fields
        }
    )
    device_enum_map = {device_name: _enum_identifier(device_name) for device_name in device_rows}
    peripheral_enum_map = {
        (device_name, peripheral_name): _enum_identifier(f"{device_name}_{peripheral_name}")
        for device_name, peripheral_name in peripheral_rows
    }
    package_enum_map = {
        (device_name, package_name): _enum_identifier(f"{device_name}_{package_name}")
        for device_name, package_name in package_rows
    }
    package_pad_enum_map = {
        (device_name, pad_id): _enum_identifier(f"{device_name}_{pad_id}")
        for device_name, pad_id in package_pad_rows
    }
    pin_enum_map = {
        (device_name, pin_name): _enum_identifier(f"{device_name}_{pin_name}")
        for device_name, pin_name, _port, _number in pin_rows
    }
    constraint_enum_map = {
        (device_name, constraint_id): _enum_identifier(f"{device_name}_{constraint_id}")
        for device_name, constraint_id, _pin, _kind, _value in constraint_rows
    }
    selector_enum_map = {
        (device_name, selector_id): _enum_identifier(f"{device_name}_{selector_id}")
        for device_name, selector_id, _selector_value in selector_rows
    }
    ip_block_enum_map = {
        (ip_name, ip_version): _enum_identifier(f"{ip_name}_{ip_version}")
        for ip_name, ip_version in ip_block_rows
    }
    capability_enum_map = {
        (device_name, capability_id): _enum_identifier(f"{device_name}_{capability_id}")
        for device_name, capability_id in capability_rows
    }
    register_enum_map = {
        (device_name, register_id): _enum_identifier(f"{device_name}_{register_id}")
        for device_name, register_id, _peripheral, _name, _offset in register_rows
    }
    register_field_enum_map = {
        (device_name, field_id): _enum_identifier(f"{device_name}_{field_id}")
        for (
            device_name,
            field_id,
            _register_id,
            _peripheral,
            _name,
            _bit_offset,
            _bit_width,
        ) in register_field_rows
    }
    return {
        "device_rows": device_rows,
        "peripheral_rows": peripheral_rows,
        "package_rows": package_rows,
        "package_pad_rows": package_pad_rows,
        "pin_rows": pin_rows,
        "constraint_rows": constraint_rows,
        "selector_rows": selector_rows,
        "ip_block_rows": ip_block_rows,
        "capability_rows": capability_rows,
        "register_rows": register_rows,
        "register_field_rows": register_field_rows,
        "device_enum_map": device_enum_map,
        "peripheral_enum_map": peripheral_enum_map,
        "package_enum_map": package_enum_map,
        "package_pad_enum_map": package_pad_enum_map,
        "pin_enum_map": pin_enum_map,
        "constraint_enum_map": constraint_enum_map,
        "selector_enum_map": selector_enum_map,
        "ip_block_enum_map": ip_block_enum_map,
        "capability_enum_map": capability_enum_map,
        "register_enum_map": register_enum_map,
        "register_field_enum_map": register_field_enum_map,
        "device_index_map": _enum_index_map(device_enum_map),
        "peripheral_index_map": _enum_index_map(peripheral_enum_map),
        "package_index_map": _enum_index_map(package_enum_map),
        "package_pad_index_map": _enum_index_map(package_pad_enum_map),
        "state_index_map": {"selected": 1},
        "pin_index_map": _enum_index_map(pin_enum_map),
        "constraint_index_map": _enum_index_map(constraint_enum_map),
        "selector_index_map": _enum_index_map(selector_enum_map),
        "ip_block_index_map": _enum_index_map(ip_block_enum_map),
        "capability_index_map": _enum_index_map(capability_enum_map),
        "register_index_map": _enum_index_map(register_enum_map),
        "register_field_index_map": _enum_index_map(register_field_enum_map),
    }


def _runtime_ref_index(
    device_name: str,
    ref_kind: str | None,
    ref_id: str | None,
    ref_catalog: dict[str, object],
    clock_gate_index_map: dict[tuple[str, str], int] | None = None,
    reset_index_map: dict[tuple[str, str], int] | None = None,
) -> int:
    if ref_kind is None or ref_id is None:
        return 0
    if ref_kind == "package":
        return ref_catalog["package_index_map"][(device_name, ref_id)]
    if ref_kind == "package-pad":
        return ref_catalog["package_pad_index_map"][(device_name, ref_id)]
    if ref_kind == "peripheral":
        return ref_catalog["peripheral_index_map"][(device_name, ref_id)]
    if ref_kind == "state":
        return ref_catalog["state_index_map"][ref_id]
    if ref_kind == "pin":
        return ref_catalog["pin_index_map"][(device_name, ref_id)]
    if ref_kind == "constraint":
        return ref_catalog["constraint_index_map"][(device_name, ref_id)]
    if ref_kind == "selector":
        return ref_catalog["selector_index_map"][(device_name, ref_id)]
    if ref_kind == "ip-block":
        ip_name, ip_version = ref_id.split("@", 1)
        return ref_catalog["ip_block_index_map"][(ip_name, ip_version)]
    if ref_kind == "capability":
        return ref_catalog["capability_index_map"][(device_name, ref_id)]
    if ref_kind == "clock-gate":
        if clock_gate_index_map is None:
            raise KeyError("clock gate index map is required for clock-gate refs")
        return clock_gate_index_map[(device_name, ref_id)]
    if ref_kind == "reset":
        if reset_index_map is None:
            raise KeyError("reset index map is required for reset refs")
        return reset_index_map[(device_name, ref_id)]
    if ref_kind == "register":
        return ref_catalog["register_index_map"][(device_name, ref_id)]
    if ref_kind == "register-field":
        return ref_catalog["register_field_index_map"][(device_name, ref_id)]
    if ref_kind == "int":
        return 0
    return 0


def _runtime_ref_index_expr(
    device_name: str,
    ref_kind: str | None,
    ref_id: str | None,
    ref_catalog: dict[str, object],
    clock_gate_index_map: dict[tuple[str, str], int] | None = None,
    reset_index_map: dict[tuple[str, str], int] | None = None,
) -> str:
    value = _runtime_ref_index(
        device_name,
        ref_kind,
        ref_id,
        ref_catalog,
        clock_gate_index_map,
        reset_index_map,
    )
    return f"{value}u"


def _eref(
    enum_name: str,
    enum_map: dict[object, str],
    device_name: str,
    ref_id: str | None,
) -> str:
    return _device_enum_ref(enum_name, enum_map, device_name, ref_id)


def _ridx(
    device_name: str,
    ref_kind: str | None,
    ref_id: str | None,
    ref_catalog: dict[str, object],
    clock_gate_index_map: dict[tuple[str, str], int] | None = None,
    reset_index_map: dict[tuple[str, str], int] | None = None,
) -> str:
    return _runtime_ref_index_expr(
        device_name,
        ref_kind,
        ref_id,
        ref_catalog,
        clock_gate_index_map,
        reset_index_map,
    )


def _runtime_ref_literal(
    device_name: str,
    ref_kind: str | None,
    ref_id: str | None,
    ref_catalog: dict[str, object],
    clock_gate_index_map: dict[tuple[str, str], int] | None = None,
    reset_index_map: dict[tuple[str, str], int] | None = None,
) -> str:
    ref_index = _ridx(
        device_name,
        ref_kind,
        ref_id,
        ref_catalog,
        clock_gate_index_map,
        reset_index_map,
    )
    return f"{{{_runtime_ref_kind_enum(ref_kind)}, {ref_index}}}"


def _unique_packages(devices: tuple[CanonicalDeviceIR, ...]) -> list[dict[str, object]]:
    packages: dict[str, dict[str, object]] = {}
    for device in devices:
        for package in device.packages:
            packages.setdefault(package.name, to_primitive(package))
    return [packages[name] for name in sorted(packages)]


def _package_pad_sort_key(pad: dict[str, object]) -> tuple[int, str, str]:
    physical_index = pad["physical_index"]
    return (
        -1 if physical_index is None else int(physical_index),
        str(pad["position_label"]),
        str(pad["pad_id"]),
    )


def _constraint_sort_key(constraint: dict[str, object]) -> tuple[str, str, str]:
    value = "" if constraint["value"] is None else str(constraint["value"])
    return (str(constraint["pin"]), str(constraint["kind"]), value)


def _build_package_metadata(devices: tuple[CanonicalDeviceIR, ...]) -> list[dict[str, object]]:
    packages: dict[str, dict[str, object]] = {}
    for device in devices:
        constraints_by_pin: dict[str, list[dict[str, object]]] = {}
        for constraint in device.pin_constraints:
            constraint_payload = to_primitive(constraint)
            constraints_by_pin.setdefault(constraint.pin, []).append(constraint_payload)

        device_pinout: list[dict[str, object]] = []
        pin_index: dict[str, dict[str, object]] = {}
        for package_pad in sorted(
            (to_primitive(pad) for pad in device.package_pads),
            key=_package_pad_sort_key,
        ):
            package_entry = packages.setdefault(
                str(package_pad["package"]),
                {
                    "name": str(package_pad["package"]),
                    "pin_count": 0,
                    "provenance": None,
                    "pads": {},
                    "devices": set(),
                },
            )
            package_entry["devices"].add(device.identity.device)
            package_entry["pads"].setdefault(
                str(package_pad["pad_id"]),
                {
                    "pad_id": package_pad["pad_id"],
                    "position_label": package_pad["position_label"],
                    "physical_index": package_pad["physical_index"],
                    "pad_kind": package_pad["pad_kind"],
                },
            )

            bonded_pin = (
                None if package_pad["bonded_pin"] is None else str(package_pad["bonded_pin"])
            )
            constraint_ids = [
                str(constraint["constraint_id"])
                for constraint in sorted(
                    constraints_by_pin.get(bonded_pin, []),
                    key=_constraint_sort_key,
                )
            ]
            device_pinout.append(
                {
                    "pad_id": package_pad["pad_id"],
                    "position_label": package_pad["position_label"],
                    "physical_index": package_pad["physical_index"],
                    "pad_kind": package_pad["pad_kind"],
                    "bonded_pin": package_pad["bonded_pin"],
                    "bonding_state": package_pad["bonding_state"],
                    "constraint_ids": constraint_ids,
                }
            )

            if bonded_pin is not None:
                pin_entry = pin_index.setdefault(
                    bonded_pin,
                    {
                        "pin": bonded_pin,
                        "pad_ids": [],
                        "constraint_ids": constraint_ids,
                    },
                )
                pin_entry["pad_ids"].append(str(package_pad["pad_id"]))

        for package in device.packages:
            package_entry = packages.setdefault(
                package.name,
                {
                    "name": package.name,
                    "pin_count": package.pin_count,
                    "provenance": to_primitive(package.provenance),
                    "pads": {},
                    "devices": set(),
                },
            )
            package_entry["pin_count"] = package.pin_count
            package_entry["provenance"] = to_primitive(package.provenance)
            package_entry["devices"].add(device.identity.device)

        selected_package = packages[device.identity.package]
        selected_package.setdefault("pinouts", []).append(
            {
                "device": device.identity.device,
                "package": device.identity.package,
                "pinout": device_pinout,
                "pin_index": [pin_index[pin_name] for pin_name in sorted(pin_index)],
                "pin_constraints": [
                    to_primitive(constraint)
                    for constraint in sorted(
                        device.pin_constraints,
                        key=lambda item: item.constraint_id,
                    )
                ],
            }
        )

    return [
        {
            "name": package["name"],
            "pin_count": package["pin_count"],
            "provenance": package["provenance"],
            "pads": [
                package["pads"][pad_id]
                for pad_id in sorted(
                    package["pads"],
                    key=lambda item: _package_pad_sort_key(package["pads"][item]),
                )
            ],
            "devices": sorted(package["devices"]),
            "pinouts": sorted(package.get("pinouts", []), key=lambda item: str(item["device"])),
        }
        for package in [packages[name] for name in sorted(packages)]
    ]


def _unique_peripherals(devices: tuple[CanonicalDeviceIR, ...]) -> list[dict[str, object]]:
    peripherals: dict[str, dict[str, object]] = {}
    for device in devices:
        for peripheral in device.peripherals:
            peripherals.setdefault(peripheral.name, to_primitive(peripheral))
    return [peripherals[name] for name in sorted(peripherals)]


def _find_family_peripheral(
    devices: tuple[CanonicalDeviceIR, ...],
    peripheral_name: str,
) -> PeripheralInstance | None:
    for device in devices:
        for peripheral in device.peripherals:
            if peripheral.name == peripheral_name:
                return peripheral
    return None


def _pin_key(pin: PinDefinition) -> tuple[str, str | None, int]:
    return (pin.name, pin.port, pin.number)


def _pin_signal_key(signal: dict[str, object]) -> tuple[str, str | None, str | None, int | None]:
    return (
        str(signal["function"]),
        None if signal["peripheral"] is None else str(signal["peripheral"]),
        None if signal["signal"] is None else str(signal["signal"]),
        None if signal["af_number"] is None else int(signal["af_number"]),
    )


def _build_pin_catalog(devices: tuple[CanonicalDeviceIR, ...]) -> list[dict[str, object]]:
    grouped: dict[tuple[str, str | None, int], dict[str, object]] = {}
    for device in devices:
        for pin in device.pins:
            key = _pin_key(pin)
            entry = grouped.setdefault(
                key,
                {
                    "name": pin.name,
                    "port": pin.port,
                    "number": pin.number,
                    "packages": set(),
                    "devices": set(),
                    "signals": {},
                },
            )
            entry["packages"].add(device.identity.package)
            entry["devices"].add(device.identity.device)
            for signal in pin.signals:
                signal_payload = to_primitive(signal)
                entry["signals"].setdefault(_pin_signal_key(signal_payload), signal_payload)

    results: list[dict[str, object]] = []
    for key in sorted(grouped):
        entry = grouped[key]
        results.append(
            {
                "name": entry["name"],
                "port": entry["port"],
                "number": entry["number"],
                "packages": sorted(entry["packages"]),
                "devices": sorted(entry["devices"]),
                "signals": [
                    entry["signals"][signal_key] for signal_key in sorted(entry["signals"])
                ],
            }
        )
    return results


def _dma_key(request: DmaRequestDefinition) -> tuple[str, str, str | None, str | None]:
    return (
        request.controller,
        request.request_line,
        request.peripheral,
        request.signal,
    )


def _unique_dma_requests(devices: tuple[CanonicalDeviceIR, ...]) -> list[dict[str, object]]:
    requests: dict[tuple[str, str, str | None, str | None], dict[str, object]] = {}
    for device in devices:
        for request in device.dma_requests:
            requests.setdefault(_dma_key(request), to_primitive(request))
    return [requests[key] for key in sorted(requests)]


def _unique_interrupts(devices: tuple[CanonicalDeviceIR, ...]) -> list[dict[str, object]]:
    interrupts: dict[tuple[str, int, str | None], dict[str, object]] = {}
    for device in devices:
        for interrupt in device.interrupts:
            key = (interrupt.name, interrupt.line, interrupt.peripheral)
            interrupts.setdefault(key, to_primitive(interrupt))
    return [interrupts[key] for key in sorted(interrupts)]


def _unique_ip_blocks(devices: tuple[CanonicalDeviceIR, ...]) -> list[dict[str, object]]:
    ip_blocks: dict[tuple[str, str], dict[str, object]] = {}
    for device in devices:
        for ip_block in device.ip_blocks:
            key = (ip_block.ip_name, ip_block.ip_version)
            ip_blocks.setdefault(key, to_primitive(ip_block))
    return [ip_blocks[key] for key in sorted(ip_blocks)]


def _unique_capabilities(devices: tuple[CanonicalDeviceIR, ...]) -> list[dict[str, object]]:
    capabilities: dict[str, dict[str, object]] = {}
    for device in devices:
        for capability in device.capabilities:
            capabilities.setdefault(capability.capability_id, to_primitive(capability))
    return [capabilities[key] for key in sorted(capabilities)]


def _unique_signal_endpoints(devices: tuple[CanonicalDeviceIR, ...]) -> list[dict[str, object]]:
    endpoints: dict[str, dict[str, object]] = {}
    for device in devices:
        for endpoint in device.signal_endpoints:
            endpoints.setdefault(endpoint.endpoint_id, to_primitive(endpoint))
    return [endpoints[key] for key in sorted(endpoints)]


def _device_connector_payload(device: CanonicalDeviceIR) -> dict[str, object]:
    return {
        "device": device.identity.device,
        "package": device.identity.package,
        "route_requirements": to_primitive(device.route_requirements),
        "route_operations": to_primitive(device.route_operations),
        "connection_candidates": to_primitive(device.connection_candidates),
        "connection_groups": to_primitive(device.connection_groups),
    }


def _device_system_descriptor_payload(device: CanonicalDeviceIR) -> dict[str, object]:
    return {
        "device": device.identity.device,
        "package": device.identity.package,
        "packages": to_primitive(device.packages),
        "package_pads": to_primitive(device.package_pads),
        "pin_constraints": to_primitive(device.pin_constraints),
        "memories": to_primitive(device.memories),
        "interrupts": to_primitive(device.interrupts),
        "vector_slots": to_primitive(device.vector_slots),
        "startup_descriptors": to_primitive(device.startup_descriptors),
        "clock_nodes": to_primitive(device.clock_nodes),
        "clock_selectors": to_primitive(device.clock_selectors),
        "clock_gates": to_primitive(device.clock_gates),
        "resets": to_primitive(device.resets),
        "peripheral_clock_bindings": to_primitive(device.peripheral_clock_bindings),
        "dma_controllers": to_primitive(device.dma_controllers),
        "dma_routes": to_primitive(device.dma_routes),
        "dma_conflict_groups": to_primitive(device.dma_conflict_groups),
    }


def _device_descriptor_coverage(device: CanonicalDeviceIR) -> dict[str, object]:
    dma_domain_applicable = (
        bool(device.dma_controllers)
        or bool(device.dma_requests)
        or bool(device.dma_routes)
        or bool(device.dma_conflict_groups)
    )
    domain_status = {
        "connectors": bool(device.signal_endpoints and device.connection_candidates),
        "ip-blocks": bool(device.ip_blocks),
        "capabilities": bool(device.capabilities),
        "package": bool(device.packages and device.package_pads),
        "interrupt": bool(device.interrupts and device.vector_slots),
        "memory": bool(device.memories),
        "startup": bool(device.startup_descriptors),
        "clock-reset": bool(device.clock_nodes and device.peripheral_clock_bindings),
        "dma": (not dma_domain_applicable) or bool(device.dma_controllers and device.dma_routes),
    }
    return {
        "device": device.identity.device,
        "package": device.identity.package,
        "domains": domain_status,
        "counts": {
            "pins": len(device.pins),
            "peripherals": len(device.peripherals),
            "signal_endpoints": len(device.signal_endpoints),
            "route_requirements": len(device.route_requirements),
            "route_operations": len(device.route_operations),
            "connection_candidates": len(device.connection_candidates),
            "connection_groups": len(device.connection_groups),
            "ip_blocks": len(device.ip_blocks),
            "capabilities": len(device.capabilities),
            "packages": len(device.packages),
            "package_pads": len(device.package_pads),
            "pin_constraints": len(device.pin_constraints),
            "interrupts": len(device.interrupts),
            "vector_slots": len(device.vector_slots),
            "memories": len(device.memories),
            "startup_descriptors": len(device.startup_descriptors),
            "clock_nodes": len(device.clock_nodes),
            "clock_selectors": len(device.clock_selectors),
            "clock_gates": len(device.clock_gates),
            "resets": len(device.resets),
            "peripheral_clock_bindings": len(device.peripheral_clock_bindings),
            "dma_controllers": len(device.dma_controllers),
            "dma_routes": len(device.dma_routes),
            "dma_conflict_groups": len(device.dma_conflict_groups),
        },
        "publishable": all(domain_status.values()),
    }


def build_device_coverage(device: CanonicalDeviceIR) -> dict[str, object]:
    """Build the machine-readable coverage payload for one device."""
    return _device_descriptor_coverage(device)


def build_coverage_payload(
    *,
    devices: tuple[CanonicalDeviceIR, ...],
    report: ValidationReport,
) -> dict[str, object]:
    """Build the family coverage payload shared by emit and publish."""
    if not devices:
        raise ValueError("Coverage payload generation requires at least one device.")
    first_device = devices[0]
    device_coverage = [
        build_device_coverage(device)
        for device in sorted(devices, key=lambda item: item.identity.device)
    ]
    return {
        "schema_version": first_device.schema_version,
        "vendor": first_device.identity.vendor,
        "family": first_device.identity.family,
        "report_id": report.report_id,
        "draft_system_descriptor_domains": list(report.draft_system_descriptor_domains),
        "all_devices_publishable": all(
            bool(device_payload["publishable"]) for device_payload in device_coverage
        ),
        "devices": device_coverage,
    }


def emit_artifact_manifest(
    *,
    family_dir: str,
    artifact_manifest: ArtifactManifest,
) -> EmittedArtifact:
    return _text_artifact(
        path=_family_manifest_path(family_dir),
        artifact_kind="canonical-metadata",
        payload=artifact_manifest.to_dict(),
    )


def emit_device_metadata(*, family_dir: str, device: CanonicalDeviceIR) -> EmittedArtifact:
    return _text_artifact(
        path=_device_metadata_path(family_dir, device.identity.device),
        artifact_kind="canonical-metadata",
        payload=device.to_dict(),
    )


def emit_validation_report(*, family_dir: str, report: ValidationReport) -> EmittedArtifact:
    return _text_artifact(
        path=_family_report_path(family_dir, "validation-report.json"),
        artifact_kind="validation-report",
        payload=report.to_dict(),
    )


def emit_validation_summary(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
    report: ValidationReport,
) -> EmittedArtifact:
    if not devices:
        raise ValueError("Validation summary emission requires at least one device.")
    first_device = devices[0]
    payload = {
        "schema_version": first_device.schema_version,
        "vendor": first_device.identity.vendor,
        "family": first_device.identity.family,
        "report_id": report.report_id,
        "is_passing": report.is_passing,
        "draft_system_descriptor_domains": list(report.draft_system_descriptor_domains),
        "gates": to_primitive(report.gates),
        "system_descriptor_domains": to_primitive(report.system_descriptor_domains),
        "device_count": len(devices),
        "devices": [
            {
                "device": device.identity.device,
                "package": device.identity.package,
                "publishable": build_device_coverage(device)["publishable"],
            }
            for device in sorted(devices, key=lambda item: item.identity.device)
        ],
    }
    return _text_artifact(
        path=_family_report_path(family_dir, "validation-summary.json"),
        artifact_kind="validation-report",
        payload=payload,
    )


def emit_coverage_report(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
    report: ValidationReport,
) -> EmittedArtifact:
    payload = build_coverage_payload(devices=devices, report=report)
    return _text_artifact(
        path=_family_report_path(family_dir, "coverage.json"),
        artifact_kind="coverage-report",
        payload=payload,
    )


def _capability_overlay_rows(device: CanonicalDeviceIR) -> list[tuple[str, ...]]:
    rows: list[tuple[str, ...]] = []
    for capability in sorted(device.capabilities, key=lambda item: item.capability_id):
        if capability.scope == "ip-block":
            continue
        rows.append(
            (
                capability.capability_id,
                capability.scope,
                capability.peripheral_class,
                capability.name,
                capability.value,
                capability.ip_name or "",
                capability.ip_version or "",
                capability.peripheral or "",
                capability.package or "",
            )
        )
    return rows


def _package_pad_ids_by_pin(device: CanonicalDeviceIR) -> dict[str, tuple[str, ...]]:
    mapping: dict[str, list[str]] = {}
    for pad in sorted(device.package_pads, key=lambda item: item.pad_id):
        if pad.bonded_pin is None:
            continue
        mapping.setdefault(pad.bonded_pin, []).append(pad.pad_id)
    return {pin_name: tuple(sorted(pad_ids)) for pin_name, pad_ids in sorted(mapping.items())}


def _constraint_ids_by_pin(device: CanonicalDeviceIR) -> dict[str, tuple[str, ...]]:
    mapping: dict[str, list[str]] = {}
    for constraint in sorted(device.pin_constraints, key=lambda item: item.constraint_id):
        mapping.setdefault(constraint.pin, []).append(constraint.constraint_id)
    return {
        pin_name: tuple(sorted(constraint_ids))
        for pin_name, constraint_ids in sorted(mapping.items())
    }


def _interrupt_names_by_peripheral(device: CanonicalDeviceIR) -> dict[str, tuple[str, ...]]:
    mapping: dict[str, list[str]] = {}
    for interrupt in sorted(device.interrupts, key=lambda item: (item.line, item.name)):
        if interrupt.peripheral is None:
            continue
        mapping.setdefault(interrupt.peripheral, []).append(interrupt.name)
    return {peripheral_name: tuple(names) for peripheral_name, names in sorted(mapping.items())}


def _binding_by_peripheral(device: CanonicalDeviceIR) -> dict[str, object]:
    return {
        binding.peripheral: binding
        for binding in sorted(device.peripheral_clock_bindings, key=lambda item: item.peripheral)
    }


def _interrupt_bindings_by_peripheral(
    device: CanonicalDeviceIR,
) -> dict[str, tuple[object, ...]]:
    mapping: dict[str, list[object]] = {}
    for binding in sorted(
        device.interrupt_bindings,
        key=lambda item: (item.peripheral, item.line, item.interrupt),
    ):
        mapping.setdefault(binding.peripheral, []).append(binding)
    return {peripheral: tuple(items) for peripheral, items in sorted(mapping.items())}


def _dma_bindings_by_peripheral(
    device: CanonicalDeviceIR,
) -> dict[str, tuple[object, ...]]:
    mapping: dict[str, list[object]] = {}
    for binding in sorted(
        device.dma_bindings,
        key=lambda item: (item.peripheral, item.signal or "", item.controller, item.request_line),
    ):
        mapping.setdefault(binding.peripheral, []).append(binding)
    return {peripheral: tuple(items) for peripheral, items in sorted(mapping.items())}


def _offset_count_maps(
    grouped_items: dict[str, tuple[object, ...]],
) -> tuple[dict[str, int], dict[str, int]]:
    offsets: dict[str, int] = {}
    counts: dict[str, int] = {}
    next_offset = 0
    for peripheral_name in sorted(grouped_items):
        items = grouped_items[peripheral_name]
        offsets[peripheral_name] = next_offset
        counts[peripheral_name] = len(items)
        next_offset += len(items)
    return offsets, counts


def emit_device_descriptor_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    capability_overlay_count = len(_capability_overlay_rows(device))
    ref_catalog = _collect_runtime_ref_catalog((device,))
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    package_ref = _eref(
        "PackageRefId",
        ref_catalog["package_enum_map"],
        device.identity.device,
        device.identity.package,
    )
    core_ref = _semantic_enum_ref(
        "CoreId",
        semantics_catalog["core_enum_map"],
        device.identity.core,
    )
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "struct DeviceDescriptor {",
                "  PackageRefId package_id;",
                "  CoreId core_id;",
                "  int pin_count;",
                "  int peripheral_count;",
                "  int interrupt_count;",
                "  int memory_region_count;",
                "  int capability_overlay_count;",
                "  int startup_descriptor_count;",
                "};",
                "inline constexpr DeviceDescriptor kDeviceDescriptor = {",
                f"  {package_ref},",
                f"  {core_ref},",
                f"  {len(device.pins)},",
                f"  {len(device.peripherals)},",
                f"  {len(device.interrupts)},",
                f"  {len(device.memories)},",
                f"  {capability_overlay_count},",
                f"  {len(device.startup_descriptors)},",
                "};",
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            '#include "../../runtime_refs.hpp"',
            '#include "../../runtime_semantics.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_generated_path(family_dir, device.identity.device, "device_descriptor.hpp"),
        content=content,
    )


def emit_pins_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    ref_catalog = _collect_runtime_ref_catalog((device,))
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    package_pad_ids_by_pin = _package_pad_ids_by_pin(device)
    constraint_ids_by_pin = _constraint_ids_by_pin(device)
    pin_rows = [
        (
            pin.name,
            pin.port,
            pin.number,
            package_pad_ids_by_pin.get(pin.name, ()),
            constraint_ids_by_pin.get(pin.name, ()),
        )
        for pin in sorted(device.pins, key=_pin_key)
    ]
    pin_package_pad_rows = [
        (pin_name, pad_id)
        for pin_name, _port, _number, package_pad_ids, _constraint_ids in pin_rows
        for pad_id in package_pad_ids
    ]
    pin_constraint_rows = [
        (pin_name, constraint_id)
        for pin_name, _port, _number, _package_pad_ids, constraint_ids in pin_rows
        for constraint_id in constraint_ids
    ]
    pin_package_pad_map = {
        pin_name: tuple(pad_ids) for pin_name, _port, _number, pad_ids, _constraint_ids in pin_rows
    }
    pin_constraint_map = {
        pin_name: tuple(constraint_ids)
        for pin_name, _port, _number, _pad_ids, constraint_ids in pin_rows
    }
    pin_package_pad_offsets, pin_package_pad_counts = _offset_count_maps(pin_package_pad_map)
    pin_constraint_offsets, pin_constraint_counts = _offset_count_maps(pin_constraint_map)
    signal_rows = [
        (
            pin.name,
            signal.function,
            signal.peripheral,
            signal.signal,
            signal.af_number,
        )
        for pin in sorted(device.pins, key=_pin_key)
        for signal in sorted(
            pin.signals,
            key=lambda item: (
                item.function,
                item.peripheral or "",
                item.signal or "",
                -1 if item.af_number is None else item.af_number,
            ),
        )
    ]
    pin_descriptor_lines = []
    for pin_name, port, number, _package_pad_ids, _constraint_ids in pin_rows:
        pin_id = _enum_ref(
            "PinRefId",
            ref_catalog["pin_enum_map"],
            (device.identity.device, pin_name),
        )
        port_id = _semantic_enum_ref(
            "PortId",
            semantics_catalog["port_enum_map"],
            port,
        )
        pin_descriptor_lines.append(
            "  {"
            f"{pin_id}, "
            f"{port_id}, "
            f"{number}, "
            f"{pin_package_pad_offsets.get(pin_name, 0)}u, "
            f"{pin_package_pad_counts.get(pin_name, 0)}u, "
            f"{pin_constraint_offsets.get(pin_name, 0)}u, "
            f"{pin_constraint_counts.get(pin_name, 0)}u"
            "},"
        )
    pin_signal_lines = []
    for pin_name, function, peripheral, signal_name, af_number in signal_rows:
        pin_id = _enum_ref(
            "PinRefId",
            ref_catalog["pin_enum_map"],
            (device.identity.device, pin_name),
        )
        function_id = _semantic_enum_ref(
            "PinFunctionId",
            semantics_catalog["pin_function_enum_map"],
            function,
        )
        peripheral_id = _enum_ref(
            "PeripheralRefId",
            ref_catalog["peripheral_enum_map"],
            _device_ref_key(device.identity.device, peripheral),
        )
        signal_id = _semantic_enum_ref(
            "SignalId",
            semantics_catalog["signal_enum_map"],
            signal_name,
        )
        pin_signal_lines.append(
            "  {"
            f"{pin_id}, "
            f"{function_id}, "
            f"{peripheral_id}, "
            f"{signal_id}, "
            f"{-1 if af_number is None else af_number}"
            "},"
        )
    pin_package_pad_ref_lines = []
    for pin_name, pad_id in pin_package_pad_rows:
        pin_id = _enum_ref(
            "PinRefId",
            ref_catalog["pin_enum_map"],
            (device.identity.device, pin_name),
        )
        package_pad_id = _eref(
            "PackagePadRefId",
            ref_catalog["package_pad_enum_map"],
            device.identity.device,
            pad_id,
        )
        pin_package_pad_ref_lines.append(f"  {{{pin_id}, {package_pad_id}}},")
    pin_constraint_ref_lines = []
    for pin_name, constraint_id in pin_constraint_rows:
        pin_id = _enum_ref(
            "PinRefId",
            ref_catalog["pin_enum_map"],
            (device.identity.device, pin_name),
        )
        constraint_ref = _eref(
            "ConstraintRefId",
            ref_catalog["constraint_enum_map"],
            device.identity.device,
            constraint_id,
        )
        pin_constraint_ref_lines.append(f"  {{{pin_id}, {constraint_ref}}},")
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "struct PinDescriptor {",
                "  PinRefId pin_id;",
                "  PortId port_id;",
                "  int number;",
                "  std::uint16_t package_pad_offset;",
                "  std::uint16_t package_pad_count;",
                "  std::uint16_t constraint_offset;",
                "  std::uint16_t constraint_count;",
                "};",
                *_std_array_lines(
                    type_name="PinDescriptor",
                    variable_name="kPins",
                    row_lines=pin_descriptor_lines,
                ),
                "",
                "struct PinPackagePadRef {",
                "  PinRefId pin_id;",
                "  PackagePadRefId package_pad_id;",
                "};",
                *_std_array_lines(
                    type_name="PinPackagePadRef",
                    variable_name="kPinPackagePadRefs",
                    row_lines=pin_package_pad_ref_lines,
                ),
                "",
                "struct PinConstraintRef {",
                "  PinRefId pin_id;",
                "  ConstraintRefId constraint_id;",
                "};",
                *_std_array_lines(
                    type_name="PinConstraintRef",
                    variable_name="kPinConstraintRefs",
                    row_lines=pin_constraint_ref_lines,
                ),
                "",
                "struct PinSignalDescriptor {",
                "  PinRefId pin_id;",
                "  PinFunctionId function_id;",
                "  PeripheralRefId peripheral_id;",
                "  SignalId signal_id;",
                "  int af_number;",
                "};",
                *_std_array_lines(
                    type_name="PinSignalDescriptor",
                    variable_name="kPinSignals",
                    row_lines=pin_signal_lines,
                ),
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../runtime_refs.hpp"',
            '#include "../../runtime_semantics.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_generated_path(family_dir, device.identity.device, "pins.hpp"),
        content=content,
    )


def emit_peripheral_instances_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    bindings_by_peripheral = _binding_by_peripheral(device)
    overlay_ids_by_peripheral = {
        peripheral_name: tuple(
            capability.capability_id
            for capability in sorted(device.capabilities, key=lambda item: item.capability_id)
            if capability.scope != "ip-block" and capability.peripheral == peripheral_name
        )
        for peripheral_name in sorted(
            {
                capability.peripheral
                for capability in device.capabilities
                if capability.scope != "ip-block" and capability.peripheral is not None
            }
        )
    }
    interrupt_bindings_by_peripheral = _interrupt_bindings_by_peripheral(device)
    dma_bindings_by_peripheral = _dma_bindings_by_peripheral(device)
    overlay_offsets, overlay_counts = _offset_count_maps(overlay_ids_by_peripheral)
    interrupt_offsets, interrupt_counts = _offset_count_maps(interrupt_bindings_by_peripheral)
    dma_offsets, dma_counts = _offset_count_maps(dma_bindings_by_peripheral)
    register_count_by_peripheral: dict[str, int] = {}
    for register in device.registers:
        register_count_by_peripheral[register.peripheral] = (
            register_count_by_peripheral.get(register.peripheral, 0) + 1
        )

    sorted_peripherals = sorted(device.peripherals, key=lambda item: item.name)
    peripheral_rows: list[str] = []
    enum_rows = [f"  {_enum_identifier(peripheral.name)}," for peripheral in sorted_peripherals]
    for peripheral in sorted_peripherals:
        binding = bindings_by_peripheral.get(peripheral.name)
        clock_gate_id = None if binding is None else binding.clock_gate_id
        reset_id = None if binding is None else binding.reset_id
        selector_id = None if binding is None else binding.selector_id
        peripheral_class_ref = _semantic_enum_ref(
            "PeripheralClassId",
            semantics_catalog["peripheral_class_enum_map"],
            canonical_peripheral_class(peripheral.ip_name),
        )
        schema_ref = _semantic_enum_ref(
            "BackendSchemaId",
            semantics_catalog["backend_schema_enum_map"],
            peripheral.backend_schema_id,
        )
        peripheral_rows.append(
            "  {"
            f"PeripheralId::{_enum_identifier(peripheral.name)}, "
            f"{peripheral_class_ref}, "
            f"{schema_ref}, "
            f"{peripheral.instance}, "
            f"0x{peripheral.base_address:08X}u, "
            f"{_clock_gate_enum_ref(device.identity.device, clock_gate_id)}, "
            f"{_reset_enum_ref(device.identity.device, reset_id)}, "
            f"{_selector_enum_ref(device.identity.device, selector_id)}, "
            f"{interrupt_offsets.get(peripheral.name, 0)}u, "
            f"{interrupt_counts.get(peripheral.name, 0)}u, "
            f"{dma_offsets.get(peripheral.name, 0)}u, "
            f"{dma_counts.get(peripheral.name, 0)}u, "
            f"{overlay_offsets.get(peripheral.name, 0)}u, "
            f"{overlay_counts.get(peripheral.name, 0)}u, "
            f"{register_count_by_peripheral.get(peripheral.name, 0)}"
            "},"
        )
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "enum class PeripheralId : std::uint16_t {",
                *enum_rows,
                "};",
                "",
                "struct PeripheralInstanceDescriptor {",
                "  PeripheralId peripheral_id;",
                "  PeripheralClassId peripheral_class_id;",
                "  BackendSchemaId schema_id;",
                "  int instance;",
                "  std::uintptr_t base_address;",
                "  ClockGateId clock_gate_id;",
                "  ResetId reset_id;",
                "  ClockSelectorId selector_id;",
                "  std::uint16_t interrupt_binding_offset;",
                "  std::uint16_t interrupt_binding_count;",
                "  std::uint16_t dma_binding_offset;",
                "  std::uint16_t dma_binding_count;",
                "  std::uint16_t capability_overlay_offset;",
                "  std::uint16_t capability_overlay_count;",
                "  int register_count;",
                "};",
                *_std_array_lines(
                    type_name="PeripheralInstanceDescriptor",
                    variable_name="kPeripheralInstances",
                    row_lines=peripheral_rows,
                ),
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../clock_tree_lite.hpp"',
            '#include "../../runtime_semantics.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_generated_path(
            family_dir,
            device.identity.device,
            "peripheral_instances.hpp",
        ),
        content=content,
    )


def emit_capability_overlays_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    overlay_rows = _capability_overlay_rows(device)
    ref_catalog = _collect_runtime_ref_catalog((device,))
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    capability_overlay_lines: list[str] = []
    for (
        capability_id,
        scope,
        peripheral_class,
        name,
        value,
        ip_name,
        ip_version,
        peripheral,
        package_name,
    ) in overlay_rows:
        capability_id_ref = _semantic_enum_ref(
            "CapabilityId",
            semantics_catalog["capability_id_enum_map"],
            capability_id,
        )
        capability_scope_ref = _semantic_enum_ref(
            "CapabilityScopeId",
            semantics_catalog["capability_scope_enum_map"],
            scope,
        )
        peripheral_class_ref = _semantic_enum_ref(
            "PeripheralClassId",
            semantics_catalog["peripheral_class_enum_map"],
            peripheral_class,
        )
        capability_key_ref = _semantic_enum_ref(
            "CapabilityKeyId",
            semantics_catalog["capability_key_enum_map"],
            f"{name}={value}",
        )
        ip_block_ref = _semantic_enum_ref(
            "IpBlockId",
            semantics_catalog["ip_block_id_enum_map"],
            None if ip_name == "" or ip_version == "" else f"{ip_name}@{ip_version}",
        )
        peripheral_ref = (
            "PeripheralId::none"
            if peripheral == ""
            else f"PeripheralId::{_enum_identifier(peripheral)}"
        )
        package_ref = _eref(
            "PackageRefId",
            ref_catalog["package_enum_map"],
            device.identity.device,
            package_name,
        )
        capability_overlay_lines.append(
            "  {"
            f"{capability_id_ref}, "
            f"{capability_scope_ref}, "
            f"{peripheral_class_ref}, "
            f"{capability_key_ref}, "
            f"{ip_block_ref}, "
            f"{peripheral_ref}, "
            f"{package_ref}"
            "},"
        )
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "struct CapabilityOverlayDescriptor {",
                "  CapabilityId capability_id;",
                "  CapabilityScopeId scope_id;",
                "  PeripheralClassId peripheral_class_id;",
                "  CapabilityKeyId capability_key_id;",
                "  IpBlockId ip_block_id;",
                "  PeripheralId peripheral_id;",
                "  PackageRefId package_id;",
                "};",
                *_std_array_lines(
                    type_name="CapabilityOverlayDescriptor",
                    variable_name="kCapabilityOverlays",
                    row_lines=capability_overlay_lines,
                ),
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../runtime_refs.hpp"',
            '#include "../../runtime_semantics.hpp"',
            '#include "peripheral_instances.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_generated_path(
            family_dir,
            device.identity.device,
            "capability_overlays.hpp",
        ),
        content=content,
    )


def emit_runtime_profiles_header(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    rows: list[tuple[str | None, str, str, str]] = []
    seen: set[tuple[str | None, str, str, str]] = set()
    for device in devices:
        for peripheral in sorted(device.peripherals, key=lambda item: item.name):
            if peripheral.backend_schema_id is None:
                continue
            row = (
                canonical_peripheral_class(peripheral.ip_name),
                peripheral.backend_schema_id,
                "peripheral",
                peripheral.name,
            )
            if row not in seen:
                seen.add(row)
                rows.append(row)
        for operation in sorted(device.route_operations, key=lambda item: item.operation_id):
            if operation.schema_id is None:
                continue
            row = (
                None,
                operation.schema_id,
                "route-operation",
                operation.operation_id,
            )
            if row not in seen:
                seen.add(row)
                rows.append(row)

    semantics_catalog = _collect_runtime_semantics_catalog(devices)
    _vendor, _family = family_dir.split("/", 1)
    runtime_profile_rows = [
        (
            _semantic_enum_ref(
                "PeripheralClassId",
                semantics_catalog["peripheral_class_enum_map"],
                subsystem,
            ),
            _semantic_enum_ref(
                "BackendSchemaId",
                semantics_catalog["backend_schema_enum_map"],
                schema_id,
            ),
            _semantic_enum_ref(
                "RuntimeProfileSourceKind",
                semantics_catalog["runtime_profile_source_kind_enum_map"],
                source_kind,
            ),
            index,
        )
        for index, (subsystem, schema_id, source_kind, _source_id) in enumerate(rows)
    ]
    namespace_block = _cpp_namespace_block(
        (_vendor, _family, "generated"),
        "\n".join(
            [
                "struct RuntimeProfileDescriptor {",
                "  PeripheralClassId peripheral_class_id;",
                "  BackendSchemaId schema_id;",
                "  RuntimeProfileSourceKind source_kind;",
                "  std::uint16_t source_index;",
                "};",
                *_std_array_lines(
                    type_name="RuntimeProfileDescriptor",
                    variable_name="kRuntimeProfiles",
                    row_lines=[
                        f"  {{{subsystem_ref}, {schema_ref}, {source_kind_ref}, {index}u}},"
                        for (
                            subsystem_ref,
                            schema_ref,
                            source_kind_ref,
                            index,
                        ) in runtime_profile_rows
                    ],
                ),
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "runtime_semantics.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(path=f"{family_dir}/generated/runtime_profiles.hpp", content=content)


def emit_runtime_semantics_header(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    _vendor, _family = family_dir.split("/", 1)
    semantics_catalog = _collect_runtime_semantics_catalog(devices)
    enum_specs = [
        ("IpBlockId", semantics_catalog["ip_block_id_enum_map"]),
        ("CapabilityId", semantics_catalog["capability_id_enum_map"]),
        ("BackendSchemaId", semantics_catalog["backend_schema_enum_map"]),
        ("PeripheralClassId", semantics_catalog["peripheral_class_enum_map"]),
        ("CapabilityScopeId", semantics_catalog["capability_scope_enum_map"]),
        ("CapabilityKeyId", semantics_catalog["capability_key_enum_map"]),
        ("RouteKindId", semantics_catalog["route_kind_enum_map"]),
        ("RequirementKindId", semantics_catalog["requirement_kind_enum_map"]),
        ("OperationKindId", semantics_catalog["operation_kind_enum_map"]),
        ("OperationSubjectKindId", semantics_catalog["operation_subject_kind_enum_map"]),
        ("MemoryKindId", semantics_catalog["memory_kind_enum_map"]),
        ("StartupKindId", semantics_catalog["startup_kind_enum_map"]),
        ("VectorKindId", semantics_catalog["vector_kind_enum_map"]),
        ("PackagePadKindId", semantics_catalog["package_pad_kind_enum_map"]),
        ("BondingStateId", semantics_catalog["bonding_state_enum_map"]),
        ("ConstraintKindId", semantics_catalog["constraint_kind_enum_map"]),
        ("ActiveLevelId", semantics_catalog["active_level_enum_map"]),
        ("CoreId", semantics_catalog["core_enum_map"]),
        ("PortId", semantics_catalog["port_enum_map"]),
        ("PinFunctionId", semantics_catalog["pin_function_enum_map"]),
        ("AccessKindId", semantics_catalog["access_kind_enum_map"]),
        ("ConstraintValueId", semantics_catalog["constraint_value_enum_map"]),
        ("SignalId", semantics_catalog["signal_enum_map"]),
        ("SignalRoleId", semantics_catalog["signal_role_enum_map"]),
        ("DirectionId", semantics_catalog["direction_enum_map"]),
        ("RegisterProfileId", semantics_catalog["register_profile_enum_map"]),
        ("ClockNodeKindId", semantics_catalog["clock_node_kind_enum_map"]),
        (
            "RuntimeProfileSourceKind",
            semantics_catalog["runtime_profile_source_kind_enum_map"],
        ),
        ("StartupRoleId", semantics_catalog["startup_role_enum_map"]),
    ]
    body_lines: list[str] = []
    for enum_name, enum_map in enum_specs:
        body_lines.extend(
            [
                f"enum class {enum_name} : std::uint16_t {{",
                "  none,",
                *_enum_rows(enum_map, empty_identifier=None),
                "};",
                "",
            ]
        )
    namespace_block = _cpp_namespace_block((_vendor, _family, "generated"), "\n".join(body_lines))
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <cstdint>",
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(path=f"{family_dir}/generated/runtime_semantics.hpp", content=content)


def emit_runtime_refs_header(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    _vendor, _family = family_dir.split("/", 1)
    ref_catalog = _collect_runtime_ref_catalog(devices)
    semantics_catalog = _collect_runtime_semantics_catalog(devices)
    device_enum_map = ref_catalog["device_enum_map"]
    peripheral_rows = ref_catalog["peripheral_rows"]
    peripheral_enum_map = ref_catalog["peripheral_enum_map"]
    package_rows = ref_catalog["package_rows"]
    package_enum_map = ref_catalog["package_enum_map"]
    package_pad_rows = [
        (
            device.identity.device,
            package_pad.package,
            package_pad.pad_id,
            package_pad.bonded_pin,
            package_pad.physical_index,
            package_pad.pad_kind,
            package_pad.bonding_state,
        )
        for device in devices
        for package_pad in sorted(device.package_pads, key=lambda item: item.pad_id)
    ]
    package_pad_enum_map = ref_catalog["package_pad_enum_map"]
    pin_rows = ref_catalog["pin_rows"]
    pin_enum_map = ref_catalog["pin_enum_map"]
    constraint_rows = ref_catalog["constraint_rows"]
    constraint_enum_map = ref_catalog["constraint_enum_map"]
    selector_rows = ref_catalog["selector_rows"]
    selector_enum_map = ref_catalog["selector_enum_map"]
    register_rows = ref_catalog["register_rows"]
    register_enum_map = ref_catalog["register_enum_map"]
    register_field_rows = ref_catalog["register_field_rows"]
    register_field_enum_map = ref_catalog["register_field_enum_map"]
    ip_block_enum_map = ref_catalog["ip_block_enum_map"]
    capability_enum_map = ref_catalog["capability_enum_map"]

    device_descriptor_lines = []
    for device in sorted(devices, key=lambda item: item.identity.device):
        device_id = f"DeviceRefId::{device_enum_map[device.identity.device]}"
        package_ref = _eref(
            "PackageRefId",
            package_enum_map,
            device.identity.device,
            device.identity.package,
        )
        core_ref = _semantic_enum_ref(
            "CoreId",
            semantics_catalog["core_enum_map"],
            device.identity.core,
        )
        device_descriptor_lines.append(f"  {{{device_id}, {package_ref}, {core_ref}}},")

    peripheral_class_by_ref = {
        (device.identity.device, peripheral.name): canonical_peripheral_class(peripheral.ip_name)
        for device in devices
        for peripheral in device.peripherals
    }
    peripheral_descriptor_lines = []
    for device_name, peripheral_name in peripheral_rows:
        device_id = f"DeviceRefId::{device_enum_map[device_name]}"
        peripheral_id = _enum_ref(
            "PeripheralRefId",
            peripheral_enum_map,
            (device_name, peripheral_name),
        )
        peripheral_class_ref = _semantic_enum_ref(
            "PeripheralClassId",
            semantics_catalog["peripheral_class_enum_map"],
            peripheral_class_by_ref[(device_name, peripheral_name)],
        )
        peripheral_descriptor_lines.append(
            f"  {{{peripheral_id}, {device_id}, {peripheral_class_ref}}},"
        )

    package_descriptor_lines = []
    for device_name, package_name in package_rows:
        package_descriptor_lines.append(
            "  {"
            f"{_eref('PackageRefId', package_enum_map, device_name, package_name)}, "
            f"DeviceRefId::{device_enum_map[device_name]}"
            "},"
        )

    package_pad_descriptor_lines = []
    for (
        device_name,
        package_name,
        pad_id,
        bonded_pin,
        physical_index,
        pad_kind,
        bonding_state,
    ) in package_pad_rows:
        device_id = f"DeviceRefId::{device_enum_map[device_name]}"
        package_id = _eref("PackageRefId", package_enum_map, device_name, package_name)
        bonded_pin_id = _eref("PinRefId", pin_enum_map, device_name, bonded_pin)
        pad_kind_id = _semantic_enum_ref(
            "PackagePadKindId",
            semantics_catalog["package_pad_kind_enum_map"],
            pad_kind,
        )
        bonding_state_id = _semantic_enum_ref(
            "BondingStateId",
            semantics_catalog["bonding_state_enum_map"],
            bonding_state,
        )
        package_pad_descriptor_lines.append(
            "  {"
            f"{_eref('PackagePadRefId', package_pad_enum_map, device_name, pad_id)}, "
            f"{device_id}, "
            f"{package_id}, "
            f"{bonded_pin_id}, "
            f"{-1 if physical_index is None else physical_index}, "
            f"{pad_kind_id}, "
            f"{bonding_state_id}"
            "},"
        )

    pin_descriptor_lines = []
    for device_name, pin_name, port, pin_number in pin_rows:
        port_id = _semantic_enum_ref(
            "PortId",
            semantics_catalog["port_enum_map"],
            port,
        )
        pin_descriptor_lines.append(
            "  {"
            f"{_enum_ref('PinRefId', pin_enum_map, (device_name, pin_name))}, "
            f"DeviceRefId::{device_enum_map[device_name]}, "
            f"{port_id}, "
            f"{pin_number}"
            "},"
        )

    constraint_descriptor_lines = []
    for device_name, constraint_id, pin_name, kind, value in constraint_rows:
        constraint_kind_id = _semantic_enum_ref(
            "ConstraintKindId",
            semantics_catalog["constraint_kind_enum_map"],
            kind,
        )
        constraint_value_id = _semantic_enum_ref(
            "ConstraintValueId",
            semantics_catalog["constraint_value_enum_map"],
            value,
        )
        constraint_descriptor_lines.append(
            "  {"
            f"{_eref('ConstraintRefId', constraint_enum_map, device_name, constraint_id)}, "
            f"DeviceRefId::{device_enum_map[device_name]}, "
            f"{_eref('PinRefId', pin_enum_map, device_name, pin_name)}, "
            f"{constraint_kind_id}, "
            f"{constraint_value_id}"
            "},"
        )

    selector_descriptor_lines = []
    for device_name, selector_id, selector_value in selector_rows:
        selector_descriptor_lines.append(
            "  {"
            f"{_eref('SelectorRefId', selector_enum_map, device_name, selector_id)}, "
            f"DeviceRefId::{device_enum_map[device_name]}, "
            f"{selector_value}"
            "},"
        )

    register_descriptor_lines = []
    for device_name, register_id, peripheral_name, _register_name, offset_bytes in register_rows:
        register_descriptor_lines.append(
            "  {"
            f"{_eref('RegisterRefId', register_enum_map, device_name, register_id)}, "
            f"DeviceRefId::{device_enum_map[device_name]}, "
            f"{_enum_ref('PeripheralRefId', peripheral_enum_map, (device_name, peripheral_name))}, "
            f"{offset_bytes}u"
            "},"
        )

    register_field_descriptor_lines = []
    for (
        device_name,
        field_id,
        register_id,
        _peripheral_name,
        _field_name,
        bit_offset,
        bit_width,
    ) in register_field_rows:
        register_field_descriptor_lines.append(
            "  {"
            f"{_eref('RegisterFieldRefId', register_field_enum_map, device_name, field_id)}, "
            f"DeviceRefId::{device_enum_map[device_name]}, "
            f"{_eref('RegisterRefId', register_enum_map, device_name, register_id)}, "
            f"{bit_offset}u, "
            f"{bit_width}u"
            "},"
        )

    ip_block_rows = [
        (
            ip_block.ip_name,
            ip_block.ip_version,
            ip_block.peripheral_class,
            ip_block.backend_schema_id,
            ip_block.register_profile,
        )
        for device in devices
        for ip_block in sorted(
            device.ip_blocks,
            key=lambda item: (item.ip_name, item.ip_version),
        )
    ]
    ip_block_descriptor_lines = []
    for ip_name, ip_version, peripheral_class, backend_schema_id, register_profile in ip_block_rows:
        ip_block_id = f"{ip_name}@{ip_version}"
        ip_block_ref = _enum_ref("IpBlockRefId", ip_block_enum_map, (ip_name, ip_version))
        ip_block_id_ref = _semantic_enum_ref(
            "IpBlockId",
            semantics_catalog["ip_block_id_enum_map"],
            ip_block_id,
        )
        peripheral_class_ref = _semantic_enum_ref(
            "PeripheralClassId",
            semantics_catalog["peripheral_class_enum_map"],
            peripheral_class,
        )
        schema_ref = _semantic_enum_ref(
            "BackendSchemaId",
            semantics_catalog["backend_schema_enum_map"],
            backend_schema_id,
        )
        register_profile_ref = _semantic_enum_ref(
            "RegisterProfileId",
            semantics_catalog["register_profile_enum_map"],
            register_profile,
        )
        ip_block_descriptor_lines.append(
            "  {"
            f"{ip_block_ref}, "
            f"{ip_block_id_ref}, "
            f"{peripheral_class_ref}, "
            f"{schema_ref}, "
            f"{register_profile_ref}"
            "},"
        )

    capability_rows = [
        (
            device.identity.device,
            capability.capability_id,
            capability.scope,
            capability.peripheral_class,
            capability.name,
            capability.value,
            capability.ip_name,
            capability.ip_version,
            capability.peripheral,
            capability.package,
        )
        for device in devices
        for capability in sorted(device.capabilities, key=lambda item: item.capability_id)
    ]
    capability_descriptor_lines = []
    for (
        device_name,
        capability_id,
        scope,
        peripheral_class,
        name,
        value,
        ip_name,
        ip_version,
        peripheral,
        package_name,
    ) in capability_rows:
        ip_block_id = None
        if ip_name is not None and ip_version is not None:
            ip_block_id = f"{ip_name}@{ip_version}"
        capability_ref = _eref("CapabilityRefId", capability_enum_map, device_name, capability_id)
        capability_id_ref = _semantic_enum_ref(
            "CapabilityId",
            semantics_catalog["capability_id_enum_map"],
            capability_id,
        )
        capability_scope_ref = _semantic_enum_ref(
            "CapabilityScopeId",
            semantics_catalog["capability_scope_enum_map"],
            scope,
        )
        capability_class_ref = _semantic_enum_ref(
            "PeripheralClassId",
            semantics_catalog["peripheral_class_enum_map"],
            peripheral_class,
        )
        capability_key_ref = _semantic_enum_ref(
            "CapabilityKeyId",
            semantics_catalog["capability_key_enum_map"],
            f"{name}={value}",
        )
        ip_block_id_ref = _semantic_enum_ref(
            "IpBlockId",
            semantics_catalog["ip_block_id_enum_map"],
            ip_block_id,
        )
        package_ref = _eref("PackageRefId", package_enum_map, device_name, package_name)
        peripheral_ref = _enum_ref(
            "PeripheralRefId",
            peripheral_enum_map,
            _device_ref_key(device_name, peripheral),
        )
        capability_descriptor_lines.append(
            "  {"
            f"{capability_ref}, "
            f"DeviceRefId::{device_enum_map[device_name]}, "
            f"{capability_id_ref}, "
            f"{capability_scope_ref}, "
            f"{capability_class_ref}, "
            f"{capability_key_ref}, "
            f"{ip_block_id_ref}, "
            f"{package_ref}, "
            f"{peripheral_ref}"
            "},"
        )

    namespace_block = _cpp_namespace_block(
        (_vendor, _family, "generated"),
        "\n".join(
            [
                "enum class DeviceRefId : std::uint16_t {",
                "  none,",
                *_enum_rows(device_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class PeripheralRefId : std::uint16_t {",
                "  none,",
                *_enum_rows(peripheral_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class PackageRefId : std::uint16_t {",
                "  none,",
                *_enum_rows(package_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class PackagePadRefId : std::uint16_t {",
                "  none,",
                *_enum_rows(package_pad_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class StateRefId : std::uint16_t {",
                "  none,",
                "  selected,",
                "};",
                "",
                "enum class PinRefId : std::uint16_t {",
                "  none,",
                *_enum_rows(pin_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class ConstraintRefId : std::uint16_t {",
                "  none,",
                *_enum_rows(constraint_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class SelectorRefId : std::uint16_t {",
                "  none,",
                *_enum_rows(selector_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class IpBlockRefId : std::uint16_t {",
                "  none,",
                *_enum_rows(ip_block_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class CapabilityRefId : std::uint16_t {",
                "  none,",
                *_enum_rows(capability_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class RegisterRefId : std::uint16_t {",
                "  none,",
                *_enum_rows(register_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class RegisterFieldRefId : std::uint16_t {",
                "  none,",
                *_enum_rows(register_field_enum_map, empty_identifier=None),
                "};",
                "",
                "struct DeviceRefDescriptor {",
                "  DeviceRefId device_id;",
                "  PackageRefId selected_package_id;",
                "  CoreId core_id;",
                "};",
                *_std_array_lines(
                    type_name="DeviceRefDescriptor",
                    variable_name="kDeviceRefs",
                    row_lines=[
                        "  {DeviceRefId::none, PackageRefId::none, CoreId::none},",
                        *device_descriptor_lines,
                    ],
                ),
                "",
                "struct PeripheralRefDescriptor {",
                "  PeripheralRefId peripheral_id;",
                "  DeviceRefId device_id;",
                "  PeripheralClassId peripheral_class_id;",
                "};",
                *_std_array_lines(
                    type_name="PeripheralRefDescriptor",
                    variable_name="kPeripheralRefs",
                    row_lines=[
                        "  {PeripheralRefId::none, DeviceRefId::none, PeripheralClassId::none},",
                        *peripheral_descriptor_lines,
                    ],
                ),
                "",
                "struct PackageRefDescriptor {",
                "  PackageRefId package_id;",
                "  DeviceRefId device_id;",
                "};",
                *_std_array_lines(
                    type_name="PackageRefDescriptor",
                    variable_name="kPackageRefs",
                    row_lines=[
                        "  {PackageRefId::none, DeviceRefId::none},",
                        *package_descriptor_lines,
                    ],
                ),
                "",
                "struct PackagePadRefDescriptor {",
                "  PackagePadRefId package_pad_id;",
                "  DeviceRefId device_id;",
                "  PackageRefId package_id;",
                "  PinRefId bonded_pin_id;",
                "  int physical_index;",
                "  PackagePadKindId pad_kind_id;",
                "  BondingStateId bonding_state_id;",
                "};",
                *_std_array_lines(
                    type_name="PackagePadRefDescriptor",
                    variable_name="kPackagePadRefs",
                    row_lines=[
                        (
                            "  {PackagePadRefId::none, DeviceRefId::none, PackageRefId::none, "
                            "PinRefId::none, -1, PackagePadKindId::none, BondingStateId::none},"
                        ),
                        *package_pad_descriptor_lines,
                    ],
                ),
                "",
                "struct StateRefDescriptor {",
                "  StateRefId state_id;",
                "};",
                *_std_array_lines(
                    type_name="StateRefDescriptor",
                    variable_name="kStateRefs",
                    row_lines=[
                        "  {StateRefId::none},",
                        "  {StateRefId::selected},",
                    ],
                ),
                "",
                "struct PinRefDescriptor {",
                "  PinRefId pin_id;",
                "  DeviceRefId device_id;",
                "  PortId port_id;",
                "  int pin_number;",
                "};",
                *_std_array_lines(
                    type_name="PinRefDescriptor",
                    variable_name="kPinRefs",
                    row_lines=[
                        "  {PinRefId::none, DeviceRefId::none, PortId::none, -1},",
                        *pin_descriptor_lines,
                    ],
                ),
                "",
                "struct ConstraintRefDescriptor {",
                "  ConstraintRefId constraint_id;",
                "  DeviceRefId device_id;",
                "  PinRefId pin_id;",
                "  ConstraintKindId kind_id;",
                "  ConstraintValueId value_id;",
                "};",
                *_std_array_lines(
                    type_name="ConstraintRefDescriptor",
                    variable_name="kConstraintRefs",
                    row_lines=[
                        (
                            "  {ConstraintRefId::none, DeviceRefId::none, PinRefId::none, "
                            "ConstraintKindId::none, ConstraintValueId::none},"
                        ),
                        *constraint_descriptor_lines,
                    ],
                ),
                "",
                "struct SelectorRefDescriptor {",
                "  SelectorRefId selector_id;",
                "  DeviceRefId device_id;",
                "  int selector_value;",
                "};",
                *_std_array_lines(
                    type_name="SelectorRefDescriptor",
                    variable_name="kSelectorRefs",
                    row_lines=[
                        "  {SelectorRefId::none, DeviceRefId::none, -1},",
                        *selector_descriptor_lines,
                    ],
                ),
                "",
                "struct IpBlockRefDescriptor {",
                "  IpBlockRefId ip_block_ref_id;",
                "  IpBlockId ip_block_id;",
                "  PeripheralClassId peripheral_class_id;",
                "  BackendSchemaId schema_id;",
                "  RegisterProfileId register_profile_id;",
                "};",
                *_std_array_lines(
                    type_name="IpBlockRefDescriptor",
                    variable_name="kIpBlockRefs",
                    row_lines=[
                        (
                            "  {IpBlockRefId::none, IpBlockId::none, PeripheralClassId::none, "
                            "BackendSchemaId::none, RegisterProfileId::none},"
                        ),
                        *ip_block_descriptor_lines,
                    ],
                ),
                "",
                "struct CapabilityRefDescriptor {",
                "  CapabilityRefId capability_ref_id;",
                "  DeviceRefId device_id;",
                "  CapabilityId capability_id;",
                "  CapabilityScopeId scope_id;",
                "  PeripheralClassId peripheral_class_id;",
                "  CapabilityKeyId capability_key_id;",
                "  IpBlockId ip_block_id;",
                "  PackageRefId package_id;",
                "  PeripheralRefId peripheral_id;",
                "};",
                *_std_array_lines(
                    type_name="CapabilityRefDescriptor",
                    variable_name="kCapabilityRefs",
                    row_lines=[
                        (
                            "  {CapabilityRefId::none, DeviceRefId::none, CapabilityId::none, "
                            "CapabilityScopeId::none, PeripheralClassId::none, "
                            "CapabilityKeyId::none, "
                            "IpBlockId::none, PackageRefId::none, PeripheralRefId::none},"
                        ),
                        *capability_descriptor_lines,
                    ],
                ),
                "",
                "struct RegisterRefDescriptor {",
                "  RegisterRefId register_id;",
                "  DeviceRefId device_id;",
                "  PeripheralRefId peripheral_id;",
                "  std::uint32_t offset_bytes;",
                "};",
                *_std_array_lines(
                    type_name="RegisterRefDescriptor",
                    variable_name="kRegisterRefs",
                    row_lines=[
                        ("  {RegisterRefId::none, DeviceRefId::none, PeripheralRefId::none, 0u},"),
                        *register_descriptor_lines,
                    ],
                ),
                "",
                "struct RegisterFieldRefDescriptor {",
                "  RegisterFieldRefId field_id;",
                "  DeviceRefId device_id;",
                "  RegisterRefId register_id;",
                "  std::uint16_t bit_offset;",
                "  std::uint16_t bit_width;",
                "};",
                *_std_array_lines(
                    type_name="RegisterFieldRefDescriptor",
                    variable_name="kRegisterFieldRefs",
                    row_lines=[
                        (
                            "  {RegisterFieldRefId::none, DeviceRefId::none, "
                            "RegisterRefId::none, 0u, 0u},"
                        ),
                        *register_field_descriptor_lines,
                    ],
                ),
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "runtime_semantics.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(path=f"{family_dir}/generated/runtime_refs.hpp", content=content)


def emit_family_index(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    if not devices:
        raise ValueError("Family index emission requires at least one device.")
    first_device = devices[0]
    payload = {
        "schema_version": first_device.schema_version,
        "vendor": first_device.identity.vendor,
        "family": first_device.identity.family,
        "device_count": len(devices),
        "devices": [
            {
                "device": device.identity.device,
                "package": device.identity.package,
                "core": device.identity.core,
                "summary": device.identity.summary,
                "metadata_path": _device_metadata_path(family_dir, device.identity.device),
            }
            for device in sorted(devices, key=lambda item: item.identity.device)
        ],
    }
    return _text_artifact(
        path=_family_metadata_path(family_dir, "family-index.json"),
        artifact_kind="canonical-metadata",
        payload=payload,
    )


def emit_family_connectivity(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    if not devices:
        raise ValueError("Family connectivity emission requires at least one device.")
    first_device = devices[0]
    payload = {
        "schema_version": first_device.schema_version,
        "vendor": first_device.identity.vendor,
        "family": first_device.identity.family,
        "packages": _unique_packages(devices),
        "peripherals": _unique_peripherals(devices),
        "pins": _build_pin_catalog(devices),
        "interrupts": _unique_interrupts(devices),
        "dma_requests": _unique_dma_requests(devices),
    }
    return _text_artifact(
        path=_family_metadata_path(family_dir, "family-connectivity.json"),
        artifact_kind="canonical-metadata",
        payload=payload,
    )


def emit_ip_block_header(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
    ip_name: str,
    ip_version: str,
) -> EmittedArtifact:
    capability_map = {
        capability.capability_id: capability
        for device in devices
        for capability in device.capabilities
    }
    ip_block = next(
        ip_block
        for device in devices
        for ip_block in device.ip_blocks
        if ip_block.ip_name == ip_name and ip_block.ip_version == ip_version
    )
    capabilities = [
        capability_map[capability_id]
        for capability_id in ip_block.capability_ids
        if capability_id in capability_map
    ]
    semantics_catalog = _collect_runtime_semantics_catalog(devices)
    _vendor, _family = family_dir.split("/", 1)
    ip_block_id_ref = _semantic_enum_ref(
        "IpBlockId",
        semantics_catalog["ip_block_id_enum_map"],
        f"{ip_block.ip_name}@{ip_block.ip_version}",
    )
    ip_block_peripheral_class_ref = _semantic_enum_ref(
        "PeripheralClassId",
        semantics_catalog["peripheral_class_enum_map"],
        ip_block.peripheral_class,
    )
    ip_block_schema_ref = _semantic_enum_ref(
        "BackendSchemaId",
        semantics_catalog["backend_schema_enum_map"],
        ip_block.backend_schema_id,
    )
    register_profile_ref = _semantic_enum_ref(
        "RegisterProfileId",
        semantics_catalog["register_profile_enum_map"],
        ip_block.register_profile,
    )
    signal_role_refs = [
        _semantic_enum_ref(
            "SignalRoleId",
            semantics_catalog["signal_role_enum_map"],
            signal_role,
        )
        for signal_role in ip_block.signal_roles
    ]
    capability_descriptor_lines = []
    for capability in sorted(capabilities, key=lambda item: item.capability_id):
        capability_id_ref = _semantic_enum_ref(
            "CapabilityId",
            semantics_catalog["capability_id_enum_map"],
            capability.capability_id,
        )
        capability_scope_ref = _semantic_enum_ref(
            "CapabilityScopeId",
            semantics_catalog["capability_scope_enum_map"],
            capability.scope,
        )
        capability_class_ref = _semantic_enum_ref(
            "PeripheralClassId",
            semantics_catalog["peripheral_class_enum_map"],
            capability.peripheral_class,
        )
        capability_key_ref = _semantic_enum_ref(
            "CapabilityKeyId",
            semantics_catalog["capability_key_enum_map"],
            f"{capability.name}={capability.value}",
        )
        capability_descriptor_lines.append(
            "  {"
            f"{capability_id_ref}, "
            f"{capability_scope_ref}, "
            f"{capability_class_ref}, "
            f"{capability_key_ref}, "
            f"{ip_block_id_ref}"
            "},"
        )
    body_lines = [
        "struct IpBlockDescriptor {",
        "  IpBlockId ip_block_id;",
        "  PeripheralClassId peripheral_class_id;",
        "  BackendSchemaId schema_id;",
        "  RegisterProfileId register_profile_id;",
        "  std::uint16_t signal_role_offset;",
        "  std::uint16_t signal_role_count;",
        "};",
        "inline constexpr IpBlockDescriptor kIpBlock = {",
        f"  {ip_block_id_ref},",
        f"  {ip_block_peripheral_class_ref},",
        f"  {ip_block_schema_ref},",
        f"  {register_profile_ref},",
        "  0u,",
        f"  {len(ip_block.signal_roles)}u,",
        "};",
        "",
        "struct IpBlockSignalRoleRef {",
        "  IpBlockId ip_block_id;",
        "  SignalRoleId signal_role_id;",
        "};",
        *_std_array_lines(
            type_name="IpBlockSignalRoleRef",
            variable_name="kSignalRoles",
            row_lines=[
                f"  {{{ip_block_id_ref}, {signal_role_ref}}},"
                for signal_role_ref in signal_role_refs
            ],
        ),
        "",
        "struct CapabilityDescriptor {",
        "  CapabilityId capability_id;",
        "  CapabilityScopeId scope_id;",
        "  PeripheralClassId peripheral_class_id;",
        "  CapabilityKeyId capability_key_id;",
        "  IpBlockId ip_block_id;",
        "};",
        *_std_array_lines(
            type_name="CapabilityDescriptor",
            variable_name="kCapabilities",
            row_lines=capability_descriptor_lines,
        ),
    ]
    namespace_block = _cpp_namespace_block(
        (_vendor, _family, "generated", "ip"),
        "\n".join(body_lines),
    )
    filename = f"{_file_component(ip_name)}_{_file_component(ip_version)}.hpp"
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../runtime_semantics.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=f"{family_dir}/generated/ip/{filename}",
        content=content,
    )


def emit_ip_blocks_metadata(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    if not devices:
        raise ValueError("IP block emission requires at least one device.")
    first_device = devices[0]
    payload = {
        "schema_version": first_device.schema_version,
        "vendor": first_device.identity.vendor,
        "family": first_device.identity.family,
        "ip_blocks": _unique_ip_blocks(devices),
        "device_usage": [
            {
                "device": device.identity.device,
                "peripherals": [
                    {
                        "name": peripheral.name,
                        "ip_name": peripheral.ip_name,
                        "ip_version": peripheral.ip_version,
                        "base_address": peripheral.base_address,
                    }
                    for peripheral in sorted(device.peripherals, key=lambda item: item.name)
                ],
            }
            for device in sorted(devices, key=lambda item: item.identity.device)
        ],
    }
    return _text_artifact(
        path=_family_metadata_path(family_dir, "ip-blocks.json"),
        artifact_kind="canonical-metadata",
        payload=payload,
    )


def emit_capabilities_metadata(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    if not devices:
        raise ValueError("Capability emission requires at least one device.")
    first_device = devices[0]
    payload = {
        "schema_version": first_device.schema_version,
        "vendor": first_device.identity.vendor,
        "family": first_device.identity.family,
        "capabilities": _unique_capabilities(devices),
    }
    return _text_artifact(
        path=_family_metadata_path(family_dir, "capabilities.json"),
        artifact_kind="canonical-metadata",
        payload=payload,
    )


def emit_packages_metadata(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    if not devices:
        raise ValueError("Package emission requires at least one device.")
    first_device = devices[0]
    payload = {
        "schema_version": first_device.schema_version,
        "vendor": first_device.identity.vendor,
        "family": first_device.identity.family,
        "packages": _build_package_metadata(devices),
    }
    return _text_artifact(
        path=_family_metadata_path(family_dir, "packages.json"),
        artifact_kind="canonical-metadata",
        payload=payload,
    )


def emit_connectors_metadata(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    if not devices:
        raise ValueError("Connector emission requires at least one device.")
    first_device = devices[0]
    payload = {
        "schema_version": first_device.schema_version,
        "vendor": first_device.identity.vendor,
        "family": first_device.identity.family,
        "signal_endpoints": _unique_signal_endpoints(devices),
        "devices": [
            _device_connector_payload(device)
            for device in sorted(devices, key=lambda item: item.identity.device)
        ],
    }
    return _text_artifact(
        path=_family_metadata_path(family_dir, "connectors.json"),
        artifact_kind="canonical-metadata",
        payload=payload,
    )


def emit_system_descriptors_metadata(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    if not devices:
        raise ValueError("System descriptor emission requires at least one device.")
    first_device = devices[0]
    payload = {
        "schema_version": first_device.schema_version,
        "vendor": first_device.identity.vendor,
        "family": first_device.identity.family,
        "devices": [
            _device_system_descriptor_payload(device)
            for device in sorted(devices, key=lambda item: item.identity.device)
        ],
    }
    return _text_artifact(
        path=_family_metadata_path(family_dir, "system-descriptors.json"),
        artifact_kind="canonical-metadata",
        payload=payload,
    )


def emit_register_map_header(*, family_dir: str, device: CanonicalDeviceIR) -> EmittedArtifact:
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    device_id_ref = f"DeviceRefId::{_enum_identifier(device.identity.device)}"
    sorted_peripherals = sorted(device.peripherals, key=lambda item: item.name)
    register_rows = [
        (
            register.register_id,
            register.peripheral,
            register.name,
            register.offset_bytes,
            register.access,
            register.size_bits,
        )
        for register in sorted(
            device.registers,
            key=lambda item: (item.peripheral, item.offset_bytes, item.name),
        )
    ]
    register_descriptor_lines = []
    for (
        register_id,
        peripheral_name,
        _register_name,
        offset_bytes,
        access,
        size_bits,
    ) in register_rows:
        access_id = _semantic_enum_ref(
            "AccessKindId",
            semantics_catalog["access_kind_enum_map"],
            access,
        )
        register_descriptor_lines.append(
            f"  {{RegisterId::{_enum_identifier(register_id)}, "
            f"PeripheralId::{_enum_identifier(peripheral_name)}, "
            f"{offset_bytes}u, {access_id}, "
            f"{-1 if size_bits is None else size_bits}}},"
        )
    register_enum_rows = [
        f"  {_enum_identifier(register_id)}," for register_id, *_rest in register_rows
    ]
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                f"inline constexpr DeviceRefId kDeviceId = {device_id_ref};",
                "struct PeripheralBase {",
                "  PeripheralId peripheral_id;",
                "  std::uintptr_t address;",
                "};",
                *_std_array_lines(
                    type_name="PeripheralBase",
                    variable_name="kPeripheralBases",
                    row_lines=[
                        (
                            "  {"
                            f"PeripheralId::{_enum_identifier(peripheral.name)}, "
                            f"0x{peripheral.base_address:08X}u"
                            "},"
                        )
                        for peripheral in sorted_peripherals
                    ],
                ),
                "",
                "enum class RegisterId : std::uint16_t {",
                *register_enum_rows,
                "};",
                "",
                "struct RegisterDescriptor {",
                "  RegisterId register_id;",
                "  PeripheralId peripheral_id;",
                "  std::uint32_t offset_bytes;",
                "  AccessKindId access_id;",
                "  int size_bits;",
                "};",
                *_std_array_lines(
                    type_name="RegisterDescriptor",
                    variable_name="kRegisters",
                    row_lines=register_descriptor_lines,
                ),
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../runtime_refs.hpp"',
            '#include "../../runtime_semantics.hpp"',
            '#include "peripheral_instances.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_generated_path(family_dir, device.identity.device, "register_map.hpp"),
        content=content,
    )


def emit_register_fields_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    field_rows = [
        (
            field.field_id,
            field.register_id,
            field.peripheral,
            field.register_name,
            field.name,
            field.bit_offset,
            field.bit_width,
            field.access,
        )
        for field in sorted(
            device.register_fields,
            key=lambda item: (
                item.peripheral,
                item.register_name,
                item.bit_offset,
                item.name,
            ),
        )
    ]
    field_enum_rows = [f"  {_enum_identifier(field_id)}," for field_id, *_rest in field_rows]
    register_field_descriptor_lines = []
    for (
        field_id,
        register_id,
        peripheral_name,
        _register_name,
        _field_name,
        bit_offset,
        bit_width,
        access,
    ) in field_rows:
        access_id = _semantic_enum_ref(
            "AccessKindId",
            semantics_catalog["access_kind_enum_map"],
            access,
        )
        register_field_descriptor_lines.append(
            f"  {{FieldId::{_enum_identifier(field_id)}, "
            f"RegisterId::{_enum_identifier(register_id)}, "
            f"PeripheralId::{_enum_identifier(peripheral_name)}, "
            f"{bit_offset}u, {bit_width}u, {access_id}}},"
        )
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "enum class FieldId : std::uint16_t {",
                *field_enum_rows,
                "};",
                "",
                "struct RegisterFieldDescriptor {",
                "  FieldId field_id;",
                "  RegisterId register_id;",
                "  PeripheralId peripheral_id;",
                "  std::uint16_t bit_offset;",
                "  std::uint16_t bit_width;",
                "  AccessKindId access_id;",
                "};",
                *_std_array_lines(
                    type_name="RegisterFieldDescriptor",
                    variable_name="kRegisterFields",
                    row_lines=register_field_descriptor_lines,
                ),
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../runtime_semantics.hpp"',
            '#include "register_map.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_generated_path(family_dir, device.identity.device, "register_fields.hpp"),
        content=content,
    )


def emit_interrupt_bindings_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    binding_rows = [
        (
            binding.binding_id,
            binding.peripheral,
            binding.interrupt,
            binding.line,
            binding.vector_slot,
            binding.symbol_name,
            binding.shared_group,
        )
        for binding in sorted(
            device.interrupt_bindings,
            key=lambda item: (item.peripheral, item.line, item.interrupt),
        )
    ]
    alias_rows = [
        (binding.binding_id, alias_name)
        for binding in sorted(
            device.interrupt_bindings,
            key=lambda item: (item.peripheral, item.line, item.interrupt),
        )
        for alias_name in binding.alias_names
    ]
    alias_names_by_binding: dict[str, tuple[str, ...]] = {}
    for binding in device.interrupt_bindings:
        alias_names_by_binding[binding.binding_id] = tuple(binding.alias_names)
    alias_offsets, alias_counts = _offset_count_maps(alias_names_by_binding)
    binding_enum_rows = [
        f"  {_enum_identifier(binding_id)}," for binding_id, *_rest in binding_rows
    ]
    interrupt_enum_map = {
        interrupt_name: _enum_identifier(interrupt_name)
        for _binding_id, _peripheral_name, interrupt_name, *_rest in binding_rows
    }
    symbol_enum_map = {
        symbol_name: _enum_identifier(symbol_name)
        for (
            _binding_id,
            _peripheral_name,
            _interrupt_name,
            _line,
            _vector_slot,
            symbol_name,
            _shared_group,
        ) in binding_rows
        if symbol_name is not None
    }
    shared_group_enum_map = {
        shared_group: _enum_identifier(shared_group)
        for (
            _binding_id,
            _peripheral_name,
            _interrupt_name,
            _line,
            _vector_slot,
            _symbol_name,
            shared_group,
        ) in binding_rows
        if shared_group is not None
    }
    alias_enum_map = {
        alias_name: _enum_identifier(alias_name) for _binding_id, alias_name in alias_rows
    }
    interrupt_binding_lines = []
    for (
        binding_id,
        peripheral_name,
        interrupt_name,
        line,
        vector_slot,
        symbol_name,
        shared_group,
    ) in binding_rows:
        symbol_id = _enum_ref("InterruptSymbolId", symbol_enum_map, symbol_name)
        shared_group_id = _enum_ref(
            "InterruptSharedGroupId",
            shared_group_enum_map,
            shared_group,
        )
        interrupt_binding_lines.append(
            f"  {{InterruptBindingId::{_enum_identifier(binding_id)}, "
            f"PeripheralId::{_enum_identifier(peripheral_name)}, "
            f"{_enum_ref('InterruptId', interrupt_enum_map, interrupt_name)}, "
            f"{line}, {-1 if vector_slot is None else vector_slot}, "
            f"{symbol_id}, {shared_group_id}, "
            f"{alias_offsets.get(binding_id, 0)}u, "
            f"{alias_counts.get(binding_id, 0)}u}},"
        )
    interrupt_alias_lines = [
        f"  {{InterruptBindingId::{_enum_identifier(binding_id)}, "
        f"{_enum_ref('InterruptAliasId', alias_enum_map, alias_name)}}},"
        for binding_id, alias_name in alias_rows
    ]
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "enum class InterruptBindingId : std::uint16_t {",
                "  none,",
                *binding_enum_rows,
                "};",
                "",
                "enum class InterruptId : std::uint16_t {",
                "  none,",
                *_enum_rows(interrupt_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class InterruptSymbolId : std::uint16_t {",
                "  none,",
                *_enum_rows(symbol_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class InterruptSharedGroupId : std::uint16_t {",
                "  none,",
                *_enum_rows(shared_group_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class InterruptAliasId : std::uint16_t {",
                "  none,",
                *_enum_rows(alias_enum_map, empty_identifier=None),
                "};",
                "",
                "struct InterruptBindingDescriptor {",
                "  InterruptBindingId binding_id;",
                "  PeripheralId peripheral_id;",
                "  InterruptId interrupt_id;",
                "  int line;",
                "  int vector_slot;",
                "  InterruptSymbolId symbol_id;",
                "  InterruptSharedGroupId shared_group_id;",
                "  std::uint16_t alias_offset;",
                "  std::uint16_t alias_count;",
                "};",
                *_std_array_lines(
                    type_name="InterruptBindingDescriptor",
                    variable_name="kInterruptBindings",
                    row_lines=interrupt_binding_lines,
                ),
                "",
                "struct InterruptBindingAlias {",
                "  InterruptBindingId binding_id;",
                "  InterruptAliasId alias_id;",
                "};",
                *_std_array_lines(
                    type_name="InterruptBindingAlias",
                    variable_name="kInterruptBindingAliases",
                    row_lines=interrupt_alias_lines,
                ),
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "peripheral_instances.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_generated_path(
            family_dir,
            device.identity.device,
            "interrupt_bindings.hpp",
        ),
        content=content,
    )


def emit_dma_bindings_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    semantics_catalog = _collect_runtime_semantics_catalog((device,))
    binding_rows = [
        (
            binding.binding_id,
            binding.peripheral,
            binding.signal,
            binding.controller,
            binding.request_line,
            binding.route_id,
            binding.conflict_group,
        )
        for binding in sorted(
            device.dma_bindings,
            key=lambda item: (
                item.peripheral,
                item.signal or "",
                item.controller,
                item.request_line,
            ),
        )
    ]
    binding_enum_rows = [
        f"  {_enum_identifier(binding_id)}," for binding_id, *_rest in binding_rows
    ]
    controller_enum_map = {
        controller_name: _enum_identifier(controller_name)
        for _binding_id, _peripheral_name, _signal_name, controller_name, *_rest in binding_rows
    }
    request_line_enum_map = {
        request_line: _enum_identifier(request_line)
        for (
            _binding_id,
            _peripheral_name,
            _signal_name,
            _controller_name,
            request_line,
            *_rest,
        ) in binding_rows
    }
    route_id_enum_map = {
        route_id: _enum_identifier(route_id)
        for (
            _binding_id,
            _peripheral_name,
            _signal_name,
            _controller_name,
            _request_line,
            route_id,
            _conflict_group,
        ) in binding_rows
    }
    conflict_group_enum_map = {
        conflict_group: _enum_identifier(conflict_group)
        for (
            _binding_id,
            _peripheral_name,
            _signal_name,
            _controller_name,
            _request_line,
            _route_id,
            conflict_group,
        ) in binding_rows
        if conflict_group is not None
    }
    dma_binding_lines = []
    for (
        binding_id,
        peripheral_name,
        signal_name,
        controller_name,
        request_line,
        route_id,
        conflict_group,
    ) in binding_rows:
        signal_id = _semantic_enum_ref(
            "SignalId",
            semantics_catalog["signal_enum_map"],
            signal_name,
        )
        controller_id = _enum_ref("DmaControllerId", controller_enum_map, controller_name)
        request_line_id = _enum_ref(
            "DmaRequestLineId",
            request_line_enum_map,
            request_line,
        )
        route_id_ref = _enum_ref("DmaRouteId", route_id_enum_map, route_id)
        conflict_group_id = _enum_ref(
            "DmaConflictGroupId",
            conflict_group_enum_map,
            conflict_group,
        )
        dma_binding_lines.append(
            f"  {{DmaBindingId::{_enum_identifier(binding_id)}, "
            f"PeripheralId::{_enum_identifier(peripheral_name)}, "
            f"{signal_id}, {controller_id}, {request_line_id}, "
            f"{route_id_ref}, {conflict_group_id}}},"
        )
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "enum class DmaBindingId : std::uint16_t {",
                *binding_enum_rows,
                "};",
                "",
                "enum class DmaControllerId : std::uint16_t {",
                "  none,",
                *_enum_rows(controller_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class DmaRequestLineId : std::uint16_t {",
                "  none,",
                *_enum_rows(request_line_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class DmaRouteId : std::uint16_t {",
                "  none,",
                *_enum_rows(route_id_enum_map, empty_identifier=None),
                "};",
                "",
                "enum class DmaConflictGroupId : std::uint16_t {",
                "  none,",
                *_enum_rows(conflict_group_enum_map, empty_identifier=None),
                "};",
                "",
                "struct DmaBindingDescriptor {",
                "  DmaBindingId binding_id;",
                "  PeripheralId peripheral_id;",
                "  SignalId signal_id;",
                "  DmaControllerId controller_id;",
                "  DmaRequestLineId request_line_id;",
                "  DmaRouteId route_id;",
                "  DmaConflictGroupId conflict_group_id;",
                "};",
                *_std_array_lines(
                    type_name="DmaBindingDescriptor",
                    variable_name="kDmaBindings",
                    row_lines=dma_binding_lines,
                ),
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../runtime_semantics.hpp"',
            '#include "peripheral_instances.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_generated_path(
            family_dir,
            device.identity.device,
            "dma_bindings.hpp",
        ),
        content=content,
    )


def emit_gpio_header(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
    peripheral_name: str,
) -> EmittedArtifact:
    peripheral: PeripheralInstance | None = None
    peripheral_device_name: str | None = None
    peripheral_binding = None
    for device in devices:
        candidate = next(
            (item for item in device.peripherals if item.name == peripheral_name),
            None,
        )
        if candidate is None:
            continue
        peripheral = candidate
        peripheral_device_name = device.identity.device
        peripheral_binding = _binding_by_peripheral(device).get(peripheral_name)
        break
    if peripheral is None or peripheral_device_name is None:
        raise ValueError(f"Family GPIO emission requires peripheral {peripheral_name}.")
    _vendor, _family = family_dir.split("/", 1)
    semantics_catalog = _collect_runtime_semantics_catalog(devices)
    clock_gate_id = None if peripheral_binding is None else peripheral_binding.clock_gate_id
    reset_id = None if peripheral_binding is None else peripheral_binding.reset_id
    peripheral_class_ref = _semantic_enum_ref(
        "PeripheralClassId",
        semantics_catalog["peripheral_class_enum_map"],
        canonical_peripheral_class(peripheral.ip_name),
    )
    schema_ref = _semantic_enum_ref(
        "BackendSchemaId",
        semantics_catalog["backend_schema_enum_map"],
        peripheral.backend_schema_id,
    )
    namespace_block = _cpp_namespace_block(
        (_vendor, _family, "generated", "peripherals"),
        "\n".join(
            [
                "struct PeripheralDescriptor {",
                "  PeripheralClassId peripheral_class_id;",
                "  BackendSchemaId schema_id;",
                "  std::uintptr_t base_address;",
                "  ClockGateId clock_gate_id;",
                "  ResetId reset_id;",
                "};",
                "inline constexpr PeripheralDescriptor kPeripheral = {",
                f"  {peripheral_class_ref},",
                f"  {schema_ref},",
                f"  0x{peripheral.base_address:08X}u,",
                f"  {_clock_gate_enum_ref(peripheral_device_name, clock_gate_id)},",
                f"  {_reset_enum_ref(peripheral_device_name, reset_id)},",
                "};",
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <cstdint>",
            '#include "../clock_tree_lite.hpp"',
            '#include "../runtime_semantics.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=f"{family_dir}/generated/peripherals/{peripheral_name.lower()}.hpp",
        content=content,
    )


def emit_connector_tables_header(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    _vendor, _family = family_dir.split("/", 1)
    ref_catalog = _collect_runtime_ref_catalog(devices)
    semantics_catalog = _collect_runtime_semantics_catalog(devices)
    pin_enum_map = ref_catalog["pin_enum_map"]
    package_enum_map = ref_catalog["package_enum_map"]
    selector_enum_map = ref_catalog["selector_enum_map"]
    requirement_rows = [
        (
            device.identity.device,
            requirement.requirement_id,
            requirement.kind,
            requirement.target_ref_kind,
            requirement.target_ref_id,
            requirement.value_ref_kind,
            requirement.value_ref_id,
            requirement.value_int,
        )
        for device in devices
        for requirement in sorted(device.route_requirements, key=lambda item: item.requirement_id)
    ]
    operation_rows = [
        (
            device.identity.device,
            operation.operation_id,
            operation.kind,
            operation.schema_id,
            operation.subject_kind,
            operation.subject_id,
            operation.target_ref_kind,
            operation.target_ref_id,
            operation.value_ref_kind,
            operation.value_ref_id,
            operation.register_id,
            operation.register_field_id,
            operation.value_int,
        )
        for device in devices
        for operation in sorted(device.route_operations, key=lambda item: item.operation_id)
    ]
    candidate_rows = [
        (
            device.identity.device,
            candidate.candidate_id,
            candidate.pin,
            candidate.peripheral,
            candidate.signal,
            candidate.route_kind,
            candidate.route_selector,
            candidate.route_group_id,
            candidate.requirement_ids,
            candidate.operation_ids,
            candidate.capability_ids,
        )
        for device in devices
        for candidate in sorted(device.connection_candidates, key=lambda item: item.candidate_id)
    ]
    group_rows = [
        (
            device.identity.device,
            group.group_id,
            group.peripheral,
            group.signals,
            group.candidate_ids,
            group.package,
            group.conflict_group,
        )
        for device in devices
        for group in sorted(device.connection_groups, key=lambda item: item.group_id)
    ]
    endpoint_rows = [
        (
            device.identity.device,
            endpoint.endpoint_id,
            endpoint.peripheral_class,
            endpoint.signal,
            endpoint.direction,
        )
        for device in devices
        for endpoint in sorted(device.signal_endpoints, key=lambda item: item.endpoint_id)
    ]
    endpoint_enum_map = {
        (device_name, endpoint_id): _enum_identifier(f"{device_name}_{endpoint_id}")
        for device_name, endpoint_id, *_rest in endpoint_rows
    }
    clock_gate_enum_map = {
        (device.identity.device, gate.gate_id): _enum_identifier(
            f"{device.identity.device}_{gate.gate_id}"
        )
        for device in devices
        for gate in sorted(device.clock_gates, key=lambda item: item.gate_id)
    }
    reset_enum_map = {
        (device.identity.device, reset.reset_id): _enum_identifier(
            f"{device.identity.device}_{reset.reset_id}"
        )
        for device in devices
        for reset in sorted(device.resets, key=lambda item: item.reset_id)
    }
    clock_gate_index_map = _enum_index_map(clock_gate_enum_map)
    reset_index_map = _enum_index_map(reset_enum_map)
    requirement_enum_map = {
        (device_name, requirement_id): _enum_identifier(f"{device_name}_{requirement_id}")
        for device_name, requirement_id, *_rest in requirement_rows
    }
    operation_enum_map = {
        (device_name, operation_id): _enum_identifier(f"{device_name}_{operation_id}")
        for device_name, operation_id, *_rest in operation_rows
    }
    candidate_enum_map = {
        (device_name, candidate_id): _enum_identifier(f"{device_name}_{candidate_id}")
        for device_name, candidate_id, *_rest in candidate_rows
    }
    conflict_group_enum_map = {
        conflict_group: _enum_identifier(conflict_group)
        for (
            _device_name,
            _group_id,
            _peripheral,
            _signals,
            _candidate_ids,
            _package_name,
            conflict_group,
        ) in group_rows
        if conflict_group is not None
    }
    group_enum_map = {
        (device_name, group_id): _enum_identifier(f"{device_name}_{group_id}")
        for device_name, group_id, *_rest in group_rows
    }

    candidate_requirements_by_candidate = {
        (device_name, candidate_id): tuple(requirement_ids)
        for (
            device_name,
            candidate_id,
            _pin,
            _peripheral,
            _signal,
            _route_kind,
            _route_selector,
            _route_group_id,
            requirement_ids,
            _operation_ids,
            _capability_ids,
        ) in candidate_rows
    }
    candidate_operations_by_candidate = {
        (device_name, candidate_id): tuple(operation_ids)
        for (
            device_name,
            candidate_id,
            _pin,
            _peripheral,
            _signal,
            _route_kind,
            _route_selector,
            _route_group_id,
            _requirement_ids,
            operation_ids,
            _capability_ids,
        ) in candidate_rows
    }
    candidate_capabilities_by_candidate = {
        (device_name, candidate_id): tuple(capability_ids)
        for (
            device_name,
            candidate_id,
            _pin,
            _peripheral,
            _signal,
            _route_kind,
            _route_selector,
            _route_group_id,
            _requirement_ids,
            _operation_ids,
            capability_ids,
        ) in candidate_rows
    }
    candidate_requirement_offsets, candidate_requirement_counts = _offset_count_maps(
        candidate_requirements_by_candidate
    )
    candidate_operation_offsets, candidate_operation_counts = _offset_count_maps(
        candidate_operations_by_candidate
    )
    candidate_capability_offsets, candidate_capability_counts = _offset_count_maps(
        candidate_capabilities_by_candidate
    )
    candidate_requirement_ref_rows = [
        (device_name, candidate_id, requirement_id)
        for (device_name, candidate_id), requirement_ids in sorted(
            candidate_requirements_by_candidate.items()
        )
        for requirement_id in requirement_ids
    ]
    candidate_operation_ref_rows = [
        (device_name, candidate_id, operation_id)
        for (device_name, candidate_id), operation_ids in sorted(
            candidate_operations_by_candidate.items()
        )
        for operation_id in operation_ids
    ]
    candidate_capability_ref_rows = [
        (device_name, candidate_id, capability_id)
        for (device_name, candidate_id), capability_ids in sorted(
            candidate_capabilities_by_candidate.items()
        )
        for capability_id in capability_ids
    ]
    group_signals_by_group = {
        (device_name, group_id): tuple(signals)
        for (
            device_name,
            group_id,
            _peripheral,
            signals,
            _candidate_ids,
            _package_name,
            _conflict_group,
        ) in group_rows
    }
    group_candidates_by_group = {
        (device_name, group_id): tuple(candidate_ids)
        for (
            device_name,
            group_id,
            _peripheral,
            _signals,
            candidate_ids,
            _package_name,
            _conflict_group,
        ) in group_rows
    }
    group_signal_offsets, group_signal_counts = _offset_count_maps(group_signals_by_group)
    group_candidate_offsets, group_candidate_counts = _offset_count_maps(group_candidates_by_group)
    group_signal_rows = [
        (device_name, group_id, signal_name)
        for (device_name, group_id), signals in sorted(group_signals_by_group.items())
        for signal_name in signals
    ]
    group_candidate_ref_rows = [
        (device_name, group_id, candidate_id)
        for (device_name, group_id), candidate_ids in sorted(group_candidates_by_group.items())
        for candidate_id in candidate_ids
    ]

    endpoint_row_lines: list[str] = []
    for device_name, endpoint_id, peripheral_class, signal, direction in endpoint_rows:
        peripheral_class_ref = _semantic_enum_ref(
            "PeripheralClassId",
            semantics_catalog["peripheral_class_enum_map"],
            peripheral_class,
        )
        signal_ref = _semantic_enum_ref(
            "SignalId",
            semantics_catalog["signal_enum_map"],
            signal,
        )
        direction_ref = _semantic_enum_ref(
            "DirectionId",
            semantics_catalog["direction_enum_map"],
            direction,
        )
        endpoint_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"SignalEndpointId::{endpoint_enum_map[(device_name, endpoint_id)]}, "
            f"{peripheral_class_ref}, "
            f"{signal_ref}, "
            f"{direction_ref}"
            "},"
        )

    requirement_row_lines: list[str] = []
    for (
        device_name,
        requirement_id,
        kind,
        target_ref_kind,
        target_ref_id,
        value_ref_kind,
        value_ref_id,
        value_int,
    ) in requirement_rows:
        kind_ref = _semantic_enum_ref(
            "RequirementKindId",
            semantics_catalog["requirement_kind_enum_map"],
            kind,
        )
        target_ref = _runtime_ref_literal(
            device_name,
            target_ref_kind,
            target_ref_id,
            ref_catalog,
            clock_gate_index_map,
            reset_index_map,
        )
        value_ref = _runtime_ref_literal(
            device_name,
            value_ref_kind,
            value_ref_id,
            ref_catalog,
            clock_gate_index_map,
            reset_index_map,
        )
        requirement_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"RouteRequirementId::{requirement_enum_map[(device_name, requirement_id)]}, "
            f"{kind_ref}, "
            f"{target_ref}, "
            f"{value_ref}, "
            f"{-1 if value_int is None else value_int}"
            "},"
        )

    operation_row_lines: list[str] = []
    for (
        device_name,
        operation_id,
        kind,
        schema_id,
        subject_kind,
        subject_id,
        target_ref_kind,
        target_ref_id,
        value_ref_kind,
        value_ref_id,
        register_id,
        register_field_id,
        value_int,
    ) in operation_rows:
        kind_ref = _semantic_enum_ref(
            "OperationKindId",
            semantics_catalog["operation_kind_enum_map"],
            kind,
        )
        schema_ref = _semantic_enum_ref(
            "BackendSchemaId",
            semantics_catalog["backend_schema_enum_map"],
            schema_id,
        )
        subject_ref = _runtime_ref_literal(
            device_name,
            subject_kind,
            subject_id,
            ref_catalog,
        )
        target_ref = _runtime_ref_literal(
            device_name,
            target_ref_kind,
            target_ref_id,
            ref_catalog,
            clock_gate_index_map,
            reset_index_map,
        )
        value_ref = _runtime_ref_literal(
            device_name,
            value_ref_kind,
            value_ref_id,
            ref_catalog,
            clock_gate_index_map,
            reset_index_map,
        )
        register_ref = _eref(
            "RegisterRefId",
            ref_catalog["register_enum_map"],
            device_name,
            register_id,
        )
        register_field_ref = _eref(
            "RegisterFieldRefId",
            ref_catalog["register_field_enum_map"],
            device_name,
            register_field_id,
        )
        operation_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"RouteOperationId::{operation_enum_map[(device_name, operation_id)]}, "
            f"{kind_ref}, "
            f"{schema_ref}, "
            f"{subject_ref}, "
            f"{target_ref}, "
            f"{value_ref}, "
            f"{register_ref}, "
            f"{register_field_ref}, "
            f"{-1 if value_int is None else value_int}"
            "},"
        )

    candidate_descriptor_row_lines: list[str] = []
    for (
        device_name,
        candidate_id,
        pin,
        peripheral,
        signal,
        route_kind,
        route_selector,
        route_group_id,
        _requirement_ids,
        _operation_ids,
        _capability_ids,
    ) in candidate_rows:
        pin_ref = _enum_ref("PinRefId", pin_enum_map, (device_name, pin))
        peripheral_ref = _enum_ref(
            "PeripheralRefId",
            ref_catalog["peripheral_enum_map"],
            (device_name, peripheral),
        )
        signal_ref = _semantic_enum_ref(
            "SignalId",
            semantics_catalog["signal_enum_map"],
            signal,
        )
        route_kind_ref = _semantic_enum_ref(
            "RouteKindId",
            semantics_catalog["route_kind_enum_map"],
            route_kind,
        )
        selector_ref = _eref(
            "SelectorRefId",
            selector_enum_map,
            device_name,
            route_selector,
        )
        group_ref = _enum_ref(
            "ConnectionGroupId",
            group_enum_map,
            _device_ref_key(device_name, route_group_id),
        )
        candidate_descriptor_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"ConnectionCandidateId::{candidate_enum_map[(device_name, candidate_id)]}, "
            f"{pin_ref}, "
            f"{peripheral_ref}, "
            f"{signal_ref}, "
            f"{route_kind_ref}, "
            f"{selector_ref}, "
            f"{group_ref}, "
            f"{candidate_requirement_offsets.get((device_name, candidate_id), 0)}u, "
            f"{candidate_requirement_counts.get((device_name, candidate_id), 0)}u, "
            f"{candidate_operation_offsets.get((device_name, candidate_id), 0)}u, "
            f"{candidate_operation_counts.get((device_name, candidate_id), 0)}u, "
            f"{candidate_capability_offsets.get((device_name, candidate_id), 0)}u, "
            f"{candidate_capability_counts.get((device_name, candidate_id), 0)}u"
            "},"
        )

    candidate_capability_row_lines = []
    for device_name, candidate_id, capability_id in candidate_capability_ref_rows:
        capability_ref = _eref(
            "CapabilityRefId",
            ref_catalog["capability_enum_map"],
            device_name,
            capability_id,
        )
        candidate_capability_row_lines.append(
            "  {"
            f"ConnectionCandidateId::{candidate_enum_map[(device_name, candidate_id)]}, "
            f"{capability_ref}"
            "},"
        )

    group_descriptor_row_lines: list[str] = []
    for (
        device_name,
        group_id,
        peripheral,
        _signals,
        _candidate_ids,
        package_name,
        conflict_group,
    ) in group_rows:
        peripheral_ref = _enum_ref(
            "PeripheralRefId",
            ref_catalog["peripheral_enum_map"],
            (device_name, peripheral),
        )
        package_ref = _eref(
            "PackageRefId",
            package_enum_map,
            device_name,
            package_name,
        )
        conflict_ref = _enum_ref(
            "ConnectionConflictGroupId",
            conflict_group_enum_map,
            conflict_group,
        )
        group_descriptor_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"ConnectionGroupId::{group_enum_map[(device_name, group_id)]}, "
            f"{peripheral_ref}, "
            f"{package_ref}, "
            f"{conflict_ref}, "
            f"{group_signal_offsets.get((device_name, group_id), 0)}u, "
            f"{group_signal_counts.get((device_name, group_id), 0)}u, "
            f"{group_candidate_offsets.get((device_name, group_id), 0)}u, "
            f"{group_candidate_counts.get((device_name, group_id), 0)}u"
            "},"
        )

    group_signal_row_lines = [
        "  {"
        f"ConnectionGroupId::{group_enum_map[(device_name, group_id)]}, "
        f"{_semantic_enum_ref('SignalId', semantics_catalog['signal_enum_map'], signal_name)}"
        "},"
        for device_name, group_id, signal_name in group_signal_rows
    ]

    body_lines = [
        "enum class RuntimeRefDomain : std::uint8_t {",
        "  none,",
        "  package,",
        "  package_pad,",
        "  peripheral,",
        "  state,",
        "  pin,",
        "  constraint,",
        "  selector,",
        "  ip_block,",
        "  capability,",
        "  clock_gate,",
        "  reset,",
        "  register_ref,",
        "  register_field_ref,",
        "  integer,",
        "  other,",
        "};",
        "",
        "struct RuntimeRef {",
        "  RuntimeRefDomain domain;",
        "  std::uint16_t index;",
        "};",
        "",
        "enum class SignalEndpointId : std::uint16_t {",
        "  none,",
        *_enum_rows(endpoint_enum_map, empty_identifier=None),
        "};",
        "",
        "struct SignalEndpointDescriptor {",
        "  DeviceRefId device_id;",
        "  SignalEndpointId endpoint_id;",
        "  PeripheralClassId peripheral_class_id;",
        "  SignalId signal_id;",
        "  DirectionId direction_id;",
        "};",
        *_std_array_lines(
            type_name="SignalEndpointDescriptor",
            variable_name="kSignalEndpoints",
            row_lines=endpoint_row_lines,
        ),
        "",
        "enum class RouteRequirementId : std::uint16_t {",
        "  none,",
        *_enum_rows(requirement_enum_map, empty_identifier=None),
        "};",
        "",
        "struct RouteRequirementDescriptor {",
        "  DeviceRefId device_id;",
        "  RouteRequirementId requirement_id;",
        "  RequirementKindId kind_id;",
        "  RuntimeRef target_ref;",
        "  RuntimeRef value_ref;",
        "  int value_int;",
        "};",
        *_std_array_lines(
            type_name="RouteRequirementDescriptor",
            variable_name="kRouteRequirements",
            row_lines=requirement_row_lines,
        ),
        "",
        "enum class RouteOperationId : std::uint16_t {",
        "  none,",
        *_enum_rows(operation_enum_map, empty_identifier=None),
        "};",
        "",
        "struct RouteOperationDescriptor {",
        "  DeviceRefId device_id;",
        "  RouteOperationId operation_id;",
        "  OperationKindId kind_id;",
        "  BackendSchemaId schema_id;",
        "  RuntimeRef subject_ref;",
        "  RuntimeRef target_ref;",
        "  RuntimeRef value_ref;",
        "  RegisterRefId register_id;",
        "  RegisterFieldRefId register_field_id;",
        "  int value_int;",
        "};",
        *_std_array_lines(
            type_name="RouteOperationDescriptor",
            variable_name="kRouteOperations",
            row_lines=operation_row_lines,
        ),
        "",
        "enum class ConnectionCandidateId : std::uint16_t {",
        "  none,",
        *_enum_rows(candidate_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class ConnectionConflictGroupId : std::uint16_t {",
        "  none,",
        *_enum_rows(conflict_group_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class ConnectionGroupId : std::uint16_t {",
        "  none,",
        *_enum_rows(group_enum_map, empty_identifier=None),
        "};",
        "",
        "struct ConnectionCandidateDescriptor {",
        "  DeviceRefId device_id;",
        "  ConnectionCandidateId candidate_id;",
        "  PinRefId pin_id;",
        "  PeripheralRefId peripheral_id;",
        "  SignalId signal_id;",
        "  RouteKindId route_kind_id;",
        "  SelectorRefId route_selector_id;",
        "  ConnectionGroupId route_group_id;",
        "  std::uint16_t requirement_offset;",
        "  std::uint16_t requirement_count;",
        "  std::uint16_t operation_offset;",
        "  std::uint16_t operation_count;",
        "  std::uint16_t capability_offset;",
        "  std::uint16_t capability_count;",
        "};",
        *_std_array_lines(
            type_name="ConnectionCandidateDescriptor",
            variable_name="kConnectionCandidates",
            row_lines=candidate_descriptor_row_lines,
        ),
        "",
        "struct CandidateRequirementRef {",
        "  ConnectionCandidateId candidate_id;",
        "  RouteRequirementId requirement_id;",
        "};",
        *_std_array_lines(
            type_name="CandidateRequirementRef",
            variable_name="kCandidateRequirementRefs",
            row_lines=[
                "  {"
                f"ConnectionCandidateId::{candidate_enum_map[(device_name, candidate_id)]}, "
                f"RouteRequirementId::{requirement_enum_map[(device_name, requirement_id)]}"
                "},"
                for device_name, candidate_id, requirement_id in candidate_requirement_ref_rows
            ],
        ),
        "",
        "struct CandidateOperationRef {",
        "  ConnectionCandidateId candidate_id;",
        "  RouteOperationId operation_id;",
        "};",
        *_std_array_lines(
            type_name="CandidateOperationRef",
            variable_name="kCandidateOperationRefs",
            row_lines=[
                "  {"
                f"ConnectionCandidateId::{candidate_enum_map[(device_name, candidate_id)]}, "
                f"RouteOperationId::{operation_enum_map[(device_name, operation_id)]}"
                "},"
                for device_name, candidate_id, operation_id in candidate_operation_ref_rows
            ],
        ),
        "",
        "struct CandidateCapabilityRef {",
        "  ConnectionCandidateId candidate_id;",
        "  CapabilityRefId capability_id;",
        "};",
        *_std_array_lines(
            type_name="CandidateCapabilityRef",
            variable_name="kCandidateCapabilityRefs",
            row_lines=candidate_capability_row_lines,
        ),
        "",
        "struct ConnectionGroupDescriptor {",
        "  DeviceRefId device_id;",
        "  ConnectionGroupId group_id;",
        "  PeripheralRefId peripheral_id;",
        "  PackageRefId package_id;",
        "  ConnectionConflictGroupId conflict_group_id;",
        "  std::uint16_t signal_offset;",
        "  std::uint16_t signal_count;",
        "  std::uint16_t candidate_offset;",
        "  std::uint16_t candidate_count;",
        "};",
        *_std_array_lines(
            type_name="ConnectionGroupDescriptor",
            variable_name="kConnectionGroups",
            row_lines=group_descriptor_row_lines,
        ),
        "",
        "struct ConnectionGroupSignalRef {",
        "  ConnectionGroupId group_id;",
        "  SignalId signal_id;",
        "};",
        *_std_array_lines(
            type_name="ConnectionGroupSignalRef",
            variable_name="kConnectionGroupSignals",
            row_lines=group_signal_row_lines,
        ),
        "",
        "struct ConnectionGroupCandidateRef {",
        "  ConnectionGroupId group_id;",
        "  ConnectionCandidateId candidate_id;",
        "};",
        *_std_array_lines(
            type_name="ConnectionGroupCandidateRef",
            variable_name="kConnectionGroupCandidateRefs",
            row_lines=[
                "  {"
                f"ConnectionGroupId::{group_enum_map[(device_name, group_id)]}, "
                f"ConnectionCandidateId::{candidate_enum_map[(device_name, candidate_id)]}"
                "},"
                for device_name, group_id, candidate_id in group_candidate_ref_rows
            ],
        ),
    ]
    namespace_block = _cpp_namespace_block((_vendor, _family, "generated"), "\n".join(body_lines))
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "runtime_refs.hpp"',
            '#include "runtime_semantics.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(path=f"{family_dir}/generated/connector_tables.hpp", content=content)


def emit_interrupt_map_header(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    ref_catalog = _collect_runtime_ref_catalog(devices)
    rows: list[
        tuple[
            str,
            str,
            int,
            str | None,
            str | None,
            tuple[str, ...],
            int | None,
            str | None,
        ]
    ] = []
    for device in devices:
        vector_map = {
            vector_slot.interrupt: vector_slot
            for vector_slot in device.vector_slots
            if vector_slot.interrupt is not None
        }
        for interrupt in sorted(device.interrupts, key=lambda item: (item.line, item.name)):
            vector_slot = vector_map.get(interrupt.name)
            rows.append(
                (
                    device.identity.device,
                    interrupt.name,
                    interrupt.line,
                    interrupt.peripheral,
                    interrupt.shared_group,
                    interrupt.alias_names,
                    None if vector_slot is None else vector_slot.slot,
                    None if vector_slot is None else vector_slot.symbol_name,
                )
            )

    _vendor, _family = family_dir.split("/", 1)
    interrupt_enum_map = {
        (device_name, interrupt_name): _enum_identifier(f"{device_name}_{interrupt_name}")
        for device_name, interrupt_name, *_rest in rows
    }
    row_fields = [
        (
            device_name,
            interrupt_name,
            line,
            peripheral,
            shared_group,
            alias_names,
            vector_slot,
            symbol_name,
        )
        for (
            device_name,
            interrupt_name,
            line,
            peripheral,
            shared_group,
            alias_names,
            vector_slot,
            symbol_name,
        ) in rows
    ]
    symbol_enum_map = {
        symbol_name: _enum_identifier(symbol_name)
        for (
            _device_name,
            _interrupt_name,
            _line,
            _peripheral,
            _shared_group,
            _alias_names,
            _vector_slot,
            symbol_name,
        ) in row_fields
        if symbol_name is not None
    }
    shared_group_enum_map = {
        shared_group: _enum_identifier(shared_group)
        for (
            _device_name,
            _interrupt_name,
            _line,
            _peripheral,
            shared_group,
            _alias_names,
            _vector_slot,
            _symbol_name,
        ) in row_fields
        if shared_group is not None
    }
    alias_rows = [
        (device_name, interrupt_name, alias_name)
        for (
            device_name,
            interrupt_name,
            _line,
            _peripheral,
            _shared_group,
            alias_names,
            _vector_slot,
            _symbol_name,
        ) in row_fields
        for alias_name in alias_names
    ]
    alias_enum_map = {
        alias_name: _enum_identifier(alias_name)
        for _device_name, _interrupt_name, alias_name in alias_rows
    }
    interrupt_alias_map = {
        (device_name, interrupt_name): tuple(alias_names)
        for (
            device_name,
            interrupt_name,
            _line,
            _peripheral,
            _shared_group,
            alias_names,
            _vector_slot,
            _symbol_name,
        ) in row_fields
    }
    alias_offsets, alias_counts = _offset_count_maps(interrupt_alias_map)
    interrupt_row_lines: list[str] = []
    for (
        device_name,
        interrupt_name,
        line,
        peripheral,
        shared_group,
        _alias_names,
        vector_slot,
        symbol_name,
    ) in row_fields:
        peripheral_ref = _enum_ref(
            "PeripheralRefId",
            ref_catalog["peripheral_enum_map"],
            _device_ref_key(device_name, peripheral),
        )
        interrupt_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"InterruptMapId::{interrupt_enum_map[(device_name, interrupt_name)]}, "
            f"{line}, "
            f"{peripheral_ref}, "
            f"{_enum_ref('InterruptMapSharedGroupId', shared_group_enum_map, shared_group)}, "
            f"{alias_offsets.get((device_name, interrupt_name), 0)}u, "
            f"{alias_counts.get((device_name, interrupt_name), 0)}u, "
            f"{-1 if vector_slot is None else vector_slot}, "
            f"{_enum_ref('InterruptMapSymbolId', symbol_enum_map, symbol_name)}"
            "},"
        )
    body_lines = [
        "enum class InterruptMapId : std::uint16_t {",
        "  none,",
        *_enum_rows(interrupt_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class InterruptMapSymbolId : std::uint16_t {",
        "  none,",
        *_enum_rows(symbol_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class InterruptMapSharedGroupId : std::uint16_t {",
        "  none,",
        *_enum_rows(shared_group_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class InterruptMapAliasId : std::uint16_t {",
        "  none,",
        *_enum_rows(alias_enum_map, empty_identifier=None),
        "};",
        "",
        "struct InterruptDescriptor {",
        "  DeviceRefId device_id;",
        "  InterruptMapId interrupt_id;",
        "  int line;",
        "  PeripheralRefId peripheral_id;",
        "  InterruptMapSharedGroupId shared_group_id;",
        "  std::uint16_t alias_offset;",
        "  std::uint16_t alias_count;",
        "  int vector_slot;",
        "  InterruptMapSymbolId symbol_id;",
        "};",
        "inline constexpr InterruptDescriptor kInterruptMap[] = {",
        *interrupt_row_lines,
        "};",
        "",
        "struct InterruptAliasRef {",
        "  InterruptMapId interrupt_id;",
        "  InterruptMapAliasId alias_id;",
        "};",
        *_std_array_lines(
            type_name="InterruptAliasRef",
            variable_name="kInterruptAliases",
            row_lines=[
                "  {"
                f"InterruptMapId::{interrupt_enum_map[(device_name, interrupt_name)]}, "
                f"{_enum_ref('InterruptMapAliasId', alias_enum_map, alias_name)}"
                "},"
                for device_name, interrupt_name, alias_name in alias_rows
            ],
        ),
    ]
    namespace_block = _cpp_namespace_block((_vendor, _family, "generated"), "\n".join(body_lines))
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "runtime_refs.hpp"',
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=f"{family_dir}/generated/interrupt_map.hpp",
        content=content,
    )


def emit_memory_map_header(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    ref_catalog = _collect_runtime_ref_catalog(devices)
    semantics_catalog = _collect_runtime_semantics_catalog(devices)
    rows = [
        (
            device.identity.device,
            memory.name,
            memory.kind,
            memory.base_address,
            memory.size_bytes,
            memory.access,
            memory.startup_roles,
        )
        for device in devices
        for memory in sorted(device.memories, key=lambda item: item.base_address)
    ]
    region_enum_map = {
        (device_name, name): _enum_identifier(f"{device_name}_{name}")
        for device_name, name, *_rest in rows
    }
    startup_role_rows = [
        (device_name, name, startup_role)
        for device_name, name, _kind, _base_address, _size_bytes, _access, startup_roles in rows
        for startup_role in startup_roles
    ]
    startup_role_map = {
        (device_name, name): tuple(startup_roles)
        for device_name, name, _kind, _base_address, _size_bytes, _access, startup_roles in rows
    }
    startup_role_offsets, startup_role_counts = _offset_count_maps(startup_role_map)
    _vendor, _family = family_dir.split("/", 1)
    memory_row_lines: list[str] = []
    for (
        device_name,
        name,
        kind,
        base_address,
        size_bytes,
        access,
        _startup_roles,
    ) in rows:
        kind_ref = _semantic_enum_ref(
            "MemoryKindId",
            semantics_catalog["memory_kind_enum_map"],
            kind,
        )
        access_ref = _semantic_enum_ref(
            "AccessKindId",
            semantics_catalog["access_kind_enum_map"],
            access,
        )
        memory_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"MemoryRegionId::{region_enum_map[(device_name, name)]}, "
            f"{kind_ref}, "
            f"0x{base_address:08X}u, "
            f"{size_bytes}u, "
            f"{access_ref}, "
            f"{startup_role_offsets.get((device_name, name), 0)}u, "
            f"{startup_role_counts.get((device_name, name), 0)}u"
            "},"
        )
    startup_role_ref_lines = []
    for device_name, name, startup_role in startup_role_rows:
        startup_role_ref = _semantic_enum_ref(
            "StartupRoleId",
            semantics_catalog["startup_role_enum_map"],
            startup_role,
        )
        startup_role_ref_lines.append(
            f"  {{MemoryRegionId::{region_enum_map[(device_name, name)]}, {startup_role_ref}}},"
        )
    body_lines = [
        "enum class MemoryRegionId : std::uint16_t {",
        "  none,",
        *_enum_rows(region_enum_map, empty_identifier=None),
        "};",
        "",
        "struct MemoryDescriptor {",
        "  DeviceRefId device_id;",
        "  MemoryRegionId region_id;",
        "  MemoryKindId kind_id;",
        "  std::uintptr_t base_address;",
        "  std::size_t size_bytes;",
        "  AccessKindId access_id;",
        "  std::uint16_t startup_role_offset;",
        "  std::uint16_t startup_role_count;",
        "};",
        "inline constexpr MemoryDescriptor kMemoryMap[] = {",
        *memory_row_lines,
        "};",
        "",
        "struct MemoryStartupRoleRef {",
        "  MemoryRegionId region_id;",
        "  StartupRoleId startup_role_id;",
        "};",
        *_std_array_lines(
            type_name="MemoryStartupRoleRef",
            variable_name="kMemoryStartupRoles",
            row_lines=startup_role_ref_lines,
        ),
    ]
    namespace_block = _cpp_namespace_block((_vendor, _family, "generated"), "\n".join(body_lines))
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstddef>",
            "#include <cstdint>",
            '#include "runtime_refs.hpp"',
            '#include "runtime_semantics.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=f"{family_dir}/generated/memory_map.hpp",
        content=content,
    )


def emit_package_map_header(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    ref_catalog = _collect_runtime_ref_catalog(devices)
    semantics_catalog = _collect_runtime_semantics_catalog(devices)
    package_rows = [
        (device.identity.device, package.name, package.pin_count)
        for device in devices
        for package in sorted(device.packages, key=lambda item: item.name)
    ]
    pad_rows = [
        (
            device.identity.device,
            package_pad.package,
            package_pad.pad_id,
            package_pad.physical_index,
            package_pad.pad_kind,
            package_pad.bonded_pin,
            package_pad.bonding_state,
        )
        for device in devices
        for package_pad in sorted(device.package_pads, key=lambda item: item.pad_id)
    ]
    constraint_rows = [
        (
            device.identity.device,
            constraint.constraint_id,
            constraint.pin,
            constraint.kind,
            constraint.value,
        )
        for device in devices
        for constraint in sorted(device.pin_constraints, key=lambda item: item.constraint_id)
    ]
    _vendor, _family = family_dir.split("/", 1)
    package_row_lines = []
    for device_name, package_name, pin_count in package_rows:
        package_ref = _eref(
            "PackageRefId",
            ref_catalog["package_enum_map"],
            device_name,
            package_name,
        )
        package_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"{package_ref}, "
            f"{pin_count}"
            "},"
        )
    package_pad_row_lines = []
    for (
        device_name,
        package_name,
        pad_id,
        physical_index,
        pad_kind,
        bonded_pin,
        bonding_state,
    ) in pad_rows:
        package_ref = _eref(
            "PackageRefId",
            ref_catalog["package_enum_map"],
            device_name,
            package_name,
        )
        pad_ref = _eref(
            "PackagePadRefId",
            ref_catalog["package_pad_enum_map"],
            device_name,
            pad_id,
        )
        pin_ref = _eref(
            "PinRefId",
            ref_catalog["pin_enum_map"],
            device_name,
            bonded_pin,
        )
        pad_kind_ref = _semantic_enum_ref(
            "PackagePadKindId",
            semantics_catalog["package_pad_kind_enum_map"],
            pad_kind,
        )
        bonding_state_ref = _semantic_enum_ref(
            "BondingStateId",
            semantics_catalog["bonding_state_enum_map"],
            bonding_state,
        )
        package_pad_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"{package_ref}, "
            f"{pad_ref}, "
            f"{pin_ref}, "
            f"{pad_kind_ref}, "
            f"{bonding_state_ref}, "
            f"{-1 if physical_index is None else physical_index}"
            "},"
        )
    pin_constraint_row_lines = []
    for device_name, constraint_id, pin_name, kind, value in constraint_rows:
        pin_ref = _eref(
            "PinRefId",
            ref_catalog["pin_enum_map"],
            device_name,
            pin_name,
        )
        constraint_ref = _eref(
            "ConstraintRefId",
            ref_catalog["constraint_enum_map"],
            device_name,
            constraint_id,
        )
        kind_ref = _semantic_enum_ref(
            "ConstraintKindId",
            semantics_catalog["constraint_kind_enum_map"],
            kind,
        )
        value_ref = _semantic_enum_ref(
            "ConstraintValueId",
            semantics_catalog["constraint_value_enum_map"],
            value,
        )
        pin_constraint_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"{pin_ref}, "
            f"{constraint_ref}, "
            f"{kind_ref}, "
            f"{value_ref}"
            "},"
        )
    body_lines = [
        "struct PackageDescriptor {",
        "  DeviceRefId device_id;",
        "  PackageRefId package_id;",
        "  int pin_count;",
        "};",
        "inline constexpr PackageDescriptor kPackageMap[] = {",
        *package_row_lines,
        "};",
        "",
        "struct PackagePadDescriptor {",
        "  DeviceRefId device_id;",
        "  PackageRefId package_id;",
        "  PackagePadRefId pad_id;",
        "  PinRefId pin_id;",
        "  PackagePadKindId pad_kind_id;",
        "  BondingStateId bonding_state_id;",
        "  int physical_index;",
        "};",
        "inline constexpr PackagePadDescriptor kPackagePads[] = {",
        *package_pad_row_lines,
        "};",
        "",
        "struct PinConstraintDescriptor {",
        "  DeviceRefId device_id;",
        "  PinRefId pin_id;",
        "  ConstraintRefId constraint_id;",
        "  ConstraintKindId kind_id;",
        "  ConstraintValueId value_id;",
        "};",
        *_std_array_lines(
            type_name="PinConstraintDescriptor",
            variable_name="kPinConstraints",
            row_lines=pin_constraint_row_lines,
        ),
    ]
    namespace_block = _cpp_namespace_block((_vendor, _family, "generated"), "\n".join(body_lines))
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            '#include "runtime_refs.hpp"',
            '#include "runtime_semantics.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=f"{family_dir}/generated/package_map.hpp",
        content=content,
    )


def emit_clock_tree_lite_header(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    ref_catalog = _collect_runtime_ref_catalog(devices)
    semantics_catalog = _collect_runtime_semantics_catalog(devices)
    register_enum_map = ref_catalog["register_enum_map"]
    register_field_enum_map = ref_catalog["register_field_enum_map"]
    node_rows = [
        (
            device.identity.device,
            node.node_id,
            node.kind,
            node.parent,
            node.selector,
        )
        for device in devices
        for node in sorted(device.clock_nodes, key=lambda item: item.node_id)
    ]
    selector_rows = [
        (
            device.identity.device,
            selector.selector_id,
            selector.parent_options,
            selector.register_id,
            selector.register_field_id,
        )
        for device in devices
        for selector in sorted(device.clock_selectors, key=lambda item: item.selector_id)
    ]
    gate_rows = [
        (
            device.identity.device,
            gate.gate_id,
            gate.peripheral,
            gate.parent_node,
            gate.register_id,
            gate.register_field_id,
        )
        for device in devices
        for gate in sorted(device.clock_gates, key=lambda item: item.gate_id)
    ]
    reset_rows = [
        (
            device.identity.device,
            reset.reset_id,
            reset.peripheral,
            reset.active_level,
            reset.register_id,
            reset.register_field_id,
        )
        for device in devices
        for reset in sorted(device.resets, key=lambda item: item.reset_id)
    ]
    binding_rows = [
        (
            device.identity.device,
            binding.peripheral,
            binding.clock_gate_id,
            binding.reset_id,
            binding.selector_id,
        )
        for device in devices
        for binding in sorted(device.peripheral_clock_bindings, key=lambda item: item.peripheral)
    ]
    node_enum_map = {
        (device_name, node_id): _enum_identifier(f"{device_name}_{node_id}")
        for device_name, node_id, *_rest in node_rows
    }
    selector_enum_map = {
        (device_name, selector_id): _enum_identifier(f"{device_name}_{selector_id}")
        for device_name, selector_id, *_rest in selector_rows
    }
    gate_enum_map = {
        (device_name, gate_id): _enum_identifier(f"{device_name}_{gate_id}")
        for device_name, gate_id, *_rest in gate_rows
    }
    reset_enum_map = {
        (device_name, reset_id): _enum_identifier(f"{device_name}_{reset_id}")
        for device_name, reset_id, *_rest in reset_rows
    }
    selector_parent_options_by_selector = {
        (device_name, selector_id): tuple(parent_options)
        for (
            device_name,
            selector_id,
            parent_options,
            _register_id,
            _register_field_id,
        ) in selector_rows
    }
    selector_parent_offsets, selector_parent_counts = _offset_count_maps(
        selector_parent_options_by_selector
    )
    selector_parent_rows = [
        (device_name, selector_id, parent_option)
        for (device_name, selector_id), parent_options in sorted(
            selector_parent_options_by_selector.items()
        )
        for parent_option in parent_options
    ]
    _vendor, _family = family_dir.split("/", 1)

    node_row_lines: list[str] = []
    for device_name, node_id, kind, parent, selector in node_rows:
        kind_ref = _semantic_enum_ref(
            "ClockNodeKindId",
            semantics_catalog["clock_node_kind_enum_map"],
            kind,
        )
        parent_ref = _enum_ref(
            "ClockNodeId",
            node_enum_map,
            _device_ref_key(device_name, parent),
        )
        selector_ref = _enum_ref(
            "ClockSelectorId",
            selector_enum_map,
            _device_ref_key(device_name, selector),
        )
        node_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"ClockNodeId::{node_enum_map[(device_name, node_id)]}, "
            f"{kind_ref}, "
            f"{parent_ref}, "
            f"{selector_ref}"
            "},"
        )

    selector_row_lines: list[str] = []
    for (
        device_name,
        selector_id,
        _parent_options,
        register_id,
        register_field_id,
    ) in selector_rows:
        register_ref = _eref(
            "RegisterRefId",
            register_enum_map,
            device_name,
            register_id,
        )
        register_field_ref = _eref(
            "RegisterFieldRefId",
            register_field_enum_map,
            device_name,
            register_field_id,
        )
        selector_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"ClockSelectorId::{selector_enum_map[(device_name, selector_id)]}, "
            f"{selector_parent_offsets.get((device_name, selector_id), 0)}u, "
            f"{selector_parent_counts.get((device_name, selector_id), 0)}u, "
            f"{register_ref}, "
            f"{register_field_ref}"
            "},"
        )

    gate_row_lines: list[str] = []
    for (
        device_name,
        gate_id,
        peripheral,
        parent_node,
        register_id,
        register_field_id,
    ) in gate_rows:
        peripheral_ref = _enum_ref(
            "PeripheralRefId",
            ref_catalog["peripheral_enum_map"],
            _device_ref_key(device_name, peripheral),
        )
        parent_ref = _enum_ref(
            "ClockNodeId",
            node_enum_map,
            _device_ref_key(device_name, parent_node),
        )
        register_ref = _eref(
            "RegisterRefId",
            register_enum_map,
            device_name,
            register_id,
        )
        register_field_ref = _eref(
            "RegisterFieldRefId",
            register_field_enum_map,
            device_name,
            register_field_id,
        )
        gate_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"ClockGateId::{gate_enum_map[(device_name, gate_id)]}, "
            f"{peripheral_ref}, "
            f"{parent_ref}, "
            f"{register_ref}, "
            f"{register_field_ref}"
            "},"
        )

    reset_row_lines: list[str] = []
    for (
        device_name,
        reset_id,
        peripheral,
        active_level,
        register_id,
        register_field_id,
    ) in reset_rows:
        peripheral_ref = _enum_ref(
            "PeripheralRefId",
            ref_catalog["peripheral_enum_map"],
            _device_ref_key(device_name, peripheral),
        )
        active_level_ref = _semantic_enum_ref(
            "ActiveLevelId",
            semantics_catalog["active_level_enum_map"],
            active_level,
        )
        register_ref = _eref(
            "RegisterRefId",
            register_enum_map,
            device_name,
            register_id,
        )
        register_field_ref = _eref(
            "RegisterFieldRefId",
            register_field_enum_map,
            device_name,
            register_field_id,
        )
        reset_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"ResetId::{reset_enum_map[(device_name, reset_id)]}, "
            f"{peripheral_ref}, "
            f"{active_level_ref}, "
            f"{register_ref}, "
            f"{register_field_ref}"
            "},"
        )

    binding_row_lines = []
    for device_name, peripheral, clock_gate_id, reset_id, selector_id in binding_rows:
        peripheral_ref = _enum_ref(
            "PeripheralRefId",
            ref_catalog["peripheral_enum_map"],
            _device_ref_key(device_name, peripheral),
        )
        binding_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"{peripheral_ref}, "
            f"{_clock_gate_enum_ref(device_name, clock_gate_id)}, "
            f"{_reset_enum_ref(device_name, reset_id)}, "
            f"{_selector_enum_ref(device_name, selector_id)}"
            "},"
        )

    body_lines = [
        "enum class ClockNodeId : std::uint16_t {",
        "  none,",
        *_enum_rows(node_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class ClockSelectorId : std::uint16_t {",
        "  none,",
        *_enum_rows(selector_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class ClockGateId : std::uint16_t {",
        "  none,",
        *_enum_rows(gate_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class ResetId : std::uint16_t {",
        "  none,",
        *_enum_rows(reset_enum_map, empty_identifier=None),
        "};",
        "",
        "struct ClockNodeDescriptor {",
        "  DeviceRefId device_id;",
        "  ClockNodeId node_id;",
        "  ClockNodeKindId kind_id;",
        "  ClockNodeId parent_node_id;",
        "  ClockSelectorId selector_id;",
        "};",
        *_std_array_lines(
            type_name="ClockNodeDescriptor",
            variable_name="kClockNodes",
            row_lines=node_row_lines,
        ),
        "",
        "struct ClockSelectorDescriptor {",
        "  DeviceRefId device_id;",
        "  ClockSelectorId selector_id;",
        "  std::uint16_t parent_option_offset;",
        "  std::uint16_t parent_option_count;",
        "  RegisterRefId register_id;",
        "  RegisterFieldRefId register_field_id;",
        "};",
        *_std_array_lines(
            type_name="ClockSelectorDescriptor",
            variable_name="kClockSelectors",
            row_lines=selector_row_lines,
        ),
        "",
        "struct ClockSelectorParentOption {",
        "  ClockSelectorId selector_id;",
        "  ClockNodeId parent_node_id;",
        "};",
        *_std_array_lines(
            type_name="ClockSelectorParentOption",
            variable_name="kClockSelectorParentOptions",
            row_lines=[
                "  {"
                f"ClockSelectorId::{selector_enum_map[(device_name, selector_id)]}, "
                f"ClockNodeId::{node_enum_map[(device_name, parent_option)]}"
                "},"
                for device_name, selector_id, parent_option in selector_parent_rows
            ],
        ),
        "",
        "struct ClockGateDescriptor {",
        "  DeviceRefId device_id;",
        "  ClockGateId gate_id;",
        "  PeripheralRefId peripheral_id;",
        "  ClockNodeId parent_node_id;",
        "  RegisterRefId register_id;",
        "  RegisterFieldRefId register_field_id;",
        "};",
        *_std_array_lines(
            type_name="ClockGateDescriptor",
            variable_name="kClockGates",
            row_lines=gate_row_lines,
        ),
        "",
        "struct ResetDescriptor {",
        "  DeviceRefId device_id;",
        "  ResetId reset_id;",
        "  PeripheralRefId peripheral_id;",
        "  ActiveLevelId active_level_id;",
        "  RegisterRefId register_id;",
        "  RegisterFieldRefId register_field_id;",
        "};",
        *_std_array_lines(
            type_name="ResetDescriptor",
            variable_name="kResets",
            row_lines=reset_row_lines,
        ),
        "",
        "struct PeripheralClockBindingDescriptor {",
        "  DeviceRefId device_id;",
        "  PeripheralRefId peripheral_id;",
        "  ClockGateId clock_gate_id;",
        "  ResetId reset_id;",
        "  ClockSelectorId selector_id;",
        "};",
        *_std_array_lines(
            type_name="PeripheralClockBindingDescriptor",
            variable_name="kPeripheralClockBindings",
            row_lines=binding_row_lines,
        ),
    ]
    namespace_block = _cpp_namespace_block((_vendor, _family, "generated"), "\n".join(body_lines))
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            '#include "runtime_refs.hpp"',
            '#include "runtime_semantics.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(path=f"{family_dir}/generated/clock_tree_lite.hpp", content=content)


def emit_startup_descriptors_header(
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
    vector_slot_row_lines = []
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
    startup_descriptor_row_lines = []
    for descriptor in sorted(device.startup_descriptors, key=lambda item: item.descriptor_id):
        descriptor_ref = (
            f"StartupDescriptorId::{startup_descriptor_enum_map[descriptor.descriptor_id]}"
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
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
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
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../runtime_semantics.hpp"',
            '#include "interrupt_bindings.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_generated_path(family_dir, device.identity.device, "startup_descriptors.hpp"),
        content=content,
    )


def emit_startup_vectors_source(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    content = "\n".join(
        [
            '#include "startup_descriptors.hpp"',
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_generated_path(family_dir, device.identity.device, "startup_vectors.cpp"),
        content=content,
    )


def emit_rcc_map_header(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    """Emit a family-level typed mapping from peripheral → clock/reset bindings."""
    ref_catalog = _collect_runtime_ref_catalog(devices)
    binding_by_device_peripheral = {
        (device.identity.device, binding.peripheral): binding
        for device in devices
        for binding in device.peripheral_clock_bindings
    }
    rows: list[tuple[str, str, str | None, str | None]] = []
    for device in devices:
        for peripheral in device.peripherals:
            binding = binding_by_device_peripheral.get((device.identity.device, peripheral.name))
            if binding is None or (binding.clock_gate_id is None and binding.reset_id is None):
                continue
            rows.append(
                (
                    device.identity.device,
                    peripheral.name,
                    binding.clock_gate_id,
                    binding.reset_id,
                )
            )
    rows.sort(key=lambda r: (r[0], r[1]))

    _vendor, _family = family_dir.split("/", 1)
    rcc_row_lines = []
    for device_name, peripheral, gate_id, reset_id in rows:
        peripheral_ref = _enum_ref(
            "PeripheralRefId",
            ref_catalog["peripheral_enum_map"],
            (device_name, peripheral),
        )
        rcc_row_lines.append(
            "  {"
            f"DeviceRefId::{ref_catalog['device_enum_map'][device_name]}, "
            f"{peripheral_ref}, "
            f"{_clock_gate_enum_ref(device_name, gate_id)}, "
            f"{_reset_enum_ref(device_name, reset_id)}"
            "},"
        )
    body_lines = [
        "struct RccDescriptor {",
        "  DeviceRefId device_id;",
        "  PeripheralRefId peripheral_id;",
        "  ClockGateId gate_id;",
        "  ResetId reset_id;",
        "};",
        "inline constexpr RccDescriptor kRccMap[] = {",
        *rcc_row_lines,
        "};",
    ]
    namespace_block = _cpp_namespace_block(
        (_vendor, _family, "generated"),
        "\n".join(body_lines),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            '#include "runtime_refs.hpp"',
            '#include "clock_tree_lite.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=f"{family_dir}/generated/rcc_map.hpp",
        content=content,
    )


def emit_dma_map_header(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
    """Emit a family-level C++ header mapping (peripheral, signal) → (controller, request_line)."""
    semantics_catalog = _collect_runtime_semantics_catalog(devices)
    seen: set[tuple[str, str, str, str]] = set()
    rows: list[tuple[str, str, str, str]] = []
    for device in devices:
        for req in device.dma_requests:
            key = (
                req.peripheral or "",
                req.signal or "",
                req.controller,
                req.request_line,
            )
            if key not in seen:
                seen.add(key)
                rows.append(key)
    rows.sort()

    _vendor, _family = family_dir.split("/", 1)
    controller_enum_map = {
        controller: _enum_identifier(controller)
        for _peripheral, _signal, controller, _request_line in rows
    }
    peripheral_enum_map = {
        peripheral: _enum_identifier(peripheral)
        for peripheral, _signal, _controller, _request_line in rows
    }
    request_line_enum_map = {
        request_line: _enum_identifier(request_line)
        for _peripheral, _signal, _controller, request_line in rows
    }
    body_lines = [
        "enum class DmaMapPeripheralId : std::uint16_t {",
        "  none,",
        *_enum_rows(peripheral_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class DmaMapControllerId : std::uint16_t {",
        "  none,",
        *_enum_rows(controller_enum_map, empty_identifier=None),
        "};",
        "",
        "enum class DmaMapRequestLineId : std::uint16_t {",
        "  none,",
        *_enum_rows(request_line_enum_map, empty_identifier=None),
        "};",
        "",
        "struct DmaDescriptor {",
        "  DmaMapPeripheralId peripheral_id;",
        "  SignalId signal_id;",
        "  DmaMapControllerId controller_id;",
        "  DmaMapRequestLineId request_line_id;",
        "};",
        *_std_array_lines(
            type_name="DmaDescriptor",
            variable_name="kDmaMap",
            row_lines=[
                "  {"
                f"{_enum_ref('DmaMapPeripheralId', peripheral_enum_map, peripheral)}, "
                f"{_semantic_enum_ref('SignalId', semantics_catalog['signal_enum_map'], signal)}, "
                f"{_enum_ref('DmaMapControllerId', controller_enum_map, controller)}, "
                f"{_enum_ref('DmaMapRequestLineId', request_line_enum_map, request_line)}"
                "},"
                for peripheral, signal, controller, request_line in rows
            ],
        ),
    ]
    namespace_block = _cpp_namespace_block(
        (_vendor, _family, "generated"),
        "\n".join(body_lines),
    )
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            '#include "runtime_semantics.hpp"',
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=f"{family_dir}/generated/dma_map.hpp",
        content=content,
    )


def emit_publication_summary(
    *,
    family_dir: str,
    target_repository: str,
    publication_mode: str,
    artifact_manifest: ArtifactManifest,
    artifacts: tuple[EmittedArtifact, ...],
    publication_root: str,
    target_artifact_revision: str | None = None,
    consumer_verification: ConsumerVerification | None = None,
) -> EmittedArtifact:
    materialized_artifacts = [
        {
            "path": artifact.path,
            "artifact_kind": artifact.artifact_kind,
            "content_sha256": artifact.content_sha256,
            "content_bytes": artifact.content_bytes,
            "materialized_path": artifact.materialized_path,
        }
        for artifact in artifacts
        if artifact.materialized_path is not None
    ]
    payload = {
        "target_repository": target_repository,
        "publication_mode": publication_mode,
        "artifact_manifest": artifact_manifest.to_dict(),
        "artifact_root": f"{family_dir}/",
        "publication_root": publication_root,
        "target_artifact_revision": target_artifact_revision,
        "consumer_verification": None
        if consumer_verification is None
        else to_primitive(consumer_verification),
        "materialized_artifact_count": len(materialized_artifacts),
        "materialized_artifacts": materialized_artifacts,
    }
    return _text_artifact(
        path=_family_report_path(family_dir, "publication-summary.json"),
        artifact_kind="publication-metadata",
        payload=payload,
    )


def materialize_artifacts(
    *,
    artifact_root: Path,
    artifacts: tuple[EmittedArtifact, ...],
) -> tuple[EmittedArtifact, ...]:
    materialized: list[EmittedArtifact] = []
    for artifact in artifacts:
        if artifact.content is None:
            materialized.append(artifact)
            continue

        output_path = artifact_root / artifact.path
        output_path.parent.mkdir(parents=True, exist_ok=True)
        output_path.write_text(artifact.content, encoding="utf-8")
        materialized.append(
            EmittedArtifact(
                path=artifact.path,
                artifact_kind=artifact.artifact_kind,
                content=artifact.content,
                content_sha256=artifact.content_sha256,
                content_bytes=artifact.content_bytes,
                materialized_path=str(output_path),
            )
        )
    return tuple(materialized)
