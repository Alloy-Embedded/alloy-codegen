## ADDED Requirements

### Requirement: CanonicalDeviceIR SHALL surface family-shaped PWM controller descriptors

`CanonicalDeviceIR` SHALL surface PWM hardware-feature facts via per-family-shape descriptor tuples — one per silicon archetype rather than a single mega-class — so each shape stays self-documenting and the IR JSON omits irrelevant fields per family.

The new fields are:

- `stm_timer_pwm_peripherals: tuple[StmTimerPwmDescriptor, ...]` —
  carries `(controller_id, base_address, kind, channel_count,
  counter_bits, valid_ch_pins_per_channel, valid_chn_pins_per_channel,
  dma_req_lines, supports_complementary, supports_deadtime,
  supports_brake, supports_center_aligned, max_clock_hz)`.
- `flex_pwm_peripherals: tuple[FlexPwmDescriptor, ...]` —
  `(controller_id, base_address, submodule_count, paired_channels,
  valid_a_pins_per_submodule, valid_b_pins_per_submodule,
  supports_complementary, supports_deadtime, supports_fault_input,
  supports_force_initialization, dma_req_lines)`.
- `mcpwm_peripherals: tuple[McpwmDescriptor, ...]` — `(controller_id,
  base_address, timer_count, output_signal_count,
  gpio_matrix_signals, capture_signals, supports_deadtime,
  supports_carrier_modulation, supports_fault_input)`.
- `avr_da_tca_pwm_peripherals: tuple[AvrDaTcaPwmDescriptor, ...]` —
  `(controller_id, base_address, default_channel_pins,
  split_mode_channels, single_mode_channels, counter_bits,
  portmux_alt)`.
- `same70_pwm_peripherals: tuple[Same70PwmDescriptor, ...]` —
  `(controller_id, base_address, kind, channel_count,
  valid_pins_per_channel, supports_dead_time, supports_fault_input,
  supports_dma)`.
- The existing `LedcDescriptor` SHALL be extended (preserving
  current fields) with `timer_count`, `low_speed_channel_count`,
  `high_speed_channel_count`, `max_resolution_bits`.

Every descriptor list defaults to the empty tuple for devices that
don't ship that flavour of PWM.

#### Scenario: STM32G0 admits TIM1 with complementary outputs

- **WHEN** the STM32G071RB device is normalized
- **THEN** `Device.stm_timer_pwm_peripherals` contains an entry for
  `TIM1` with `kind = "advanced"`, `channel_count = 4`,
  `counter_bits = 16`, `supports_complementary = true`,
  `supports_deadtime = true`, `supports_brake = true`
- **AND** `valid_ch_pins_per_channel[0]` (CH1 pads) is non-empty
- **AND** `valid_chn_pins_per_channel[0]` (CH1N complementary
  output pads) is non-empty

#### Scenario: iMXRT1060 admits four FlexPWM controllers

- **WHEN** the mimxrt1062 device is normalized
- **THEN** `Device.flex_pwm_peripherals` contains four entries
  (`PWM1` .. `PWM4`)
- **AND** every entry carries `submodule_count = 4` and
  `paired_channels = true`
- **AND** `supports_complementary`, `supports_deadtime`,
  `supports_fault_input`, `supports_force_initialization` are all
  `true` per FlexPWM silicon spec

#### Scenario: ESP32 classic admits MCPWM, ESP32-C3 does not

- **WHEN** the ESP32 classic device is normalized
- **THEN** `Device.mcpwm_peripherals` contains two entries
  (`MCPWM0`, `MCPWM1`)
- **AND** the ESP32-C3 normalize result has `mcpwm_peripherals == ()`

#### Scenario: AVR-DA TCA0 records the default placement

- **WHEN** the avr128da32 device is normalized
- **THEN** `Device.avr_da_tca_pwm_peripherals` contains an entry
  for `TCA0` with `default_channel_pins == ("PA0", "PA1", "PA2",
  "PA3", "PA4", "PA5")`, `split_mode_channels = 6`,
  `single_mode_channels = 3`, `counter_bits = 16`,
  `portmux_alt = false`

#### Scenario: SAME70 admits both PWM peripherals and TC waveform mode

- **WHEN** the atsame70q21b device is normalized
- **THEN** `Device.same70_pwm_peripherals` contains six entries:
  `PWM0`, `PWM1` with `kind = "pwm"` and `channel_count = 4`; plus
  `TC0`, `TC1`, `TC2`, `TC3` with `kind = "tc"` and
  `channel_count = 3`

#### Scenario: Devices without PWM hardware carry empty tuples

- **WHEN** any admitted device without PWM (currently none — every
  admitted family ships at least one PWM-capable peripheral) is
  normalized
- **THEN** every PWM descriptor field is the empty tuple
- **AND** all six PWM descriptor fields are omitted from the
  serialized canonical IR JSON
