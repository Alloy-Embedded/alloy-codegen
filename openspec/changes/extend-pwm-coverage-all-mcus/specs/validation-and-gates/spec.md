## ADDED Requirements

### Requirement: PWM-bearing families MUST pass the PWM semantic coverage gate

Every admitted MCU family that ships at least one PWM-capable peripheral MUST emit a `driver_semantics/pwm.hpp` containing at least one populated specialization of one of the family-shaped trait templates (`StmTimerPwmTraits`, `FlexPwmTraits`, `McpwmTraits`, `LedcTraits`, `AvrDaTcaPwmTraits`, `Same70PwmTraits`, or the existing `Rp2040PwmSliceHwTraits`). A repository-level CI gate MUST fail PRs that admit a new PWM-bearing family without populated traits, or that regress an existing family back to a zero-specialization state.

The gate is rolled out per-family alongside the implementation phase that populates that family. The gate becomes mandatory for every admitted family once Phase F (the final phase) lands.

#### Scenario: PWM coverage gate accepts a populated family

- **WHEN** a family that has been wired through the PWM-semantic emitter (any of the six family-shape templates) emits its `pwm.hpp`
- **THEN** the file contains at least one specialization where `kPresent = true`
- **AND** the coverage gate passes for that family

#### Scenario: PWM coverage gate flags a regression

- **WHEN** a family that previously emitted populated PWM specializations is changed in a way that drops all of them
- **THEN** the coverage gate flags the family as regressed and the CI job fails

#### Scenario: ESP32-C3 satisfies the gate via LEDC alone

- **WHEN** the ESP32-C3 device is emitted
- **THEN** `LedcTraits<RuntimeLedcId::LEDC>::kPresent` is `true`
- **AND** the gate passes for ESP32-C3 even though `McpwmTraits` carries no specializations on that variant
