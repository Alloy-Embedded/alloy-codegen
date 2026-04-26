# Driver-Semantics Roadmap

Implementation order for the OpenSpec changes that bring every emitted
`<peripheral>.hpp` up to ADC-gold-standard depth.  The ADC reference
header in `tests/fixtures/emitted/stm32g0/.../driver_semantics/adc.hpp`
is the target — option arrays + capability flags + calibration data +
external triggers + DMA bindings + max-clock + per-channel pin maps.

The order is dictated by what the **alloy async HAL drivers** consume
first, not by which peripheral has the largest gap.

## Stage 0 — done

| Change | Status |
|---|---|
| `add-adc-tier-2-3-4-data` | ✅ archived |
| `add-uart-spi-tier-2-3-4-data` | ✅ archived (2026-04-26) |
| `fill-i2c-semantic-gaps` | ✅ archived (Tier 1 + clock-mux + pinmux) |
| `fill-gpio-semantic-gaps` | ✅ archived (alt-fn lists) |

## Stage 1 — cross-cutting unblockers (P0)

These three are prerequisites for *every* async HAL driver in alloy.
Land them in this order so the consumer can stand up a full
async-UART driver immediately after the third merges.

| # | Change | What it adds | Why first |
|---|---|---|---|
| 1 | `add-irq-vector-traits` | `kIrqNumbers[]` on UART/SPI/I2C/TIMER/DMA traits + emitter wiring | Async drivers need NVIC vector ID at compile time to install handlers |
| 2 | `add-peripheral-dma-cross-references` | `kDmaBindings[]` on UART/SPI/I2C/TIMER traits — back-references into the existing `dma.hpp` binding ID space | DMA info already exists in the IR; today only `dma.hpp` knows `USART1_TX`. Drivers need `UartSemanticTraits<USART1>::kDmaBindings` |
| 3 | `add-kernel-clock-traits` | `kKernelClockSourceField` (RCC mux ref) + `kMaxClockHz` on UART/SPI/I2C/QSPI/SDMMC | modm-style baud resolver `Baudrate<f_pclk, 115200>` needs both the clock-source ref and the max input |

## Stage 2 — peripheral-tier completions (P1)

Mirrors of `add-uart-spi-tier-2-3-4-data` for the next set of
peripherals the alloy HAL roadmap targets.

| # | Change | Mirrors | Notes |
|---|---|---|---|
| 4 | `add-i2c-tier-2-3-4-data` | UART/SPI Tier 2/3/4 | Also fixes the broken STM32G0 emission (`kI2cSemanticPeripherals = {}`) |
| 5 | `fill-gpio-tier-1-fields` | n/a (Tier-1 activation) | STM32 GPIO mode/pull/speed/output-type fields are `kInvalidFieldRef` today; populate them |
| 6 | `add-timer-tier-2-3-4-data` | UART/SPI Tier 2/3/4 | Prescaler ranges, trigger sources (ITRx/ETR), DMA bindings, IRQ split (UP/CC/BRK) |

## Stage 3 — secondary peripherals (P2)

Build on Stage 2 outputs.  Lower priority because no async driver
in alloy is gated on them yet, but cheap to land once Stage 2 is in.

| # | Change | Notes |
|---|---|---|
| 7 | `add-pwm-tier-2-3-4-data` | After TIMER — adds prescaler range, deadtime options, break inputs |
| 8 | `fill-dma-controller-hw-traits` | Channel count, burst sizes, max-transfer, priority levels.  `dma.hpp` controller side is mostly stubbed today |

## Stage 4 — niche peripherals (P3, on demand)

Defer until the corresponding alloy HAL driver is on the roadmap.
Each one would mirror the Stage 2 pattern.

- `add-dac-tier-2-3-4-data` — resolution, triggers, waveform generators
- `add-can-tier-2-3-4-data` — filter banks, FIFO depths, FD vs classic, max bitrate
- `add-rtc-tier-2-3-4-data` — clock sources, alarm count, sub-second bits, tamper
- `add-watchdog-tier-2-3-4-data` — clock source, prescaler, reload bits, timeout range
- `add-usb-tier-2-3-4-data` — speeds, endpoint-buffer kind, max packet sizes (also needs to fix G0 emission)
- `add-eth-tier-2-3-4-data` — descriptor counts, PHY clock, PTP flag, checksum offload
- `add-sdmmc-tier-2-3-4-data` — clock dividers, UHS modes, ADMA flags, voltages
- `add-qspi-tier-2-3-4-data` — line counts, address sizes, dummy cycles, mem-mapped base

## Cross-references that don't need a separate OpenSpec

These will be addressed inside the Stage 1–2 changes above:

- ADC currently emits `kHasDma = false` / `kDmaBindings = {}` even
  though ADC has DMA — fixed inside `add-peripheral-dma-cross-references`
  (Stage 1, item 2).
- STM32G0 has empty specialization arrays for I2C, USB, QSPI, SDMMC.
  I2C is fixed in Stage 2 (`add-i2c-tier-2-3-4-data`).  USB / QSPI /
  SDMMC are Stage 4.

## Ordering rule of thumb

If two changes are independent (e.g. `add-irq-vector-traits` and
`add-peripheral-dma-cross-references`), prefer the one that
unblocks the most consumer drivers per line of patch JSON.  Stage 1
items 1–3 are deliberately ordered for that reason: IRQ vectors
unblock 5 driver kinds; DMA cross-refs unblock 4; kernel-clock
unblocks 5 *but* requires the runtime-lite clock tree to consume
the new field-ref shape, so it ships last in Stage 1.
