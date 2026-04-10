## ADDED Requirements

### Requirement: Generic Named Source Overrides
The CLI SHALL expose a generic mechanism for overriding upstream source inputs by logical source
ID.

#### Scenario: Override multiple sources for one family
- **WHEN** the user runs `fetch`, `normalize`, `validate`, `emit`, `publish`, or `pipeline` for a
  family with composite inputs
- **THEN** the CLI SHALL allow overriding each logical source input independently by source ID
- **AND** those overrides SHALL be visible in structured command output and source manifests

#### Scenario: Legacy special-case source flags are deprecated
- **WHEN** the system still supports older vendor-specific source flags during migration
- **THEN** the CLI SHALL surface a clear deprecation path toward the generic named-source model
- **AND** new vendor support SHALL be implemented only through the generic mechanism
