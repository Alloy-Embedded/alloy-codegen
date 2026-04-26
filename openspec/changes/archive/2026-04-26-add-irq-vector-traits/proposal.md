# Add IRQ Vector Traits to Driver-Semantics Headers

## Why

Async HAL drivers in alloy need to install NVIC handlers at compile
time, but no emitted `<peripheral>.hpp` carries the IRQ vector number
today.  The single missing fact `kIrqNumbers[]` blocks **every** async
driver — UART, SPI, I2C, TIMER, DMA — because the user otherwise has
to hand-write `extern "C" void USART1_IRQHandler()` and remember which
peripheral it belongs to.

The IRQ data already exists in the canonical IR (`InterruptDescriptor`
with `name`, `number`, `peripheral_aliases`).  Today only the
`interrupt_bindings.hpp` consumer sees it; the per-peripheral
specialization headers do not.

This is one of the two highest-priority cross-cutting gaps surfaced
in the post-`add-uart-spi-tier-2-3-4-data` analysis.  modm exposes
the same fact via `Usart1::Interrupt` constants; alloy needs it via
`UartSemanticTraits<USART1>::kIrqNumbers`.

## What Changes

### Trait surface

Each peripheral whose specialization template is emitted today gains
a new constexpr `std::array<std::uint32_t, N> kIrqNumbers` listing
the NVIC vector indices that fire for that instance, in canonical
order:

- **UART / SPI / I2C / DAC / RTC / Watchdog / USB / SDMMC / QSPI /
  ETH / CAN** — single entry typically (`USART1_IRQn`); CAN may carry
  two (`FDCAN1_IT0_IRQn`, `FDCAN1_IT1_IRQn`).
- **TIMER** — split into `kUpdateIrqNumber`, `kCaptureIrqNumber`,
  `kBreakIrqNumber`, `kTriggerIrqNumber` (some chips share, some don't).
- **DMA** — per-channel `kIrqNumber` on `DmaChannelHwTraits`.
- **GPIO / PIO** — out of scope; EXTI lines stay in their own header.

Empty array (`size() == 0`) on the unspecialized template so consumer
code branching on `kIrqNumbers.size() > 0` compiles even on devices
where no NVIC line is admitted.

### Pipeline

- New row field `irq_numbers: tuple[int, ...]` on every
  `*SemanticRow` dataclass that owns a peripheral instance.
- New helper `_irq_numbers_for_peripheral(context, peripheral_name)`
  in `runtime_driver_semantics.py` walking `device.interrupt_bindings`
  filtered by `peripheral_aliases`.
- Specialization builders (`_uart_specialization_builder`,
  `_spi_specialization_builder`, ...) emit the new constexpr.
- `default_lines` in each `emit_runtime_driver_*_semantics_header`
  ships the safe-falsy empty array so existing fixtures stay
  byte-stable for any device whose interrupt_bindings haven't yet
  been admitted upstream.

### Goldens

Regenerate every `<peripheral>.hpp` golden across all 9 admitted
families.  Diff scope: ONE new constexpr line per specialization.

## Impact

Unblocks the alloy `add-async-uart-hal`, `add-async-spi-hal`,
`add-async-i2c-hal` drivers — the NVIC handler can now be installed
via `kIrqNumbers[0]` without touching any vendor header.
