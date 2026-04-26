# Add PWM Tier 2/3/4 Data

## Why

`PwmSemanticTraits` ships counter bits + channel count + a few
capability flags today, but none of the silicon facts an alloy PWM
driver needs to validate compile-time configurations:

- **Prescaler / period range** — derived from
  `add-timer-tier-2-3-4-data` but needs to be projected onto the PWM
  surface
- **Deadtime configuration** — STM32 advanced timers have a 4-bit
  prescaler + 8-bit count; SAME70 PWM has independent DT registers
- **Break inputs** — BKIN, BKIN2 (STM32), FAULT0..3 (SAM)
- **Output alignment modes** — edge / center-up / center-down /
  center-up-down
- **Output polarity matrix** — invert flags per channel

modm exposes these via
`PwmFrequency<hz>`, `Deadtime<ns>`, and a `BreakInput::*` enum.

This change is the natural follow-up to `add-timer-tier-2-3-4-data`
(Stage 2, item 6).

## What Changes

### IR plumbing

- `PwmDeadtimeOptionPatch` — `{peripheral, prescaler_field_value,
  count_max}` describing DTPSC + DTG combinations
- `PwmAlignmentOptionPatch` — `{peripheral, alignment, field_value}`
- `PwmBreakInputPatch` — `{peripheral, input_id, polarity_field, …}`
- `PwmModeFlagsPatch` — `supports_deadtime`, `supports_break_input`,
  `supports_complementary_outputs`, `supports_asymmetric_pwm`,
  `supports_combined_pwm`

### Trait surface

`PwmSemanticTraits` specializations gain:

- `kMaxPrescaler`, `kMaxPeriod`
- `kDeadtimeOptions` — array of `{prescaler, count_bits, max_ns}`
- `kSupportedAlignments` — array of `Alignment` enum values
- `kBreakInputs` — array of `BreakInputDescriptor`
- Capability bools as listed above

### Per-family population

- STM32G0 TIM1 / TIM14 / TIM16 / TIM17 — TIM1 has full deadtime +
  BKIN; basic timers carry empty arrays
- STM32F4 TIM1 / TIM8 / TIM9..14 — full advanced + general
- SAME70 PWM0 / PWM1 — 4 channels each, independent deadtime
- iMXRT1060 PWM1..PWM4 — 4 submodules each
- ESP32 LEDC + MCPWM — different surface; MCPWM has full break/dt
- RP2040 PWM slices already partial; complete arrays + break

### Goldens

Regenerate every `pwm.hpp` golden across all 9 families.

## Impact

Combined with `add-timer-tier-2-3-4-data`, unblocks
`alloy/add-pwm-hal` driver development.
