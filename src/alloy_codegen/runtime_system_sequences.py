"""Generated runtime system-sequence contract."""

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import (
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
    _enum_rows,
    _std_array_lines,
)
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
    _runtime_lite_startup_control_peripheral_names,
)

SYSTEM_SEQUENCES_HEADER = "system_sequences.hpp"


@dataclass(frozen=True, slots=True)
class RuntimeSystemSequenceStep:
    """One typed bring-up sequence step.

    ``secondary_core_release_register_id`` and
    ``secondary_core_release_register_secondary_id`` (added by
    ``expose-xtensa-dual-core-facts``) carry the typed ``register_id`` of
    the APP_CPU control register(s) for ``kind == "secondary-core-release"``
    steps.  ``secondary_core_release_operation`` carries the bit-level
    operation (``set-bit-0`` / ``clear-runstall-after-clkgate``).  All three
    fields are ``None`` for every other step kind.
    """

    sequence_id: str
    ordinal: int
    kind: str
    startup_descriptor_id: str | None
    peripheral_name: str | None
    system_clock_profile_id: str | None
    secondary_core_release_register_id: str | None = None
    secondary_core_release_register_secondary_id: str | None = None
    secondary_core_release_operation: str | None = None


def runtime_system_sequence_steps(
    device: CanonicalDeviceIR,
) -> tuple[RuntimeSystemSequenceStep, ...]:
    """Return the typed runtime bring-up sequence steps for one device."""

    startup_descriptors = tuple(
        sorted(device.startup_descriptors, key=lambda item: item.descriptor_id)
    )
    startup_controls = tuple(sorted(_runtime_lite_startup_control_peripheral_names(device)))
    profiles = tuple(sorted(device.system_clock_profiles, key=lambda item: item.profile_id))
    default_profile = next((profile for profile in profiles if profile.kind == "default"), None)

    steps: list[RuntimeSystemSequenceStep] = []
    ordinal = 0
    for descriptor in startup_descriptors:
        steps.append(
            RuntimeSystemSequenceStep(
                sequence_id="default_bringup",
                ordinal=ordinal,
                kind="startup-descriptor",
                startup_descriptor_id=descriptor.descriptor_id,
                peripheral_name=None,
                system_clock_profile_id=None,
            )
        )
        ordinal += 1

    for peripheral_name in startup_controls:
        steps.append(
            RuntimeSystemSequenceStep(
                sequence_id="default_bringup",
                ordinal=ordinal,
                kind="startup-control",
                startup_descriptor_id=None,
                peripheral_name=peripheral_name,
                system_clock_profile_id=None,
            )
        )
        ordinal += 1

    if default_profile is not None:
        steps.append(
            RuntimeSystemSequenceStep(
                sequence_id="default_bringup",
                ordinal=ordinal,
                kind="system-clock-profile",
                startup_descriptor_id=None,
                peripheral_name=None,
                system_clock_profile_id=default_profile.profile_id,
            )
        )
        ordinal += 1

    # Secondary-core release (added by ``expose-xtensa-dual-core-facts``).
    # Emitted only on asymmetric Xtensa devices.  The step references the
    # APP_CPU control register(s) by typed ``register_id``; the bit-level
    # operation is carried alongside so consumers can inline the writes
    # without parsing the register name.
    if (
        device.multicore_topology == "xtensa_asymmetric_dual_core"
        and device.app_cpu_control_plane is not None
    ):
        steps.append(
            RuntimeSystemSequenceStep(
                sequence_id="default_bringup",
                ordinal=ordinal,
                kind="secondary-core-release",
                startup_descriptor_id=None,
                peripheral_name=None,
                system_clock_profile_id=None,
                secondary_core_release_register_id=(
                    device.app_cpu_control_plane.release_register
                ),
                secondary_core_release_register_secondary_id=(
                    device.app_cpu_control_plane.release_register_secondary
                ),
                secondary_core_release_operation=(
                    device.app_cpu_control_plane.operation
                ),
            )
        )

    return tuple(steps)


def runtime_system_sequences_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(
            family_dir,
            device.identity.device,
            SYSTEM_SEQUENCES_HEADER,
        )
        for device in devices
        if device.startup_descriptors
        or device.system_clock_profiles
        or _runtime_lite_startup_control_peripheral_names(device)
    )


def emit_runtime_system_sequences_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    startup_descriptors = tuple(
        sorted(device.startup_descriptors, key=lambda item: item.descriptor_id)
    )
    startup_controls = tuple(sorted(_runtime_lite_startup_control_peripheral_names(device)))
    profiles = tuple(sorted(device.system_clock_profiles, key=lambda item: item.profile_id))
    default_profile = next((profile for profile in profiles if profile.kind == "default"), None)
    safe_profile = next((profile for profile in profiles if profile.kind == "safe"), None)
    steps = runtime_system_sequence_steps(device)

    step_kind_enum_map = {
        "startup-descriptor": "startup_descriptor",
        "startup-control": "startup_control",
        "system-clock-profile": "system_clock_profile",
        "secondary-core-release": "secondary_core_release",
    }
    secondary_release_operation_enum_map = {
        "set-bit-0": "set_bit_0",
        "clear-runstall-after-clkgate": "clear_runstall_after_clkgate",
    }

    def _startup_descriptor_ref(descriptor_id: str | None) -> str:
        if descriptor_id is None:
            return "StartupDescriptorId::none"
        return f"StartupDescriptorId::{_enum_identifier(descriptor_id)}"

    def _peripheral_ref(peripheral_name: str | None) -> str:
        if peripheral_name is None:
            return "PeripheralId::none"
        return f"PeripheralId::{_enum_identifier(peripheral_name)}"

    def _profile_ref(profile_id: str | None) -> str:
        if profile_id is None:
            return "SystemClockProfileId::none"
        return f"SystemClockProfileId::{_enum_identifier(profile_id)}"

    def _register_ref(register_id: str | None) -> str:
        if register_id is None:
            return "RegisterId::none"
        return f"RegisterId::{_enum_identifier(register_id)}"

    def _operation_ref(operation: str | None) -> str:
        if operation is None:
            return "SecondaryCoreReleaseOperationId::none"
        ident = secondary_release_operation_enum_map.get(operation)
        if ident is None:
            return "SecondaryCoreReleaseOperationId::none"
        return f"SecondaryCoreReleaseOperationId::{ident}"

    descriptor_count = len(startup_descriptors)
    startup_control_count = len(startup_controls)
    step_rows: list[str] = []
    for step in steps:
        step_rows.append(
            "  {"
            f"SystemSequenceId::{_enum_identifier(step.sequence_id)}, "
            f"{step.ordinal}u, "
            f"SystemSequenceStepKindId::{step_kind_enum_map[step.kind]}, "
            f"{_startup_descriptor_ref(step.startup_descriptor_id)}, "
            f"{_peripheral_ref(step.peripheral_name)}, "
            f"{_profile_ref(step.system_clock_profile_id)}, "
            f"{_register_ref(step.secondary_core_release_register_id)}, "
            f"{_register_ref(step.secondary_core_release_register_secondary_id)}, "
            f"{_operation_ref(step.secondary_core_release_operation)}"
            "},"
        )

    body = "\n".join(
        [
            "enum class SystemSequenceId : std::uint16_t {",
            "  none,",
            "  default_bringup,",
            "};",
            "",
            "enum class SystemSequenceStepKindId : std::uint16_t {",
            "  none,",
            *_enum_rows(step_kind_enum_map, empty_identifier=None),
            "};",
            "",
            "enum class SecondaryCoreReleaseOperationId : std::uint16_t {",
            "  none,",
            *_enum_rows(secondary_release_operation_enum_map, empty_identifier=None),
            "};",
            "",
            "struct SystemSequenceStepDescriptor {",
            "  SystemSequenceId sequence_id;",
            "  std::uint16_t ordinal;",
            "  SystemSequenceStepKindId kind_id;",
            "  StartupDescriptorId startup_descriptor_id;",
            "  PeripheralId peripheral_id;",
            "  SystemClockProfileId system_clock_profile_id;",
            "  RegisterId secondary_core_release_register_id;",
            "  RegisterId secondary_core_release_register_secondary_id;",
            "  SecondaryCoreReleaseOperationId secondary_core_release_operation_id;",
            "};",
            *_std_array_lines(
                type_name="SystemSequenceStepDescriptor",
                variable_name="kSystemSequenceSteps",
                row_lines=step_rows,
            ),
            "",
            "template<SystemSequenceId Id>",
            "struct SystemSequenceTraits {",
            "  static constexpr bool kPresent = false;",
            "  static constexpr std::uint16_t kStepCount = 0u;",
            "  static constexpr std::uint16_t kStartupDescriptorCount = 0u;",
            "  static constexpr std::uint16_t kStartupControlCount = 0u;",
            "  static constexpr SystemClockProfileId kDefaultSystemClockProfileId = "
            "SystemClockProfileId::none;",
            "  static constexpr SystemClockProfileId kSafeSystemClockProfileId = "
            "SystemClockProfileId::none;",
            "};",
            "",
            "template<>",
            "struct SystemSequenceTraits<SystemSequenceId::default_bringup> {",
            "  static constexpr bool kPresent = true;",
            f"  static constexpr std::uint16_t kStepCount = {len(step_rows)}u;",
            f"  static constexpr std::uint16_t kStartupDescriptorCount = {descriptor_count}u;",
            f"  static constexpr std::uint16_t kStartupControlCount = {startup_control_count}u;",
            "  static constexpr SystemClockProfileId kDefaultSystemClockProfileId = "
            f"{_profile_ref(default_profile.profile_id if default_profile is not None else None)};",
            "  static constexpr SystemClockProfileId kSafeSystemClockProfileId = "
            f"{_profile_ref(safe_profile.profile_id if safe_profile is not None else None)};",
            "};",
        ]
    )

    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "peripheral_instances.hpp"',
            '#include "registers.hpp"',
            '#include "startup.hpp"',
            '#include "system_clock.hpp"',
            "",
            _cpp_namespace_block(_runtime_device_namespace_components(device), body),
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir,
            device.identity.device,
            SYSTEM_SEQUENCES_HEADER,
        ),
        content=content,
    )


__all__ = [
    "emit_runtime_system_sequences_header",
    "RuntimeSystemSequenceStep",
    "runtime_system_sequences_required_paths",
    "runtime_system_sequence_steps",
]
