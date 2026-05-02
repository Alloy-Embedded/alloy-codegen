## ADDED Requirements

### Requirement: Runtime-Lite Contract SHALL Expose `alloy_nvic_apply_priorities`

The runtime-lite contract SHALL expose
`void alloy_nvic_apply_priorities(void)` defined in
`vector_table.c` so consumers can apply the per-vector NVIC
priority configuration in their reset path before any IRQ is
enabled.  The function body SHALL walk the typed
`alloy_nvic_priority_setup[]` table and call
`NVIC_SetPriority` for each entry.

#### Scenario: Reset path applies priorities before NVIC enable

- **WHEN** a consumer calls
  `alloy_nvic_apply_priorities()` from `Reset_Handler` before
  any peripheral interrupt is enabled
- **THEN** every entry of `alloy_nvic_priority_setup[]` has its
  priority written into `NVIC->IPR[irqn]` upper bits
- **AND** unset vectors retain the chip's reset-default
  priority (0)

### Requirement: Runtime-Lite Contract SHALL Expose `alloy_system_init_fpu` And `alloy_system_init_mpu`

The runtime-lite contract SHALL expose typed
`alloy_system_init_fpu(void)` and `alloy_system_init_mpu(void)`
helpers in `system_init.c`.  When `core.fpu = FpuVariant.NONE`
or `core.mpu = MpuVariant.NONE`, the corresponding helper body
SHALL be empty (return immediately) so consumers can call them
unconditionally.

#### Scenario: STM32 G0 startup calls fpu-init unconditionally

- **WHEN** consumer code calls `alloy_system_init_fpu()` from
  `Reset_Handler` on an STM32 G0 (no FPU)
- **THEN** the function returns without writing any register
- **AND** the consumer does not need a `#ifdef HAS_FPU` guard

#### Scenario: STM32 H7 startup enables FPU and MPU

- **WHEN** consumer code calls
  `alloy_system_init()` from `Reset_Handler` on an STM32 H7
- **THEN** the umbrella function enables the FPU
  (`SCB->CPACR |= (0xF << 20)`), enables the MPU
  (`MPU->CTRL |= MPU_CTRL_ENABLE_Msk`), and applies NVIC
  priorities, in that order
- **AND** subsequent C++ static initializers using floating
  point arithmetic do not fault

### Requirement: Runtime-Lite Contract SHALL Document System-Init Call Ordering

The runtime-lite contract SHALL document that
`alloy_system_init_fpu()` MUST be called before any C++ static
initializer with floating-point arithmetic, and
`alloy_nvic_apply_priorities()` MUST be called before any IRQ
is enabled.  The umbrella `alloy_system_init()` SHALL satisfy
this ordering when called once at the top of `Reset_Handler`
before C++ static initializers and before peripheral
initialization.

#### Scenario: Documented umbrella call satisfies ordering

- **WHEN** a consumer calls `alloy_system_init()` as the first
  C-level call in `Reset_Handler` on a Cortex-M4F device
- **THEN** the FPU is enabled before any C++ static
  initializer runs
- **AND** the MPU and NVIC priorities are configured before
  any peripheral interrupt is unmasked
