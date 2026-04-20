## ADDED Requirements

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
