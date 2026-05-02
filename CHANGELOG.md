# Changelog

All notable changes to alloy-codegen are recorded in this file.

The format follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/);
versions follow [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.2.0] — 2026-05-02

### Generator parity with canonical-device v2.1

`alloy-codegen` produces six artifacts per device now (was four),
covering the full bring-up surface alloy HAL needs to compile and
boot a chip end-to-end without per-vendor escape hatches:

```
out/<vendor>/<family>/<chip>/
├── linker.ld
├── peripheral_traits.h
├── pin_router.h          (new in 0.2.0 — `pins.h`)
├── runtime_init.c
├── system_init.c         (new in 0.2.0)
└── vector_table.c
```

#### Added

- **`pins.h` (new artifact)** — typed `enum class pin::id` per
  device + `kRoutes` table mapping every
  `(peripheral_instance, signal, pad)` triple admitted by the IR's
  `peripherals[*].pin_options`.  Backend dispatch via a
  `PinmuxBackend` Protocol; first vendor backend covers STM32 AF
  (`alloy.pinmux.stm32-af-v1`, 514 admitted chips).  STM32
  alternate-pin annotations (`PA12 [PA10]` / `PC15-OSC32_OUT`)
  are normalised at synthesis time.
- **`system_init.c` (new artifact)** — `alloy_system_init_fpu()`
  programs `SCB->CPACR` for Cortex-M with FPU; `alloy_system_init_mpu()`
  enables the MPU with `PRIVDEFENA=1` for Cortex-M with MPU; both
  are explicit no-ops on cores without the feature.  Umbrella
  `alloy_system_init()` calls fpu → mpu → `alloy_nvic_apply_priorities()`
  in the documented order.
- **NVIC priority surface in `vector_table.c`** —
  `alloy_nvic_priority_setup[]` table built from
  `InterruptVector.priority`; `alloy_nvic_apply_priorities()` is
  always defined so consumers can call it unconditionally even when
  no vector carries an explicit priority.
- **Clock-tree dispatch in `runtime_init.c`** —
  `alloy_clock_enter_<profile_id>()` carries an executable body
  per `clock.profiles[]` entry: FLASH WS programming, PLL coefficient
  writes, PLL lock spin, SYSCLK switch + SWS readback, DSB/ISB
  barriers.  Lowering goes through a per-vendor `ClockBackend`
  Protocol; STM32 backend covers F0/F1/F3/F4/G0/G4/H7.  Profiles
  whose YAML lacks `hclk_hz` degrade to a documented stub instead
  of crashing synthesis.
- **Rich `peripheral_traits.h`** — new `calibration::{vrefint,
  ts_cal_low, ts_cal_high}` and `external_triggers::{regular,
  injected}` sub-namespaces for ADC instances; `timing_presets`
  for I²C; `trigger_sources` / `master_outputs` /
  `deadtime_options` / `break_inputs` for advanced timer
  templates.  Coverage on the admitted corpus: 514 ADCs with
  calibration, 269 with external triggers, 181 with timer matrix.
- **IR additions** — first-class `ClockProfile.hclk_hz`,
  `pclk_hz`, `pll_m/n/r/p/q/frac`, `flash_latency_hz`;
  `Identity.flash_wait_states: tuple[FlashLatencyEntry, ...]`;
  `InterruptVector.priority: int | None`; new
  `SynthesisedDevice.clock_program_steps` and `pin_routes` fields.

### Changed

- **CI (`bootstrap-family.yml`, `publish-alloy-devices.yml`)** —
  removed.  alloy-codegen no longer publishes generated artifacts
  to a separate `alloy-devices` repository.  Consumers obtain the
  CLI from PyPI and run it directly against their project's
  device data.  Pre-merge tests run via the new lean
  `.github/workflows/tests.yml`.
- **Submodule pin** — `data/devices` advanced from `bd4015e` to
  `2f10ac0`, expanding the admitted corpus to 587 chips across
  STM32 (G0/F4 plus G4/H7/F0/F1/F3 bulk-emit), SAM E70/V71/D21/
  D51/L21, RP2040, ESP32 family, Nordic nRF52, NXP iMX RT 1060,
  AVR-DA.  Pytest stays 100% green across the bumped corpus.
- **`runtime_init.c` profile fn name** —
  `alloy_clock_apply_<id>()` → `alloy_clock_enter_<id>()` to match
  the runtime-lite-contract bring-up vocabulary.

### Improved

- Test count grew from 102 → 138 (+36) across four foundational
  implementation passes; suite runs in under 9 seconds on a stock
  Apple Silicon laptop.
- 5 new OpenSpec proposals documenting the v2.1 parity surface,
  all `openspec validate --strict` clean.

## [0.1.0] — 2026-04-30

### Added

- Initial public release on PyPI.
- Canonical-device v2.1 IR + four-emitter pipeline (`linker.ld`,
  `peripheral_traits.h`, `runtime_init.c`, `vector_table.c`).
- `alloy-codegen` CLI + `alloy_codegen.generate(config, out_dir)`
  Python entrypoint.
- 102 regression tests covering the IR loader, synthesiser, and
  every emitter.
