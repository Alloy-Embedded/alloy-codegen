# artifact-contract Specification

## Purpose
TBD - created by archiving change build-best-in-class-generator-core. Update Purpose after archive.
## Requirements
### Requirement: Published runtime contract exposes system-control fabric

The supported runtime C++ contract MUST publish typed device-scoped system-control facts needed by
Alloy and advanced consumers.

#### Scenario: Runtime contract includes interrupts, resets, and clock dependencies
- **WHEN** a foundational device is published
- **THEN** its runtime contract exposes typed interrupt facts, reset-control facts, and clock
  dependency facts
- **AND** those facts live under `generated/runtime/devices/<device>/`

### Requirement: Published runtime contract exposes formal capabilities

The supported runtime C++ contract MUST expose formal capability descriptors for runtime-supported
peripherals.

#### Scenario: Capabilities are published as supported contract facts
- **WHEN** a foundational device is published
- **THEN** runtime-supported peripherals publish typed capability facts
- **AND** those facts are queryable without legacy reflection artifacts

### Requirement: Publication emits explainability and provenance reports

Publication MUST emit machine-readable explainability and provenance outputs for runtime-critical
generated facts.

#### Scenario: Publication reports explain emitted facts
- **WHEN** a foundational family is published
- **THEN** reports identify the source, patch, or inference path behind runtime-critical facts
- **AND** they explicitly mark unsupported or heuristic coverage

