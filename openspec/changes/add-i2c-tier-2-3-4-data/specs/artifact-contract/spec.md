## ADDED Requirements

### Requirement: i2c.hpp SHALL surface Tier 2/3/4 silicon facts

The emitted `i2c.hpp` SHALL extend every populated
`I2cSemanticTraits` specialization with: supported speeds,
addressing-mode flags (7-bit / 10-bit / SMBus / PMBus), supported
slave / general-call / dual-address flags, max clock, and
precomputed TIMINGR / CWGR presets keyed by source clock.  Empty
arrays / false flags / `0u` on the unspecialized template.

#### Scenario: STM32G0 I2C1 surfaces three speeds + Fast-Mode-Plus

- **WHEN** the pipeline emits `i2c.hpp` for STM32G0 stm32g071rb
- **THEN** `I2cSemanticTraits<PeripheralId::I2C1>::kSupportedSpeeds`
  contains `100'000u`, `400'000u`, and `1'000'000u`
- **AND** `kSupports7BitAddressing == true`
- **AND** `kSupports10BitAddressing == true`
- **AND** `kSupportsSmbus == true`
- **AND** `kTimingPresets.size() >= 3`
- **AND** at least one preset has
  `source_clock_hz == 64'000'000u` and `speed_hz == 400'000u`

#### Scenario: STM32G0 emission bug is fixed

- **WHEN** the pipeline emits `i2c.hpp` for STM32G0 stm32g071rb
- **THEN** `kI2cSemanticPeripherals` SHALL include `PeripheralId::I2C1`
- **AND** an explicit `I2cSemanticTraits<PeripheralId::I2C1>`
  specialization SHALL be present (today the unspecialized
  fallback fires because the array is empty)

#### Scenario: AVR-DA TWI carries fewer flags but valid presets

- **WHEN** the pipeline emits `i2c.hpp` for AVR-DA avr128da32
- **THEN** `I2cSemanticTraits<PeripheralId::TWI0>::kSupportsSmbus
  == false`
- **AND** `kSupportsSlave == true` (AVR TWI is bidirectional)
- **AND** `kSupportedSpeeds` contains `100'000u` and `400'000u`
