## Why

`add-full-adc-coverage` shipped Tier 1 (5 new vendor builders → 9/9 ADC
trait coverage) and laid the schema foundation: `AdcSemanticTraits`
declares 14 Tier 2/3/4 fields with safe defaults (empty `std::array<X, 0>`).

Today the consumer can already reference `kInternalChannels`, `kDmaBindings`,
`kCalibrationContext`, etc. — but every family returns empty values.  Apps
can't generate `Adc1::readTemperature() -> celsius` or
`AdcDma<Dma1Channel1>::startTimerTriggered<Tim1::Trgo>(buf)` because the
data isn't there.

This change populates Tier 2/3/4 incrementally: device.json patches gain
opt-in blocks (`adc_internal_channels`, `adc_calibration_context`,
`adc_resolution_options`, etc.), the existing builders consume them, and
`AdcDmaBinding[]` derives automatically from `device.dma_requests` filtered
by ADC peripheral.

## What Changes

### IR plumbing

- New patch dataclasses in `patches.py`:
  - `AdcInternalChannelPatch`
  - `AdcCalibrationDataPointPatch`
  - `AdcCalibrationContextPatch`
  - `AdcResolutionOptionPatch`
  - `AdcSampleTimeOptionPatch`
  - `AdcOversamplingOptionPatch`
  - `AdcExternalTriggerPatch`
- `DevicePatch` gains optional tuples carrying these
- `CanonicalDeviceIR` carries them through every device builder
  (`_build_st_device_ir`, `_build_microchip_device_ir`,
  `_build_avr_da_device_ir`, `_build_esp32_device_ir`,
  `_build_rp2040_device_ir`, `_build_imxrt1060_device_ir`)

### Builder integration

- Each ADC builder reads the new IR fields and populates the corresponding
  Tier 2/3/4 fields on the `AdcSemanticRow` it returns
- DMA bindings derive from `device.dma_requests` filtered by peripheral —
  no patch needed for those

### Per-family data population

| Family | What lands |
|--------|------------|
| `st/stm32g0` | TempSensor ch12, VrefInt ch13, VBat ch14, VREFINT_CAL @ 0x1FFF75AA, TS_CAL_30 / TS_CAL_130, cal context (3.0V / 30°C / 130°C), resolution 6/8/10/12-bit, sample time 8 options, oversampling 2x..256x, external triggers from G0 RM, max clock 35 MHz |
| `st/stm32f4` | TempSensor ch16/18, VrefInt ch17, cal context (3.3V / 30°C / 110°C), VREFINT_CAL/TS_CAL, resolution 6/8/10/12, sample time 8 options, no oversampling, external triggers from F4 RM, max clock 36 MHz |
| `microchip/same70` | AFEC0/1 channel mapping, no factory cal, resolution 12/14/16-bit (with averaging), trigger sources from TC/PWM |
| `nxp/imxrt1060` | ADC1/2 internal temp via via channel 26, no factory cal (runtime self-cal), resolution 8/10/12-bit, XBAR triggers |
| `microchip/avr-da` | TempSensor MUXPOS 0x42, AC0/DAC0/GND/VDDIO internal channels, SIGROW.SREF/TEMPSENSE0/TEMPSENSE1 cal data points, cal context formula, resolution 8/10/12-bit, oversampling 2x/4x/8x/16x/32x/64x/128x, no DMA, no external trigger in this admission |
| `raspberrypi/rp2040` | TempSensor at channel 4, no cal data, resolution 12-bit only, no oversampling, no external trigger, DMA via DREQ_ADC=36 |
| `espressif/esp32` `esp32c3` `esp32s3` | Internal channels (TempSensor/HALL where applicable), `kCalibrationContext.valid=false` (deferred to esp-idf), DMA bindings on S3 only, software trigger only |

### Cross-cutting

- **DMA bindings** auto-derive in every existing builder by walking
  `device.dma_requests` filtered by ADC peripheral — no per-family code
  needed beyond the helper

## Impact

- Affected specs: `artifact-contract` (delta extends the existing
  Tier-1-emitted requirement with concrete population scenarios)
- Affected code:
  - `src/alloy_codegen/patches.py` (7 new patch dataclasses + parsers)
  - `src/alloy_codegen/ir/model.py` (extend `CanonicalDeviceIR`)
  - `src/alloy_codegen/stages/normalize.py` (forward patch fields to IR
    in every device builder)
  - `src/alloy_codegen/runtime_driver_semantics.py` (5 vendor ADC builders
    consume the new IR fields; new helper `_dma_bindings_for_peripheral`)
  - 9 device.json patches expanded with the new opt-in blocks
  - Tests: per-family regression for cal context, internal channels, DMA
    bindings, trigger arrays
  - 9 goldens regenerated

## Implementation Phases

| Phase | Scope | Deliverable |
|-------|-------|-------------|
| 1 | Patch parser plumbing | 7 new dataclasses, `DevicePatch` extended, `CanonicalDeviceIR` extended, every device IR builder forwards the fields |
| 2 | DMA bindings helper | `_dma_bindings_for_peripheral` + transfer-width inference + tests |
| 3 | STM32 G0/F4 population | device patches + `_st_adc_row` consuming them |
| 4 | SAME70 + iMXRT1060 population | device patches + builders consuming |
| 5 | AVR-DA population | device patch + `_microchip_avr_adc_row` consuming |
| 6 | ESP32 family population | device patches (internal channels) + 3 ESP builders consuming; cal context stays invalid (esp-idf delegated) |
| 7 | RP2040 population | device patches + `_raspberrypi_adc_row` consuming |
| 8 | Tests + goldens (9 fixtures regenerated) |
| 9 | Spec delta + final checks |

## Non-Goals

- Differential mode pairs (vendor-specific; deferred)
- Injected vs regular conversion groups (STM32; deferred)
- ADC channel attenuation enum (ESP32-specific; separate change)
- Conversion math implementation (lives in alloy consumer)
- DMAMUX runtime reconfiguration (kDmaBindings stays static)
