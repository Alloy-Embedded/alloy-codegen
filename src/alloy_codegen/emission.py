"""Deterministic metadata emission helpers."""

from __future__ import annotations

import json
from pathlib import Path

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
        or any(
            token in value.lower()
            for peripheral in device.peripherals
            for value in (peripheral.name, peripheral.ip_name)
            for token in ("dma", "dmamux", "edma")
        )
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
                "publishable": _device_descriptor_coverage(device)["publishable"],
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
    if not devices:
        raise ValueError("Coverage report emission requires at least one device.")
    first_device = devices[0]
    device_coverage = [
        _device_descriptor_coverage(device)
        for device in sorted(devices, key=lambda item: item.identity.device)
    ]
    payload = {
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
    return _text_artifact(
        path=_family_report_path(family_dir, "coverage.json"),
        artifact_kind="coverage-report",
        payload=payload,
    )


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
        "  const char* register_profile;",
        "  const char* signal_roles;",
        "};",
        "inline constexpr IpBlockDescriptor kIpBlock = {",
        f"  {json.dumps(ip_block.ip_name)},",
        f"  {json.dumps(ip_block.ip_version)},",
        f"  {json.dumps(ip_block.peripheral_class)},",
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
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                f"inline constexpr const char* kDevice = {json.dumps(device.identity.device)};",
                "struct PeripheralBase {",
                "  const char* name;",
                "  std::uintptr_t address;",
                "};",
                "inline constexpr PeripheralBase kPeripheralBases[] = {",
                *[
                    f"  {{{json.dumps(peripheral.name)}, 0x{peripheral.base_address:08X}u}},"
                    for peripheral in sorted(device.peripherals, key=lambda item: item.name)
                ],
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
        path=_device_generated_path(family_dir, device.identity.device, "register_map.hpp"),
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
    requirement_rows = [
        (
            device.identity.device,
            requirement.requirement_id,
            requirement.kind,
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

    body_lines = [
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
        "struct RouteRequirementDescriptor {",
        "  const char* device;",
        "  const char* requirement_id;",
        "  const char* kind;",
        "  const char* target;",
        "  const char* value;",
        "};",
        "inline constexpr RouteRequirementDescriptor kRouteRequirements[] = {",
        *[
            f"  {{{json.dumps(device_name)}, {json.dumps(requirement_id)}, "
            f"{json.dumps(kind)}, {_quoted(target)}, {_quoted(value)}}},"
            for device_name, requirement_id, kind, target, value in requirement_rows
        ],
        "};",
        "",
        "struct RouteOperationDescriptor {",
        "  const char* device;",
        "  const char* operation_id;",
        "  const char* kind;",
        "  const char* target;",
        "  const char* value;",
        "};",
        "inline constexpr RouteOperationDescriptor kRouteOperations[] = {",
        *[
            f"  {{{json.dumps(device_name)}, {json.dumps(operation_id)}, "
            f"{json.dumps(kind)}, {json.dumps(target)}, {_quoted(value)}}},"
            for device_name, operation_id, kind, target, value in operation_rows
        ],
        "};",
        "",
        "struct ConnectionCandidateDescriptor {",
        "  const char* device;",
        "  const char* candidate_id;",
        "  const char* pin;",
        "  const char* peripheral;",
        "  const char* signal;",
        "  const char* route_kind;",
        "  const char* route_selector;",
        "  const char* route_group_id;",
        "  const char* requirement_ids;",
        "  const char* operation_ids;",
        "  const char* capability_ids;",
        "};",
        "inline constexpr ConnectionCandidateDescriptor kConnectionCandidates[] = {",
        *[
            f"  {{{json.dumps(device_name)}, {json.dumps(candidate_id)}, {json.dumps(pin)}, "
            f"{json.dumps(peripheral)}, {json.dumps(signal)}, {json.dumps(route_kind)}, "
            f"{_quoted(route_selector)}, {_quoted(route_group_id)}, "
            f"{json.dumps(','.join(requirement_ids))}, {json.dumps(','.join(operation_ids))}, "
            f"{json.dumps(','.join(capability_ids))}}},"
            for (
                device_name,
                candidate_id,
                pin,
                peripheral,
                signal,
                route_kind,
                route_selector,
                route_group_id,
                requirement_ids,
                operation_ids,
                capability_ids,
            ) in candidate_rows
        ],
        "};",
        "",
        "struct ConnectionGroupDescriptor {",
        "  const char* device;",
        "  const char* group_id;",
        "  const char* peripheral;",
        "  const char* signals;",
        "  const char* candidate_ids;",
        "  const char* package_name;",
        "  const char* conflict_group;",
        "};",
        "inline constexpr ConnectionGroupDescriptor kConnectionGroups[] = {",
        *[
            f"  {{{json.dumps(device_name)}, {json.dumps(group_id)}, {json.dumps(peripheral)}, "
            f"{json.dumps(','.join(signals))}, {json.dumps(','.join(candidate_ids))}, "
            f"{_quoted(package_name)}, {_quoted(conflict_group)}}},"
            for (
                device_name,
                group_id,
                peripheral,
                signals,
                candidate_ids,
                package_name,
                conflict_group,
            ) in group_rows
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

    _vendor, _family = family_dir.split("/", 1)
    body_lines = [
        "struct ClockNodeDescriptor {",
        "  const char* device;",
        "  const char* node_id;",
        "  const char* kind;",
        "  const char* parent;",
        "  const char* selector;",
        "};",
        *_std_array_lines(
            type_name="ClockNodeDescriptor",
            variable_name="kClockNodes",
            row_lines=[
                f"  {{{json.dumps(device_name)}, {json.dumps(node_id)}, {json.dumps(kind)}, "
                f"{_quoted(parent)}, {_quoted(selector)}}},"
                for device_name, node_id, kind, parent, selector in node_rows
            ],
        ),
        "",
        "struct ClockSelectorDescriptor {",
        "  const char* device;",
        "  const char* selector_id;",
        "  const char* parent_options;",
        "  const char* register_target;",
        "};",
        *_std_array_lines(
            type_name="ClockSelectorDescriptor",
            variable_name="kClockSelectors",
            row_lines=[
                f"  {{{json.dumps(device_name)}, {json.dumps(selector_id)}, "
                f"{json.dumps(','.join(parent_options))}, {_quoted(register_target)}}},"
                for device_name, selector_id, parent_options, register_target in selector_rows
            ],
        ),
        "",
        "struct ClockGateDescriptor {",
        "  const char* device;",
        "  const char* gate_id;",
        "  const char* peripheral;",
        "  const char* enable_signal;",
        "  const char* parent_node;",
        "};",
        *_std_array_lines(
            type_name="ClockGateDescriptor",
            variable_name="kClockGates",
            row_lines=[
                f"  {{{json.dumps(device_name)}, {json.dumps(gate_id)}, {_quoted(peripheral)}, "
                f"{json.dumps(enable_signal)}, {_quoted(parent_node)}}},"
                for device_name, gate_id, peripheral, enable_signal, parent_node in gate_rows
            ],
        ),
        "",
        "struct ResetDescriptor {",
        "  const char* device;",
        "  const char* reset_id;",
        "  const char* peripheral;",
        "  const char* reset_signal;",
        "  const char* active_level;",
        "};",
        *_std_array_lines(
            type_name="ResetDescriptor",
            variable_name="kResets",
            row_lines=[
                f"  {{{json.dumps(device_name)}, {json.dumps(reset_id)}, {_quoted(peripheral)}, "
                f"{json.dumps(reset_signal)}, {json.dumps(active_level)}}},"
                for device_name, reset_id, peripheral, reset_signal, active_level in reset_rows
            ],
        ),
        "",
        "struct PeripheralClockBindingDescriptor {",
        "  const char* device;",
        "  const char* peripheral;",
        "  const char* clock_gate_id;",
        "  const char* reset_id;",
        "  const char* selector_id;",
        "};",
        *_std_array_lines(
            type_name="PeripheralClockBindingDescriptor",
            variable_name="kPeripheralClockBindings",
            row_lines=[
                "  {"
                f"{json.dumps(device_name)}, "
                f"{json.dumps(peripheral)}, "
                f"{_quoted(clock_gate_id)}, "
                f"{_quoted(reset_id)}, "
                f"{_quoted(selector_id)}"
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
