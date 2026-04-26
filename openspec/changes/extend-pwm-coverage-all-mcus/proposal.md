# Extend PWM Trait Coverage Across All Admitted MCU Families

## Why

Compile-time PWM concept checks in alloy's HAL (`PwmGenerator<T>`,
`AdvancedPwm<T>`, `MotorPwm<T>`) require populated
`PwmPeripheralTraits<RuntimeXxx>` for every admitted family. Today:

| Family | PWM peripheral(s) | Trait coverage |
|--------|-------------------|----------------|
| stm32g0 / stm32f4 | TIM1 (advanced), TIM2/3/14/16/17 (general) | Empty |
| nxp/imxrt1060 | PWM1/2/3/4 (FlexPWM, 4 submodules each) | Empty |
| espressif/esp32 + esp32s3 | LEDC + MCPWM0 + MCPWM1 | Partial — `LedcDescriptor` only |
| espressif/esp32c3 | LEDC only | Partial — `LedcDescriptor` |
| raspberrypi/rp2040 | PWM (8 slices × 2 channels) | ✓ via `Rp2040PwmSliceHwDescriptor` (`complete-rp2040-semantics` Phase D) |
| microchip/avr-da | TCA0 (with split-mode PWM) | Empty |
| microchip/same70 | PWM0 + PWM1 + TC0/1/2/3 | Empty |

Without populated traits the alloy `PwmGenerator<T>` concept check
silently passes for any unwired family — misconfigured PWM ids
compile with no diagnostic, defeating the core differentiator over
mbed OS / libhal.

## What Changes

This change introduces a **family-shaped descriptor strategy** mirroring
the ADC pattern (single `Rp2040AdcPeripheralDescriptor` for the RP2040
shape coexists with Espressif's `AdcUnitDescriptor`). For PWM the
hardware is more diverse than ADC, so we introduce **per-flavour**
descriptors keyed by the silicon archetype rather than one mega-class
forced to cover all permutations:

### 1. STM32 Advanced + General-purpose Timers (`StmTimerPwmDescriptor`)

STM32 timers act as PWM generators when configured in PWM mode. The
descriptor captures:

- `controller_id` — peripheral name (`"TIM1"`, `"TIM2"`, …).
- `base_address` — from SVD.
- `kind` — `"advanced"` (TIM1/TIM8) or `"general"` (TIM2..TIM5).
  Advanced timers expose complementary outputs + dead-time + brake
  inputs; general timers don't.
- `channel_count` — `4` for TIM1..TIM5, `1` for TIM10/14/16/17.
- `counter_bits` — `16` (TIM1, TIM3, TIM4) or `32` (TIM2, TIM5).
- `valid_ch_pins_per_channel` — `tuple[tuple[str, ...], ...]` of
  canonical pin names (`"PA8"`) sourced from the OPD AF table for
  each channel (`CH1`..`CH4`). Complementary outputs (`CHxN`) are
  recorded under `valid_chn_pins_per_channel`.
- `dma_req_lines` — `tuple[int, ...]` mapping `(CH1, CH2, CH3, CH4,
  UP)` to DMAMUX line indices (G0) or stream/channel pairs (F4).
- `supports_complementary` / `supports_deadtime` / `supports_brake`
  / `supports_center_aligned`.
- `max_clock_hz` — APB-bus clock ceiling on the device.

### 2. NXP iMXRT FlexPWM (`FlexPwmDescriptor`)

iMXRT FlexPWM has a stronger structure than STM32 timer: each
`PWM1..PWM4` block has 4 *submodules*, and each submodule has paired
A/B PWM outputs.

- `controller_id` — peripheral name (`"PWM1"`, …).
- `base_address`.
- `submodule_count` — `4`.
- `paired_channels` — always `True` (A / B per submodule).
- `valid_a_pins_per_submodule`, `valid_b_pins_per_submodule` —
  `tuple[tuple[str, ...], ...]` of `"GPIO_AD_B0_NN"`-style names from
  the iMXRT IOMUX table.
- `supports_complementary`, `supports_deadtime`, `supports_fault_input`,
  `supports_force_initialization`.
- `dma_req_lines` — per-submodule eDMA request line ids.

### 3. Espressif MCPWM (`McpwmDescriptor`)

ESP32 classic + S3 ship two MCPWM peripherals (`MCPWM0`, `MCPWM1`).
Each has 3 timers + 6 PWM outputs (3 paired) + capture inputs. C3
does **not** ship MCPWM (LEDC-only).

- `controller_id` — `"MCPWM0"`, `"MCPWM1"`.
- `base_address`.
- `timer_count` — `3`.
- `output_signal_count` — `6` (3 paired A/B operators).
- `gpio_matrix_signals` — `tuple[int, ...]` of GPIO matrix output
  signal indices for `MCPWM_TIMER0_A_OUT`..`MCPWM_TIMER2_B_OUT`.
- `capture_signals` — `tuple[int, ...]` of input signal indices.
- `supports_deadtime`, `supports_carrier_modulation`,
  `supports_fault_input`.

### 4. Espressif LEDC — extend existing `LedcDescriptor`

`LedcDescriptor` exists but only carries base + channel_count +
resolution + clock_sources + output_signals. Extend with:

- `timer_count` — `4` on classic, `4` on C3 / S3.
- `low_speed_channel_count`, `high_speed_channel_count` (classic
  has both groups; C3 / S3 only low-speed).
- `max_resolution_bits` — `20` on classic, `14` on C3, `20` on S3
  (per ESP-IDF `soc/ledc_periph.h`).

### 5. AVR-DA Timer-Counter Type A (`AvrDaTcaPwmDescriptor`)

AVR-DA TCA0 (and TCA1 on larger packages) supports split-mode PWM
where one 16-bit timer becomes two 8-bit timers driving 6 PWM channels.

- `controller_id` — `"TCA0"` (or `"TCA1"`).
- `base_address`.
- `default_channel_pins` — fixed default placement
  (`("PA0".."PA5")`). Alternate placement via `PORTMUX_TCAROUTEA`
  is recorded as a separate descriptor with `portmux_alt = True`.
- `split_mode_channels` — `6` (when split mode is engaged).
- `single_mode_channels` — `3`.
- `counter_bits` — `16`.

### 6. SAME70 PWM (`Same70PwmDescriptor`)

SAME70 has two `PWM` peripherals + four `TC` timer-counter
peripherals capable of waveform output.

- `controller_id` — `"PWM0"`, `"PWM1"`, `"TC0".."TC3"`.
- `base_address`.
- `kind` — `"pwm"` (full PWM) or `"tc"` (timer-counter waveform mode).
- `channel_count` — `4` for `PWM*`, `3` for `TC*` (channels 0/1/2).
- `valid_pins_per_channel` — from SAME70 ATDF pin AF table.
- `supports_dead_time`, `supports_fault_input`, `supports_dma`.

## Cross-cutting C++ Trait Surface

Each family-shaped descriptor surfaces through a sibling
`*PwmTraits<Runtime*Id>` template emitted into the existing
`pwm.hpp`, alongside the register-level `PwmSemanticTraits<PeripheralId>`
already there:

- `StmTimerPwmTraits<RuntimeStmTimerPwmId>`
- `FlexPwmTraits<RuntimeFlexPwmId>`
- `McpwmTraits<RuntimeMcpwmId>`
- `LedcTraits<RuntimeLedcId>` (only one instance per device — keyed
  by enum to keep the cross-family pattern uniform)
- `AvrDaTcaPwmTraits<RuntimeAvrDaTcaId>`
- `Same70PwmTraits<RuntimeSame70PwmId>`

Pad arrays use `std::array<PinId, N>` (the `PinId` enum from
`../pins.hpp`) — never string literals (boundary test gate). Empty
arrays sentinel-mean "any pad" only on Espressif IO-matrix paths.

## Cross-cutting Validation

- A new `pwm-semantic-coverage` CI gate fails the build when an
  admitted family has zero `kPresent = true` PWM specializations
  on its emitted `pwm.hpp`. Same shape as the GPIO / I2C gates.
- Compile-time invariant tests under `tests/compile_tests/test_*_pwm_traits.cpp`
  driven by the existing `test_compile_invariants.py` harness when
  a host C++20 compiler is on PATH.

## What Does NOT Change

- `Rp2040PwmSliceHwDescriptor` stays the canonical RP2040 descriptor —
  PWM coverage on RP2040 already landed via `complete-rp2040-semantics`
  Phase D and is not re-shaped here.
- The existing register-level `PwmSemanticTraits<PeripheralId>` (the
  per-register stub already in `pwm.hpp`) is preserved — this change
  only **adds** sibling per-controller trait structs.
- Tile-up of the alloy HAL `PwmGenerator<T>` / `AdvancedPwm<T>` /
  `MotorPwm<T>` concept logic — that lives in the `alloy/` repo and
  is its own change.
- I²S / SAI as-PWM (sigma-delta DAC) — separate openspec.

## Alternatives Considered

**Single unified `PwmControllerDescriptor` (one class, optional
fields covering every flavour) like `I2cPeripheralDescriptor`:**

PWM hardware is genuinely heterogeneous — STM32 advanced timer's
brake inputs have nothing in common with iMXRT FlexPWM's force-init
or Espressif MCPWM's capture trigger. Forcing them into one shape
yields ~30 optional fields with cryptic interaction rules. The
ADC-style **family-shaped** descriptor split keeps each shape
self-documenting at the cost of more emit-side code paths. Given
PWM is one of the widest peripheral surfaces in any MCU portfolio,
the readability win is worth the duplication.

**Defer non-RP2040 / non-Espressif coverage:**

Half-coverage means the alloy `MotorPwm<T>` concept silently passes
on STM32 and iMXRT (the two biggest motor-control targets in the
admitted set). Not acceptable.
