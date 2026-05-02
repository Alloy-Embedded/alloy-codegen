## ADDED Requirements

### Requirement: Published Runtime Contract SHALL Include `pins.h` For Every Admitted Device

For every admitted device, alloy-codegen SHALL emit a runtime-lite
header `pins.h` carrying typed pin identity, typed pin routes, and
typed pin constraint accessors.  The header SHALL live next to the
existing `peripheral_traits.h`, `runtime_init.c`, `linker.ld`, and
`vector_table.c` artifacts.

#### Scenario: STM32 G0 device publishes `pins.h`

- **WHEN** alloy-codegen emits artifacts for `st/stm32g0/stm32g071rb`
- **THEN** the output tree contains
  `out/st/stm32g0/stm32g071rb/pins.h`
- **AND** the header defines `enum class PinId : uint16_t` with one
  entry per non-power pad in `device.pinout`
- **AND** the header defines a `constexpr std::array<PinRoute, N>
  kRoutes` whose size equals `len(synthesised.pin_routes)`

#### Scenario: SAM E70 device publishes `pins.h`

- **WHEN** alloy-codegen emits artifacts for
  `microchip/same70/atsame70q21b`
- **THEN** the output tree contains
  `out/microchip/same70/atsame70q21b/pins.h`
- **AND** every `PinRoute` in `kRoutes` carries an integer code in
  `[0, 4)` (PIO matrix functions A through D)

### Requirement: `pins.h` SHALL Be Zero-String

`pins.h` SHALL contain no semantic `const char*` fields. All routing,
identity, and constraint facts SHALL be expressed as enums, ids,
typed refs, integers, masks, or `std::array` literals of those.

#### Scenario: `pins.h` does not embed pad-name strings at runtime

- **WHEN** the pre-publication zero-string gate scans
  `out/<vendor>/<family>/<chip>/pins.h`
- **THEN** the gate finds zero `const char*` literals naming a
  pad, signal, or peripheral
- **AND** every `PinRoute` field is integral or an enum value

### Requirement: `pins.h` SHALL Carry The Backend Schema ID In Its Header Banner

`pins.h` SHALL declare its layout version and pinmux backend schema
id in a top-of-file banner so consumers can reject incompatible
backends at compile time.

#### Scenario: STM32 family banner declares the AF v1 schema

- **WHEN** a consumer includes `pins.h` from an STM32 device
- **THEN** the file's top-of-file comment contains
  `alloy.pinmux.stm32-af-v1` and a layout-version string
  (e.g. `// alloy-pins layout v1`)

### Requirement: `pins.h` Generation SHALL Be Deterministic

For a fixed canonical IR, `pins.h` SHALL be byte-identical across
runs on different machines, Python versions ≥ 3.13, and OSes.

#### Scenario: Diff against the golden file is empty

- **WHEN** the test suite regenerates `pins.h` for any admitted
  device and diffs against
  `tests/fixtures/emitted/<vendor>/<family>/<chip>/pins.h`
- **THEN** the diff is empty

## MODIFIED Requirements

### Requirement: Runtime Maps and Bindings SHALL Use Typed IDs Only

Family maps and device-scoped bindings SHALL use typed ids only for runtime relationships.
This SHALL include the new `pins.h` runtime-lite header.

#### Scenario: Alloy consumes peripheral, interrupt, DMA, pin, and package bindings

- **WHEN** the runtime reads `rcc_map.hpp`, `interrupt_map.hpp`, `dma_map.hpp`, `pins.h`,
  `package_map.hpp`, or device-scoped binding headers
- **THEN** those relationships are encoded with typed ids or refs
- **AND** no semantic string parsing is required

#### Scenario: Pin routes resolve via typed refs only

- **WHEN** alloy HAL calls `route_for<PeripheralId::USART2,
  SignalId::tx, PinId::pa2>()` on a `pins.h` from an STM32 G0 device
- **THEN** the return type is `PinRoute` (or backend-typed cell)
- **AND** the call requires no string label and no runtime table scan
