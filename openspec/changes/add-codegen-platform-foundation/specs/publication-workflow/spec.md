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

### Requirement: Remote Publication Automation
The system SHALL support CI orchestration that commits validated publication outputs into the
real `alloy-devices` repository only when the materialized artifact tree changes.

#### Scenario: Remote publication commits only changed validated outputs
- **WHEN** CI publishes a validated scope into a clean `alloy-devices` checkout
- **AND** the resulting materialized tree differs from the target branch contents
- **THEN** CI SHALL create a deterministic commit representing only the published artifact
  changes
- **AND** CI SHALL push that commit only when dedicated publication credentials are
  configured

#### Scenario: Remote publication is a no-op when outputs already match
- **WHEN** CI publishes a validated scope into a clean `alloy-devices` checkout
- **AND** the resulting materialized tree matches the target branch contents
- **THEN** CI SHALL avoid creating or pushing a no-op commit
