# runtime-lite-contract Specification

## Purpose
TBD - created by archiving change split-reflection-and-runtime-lite-contract. Update Purpose after archive.
## Requirements
### Requirement: Reflection And Runtime-Lite Contracts SHALL Be Distinct

`alloy-codegen` SHALL emit generated C++ artifacts in two explicit categories:

- a reflection contract for validation, tooling, smoke compilation, and inspection
- a runtime-lite contract for hot-path runtime consumption

The runtime-lite contract SHALL be stable and documented as the preferred runtime boundary for
`alloy`.

#### Scenario: Foundational family publish includes both contract types

- **WHEN** `alloy-codegen` publishes artifacts for a foundational family
- **THEN** the publication includes both reflection artifacts and runtime-lite artifacts
- **AND** the runtime-lite artifacts are sufficient for runtime-owned peripheral classes

### Requirement: Runtime-Lite Contract SHALL Avoid Family-Wide Lookup As Normal Usage

Runtime-lite artifacts SHALL represent runtime-owned hardware facts using compile-time-friendly
constructs such as typed specializations, typed aliases, compact refs, and `constexpr` packs,
rather than requiring generic family-wide table scans.

#### Scenario: One UART route is lowered without generic candidate scanning

- **WHEN** a published connector route is consumed by the runtime-lite contract
- **THEN** the runtime can obtain the selected instance, register refs, field refs, clock
  bindings, and route operations without scanning the family connector graph at runtime

### Requirement: Runtime-Lite Contract SHALL Cover Foundational Runtime-Owned Drivers

The runtime-lite contract SHALL cover at least the foundational runtime-owned use cases:

- GPIO enable and mode configuration
- UART open on a chosen connector
- SPI open on a chosen connector
- I2C open on a chosen connector

#### Scenario: Foundational families publish runtime-lite coverage

- **WHEN** `st/stm32g0`, `st/stm32f4`, `microchip/same70`, and `nxp/imxrt1060` are emitted
- **THEN** each family includes runtime-lite artifacts sufficient to implement those driver
  paths without reflection-table dependency

### Requirement: Driver Semantics SHALL Resolve HAL-Referenced Fields To Valid RuntimeFieldRef

The generated driver-semantics header SHALL emit a `RuntimeFieldRef` whose
`valid` flag is true and whose `bit_offset` / `bit_width` match the vendor
register description for every register bit referenced by a public HAL
backend in the admitted families. `kInvalidFieldRef` SHALL NOT appear in
the HAL-referenced field set of `driver_semantics/*.hpp`.

#### Scenario: TWIHS START / STOP / MSEN bits resolve on SAM E70

- **WHEN** the Microchip SAM E70 family is emitted
- **THEN** for each TWIHS instance, the driver-semantics header defines
  `kStartField`, `kStopField`, `kMsenField`, `kMsdisField`, and `kSvdisField`
  as `RuntimeFieldRef` entries with `valid = true`, `bit_offset` /
  `bit_width` populated against `TWIHS.CR`
- **AND** the TWIHS HAL backend can drive START / STOP without raw bit masks

### Requirement: Runtime-Lite Contract SHALL Emit Typed Peripheral Base Accessor

The generated runtime-lite peripheral-instances header SHALL expose
`template <PeripheralId Id> constexpr auto alloy::device::base() noexcept`
returning `PeripheralInstanceTraits<Id>::kBaseAddress`.

#### Scenario: Probe obtains GMAC base through typed accessor

- **WHEN** user code calls `alloy::device::base<PeripheralId::GMAC>()` on a
  SAM E70 device
- **THEN** the accessor returns the GMAC base address
  (`0x40050000u` for ATSAME70Q21B)
- **AND** no numeric base-address literal is required in the probe source

### Requirement: Runtime-Lite Contract SHALL Emit Typed Clock Enable / Disable Helpers

The generated runtime-lite clock-bindings header SHALL expose
`alloy::clock::enable(PeripheralId)` and `alloy::clock::disable(PeripheralId)`
free functions that resolve to the correct clock-gate register write for
the selected device, consuming the `ClockGateId` + clock-bindings artifacts
already emitted.

#### Scenario: Adopter enables the GMAC peripheral clock

- **WHEN** user code calls `alloy::clock::enable(PeripheralId::GMAC)` on a
  SAM E70 device
- **THEN** the helper writes bit `(39 - 32)` into `PMC_PCER1`
- **AND** the adopter does not need to know the PID number or the register
  address

### Requirement: Runtime-Lite Contract SHALL Emit Typed Pin-Route Helper

The generated runtime-lite routes header SHALL expose
`template <PinId, PeripheralId, SignalId> void alloy::pinmux::route() noexcept`
that writes the vendor-correct selector register(s) for the route already
captured in the table (`ABCDSR1` / `ABCDSR2` / `PDR` on SAM E70).

#### Scenario: Adopter muxes a GMAC pin through the typed helper

- **WHEN** user code calls
  `alloy::pinmux::route<PinId::PD0, PeripheralId::GMAC, SignalId::signal_gtxck>()`
- **THEN** the helper writes the peripheral-A selector (value `0`) into
  `PIOD.ABCDSR1` / `ABCDSR2` at pin offset 0 and releases PIOD bit 0 to
  peripheral control via `PDR`

#### Scenario: Invalid route triple fails at compile time

- **WHEN** user code requests a `(Pin, Peripheral, Signal)` triple that is
  not present in the emitted routes table
- **THEN** the emitted helper produces a `static_assert` diagnostic naming
  the missing route

### Requirement: pio.hpp SHALL define a populated PioSemanticTraits surface

Every emitted `driver_semantics/pio.hpp` SHALL declare a primary
`PioSemanticTraits<PioId>` template whose body provides zero-valued defaults
for the full set of compile-time PIO facts so that downstream alloy concept
checks can rely on the fields existing regardless of family:

- `kPresent: bool` (default `false`)
- `kStateMachineCount: std::uint8_t`
- `kInstructionMemoryDepth: std::uint8_t`
- `kTxFifoDepth: std::uint8_t`
- `kRxFifoDepth: std::uint8_t`
- `kGpioBase: std::uint8_t`
- `kGpioCount: std::uint8_t`
- `kBaseAddress: std::uint32_t`
- `kDreqTx: std::uint8_t`
- `kDreqRx: std::uint8_t`

Devices without PIO hardware SHALL emit only the primary template (all defaults).

#### Scenario: Non-PIO families keep zero-cost defaults

- **WHEN** a device with `pio_blocks == []` is emitted
- **THEN** the emitted `pio.hpp` declares the primary template with all fields
  defaulted to zero (and `kPresent = false`)
- **AND** no `PioSemanticTraits<PioId::*>` specializations are emitted

#### Scenario: RP2040 emits fully populated specializations

- **WHEN** the RP2040 device is emitted
- **THEN** `pio.hpp` contains a `PioSemanticTraits<PioId::Pio0>` specialization
  with `kPresent = true`, `kStateMachineCount = 4`, `kInstructionMemoryDepth = 32`,
  `kTxFifoDepth = 4`, `kRxFifoDepth = 4`, `kGpioBase = 0`, `kGpioCount = 30`,
  `kBaseAddress = 0x50200000u`, `kDreqTx = 0`, `kDreqRx = 4`
- **AND** an analogous `PioSemanticTraits<PioId::Pio1>` specialization is emitted
  with `kBaseAddress = 0x50300000u`, `kDreqTx = 8`, `kDreqRx = 12`

### Requirement: pio.hpp SHALL define StateMachineSemanticTraits per PIO state machine

Every emitted `driver_semantics/pio.hpp` SHALL declare a primary
`StateMachineSemanticTraits<PioId, std::uint8_t Sm>` template providing
`kPresent`, `kDreqTx`, and `kDreqRx` defaults so consumer code can index
state-machine DREQs at compile time without runtime arithmetic.

For each `PioDescriptor` in `device.pio_blocks`, the emitter SHALL produce
`state_machine_count` specializations whose `kDreqTx = dreq_tx_base + sm` and
`kDreqRx = dreq_rx_base + sm` for `sm` in `[0, state_machine_count)`.

#### Scenario: RP2040 emits 8 state-machine specializations

- **WHEN** the RP2040 device is emitted
- **THEN** `pio.hpp` declares `StateMachineSemanticTraits<PioId::Pio0, 0>`
  through `StateMachineSemanticTraits<PioId::Pio1, 3>` (8 specializations total)
- **AND** `StateMachineSemanticTraits<PioId::Pio0, 3>::kDreqTx == 3`
- **AND** `StateMachineSemanticTraits<PioId::Pio1, 2>::kDreqTx == 10`
- **AND** every specialization sets `kPresent = true`

#### Scenario: Non-PIO families emit only the primary StateMachineSemanticTraits template

- **WHEN** a device with `pio_blocks == []` is emitted
- **THEN** `pio.hpp` declares the primary `StateMachineSemanticTraits` template
  with `kPresent = false` and zero-valued DREQ defaults
- **AND** emits no `StateMachineSemanticTraits<...>` specializations

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

