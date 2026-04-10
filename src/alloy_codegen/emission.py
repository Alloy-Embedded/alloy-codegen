"""Deterministic metadata emission helpers."""

from __future__ import annotations

import json
from pathlib import Path

from alloy_codegen.bootstrap import BOOTSTRAP_FAMILY, BOOTSTRAP_VENDOR
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


def _namespace_components(device: CanonicalDeviceIR) -> tuple[str, str, str]:
    return (
        _identifier(device.identity.vendor),
        _identifier(device.identity.family),
        _identifier(device.identity.device),
    )


def _cpp_namespace_block(namespaces: tuple[str, ...], body: str) -> str:
    lines = [f"namespace {name} {{" for name in namespaces]
    lines.append(body)
    lines.extend("}" for _ in namespaces)
    return "\n".join(lines)


def _quoted(value: str | None) -> str:
    return "nullptr" if value is None else json.dumps(value)


def _unique_packages(devices: tuple[CanonicalDeviceIR, ...]) -> list[dict[str, object]]:
    packages: dict[str, dict[str, object]] = {}
    for device in devices:
        for package in device.packages:
            packages.setdefault(package.name, to_primitive(package))
    return [packages[name] for name in sorted(packages)]


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
                    entry["signals"][signal_key]
                    for signal_key in sorted(entry["signals"])
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


def emit_artifact_manifest(
    *,
    family_dir: str,
    artifact_manifest: ArtifactManifest,
) -> EmittedArtifact:
    return _text_artifact(
        path=f"{family_dir}/artifact-manifest.json",
        artifact_kind="canonical-metadata",
        payload=artifact_manifest.to_dict(),
    )


def emit_device_metadata(*, family_dir: str, device: CanonicalDeviceIR) -> EmittedArtifact:
    return _text_artifact(
        path=f"{family_dir}/{device.identity.device}/device.json",
        artifact_kind="canonical-metadata",
        payload=device.to_dict(),
    )


def emit_validation_report(*, family_dir: str, report: ValidationReport) -> EmittedArtifact:
    return _text_artifact(
        path=f"{family_dir}/validation-report.json",
        artifact_kind="validation-report",
        payload=report.to_dict(),
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
                "metadata_path": f"{family_dir}/{device.identity.device}/device.json",
            }
            for device in sorted(devices, key=lambda item: item.identity.device)
        ],
    }
    return _text_artifact(
        path=f"{family_dir}/family-index.json",
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
        path=f"{family_dir}/family-connectivity.json",
        artifact_kind="canonical-metadata",
        payload=payload,
    )


def emit_register_map_header(*, family_dir: str, device: CanonicalDeviceIR) -> EmittedArtifact:
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "inline constexpr const char* kDevice = "
                f"{json.dumps(device.identity.device)};",
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
        path=f"{family_dir}/{device.identity.device}/register_map.hpp",
        content=content,
    )


def emit_pin_functions_header(*, family_dir: str, device: CanonicalDeviceIR) -> EmittedArtifact:
    pin_lines = [
        "struct PinFunctionDescriptor {",
        "  const char* pin_name;",
        "  const char* function;",
        "  const char* peripheral;",
        "  const char* signal;",
        "  int af_number;",
        "};",
        "inline constexpr PinFunctionDescriptor kPinFunctions[] = {",
    ]
    for pin in sorted(device.pins, key=lambda item: (item.port or "", item.number, item.name)):
        for signal in pin.signals:
            pin_lines.append(
                "  {"
                f"{json.dumps(pin.name)}, "
                f"{json.dumps(signal.function)}, "
                f"{_quoted(signal.peripheral)}, "
                f"{_quoted(signal.signal)}, "
                f"{-1 if signal.af_number is None else signal.af_number}"
                "},"
            )
    pin_lines.append("};")
    namespace_block = _cpp_namespace_block(_namespace_components(device), "\n".join(pin_lines))
    content = "\n".join(
        [
            "#pragma once",
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=f"{family_dir}/{device.identity.device}/pin_functions.hpp",
        content=content,
    )


def emit_startup_source(*, family_dir: str, device: CanonicalDeviceIR) -> EmittedArtifact:
    namespace_block = _cpp_namespace_block(
        _namespace_components(device),
        "\n".join(
            [
                "struct InterruptDescriptor {",
                "  const char* name;",
                "  int line;",
                "  const char* peripheral;",
                "};",
                "inline constexpr InterruptDescriptor kInterruptTable[] = {",
                *[
                    "  {"
                    f"{json.dumps(interrupt.name)}, "
                    f"{interrupt.line}, "
                    f"{_quoted(interrupt.peripheral)}"
                    "},"
                    for interrupt in sorted(
                        device.interrupts,
                        key=lambda item: (item.line, item.name),
                    )
                ],
                "};",
            ]
        ),
    )
    content = "\n".join(
        [
            "// Generated startup metadata bootstrap unit.",
            "#include <cstdint>",
            "",
            namespace_block,
            "",
        ]
    )
    return _cpp_artifact(
        path=f"{family_dir}/{device.identity.device}/startup.cpp",
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
    namespace_block = _cpp_namespace_block(
        (BOOTSTRAP_VENDOR, BOOTSTRAP_FAMILY, "generated", "peripherals"),
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
        path=f"{family_dir}/publication-summary.json",
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
