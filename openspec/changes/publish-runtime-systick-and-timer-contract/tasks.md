## 1. Spec and Normalization

- [x] 1.1 Add this SysTick/timer/PWM runtime contract change
- [x] 1.2 Decide and implement the SysTick synthesis point for Cortex-M devices
- [ ] 1.3 Expand runtime-lite timing class selection to include `systick`, `timer` and `pwm`
- [x] 1.4 Normalize timer-like families such as `gpt` and `pit` into the timing publication path

## 2. SysTick Runtime Contract

- [x] 2.1 Emit `generated/runtime/devices/<device>/systick.hpp`
- [x] 2.2 Publish SysTick traits for `stm32g071rb`
- [x] 2.3 Publish SysTick traits for `stm32f401re`
- [x] 2.4 Publish SysTick traits for `atsame70q21b`
- [x] 2.5 Publish SysTick traits for `mimxrt1062`
- [x] 2.6 Expose typed configuration helpers and optional calibration/source traits

## 3. Timer Runtime Contract

- [x] 3.1 Add `TimerSemanticRow` and `TimerChannelSemanticRow` emission support
- [x] 3.2 Emit `generated/runtime/devices/<device>/driver_semantics/timer.hpp`
- [x] 3.3 Cover STM32 timer schemas for foundational families
- [x] 3.4 Cover Microchip `TC` timer schemas
- [x] 3.5 Cover NXP `GPT` and `PIT` timer schemas
- [x] 3.6 Publish explicit per-channel compare/capture/output capability traits

## 4. PWM Runtime Contract

- [x] 4.1 Add `PwmSemanticRow` and `PwmChannelSemanticRow` emission support
- [x] 4.2 Emit `generated/runtime/devices/<device>/driver_semantics/pwm.hpp`
- [x] 4.3 Cover timer-backed PWM on STM32 timers
- [x] 4.4 Cover Microchip dedicated PWM peripherals
- [x] 4.5 Cover NXP dedicated PWM peripherals
- [x] 4.6 Publish advanced capability traits for complementary outputs, deadtime, fault/break and synchronized update where supported

## 5. Gates, Fixtures and Validation

- [x] 5.1 Update artifact contract gates and consumer smoke coverage
- [x] 5.2 Regenerate affected emitted fixtures
- [x] 5.3 Validate with `python3 -m ruff check src tests`
- [x] 5.4 Validate with `python3 -m pytest tests -q`
- [x] 5.5 Validate with `openspec validate publish-runtime-systick-and-timer-contract --strict`
