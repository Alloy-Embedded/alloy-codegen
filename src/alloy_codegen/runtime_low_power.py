"""Generated runtime low-power and wakeup contract."""

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

LOW_POWER_HEADER = "low_power.hpp"


def _low_power_header_path(family_dir: str, device: CanonicalDeviceIR) -> str:
    return _device_runtime_generated_path(family_dir, device.identity.device, LOW_POWER_HEADER)


def runtime_low_power_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(_low_power_header_path(family_dir, device) for device in devices)


def _has_sleepdeep_control(device: CanonicalDeviceIR) -> bool:
    return any(
        field.peripheral.upper() == "SCB"
        and field.register_name.upper() == "SCR"
        and field.name.upper() == "SLEEPDEEP"
        for field in device.register_fields
    )


def emit_runtime_low_power_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact:
    modes: list[tuple[str, bool]] = [("sleep", False)]
    if _has_sleepdeep_control(device):
        modes.append(("deep_sleep", True))

    wakeup_constraints = tuple(
        sorted(
            (
                constraint
                for constraint in device.pin_constraints
                if constraint.kind == "wakeup-capable" and constraint.value
            ),
            key=lambda item: (item.pin, item.value or ""),
        )
    )

    mode_trait_lines = [
        "enum class LowPowerModeId : std::uint16_t {",
        "  none,",
        *[f"  {_enum_identifier(mode_id)}," for mode_id, _ in modes],
        "};",
        "",
        "struct LowPowerModeDescriptor {",
        "  LowPowerModeId mode_id;",
        "  bool uses_sleepdeep;",
        "};",
        "",
        "template<LowPowerModeId Id>",
        "struct LowPowerModeTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr bool kUsesSleepdeep = false;",
        "};",
        "",
    ]
    for mode_id, uses_sleepdeep in modes:
        mode_trait_lines.extend(
            [
                "template<>",
                f"struct LowPowerModeTraits<LowPowerModeId::{_enum_identifier(mode_id)}> {{",
                "  static constexpr bool kPresent = true;",
                (
                    "  static constexpr bool kUsesSleepdeep = "
                    f"{'true' if uses_sleepdeep else 'false'};"
                ),
                "};",
                "",
            ]
        )

    wakeup_trait_lines = [
        "enum class WakeupTagId : std::uint16_t {",
        "  none,",
        *[
            f"  {_enum_identifier(constraint.value or 'none')},"
            for constraint in wakeup_constraints
        ],
        "};",
        "",
        "enum class WakeupSourceId : std::uint16_t {",
        "  none,",
        *[
            f"  {_enum_identifier(f'{constraint.pin}_{constraint.value}')},"
            for constraint in wakeup_constraints
        ],
        "};",
        "",
        "struct WakeupSourceDescriptor {",
        "  WakeupSourceId wakeup_source_id;",
        "  PinId pin_id;",
        "  WakeupTagId tag_id;",
        "};",
        "",
        "template<WakeupSourceId Id>",
        "struct WakeupSourceTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr PinId kPinId = PinId::none;",
        "  static constexpr WakeupTagId kTagId = WakeupTagId::none;",
        "};",
        "",
        "template<PinId Pin>",
        "struct WakeupPinTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::none;",
        "  static constexpr WakeupTagId kTagId = WakeupTagId::none;",
        "};",
        "",
    ]

    wakeup_rows: list[str] = []
    for constraint in wakeup_constraints:
        source_id = _enum_identifier(f"{constraint.pin}_{constraint.value}")
        pin_id = _enum_identifier(constraint.pin)
        tag = constraint.value or ""
        wakeup_rows.append(
            "  {"
            f"WakeupSourceId::{source_id}, "
            f"PinId::{pin_id}, "
            f"WakeupTagId::{_enum_identifier(tag)}"
            "},"
        )
        wakeup_trait_lines.extend(
            [
                "template<>",
                f"struct WakeupSourceTraits<WakeupSourceId::{source_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr PinId kPinId = PinId::{pin_id};",
                f"  static constexpr WakeupTagId kTagId = WakeupTagId::{_enum_identifier(tag)};",
                "};",
                "",
                "template<>",
                f"struct WakeupPinTraits<PinId::{pin_id}> {{",
                "  static constexpr bool kPresent = true;",
                f"  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::{source_id};",
                f"  static constexpr WakeupTagId kTagId = WakeupTagId::{_enum_identifier(tag)};",
                "};",
                "",
            ]
        )

    mode_rows = [
        "  {"
        f"LowPowerModeId::{_enum_identifier(mode_id)}, "
        f"{'true' if uses_sleepdeep else 'false'}"
        "},"
        for mode_id, uses_sleepdeep in modes
    ]

    body = "\n".join(
        [
            *mode_trait_lines,
            *_std_array_lines(
                type_name="LowPowerModeDescriptor",
                variable_name="kLowPowerModes",
                row_lines=mode_rows,
            ),
            "",
            *wakeup_trait_lines,
            *_std_array_lines(
                type_name="WakeupSourceDescriptor",
                variable_name="kWakeupSources",
                row_lines=wakeup_rows,
            ),
        ]
    )

    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../types.hpp"',
            "",
            _cpp_namespace_block(_runtime_device_namespace_components(device), body),
            "",
        ]
    )
    return _cpp_artifact(path=_low_power_header_path(family_dir, device), content=content)


__all__ = [
    "LOW_POWER_HEADER",
    "emit_runtime_low_power_header",
    "runtime_low_power_required_paths",
]
