## ADDED Requirements

### Requirement: Runtime-lite SysTick contract is published for Cortex-M devices

Cortex-M device publications MUST include a generated SysTick runtime contract.

#### Scenario: Foundational Cortex-M device publishes systick header
- **WHEN** a foundational Cortex-M device is emitted
- **THEN** it publishes `generated/runtime/devices/<device>/systick.hpp`
- **AND** the header publishes typed register/field refs for SysTick control and reload/value state
- **AND** the header publishes typed traits for clock-source and calibration capabilities

### Requirement: Runtime-lite timer and PWM semantics are published

Devices with timer or PWM-capable peripherals MUST publish device-scoped runtime semantics for
those domains.

#### Scenario: Device with timer peripherals publishes timer semantics
- **WHEN** a device exposes timer-capable peripherals under the active runtime contract
- **THEN** it publishes `generated/runtime/devices/<device>/driver_semantics/timer.hpp`
- **AND** the header publishes per-peripheral and per-channel typed traits

#### Scenario: Device with PWM-capable peripherals publishes pwm semantics
- **WHEN** a device exposes PWM-capable peripherals under the active runtime contract
- **THEN** it publishes `generated/runtime/devices/<device>/driver_semantics/pwm.hpp`
- **AND** the header publishes typed capability and channel traits for supported waveform features
