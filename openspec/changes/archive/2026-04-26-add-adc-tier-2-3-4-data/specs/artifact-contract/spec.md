## ADDED Requirements

### Requirement: ADC trait Tier 2/3/4 fields MUST be populated per device patch declarations

Each emitted `AdcSemanticTraits` SHALL populate its Tier 2/3/4 fields (internal channels, calibration data points and context, resolution/sample-time/oversampling options, DMA bindings, external trigger sources, DMA mode options) from the device-patch declarations, so apps can compile-time generate high-level helpers like `readTemperature() -> celsius`, `readVdd() -> mV`, and `AdcDma<Dma1Channel1>::startTimerTriggered<Tim1::Trgo>(buffer)` without hardcoding vendor-specific constants.

#### Scenario: STM32 ADC surfaces internal channels and factory calibration with semantic constants

- **WHEN** the ST G0 / F4 family emits its ADC traits
- **THEN** `kInternalChannels` carries entries for `temperature_sensor`,
  `vrefint`, and `vbat` with their documented channel indices
- **AND** `kCalibrationDataPoints` carries entries with concrete
  `RuntimeRegisterRef` pointing at the system memory cal addresses, plus
  `semantic_constant` set to the temperature (°C) or voltage (mV) at
  which each value was measured
- **AND** `kCalibrationContext` carries `cal_temp_low_celsius`,
  `cal_temp_high_celsius`, `cal_voltage_mv`, and `vrefint_nominal_mv` —
  enough metadata for the consumer to derive the standard temp / mV
  conversion formulas

#### Scenario: AVR-DA surfaces SIGROW factory calibration

- **WHEN** the AVR-DA family emits its ADC traits
- **THEN** `kCalibrationDataPoints` references SIGROW.SREF, TEMPSENSE0,
  and TEMPSENSE1 with their flash-location addresses
- **AND** `kInternalChannels` includes the AVR-DA temperature sensor
  with MUXPOS 0x42 (the documented internal-temp channel)

#### Scenario: ESP32 calibration is delegated to esp-idf with empty cal arrays

- **WHEN** an ESP32 family (esp32, esp32c3, esp32s3) emits its ADC traits
- **THEN** `kCalibrationContext.valid` is `false` and
  `kCalibrationDataPointCount` is `0`
- **AND** the family's `__readme_caveat` documents that factory calibration
  uses esp-idf's `esp_adc_cal_*` runtime API

#### Scenario: RP2040 surfaces the on-die temperature sensor

- **WHEN** the RP2040 family emits its ADC traits
- **THEN** `kInternalChannels` contains exactly one entry of kind
  `temperature_sensor` at channel index 4

#### Scenario: Resolution / sample time / oversampling carry paired arrays

- **WHEN** any family with ADC emits its ADC traits
- **THEN** `kSupportedResolutions` is a non-empty array of `(bits,
  field_value)` pairs covering what the device documents
- **AND** if the device supports configurable sample time, the
  `kSupportedSampleTimes` array carries Q8.8-encoded cycle counts paired
  with their raw field values
- **AND** if the device supports HW oversampling, the
  `kSupportedOversamplings` array carries `(ratio, field_value)` pairs
- **AND** families that don't support a feature carry empty arrays for it

#### Scenario: DMA bindings derive from device.dma_requests

- **WHEN** any family's ADC peripheral has a matching `dma_requests` entry
  in its IR
- **THEN** `kDmaBindings` contains an `AdcDmaBinding` per matching request
  with controller_peripheral, controller_id, binding_id, request_value,
  data_register, and transfer_width_bits populated
- **AND** families without DMA-capable ADC (AVR-DA, ESP32 classic ADC1,
  ESP32-C3) carry `kDmaBindingCount=0`

#### Scenario: External trigger sources are enumerated with EXTSEL values

- **WHEN** a family that supports timer-triggered ADC emits its ADC traits
- **THEN** `kExternalTriggers` contains an `AdcExternalTrigger` per
  documented trigger source
- **AND** each entry carries the symbolic `AdcExternalTriggerSource` enum
  value, the raw EXTSEL field value to write, and the default polarity
- **AND** families admitting only software trigger (RP2040, AVR-DA at
  this stage, ESP32 in this admission) carry `kExternalTriggerCount=0`
