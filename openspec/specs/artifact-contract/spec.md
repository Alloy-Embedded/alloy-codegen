# artifact-contract Specification

## Purpose
TBD - created by archiving change build-best-in-class-generator-core. Update Purpose after archive.
## Requirements
### Requirement: Published runtime contract exposes system-control fabric

The supported runtime C++ contract MUST publish typed device-scoped system-control facts needed by
Alloy and advanced consumers.

#### Scenario: Runtime contract includes interrupts, resets, and clock dependencies
- **WHEN** a foundational device is published
- **THEN** its runtime contract exposes typed interrupt facts, reset-control facts, and clock
  dependency facts
- **AND** those facts live under `generated/runtime/devices/<device>/`

### Requirement: Published runtime contract exposes formal capabilities

The supported runtime C++ contract MUST expose formal capability descriptors for runtime-supported
peripherals.

#### Scenario: Capabilities are published as supported contract facts
- **WHEN** a foundational device is published
- **THEN** runtime-supported peripherals publish typed capability facts
- **AND** those facts are queryable without legacy reflection artifacts

### Requirement: Publication emits explainability and provenance reports

Publication MUST emit machine-readable explainability and provenance outputs for runtime-critical
generated facts.

#### Scenario: Publication reports explain emitted facts
- **WHEN** a foundational family is published
- **THEN** reports identify the source, patch, or inference path behind runtime-critical facts
- **AND** they explicitly mark unsupported or heuristic coverage

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

### Requirement: Reflection Headers MUST Not Be The Default Runtime Boundary

Headers such as connector graphs, clock maps, and other family-wide reflective inventories SHALL
be documented and emitted as reflection artifacts. They SHALL NOT be the primary hot-path
contract for `alloy`.

#### Scenario: Generated layout distinguishes contract purpose

- **WHEN** a consumer inspects the emitted tree
- **THEN** reflection-oriented artifacts and runtime-lite artifacts are distinguishable by path
  or naming convention

### Requirement: Runtime-Lite Headers SHALL Be Minimal And Compile-Time Oriented

Runtime-lite headers SHALL publish only the information required for runtime-owned hot-path
consumption, using typed ids, refs, trait specializations, and compact `constexpr` data.

#### Scenario: Runtime-lite peripheral instance header avoids reflection payload

- **WHEN** a device-scoped runtime-lite peripheral instance header is emitted
- **THEN** it exposes instance-local typed data needed by the runtime
- **AND** it does not require human-readable reflective payload to be usable

