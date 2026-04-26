## ADDED Requirements

### Requirement: RP2040 gpio.hpp SHALL emit populated GpioSemanticTraits specializations

The RP2040 emitted `driver_semantics/gpio.hpp` SHALL produce one
`GpioSemanticTraits<PinId::GP{N}>` specialization for every entry in
`device.gpio_pins`. Each specialization SHALL carry:

- `kPresent = true`
- `kPortOffset = 0u`
- `kPinIndex = N` (pad number 0..29)
- `kIsInputOnly = false`
- `kValidAltFunctions` populated from FUNCSEL indexes (subset of `1..9`)
- `kMaxAltFunction` set to the maximum FUNCSEL index for the pad

#### Scenario: rp2040 GP0 specialization records its AF set

- **WHEN** rp2040 `gpio.hpp` is emitted
- **THEN** `GpioSemanticTraits<PinId::GP0>::kPresent` is `true`
- **AND** `GpioSemanticTraits<PinId::GP0>::kPinIndex == 0u`
- **AND** `kValidAltFunctions` contains `{1, 2, 3}` (SPI0_RX,
  UART0_TX, I2C0_SDA from the FUNCSEL table)

#### Scenario: rp2040 GP26 includes the ADC FUNCSEL entry

- **WHEN** rp2040 `gpio.hpp` is emitted
- **THEN** the `kValidAltFunctions` array on
  `GpioSemanticTraits<PinId::GP26>` contains the FUNCSEL index for ADC0
  (the upstream IR records this via the synthetic `peripheral = "ADC"`
  binding — exact af_number is consumed verbatim from the family-patch
  data, no transformation)
