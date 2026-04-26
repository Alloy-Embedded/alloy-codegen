# Tasks — add-pwm-tier-2-3-4-data

## Phase 1: Patch parser plumbing

- [ ] 1.1 Add patch dataclasses + parsers:
      `PwmDeadtimeOptionPatch`, `PwmAlignmentOptionPatch`,
      `PwmBreakInputPatch`, extend `PwmModeFlagsPatch`.
- [ ] 1.2 Extend `DevicePatch` and `CanonicalDeviceIR`.
- [ ] 1.3 Forwarders + round-trip tests.

## Phase 2: Trait surface + safe defaults

- [ ] 2.1 Extend `PwmSemanticRow` with new fields.
- [ ] 2.2 `_pwm_specialization_builder` emits new constexprs.
- [ ] 2.3 `default_lines` ships safe-falsy values.

## Phase 3: Per-family population

- [ ] 3.1 STM32G0 — TIM1 (advanced, full deadtime + BKIN),
      TIM14 / TIM16 / TIM17 (basic).
- [ ] 3.2 STM32F4 — TIM1 / TIM8 (advanced), TIM9..14 (general).
- [ ] 3.3 SAME70 — PWM0 / PWM1 with 4 channels each.
- [ ] 3.4 iMXRT1060 — PWM1..PWM4 with 4 submodules.
- [ ] 3.5 ESP32 family — LEDC + MCPWM (S3 only).
- [ ] 3.6 RP2040 — complete the existing PWM slice descriptors
      (already have channel A/B pin + clock_div range) with
      alignment + break info.
- [ ] 3.7 AVR-DA — TCA WGM modes.

## Phase 4: Tests + goldens

- [ ] 4.1 Per-family regression tests.
- [ ] 4.2 STM32G0 TIM1 PWM test:
      `kSupportsDeadtime == true`, `kBreakInputs.size() == 1`,
      `kSupportedAlignments.size() == 4`.
- [ ] 4.3 Regenerate emit-fixture goldens.

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/artifact-contract/spec.md`.
- [ ] 5.2 `openspec validate add-pwm-tier-2-3-4-data --strict` passes.
- [ ] 5.3 Full `pytest -q` + `ruff check` clean.
- [ ] 5.4 Archive entry notes that this unblocks `add-pwm-hal`
      in alloy.
