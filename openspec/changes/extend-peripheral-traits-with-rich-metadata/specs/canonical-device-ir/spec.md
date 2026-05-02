## ADDED Requirements

### Requirement: Canonical IR `AdcCalibration` SHALL Carry A Complete Calibration Surface

The canonical IR loader SHALL accept `peripherals[].calibration:
AdcCalibration` only when populated entries carry every field
required by alloy's ADC HAL (`vrefint`, `ts_cal_low`, `ts_cal_high`,
`ts_low_temp_c`, `ts_high_temp_c`, `ts_slope_uv_per_c`), and SHALL
raise `ConfigError` on any partial calibration record.

#### Scenario: Complete STM32 G0 ADC calibration loads cleanly

- **WHEN** alloy-codegen loads
  `data/devices/vendors/st/stm32g0/devices/stm32g071rb.yml`
- **THEN** `device.peripherals[id == "adc1"].calibration` is a
  populated `AdcCalibration` with non-`None` `vrefint`,
  `ts_cal_low`, `ts_cal_high`, `ts_low_temp_c`,
  `ts_high_temp_c`, `ts_slope_uv_per_c`

#### Scenario: Partial calibration refuses to load

- **WHEN** a YAML carries `peripherals[].calibration` with
  `ts_cal_low: 0x1FFF75A8` but no `ts_slope_uv_per_c`
- **THEN** the loader raises `ConfigError` naming the offending
  peripheral id and the missing field

### Requirement: Canonical IR `I2cTimingPreset` SHALL Carry The Encoded Register Payload

The canonical IR `I2cTimingPreset` SHALL carry a typed
`speed_hz: int`, `pclk_hz: int`, and the vendor-encoded register
payload (`timingr` for STM32 I²C-v2/v3, or `ccr` + `trise` for
STM32 I²C-v1) sufficient to program the instance without runtime
division.

#### Scenario: STM32 G0 I²C presets carry pre-computed TIMINGR

- **WHEN** alloy-codegen loads any STM32 G0 device
- **THEN** every populated `peripherals[].timing_presets[i]`
  carries a non-zero `timingr` integer
- **AND** the `pclk_hz` field matches the PCLK assumed when the
  preset was computed

### Requirement: Canonical IR Timer Template Matrix Fields SHALL Carry Executable Triples

The canonical IR SHALL carry a register/field/encoding triple
on every entry of `Template.trigger_sources`,
`Template.master_outputs`, `Template.deadtime_options`, and
`Template.break_inputs`, rather than a human-readable label
alone, so an emitter can program the timer matrix from the IR
alone.

#### Scenario: STM32 F4 advanced-timer trigger source carries register triple

- **WHEN** alloy-codegen loads any STM32 F4 device
- **THEN** every entry in `templates[tim_advanced].trigger_sources`
  carries `(register_ref, field_ref, encoding_int)`
- **AND** the encoding integer is the value to write into the
  `SMCR.TS` field for that source
