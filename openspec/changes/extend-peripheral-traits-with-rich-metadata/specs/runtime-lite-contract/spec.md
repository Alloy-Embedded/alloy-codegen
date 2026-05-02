## ADDED Requirements

### Requirement: Runtime-Lite Contract SHALL Expose Typed ADC Calibration Accessors

The runtime-lite contract SHALL expose typed `AdcInstanceTraits<I>::kCalibration`
and `kExternalTriggers` accessors so alloy's ADC HAL can read
factory calibration ROM addresses and external-trigger encoding
without vendor-specific lookup tables.

#### Scenario: ADC HAL reads VREFINT ROM address through trait

- **WHEN** alloy ADC HAL on an STM32 G0 calls
  `AdcInstanceTraits<PeripheralId::ADC1>::kCalibration.vrefint_addr`
- **THEN** the value resolves at compile time to the exact ROM
  address the YAML carries
- **AND** the HAL does not require a `#ifdef STM32G0` block

### Requirement: Runtime-Lite Contract SHALL Expose Typed I²C Timing-Preset Accessors

The runtime-lite contract SHALL expose
`I2cInstanceTraits<I>::kTimingPresets` as a `constexpr
std::array<I2cTimingPreset, N>` accessor so alloy's I²C HAL can
pick a pre-computed `timingr` at open time without runtime
division.

#### Scenario: I²C HAL picks 400 kHz preset at compile time

- **WHEN** alloy I²C HAL on an STM32 G0 calls
  `pick_preset<PeripheralId::I2C1>(/*speed_hz=*/400000,
  /*pclk_hz=*/64000000)`
- **THEN** the call resolves at compile time to the matching
  `I2cTimingPreset` with `speed_hz=400000, pclk_hz=64000000`
- **AND** the HAL does not perform any runtime PCLK division

### Requirement: Runtime-Lite Contract SHALL Expose Typed Timer Matrix Accessors

The runtime-lite contract SHALL expose
`TimerTemplateTraits<T>::kTriggerSources`,
`kMasterOutputs`, `kDeadtimeOptions`, `kBreakInputs`,
`kCounterBitsOptions`, and `kWaveformModes` as `constexpr`
arrays/sets so motor-control and complementary-PWM drivers can
`static_assert` feature support and look up encoded register
values without runtime tables.

#### Scenario: Motor-control HAL refuses dead-time on basic timer

- **WHEN** alloy motor-control HAL instantiates with
  `PeripheralId::TIM6` (a basic timer with no deadtime support)
- **THEN** a `static_assert(TimerTemplateTraits<
  PeripheralTemplate::tim_basic>::kDeadtimeOptions.size() > 0)`
  fails at compile time
- **AND** the diagnostic names the unsupported feature
