## ADDED Requirements

### Requirement: Timing domains are representable in the generated runtime contract

The canonical-to-runtime publication path MUST carry enough typed timing information to emit
SysTick, timer, and PWM runtime contracts.

#### Scenario: SysTick is synthesized for Cortex-M devices when upstream data is incomplete
- **WHEN** a Cortex-M device source package does not expose SysTick as a normal peripheral
- **THEN** the codegen pipeline still synthesizes a typed SysTick publication baseline
- **AND** the generated runtime contract still includes `systick.hpp`

#### Scenario: Timer-like peripherals flow into runtime timing publication
- **WHEN** the canonical model contains timer-capable schemas such as `timer`, `gpt`, `pit`, or
  dedicated `pwm`
- **THEN** those peripherals are admitted into the timing publication path
- **AND** their runtime artifacts are emitted from typed peripheral/register/field data instead of
  reflection tables
