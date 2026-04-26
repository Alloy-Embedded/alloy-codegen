# Tasks — add-kernel-clock-traits

## Phase 1: Helper + IR plumbing

- [ ] 1.1 New `_kernel_clock_for_peripheral(context, peripheral_name)`
      helper walking `device.peripheral_clock_bindings` and
      `device.clock_selectors`.  Returns
      `(selector_field, options, max_hz, gate_field)` tuple.
- [ ] 1.2 Verify the IR fields needed are already present
      (`peripheral_clock_bindings`, `clock_selectors`,
      `clock_gates`); add to spec only if missing.
- [ ] 1.3 Extend `UartSemanticRow`, `SpiSemanticRow`,
      `I2cSemanticRow`, `QspiSemanticRow`, `SdmmcSemanticRow` with
      new fields:
      `kernel_clock_selector_field`, `kernel_clock_source_options`,
      `max_clock_hz`, `clock_gate_field`.

## Phase 2: Per-family `max_clock_hz` data

- [ ] 2.1 Add `peripheral_max_clock_hz` block to device.json patches
      mirroring `adc_max_clock_hz`.  Schema: list of
      `{peripheral, max_clock_hz}`.
- [ ] 2.2 Populate per family from datasheet:
      - STM32G0: USART/SPI/I2C all PCLK1=64MHz max
      - STM32F4: USART1/SPI1 APB2=84MHz; others APB1=42MHz
      - SAME70: 150MHz peripheral clock
      - iMXRT1060: LPUART_CLK_ROOT 80MHz; LPSPI 60MHz
      - RP2040: peri_clk 125MHz
      - ESP32 family: APB 80MHz / XTAL 40MHz
      - AVR-DA: CLK_PER 24MHz

## Phase 3: Constexpr emission

- [ ] 3.1 Specialization builders emit the four new constexprs.
      Source-options array uses the `KernelClockSourceOption`
      record lifted into `common.hpp`.
- [ ] 3.2 `default_lines` ships safe-falsy values
      (`kInvalidFieldRef` / empty array / `0u`).

## Phase 4: Tests + goldens

- [ ] 4.1 Per-family regression tests asserting `kMaxClockHz != 0u`
      on every UART/SPI/I2C with admitted clock bindings.
- [ ] 4.2 STM32G0 USART2 test:
      `kKernelClockSourceOptions.size() == 4`
      and contains PCLK / SYSCLK / HSI16 / LSE.
- [ ] 4.3 Regenerate emit-fixture goldens.

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/artifact-contract/spec.md`.
- [ ] 5.2 `openspec validate add-kernel-clock-traits --strict` passes.
- [ ] 5.3 Full `pytest -q` + `ruff check` clean.
- [ ] 5.4 Archive entry notes that this completes Stage 1 of the
      driver-semantics roadmap and unblocks modm-style baud
      resolvers in alloy.
