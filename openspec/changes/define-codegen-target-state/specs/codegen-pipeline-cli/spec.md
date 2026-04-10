## ADDED Requirements

### Requirement: Generic Source Override Interface
The CLI SHALL expose a generic source override interface keyed by logical source IDs.

#### Scenario: One family overrides multiple source IDs
- **WHEN** a user or CI targets a family backed by more than one logical source product
- **THEN** the CLI SHALL allow each source product to be overridden independently by source ID
- **AND** those overrides SHALL be visible in structured command output

### Requirement: Machine-Readable Publishability Output
The CLI SHALL expose family publishability status as machine-readable output.

#### Scenario: CI decides draft versus publishable from CLI output
- **WHEN** validation or publish is run in CI for a family
- **THEN** the structured CLI output SHALL identify whether that family is draft or publishable
- **AND** downstream automation SHALL be able to gate publication from that result without parsing
  human-oriented log text
