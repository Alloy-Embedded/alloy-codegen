## Overview

This change extends the generated bring-up/runtime boundary into the MCU timing domain.

There are two related but distinct contracts:

1. `SysTick`
   - architecturally common across Cortex-M
   - still device-scoped in publication because the system clock profile, optional calibration
     data, and source package completeness differ by vendor/device
2. `timer/PWM`
   - schema-specific peripheral semantics
   - must publish per-instance and per-channel capability/field/register traits

The intent is not to emit a monolithic cross-vendor timer abstraction inside `alloy-codegen`.
The intent is to publish enough typed device/runtime data so Alloy can implement zero-overhead
timer, capture/compare and PWM APIs without raw-register fallback.

## SysTick Contract

### Artifact

Each Cortex-M device emits:

- `generated/runtime/devices/<device>/systick.hpp`

This header publishes a device-scoped SysTick contract with:

- `enum class SysTickClockSourceId`
- `struct SysTickDescriptor`
- `template<> struct SysTickTraits`
- typed register refs for `CTRL`, `LOAD`, `VAL`, `CALIB`
- typed field refs for `ENABLE`, `TICKINT`, `CLKSOURCE`, `COUNTFLAG`, `RELOAD`, `CURRENT`,
  `TENMS`, `SKEW`, `NOREF` when available
- optional system-handler priority field refs when they can be resolved cleanly from the source
  package
- minimal generated configuration helpers that can:
  - set the clock source
  - program reload
  - clear current value
  - enable/disable counter and interrupt request

The generated helper is intentionally low-level. It is not a public HAL class. Alloy still owns
the user-facing `SysTick` API.

### Architectural synthesis

Some upstream packages expose SysTick as a normal peripheral. Some do not.

For Cortex-M devices, `alloy-codegen` must synthesize the SysTick publication when upstream data is
missing or incomplete. The synthesis baseline is:

- base address `0xE000E010`
- 24-bit reload/current value model
- vector slot `15` / `SysTick_Handler`

When upstream data provides real `CALIB` or SCB field information, the generated contract must use
it. Otherwise the contract publishes explicit invalid/unknown refs for optional fields instead of
dropping the contract entirely.

### Relationship to system clock

`SysTick` configuration depends on core clock frequency, but it is not another system clock
profile.

The contract must therefore link cleanly to existing `system_clock.hpp` publication:

- device-scoped SysTick traits expose whether the timer can run from core clock only, core/8, or a
  separate reference source
- helper functions accept a caller-provided clock frequency or a published system-clock profile
- no handwritten board-local register recipe is required just to start SysTick on supported
  devices

## Timer/PWM Contract

### Artifacts

Each device with timer-capable peripherals emits:

- `generated/runtime/devices/<device>/driver_semantics/timer.hpp`

Each device with PWM-capable peripherals emits:

- `generated/runtime/devices/<device>/driver_semantics/pwm.hpp`

These contracts are runtime-lite artifacts. They are device-scoped and schema-driven like the
existing `gpio/uart/i2c/spi/dma` semantics.

### Peripheral coverage

The publication must cover three categories:

1. general/basic/advanced timers
   - STM32 `TIMx`
   - Microchip `TCx`
   - NXP `GPT`, `PIT`
2. timer-backed PWM capability
   - timers whose channels can generate PWM
3. dedicated PWM peripherals
   - Microchip `PWM`
   - NXP `PWM`

The contract must not assume every timer can do every waveform mode. Unsupported features must be
represented explicitly in the traits.

### Capability model

The timer/PWM contract must publish typed capability facts rather than force Alloy to rediscover
them from register names.

At minimum, the traits must cover:

- counter presence
- counter width
- channel count
- prescaler support
- auto-reload/period support
- output compare support
- input capture support
- PWM support
- one-pulse support when available
- center-aligned mode when available
- complementary outputs when available
- deadtime support when available
- break/fault support when available
- synchronous update / shadow transfer support when available

This can be represented as `constexpr` booleans and numeric limits in per-peripheral/per-channel
traits. It does not need a runtime-polymorphic capability table.

### Trait shape

The generated surface should be shaped like the existing driver semantics:

- `template<PeripheralId Id> struct TimerSemanticTraits`
- `template<PeripheralId Id, std::size_t ChannelIndex> struct TimerChannelSemanticTraits`
- `template<PeripheralId Id> struct PwmSemanticTraits`
- `template<PeripheralId Id, std::size_t ChannelIndex> struct PwmChannelSemanticTraits`

These traits publish:

- typed register refs for control/status/counter/prescaler/period/update registers
- typed field refs for enable/disable/start/stop/update/event bits
- typed field refs for compare/capture mode bits
- typed field refs for output enable/polarity/preload bits
- typed refs for duty/period/channel compare registers
- optional typed refs for advanced features like complementary output enable, deadtime and fault

Routes and pin ownership remain in the existing `routes.hpp` contract. The new semantics only cover
the device/peripheral behavior layer.

### Vendor/schema strategy

Like `uart/i2c/spi/dma`, timer/PWM semantics are emitted by backend schema and vendor family.

Initial schema coverage must include:

- `st/stm32g0`
  - `schema_alloy_timer_st_tim`
  - `schema_alloy_timer_st_gptimer2_v3_x_cube`
- `st/stm32f4`
  - `schema_alloy_timer_st_tim`
  - `schema_alloy_timer_st_gptimer2_v2_x_cube`
- `microchip/same70`
  - `schema_alloy_timer_microchip_tc_zl`
  - `schema_alloy_pwm_microchip_pwm_y`
  - `schema_alloy_systick_microchip_systick`
- `nxp/imxrt1060`
  - `schema_alloy_gpt_nxp_gpt`
  - `schema_alloy_pit_nxp_pit`
  - `schema_alloy_pwm_nxp_pwm`

If a vendor family publishes devices with timer/PWM schemas outside this list, publication must not
pretend support exists. The gate should either fail or emit explicit TODO coverage markers only in
non-foundational contexts.

## Canonical and Runtime-Lite Selection

### SysTick

For Cortex-M devices, SysTick must become part of the generated runtime domain even if it does not
arrive from the source package as a normal peripheral. This may be implemented as:

- a synthetic canonical peripheral/register/field enrichment step, or
- a runtime-lite/emitter-side synthesis step

The important rule is the published contract, not which internal layer synthesizes it.

### Timer/PWM inclusion

`runtime-lite` currently filters peripheral classes to:

- `gpio`
- `uart`
- `spi`
- `i2c`
- `dma`
- `dma-router`

This change expands the active runtime publication set to include timing classes:

- `systick`
- `timer`
- `pwm`

And, where appropriate, timer-like classes such as `gpt` and `pit` must normalize into the timing
contract instead of staying outside it.

## Validation and Gates

Foundational publication must fail when:

- a Cortex-M foundational device lacks `generated/runtime/devices/<device>/systick.hpp`
- a foundational device with timer peripherals lacks `driver_semantics/timer.hpp`
- a foundational device with PWM-capable peripherals lacks `driver_semantics/pwm.hpp`
- the published timing headers do not expose typed traits and the minimum required register/field
  refs for their supported schemas

Consumer smoke must compile:

- `systick.hpp`
- `driver_semantics/timer.hpp`
- `driver_semantics/pwm.hpp`

for each foundational family where those domains apply.

## Non-Goals

- No attempt to solve every timer mode in one generic algorithm inside the code generator
- No public user-facing timer/PWM HAL API in `alloy-codegen`
- No reflection-heavy global timer tables in the runtime-lite contract

This change is only about publishing the typed device semantics Alloy needs to build those APIs
cleanly.
