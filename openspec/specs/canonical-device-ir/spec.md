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

