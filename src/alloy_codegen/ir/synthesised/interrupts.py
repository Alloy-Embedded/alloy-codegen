"""Synthesised interrupt bindings + vector slots.

The on-disk YAML carries either a flat ``interrupts:`` vector list or
the matrix shape (ESP32).  The synthesis stage normalises both into
typed :class:`InterruptBinding` (per-peripheral) and :class:`VectorSlot`
(per-IRQ-line) rows the runtime emitter consumes.
"""

from __future__ import annotations

from dataclasses import dataclass
from typing import Literal

VectorKind = Literal[
    "initial-stack-pointer",
    "reset",
    "system-exception",
    "peripheral-irq",
    "shared-irq",          # multiple peripherals collapsed onto one slot (nRF52)
    "matrix-source",       # ESP32 — slot is dynamically routed at runtime
]


@dataclass(frozen=True, slots=True)
class InterruptBinding:
    """One typed (peripheral → IRQ) binding."""

    binding_id: str
    peripheral: str
    interrupt: str
    line: int
    vector_slot: int | None = None
    symbol_name: str | None = None
    shared_group: str | None = None
    """Set when multiple peripherals collapse onto the same vector
    (nRF52's SPIM0/SPIS0/TWIM0/TWIS0/SPI0/TWI0 all map to NVIC line 3
    via a `mutex_group`).  Codegen warns when more than one is enabled."""


@dataclass(frozen=True, slots=True)
class VectorSlot:
    """One row of the vector table the startup emitter writes."""

    slot: int
    symbol_name: str
    kind: VectorKind
    interrupt: str | None = None
    """For peripheral / shared / matrix kinds, the IRQ name."""
    core_affinity: str = "cpu0"
    """Multi-core devices broadcast NMI / fault to both cores
    (``"shared"``) but pin per-peripheral vectors to a single core."""
