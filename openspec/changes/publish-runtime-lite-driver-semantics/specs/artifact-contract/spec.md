## MODIFIED Requirements

### Requirement: Runtime-Lite C++ Contract
The published C++ artifact contract MUST separate reflection-oriented artifacts from hot-path
runtime artifacts. For foundational driver classes, the hot-path contract MUST include typed
driver-semantic traits in addition to runtime-lite facts.

#### Scenario: Foundational driver semantics are published
- **WHEN** a family publishes runtime-lite artifacts for a foundational device
- **THEN** the artifact tree SHALL include typed semantic trait headers for `gpio`, `uart`,
  `i2c`, and `spi` under `generated/runtime/devices/<device>/driver_semantics/`
- **AND** those headers SHALL reference only typed ids and traits already published by the
  runtime-lite contract
- **AND** the normal driver path SHALL NOT require reflection tables to identify semantic roles

#### Scenario: Reflection remains available for tooling
- **WHEN** the family publishes reflection artifacts
- **THEN** those artifacts MAY remain available for validation, smoke coverage, or tooling
- **BUT** they SHALL NOT be the required hot-path dependency for foundational drivers
