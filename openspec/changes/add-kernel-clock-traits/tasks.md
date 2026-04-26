# Tasks — add-kernel-clock-traits

## Phase 1: Helper + IR plumbing

- [x] 1.1 Added `_kernel_clock_for_peripheral(context, peripheral_name)`
      helper that walks `device.peripheral_clock_bindings`, follows
      `selector_id` into `clock_selectors`, and resolves both the
      selector and gate `register_field_id` to typed
      `RuntimeFieldRef` records via `_resolve_field_ref_by_id` (a
      new helper that parses `field:<peripheral>:<register>:<field>`).
      Bonus helper `_classify_kernel_clock_source` maps clock-tree
      node IDs to the `KernelClockSource` enum.
- [x] 1.2 IR fields already present (`peripheral_clock_bindings`,
      `clock_selectors`, `clock_gates`).  No spec change needed.
- [x] 1.3 Extended `UartSemanticRow`, `SpiSemanticRow`,
      `I2cSemanticRow`, `QspiSemanticRow`, `SdmmcSemanticRow` with
      `kernel_clock_selector_field`, `kernel_clock_source_options`,
      `max_clock_hz`, `clock_gate_field`.

## Phase 2: Per-family `max_clock_hz` data

- [x] 2.1 Added `PeripheralMaxClockPatch` dataclass +
      `peripheral_max_clock_hz` field on `DevicePatch` and
      `CanonicalDeviceIR`.  Wired forwarders in `normalize.py` and
      `connector_model.py`.  Schema: list of
      `{peripheral, max_clock_hz}`.
- [x] 2.2 Populated per family via
      `scripts/populate_kernel_clock_max.py`:
      - STM32G0: 64 MHz on every USART/SPI/I2C
      - STM32F4: 84 MHz APB2 (USART1/USART6/SPI1), 42 MHz APB1 (rest)
      - SAME70: 150 MHz on every UART/USART/SPI
      - iMXRT1060: 80 MHz LPUART, 60 MHz LPSPI
      - RP2040: 125 MHz peri_clk
      - ESP32 family: 80 MHz APB
      - AVR-DA: 24 MHz CLK_PER

## Phase 3: Constexpr emission

- [x] 3.1 New `_kernel_clock_lines` renderer + `KernelClockSource`
      enum + `KernelClockSourceOption` struct lifted into
      `common.hpp`.  UART, SPI, I2C, QSPI, SDMMC specialization
      builders emit the four constexprs in both stub and non-stub
      branches.  Renamed the new constexpr to `kKernelMaxClockHz`
      to avoid colliding with the existing SPI `kMaxClockHz` (which
      describes the SPI's *output* max from `fill-espressif-semantic-gaps`).
- [x] 3.2 `default_lines` in every relevant
      `emit_runtime_driver_*_semantics_header` ships safe-falsy
      values (`kInvalidFieldRef` / empty array / `0u`).

## Phase 4: Tests + goldens

- [x] 4.1 Regression test
      `test_stm32g071rb_uart_traits_emit_kernel_clock` asserts
      USART1 has 4 source options (PCLK / SYSCLK / HSI16 / LSE),
      `kKernelMaxClockHz == 64'000'000u`, and a valid
      `RuntimeFieldRef` for the gate.
- [x] 4.2 Regenerated normalize fixtures + emit-fixture goldens for
      every family (`scripts/regen_canonical_fixtures.py` +
      `scripts/update_goldens.py`).

## Phase 5: Spec + final checks

- [x] 5.1 Spec delta already landed in
      `specs/artifact-contract/spec.md` during proposal authoring.
- [x] 5.2 `openspec validate add-kernel-clock-traits --strict`
      passes.
- [x] 5.3 Full `pytest -q` passes (370 passed, 1 skipped).
      `ruff check` + format clean.
- [x] 5.4 Archive entry notes that this completes Stage 1 of the
      driver-semantics roadmap (irq-vectors + dma-cross-refs +
      kernel-clock) and unblocks modm-style baud resolvers in
      alloy.
