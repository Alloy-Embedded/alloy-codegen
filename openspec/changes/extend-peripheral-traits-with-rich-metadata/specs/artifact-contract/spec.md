## ADDED Requirements

### Requirement: `peripheral_traits.h` SHALL Expose `AdcInstanceTraits` For Every ADC Instance With Calibration

The published `peripheral_traits.h` SHALL contain an
`AdcInstanceTraits<PeripheralId::Ix>` specialisation for every
peripheral instance whose canonical template class is `adc` and
whose `peripherals[].calibration` is populated.  The
specialisation SHALL expose `kCalibration` (typed
`CalibrationConstants`), `kExternalTriggers` (when populated),
and `kCalibrationData` (when the IR carries calibration data
points).

#### Scenario: STM32 G0 ADC1 publishes a calibration surface

- **WHEN** alloy-codegen emits artifacts for
  `st/stm32g0/stm32g071rb`
- **THEN** `peripheral_traits.h` contains
  `template <> struct AdcInstanceTraits<PeripheralId::ADC1>`
- **AND** the specialisation defines
  `static constexpr CalibrationConstants kCalibration` whose
  `vrefint_addr`, `ts_cal_low_addr`, `ts_cal_high_addr` are the
  exact ROM addresses from the IR

#### Scenario: ADC instance without calibration receives no AdcInstanceTraits

- **WHEN** alloy-codegen emits artifacts for a chip whose ADC
  instance has no populated `calibration`
- **THEN** `peripheral_traits.h` contains no
  `AdcInstanceTraits<>` specialisation for that instance
- **AND** consumers that try to use the trait fail to compile

### Requirement: `peripheral_traits.h` SHALL Expose `I2cInstanceTraits::kTimingPresets` Where Populated

The published `peripheral_traits.h` SHALL contain an
`I2cInstanceTraits<PeripheralId::Ix>` specialisation exposing
`kTimingPresets` for every I²C instance with a non-empty
`timing_presets` IR block.

#### Scenario: STM32 G0 I2C1 publishes timing presets

- **WHEN** alloy-codegen emits artifacts for
  `st/stm32g0/stm32g071rb`
- **THEN** `peripheral_traits.h` contains
  `template <> struct I2cInstanceTraits<PeripheralId::I2C1>`
  defining `static constexpr std::array<I2cTimingPreset, N>
  kTimingPresets`
- **AND** every entry carries a non-zero `timingr` and the
  exact `pclk_hz` assumed at YAML-emit time

### Requirement: `peripheral_traits.h` SHALL Expose `TimerTemplateTraits` Matrix Fields

The published `peripheral_traits.h` SHALL contain a
`TimerTemplateTraits<PeripheralTemplate::Tx>` specialisation
exposing `kTriggerSources`, `kMasterOutputs`, `kDeadtimeOptions`,
`kBreakInputs`, `kCounterBitsOptions`, and `kWaveformModes` for
every template whose IR carries any of those matrix fields.

#### Scenario: STM32 F4 advanced timer template publishes its matrix

- **WHEN** alloy-codegen emits artifacts for any STM32 F4 device
- **THEN** `peripheral_traits.h` contains a
  `TimerTemplateTraits<PeripheralTemplate::tim_advanced>`
  specialisation whose `kTriggerSources.size()` matches
  `len(templates[tim_advanced].trigger_sources)` and whose
  encoded values match the IR

### Requirement: New Trait Specialisations SHALL Stay Zero-String

`peripheral_traits.h` SHALL emit no semantic `const char*` field
inside any new `AdcInstanceTraits`, `I2cInstanceTraits`, or
`TimerTemplateTraits` specialisation; all metadata SHALL be
encoded as enums, ids, refs, integers, or masks per the existing
zero-string artifact-contract rule.

#### Scenario: Zero-string gate passes after rich-metadata emission

- **WHEN** the pre-publication zero-string gate scans
  `out/<vendor>/<family>/<chip>/peripheral_traits.h` after this
  proposal's emitter changes
- **THEN** the gate finds no semantic string literal in any
  `AdcInstanceTraits<>`, `I2cInstanceTraits<>`, or
  `TimerTemplateTraits<>` block
