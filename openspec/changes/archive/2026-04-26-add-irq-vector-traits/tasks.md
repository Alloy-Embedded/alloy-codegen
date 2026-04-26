# Tasks — add-irq-vector-traits

## Phase 1: Helper + row field

- [x] 1.1 Added `_irq_numbers_for_peripheral(context, peripheral_name)`
      helper in `runtime_driver_semantics.py` walking
      `device.interrupt_bindings`.  De-duplicates lines and yields
      them sorted ascending so goldens stay deterministic.
- [x] 1.2 Extended the following dataclasses with
      `irq_numbers: tuple[int, ...] = ()`:
      `UartSemanticRow`, `SpiSemanticRow`, `I2cSemanticRow`,
      `AdcSemanticRow` (bonus), `DacSemanticRow`, `RtcSemanticRow`,
      `WatchdogSemanticRow`, `UsbSemanticRow`, `SdmmcSemanticRow`,
      `QspiSemanticRow`, `EthSemanticRow`, `CanSemanticRow`.
- [x] 1.3 Extended `TimerSemanticRow` with split fields:
      `update_irq_number`, `capture_irq_number`,
      `break_irq_number`, `trigger_irq_number` (each `int | None`),
      plus a `_timer_irq_numbers_for_peripheral` classifier helper
      that splits `interrupt_bindings` by name suffix
      (UP / CC / COM / BRK / TRG).
- [ ] 1.4 DMA channel `irq_number` — **deferred**.  The DMA HW row
      type (`Rp2040DmaControllerHwDescriptor`) is RP2040-only at
      this point in the IR; per-channel IRQ surfacing would need a
      broader IR shape.  Tracked as a follow-up after
      `fill-dma-controller-hw-traits`.

## Phase 2: Constexpr emission

- [x] 2.1 Specialization builders emit
      `static constexpr std::array<std::uint32_t, N> kIrqNumbers`
      for UART / SPI / I2C / ADC / DAC / RTC / Watchdog / CAN /
      USB / ETH / QSPI / SDMMC.  Shared `_irq_numbers_lines`
      renderer.
- [x] 2.2 TIMER builder emits four scalars
      (`kUpdateIrqNumber`, `kCaptureIrqNumber`,
      `kBreakIrqNumber`, `kTriggerIrqNumber`) with `0xFFFFFFFFu`
      sentinel when the chip doesn't surface that vector, plus
      a de-duplicated `kIrqNumbers` union array.
- [x] 2.3 `default_lines` in every
      `emit_runtime_driver_*_semantics_header` ships
      `kIrqNumbers = std::array<std::uint32_t, 0>{}` (and the four
      sentinel scalars on the timer template).

## Phase 3: Per-family wiring

- [x] 3.1 UART/SPI extension helpers
      (`_uart_extension_for_peripheral`,
      `_spi_extension_for_peripheral`) include
      `irq_numbers=_irq_numbers_for_peripheral(...)` so every UART
      and SPI row across all 9 admitted families pulls IRQs
      automatically (ST / Microchip USART / Microchip UART /
      AVR-DA / NXP LPUART / RP2040 / ESP32 family stubs).
- [x] 3.2 I2C / ADC / TIMER / DAC / RTC / etc. row constructors —
      defaults to empty tuple.  Per-builder population happens
      naturally as later openspecs (TIMER Tier 2/3/4, I2C Tier
      2/3/4) add their own extension helpers.

## Phase 4: Tests + goldens

- [x] 4.1 Regression test
      `test_stm32g071rb_uart_traits_emit_irq_numbers` asserting
      `UartSemanticTraits<USART1>::kIrqNumbers == {{27u}}` and the
      unspecialized template ships an empty array.
- [x] 4.2 Regenerated emit-fixture goldens — one new constexpr per
      specialization across 18 headers in 9 families.

## Phase 5: Spec + final checks

- [x] 5.1 Spec delta in `specs/artifact-contract/spec.md` already
      landed during proposal authoring.
- [x] 5.2 `openspec validate add-irq-vector-traits --strict` passes.
- [x] 5.3 Full `pytest -q` passes (357 passed, 1 skipped).
      `ruff check` + format clean.
- [x] 5.4 Archive entry notes that this unblocks
      `add-async-uart-hal` / `add-async-spi-hal` /
      `add-async-i2c-hal` in alloy.
