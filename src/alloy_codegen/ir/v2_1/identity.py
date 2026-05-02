"""Top-level device identity dataclasses.

Mirrors ``$defs/identity`` and ``$defs/core`` in the v2.1 schema.
"""

from __future__ import annotations

from dataclasses import dataclass, field
from typing import Literal

CoreBits = Literal[8, 16, 32, 64]
Endianness = Literal["little", "big"]
MulticoreTopology = Literal[
    "single_core",
    "symmetric_dual_core",
    "xtensa_asymmetric_dual_core",
]


@dataclass(frozen=True, slots=True)
class MulticoreCore:
    """One core in a multi-core topology."""

    id: str
    role: str
    vector_base: int | None = None
    app_cpu: bool | None = None
    release_register: str | None = None
    release_op: str | None = None
    start_vector_symbol: str | None = None


@dataclass(frozen=True, slots=True)
class Multicore:
    """Multi-core organisation block under :class:`Core`."""

    topology: MulticoreTopology
    cores: tuple[MulticoreCore, ...]


@dataclass(frozen=True, slots=True)
class Core:
    """CPU descriptor.

    `nvic_priority_bits` is 0 on architectures that don't expose
    NVIC priority encoding (AVR, classic Xtensa).  `interrupt_lines`
    counts NVIC IRQs (excluding system exceptions) on Cortex-M; on
    AVR / Xtensa it counts the vector-table size.
    """

    isa: str
    name: str
    bits: CoreBits
    fpu: bool = False
    mpu: bool = False
    endianness: Endianness = "little"
    interrupt_lines: int | None = None
    nvic_priority_bits: int | None = None
    multicore: Multicore | None = None


@dataclass(frozen=True, slots=True)
class FlashLatencyEntry:
    """One row of the FLASH wait-state table.

    For Cortex-M parts, every clock-tree program needs to know
    "at this HCLK, how many wait states do I write into FLASH.ACR
    (or its equivalent)".  The table is family-wide — every chip
    in stm32g0 shares the same 0/1/2 WS thresholds — so admitting
    a new chip in an existing family is one YAML edit, not a
    per-chip table.

    ``min_hz`` is inclusive, ``max_hz`` is exclusive.  ``encoding``
    is the value to write into the FLASH latency field.
    """

    min_hz: int
    max_hz: int
    ws: int
    encoding: int


@dataclass(frozen=True, slots=True)
class Identity:
    """Top-level identity block."""

    vendor: str
    family: str
    device: str
    core: Core
    package: str | None = None
    variant: str | None = None
    flash_size: str | None = None
    ram_size: str | None = None
    description: str | None = None
    flash_wait_states: tuple[FlashLatencyEntry, ...] = field(default_factory=tuple)
    """FLASH wait-state table, family-wide.

    Empty until the data team promotes the per-family thresholds
    out of inline backend knowledge.  Backends that need WS
    programming (every Cortex-M with embedded FLASH) fall back
    to a hard-coded family table when this is empty, and warn
    once at synthesis time so the gap is visible.
    """
    extra: dict[str, object] = field(default_factory=dict)
    """Vendor-specific extra fields preserved through round-trip."""
