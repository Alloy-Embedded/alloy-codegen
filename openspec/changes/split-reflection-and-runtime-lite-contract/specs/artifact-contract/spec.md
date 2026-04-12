## ADDED Requirements

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
