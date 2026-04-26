"""Canonical IR data models."""

from __future__ import annotations

from dataclasses import dataclass, field
from typing import Literal

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


# Multi-core topology vocabulary (added by expose-xtensa-dual-core-facts).
#
# - ``single_core``: trivially one CPU (default).  Most ARM Cortex-M devices,
#   ESP32-C3, AVR-Dx fall here.
# - ``symmetric_dual_core``: two homogeneous cores sharing one bring-up
#   sequence (RP2040-style).
# - ``xtensa_asymmetric_dual_core``: PRO_CPU (core 0) brings up APP_CPU
#   (core 1) by writing a dedicated control register.  ESP32 classic and
#   ESP32-S3 fall here; the LX6/LX7 wiring differs.
MulticoreTopology = Literal[
    "single_core",
    "symmetric_dual_core",
    "xtensa_asymmetric_dual_core",
]


@dataclass(frozen=True, slots=True)
class AppCpuControlPlane:
    """APP_CPU release sequence for asymmetric Xtensa dual-core devices.

    ``operation`` distinguishes the LX6 ``set bit 0 of DPORT.APPCPU_CTRL_B``
    sequence from the LX7 ``enable CLKGATE then clear RUNSTALL`` sequence.
    ``release_register`` carries the typed ``register_id`` of the primary
    write target.  ``release_register_secondary`` is populated when the
    sequence requires two writes (LX7).
    """

    release_register: str
    operation: str  # "set-bit-0" | "clear-runstall-after-clkgate"
    start_vector_symbol: str
    release_register_secondary: str | None = None


# Register-role tag (added by expose-xtensa-dual-core-facts).  ``general`` is
# the default; ``secondary_core_release`` flags registers that participate in
# the APP_CPU bring-up sequence so consumers can find them by enum equality
# instead of name matching.
RegisterRole = Literal["general", "secondary_core_release"]


# Hardware-feature descriptors added by ``fill-espressif-semantic-gaps``.
# Each captures the static silicon facts for one peripheral instance — base
# address, register-window size hints, fixed pin assignments, GPIO-matrix
# signal indices — that drive alloy ``*SemanticTraits`` ``kPresent`` /
# ``kBaseAddress`` / feature-flag constexprs for families whose register-
# level schema is not yet admitted (Espressif today).  These descriptors
# stay thin: register-by-register traits live on the existing
# ``UartSemanticRow`` / ``SpiSemanticRow`` / etc. rows.
@dataclass(frozen=True, slots=True)
class UartPeripheralDescriptor:
    """UART hardware-feature facts (base address, FIFO depth, GPIO matrix
    signal indices, DMA support)."""

    peripheral_id: str
    base_address: int
    fifo_depth: int
    tx_signal_idx: int | None = None
    rx_signal_idx: int | None = None
    supports_dma: bool = False


@dataclass(frozen=True, slots=True)
class SpiPeripheralDescriptor:
    """SPI hardware-feature facts (base, max clock, GPIO matrix signals,
    optional IO-MUX fast-path pins, DMA support)."""

    peripheral_id: str
    base_address: int
    max_clock_hz: int
    mosi_out_signal: int | None = None
    miso_in_signal: int | None = None
    clk_out_signal: int | None = None
    cs_out_signal: int | None = None
    has_iomux_fast_path: bool = False
    iomux_mosi_pin: int | None = None
    iomux_miso_pin: int | None = None
    iomux_clk_pin: int | None = None
    iomux_cs_pin: int | None = None
    supports_dma: bool = False


@dataclass(frozen=True, slots=True)
class AdcUnitDescriptor:
    """ADC hardware-feature facts (channel count, resolution, Wi-Fi
    conflict flag, channel→pin mapping)."""

    unit_id: str
    channel_count: int
    resolution_bits: int
    conflicts_with_wifi: bool = False
    channel_pins: tuple[int, ...] = ()


@dataclass(frozen=True, slots=True)
class TimerUnitDescriptor:
    """Timer/Counter hardware-feature facts (group/timer indices, base,
    counter width, clock sources)."""

    timer_id: str
    group_idx: int
    timer_idx: int
    base_address: int
    bits: int
    clock_sources: tuple[str, ...] = ()


@dataclass(frozen=True, slots=True)
class LedcDescriptor:
    """LEDC PWM hardware-feature facts (base, channel count, max
    resolution, clock sources, GPIO-matrix output signals per channel)."""

    base_address: int
    channel_count: int
    resolution_bits: int
    clock_sources: tuple[str, ...] = ()
    output_signals: tuple[int, ...] = ()


@dataclass(frozen=True, slots=True)
class DmaChannelDescriptor:
    """DMA channel hardware-feature facts (index, GDMA flag, max transfer
    bytes, peripheral→request-line map)."""

    channel_id: str
    channel_index: int
    is_gdma: bool
    max_transfer_bytes: int = 0
    peripheral_requests: tuple[tuple[str, int], ...] = ()


@dataclass(frozen=True, slots=True)
class UsbControllerDescriptor:
    """Hardware-feature facts for one USB controller (added by
    ``add-usb-semantic-traits``).

    Captures the high-level USB hardware shape (base address, packet memory,
    endpoint count, speed/host capabilities, fixed DM/DP pin assignments)
    that drives the alloy ``UsbDeviceController<T>`` concept.  These are the
    facts that are *static for the silicon* — register layout details for
    runtime poking live in the existing register/field descriptors.

    ``controller_id`` is the peripheral name (``"USB"``, ``"OTG_FS"``,
    ``"UOTGHS"``, etc.) so the emitter can key trait specializations by
    typed ``PeripheralId``.  ``dpram_base_address`` / ``dpram_size_bytes``
    are populated only when the controller has a dedicated packet memory
    area (STM32 PMA, RP2040 DPRAM); ``None`` for OTG-style FIFO
    architectures.  ``dm_pin`` / ``dp_pin`` are populated for controllers
    with fixed pin routing (no IO matrix); ``None`` when the pads are
    routed through GPIO/IO-matrix.  ``clock_source`` is a free-form token
    (``"hsi48-with-crs"``, ``"pll-48mhz"``, ``"xtal-12mhz"``) consumed by
    the alloy clock tree validator.
    """

    controller_id: str
    base_address: int
    endpoint_count: int
    supports_high_speed: bool = False
    supports_host_mode: bool = False
    supports_dma: bool = False
    crystalless: bool = False
    dpram_base_address: int | None = None
    dpram_size_bytes: int | None = None
    dma_channel_count: int = 0
    dm_pin: str | None = None
    dp_pin: str | None = None
    clock_source: str | None = None


@dataclass(frozen=True, slots=True)
class MemoryRegion:
    """A memory region in the canonical IR."""

    name: str
    kind: str
    base_address: int
    size_bytes: int
    access: str
    provenance: Provenance
    address_space: str | None = field(default=None, metadata={"omit_if_empty": True})
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
    """One peripheral instance.

    ``rcc_enable_signal`` and ``rcc_reset_signal`` are normalize-time source
    inputs (raw patch signal strings like ``"RCC_AHBENR.GPIOAEN"``).  They are
    resolved into typed ``ClockGateId`` / ``ResetId`` runtime references via
    ``PeripheralClockBinding`` and ``connector_model``.  They MUST NOT be
    treated as the primary runtime contract — the typed binding IDs are the
    source of truth for emitted artifacts.
    """

    name: str
    ip_name: str
    ip_version: str | None
    instance: int
    base_address: int
    # Diagnostic/normalize-time only — see docstring.
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
    channel_index: int | None = field(default=None, metadata={"omit_if_empty": True})
    request_value: int | None = field(default=None, metadata={"omit_if_empty": True})
    channel_selector: int | None = field(default=None, metadata={"omit_if_empty": True})


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
    """One normalized register descriptor owned by a peripheral instance.

    ``role`` (added by expose-xtensa-dual-core-facts) flags registers that
    play a special part in device bring-up so consumers can find them by
    typed enum equality instead of fragile name matching.  Defaults to
    ``"general"`` for every register; overridden per-register in the
    normalizer (e.g. ESP32 ``DPORT.APPCPU_CTRL_B`` →
    ``"secondary_core_release"``).
    """

    register_id: str
    peripheral: str
    name: str
    offset_bytes: int
    access: str | None
    size_bits: int | None
    provenance: Provenance
    role: RegisterRole = field(default="general", metadata={"omit_if_default": True})


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
    """One prerequisite for a candidate or connection group.

    The primary runtime contract is the typed ref pair
    ``(target_ref_kind, target_ref_id)`` plus ``(value_ref_kind, value_ref_id,
    value_int)``.  The ``target`` and ``value`` string fields are kept as
    human-readable diagnostics only — runtime consumers MUST execute against
    the typed refs and SHALL NOT parse these strings.
    """

    requirement_id: str
    kind: str
    # Diagnostic/human-readable only — see docstring.
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
    """One concrete hardware operation required to realize a route.

    The primary runtime contract is typed: ``(target_ref_kind, target_ref_id)``
    selects the target domain, ``(value_ref_kind, value_ref_id, value_int)``
    selects the value, and ``(register_id, register_field_id)`` identify the
    bit being manipulated.  The following fields are human-readable diagnostics
    only — runtime consumers MUST NOT depend on them for execution:

    - ``target``                 (diagnostic echo of the upstream signal name)
    - ``value``                  (diagnostic echo of the literal value string)
    - ``subject_kind`` / ``subject_id``  (diagnostic trace of who owns the op)
    - ``register_peripheral`` / ``register_name`` / ``register_offset``
      (diagnostic echo resolved from ``register_id`` + ``register_field_id``)
    """

    operation_id: str
    kind: str
    # Diagnostic/human-readable only — see docstring.
    target: str
    value: str | None
    provenance: Provenance
    schema_id: str | None = None
    # Diagnostic/human-readable only — see docstring.
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
    """One vector-table slot descriptor.

    ``core_affinity`` records which core the vector belongs to on multi-core
    targets.  Single-core devices (Cortex-M, RISC-V mononúcleo, AVR8) carry
    the default ``"cpu0"`` and downstream emitters ignore the field.  Dual-core
    Xtensa families (ESP32 LX6, ESP32-S3 LX7) partition vectors between
    ``"cpu0"`` and ``"cpu1"`` so the runtime startup emitter can synthesize
    ``_vectors_cpu0[]`` and ``_vectors_cpu1[]`` for the per-core VECBASE
    regions.  ``"shared"`` denotes vectors broadcast to both cores (NMI,
    double-fault) which appear in both per-core tables.
    """

    slot: int
    symbol_name: str
    interrupt: str | None
    kind: str
    provenance: Provenance
    core_affinity: str = field(default="cpu0", metadata={"omit_if_default": True})


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
class SystemClockProfile:
    """One typed system clock bring-up profile."""

    profile_id: str
    kind: str
    source_kind: str
    sysclk_hz: int
    provenance: Provenance
    hclk_hz: int | None = field(default=None, metadata={"omit_if_empty": True})
    apb1_hz: int | None = field(default=None, metadata={"omit_if_empty": True})
    apb2_hz: int | None = field(default=None, metadata={"omit_if_empty": True})
    pclk_hz: int | None = field(default=None, metadata={"omit_if_empty": True})
    source_hz: int | None = field(default=None, metadata={"omit_if_empty": True})
    ahb_prescaler: int | None = field(default=None, metadata={"omit_if_empty": True})
    apb1_prescaler: int | None = field(default=None, metadata={"omit_if_empty": True})
    apb2_prescaler: int | None = field(default=None, metadata={"omit_if_empty": True})
    oscillator_startup_cycles: int | None = field(
        default=None,
        metadata={"omit_if_empty": True},
    )
    mck_prescaler: int | None = field(default=None, metadata={"omit_if_empty": True})
    cpu_prescaler: int | None = field(default=None, metadata={"omit_if_empty": True})
    ipg_prescaler: int | None = field(default=None, metadata={"omit_if_empty": True})
    pll_m: int | None = field(default=None, metadata={"omit_if_empty": True})
    pll_n: int | None = field(default=None, metadata={"omit_if_empty": True})
    pll_p: int | None = field(default=None, metadata={"omit_if_empty": True})
    pll_q: int | None = field(default=None, metadata={"omit_if_empty": True})
    pll_r: int | None = field(default=None, metadata={"omit_if_empty": True})
    flash_latency: int | None = field(default=None, metadata={"omit_if_empty": True})


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
    channel_index: int | None = field(default=None, metadata={"omit_if_empty": True})
    request_value: int | None = field(default=None, metadata={"omit_if_empty": True})
    channel_selector: int | None = field(default=None, metadata={"omit_if_empty": True})


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
    channel_index: int | None = field(default=None, metadata={"omit_if_empty": True})
    request_value: int | None = field(default=None, metadata={"omit_if_empty": True})
    channel_selector: int | None = field(default=None, metadata={"omit_if_empty": True})


@dataclass(frozen=True, slots=True)
class DmaConflictGroup:
    """One explicit DMA route conflict group."""

    conflict_group_id: str
    route_ids: tuple[str, ...]
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class AltFunctionDescriptor:
    """One alternate-function entry on a GPIO pin.

    Captures `(af_number, signal_name, peripheral)` so the GPIO-semantics
    emitter can produce ``kValidAltFunctions`` arrays without re-resolving
    signal names against the peripheral list at emit time.
    """

    af_number: int
    signal_name: str
    peripheral: str


@dataclass(frozen=True, slots=True)
class GpioPinDescriptor:
    """Compile-time GPIO topology for one pin.

    Surfaces the facts needed by ``runtime_driver_semantics.gpio.hpp`` to
    populate the alternate-function fields of ``GpioSemanticTraits<PinId>``
    (``kPortOffset``, ``kPinIndex``, ``kMaxAltFunction``,
    ``kValidAltFunctions``). ``port`` is the GPIO peripheral / port name
    (``"GPIOA"``, ``"GPIO1"``, ``"PORTA"`` …); ``port_offset`` is the
    address offset from the family's first GPIO port, allowing alloy
    consumers to reach the port's register block via pointer arithmetic.

    ``alt_functions`` is sorted by ``(af_number, signal_name)`` so the
    emitted ``kValidAltFunctions`` array is also sorted ascending.
    """

    pin_id: str
    port: str
    pin_index: int
    port_offset: int
    alt_functions: tuple[AltFunctionDescriptor, ...]
    is_input_only: bool
    provenance: Provenance


@dataclass(frozen=True, slots=True)
class Rp2040UartPeripheralDescriptor:
    """Per-controller UART hardware facts (added by complete-rp2040-semantics).

    Surfaces the family-constant per-controller data — base address, FIFO
    depth, per-direction DMA DREQ values — plus the set of GPIO pads that
    can carry each UART signal.  ``valid_*_pins`` arrays are sorted
    ascending by pad number so consumer concept checks see a stable order.
    """

    controller_id: str
    base_address: int
    fifo_depth: int
    dreq_tx: int
    dreq_rx: int
    valid_tx_pins: tuple[int, ...]
    valid_rx_pins: tuple[int, ...]
    valid_cts_pins: tuple[int, ...]
    valid_rts_pins: tuple[int, ...]


@dataclass(frozen=True, slots=True)
class Rp2040SpiPeripheralDescriptor:
    """Per-controller SPI hardware facts (added by complete-rp2040-semantics).

    Mirrors ``Rp2040UartPeripheralDescriptor`` for SPI.  ``max_clock_hz`` is the
    silicon-level peripheral clock ceiling.
    """

    controller_id: str
    base_address: int
    max_clock_hz: int
    dreq_tx: int
    dreq_rx: int
    valid_mosi_pins: tuple[int, ...]
    valid_miso_pins: tuple[int, ...]
    valid_clk_pins: tuple[int, ...]
    valid_cs_pins: tuple[int, ...]


@dataclass(frozen=True, slots=True)
class Rp2040DmaControllerHwDescriptor:
    """Per-controller DMA hardware facts (added by complete-rp2040-semantics
    Phase D).  Captures silicon-fixed parameters that the existing
    ``DmaControllerDescriptor`` does not surface (channel count, max
    transfer count, chaining / byte-swap support)."""

    controller_id: str
    base_address: int
    channel_count: int
    max_transfer_count: int
    supports_chaining: bool
    supports_byte_swap: bool


@dataclass(frozen=True, slots=True)
class Rp2040TimerControllerHwDescriptor:
    """Per-controller timer hardware facts.  RP2040's single TIMER block
    has 64-bit counter + 4 hardware alarms with consecutive DMA DREQs."""

    controller_id: str
    base_address: int
    counter_bits: int
    alarm_count: int
    dreq_alarm_base: int  # ALARM0 DREQ; ALARMn DREQ = base + n


@dataclass(frozen=True, slots=True)
class Rp2040PwmSliceHwDescriptor:
    """One PWM slice (RP2040 has 8 slices, each with A/B channels).
    ``channel_a_pin`` / ``channel_b_pin`` carry the primary GPIO mapping
    (slice 0 → A=GP0, B=GP1; slice 7 → A=GP14, B=GP15)."""

    slice_index: int
    channel_a_pin: int
    channel_b_pin: int
    counter_bits: int
    clock_div_min_q4: int  # 1/16 of a count (fractional divider min)
    clock_div_max_q4: int  # 256 << 4 (fractional divider max)


@dataclass(frozen=True, slots=True)
class Rp2040AdcPeripheralDescriptor:
    """Per-controller ADC hardware facts (added by complete-rp2040-semantics
    Phase C).

    Captures the silicon-level fixed parameters for one ADC controller:
    base address, channel count, ADC resolution, the GPIO pad list that
    can route into each channel (sentinel ``255`` for the internal
    temperature sensor), DMA DREQ value, and the per-controller FIFO
    depth.
    """

    controller_id: str
    base_address: int
    channel_count: int
    resolution_bits: int
    channel_pins: tuple[int, ...]
    dreq: int
    fifo_depth: int
    supports_fifo: bool


@dataclass(frozen=True, slots=True)
class PioDescriptor:
    """Compile-time topology of one Programmable I/O block.

    Carries the facts needed by ``runtime_driver_semantics.pio.hpp`` to populate
    ``PioSemanticTraits<PioId>`` and ``StateMachineSemanticTraits<PioId, Sm>``
    specializations. Values are sourced from a vendor patch overlay (e.g.
    ``patches/raspberrypi/rp2040/pio.json``) — this dataclass is a thin
    pass-through.
    """

    pio_id: str
    base_address: int
    state_machine_count: int
    instruction_memory_depth: int
    tx_fifo_depth: int
    rx_fifo_depth: int
    gpio_base: int
    gpio_count: int
    dreq_tx_base: int
    dreq_rx_base: int
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
    system_clock_profiles: tuple[SystemClockProfile, ...] = field(
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
    # ADC Tier 2/3/4 (added by add-adc-tier-2-3-4-data).  Stored as tuples of
    # patch dataclasses (the IR layer is a thin pass-through; the typed C++
    # rendering happens in `runtime_driver_semantics`).  ``omit_if_empty`` so
    # devices without ADC config don't bloat the canonical IR JSON.
    adc_internal_channels: tuple[object, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    adc_calibration_data_points: tuple[object, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    adc_calibration_context: object | None = field(
        default=None,
        metadata={"omit_if_empty": True},
    )
    adc_resolution_options: tuple[object, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    adc_sample_time_options: tuple[object, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    adc_oversampling_options: tuple[object, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    adc_external_triggers: tuple[object, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    adc_max_clock_hz: int = field(default=0, metadata={"omit_if_default": True})
    # UART + SPI Tier 2/3/4 (added by add-uart-spi-tier-2-3-4-data).  Same
    # pass-through pattern as ADC: tuples of patch dataclasses, the typed
    # C++ rendering happens in ``runtime_driver_semantics``.  Empty for
    # families whose device patches don't curate the data.
    uart_baud_clock_sources: tuple[object, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    uart_baud_oversampling_options: tuple[object, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    uart_fifo_trigger_options: tuple[object, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    uart_data_bits_options: tuple[object, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    uart_parity_options: tuple[object, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    uart_stop_bits_options: tuple[object, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    uart_mode_flags: tuple[object, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    uart_max_baud_hz: int = field(default=0, metadata={"omit_if_default": True})
    spi_baud_prescaler_options: tuple[object, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    spi_frame_size_options: tuple[object, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    spi_fifo_threshold_options: tuple[object, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    spi_mode_flags: tuple[object, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    # Multi-core topology + APP_CPU control plane (added by
    # expose-xtensa-dual-core-facts).  ``multicore_topology`` defaults to
    # ``"single_core"`` so existing single-core fixtures keep validating
    # without changes.  ``app_cpu_control_plane`` is populated only for
    # asymmetric Xtensa devices (ESP32 classic + ESP32-S3); single-core
    # devices and symmetric dual-core devices (RP2040) carry ``None``.
    multicore_topology: MulticoreTopology = field(
        default="single_core", metadata={"omit_if_default": True}
    )
    app_cpu_control_plane: AppCpuControlPlane | None = field(
        default=None,
        metadata={"omit_if_empty": True},
    )
    # PIO block topology (added by define-pio-semantic-struct).  Empty for
    # devices without Programmable I/O hardware.
    pio_blocks: tuple[PioDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    # USB controller hardware-feature descriptors (added by
    # ``add-usb-semantic-traits``).  Populated only for devices with USB
    # hardware (STM32G0, STM32F4, RP2040, SAME70, ESP32-S3); empty tuple
    # everywhere else so existing fixtures stay byte-stable.
    usb_controllers: tuple[UsbControllerDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    # Hardware-feature descriptors added by ``fill-espressif-semantic-gaps``.
    # Empty tuples on devices whose family overlay doesn't ship the block
    # so existing fixtures stay byte-stable.
    uart_peripherals: tuple[UartPeripheralDescriptor, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    spi_peripherals: tuple[SpiPeripheralDescriptor, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    adc_units: tuple[AdcUnitDescriptor, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    timer_units: tuple[TimerUnitDescriptor, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    ledc: LedcDescriptor | None = field(default=None, metadata={"omit_if_empty": True})
    dma_channels: tuple[DmaChannelDescriptor, ...] = field(
        default_factory=tuple, metadata={"omit_if_empty": True}
    )
    # GPIO pin alternate-function topology (added by fill-gpio-semantic-gaps).
    # Empty for devices whose normalizers have not yet been wired to populate
    # GPIO topology; populated per family as the change rolls out.
    gpio_pins: tuple[GpioPinDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    # RP2040 per-controller hardware-feature descriptors (added by
    # complete-rp2040-semantics Phases B-D).  Coexist with the Espressif
    # ``uart_peripherals`` / ``spi_peripherals`` / etc. fields above
    # which use a different schema (peripheral_id + GPIO-matrix signal
    # indices).  All omit-if-empty.
    rp2040_uart_peripherals: tuple[Rp2040UartPeripheralDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    rp2040_spi_peripherals: tuple[Rp2040SpiPeripheralDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    rp2040_adc_peripherals: tuple[Rp2040AdcPeripheralDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    rp2040_dma_controller_hw: tuple[Rp2040DmaControllerHwDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    rp2040_timer_controller_hw: tuple[Rp2040TimerControllerHwDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )
    rp2040_pwm_slice_hw: tuple[Rp2040PwmSliceHwDescriptor, ...] = field(
        default_factory=tuple,
        metadata={"omit_if_empty": True},
    )

    def to_dict(self) -> dict[str, object]:
        return to_primitive(self)
