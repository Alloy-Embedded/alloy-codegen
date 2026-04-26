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

## 3. STM32F4 (Phase B — pending)

- [ ] 3.1 Verify `stm32f401re` / `stm32f405rg` flow through
      `_build_st_gpio_pins` unchanged (same OPD source structure).
- [ ] 3.2 Regenerate or add stm32f4 emit goldens once the family is
      covered by the fixture sources.
- [ ] 3.3 Extend `tests/test_gpio_semantic_traits.py` with an STM32F4
      pin assertion (e.g. PA5 LED on Nucleo-F401RE).

## 4. Espressif (Phase C — pending)

- [ ] 4.1 Add `GpioMatrixSignalDescriptor` to the IR (signal_name,
      `in_sel_idx`, `out_sel_idx`, `out_en_sel_idx`).
- [ ] 4.2 Wire `_build_espressif_gpio_pins` for ESP32 classic / C3 / S3:
      populate `is_input_only` for GPIO34–39 on classic; `port` is the
      single GPIO peripheral on ESP32 (no STM32-style ports).
- [ ] 4.3 Emit `GpioMatrixSemanticTraits<SignalId>` alongside
      `GpioSemanticTraits` for the IO-matrix path.
- [ ] 4.4 Goldens + invariant tests for the three ESP32 variants.

## 5. AVR-DA (Phase D — pending)

- [ ] 5.1 Add `_build_avr_da_gpio_pins` reading `<module name="PORT">` and
      `<module name="PORTMUX">` from the AVR128DA32 ATDF; populate
      `port` (PORTA/B/...), `pin_index`, and AF data from PORTMUX.
- [ ] 5.2 Goldens + invariant tests for `avr128da32`.

## 6. CI gate + documentation (Phase E — pending)

- [ ] 6.1 Add a `tests/test_gpio_semantic_coverage.py` that fails CI when
      any admitted family emits zero `kPresent = true` GPIO specializations
      (initially gated to families covered by Phases A–D; ungated once all
      phases land).
- [ ] 6.2 Set up `tests/compile_tests/` infrastructure (single CMake +
      pytest entry point) and add:
      - `test_stm32g0_gpio_traits.cpp` (PA0 / PB6 `static_assert`s)
      - `test_rp2040_pio_traits.cpp` — completes the deferred 5.2 task on
        `define-pio-semantic-struct`.
- [ ] 6.3 Update `docs/COVERAGE_MATRIX.md` (or, if the file still does
      not exist, add a `gpio_traits` column to the auto-generated
      family README) once CI gate is enabled.
