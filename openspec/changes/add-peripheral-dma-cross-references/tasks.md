# Tasks — add-peripheral-dma-cross-references

## Phase 1: Helpers

- [ ] 1.1 Audit existing helpers: `_uart_dma_bindings_for_peripheral`,
      `_spi_dma_bindings_for_peripheral`.  Generalise into a single
      `_dma_bindings_for_peripheral(context, peripheral_name, signal_filter)`
      that returns `tuple[DmaBindingRow, ...]`.
- [ ] 1.2 Add helpers for ADC, I2C, TIMER, DAC, SDMMC, QSPI, ETH.

## Phase 2: Row + emission

- [ ] 2.1 Extend `AdcSemanticRow` with `dma_bindings: tuple[...] = ()`
      (today the helper exists but the value is dropped).  Same for
      `I2cSemanticRow`, `TimerSemanticRow`, `DacSemanticRow`,
      `SdmmcSemanticRow`, `QspiSemanticRow`, `EthSemanticRow`.
- [ ] 2.2 Specialization builders emit
      `static constexpr std::array<DmaBindingRef, N> kDmaBindings = {{...}}`
      with a shared `DmaBindingRef` record type lifted into
      `common.hpp`.
- [ ] 2.3 ADC bug fix — `_st_adc_row` already calls the helper but
      the result is unused; thread the value through.

## Phase 3: Per-family wiring

- [ ] 3.1 STM32 G0/F4 — verify ADC DMA bindings now populate.
- [ ] 3.2 STM32G0 USART1/USART2 + SPI1 — verify TX/RX bindings.
- [ ] 3.3 iMXRT1060 LPUART/LPSPI — verify eDMA + DMAMUX.
- [ ] 3.4 RP2040 — verify DREQ-based bindings.
- [ ] 3.5 ESP32 family — verify GDMA bindings on supported chips.

## Phase 4: Tests + goldens

- [ ] 4.1 Per-family tests asserting non-zero `kDmaBindings.size()`
      on every peripheral with admitted DMA routes.
- [ ] 4.2 ADC regression test: STM32G0 ADC1 surfaces ≥1 DMA binding.
- [ ] 4.3 Regenerate emit-fixture goldens.  Diff scope: ONE new
      array per specialization with admitted bindings.

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/artifact-contract/spec.md`.
- [ ] 5.2 `openspec validate add-peripheral-dma-cross-references --strict`
      passes.
- [ ] 5.3 Full `pytest -q` + `ruff check` clean.
- [ ] 5.4 Archive entry notes ADC bug fix (drop-on-floor).
