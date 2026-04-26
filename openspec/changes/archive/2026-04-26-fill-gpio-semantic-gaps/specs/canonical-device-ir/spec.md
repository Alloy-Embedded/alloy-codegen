## ADDED Requirements

### Requirement: IR SHALL model GPIO pin alternate-function topology with structured descriptors

The canonical IR SHALL represent the alternate-function (AF) topology of every
GPIO-capable pin on a device using two new structured types:

- `AltFunctionDescriptor(af_number: int, signal_name: str, peripheral: str)`
  records one entry of the per-pin AF table.
- `GpioPinDescriptor(pin_id, port, pin_index, port_offset, alt_functions,
  is_input_only, provenance)` records the compile-time facts that downstream
  emitters need to populate `GpioSemanticTraits<PinId>` AF specializations
  (port enum / port-base offset, bit-position within the port, the sorted
  list of valid AF numbers, and an input-only flag for pads such as
  Espressif GPIO34–39).

`GpioPinDescriptor` SHALL be carried on `CanonicalDeviceIR` as
`gpio_pins: tuple[GpioPinDescriptor, ...]`, defaulting to an empty tuple for
devices whose normalizers have not yet been wired to populate it.

#### Scenario: STM32G071RB IR exposes GPIO pin topology

- **WHEN** the STM32G071RB device is normalized
- **THEN** `device.gpio_pins` is non-empty
- **AND** every entry has a non-null `port` (e.g. `"GPIOA"`) and a
  `pin_index` in `[0, 15]`
- **AND** entries with at least one alternate-function signal carry a
  non-empty `alt_functions` tuple sorted by `(af_number, signal_name)`
- **AND** every `AltFunctionDescriptor` references a peripheral that
  appears in `device.peripherals`

#### Scenario: Devices without GPIO topology leave gpio_pins empty

- **WHEN** any device whose normalizer has not yet been wired to populate
  GPIO topology is normalized
- **THEN** `device.gpio_pins` is an empty tuple
- **AND** the canonical IR JSON serialization omits the `gpio_pins` array

#### Scenario: GpioPinDescriptor data is provenance-tagged

- **WHEN** `device.gpio_pins` is populated from a vendor source
- **THEN** each `GpioPinDescriptor` carries provenance referencing the
  upstream artifact (e.g. ST Open Pin Data XML, Espressif gpio_sig_map.h,
  AVR ATDF) plus any patch ids that contributed to the entry
