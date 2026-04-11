## ADDED Requirements

### Requirement: Foundational Runtime Descriptor Completeness

The validation pipeline SHALL treat backend schema coverage, typed route operations, and
register descriptor coverage as foundational publication requirements.

#### Scenario: Publish blocks on missing backend schema coverage

- **WHEN** a foundational family includes a runtime-owned peripheral class without backend schema coverage
- **THEN** validation marks the runtime contract incomplete
- **AND** publish is blocked for that scope

#### Scenario: Publish blocks on missing normalized register offsets

- **WHEN** a foundational family omits normalized register descriptors for runtime-owned peripherals
- **THEN** validation marks the runtime contract incomplete
- **AND** publish is blocked for that scope
