# Add Timer Tier 2/3/4 Data

## Why

`TimerSemanticTraits` ships counter bits + channel count + boolean
capability flags today, but no timing-resolution facts.  An alloy
PWM driver or async time source needs:

- **Prescaler range** (max 16-bit on STM32 core timers, 32-bit
  CNT on TIM2/TIM5)
- **Trigger sources** — internal trigger lines (ITR0..ITR3), ETR
  pin, slave-mode controller triggers
- **Master-output trigger** (TRGO) connections
- **DMA bindings** — UP, CC1..CC4, TRIG (already covered by
  `add-peripheral-dma-cross-references`)
- **IRQ split** — UP, CC, BRK, TRG (already covered by
  `add-irq-vector-traits`)

modm exposes `Timer1::Resolution<bits>`, `OverflowFrequency<hz>`,
and a slave-mode trigger enum; alloy needs the equivalent constexpr
surface.

## What Changes

### IR plumbing

New patch dataclasses in `patches.py`:

- `TimerPrescalerOptionPatch` — `{peripheral, max_prescaler}`
- `TimerTriggerSourcePatch` — `{peripheral, source (itr0..3 / etr /
  ti1f / …), field_value}`
- `TimerMasterOutputPatch` — `{peripheral, source (reset / enable /
  update / cc1..4 / oc1..4ref), field_value}`
- `TimerModeFlagsPatch` extends existing flags with
  `supports_dma_burst`, `supports_repetition_counter`,
  `supports_xor_input`

### Trait surface

Each `TimerSemanticTraits` specialization gains:

- `kMaxPrescaler` — typically `0xFFFFu` (16-bit) or `0xFFFFFFFFu`
- `kMaxAutoReload` — same or wider
- `kTriggerSources` — `std::array<TriggerSourceOption, N>`
- `kMasterOutputModes` — `std::array<MasterOutputOption, M>`
- `kSupportsDmaBurst`, `kSupportsRepetitionCounter`,
  `kSupportsXorInput`

### Per-family population

- STM32G0/F4 — TIM1/TIM2/TIM3/TIM14/.. with full ITR/ETR matrix
- SAME70 — TC0..TC11 with TIOA / TIOB / XC0..2 trigger pins
- iMXRT1060 — GPT, PIT, QTMR
- AVR-DA — TCA, TCB, TCD with their event-system bindings
- ESP32 family — General-purpose timers + RMT + LEDC
- RP2040 — single-shot timer + PWM slices (already covered by
  `pwm.hpp`)

### Goldens

Regenerate every `timer.hpp` golden across all 9 families.

## Impact

After this lands plus PWM Tier 2/3/4, the alloy `add-async-timer-hal`
and `add-pwm-hal` drivers can be written purely in alloy.
