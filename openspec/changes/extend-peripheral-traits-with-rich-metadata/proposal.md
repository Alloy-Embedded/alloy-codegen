# Extend Peripheral Traits with Rich v2.1 Metadata

## Why

Three rich peripheral metadata blocks live on hundreds of admitted
chips and are **dropped at the emitter layer**:

1. **ADC factory calibration & external triggers** — populated on
   **every** STM32 ADC instance (514 chips, 88% of corpus).
   `peripherals[].calibration: AdcCalibration` carries `vrefint`,
   `ts_cal_low`, `ts_cal_high`, `ts_slope_uv_per_c`, plus a tuple
   of `CalibrationDataPoint` rows.  `peripherals[].external_triggers`
   on STM32 F4+G0 (269 ADC instances, 31% of corpus) carries the
   `ExternalTrigger{kind, extsel, polarity}` matrix the
   regular/injected channels use.  None of this reaches `peripheral_traits.h`.

2. **Timer feature matrix** — populated on every advanced/general-
   purpose timer template across STM32 F4+G0 (181 chips, 31% of
   corpus).  `Template.trigger_sources`,
   `Template.master_outputs`, `Template.deadtime_options`,
   `Template.break_inputs`, `Template.counter_bits_options`,
   `Template.waveform_modes` carry the per-template feature surface
   needed for motor-control and complementary-PWM drivers.  Only
   `Template.registers` and `Template.fields` are emitted today.

3. **I²C timing presets** — `peripherals[].timing_presets:
   tuple[I2cTimingPreset, ...]` carries pre-computed
   TIMINGR/CCR/TRISE values for standard 100 kHz / fast 400 kHz /
   fast-plus 1 MHz speeds.  Today the I²C HAL recomputes these
   from PCLK at runtime even though the codegen has them
   pre-baked.

The downstream consequence: alloy's `extend-adc-coverage`,
`extend-i2c-coverage`, and the (planned) advanced-timer/motor-control
HAL series all need this metadata in `peripheral_traits.h` to compile
without `#ifdef STM32F4` / per-vendor escape hatches.  The codegen
has the data; the emitter just doesn't surface it.

## What Changes

`emit_peripheral_traits` is extended to emit three new typed
specialisation surfaces alongside the existing
`PeripheralInstanceTraits<I>` and `PeripheralTemplateTraits<T>`:

### A. `AdcInstanceTraits<I>`

When an instance's template class is `adc` (the only template-class
branch this proposal introduces, gated through a single classifier
helper), the emitter emits an additional specialisation:

```cpp
template <> struct AdcInstanceTraits<PeripheralId::ADC1> {
    static constexpr CalibrationConstants kCalibration = {
        .vrefint_addr = 0x1FFF75AA,  // typed AddrRef in actual emission
        .ts_cal_low_addr = 0x1FFF75A8,
        .ts_cal_high_addr = 0x1FFF75CA,
        .ts_low_temp_c = 30,
        .ts_high_temp_c = 130,
        .ts_slope_uv_per_c = 2530,
    };
    static constexpr std::array<ExternalTrigger, 16> kExternalTriggers = {
        ExternalTrigger{TriggerKind::Regular, /*extsel=*/0, /*polarity=*/Rising, ...},
        ...
    };
    // ... CalibrationDataPoint rows when populated
};
```

ADC HAL no longer reads vendor data sheet constants — it reads the
ROM addresses from this trait and lets the bring-up routine load
them.

### B. `TimerTemplateTraits<T>` matrix surface

For every template populated with `trigger_sources`,
`master_outputs`, `deadtime_options`, `break_inputs`,
`counter_bits_options`, or `waveform_modes`, the emitter emits a
matrix-typed specialisation:

```cpp
template <> struct TimerTemplateTraits<PeripheralTemplate::tim_advanced> {
    static constexpr std::array<TriggerSource, 8> kTriggerSources = { ... };
    static constexpr std::array<MasterOutputId, 8> kMasterOutputs = { ... };
    static constexpr std::array<DeadtimeOption, N> kDeadtimeOptions = { ... };
    static constexpr std::array<BreakInput, M> kBreakInputs = { ... };
    static constexpr CounterBitsSet kCounterBitsOptions = ...;
    static constexpr WaveformModeSet kWaveformModes = ...;
};
```

Motor-control HAL queries these at compile time to refuse
unsupported feature requests (e.g. asking for complementary
output on a basic timer that lacks `BDTR`).

### C. `I2cInstanceTraits<I>` timing presets

For every I²C instance with a non-empty `timing_presets`, the
emitter emits a typed `kTimingPresets` array:

```cpp
template <> struct I2cInstanceTraits<PeripheralId::I2C1> {
    static constexpr std::array<I2cTimingPreset, 3> kTimingPresets = {
        I2cTimingPreset{ .speed_hz=100000, .pclk_hz=64000000, .timingr=0x10707DBC, ... },
        I2cTimingPreset{ .speed_hz=400000, .pclk_hz=64000000, .timingr=0x00602173, ... },
        I2cTimingPreset{ .speed_hz=1000000, .pclk_hz=64000000, .timingr=0x00200818, ... },
    };
};
```

I²C HAL picks a preset matching the active PCLK at open time;
no runtime division required.

The emitter remains **template-class blind in its iteration loop**:
it walks `device.peripherals[*]` and queries a single
`TraitClassifier` helper for each instance to decide which (if any)
of `AdcInstanceTraits` / `I2cInstanceTraits` to emit.  Adding a
new class (e.g. `Sai` for audio) adds one classifier branch and
one trait shape, no rewriting of the loop.

`linker_script`, `runtime_init`, `vector_table`, and the (new)
`pin_router` emitter are untouched.

## Impact

- **Affected specs**:
  - **MODIFIED** `canonical-device-ir` — promotes
    `AdcCalibration`, `ExternalTrigger`, `I2cTimingPreset`, and
    the `Template` matrix fields from "round-trip metadata" to
    "runtime-executable contract".
  - **MODIFIED** `artifact-contract` — `peripheral_traits.h`
    grows three new specialisation classes, all under the
    existing zero-string runtime contract.
  - **MODIFIED** `runtime-lite-contract` — adds typed
    `AdcInstanceTraits<I>::kCalibration`, `kExternalTriggers`,
    `TimerTemplateTraits<T>::k*`, `I2cInstanceTraits<I>::kTimingPresets`
    accessors.
- **Affected code**:
  - `src/alloy_codegen/emit_v2_1/peripheral_traits.py` — gains
    three new emit helpers + a small `TraitClassifier`
  - new `src/alloy_codegen/emit_v2_1/trait_classifier.py` —
    the only place template-class names appear; one-line
    branches per class
  - `tests/fixtures/emitted/<vendor>/<family>/<chip>/peripheral_traits.h`
    goldens regenerated (514 STM32 + 9 SAM E70 chips for I²C
    where applicable)
- **Risks / trade-offs**:
  - **Trait-class proliferation** — adding `AdcInstanceTraits`,
    `I2cInstanceTraits`, `TimerTemplateTraits` opens the door
    for `SpiInstanceTraits`, `UartInstanceTraits`, etc. ad
    nauseam.  Mitigation: each new trait shape requires its own
    OpenSpec proposal demonstrating non-trivial per-instance
    metadata (more than 2-3 fields).
  - **Calibration-row payload size** — chips like STM32H743
    can carry 30+ calibration data points.  Mitigation: emit
    `kCalibrationData` as a flat `constexpr std::array` of
    structs; consumers only pay for what they reference (LTO
    drops the rest).
  - **TimingPreset PCLK assumption** — pre-computed presets
    assume a specific PCLK; if the user picks a non-standard
    clock profile, the preset is wrong.  Mitigation: presets
    carry `pclk_hz` so the HAL can refuse silently mis-matched
    presets at compile time.
- **Out of scope**:
  - DMA `route_operations` for ADC channels — separate
    capability already covered by the existing `route_operations`
    table in `runtime_init`.
  - SAR oversampling configuration — `peripherals[].oversampling`
    is parsed but not promoted here; queue for a follow-up
    `extend-adc-oversampling` proposal once the calibration
    surface lands.
  - Per-instance NVIC priority — covered by the sibling
    `add-nvic-system-exception-init` proposal.
