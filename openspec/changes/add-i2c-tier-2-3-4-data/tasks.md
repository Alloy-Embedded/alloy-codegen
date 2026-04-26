# Tasks — add-i2c-tier-2-3-4-data

## Phase 1: Investigate + fix STM32G0 emission bug

- [ ] 1.1 Reproduce: `python -m alloy_codegen.cli emit stm32g071rb`
      and inspect `i2c.hpp` for empty
      `kI2cSemanticPeripherals`.
- [ ] 1.2 Trace `_build_i2c_rows` dispatch.  Likely the I2C schema
      matcher rejects G0's backend_schema_id, or rows are filtered
      out upstream.  Fix root cause.
- [ ] 1.3 Add a regression test asserting
      `len(I2cSemanticTraits<I2C1>) > 0` for stm32g071rb.

## Phase 2: Patch parser plumbing

- [ ] 2.1 Add patch dataclasses to `patches.py`:
      `I2cSpeedOptionPatch`, `I2cAddressingOptionPatch`,
      `I2cTimingPresetPatch`, `I2cModeFlagsPatch`.
- [ ] 2.2 Extend `DevicePatch` with new tuples + `i2c_max_clock_hz`.
- [ ] 2.3 Extend `CanonicalDeviceIR` and forwarders
      (`normalize.py`, `connector_model.py`).
- [ ] 2.4 Round-trip tests.

## Phase 3: Trait surface + safe defaults

- [ ] 3.1 Extend `I2cSemanticRow` with new fields.
- [ ] 3.2 `_i2c_specialization_builder` emits new constexprs.
- [ ] 3.3 `default_lines` ships safe-falsy values.

## Phase 4: Per-family population

- [ ] 4.1 STM32G0 (g071rb / g030f6 / g0b1re) — speeds 100k/400k/1M,
      TIMINGR presets for PCLK 64 MHz, max 64 MHz, 7-bit + 10-bit
      + SMBus = true.
- [ ] 4.2 STM32F4 (f401re / f405rg) — speeds 100k/400k, presets
      for PCLK 42 MHz; no TIMINGR (older I2C uses CCR).
- [ ] 4.3 SAME70 (n21b / q21b) — TWIHS speeds 100k/400k/1M, CWGR
      presets.
- [ ] 4.4 iMXRT1060 (mimxrt1062 / mimxrt1064) — LPI2C
      speeds 100k/400k/1M.
- [ ] 4.5 AVR-DA — TWI speeds 100k/400k.
- [ ] 4.6 ESP32 family — speeds 100k/400k/800k.
- [ ] 4.7 RP2040 — DW_I2C speeds 100k/400k/1M.

## Phase 5: Tests + goldens

- [ ] 5.1 Per-family regression tests.
- [ ] 5.2 Regenerate emit-fixture goldens.

## Phase 6: Spec + final checks

- [ ] 6.1 Spec delta in `specs/artifact-contract/spec.md`.
- [ ] 6.2 `openspec validate add-i2c-tier-2-3-4-data --strict` passes.
- [ ] 6.3 Full `pytest -q` + `ruff check` clean.
- [ ] 6.4 Archive entry notes that this unblocks
      `add-async-i2c-hal` in alloy.
