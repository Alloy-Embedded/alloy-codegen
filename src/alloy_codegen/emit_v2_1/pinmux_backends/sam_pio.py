"""SAM PIO (SAME70 / SAMV71) pinmux backend — ``alloy.pinmux.sam-matrix-function-v1``.

Microchip SAM E70 / SAM V71 select peripheral signals through the PIO
controller's Peripheral Select registers (ABCDSR0 / ABCDSR1).  Each GPIO
line can be assigned to one of four peripheral functions (A=0, B=1, C=2,
D=3); the two-bit encoded value is written into ABCDSR0/1 and the PIO
line is given to the peripheral via the PIO Disable Register (PDR).

Today's admitted YAMLs carry the **pad candidate** for each
``(peripheral, signal)`` triple but **not the A/B/C/D function code**.
This backend therefore returns ``code=None`` until the YAML schema gains
a ``func:`` field on each ``PinOptionFixed`` row (scheduled for the
alloy-devices-yml enrichment pass).

When ``code is None`` the emitter still publishes a typed
``ConnectorTraits`` specialisation so the HAL can refuse invalid
pad↔signal combinations at compile time; the ``kRoutes`` table entry
carries ``code = 0xFFFFu`` as a sentinel.  The runtime's
``make_same70_pinmux_operation()`` currently synthesises the ABCDSR bit
from the routing code in ``kRoutes``; until the YAML carries real A/B/C/D
values the runtime falls back to the existing hand-curated
``RouteTraits`` path.

See: ``hal/connect/runtime_connector.hpp`` — ``make_same70_pinmux_operation()``.
"""

from __future__ import annotations

from alloy_codegen.emit_v2_1.pinmux_backends._protocol import PinOption
from alloy_codegen.ir.synthesised.pin_routes import PinRoute
from alloy_codegen.ir.v2_1 import (
    PeripheralInstance,
    PinOptionFixed,
)

SCHEMA_ID = "alloy.pinmux.sam-matrix-function-v1"


def _normalise_pin_id(raw: str) -> str:
    """Lower-case the canonical SAM pad label.

    Examples:

    * ``PA9``   → ``pa9``
    * ``PD30``  → ``pd30``
    * ``PC15``  → ``pc15``
    """
    return raw.strip().lower()


class _SamPioBackend:
    schema_id = SCHEMA_ID

    def encode(
        self,
        peripheral: PeripheralInstance,
        signal: str,
        option: PinOption,
    ) -> PinRoute:
        if not isinstance(option, PinOptionFixed):
            # SAME70 PIO admits Fixed candidates only.  Matrix / Psel
            # option types are ESP32 / Nordic idioms and must not appear
            # in Microchip SAM descriptors.
            raise ValueError(
                f"sam-pio backend cannot encode option type "
                f"{type(option).__name__} (peripheral={peripheral.id}, "
                f"signal={signal})"
            )

        # ``option.func`` carries the A/B/C/D numeric code (0–3) once
        # the YAML is enriched; ``None`` until then.  Use ``option.func``
        # directly — the emitter propagates ``None`` as the sentinel
        # ``0xFFFFu`` in ``kRoutes``.
        return PinRoute(
            peripheral_id=peripheral.id,
            signal_id=signal,
            pin_id=_normalise_pin_id(option.pin),
            backend_schema_id=SCHEMA_ID,
            code=option.func,
        )


SAM_PIO_BACKEND = _SamPioBackend()
"""Singleton — registered under ``alloy.pinmux.sam-matrix-function-v1``
for ``("microchip", "same70")`` and ``("microchip", "samv71")``."""

__all__ = ["SAM_PIO_BACKEND", "SCHEMA_ID"]
