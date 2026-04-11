## ADDED Requirements

### Requirement: Validators Prove Connector Graph Consistency
Validation SHALL prove that the connector graph is internally consistent and sufficient for
compile-time-safe `connect()` behavior in Alloy.

#### Scenario: A connection group references incompatible or conflicting candidates
- **WHEN** connector candidates, groups, requirements, or route operations disagree about which
  signals may coexist or what resources they require
- **THEN** validation SHALL fail the family publishability gate
- **AND** the failure output SHALL identify the conflicting connector facts machine-readably

### Requirement: Validators Prove System Descriptor Completeness
Validation SHALL prove that interrupt, memory, startup, clock/reset, package, and DMA descriptor
domains are complete enough for publication.

#### Scenario: A family lacks startup vectors or clock bindings for a published peripheral
- **WHEN** a publishability-critical system descriptor is missing or inconsistent
- **THEN** validation SHALL block publication automatically
- **AND** the report SHALL identify which descriptor domain is still draft

### Requirement: Foundational Vendors Share the Same Publishability Gates
ST, Microchip, and NXP foundational families SHALL pass the same descriptor completeness and
connector safety gates before vendor 4 support is admitted.

#### Scenario: A vendor-specific path requests an exception to the descriptor contract
- **WHEN** a foundational family cannot satisfy a required descriptor category on the shared model
- **THEN** the family SHALL remain non-publishable
- **AND** the pipeline SHALL NOT bypass the gate through emitter-specific exceptions
