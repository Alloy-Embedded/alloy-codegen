## ADDED Requirements

### Requirement: Publication emits a device-specific linker script

Each supported device MUST have a generated GCC linker script that fully describes its
memory layout, derived exclusively from `MemoryRegion` facts in the canonical IR.

#### Scenario: Linker script covers flash, SRAM, and startup sections

- **WHEN** the pipeline emits artifacts for any supported device
- **THEN** `generated/devices/<device>/device.ld` is present and contains a `MEMORY {}` block with at
  least one nonvolatile (flash) region and one volatile (SRAM) region
- **AND** the `SECTIONS {}` block places `.text` in flash, `.data` with correct
  `AT>` load address, `.bss` zero-init region, and a `__stack_top` symbol
- **AND** all region sizes and addresses match the canonical IR `MemoryRegion` facts

#### Scenario: Linker script is valid for the device toolchain

- **WHEN** the consumer validation step runs against the generated
  `generated/devices/<device>/device.ld`
- **THEN** the link succeeds without warnings about overlapping regions or missing symbols

### Requirement: Publication emits clock configuration code per device

Each supported device MUST have a generated `clock_config.hpp` providing at least one
ready-to-use clock profile function, derived from the canonical clock graph.

#### Scenario: Clock profile functions are present and compilable

- **WHEN** the pipeline emits artifacts for any supported device with a non-trivial clock tree
- **THEN** `generated/runtime/devices/<device>/clock_config.hpp` is present
- **AND** it defines at least one `constexpr void apply_clock_profile_*()` function
- **AND** `generated/runtime/devices/<device>/clock_profiles.hpp` enumerates the
  available `ClockProfileId` values for that device
- **AND** the consumer smoke test includes and calls a profile function without error

#### Scenario: Clock profile covers at minimum default and maximum PLL frequency

- **WHEN** a foundational device has a PLL in its clock tree
- **THEN** the emitted clock profiles include a default (no PLL, RC oscillator) profile
  and a maximum-frequency PLL profile
- **AND** the register write sequence in each profile follows the correct ordering
  (enable oscillator → wait ready → configure PLL → enable PLL → wait ready → switch)

### Requirement: Publication emits connector tables for compile-time pin validation

Each supported device MUST have a generated `connectors.hpp` providing typed
`GpioConnector` specializations for every valid pin-to-peripheral-signal combination,
and a static diagnostic for every invalid combination.

#### Scenario: Valid connector compiles without error

- **WHEN** application code instantiates `GpioConnector<Usart1, signal::Tx, GpioA9>`
  on a device where PA9 connects to USART1_TX
- **THEN** the instantiation compiles without error or warning
- **AND** the `af_number` and `signal_role` values are correct for that device

#### Scenario: Invalid connector produces a provenance-cited error

- **WHEN** application code instantiates `GpioConnector<Usart1, signal::Tx, GpioA0>`
  on a device where PA0 does not connect to USART1_TX
- **THEN** the compiler reports a `static_assert` failure
- **AND** the error message names the valid alternative pins for USART1_TX on that device
- **AND** the error message cites the source patch or SVD that defines those alternatives

### Requirement: Publication emits a formal capability manifest per device

Each supported device MUST have a generated capability manifest providing machine-readable
facts about runtime-supported peripheral features.

#### Scenario: Capability header enables compile-time feature guards

- **WHEN** a device's `capabilities.hpp` is included
- **THEN** peripheral capability constants are available as `constexpr` booleans and
  integers in the device namespace (e.g., `alloy::<device>::usart1::kHasDmaTx`,
  `alloy::<device>::usart1::kMaxBaudRate`)
- **AND** application code can use them in `static_assert` without any runtime cost

#### Scenario: Capability JSON sidecar is queryable by CMake

- **WHEN** the pipeline emits artifacts for a supported device
- **THEN** `generated/runtime/devices/<device>/capabilities.json` is present
- **AND** it contains capability entries for all runtime-supported peripherals
- **AND** it is valid JSON that a CMake `file(READ ...)` + `string(JSON ...)` call
  can parse to extract a capability value

### Requirement: Publication emits weak interrupt handler stubs per device

Each supported device MUST have a generated `interrupt_stubs.hpp` declaring all device
interrupt handlers as weak symbols, enabling application code to override them selectively.

#### Scenario: Interrupt stubs are present for all device interrupts

- **WHEN** the pipeline emits artifacts for a supported device
- **THEN** `generated/runtime/devices/<device>/interrupt_stubs.hpp` is present
- **AND** it declares a `weak` `extern "C"` function for every interrupt in
  `device.interrupts`
- **AND** each handler defaults to `Default_Handler` (infinite loop or reset)

#### Scenario: Application code can override any interrupt handler

- **WHEN** application code defines a non-weak `void USART1_IRQHandler()` and includes
  `interrupt_stubs.hpp`
- **THEN** the linker uses the application's definition without conflict
