# Tasks: Extend PWM Coverage Across All MCUs

Phased rollout — each phase is independently reviewable, regressions
the per-family coverage gate one MCU at a time. Phase F flips the gate
to mandatory across every admitted family.

## Phase A — IR scaffold + STM32 (TIM advanced + general timers)

- [ ] A.1 New IR types `StmTimerPwmDescriptor` (with `kind`,
      `channel_count`, `counter_bits`, per-channel pin tuples,
      `dma_req_lines`, `supports_*` flags, `max_clock_hz`) in
      `src/alloy_codegen/ir/model.py`. Carried on
      `Device.stm_timer_pwm_peripherals` (omit-if-empty).
- [ ] A.2 JSON schema (`schemas/canonical-device-ir-v1.schema.json`)
      and `connector_model.py` carry-forward.
- [ ] A.3 `_build_st_timer_pwm_peripherals` in
      `stages/normalize.py` filters `device.peripherals` for
      `name in ("TIM1".."TIM17")` and pulls per-channel pin sets from
      `device.pins[*].signals` (signal names `CH1`..`CH4` and `CH1N`
      ..`CH3N`).  Wired into the ST builder.
- [ ] A.4 Emitter: `_stm_timer_pwm_traits_block` produces
      `RuntimeStmTimerPwmId` enum + `StmTimerPwmTraits` template
      with zero defaults plus populated specializations for STM32G0
      and STM32F4.
- [ ] A.5 Tests: `tests/test_pwm_peripheral_traits.py` (primary
      template defaults + TIM1 specialization on G0 / F4 with a
      non-empty CH1 pad set).

## Phase B — Espressif (LEDC extension + new MCPWM)

- [ ] B.1 Extend `LedcDescriptor` with `timer_count`,
      `low_speed_channel_count`, `high_speed_channel_count`,
      `max_resolution_bits`. Preserve existing field names so the
      Espressif normalize path stays byte-stable beyond the new
      fields.
- [ ] B.2 New `McpwmDescriptor`. ESP32 classic and S3 each ship two
      MCPWM peripherals; C3 ships none. Wire into
      `_build_esp32_device_ir`. Signal indices come from
      `gpio_sig_map.h` — extend `esp_idf.py` to pluck
      `MCPWM*_OUT_*_IDX` and `MCPWM*_CAP*_IN_IDX`.
- [ ] B.3 Emitter: extend the existing LEDC trait emission and add
      a new `_mcpwm_traits_block`. Both use the typed
      `RuntimeLedcId` / `RuntimeMcpwmId` enums so the boundary test's
      `class Pwm` substring check stays clear.
- [ ] B.4 Tests: LEDC field expansion (kMaxResolutionBits=20 on
      classic, 14 on C3, 20 on S3); MCPWM signal-index assertions
      on classic + S3, **N/A** on C3 (verified via the descriptor
      tuple staying empty).

## Phase C — NXP iMXRT FlexPWM

- [ ] C.1 New `FlexPwmDescriptor` with `submodule_count = 4`,
      `paired_channels = True`, `valid_a_pins_per_submodule`,
      `valid_b_pins_per_submodule` from the iMXRT IOMUX table,
      `supports_*` flags, `dma_req_lines`.
- [ ] C.2 Wire `_build_nxp_flex_pwm_peripherals` from the iMXRT
      normalize path; the IOMUX entries already flow through pins,
      so this mirrors the STM32 helper's filter pattern.
- [ ] C.3 Emitter: `_flex_pwm_traits_block` (4 specializations per
      device — PWM1..PWM4).
- [ ] C.4 Tests: PWM1 SubModule0 A/B pin sets on mimxrt1062.

## Phase D — AVR-DA TCA + SAME70 PWM/TC

- [ ] D.1 New `AvrDaTcaPwmDescriptor` with `default_channel_pins`,
      `split_mode_channels`, `single_mode_channels`, `counter_bits`.
      Wire into `_build_avr_da_device_ir`. Default placement:
      `("PA0".."PA5")`; PORTMUX alternate placement deferred to a
      follow-up.
- [ ] D.2 New `Same70PwmDescriptor` with `kind` (`"pwm"` /
      `"tc"`), `channel_count`, `valid_pins_per_channel`,
      `supports_*` flags. Wire into `_build_microchip_device_ir`.
- [ ] D.3 Emitter: `_avr_da_tca_pwm_traits_block` and
      `_same70_pwm_traits_block`.
- [ ] D.4 Tests: TCA0 default placement; PWM0 channel set on SAME70.

## Phase E — Compile tests + per-family coverage gate

- [ ] E.1 New compile-time `static_assert` smokes:
      * `tests/compile_tests/test_stm32g0_pwm_traits.cpp` — TIM1
        CH1 pin set + complementary support.
      * `tests/compile_tests/test_imxrt1060_pwm_traits.cpp` — PWM1
        SubModule0 A/B pad sets + supports_complementary.
      * `tests/compile_tests/test_esp32_pwm_traits.cpp` — LEDC
        max-resolution + MCPWM0 capture-signal index.
      * `tests/compile_tests/test_avr_da_pwm_traits.cpp` — TCA0
        default channel pin set.
- [ ] E.2 New `tests/test_pwm_semantic_coverage.py` with one test
      per family asserting `>= 1 kPresent = true` populated PWM
      specialization on the emitted `pwm.hpp`.

## Phase F — Coverage matrix flip + archive

- [ ] F.1 Update `docs/COVERAGE_MATRIX.md` with a `pwm_traits` column
      annotated per family (TIM advanced/general, FlexPWM, MCPWM +
      LEDC, RP2040 slice, AVR-DA TCA, SAME70 PWM/TC). All families
      flip to ✓ at this phase.
- [ ] F.2 `openspec archive extend-pwm-coverage-all-mcus`.
