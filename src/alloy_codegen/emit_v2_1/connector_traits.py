"""Emit ``connectors.hpp`` — compile-time connector validation for alloy HAL.

Generates the full ``ConnectorTraits`` template specialisation tree that the
HAL's ``connect/runtime_connector.hpp`` imports as ``device/connectors.hpp``.

The artifact replaces the hand-written / pre-generated file that used to live
in the now-deleted ``alloy-devices`` repository.  alloy-codegen produces it
on-demand from the synthesised ``pin_routes`` table.

What is emitted
---------------
* Typed enums: ``PinId``, ``PeripheralId``, ``SignalId``, ``RouteKindId``,
  ``ConnectionGroupId``, ``RouteId``, ``ConnectorId``.
* ``ConnectorDescriptor`` struct.
* Base ``ConnectorTraits<PinId, PeripheralId, SignalId>`` template (always
  ``kPresent = false``; no static_assert — this fires for completely unknown
  combinations).
* Full specialisations for every valid ``(pin, peripheral, signal)`` triple
  from ``pin_routes`` — ``kPresent = true``, real IDs.
* Guard A partial specialisations  ``ConnectorTraits<Pin, PeripheralId::X,
  SignalId::Y>`` — fires ``static_assert`` for a *wrong* pin on a known
  peripheral+signal combo.
* Guard B partial specialisations  ``ConnectorTraits<PinId::X, Peripheral,
  SignalId::Y>`` — fires ``static_assert`` for a *wrong* peripheral on a
  known pin+signal combo.
* ``ConnectorSignalTraits<PeripheralId, SignalId>`` — base + full specs
  (arrays of valid pins and connector-ids per peripheral+signal).
* ``inline constexpr std::array<ConnectorDescriptor, N> kConnectors``.

Guard ordering
--------------
Full specialisations are emitted **before** Guard A / B partial specs so the
compiler prefers the full (more specific) specialisation for valid combos and
falls through to the partial spec's ``static_assert`` only for invalid ones.
"""

from __future__ import annotations

from collections import defaultdict

from alloy_codegen.ir.synthesised import PinRoute, SynthesisedDevice
from alloy_codegen.ir.v2_1 import CanonicalDevice

# ---------------------------------------------------------------------------
# Identifier helpers
# ---------------------------------------------------------------------------

_ROUTE_KIND_MAP: dict[str, str] = {
    "alloy.pinmux.stm32-af-v1":          "route_kind_alternate_function",
    "alloy.pinmux.sam-matrix-function-v1": "route_kind_matrix_function",
    "alloy.pinmux.rp2040-funcsel-v1":    "route_kind_funcsel",
    "alloy.pinmux.esp32-io-matrix-v1":   "route_kind_io_matrix",
    "alloy.pinmux.nordic-psel-v1":       "route_kind_psel",
}


def _safe_c_id(value: str) -> str:
    """Sanitise an arbitrary string into a valid C identifier."""
    out: list[str] = []
    for ch in value:
        if ch.isalnum() or ch == "_":
            out.append(ch)
        else:
            out.append("_")
    if not out or not out[0].isalpha():
        out.insert(0, "_")
    return "".join(out)


def _namespace_path(device: CanonicalDevice) -> str:
    v = device.identity.vendor.replace("-", "_").lower()
    f = device.identity.family.replace("-", "_").lower()
    d = device.identity.device.replace("-", "_").lower()
    return f"alloy::{v}::{f}::{d}"


def _header_guard(device: CanonicalDevice) -> str:
    parts = (
        device.identity.vendor,
        device.identity.family,
        device.identity.device,
        "connectors_hpp",
    )
    return "_".join(p.upper().replace("-", "_") for p in parts) + "_"


# ---------------------------------------------------------------------------
# Route → C++ name helpers
# ---------------------------------------------------------------------------


def _pin_enum_val(pin_id: str) -> str:
    """``"pa1"`` → ``"PA1"`` (PinId enumerator)."""
    return pin_id.upper()


def _peripheral_enum_val(peripheral_id: str) -> str:
    """``"USART1"`` → ``"USART1"`` (PeripheralId enumerator, already upper)."""
    return peripheral_id.upper()


def _signal_enum_val(signal_id: str) -> str:
    """``"tx"`` → ``"signal_tx"`` (SignalId enumerator)."""
    return f"signal_{signal_id}"


def _route_kind_for(backend_schema_id: str) -> str:
    """Map a backend schema id to the ``RouteKindId`` enumerator string."""
    if backend_schema_id in _ROUTE_KIND_MAP:
        return _ROUTE_KIND_MAP[backend_schema_id]
    # Generic / unknown backends emit a safe sentinel rather than crashing.
    safe = _safe_c_id(backend_schema_id.lower())
    return f"route_kind_{safe}"


def _connector_id_val(pin_id: str, peripheral_id: str, signal_id: str) -> str:
    """``candidate_<pin>_<peri_lower>_<sig>``."""
    return f"candidate_{pin_id}_{peripheral_id.lower()}_{signal_id}"


# ---------------------------------------------------------------------------
# Gather unique values from routes
# ---------------------------------------------------------------------------


def _unique_sorted(values: list[str]) -> list[str]:
    return sorted(set(values))


def _gather_enum_values(
    routes: tuple[PinRoute, ...],
) -> tuple[list[str], list[str], list[str], list[str]]:
    """Return (pin_ids, peripheral_ids, signal_ids, route_kind_ids) — unique, sorted."""
    pins: list[str] = []
    peripherals: list[str] = []
    signals: list[str] = []
    route_kinds: list[str] = []
    for r in routes:
        pins.append(_pin_enum_val(r.pin_id))
        peripherals.append(_peripheral_enum_val(r.peripheral_id))
        signals.append(_signal_enum_val(r.signal_id))
        rk = _route_kind_for(r.backend_schema_id)
        route_kinds.append(rk)
    return (
        _unique_sorted(pins),
        _unique_sorted(peripherals),
        _unique_sorted(signals),
        _unique_sorted(route_kinds),
    )


# ---------------------------------------------------------------------------
# Enum block emitters
# ---------------------------------------------------------------------------


def _emit_enum(
    name: str,
    underlying: str,
    values: list[str],
    *,
    none_first: bool = True,
    extra_sentinels: list[str] | None = None,
) -> list[str]:
    """Emit ``enum class <name> : <underlying> { none, <values>... };``."""
    lines: list[str] = [f"enum class {name} : {underlying} {{"]
    if none_first:
        lines.append("  none,")
    for v in values:
        lines.append(f"  {v},")
    if extra_sentinels:
        for s in extra_sentinels:
            lines.append(f"  {s},")
    lines.append("};")
    return lines


# ---------------------------------------------------------------------------
# ConnectorDescriptor struct
# ---------------------------------------------------------------------------


def _emit_connector_descriptor() -> list[str]:
    return [
        "struct ConnectorDescriptor {",
        "  ConnectorId      connector_id;",
        "  PinId            pin_id;",
        "  PeripheralId     peripheral_id;",
        "  SignalId         signal_id;",
        "  RouteId          route_id;",
        "  RouteKindId      route_kind_id;",
        "  ConnectionGroupId group_id;",
        "};",
    ]


# ---------------------------------------------------------------------------
# Base ConnectorTraits template
# ---------------------------------------------------------------------------


def _emit_base_connector_traits() -> list[str]:
    return [
        "/// Primary template — always false.  Use a full specialisation for a",
        "/// valid (PinId, PeripheralId, SignalId) triple.",
        "template<PinId kPin, PeripheralId kPeripheral, SignalId kSignal>",
        "struct ConnectorTraits {",
        "  static constexpr bool            kPresent     = false;",
        "  static constexpr ConnectorId     kConnectorId = ConnectorId::none;",
        "  static constexpr PinId           kPinId       = PinId::none;",
        "  static constexpr PeripheralId    kPeripheralId = PeripheralId::none;",
        "  static constexpr SignalId        kSignalId    = SignalId::none;",
        "  static constexpr RouteId         kRouteId     = RouteId::none;",
        "  static constexpr RouteKindId     kRouteKindId = RouteKindId::none;",
        "  static constexpr ConnectionGroupId kGroupId   = ConnectionGroupId::none;",
        "};",
    ]


# ---------------------------------------------------------------------------
# Full ConnectorTraits specialisations (valid combos)
# ---------------------------------------------------------------------------


def _emit_full_connector_traits_spec(route: PinRoute) -> list[str]:
    pin_val = _pin_enum_val(route.pin_id)
    peri_val = _peripheral_enum_val(route.peripheral_id)
    sig_val = _signal_enum_val(route.signal_id)
    conn_val = _connector_id_val(route.pin_id, route.peripheral_id, route.signal_id)
    rk_val = _route_kind_for(route.backend_schema_id)
    return [
        f"template<>",
        f"struct ConnectorTraits<PinId::{pin_val}, PeripheralId::{peri_val}, SignalId::{sig_val}> {{",
        f"  static constexpr bool            kPresent      = true;",
        f"  static constexpr ConnectorId     kConnectorId  = ConnectorId::{conn_val};",
        f"  static constexpr PinId           kPinId        = PinId::{pin_val};",
        f"  static constexpr PeripheralId    kPeripheralId = PeripheralId::{peri_val};",
        f"  static constexpr SignalId        kSignalId     = SignalId::{sig_val};",
        f"  static constexpr RouteId         kRouteId      = RouteId::{conn_val};",
        f"  static constexpr RouteKindId     kRouteKindId  = RouteKindId::{rk_val};",
        f"  static constexpr ConnectionGroupId kGroupId    = ConnectionGroupId::none;",
        f"}};",
    ]


# ---------------------------------------------------------------------------
# detail::kInvalidConnector helper
# ---------------------------------------------------------------------------


def _emit_detail_namespace() -> list[str]:
    return [
        "namespace detail {",
        "",
        "/// Always-false helper for ``static_assert`` in Guard A / B partial",
        "/// specialisations.  The template parameter makes the assertion",
        "/// dependent so it is only evaluated when the specialisation is",
        "/// instantiated.",
        "template<auto V>",
        "inline constexpr bool kInvalidConnector = false;",
        "",
        "}  // namespace detail",
    ]


# ---------------------------------------------------------------------------
# Guard A — wrong pin for a known (peripheral, signal) pair
# ---------------------------------------------------------------------------


def _emit_guard_a_specs(routes: tuple[PinRoute, ...]) -> list[str]:
    """Emit one partial spec per unique (peripheral_id, signal_id) pair.

    The static_assert message lists the *valid* pins so the developer knows
    which pin to choose.
    """
    # Group valid pins per (peripheral, signal).
    valid_pins: dict[tuple[str, str], list[str]] = defaultdict(list)
    for r in routes:
        key = (_peripheral_enum_val(r.peripheral_id), _signal_enum_val(r.signal_id))
        pin_val = _pin_enum_val(r.pin_id)
        if pin_val not in valid_pins[key]:
            valid_pins[key].append(pin_val)

    lines: list[str] = []
    for (peri_val, sig_val), pins in sorted(valid_pins.items()):
        pins_list = ", ".join(pins)
        # Human-readable peripheral+signal for the diagnostic.
        lines.append(f"/// Guard A — fires for any pin that is NOT valid for")
        lines.append(f"/// {peri_val} / {sig_val}.  Valid pins: {pins_list}.")
        lines.append(f"template<PinId kPin>")
        lines.append(f"struct ConnectorTraits<kPin, PeripheralId::{peri_val}, SignalId::{sig_val}> {{")
        lines.append(f"  static_assert(")
        lines.append(f"    detail::kInvalidConnector<kPin>,")
        lines.append(f"    \"Invalid pin for {peri_val} {sig_val}. Valid pins: {pins_list}.\");")
        lines.append(f"}};")
        lines.append("")
    return lines


# ---------------------------------------------------------------------------
# Guard B — wrong peripheral for a known (pin, signal) pair
# ---------------------------------------------------------------------------


def _emit_guard_b_specs(routes: tuple[PinRoute, ...]) -> list[str]:
    """Emit one partial spec per unique (pin_id, signal_id) pair."""
    # Group valid peripherals per (pin, signal).
    valid_peris: dict[tuple[str, str], list[str]] = defaultdict(list)
    for r in routes:
        key = (_pin_enum_val(r.pin_id), _signal_enum_val(r.signal_id))
        peri_val = _peripheral_enum_val(r.peripheral_id)
        if peri_val not in valid_peris[key]:
            valid_peris[key].append(peri_val)

    lines: list[str] = []
    for (pin_val, sig_val), peris in sorted(valid_peris.items()):
        peris_list = ", ".join(peris)
        lines.append(f"/// Guard B — fires for any peripheral that is NOT valid for")
        lines.append(f"/// {pin_val} / {sig_val}.  Valid peripherals: {peris_list}.")
        lines.append(f"template<PeripheralId kPeripheral>")
        lines.append(f"struct ConnectorTraits<PinId::{pin_val}, kPeripheral, SignalId::{sig_val}> {{")
        lines.append(f"  static_assert(")
        lines.append(f"    detail::kInvalidConnector<kPeripheral>,")
        lines.append(f"    \"{pin_val} cannot serve {sig_val} on the requested peripheral. Valid peripherals: {peris_list}.\");")
        lines.append(f"}};")
        lines.append("")
    return lines


# ---------------------------------------------------------------------------
# ConnectorSignalTraits
# ---------------------------------------------------------------------------


def _emit_base_connector_signal_traits() -> list[str]:
    return [
        "/// Primary template — always false / empty arrays.",
        "template<PeripheralId kPeripheral, SignalId kSignal>",
        "struct ConnectorSignalTraits {",
        "  static constexpr bool kPresent = false;",
        "  static constexpr std::array<PinId,       0> kPins{};",
        "  static constexpr std::array<ConnectorId, 0> kConnectors{};",
        "};",
    ]


def _emit_full_connector_signal_traits_specs(routes: tuple[PinRoute, ...]) -> list[str]:
    """One full specialisation per unique (peripheral_id, signal_id) pair."""
    # Group routes per (peripheral_id, signal_id).
    groups: dict[tuple[str, str], list[PinRoute]] = defaultdict(list)
    for r in routes:
        key = (_peripheral_enum_val(r.peripheral_id), _signal_enum_val(r.signal_id))
        groups[key].append(r)

    lines: list[str] = []
    for (peri_val, sig_val), group_routes in sorted(groups.items()):
        # Unique, sorted pins and connector IDs.
        seen_pins: dict[str, None] = {}
        seen_conns: dict[str, None] = {}
        for r in group_routes:
            seen_pins[_pin_enum_val(r.pin_id)] = None
            seen_conns[_connector_id_val(r.pin_id, r.peripheral_id, r.signal_id)] = None
        pins = list(seen_pins)
        conns = list(seen_conns)
        n = len(pins)
        pin_list = ", ".join(f"PinId::{p}" for p in pins)
        conn_list = ", ".join(f"ConnectorId::{c}" for c in conns)
        lines.append(f"template<>")
        lines.append(f"struct ConnectorSignalTraits<PeripheralId::{peri_val}, SignalId::{sig_val}> {{")
        lines.append(f"  static constexpr bool kPresent = true;")
        lines.append(f"  static constexpr std::array<PinId,       {n}> kPins{{{{")
        lines.append(f"    {pin_list}")
        lines.append(f"  }}}};")
        lines.append(f"  static constexpr std::array<ConnectorId, {n}> kConnectors{{{{")
        lines.append(f"    {conn_list}")
        lines.append(f"  }}}};")
        lines.append(f"}};")
        lines.append("")
    return lines


# ---------------------------------------------------------------------------
# kConnectors table
# ---------------------------------------------------------------------------


def _emit_k_connectors(routes: tuple[PinRoute, ...]) -> list[str]:
    # Deduplicate by (pin_id, peripheral_id, signal_id) — alternate_pin
    # variants can produce duplicate triples; keep one per triple.
    seen: set[tuple[str, str, str]] = set()
    unique: list[PinRoute] = []
    for r in routes:
        key = (r.pin_id, r.peripheral_id, r.signal_id)
        if key not in seen:
            seen.add(key)
            unique.append(r)
    n = len(unique)
    if n == 0:
        return ["inline constexpr std::array<ConnectorDescriptor, 0> kConnectors{};"]
    lines: list[str] = [
        f"inline constexpr std::array<ConnectorDescriptor, {n}> kConnectors = {{{{",
    ]
    for r in unique:
        pin_val = _pin_enum_val(r.pin_id)
        peri_val = _peripheral_enum_val(r.peripheral_id)
        sig_val = _signal_enum_val(r.signal_id)
        conn_val = _connector_id_val(r.pin_id, r.peripheral_id, r.signal_id)
        rk_val = _route_kind_for(r.backend_schema_id)
        lines.append(
            f"  {{ ConnectorId::{conn_val}, PinId::{pin_val}, PeripheralId::{peri_val},"
            f" SignalId::{sig_val}, RouteId::{conn_val},"
            f" RouteKindId::{rk_val}, ConnectionGroupId::none }},"
        )
    lines.append("}};")
    return lines


# ---------------------------------------------------------------------------
# Public emitter
# ---------------------------------------------------------------------------


def emit_connector_traits(device: CanonicalDevice, synthesised: SynthesisedDevice) -> str:
    """Render ``connectors.hpp`` for ``device``."""
    routes = synthesised.pin_routes

    pin_ids, peripheral_ids, signal_ids, route_kind_ids = _gather_enum_values(routes)

    # Collect all ConnectorId / RouteId values (one per route).
    connector_ids: list[str] = []
    for r in routes:
        connector_ids.append(_connector_id_val(r.pin_id, r.peripheral_id, r.signal_id))
    connector_ids = _unique_sorted(connector_ids)

    guard = _header_guard(device)
    ns = _namespace_path(device)
    schema_id = (
        routes[0].backend_schema_id if routes else "alloy.pinmux.unknown-v0"
    )

    lines: list[str] = [
        "/* connectors.hpp",
        " *",
        f" * {device.identity.vendor}/{device.identity.family}/{device.identity.device}"
        f" — generated from {device.schema}",
        " *",
        f" * Pinmux backend : {schema_id}",
        f" * Routes         : {len(routes)}",
        " *",
        " * Compile-time connector validation for the alloy HAL.",
        " * Imported by connect/runtime_connector.hpp as device/connectors.hpp.",
        " *",
        " * Do NOT edit — regenerate with alloy-codegen.",
        " */",
        "#pragma once",
        f"#ifndef {guard}",
        f"#define {guard}",
        "",
        "#include <array>",
        "#include <cstdint>",
        "",
        f"namespace {ns} {{",
        "",
    ]

    # --- Enums ---------------------------------------------------------------
    lines.extend(_emit_enum("PinId", "std::uint16_t", pin_ids))
    lines.append("")
    lines.extend(_emit_enum("PeripheralId", "std::uint16_t", peripheral_ids))
    lines.append("")
    lines.extend(_emit_enum("SignalId", "std::uint16_t", signal_ids))
    lines.append("")
    lines.extend(_emit_enum("RouteKindId", "std::uint8_t", route_kind_ids))
    lines.append("")
    lines.extend(_emit_enum("ConnectionGroupId", "std::uint16_t", []))
    lines.append("")
    lines.extend(_emit_enum("RouteId", "std::uint16_t", connector_ids))
    lines.append("")
    lines.extend(_emit_enum("ConnectorId", "std::uint16_t", connector_ids))
    lines.append("")

    # --- ConnectorDescriptor struct ------------------------------------------
    lines.extend(_emit_connector_descriptor())
    lines.append("")

    # --- detail namespace (kInvalidConnector) --------------------------------
    lines.extend(_emit_detail_namespace())
    lines.append("")

    # --- Base ConnectorTraits template ---------------------------------------
    lines.extend(_emit_base_connector_traits())
    lines.append("")

    # --- Full specialisations (valid combos — most specific) -----------------
    # Deduplicate by (pin_id, peripheral_id, signal_id): two PinRoute rows can
    # share the same triple when alternate_pin variants coexist with canonical
    # entries (e.g. PA9 as canonical + PA9 as alternate of PA11 for the same
    # peripheral/signal).  C++ does not allow two full specialisations with
    # identical template arguments.
    if routes:
        lines.append("// --- Full specialisations (valid pin/peripheral/signal combos) ---")
        lines.append("")
        seen_triples: set[tuple[str, str, str]] = set()
        for route in routes:
            triple = (route.pin_id, route.peripheral_id, route.signal_id)
            if triple in seen_triples:
                continue
            seen_triples.add(triple)
            lines.extend(_emit_full_connector_traits_spec(route))
            lines.append("")

    # --- Guard A partial specs -----------------------------------------------
    if routes:
        lines.append("// --- Guard A: wrong pin for a known (peripheral, signal) pair ---")
        lines.append("")
        lines.extend(_emit_guard_a_specs(routes))

    # --- Guard B partial specs -----------------------------------------------
    if routes:
        lines.append("// --- Guard B: wrong peripheral for a known (pin, signal) pair ---")
        lines.append("")
        lines.extend(_emit_guard_b_specs(routes))

    # --- ConnectorSignalTraits -----------------------------------------------
    lines.append("// --- ConnectorSignalTraits ---")
    lines.append("")
    lines.extend(_emit_base_connector_signal_traits())
    lines.append("")
    lines.extend(_emit_full_connector_signal_traits_specs(routes))

    # --- kConnectors table ---------------------------------------------------
    lines.append("// --- kConnectors descriptor table ---")
    lines.append("")
    lines.extend(_emit_k_connectors(routes))
    lines.append("")

    # --- Close namespace and include guard -----------------------------------
    lines.append(f"}}  // namespace {ns}")
    lines.append("")
    lines.append(f"#endif  // {guard}")
    lines.append("")

    return "\n".join(lines)


__all__ = ["emit_connector_traits"]
