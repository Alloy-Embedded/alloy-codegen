# Add Peripheral → DMA Cross-References

## Why

DMA bindings are unidirectional today: `dma.hpp` knows that
`USART1_TX` resolves to DMA1 channel 1 with request line 50, but
`uart.hpp` emits `kDmaBindingCount = 0` and `kDmaBindings = {}`.  The
same applies to SPI, I2C, ADC, TIMER — every peripheral that *uses*
DMA but doesn't *back-reference* the bindings it owns.

The data already exists in the IR (`device.dma_requests`, filtered by
`peripheral`).  ADC has the right helper but emits empty bindings
because of a wiring bug; UART/SPI shipped the dataclass scaffolding
in `add-uart-spi-tier-2-3-4-data` but the cross-reference array
itself ships zero entries today.

Without these arrays, the alloy async HAL cannot answer "give me the
DMA binding for SPI1 RX" without a textual scan of `dma.hpp`.  modm
exposes the same fact via `DmaResource::Channel<Spi1, Receive>`.

This change is one of the two highest-priority unblockers identified
in the post-`add-uart-spi-tier-2-3-4-data` analysis.

## What Changes

### Trait surface

Each peripheral specialization that already carries
`kSupportsDma = true` (or whose IR filters non-empty for DMA
requests) SHALL emit a populated `kDmaBindings[]` array of
`DmaBindingRef` records carrying:

- `controller_id` (e.g. `DmaControllerId::DMA1`)
- `channel_index`
- `request_line` (DMAMUX value or per-stream ID on F4)
- `signal` (`Tx`, `Rx`, `Cmd`, `Ack`, ...)
- `transfer_width_bits` (8 / 16 / 32, derived from frame size)
- `binding_id` (the ID already used by `dma.hpp` so the consumer
  can correlate)

### Pipeline

- `_dma_bindings_for_peripheral(context, peripheral_name, signal_filter)`
  helpers already exist for UART/SPI; extend the same pattern to
  ADC, I2C, TIMER, DAC, SDMMC, QSPI, ETH.
- Specialization builders emit
  `static constexpr std::array<DmaBindingRef, N> kDmaBindings = {{...}}`.
- ADC fix: today `_st_adc_row` calls the helper but the result is
  ignored — wire it through.

### Goldens

Regenerate every `<peripheral>.hpp` golden across all 9 admitted
families.  Diff scope: ONE new array per specialization on
peripherals that have admitted DMA bindings.

## Impact

Together with `add-irq-vector-traits`, this completes the two facts
that every async driver needs at compile time.  After both land,
the alloy `add-async-uart-hal` can be implemented purely in alloy
without touching codegen again.
