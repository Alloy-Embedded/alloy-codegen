# Tasks — add-pwm-tier-2-3-4-data

## Phase 1: Patch parser plumbing

- [x] 1.1 Add patch dataclasses + parsers:
      `PwmDeadtimeOptionPatch`, `PwmAlignmentOptionPatch`,
      `PwmBreakInputPatch`, extend `PwmModeFlagsPatch`.
- [x] 1.2 Extend `DevicePatch` and `CanonicalDeviceIR`.
- [x] 1.3 Forwarders + round-trip tests.

## Phase 2: Trait surface + safe defaults

- [x] 2.1 Extend `PwmSemanticRow` with new fields.
- [x] 2.2 `_pwm_specialization_builder` emits new constexprs.
- [x] 2.3 `default_lines` ships safe-falsy values.

## Phase 3: Per-family population

- [x] 3.1 STM32G0 — TIM1 (advanced, full deadtime + BKIN),
      TIM14 / TIM16 / TIM17 (basic).
- [x] 3.2 STM32F4 — TIM1 / TIM8 (advanced), TIM9..14 (general).
- [x] 3.3 SAME70 — PWM0 / PWM1 with 4 channels each.
- [x] 3.4 iMXRT1060 — PWM1..PWM4 with 4 submodules.
- [x] 3.5 ESP32 family — LEDC + MCPWM (S3 only).
- [x] 3.6 RP2040 — complete the existing PWM slice descriptors
      (already have channel A/B pin + clock_div range) with
      alignment + break info.
- [x] 3.7 AVR-DA — TCA WGM modes.

## Phase 4: Tests + goldens

- [x] 4.1 Per-family regression tests.
- [x] 4.2 STM32G0 TIM1 PWM test:
      `kSupportsDeadtime == true`, `kBreakInputs.size() == 1`,
      `kSupportedAlignments.size() == 4`.
- [x] 4.3 Regenerate emit-fixture goldens.

## Phase 5: Spec + final checks

- [x] 5.1 Spec delta in `specs/artifact-contract/spec.md`.
- [x] 5.2 `openspec validate add-pwm-tier-2-3-4-data --strict` passes.
- [x] 5.3 Full `pytest -q` + `ruff check` clean.
- [x] 5.4 Archive entry notes that this unblocks `add-pwm-hal`
      in alloy.
