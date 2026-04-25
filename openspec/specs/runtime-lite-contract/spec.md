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

