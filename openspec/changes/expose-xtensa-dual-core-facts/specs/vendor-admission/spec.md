## MODIFIED Requirements

### Requirement: Espressif ESP32 classic family is admitted as a dual-core LX6 target

The pipeline MUST support the Espressif ESP32 classic family (dual-core
Xtensa LX6) as a first-class target, sharing the existing `espressif-svd`
source adapter and the dual-core Xtensa runtime contract. ESP32 classic
admission MUST additionally surface the dual-core control plane facts
(topology, core count, secondary-core release register) in the published
artifacts so downstream consumers can reason about cores from data alone.

#### Scenario: ESP32 classic is a supported family

- **WHEN** the pipeline runs for vendor `espressif`, family `esp32`
- **THEN** it fetches `esp32.svd` via the existing `espressif-svd` adapter
  without requiring a new source adapter
- **AND** it produces a valid `CanonicalDeviceIR` for both `esp32` (QFN48)
  and `esp32-wroom32` (module) device variants
- **AND** the canonical IR has `multicore_topology =
  xtensa_asymmetric_dual_core`, `core_count = 2`, and a populated
  `app_cpu_control_plane`
- **AND** it emits runtime C++ headers that pass the architecture-scoped
  artifact contract

#### Scenario: ESP32 classic admission publishes multicore facts in artefacts

- **WHEN** the pipeline emits the published artefact bundle for an admitted
  ESP32 classic device
- **THEN** `capabilities.json` carries
  `device:multicore-topology = "xtensa-dual-core"`,
  `device:core-count = 2`, and
  `device:secondary-core-release-register = "register_dport_appcpu_ctrl_b"`
- **AND** `system_sequences.hpp` ends `default_bringup` with a
  `secondary_core_release` step referencing the typed release register
- **AND** `registers.hpp` emits `register_dport_appcpu_ctrl_b` with
  `role = secondary_core_release`
- **AND** these facts are sufficient for a descriptor-only consumer to
  decide that the device is dual-core and which register releases the
  secondary core

#### Scenario: ESP32 classic admits two packages sharing one family catalog

- **WHEN** the bootstrap registers `espressif/esp32`
- **THEN** the family catalog `patches/espressif/esp32/family.json` is
  shared by every device variant
- **AND** at least two device patches exist: `esp32.json` for QFN48 and
  `esp32-wroom32.json` for the WROOM-32 module
- **AND** the family catalog carries a `multicore_topology` block declaring
  `topology = "xtensa-asymmetric-dual-core"`, `core_count = 2`, and the
  `app_cpu_control_plane` register reference
- **AND** ESP32-PICO-D4 and ESP32-WROVER are explicitly NOT admitted in
  the original admission change (this change does not relax that)

#### Scenario: ESP32-S3 admission also publishes multicore facts

- **WHEN** the pipeline emits the published artefact bundle for an admitted
  ESP32-S3 device
- **THEN** `capabilities.json` carries
  `device:multicore-topology = "xtensa-dual-core"` and
  `device:core-count = 2`
- **AND** `device:secondary-core-release-register` references both
  `register_system_core_1_control_0` and
  `register_system_core_1_control_1`
- **AND** the artefacts otherwise match the ESP32 classic shape (step kind,
  register role tag)
