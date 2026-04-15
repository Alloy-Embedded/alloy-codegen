## MODIFIED Requirements

### Requirement: Generated artifacts stay on the codegen side of the boundary

Generated artifacts MUST stay device-scoped, typed, and free of Alloy-owned public HAL surface.

#### Scenario: Generated timing contracts remain inside the contract boundary
- **WHEN** SysTick, timer, or PWM artifacts are emitted
- **THEN** they are published under `generated/runtime/devices/<device>/...`
- **AND** they do not emit `namespace alloy`
- **AND** they do not emit public HAL driver classes
- **AND** they only publish typed traits, helpers, and runtime refs needed for device behavior

#### Scenario: Codegen owns low-level timing semantics and Alloy owns public APIs
- **WHEN** the timing contract is consumed by Alloy
- **THEN** codegen supplies device-scoped SysTick/timer/PWM hardware semantics
- **AND** Alloy remains responsible for user-facing timer, PWM, and SysTick API shape
