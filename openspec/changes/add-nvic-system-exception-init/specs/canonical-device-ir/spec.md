## ADDED Requirements

### Requirement: Canonical IR `InterruptVector` SHALL Carry Optional Per-Vector Priority

The canonical IR `InterruptVector` dataclass SHALL carry an
optional `priority: int | None` field.  When set, the priority
SHALL be in `[0, 1 << core.nvic_priority_bits)` and SHALL be
validated by the loader; out-of-range values SHALL raise
`ConfigError`.

#### Scenario: STM32 G0 vector with valid priority loads

- **WHEN** a YAML carries
  `interrupts.vectors[7]: {num: 7, name: EXTI4_15_IRQHandler,
  priority: 12}` for a chip with
  `core.nvic_priority_bits: 2`
- **THEN** the loader rejects (priority 12 ≥ 4)
- **AND** the error message names the offending vector and the
  priority bound

#### Scenario: Vector without priority loads as None

- **WHEN** a YAML omits the `priority` field on a vector entry
- **THEN** `device.interrupts.vectors[i].priority` is `None`
- **AND** the emitter does not emit a row for that vector in
  `kNvicPrioritySetup`

### Requirement: Canonical IR `core.fpu` SHALL Be A Typed Enum

The canonical IR SHALL expose `core.fpu` as a typed
`FpuVariant ∈ {NONE, FPV4_SP_D16, FPV5_SP_D16, FPV5_D16,
FPV5_DP_D16}`.  Legacy `fpu: bool` carriage SHALL be lifted to
`FPV4_SP_D16` for ARMv7E-M cores and `NONE` otherwise unless the
YAML overrides explicitly.

#### Scenario: STM32 F4 core.fpu lifts to FPV4_SP_D16

- **WHEN** alloy-codegen loads any STM32 F4 device
- **THEN** `device.identity.core.fpu` is `FpuVariant.FPV4_SP_D16`
- **AND** the emitter can dispatch on the variant without
  re-deriving the FPU type from the core ISA name

### Requirement: Canonical IR `core.mpu` SHALL Be A Typed Enum

The canonical IR SHALL expose `core.mpu` as a typed
`MpuVariant ∈ {NONE, ARMV7M_PMSA, ARMV8M_PMSA}`.  Legacy
`mpu: bool` carriage SHALL be lifted to `ARMV7M_PMSA` for
ARMv7-M cores and `ARMV8M_PMSA` for ARMv8-M cores unless
overridden.

#### Scenario: STM32 H7 core.mpu lifts to ARMV7M_PMSA

- **WHEN** alloy-codegen loads any STM32 H7 device
- **THEN** `device.identity.core.mpu` is `MpuVariant.ARMV7M_PMSA`
