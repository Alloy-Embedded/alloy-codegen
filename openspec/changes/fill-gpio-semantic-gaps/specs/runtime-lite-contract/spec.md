## ADDED Requirements

### Requirement: GpioSemanticTraits SHALL expose alternate-function topology

Every emitted `driver_semantics/gpio.hpp` SHALL extend the primary
`GpioSemanticTraits<PinId>` template body with four new compile-time fields
so downstream alloy concept checks can validate pin/AF assignments without
runtime indexing:

- `kPortOffset: std::uint32_t` — port-base offset from the family's GPIOA
  base (e.g. `GPIOA=0`, `GPIOB=0x400` on STM32). Zero on the primary template.
- `kPinIndex: std::uint32_t` — bit position of the pin within its port.
  Zero on the primary template.
- `kMaxAltFunction: std::uint8_t` — highest alternate-function index this
  pin supports. Zero on the primary template.
- `kValidAltFunctions: std::array<std::uint8_t, N>` — the sorted set of
  alternate-function numbers valid for this pin, with `N` derived from
  `device.gpio_pins` data (empty array on the primary template).

For every entry in `device.gpio_pins` whose port and pin-index resolve to a
named `PinId`, the emitter SHALL produce a `GpioSemanticTraits<PinId::...>`
specialization populating these four fields. Specializations that already
exist for register-level GPIO semantics (e.g. NXP iMXRT) SHALL also include
the four new fields, defaulted to zero / empty when no AF data is available
for the pin.

#### Scenario: Non-GPIO-mapped families keep zero defaults

- **WHEN** a device with `gpio_pins == ()` is emitted
- **THEN** the primary `GpioSemanticTraits<PinId>` template declares the
  four new fields with zero / empty defaults
- **AND** no AF-driven specializations are emitted

#### Scenario: STM32G071RB emits populated AF specializations

- **WHEN** the STM32G071RB device is emitted
- **THEN** the primary `GpioSemanticTraits<PinId>` template carries the
  four zero-defaulted fields
- **AND** for `PA5` (the LED pin on Nucleo-G071RB), the
  `GpioSemanticTraits<PinId::PA5>` specialization carries
  `kPortOffset = 0u`, `kPinIndex = 5u`, a `kMaxAltFunction` value
  reflecting the pin's actual maximum AF, and a non-empty
  `kValidAltFunctions` array sorted ascending
- **AND** every populated specialization keeps `kPresent = true`
