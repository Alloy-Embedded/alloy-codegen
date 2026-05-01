"""Top-level :class:`CanonicalDevice` aggregate.

Carries every required and optional section of the v2.1 schema.
"""

from __future__ import annotations

from dataclasses import dataclass, field

from alloy_codegen.ir.v2_1.clock import Clock
from alloy_codegen.ir.v2_1.identity import Identity
from alloy_codegen.ir.v2_1.interrupts import InterruptMatrix, InterruptVector
from alloy_codegen.ir.v2_1.memory import MemoryRegion
from alloy_codegen.ir.v2_1.peripherals import PeripheralInstance
from alloy_codegen.ir.v2_1.pinout import Pin
from alloy_codegen.ir.v2_1.provenance import Provenance
from alloy_codegen.ir.v2_1.templates import Template


@dataclass(frozen=True, slots=True)
class CanonicalDevice:
    """The whole canonical device IR.

    Required sections per the schema: ``schema``, ``identity``,
    ``provenance``, ``memory``, ``clock``, ``peripherals``, ``pinout``.
    Optional: ``templates``, ``interrupts``, ``fuses``,
    ``system_examples``.
    """

    identity:        Identity
    provenance:      Provenance
    memory:          tuple[MemoryRegion, ...]
    clock:           Clock
    peripherals:     tuple[PeripheralInstance, ...]
    pinout:          tuple[Pin, ...]
    schema:          str = "alloy.device.v2.1"
    templates:       dict[str, Template] = field(default_factory=dict)
    interrupts:      tuple[InterruptVector, ...] | InterruptMatrix | None = None
    fuses:           dict[str, object] | None = None
    system_examples: dict[str, object] | None = None
