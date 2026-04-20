# validation-and-gates Specification

## Purpose
TBD - created by archiving change build-best-in-class-generator-core. Update Purpose after archive.
## Requirements
### Requirement: Publish proves deterministic runtime publication

Foundational publication MUST prove that identical inputs produce the same materialized runtime
tree.

#### Scenario: Repeated publish yields the same tree revision
- **WHEN** the same foundational family is published twice with the same sources and patches
- **THEN** the materialized publication tree revision is identical

### Requirement: Publish fails on missing semantic completeness

Foundational publication MUST fail when the runtime contract is semantically incomplete.

#### Scenario: Missing system-control coverage blocks publish
- **WHEN** a foundational family lacks required runtime interrupt, reset, clock, or power facts
- **THEN** publish fails

#### Scenario: Missing capability coverage blocks publish
- **WHEN** a runtime-supported foundational peripheral lacks formal capability coverage
- **THEN** publish fails

### Requirement: Consumer verification compiles the semantic moat

Consumer verification MUST compile the new runtime semantic layers directly.

#### Scenario: Consumer smoke covers system-control and capability contracts
- **WHEN** consumer verification runs for a foundational device
- **THEN** it compiles the typed runtime contracts for system-control and capability surfaces
- **AND** it does not substitute handwritten assumptions for those contracts

### Requirement: Validation SHALL Ban Semantic Strings In Runtime C++ Headers

Validation SHALL fail when a runtime-consumed generated C++ header exposes a semantic string
field.

#### Scenario: Runtime header still exposes textual schema or signal information
- **WHEN** validation detects fields such as `const char* schema_id`, `const char* signal`,
  `const char* kind`, `const char* package_name`, or similar semantic labels in a runtime
  header
- **THEN** validation fails
- **AND** publication is blocked

### Requirement: Foundational Publication SHALL Require Zero-String Runtime Headers

Foundational families SHALL not publish unless every runtime-consumed generated C++ artifact
obeys the zero-string rule.

#### Scenario: Foundational family still leaks semantic labels into C++
- **WHEN** a foundational family emits a runtime-facing C++ artifact with semantic strings
- **THEN** publish fails for that family
- **AND** no artifact publication record is materialized

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

