## ADDED Requirements

### Requirement: Runtime Headers SHALL Expose Typed Binding Contracts

The emitted C++ artifact contract SHALL expose typed binding descriptors for peripheral
instances, registers, fields, interrupts, DMA, and connector operations.

#### Scenario: Alloy imports generated runtime headers
- **WHEN** Alloy includes the runtime-facing headers for a device
- **THEN** it can discover peripheral bindings, register IDs, field IDs, interrupt bindings,
  and DMA bindings through typed descriptors
- **AND** it does not need to parse comma-separated payloads to recover relationships

### Requirement: Register and Field Headers SHALL Be Published for Runtime-Owned Schemas

The emitted device-scoped artifacts SHALL include register and field descriptor headers for
runtime-owned backend schemas in foundational families.

#### Scenario: Foundational device is published
- **WHEN** a foundational family device is published to `alloy-devices`
- **THEN** its generated artifact tree includes `register_map.hpp` and `register_fields.hpp`
- **AND** those headers provide enough information for Alloy to address registers and fields
  without handwritten offsets

### Requirement: Connector and Clock Artifacts SHALL Use Structured Arrays

Connector and clock artifacts SHALL publish structured arrays and typed identifier references
as the primary runtime interface.

#### Scenario: Route operation and selector descriptors are emitted
- **WHEN** `connector_tables.hpp` and `clock_tree_lite.hpp` are emitted
- **THEN** candidate, group, selector, gate, reset, and operation relationships are encoded
  through typed IDs and structured rows
- **AND** any human-readable strings are secondary diagnostics rather than required runtime
  inputs
