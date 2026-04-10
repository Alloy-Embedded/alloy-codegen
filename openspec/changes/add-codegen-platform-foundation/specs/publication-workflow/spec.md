## ADDED Requirements

### Requirement: Validated Publication Workflow
The system SHALL publish artifacts to `alloy-devices` only from validated, gated pipeline
states.

#### Scenario: Publication requires passing gates
- **WHEN** the publish stage is requested
- **THEN** it SHALL verify that all required gates for the targeted publication scope are
  passing
- **AND** if a required gate is failing, publication SHALL stop before modifying
  `alloy-devices`

#### Scenario: Publication records release provenance
- **WHEN** a publication succeeds
- **THEN** the publication record SHALL identify the generator revision, manifest set,
  validation outcome, and target artifact revision written to `alloy-devices`

### Requirement: Deterministic Publication
The publication workflow SHALL be deterministic for the same validated inputs.

#### Scenario: Re-publishing identical validated inputs does not drift
- **WHEN** the same validated scope is published twice without input changes
- **THEN** the produced artifact contents SHALL be byte-equivalent
- **AND** any revision metadata differences SHALL be explicitly versioned rather than hidden
