## Context

The `alloy-codegen` bootstrap implementation has already proven several important things:

- source-bundle based ingestion works for ST and Microchip
- deterministic publish into `alloy-devices` works
- Alloy smoke-consumer verification can be performed against published descriptors

What it has **not** proven yet is the final shape of the hardware model. The current IR is still
best described as "bootstrap connectivity plus useful device facts". That is not enough for the
future Alloy architecture, whose core differentiator is:

- descriptor-first and auditable codegen
- clear simple/expert API split in Alloy
- compile-time-safe peripheral bring-up through a generic `connect()` layer

The new model must therefore be driven by one rule:

> The codegen must describe all the facts required to answer hardware questions, but it must not
> implement the user-facing behavior that consumes those facts.

## Goals / Non-Goals

### Goals

- Replace the AF-centric connectivity model with a route-driven connector model that works across
  ST, Microchip, and NXP
- Separate `ip_block` facts from `peripheral instance` facts
- Model package and pad topology strongly enough to support package-aware connection validation
- Model interrupts, memory, startup, clock/reset/enable, and DMA as first-class canonical domains
- Emit every descriptor family the future Alloy runtime needs from `alloy-devices`
- Keep the boundary explicit:
  - `alloy-codegen` emits facts, compatibility data, and descriptor translation units
  - `alloy` implements runtime `connect()`, ownership, and behavioral policies
- Force the same descriptor contract through ST, Microchip, and NXP before vendor 4

### Non-Goals

- Generating runtime `Uart`, `Spi`, `I2c`, or `Gpio` classes
- Generating ownership tokens, singleton claims, or board policies
- Building a full clock-tree solver for every family
- Encoding vendor quirks directly in final emitters
- Adding vendor 4 before the foundational three vendor shapes pass

## Design Principles

### 1. Connectivity is a route graph, not an AF number

The canonical question is not:

- "what AF number does this pin use?"

The canonical question is:

- "which concrete hardware route makes this pin satisfy this peripheral signal?"

That distinction matters because:

- ST often expresses routes as alternate functions
- Microchip may express routes through PIO/peripheral matrix selections
- NXP may require mux selectors, input daisy selectors, and pad configuration facts

The IR must treat all three as instances of the same abstract concept: a route candidate.

### 2. IP capability is versioned separately from instance placement

An `ip_version` describes what a block can do.
An instance describes where that block lives in a specific device and how it is connected to the
rest of the chip.

That separation is required to:

- deduplicate logic across devices
- make capability descriptors reusable
- prevent emitters from reverse-engineering capability from instance names

### 3. Package topology is part of correctness

Compile-time-safe `connect()` requires knowing more than pin names.

The pipeline must know:

- which physical pads exist in a package
- which pins are bonded in a given package variant
- which pads are power/ground/reset/debug-only
- which pins carry additional constraints

Without that, the final `connect()` contract cannot be trusted.

### 4. Startup data belongs in descriptors; startup logic belongs in Alloy

The codegen must emit:

- vector slot data
- memory-region data
- copy/zero/init descriptors
- device-specific startup constants

The Alloy runtime must still own:

- reset handler behavior
- section initialization algorithm
- weak handler policies

### 5. Clock modeling should be "enough to initialize safely"

The target is not a full vendor clock planner in phase one.
The target is a `ClockGraphLite` that can answer:

- what must be enabled
- what can be reset
- which parent/source choices exist
- which minimal selector/divider facts Alloy needs for bring-up

That is sufficient for the first driver families and prevents the clock domain from remaining a
handwritten gap.

## Target Canonical Model

The bootstrap `CanonicalDeviceIR` is replaced by a richer device model composed of reusable
sub-domains.

### Identity and provenance

- `VendorIdentity`
- `FamilyIdentity`
- `DeviceIdentity`
- `PackageVariant`
- `Provenance`
- `SourceReference`
- `PatchReference`

Every emitted fact must remain traceable to source and patch identity.

### IP blocks and capabilities

- `IpBlockDefinition`
  - `ip_name`
  - `ip_version`
  - `peripheral_class`
  - `register_profile`
  - `signal_roles`
  - `capability_ids`
  - `provenance`
- `CapabilityDescriptor`
  - class-scoped capabilities such as FIFO, DMA support, CTS/RTS, channel count, pad control,
    daisy-routing support, etc.
- `PeripheralInstance`
  - `name`
  - `instance_index`
  - `ip_block_ref`
  - `base_address`
  - `address_space`
  - `clock_binding_ref`
  - `reset_binding_ref`
  - `interrupt_refs`
  - `dma_refs`
  - `instance_capability_overrides`

### Package and pin topology

- `PackageVariant`
  - `package_id`
  - `package_name`
  - `package_kind`
  - `pad_count`
  - `dimensions_or_pitch` when known
- `PackagePad`
  - `pad_id`
  - `position_label`
  - `physical_index`
  - `pad_kind`
  - `bonded_pin_ref`
- `PinDescriptor`
  - `pin_id`
  - `canonical_name`
  - `port`
  - `number`
  - `package_pad_refs`
  - `constraint_ids`
- `PinConstraint`
  - reserved
  - NC
  - analog-only
  - debug-only
  - wakeup-only
  - open-drain-only
  - voltage domain constraints

### Route-driven connector model

- `SignalEndpoint`
  - canonical peripheral-side signal identity such as `tx`, `rx`, `sck`, `sda`, `ch0`, `tioa0`
- `ConnectionCandidate`
  - one concrete valid route from `pin -> peripheral instance signal`
  - contains:
    - `candidate_id`
    - `pin_ref`
    - `peripheral_ref`
    - `signal_ref`
    - `route_kind`
    - `route_selector`
    - `route_group_id`
    - `requirement_ids`
    - `operation_ids`
    - `provenance`
- `ConnectionGroup`
  - a valid set of candidates that may coexist for one connectable configuration
  - encodes:
    - required signals
    - mutually exclusive candidates
    - package restrictions
    - instance restrictions
- `RouteRequirement`
  - required enable/reset/source/package facts for a candidate or group
- `RouteOperation`
  - low-level hardware operations needed to materialize a route
  - examples:
    - write mux field
    - write input daisy field
    - write pad control field
    - enable peripheral clock gate
    - clear reset line

This is the core abstraction that lets Alloy implement one generic `connect()` API over three
different vendor source shapes.

### Interrupt domain

- `InterruptDescriptor`
  - `interrupt_id`
  - `name`
  - `line`
  - `owner_peripheral_ref`
  - `shared_group`
  - `alias_names`
- `VectorSlotDescriptor`
  - `slot_index`
  - `symbol_name`
  - `interrupt_ref | system_exception_kind`

### Memory and startup domain

- `MemoryRegion`
  - flash, sram, itcm, dtcm, backup, otp, etc.
- `StartupCopyDescriptor`
- `StartupZeroDescriptor`
- `StartupSectionDescriptor`
- `StartupVectorDescriptor`
- `StartupDeviceDescriptor`

The output must be rich enough for Alloy to implement startup behavior without any vendor-local
handwritten tables.

### Clock/reset/enable domain

- `ClockNodeLite`
  - root, parent, derived node type
- `ClockSelectorLite`
  - available parents and selector values
- `ClockGateDescriptor`
  - enable target and required parent
- `ResetDescriptor`
  - reset target and polarity
- `PeripheralClockBinding`
  - how a peripheral instance is tied into `ClockGraphLite`

This is intentionally limited to "bring-up sufficient". Full clock-tree solving remains out of
scope for this change.

### DMA domain

- `DmaControllerDescriptor`
- `DmaRequestDescriptor`
- `DmaRouteDescriptor`
- `DmaConflictGroup`

## Generic `connect()` Contract

This change does **not** implement `connect()` inside the codegen.
It defines what Alloy will later consume.

### Codegen responsibilities

The codegen must emit:

- canonical connector metadata
- generated connector tables
- route operations
- route requirements
- capability descriptors
- package-aware compatibility facts

### Alloy responsibilities

Alloy later implements:

1. selection of requested peripheral and signal roles
2. compile-time validation that at least one `ConnectionGroup` satisfies the request
3. compile-time rejection of impossible or conflicting pin combinations
4. resource ownership and claim logic
5. execution of route operations and clock/reset actions

### Result

The Alloy API can be generic while the data remain vendor-specific and descriptor-first.

## Target Emitted Artifacts

The change fills in the missing descriptor families needed by the target-state contract.

### `metadata/`

- `metadata/family-index.json`
- `metadata/family-connectivity.json`
- `metadata/ip-blocks.json`
- `metadata/capabilities.json`
- `metadata/packages.json`
- `metadata/interrupt-map.json`
- `metadata/memory-map.json`
- `metadata/clock-reset-map.json`
- `metadata/dma-map.json`
- `metadata/connectors.json`
- `metadata/docs.json`
- `metadata/devices/<device>.json`
- family root `manifest.json`

### `generated/`

- `generated/peripherals/<peripheral>.hpp`
- `generated/ip/<ip-version>.hpp`
- `generated/connector_tables.hpp`
- `generated/interrupt_map.hpp`
- `generated/memory_map.hpp`
- `generated/package_map.hpp`
- `generated/clock_tree_lite.hpp`
- `generated/rcc_map.hpp`
- `generated/dma_map.hpp`
- `generated/devices/<device>/register_map.hpp`
- `generated/devices/<device>/startup_descriptors.hpp`
- `generated/devices/<device>/startup_vectors.cpp`

### `reports/`

- `reports/validation-summary.json`
- `reports/coverage.json`
- `reports/publication-record.json`

## Validation Strategy

### Connector graph validators

The validator must prove:

- every `ConnectionCandidate` references known pins, peripherals, signals, and route ops
- every `ConnectionGroup` references only compatible candidates
- required signals are satisfiable
- package restrictions are respected
- route conflicts are explicit and machine-readable

### System descriptor validators

The validator must prove:

- interrupt ownership and vector coverage are complete
- memory regions are non-overlapping where required
- startup descriptors are sufficient for emitted startup data
- peripheral clock and reset bindings exist when needed
- DMA requests and conflicts are explicit

### Cross-vendor validators

The validator must prove that ST, Microchip, and NXP all satisfy the same descriptor categories.
No vendor may bypass the route model or publishability gates through emitter exceptions.

## Migration Plan

### Phase 1: schema and dual-model transition

- add the new descriptor types alongside the current bootstrap IR
- keep the current artifact set temporarily while new emitters are added
- mark the old `PinSignal.af_number` model as transitional

### Phase 2: connector-first emission

- emit connector metadata and generated connector headers
- switch validation to gate publication on route completeness

### Phase 3: system-descriptor completion

- emit interrupt, memory, package, startup, and clock-lite descriptors
- make publication depend on these descriptors rather than handwritten bootstrap gaps

### Phase 4: family closure

- migrate `stm32g0` first
- then complete `same70`
- then complete `imxrt1060`

### Phase 5: legacy removal

- remove legacy AF-centric emitter assumptions
- remove transitional compatibility fields once all foundational families emit the new contract

## Risks / Trade-offs

- **Risk: the IR refactor is large and touches almost every stage**
  - Mitigation: allow a dual-model transition and gate removal of legacy fields on family closure

- **Risk: connector groups become too abstract**
  - Mitigation: force route operations, requirements, and provenance to remain explicit and
    vendor-auditable

- **Risk: clock modeling expands too far**
  - Mitigation: keep this change limited to `ClockGraphLite`, sufficient for enable/reset/source
    selection only

- **Risk: vendor-specific quirks leak into emitters**
  - Mitigation: corrections stay in normalization and patches; emitters remain descriptor-only

- **Risk: NXP implementation starts before the model is stable**
  - Mitigation: block final `add-nxp-mcux-family` completion until this change lands

## Resolved Design Decisions

- `pin_functions.hpp` and `signal_map.hpp` are retired; `connector_tables.hpp` is the only
  pin-level connectivity artifact (C1.1 / I.1 closed)
- `startup.cpp` (`kInterruptTable`) is retired; `startup_descriptors.hpp` + `startup_vectors.cpp`
  are the final startup artifacts (I.2 closed)
- `clock_tree_lite.hpp` coexists with `rcc_map.hpp` during the transition; `rcc_map.hpp` remains
  as the flat peripheral clock/reset convenience table
- Device-local startup is split: `startup_descriptors.hpp` (rich descriptor data) and
  `startup_vectors.cpp` (descriptor-only vector translation unit)
