# Tasks — Extend Peripheral Traits with Rich Metadata

## 1. IR validation

- [ ] 1.1 Tighten the JSON schema for
      `peripherals[].calibration: AdcCalibration` so populated
      entries MUST carry `vrefint`, `ts_cal_low`, `ts_cal_high`,
      `ts_low_temp_c`, `ts_high_temp_c`, `ts_slope_uv_per_c`.
      Partial calibration carriage is ambiguous; reject at load.
- [ ] 1.2 Tighten the schema for
      `peripherals[].timing_presets: tuple[I2cTimingPreset, ...]`
      so each preset MUST carry `speed_hz`, `pclk_hz`, and the
      vendor-specific encoded register value
      (`timingr` for STM32 v2 I²C, `ccr/trise` for STM32 v1).
- [ ] 1.3 Tighten the schema for `Template.trigger_sources`,
      `Template.master_outputs`, `Template.deadtime_options`,
      `Template.break_inputs` so each entry carries its
      register/field/encoding triple, not just a label.

## 2. Trait classifier

- [ ] 2.1 New module
      `src/alloy_codegen/emit_v2_1/trait_classifier.py` exporting
      `classify_instance(per: PeripheralInstance) ->
      InstanceTraitKind` and
      `classify_template(t: Template) -> TemplateTraitKind`.
- [ ] 2.2 `InstanceTraitKind ∈ {NONE, ADC, I2C, ...}`
      (one per shape this proposal lands; future proposals add
      members).  Decision is based on
      `template.class` plus a small allow-list of `ip_version`
      patterns where the IP carries a calibration surface (ST
      ADCv1/v2/v3) or a timing-preset surface (ST I2Cv2/v3).
- [ ] 2.3 `TemplateTraitKind ∈ {NONE, TIMER}` for this
      proposal; `TIMER` is set when the template carries any
      of the matrix fields.

## 3. Emitter helpers

- [ ] 3.1 `peripheral_traits.py::_emit_adc_instance_traits(
      device, per) -> str` — emits the
      `AdcInstanceTraits<PeripheralId::Ix>` specialisation when
      `classify_instance(per) == ADC`.  Reads `per.calibration`,
      `per.external_triggers`, `per.calibration.calibration_data`.
- [ ] 3.2 `peripheral_traits.py::_emit_i2c_instance_traits(
      device, per) -> str` — emits the
      `I2cInstanceTraits<PeripheralId::Ix>::kTimingPresets`
      array.
- [ ] 3.3 `peripheral_traits.py::_emit_timer_template_traits(
      template) -> str` — emits the
      `TimerTemplateTraits<PeripheralTemplate::Tx>` specialisation
      with all populated matrix fields.
- [ ] 3.4 Wire each emit helper into the existing
      `emit_peripheral_traits(device, synthesised)` dispatcher
      via the trait classifier.  Helpers return `""` when the
      classifier says `NONE`.

## 4. Runtime-lite C++ surface

- [ ] 4.1 Add C++ struct definitions for
      `CalibrationConstants`, `CalibrationDataPoint`,
      `ExternalTrigger`, `TriggerKind`, `TriggerPolarity`,
      `I2cTimingPreset`, `TriggerSource`, `MasterOutputId`,
      `DeadtimeOption`, `BreakInput`, `CounterBitsSet`,
      `WaveformModeSet` to the runtime-lite header preamble
      (or a shared `peripheral_traits_types.h`).
- [ ] 4.2 Each struct carries only typed integers/enums/refs
      (no semantic strings) per the existing zero-string rule.

## 5. Tests

- [ ] 5.1 Per-trait-class unit tests in
      `tests/test_emit_peripheral_traits_rich.py` — synthetic
      `PeripheralInstance` with an `AdcCalibration`; assert the
      emitted block matches the expected struct literal.
- [ ] 5.2 Synthetic `Template` carrying a full timer matrix;
      assert the emitted `TimerTemplateTraits` block has
      `kTriggerSources`/`kMasterOutputs`/etc. with the right
      sizes.
- [ ] 5.3 Regenerate `peripheral_traits.h` golden files for
      every admitted device.  Verify byte-stable.
- [ ] 5.4 Compile-test the regenerated headers with
      `arm-none-eabi-g++ -std=c++23 -fsyntax-only` against a
      stub HAL header.
- [ ] 5.5 Negative test: an ADC instance with partial
      `calibration` (missing `ts_slope_uv_per_c`) refuses to
      load with a clear `ConfigError`.

## 6. Documentation

- [ ] 6.1 Update `peripheral_traits` design notes describing the
      new specialisation classes.
- [ ] 6.2 Update alloy HAL's `extend-adc-coverage` and
      `extend-i2c-coverage` proposals to reference the typed
      surfaces this proposal publishes (cross-link only; no
      change here).
