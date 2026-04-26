## ADDED Requirements

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

## MODIFIED Requirements

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
