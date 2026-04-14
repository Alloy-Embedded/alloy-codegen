## ADDED Requirements

### Requirement: Publish is blocked by incomplete bring-up artifacts

Publish MUST fail when foundational startup or system-clock bring-up artifacts are missing or
structurally incomplete.

#### Scenario: Missing startup.cpp blocks publish
- **WHEN** a foundational device is emitted without `generated/devices/<device>/startup.cpp`
- **THEN** publish fails

#### Scenario: Missing system_clock.hpp blocks publish
- **WHEN** a foundational device is emitted without
  `generated/runtime/devices/<device>/system_clock.hpp`
- **THEN** publish fails

#### Scenario: Runtime-lite smoke includes system clock
- **WHEN** runtime-lite consumer verification runs
- **THEN** the smoke consumer includes the generated system clock header
- **AND** verifies at least one published default/safe profile when the device exposes profiles
