"""Synthesised pin routes — one row per
``(peripheral_instance, peripheral_signal, pin)`` triple the IR
admits as a valid routing.

Built by walking ``device.peripherals[*].pin_options`` and
delegating per-vendor encoding (AF number for STM32, PIO matrix
function letter for SAM E70/V71, FUNCSEL for RP2040, IO Matrix
slot for ESP32, etc.) to a :class:`PinmuxBackend` keyed by the
family's ``pinmux_backend_schema_id``.

When the on-disk YAML doesn't yet carry the routing code (today's
STM32 + SAM corpus does **not** carry ``af`` numbers), the
backend returns ``code=None``.  The emitter still publishes the
typed ``PinRoute`` so consumers can refuse invalid pad ↔ signal
combinations at compile time; AF numeric dispatch lights up on
the next YAML enrichment pass without a shape change.

Determinism: rows are sorted by
``(peripheral_id, signal_id, pin_id)`` ascending so regenerated
``pins.h`` files are byte-identical across runs.
"""

from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True, slots=True)
class PinRoute:
    """One canonical-typed pin route."""

    peripheral_id: str
    """``device.peripherals[i].id`` — typed-ref source of truth."""

    signal_id: str
    """The signal name as the YAML keys it (``tx``, ``rx``,
    ``ch1``, ``txd``, ``mclk``, ...).  This is the alloy-device
    signal-id that flows into ``pins.h`` as a typed enum value."""

    pin_id: str
    """``device.pinout[j].signal`` — the canonical pad label.
    Already filtered to pads not marked as ``power``/``ground``
    (those flow through ``constraints_of()`` only)."""

    backend_schema_id: str
    """The family's ``pinmux_backend_schema_id`` — encodes how to
    interpret ``code`` (AF number, PIO matrix letter as int,
    FUNCSEL slot, etc.)."""

    code: int | None = None
    """Backend-encoded routing cell.  ``None`` when the IR does
    not yet carry the routing code for this pad/signal — the
    emitter still publishes the route entry so consumers can
    refuse invalid pad ↔ signal combinations at compile time."""

    alternate_pin: str | None = None
    """Set on STM32 routes that carry a package-conditional
    alternate-pin annotation (``PA12 [PA10]`` style — the canonical
    pad is PA12 but on the package's UFQFPN28 the routing is
    available through PA10).  Resolved at runtime by
    ``pin_route_lookup`` when ``alternate_pin is not None``."""
