# Tasks — add-timer-tier-2-3-4-data

## Phase 1: Patch parser plumbing

- [x] 1.1 Add patch dataclasses + parsers:
      `TimerPrescalerOptionPatch`, `TimerTriggerSourcePatch`,
      `TimerMasterOutputPatch`, extend `TimerModeFlagsPatch`.
- [x] 1.2 Extend `DevicePatch` and `CanonicalDeviceIR`.
- [x] 1.3 Forwarders + round-trip tests.

## Phase 2: Trait surface + safe defaults

- [x] 2.1 Extend `TimerSemanticRow` with new fields.
- [x] 2.2 `_timer_specialization_builder` emits new constexprs.
- [x] 2.3 `default_lines` ships safe-falsy values.

## Phase 3: Per-family population

- [x] 3.1 STM32G0 — TIM1 / TIM3 / TIM14 / TIM16 / TIM17 with ITR
      matrix from RM0454 §15.4.3.
- [x] 3.2 STM32F4 — TIM1..TIM14 with full ITR/ETR/TRGO matrix.
- [x] 3.3 SAME70 — TC0..TC11 (3 channels each) with XC0..2.
- [x] 3.4 iMXRT1060 — GPT1/2 + PIT + QTMR.
- [x] 3.5 AVR-DA — TCA0/1, TCB0..4, TCD0 with event-system bindings.
- [x] 3.6 ESP32 family — gp_timer_t (T0/T1) + LEDC.
- [x] 3.7 RP2040 — already mostly handled by PWM slices.

## Phase 4: Tests + goldens

- [x] 4.1 Per-family regression tests asserting
      `kTriggerSources.size() >= 1` on every advanced timer.
- [x] 4.2 STM32G0 TIM1 test:
      `kSupportsRepetitionCounter == true`,
      `kMasterOutputModes.size() == 8`.
- [x] 4.3 Regenerate emit-fixture goldens.

## Phase 5: Spec + final checks

- [x] 5.1 Spec delta in `specs/artifact-contract/spec.md`.
- [x] 5.2 `openspec validate add-timer-tier-2-3-4-data --strict` passes.
- [x] 5.3 Full `pytest -q` + `ruff check` clean.
- [x] 5.4 Archive entry notes that this unblocks
      `add-async-timer-hal` and `add-pwm-hal` (after the Stage 3
      PWM change) in alloy.
