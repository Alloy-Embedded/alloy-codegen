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

### Requirement: Publication root carries an auto-generated device matrix README

The publish stage SHALL emit a `README.md` artifact at the publication root
listing every admitted `(vendor, family)` pair plus the devices, packages,
and peripherals each one carries.  The file is regenerated on every publish
from `DEVICE_REGISTRY` and the family/device patches and is byte-deterministic
across parallel matrix jobs.

#### Scenario: Every admitted family appears in the README table

- **WHEN** the publish stage runs for any `(vendor, family)` admitted in
  `DEVICE_REGISTRY`
- **THEN** the emitted artifact list contains an `EmittedArtifact(path="README.md",
  artifact_kind="documentation", ...)`
- **AND** the markdown file contains a row in the "Admitted families" table for
  every `(vendor, family)` in `DEVICE_REGISTRY` — not only the family currently
  being published
- **AND** every row lists the vendor, family, ISA, devices, packages, and the
  full peripheral allowlist sourced from the family.json

#### Scenario: Coverage caveats are auto-extracted

- **WHEN** a family's `family.json` declares
  `__source_notes.__readme_caveat: "<text>"`
- **THEN** the README's "Coverage caveats" section contains a bullet
  `**<vendor>/<family>**: <text>`
- **AND** families whose `family.json` does NOT declare `__readme_caveat` are
  omitted from the caveats section so the section stays enxuta

#### Scenario: README regeneration is idempotent across parallel jobs

- **WHEN** the publish workflow runs the per-family matrix and each job emits
  the README artifact
- **THEN** every job produces byte-identical README content for the same
  alloy-codegen revision
- **AND** the publication-diff step (`git status`) detects no change in
  `README.md` when nothing meaningful changed between runs, skipping the commit
  for that artifact alone
- **AND** the auto-generated header includes the alloy-codegen revision so
  unintentional manual edits are obvious in `git blame`

#### Scenario: Manual edits are explicitly disallowed

- **WHEN** the README is rendered
- **THEN** the first line below the title is a quote block declaring
  "Auto-generated by alloy-codegen ... Do not edit manually"
- **AND** any future publish overwrites manual edits without warning

### Requirement: ADC trait header is populated for every admitted ADC peripheral

For every admitted device, the emitted `driver_semantics/adc.hpp` SHALL
contain a populated `AdcSemanticTraits` specialisation
(`kPresent = true` and `kSchemaId != BackendSchemaId::none`) for every
peripheral whose canonical class is `adc` AND whose family explicitly
declares an ``ip_version`` admitting it.  Devices with no admitted ADC
peripheral SHALL emit only the unspecialised template (default
`kPresent = false`).

The publish stage SHALL fail when an explicitly-admitted ADC peripheral has
only the catch-all stub specialisation, ensuring no family ships incomplete
ADC metadata silently.

#### Scenario: ESP32 family ADC peripherals are populated with distinct schemas

- **WHEN** the publish stage runs for `espressif/esp32`, `espressif/esp32c3`,
  or `espressif/esp32s3`
- **THEN** the emitted `driver_semantics/adc.hpp` carries a populated
  specialisation with `kSchemaId` matching the family's distinct schema id
  (`alloy.adc.espressif-esp32-sens-v1`,
  `alloy.adc.espressif-esp32c3-saradc-v1`, or
  `alloy.adc.espressif-esp32s3-saradc-v1`)
- **AND** the row exposes typed `RuntimeRegisterRef` for control and data
  registers, plus a `kChannelCount` consistent with the chip's documented
  channel inventory

#### Scenario: AVR-DA and RP2040 emit populated ADC traits

- **WHEN** the publish stage runs for `microchip/avr-da` or
  `raspberrypi/rp2040`
- **THEN** the emitted `driver_semantics/adc.hpp` carries a populated
  specialisation with `kSchemaId` matching `alloy.adc.microchip-avr-da-adc-v1`
  or `alloy.adc.raspberrypi-rp2040-adc-v1` respectively

#### Scenario: Validation gates an unimplemented ADC peripheral

- **WHEN** a device's IR carries a peripheral with class `adc`, an explicit
  `ip_version`, and a schema id for which no builder exists in
  `_build_adc_rows`
- **THEN** validation fails with rule id `<device>-adc-semantics-populated`
  at severity `error`
- **AND** the publish stage refuses to publish with the warning "ADC
  peripheral admitted without populated semantic traits"

#### Scenario: SVD-sourced ADC-class peripherals without explicit admission are exempt

- **WHEN** a peripheral such as ESP32-S3's `SENS` (touch + temperature
  sensor block) lacks an explicit `ip_version` in family.json
- **THEN** the validation rule treats it as an incidental SVD-sourced extra
  and does NOT fail
- **AND** the trait still emits a stub specialisation
  (`kPresent = false`) so downstream code can detect that the peripheral
  exists but has no semantic schema

### Requirement: ADC trait schema carries Tier 2/3/4 fields with safe defaults

The `AdcSemanticTraits` template SHALL declare static array fields for
internal channels, calibration data points and context, supported
configuration values (resolution, sample time, oversampling), DMA bindings,
external trigger sources, and DMA mode options.  Defaults SHALL be empty
``std::array<X, 0>`` so any vendor builder can opt in to populating them
incrementally without breaking previously-published goldens.

The follow-on change `add-adc-tier-2-3-4-data` SHALL populate these fields
per vendor.  Until then, the schema surface is stable and consumers can
already reference the symbols (they will resolve to empty arrays).

#### Scenario: Schema fields appear in every emitted adc.hpp

- **WHEN** any device with an admitted ADC peripheral emits its
  `driver_semantics/adc.hpp`
- **THEN** the file declares `kInternalChannels`, `kCalibrationDataPoints`,
  `kCalibrationContext`, `kSupportedResolutions`, `kSupportedSampleTimes`,
  `kSupportedOversamplings`, `kDmaBindings`, `kExternalTriggers`, and
  `kSupportedDmaModes` on each populated specialisation
- **AND** the corresponding `kXxxCount` constants are emitted as
  `static constexpr std::uint32_t`
- **AND** every field carries a syntactically valid C++ initialiser even
  when the vendor builder has not yet populated the data (empty array is
  the canonical "absent" form)

#### Scenario: New ADC support types appear in common.hpp

- **WHEN** any device emits its `driver_semantics/common.hpp`
- **THEN** the file declares the support enums
  (`InternalAdcChannelKind`, `AdcCalibrationKind`,
  `AdcExternalTriggerSource`, `AdcDmaMode`) and structs
  (`InternalAdcChannel`, `CalibrationDataPoint`, `CalibrationContext`,
  `AdcResolutionOption`, `AdcSampleTimeOption`, `AdcOversamplingOption`,
  `AdcExternalTrigger`, `AdcDmaBinding`, `AdcDmaModeOption`)
- **AND** these types are usable by any consumer-side code generator that
  wants to produce modm-style high-level ADC drivers

### Requirement: ADC trait Tier 2/3/4 fields MUST be populated per device patch declarations

Each emitted `AdcSemanticTraits` SHALL populate its Tier 2/3/4 fields (internal channels, calibration data points and context, resolution/sample-time/oversampling options, DMA bindings, external trigger sources, DMA mode options) from the device-patch declarations, so apps can compile-time generate high-level helpers like `readTemperature() -> celsius`, `readVdd() -> mV`, and `AdcDma<Dma1Channel1>::startTimerTriggered<Tim1::Trgo>(buffer)` without hardcoding vendor-specific constants.

#### Scenario: STM32 ADC surfaces internal channels and factory calibration with semantic constants

- **WHEN** the ST G0 / F4 family emits its ADC traits
- **THEN** `kInternalChannels` carries entries for `temperature_sensor`,
  `vrefint`, and `vbat` with their documented channel indices
- **AND** `kCalibrationDataPoints` carries entries with concrete
  `RuntimeRegisterRef` pointing at the system memory cal addresses, plus
  `semantic_constant` set to the temperature (°C) or voltage (mV) at
  which each value was measured
- **AND** `kCalibrationContext` carries `cal_temp_low_celsius`,
  `cal_temp_high_celsius`, `cal_voltage_mv`, and `vrefint_nominal_mv` —
  enough metadata for the consumer to derive the standard temp / mV
  conversion formulas

#### Scenario: AVR-DA surfaces SIGROW factory calibration

- **WHEN** the AVR-DA family emits its ADC traits
- **THEN** `kCalibrationDataPoints` references SIGROW.SREF, TEMPSENSE0,
  and TEMPSENSE1 with their flash-location addresses
- **AND** `kInternalChannels` includes the AVR-DA temperature sensor
  with MUXPOS 0x42 (the documented internal-temp channel)

#### Scenario: ESP32 calibration is delegated to esp-idf with empty cal arrays

- **WHEN** an ESP32 family (esp32, esp32c3, esp32s3) emits its ADC traits
- **THEN** `kCalibrationContext.valid` is `false` and
  `kCalibrationDataPointCount` is `0`
- **AND** the family's `__readme_caveat` documents that factory calibration
  uses esp-idf's `esp_adc_cal_*` runtime API

#### Scenario: RP2040 surfaces the on-die temperature sensor

- **WHEN** the RP2040 family emits its ADC traits
- **THEN** `kInternalChannels` contains exactly one entry of kind
  `temperature_sensor` at channel index 4

#### Scenario: Resolution / sample time / oversampling carry paired arrays

- **WHEN** any family with ADC emits its ADC traits
- **THEN** `kSupportedResolutions` is a non-empty array of `(bits,
  field_value)` pairs covering what the device documents
- **AND** if the device supports configurable sample time, the
  `kSupportedSampleTimes` array carries Q8.8-encoded cycle counts paired
  with their raw field values
- **AND** if the device supports HW oversampling, the
  `kSupportedOversamplings` array carries `(ratio, field_value)` pairs
- **AND** families that don't support a feature carry empty arrays for it

#### Scenario: DMA bindings derive from device.dma_requests

- **WHEN** any family's ADC peripheral has a matching `dma_requests` entry
  in its IR
- **THEN** `kDmaBindings` contains an `AdcDmaBinding` per matching request
  with controller_peripheral, controller_id, binding_id, request_value,
  data_register, and transfer_width_bits populated
- **AND** families without DMA-capable ADC (AVR-DA, ESP32 classic ADC1,
  ESP32-C3) carry `kDmaBindingCount=0`

#### Scenario: External trigger sources are enumerated with EXTSEL values

- **WHEN** a family that supports timer-triggered ADC emits its ADC traits
- **THEN** `kExternalTriggers` contains an `AdcExternalTrigger` per
  documented trigger source
- **AND** each entry carries the symbolic `AdcExternalTriggerSource` enum
  value, the raw EXTSEL field value to write, and the default polarity
- **AND** families admitting only software trigger (RP2040, AVR-DA at
  this stage, ESP32 in this admission) carry `kExternalTriggerCount=0`

### Requirement: registers.hpp MUST emit secondary-core-release control registers

The emitted `registers.hpp` MUST include the registers that participate in
secondary-core release for asymmetric Xtensa dual-core devices, and MUST tag
them with a typed `RegisterRole` so consumers find them without name pattern
matching.

#### Scenario: ESP32 classic emits APPCPU_CTRL_A/B/C/D in the typed enum

- **WHEN** the pipeline emits `registers.hpp` for an ESP32 classic device
- **THEN** the typed `RegisterId` enum includes
  `register_dport_appcpu_ctrl_a`, `register_dport_appcpu_ctrl_b`,
  `register_dport_appcpu_ctrl_c`, and `register_dport_appcpu_ctrl_d`
- **AND** the descriptor for `register_dport_appcpu_ctrl_b` carries
  `role = secondary_core_release`
- **AND** the remaining APPCPU_CTRL_* descriptors carry `role = general`

#### Scenario: ESP32-S3 tags SYSTEM.CORE_1_CONTROL_0/1 with the role

- **WHEN** the pipeline emits `registers.hpp` for an ESP32-S3 device
- **THEN** the descriptors for `register_system_core_1_control_0` and
  `register_system_core_1_control_1` carry `role = secondary_core_release`

#### Scenario: Single-core devices emit no role-tagged release registers

- **WHEN** the pipeline emits `registers.hpp` for a single-core device
  (e.g. ESP32-C3, STM32G0, SAME70)
- **THEN** no register descriptor carries `role = secondary_core_release`
- **AND** the `RegisterRole` enum is still emitted (consumers that branch
  on it see only `general`)

### Requirement: system_sequences.hpp MUST emit a secondary-core-release step on dual-core targets

The emitted `system_sequences.hpp` MUST add a
`SystemSequenceStepKindId::secondary_core_release` step to the
`default_bringup` sequence on every device whose
`Device.multicore_topology` is `xtensa_asymmetric_dual_core`. The step MUST
reference the secondary-core release register(s) by typed `RegisterId`
rather than by raw address.

#### Scenario: ESP32 classic emits the step referencing DPORT.APPCPU_CTRL_B

- **WHEN** the pipeline emits `system_sequences.hpp` for an ESP32 classic
  device
- **THEN** the `default_bringup` sequence contains a step with
  `kind = secondary_core_release`
- **AND** the step's typed register reference resolves to
  `register_dport_appcpu_ctrl_b`
- **AND** the step's `operation` field is `set_bit_0`
- **AND** the step is positioned after all clock-related steps and before
  the application entry

#### Scenario: ESP32-S3 emits the step referencing both CORE_1_CONTROL registers

- **WHEN** the pipeline emits `system_sequences.hpp` for an ESP32-S3 device
- **THEN** the `default_bringup` sequence contains a step with
  `kind = secondary_core_release`
- **AND** the step's typed register references resolve to
  `register_system_core_1_control_0` and `register_system_core_1_control_1`
- **AND** the step's `operation` field is
  `clear_runstall_after_clkgate`

#### Scenario: Single-core devices do not emit the step

- **WHEN** the pipeline emits `system_sequences.hpp` for a device whose
  `Device.multicore_topology` is `single_core`
- **THEN** no step in any sequence carries
  `kind = secondary_core_release`
- **AND** the symmetric_dual_core RP2040 device does NOT emit the step
  either (asymmetric-only)

### Requirement: capabilities.json MUST surface multicore topology and core count

The emitted `capabilities.json` MUST carry, for every device, the
`device:multicore-topology` and `device:core-count` keys. For asymmetric
Xtensa devices it MUST additionally carry
`device:secondary-core-release-register` naming the typed register id.

#### Scenario: Single-core devices carry the safe defaults

- **WHEN** the pipeline emits `capabilities.json` for a single-core device
- **THEN** `device:multicore-topology = "single-core"`
- **AND** `device:core-count = 1`
- **AND** no `device:secondary-core-release-register` key is present

#### Scenario: ESP32 classic capabilities surface the LX6 release register

- **WHEN** the pipeline emits `capabilities.json` for an ESP32 classic device
- **THEN** `device:multicore-topology = "xtensa-dual-core"`
- **AND** `device:core-count = 2`
- **AND** `device:secondary-core-release-register =
  "register_dport_appcpu_ctrl_b"`

#### Scenario: ESP32-S3 capabilities surface the LX7 register pair

- **WHEN** the pipeline emits `capabilities.json` for an ESP32-S3 device
- **THEN** `device:multicore-topology = "xtensa-dual-core"`
- **AND** `device:core-count = 2`
- **AND** `device:secondary-core-release-register` is the JSON array
  `["register_system_core_1_control_0",
  "register_system_core_1_control_1"]`

#### Scenario: RP2040 carries symmetric topology with no release register

- **WHEN** the pipeline emits `capabilities.json` for an RP2040 device
- **THEN** `device:multicore-topology = "symmetric-dual-core"`
- **AND** `device:core-count = 2`
- **AND** no `device:secondary-core-release-register` key is present

### Requirement: usb.hpp SHALL emit USB hardware-feature constexprs alongside register references

The emitted `driver_semantics/usb.hpp` MUST expose hardware-feature
constexprs on every `UsbSemanticTraits` specialization for devices whose
`Device.usb_controllers` carries a matching `UsbControllerDescriptor`.
The constexprs (`kHardwarePresent`, `kBaseAddress`, `kEndpointCount`,
`kSupportsHighSpeed`, `kSupportsDma`, `kCrystalless`,
`kDpramBaseAddress`, `kDpramSizeBytes`, `kDmaChannelCount`, `kDmPin`,
`kDpPin`) MUST default to safe falsy values on the unspecialized
template so consumer code that branches on `kHardwarePresent` compiles
even when no controller is admitted.

`kDmPin` / `kDpPin` MUST resolve to typed `PinId` enum values when the
documented pin is admitted in the device's `PinId` enum, and to
`PinId::none` otherwise (preserving compile-time correctness across
package variants where the pad isn't bonded out).

#### Scenario: STM32G0B1 emits hardware-feature constexprs on the USB specialization

- **WHEN** the pipeline emits `usb.hpp` for STM32G0B1
- **THEN** `UsbSemanticTraits<PeripheralId::USB>` carries
  `kHardwarePresent = true`, `kBaseAddress = 0x40005C00u`,
  `kEndpointCount = 8u`, `kCrystalless = true`,
  `kDpramBaseAddress = 0x40006000u`, `kDpramSizeBytes = 1024u`

#### Scenario: STM32F401RE emits OTG FS facts and gracefully drops missing pins

- **WHEN** the pipeline emits `usb.hpp` for STM32F401RE
- **THEN** `UsbSemanticTraits<PeripheralId::OTG_FS>` carries
  `kBaseAddress = 0x50000000u`, `kEndpointCount = 4u`,
  `kSupportsDma = true`
- **AND** `kDmPin` / `kDpPin` resolve to `PinId::none` when PA11/PA12
  are not in the admitted package's pin set

#### Scenario: Devices without admitted USB peripherals see only the default trait

- **WHEN** the pipeline emits `usb.hpp` for a device with no admitted
  USB peripheral (e.g. ESP32 classic, AVR-DA)
- **THEN** the file contains only the unspecialized template with
  `kPresent = false` and `kHardwarePresent = false`
- **AND** `kUsbSemanticPeripherals` is the empty array

### Requirement: uart.hpp SHALL emit hardware-feature constexprs from Device.uart_peripherals

The emitted `uart.hpp` SHALL surface `kHardwarePresent = true` plus
`kBaseAddress`, `kFifoDepth`, `kTxSignalIdx`, `kRxSignalIdx`,
`kSupportsDma` on every `UartSemanticTraits` specialization whose
peripheral has a matching `UartPeripheralDescriptor` on the device IR.
These constexprs MUST default to safe falsy values on the unspecialized
template so consumer code that branches on `kHardwarePresent` compiles
even when no descriptor is admitted.

`kBaseAddress` MUST be sourced from the peripheral IR (which mirrors
the SVD) rather than the patch overlay so a hand-typed patch base
address can never disagree with the silicon spec.

#### Scenario: ESP32 UART0 emits the SVD-correct base address and 128-byte FIFO depth

- **WHEN** the pipeline emits `uart.hpp` for ESP32 classic
- **THEN** `UartSemanticTraits<PeripheralId::UART0>` carries
  `kHardwarePresent = true`, `kBaseAddress = 0x3FF40000u`,
  `kFifoDepth = 128u`, `kSupportsDma = true`

#### Scenario: ESP32-C3 UART0 emits the larger 256-byte FIFO depth

- **WHEN** the pipeline emits `uart.hpp` for ESP32-C3
- **THEN** `UartSemanticTraits<PeripheralId::UART0>` carries
  `kFifoDepth = 256u` (vs 128 on classic/S3)

### Requirement: spi.hpp SHALL emit hardware-feature constexprs from Device.spi_peripherals

The emitted `spi.hpp` SHALL surface `kHardwarePresent = true` plus
`kBaseAddress`, `kMaxClockHz`, `kHasIomuxFastPath`, IO-MUX fast-path
pin numbers (`kIomuxMosiPin`, `kIomuxMisoPin`, `kIomuxClkPin`,
`kIomuxCsPin`), GPIO-matrix signal indices (`kMosiOutSignal`,
`kMisoInSignal`, `kClkOutSignal`, `kCsOutSignal`), and `kSupportsDma`
on every `SpiSemanticTraits` specialization whose peripheral has a
matching `SpiPeripheralDescriptor` on the device IR. These constexprs
MUST default to safe falsy values on the unspecialized template.

#### Scenario: ESP32 SPI2 advertises its IO_MUX fast-path pins

- **WHEN** the pipeline emits `spi.hpp` for ESP32 classic
- **THEN** `SpiSemanticTraits<PeripheralId::SPI2>` carries
  `kHasIomuxFastPath = true`, `kIomuxMosiPin = 13`,
  `kIomuxMisoPin = 12`, `kIomuxClkPin = 14`,
  `kIomuxCsPin = 15`, `kMaxClockHz = 80000000u`

#### Scenario: ESP32-C3 SPI2 has no dedicated IO_MUX pins

- **WHEN** the pipeline emits `spi.hpp` for ESP32-C3
- **THEN** `SpiSemanticTraits<PeripheralId::SPI2>` carries
  `kHasIomuxFastPath = false`

### Requirement: uart.hpp SHALL surface Tier 2/3/4 silicon facts

The emitted `uart.hpp` SHALL extend every populated
`UartSemanticTraits` specialization with the Tier 2/3/4 facts the
alloy concept-validated HAL needs at compile time: supported data
bits, parity options, stop-bit options, baud-clock sources, baud
oversampling options, FIFO trigger levels (when present), max baud
rate, mode-capability flags (LIN / IrDA / smartcard / half-duplex /
synchronous / auto-baud / wake-from-stop), and a typed
`kDmaBindings` array auto-derived from `device.dma_requests`. These
constexprs MUST default to safe falsy values
(`std::array<X, 0>{}` / `false` / `0`) on the unspecialized template
so consumer code that branches on them compiles even when no
descriptor is admitted.

#### Scenario: STM32G0 USART2 advertises LIN + 8x oversampling + FIFO triggers

- **WHEN** the pipeline emits `uart.hpp` for an STM32G0 device that
  admits USART2
- **THEN** `UartSemanticTraits<PeripheralId::USART2>` carries
  `kSupportsLin = true`, `kSupportsIrda = true`,
  `kSupportsSmartcard = true`, `kBaudOversamplingOptions.size() == 2`,
  `kFifoTriggerLevels.size() >= 4`, `kMaxBaudHz == 4'000'000u`,
  `kSupportedDataBits` contains `7`, `8`, and `9`

#### Scenario: AVR-DA USART0 carries no LIN and no DMA bindings

- **WHEN** the pipeline emits `uart.hpp` for an AVR-DA device
- **THEN** `UartSemanticTraits<PeripheralId::USART0>::kSupportsLin == false`
- **AND** `kDmaBindings.size() == 0` (AVR-DA has no DMA controller)
- **AND** `kSupportedDataBits` contains `5`, `6`, `7`, `8`, and `9`

#### Scenario: RP2040 UART0 surfaces 32-byte FIFO trigger options

- **WHEN** the pipeline emits `uart.hpp` for RP2040
- **THEN** `UartSemanticTraits<PeripheralId::UART0>::kFifoTriggerLevels`
  contains the five PL011 trigger levels (1/8, 2/8, 4/8, 6/8, 7/8)
- **AND** `kDmaBindings` contains exactly two entries (TX + RX) with
  the DREQ values from `device.dma_requests`

#### Scenario: Devices without admitted UART hardware see only safe defaults

- **WHEN** the pipeline emits `uart.hpp` for a device with no UART
  peripheral admitted
- **THEN** the unspecialized template carries `kSupportedDataBits`,
  `kSupportedParity`, `kSupportedStopBits`, `kBaudClockSources`,
  `kFifoTriggerLevels`, `kDmaBindings` all as `std::array<X, 0>{}`
- **AND** every `kSupports*` flag is `false`
- **AND** `kMaxBaudHz` is `0u`

### Requirement: spi.hpp SHALL surface Tier 2/3/4 silicon facts

The emitted `spi.hpp` SHALL extend every populated
`SpiSemanticTraits` specialization with the Tier 2/3/4 facts: a
typed `kSupportedFrameSizes` array (data-bits per frame), baud
prescaler options, FIFO threshold options (when present),
mode-capability flags (CRC / TI frame / I²S sub-mode / bidirectional
3-wire / LSB-first / NSS hardware management / Motorola frame), and
a typed `kDmaBindings` array auto-derived from
`device.dma_requests`. Defaults follow the same safe-falsy pattern
as UART.

#### Scenario: STM32G0 SPI1 advertises 4..16 bit frame sizes and CRC

- **WHEN** the pipeline emits `spi.hpp` for an STM32G0 device
- **THEN** `SpiSemanticTraits<PeripheralId::SPI1>::kSupportedFrameSizes`
  contains every integer from `4` to `16` inclusive
- **AND** `kSupportsCrc == true`, `kSupportsTiFrame == true`,
  `kSupportsMotorolaFrame == true`, `kSupportsLsbFirst == true`,
  `kSupportsNssHwManagement == true`,
  `kSupportsBidirectional3Wire == true`
- **AND** `kFifoThresholdOptions.size() == 2` (8-bit / 16-bit FRXTH)
- **AND** `kBaudPrescalerOptions.size() == 8` (BR=0..7 → /2 .. /256)

#### Scenario: AVR-DA SPI0 emits an 8-bit-only frame size and no CRC

- **WHEN** the pipeline emits `spi.hpp` for an AVR-DA device
- **THEN** `SpiSemanticTraits<PeripheralId::SPI0>::kSupportedFrameSizes`
  is the single-element array `{8}`
- **AND** `kSupportsCrc == false`, `kSupportsTiFrame == false`,
  `kSupportsI2sSubmode == false`
- **AND** `kSupportsLsbFirst == true` (DORD bit on AVR SPI)

#### Scenario: ESP32-S3 SPI2 advertises 1..32 bit frames and DMA bindings

- **WHEN** the pipeline emits `spi.hpp` for ESP32-S3
- **THEN** `SpiSemanticTraits<PeripheralId::SPI2>::kSupportedFrameSizes`
  contains every integer from `1` to `32` inclusive
- **AND** `kDmaBindings.size() == 2` (TX + RX, derived from the
  `gdma-spi2-tx` / `gdma-spi2-rx` entries in `dma_requests`)
- **AND** `kSupportsLsbFirst == true`,
  `kSupportsBidirectional3Wire == true`

#### Scenario: SPI peripherals with no DMA route emit empty kDmaBindings

- **WHEN** the pipeline emits `spi.hpp` for a device whose
  `device.dma_requests` carries no entry for the SPI peripheral
- **THEN** the corresponding specialization's `kDmaBindings` is
  `std::array<SpiDmaBinding, 0>{}`
- **AND** `kSupportsDma` (the existing flag) MAY remain `true` —
  hardware can support DMA even when no static binding is admitted
  yet; consumers that need a binding MUST gate on
  `kDmaBindings.size() > 0u`

### Requirement: Emitted ADC Driver-Semantics Header SHALL Declare A Typed Per-Peripheral Channel Enum

Every emitted `<vendor>/<family>/.../driver_semantics/adc.hpp` MUST
declare `template <PeripheralId Id> struct AdcChannelOf` with an
empty-fallback `enum class type : std::uint8_t {};` and one
specialisation per ADC peripheral whose `AdcSemanticTraits<P>::kPresent`
is true. The specialisation's enum MUST list:

- one ordinal enumerator `CH<n>` per channel index in
  `0..kChannelCount-1`
- one named alias per `kInternalChannels` entry whose `kind` matches
  the closed name table
  (`temperature_sensor` → `TempSensor`,
  `vrefint` → `Vrefint`,
  `vbat` → `VBat`,
  `opamp_output` → `OpAmpOut`,
  `dac_output` → `DacOut`),
  with the underlying value equal to the descriptor's published
  `channel_index`.

After all specialisations, the file MUST emit a convenience alias
`template <PeripheralId Id> using AdcChannel = typename
AdcChannelOf<Id>::type;`.

#### Scenario: STM32G0 ADC1 declares a typed Channel enum with internal aliases

- **WHEN** the publication emits
  `st/stm32g0/.../stm32g071rb/.../driver_semantics/adc.hpp`
- **THEN** the file contains
  `template<> struct AdcChannelOf<PeripheralId::ADC1>` whose
  `enum class type : std::uint8_t` lists `CH0`..`CH18` plus
  `TempSensor = 12`, `Vrefint = 13`, `VBat = 14`
- **AND** the file ends with
  `template<PeripheralId Id> using AdcChannel = typename
  AdcChannelOf<Id>::type;`

#### Scenario: SAME70 AFEC0 / AFEC1 declare distinct Channel enums

- **WHEN** the publication emits the same70 ADC traits for
  `atsame70q21b`
- **THEN** both `AdcChannelOf<PeripheralId::AFEC0>` and
  `AdcChannelOf<PeripheralId::AFEC1>` are emitted as distinct
  specialisations, each with its own enum
- **AND** the type system rejects passing
  `AdcChannel<PeripheralId::AFEC0>::CH3` to a function expecting
  `AdcChannel<PeripheralId::AFEC1>` (validated by the C++ compile
  probe under `tests/compile_probes/adc_channel_enum.cpp`)

#### Scenario: Devices without ADC traits get the empty fallback

- **WHEN** the publication emits ADC traits for a device whose
  `AdcSemanticTraits<P>::kPresent` is false (today: ESP32 family,
  RP2040)
- **THEN** the file still contains the
  `template <PeripheralId Id> struct AdcChannelOf` primary template
  with an empty `enum class type : std::uint8_t {}`
- **AND** consumer code that compiles against those targets sees
  no missing-symbol error when it references `AdcChannel<...>`
  through guarded `if constexpr (kPresent)` blocks

### Requirement: Emitted ADC Channel Enum SHALL Detect Duplicate Enumerator Names At Emit Time

The emitter MUST fail the publication run if the channel manifest
derivation produces two enumerators sharing the same name on a
single ADC peripheral (e.g. two `temperature_sensor` internal
channels on some hypothetical future device). The emitter MUST
with a diagnostic naming the device, the duplicate enumerator name,
and the conflicting channel indices. The emitter MUST NOT silently
emit two members with the same name (which is ill-formed C++) and
MUST NOT silently drop one of them.

#### Scenario: Duplicate kind on a single peripheral fails fast

- **WHEN** a (hypothetical) device patch declares two internal
  channels with `kind = "temperature_sensor"` on the same ADC
  peripheral
- **THEN** the publication fails with a diagnostic of the form
  "AdcChannelOf: duplicate enumerator name 'TempSensor' on
  PeripheralId::<P> at indices <i>, <j>"
- **AND** no `adc.hpp` is written for the affected device

### Requirement: Goldens SHALL Cover Every Published ADC Device

The publication MUST regenerate every ADC driver-semantics golden
in `tests/fixtures/emitted/<family>/.../driver_semantics/adc.hpp`
as part of this change so every published ADC
peripheral's `AdcChannelOf<P>` specialisation is captured in the
golden, and every `kPresent=false` device's empty-fallback is
captured. The diff against the prior goldens MUST be additive only
— no reordering, no whitespace churn outside the new block.

#### Scenario: Every ST/Microchip/NXP ADC golden gains the typed enum block

- **WHEN** the goldens regenerate after this change lands
- **THEN** each of the following files gains a typed
  `AdcChannelOf<PeripheralId::<P>>` specialisation:
  `st/stm32g0/.../{stm32g030f6,stm32g071rb,stm32g0b1re}/...`,
  `st/stm32f4/.../{stm32f401re,stm32f405rg}/...`,
  `microchip/same70/.../{atsame70n21b,atsame70q21b}/...`,
  `microchip/avr-da/.../avr128da32/...`,
  `nxp/imxrt1060/.../{mimxrt1062,mimxrt1064}/...`
- **AND** each `kPresent=false` family
  (`espressif/esp32`, `esp32c3`, `esp32s3`, `raspberrypi/rp2040`)
  gains the empty-fallback `AdcChannelOf<…>` primary template only

### Requirement: timer.hpp SHALL surface Tier 2/3/4 silicon facts

The emitted `timer.hpp` SHALL extend every populated
`TimerSemanticTraits` specialization with: max prescaler, max
auto-reload, trigger-source array (ITR0..ITR3 + ETR + TI1F + ...),
master-output mode array (TRGO sources), and capability flags
`kSupportsDmaBurst`, `kSupportsRepetitionCounter`,
`kSupportsXorInput`.  Empty arrays / `0u` / `false` on the
unspecialized template.

#### Scenario: STM32G0 TIM1 advertises full ITR matrix + repetition counter

- **WHEN** the pipeline emits `timer.hpp` for STM32G0 stm32g071rb
- **THEN** `TimerSemanticTraits<PeripheralId::TIM1>::kMaxPrescaler`
  equals `0xFFFFu`
- **AND** `kTriggerSources.size() >= 4`
  (ITR0, ITR1, ITR2, ITR3 minimum)
- **AND** `kMasterOutputModes.size() >= 8`
  (Reset, Enable, Update, ComparePulse, OC1Ref..OC4Ref)
- **AND** `kSupportsRepetitionCounter == true`
- **AND** `kSupportsDmaBurst == true`

#### Scenario: STM32G0 TIM14 is a basic timer with empty trigger array

- **WHEN** the pipeline emits `timer.hpp` for STM32G0 stm32g071rb
- **THEN** `TimerSemanticTraits<PeripheralId::TIM14>::kTriggerSources.size()`
  equals `0`
- **AND** `kSupportsRepetitionCounter == false`
- **AND** `kSupportsDmaBurst == false`
- **AND** `kMaxPrescaler == 0xFFFFu`

### Requirement: UART / SPI / I2C / QSPI / SDMMC traits SHALL surface kernel-clock selector + max-clock

Each emitted `<peripheral>.hpp` for UART, SPI, I2C, QSPI, and SDMMC SHALL extend its specialization template with `kKernelClockSelectorField` (RCC mux `FieldRef`, or `kInvalidFieldRef` when hard-wired), `kKernelClockSourceOptions` (array mapping each `field_value` to a `ClockTreeNodeId`), `kMaxClockHz` (peripheral input clock ceiling, `0u` on the unspecialized template), and `kClockGateField` (RCC enable bit, co-located with the semantic surface).

#### Scenario: STM32G0 USART2 surfaces 4 clock sources + 64 MHz max

- **WHEN** the pipeline emits `uart.hpp` for STM32G0 stm32g071rb
- **THEN** `UartSemanticTraits<PeripheralId::USART2>::kMaxClockHz`
  equals `64'000'000u`
- **AND** `kKernelClockSourceOptions.size()` equals `4`
- **AND** the option set contains identifiers for PCLK, SYSCLK,
  HSI16, and LSE
- **AND** `kKernelClockSelectorField` resolves to the
  `RCC_CCIPR.USART2SEL` field reference

#### Scenario: AVR-DA USART0 has hard-wired clock and ships kInvalidFieldRef

- **WHEN** the pipeline emits `uart.hpp` for an AVR-DA device
- **THEN** `UartSemanticTraits<PeripheralId::USART0>::kKernelClockSelectorField`
  equals `kInvalidFieldRef` (CLK_PER is the only source)
- **AND** `kKernelClockSourceOptions.size()` equals `1`
- **AND** `kMaxClockHz` equals `24'000'000u`

### Requirement: Per-peripheral semantic traits SHALL surface NVIC IRQ numbers

Every emitted `<peripheral>.hpp` SHALL carry a `kIrqNumbers` constexpr array (or split scalar fields for TIMER / per-channel for DMA) listing the NVIC vector indices that fire for each admitted peripheral instance, sourced from the canonical-device-IR `interrupt_bindings` table filtered by `peripheral_aliases`. The unspecialized template SHALL ship an empty array (or sentinel `0xFFFF'FFFFu` for the split scalar form) so consumer code that branches on `kIrqNumbers.size() > 0` compiles even when no binding is admitted.

#### Scenario: STM32G0 USART2 advertises USART2_IRQn

- **WHEN** the pipeline emits `uart.hpp` for an STM32G0 device that
  admits USART2 and the IR carries an `InterruptDescriptor` named
  `USART2` with `peripheral_aliases = ("USART2",)`
- **THEN** `UartSemanticTraits<PeripheralId::USART2>::kIrqNumbers`
  has size `1` and `kIrqNumbers[0]` equals the SVD-reported
  USART2 NVIC vector number

#### Scenario: STM32G0 TIM1 splits update / capture / break / trigger

- **WHEN** the pipeline emits `timer.hpp` for an STM32G0 device that
  admits TIM1
- **THEN** `TimerSemanticTraits<PeripheralId::TIM1>::kUpdateIrqNumber`
  matches the TIM1_BRK_UP_TRG_COM line index reported by the SVD
- **AND** `kBreakIrqNumber`, `kTriggerIrqNumber` mirror the same
  line on G0 (shared vector); on F4/F7 they resolve to distinct
  indices

#### Scenario: AVR-DA SPI0 has no NVIC and ships an empty array

- **WHEN** the pipeline emits `spi.hpp` for an AVR-DA device
- **THEN** `SpiSemanticTraits<PeripheralId::SPI0>::kIrqNumbers.size()`
  equals `0` (AVR has its own vector table not surfaced as
  `interrupt_bindings`)
- **AND** the unspecialized fallback `SpiSemanticTraits<X>::kIrqNumbers`
  is `std::array<std::uint32_t, 0>{}`

### Requirement: pwm.hpp SHALL surface Tier 2/3/4 silicon facts

The emitted `pwm.hpp` SHALL extend every populated
`PwmSemanticTraits` specialization with: max prescaler, max
period, deadtime configuration options, supported alignment
modes (edge / center-up / center-down / center-up-down), break
input descriptors, and capability flags `kSupportsDeadtime`,
`kSupportsBreakInput`, `kSupportsComplementaryOutputs`,
`kSupportsAsymmetricPwm`, `kSupportsCombinedPwm`.  Empty arrays /
`0u` / `false` on the unspecialized template.

#### Scenario: STM32G0 TIM1 PWM advertises full deadtime + 1 break input

- **WHEN** the pipeline emits `pwm.hpp` for STM32G0 stm32g071rb
- **THEN** `PwmSemanticTraits<PeripheralId::TIM1>::kSupportsDeadtime
  == true`
- **AND** `kSupportsBreakInput == true`
- **AND** `kBreakInputs.size() == 1`
- **AND** `kSupportedAlignments.size() == 4`
  (edge + 3 center-aligned modes)
- **AND** `kDeadtimeOptions.size() >= 4`
  (4 DTPSC prescaler choices)

#### Scenario: STM32G0 TIM14 PWM is basic — no deadtime, no break

- **WHEN** the pipeline emits `pwm.hpp` for STM32G0 stm32g071rb
- **THEN** `PwmSemanticTraits<PeripheralId::TIM14>::kSupportsDeadtime
  == false`
- **AND** `kSupportsBreakInput == false`
- **AND** `kBreakInputs.size() == 0`
- **AND** `kSupportedAlignments.size() == 1` (edge only)

### Requirement: dma.hpp SHALL surface DMA controller hardware traits

The emitted `dma.hpp` SHALL extend every populated
`DmaControllerHwTraits<DmaControllerId>` specialization with:
channel count, max transfer count (NDTR width), supported burst
sizes, supported data widths, priority level count, and capability
flags `kSupportsCircular`, `kSupportsDoubleBuffer`,
`kSupportsMemToMem`, `kSupportsDescriptorChaining`,
`kSupportsByteSwap`, `kSupportsScatterGather`.  `0u` / empty
arrays / `false` on the unspecialized template.

#### Scenario: RP2040 DMA controller advertises 12 channels + byte-swap

- **WHEN** the pipeline emits `dma.hpp` for RP2040 rp2040
- **THEN** `DmaControllerHwTraits<DmaControllerId::DMA>::kChannelCount`
  equals `12u`
- **AND** `kSupportsByteSwap == true`
- **AND** `kSupportsScatterGather == true`
- **AND** `kSupportedBurstSizes.size() >= 1`

#### Scenario: STM32G0 DMA1 advertises 7 channels + 4 priority levels

- **WHEN** the pipeline emits `dma.hpp` for STM32G0 stm32g071rb
- **THEN** `DmaControllerHwTraits<DmaControllerId::DMA1>::kChannelCount`
  equals `7u`
- **AND** `kPriorityLevelCount == 4u`
- **AND** `kMaxTransferCount == 0xFFFFu`
- **AND** `kSupportsCircular == true`
- **AND** `kSupportsByteSwap == false`

### Requirement: i2c.hpp SHALL surface Tier 2/3/4 silicon facts

The emitted `i2c.hpp` SHALL extend every populated
`I2cSemanticTraits` specialization with: supported speeds,
addressing-mode flags (7-bit / 10-bit / SMBus / PMBus), supported
slave / general-call / dual-address flags, max clock, and
precomputed TIMINGR / CWGR presets keyed by source clock.  Empty
arrays / false flags / `0u` on the unspecialized template.

#### Scenario: STM32G0 I2C1 surfaces three speeds + Fast-Mode-Plus

- **WHEN** the pipeline emits `i2c.hpp` for STM32G0 stm32g071rb
- **THEN** `I2cSemanticTraits<PeripheralId::I2C1>::kSupportedSpeeds`
  contains `100'000u`, `400'000u`, and `1'000'000u`
- **AND** `kSupports7BitAddressing == true`
- **AND** `kSupports10BitAddressing == true`
- **AND** `kSupportsSmbus == true`
- **AND** `kTimingPresets.size() >= 3`
- **AND** at least one preset has
  `source_clock_hz == 64'000'000u` and `speed_hz == 400'000u`

#### Scenario: STM32G0 emission bug is fixed

- **WHEN** the pipeline emits `i2c.hpp` for STM32G0 stm32g071rb
- **THEN** `kI2cSemanticPeripherals` SHALL include `PeripheralId::I2C1`
- **AND** an explicit `I2cSemanticTraits<PeripheralId::I2C1>`
  specialization SHALL be present (today the unspecialized
  fallback fires because the array is empty)

#### Scenario: AVR-DA TWI carries fewer flags but valid presets

- **WHEN** the pipeline emits `i2c.hpp` for AVR-DA avr128da32
- **THEN** `I2cSemanticTraits<PeripheralId::TWI0>::kSupportsSmbus
  == false`
- **AND** `kSupportsSlave == true` (AVR TWI is bidirectional)
- **AND** `kSupportedSpeeds` contains `100'000u` and `400'000u`

### Requirement: UART/SPI/I2C/TIMER/PWM trait headers SHALL surface typed per-peripheral option enums

For every option-array currently emitted as `std::array<std::uint8_t, N>` on UART, SPI, I2C, TIMER, and PWM trait headers, the pipeline SHALL also emit a paired `enum class <Name>Of<PeripheralId::P>::type` with named entries derived from the populated patch values, plus a typed `std::array<<Name>Of<P>::type, N>` constexpr alongside the existing raw array.  The naming pattern SHALL follow the ADC channel-enum convention (`<Peripheral><Option>Of<P>::type`).  Each typed enum SHALL ship with a closed kind→name lookup table so `to_string(...)` round-trips deterministically.  The existing raw `_Raw` arrays SHALL be retained for one release cycle for back-compat and removed in a follow-up cleanup change.

#### Scenario: STM32G0 USART1 surfaces UartParityOf typed enum

- **WHEN** the pipeline emits `uart.hpp` for STM32G0 stm32g071rb
- **THEN** the file SHALL contain a `UartParityOf<PeripheralId::USART1>::type`
  enum class with entries `none`, `even`, and `odd`
- **AND** SHALL contain a paired
  `static constexpr std::array<UartParityOf<PeripheralId::USART1>::type, 3> kSupportedParity`
- **AND** SHALL retain the existing
  `static constexpr std::array<std::uint8_t, 3> kSupportedParityRaw`
- **AND** the typed enum entries SHALL map back to the same
  `field_value` integers carried in `kSupportedParityRaw`

#### Scenario: STM32G0 SPI1 surfaces SpiFrameSizeOf typed enum

- **WHEN** the pipeline emits `spi.hpp` for STM32G0 stm32g071rb
- **THEN** the file SHALL contain a
  `SpiFrameSizeOf<PeripheralId::SPI1>::type` enum class with
  entries `bits_4`, `bits_5`, …, `bits_16`
- **AND** SHALL contain a paired
  `static constexpr std::array<SpiFrameSizeOf<PeripheralId::SPI1>::type, 13> kSupportedFrameSizes`

#### Scenario: AVR-DA TWI0 surfaces only the populated speed modes

- **WHEN** the pipeline emits `i2c.hpp` for AVR-DA avr128da32
- **THEN** the file SHALL contain a `I2cSpeedModeOf<PeripheralId::TWI0>::type`
  enum class with entries `standard` and `fast` (no `fast_plus`)
- **AND** the typed `kSupportedSpeedModes` array SHALL have size 2

### Requirement: Runtime C++ artifacts SHALL NOT carry string literals for typed enum names

Per the publication gate, runtime-generated C++ artifacts MUST NOT contain string literals (firmware-image bloat).  The typed enum value names themselves (`UartParityOf<USART1>::type::even`) provide compile-time identification — round-trip stringification, when needed, SHALL be implemented host-side by consumers via a switch over the typed enum.  No `std::string_view` name-table is emitted alongside the typed enums.

#### Scenario: Emitted UART header carries no string literals for parity names

- **WHEN** the pipeline emits `uart.hpp` for STM32G0 stm32g071rb
- **THEN** the file SHALL contain the typed
  `UartParityOf<PeripheralId::USART1>::type` enum class with named
  entries `none`, `even`, `odd`
- **AND** the file SHALL NOT contain a `kUartParityNames` string-view
  table — the publication gate enforces zero string literals in
  runtime C++ artifacts

### Requirement: Per-board BSP header SHALL surface named pins + default clock profile

The pipeline SHALL emit a `<vendor>/<family>/generated/runtime/boards/<board_id>/board.hpp` artifact for every admitted board, exposing the on-board pin functions (LEDs, buttons, debug UART, etc.) as typed `PinId` constexpr constants grouped by category, plus the default `ClockProfile` reference.  Each named pin SHALL embed a `static_assert(GpioSemanticTraits<PinId::*>::kPresent)` so consumer typos fail at `#include`-time.  The header SHALL re-export the device's `peripheral_instances.hpp` + `pins.hpp` so a single `#include "board.hpp"` is sufficient (matching the `<modm/board.hpp>` ergonomic).

#### Scenario: Nucleo-G071RB BSP exposes LED + button + debug UART

- **WHEN** the pipeline emits BSP artifacts for the Nucleo-G071RB board file
- **THEN** `st/stm32g0/generated/runtime/boards/nucleo-g071rb/board.hpp`
  SHALL contain `static constexpr PinId kGreen = PinId::PA5;` inside a
  `Leds` struct
- **AND** SHALL contain `static constexpr bool kGreenActiveHigh = true;`
- **AND** SHALL contain `static constexpr PinId kUser = PinId::PB7;`
  inside a `Buttons` struct with `kUserActiveHigh = false`
  (the test fixture's STM32G071RB SVD slice does not include GPIOC,
  so the seed board uses PB7 as the user-button pin; the real
  Nucleo-G071RB silicon uses PC13 — switching back is a one-line
  patch once the fixture admits GPIOC)
- **AND** SHALL contain a `DebugUart` struct exposing
  `kPeripheral == PeripheralId::USART2`, `kTxPin == PinId::PA2`,
  `kRxPin == PinId::PA3`
- **AND** SHALL embed `static_assert` calls for each named pin

### Requirement: Board catalog SHALL enumerate every admitted board

The pipeline SHALL emit a top-level `metadata/boards.json` artifact listing every admitted board globally with its `board_id`, `device`, `vendor`, `family`, `package`, and `summary`.  Each per-device sidecar `metadata/devices/<device>.json` SHALL list the boards that target the device under a `boards` field.

#### Scenario: Boards manifest enumerates Nucleo-G071RB

- **WHEN** the pipeline emits artifacts for any device that has at
  least one board file
- **THEN** `metadata/boards.json` SHALL contain an entry with
  `board_id == "nucleo-g071rb"`, `device == "stm32g071rb"`,
  `vendor == "st"`, `family == "stm32g0"`
- **AND** `metadata/devices/stm32g071rb.json` SHALL list
  `"nucleo-g071rb"` in its `boards` array

### Requirement: Board patches with invalid pin references SHALL fail at normalize time

Board files referencing pins that the device's admitted package does not expose SHALL raise a `StageExecutionError` during the normalize stage with a message identifying the offending `(board_id, named_pin, pin_name)` triple.  This is a hard-fail to prevent shipping a BSP header that would `static_assert` at the consumer's `#include`.

#### Scenario: Board file with non-existent pin fails normalize

- **WHEN** a board file declares a `named_pin` whose `pin` value is
  not in the device's admitted `pin_definitions`
- **THEN** the normalize stage SHALL raise `StageExecutionError`
- **AND** the error message SHALL include the board ID, the named
  pin label, and the unrecognised pin string

