## ADDED Requirements

### Requirement: pwm.hpp SHALL surface Tier 2/3/4 silicon facts

The emitted `pwm.hpp` SHALL extend every populated
`PwmSemanticTraits` specialization with: max prescaler, max
period, deadtime configuration options, supported alignment
modes (edge / center-up / center-down / center-up-down), break
input descriptors, and capability flags `kSupportsDeadtime`,
`kSupportsBreakInput`, `kSupportsComplementaryOutputs`,
`kSupportsAsymmetricPwm`, `kSupportsCombinedPwm`.  Empty arrays /
`0u` / `false` on the unspecialized template.

#### Scenario: STM32G0 TIM1 PWM advertises full deadtime + 1 break input

- **WHEN** the pipeline emits `pwm.hpp` for STM32G0 stm32g071rb
- **THEN** `PwmSemanticTraits<PeripheralId::TIM1>::kSupportsDeadtime
  == true`
- **AND** `kSupportsBreakInput == true`
- **AND** `kBreakInputs.size() == 1`
- **AND** `kSupportedAlignments.size() == 4`
  (edge + 3 center-aligned modes)
- **AND** `kDeadtimeOptions.size() >= 4`
  (4 DTPSC prescaler choices)

#### Scenario: STM32G0 TIM14 PWM is basic — no deadtime, no break

- **WHEN** the pipeline emits `pwm.hpp` for STM32G0 stm32g071rb
- **THEN** `PwmSemanticTraits<PeripheralId::TIM14>::kSupportsDeadtime
  == false`
- **AND** `kSupportsBreakInput == false`
- **AND** `kBreakInputs.size() == 0`
- **AND** `kSupportedAlignments.size() == 1` (edge only)
