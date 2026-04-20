"""Generated runtime clock-profile and clock-config contracts."""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import _cpp_artifact, _cpp_namespace_block, _enum_identifier, _std_array_lines
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
)
from .runtime_system_clock import _safe_enum_identifier

CLOCK_PROFILES_HEADER = "clock_profiles.hpp"
CLOCK_CONFIG_HEADER = "clock_config.hpp"


def _clock_profiles_header_path(family_dir: str, device: CanonicalDeviceIR) -> str:
    return _device_runtime_generated_path(family_dir, device.identity.device, CLOCK_PROFILES_HEADER)


def _clock_config_header_path(family_dir: str, device: CanonicalDeviceIR) -> str:
    return _device_runtime_generated_path(family_dir, device.identity.device, CLOCK_CONFIG_HEADER)


def runtime_clock_config_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    paths: list[str] = []
    for device in devices:
        paths.append(_clock_profiles_header_path(family_dir, device))
        paths.append(_clock_config_header_path(family_dir, device))
    return tuple(paths)


def _profile_ref(profile_id: str | None) -> str:
    if profile_id is None:
        return "ClockProfileId::none"
    return f"ClockProfileId::{_safe_enum_identifier(profile_id)}"


def _profile_function_suffix(profile_id: str) -> str:
    return _enum_identifier(profile_id)


def emit_runtime_clock_profiles_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    profiles = tuple(sorted(device.system_clock_profiles, key=lambda item: item.profile_id))
    default_profile = next((profile for profile in profiles if profile.kind == "default"), None)
    safe_profile = next((profile for profile in profiles if profile.kind == "safe"), None)
    max_profile = max(profiles, key=lambda item: item.sysclk_hz, default=None)

    profile_id_rows = [f"  {_profile_ref(profile.profile_id)}," for profile in profiles]
    body_lines = [
        "using ClockProfileId = SystemClockProfileId;",
        "using ClockProfileKindId = SystemClockProfileKindId;",
        "using ClockProfileSourceKindId = SystemClockSourceKindId;",
        "using ClockProfileDescriptor = SystemClockProfileDescriptor;",
        "",
        "template<ClockProfileId Id>",
        "using ClockProfileTraits = SystemClockProfileTraits<Id>;",
        "",
        *_std_array_lines(
            type_name="ClockProfileId",
            variable_name="kClockProfileIds",
            row_lines=profile_id_rows,
        ),
        "",
        "inline constexpr auto kClockProfiles = kSystemClockProfiles;",
        (
            "inline constexpr ClockProfileId kDefaultClockProfileId = "
            f"{_profile_ref(default_profile.profile_id if default_profile is not None else None)};"
        ),
        (
            "inline constexpr ClockProfileId kSafeClockProfileId = "
            f"{_profile_ref(safe_profile.profile_id if safe_profile is not None else None)};"
        ),
        (
            "inline constexpr ClockProfileId kMaxClockProfileId = "
            f"{_profile_ref(max_profile.profile_id if max_profile is not None else None)};"
        ),
        (
            "inline constexpr std::uint32_t kMaxClockFrequencyHz = "
            f"{0 if max_profile is None else max_profile.sysclk_hz}u;"
        ),
    ]
    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "system_clock.hpp"',
            "",
            _cpp_namespace_block(
                _runtime_device_namespace_components(device), "\n".join(body_lines)
            ),
            "",
        ]
    )
    return _cpp_artifact(
        path=_clock_profiles_header_path(family_dir, device),
        content=content,
    )


def emit_runtime_clock_config_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    profiles = tuple(sorted(device.system_clock_profiles, key=lambda item: item.profile_id))
    default_profile = next((profile for profile in profiles if profile.kind == "default"), None)
    safe_profile = next((profile for profile in profiles if profile.kind == "safe"), None)
    max_profile = max(profiles, key=lambda item: item.sysclk_hz, default=None)

    body_lines = [
        "template<ClockProfileId Id>",
        "inline bool apply_clock_profile() {",
        "  return apply_system_clock_profile<Id>();",
        "}",
        "",
        "inline bool apply_default_clock_profile() {",
        (
            "  return false;"
            if default_profile is None
            else f"  return apply_clock_profile<{_profile_ref(default_profile.profile_id)}>();"
        ),
        "}",
        "",
        "inline bool apply_safe_clock_profile() {",
        (
            "  return false;"
            if safe_profile is None
            else f"  return apply_clock_profile<{_profile_ref(safe_profile.profile_id)}>();"
        ),
        "}",
        "",
        "inline bool apply_max_clock_profile() {",
        (
            "  return false;"
            if max_profile is None
            else f"  return apply_clock_profile<{_profile_ref(max_profile.profile_id)}>();"
        ),
        "}",
        "",
    ]
    for profile in profiles:
        function_name = f"apply_clock_profile_{_profile_function_suffix(profile.profile_id)}"
        body_lines.extend(
            [
                f"inline bool {function_name}() {{",
                f"  return apply_clock_profile<{_profile_ref(profile.profile_id)}>();",
                "}",
                "",
            ]
        )

    content = "\n".join(
        [
            "#pragma once",
            "",
            '#include "clock_profiles.hpp"',
            "",
            _cpp_namespace_block(
                _runtime_device_namespace_components(device), "\n".join(body_lines)
            ),
            "",
        ]
    )
    return _cpp_artifact(
        path=_clock_config_header_path(family_dir, device),
        content=content,
    )


__all__ = [
    "CLOCK_CONFIG_HEADER",
    "CLOCK_PROFILES_HEADER",
    "emit_runtime_clock_config_header",
    "emit_runtime_clock_profiles_header",
    "runtime_clock_config_required_paths",
]
