## ADDED Requirements

### Requirement: Multi-Layer Validation
The system SHALL validate data in multiple layers before emission or publication.

#### Scenario: Validate schema and semantics separately
- **WHEN** validation runs for a targeted scope
- **THEN** it SHALL perform schema validation and semantic validation as distinct checks
- **AND** validation reports SHALL distinguish structural failures from semantic failures

#### Scenario: Semantic validation covers connectivity-critical domains
- **WHEN** validation runs for a supported family
- **THEN** it SHALL validate at least pins, alternate functions, packages, RCC, interrupts,
  and DMA routing for critical conflicts and missing required relationships

### Requirement: Hard Maturity Gates
The system SHALL enforce explicit maturity gates that block progression to later phases.

#### Scenario: Publication is blocked before semantic closure
- **WHEN** Gate C has not passed for a targeted family
- **THEN** publication of family artifacts SHALL be blocked
- **AND** emit outputs SHALL be considered non-publishable draft artifacts only

#### Scenario: Family expansion is blocked before artifact maturity
- **WHEN** Gate D has not passed for the bootstrap family
- **THEN** a second major family SHALL NOT enter active support scope
- **AND** CI and planning SHALL treat further family expansion as blocked work

### Requirement: Machine-Readable Validation Reports
Validation results SHALL be emitted in machine-readable form for CI, tooling, and
publication decisions.

#### Scenario: CI consumes validation status
- **WHEN** validation completes in CI
- **THEN** it SHALL emit a structured report including scope, rule results, severity, and
  gate status
- **AND** CI SHALL use that report to determine pass/fail decisions
