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
        "state": "state",
        "pin": "pin",
        "constraint": "constraint",
        "selector": "selector",
        "clock-gate": "clock_gate",
        "reset": "reset",
        "int": "integer",
    }
    return f"RuntimeRefKind::{mapping.get(kind, 'other')}"


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


def _enum_rows(enum_map: dict[object, str]) -> list[str]:
    rows = [f"  {identifier}," for identifier in enum_map.values()]
    return rows if rows else ["  none,"]


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
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "struct DeviceDescriptor {",
                "  const char* vendor;",
                "  const char* family;",
                "  const char* device;",
                "  const char* package_name;",
                "  const char* core;",
                "  const char* summary;",
                "  int pin_count;",
                "  int peripheral_count;",
                "  int interrupt_count;",
                "  int memory_region_count;",
                "  int capability_overlay_count;",
                "  int startup_descriptor_count;",
                "};",
                "inline constexpr DeviceDescriptor kDeviceDescriptor = {",
                f"  {json.dumps(device.identity.vendor)},",
                f"  {json.dumps(device.identity.family)},",
                f"  {json.dumps(device.identity.device)},",
                f"  {json.dumps(device.identity.package)},",
                f"  {json.dumps(device.identity.core)},",
                f"  {json.dumps(device.identity.summary)},",
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
    content = "\n".join(["#pragma once", "", namespace_block, ""])
    return _cpp_artifact(
        path=_device_generated_path(family_dir, device.identity.device, "device_descriptor.hpp"),
        content=content,
    )


def emit_pins_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
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
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "struct PinDescriptor {",
                "  const char* pin_name;",
                "  const char* port;",
                "  int number;",
                "  const char* package_pad_ids;",
                "  const char* constraint_ids;",
                "};",
                *_std_array_lines(
                    type_name="PinDescriptor",
                    variable_name="kPins",
                    row_lines=[
                        f"  {{{json.dumps(pin_name)}, {_quoted(port)}, {number}, "
                        f"{json.dumps(','.join(package_pad_ids))}, "
                        f"{json.dumps(','.join(constraint_ids))}}},"
                        for pin_name, port, number, package_pad_ids, constraint_ids in pin_rows
                    ],
                ),
                "",
                "struct PinSignalDescriptor {",
                "  const char* pin_name;",
                "  const char* function;",
                "  const char* peripheral;",
                "  const char* signal;",
                "  int af_number;",
                "};",
                *_std_array_lines(
                    type_name="PinSignalDescriptor",
                    variable_name="kPinSignals",
                    row_lines=[
                        f"  {{{json.dumps(pin_name)}, {json.dumps(function)}, "
                        f"{_quoted(peripheral)}, {_quoted(signal_name)}, "
                        f"{-1 if af_number is None else af_number}}},"
                        for pin_name, function, peripheral, signal_name, af_number in signal_rows
                    ],
                ),
            ]
        ),
    )
    content = "\n".join(["#pragma once", "", "#include <array>", "", namespace_block, ""])
    return _cpp_artifact(
        path=_device_generated_path(family_dir, device.identity.device, "pins.hpp"),
        content=content,
    )


def emit_peripheral_instances_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    interrupts_by_peripheral = _interrupt_names_by_peripheral(device)
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
    enum_rows = [
        f"  {_enum_identifier(peripheral.name)},"
        for peripheral in sorted_peripherals
    ]
    for peripheral in sorted_peripherals:
        binding = bindings_by_peripheral.get(peripheral.name)
        clock_gate_id = None if binding is None else binding.clock_gate_id
        reset_id = None if binding is None else binding.reset_id
        selector_id = None if binding is None else binding.selector_id
        interrupt_names = ",".join(interrupts_by_peripheral.get(peripheral.name, ()))
        overlay_ids = ",".join(overlay_ids_by_peripheral.get(peripheral.name, ()))
        peripheral_rows.append(
            "  {"
            f"PeripheralId::{_enum_identifier(peripheral.name)}, "
            f"{json.dumps(peripheral.name)}, "
            f"{json.dumps(peripheral.ip_name)}, "
            f"{_quoted(peripheral.ip_version)}, "
            f"{_quoted(peripheral.backend_schema_id)}, "
            f"{peripheral.instance}, "
            f"0x{peripheral.base_address:08X}u, "
            f"{_quoted(peripheral.rcc_enable_signal)}, "
            f"{_quoted(peripheral.rcc_reset_signal)}, "
            f"{_quoted(clock_gate_id)}, "
            f"{_quoted(reset_id)}, "
            f"{_quoted(selector_id)}, "
            f"{interrupt_offsets.get(peripheral.name, 0)}u, "
            f"{interrupt_counts.get(peripheral.name, 0)}u, "
            f"{dma_offsets.get(peripheral.name, 0)}u, "
            f"{dma_counts.get(peripheral.name, 0)}u, "
            f"{overlay_offsets.get(peripheral.name, 0)}u, "
            f"{overlay_counts.get(peripheral.name, 0)}u, "
            f"{json.dumps(interrupt_names)}, "
            f"{json.dumps(overlay_ids)}, "
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
                "  const char* name;",
                "  const char* ip_name;",
                "  const char* ip_version;",
                "  const char* backend_schema_id;",
                "  int instance;",
                "  std::uintptr_t base_address;",
                "  const char* rcc_enable_signal;",
                "  const char* rcc_reset_signal;",
                "  const char* clock_gate_id;",
                "  const char* reset_id;",
                "  const char* selector_id;",
                "  std::uint16_t interrupt_binding_offset;",
                "  std::uint16_t interrupt_binding_count;",
                "  std::uint16_t dma_binding_offset;",
                "  std::uint16_t dma_binding_count;",
                "  std::uint16_t capability_overlay_offset;",
                "  std::uint16_t capability_overlay_count;",
                "  const char* interrupt_names;",
                "  const char* capability_overlay_ids;",
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
        ["#pragma once", "", "#include <array>", "#include <cstdint>", "", namespace_block, ""]
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
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "struct CapabilityOverlayDescriptor {",
                "  const char* capability_id;",
                "  const char* scope;",
                "  const char* peripheral_class;",
                "  const char* name;",
                "  const char* value;",
                "  const char* ip_name;",
                "  const char* ip_version;",
                "  const char* peripheral;",
                "  const char* package_name;",
                "};",
                *_std_array_lines(
                    type_name="CapabilityOverlayDescriptor",
                    variable_name="kCapabilityOverlays",
                    row_lines=[
                        f"  {{{json.dumps(capability_id)}, {json.dumps(scope)}, "
                        f"{json.dumps(peripheral_class)}, {json.dumps(name)}, {json.dumps(value)}, "
                        f"{_quoted(ip_name or None)}, {_quoted(ip_version or None)}, "
                        f"{_quoted(peripheral or None)}, {_quoted(package_name or None)}}},"
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
                        ) in overlay_rows
                    ],
                ),
            ]
        ),
    )
    content = "\n".join(["#pragma once", "", "#include <array>", "", namespace_block, ""])
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
    rows: list[tuple[str, str, str, str]] = []
    seen: set[tuple[str, str, str, str]] = set()
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
                operation.kind,
                operation.schema_id,
                "route-operation",
                operation.operation_id,
            )
            if row not in seen:
                seen.add(row)
                rows.append(row)

    _vendor, _family = family_dir.split("/", 1)
    namespace_block = _cpp_namespace_block(
        (_vendor, _family, "generated"),
        "\n".join(
            [
                "struct RuntimeProfileDescriptor {",
                "  const char* subsystem;",
                "  const char* schema_id;",
                "  const char* source_kind;",
                "  const char* source_id;",
                "};",
                *_std_array_lines(
                    type_name="RuntimeProfileDescriptor",
                    variable_name="kRuntimeProfiles",
                    row_lines=[
                        f"  {{{json.dumps(subsystem)}, {json.dumps(schema_id)}, "
                        f"{json.dumps(source_kind)}, {json.dumps(source_id)}}},"
                        for subsystem, schema_id, source_kind, source_id in rows
                    ],
                ),
            ]
        ),
    )
    content = "\n".join(["#pragma once", "", "#include <array>", "", namespace_block, ""])
    return _cpp_artifact(path=f"{family_dir}/generated/runtime_profiles.hpp", content=content)


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
    _vendor, _family = family_dir.split("/", 1)
    body_lines = [
        "struct IpBlockDescriptor {",
        "  const char* ip_name;",
        "  const char* ip_version;",
        "  const char* peripheral_class;",
        "  const char* backend_schema_id;",
        "  const char* register_profile;",
        "  const char* signal_roles;",
        "};",
        "inline constexpr IpBlockDescriptor kIpBlock = {",
        f"  {json.dumps(ip_block.ip_name)},",
        f"  {json.dumps(ip_block.ip_version)},",
        f"  {json.dumps(ip_block.peripheral_class)},",
        f"  {_quoted(ip_block.backend_schema_id)},",
        f"  {_quoted(ip_block.register_profile)},",
        f"  {json.dumps(','.join(ip_block.signal_roles))},",
        "};",
        "",
        "struct CapabilityDescriptor {",
        "  const char* capability_id;",
        "  const char* scope;",
        "  const char* peripheral_class;",
        "  const char* name;",
        "  const char* value;",
        "  const char* ip_name;",
        "  const char* ip_version;",
        "  const char* peripheral;",
        "  const char* package;",
        "};",
        *_std_array_lines(
            type_name="CapabilityDescriptor",
            variable_name="kCapabilities",
            row_lines=[
                f"  {{{json.dumps(capability.capability_id)}, "
                f"{json.dumps(capability.scope)}, "
                f"{json.dumps(capability.peripheral_class)}, "
                f"{json.dumps(capability.name)}, {json.dumps(capability.value)}, "
                f"{_quoted(capability.ip_name)}, {_quoted(capability.ip_version)}, "
                f"{_quoted(capability.peripheral)}, {_quoted(capability.package)}}},"
                for capability in sorted(capabilities, key=lambda item: item.capability_id)
            ],
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
    register_enum_rows = [
        f"  {_enum_identifier(register_id)},"
        for register_id, *_rest in register_rows
    ]
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                f"inline constexpr const char* kDevice = {json.dumps(device.identity.device)};",
                "struct PeripheralBase {",
                "  PeripheralId peripheral_id;",
                "  const char* name;",
                "  std::uintptr_t address;",
                "};",
                *_std_array_lines(
                    type_name="PeripheralBase",
                    variable_name="kPeripheralBases",
                    row_lines=[
                        f"  {{PeripheralId::{_enum_identifier(peripheral.name)}, "
                        f"{json.dumps(peripheral.name)}, 0x{peripheral.base_address:08X}u}},"
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
                "  const char* peripheral_name;",
                "  const char* register_name;",
                "  std::uint32_t offset_bytes;",
                "  const char* access;",
                "  int size_bits;",
                "};",
                *_std_array_lines(
                    type_name="RegisterDescriptor",
                    variable_name="kRegisters",
                    row_lines=[
                        (
                            f"  {{RegisterId::{_enum_identifier(register_id)}, "
                            f"PeripheralId::{_enum_identifier(peripheral_name)}, "
                            f"{json.dumps(peripheral_name)}, {json.dumps(register_name)}, "
                            f"{offset_bytes}u, {_quoted(access)}, "
                            f"{-1 if size_bits is None else size_bits}}},"
                        )
                        for (
                            register_id,
                            peripheral_name,
                            register_name,
                            offset_bytes,
                            access,
                            size_bits,
                        ) in register_rows
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
                "  const char* peripheral_name;",
                "  const char* register_name;",
                "  const char* field_name;",
                "  std::uint16_t bit_offset;",
                "  std::uint16_t bit_width;",
                "  const char* access;",
                "};",
                *_std_array_lines(
                    type_name="RegisterFieldDescriptor",
                    variable_name="kRegisterFields",
                    row_lines=[
                        (
                            f"  {{FieldId::{_enum_identifier(field_id)}, "
                            f"RegisterId::{_enum_identifier(register_id)}, "
                            f"PeripheralId::{_enum_identifier(peripheral_name)}, "
                            f"{json.dumps(peripheral_name)}, {json.dumps(register_name)}, "
                            f"{json.dumps(field_name)}, {bit_offset}u, {bit_width}u, "
                            f"{_quoted(access)}}},"
                        )
                        for (
                            field_id,
                            register_id,
                            peripheral_name,
                            register_name,
                            field_name,
                            bit_offset,
                            bit_width,
                            access,
                        ) in field_rows
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
        f"  {_enum_identifier(binding_id)},"
        for binding_id, *_rest in binding_rows
    ]
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "enum class InterruptBindingId : std::uint16_t {",
                *binding_enum_rows,
                "};",
                "",
                "struct InterruptBindingDescriptor {",
                "  InterruptBindingId binding_id;",
                "  PeripheralId peripheral_id;",
                "  const char* peripheral_name;",
                "  const char* interrupt_name;",
                "  int line;",
                "  int vector_slot;",
                "  const char* symbol_name;",
                "  const char* shared_group;",
                "  std::uint16_t alias_offset;",
                "  std::uint16_t alias_count;",
                "};",
                *_std_array_lines(
                    type_name="InterruptBindingDescriptor",
                    variable_name="kInterruptBindings",
                    row_lines=[
                        (
                            f"  {{InterruptBindingId::{_enum_identifier(binding_id)}, "
                            f"PeripheralId::{_enum_identifier(peripheral_name)}, "
                            f"{json.dumps(peripheral_name)}, {json.dumps(interrupt_name)}, "
                            f"{line}, {-1 if vector_slot is None else vector_slot}, "
                            f"{_quoted(symbol_name)}, {_quoted(shared_group)}, "
                            f"{alias_offsets.get(binding_id, 0)}u, "
                            f"{alias_counts.get(binding_id, 0)}u}},"
                        )
                        for (
                            binding_id,
                            peripheral_name,
                            interrupt_name,
                            line,
                            vector_slot,
                            symbol_name,
                            shared_group,
                        ) in binding_rows
                    ],
                ),
                "",
                "struct InterruptBindingAlias {",
                "  InterruptBindingId binding_id;",
                "  const char* alias_name;",
                "};",
                *_std_array_lines(
                    type_name="InterruptBindingAlias",
                    variable_name="kInterruptBindingAliases",
                    row_lines=[
                        (
                            f"  {{InterruptBindingId::{_enum_identifier(binding_id)}, "
                            f"{json.dumps(alias_name)}}},"
                        )
                        for binding_id, alias_name in alias_rows
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
        f"  {_enum_identifier(binding_id)},"
        for binding_id, *_rest in binding_rows
    ]
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "enum class DmaBindingId : std::uint16_t {",
                *binding_enum_rows,
                "};",
                "",
                "struct DmaBindingDescriptor {",
                "  DmaBindingId binding_id;",
                "  PeripheralId peripheral_id;",
                "  const char* peripheral_name;",
                "  const char* signal_name;",
                "  const char* controller_name;",
                "  const char* request_line;",
                "  const char* route_id;",
                "  const char* conflict_group;",
                "};",
                *_std_array_lines(
                    type_name="DmaBindingDescriptor",
                    variable_name="kDmaBindings",
                    row_lines=[
                        (
                            f"  {{DmaBindingId::{_enum_identifier(binding_id)}, "
                            f"PeripheralId::{_enum_identifier(peripheral_name)}, "
                            f"{json.dumps(peripheral_name)}, {_quoted(signal_name)}, "
                            f"{json.dumps(controller_name)}, {json.dumps(request_line)}, "
                            f"{json.dumps(route_id)}, {_quoted(conflict_group)}}},"
                        )
                        for (
                            binding_id,
                            peripheral_name,
                            signal_name,
                            controller_name,
                            request_line,
                            route_id,
                            conflict_group,
                        ) in binding_rows
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
    peripheral = _find_family_peripheral(devices, peripheral_name)
    if peripheral is None:
        raise ValueError(f"Family GPIO emission requires peripheral {peripheral_name}.")
    _vendor, _family = family_dir.split("/", 1)
    namespace_block = _cpp_namespace_block(
        (_vendor, _family, "generated", "peripherals"),
        "\n".join(
            [
                "struct PeripheralDescriptor {",
                "  const char* name;",
                "  std::uintptr_t base_address;",
                "  const char* rcc_enable_signal;",
                "  const char* rcc_reset_signal;",
                "};",
                "inline constexpr PeripheralDescriptor kPeripheral = {",
                f"  {json.dumps(peripheral.name)},",
                f"  0x{peripheral.base_address:08X}u,",
                f"  {_quoted(peripheral.rcc_enable_signal)},",
                f"  {_quoted(peripheral.rcc_reset_signal)},",
                "};",
            ]
        ),
    )
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
            requirement.target,
            requirement.value,
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
            operation.register_peripheral,
            operation.register_name,
            operation.register_offset,
            operation.register_id,
            operation.register_field_id,
            operation.value_int,
            operation.target,
            operation.value,
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
    group_enum_map = {
        (device_name, group_id): _enum_identifier(f"{device_name}_{group_id}")
        for device_name, group_id, *_rest in group_rows
    }
    group_index_map = {
        (device_name, group_id): index
        for index, (device_name, group_id, *_rest) in enumerate(group_rows)
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
        (
            device_name,
            candidate_id,
            requirement_id,
        )
        for (device_name, candidate_id), requirement_ids in sorted(
            candidate_requirements_by_candidate.items()
        )
        for requirement_id in requirement_ids
    ]
    candidate_operation_ref_rows = [
        (
            device_name,
            candidate_id,
            operation_id,
        )
        for (device_name, candidate_id), operation_ids in sorted(
            candidate_operations_by_candidate.items()
        )
        for operation_id in operation_ids
    ]
    candidate_capability_ref_rows = [
        (
            device_name,
            candidate_id,
            capability_id,
        )
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
    candidate_descriptor_row_lines = []
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
        route_group_index = (
            -1 if route_group_id is None else group_index_map[(device_name, route_group_id)]
        )
        candidate_descriptor_row_lines.append(
            "  {"
            f"{json.dumps(device_name)}, "
            f"ConnectionCandidateId::{candidate_enum_map[(device_name, candidate_id)]}, "
            f"{json.dumps(candidate_id)}, "
            f"{json.dumps(pin)}, "
            f"{json.dumps(peripheral)}, "
            f"{json.dumps(signal)}, "
            f"{json.dumps(route_kind)}, "
            f"{_quoted(route_selector)}, "
            f"{route_group_index}, "
            f"{candidate_requirement_offsets.get((device_name, candidate_id), 0)}u, "
            f"{candidate_requirement_counts.get((device_name, candidate_id), 0)}u, "
            f"{candidate_operation_offsets.get((device_name, candidate_id), 0)}u, "
            f"{candidate_operation_counts.get((device_name, candidate_id), 0)}u, "
            f"{candidate_capability_offsets.get((device_name, candidate_id), 0)}u, "
            f"{candidate_capability_counts.get((device_name, candidate_id), 0)}u"
            "},"
        )

    body_lines = [
        "enum class RuntimeRefKind : std::uint8_t {",
        "  none,",
        "  package,",
        "  state,",
        "  pin,",
        "  constraint,",
        "  selector,",
        "  clock_gate,",
        "  reset,",
        "  integer,",
        "  other,",
        "};",
        "",
        "struct SignalEndpointDescriptor {",
        "  const char* device;",
        "  const char* endpoint_id;",
        "  const char* peripheral_class;",
        "  const char* signal;",
        "  const char* direction;",
        "};",
        "inline constexpr SignalEndpointDescriptor kSignalEndpoints[] = {",
        *[
            f"  {{{json.dumps(device_name)}, {json.dumps(endpoint_id)}, "
            f"{json.dumps(peripheral_class)}, {json.dumps(signal)}, {_quoted(direction)}}},"
            for device_name, endpoint_id, peripheral_class, signal, direction in endpoint_rows
        ],
        "};",
        "",
        "enum class RouteRequirementId : std::uint16_t {",
        *(
            [
                f"  {identifier},"
                for identifier in requirement_enum_map.values()
            ]
            if requirement_enum_map
            else ["  none,"]
        ),
        "};",
        "",
        "struct RouteRequirementDescriptor {",
        "  const char* device;",
        "  RouteRequirementId requirement_id;",
        "  const char* requirement_name;",
        "  const char* kind;",
        "  RuntimeRefKind target_ref_kind;",
        "  const char* target_ref_id;",
        "  RuntimeRefKind value_ref_kind;",
        "  const char* value_ref_id;",
        "  int value_int;",
        "  const char* diagnostic_target;",
        "  const char* diagnostic_value;",
        "};",
        *_std_array_lines(
            type_name="RouteRequirementDescriptor",
            variable_name="kRouteRequirements",
            row_lines=[
                "  {"
                f"{json.dumps(device_name)}, "
                f"RouteRequirementId::{requirement_enum_map[(device_name, requirement_id)]}, "
                f"{json.dumps(requirement_id)}, "
                f"{json.dumps(kind)}, "
                f"{_runtime_ref_kind_enum(target_ref_kind)}, "
                f"{_quoted(target_ref_id)}, "
                f"{_runtime_ref_kind_enum(value_ref_kind)}, "
                f"{_quoted(value_ref_id)}, "
                f"{-1 if value_int is None else value_int}, "
                f"{_quoted(target)}, "
                f"{_quoted(value)}"
                "},"
                for (
                    device_name,
                    requirement_id,
                    kind,
                    target_ref_kind,
                    target_ref_id,
                    value_ref_kind,
                    value_ref_id,
                    value_int,
                    target,
                    value,
                ) in requirement_rows
            ],
        ),
        "",
        "enum class RouteOperationId : std::uint16_t {",
        *(
            [
                f"  {identifier},"
                for identifier in operation_enum_map.values()
            ]
            if operation_enum_map
            else ["  none,"]
        ),
        "};",
        "",
        "struct RouteOperationDescriptor {",
        "  const char* device;",
        "  RouteOperationId operation_id;",
        "  const char* operation_name;",
        "  const char* kind;",
        "  const char* schema_id;",
        "  const char* subject_kind;",
        "  const char* subject_id;",
        "  RuntimeRefKind target_ref_kind;",
        "  const char* target_ref_id;",
        "  RuntimeRefKind value_ref_kind;",
        "  const char* value_ref_id;",
        "  const char* register_peripheral;",
        "  const char* register_name;",
        "  int register_offset;",
        "  const char* register_id;",
        "  const char* register_field_id;",
        "  int value_int;",
        "  const char* diagnostic_target;",
        "  const char* diagnostic_value;",
        "};",
        *_std_array_lines(
            type_name="RouteOperationDescriptor",
            variable_name="kRouteOperations",
            row_lines=[
                "  {"
                f"{json.dumps(device_name)}, "
                f"RouteOperationId::{operation_enum_map[(device_name, operation_id)]}, "
                f"{json.dumps(operation_id)}, "
                f"{json.dumps(kind)}, "
                f"{_quoted(schema_id)}, "
                f"{_quoted(subject_kind)}, "
                f"{_quoted(subject_id)}, "
                f"{_runtime_ref_kind_enum(target_ref_kind)}, "
                f"{_quoted(target_ref_id)}, "
                f"{_runtime_ref_kind_enum(value_ref_kind)}, "
                f"{_quoted(value_ref_id)}, "
                f"{_quoted(register_peripheral)}, "
                f"{_quoted(register_name)}, "
                f"{-1 if register_offset is None else register_offset}, "
                f"{_quoted(register_id)}, "
                f"{_quoted(register_field_id)}, "
                f"{-1 if value_int is None else value_int}, "
                f"{_quoted(target)}, "
                f"{_quoted(value)}"
                "},"
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
                    register_peripheral,
                    register_name,
                    register_offset,
                    register_id,
                    register_field_id,
                    value_int,
                    target,
                    value,
                ) in operation_rows
            ],
        ),
        "",
        "enum class ConnectionCandidateId : std::uint16_t {",
        *_enum_rows(candidate_enum_map),
        "};",
        "",
        "struct ConnectionCandidateDescriptor {",
        "  const char* device;",
        "  ConnectionCandidateId candidate_id;",
        "  const char* candidate_name;",
        "  const char* pin;",
        "  const char* peripheral;",
        "  const char* signal;",
        "  const char* route_kind;",
        "  const char* route_selector;",
        "  int route_group_index;",
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
        "  const char* capability_id;",
        "};",
        *_std_array_lines(
            type_name="CandidateCapabilityRef",
            variable_name="kCandidateCapabilityRefs",
            row_lines=[
                "  {"
                f"ConnectionCandidateId::{candidate_enum_map[(device_name, candidate_id)]}, "
                f"{json.dumps(capability_id)}"
                "},"
                for device_name, candidate_id, capability_id in candidate_capability_ref_rows
            ],
        ),
        "",
        "enum class ConnectionGroupId : std::uint16_t {",
        *(
            [
                f"  {identifier},"
                for identifier in group_enum_map.values()
            ]
            if group_enum_map
            else ["  none,"]
        ),
        "};",
        "",
        "struct ConnectionGroupDescriptor {",
        "  const char* device;",
        "  ConnectionGroupId group_id;",
        "  const char* group_name;",
        "  const char* peripheral;",
        "  const char* package_name;",
        "  const char* conflict_group;",
        "  std::uint16_t signal_offset;",
        "  std::uint16_t signal_count;",
        "  std::uint16_t candidate_offset;",
        "  std::uint16_t candidate_count;",
        "};",
        *_std_array_lines(
            type_name="ConnectionGroupDescriptor",
            variable_name="kConnectionGroups",
            row_lines=[
                "  {"
                f"{json.dumps(device_name)}, "
                f"ConnectionGroupId::{group_enum_map[(device_name, group_id)]}, "
                f"{json.dumps(group_id)}, "
                f"{json.dumps(peripheral)}, "
                f"{_quoted(package_name)}, "
                f"{_quoted(conflict_group)}, "
                f"{group_signal_offsets.get((device_name, group_id), 0)}u, "
                f"{group_signal_counts.get((device_name, group_id), 0)}u, "
                f"{group_candidate_offsets.get((device_name, group_id), 0)}u, "
                f"{group_candidate_counts.get((device_name, group_id), 0)}u"
                "},"
                for (
                    device_name,
                    group_id,
                    peripheral,
                    _signals,
                    _candidate_ids,
                    package_name,
                    conflict_group,
                ) in group_rows
            ],
        ),
        "",
        "struct ConnectionGroupSignalRef {",
        "  ConnectionGroupId group_id;",
        "  const char* signal_name;",
        "};",
        *_std_array_lines(
            type_name="ConnectionGroupSignalRef",
            variable_name="kConnectionGroupSignals",
            row_lines=[
                "  {"
                f"ConnectionGroupId::{group_enum_map[(device_name, group_id)]}, "
                f"{json.dumps(signal_name)}"
                "},"
                for device_name, group_id, signal_name in group_signal_rows
            ],
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
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=f"{family_dir}/generated/connector_tables.hpp",
        content=content,
    )


def emit_interrupt_map_header(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> EmittedArtifact:
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
    body_lines = [
        "struct InterruptDescriptor {",
        "  const char* device;",
        "  const char* interrupt_name;",
        "  int line;",
        "  const char* peripheral;",
        "  const char* shared_group;",
        "  const char* alias_names;",
        "  int vector_slot;",
        "  const char* symbol_name;",
        "};",
        "inline constexpr InterruptDescriptor kInterruptMap[] = {",
        *[
            "  {"
            f"{json.dumps(device_name)}, "
            f"{json.dumps(interrupt_name)}, "
            f"{line}, "
            f"{_quoted(peripheral)}, "
            f"{_quoted(shared_group)}, "
            f"{json.dumps(','.join(alias_names))}, "
            f"{-1 if vector_slot is None else vector_slot}, "
            f"{_quoted(symbol_name)}"
            "},"
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
        ],
        "};",
    ]
    namespace_block = _cpp_namespace_block((_vendor, _family, "generated"), "\n".join(body_lines))
    content = "\n".join(
        [
            "#pragma once",
            "",
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
    _vendor, _family = family_dir.split("/", 1)
    body_lines = [
        "struct MemoryDescriptor {",
        "  const char* device;",
        "  const char* name;",
        "  const char* kind;",
        "  std::uintptr_t base_address;",
        "  std::size_t size_bytes;",
        "  const char* access;",
        "  const char* startup_roles;",
        "};",
        "inline constexpr MemoryDescriptor kMemoryMap[] = {",
        *[
            "  {"
            f"{json.dumps(device_name)}, "
            f"{json.dumps(name)}, "
            f"{json.dumps(kind)}, "
            f"0x{base_address:08X}u, "
            f"{size_bytes}u, "
            f"{json.dumps(access)}, "
            f"{json.dumps(','.join(startup_roles))}"
            "},"
            for (
                device_name,
                name,
                kind,
                base_address,
                size_bytes,
                access,
                startup_roles,
            ) in rows
        ],
        "};",
    ]
    namespace_block = _cpp_namespace_block((_vendor, _family, "generated"), "\n".join(body_lines))
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <cstddef>",
            "#include <cstdint>",
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
            package_pad.position_label,
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
            constraint.pin,
            constraint.kind,
            constraint.value,
        )
        for device in devices
        for constraint in sorted(device.pin_constraints, key=lambda item: item.constraint_id)
    ]
    _vendor, _family = family_dir.split("/", 1)
    body_lines = [
        "struct PackageDescriptor {",
        "  const char* device;",
        "  const char* package_name;",
        "  int pin_count;",
        "};",
        "inline constexpr PackageDescriptor kPackageMap[] = {",
        *[
            f"  {{{json.dumps(device_name)}, {json.dumps(package_name)}, {pin_count}}},"
            for device_name, package_name, pin_count in package_rows
        ],
        "};",
        "",
        "struct PackagePadDescriptor {",
        "  const char* device;",
        "  const char* package_name;",
        "  const char* pad_id;",
        "  const char* position_label;",
        "  int physical_index;",
        "  const char* pad_kind;",
        "  const char* bonded_pin;",
        "  const char* bonding_state;",
        "};",
        "inline constexpr PackagePadDescriptor kPackagePads[] = {",
        *[
            "  {"
            f"{json.dumps(device_name)}, "
            f"{json.dumps(package_name)}, "
            f"{json.dumps(pad_id)}, "
            f"{json.dumps(position_label)}, "
            f"{-1 if physical_index is None else physical_index}, "
            f"{json.dumps(pad_kind)}, "
            f"{_quoted(bonded_pin)}, "
            f"{json.dumps(bonding_state)}"
            "},"
            for (
                device_name,
                package_name,
                pad_id,
                position_label,
                physical_index,
                pad_kind,
                bonded_pin,
                bonding_state,
            ) in pad_rows
        ],
        "};",
        "",
        "struct PinConstraintDescriptor {",
        "  const char* device;",
        "  const char* pin_name;",
        "  const char* kind;",
        "  const char* value;",
        "};",
        *_std_array_lines(
            type_name="PinConstraintDescriptor",
            variable_name="kPinConstraints",
            row_lines=[
                f"  {{{json.dumps(device_name)}, {json.dumps(pin_name)}, "
                f"{json.dumps(kind)}, {_quoted(value)}}},"
                for device_name, pin_name, kind, value in constraint_rows
            ],
        ),
    ]
    namespace_block = _cpp_namespace_block((_vendor, _family, "generated"), "\n".join(body_lines))
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
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
            selector.register_target,
            selector.register_peripheral,
            selector.register_name,
            selector.register_offset,
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
            gate.enable_signal,
            gate.parent_node,
            gate.register_peripheral,
            gate.register_name,
            gate.register_offset,
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
            reset.reset_signal,
            reset.active_level,
            reset.register_peripheral,
            reset.register_name,
            reset.register_offset,
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
    node_index_map = {
        (device_name, node_id): index
        for index, (device_name, node_id, *_rest) in enumerate(node_rows)
    }
    selector_index_map = {
        (device_name, selector_id): index
        for index, (device_name, selector_id, *_rest) in enumerate(selector_rows)
    }
    gate_index_map = {
        (device_name, gate_id): index
        for index, (device_name, gate_id, *_rest) in enumerate(gate_rows)
    }
    reset_index_map = {
        (device_name, reset_id): index
        for index, (device_name, reset_id, *_rest) in enumerate(reset_rows)
    }
    selector_parent_options_by_selector = {
        (device_name, selector_id): tuple(parent_options)
        for (
            device_name,
            selector_id,
            parent_options,
            _register_target,
            _register_peripheral,
            _register_name,
            _register_offset,
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
    body_lines = [
        "enum class ClockNodeId : std::uint16_t {",
        *_enum_rows(node_enum_map),
        "};",
        "",
        "enum class ClockSelectorId : std::uint16_t {",
        *_enum_rows(selector_enum_map),
        "};",
        "",
        "enum class ClockGateId : std::uint16_t {",
        *_enum_rows(gate_enum_map),
        "};",
        "",
        "enum class ResetId : std::uint16_t {",
        *_enum_rows(reset_enum_map),
        "};",
        "",
        "struct ClockNodeDescriptor {",
        "  const char* device;",
        "  ClockNodeId node_id;",
        "  const char* node_name;",
        "  const char* kind;",
        "  int parent_index;",
        "  int selector_index;",
        "};",
        *_std_array_lines(
            type_name="ClockNodeDescriptor",
            variable_name="kClockNodes",
            row_lines=[
                "  {"
                f"{json.dumps(device_name)}, "
                f"ClockNodeId::{node_enum_map[(device_name, node_id)]}, "
                f"{json.dumps(node_id)}, "
                f"{json.dumps(kind)}, "
                f"{-1 if parent is None else node_index_map[(device_name, parent)]}, "
                f"{-1 if selector is None else selector_index_map[(device_name, selector)]}"
                "},"
                for device_name, node_id, kind, parent, selector in node_rows
            ],
        ),
        "",
        "struct ClockSelectorDescriptor {",
        "  const char* device;",
        "  ClockSelectorId selector_id;",
        "  const char* selector_name;",
        "  std::uint16_t parent_option_offset;",
        "  std::uint16_t parent_option_count;",
        "  const char* register_target;",
        "  const char* register_peripheral;",
        "  const char* register_name;",
        "  int register_offset;",
        "  const char* register_id;",
        "  const char* register_field_id;",
        "};",
        *_std_array_lines(
            type_name="ClockSelectorDescriptor",
            variable_name="kClockSelectors",
            row_lines=[
                "  {"
                f"{json.dumps(device_name)}, "
                f"ClockSelectorId::{selector_enum_map[(device_name, selector_id)]}, "
                f"{json.dumps(selector_id)}, "
                f"{selector_parent_offsets.get((device_name, selector_id), 0)}u, "
                f"{selector_parent_counts.get((device_name, selector_id), 0)}u, "
                f"{_quoted(register_target)}, "
                f"{_quoted(register_peripheral)}, "
                f"{_quoted(register_name)}, "
                f"{-1 if register_offset is None else register_offset}, "
                f"{_quoted(register_id)}, "
                f"{_quoted(register_field_id)}"
                "},"
                for (
                    device_name,
                    selector_id,
                    _parent_options,
                    register_target,
                    register_peripheral,
                    register_name,
                    register_offset,
                    register_id,
                    register_field_id,
                ) in selector_rows
            ],
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
        "  const char* device;",
        "  ClockGateId gate_id;",
        "  const char* gate_name;",
        "  const char* peripheral;",
        "  int parent_node_index;",
        "  const char* enable_signal;",
        "  const char* register_peripheral;",
        "  const char* register_name;",
        "  int register_offset;",
        "  const char* register_id;",
        "  const char* register_field_id;",
        "};",
        *_std_array_lines(
            type_name="ClockGateDescriptor",
            variable_name="kClockGates",
            row_lines=[
                "  {"
                f"{json.dumps(device_name)}, "
                f"ClockGateId::{gate_enum_map[(device_name, gate_id)]}, "
                f"{json.dumps(gate_id)}, "
                f"{_quoted(peripheral)}, "
                f"{-1 if parent_node is None else node_index_map[(device_name, parent_node)]}, "
                f"{json.dumps(enable_signal)}, "
                f"{_quoted(register_peripheral)}, "
                f"{_quoted(register_name)}, "
                f"{-1 if register_offset is None else register_offset}, "
                f"{_quoted(register_id)}, "
                f"{_quoted(register_field_id)}"
                "},"
                for (
                    device_name,
                    gate_id,
                    peripheral,
                    enable_signal,
                    parent_node,
                    register_peripheral,
                    register_name,
                    register_offset,
                    register_id,
                    register_field_id,
                ) in gate_rows
            ],
        ),
        "",
        "struct ResetDescriptor {",
        "  const char* device;",
        "  ResetId reset_id;",
        "  const char* reset_name;",
        "  const char* peripheral;",
        "  const char* reset_signal;",
        "  const char* active_level;",
        "  const char* register_peripheral;",
        "  const char* register_name;",
        "  int register_offset;",
        "  const char* register_id;",
        "  const char* register_field_id;",
        "};",
        *_std_array_lines(
            type_name="ResetDescriptor",
            variable_name="kResets",
            row_lines=[
                "  {"
                f"{json.dumps(device_name)}, "
                f"ResetId::{reset_enum_map[(device_name, reset_id)]}, "
                f"{json.dumps(reset_id)}, "
                f"{_quoted(peripheral)}, "
                f"{json.dumps(reset_signal)}, "
                f"{json.dumps(active_level)}, "
                f"{_quoted(register_peripheral)}, "
                f"{_quoted(register_name)}, "
                f"{-1 if register_offset is None else register_offset}, "
                f"{_quoted(register_id)}, "
                f"{_quoted(register_field_id)}"
                "},"
                for (
                    device_name,
                    reset_id,
                    peripheral,
                    reset_signal,
                    active_level,
                    register_peripheral,
                    register_name,
                    register_offset,
                    register_id,
                    register_field_id,
                ) in reset_rows
            ],
        ),
        "",
        "struct PeripheralClockBindingDescriptor {",
        "  const char* device;",
        "  const char* peripheral;",
        "  int clock_gate_index;",
        "  int reset_index;",
        "  int selector_index;",
        "};",
        *_std_array_lines(
            type_name="PeripheralClockBindingDescriptor",
            variable_name="kPeripheralClockBindings",
            row_lines=[
                "  {"
                f"{json.dumps(device_name)}, "
                f"{json.dumps(peripheral)}, "
                f"{-1 if clock_gate_id is None else gate_index_map[(device_name, clock_gate_id)]}, "
                f"{-1 if reset_id is None else reset_index_map[(device_name, reset_id)]}, "
                f"{-1 if selector_id is None else selector_index_map[(device_name, selector_id)]}"
                "},"
                for device_name, peripheral, clock_gate_id, reset_id, selector_id in binding_rows
            ],
        ),
    ]
    namespace_block = _cpp_namespace_block((_vendor, _family, "generated"), "\n".join(body_lines))
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=f"{family_dir}/generated/clock_tree_lite.hpp",
        content=content,
    )


def emit_startup_descriptors_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "struct VectorSlotDescriptor {",
                "  int slot;",
                "  const char* symbol_name;",
                "  const char* interrupt_name;",
                "  const char* kind;",
                "};",
                "inline constexpr VectorSlotDescriptor kVectorSlots[] = {",
                *[
                    "  {"
                    f"{vector_slot.slot}, "
                    f"{json.dumps(vector_slot.symbol_name)}, "
                    f"{_quoted(vector_slot.interrupt)}, "
                    f"{json.dumps(vector_slot.kind)}"
                    "},"
                    for vector_slot in sorted(device.vector_slots, key=lambda item: item.slot)
                ],
                "};",
                "",
                "struct StartupDescriptor {",
                "  const char* descriptor_id;",
                "  const char* kind;",
                "  const char* source_region;",
                "  const char* target_region;",
                "  const char* symbol;",
                "};",
                "inline constexpr StartupDescriptor kStartupDescriptors[] = {",
                *[
                    "  {"
                    f"{json.dumps(descriptor.descriptor_id)}, "
                    f"{json.dumps(descriptor.kind)}, "
                    f"{_quoted(descriptor.source_region)}, "
                    f"{_quoted(descriptor.target_region)}, "
                    f"{_quoted(descriptor.symbol)}"
                    "},"
                    for descriptor in sorted(
                        device.startup_descriptors,
                        key=lambda item: item.descriptor_id,
                    )
                ],
                "};",
            ]
        ),
    )
    content = "\n".join(
        [
            "#pragma once",
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
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "struct StartupVectorDescriptor {",
                "  int slot;",
                "  const char* symbol_name;",
                "};",
                "inline constexpr StartupVectorDescriptor kStartupVectorTable[] = {",
                *[
                    f"  {{{vector_slot.slot}, {json.dumps(vector_slot.symbol_name)}}},"
                    for vector_slot in sorted(device.vector_slots, key=lambda item: item.slot)
                ],
                "};",
            ]
        ),
    )
    content = "\n".join(
        [
            "// Generated descriptor-only startup vector unit.",
            "",
            namespace_block,
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
    """Emit a family-level C++ header mapping peripheral → (rcc_enable_signal, rcc_reset_signal)."""
    # Collect unique (peripheral, enable_signal, reset_signal) triples across every device.
    seen: set[str] = set()
    rows: list[tuple[str, str, str]] = []
    for device in devices:
        for peripheral in device.peripherals:
            if peripheral.rcc_enable_signal is None and peripheral.rcc_reset_signal is None:
                continue
            if peripheral.name in seen:
                continue
            seen.add(peripheral.name)
            rows.append(
                (
                    peripheral.name,
                    peripheral.rcc_enable_signal or "",
                    peripheral.rcc_reset_signal or "",
                )
            )
    rows.sort(key=lambda r: r[0])

    _vendor, _family = family_dir.split("/", 1)
    body_lines = [
        "struct RccDescriptor {",
        "  const char* peripheral;",
        "  const char* enable_signal;",
        "  const char* reset_signal;",
        "};",
        "inline constexpr RccDescriptor kRccMap[] = {",
        *[
            f"  {{{json.dumps(peripheral)}, {json.dumps(enable)}, {json.dumps(reset)}}},"
            for peripheral, enable, reset in rows
        ],
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
    body_lines = [
        "struct DmaDescriptor {",
        "  const char* peripheral;",
        "  const char* signal;",
        "  const char* controller;",
        "  const char* request_line;",
        "};",
        *_std_array_lines(
            type_name="DmaDescriptor",
            variable_name="kDmaMap",
            row_lines=[
                f"  {{{json.dumps(peripheral)}, {json.dumps(signal)}, "
                f"{json.dumps(controller)}, {json.dumps(request_line)}}},"
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
