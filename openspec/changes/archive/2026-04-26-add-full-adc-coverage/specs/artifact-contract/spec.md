## ADDED Requirements

### Requirement: ADC trait header is populated for every admitted ADC peripheral

For every admitted device, the emitted `driver_semantics/adc.hpp` SHALL
contain a populated `AdcSemanticTraits` specialisation
(`kPresent = true` and `kSchemaId != BackendSchemaId::none`) for every
peripheral whose canonical class is `adc` AND whose family explicitly
declares an ``ip_version`` admitting it.  Devices with no admitted ADC
peripheral SHALL emit only the unspecialised template (default
`kPresent = false`).

The publish stage SHALL fail when an explicitly-admitted ADC peripheral has
only the catch-all stub specialisation, ensuring no family ships incomplete
ADC metadata silently.

#### Scenario: ESP32 family ADC peripherals are populated with distinct schemas

- **WHEN** the publish stage runs for `espressif/esp32`, `espressif/esp32c3`,
  or `espressif/esp32s3`
- **THEN** the emitted `driver_semantics/adc.hpp` carries a populated
  specialisation with `kSchemaId` matching the family's distinct schema id
  (`alloy.adc.espressif-esp32-sens-v1`,
  `alloy.adc.espressif-esp32c3-saradc-v1`, or
  `alloy.adc.espressif-esp32s3-saradc-v1`)
- **AND** the row exposes typed `RuntimeRegisterRef` for control and data
  registers, plus a `kChannelCount` consistent with the chip's documented
  channel inventory

#### Scenario: AVR-DA and RP2040 emit populated ADC traits

- **WHEN** the publish stage runs for `microchip/avr-da` or
  `raspberrypi/rp2040`
- **THEN** the emitted `driver_semantics/adc.hpp` carries a populated
  specialisation with `kSchemaId` matching `alloy.adc.microchip-avr-da-adc-v1`
  or `alloy.adc.raspberrypi-rp2040-adc-v1` respectively

#### Scenario: Validation gates an unimplemented ADC peripheral

- **WHEN** a device's IR carries a peripheral with class `adc`, an explicit
  `ip_version`, and a schema id for which no builder exists in
  `_build_adc_rows`
- **THEN** validation fails with rule id `<device>-adc-semantics-populated`
  at severity `error`
- **AND** the publish stage refuses to publish with the warning "ADC
  peripheral admitted without populated semantic traits"

#### Scenario: SVD-sourced ADC-class peripherals without explicit admission are exempt

- **WHEN** a peripheral such as ESP32-S3's `SENS` (touch + temperature
  sensor block) lacks an explicit `ip_version` in family.json
- **THEN** the validation rule treats it as an incidental SVD-sourced extra
  and does NOT fail
- **AND** the trait still emits a stub specialisation
  (`kPresent = false`) so downstream code can detect that the peripheral
  exists but has no semantic schema

### Requirement: ADC trait schema carries Tier 2/3/4 fields with safe defaults

The `AdcSemanticTraits` template SHALL declare static array fields for
internal channels, calibration data points and context, supported
configuration values (resolution, sample time, oversampling), DMA bindings,
external trigger sources, and DMA mode options.  Defaults SHALL be empty
``std::array<X, 0>`` so any vendor builder can opt in to populating them
incrementally without breaking previously-published goldens.

The follow-on change `add-adc-tier-2-3-4-data` SHALL populate these fields
per vendor.  Until then, the schema surface is stable and consumers can
already reference the symbols (they will resolve to empty arrays).

#### Scenario: Schema fields appear in every emitted adc.hpp

- **WHEN** any device with an admitted ADC peripheral emits its
  `driver_semantics/adc.hpp`
- **THEN** the file declares `kInternalChannels`, `kCalibrationDataPoints`,
  `kCalibrationContext`, `kSupportedResolutions`, `kSupportedSampleTimes`,
  `kSupportedOversamplings`, `kDmaBindings`, `kExternalTriggers`, and
  `kSupportedDmaModes` on each populated specialisation
- **AND** the corresponding `kXxxCount` constants are emitted as
  `static constexpr std::uint32_t`
- **AND** every field carries a syntactically valid C++ initialiser even
  when the vendor builder has not yet populated the data (empty array is
  the canonical "absent" form)

#### Scenario: New ADC support types appear in common.hpp

- **WHEN** any device emits its `driver_semantics/common.hpp`
- **THEN** the file declares the support enums
  (`InternalAdcChannelKind`, `AdcCalibrationKind`,
  `AdcExternalTriggerSource`, `AdcDmaMode`) and structs
  (`InternalAdcChannel`, `CalibrationDataPoint`, `CalibrationContext`,
  `AdcResolutionOption`, `AdcSampleTimeOption`, `AdcOversamplingOption`,
  `AdcExternalTrigger`, `AdcDmaBinding`, `AdcDmaModeOption`)
- **AND** these types are usable by any consumer-side code generator that
  wants to produce modm-style high-level ADC drivers
