## ADDED Requirements

### Requirement: CanonicalDeviceIR SHALL surface I2C controller hardware-feature descriptors

`CanonicalDeviceIR` SHALL surface I2C / TWI hardware-feature facts via an `i2c_peripherals` tuple of `I2cPeripheralDescriptor` records. Each descriptor MUST carry the silicon-fixed facts that alloy's `I2cMaster<T>` concept relies on at compile time:

- `peripheral_id` — vendor name (`"I2C0"`, `"I2C1"`, `"TWI0"`,…).
- `base_address` — peripheral base, from SVD or ATDF.
- `clock_source` — STM32-only token (`"pclk"`, `"hsi16"`, `"sysclk"`),
  `None` on families whose I2C clock is family-fixed.
- `dma_req_tx`, `dma_req_rx` — DMAMUX line / RP2040 DREQ index, `None`
  when the controller has no DMA-attached path.
- `valid_sda_pins`, `valid_scl_pins` — sorted ascending tuple of GPIO
  pad numbers that can route this controller's SDA / SCL signal. The
  empty tuple is the **`AllGpios{}` sentinel** used by Espressif's IO
  matrix to mean "any pad accepted".
- `gpio_matrix_in_sda_signal`, `gpio_matrix_in_scl_signal`,
  `gpio_matrix_out_sda_signal`, `gpio_matrix_out_scl_signal` —
  Espressif IO-matrix signal indices, `None` on families with fixed pin
  routing.
- `supports_fast_mode_plus` — `true` for ESP32-S3 + STM32G0/F4 (1 MHz
  Fm+); `false` otherwise.
- `portmux_alt` — AVR-DA PORTMUX alternate-pin flag, `None` elsewhere.

`Device.i2c_peripherals` MUST default to the empty tuple for devices
without I2C hardware so existing fixtures stay byte-stable.

#### Scenario: STM32G071RB admits two I2C peripherals via PCLK

- **WHEN** the normalizer processes STM32G071RB
- **THEN** `Device.i2c_peripherals` contains entries for `I2C1`
  (`base_address = 0x40005400`) and `I2C2` (`base_address = 0x40005800`)
- **AND** both carry `clock_source = "pclk"`
- **AND** `valid_sda_pins` / `valid_scl_pins` are non-empty (sourced
  from the ST Open Pin Data AF table)

#### Scenario: ESP32-C3 admits a single I2C with the AllGpios sentinel

- **WHEN** the normalizer processes ESP32-C3
- **THEN** `Device.i2c_peripherals` contains exactly one entry
  (`peripheral_id = "I2C0"`)
- **AND** `valid_sda_pins == ()` (the AllGpios sentinel — any pad routes
  via the IO matrix)
- **AND** `gpio_matrix_in_sda_signal` / `gpio_matrix_out_sda_signal`
  carry the C3 IO-matrix indices

#### Scenario: RP2040 records pin constraints from datasheet Table 2-5

- **WHEN** the rp2040 device is normalized
- **THEN** `Device.i2c_peripherals` contains entries for `I2C0` and
  `I2C1`
- **AND** I2C0 carries `valid_sda_pins == (0, 4, 8, 12, 16, 20, 24, 28)`
- **AND** I2C0 carries `valid_scl_pins == (1, 5, 9, 13, 17, 21, 25, 29)`
- **AND** I2C0 carries `dma_req_tx = 32`, `dma_req_rx = 33` (datasheet
  Table 2-7)

#### Scenario: Devices without I2C carry an empty tuple

- **WHEN** the normalizer processes any device without an I2C / TWI
  controller
- **THEN** `Device.i2c_peripherals` is the empty tuple
- **AND** the field is omitted from the serialized canonical IR JSON
