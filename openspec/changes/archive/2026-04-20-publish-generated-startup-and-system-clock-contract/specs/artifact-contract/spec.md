## ADDED Requirements

### Requirement: Generated startup translation unit is published

Foundational published device trees MUST include `generated/devices/<device>/startup.cpp`.

#### Scenario: Foundational device publish includes startup translation unit
- **WHEN** a foundational family is emitted
- **THEN** each foundational device publishes `generated/devices/<device>/startup.cpp`
- **AND** the source materializes `Reset_Handler`
- **AND** the source materializes a vector table from published vector slots

### Requirement: Runtime-lite system clock contract is published

Foundational published device trees MUST include
`generated/runtime/devices/<device>/system_clock.hpp`.

#### Scenario: Foundational device publish includes system clock header
- **WHEN** a foundational family is emitted
- **THEN** each foundational device publishes `generated/runtime/devices/<device>/system_clock.hpp`
- **AND** the header publishes typed profile identifiers and traits
- **AND** the header publishes generated default/safe bring-up helpers
