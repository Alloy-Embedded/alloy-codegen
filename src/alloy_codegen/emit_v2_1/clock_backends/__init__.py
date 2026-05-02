"""Clock-backend registry.

Lookup is intentionally explicit — ``registry()`` returns the
``vendor → ClockBackend`` mapping at the time of the call.  The
synthesiser uses ``backend_for(vendor)`` to pick (or learn that
no backend exists, in which case we emit no
``clock_program_steps`` and the runtime-init emitter falls back
to declaration-only output for that profile).
"""

from __future__ import annotations

from alloy_codegen.emit_v2_1.clock_backends._protocol import ClockBackend
from alloy_codegen.emit_v2_1.clock_backends.st import ST_CLOCK_BACKEND


def registry() -> dict[str, ClockBackend]:
    """Return the ``vendor → ClockBackend`` mapping."""
    # Add new entries here as backends land.  The keys MUST match
    # ``device.identity.vendor`` exactly (lower-case, dotted-id
    # style — ``st``, ``microchip``, ``raspberrypi``, ``espressif``,
    # ``nxp``, ``nordic``).
    return {
        "st": ST_CLOCK_BACKEND,
    }


def backend_for(vendor: str) -> ClockBackend | None:
    """Return the backend for ``vendor`` or ``None`` if no
    backend ships for it yet.  Synthesis treats ``None`` as
    "leave ``clock_program_steps`` empty" and the emitter then
    only writes the legacy forward-decls."""
    return registry().get(vendor.lower())


__all__ = ["ClockBackend", "backend_for", "registry"]
