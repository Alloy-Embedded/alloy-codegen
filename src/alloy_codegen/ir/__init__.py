"""Canonical intermediate representation types — v2.1 only.

The v1 IR module tree (``alloy_codegen.ir.model`` + the
``CanonicalDeviceIR`` dataclass family) was removed by
``adopt-canonical-device-v2-1``.  Every consumer migrates to the
typed v2.1 surface re-exported below.
"""

from alloy_codegen.ir.synthesised import (
    InterruptBinding,
    RouteOperation,
    SignalEndpoint,
    SynthesisedDevice,
    VectorSlot,
    build_synthesised,
)
from alloy_codegen.ir.v2_1 import (
    CANONICAL_SCHEMA,
    CanonicalDevice,
    Clock,
    ClockDomain,
    ClockProfile,
    Core,
    Identity,
    InterruptMatrix,
    InterruptVector,
    MemoryRegion,
    Multicore,
    Oscillator,
    PeripheralInstance,
    Pin,
    Provenance,
    Template,
    TemplateField,
    TemplateRegister,
)

__all__ = [
    "CANONICAL_SCHEMA",
    "CanonicalDevice",
    "Clock",
    "ClockDomain",
    "ClockProfile",
    "Core",
    "Identity",
    "InterruptBinding",
    "InterruptMatrix",
    "InterruptVector",
    "MemoryRegion",
    "Multicore",
    "Oscillator",
    "PeripheralInstance",
    "Pin",
    "Provenance",
    "RouteOperation",
    "SignalEndpoint",
    "SynthesisedDevice",
    "Template",
    "TemplateField",
    "TemplateRegister",
    "VectorSlot",
    "build_synthesised",
]
