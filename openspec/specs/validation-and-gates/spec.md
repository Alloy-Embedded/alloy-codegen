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

