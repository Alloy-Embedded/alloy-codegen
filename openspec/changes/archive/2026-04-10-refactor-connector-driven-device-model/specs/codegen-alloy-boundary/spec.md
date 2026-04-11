## ADDED Requirements

### Requirement: Codegen Emits `connect()` Descriptors, Alloy Implements `connect()` Behavior
`alloy-codegen` SHALL emit the descriptor data required for a generic `connect()` system, while
`alloy` SHALL remain responsible for the runtime and compile-time behavior that consumes those
descriptors.

#### Scenario: A user requests a typed peripheral connection in Alloy
- **WHEN** Alloy evaluates whether a requested set of pins can satisfy a peripheral connection
- **THEN** it SHALL consume codegen-emitted connector descriptors and capability data
- **AND** the logic that selects, validates, claims, and applies the connection SHALL remain
  handwritten in Alloy

### Requirement: Codegen Must Not Emit Runtime Ownership or Driver Policy
Generated artifacts SHALL remain descriptor-oriented and SHALL NOT introduce runtime ownership,
board policy, or public driver behavior.

#### Scenario: A generated artifact category is proposed for resource ownership
- **WHEN** a new generated header or translation unit is proposed for `alloy-codegen`
- **THEN** it MAY expose facts, compatibility data, addresses, vectors, or route operations
- **AND** it SHALL NOT implement token ownership, board initialization policy, or public peripheral
  driver APIs
