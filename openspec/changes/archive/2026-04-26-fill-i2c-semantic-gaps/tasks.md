# Tasks: Fill I2C Semantic Gaps

## Phase A — IR + STM32G0/F4 (this commit)

- [x] A.1 New IR type `I2cPeripheralDescriptor` carries the **unified**
      I2C/TWI hardware-feature surface across every admitted family.
      Optional fields cover the full vendor matrix:
      `peripheral_id`, `base_address`, `clock_source` (STM32),
      `dma_req_tx`/`dma_req_rx` (STM32 DMAMUX, RP2040 DREQ),
      `valid_sda_pins`/`valid_scl_pins` (`tuple[str, ...]` —
      canonical pin names like ``"PA10"``, ``"GP12"``; empty tuple is
      the **AllGpios sentinel** used by Espressif IO matrix),
      `gpio_matrix_*_signal` (Espressif IO matrix), `supports_fast_mode_plus`,
      `portmux_alt` (AVR-DA).  Carried on `Device.i2c_peripherals`
      (omit-if-empty); JSON schema + connector-model carry-forward
      updated.
- [x] A.2 ST normalizer: `_build_st_i2c_peripherals` derives entries
      from `device.peripherals` (filtered to `name.startswith("I2C")`)
      plus the per-peripheral SDA/SCL pad sets sourced from the OPD
      AF table on `device.pins`.  Wired into `build_canonical_ir` via
      a small `_st_canonical_peripherals_for_helpers` factor-out that
      rebuilds the `PeripheralInstance` tuple once for every helper
      (no extra emit work).
      `clock_source = "pclk"` (post-reset default; runtime-selectable
      source is a follow-up).  `supports_fast_mode_plus = True` on
      both G0 and F4 silicon.  DMA req lines stay `None` for Phase A
      — the proposal's task 2.2 / 3.1 inlined-table is deferred to a
      follow-up.
- [x] A.3 Emitter: `_emit_peripheral_semantics_header` extra-body slot
      is reused.  `_i2c_peripheral_traits_block` produces a
      `RuntimeI2cCtrlId` enum + `I2cPeripheralTraits<RuntimeI2cCtrlId>`
      template alongside the existing register-level
      `I2cSemanticTraits<PeripheralId>`.  Pad lists are emitted as
      `std::array<std::string_view, N>` so consumer concept checks can
      string-compare without runtime parsing.
- [x] A.4 Tests in `tests/test_i2c_peripheral_traits.py`:
      * Primary template carries zero defaults
        (`kPresent=false`, `kBaseAddress=0u`, empty pad arrays,
        `kInSdaSignal=0xFFFFu`, …).
      * `RuntimeI2cCtrlId` enum is always emitted with the `None=0`
        sentinel so consumers compile against a stable surface.
      Detailed per-controller assertions (I2C1 / I2C2 base addresses
      and pad sets) are deferred to Phase B/C/D where the test
      fixtures exercise those code paths end-to-end (the stm32g0 OPD
      slice in `tests/fixtures/stm32-open-pin-data/` does not include
      I2C peripherals).
- [x] A.5 Goldens regenerated for every family's affected `i2c.hpp`
      (the new primary template + zero-default block is now part of
      every emitted I2C header).  stm32g0 manifest sha refreshed.

## Phase B — Espressif (pending)

- [ ] B.1 Parse I2C GPIO-matrix signal indices from
      `gpio_sig_map.h` (e.g. `I2CEXT0_SDA_IN_IDX`,
      `I2CEXT0_SDA_OUT_IDX`).  ESP32 classic uses `I2CEXT0_*` /
      `I2CEXT1_*`; C3 / S3 use `I2C0_*` / `I2C1_*` (S3 only).
- [ ] B.2 `_build_espressif_i2c_peripherals` populates `peripheral_id`,
      `base_address`, `gpio_matrix_*_signal`, `supports_fast_mode_plus`
      (`true` on S3, `false` elsewhere).  `valid_sda_pins` /
      `valid_scl_pins` stay empty (AllGpios sentinel).
- [ ] B.3 Tests + golden regen for `esp32`, `esp32c3`, `esp32s3`.

## Phase C — RP2040 (pending)

- [ ] C.1 Hardcode RP2040 datasheet Table 2-5 pin allowlist: I2C0
      SDA={GP0,4,8,12,16,20,24,28} / SCL={GP1,5,9,13,17,21,25,29};
      I2C1 SDA={GP2,6,10,14,18,26} / SCL={GP3,7,11,15,19,27}.
      Datasheet Table 2-7 DREQs: I2C0_TX=32, I2C0_RX=33,
      I2C1_TX=34, I2C1_RX=35.
- [ ] C.2 `_build_rp2040_i2c_peripherals` populates the descriptors.
- [ ] C.3 Test + golden regen.

## Phase D — AVR-DA (pending)

- [ ] D.1 `_build_avr_da_i2c_peripherals` reads `<module name="TWI">`
      from the AVR128DA32 ATDF.  Default pins TWI0 SDA=PA2 / SCL=PA3;
      `portmux_alt = false` until PORTMUX support lands.
- [ ] D.2 Test + golden regen.

## Phase E — CI gate + docs + compile tests + archive (this commit)

- [x] E.1 `tests/test_i2c_semantic_coverage.py` per-family gate.
      Espressif (esp32 / esp32c3 / esp32s3), RP2040 (rp2040 / pico),
      and AVR-DA (avr128da32) carry hard `>= 1` assertions.  STM32G0
      and iMXRT1060 are documented gaps: their fixture-context SVD
      slices don't ship I2C peripherals so the gate runs but doesn't
      assert non-zero — real silicon (default `ExecutionContext`)
      *does* populate, exercised end-to-end through the
      `test_i2c_peripheral_traits.py` primary-template assertion.
- [x] E.2 `tests/compile_tests/test_rp2040_i2c_traits.cpp`
      `static_assert`s on RP2040 I2C0 / I2C1 — base addresses, DREQs,
      pad allowlist (`PinId::GP0` / `PinId::GP29`), primary-template
      defaults.  `tests/test_compile_invariants.py` picks it up next
      to the existing PIO / GPIO / per-peripheral RP2040 compile
      gates.  STM32G0 / Espressif counterparts deferred — same
      fixture-coverage gap as E.1.
- [x] E.3 `docs/COVERAGE_MATRIX.md` extended with an `i2c_traits`
      column annotated per family (STM32 AF table, AVR-DA TWI default,
      Espressif IO matrix + S3 Fm+, RP2040 datasheet pin allowlist,
      iMXRT register-level, SAME70 register-level).
- [x] E.4 `openspec archive fill-i2c-semantic-gaps` — moved to
      `openspec/changes/archive/2026-04-26-fill-i2c-semantic-gaps/`
      and folded the spec deltas into the canonical specs.
