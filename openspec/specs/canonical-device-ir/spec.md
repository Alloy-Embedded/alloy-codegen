# canonical-device-ir Specification

## Purpose
TBD - created by archiving change build-best-in-class-generator-core. Update Purpose after archive.
## Requirements
### Requirement: Canonical IR models full system-control fabric

Canonical IR MUST represent the device-level control graph required to explain and execute bring-up
and peripheral activation across vendors.

#### Scenario: System-control facts are explicit in canonical IR
- **WHEN** canonical IR is materialized for a supported device
- **THEN** it includes typed facts for clocks, resets, interrupts, and relevant power domains
- **AND** those facts are structured enough to derive bring-up and peripheral dependencies without
  reconstructing intent from unrelated low-level fields

### Requirement: Canonical IR models formal peripheral capabilities

Canonical IR MUST express runtime-relevant peripheral capabilities as first-class facts.

#### Scenario: Capabilities do not rely on downstream heuristics
- **WHEN** a supported runtime peripheral is represented in canonical IR
- **THEN** its supported features are available as typed capability facts
- **AND** Alloy does not need to infer them from schema strings or handwritten rules

### Requirement: Canonical IR preserves provenance for runtime-critical facts

Canonical IR MUST preserve enough provenance to explain how runtime-critical facts were produced.

#### Scenario: Emitted runtime facts can be traced back to origin
- **WHEN** a runtime fact is emitted from canonical IR
- **THEN** its origin can be traced to upstream source data, patch data, inference, or merge logic

### Requirement: Canonical IR SHALL Model Every Runtime Semantic Domain As Typed IDs

The canonical device IR SHALL model every semantic domain consumed by the Alloy runtime as
typed ids, enums, or typed refs rather than human-readable labels.

#### Scenario: Foundational device is normalized
- **WHEN** a foundational device is normalized into the canonical IR
- **THEN** backend schema, peripheral class, signal, signal role, route kind, requirement
  kind, operation kind, operation subject kind, memory kind, startup kind, package pad kind,
  and active level are represented by typed ids
- **AND** the runtime does not need semantic strings to understand those domains

### Requirement: Canonical IR SHALL Keep Human Labels Out Of Runtime C++ Payloads

The canonical device IR SHALL distinguish metadata labels from runtime contract fields so that
human-readable names are not required in runtime-facing C++ artifacts.

#### Scenario: Runtime-facing header is emitted
- **WHEN** a runtime-facing C++ artifact is emitted from the canonical IR
- **THEN** every executable semantic field can be emitted from typed ids, refs, and integers
- **AND** any human-readable labels remain available only in metadata or reports

### Requirement: Canonical IR encodes formal capability facts per peripheral instance

`CanonicalDeviceIR` MUST carry typed capability facts for every runtime-supported
peripheral instance, derived from IP block definitions and enriched by patches,
so that emitters can produce a capability manifest without heuristics or string parsing.

#### Scenario: Capability facts are available without downstream inference

- **WHEN** canonical IR is materialized for a device with a UART that supports DMA
- **THEN** the IR contains a `CapabilityDescriptor` for that UART with
  `capability_id: "uart.dma-tx"` and `value: "true"`
- **AND** the emitter reads this fact directly without querying other IR structures

#### Scenario: Missing capability is explicitly absent, not silently false

- **WHEN** a device's UART does not support hardware flow control
- **THEN** no `CapabilityDescriptor` with `capability_id: "uart.hardware-flow-control"`
  exists for that peripheral
- **AND** the capability manifest emitter treats absence as `false` and emits
  `kHasHardwareFlowControl = false` explicitly
- **AND** the absence is not indistinguishable from a missing patch

#### Scenario: Capability facts carry provenance

- **WHEN** a `CapabilityDescriptor` is present in canonical IR
- **THEN** its `provenance` field identifies whether it was sourced from an IP block
  definition, a device patch, or inferred from register structure
- **AND** the `alloy explain` CLI can surface this provenance on demand

### Requirement: Canonical IR encodes clock profile paths for code generation

`CanonicalDeviceIR` MUST contain enough clock graph structure for emitters to derive
complete, correct register-write sequences for at least two clock profiles per device
(default RC oscillator and maximum PLL frequency).

#### Scenario: PLL configuration parameters are available in the IR

- **WHEN** canonical IR is materialized for a device with a PLL
- **THEN** the clock node for the PLL contains multiplier range, divider range,
  VCO frequency bounds, and output clock node
- **AND** the emitter can derive the correct PLLCFGR/PLLCTRL register values
  without consulting the vendor datasheet directly

#### Scenario: Clock switch ordering is derivable from the graph

- **WHEN** canonical IR is materialized for a device
- **THEN** the clock dependency graph (`kClockDependencies`) is acyclic
- **AND** the correct enable-then-switch ordering is derivable by topological sort
  of the graph edges

### Requirement: Canonical IR preserves connector table facts with provenance

The pin-signal facts used to build `GpioConnector` specializations MUST be traceable
to their source SVD or patch entry, so that compiler error messages can cite origin.

#### Scenario: Every pin-signal binding has a traceable provenance

- **WHEN** a `PinSignal` entry exists in canonical IR for a peripheral-pin combination
- **THEN** its `provenance.source_id` identifies the SVD file or patch that declared it
- **AND** the connector table emitter can embed this provenance in the generated
  `static_assert` message for invalid combinations

#### Scenario: Absence of a binding is derivable, not assumed

- **WHEN** a given pin does not connect to a given peripheral signal on a device
- **THEN** no `PinSignal` entry exists in the IR for that combination
- **AND** the connector table emitter generates a `static_assert(false, ...)` for
  that combination with the correct list of valid alternatives from the same IR

### Requirement: Canonical IR SHALL Model Typed Runtime References

The canonical IR SHALL expose typed reference descriptors for every runtime-owned domain used
by Alloy backend execution, including registers, register fields, clock gates, resets,
selectors, interrupt bindings, DMA bindings, and route-operation targets.

#### Scenario: Foundational device is normalized for runtime consumption
- **WHEN** a foundational family device is normalized
- **THEN** its canonical IR includes stable typed IDs for runtime-owned registers and fields
- **AND** route operations reference typed targets instead of relying only on textual targets

### Requirement: Canonical IR SHALL Model Register Fields for Runtime-Owned Schemas

The canonical IR SHALL carry normalized register-field descriptors for runtime-owned backend
schemas so Alloy does not need handwritten bit offsets or widths.

#### Scenario: UART or GPIO backend consumes generated register field data
- **WHEN** a foundational UART or GPIO instance is normalized
- **THEN** the canonical IR includes field descriptors for the registers needed by that schema
- **AND** each field descriptor includes a typed register reference, bit offset, width, and
  access shape

### Requirement: Canonical IR SHALL Model Typed Peripheral Bindings

The canonical IR SHALL model interrupt, DMA, clock, reset, and selector bindings as typed
descriptors associated with peripheral instances.

#### Scenario: Peripheral instance is normalized
- **WHEN** a runtime-owned peripheral instance is emitted into the canonical IR
- **THEN** the instance can be connected to its interrupt, DMA, clock, reset, and selector
  domains through typed IDs
- **AND** the runtime does not need to reconstruct these bindings from names or CSV strings

