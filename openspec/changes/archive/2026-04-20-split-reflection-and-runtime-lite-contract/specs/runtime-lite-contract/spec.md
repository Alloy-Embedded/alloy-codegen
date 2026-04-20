## ADDED Requirements

### Requirement: Reflection And Runtime-Lite Contracts SHALL Be Distinct

`alloy-codegen` SHALL emit generated C++ artifacts in two explicit categories:

- a reflection contract for validation, tooling, smoke compilation, and inspection
- a runtime-lite contract for hot-path runtime consumption

The runtime-lite contract SHALL be stable and documented as the preferred runtime boundary for
`alloy`.

#### Scenario: Foundational family publish includes both contract types

- **WHEN** `alloy-codegen` publishes artifacts for a foundational family
- **THEN** the publication includes both reflection artifacts and runtime-lite artifacts
- **AND** the runtime-lite artifacts are sufficient for runtime-owned peripheral classes

### Requirement: Runtime-Lite Contract SHALL Avoid Family-Wide Lookup As Normal Usage

Runtime-lite artifacts SHALL represent runtime-owned hardware facts using compile-time-friendly
constructs such as typed specializations, typed aliases, compact refs, and `constexpr` packs,
rather than requiring generic family-wide table scans.

#### Scenario: One UART route is lowered without generic candidate scanning

- **WHEN** a published connector route is consumed by the runtime-lite contract
- **THEN** the runtime can obtain the selected instance, register refs, field refs, clock
  bindings, and route operations without scanning the family connector graph at runtime

### Requirement: Runtime-Lite Contract SHALL Cover Foundational Runtime-Owned Drivers

The runtime-lite contract SHALL cover at least the foundational runtime-owned use cases:

- GPIO enable and mode configuration
- UART open on a chosen connector
- SPI open on a chosen connector
- I2C open on a chosen connector

#### Scenario: Foundational families publish runtime-lite coverage

- **WHEN** `st/stm32g0`, `st/stm32f4`, `microchip/same70`, and `nxp/imxrt1060` are emitted
- **THEN** each family includes runtime-lite artifacts sufficient to implement those driver
  paths without reflection-table dependency
