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


@dataclass(frozen=True, slots=True)
class RawPinAlternateFunction:
    """One alternate-function capable signal attached to a GPIO pin."""

    signal_name: str
    af_number: int


@dataclass(frozen=True, slots=True)
class RawPinDocumentEntry:
    """One GPIO-capable pin entry extracted from upstream pin data."""

    name: str
    port: str
    number: int
    signals: tuple[RawPinAlternateFunction, ...]


@dataclass(frozen=True, slots=True)
class RawPinDataDocument:
    """Raw package and pin connectivity extracted from open pin data."""

    device_name: str
    package_name: str
    package_pin_count: int | None
    pins: tuple[RawPinDocumentEntry, ...]
    gpio_modes_file: str
