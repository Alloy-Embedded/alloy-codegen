"""Top-level :class:`SynthesisedDevice` aggregate.

Carries every typed row alloy-codegen synthesises from the on-disk
:class:`alloy_codegen.ir.v2_1.CanonicalDevice` at codegen time.  These
rows never travel through YAML — keeping them out of the source-of-
truth file is one of the v2.1 design pillars.
"""

from __future__ import annotations

from dataclasses import dataclass, field

from alloy_codegen.ir.synthesised.endpoints import SignalEndpoint
from alloy_codegen.ir.synthesised.interrupts import (
    InterruptBinding,
    VectorSlot,
)
from alloy_codegen.ir.synthesised.route_operations import RouteOperation


@dataclass(frozen=True, slots=True)
class SynthesisedDevice:
    """Aggregate of typed runtime rows derived from a CanonicalDevice."""

    route_operations:    tuple[RouteOperation, ...] = field(default_factory=tuple)
    interrupt_bindings:  tuple[InterruptBinding, ...] = field(default_factory=tuple)
    vector_slots:        tuple[VectorSlot, ...] = field(default_factory=tuple)
    signal_endpoints:    tuple[SignalEndpoint, ...] = field(default_factory=tuple)
