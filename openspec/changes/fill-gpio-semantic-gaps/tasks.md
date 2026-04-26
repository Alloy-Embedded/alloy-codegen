# Tasks: Fill GPIO Semantic Gaps

Tasks are ordered by family. CI gate in phase 5 blocks all subsequent family
admissions.

## 1. GPIO semantic emitter infrastructure

- [ ] 1.1 Add `GpioSemanticEmitter` base class in
      `src/alloy_codegen/emitters/gpio_semantics.py`. Defines the `emit(device)`
      interface that each family adapter implements.
- [ ] 1.2 Extend `CanonicalDeviceIR` with a `gpio_pins: list[GpioPinDescriptor]`
      field. `GpioPinDescriptor` carries `pin_id`, `port`, `pin_index`, `is_input_only`,
      `alt_functions: list[AltFunctionDescriptor]`.
- [ ] 1.3 Add JSON schema for `GpioPinDescriptor` and update `ir/schema.json`.
      Validate round-trip: existing fixtures (all with empty `gpio_pins`) still pass.
- [ ] 1.4 Update `artifact-contract` spec scenario: `gpio.hpp` MUST contain at
      least one specialization with `kPresent = true` for every admitted family
      after this change lands.

## 2. STM32G0 GPIO traits

- [ ] 2.1 Create `patches/st/stm32g0/pin_data.json`: machine-readable pin
      alternate-function table for the STM32G071RB (LQFP64 package). Source from
      ST's Open Pin Data spreadsheet. Fields: `pin_name`, `port`, `pin_num`,
      `alt_functions: [{af_num, signal_name}]`.
- [ ] 2.2 Implement `STM32GpioNormalizer` in
      `src/alloy_codegen/sources/stm32_open_pin_data.py`: reads `pin_data.json`,
      resolves each signal name against the SVD peripheral list, populates
      `GpioPinDescriptor` in the IR.
- [ ] 2.3 Implement `STM32GpioSemanticEmitter.emit(device)`: writes
      `gpio.hpp` specializations for STM32G0. Template uses `kPortOffset =
      (GPIOX_BASE - GPIOA_BASE)`, `kPinIndex`, `kMaxAltFunction`,
      `kValidAltFunctions`.
- [ ] 2.4 Golden: regenerate `tests/fixtures/emitted/stm32g071rb/driver_semantics/gpio.hpp`.
      Assert: GPIOA_PIN5 (LED pin on Nucleo-G071RB) has `kPresent=true`,
      `kPortOffset=0`, `kPinIndex=5`.
- [ ] 2.5 Compile test: `tests/compile_tests/test_stm32g0_gpio_traits.cpp` —
      instantiate `gpio::pin<GpioPinId::GPIOA_5>()` and verify concept satisfied.

## 3. STM32F4 GPIO traits

- [ ] 3.1 Create `patches/st/stm32f401re/pin_data.json` (LQFP64) from ST Open
      Pin Data. Same schema as STM32G0.
- [ ] 3.2 Extend `STM32GpioNormalizer` to accept F4 family (same logic, different
      AF count — F4 supports AF0–AF15 vs G0's AF0–AF7 on most pins).
- [ ] 3.3 Emit and golden for `stm32f401re`. Assert GPIOA_PIN5 (LED on F4 Nucleo)
      has `kMaxAltFunction=15`.
- [ ] 3.4 Compile test for F4 GPIO traits.

## 4. Espressif GPIO traits

- [ ] 4.1 Add `GpioMatrixSignalDescriptor` to the IR: `signal_name`, `in_sel_idx`,
      `out_sel_idx`, `out_en_sel_idx`. Populate from `gpio_sig_map.h` parsing
      already in `esp_idf.py`.
- [ ] 4.2 Implement `EspressifGpioSemanticEmitter` for ESP32 classic:
      - 40 pads (0–39): `kGpioNum`, `kIsInputOnly` (GPIO34–39 = true),
        `kHasIoMuxFastPath` (pads with IO_MUX direct = true).
      - `GpioMatrixSemanticTraits<SignalId>`: `kInSelIdx`, `kOutSelIdx`.
      Emits both into `gpio.hpp`.
- [ ] 4.3 ESP32-C3 variant (21 pads, all bidirectional, single GPIO matrix —
      no separate IO_MUX path for most pads). Emit `kIsInputOnly=false` for all.
- [ ] 4.4 ESP32-S3 variant (48 pads). IO_MUX fast-path pads from S3 TRM table.
- [ ] 4.5 Goldens for esp32, esp32c3, esp32s3. Assert GPIO2 on ESP32 classic has
      `kHasIoMuxFastPath=true` and `kIsInputOnly=false`.
- [ ] 4.6 Compile tests for all three Espressif variants.

## 5. AVR-DA GPIO traits

- [ ] 5.1 Implement `AvrDaGpioNormalizer` in
      `src/alloy_codegen/sources/atdf_avr.py`: parse `<module name="PORT">` and
      `<module name="PORTMUX">` from the AVR128DA48 ATDF. Populate
      `GpioPinDescriptor` with `kPortIndex`, `kPinBit`, `kPmuxChannel`.
- [ ] 5.2 Implement `AvrDaGpioSemanticEmitter`. PORTMUX channel index = -1 if
      pin has no mux assignment.
- [ ] 5.3 Golden for `avr128da48`. Assert PORTA_PIN7 present with correct
      `kPortIndex=0`, `kPinBit=7`.
- [ ] 5.4 Compile test for AVR-DA GPIO traits.

## 6. CI gate

- [ ] 6.1 Add `gpio-semantic-coverage` CI job: runs `pytest tests/test_gpio_semantics.py`.
      Fails if any admitted family has zero `kPresent=true` entries in `gpio.hpp`.
      Blocks PRs that admit a new family without GPIO traits.
- [ ] 6.2 Update `docs/COVERAGE_MATRIX.md`: add `gpio_traits` column. Mark
      SAME70=✓, STM32G0=✓, STM32F4=✓, ESP32=✓, ESP32-C3=✓, ESP32-S3=✓,
      AVR-DA=✓, RP2040=see `complete-rp2040-semantics`.
