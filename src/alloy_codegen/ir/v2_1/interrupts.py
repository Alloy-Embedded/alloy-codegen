"""Interrupt vector / matrix dataclasses.

Two on-disk shapes per the schema's `oneOf`:

* **Vector table** (Cortex-M, AVR, RP2040) — list of
  ``{num, name}`` entries.
* **Matrix** (ESP32) — peripheral signals route to internal IRQ slots
  dynamically; only the source list is interesting.
"""

from __future__ import annotations

from dataclasses import dataclass, field


@dataclass(frozen=True, slots=True)
class InterruptVector:
    """One row in a fixed vector table."""

    num: int
    name: str
    role: str | None = None


@dataclass(frozen=True, slots=True)
class InterruptPeripheralSource:
    """One peripheral interrupt source on a matrix-style chip."""

    id: int
    name: str


@dataclass(frozen=True, slots=True)
class InterruptMatrix:
    """ESP32-style dynamic interrupt matrix."""

    matrix: bool = True
    internal_per_cpu: int | None = None
    peripheral_sources: tuple[InterruptPeripheralSource, ...] = field(default_factory=tuple)
