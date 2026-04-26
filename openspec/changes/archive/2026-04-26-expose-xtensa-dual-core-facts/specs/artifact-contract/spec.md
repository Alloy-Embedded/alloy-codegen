## ADDED Requirements

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
