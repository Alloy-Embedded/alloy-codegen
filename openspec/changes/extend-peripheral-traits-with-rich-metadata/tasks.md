# Tasks — Extend Peripheral Traits with Rich Metadata

## 1. IR validation

- [ ] 1.1 Tighten the JSON schema for
      `peripherals[].calibration: AdcCalibration` so populated
      entries MUST carry `vrefint`, `ts_cal_low`, `ts_cal_high`,
      `ts_low_temp_c`, `ts_high_temp_c`, `ts_slope_uv_per_c`.
      *(Deferred — current YAMLs ship vrefint + ts_cal_low/high
      but `ts_slope_uv_per_c` is `None` on every admitted ST
      ADC.  Tightening would block synthesis on every chip until
      the upstream YAML enrichment lands; the emitter today
      omits the slope row when None.)*
- [ ] 1.2 Tighten the schema for `timing_presets`.
      *(Deferred — no admitted YAML carries timing_presets yet,
      so there's nothing to validate.  The emitter handles them
      via the synthetic test path.)*
- [ ] 1.3 Tighten the schema for `Template.trigger_sources` etc.
      *(Deferred — current shape is `name → encoding_int`, which
      is enough for the foundational pass.  Promotion to
      register/field/encoding triples lands when consumers need
      to program the matrix from typed refs rather than raw
      indices.)*

## 2. Trait classifier

- [x] 2.1 New module
      `src/alloy_codegen/emit_v2_1/trait_classifier.py` exporting
      `classify_instance(per) -> InstanceTraitKind` and
      `classify_template(t) -> TemplateTraitKind`.
- [x] 2.2 `InstanceTraitKind ∈ {NONE, ADC, I2C}` — decision is
      template-name-first against an allow-list (covers ST ADC,
      ESP32 SARADC, SAM AFEC for ADC; ST I²C v1+v2, SAM TWIHS,
      SERCOM TWI for I²C) plus a payload-presence check so we
      don't emit empty trait blocks.
- [x] 2.3 `TemplateTraitKind ∈ {NONE, TIMER}` — set when ANY of
      `trigger_sources`, `master_outputs`, `deadtime_options`,
      `break_inputs`, `waveform_modes`, or `counter_bits_options`
      is populated.

## 3. Emitter helpers

- [x] 3.1 `peripheral_traits.py::_emit_adc_instance_traits` —
      emits a per-instance `calibration::{vrefint, ts_cal_low,
      ts_cal_high}` sub-namespace and an
      `external_triggers::{regular, injected}` map when populated.
      ROM addresses + nominal/temperature constants emitted as
      `inline constexpr`; trigger rows include source label,
      extsel, jextsel, polarity.
- [x] 3.2 `_emit_i2c_instance_traits` — emits a per-instance
      `timing_presets::kRows` table with `(speed, source_clock,
      timingr, ccr, trise)` per row.  Skipped when YAML carries
      no presets.
- [x] 3.3 `_emit_timer_template_traits` — emits per-template
      `trigger_sources`, `master_outputs`, `waveform_modes`,
      `deadtime_options`, `break_inputs`, `counter_bits_options`
      sub-namespaces, all populated entries lowered to
      `inline constexpr unsigned <name> = <encoding>` rows.
- [x] 3.4 Helpers wired into the existing
      `emit_peripheral_traits` dispatcher via `classify_instance`
      / `classify_template`.  Skipped (return empty) when the
      classifier says NONE so the file stays small for chips
      without rich metadata.

## 4. Runtime-lite C++ surface

- [ ] 4.1 Add typed struct definitions for `CalibrationConstants`
      etc. to a shared `peripheral_traits_types.h`.
      *(Deferred — current emission uses inline `constexpr`
      blocks consistent with the existing peripheral_traits.h
      idiom, so consumers can read the constants without
      additional headers.)*
- [ ] 4.2 Each struct carries only typed integers/enums/refs
      (zero-string rule).
      *(Partially honoured — integer ROM addresses, sizes, and
      encodings are typed; trigger source labels and I²C speed
      labels remain `const char *` until the IR surfaces them
      as typed enums.)*

## 5. Tests

- [x] 5.1 Per-trait-class unit tests in
      `tests/test_peripheral_traits_rich.py` — 10 tests covering
      classifier dispatch (positive + negative paths), ADC
      calibration block shape, ADC external-trigger row layout,
      I²C preset emission via synthetic IR, timer matrix
      sub-namespaces, and skip-when-empty behaviour.
- [x] 5.2 Synthetic `Template` + `PeripheralInstance` exercise
      every emit path independently of the live YAML corpus
      (so the contract is testable even before alloy-devices-yml
      enrichment lands).
- [ ] 5.3 Regenerate `peripheral_traits.h` golden files for
      every admitted device.  Verify byte-stable.
- [ ] 5.4 Compile-test the regenerated headers with
      `arm-none-eabi-g++ -std=c++23 -fsyntax-only` against a
      stub HAL header.
- [ ] 5.5 Negative test: an ADC instance with partial
      `calibration` (missing `ts_slope_uv_per_c`) refuses to
      load with a clear `ConfigError`.
      *(Currently None is allowed and the slope row is omitted;
      strict refusal lands with task 1.1.)*

## 6. Documentation

- [ ] 6.1 Update `peripheral_traits` design notes describing the
      new specialisation classes.
- [ ] 6.2 Update alloy HAL's `extend-adc-coverage` and
      `extend-i2c-coverage` proposals to reference the typed
      surfaces this proposal publishes (cross-link only).
