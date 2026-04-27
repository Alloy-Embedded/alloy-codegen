"""Generated runtime pin-validation contract.

Projects ``device.connection_candidates`` into C++20 concepts so that
HAL drivers can constrain templates with ``ValidPinAssignment<Pin,
PeripheralSignal::FOO>`` and refuse invalid pinmux at compile time.

Added by ``emit-pinmux-validator-concepts``.
"""

from __future__ import annotations

import re

from alloy_codegen.errors import StageExecutionError
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
)

PIN_VALIDATION_HEADER = "pin_validation.hpp"

# Restrict route-kind labels to printable ASCII letters/digits plus the
# canonical ``-``/``_`` separators we already see in the IR
# (``alternate-function``, ``iomuxc-mux``, ``peripheral-mux``, ``mux``).
# Anything else is treated as a typo and fails the publication gate.
_ROUTE_KIND_PATTERN = re.compile(r"^[a-z0-9]+(?:[-_][a-z0-9]+)*$")


def _peripheral_signal_identifier(peripheral: str, signal: str) -> str:
    """Canonical ``<PERIPHERAL>_<SIGNAL>`` enumerator for a route.

    Upper-snake-case so consumers can write
    ``PeripheralSignal::SPI1_SCK`` (mirrors the per-peripheral typed
    enum convention used by the ADC channel enums).
    """
    return _enum_identifier(f"{peripheral}_{signal}").upper()


def _route_kind_identifier(route_kind: str) -> str:
    """Canonical lower-snake-case enumerator for a route-kind label."""
    if not isinstance(route_kind, str) or not _ROUTE_KIND_PATTERN.match(route_kind):
        raise StageExecutionError(
            f"invalid connection-candidate route_kind {route_kind!r}: "
            "expected lower-case ascii words separated by '-' or '_'"
        )
    return _enum_identifier(route_kind).lower()


def _route_selector_index(route_selector: str | None) -> int:
    """Extract the integer selector from ``selector:N`` (default 0)."""
    if route_selector is None:
        return 0
    if route_selector.startswith("selector:"):
        try:
            return int(route_selector.split(":", 1)[1])
        except ValueError:
            return 0
    # Some vendors use bare integer strings.
    try:
        return int(route_selector)
    except ValueError:
        return 0


def runtime_pin_validation_required_paths(
    *,
    family_dir: str,
    devices: tuple[CanonicalDeviceIR, ...],
) -> tuple[str, ...]:
    return tuple(
        _device_runtime_generated_path(
            family_dir, device.identity.device, PIN_VALIDATION_HEADER
        )
        for device in devices
        if device.connection_candidates
    )


def emit_runtime_pin_validation_header(
    *,
    family_dir: str,
    device: CanonicalDeviceIR,
) -> EmittedArtifact | None:
    candidates = tuple(
        sorted(
            device.connection_candidates,
            key=lambda item: (item.peripheral, item.signal, item.pin),
        )
    )
    if not candidates:
        return None

    # Closed PeripheralSignal enum: one entry per distinct (peripheral,
    # signal) pair, sorted by canonicalised enumerator name.
    peripheral_signal_pairs = sorted(
        {(candidate.peripheral, candidate.signal) for candidate in candidates},
        key=lambda pair: _peripheral_signal_identifier(*pair),
    )
    peripheral_signal_lines = [
        "enum class PeripheralSignal : std::uint16_t {",
        *(
            f"  {_peripheral_signal_identifier(peripheral, signal)} = "
            f"{index}u,"
            for index, (peripheral, signal) in enumerate(peripheral_signal_pairs)
        ),
        "};",
        "",
    ]

    # Closed RouteKind enum: one entry per distinct route_kind in the
    # device.  Validated against the canonical pattern up front so a
    # typo'd label aborts emission rather than shipping silently.
    route_kind_identifiers = sorted(
        {_route_kind_identifier(candidate.route_kind) for candidate in candidates}
    )
    route_kind_lines = [
        "enum class RouteKind : std::uint8_t {",
        *(
            f"  {identifier} = {index}u,"
            for index, identifier in enumerate(route_kind_identifiers)
        ),
        "};",
        "",
    ]

    primary_template_lines = [
        "template<PinId Pin, PeripheralSignal Signal>",
        "struct PinAssignmentValid : std::false_type {};",
        "",
    ]

    specialisation_lines: list[str] = []
    table_rows: list[str] = []
    for candidate in candidates:
        pin_ref = f"PinId::{_enum_identifier(candidate.pin)}"
        signal_ref = (
            "PeripheralSignal::"
            + _peripheral_signal_identifier(candidate.peripheral, candidate.signal)
        )
        route_kind_ref = (
            "RouteKind::" + _route_kind_identifier(candidate.route_kind)
        )
        selector_index = _route_selector_index(candidate.route_selector)
        specialisation_lines.extend(
            [
                "template<>",
                f"struct PinAssignmentValid<{pin_ref}, {signal_ref}> "
                ": std::true_type {",
                f"  static constexpr RouteKind kRouteKind = {route_kind_ref};",
                "  static constexpr std::uint8_t kRouteSelectorIndex = "
                f"{selector_index}u;",
                "};",
                "",
            ]
        )
        table_rows.append(
            f"  {{{pin_ref}, {signal_ref}, {route_kind_ref}, "
            f"{selector_index}u}},"
        )

    concept_lines = [
        "template<PinId Pin, PeripheralSignal Signal>",
        "concept ValidPinAssignment = "
        "PinAssignmentValid<Pin, Signal>::value;",
        "",
    ]

    table_struct_lines = [
        "struct PinAssignmentEntry {",
        "  PinId pin;",
        "  PeripheralSignal signal;",
        "  RouteKind route_kind;",
        "  std::uint8_t route_selector_index;",
        "};",
        "",
        f"inline constexpr std::array<PinAssignmentEntry, {len(table_rows)}> "
        "kPinAssignments = {{",
        *table_rows,
        "}};",
        "",
        "constexpr bool is_valid_pin_assignment("
        "PinId pin, PeripheralSignal signal) noexcept {",
        "  for (auto const& entry : kPinAssignments) {",
        "    if (entry.pin == pin && entry.signal == signal) {",
        "      return true;",
        "    }",
        "  }",
        "  return false;",
        "}",
    ]

    body = "\n".join(
        [
            *peripheral_signal_lines,
            *route_kind_lines,
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
            '#include "../../types.hpp"',
            '#include "peripheral_instances.hpp"',
            '#include "pins.hpp"',
            "",
            _cpp_namespace_block(_runtime_device_namespace_components(device), body),
            "",
        ]
    )
    return _cpp_artifact(
        path=_device_runtime_generated_path(
            family_dir, device.identity.device, PIN_VALIDATION_HEADER
        ),
        content=content,
    )


__all__ = [
    "PIN_VALIDATION_HEADER",
    "emit_runtime_pin_validation_header",
    "runtime_pin_validation_required_paths",
]
