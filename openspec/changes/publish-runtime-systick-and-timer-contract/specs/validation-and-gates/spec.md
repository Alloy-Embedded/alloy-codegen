## ADDED Requirements

### Requirement: Publish is blocked by incomplete timing artifacts

Publish MUST fail when foundational timing artifacts are missing or structurally incomplete.

#### Scenario: Missing systick header blocks foundational publish
- **WHEN** a foundational Cortex-M device is emitted without
  `generated/runtime/devices/<device>/systick.hpp`
- **THEN** publish fails

#### Scenario: Missing timer semantics blocks foundational publish
- **WHEN** a foundational device with timer-capable peripherals is emitted without
  `generated/runtime/devices/<device>/driver_semantics/timer.hpp`
- **THEN** publish fails

#### Scenario: Missing pwm semantics blocks foundational publish
- **WHEN** a foundational device with PWM-capable peripherals is emitted without
  `generated/runtime/devices/<device>/driver_semantics/pwm.hpp`
- **THEN** publish fails

#### Scenario: Runtime-lite consumer smoke includes timing contracts
- **WHEN** runtime-lite consumer verification runs for a foundational device
- **THEN** the smoke consumer includes the generated SysTick, timer, and PWM headers when those
  domains apply
- **AND** it compiles representative traits from each published timing domain
