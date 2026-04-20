## MODIFIED Requirements

### Requirement: Runtime-Lite C++ Contract
The published C++ artifact contract MUST separate reflection-oriented artifacts from hot-path
runtime artifacts. System startup and system-clock bring-up artifacts MUST be executable when the
family is declared foundational for Alloy runtime consumption.

#### Scenario: Foundational SAME70 system clock is executable
- **WHEN** `microchip/same70` publishes a foundational device with system-clock profiles
- **THEN** `generated/runtime/devices/<device>/system_clock.hpp` SHALL emit typed profile traits
- **AND** it SHALL emit device-scoped executable bring-up code for the published SAME70 profiles
- **AND** it SHALL NOT reduce those profiles to a generic metadata-only fallback body
