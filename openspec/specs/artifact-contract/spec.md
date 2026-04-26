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

