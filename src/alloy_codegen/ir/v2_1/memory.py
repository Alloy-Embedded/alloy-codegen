"""Memory map — feeds the linker script.

Mirrors ``$defs/memory_region``.  AVR's Harvard architecture and
ESP32/RP2040 external XIP flash both fit cleanly because
:attr:`address_space` and :attr:`backing` are explicit.
"""

from __future__ import annotations

from dataclasses import dataclass, field
from typing import Literal

AddressSpace = Literal[
    "program", "data", "instruction", "eeprom", "fuse", "signature",
]
Access = Literal["r", "rw", "rwx", "rx", "ro", "wo"]


@dataclass(frozen=True, slots=True)
class MemoryRegion:
    """One memory region in the device map.

    `id` is lowercase + hyphens (``flash``, ``sram``, ``ccmram``,
    ``rtc_fast``, ``flash_xip``, …).  `base` is canonical bytes (the
    parser accepts either ``int`` or ``"0x..."``).  `size` is a
    string with KB/MB/GB suffix preserved as written so reviewers
    can compare against datasheets without unit conversion in their
    heads.
    """

    id: str
    base: int
    size: str
    access: Access
    alias: str | None = None
    address_space: AddressSpace | None = None
    backing: str | None = None
    role: str | None = None
    banks: tuple[str, ...] = field(default_factory=tuple)
    default_use: str | None = None
    survives: str | None = None
    extra: dict[str, object] = field(default_factory=dict)
