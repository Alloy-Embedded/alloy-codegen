## ADDED Requirements

### Requirement: Stage-Separated Source Ingestion
The system SHALL ingest upstream hardware description sources through an explicit source
stage that records provenance and produces deterministic fetch outputs.

#### Scenario: Fetch a bootstrap family reproducibly
- **WHEN** the user or CI runs the source fetch stage for the bootstrap family
- **THEN** the system SHALL acquire the configured upstream inputs into a controlled local
  source workspace
- **AND** it SHALL record a source manifest containing origin, revision, fetch time, and
  source identity
- **AND** rerunning the fetch stage against the same upstream revision SHALL produce the
  same manifest content except for explicitly versioned runtime metadata

#### Scenario: Source adapters isolate vendor-specific behavior
- **WHEN** the system ingests sources from a specific vendor or format
- **THEN** vendor-specific fetch and parsing behavior SHALL live in dedicated source adapter
  code
- **AND** downstream stages SHALL consume adapter outputs rather than calling vendor
  fetch/parsing logic directly

### Requirement: Source Scope Control
The source stage SHALL support scoped execution by vendor, family, and device.

#### Scenario: Restrict source fetch to one family
- **WHEN** the user requests source ingestion for a specific family
- **THEN** the system SHALL fetch only the sources needed for that family
- **AND** it SHALL NOT require a full multi-vendor fetch to bootstrap one family
