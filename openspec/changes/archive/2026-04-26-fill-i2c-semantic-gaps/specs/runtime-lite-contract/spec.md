## ADDED Requirements

### Requirement: i2c.hpp SHALL emit populated I2cPeripheralTraits specializations

Every emitted `driver_semantics/i2c.hpp` SHALL declare an `I2cPeripheralTraits<RuntimeI2cCtrlId>` template alongside the existing register-level `I2cSemanticTraits<PeripheralId>`. The new trait is keyed by a generated `RuntimeI2cCtrlId` enum populated from `device.i2c_peripherals[*].peripheral_id`.

The primary `I2cPeripheralTraits<RuntimeI2cCtrlId>` template SHALL carry
zero-valued defaults so families without I2C hardware remain
zero-cost. Each populated specialization SHALL surface:

- `kPresent` (bool)
- `kBaseAddress` (uint32_t)
- `kClockSource` token as `std::string_view` (or empty string when
  family-fixed)
- `kDmaReqTx`, `kDmaReqRx` (uint8_t; `0` when no DMA path)
- `kValidSdaPins`, `kValidSclPins` (`std::array<std::uint8_t, N>`;
  `N==0` means the AllGpios sentinel — any pad acceptable)
- `kInSdaSignal`, `kInSclSignal`, `kOutSdaSignal`, `kOutSclSignal`
  (uint16_t; Espressif IO-matrix indices, `0xFFFF` when not used)
- `kSupportsFastModePlus` (bool)
- `kPortmuxAlt` (bool; AVR-DA only)

#### Scenario: Non-I2C families keep zero-cost defaults

- **WHEN** a device with `i2c_peripherals == ()` is emitted
- **THEN** `i2c.hpp` declares the primary `I2cPeripheralTraits` template
  with `kPresent = false` and zero-valued defaults
- **AND** no `I2cPeripheralTraits<RuntimeI2cCtrlId::*>` specialization
  is emitted
- **AND** the existing register-level `I2cSemanticTraits<PeripheralId>`
  template is unchanged

#### Scenario: STM32G071RB emits I2C1 and I2C2 specializations

- **WHEN** the STM32G071RB device is emitted
- **THEN** `i2c.hpp` contains
  `I2cPeripheralTraits<RuntimeI2cCtrlId::I2C1>` with
  `kBaseAddress = 0x40005400u` and a non-empty `kValidSdaPins`
- **AND** I2C2 has `kBaseAddress = 0x40005800u`
- **AND** both carry `kClockSource = "pclk"` and
  `kSupportsFastModePlus = true`

#### Scenario: RP2040 I2C0 records FUNCSEL-derived pin constraints

- **WHEN** the rp2040 device is emitted
- **THEN** `I2cPeripheralTraits<RuntimeI2cCtrlId::I2C0>` records
  `kValidSdaPins = {{0u, 4u, 8u, 12u, 16u, 20u, 24u, 28u}}` and
  `kValidSclPins = {{1u, 5u, 9u, 13u, 17u, 21u, 25u, 29u}}`
- **AND** `kDmaReqTx = 32u`, `kDmaReqRx = 33u`
