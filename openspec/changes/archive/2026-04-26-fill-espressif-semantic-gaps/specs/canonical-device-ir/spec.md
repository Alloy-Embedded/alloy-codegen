## ADDED Requirements

### Requirement: CanonicalDeviceIR SHALL expose hardware-feature descriptors for Espressif peripherals

Devices on Espressif targets MUST surface six hardware-feature descriptor
tuples on the canonical IR — one per peripheral type called out by
``add-usb-hal``-class concept checks: `uart_peripherals`,
`spi_peripherals`, `adc_units`, `timer_units`, `dma_channels`, plus a
single `ledc` block. Each descriptor records the static silicon facts
(base address, FIFO depth / endpoint count, GPIO-matrix signal indices,
DMA support, IO-MUX fast-path pins, ADC channel→pin maps) that the
alloy concept-validated HAL needs at compile time.

These descriptors MUST default to empty for devices whose family
overlay doesn't ship the block, so existing fixtures stay byte-stable.

#### Scenario: ESP32 classic admits three UART peripherals with 128-byte FIFOs

- **WHEN** the normalizer processes ESP32 classic
- **THEN** `Device.uart_peripherals` contains three entries with
  `peripheral_id ∈ {"UART0", "UART1", "UART2"}`
- **AND** every entry carries `fifo_depth = 128` and `supports_dma = true`

#### Scenario: ESP32-C3 admits a single SPI peripheral without IO_MUX fast path

- **WHEN** the normalizer processes ESP32-C3
- **THEN** `Device.spi_peripherals` contains one entry with
  `peripheral_id = "SPI2"` and `has_iomux_fast_path = false`

#### Scenario: ESP32-S3 admits two ADC units with the second flagged as Wi-Fi-conflicted

- **WHEN** the normalizer processes ESP32-S3
- **THEN** `Device.adc_units` contains two entries
- **AND** `unit_id = "ADC2"` carries `conflicts_with_wifi = true`

#### Scenario: Non-Espressif devices carry empty hardware-feature tuples

- **WHEN** the normalizer processes a non-Espressif device (STM32, NXP,
  RP2040, AVR-DA, SAME70)
- **THEN** `Device.uart_peripherals`, `Device.spi_peripherals`,
  `Device.adc_units`, `Device.timer_units`, `Device.dma_channels` are
  the empty tuple
- **AND** `Device.ledc` is `None`
- **AND** all six fields are omitted from the serialized canonical IR JSON
