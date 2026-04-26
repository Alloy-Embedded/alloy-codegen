# Tasks — add-adc-tier-2-3-4-data

## Phase 1: Patch parser plumbing

- [x] 1.1 Add 7 new patch dataclasses + parsers to `patches.py`:
      `AdcInternalChannelPatch`, `AdcCalibrationDataPointPatch`,
      `AdcCalibrationContextPatch`, `AdcResolutionOptionPatch`,
      `AdcSampleTimeOptionPatch`, `AdcOversamplingOptionPatch`,
      `AdcExternalTriggerPatch`
- [x] 1.2 Extend `DevicePatch` with optional tuples:
      `adc_internal_channels`, `adc_calibration_data_points`,
      `adc_calibration_context`, `adc_resolution_options`,
      `adc_sample_time_options`, `adc_oversampling_options`,
      `adc_external_triggers`, `adc_max_clock_hz`
- [x] 1.3 Extend `CanonicalDeviceIR` with the same optional tuples
- [x] 1.4 Forward the patch fields through every device IR builder
      (ST, Microchip, AVR-DA, ESP32, RP2040, iMXRT1060)

## Phase 2: DMA bindings helper

- [x] 2.1 New helper `_dma_bindings_for_peripheral(device, peripheral_name)`
      in `runtime_driver_semantics.py`: walks `device.dma_requests` filtered
      by `peripheral == peripheral_name`, builds `AdcDmaBindingRow` rows
      with controller_peripheral / controller_id / binding_id derived from
      the existing DMA tables, plus data_register from the ADC trait's
      kDataRegister
- [x] 2.2 Inference helper for `transfer_width_bits` (12 → 16, 16 → 16,
      others → 32)
- [x] 2.3 Unit tests covering: peripheral with no DMA route → empty tuple;
      peripheral with one DMA route → single binding; peripheral with
      multiple DMA routes (e.g., STM32 ADC1 RX/TX or NXP ADC1+ADC2) →
      multiple bindings

## Phase 3: STM32 G0/F4 population

- [x] 3.1 Update `_st_adc_row` to read IR fields and populate the row's
      Tier 2/3/4 tuples + `kCalibrationContext`
- [x] 3.2 Add config blocks to `patches/st/stm32g0/devices/*.json`:
      - `adc_internal_channels`: TempSensor ch12, VrefInt ch13, VBat ch14
      - `adc_calibration_data_points`: VREFINT_CAL @ 0x1FFF75AA (16-bit,
        semantic_constant=3000), TS_CAL_30 @ 0x1FFF75A8 (semantic=30),
        TS_CAL_130 @ 0x1FFF75CA (semantic=130)
      - `adc_calibration_context`: cal_temp_low=30, cal_temp_high=130,
        cal_voltage_mv=3000, vrefint_nominal_mv=1212
      - `adc_resolution_options`: 12-bit value=0, 10-bit=1, 8-bit=2, 6-bit=3
      - `adc_sample_time_options`: 1.5, 3.5, 7.5, 12.5, 19.5, 39.5, 79.5,
        160.5 cycles → field values 0..7
      - `adc_oversampling_options`: 2x..256x via OVSR field
      - `adc_external_triggers`: TIM1_TRGO=0, TIM1_CC4=1, TIM2_TRGO=2,
        TIM3_TRGO=3, TIM6_TRGO=5, TIM15_TRGO=6, EXTI11=7
      - `adc_max_clock_hz`: 35000000
- [x] 3.3 Same blocks for `patches/st/stm32f4/devices/*.json` (F4 has temp
      ch16, VrefInt ch17, VBat ch18; cal context 30°C @ 3.3V; vrefint
      nominal 1210mV; resolution 6/8/10/12; no HW oversampling; trigger
      sources from F4 RM table 91; max clock 36 MHz)

## Phase 4: SAME70 + iMXRT1060 population

- [ ] 4.1 Update `_microchip_afec_row` to consume IR fields
- [ ] 4.2 Add `adc_internal_channels` to SAME70 device patches (TempSensor
      AFEC channel 11)
- [ ] 4.3 SAME70 has no factory cal — `adc_calibration_context.valid=false`,
      `kCalibrationDataPointCount=0`
- [ ] 4.4 SAME70 resolution options: 10/12/14/16 bit (16 via averaging)
- [ ] 4.5 SAME70 trigger sources from RM (TC0_TIOA0..TC2_TIOA2, PWM0/1)
- [ ] 4.6 Update `_nxp_adc_row` to consume IR fields
- [ ] 4.7 iMXRT1060 ADC: no factory cal (runtime self-cal),
      `adc_resolution_options` 8/10/12-bit, sample time options from
      ADC_CFG.ADSTS, trigger sources via XBAR_IN0..3

## Phase 5: AVR-DA population

- [x] 5.1 Update `_microchip_avr_adc_row` to consume IR fields
- [x] 5.2 Add `adc_internal_channels` to avr128da32.json:
      TempSensor MUXPOS 0x42 (66), AC0_OUT 0x43, DAC0 0x48, GND 0x40,
      VDDIO_DIV10 0x41
- [x] 5.3 Add `adc_calibration_data_points`: SIGROW.SREF @ 0x112E (16-bit,
      semantic=1024 -> 1024 == 1.024V), TEMPSENSE0 @ 0x1118 (offset),
      TEMPSENSE1 @ 0x111A (slope)
- [x] 5.4 `adc_calibration_context`: cal_voltage_mv=1024, vrefint_nominal_mv=
      1024 (AVR-Dx uses internal 1.024V/2.048V/2.5V/4.096V refs);
      cal_temp_low/high derived from SIGROW formula (datasheet §30.3.1.4)
- [x] 5.5 `adc_resolution_options`: 12-bit field=0, 10-bit field=1,
      8-bit field=2 (RESSEL field is 1 bit so admit only 12/10)
- [x] 5.6 `adc_oversampling_options`: 2x SAMPNUM=1, 4x=2, 8x=3, 16x=4,
      32x=5, 64x=6, 128x=7 (SAMPNUM is 4-bit; 0=no accum)
- [x] 5.7 No DMA, no external trigger in this admission

## Phase 6: ESP32 family population

- [ ] 6.1 Update 3 ESP builders (`_espressif_saradc_row`,
      `_espressif_esp32_sens_row`) to consume IR fields
- [ ] 6.2 ESP32 classic device.json: `adc_internal_channels` (HALL sensor
      via SENS, TempSensor not on classic), no calibration context
- [ ] 6.3 ESP32-C3 device.json: TempSensor channel 5 (RTC peripheral; mark
      as opamp_output / dac_output kind not strictly applicable — leave
      empty for now), no calibration context
- [ ] 6.4 ESP32-S3 device.json: TempSensor at channel index 14 internal,
      no calibration context
- [ ] 6.5 Update `__readme_caveat` for esp32, esp32c3, esp32s3 to note
      that calibration is delegated to esp-idf runtime
- [ ] 6.6 ESP32-S3 should populate DMA bindings via the existing GDMA
      → APB_SARADC route in family.json `dma_requests`

## Phase 7: RP2040 population

- [x] 7.1 Update `_raspberrypi_adc_row` to consume IR fields
- [x] 7.2 RP2040 device patches: `adc_internal_channels` (temperature_sensor
      at channel 4); no factory cal; resolution 12-bit only field=0;
      no oversampling; no external trigger; max_clock 48000000
- [x] 7.3 RP2040 DMA binding: derive from existing dma_requests entry
      (DREQ_ADC=36, controller=DMA, peripheral=ADC, signal=DATA)

## Phase 8: Tests + goldens

- [x] 8.1 Cross-family regression test asserting populated Tier 2/3/4 fields
      per family (count > 0 where applicable, valid context, etc.)
- [ ] 8.2 Internal channels regression — STM32 G0 has temp@12, AVR-DA has
      temp@66, RP2040 has temp@4
- [ ] 8.3 Calibration context regression — STM32 G0 cal_temp_low=30
      cal_temp_high=130 cal_voltage_mv=3000; AVR-DA SIGROW values; ESP32
      family carries valid=false
- [ ] 8.4 Resolution / sample time / oversampling regression — at least
      one positive case per vendor
- [ ] 8.5 DMA bindings regression — STM32G0 ADC1 binds DMA1 channel via
      DMAMUX; RP2040 ADC binds DMA via DREQ_ADC; ESP32-S3 binds GDMA;
      AVR-DA + ESP32 classic + ESP32-C3 carry empty bindings
- [ ] 8.6 External triggers regression — STM32G0 has TIM1_TRGO with
      EXTSEL=0; AVR-DA + ESP32 carry empty
- [ ] 8.7 Regenerate every adc.hpp golden across the 9 admitted families

## Phase 9: Spec delta + final checks

- [x] 9.1 Author `specs/artifact-contract/spec.md` delta with ADDED
      requirement "ADC trait Tier 2/3/4 fields are populated per device
      patch declarations" + scenarios for STM32 cal context, AVR-DA
      SIGROW, RP2040 temp sensor, ESP32 cal-deferred, DMA bindings
      per-vendor, external triggers per-vendor
- [x] 9.2 Run `openspec validate add-adc-tier-2-3-4-data --strict`; resolve
      findings
- [ ] 9.3 Update alloy-codegen `README.md` to mention that ADC traits now
      carry full configuration semantics including cal context, internal
      channels, DMA bindings, and external trigger sources
