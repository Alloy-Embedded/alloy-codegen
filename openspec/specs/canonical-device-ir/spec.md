# canonical-device-ir Specification

## Purpose
TBD - created by archiving change build-best-in-class-generator-core. Update Purpose after archive.
## Requirements
### Requirement: Canonical IR models full system-control fabric

Canonical IR MUST represent the device-level control graph required to explain and execute bring-up
and peripheral activation across vendors.

#### Scenario: System-control facts are explicit in canonical IR
- **WHEN** canonical IR is materialized for a supported device
- **THEN** it includes typed facts for clocks, resets, interrupts, and relevant power domains
- **AND** those facts are structured enough to derive bring-up and peripheral dependencies without
  reconstructing intent from unrelated low-level fields

### Requirement: Canonical IR models formal peripheral capabilities

Canonical IR MUST express runtime-relevant peripheral capabilities as first-class facts.

#### Scenario: Capabilities do not rely on downstream heuristics
- **WHEN** a supported runtime peripheral is represented in canonical IR
- **THEN** its supported features are available as typed capability facts
- **AND** Alloy does not need to infer them from schema strings or handwritten rules

### Requirement: Canonical IR preserves provenance for runtime-critical facts

Canonical IR MUST preserve enough provenance to explain how runtime-critical facts were produced.

#### Scenario: Emitted runtime facts can be traced back to origin
- **WHEN** a runtime fact is emitted from canonical IR
- **THEN** its origin can be traced to upstream source data, patch data, inference, or merge logic

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

