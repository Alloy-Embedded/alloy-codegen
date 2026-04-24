# artifact-contract Specification

## Purpose
TBD - created by archiving change build-best-in-class-generator-core. Update Purpose after archive.
## Requirements
### Requirement: Published runtime contract exposes system-control fabric

The supported runtime C++ contract MUST publish typed device-scoped system-control facts needed by
Alloy and advanced consumers.

#### Scenario: Runtime contract includes interrupts, resets, and clock dependencies
- **WHEN** a foundational device is published
- **THEN** its runtime contract exposes typed interrupt facts, reset-control facts, and clock
  dependency facts
- **AND** those facts live under `generated/runtime/devices/<device>/`

### Requirement: Published runtime contract exposes formal capabilities

The supported runtime C++ contract MUST expose formal capability descriptors for runtime-supported
peripherals.

#### Scenario: Capabilities are published as supported contract facts
- **WHEN** a foundational device is published
- **THEN** runtime-supported peripherals publish typed capability facts
- **AND** those facts are queryable without legacy reflection artifacts

### Requirement: Publication emits explainability and provenance reports

Publication MUST emit machine-readable explainability and provenance outputs for runtime-critical
generated facts.

#### Scenario: Publication reports explain emitted facts
- **WHEN** a foundational family is published
- **THEN** reports identify the source, patch, or inference path behind runtime-critical facts
- **AND** they explicitly mark unsupported or heuristic coverage

### Requirement: Runtime C++ Artifact Contract SHALL Be Zero-String

All runtime-consumed generated C++ artifacts SHALL expose no semantic string fields.

#### Scenario: Alloy includes generated runtime headers
- **WHEN** Alloy includes runtime-facing generated C++ headers from `alloy-devices`
- **THEN** the consumed structs and tables contain only enums, ids, refs, addresses, offsets,
  widths, masks, counts, and integral values
- **AND** they do not contain semantic `const char*` fields such as schema names, kind names,
  signal names, package names, or register names

### Requirement: Runtime Maps and Bindings SHALL Use Typed IDs Only

Family maps and device-scoped bindings SHALL use typed ids only for runtime relationships.

#### Scenario: Alloy consumes peripheral, interrupt, DMA, pin, and package bindings
- **WHEN** the runtime reads `rcc_map.hpp`, `interrupt_map.hpp`, `dma_map.hpp`, `pins.hpp`,
  `package_map.hpp`, or device-scoped binding headers
- **THEN** those relationships are encoded with typed ids or refs
- **AND** no semantic string parsing is required

### Requirement: IP and Capability Headers SHALL Be Fully Typed

Runtime-consumed IP and capability headers SHALL publish typed profile information without
semantic string fields.

#### Scenario: Alloy dispatches on an IP profile
- **WHEN** Alloy consumes `generated/ip/*.hpp` or capability overlays
- **THEN** it can identify backend schema, peripheral class, and signal roles from typed ids
- **AND** it does not need textual labels to dispatch behavior

### Requirement: Reflection Headers MUST Not Be The Default Runtime Boundary

Headers such as connector graphs, clock maps, and other family-wide reflective inventories SHALL
be documented and emitted as reflection artifacts. They SHALL NOT be the primary hot-path
contract for `alloy`.

#### Scenario: Generated layout distinguishes contract purpose

- **WHEN** a consumer inspects the emitted tree
- **THEN** reflection-oriented artifacts and runtime-lite artifacts are distinguishable by path
  or naming convention

### Requirement: Runtime-Lite Headers SHALL Be Minimal And Compile-Time Oriented

Runtime-lite headers SHALL publish only the information required for runtime-owned hot-path
consumption, using typed ids, refs, trait specializations, and compact `constexpr` data.

#### Scenario: Runtime-lite peripheral instance header avoids reflection payload

- **WHEN** a device-scoped runtime-lite peripheral instance header is emitted
- **THEN** it exposes instance-local typed data needed by the runtime
- **AND** it does not require human-readable reflective payload to be usable

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
- **AND** it defines at least one `inline bool apply_clock_profile_*()` helper
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

### Requirement: Runtime contract expands to the remaining high-value peripheral classes

The supported runtime contract MUST eventually cover the major peripheral classes required by
modern embedded products.

#### Scenario: New peripheral classes follow the runtime-only contract
- **WHEN** CAN, RTC, watchdog, USB, ETH, QSPI/OSPI, SDMMC, or advanced timer features are added
- **THEN** they are published through the typed runtime contract
- **AND** they do not rely on legacy reflection-oriented C++ artifacts

### Requirement: Runtime Headers SHALL Expose Typed Binding Contracts

The emitted C++ artifact contract SHALL expose typed binding descriptors for peripheral
instances, registers, fields, interrupts, DMA, and connector operations.

#### Scenario: Alloy imports generated runtime headers
- **WHEN** Alloy includes the runtime-facing headers for a device
- **THEN** it can discover peripheral bindings, register IDs, field IDs, interrupt bindings,
  and DMA bindings through typed descriptors
- **AND** it does not need to parse comma-separated payloads to recover relationships

### Requirement: Register and Field Headers SHALL Be Published for Runtime-Owned Schemas

The emitted device-scoped artifacts SHALL include register and field descriptor headers for
runtime-owned backend schemas in foundational families.

#### Scenario: Foundational device is published
- **WHEN** a foundational family device is published to `alloy-devices`
- **THEN** its generated artifact tree includes `register_map.hpp` and `register_fields.hpp`
- **AND** those headers provide enough information for Alloy to address registers and fields
  without handwritten offsets

### Requirement: Connector and Clock Artifacts SHALL Use Structured Arrays

Connector and clock artifacts SHALL publish structured arrays and typed identifier references
as the primary runtime interface.

#### Scenario: Route operation and selector descriptors are emitted
- **WHEN** `connector_tables.hpp` and `clock_tree_lite.hpp` are emitted
- **THEN** candidate, group, selector, gate, reset, and operation relationships are encoded
  through typed IDs and structured rows
- **AND** any human-readable strings are secondary diagnostics rather than required runtime
  inputs

### Requirement: Linker script contract SHALL support XIP memory layout

The linker script emitter MUST produce valid output for devices with `xip-flash` memory
regions, emitting the BOOT2 stage placeholder section and XIP text region alongside the
standard SRAM regions.

#### Scenario: RP2040 device.ld contains BOOT2 and XIP sections

- **WHEN** `device.ld` is emitted for a device with a `xip-flash` memory region
- **THEN** the linker script MEMORY block contains a `BOOT2 (rx)` region of 256 bytes
  at the start of the XIP window
- **AND** the linker script MEMORY block contains an `XIP_MAIN (rx)` region for the
  remaining XIP-mapped flash space
- **AND** the linker script defines `__boot2_start`, `__boot2_end`, `__boot2_size`,
  `__xip_text_start`, and `__xip_text_end` symbols
- **AND** the standard SRAM-based `.data`, `.bss`, and `.stack` sections are also present

#### Scenario: Standard flash devices produce unmodified linker scripts

- **WHEN** `device.ld` is emitted for a device with a `flash` (not `xip-flash`) memory region
- **THEN** no `BOOT2` section is present
- **AND** the linker script structure is identical to existing foundational devices

### Requirement: Startup artifact contract SHALL accommodate XIP flash initialization

The emitted `startup.cpp` for XIP-booting devices MUST include a flash initialization
step and a boot2 placeholder before the standard data-copy and BSS-zero loop.

#### Scenario: RP2040 startup.cpp contains XIP init and boot2 placeholder

- **WHEN** `startup.cpp` is emitted for a device with a `xip-flash` memory region
- **THEN** the emitted file includes a `.boot2` section placeholder (256-byte weak symbol)
- **AND** it calls `xip_init()` before the `.data` copy loop
- **AND** it contains a generated comment noting that the boot2 placeholder must be
  replaced with a flash-specific second-stage bootloader for hardware execution
- **AND** the standard `.data` copy, `.bss` zero, and `main()` call are present

#### Scenario: Non-XIP startup is unaffected

- **WHEN** `startup.cpp` is emitted for a device without a `xip-flash` memory region
- **THEN** no `xip_init()` call or `.boot2` placeholder is present
- **AND** the standard startup sequence is emitted unchanged

### Requirement: PIO driver semantics stub SHALL be emitted and tracked

Devices with PIO peripherals SHALL have a `driver_semantics/pio.hpp` stub emitted and the
`runtime-support:pio` capability SHALL be tracked in the capability regression gate.

#### Scenario: RP2040 emits pio.hpp as an explicit stub

- **WHEN** `driver_semantics/pio.hpp` is emitted for an RP2040 device
- **THEN** the file contains a `PioSemanticTraits<Id>` template with `kPresent = false`
- **AND** all register and field references are `kInvalidRegisterRef` / `kInvalidFieldRef`
- **AND** `kPioSemanticPeripherals` is an array of size 0

#### Scenario: runtime-support:pio is tracked across publication cycles

- **WHEN** the RP2040 device is published and a subsequent publication cycle runs
- **THEN** the presence of `runtime-support:pio` in the capability manifest is checked
  for regression
- **AND** a publication that drops `runtime-support:pio` from RP2040 is blocked

### Requirement: Typed Peripheral Instance Contract
The emitted `generated/devices/<device>/peripheral_instances.hpp` SHALL expose only typed
primary runtime fields for bindings, clock/reset references, and capability coverage.

#### Scenario: Peripheral instance header avoids CSV/runtime strings
- **WHEN** a device is emitted
- **THEN** each peripheral instance descriptor exposes typed offsets/counts and typed binding
  references
- **AND** it does not require CSV strings or RCC signal strings for runtime execution

### Requirement: Typed Connector Runtime Contract
The emitted `generated/connector_tables.hpp` SHALL expose route requirements and route
operations with typed domains and ids as the primary runtime contract.

#### Scenario: Connector tables are executable without parsing strings
- **WHEN** Alloy consumes route requirements or operations
- **THEN** it can execute them from typed ids, domains, and numeric values alone
- **AND** any human-readable strings are clearly secondary diagnostics

### Requirement: Typed Clock Reset Contract
The emitted family-level clock/reset contract SHALL publish typed gate/reset bindings rather
than raw textual signals as the primary runtime API.

#### Scenario: Family clock header is typed
- **WHEN** a foundational family is emitted
- **THEN** its clock/reset header publishes typed references to gates and resets
- **AND** the runtime does not need to parse an RCC/PMC signal string to enable or reset a
  peripheral

### Requirement: ESP32 families emit runtime headers matching the standard contract shape

Espressif ESP32 devices MUST emit the same runtime header set as ARM foundational devices,
with the exception of artifacts that are explicitly scoped to a different architecture family.

#### Scenario: ESP32-C3 runtime device headers are present and valid

- **WHEN** the pipeline emits artifacts for an ESP32-C3 device
- **THEN** `generated/runtime/devices/esp32c3/interrupts.hpp` is present and contains
  `enum class InterruptId` and `kInterruptDescriptors`
- **AND** `generated/runtime/devices/esp32c3/clock_graph.hpp` is present and contains
  `enum class ClockNodeId` and `kClockDependencies`
- **AND** `generated/runtime/devices/esp32c3/peripheral_instances.hpp` is present and
  contains `enum class PeripheralId` and `kPeripheralInstances`
- **AND** `generated/runtime/devices/esp32c3/systick.hpp` is NOT emitted (RISC-V has no SysTick)
- **AND** the artifact contract treats that omission as valid because `systick.hpp`
  is Cortex-M-scoped

#### Scenario: ESP32-C3 startup artifact uses RISC-V conventions

- **WHEN** the pipeline emits startup artifacts for an ESP32-C3 device
- **THEN** the startup file uses RISC-V reset vector conventions (`mtvec`, BSS clear, `main()`)
- **AND** no ARM CMSIS vector table (`__Vectors[]` at address 0) is emitted

#### Scenario: ESP32-S3 runtime device headers are present and valid

- **WHEN** the pipeline emits artifacts for an ESP32-S3 device
- **THEN** `generated/runtime/devices/esp32s3/interrupts.hpp` is present with Xtensa interrupt IDs
- **AND** `generated/runtime/devices/esp32s3/clock_graph.hpp` is present with ESP32-S3 clock nodes
- **AND** the startup file uses Xtensa reset vector conventions (`VECBASE`, level handlers)
- **AND** `generated/runtime/devices/esp32s3/systick.hpp` is NOT emitted
- **AND** the artifact contract treats that omission as valid because `systick.hpp`
  is Cortex-M-scoped

#### Scenario: Consumer smoke test compiles ESP32 runtime headers without error

- **WHEN** the consumer smoke test runs for an ESP32-C3 device
- **THEN** it compiles `interrupts.hpp`, `clock_graph.hpp`, and `peripheral_instances.hpp`
  without errors
- **AND** it does not require any ARM-specific include paths or definitions

### Requirement: Published Espressif artifacts are covered by the artifact contract validator

The artifact contract checker MUST validate ESP32 device artifacts using the same required-paths
and content checks applied to ARM devices.

#### Scenario: Artifact contract catches missing ESP32 interrupt header

- **WHEN** the artifact contract validator runs for an ESP32-C3 device
- **THEN** it verifies that `generated/runtime/devices/esp32c3/interrupts.hpp` is present
- **AND** it verifies the file contains `enum class InterruptId` and `kInterruptDescriptors`
- **AND** it reports a violation if either check fails

### Requirement: Supplementary non-SVD sources are part of the validated contract

When a published family depends on supplementary non-SVD sources, the contract MUST record
their provenance and treat them as part of the supported input set.

#### Scenario: IO Matrix publication records supplementary-source provenance

- **WHEN** the pipeline publishes artifacts for an Espressif family that uses `gpio_sig_map.h`
- **THEN** the publication metadata records that supplementary source alongside the SVD source
- **AND** emitted IO Matrix facts can be traced back to that supplementary source
- **AND** the absence of that source metadata is a contract violation

#### Scenario: Artifact contract catches missing ESP32 clock graph header

- **WHEN** the artifact contract validator runs for an ESP32-C3 device
- **THEN** it verifies that `generated/runtime/devices/esp32c3/clock_graph.hpp` is present
- **AND** it verifies the file contains `enum class ClockNodeId` and `kClockDependencies`
- **AND** it reports a violation if either check fails

### Requirement: AVR-DA devices emit runtime headers matching the standard contract shape

Microchip AVR-DA devices MUST emit the same runtime header set as ARM foundational devices,
with the exception of headers that are explicitly gated on Cortex-M architecture, and with
an AVR-specific startup artifact instead of an ARM CMSIS vector table.

#### Scenario: AVR128DA32 runtime device headers are present and valid

- **WHEN** the pipeline emits artifacts for an AVR128DA32 device
- **THEN** `generated/runtime/devices/avr128da32/interrupts.hpp` is present and contains
  `enum class InterruptId` and `kInterruptDescriptors`
- **AND** `generated/runtime/devices/avr128da32/clock_graph.hpp` is present and contains
  `enum class ClockNodeId` and `kClockDependencies`
- **AND** `generated/runtime/devices/avr128da32/peripheral_instances.hpp` is present and
  contains `enum class PeripheralId` and `kPeripheralInstances`
- **AND** `generated/runtime/devices/avr128da32/systick.hpp` is NOT emitted (AVR8 has no SysTick)

#### Scenario: AVR128DA32 startup artifact uses AVR8 vector table conventions

- **WHEN** the pipeline emits startup artifacts for an AVR128DA32 device
- **THEN** the startup file places a weak-symbol vector table in `.section .vectors`
  using C function pointer slots (`__vector_0` through `__vector_N`)
- **AND** it includes crt0 initialization: `.data` section copy from flash,
  `.bss` section zeroing, and a call to `main()`
- **AND** no ARM CMSIS vector table (`__Vectors[]` at address 0) is emitted
- **AND** no RISC-V `mtvec` initialization is emitted

#### Scenario: Consumer smoke test compiles AVR128DA32 runtime headers without error

- **WHEN** the consumer smoke test runs for an AVR128DA32 device
- **THEN** it compiles `interrupts.hpp`, `clock_graph.hpp`, and `peripheral_instances.hpp`
  using an AVR8 target triple (`avr-unknown-none`)
- **AND** it does not require any ARM-specific include paths or definitions

### Requirement: Published AVR-DA artifacts are covered by the artifact contract validator

The artifact contract checker MUST validate AVR-DA device artifacts using the same
required-paths and content checks applied to ARM and ESP32 devices.

#### Scenario: Artifact contract catches missing AVR interrupt header

- **WHEN** the artifact contract validator runs for an AVR128DA32 device
- **THEN** it verifies that `generated/runtime/devices/avr128da32/interrupts.hpp` is present
- **AND** it verifies the file contains `enum class InterruptId` and `kInterruptDescriptors`
- **AND** it reports a violation if either check fails

#### Scenario: Artifact contract catches missing AVR clock graph header

- **WHEN** the artifact contract validator runs for an AVR128DA32 device
- **THEN** it verifies that `generated/runtime/devices/avr128da32/clock_graph.hpp` is present
- **AND** it verifies the file contains `enum class ClockNodeId` and `kClockDependencies`
- **AND** it reports a violation if either check fails

#### Scenario: Artifact contract does not require systick header for AVR devices

- **WHEN** the artifact contract validator runs for an AVR128DA32 device
- **THEN** it does not flag the absence of `systick.hpp` as a violation
- **AND** it only enforces the systick requirement for Cortex-M family devices

