"""Validation helpers for the generated runtime artifact contract."""

from __future__ import annotations

from alloy_codegen.connector_model import canonical_peripheral_class
from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact
from alloy_codegen.runtime_lite_emission import (
    RUNTIME_LITE_PERIPHERAL_CLASSES,
    runtime_lite_required_paths,
)


def find_runtime_cpp_string_violations(
    artifacts: tuple[EmittedArtifact, ...],
) -> tuple[str, ...]:
    """Return violations for generated runtime artifacts that still carry string literals."""

    violations: list[str] = []
    for artifact in artifacts:
        if artifact.artifact_kind != "generated-cpp":
            continue
        if "/generated/" not in f"/{artifact.path}":
            continue
        if artifact.content is None:
            continue
        for lineno, line in enumerate(artifact.content.splitlines(), start=1):
            stripped = line.strip()
            if stripped.startswith("#include") or stripped.startswith("#pragma once"):
                continue
            if '"' in line:
                violations.append(
                    f"{artifact.path}:{lineno} contains a string literal in runtime C++ output"
                )
    return tuple(violations)


def find_runtime_lite_contract_violations(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
    artifacts: tuple[EmittedArtifact, ...],
) -> tuple[str, ...]:
    """Return runtime-lite contract violations for foundational runtime consumers."""

    artifacts_by_path = {artifact.path: artifact for artifact in artifacts}
    violations: list[str] = []
    required_paths = runtime_lite_required_paths(family_dir=family_dir, devices=devices)
    for path in required_paths:
        if path not in artifacts_by_path:
            violations.append(f"missing runtime-lite artifact: {path}")

    forbidden_reflection_headers = (
        "connector_tables.hpp",
        "clock_tree_lite.hpp",
        "runtime_refs.hpp",
        "runtime_semantics.hpp",
        "rcc_map.hpp",
        "dma_map.hpp",
        "interrupt_map.hpp",
        "memory_map.hpp",
        "package_map.hpp",
    )
    forbidden_reflection_tokens = (
        "kConnectionCandidates",
        "kConnectionGroups",
        "kClockNodes",
        "kClockGates",
        "kPeripheralClockBindings",
    )
    for artifact in artifacts:
        if artifact.content is None:
            continue
        if f"/{family_dir}/generated/runtime/" not in f"/{artifact.path}":
            continue
        for lineno, line in enumerate(artifact.content.splitlines(), start=1):
            stripped = line.strip()
            if stripped.startswith("#include"):
                for header_name in forbidden_reflection_headers:
                    if header_name in stripped:
                        violations.append(
                            f"{artifact.path}:{lineno} depends on reflection header {header_name}"
                        )
            for token in forbidden_reflection_tokens:
                if token in line:
                    violations.append(
                        f"{artifact.path}:{lineno} leaks reflection payload token {token}"
                    )

    for device in devices:
        runtime_peripherals = tuple(
            peripheral
            for peripheral in device.peripherals
            if canonical_peripheral_class(peripheral.ip_name) in RUNTIME_LITE_PERIPHERAL_CLASSES
        )
        if not runtime_peripherals:
            continue

        device_runtime_root = f"{family_dir}/generated/runtime/devices/{device.identity.device}"
        runtime_candidates = tuple(
            candidate
            for candidate in device.connection_candidates
            if candidate.peripheral in {peripheral.name for peripheral in runtime_peripherals}
        )
        device_runtime_paths = {
            "peripheral_instances": f"{device_runtime_root}/peripheral_instances.hpp",
            "pins": f"{device_runtime_root}/pins.hpp",
            "registers": f"{device_runtime_root}/registers.hpp",
            "register_fields": f"{device_runtime_root}/register_fields.hpp",
            "clock_bindings": f"{device_runtime_root}/clock_bindings.hpp",
            "routes": f"{device_runtime_root}/routes.hpp",
        }
        content_by_key = {
            key: artifacts_by_path[path].content if path in artifacts_by_path else None
            for key, path in device_runtime_paths.items()
        }

        if (
            content_by_key["peripheral_instances"]
            and "PeripheralInstanceTraits<PeripheralId::"
            not in content_by_key["peripheral_instances"]
        ):
            violations.append(
                f"{device_runtime_paths['peripheral_instances']} does not emit per-instance traits"
            )
        if content_by_key["pins"] and "PinTraits<PinId::" not in content_by_key["pins"]:
            violations.append(f"{device_runtime_paths['pins']} does not emit pin traits")
        if (
            content_by_key["registers"]
            and "RegisterTraits<RegisterId::" not in content_by_key["registers"]
        ):
            violations.append(f"{device_runtime_paths['registers']} does not emit register traits")
        if (
            content_by_key["register_fields"]
            and "RegisterFieldTraits<FieldId::" not in content_by_key["register_fields"]
        ):
            violations.append(
                f"{device_runtime_paths['register_fields']} does not emit register field traits"
            )
        if (
            content_by_key["clock_bindings"]
            and "PeripheralClockBindingTraits<PeripheralId::"
            not in content_by_key["clock_bindings"]
        ):
            violations.append(
                f"{device_runtime_paths['clock_bindings']} does not emit "
                "peripheral clock binding traits"
            )
        if runtime_candidates:
            routes_content = content_by_key["routes"]
            if routes_content is None:
                violations.append(
                    f"missing runtime-lite routes header: {device_runtime_paths['routes']}"
                )
            elif "RouteTraits<" not in routes_content:
                violations.append(f"{device_runtime_paths['routes']} does not emit route traits")
    return tuple(violations)
