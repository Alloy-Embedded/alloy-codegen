# Tasks: Fill GPIO Semantic Gaps

Tasks are ordered by family. The CI gate in phase 6 becomes mandatory once
the final phase lands; earlier phases extend coverage incrementally without
breaking already-passing families.

> **Implementation note (2026-04-26):** the proposal's row "NXP LPC55S69 |
> Not yet admitted" is stale — the admitted NXP family is `imxrt1060`, which
> already emits 124 register-level GPIO trait specializations. Rather than
> reimplementing that schema, this change *extends* the existing
> `GpioSemanticTraits` struct with four new alternate-function fields
> (`kPortOffset`, `kPinIndex`, `kMaxAltFunction`, `kValidAltFunctions`) and
> populates them per family. Existing iMXRT specializations carry zero /
> empty defaults for the new fields until a follow-up wires NXP IOMUX data.
> Per-family AVR-DA support is scoped to the admitted device `avr128da32`
> (the proposal mentioned `avr128da48`, which is not in the registry).

## 1. GPIO semantic emitter infrastructure (Phase A)

- [x] 1.1 New IR types `AltFunctionDescriptor` and `GpioPinDescriptor` in
      `src/alloy_codegen/ir/model.py` capture the per-pin AF table; the
      `Device.gpio_pins` field carries them as an omit-if-empty tuple.
- [x] 1.2 JSON schema (`schemas/canonical-device-ir-v1.schema.json`)
      extended with `$defs/alt_function_descriptor`,
      `$defs/gpio_pin_descriptor`, and `gpio_pins`. Existing fixtures pass.
- [x] 1.3 `connector_model.py` carries `gpio_pins` through
      `ensure_connector_descriptors` so it survives the rebuild.
- [x] 1.4 The primary `GpioSemanticTraits<PinId>` template body in
      `runtime_driver_semantics.py` declares the four new fields with
      zero / empty defaults; existing iMXRT specializations now also emit
      zero defaults for the new fields. The `artifact-contract` /
      coverage-gate scenario lives in `validation-and-gates` (Phase E).

## 2. STM32G0 (Phase A — done in this commit)

- [x] 2.1 The proposal's `pin_data.json` overlay is **not** introduced —
      the data already exists in the upstream ST Open Pin Data XMLs that
      the `stm32_open_pin_data.py` source loader parses. Phase A derives
      `gpio_pins` directly from `device.pins[i].signals[j]` instead.
- [x] 2.2 `_build_st_gpio_pins` in `stages/normalize.py` produces a
      `GpioPinDescriptor` per pin with a non-empty AF list; signals
      without an `af_number` (analog inputs, debug-only signals) are
      skipped. Wired into the ST builder.
- [x] 2.3 The GPIO emitter emits an AF-only specialization per
      `GpioPinDescriptor` whose `PinId` is not already covered by a
      register-level row. Specializations carry `kPortOffset`,
      `kPinIndex`, `kMaxAltFunction`, and a sorted-deduplicated
      `kValidAltFunctions` array.
- [x] 2.4 Goldens regenerated:
      `tests/fixtures/emitted/stm32g0/.../driver_semantics/gpio.hpp` plus
      affected metadata / manifest JSONs (canonical-IR sha changed).
- [x] 2.5 Python invariant tests in
      `tests/test_gpio_semantic_traits.py` assert: primary template carries
      zero defaults; `PA0` records `kPortOffset = 0`; `PB6` records
      `kPortOffset = 0x400` and a non-empty `kValidAltFunctions`; the
      regenerated golden contains ≥1 `kPresent = true`.
      (C++ `static_assert` smoke deferred to Phase E with a single
      `tests/compile_tests/` infrastructure pass.)

## 3. STM32F4 (Phase B — done in this commit)

- [x] 3.1 `stm32f401re` and `stm32f405rg` flow through `_build_st_gpio_pins`
      unchanged.  Verified via the `gpio_pins` length on the canonical IR
      (50 / 51 entries) and PA5 carrying a non-empty AF list end-to-end
      with the full upstream sources.
- [x] 3.2 Canonical-IR fixtures regenerated:
      `tests/fixtures/stm32f4/{stm32f401re,stm32f405rg}.canonical.json`
      (and the stm32g0 equivalents that were missed in Phase A's regen
      pass).  No emit goldens exist for STM32F4 in this repo; nothing
      additional to refresh.
- [x] 3.3 `tests/test_gpio_semantic_traits.py` extended with two F4
      assertions: `PA9` on F401RE records `kPortOffset = 0x00000000u`,
      `kPinIndex = 9u`, and a non-empty `kValidAltFunctions`; `PA3` on
      F405RG records the same zero port offset.

## 4. Espressif (Phase C — done in this commit)

- [ ] 4.1 `GpioMatrixSignalDescriptor` (separate `GpioMatrixSemanticTraits<SignalId>`
      with explicit `in_sel_idx` / `out_sel_idx` / `out_en_sel_idx`) is
      **deferred**.  Phase C reuses `GpioPinDescriptor` and surfaces the
      IO-matrix signal index through ``alt_functions[*].af_number`` (the
      `gpio_sig_map.h` parser already records that index in
      `RawPinSignal.af_number`).  Splitting the matrix table into its own
      trait struct adds compile-time ergonomics for consumer code that
      configures `GPIO.func_in_sel_cfg` / `func_out_sel_cfg` from the
      *signal* side; that ergonomic gain is its own follow-up proposal.
- [x] 4.2 `_build_espressif_gpio_pins` wired into `_build_esp32_device_ir`
      (single ``port = "GPIO"``, ``port_offset = 0``,
      ``is_input_only = True`` for GPIO34..39 on the classic ESP32 only).
- [x] 4.3 `GpioSemanticTraits` primary template gains a `kIsInputOnly`
      bool; AF-only specializations now emit it set from
      `GpioPinDescriptor.is_input_only`.  Existing iMXRT register-level
      specializations carry the same zero default.  See note 4.1 above
      regarding `GpioMatrixSemanticTraits<SignalId>`.
- [x] 4.4 Canonical-IR fixtures regenerated for `esp32`, `esp32c3`,
      `esp32s3`, plus all other admitted families (stm32g0, stm32f4,
      same70, avr-da, rp2040, imxrt1060) since the new `kIsInputOnly`
      field is part of the canonical IR.  Tests in
      `tests/test_gpio_semantic_traits.py` add ESP32-C3 GPIO2 (signal 63
      via IO matrix) and a guard that input-only pads on classic ESP32
      carry `kIsInputOnly = true` when present.

## 5. AVR-DA (Phase D — done in this commit)

- [x] 5.1 `_build_avr_da_gpio_pins` keys off the per-port ATDF `PORTx`
      peripherals already loaded by the AVR-DA normalizer; the
      pin-letter (`pin.port = "A"`) is mapped to the peripheral name
      (`PORTA`).  ``port_offset`` is the per-port base offset relative
      to ``PORTA`` (32-byte stride on AVR-DA), and `is_input_only` is
      always `False`.  The PORTMUX channel index already flows in via
      `RawPinSignal.af_number`, so the helper reuses the same flatten
      logic as STM32 / ESP32.
- [x] 5.2 Canonical IR fixture regenerated for `avr128da32`; the new
      Phase-D test `tests/test_gpio_semantic_traits.py::test_avr128da32_gpio_pins_emit_port_topology`
      asserts `PA0` records `kPortOffset = 0`, `kPinIndex = 0`,
      `kValidAltFunctions = {{0u}}` (USART0_TX), and `PC0` records
      `kPortOffset = 0x40`.

## 6. CI gate + documentation (Phase E — done in this commit)

- [x] 6.1 `tests/test_gpio_semantic_coverage.py` runs the GPIO-semantic
      coverage gate per family using the per-family fixture-source
      contexts (hermetic — no DFP downloads required).  STM32G0,
      STM32F4, SAME70, AVR-DA, iMXRT1060, and Espressif (esp32 / c3 / s3)
      assert `>= 1` populated specialization.  The RP2040 case is
      intentionally `xfail`-marked and unblocks once
      `complete-rp2040-semantics` lands; flipping the marker is the
      regression boundary documented inside the test.
- [x] 6.2 `tests/compile_tests/` infrastructure: a lightweight
      Python harness (`tests/test_compile_invariants.py`) drives a host
      C++20 compiler over the regenerated fixture headers.  When no
      C++ toolchain is on `PATH` the tests skip gracefully.  Two source
      files exercise the new compile-time invariants:
      * `test_stm32g0_gpio_traits.cpp` — PA0 / PB6 `static_assert`s plus
        primary-template defaults and the 0x400 GPIOA→GPIOB stride;
      * `test_rp2040_pio_traits.cpp` — fulfills the previously-deferred
        `define-pio-semantic-struct` task 5.2 (PioId, base addresses,
        per-SM DREQ derivation).
- [x] 6.3 `docs/COVERAGE_MATRIX.md` now exists with a `gpio_traits`
      column showing the AF source per family (STM32 OPD, AVR PORTMUX,
      Espressif IO matrix, NXP register-level + AF zero-defaults) and
      flags RP2040 as ⏳ pending behind `complete-rp2040-semantics`.
      Live per-family coverage stays in
      `<vendor>/<family>/reports/coverage.json`.
