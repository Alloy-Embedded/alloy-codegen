# Tasks — add-i2c-tier-2-3-4-data

## Phase 1: Investigate + fix STM32G0 emission bug

- [x] 1.1 Reproduced: `kI2cSemanticPeripherals = {}` on G0 because
      I2C peripherals weren't admitted in the canonical IR.  Two
      root causes: (a) device patches lacked I2C in `peripherals`
      list + at least one register stub; (b) `INSTANCE_PATTERN`
      didn't extract the digit suffix from "I2C1" (returned ip_name
      "i2c1" instead of "i2c"), so `canonical_peripheral_class`
      mismatched.
- [x] 1.2 Fixed both root causes:
      - Tightened `INSTANCE_PATTERN` from `^[A-Z]+?\d+$` to
        `^[A-Z][A-Z0-9]*?\d+$` so embedded digits (I2C1, LPI2C1,
        FDCAN1) correctly split into ip + instance.
      - Extended `_build_i2c_rows` to surface I2C peripherals
        admitted via the device patch even without pin-routing
        candidates (mirrors the UART-builder pattern).
      - Added I2C1/I2C2 to STM32G0 device patches (g071rb,
        g030f6, g0b1re) with stub `CR1` registers.
- [x] 1.3 Regression test
      `test_stm32g071rb_i2c_traits_emit_specialization_and_tier234`
      asserts both I2C1 and I2C2 specializations exist.

## Phase 2: Patch parser plumbing

- [x] 2.1 Added `I2cSpeedOptionPatch`, `I2cTimingPresetPatch`,
      `I2cModeFlagsPatch` dataclasses + parsers.  Folded
      addressing modes into the mode-flags block instead of a
      separate `I2cAddressingOptionPatch` (smaller surface, same
      info).
- [x] 2.2 Extended `DevicePatch` with `i2c_speed_options`,
      `i2c_timing_presets`, `i2c_mode_flags` tuples.  Skipped
      `i2c_max_clock_hz` scalar — the existing
      `peripheral_max_clock_hz` (added by `add-kernel-clock-traits`)
      already covers I2C ceilings.
- [x] 2.3 Extended `CanonicalDeviceIR` and forwarders
      (`normalize.py`, `connector_model.py`).
- [x] 2.4 Round-trip via the regenerated canonical fixtures.

## Phase 3: Trait surface + safe defaults

- [x] 3.1 Extended `I2cSemanticRow` with `speed_options`,
      `timing_presets`, `mode_flags` fields + `I2cSpeedOption`,
      `I2cTimingPreset`, `I2cModeFlags` value dataclasses.  Added
      `_i2c_extension_for_peripheral` helper (mirrors the
      UART/SPI Tier-2/3/4 helpers) and threaded it through all 5
      `I2cSemanticRow` constructors.
- [x] 3.2 New `_i2c_tier234_lines` renderer; `_i2c_specialization_builder`
      emits the 9 new constexprs in stub + non-stub branches.
- [x] 3.3 `default_lines` in `emit_runtime_driver_i2c_semantics_header`
      ships safe-falsy values.  `I2cTimingPreset` C++ struct lifted
      into `common.hpp`.

## Phase 4: Per-family population

- [x] 4.1 STM32G0 (g071rb / g030f6 / g0b1re) — speeds 100k/400k/1M,
      TIMINGR presets for PCLK 64 MHz, full mode flags.
- [x] 4.2 STM32F4 (f401re / f405rg) — speeds 100k/400k, presets
      for PCLK 42 MHz, full mode flags.
- [x] 4.3 SAME70 — `populate_i2c_tier234.py` carries the schema
      (`same70_i2c_blocks`); SAME70 device patches don't list
      TWIHS so the helper isn't called yet.  Surfaces empty
      defaults until SAME70 admits TWIHS in its device patches.
- [x] 4.4 iMXRT1060 — same situation as SAME70.  Schema in script.
- [x] 4.5 AVR-DA — TWI0 speeds 100k/400k populated on `avr128da32`.
- [x] 4.6 ESP32 family — schema in script; ESP32 device patches
      don't admit I2C peripherals yet (gap inherited from SVD
      fixture).
- [x] 4.7 RP2040 — schema in script; same situation.

## Phase 5: Tests + goldens

- [x] 5.1 `test_stm32g071rb_i2c_traits_emit_specialization_and_tier234`
      validates the full pipeline end-to-end (specialization + 3
      speeds + TIMINGR preset + mode flags).
- [x] 5.2 Regenerated normalize fixtures + emit goldens for every
      affected family (`scripts/regen_canonical_fixtures.py` +
      `scripts/update_goldens.py`).

## Phase 6: Spec + final checks

- [x] 6.1 Spec delta already landed in
      `specs/artifact-contract/spec.md` during proposal authoring.
- [x] 6.2 `openspec validate add-i2c-tier-2-3-4-data --strict`
      passes.
- [x] 6.3 Full `pytest -q` passes (384 passed, 1 skipped).
      `ruff check` + format clean.
- [x] 6.4 Archive entry notes that this unblocks the alloy
      `add-async-i2c-hal` driver — alloy can now ship I2C
      compile-time speed selection (`I2cMaster<I2C1>::set_speed<400_kHz>()`)
      using the trait surface without further codegen iteration.
