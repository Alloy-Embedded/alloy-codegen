"""Emit ``pins.h`` — typed pin identity + signal→pad route table.

Foundational pass on the ``add-pin-router-emitter`` proposal.  The
artifact is a runtime-lite header that publishes:

* ``enum class id`` — one entry per non-power pad in
  ``device.pinout`` (lower-cased; e.g. ``PA2`` → ``pa2``).
* ``constexpr std::array<route, N> kRoutes`` — one row per
  ``(peripheral_id, signal_id, pin_id)`` triple admitted by the
  IR's ``peripherals[*].pin_options``.  Already sorted by the
  synthesiser.
* Convenience accessor: ``constexpr unsigned kPinCount`` and
  ``constexpr unsigned kRouteCount``.

Known follow-ups (deferred to next implementation passes):

* ``peripheral`` / ``signal`` flow as ``const char *`` literals
  for now — the IR doesn't yet carry typed PeripheralId / SignalId
  enums shared between this header and ``peripheral_traits.h``.
  When that lands, those columns become typed enum values and the
  artifact becomes fully zero-string per the artifact-contract
  rule.
* ``code`` is ``-1`` placeholder until alloy-devices-yml carries
  the AF number on each ``PinOptionFixed`` row (the ST backend
  passes ``option.func`` through, but ST YAMLs don't populate it
  today; same for SAM matrix function letters).
* ``constraints_of(...)`` and the alternate-pin runtime fallback
  table are deferred until the proposal's Tasks 3.6 / 3.7 land.
"""

from __future__ import annotations

from alloy_codegen.ir.synthesised import PinRoute, SynthesisedDevice
from alloy_codegen.ir.v2_1 import CanonicalDevice

LAYOUT_VERSION = "alloy-pins layout v1"
"""Top-of-file banner string.  Bumped on every breaking shape
change so consumers can refuse incompatible headers via
``#error``."""


def _safe_c_id(value: str) -> str:
    """Sanitise an arbitrary string into a valid C identifier.

    Mirrors ``runtime_init._safe_c_id`` so the two emitters keep
    consistent identifier-mangling rules.
    """
    out: list[str] = []
    for ch in value:
        if ch.isalnum() or ch == "_":
            out.append(ch)
        else:
            out.append("_")
    if not out or not out[0].isalpha():
        out.insert(0, "_")
    return "".join(out)


def _canonical_pin_id(raw: str) -> str | None:
    """Apply the same prefix extraction the STM32 backend does to
    ``device.pinout[i].signal`` so the ``pin::id`` enum entries
    match the values referenced by ``kRoutes``.

    Returns ``None`` for pads that should be excluded from
    ``pin::id`` (power, ground, marker-only).
    """
    raw = raw.strip()
    # Drop alternate-pin annotation: ``PA12 [PA10]`` → ``PA12``.
    if "[" in raw:
        raw = raw.split("[", 1)[0].strip()
    # Drop trailing function annotation: ``PA14-BOOT0`` → ``PA14``.
    if "-" in raw:
        raw = raw.split("-", 1)[0].strip()
    # Drop a parenthesised disambiguation: ``PC15 (PC15)``.
    if " (" in raw:
        raw = raw.split(" (", 1)[0].strip()
    raw = raw.lower()
    # Filter pads that aren't routable in any meaningful sense:
    # power rails, vbat, vref, ground.  (Returning None here
    # excludes them from ``pin::id`` — they only show up via
    # ``constraints_of()`` in the follow-up pass.)
    if raw in {"vdd", "vss", "vssa", "vdda", "vbat", "vref+", "vref-",
               "ucpd1_dbcc1", "ucpd1_dbcc2", "ucpd2_dbcc1", "ucpd2_dbcc2"}:
        return None
    if not raw:
        return None
    return _safe_c_id(raw)


def _gather_pin_ids(device: CanonicalDevice, routes: tuple[PinRoute, ...]) -> tuple[str, ...]:
    """Build the deterministic ``pin::id`` enumeration.

    Sources:
    * ``device.pinout[i].signal`` — every routable pad on the
      package.
    * Every ``PinRoute.pin_id`` referenced by ``routes`` — guards
      against a pinout entry the backend resolved to a different
      canonical id.
    * Every ``PinRoute.alternate_pin`` (lower-cased) — alternate-
      pin annotations create extra ``pin::id`` entries the
      runtime fallback table can dispatch through.
    """
    seen: dict[str, None] = {}
    for pin in device.pinout:
        canonical = _canonical_pin_id(pin.signal)
        if canonical is not None:
            seen[canonical] = None
    for route in routes:
        seen[route.pin_id] = None
        if route.alternate_pin is not None:
            alt = _canonical_pin_id(route.alternate_pin)
            if alt is not None:
                seen[alt] = None
    return tuple(sorted(seen))


def _emit_pin_id_enum(pin_ids: tuple[str, ...]) -> list[str]:
    """``enum class id : uint16_t { ... }`` block."""
    if not pin_ids:
        return [
            "  enum class id : uint16_t { /* no routable pads */ };",
            "  inline constexpr unsigned kCount = 0;",
        ]
    out: list[str] = ["  enum class id : uint16_t {"]
    for pid in pin_ids:
        out.append(f"    {pid},")
    out.append("  };")
    out.append(f"  inline constexpr unsigned kCount = {len(pin_ids)}u;")
    return out


def _emit_route_struct() -> list[str]:
    """The ``route`` struct shared by every per-device file.

    Note: ``peripheral`` and ``signal`` are ``const char *``
    placeholders.  Once the IR ships typed ``PeripheralId`` and
    ``SignalId`` enums (alloy-devices-yml v2.2+), this block
    swaps them for typed enum members.
    """
    return [
        "  struct route {",
        "    const char *peripheral;          // typed-id placeholder; see header banner",
        "    const char *signal;              // typed-id placeholder; see header banner",
        "    pin::id     pin;",
        "    int16_t     code;                // backend-encoded; -1 = unknown",
        "    const char *alternate_pin;       // nullptr unless package carries alt-pin",
        "  };",
    ]


def _emit_route_row(route: PinRoute) -> str:
    code = route.code if route.code is not None else -1
    alt = (
        f"\"{route.alternate_pin}\""
        if route.alternate_pin is not None
        else "nullptr"
    )
    return (
        "    "
        + "{ "
        + f"\"{route.peripheral_id}\", "
        + f"\"{route.signal_id}\", "
        + f"pin::id::{route.pin_id}, "
        + f"{code}, "
        + alt
        + " },"
    )


def emit_pin_router(device: CanonicalDevice, synthesised: SynthesisedDevice) -> str:
    """Render ``pins.h`` for ``device``."""
    routes = synthesised.pin_routes
    pin_ids = _gather_pin_ids(device, routes)

    schema_id = (
        routes[0].backend_schema_id
        if routes
        else "alloy.pinmux.unknown-v0"
    )

    guard = "ALLOY_" + _safe_c_id(
        f"{device.identity.vendor}_{device.identity.family}_{device.identity.device}"
    ).upper() + "_PINS_H"

    lines: list[str] = [
        "/* pins.h",
        " *",
        f" * {device.identity.vendor}/{device.identity.family}/{device.identity.device}"
        f" — generated from {device.schema}",
        " *",
        f" * Pinmux backend: {schema_id}",
        f" * Layout version: {LAYOUT_VERSION}",
        " *",
        f" * Routes: {len(routes)}, pads: {len(pin_ids)}",
        " *",
        " * NOTE: peripheral / signal columns are `const char *` until",
        " * the IR ships typed PeripheralId / SignalId enums (alloy-",
        " * devices-yml v2.2+).  Pin id is already typed.  See proposal",
        " * `add-pin-router-emitter` for the full zero-string roadmap.",
        " */",
        f"#ifndef {guard}",
        f"#define {guard}",
        "",
        "#include <array>",
        "#include <cstdint>",
        "",
        f"namespace alloy::{device.identity.vendor}::{device.identity.family}::{_safe_c_id(device.identity.device)} {{",
        "",
        "namespace pin {",
    ]
    lines.extend(_emit_pin_id_enum(pin_ids))
    lines.append("}  // namespace pin")
    lines.append("")
    lines.append("namespace pin_routes {")
    lines.extend(_emit_route_struct())
    lines.append("")
    if routes:
        lines.append(f"  inline constexpr std::array<route, {len(routes)}> kRoutes = {{{{")
        for route in routes:
            lines.append(_emit_route_row(route))
        lines.append("  }};")
    else:
        lines.append("  inline constexpr std::array<route, 0> kRoutes{};")
    lines.append(f"  inline constexpr unsigned kRouteCount = {len(routes)}u;")
    lines.append("}  // namespace pin_routes")
    lines.append("")
    lines.append(f"}}  // namespace alloy::{device.identity.vendor}::{device.identity.family}::{_safe_c_id(device.identity.device)}")
    lines.append("")
    lines.append(f"#endif  /* {guard} */")
    lines.append("")
    return "\n".join(lines)


__all__ = ["LAYOUT_VERSION", "emit_pin_router"]
