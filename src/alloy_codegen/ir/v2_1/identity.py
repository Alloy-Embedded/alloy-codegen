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
    extra: dict[str, object] = field(default_factory=dict)
    """Vendor-specific extra fields preserved through round-trip."""
