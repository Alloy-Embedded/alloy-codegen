## ADDED Requirements

### Requirement: Publishable Family Gate
The validation system SHALL distinguish clearly between draft families and publishable families.

#### Scenario: Draft family can normalize but cannot publish
- **WHEN** a family normalizes successfully but still lacks closed semantics in package, clock,
  DMA, interrupt, memory, or startup-critical domains
- **THEN** validation SHALL mark that family as draft
- **AND** publication SHALL remain blocked for that family

#### Scenario: Publishable family passes machine-readable gates
- **WHEN** a family satisfies all publishability-critical semantic checks
- **THEN** validation SHALL emit a machine-readable result marking that family publishable
- **AND** the publish stage SHALL be allowed to release its artifacts

### Requirement: Foundational Vendor Gate
The system SHALL require the foundational vendor set to pass on the same generic architecture
before vendor 4 enters active implementation.

#### Scenario: Vendor 4 remains blocked until the foundational set closes
- **WHEN** ST, Microchip, and NXP do not yet each have at least one publishable family on the
  common artifact and IR contract
- **THEN** vendor 4 SHALL remain blocked from active implementation scope

#### Scenario: Foundational families prove genericity before expansion
- **WHEN** the foundational families close their publishable-family gates and complete repeated
  stable publication cycles
- **THEN** the system MAY admit vendor 4 proposals for implementation
- **AND** those proposals SHALL reuse the same source-bundle, IR, validation, and publication
  contracts
