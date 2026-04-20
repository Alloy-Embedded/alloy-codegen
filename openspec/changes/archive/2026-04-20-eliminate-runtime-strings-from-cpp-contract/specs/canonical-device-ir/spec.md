## ADDED Requirements

### Requirement: Canonical IR SHALL Model Every Runtime Semantic Domain As Typed IDs

The canonical device IR SHALL model every semantic domain consumed by the Alloy runtime as
typed ids, enums, or typed refs rather than human-readable labels.

#### Scenario: Foundational device is normalized
- **WHEN** a foundational device is normalized into the canonical IR
- **THEN** backend schema, peripheral class, signal, signal role, route kind, requirement
  kind, operation kind, operation subject kind, memory kind, startup kind, package pad kind,
  and active level are represented by typed ids
- **AND** the runtime does not need semantic strings to understand those domains

### Requirement: Canonical IR SHALL Keep Human Labels Out Of Runtime C++ Payloads

The canonical device IR SHALL distinguish metadata labels from runtime contract fields so that
human-readable names are not required in runtime-facing C++ artifacts.

#### Scenario: Runtime-facing header is emitted
- **WHEN** a runtime-facing C++ artifact is emitted from the canonical IR
- **THEN** every executable semantic field can be emitted from typed ids, refs, and integers
- **AND** any human-readable labels remain available only in metadata or reports
