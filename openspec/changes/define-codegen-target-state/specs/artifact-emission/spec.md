## ADDED Requirements

### Requirement: Descriptor-First Artifact Emission
The emit stage SHALL publish hardware descriptors and machine-readable metadata, not runtime HAL
behavior.

#### Scenario: Generated C++ remains descriptor-oriented
- **WHEN** the emit stage generates C++ artifacts for future Alloy consumption
- **THEN** those artifacts SHALL expose addresses, tables, identifiers, compatibility data,
  startup descriptors, or other hardware facts
- **AND** they SHALL NOT implement public runtime drivers or behavioral policies

#### Scenario: Metadata and generated C++ stay aligned
- **WHEN** emitted metadata and emitted C++ describe the same family or device
- **THEN** they SHALL be derived from the same validated IR revision
- **AND** they SHALL agree on device identity, peripheral identity, and connectivity facts

### Requirement: Complete Artifact Set for Alloy Consumption
The emit stage SHALL provide the artifact categories required for the future Alloy architecture.

#### Scenario: Family artifacts include metadata, reports, and generated descriptors
- **WHEN** a family is emitted for publication
- **THEN** the artifact set SHALL include family manifest data, machine-readable metadata,
  validation/report artifacts, and generated C++ descriptor artifacts

#### Scenario: Device artifacts include startup and connectivity descriptors
- **WHEN** a publishable device artifact set is emitted
- **THEN** it SHALL include device-level register, pin-function, and startup descriptor artifacts
- **AND** Alloy SHALL not need to reconstruct those hardware facts from raw vendor sources
