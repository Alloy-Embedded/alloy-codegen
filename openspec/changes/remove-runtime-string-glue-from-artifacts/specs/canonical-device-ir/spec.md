## ADDED Requirements

### Requirement: Typed Runtime Reference Domains
The canonical device IR SHALL model runtime-owned references with typed domains and ids for
packages, pins, constraints, selectors, clock gates, resets, registers, and register fields.

#### Scenario: Foundational device carries typed refs
- **WHEN** a foundational device is normalized
- **THEN** its runtime-owned references are represented with typed ids
- **AND** the runtime contract does not require raw signal strings as the only executable
  source of truth

### Requirement: Diagnostic Strings Are Secondary
The canonical device IR SHALL treat any human-readable route or instance string as diagnostic
metadata only, not as a primary executable contract field.

#### Scenario: Runtime field has typed and diagnostic forms
- **WHEN** a route operation or instance binding keeps a human-readable label
- **THEN** the typed ids remain sufficient to execute the runtime behavior
- **AND** removing the diagnostic string would not make the route ambiguous to the runtime
