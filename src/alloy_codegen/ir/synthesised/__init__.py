"""Synthesised IR rows — produced from :class:`CanonicalDevice` at
codegen time, never serialised to disk.

Public surface:

* :class:`RouteOperation`
* :class:`InterruptBinding`, :class:`VectorSlot`
* :class:`SignalEndpoint`
* :class:`SynthesisedDevice` — the aggregate
* :func:`build_synthesised(device)` — the builder
"""

from __future__ import annotations

from alloy_codegen.ir.synthesised.builder import build_synthesised
from alloy_codegen.ir.synthesised.device import SynthesisedDevice
from alloy_codegen.ir.synthesised.endpoints import SignalEndpoint
from alloy_codegen.ir.synthesised.interrupts import (
    InterruptBinding,
    VectorSlot,
)
from alloy_codegen.ir.synthesised.route_operations import RouteOperation

__all__ = [
    "InterruptBinding",
    "RouteOperation",
    "SignalEndpoint",
    "SynthesisedDevice",
    "VectorSlot",
    "build_synthesised",
]
