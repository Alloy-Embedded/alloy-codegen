"""Raw source models extracted from upstream descriptions."""

from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True, slots=True)
class RawPeripheral:
    """One peripheral instance extracted from a raw source."""

    name: str
    base_address: int


@dataclass(frozen=True, slots=True)
class RawInterrupt:
    """One interrupt line extracted from a raw source."""

    name: str
    line: int
    peripheral: str | None


@dataclass(frozen=True, slots=True)
class RawDeviceDocument:
    """A raw device description extracted from upstream source."""

    device_name: str
    description: str
    svd_version: str | None
    peripherals: tuple[RawPeripheral, ...]
    interrupts: tuple[RawInterrupt, ...]
