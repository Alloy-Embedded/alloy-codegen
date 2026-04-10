## ADDED Requirements

### Requirement: Canonical Device IR
The system SHALL define a versioned canonical intermediate representation (IR) that is the
single source of truth for validation, emission, and publication.

#### Scenario: Canonical IR models core hardware domains
- **WHEN** a device is normalized successfully
- **THEN** the canonical IR SHALL represent at least:
  device identity, family, packages, pins, alternate functions, IP blocks, register blocks,
  interrupts, DMA routing, RCC/clock/reset relationships, memory regions, and provenance

#### Scenario: IR is versioned explicitly
- **WHEN** normalized output is written or emitted
- **THEN** it SHALL declare the IR schema version explicitly
- **AND** any incompatible schema change SHALL require a breaking change proposal

### Requirement: IR-First Downstream Consumption
Downstream stages SHALL consume canonical IR rather than raw sources or ad-hoc intermediate
structures.

#### Scenario: Emitters read IR only
- **WHEN** the emit stage generates metadata or C++ artifacts
- **THEN** it SHALL consume validated canonical IR as input
- **AND** it SHALL NOT read vendor raw sources directly to recover missing semantics

#### Scenario: Validators read IR and manifests
- **WHEN** the validate stage runs semantic checks
- **THEN** it SHALL operate on canonical IR plus recorded provenance and manifest data
- **AND** it SHALL NOT require emit-stage outputs to determine core correctness
