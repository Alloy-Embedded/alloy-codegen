## ADDED Requirements

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

Xtensa dual-core families (ESP32, ESP32-S3) SHALL emit a control plane that brings up
both cores at the bootstrap layer, while explicitly delegating affinity routing and
inter-core synchronization to application or framework code.

#### Scenario: Dual vector tables are emitted

- **WHEN** `runtime_xtensa_startup.py` emits `startup.cpp` for an ESP32 or ESP32-S3 device
- **THEN** the file contains `_vectors_cpu0[]` and `_vectors_cpu1[]` arrays
- **AND** each array is populated from vector slots filtered by `core_affinity`
  (`"cpu0"` and `"shared"` go to `_vectors_cpu0[]`; `"cpu1"` and `"shared"` go to
  `_vectors_cpu1[]`)
- **AND** the linker section attribute on each table differs (`.xtensa_vectors_cpu0`
  vs `.xtensa_vectors_cpu1`) so the consumer linker script can map them into the
  per-core VECBASE regions

#### Scenario: Both cores have entry points

- **WHEN** `startup.cpp` is emitted for a dual-core Xtensa device
- **THEN** the file declares `Reset_Handler` (PRO_CPU entry, performs BSS/data init,
  C++ ctors, calls `main()`)
- **AND** the file declares `Reset_Handler_CPU1` (APP_CPU entry, skips static init,
  calls weak `app_main_cpu1()` if defined, then enters `Default_Handler` loop)
- **AND** both symbols are exposed with `extern "C"` linkage

#### Scenario: APP_CPU bring-up primitive is emitted

- **WHEN** `startup.cpp` is emitted for a dual-core Xtensa device
- **THEN** the file declares `bring_up_app_cpu()` that touches the per-device CPU-1
  control registers to release APP_CPU from reset
- **AND** for ESP32 classic the function writes `DPORT.APPCPU_CTRL_B` bit 0
- **AND** for ESP32-S3 the function clears `SYSTEM.CORE_1_CONTROL_1.RUNSTALL` after
  enabling `SYSTEM.CORE_1_CONTROL_0.CLKGATE_EN`
- **AND** the function is NOT called automatically from `Reset_Handler` — applications
  invoke it explicitly when they want the second core running

#### Scenario: Affinity routing and inter-core IPC are out of scope

- **WHEN** `startup.cpp` is emitted for a dual-core Xtensa device
- **THEN** the file does NOT contain IPI sender/receiver helpers, spinlocks, queues,
  or shared-memory cache invalidation routines
- **AND** an emitted comment block points readers at esp-idf's `esp_intr_alloc` and
  framework synchronization primitives for those concerns

#### Scenario: ESP32-S3 retrofit replaces single-core-perspective

- **WHEN** the existing ESP32-S3 device is re-normalized after this change is applied
- **THEN** `INTERRUPT_CORE1` is no longer filtered from the canonical IR by
  `_build_esp32_device_ir`
- **AND** the emitted ESP32-S3 `startup.cpp` contains the dual vector tables, both
  Reset_Handlers, and `bring_up_app_cpu()` — superseding the single-core-perspective
  posture introduced in the prior `add-espressif-esp32-target` change
- **AND** the regenerated ESP32-S3 goldens reflect the new dual-core artifacts
