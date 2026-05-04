"""Emit ``routes.hpp`` — route enumeration and descriptor table for alloy HAL.

Generates the runtime routing artifact that maps ``RouteId`` enumerators to
their hardware-level configuration values (alternate-function numbers, FUNCSEL
slots, PIO matrix function codes, etc.).

The artifact is consumed by the alloy HAL's routing runtime — the connector
system selects a ``RouteId`` at compile time (via ``ConnectorTraits``), then
looks it up in ``kRoutes`` at runtime to apply the correct register values.

What is emitted
---------------
* ``RouteId`` enum — one enumerator per valid ``(pin, peripheral, signal)``
  triple, named ``candidate_<pin>_<peripheral_lower>_<signal>``.
* ``RouteKindId`` enum — one enumerator per distinct pinmux backend family
  (e.g. ``route_kind_alternate_function`` for STM32 AF).
* ``RouteDescriptor`` struct — ``{ route_id, route_kind_id, code }``.
  ``code`` is backend-specific (AF number for STM32, FUNCSEL index for RP2040,
  etc.).  ``0xFFFF`` is the sentinel for "code not yet in IR".
* ``inline constexpr std::array<RouteDescriptor, N> kRoutes`` — sorted by
  ``RouteId`` enumerator value (i.e. the order in the enum, which is
  alphabetical by connector name).

Relationship to ``connectors.hpp``
-----------------------------------
``connectors.hpp`` carries the compile-time template machinery (``ConnectorTraits``,
Guards A/B, ``ConnectorSignalTraits``).  ``routes.hpp`` carries the runtime
lookup table.  Both share the same enum-value names for ``RouteId`` and
``RouteKindId``; the HAL is expected to include both headers together.
"""

from __future__ import annotations

from alloy_codegen.ir.synthesised import PinRoute, SynthesisedDevice
from alloy_codegen.ir.v2_1 import CanonicalDevice

# ---------------------------------------------------------------------------
# Shared naming helpers — must stay in sync with connector_traits.py
# ---------------------------------------------------------------------------

_ROUTE_KIND_MAP: dict[str, str] = {
    "alloy.pinmux.stm32-af-v1":            "route_kind_alternate_function",
    "alloy.pinmux.sam-matrix-function-v1": "route_kind_matrix_function",
    "alloy.pinmux.rp2040-funcsel-v1":      "route_kind_funcsel",
    "alloy.pinmux.esp32-io-matrix-v1":     "route_kind_io_matrix",
    "alloy.pinmux.nordic-psel-v1":         "route_kind_psel",
}

_CODE_SENTINEL = "0xFFFFu"  # code not yet in IR


def _safe_c_id(value: str) -> str:
    out: list[str] = []
    for ch in value:
        if ch.isalnum() or ch == "_":
            out.append(ch)
        else:
            out.append("_")
    if not out or not out[0].isalpha():
        out.insert(0, "_")
    return "".join(out)


def _route_kind_for(backend_schema_id: str) -> str:
    if backend_schema_id in _ROUTE_KIND_MAP:
        return _ROUTE_KIND_MAP[backend_schema_id]
    safe = _safe_c_id(backend_schema_id.lower())
    return f"route_kind_{safe}"


def _route_id_val(route: PinRoute) -> str:
    """``candidate_<pin>_<peri_lower>_<signal>``."""
    return f"candidate_{route.pin_id}_{route.peripheral_id.lower()}_{route.signal_id}"


def _header_guard(device: CanonicalDevice) -> str:
    parts = (
        device.identity.vendor,
        device.identity.family,
        device.identity.device,
        "routes_hpp",
    )
    return "_".join(p.upper().replace("-", "_") for p in parts) + "_"


def _namespace_path(device: CanonicalDevice) -> str:
    v = device.identity.vendor.replace("-", "_").lower()
    f = device.identity.family.replace("-", "_").lower()
    d = device.identity.device.replace("-", "_").lower()
    return f"alloy::{v}::{f}::{d}"


# ---------------------------------------------------------------------------
# Section emitters
# ---------------------------------------------------------------------------


def _emit_route_descriptor() -> list[str]:
    return [
        "/// Holds the hardware-level configuration for one route.",
        "/// ``code`` is backend-specific:",
        "///   STM32 AF  → alternate-function number (0–15)",
        "///   RP2040    → FUNCSEL slot index",
        "///   SAM E70   → PIO matrix function letter as integer",
        "/// ``0xFFFFu`` means the IR does not yet carry the routing code.",
        "struct RouteDescriptor {",
        "  RouteId     route_id;",
        "  RouteKindId route_kind_id;",
        "  std::uint16_t code;",
        "};",
    ]


def _emit_k_routes(routes: tuple[PinRoute, ...]) -> list[str]:
    # Deduplicate by (pin_id, peripheral_id, signal_id) — same logic as the
    # full-spec deduplication in connector_traits.py.
    seen: set[tuple[str, str, str]] = set()
    unique: list[PinRoute] = []
    for r in routes:
        key = (r.pin_id, r.peripheral_id, r.signal_id)
        if key not in seen:
            seen.add(key)
            unique.append(r)
    n = len(unique)
    if n == 0:
        return ["inline constexpr std::array<RouteDescriptor, 0> kRoutes{};"]
    lines: list[str] = [
        f"inline constexpr std::array<RouteDescriptor, {n}> kRoutes = {{{{",
    ]
    for r in unique:
        rid = _route_id_val(r)
        rk = _route_kind_for(r.backend_schema_id)
        code = str(r.code) + "u" if r.code is not None else _CODE_SENTINEL
        lines.append(f"  {{ RouteId::{rid}, RouteKindId::{rk}, {code} }},")
    lines.append("}};")
    return lines


# ---------------------------------------------------------------------------
# Public emitter
# ---------------------------------------------------------------------------


def emit_routes(device: CanonicalDevice, synthesised: SynthesisedDevice) -> str:
    """Render ``routes.hpp`` for ``device``."""
    routes = synthesised.pin_routes
    guard = _header_guard(device)
    ns = _namespace_path(device)
    schema_id = routes[0].backend_schema_id if routes else "alloy.pinmux.unknown-v0"

    lines: list[str] = [
        "/* routes.hpp",
        " *",
        f" * {device.identity.vendor}/{device.identity.family}/{device.identity.device}"
        f" — generated from {device.schema}",
        " *",
        f" * Pinmux backend : {schema_id}",
        f" * Routes         : {len(routes)}",
        " *",
        " * Hardware-level route descriptor table for alloy HAL.",
        " * RouteId / RouteKindId are defined in connectors.hpp;",
        " * include routes.hpp after connectors.hpp (or standalone —",
        " * this header includes connectors.hpp itself).",
        " *",
        " * Do NOT edit — regenerate with alloy-codegen.",
        " */",
        "#pragma once",
        f"#ifndef {guard}",
        f"#define {guard}",
        "",
        "// connectors.hpp defines RouteId, RouteKindId, ConnectionGroupId.",
        '#include "connectors.hpp"',
        "",
        f"namespace {ns} {{",
        "",
    ]

    # No enum re-definitions — RouteId and RouteKindId come from connectors.hpp.

    # RouteDescriptor struct.
    lines.extend(_emit_route_descriptor())
    lines.append("")

    # kRoutes table.
    lines.append("// --- kRoutes descriptor table ---")
    lines.append("")
    lines.extend(_emit_k_routes(routes))
    lines.append("")

    # Close.
    lines.append(f"}}  // namespace {ns}")
    lines.append("")
    lines.append(f"#endif  // {guard}")
    lines.append("")

    return "\n".join(lines)


__all__ = ["emit_routes"]
