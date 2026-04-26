## ADDED Requirements

### Requirement: CanonicalDeviceIR SHALL surface USB controller hardware-feature facts

Devices with a USB controller MUST expose a `usb_controllers` tuple of
`UsbControllerDescriptor` records on the canonical IR. Each descriptor
carries the static silicon facts the alloy `UsbDeviceController<T>` HAL
needs at compile time: base address, endpoint count, packet memory shape
(`dpram_base_address` / `dpram_size_bytes`), speed and host-mode
capability flags, fixed DM/DP pin assignments (when not IO-matrix
routed), DMA channel count, and clock-source token.

`Device.usb_controllers` MUST default to the empty tuple for devices
without USB hardware so existing fixtures stay byte-stable.

#### Scenario: STM32G0 admits a single Crystal-less USB FS controller

- **WHEN** the normalizer processes an STM32G0 device that admits the
  `USB` peripheral (e.g. STM32G0B1)
- **THEN** `Device.usb_controllers` contains one entry with
  `controller_id = "USB"`, `endpoint_count = 8`, `crystalless = true`,
  `dpram_size_bytes = 1024`, `clock_source = "hsi48-with-crs"`

#### Scenario: STM32F4 admits OTG FS with fixed DM/DP pins

- **WHEN** the normalizer processes an STM32F4 device that admits the
  `OTG_FS` peripheral
- **THEN** `Device.usb_controllers` contains an entry with
  `controller_id = "OTG_FS"`, `dm_pin = "PA11"`, `dp_pin = "PA12"`,
  `supports_dma = true`

#### Scenario: Devices without USB hardware carry an empty tuple

- **WHEN** the normalizer processes a device without USB (e.g.
  ESP32 classic, AVR-DA, ESP32-C3)
- **THEN** `Device.usb_controllers` is the empty tuple
- **AND** the field is omitted from the serialized canonical IR JSON
