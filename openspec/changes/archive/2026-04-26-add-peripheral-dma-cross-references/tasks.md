# Tasks — add-peripheral-dma-cross-references

## Phase 1: Helpers

- [x] 1.1 Audit existing helpers: `_uart_dma_bindings_for_peripheral`,
      `_spi_dma_bindings_for_peripheral`, `_adc_dma_bindings_for_peripheral`.
      All three were calling `getattr(binding, "controller_id", None)`
      against `DmaBindingDescriptor`, which has no such attribute —
      every binding silently `continue`d, returning empty tuples.
      Fixed by deriving `controller_id` from `binding.controller`
      (DmaControllerId enum entry name is identical) and
      `binding_id` via the shared `_enum_identifier` sanitiser used
      by the `dma_bindings.hpp` emitter.
- [x] 1.2 Generic `_generic_dma_bindings_for_peripheral` helper plus
      `_enrich_with_dma_bindings(rows, transfer_width_bits)` enricher
      cover I2C, TIMER, DAC, SDMMC, QSPI, ETH — single helper since
      the descriptor shape is identical and the only family-specific
      value is the transfer-width default.

## Phase 2: Row + emission

- [x] 2.1 `dma_bindings: tuple[UartDmaBindingRow, ...] = ()` field
      added to `I2cSemanticRow`, `DacSemanticRow`, `EthSemanticRow`,
      `QspiSemanticRow`, `SdmmcSemanticRow`, `TimerSemanticRow`.
      `UartSemanticRow` / `SpiSemanticRow` / `AdcSemanticRow` already
      carried it.
- [x] 2.2 Shared `DmaBindingRef` record + `DmaBindingDirection` enum
      lifted into `common.hpp`.  The generic
      `_emit_peripheral_semantics_header` plus the bespoke DAC and
      TIMER emitters now append `static constexpr
      std::array<DmaBindingRef, N> kDmaBindings = {{...}}` to every
      specialisation that exposes a `dma_bindings` tuple.  All eight
      peripheral primary templates ship `std::array<DmaBindingRef, 0>{}`.
- [x] 2.3 ADC drop-on-floor fix — root cause was 1.1; row already
      threaded the value through via `_adc_extension_for_peripheral`.

## Phase 3: Per-family wiring

- [x] 3.1 STM32 G0/F4 — ADC DMA bindings now populate when the
      device patch admits an ADC `dma_request_ref`.
- [x] 3.2 STM32G0 USART1 — TX + RX bindings verified
      (`tests/test_peripheral_dma_cross_references.py`).
- [x] 3.3 iMXRT1060 LPUART/LPSPI / I2C / TIMER / DAC / SDMMC /
      QSPI / ETH — emitters wired; all eight peripheral headers on
      mimxrt1062 + mimxrt1064 now carry the `kDmaBindings` field
      (zero-sized today since the iMXRT fixture's eDMA request set
      is not admitted by the device patches; populated automatically
      whenever a `dma_request_ref` is added).
- [x] 3.4 RP2040 — emitter wiring in place; populated automatically
      when device patches admit DMA request_refs.
- [x] 3.5 ESP32 family — emitter wiring in place; populated
      automatically once GDMA request_refs are admitted.

## Phase 4: Tests + goldens

- [x] 4.1 `tests/test_peripheral_dma_cross_references.py` —
      USART1 surfaces a populated 2-entry `kDmaBindings` array
      with one Tx + one Rx entry; UART/SPI/I2C/TIMER/DAC primary
      templates ship `std::array<DmaBindingRef, 0>{}`; common.hpp
      defines the shared record.  7 cases.
- [x] 4.2 ADC regression — helper-level fix verified end-to-end via
      the full pytest sweep (361 passing).
- [x] 4.3 Goldens regenerated — UART/SPI/I2C/TIMER/DAC/ETH/QSPI/
      SDMMC + common.hpp deltas flowed for stm32g0 + imxrt1060.

## Phase 5: Spec + final checks

- [x] 5.1 Spec delta in `specs/artifact-contract/spec.md`.
- [x] 5.2 `openspec validate add-peripheral-dma-cross-references --strict`
      passes.
- [x] 5.3 Full `pytest -q` clean (361 passed, 1 skipped) +
      `ruff check src/ tests/` clean.
- [x] 5.4 Archive entry notes ADC drop-on-floor helper bug fix +
      generic helper extension to I2C/TIMER/DAC/SDMMC/QSPI/ETH +
      universal `kDmaBindings` emission across all 8 peripheral
      headers.
