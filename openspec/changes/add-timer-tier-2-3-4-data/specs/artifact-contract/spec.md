## ADDED Requirements

### Requirement: timer.hpp SHALL surface Tier 2/3/4 silicon facts

The emitted `timer.hpp` SHALL extend every populated
`TimerSemanticTraits` specialization with: max prescaler, max
auto-reload, trigger-source array (ITR0..ITR3 + ETR + TI1F + ...),
master-output mode array (TRGO sources), and capability flags
`kSupportsDmaBurst`, `kSupportsRepetitionCounter`,
`kSupportsXorInput`.  Empty arrays / `0u` / `false` on the
unspecialized template.

#### Scenario: STM32G0 TIM1 advertises full ITR matrix + repetition counter

- **WHEN** the pipeline emits `timer.hpp` for STM32G0 stm32g071rb
- **THEN** `TimerSemanticTraits<PeripheralId::TIM1>::kMaxPrescaler`
  equals `0xFFFFu`
- **AND** `kTriggerSources.size() >= 4`
  (ITR0, ITR1, ITR2, ITR3 minimum)
- **AND** `kMasterOutputModes.size() >= 8`
  (Reset, Enable, Update, ComparePulse, OC1Ref..OC4Ref)
- **AND** `kSupportsRepetitionCounter == true`
- **AND** `kSupportsDmaBurst == true`

#### Scenario: STM32G0 TIM14 is a basic timer with empty trigger array

- **WHEN** the pipeline emits `timer.hpp` for STM32G0 stm32g071rb
- **THEN** `TimerSemanticTraits<PeripheralId::TIM14>::kTriggerSources.size()`
  equals `0`
- **AND** `kSupportsRepetitionCounter == false`
- **AND** `kSupportsDmaBurst == false`
- **AND** `kMaxPrescaler == 0xFFFFu`
