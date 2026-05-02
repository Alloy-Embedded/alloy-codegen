## ADDED Requirements

### Requirement: `vector_table.c` SHALL Emit A Typed NVIC Priority Table

The published `vector_table.c` SHALL emit a typed
`alloy_nvic_priority_setup[]` table containing one row per
`InterruptVector` whose `priority` is set, plus a
`alloy_nvic_apply_priorities(void)` helper that walks the table
and applies each priority via `NVIC_SetPriority`.  Rows where
`priority is None` SHALL be omitted from the table.

#### Scenario: STM32 G0 priority table contains explicit rows only

- **WHEN** alloy-codegen emits `vector_table.c` for a
  `st/stm32g0/stm32g071rb` whose YAML sets `priority: 1` on
  `EXTI4_15_IRQHandler` and leaves the rest unset
- **THEN** `alloy_nvic_priority_setup[]` contains one row
  with `irqn=7, priority=<1 left-shifted into the upper bits
  of an 8-bit IPR slot>`
- **AND** the table size is exactly 1
- **AND** `alloy_nvic_apply_priorities()` is defined and walks
  the table

### Requirement: Published Artifact Tree SHALL Include `system_init.c`

The published artifact tree SHALL include a runtime-lite
`system_init.c` carrying typed `alloy_system_init_fpu()`,
`alloy_system_init_mpu()`, and umbrella `alloy_system_init()`
helpers for every admitted device.

#### Scenario: STM32 H7 publishes system_init.c with FPU enable

- **WHEN** alloy-codegen emits artifacts for any STM32 H7 device
- **THEN** `out/st/stm32h7/<chip>/system_init.c` exists
- **AND** `alloy_system_init_fpu()` body writes
  `SCB->CPACR |= (0xF << 20)` (full access to CP10/CP11)
- **AND** `alloy_system_init_mpu()` body writes
  `MPU->CTRL = MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_ENABLE_Msk`

#### Scenario: Cortex-M0+ chip without FPU emits no-op body

- **WHEN** alloy-codegen emits `system_init.c` for any STM32 G0
  device (no FPU)
- **THEN** `alloy_system_init_fpu()` body is empty (a single
  `return;` statement)
- **AND** `alloy_system_init_mpu()` body is empty when
  `core.mpu = MpuVariant.NONE`, or programs the MPU otherwise

### Requirement: NVIC Priority And System-Init Bodies SHALL Stay Zero-String

`vector_table.c` and `system_init.c` SHALL contain no semantic `const char*` fields in priority-table rows or system-init bodies; all references SHALL be encoded as enums, ids, integers, or masks per the existing zero-string artifact-contract rule.

#### Scenario: Zero-string gate passes after NVIC + system-init lands

- **WHEN** the pre-publication zero-string gate scans
  `out/<vendor>/<family>/<chip>/vector_table.c` and
  `system_init.c` after this proposal's emitter changes
- **THEN** the gate finds no semantic string literal in the
  priority-table rows or any `alloy_system_init_*` body
