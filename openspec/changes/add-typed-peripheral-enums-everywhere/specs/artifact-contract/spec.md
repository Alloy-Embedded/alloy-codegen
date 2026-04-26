## ADDED Requirements

### Requirement: UART/SPI/I2C/TIMER/PWM trait headers SHALL surface typed per-peripheral option enums

For every option-array currently emitted as `std::array<std::uint8_t, N>` on UART, SPI, I2C, TIMER, and PWM trait headers, the pipeline SHALL also emit a paired `enum class <Name>Of<PeripheralId::P>::type` with named entries derived from the populated patch values, plus a typed `std::array<<Name>Of<P>::type, N>` constexpr alongside the existing raw array.  The naming pattern SHALL follow the ADC channel-enum convention (`<Peripheral><Option>Of<P>::type`).  Each typed enum SHALL ship with a closed kind→name lookup table so `to_string(...)` round-trips deterministically.  The existing raw `_Raw` arrays SHALL be retained for one release cycle for back-compat and removed in a follow-up cleanup change.

#### Scenario: STM32G0 USART1 surfaces UartParityOf typed enum

- **WHEN** the pipeline emits `uart.hpp` for STM32G0 stm32g071rb
- **THEN** the file SHALL contain a `UartParityOf<PeripheralId::USART1>::type`
  enum class with entries `none`, `even`, and `odd`
- **AND** SHALL contain a paired
  `static constexpr std::array<UartParityOf<PeripheralId::USART1>::type, 3> kSupportedParity`
- **AND** SHALL retain the existing
  `static constexpr std::array<std::uint8_t, 3> kSupportedParityRaw`
- **AND** the typed enum entries SHALL map back to the same
  `field_value` integers carried in `kSupportedParityRaw`

#### Scenario: STM32G0 SPI1 surfaces SpiFrameSizeOf typed enum

- **WHEN** the pipeline emits `spi.hpp` for STM32G0 stm32g071rb
- **THEN** the file SHALL contain a
  `SpiFrameSizeOf<PeripheralId::SPI1>::type` enum class with
  entries `bits_4`, `bits_5`, …, `bits_16`
- **AND** SHALL contain a paired
  `static constexpr std::array<SpiFrameSizeOf<PeripheralId::SPI1>::type, 13> kSupportedFrameSizes`

#### Scenario: AVR-DA TWI0 surfaces only the populated speed modes

- **WHEN** the pipeline emits `i2c.hpp` for AVR-DA avr128da32
- **THEN** the file SHALL contain a `I2cSpeedModeOf<PeripheralId::TWI0>::type`
  enum class with entries `standard` and `fast` (no `fast_plus`)
- **AND** the typed `kSupportedSpeedModes` array SHALL have size 2

### Requirement: Typed enums SHALL ship name-tables for round-trip stringification

Every emitted typed enum SHALL be paired with a closed `std::array<NameEntry, N>` constant mapping each enum entry to its lowercase string label.  Consumer code that needs runtime stringification SHALL be able to look the name up without a `switch` statement.  Mirrors the ADC channel-name table established by `add-adc-channel-typed-enum`.

#### Scenario: UART parity name table round-trips

- **WHEN** the pipeline emits `uart.hpp` for STM32G0 stm32g071rb
- **THEN** the file SHALL define a `kUartParityNames` table for
  `USART1` of size 3
- **AND** the entry corresponding to
  `UartParityOf<PeripheralId::USART1>::type::even` SHALL carry the
  string `"even"`
