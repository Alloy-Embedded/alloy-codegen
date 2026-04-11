## ADDED Requirements

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
