# Tasks — add-timer-tier-2-3-4-data

## Phase 1: Patch parser plumbing

- [ ] 1.1 Add patch dataclasses + parsers:
      `TimerPrescalerOptionPatch`, `TimerTriggerSourcePatch`,
      `TimerMasterOutputPatch`, extend `TimerModeFlagsPatch`.
- [ ] 1.2 Extend `DevicePatch` and `CanonicalDeviceIR`.
- [ ] 1.3 Forwarders + round-trip tests.

## Phase 2: Trait surface + safe defaults

- [ ] 2.1 Extend `TimerSemanticRow` with new fields.
- [ ] 2.2 `_timer_specialization_builder` emits new constexprs.
- [ ] 2.3 `default_lines` ships safe-falsy values.

## Phase 3: Per-family population

- [ ] 3.1 STM32G0 — TIM1 / TIM3 / TIM14 / TIM16 / TIM17 with ITR
      matrix from RM0454 §15.4.3.
- [ ] 3.2 STM32F4 — TIM1..TIM14 with full ITR/ETR/TRGO matrix.
- [ ] 3.3 SAME70 — TC0..TC11 (3 channels each) with XC0..2.
- [ ] 3.4 iMXRT1060 — GPT1/2 + PIT + QTMR.
- [ ] 3.5 AVR-DA — TCA0/1, TCB0..4, TCD0 with event-system bindings.
- [ ] 3.6 ESP32 family — gp_timer_t (T0/T1) + LEDC.
- [ ] 3.7 RP2040 — already mostly handled by PWM slices.

## Phase 4: Tests + goldens

- [ ] 4.1 Per-family regression tests asserting
      `kTriggerSources.size() >= 1` on every advanced timer.
- [ ] 4.2 STM32G0 TIM1 test:
      `kSupportsRepetitionCounter == true`,
      `kMasterOutputModes.size() == 8`.
- [ ] 4.3 Regenerate emit-fixture goldens.

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/artifact-contract/spec.md`.
- [ ] 5.2 `openspec validate add-timer-tier-2-3-4-data --strict` passes.
- [ ] 5.3 Full `pytest -q` + `ruff check` clean.
- [ ] 5.4 Archive entry notes that this unblocks
      `add-async-timer-hal` and `add-pwm-hal` (after the Stage 3
      PWM change) in alloy.
