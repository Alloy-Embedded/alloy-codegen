# Tasks — add-irq-vector-traits

## Phase 1: Helper + row field

- [ ] 1.1 Add `_irq_numbers_for_peripheral(context, peripheral_name)`
      helper in `runtime_driver_semantics.py` walking
      `device.interrupt_bindings` filtered by `peripheral_aliases`.
- [ ] 1.2 Extend the following dataclasses with
      `irq_numbers: tuple[int, ...] = ()`:
      `UartSemanticRow`, `SpiSemanticRow`, `I2cSemanticRow`,
      `DacSemanticRow`, `RtcSemanticRow`, `WatchdogSemanticRow`,
      `UsbSemanticRow`, `SdmmcSemanticRow`, `QspiSemanticRow`,
      `EthSemanticRow`, `CanSemanticRow`.
- [ ] 1.3 Extend `TimerSemanticRow` with split fields:
      `update_irq_number`, `capture_irq_number`,
      `break_irq_number`, `trigger_irq_number` (each `int | None`).
- [ ] 1.4 Extend `DmaChannelHwRow` (or equivalent) with
      `irq_number: int | None`.

## Phase 2: Constexpr emission

- [ ] 2.1 Specialization builders emit
      `static constexpr std::array<std::uint32_t, N> kIrqNumbers`
      for each peripheral.
- [ ] 2.2 TIMER builder emits four scalars
      (`kUpdateIrqNumber`, `kCaptureIrqNumber`,
      `kBreakIrqNumber`, `kTriggerIrqNumber`); `0xFFFF'FFFFu`
      sentinel when absent.
- [ ] 2.3 `default_lines` in every
      `emit_runtime_driver_*_semantics_header` ships
      `kIrqNumbers = std::array<std::uint32_t, 0>{}`.

## Phase 3: Per-family wiring

- [ ] 3.1 `_st_uart_row` / `_st_spi_row` / `_st_i2c_row` / `_st_timer_row`
      consume the new helper.
- [ ] 3.2 `_microchip_*_row` and `_microchip_avr_*_row` ditto.
- [ ] 3.3 `_nxp_uart_row` / `_nxp_spi_row` ditto.
- [ ] 3.4 Stub branches for ESP32 / RP2040 / AVR-DA pull through
      via the same helper (interrupt_bindings present in IR).

## Phase 4: Tests + goldens

- [ ] 4.1 Per-family regression tests asserting
      `kIrqNumbers.size() >= 1` on every UART / SPI / I2C
      specialization with admitted interrupt bindings.
- [ ] 4.2 Regenerate all emit-fixture goldens.  Diff scope: ONE
      new constexpr per specialization.

## Phase 5: Spec + final checks

- [ ] 5.1 Spec delta in `specs/artifact-contract/spec.md`.
- [ ] 5.2 `openspec validate add-irq-vector-traits --strict` passes.
- [ ] 5.3 Full `pytest -q` passes; `ruff check` + format clean.
- [ ] 5.4 Archive entry notes that this unblocks
      `add-async-uart-hal` / `add-async-spi-hal` /
      `add-async-i2c-hal` in alloy.
