"""Canonical IR data models."""

from __future__ import annotations

from dataclasses import dataclass, field

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
    startup_roles: tuple[str, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )


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
    ip_version: str | None
    instance: int
    base_address: int
    rcc_enable_signal: str | None
    rcc_reset_signal: str | None
    provenance: Provenance
    backend_schema_id: str | None = None


@dataclass(frozen=True, slots=True)
class InterruptDefinition:
    """One interrupt line."""

    name: str
    line: int
    peripheral: str | None
    provenance: Provenance
    shared_group: str | None = None
    alias_names: tuple[str, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )


@dataclass(frozen=True, slots=True)
class DmaRequestDefinition:
    """One DMA request mapping."""

    controller: str
    request_line: str
    peripheral: str | None
    signal: str | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class IpBlockDefinition:
    """Reusable IP block definition keyed by name and version."""

    ip_name: str
    ip_version: str
    peripheral_class: str
    register_profile: str | None
    signal_roles: tuple[str, ...]
    capability_ids: tuple[str, ...]
    provenance: Provenance
    backend_schema_id: str | None = None


@dataclass(frozen=True, slots=True)
class RegisterDescriptor:
    """One normalized register descriptor owned by a peripheral instance."""

    register_id: str
    peripheral: str
    name: str
    offset_bytes: int
    access: str | None
    size_bits: int | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class RegisterFieldDescriptor:
    """One normalized register field owned by a peripheral register."""

    field_id: str
    register_id: str
    peripheral: str
    register_name: str
    name: str
    bit_offset: int
    bit_width: int
    access: str | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class CapabilityDescriptor:
    """One versioned capability fact exposed to emitters and Alloy."""

    capability_id: str
    scope: str
    peripheral_class: str
    name: str
    value: str
    provenance: Provenance
    ip_name: str | None = None
    ip_version: str | None = None
    peripheral: str | None = None
    package: str | None = None


@dataclass(frozen=True, slots=True)
class PackagePad:
    """One physical package pad entry."""

    pad_id: str
    package: str
    position_label: str
    physical_index: int | None
    pad_kind: str
    bonded_pin: str | None
    provenance: Provenance
    bonding_state: str = "bonded"


@dataclass(frozen=True, slots=True)
class PinConstraint:
    """One pin-level constraint."""

    constraint_id: str
    pin: str
    kind: str
    value: str | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class SignalEndpoint:
    """One canonical peripheral-side signal identity."""

    endpoint_id: str
    peripheral_class: str
    signal: str
    direction: str | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class RouteRequirement:
    """One prerequisite for a candidate or connection group."""

    requirement_id: str
    kind: str
    target: str | None
    value: str | None
    provenance: Provenance
    target_ref_kind: str | None = field(default=None, metadata={"omit_if_empty": True})
    target_ref_id: str | None = field(default=None, metadata={"omit_if_empty": True})
    value_ref_kind: str | None = field(default=None, metadata={"omit_if_empty": True})
    value_ref_id: str | None = field(default=None, metadata={"omit_if_empty": True})
    value_int: int | None = field(default=None, metadata={"omit_if_empty": True})


@dataclass(frozen=True, slots=True)
class RouteOperation:
    """One concrete hardware operation required to realize a route."""

    operation_id: str
    kind: str
    target: str
    value: str | None
    provenance: Provenance
    schema_id: str | None = None
    subject_kind: str | None = None
    subject_id: str | None = None
    register_peripheral: str | None = None
    register_name: str | None = None
    register_offset: int | None = None
    value_int: int | None = None
    register_id: str | None = field(default=None, metadata={"omit_if_empty": True})
    register_field_id: str | None = field(default=None, metadata={"omit_if_empty": True})
    target_ref_kind: str | None = field(default=None, metadata={"omit_if_empty": True})
    target_ref_id: str | None = field(default=None, metadata={"omit_if_empty": True})
    value_ref_kind: str | None = field(default=None, metadata={"omit_if_empty": True})
    value_ref_id: str | None = field(default=None, metadata={"omit_if_empty": True})


@dataclass(frozen=True, slots=True)
class ConnectionCandidate:
    """One valid concrete route from a pin to a peripheral signal."""

    candidate_id: str
    pin: str
    peripheral: str
    signal: str
    route_kind: str
    route_selector: str | None
    route_group_id: str | None
    requirement_ids: tuple[str, ...]
    operation_ids: tuple[str, ...]
    capability_ids: tuple[str, ...]
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class ConnectionGroup:
    """One valid group of candidates that may coexist."""

    group_id: str
    peripheral: str
    signals: tuple[str, ...]
    candidate_ids: tuple[str, ...]
    package: str | None
    conflict_group: str | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class InterruptBindingDescriptor:
    """One typed interrupt binding owned by a peripheral instance."""

    binding_id: str
    peripheral: str
    interrupt: str
    line: int
    vector_slot: int | None
    symbol_name: str | None
    shared_group: str | None
    provenance: Provenance
    alias_names: tuple[str, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )


@dataclass(frozen=True, slots=True)
class VectorSlotDescriptor:
    """One vector-table slot descriptor."""

    slot: int
    symbol_name: str
    interrupt: str | None
    kind: str
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class StartupDescriptor:
    """One startup-related descriptor entry."""

    descriptor_id: str
    kind: str
    source_region: str | None
    target_region: str | None
    symbol: str | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class ClockNodeLite:
    """One simplified clock-tree node."""

    node_id: str
    kind: str
    parent: str | None
    selector: str | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class ClockSelectorLite:
    """One simplified parent/source selector."""

    selector_id: str
    parent_options: tuple[str, ...]
    register_target: str | None
    provenance: Provenance
    register_peripheral: str | None = field(default=None, metadata={"omit_if_empty": True})
    register_name: str | None = field(default=None, metadata={"omit_if_empty": True})
    register_offset: int | None = field(default=None, metadata={"omit_if_empty": True})
    register_id: str | None = field(default=None, metadata={"omit_if_empty": True})
    register_field_id: str | None = field(default=None, metadata={"omit_if_empty": True})


@dataclass(frozen=True, slots=True)
class ClockGateDescriptor:
    """One clock gate descriptor."""

    gate_id: str
    peripheral: str | None
    enable_signal: str
    parent_node: str | None
    provenance: Provenance
    register_peripheral: str | None = field(default=None, metadata={"omit_if_empty": True})
    register_name: str | None = field(default=None, metadata={"omit_if_empty": True})
    register_offset: int | None = field(default=None, metadata={"omit_if_empty": True})
    register_id: str | None = field(default=None, metadata={"omit_if_empty": True})
    register_field_id: str | None = field(default=None, metadata={"omit_if_empty": True})


@dataclass(frozen=True, slots=True)
class ResetDescriptor:
    """One reset descriptor."""

    reset_id: str
    peripheral: str | None
    reset_signal: str
    active_level: str | None
    provenance: Provenance
    register_peripheral: str | None = field(default=None, metadata={"omit_if_empty": True})
    register_name: str | None = field(default=None, metadata={"omit_if_empty": True})
    register_offset: int | None = field(default=None, metadata={"omit_if_empty": True})
    register_id: str | None = field(default=None, metadata={"omit_if_empty": True})
    register_field_id: str | None = field(default=None, metadata={"omit_if_empty": True})


@dataclass(frozen=True, slots=True)
class PeripheralClockBinding:
    """How one peripheral instance binds into the simplified clock/reset graph."""

    peripheral: str
    clock_gate_id: str | None
    reset_id: str | None
    selector_id: str | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class DmaBindingDescriptor:
    """One typed DMA binding owned by a peripheral instance."""

    binding_id: str
    peripheral: str
    signal: str | None
    controller: str
    request_line: str
    route_id: str
    conflict_group: str | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class DmaControllerDescriptor:
    """One DMA controller descriptor."""

    controller: str
    version: str | None
    channel_count: int | None
    request_count: int | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class DmaRouteDescriptor:
    """One normalized DMA route descriptor."""

    route_id: str
    controller: str
    request_line: str
    peripheral: str | None
    signal: str | None
    conflict_group: str | None
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class DmaConflictGroup:
    """One explicit DMA route conflict group."""

    conflict_group_id: str
    route_ids: tuple[str, ...]
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
    registers: tuple[RegisterDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    register_fields: tuple[RegisterFieldDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    ip_blocks: tuple[IpBlockDefinition, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    capabilities: tuple[CapabilityDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    package_pads: tuple[PackagePad, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    pin_constraints: tuple[PinConstraint, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    signal_endpoints: tuple[SignalEndpoint, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    route_requirements: tuple[RouteRequirement, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    route_operations: tuple[RouteOperation, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    connection_candidates: tuple[ConnectionCandidate, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    connection_groups: tuple[ConnectionGroup, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    interrupt_bindings: tuple[InterruptBindingDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    vector_slots: tuple[VectorSlotDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    startup_descriptors: tuple[StartupDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    clock_nodes: tuple[ClockNodeLite, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    clock_selectors: tuple[ClockSelectorLite, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    clock_gates: tuple[ClockGateDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    resets: tuple[ResetDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    peripheral_clock_bindings: tuple[PeripheralClockBinding, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    dma_controllers: tuple[DmaControllerDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    dma_bindings: tuple[DmaBindingDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    dma_routes: tuple[DmaRouteDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    dma_conflict_groups: tuple[DmaConflictGroup, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )

    def to_dict(self) -> dict[str, object]:
        return to_primitive(self)
