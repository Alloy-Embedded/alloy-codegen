## ADDED Requirements

### Requirement: Foundational Publish SHALL Fail Without Runtime-Lite Coverage

Foundational family publication SHALL fail when runtime-lite artifacts do not provide the data
needed for foundational runtime-owned drivers.

#### Scenario: Missing runtime-lite route lowering blocks publication

- **WHEN** a foundational family lacks runtime-lite route data for a published UART or GPIO path
- **THEN** the publish stage fails before publication

### Requirement: Foundational Publish SHALL Fail When Runtime-Lite Depends On Reflection Lookup

Foundational family publication SHALL fail when the emitted runtime-lite contract still requires
reflection-style family table lookup as the normal runtime usage model.

#### Scenario: Family emits only reflective connector graph

- **WHEN** the generated output exposes only reflection connector tables for a foundational
  runtime-owned use case
- **THEN** validation marks the runtime-lite contract incomplete
- **AND** publication is blocked
