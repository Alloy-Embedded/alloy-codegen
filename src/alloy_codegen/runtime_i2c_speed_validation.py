"""Generated runtime I2C-speed validation contract.

Projects ``device.i2c_speed_options`` into a C++20 concept so HAL
drivers can constrain templates with
``ValidI2cSpeed<PeripheralId, SpeedHz>`` and refuse invalid bus
speeds at compile time.

Implemented as a ``consteval`` predicate over the per-peripheral
``speed_hz`` set so consumers can write
``requires ValidI2cSpeed<PeripheralId::I2C1, 400'000>``.

Added by ``add-additional-validity-concepts``.
"""

from __future__ import annotations

from collections import defaultdict

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import (
    _cpp_artifact,
    _cpp_namespace_block,
    _enum_identifier,
)
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
    _runtime_lite_peripheral_names,
)

I2C_SPEED_VALIDATION_HEADER = "i2c_speed_validation.hpp"


def _speed_options(device: CanonicalDeviceIR) -> tuple[tuple[str, int, str], ...]:
    known_peripherals = _runtime_lite_peripheral_names(device)
    rows: list[tuple[str, int, str]] = []
    for option in device.i2c_speed_options:
        peripheral = getattr(option, "peripheral", None)
        speed_hz = getattr(option, "speed_hz", None)
        mode = getattr(option, "mode", None)
        if peripheral is None or speed_hz is None:
            continue
        if str(peripheral) not in known_peripherals:
            continue
        rows.append((str(peripheral), int(speed_hz), str(mode or "")))
    return tuple(sorted(set(rows), key=lambda row: (row[0], row[1])))


def runtime_i2c_speed_validation_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(
            family_dir, device.identity.device, I2C_SPEED_VALIDATION_HEADER
        )
        for device in devices
        if _speed_options(device)
    )


def emit_runtime_i2c_speed_validation_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact | None:
    options = _speed_options(device)
    if not options:
        return None

    by_peripheral: dict[str, list[tuple[int, str]]] = defaultdict(list)
    for peripheral, speed_hz, mode in options:
        by_peripheral[peripheral].append((speed_hz, mode))

    table_rows: list[str] = []
    branch_lines: list[str] = []
    for peripheral in sorted(by_peripheral):
        peripheral_ref = f"PeripheralId::{_enum_identifier(peripheral)}"
        speeds = sorted(by_peripheral[peripheral])
        speed_literals = ", ".join(f"{speed}u" for speed, _ in speeds)
        branch_lines.extend(
            [
                f"  if (peripheral == {peripheral_ref}) {{",
                f"    constexpr std::uint32_t kSpeeds[] = {{ {speed_literals} }};",
                "    for (auto candidate : kSpeeds) {",
                "      if (candidate == speed_hz) {",
                "        return true;",
                "      }",
                "    }",
                "    return false;",
                "  }",
            ]
        )
        for speed, _mode in speeds:
            # Mode is a string label and so it is dropped from the
            # emitted runtime contract per
            # ``eliminate-runtime-strings-from-cpp-contract``.
            table_rows.append(f"  {{{peripheral_ref}, {speed}u}},")

    predicate_lines = [
        "consteval bool is_valid_i2c_speed(PeripheralId peripheral, "
        "std::uint32_t speed_hz) noexcept {",
        *branch_lines,
        "  return false;",
        "}",
        "",
        "template<PeripheralId Peripheral, std::uint32_t SpeedHz>",
        "concept ValidI2cSpeed = is_valid_i2c_speed(Peripheral, SpeedHz);",
        "",
        "namespace detail {",
        "template<PeripheralId Peripheral, std::uint32_t SpeedHz>",
        "inline constexpr bool kInvalidI2cSpeed = false;",
        "}  // namespace detail",
        "",
    ]

    table_struct_lines = [
        "struct I2cSpeedEntry {",
        "  PeripheralId peripheral;",
        "  std::uint32_t speed_hz;",
        "};",
        "",
        f"inline constexpr std::array<I2cSpeedEntry, {len(table_rows)}> kI2cSpeeds = {{{{",
        *table_rows,
        "}};",
    ]

    body = "\n".join(
        [
            *predicate_lines,
            *table_struct_lines,
        ]
    )

    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            '#include "../../types.hpp"',
            '#include "peripheral_instances.hpp"',
            "",
            _cpp_namespace_block(_runtime_device_namespace_components(device), body),
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir, device.identity.device, I2C_SPEED_VALIDATION_HEADER
        ),
        content=content,
    )


__all__ = [
    "I2C_SPEED_VALIDATION_HEADER",
    "emit_runtime_i2c_speed_validation_header",
    "runtime_i2c_speed_validation_required_paths",
]
