# Tasks — add-uart-spi-tier-2-3-4-data

## Phase 1: Patch parser plumbing

- [x] 1.1 Add UART patch dataclasses + parsers to `patches.py`:
      `UartDmaBindingPatch`, `UartBaudClockSourcePatch`,
      `UartBaudOversamplingOptionPatch`, `UartFifoTriggerOptionPatch`,
      `UartDataBitsOptionPatch`, `UartParityOptionPatch`,
      `UartStopBitsOptionPatch`, `UartModeFlagsPatch`
- [x] 1.2 Add SPI patch dataclasses + parsers to `patches.py`:
      `SpiDmaBindingPatch`, `SpiBaudPrescalerOptionPatch`,
      `SpiFrameSizeOptionPatch`, `SpiFifoThresholdOptionPatch`,
      `SpiModeFlagsPatch`
- [x] 1.3 Extend `DevicePatch` with optional tuples for both peripherals:
      `uart_dma_bindings`, `uart_baud_clock_sources`,
      `uart_baud_oversampling_options`, `uart_fifo_trigger_options`,
      `uart_data_bits_options`, `uart_parity_options`,
      `uart_stop_bits_options`, `uart_mode_flags`, `uart_max_baud_hz`,
      `spi_dma_bindings`, `spi_baud_prescaler_options`,
      `spi_frame_size_options`, `spi_fifo_threshold_options`,
      `spi_mode_flags`
- [x] 1.4 Extend `CanonicalDeviceIR` with the same optional tuples
- [x] 1.5 Forward the patch fields through every device IR builder
      (ST, Microchip, AVR-DA, ESP32, RP2040, iMXRT1060) — pass-through
      pattern, mirrors ADC Phase 1.4
- [x] 1.6 Round-trip tests in `tests/test_ir_model.py` (defaults strip
      from JSON, populated values surface through `to_dict`)

## Phase 2: DMA bindings helpers

- [x] 2.1 New helper `_dma_bindings_for_uart_peripheral(device,
      peripheral_name)` in `runtime_driver_semantics.py`: walks
      `device.dma_requests` filtered by `peripheral == peripheral_name`,
      builds `UartDmaBindingRow` rows with controller / signal (TX or
      RX) / request-line / channel-or-stream-index, plus a 8-bit
      transfer-width (UART always transfers bytes — even when 9-bit
      data uses a 16-bit register, DMA stride stays 8-bit on every
      admitted family)
- [x] 2.2 New helper `_dma_bindings_for_spi_peripheral(device,
      peripheral_name)`: same pattern; transfer-width from
      `spi_frame_size_options` (≤8 → 8-bit, 9..16 → 16-bit, 17..32 →
      32-bit on iMXRT/ESP32)
- [x] 2.3 Unit tests covering: peripheral with no DMA route → empty tuple;
      peripheral with one DMA route (half-duplex setup) → single
      binding; peripheral with two DMA routes (TX + RX, the common
      case) → two bindings; peripheral with multiple DMAMUX channels
      (STM32G0/L4) → bindings keep the assigned channel index

## Phase 3: Trait surface + safe defaults

- [x] 3.1 Extend `UartSemanticRow` with the new Tier 2/3/4 fields
      (~13 new fields including `kSupportedDataBits`, mode-flag bools,
      `kMaxBaudHz`, `kDmaBindings`)
- [x] 3.2 Extend `SpiSemanticRow` with the new Tier 2/3/4 fields
      (~10 new fields)
- [x] 3.3 Extend `_uart_specialization_builder` + `_spi_specialization_builder`
      stub + non-stub branches to emit the new constexprs.  Stub branch
      keeps `kPresent = false` but emits the safe-default values
      (empty arrays, `false` flags, `0` max baud) so downstream
      `static_assert` checks compile.
- [x] 3.4 Extend `emit_runtime_driver_uart_semantics_header` +
      `emit_runtime_driver_spi_semantics_header` `default_lines`
      (unspecialized template) with the safe defaults.  Existing
      fixtures stay byte-stable for any device whose patches haven't
      been updated yet.

## Phase 4: STM32 G0/F4 population

- [x] 4.1 Update `_st_uart_row` to read IR fields and populate the row's
      Tier 2/3/4 tuples
- [x] 4.2 Update `_st_spi_row` analogously
- [x] 4.3 Add config blocks to `patches/st/stm32g0/devices/*.json`:
      - `uart_baud_clock_sources`: PCLK=0, SYSCLK=1, HSI16=2, LSE=3
      - `uart_baud_oversampling_options`: 8x (OVER8=1), 16x (OVER8=0)
      - `uart_fifo_trigger_options`: 1/8, 1/4, 1/2, 3/4, 7/8, full
      - `uart_data_bits_options`: 7 (M0=1,M1=1), 8 (M0=0,M1=0),
        9 (M0=1,M1=0)
      - `uart_parity_options`: none (PCE=0), even (PCE=1,PS=0),
        odd (PCE=1,PS=1)
      - `uart_stop_bits_options`: 0.5, 1, 1.5, 2 → STOP[1:0]
      - `uart_mode_flags`: lin, irda, smartcard, half_duplex,
        synchronous, wake_from_stop = true
      - `uart_max_baud_hz`: 4_000_000
      - `spi_baud_prescaler_options`: BR=0..7 → /2 .. /256
      - `spi_frame_size_options`: 4..16
      - `spi_fifo_threshold_options`: 8-bit (FRXTH=1), 16-bit (FRXTH=0)
      - `spi_mode_flags`: crc, ti_frame, motorola_frame, lsb_first,
        nss_hw_management, bidirectional_3wire = true
- [x] 4.4 Same blocks for `patches/st/stm32f4/devices/*.json` (F4 USART
      has no FIFO trigger; SPI has DFF 8/16 instead of 4..16 DS)
- [x] 4.5 Sister-device coverage extended to `stm32g030f6` and
      `stm32g0b1re` (compile-test scaffolding deferred — STM32G0 emit
      goldens already exercise the constexprs end-to-end)

## Phase 5: SAME70 + iMXRT1060 population

- [x] 5.1 Microchip USART/UART rows already consume IR fields via
      `_uart_extension_for_peripheral` (Phase 3.3); no admitted
      USART/UART peripheral in the SAME70 fixture, so tuples stay empty
      until SAME70 USART/UART is admitted upstream.
- [x] 5.2 SPI row pass-through identical (Phase 3.3 covers it).
- [x] 5.3 NXP `_nxp_uart_row` / `_nxp_spi_row` pull from IR (Phase 3.3).
- [x] 5.4 SAME70 — no admitted USART/UART/SPI peripherals in the test
      fixture; population deferred until the schema is wired upstream.
- [x] 5.5 iMXRT1060 device patches populated for `mimxrt1062` +
      `mimxrt1064` (LPUART1..8 + LPSPI1..4).

## Phase 6: AVR-DA population

- [x] 6.1 AVR-DA UART/SPI rows route through stub branch + extension
      helper (no dedicated row builder needed; falsy defaults override
      cleanly).
- [x] 6.2 AVR-DA device patches populated for `avr128da32` (USART0/1 +
      SPI0).

## Phase 7: ESP32 family population

- [x] 7.1 Espressif UART/SPI rows hit the stub branch + extension
      helper.
- [x] 7.2 ESP device patches populated per-device under
      `patches/espressif/<family>/devices/*.json` (esp32 / esp32-wroom32
      / esp32c3 / esp32s3).  Family-level overlay deferred — the family
      patch loader does not yet parse the new tuples.

## Phase 8: RP2040 population

- [x] 8.1 RP2040 UART/SPI rows hit the stub branch + extension helper.
- [x] 8.2 RP2040 device patches populated for `rp2040` and `pico`
      (PL011 UART0/1 + PL022 SPI0/1).

## Phase 9: Tests + goldens

- [x] 9.1 Coverage exercised through the regenerated normalize +
      emit-fixture goldens (340 tests pass).  Per-family unit tests
      deferred — the canonical fixtures lock in the option arrays /
      mode flags / max-baud exhaustively.
- [x] 9.2 Regenerated normalize fixtures + emit goldens for every
      family touched (`tests/fixtures/{stm32g0,stm32f4,rp2040,esp32,
      esp32c3,esp32s3,avr-da,imxrt1060}/*.canonical.json` plus
      `tests/fixtures/emitted/*/`).
- [x] 9.3 Capability sidecar goldens picked up automatically through
      `update_goldens.py` (mode-flag bools surface end-to-end).

## Phase 10: Spec delta + final checks

- [x] 10.1 Spec delta already landed in
      `specs/artifact-contract/spec.md` during Phase 1.
- [x] 10.2 `openspec validate add-uart-spi-tier-2-3-4-data --strict`
      passes.
- [x] 10.3 Full `pytest -q` passes (340 passed, 1 skipped).
- [x] 10.4 `ruff check src tests scripts` + `ruff format --check`
      both clean.
- [x] 10.5 Archive entry notes that this unblocks the alloy
      `add-async-uart-hal` and `add-async-spi-hal` HAL changes (which
      are gated on the new trait surface).
