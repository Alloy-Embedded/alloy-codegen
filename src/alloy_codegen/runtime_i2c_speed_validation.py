"""Generated runtime I2C-speed validation contract.

Projects ``device.i2c_peripherals`` into a C++20 concept so HAL
drivers can constrain templates with
``ValidI2cSpeed<Peripheral, I2cSpeedGrade>`` and refuse
unsupported bus speeds at compile time.

Speed grades follow the I2C-bus standard:

* ``Standard``  — 100 kHz (every controller supports it)
* ``Fast``      — 400 kHz (every controller supports it)
* ``FastModePlus`` — 1 MHz (only when
  ``I2cPeripheralDescriptor.supports_fast_mode_plus`` is True)

Added by ``add-additional-validity-concepts``.
"""

from __future__ import annotations

from alloy_codegen.ir.model import CanonicalDeviceIR
from alloy_codegen.reporting import EmittedArtifact

from .emission import _cpp_artifact, _cpp_namespace_block, _enum_identifier
from .runtime_lite_emission import (
    _device_runtime_generated_path,
    _runtime_device_namespace_components,
)

I2C_SPEED_VALIDATION_HEADER = "i2c_speed_validation.hpp"

# (grade enumerator, frequency in Hz, baseline-vs-fm+ gate)
_GRADES: tuple[tuple[str, int, bool], ...] = (
    ("Standard", 100_000, False),
    ("Fast", 400_000, False),
    ("FastModePlus", 1_000_000, True),
)


def runtime_i2c_speed_validation_required_paths(
    *, family_dir: str, devices: tuple[CanonicalDeviceIR, ...]
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(
            family_dir, device.identity.device, I2C_SPEED_VALIDATION_HEADER
        )
        for device in devices
        if device.i2c_peripherals
    )


def emit_runtime_i2c_speed_validation_header(
    *, family_dir: str, device: CanonicalDeviceIR
) -> EmittedArtifact | None:
    peripherals = tuple(
        sorted(device.i2c_peripherals, key=lambda p: p.peripheral_id)
    )
    if not peripherals:
        return None

    peripheral_lines = [
        "enum class I2cPeripheral : std::uint16_t {",
        *(
            f"  {_enum_identifier(p.peripheral_id)} = {i}u,"
            for i, p in enumerate(peripherals)
        ),
        "};",
        "",
    ]

    grade_lines = [
        "enum class I2cSpeedGrade : std::uint8_t {",
        *(f"  {grade} = {hz}u," for grade, hz, _ in _GRADES),
        "};",
        "",
    ]

    primary_template_lines = [
        "template<I2cPeripheral Peripheral, I2cSpeedGrade Speed>",
        "struct I2cSpeedValid : std::false_type {};",
        "",
    ]

    specialisation_lines: list[str] = []
    table_rows: list[str] = []
    for p in peripherals:
        peri_ref = "I2cPeripheral::" + _enum_identifier(p.peripheral_id)
        for grade, hz, fm_plus_only in _GRADES:
            if fm_plus_only and not p.supports_fast_mode_plus:
                continue
            grade_ref = f"I2cSpeedGrade::{grade}"
            specialisation_lines.extend(
                [
                    "template<>",
                    f"struct I2cSpeedValid<{peri_ref}, {grade_ref}> : std::true_type {{",
                    f"  static constexpr std::uint32_t kFrequencyHz = {hz}u;",
                    "};",
                    "",
                ]
            )
            table_rows.append(f"  {{{peri_ref}, {grade_ref}, {hz}u}},")

    concept_lines = [
        "template<I2cPeripheral Peripheral, I2cSpeedGrade Speed>",
        "concept ValidI2cSpeed = I2cSpeedValid<Peripheral, Speed>::value;",
        "",
    ]

    table_struct_lines = [
        "struct I2cSpeedEntry {",
        "  I2cPeripheral peripheral;",
        "  I2cSpeedGrade speed;",
        "  std::uint32_t frequency_hz;",
        "};",
        "",
        f"inline constexpr std::array<I2cSpeedEntry, {len(table_rows)}> "
        "kI2cSpeeds = {{",
        *table_rows,
        "}};",
        "",
        "constexpr bool is_valid_i2c_speed(I2cPeripheral peripheral, "
        "I2cSpeedGrade speed) noexcept {",
        "  for (auto const& entry : kI2cSpeeds) {",
        "    if (entry.peripheral == peripheral && entry.speed == speed) {",
        "      return true;",
        "    }",
        "  }",
        "  return false;",
        "}",
    ]

    body = "\n".join(
        [
            *peripheral_lines,
            *grade_lines,
            *primary_template_lines,
            *specialisation_lines,
            *concept_lines,
            *table_struct_lines,
        ]
    )

    content = "\n".join(
        [
            "#pragma once",
            "",
            "#include <array>",
            "#include <cstdint>",
            "#include <type_traits>",
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
