## ADDED Requirements

### Requirement: Dual Artifact Emission
The system SHALL emit both machine-readable metadata artifacts and generated C++ artifacts
from the same validated canonical IR.

#### Scenario: Metadata and C++ share one input revision
- **WHEN** the emit stage runs for a validated scope
- **THEN** metadata artifacts and generated C++ artifacts SHALL be derived from the same IR
  revision and manifest set
- **AND** they SHALL agree on device identity and scope

#### Scenario: Emitters do not perform semantic corrections
- **WHEN** an emitter encounters inconsistent or incomplete semantics
- **THEN** it SHALL fail or surface a validation error
- **AND** it SHALL NOT silently repair the problem inside the emitter

### Requirement: Stable Artifact Contract
The emitted artifact layout and manifests SHALL form a stable downstream contract.

#### Scenario: Artifacts include manifests and traceability
- **WHEN** artifacts are emitted for publication
- **THEN** they SHALL include generator version, IR schema version, source manifest
  reference, patch manifest reference, and artifact scope metadata
- **AND** downstream consumers SHALL be able to trace artifacts back to their inputs
