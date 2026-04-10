"""Canonical IR data models."""

from __future__ import annotations

from dataclasses import dataclass

from alloy_codegen.serialization import to_primitive


@dataclass(frozen=True, slots=True)
class Provenance:
    """Traceability for one normalized fact."""

    source_id: str
    source_path: str | None
    patch_ids: tuple[str, ...]


@dataclass(frozen=True, slots=True)
class DeviceIdentity:
    """Top-level device identity."""

    vendor: str
    family: str
    device: str
    package: str
    core: str
    summary: str


@dataclass(frozen=True, slots=True)
class MemoryRegion:
    """A memory region in the canonical IR."""

    name: str
    kind: str
    base_address: int
    size_bytes: int
    access: str
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class PackageDefinition:
    """One package variant."""

    name: str
    pin_count: int
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class PinSignal:
    """One signal attached to a pin."""

    function: str
    peripheral: str | None
    signal: str | None
    af_number: int | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class PinDefinition:
    """One canonical pin entry."""

    name: str
    port: str | None
    number: int
    signals: tuple[PinSignal, ...]
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class PeripheralInstance:
    """One peripheral instance."""

    name: str
    ip_name: str
    instance: int
    base_address: int
    rcc_enable_signal: str | None
    rcc_reset_signal: str | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class InterruptDefinition:
    """One interrupt line."""

    name: str
    line: int
    peripheral: str | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class DmaRequestDefinition:
    """One DMA request mapping."""

    controller: str
    request_line: str
    peripheral: str | None
    signal: str | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class CanonicalDeviceIR:
    """Canonical device description used by validation and emitters."""

    schema_version: str
    identity: DeviceIdentity
    memories: tuple[MemoryRegion, ...]
    packages: tuple[PackageDefinition, ...]
    pins: tuple[PinDefinition, ...]
    peripherals: tuple[PeripheralInstance, ...]
    interrupts: tuple[InterruptDefinition, ...]
    dma_requests: tuple[DmaRequestDefinition, ...]
    provenance: Provenance

    def to_dict(self) -> dict[str, object]:
        return to_primitive(self)

