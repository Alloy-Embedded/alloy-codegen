"""Top-level :class:`SynthesisedDevice` aggregate.

Carries every typed row alloy-codegen synthesises from the on-disk
:class:`alloy_codegen.ir.v2_1.CanonicalDevice` at codegen time.  These
rows never travel through YAML — keeping them out of the source-of-
truth file is one of the v2.1 design pillars.
"""

from __future__ import annotations

from dataclasses import dataclass, field

from alloy_codegen.ir.synthesised.clock_program import ClockProgramStep
from alloy_codegen.ir.synthesised.endpoints import SignalEndpoint
from alloy_codegen.ir.synthesised.interrupts import (
    InterruptBinding,
    VectorSlot,
)
from alloy_codegen.ir.synthesised.pin_routes import PinRoute
from alloy_codegen.ir.synthesised.route_operations import RouteOperation
from alloy_codegen.ir.v2_1.peripherals import PeripheralRcc


@dataclass(frozen=True, slots=True)
class SynthesisedDevice:
    """Aggregate of typed runtime rows derived from a CanonicalDevice."""

    route_operations:    tuple[RouteOperation, ...] = field(default_factory=tuple)
    interrupt_bindings:  tuple[InterruptBinding, ...] = field(default_factory=tuple)
    vector_slots:        tuple[VectorSlot, ...] = field(default_factory=tuple)
    signal_endpoints:    tuple[SignalEndpoint, ...] = field(default_factory=tuple)
    clock_program_steps: dict[str, tuple[ClockProgramStep, ...]] = field(default_factory=dict)
    per_rcc_map:         dict[str, PeripheralRcc] = field(default_factory=dict)
    """Per-peripheral RCC info (enable + reset paths + bus + clock_sel).
    Populated by cross-linking the top-level 'rcc' template fields to
    each peripheral instance.  Falls back to the peripheral's own
    ``rcc:`` block when set directly in the YAML."""
    """Per-profile clock program — keyed by ``ClockProfile.id``,
    valued as the ordered tuple of vendor-agnostic
    :class:`ClockProgramStep` rows the emitter walks to produce
    ``alloy_clock_enter_<profile_id>()``.  Empty when no
    :class:`ClockBackend` matches the device's vendor (the
    runtime-init emitter then falls back to the legacy
    forward-declaration-only output)."""
    pin_routes:          tuple[PinRoute, ...] = field(default_factory=tuple)
    """Deterministically-ordered table of every
    ``(peripheral_instance, peripheral_signal, pin)`` triple the
    IR admits as a valid routing.  Produced by walking
    ``device.peripherals[*].pin_options`` and delegating to a
    :class:`PinmuxBackend` keyed by the family's pinmux schema
    id.  Sorted by ``(peripheral_id, signal_id, pin_id)``."""
