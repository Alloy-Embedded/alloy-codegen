## ADDED Requirements

### Requirement: RP2040 IR SHALL surface GPIO pad topology via gpio_pins

For RP2040, the canonical IR SHALL populate `Device.gpio_pins` with one
`GpioPinDescriptor` per admitted pad (`GP0`..`GP29` on the QFN56 package,
filtered to the package's bonded pads on `pico`). The descriptor uses
`port = "GPIO"` and `port_offset = 0` (single GPIO peripheral on RP2040),
`pin_index = pad number`, and the FUNCSEL alternate-function table
already produced by the family-patch normalize path
(`af_number = FUNCSEL index 1..9`).

#### Scenario: rp2040 IR exposes 30 GPIO descriptors

- **WHEN** the rp2040 device is normalized
- **THEN** `device.gpio_pins` has exactly 30 entries (`GP0`..`GP29`)
- **AND** every entry carries `port = "GPIO"`, `port_offset = 0`,
  `is_input_only = false`
- **AND** the `pico` device is normalized with 26 `gpio_pins` (the QFN56
  pads minus GP23/GP24/GP29 which are not bonded on the Pico package)

#### Scenario: rp2040 GP0 records SPI / UART / I2C alternate functions

- **WHEN** `device.gpio_pins` is populated for rp2040
- **THEN** the `GP0` entry carries alt-function entries with
  `(af_number=1, signal_name="RX", peripheral="SPI0")`,
  `(af_number=2, signal_name="TX", peripheral="UART0")`, and
  `(af_number=3, signal_name="SDA", peripheral="I2C0")`

### Requirement: RP2040 IR SHALL include UART, SPI, and ADC peripheral facts via gpio_pins AF table

The RP2040 GPIO descriptors SHALL be authoritative for the per-pin
function table; downstream emitters that produce `uart.hpp`, `spi.hpp`,
and `adc.hpp` SHALL derive valid-pin sets by filtering
`device.gpio_pins[*].alt_functions` for the relevant peripheral.

#### Scenario: UART0 valid TX pin set is derivable from gpio_pins

- **WHEN** the rp2040 device is normalized
- **THEN** filtering `device.gpio_pins` for entries whose
  `alt_functions` include `peripheral = "UART0"` and `signal_name = "TX"`
  yields the pad numbers `{0, 12, 16, 28}`

#### Scenario: ADC channel pins are derivable from gpio_pins

- **WHEN** the rp2040 device is normalized
- **THEN** filtering `device.gpio_pins` for entries whose
  `alt_functions` include `peripheral = "ADC"` yields the pad numbers
  `{26, 27, 28, 29}` (the four external analog inputs)
