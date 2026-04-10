## ADDED Requirements

### Requirement: Cross-Family IR Compatibility
The canonical IR schema SHALL be reused across all supported vendor/family pairs without
forking. No family-specific IR model or schema file SHALL be introduced.

#### Scenario: F4 devices normalise into the same CanonicalDeviceIR
- **WHEN** a `stm32f4` device is normalised
- **THEN** the output SHALL conform to the same `CanonicalDeviceIR` schema version as the
  bootstrap family
- **AND** the `schema_version` field in the output SHALL be identical to that of a
  normalised `stm32g0` device

#### Scenario: Adding a new family does not change existing golden fixtures
- **WHEN** a second family is added to the device registry
- **THEN** the normalised canonical JSON for all previously-supported devices SHALL remain
  byte-for-byte identical
- **AND** the IR schema version SHALL NOT be bumped solely to accommodate the new family
