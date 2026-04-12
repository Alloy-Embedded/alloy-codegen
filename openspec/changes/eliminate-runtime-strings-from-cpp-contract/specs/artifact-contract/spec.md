## ADDED Requirements

### Requirement: Runtime C++ Artifact Contract SHALL Be Zero-String

All runtime-consumed generated C++ artifacts SHALL expose no semantic string fields.

#### Scenario: Alloy includes generated runtime headers
- **WHEN** Alloy includes runtime-facing generated C++ headers from `alloy-devices`
- **THEN** the consumed structs and tables contain only enums, ids, refs, addresses, offsets,
  widths, masks, counts, and integral values
- **AND** they do not contain semantic `const char*` fields such as schema names, kind names,
  signal names, package names, or register names

### Requirement: Runtime Maps and Bindings SHALL Use Typed IDs Only

Family maps and device-scoped bindings SHALL use typed ids only for runtime relationships.

#### Scenario: Alloy consumes peripheral, interrupt, DMA, pin, and package bindings
- **WHEN** the runtime reads `rcc_map.hpp`, `interrupt_map.hpp`, `dma_map.hpp`, `pins.hpp`,
  `package_map.hpp`, or device-scoped binding headers
- **THEN** those relationships are encoded with typed ids or refs
- **AND** no semantic string parsing is required

### Requirement: IP and Capability Headers SHALL Be Fully Typed

Runtime-consumed IP and capability headers SHALL publish typed profile information without
semantic string fields.

#### Scenario: Alloy dispatches on an IP profile
- **WHEN** Alloy consumes `generated/ip/*.hpp` or capability overlays
- **THEN** it can identify backend schema, peripheral class, and signal roles from typed ids
- **AND** it does not need textual labels to dispatch behavior
