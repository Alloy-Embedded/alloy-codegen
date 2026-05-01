"""Pinout (per-package pin map) + pin-constraint vocabulary.

Mirrors ``$defs/pin``.  The constraint enum is the single source of
truth for codegen's pin-router validity checks.
"""

from __future__ import annotations

from dataclasses import dataclass, field

# Closed enum.  Matches the schema's pinout/items/constraints enum.
PIN_CONSTRAINT_ALLOWED: frozenset[str] = frozenset({
    "analog-only",
    "analog-capable",
    "analog",
    "strapping",
    "flash-reserved",
    "nfc-default",
    "lfxo-bond",
    "input-only",
    "rtc",
    "reset",
    "debug-default",
    "boot",
    "oscillator",
    "power",
    "power-control",
    "chip-enable",
    "module-reserved",
    "low-drive",
})


@dataclass(frozen=True, slots=True)
class Pin:
    """One bonded pad on the chip / module."""

    signal: str
    pin: int | None = None
    pad: int | None = None
    default_function: str | None = None
    ft: bool | None = None             # 5V-tolerant input flag
    rtc: str | None = None
    iomux: str | None = None
    saadc: str | None = None
    adc: str | None = None
    arduino: str | None = None
    pico: str | None = None
    voltage: str | None = None
    strapping_role: str | None = None
    input_only: bool | None = None
    pinned: bool = True
    constraints: tuple[str, ...] = field(default_factory=tuple)
    extra: dict[str, object] = field(default_factory=dict)
