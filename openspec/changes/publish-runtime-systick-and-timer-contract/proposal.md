## Why

Two timing domains are still missing from the generated runtime contract:

- `SysTick` is treated today as a handwritten Cortex-M helper inside `alloy`, not as a generated
  device contract
- `timer/PWM` peripherals are visible in the canonical model and runtime enums, but they are
  filtered out of `runtime-lite` and do not publish `driver_semantics`

That leaves one of the most common MCU subsystems outside the generated boundary. Users still need
to understand vendor manuals for:

- system tick configuration
- timer base setup
- output compare
- input capture
- PWM waveform generation
- advanced timer features such as complementary outputs, deadtime, break/fault and synchronized
  update

For supported devices, that is not acceptable as a long-term contract.

## What Changes

- publish a generated `generated/runtime/devices/<device>/systick.hpp` for Cortex-M devices
- synthesize/publish a typed SysTick contract even when the upstream source package does not model
  SysTick as a normal peripheral
- extend `runtime-lite` publication to include `timer` and `pwm` domains
- publish `generated/runtime/devices/<device>/driver_semantics/timer.hpp`
- publish `generated/runtime/devices/<device>/driver_semantics/pwm.hpp`
- publish explicit timer/PWM capability traits so unsupported features are represented as typed
  `false`/invalid refs instead of being silently absent
- harden validation and publish gates so foundational families cannot ship without SysTick and
  timer/PWM runtime contracts when those capabilities exist on the device

## Impact

- Alloy can stop treating SysTick as handwritten board glue and instead consume a generated
  hardware contract
- timer/PWM support can be built on top of typed runtime semantics instead of legacy vendor
  wrappers and handwritten policies
- supported devices gain a publishable, extensible path for counters, compare/capture and PWM
  without reflection or raw-register examples becoming the canonical workflow
