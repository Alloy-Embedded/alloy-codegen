# Tasks — add-full-adc-coverage

## Phase 1: Schema extension (Tier 2 + 3 + 4 fields)

- [x] 1.1 Add new C++ enums to the generated `common.hpp` via the existing
      common-types emitter:
      - `InternalAdcChannelKind` (`temperature_sensor`, `vrefint`, `vbat`,
        `opamp_output`, `dac_output`, `none`)
      - `AdcCalibrationKind` (`vrefint_cal`, `ts_cal_low`, `ts_cal_high`,
        `sigrow_sref`, `sigrow_tempsense_low`, `sigrow_tempsense_high`,
        `efuse_init_code`, `none`)
      - `AdcExternalTriggerSource` (vendor-aware union: `software`,
        `tim1_cc1..tim1_cc4`, `tim1_trgo`, `tim2_trgo`, `tim3_trgo`,
        `tim4_trgo`, `tim6_trgo`, `tim7_trgo`, `tim15_trgo`, `tim16_trgo`,
        `exti11`, `exti15`, `gpt1_compare1`, `gpt2_compare1`, `none`)
      - `AdcDmaMode` (`one_shot`, `circular`, `none`)
- [x] 1.2 Add new POD structs to `common.hpp`:
      - `InternalAdcChannel { kind; channel_index; valid; }`
      - `CalibrationDataPoint { kind; location:RuntimeRegisterRef;
        semantic_constant:int32_t; valid; }`
      - `CalibrationContext { cal_temp_low_celsius:int16_t;
        cal_temp_high_celsius:int16_t; cal_voltage_mv:uint16_t;
        vrefint_nominal_mv:uint16_t; valid; }`
      - `AdcDmaBinding { controller:DmaControllerId; request_id:DmaRequestId;
        request_value:uint8_t; data_register:RuntimeRegisterRef;
        transfer_width_bits:uint8_t; valid; }`
      - `AdcExternalTrigger { source:AdcExternalTriggerSource;
        extsel_value:uint8_t; exten_polarity_default:uint8_t; valid; }`
- [x] 1.3 Extend `AdcSemanticTraits` template (default + populated rows)
      with the new fields, all with safe defaults:
      - Tier 2: `kInternalChannelCount`, `kInternalChannels[]`,
        `kCalibrationDataPointCount`, `kCalibrationDataPoints[]`,
        `kCalibrationContext`
      - Tier 3: `kSupportedResolutionBits[]`, `kResolutionFieldValues[]`,
        `kSampleTimeCyclesOptions[]`, `kSampleTimeFieldValues[]`,
        `kOversamplingRatios[]`, `kOversamplingFieldValues[]`,
        `kAdcMaxClockHz`
      - Tier 4: `kDmaBindingCount`, `kDmaBindings[]`,
        `kExternalTriggerCount`, `kExternalTriggers[]`,
        `kDmaModeOptions[]`, `kDmaModeFieldValues[]`
- [x] 1.4 Confirm no goldens drift on STM32 G0/F4, NXP iMXRT1060, SAME70
      from adding fields with safe defaults (rerun test suite — fixtures
      should still match because defaults serialize to empty/invalid)

## Phase 2: IR + patch parser plumbing

- [ ] 2.1 Add patch dataclasses to `patches.py`:
      `AdcInternalChannelPatch`, `AdcCalibrationDataPointPatch`,
      `AdcCalibrationContextPatch`, `AdcResolutionOptionPatch`,
      `AdcSampleTimeOptionPatch`, `AdcOversamplingOptionPatch`,
      `AdcExternalTriggerPatch`
- [ ] 2.2 Extend `DevicePatch` with optional tuples:
      `adc_internal_channels`, `adc_calibration_data_points`,
      `adc_calibration_context`, `adc_resolution_options`,
      `adc_sample_time_options`, `adc_oversampling_options`,
      `adc_external_triggers`, `adc_max_clock_hz`
- [ ] 2.3 Surface the new patch fields onto `CanonicalDeviceIR` as optional
      tuples (every device IR builder forwards them — `_build_st_device_ir`,
      `_build_microchip_device_ir`, `_build_avr_da_device_ir`,
      `_build_esp32_device_ir`, `_build_rp2040_device_ir`,
      `_build_imxrt1060_device_ir`)
- [ ] 2.4 Helper in `runtime_driver_semantics.py`:
      `_dma_bindings_for_peripheral(device, peripheral_name)` walking
      `device.dma_requests` and synthesising `AdcDmaBinding` rows with
      `data_register` resolved from the ADC peripheral's data register

## Phase 3: Existing builders ganham fields novos (ST, NXP, SAME70)

- [ ] 3.1 Update `_st_adc_row` to populate Tier 2+3+4 fields when device
      patch carries the data
- [ ] 3.2 Add the new ADC config blocks to `patches/st/stm32g0/devices/*.json`:
      - `adc_internal_channels`: TempSensor ch12, VrefInt ch13, VBat ch14
      - `adc_calibration_data_points`: VREFINT_CAL @ 0x1FFF75AA (16-bit),
        TS_CAL_30 @ 0x1FFF75A8, TS_CAL_130 @ 0x1FFF75CA
      - `adc_calibration_context`:
        `cal_temp_low=30, cal_temp_high=130, cal_voltage_mv=3000, vrefint_nominal_mv=3000`
      - `adc_resolution_options`: 6/8/10/12-bit with field values 0x3/0x2/0x1/0x0
      - `adc_sample_time_options`: 1.5/3.5/7.5/12.5/19.5/39.5/79.5/160.5
        cycles (G0) with field values 0..7
      - `adc_oversampling_options`: 2x/4x/8x/.../256x with shift options
      - `adc_external_triggers`: TIM1_TRGO/TIM1_CC4/TIM2_TRGO/TIM3_TRGO/
        TIM6_TRGO/TIM15_TRGO/EXTI11 from G0 RM
      - `adc_max_clock_hz`: 35e6 (35 MHz)
- [ ] 3.3 Same blocks for `patches/st/stm32f4/devices/*.json` (F4 has TempSensor
      ch16, VrefInt ch17, VBat ch18 on ADC1; F4 cal context: 30°C @ 3.3V,
      1.43V vrefint nominal)
- [ ] 3.4 Update `_microchip_afec_row` to populate the new fields and
      extend `patches/microchip/same70/devices/*.json` with SAME70 AFEC
      config blocks (resolution 10-bit / 12-bit / 14-bit, sample time
      via TRACKTIM/SETTLING, oversampling via OSR, internal temp sensor
      via channel 11)
- [ ] 3.5 Update `_nxp_adc_row` to populate new fields and extend
      `patches/nxp/imxrt1060/devices/*.json` (12-bit only, no factory cal,
      runtime self-cal via CFG/HC0; trigger sources via XBAR)

## Phase 4: ESP32 family ADC builders (3 schemas)

- [x] 4.1 Add 3 schema IDs to `connector_model.py` ADC dispatch
- [x] 4.2 Implement `_espressif_esp32_sens_row` for SENS peripheral
      (ESP32 classic) — ADC1 (channels 0–7 mapped GPIO32–39) and ADC2
      (channels 0–9 mapped GPIO0/2/4/12–15/25–27)
- [x] 4.3 Implement `_espressif_esp32c3_saradc_row` for ESP32-C3 APB_SARADC
      (channel count 5, GPIO0–GPIO4)
- [x] 4.4 Implement `_espressif_esp32s3_saradc_row` for ESP32-S3 APB_SARADC
      (ADC1 channels 0–9 GPIO1–10, ADC2 channels 0–9 GPIO11–20)
- [x] 4.5 Update `_build_adc_rows` dispatch in `runtime_driver_semantics.py`
- [x] 4.6 Update `family.json` for esp32, esp32c3, esp32s3 — each ADC
      peripheral declares its `ip_version` linking to the new schema id
- [ ] 4.7 ESP32 device.json updates: `adc_internal_channels` (HALL sensor
      on ESP32 classic, temp sensor on S3, etc.), no calibration data points
      (`kCalibrationContext.valid=false`), no oversampling options
      (HW oversampling absent), trigger source = software only at this stage
- [ ] 4.8 Update `__readme_caveat` for the 3 ESP families to document
      that factory calibration is delegated to esp-idf runtime

## Phase 5: AVR-DA + RP2040 builders

- [x] 5.1 Add `alloy.adc.microchip-avr-adc-v1` schema; implement
      `_microchip_avr_adc_row` for AVR-DA ADC0 (12-bit, 1 ADC, channels
      mux'd to PA0–PA7 / PD0–PD7 / internal)
- [ ] 5.2 Update `patches/microchip/avr-da/devices/avr128da32.json`:
      `adc_internal_channels` (TempSensor MUXPOS 0x42, AC0 OUT 0x43,
      DAC0 OUT 0x48, GND 0x40, VDDIO/10 0x41), `adc_calibration_data_points`
      (SIGROW.SREF @ 0x112E, TEMPSENSE0/1 @ 0x1118/0x111A),
      `adc_calibration_context` (datasheet TempSense formula),
      `adc_resolution_options` (8/10/12 bit), `adc_oversampling_options`
      (2x/4x/8x/16x/32x/64x/128x via SAMPNUM)
- [ ] 5.3 AVR-DA has no DMA for ADC — `kDmaBindingCount=0`
- [ ] 5.4 No external trigger via timer in this first cut for AVR-DA
      (event system is its own peripheral; deferred follow-on);
      `kExternalTriggerCount=0`
- [x] 5.5 Add `alloy.adc.raspberrypi-adc-v1` schema; implement
      `_raspberrypi_adc_row` for RP2040 ADC (5 channels: GP26–GP29 + temp
      sensor at channel 4)
- [ ] 5.6 Update `patches/raspberrypi/rp2040/devices/*.json`:
      `adc_internal_channels` (temperature_sensor at channel 4),
      `adc_resolution_options` (12-bit only), `adc_max_clock_hz` (48 MHz),
      no calibration data points; `adc_external_triggers` empty (RP2040
      ADC starts via CS.START_ONCE / START_MANY, no external trigger
      register)

## Phase 6: DMA bindings cross-vendor

- [ ] 6.1 Confirm `_st_adc_row` populates `kDmaBindings[]` from
      `device.dma_requests` filtered for ADC peripheral (G0 has DMA1 ch1
      via DMAMUX request 5; F4 has DMA2 stream 0/4 channel 0)
- [ ] 6.2 Confirm `_nxp_adc_row` populates DMA bindings (iMXRT1060 ADC1/2
      via DMA0 + DMAMUX1)
- [ ] 6.3 Confirm `_microchip_afec_row` populates DMA bindings (SAME70
      AFEC via XDMAC peripheral request id)
- [ ] 6.4 Confirm `_raspberrypi_adc_row` populates DMA bindings (RP2040
      via DMA peripheral with DREQ_ADC = 36)
- [ ] 6.5 Confirm ESP32 builders populate DMA bindings ONLY for S3
      (S3 APB_SARADC has GDMA channel binding) — C3 and classic SENS
      ADC1 carry empty array

## Phase 7: External triggers cross-vendor

- [ ] 7.1 Populate `adc_external_triggers` in STM32 G0/F4 device.json
      from RM trigger tables
- [ ] 7.2 Populate same in `patches/microchip/same70/devices/*.json`
      (AFEC trigger from TC, PWM, etc.)
- [ ] 7.3 Populate same in `patches/nxp/imxrt1060/devices/*.json` (XBAR
      routes)
- [ ] 7.4 Confirm AVR-DA, RP2040, ESP32 (all 3 variants) carry empty
      trigger arrays as documented in design Decision 8

## Phase 8: Validation rule

- [x] 8.1 Add `<device>-adc-semantics-populated` rule to `validation.py`:
      iterate device peripherals; for every `peripheral_class == "adc"`,
      assert there is a corresponding populated `AdcSemanticRow`
- [ ] 8.2 Wire the new rule into the right system descriptor domain (likely
      `peripheral` or a new `driver-semantics` domain) so missing
      populated traits become a `draft_system_descriptor_domains` entry
- [x] 8.3 Unit test: device with ADC peripheral but no builder fails with
      this rule_id; device without any ADC peripheral passes the rule
      trivially

## Phase 9: Tests + goldens

- [ ] 9.1 Per-vendor unit test in `tests/test_runtime_driver_semantics.py`
      asserting each new builder produces row with `kPresent=true`,
      schema id matching, channel count consistent with datasheet
- [ ] 9.2 Cross-family parametrised test asserting every admitted family
      with ADC peripheral produces emitted `adc.hpp` with at least one
      populated `AdcSemanticTraits` specialisation
- [ ] 9.3 Internal channels regression — STM32 G0 has temp@12, vrefint@13,
      vbat@14; AVR-DA has temp@0x42; RP2040 has temp@4
- [ ] 9.4 Calibration context regression — STM32 G0 vrefint_nominal_mv=3000
      cal_temp_low=30 cal_temp_high=130; AVR-DA carries SIGROW datasheet
      values; ESP32 carries `valid=false`
- [ ] 9.5 Resolution / sample time / oversampling regression — at least one
      vendor verified per field family
- [ ] 9.6 DMA bindings regression — STM32G0 ADC1 binds DMA1 channel 1;
      RP2040 ADC binds DMA channel via DREQ_ADC; ESP32-S3 binds GDMA;
      AVR-DA + ESP32 classic ADC1 + ESP32-C3 carry empty bindings
- [ ] 9.7 External triggers regression — STM32G0 has at least 5 trigger
      sources including TIM1_TRGO with EXTSEL=0; ESP32 carries empty
- [ ] 9.8 Regenerate emitted goldens for every family with `driver_semantics/
      adc.hpp` (4 already emitted + 5 new); pin them under
      `tests/fixtures/emitted/<family>/`

## Phase 10: Spec deltas + docs

- [x] 10.1 Author `specs/artifact-contract/spec.md` delta with 3 ADDED
      requirements:
      (a) "ADC trait header is populated for every admitted ADC peripheral"
      (b) "ADC trait surfaces internal channels, calibration context, and
           configuration value semantics"
      (c) "ADC trait surfaces DMA bindings and external trigger sources"
- [ ] 10.2 Update `__readme_caveat` for esp32, esp32c3, esp32s3, avr-da,
      rp2040 to describe their ADC coverage scope
- [ ] 10.3 Update alloy-codegen `README.md`'s "Published Device Matrix"
      section: mention that ADC traits include cal context / DMA bindings /
      external trigger sources
- [x] 10.4 Run `openspec validate add-full-adc-coverage --strict`; resolve
      any findings
