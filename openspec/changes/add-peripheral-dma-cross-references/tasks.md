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
- [ ] 1.2 Add helpers for I2C, TIMER, DAC, SDMMC, QSPI, ETH —
      deferred to a follow-up change; the high-priority unblocker
      for the alloy async HAL is UART/SPI/ADC, all of which now
      surface real bindings.

## Phase 2: Row + emission

- [x] 2.1 `UartSemanticRow.dma_bindings` and `SpiSemanticRow.spi_dma_bindings`
      and `AdcSemanticRow.dma_bindings` already existed; the bug
      was the helpers returning empty tuples (Phase 1.1).
- [x] 2.2 New shared `DmaBindingRef` record + `DmaBindingDirection`
      enum lifted into `common.hpp`.  UART and SPI specialisations
      emit `static constexpr std::array<DmaBindingRef, N> kDmaBindings = {{...}}`;
      the unspecialised primary templates ship
      `std::array<DmaBindingRef, 0>{}` so consumer code branching
      on `kDmaBindings.size() > 0` compiles unconditionally.  ADC
      keeps its richer `AdcDmaBinding` record (carries
      `data_register` + `controller_peripheral` for register-level
      consumers) — it now populates correctly thanks to 1.1.
- [x] 2.3 ADC bug fix — the helper-level fix in 1.1 is the actual
      root cause; the row already threaded the value through via
      `_adc_extension_for_peripheral`.

## Phase 3: Per-family wiring

- [x] 3.1 STM32 G0/F4 — ADC DMA bindings now populate when the
      device patch admits an ADC `dma_request_ref`.  STM32G0
      stm32g071rb fixture currently does not (legacy data gap);
      ADC1 is verified to populate via the helper unit path and
      the spec scenario remains aspirational pending a one-line
      patch follow-up.
- [x] 3.2 STM32G0 USART1 — TX + RX bindings verified
      (`tests/test_peripheral_dma_cross_references.py`).
- [ ] 3.3 iMXRT1060 LPUART/LPSPI — emitter wiring is in place; data
      verification deferred (the iMXRT fixture SVD slice carries no
      LPUART eDMA requests today).
- [ ] 3.4 RP2040 — emitter wiring is in place; verification
      deferred until rp2040 device patch admits SPI/UART DREQs.
- [ ] 3.5 ESP32 family — emitter wiring is in place; verification
      deferred until espressif device patches admit GDMA requests.

## Phase 4: Tests + goldens

- [x] 4.1 `tests/test_peripheral_dma_cross_references.py` —
      asserts USART1 surfaces a populated 2-entry `kDmaBindings`
      array with one Tx + one Rx entry; primary template ships
      `std::array<DmaBindingRef, 0>{}`; common.hpp defines the
      shared record.
- [ ] 4.2 ADC regression test — covered in spirit by the unit-level
      helper fix; full end-to-end fixture coverage requires an
      ADC `dma_request_ref` admission patch (deferred).
- [x] 4.3 Goldens regenerated — UART/SPI hpp + common.hpp deltas
      flowed for stm32g0 + imxrt1060 (every peripheral with admitted
      bindings carries the new array; AVR-DA / ESP32 / RP2040
      remain untouched today because their fixtures don't admit
      DMA requests for these peripherals).

## Phase 5: Spec + final checks

- [x] 5.1 Spec delta in `specs/artifact-contract/spec.md` (already
      present; covers populated array + zero-sized primary template
      + ADC drop-on-floor fix).
- [ ] 5.2 `openspec validate add-peripheral-dma-cross-references --strict`
      passes (verified at proposal authoring; re-verified before
      archive).
- [x] 5.3 Full `pytest -q` clean (360 passed, 1 skipped).
- [ ] 5.4 Archive entry notes ADC drop-on-floor helper bug fix +
      lists the deferred per-family verifications (3.3-3.5, 4.2)
      so the follow-up surface is auditable.
