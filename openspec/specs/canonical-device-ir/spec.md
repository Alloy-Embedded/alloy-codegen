# canonical-device-ir Specification

## Purpose
TBD - created by archiving change build-best-in-class-generator-core. Update Purpose after archive.
## Requirements
### Requirement: Canonical IR models full system-control fabric

Canonical IR MUST represent the device-level control graph required to explain and execute bring-up
and peripheral activation across vendors.

#### Scenario: System-control facts are explicit in canonical IR
- **WHEN** canonical IR is materialized for a supported device
- **THEN** it includes typed facts for clocks, resets, interrupts, and relevant power domains
- **AND** those facts are structured enough to derive bring-up and peripheral dependencies without
  reconstructing intent from unrelated low-level fields

### Requirement: Canonical IR models formal peripheral capabilities

Canonical IR MUST express runtime-relevant peripheral capabilities as first-class facts.

#### Scenario: Capabilities do not rely on downstream heuristics
- **WHEN** a supported runtime peripheral is represented in canonical IR
- **THEN** its supported features are available as typed capability facts
- **AND** Alloy does not need to infer them from schema strings or handwritten rules

### Requirement: Canonical IR preserves provenance for runtime-critical facts

Canonical IR MUST preserve enough provenance to explain how runtime-critical facts were produced.

#### Scenario: Emitted runtime facts can be traced back to origin
- **WHEN** a runtime fact is emitted from canonical IR
- **THEN** its origin can be traced to upstream source data, patch data, inference, or merge logic

### Requirement: Canonical IR SHALL Model Every Runtime Semantic Domain As Typed IDs

The canonical device IR SHALL model every semantic domain consumed by the Alloy runtime as
typed ids, enums, or typed refs rather than human-readable labels.

#### Scenario: Foundational device is normalized
- **WHEN** a foundational device is normalized into the canonical IR
- **THEN** backend schema, peripheral class, signal, signal role, route kind, requirement
  kind, operation kind, operation subject kind, memory kind, startup kind, package pad kind,
  and active level are represented by typed ids
- **AND** the runtime does not need semantic strings to understand those domains

### Requirement: Canonical IR SHALL Keep Human Labels Out Of Runtime C++ Payloads

The canonical device IR SHALL distinguish metadata labels from runtime contract fields so that
human-readable names are not required in runtime-facing C++ artifacts.

#### Scenario: Runtime-facing header is emitted
- **WHEN** a runtime-facing C++ artifact is emitted from the canonical IR
- **THEN** every executable semantic field can be emitted from typed ids, refs, and integers
- **AND** any human-readable labels remain available only in metadata or reports

### Requirement: Canonical IR encodes formal capability facts per peripheral instance

`CanonicalDeviceIR` MUST carry typed capability facts for every runtime-supported
peripheral instance, derived from IP block definitions and enriched by patches,
so that emitters can produce a capability manifest without heuristics or string parsing.

#### Scenario: Capability facts are available without downstream inference

- **WHEN** canonical IR is materialized for a device with a UART that supports DMA
- **THEN** the IR contains a `CapabilityDescriptor` for that UART with
  `capability_id: "uart.dma-tx"` and `value: "true"`
- **AND** the emitter reads this fact directly without querying other IR structures

#### Scenario: Missing capability is explicitly absent, not silently false

- **WHEN** a device's UART does not support hardware flow control
- **THEN** no `CapabilityDescriptor` with `capability_id: "uart.hardware-flow-control"`
  exists for that peripheral
- **AND** the capability manifest emitter treats absence as `false` and emits
  `kHasHardwareFlowControl = false` explicitly
- **AND** the absence is not indistinguishable from a missing patch

#### Scenario: Capability facts carry provenance

- **WHEN** a `CapabilityDescriptor` is present in canonical IR
- **THEN** its `provenance` field identifies whether it was sourced from an IP block
  definition, a device patch, or inferred from register structure
- **AND** the `alloy explain` CLI can surface this provenance on demand

### Requirement: Canonical IR encodes clock profile paths for code generation

`CanonicalDeviceIR` MUST contain enough clock graph structure for emitters to derive
complete, correct register-write sequences for at least two clock profiles per device
(default RC oscillator and maximum PLL frequency).

#### Scenario: PLL configuration parameters are available in the IR

- **WHEN** canonical IR is materialized for a device with a PLL
- **THEN** the clock node for the PLL contains multiplier range, divider range,
  VCO frequency bounds, and output clock node
- **AND** the emitter can derive the correct PLLCFGR/PLLCTRL register values
  without consulting the vendor datasheet directly

#### Scenario: Clock switch ordering is derivable from the graph

- **WHEN** canonical IR is materialized for a device
- **THEN** the clock dependency graph (`kClockDependencies`) is acyclic
- **AND** the correct enable-then-switch ordering is derivable by topological sort
  of the graph edges

### Requirement: Canonical IR preserves connector table facts with provenance

The pin-signal facts used to build `GpioConnector` specializations MUST be traceable
to their source SVD or patch entry, so that compiler error messages can cite origin.

#### Scenario: Every pin-signal binding has a traceable provenance

- **WHEN** a `PinSignal` entry exists in canonical IR for a peripheral-pin combination
- **THEN** its `provenance.source_id` identifies the SVD file or patch that declared it
- **AND** the connector table emitter can embed this provenance in the generated
  `static_assert` message for invalid combinations

#### Scenario: Absence of a binding is derivable, not assumed

- **WHEN** a given pin does not connect to a given peripheral signal on a device
- **THEN** no `PinSignal` entry exists in the IR for that combination
- **AND** the connector table emitter generates a `static_assert(false, ...)` for
  that combination with the correct list of valid alternatives from the same IR

### Requirement: Canonical IR SHALL Model Typed Runtime References

The canonical IR SHALL expose typed reference descriptors for every runtime-owned domain used
by Alloy backend execution, including registers, register fields, clock gates, resets,
selectors, interrupt bindings, DMA bindings, and route-operation targets.

#### Scenario: Foundational device is normalized for runtime consumption
- **WHEN** a foundational family device is normalized
- **THEN** its canonical IR includes stable typed IDs for runtime-owned registers and fields
- **AND** route operations reference typed targets instead of relying only on textual targets

### Requirement: Canonical IR SHALL Model Register Fields for Runtime-Owned Schemas

The canonical IR SHALL carry normalized register-field descriptors for runtime-owned backend
schemas so Alloy does not need handwritten bit offsets or widths.

#### Scenario: UART or GPIO backend consumes generated register field data
- **WHEN** a foundational UART or GPIO instance is normalized
- **THEN** the canonical IR includes field descriptors for the registers needed by that schema
- **AND** each field descriptor includes a typed register reference, bit offset, width, and
  access shape

### Requirement: Canonical IR SHALL Model Typed Peripheral Bindings

The canonical IR SHALL model interrupt, DMA, clock, reset, and selector bindings as typed
descriptors associated with peripheral instances.

#### Scenario: Peripheral instance is normalized
- **WHEN** a runtime-owned peripheral instance is emitted into the canonical IR
- **THEN** the instance can be connected to its interrupt, DMA, clock, reset, and selector
  domains through typed IDs
- **AND** the runtime does not need to reconstruct these bindings from names or CSV strings

### Requirement: IR SHALL model XIP-mapped flash as a distinct memory kind

The canonical device IR SHALL represent externally-mapped XIP (Execute in Place) flash
regions with `kind = "xip-flash"` rather than `kind = "flash"`, preserving the distinction
between internal programmable flash and read-execute memory accessed via an XIP controller.

#### Scenario: RP2040 XIP window is captured as xip-flash kind

- **WHEN** the RP2040 device is normalized
- **THEN** the memory region at `0x10000000` carries `kind = "xip-flash"` and `access = "rx"`
- **AND** no `kind = "flash"` region exists for RP2040 (it has no internal flash)
- **AND** the SRAM regions at `0x20000000` continue to carry `kind = "sram"`

#### Scenario: Internal-flash devices are unaffected by the new kind

- **WHEN** an STM32 or SAME70 device is normalized
- **THEN** its flash region retains `kind = "flash"`
- **AND** no `xip-flash` region is emitted for those devices

#### Scenario: Consumers can distinguish programmable flash from XIP

- **WHEN** the linker script emitter processes a device IR
- **THEN** `kind = "xip-flash"` regions produce `BOOT2` and `XIP_MAIN` MEMORY entries
- **AND** `kind = "flash"` regions produce standard `FLASH` MEMORY entries

### Requirement: IR SHALL capture PIO as a present peripheral with an explicit stub schema

The canonical IR SHALL capture Programmable I/O (PIO) peripherals as present entries
with a named stub schema that explicitly signals the program-execution semantics
(state-machine instruction format, assembled program payloads) are not yet fully
modeled, while the topology of each block is structured via `PioDescriptor`
(see "IR SHALL model PIO blocks with a structured PioDescriptor"). The stub
schema designation applies only to program-execution semantics; topology is
no longer stubbed.

#### Scenario: PIO0 and PIO1 are present in RP2040 canonical IR

- **WHEN** the RP2040 device is normalized
- **THEN** `PIO0` and `PIO1` appear in the peripheral instance list
- **AND** their `backend_schema_id` is `alloy.pio.rp2040-v1-stub`
- **AND** the capability manifest records `runtime-support:pio` as present

#### Scenario: PIO stub schema does not block admission

- **WHEN** the RP2040 vendor-admission gates are evaluated
- **THEN** the presence of PIO with a stub schema does not cause any CI gate to fail
- **AND** the stub schema is explicitly recognized as admission-valid until a full
  PIO program-execution spec is approved

### Requirement: IR SHALL model dual-core topology with single-core-perspective annotation

The canonical device IR SHALL record the actual core topology of multi-core devices in
device metadata and SHALL carry an explicit provenance note documenting which core
perspective the emitted artifacts represent.

#### Scenario: RP2040 dual-core topology is recorded in IR

- **WHEN** the RP2040 device is normalized
- **THEN** device metadata records `core = "cortex-m0plus-dual"`
- **AND** a provenance note documents that emitted artifacts target core 0 only
- **AND** no facts about core 1 state, inter-core FIFOs, or spinlocks are emitted
  in this first cut

#### Scenario: Single-core annotation is visible in emitted startup

- **WHEN** `startup.cpp` is emitted for an RP2040 device
- **THEN** a generated comment explicitly states the single-core-perspective assumption
- **AND** no code to launch or synchronize core 1 is present in the emitted file

### Requirement: Typed Runtime Reference Domains
The canonical device IR SHALL model runtime-owned references with typed domains and ids for
packages, pins, constraints, selectors, clock gates, resets, registers, and register fields.

#### Scenario: Foundational device carries typed refs
- **WHEN** a foundational device is normalized
- **THEN** its runtime-owned references are represented with typed ids
- **AND** the runtime contract does not require raw signal strings as the only executable
  source of truth

### Requirement: Diagnostic Strings Are Secondary
The canonical device IR SHALL treat any human-readable route or instance string as diagnostic
metadata only, not as a primary executable contract field.

#### Scenario: Runtime field has typed and diagnostic forms
- **WHEN** a route operation or instance binding keeps a human-readable label
- **THEN** the typed ids remain sufficient to execute the runtime behavior
- **AND** removing the diagnostic string would not make the route ambiguous to the runtime

### Requirement: Canonical IR supports non-ARM system-vector topologies

The pipeline MUST produce correct interrupt and vector-slot metadata for non-ARM ISA families
(RISC-V, Xtensa) without applying ARM Cortex-M exception table assumptions.

#### Scenario: RISC-V devices receive a RISC-V vector baseline

- **WHEN** canonical IR is built for an ESP32-C3 (RISC-V RV32IMC) device
- **THEN** interrupt vector slots are derived from the RISC-V CLIC flat table
- **AND** no ARM-specific exception slots (NMI_Handler, HardFault_Handler, PendSV_Handler,
  SysTick_Handler) are inserted into the interrupt binding list
- **AND** `vector_slot` values reflect actual hardware interrupt IDs, not NVIC-offset numbers

#### Scenario: Xtensa devices receive an Xtensa vector baseline

- **WHEN** canonical IR is built for an ESP32-S3 (Xtensa LX7) device
- **THEN** interrupt vector slots are derived from the Xtensa 32-level interrupt model
- **AND** no Cortex-M exception slots appear in the interrupt binding list

#### Scenario: Unknown core fails explicitly rather than silently

- **WHEN** a device with an unrecognized `core` string is processed
- **THEN** the pipeline raises an explicit error identifying the unknown core
- **AND** it does not silently fall back to a Cortex-M4 baseline

### Requirement: Canonical IR models ESP32 clock/reset control signals

The pipeline MUST parse and normalize ESP32 PCR and DPORT clock/reset register references into
canonical clock-node and reset-control facts, consistent with the patterns used for ST RCC and
NXP CCM.

#### Scenario: ESP32-C3 PCR register references are resolved

- **WHEN** a peripheral patch declares `rcc_enable_signal: "PCR_UART0_CONF0_REG.UART0_CLK_EN"`
- **THEN** `connector_model` resolves the peripheral name (`PCR`), register name
  (`UART0_CONF0_REG`), and field name (`UART0_CLK_EN`) to a typed register reference
- **AND** a `clock-node:pcr-uart0-conf0-reg` clock node is inferred in the device clock graph

#### Scenario: ESP32 DPORT register references are resolved (ESP32 original / S3)

- **WHEN** a peripheral patch declares
  `rcc_enable_signal: "DPORT_PERIP_CLK_EN_REG.UART0_CLK_EN"`
- **THEN** `connector_model` resolves it to a typed register reference via the generic
  `REGISTER_FIELD_TARGET_PATTERN` fallback or a dedicated DPORT matcher
- **AND** a corresponding clock node is added to the device clock graph

### Requirement: Canonical IR tracks supplementary-source provenance for IO Matrix facts

The canonical IR MUST preserve the provenance of non-SVD Espressif routing data used to build
IO Matrix bindings.

#### Scenario: IO Matrix pin bindings cite the supplementary source

- **WHEN** canonical IR contains an Espressif pin-signal binding derived from `gpio_sig_map.h`
- **THEN** that binding's provenance identifies the supplementary source file and revision
- **AND** the provenance is distinct from the SVD provenance used for registers and interrupts

### Requirement: Canonical IR models Harvard address space separation

For Harvard architecture devices, `CanonicalDeviceIR` MUST annotate each memory region with
its address space so that overlapping base addresses across separate spaces are not ambiguous.

#### Scenario: AVR flash and EEPROM regions carry distinct address spaces

- **WHEN** canonical IR is built for an AVR-DA device
- **THEN** the flash memory region carries `address_space: "prog"`
- **AND** the SRAM memory region carries `address_space: "data"`
- **AND** the EEPROM memory region carries `address_space: "eeprom"`
- **AND** no two memory regions with the same `base_address` value appear without distinct
  `address_space` values

#### Scenario: Unified-address-space devices omit the address space field

- **WHEN** canonical IR is built for an ARM Cortex-M, RISC-V, or Xtensa device
- **THEN** all memory regions have `address_space` absent or null
- **AND** no behavioral change occurs in normalization, emission, or validation for those devices

#### Scenario: Schema version reflects the Harvard extension

- **WHEN** any consumer reads a serialized `CanonicalDeviceIR`
- **THEN** the schema version is `1.2.0` or higher if `address_space` may be present
- **AND** consumers that only handle `address_space: null` can ignore the field without error

### Requirement: Canonical IR recognizes EEPROM as a distinct memory kind

The pipeline MUST represent EEPROM memory as a first-class memory kind with no startup copy
roles, distinct from flash (copy-source), SRAM (copy-target), and retained memory.

#### Scenario: EEPROM region has no startup roles

- **WHEN** canonical IR is built for a device with an EEPROM region
- **THEN** the EEPROM memory region has zero startup roles
- **AND** it is not designated `nonvolatile`, `copy-source`, `volatile-target`, or
  `copy-target` — none of those roles apply to EEPROM in startup context
- **AND** the startup emitter does not emit copy or zeroing code for the EEPROM region

#### Scenario: EEPROM kind is distinct from flash and SRAM kinds

- **WHEN** a memory region with kind `"eeprom"` is present in canonical IR
- **THEN** it is correctly classified as EEPROM in normalization output
- **AND** it does not inherit `vector-source`, `copy-source`, `stack-target`, or any
  other role that would cause incorrect startup behavior

### Requirement: Canonical IR supports the AVR8 system-vector topology

The pipeline MUST produce correct interrupt and vector-slot metadata for 8-bit AVR devices,
where the vector table starts directly with device-specific handlers (no ARM system exceptions
prefix) and the reset handler occupies slot 0.

#### Scenario: AVR8 devices receive a reset-only vector baseline

- **WHEN** canonical IR is built for an AVR-DA device with core `"avr8"`
- **THEN** vector slot 0 is reserved for the reset handler (`__vector_0`)
- **AND** no ARM system exception slots (NMI_Handler, HardFault_Handler, SysTick_Handler,
  etc.) appear in the interrupt binding list
- **AND** device interrupt bindings start at vector slot 1 and are numbered by their
  ATDF interrupt line value

#### Scenario: Unknown core fails explicitly rather than silently defaulting to ARM

- **WHEN** a device with an unrecognized `core` string is processed
- **THEN** the pipeline raises an explicit error identifying the unknown core
- **AND** it does not silently fall back to a Cortex-M4 baseline

### Requirement: Vector slots SHALL carry core affinity for dual-core targets

The canonical device IR SHALL annotate every vector slot with a `core_affinity`
indicator so emitters can partition vectors across the cores of multi-core devices
without re-deriving the routing from peripheral names at emission time.

#### Scenario: Default affinity is cpu0

- **WHEN** a single-core device (Cortex-M, RISC-V mononúcleo, AVR8) is normalized
- **THEN** every `VectorSlotDescriptor.core_affinity` is `"cpu0"` by default
- **AND** non-Xtensa runtime emitters ignore the field (forward-compatible)

#### Scenario: Xtensa dual-core targets partition vectors by interrupt-matrix peripheral

- **WHEN** an ESP32 (LX6) or ESP32-S3 (LX7) device is normalized
- **THEN** vector slots whose interrupt's owning peripheral is `INTERRUPT_CORE0` (S3),
  `DPORT_PRO_INTR_*` (classic), or has no peripheral attribution carry
  `core_affinity = "cpu0"`
- **AND** vector slots whose interrupt's owning peripheral is `INTERRUPT_CORE1` (S3) or
  `DPORT_APP_INTR_*` (classic) carry `core_affinity = "cpu1"`
- **AND** system exceptions explicitly broadcast to both cores (e.g. NMI) carry
  `core_affinity = "shared"`

### Requirement: Xtensa dual-core families SHALL emit dual-core control plane

Xtensa dual-core families (ESP32, ESP32-S3) SHALL emit a control plane that
brings up both cores at the bootstrap layer, while explicitly delegating
affinity routing and inter-core synchronization to application or framework
code. The control-plane facts (which register releases the secondary core,
what bit is touched, what start vector address is used) SHALL be sourced from
`Device.app_cpu_control_plane` and SHALL be discoverable from the published
descriptor's data-only surface.

#### Scenario: Dual vector tables are emitted

- **WHEN** `runtime_xtensa_startup.py` emits `startup.cpp` for an ESP32 or
  ESP32-S3 device
- **THEN** the file contains `_vectors_cpu0[]` and `_vectors_cpu1[]` arrays
- **AND** each array is populated from vector slots filtered by
  `core_affinity` (`"cpu0"` and `"shared"` go to `_vectors_cpu0[]`; `"cpu1"`
  and `"shared"` go to `_vectors_cpu1[]`)
- **AND** the linker section attribute on each table differs
  (`.xtensa_vectors_cpu0` vs `.xtensa_vectors_cpu1`) so the consumer linker
  script can map them into the per-core VECBASE regions

#### Scenario: Both cores have entry points

- **WHEN** `startup.cpp` is emitted for a dual-core Xtensa device
- **THEN** the file declares `Reset_Handler` (PRO_CPU entry, performs BSS/data
  init, C++ ctors, calls `main()`)
- **AND** the file declares `Reset_Handler_CPU1` (APP_CPU entry, skips static
  init, calls weak `app_main_cpu1()` if defined, then enters
  `Default_Handler` loop)
- **AND** both symbols are exposed with `extern "C"` linkage

#### Scenario: APP_CPU bring-up primitive is data-driven

- **WHEN** `startup.cpp` is emitted for a dual-core Xtensa device
- **THEN** the file declares `bring_up_app_cpu()` whose register touches are
  derived from `Device.app_cpu_control_plane`, not from emitter-internal
  hardcoded constants
- **AND** for ESP32 classic the emitted body writes
  `DPORT.APPCPU_CTRL_B` bit 0 (sourced from the typed release register)
- **AND** for ESP32-S3 the emitted body sets
  `SYSTEM.CORE_1_CONTROL_0.CLKGATE_EN` then clears
  `SYSTEM.CORE_1_CONTROL_1.RUNSTALL` (sourced from the typed release register
  pair)
- **AND** the function is NOT called automatically from `Reset_Handler` —
  applications and runtimes invoke it explicitly

#### Scenario: Dual-core facts are discoverable from descriptor data alone

- **WHEN** a downstream consumer (e.g. alloy runtime) inspects only the
  published descriptor (no C++ source parsing)
- **THEN** the consumer can determine `core_count = 2` from
  `capabilities.json`
- **AND** the consumer can resolve the typed `RegisterId` for the
  secondary-core release register from
  `device:secondary-core-release-register` in `capabilities.json`
- **AND** the consumer can locate the release step in
  `system_sequences.hpp` under
  `SystemSequenceStepKindId::secondary_core_release`
- **AND** no part of the determination requires matching register names by
  string

#### Scenario: Affinity routing and inter-core IPC are out of scope

- **WHEN** `startup.cpp` is emitted for a dual-core Xtensa device
- **THEN** the file does NOT contain IPI sender/receiver helpers, spinlocks,
  queues, mailboxes, or shared-memory cache-invalidation primitives
- **AND** affinity routing of individual interrupts at runtime is delegated
  entirely to application or framework code via the `core_affinity` field
  already present on each vector slot

### Requirement: IR SHALL carry typed multicore topology on every Device

The canonical device IR MUST carry a typed `multicore_topology` field on every
`Device`, defaulting to `single_core`, plus an explicit integer `core_count`.
Consumers MUST be able to branch on topology without parsing the legacy
stringly-typed `core` field.

#### Scenario: Single-core devices default to single_core

- **WHEN** the canonical IR is built for any single-core device (Cortex-M0+,
  Cortex-M4, RISC-V mononúcleo, AVR8, ESP32-C3)
- **THEN** `Device.multicore_topology` is `MulticoreTopology.single_core`
- **AND** `Device.core_count` is `1`
- **AND** `Device.app_cpu_control_plane` is `None`

#### Scenario: ESP32 classic carries xtensa_asymmetric_dual_core

- **WHEN** the canonical IR is built for an ESP32 classic device
- **THEN** `Device.multicore_topology` is
  `MulticoreTopology.xtensa_asymmetric_dual_core`
- **AND** `Device.core_count` is `2`
- **AND** `Device.app_cpu_control_plane` is populated

#### Scenario: ESP32-S3 carries xtensa_asymmetric_dual_core

- **WHEN** the canonical IR is built for an ESP32-S3 device
- **THEN** `Device.multicore_topology` is
  `MulticoreTopology.xtensa_asymmetric_dual_core`
- **AND** `Device.core_count` is `2`
- **AND** `Device.app_cpu_control_plane` is populated

#### Scenario: RP2040 carries symmetric_dual_core

- **WHEN** the canonical IR is built for an RP2040 device
- **THEN** `Device.multicore_topology` is
  `MulticoreTopology.symmetric_dual_core`
- **AND** `Device.core_count` is `2`
- **AND** `Device.app_cpu_control_plane` is `None` (symmetric dual-core does
  not use the asymmetric APP_CPU release lever)

### Requirement: IR SHALL carry an APP_CPU control plane for asymmetric Xtensa

For asymmetric Xtensa dual-core devices the IR MUST carry an
`AppCpuControlPlane` record naming the typed `RegisterId` of the secondary-core
release register, the bit-level operation, and the start-vector symbol. The
record MUST reference registers by typed identifier rather than by raw
address or string name.

#### Scenario: ESP32 classic exposes DPORT.APPCPU_CTRL_B as the release register

- **WHEN** the canonical IR is built for an ESP32 classic device
- **THEN** `Device.app_cpu_control_plane.release_register` resolves to the
  typed id of `DPORT.APPCPU_CTRL_B`
- **AND** `Device.app_cpu_control_plane.release_register_secondary` is `None`
- **AND** `Device.app_cpu_control_plane.operation` is `"set-bit-0"`
- **AND** `Device.app_cpu_control_plane.start_vector_symbol` is
  `"_vectors_cpu1"`

#### Scenario: ESP32-S3 exposes both SYSTEM.CORE_1_CONTROL_0 and _1

- **WHEN** the canonical IR is built for an ESP32-S3 device
- **THEN** `Device.app_cpu_control_plane.release_register` resolves to the
  typed id of `SYSTEM.CORE_1_CONTROL_0`
- **AND** `Device.app_cpu_control_plane.release_register_secondary` resolves
  to the typed id of `SYSTEM.CORE_1_CONTROL_1`
- **AND** `Device.app_cpu_control_plane.operation` is
  `"clear-runstall-after-clkgate"`

#### Scenario: Pipeline fails fast if the release register is filtered out

- **WHEN** an asymmetric Xtensa device declares an `app_cpu_control_plane`
  but the named register is absent from the typed `RegisterId` enum
- **THEN** the pipeline fails admission with a diagnostic naming the missing
  register and pointing at the patch overlay

### Requirement: RegisterDescriptor SHALL carry a typed role

Every `RegisterDescriptor` MUST carry a typed `role` field. The default role
is `general`. Registers participating in the secondary-core release sequence
MUST be tagged with `role = "secondary-core-release"` so consumers find them
without name pattern matching.

#### Scenario: General registers default to role = general

- **WHEN** the IR is built for any device
- **THEN** every `RegisterDescriptor` not explicitly tagged carries
  `role = "general"`
- **AND** consumers that ignore the field see no behavior change

#### Scenario: APP_CPU control registers carry secondary-core-release role

- **WHEN** the IR is built for ESP32 classic
- **THEN** the descriptor for `DPORT.APPCPU_CTRL_B` carries
  `role = "secondary-core-release"`
- **WHEN** the IR is built for ESP32-S3
- **THEN** the descriptors for `SYSTEM.CORE_1_CONTROL_0` and
  `SYSTEM.CORE_1_CONTROL_1` both carry `role = "secondary-core-release"`

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

### Requirement: IR SHALL model PIO blocks with a structured PioDescriptor

The canonical device IR SHALL represent each Programmable I/O block as a
`PioDescriptor` carrying the compile-time facts that downstream emitters need to
populate driver-semantic traits (state-machine count, instruction memory depth,
TX/RX FIFO depth, GPIO range, base address, and TX/RX DMA DREQ bases).

`PioDescriptor` SHALL be carried on `CanonicalDeviceIR` as `pio_blocks: list[PioDescriptor]`,
defaulting to an empty list for devices without PIO hardware.

#### Scenario: RP2040 IR exposes two structured PIO descriptors

- **WHEN** the RP2040 device is normalized
- **THEN** `device.pio_blocks` contains two entries with `pio_id` `Pio0` and `Pio1`
- **AND** each entry records `state_machine_count = 4`, `instruction_memory_depth = 32`,
  `tx_fifo_depth = 4`, `rx_fifo_depth = 4`, `gpio_base = 0`, `gpio_count = 30`
- **AND** `Pio0.base_address == 0x50200000` and `Pio1.base_address == 0x50300000`
- **AND** `Pio0.dreq_tx_base == 0`, `Pio0.dreq_rx_base == 4`,
  `Pio1.dreq_tx_base == 8`, `Pio1.dreq_rx_base == 12`

#### Scenario: Devices without PIO leave pio_blocks empty

- **WHEN** any non-RP2040 admitted device is normalized
- **THEN** `device.pio_blocks` is an empty list
- **AND** the canonical IR JSON serialization omits or emits an empty `pio_blocks` array

#### Scenario: PioDescriptor data is patch-sourced and provenance-tagged

- **WHEN** the RP2040 normalizer assembles `pio_blocks`
- **THEN** the values are loaded from `patches/raspberrypi/rp2040/pio.json`
- **AND** each `PioDescriptor` carries provenance referencing that patch file

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

### Requirement: CanonicalDeviceIR SHALL expose hardware-feature descriptors for Espressif peripherals

Devices on Espressif targets MUST surface six hardware-feature descriptor
tuples on the canonical IR — one per peripheral type called out by
``add-usb-hal``-class concept checks: `uart_peripherals`,
`spi_peripherals`, `adc_units`, `timer_units`, `dma_channels`, plus a
single `ledc` block. Each descriptor records the static silicon facts
(base address, FIFO depth / endpoint count, GPIO-matrix signal indices,
DMA support, IO-MUX fast-path pins, ADC channel→pin maps) that the
alloy concept-validated HAL needs at compile time.

These descriptors MUST default to empty for devices whose family
overlay doesn't ship the block, so existing fixtures stay byte-stable.

#### Scenario: ESP32 classic admits three UART peripherals with 128-byte FIFOs

- **WHEN** the normalizer processes ESP32 classic
- **THEN** `Device.uart_peripherals` contains three entries with
  `peripheral_id ∈ {"UART0", "UART1", "UART2"}`
- **AND** every entry carries `fifo_depth = 128` and `supports_dma = true`

#### Scenario: ESP32-C3 admits a single SPI peripheral without IO_MUX fast path

- **WHEN** the normalizer processes ESP32-C3
- **THEN** `Device.spi_peripherals` contains one entry with
  `peripheral_id = "SPI2"` and `has_iomux_fast_path = false`

#### Scenario: ESP32-S3 admits two ADC units with the second flagged as Wi-Fi-conflicted

- **WHEN** the normalizer processes ESP32-S3
- **THEN** `Device.adc_units` contains two entries
- **AND** `unit_id = "ADC2"` carries `conflicts_with_wifi = true`

#### Scenario: Non-Espressif devices carry empty hardware-feature tuples

- **WHEN** the normalizer processes a non-Espressif device (STM32, NXP,
  RP2040, AVR-DA, SAME70)
- **THEN** `Device.uart_peripherals`, `Device.spi_peripherals`,
  `Device.adc_units`, `Device.timer_units`, `Device.dma_channels` are
  the empty tuple
- **AND** `Device.ledc` is `None`
- **AND** all six fields are omitted from the serialized canonical IR JSON

### Requirement: RP2040 IR SHALL surface GPIO pad topology via gpio_pins

For RP2040, the canonical IR SHALL populate `Device.gpio_pins` with one
`GpioPinDescriptor` per admitted pad (`GP0`..`GP29` on the QFN56 package,
filtered to the package's bonded pads on `pico`). The descriptor uses
`port = "GPIO"` and `port_offset = 0` (single GPIO peripheral on RP2040),
`pin_index = pad number`, and the FUNCSEL alternate-function table
already produced by the family-patch normalize path
(`af_number = FUNCSEL index 1..9`).

#### Scenario: rp2040 IR exposes 30 GPIO descriptors

- **WHEN** the rp2040 device is normalized
- **THEN** `device.gpio_pins` has exactly 30 entries (`GP0`..`GP29`)
- **AND** every entry carries `port = "GPIO"`, `port_offset = 0`,
  `is_input_only = false`
- **AND** the `pico` device is normalized with 26 `gpio_pins` (the QFN56
  pads minus GP23/GP24/GP29 which are not bonded on the Pico package)

#### Scenario: rp2040 GP0 records SPI / UART / I2C alternate functions

- **WHEN** `device.gpio_pins` is populated for rp2040
- **THEN** the `GP0` entry carries alt-function entries with
  `(af_number=1, signal_name="RX", peripheral="SPI0")`,
  `(af_number=2, signal_name="TX", peripheral="UART0")`, and
  `(af_number=3, signal_name="SDA", peripheral="I2C0")`

### Requirement: RP2040 IR SHALL include UART, SPI, and ADC peripheral facts via gpio_pins AF table

The RP2040 GPIO descriptors SHALL be authoritative for the per-pin
function table; downstream emitters that produce `uart.hpp`, `spi.hpp`,
and `adc.hpp` SHALL derive valid-pin sets by filtering
`device.gpio_pins[*].alt_functions` for the relevant peripheral.

#### Scenario: UART0 valid TX pin set is derivable from gpio_pins

- **WHEN** the rp2040 device is normalized
- **THEN** filtering `device.gpio_pins` for entries whose
  `alt_functions` include `peripheral = "UART0"` and `signal_name = "TX"`
  yields the pad numbers `{0, 12, 16, 28}`

#### Scenario: ADC channel pins are derivable from gpio_pins

- **WHEN** the rp2040 device is normalized
- **THEN** filtering `device.gpio_pins` for entries whose
  `alt_functions` include `peripheral = "ADC"` yields the pad numbers
  `{26, 27, 28, 29}` (the four external analog inputs)

### Requirement: CanonicalDeviceIR SHALL surface I2C controller hardware-feature descriptors

`CanonicalDeviceIR` SHALL surface I2C / TWI hardware-feature facts via an `i2c_peripherals` tuple of `I2cPeripheralDescriptor` records. Each descriptor MUST carry the silicon-fixed facts that alloy's `I2cMaster<T>` concept relies on at compile time:

- `peripheral_id` — vendor name (`"I2C0"`, `"I2C1"`, `"TWI0"`,…).
- `base_address` — peripheral base, from SVD or ATDF.
- `clock_source` — STM32-only token (`"pclk"`, `"hsi16"`, `"sysclk"`),
  `None` on families whose I2C clock is family-fixed.
- `dma_req_tx`, `dma_req_rx` — DMAMUX line / RP2040 DREQ index, `None`
  when the controller has no DMA-attached path.
- `valid_sda_pins`, `valid_scl_pins` — sorted ascending tuple of GPIO
  pad numbers that can route this controller's SDA / SCL signal. The
  empty tuple is the **`AllGpios{}` sentinel** used by Espressif's IO
  matrix to mean "any pad accepted".
- `gpio_matrix_in_sda_signal`, `gpio_matrix_in_scl_signal`,
  `gpio_matrix_out_sda_signal`, `gpio_matrix_out_scl_signal` —
  Espressif IO-matrix signal indices, `None` on families with fixed pin
  routing.
- `supports_fast_mode_plus` — `true` for ESP32-S3 + STM32G0/F4 (1 MHz
  Fm+); `false` otherwise.
- `portmux_alt` — AVR-DA PORTMUX alternate-pin flag, `None` elsewhere.

`Device.i2c_peripherals` MUST default to the empty tuple for devices
without I2C hardware so existing fixtures stay byte-stable.

#### Scenario: STM32G071RB admits two I2C peripherals via PCLK

- **WHEN** the normalizer processes STM32G071RB
- **THEN** `Device.i2c_peripherals` contains entries for `I2C1`
  (`base_address = 0x40005400`) and `I2C2` (`base_address = 0x40005800`)
- **AND** both carry `clock_source = "pclk"`
- **AND** `valid_sda_pins` / `valid_scl_pins` are non-empty (sourced
  from the ST Open Pin Data AF table)

#### Scenario: ESP32-C3 admits a single I2C with the AllGpios sentinel

- **WHEN** the normalizer processes ESP32-C3
- **THEN** `Device.i2c_peripherals` contains exactly one entry
  (`peripheral_id = "I2C0"`)
- **AND** `valid_sda_pins == ()` (the AllGpios sentinel — any pad routes
  via the IO matrix)
- **AND** `gpio_matrix_in_sda_signal` / `gpio_matrix_out_sda_signal`
  carry the C3 IO-matrix indices

#### Scenario: RP2040 records pin constraints from datasheet Table 2-5

- **WHEN** the rp2040 device is normalized
- **THEN** `Device.i2c_peripherals` contains entries for `I2C0` and
  `I2C1`
- **AND** I2C0 carries `valid_sda_pins == (0, 4, 8, 12, 16, 20, 24, 28)`
- **AND** I2C0 carries `valid_scl_pins == (1, 5, 9, 13, 17, 21, 25, 29)`
- **AND** I2C0 carries `dma_req_tx = 32`, `dma_req_rx = 33` (datasheet
  Table 2-7)

#### Scenario: Devices without I2C carry an empty tuple

- **WHEN** the normalizer processes any device without an I2C / TWI
  controller
- **THEN** `Device.i2c_peripherals` is the empty tuple
- **AND** the field is omitted from the serialized canonical IR JSON

