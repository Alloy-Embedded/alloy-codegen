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
- [ ] 2.3 Unit tests covering: peripheral with no DMA route → empty tuple;
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
- [ ] 3.3 Extend `_uart_specialization_builder` + `_spi_specialization_builder`
      stub + non-stub branches to emit the new constexprs.  Stub branch
      keeps `kPresent = false` but emits the safe-default values
      (empty arrays, `false` flags, `0` max baud) so downstream
      `static_assert` checks compile.
- [ ] 3.4 Extend `emit_runtime_driver_uart_semantics_header` +
      `emit_runtime_driver_spi_semantics_header` `default_lines`
      (unspecialized template) with the safe defaults.  Existing
      fixtures stay byte-stable for any device whose patches haven't
      been updated yet.

## Phase 4: STM32 G0/F4 population

- [ ] 4.1 Update `_st_uart_row` to read IR fields and populate the row's
      Tier 2/3/4 tuples
- [ ] 4.2 Update `_st_spi_row` analogously
- [ ] 4.3 Add config blocks to `patches/st/stm32g0/devices/*.json`:
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
- [ ] 4.4 Same blocks for `patches/st/stm32f4/devices/*.json` (F4 USART
      has no FIFO trigger; SPI has BR=0..7 / DFF instead of DS)
- [ ] 4.5 Compile-test (`tests/compile_tests/test_stm32g0_uart_traits.cpp`)
      asserting `static_assert(UartSemanticTraits<PeripheralId::USART2>::kSupportsLin)`,
      `kBaudOversamplingOptions.size() == 2`, `kMaxBaudHz == 4'000'000u`

## Phase 5: SAME70 + iMXRT1060 population

- [ ] 5.1 Update `_microchip_uart_row` + `_microchip_usart_zw_row` to
      consume IR fields
- [ ] 5.2 Update `_microchip_spi_row` to consume IR fields
- [ ] 5.3 Update `_nxp_uart_row` (LPUART) + `_nxp_spi_row` (LPSPI) to
      consume IR fields
- [ ] 5.4 SAME70 device patches (USART0/1/2 + UART0..4):
      - USART: lin / irda / hw_handshake / wake = true
      - UART: data 8 bits only, parity N/E/O, stop 1, no LIN
      - max baud 8_000_000
      - SPI0/1: frame 8..16, lsb_first, motorola
- [ ] 5.5 iMXRT1060 device patches (LPUART1..8 + LPSPI1..4):
      - LPUART: data 7..10, lin, idle_line_detect, single_wire
      - LPSPI: frame 2..32 bits, lsb_first, ti, master_slave_mode
      - DMA bindings emerge from `device.dma_requests` (eDMA + DMAMUX)

## Phase 6: AVR-DA population

- [ ] 6.1 Update `_microchip_avr_uart_row` + `_microchip_avr_spi_row` to
      consume IR fields (AVR-DA has no DMA, no FIFO; tuples stay tight)
- [ ] 6.2 AVR-DA device patches:
      - USART: data 5..9, parity N/E/O, stop 1/2, baud-clock {CLK_PER},
        synchronous = true
      - SPI: frame 8 fixed, lsb_first, master_slave_mode
      - max baud per OSR (CLK_PER / 16; CLK_PER / 8 in DOUBLEX mode)

## Phase 7: ESP32 family population

- [ ] 7.1 Update the 3 Espressif UART/SPI builders to consume IR fields
- [ ] 7.2 family.json blocks for esp32 / esp32c3 / esp32s3 (one set per
      family, not per-device):
      - UART mode flags: irda, autobaud, half_duplex, wake_from_stop;
        lin only on S3
      - UART data 5..8, parity N/E/O, stop 1/1.5/2, baud-clock
        {APB, REF_TICK, XTAL, RC_FAST}
      - SPI frame 1..32 bits, lsb_first, half_duplex, gpio_matrix_routing
      - max UART baud 5_000_000
      - DMA bindings derive from existing `gdma-uart*` / `gdma-spi*`
        entries in `dma_requests`

## Phase 8: RP2040 population

- [ ] 8.1 Update RP2040 UART/SPI builders to consume IR fields
- [ ] 8.2 family.json blocks for rp2040:
      - UART (PL011): data 5..8, parity N/E/O, stop 1/2, FIFO 32-byte
        triggers 1/8 / 2/8 / 4/8 / 6/8 / 7/8, IrDA via SIRLP,
        half_duplex via direction switching
      - SPI (PL022): frame 4..16, lsb_first, motorola, ti, microwire
      - max UART baud 7_812_500 (PERI_CLK / 16)
      - DMA bindings derive from `dma-uart*-rx/tx` and `dma-spi*-rx/tx`
        in `dma_requests`

## Phase 9: Tests + goldens

- [ ] 9.1 Per-family regression tests asserting:
      - DMA bindings count + signal direction (TX vs RX)
      - mode flag values (e.g. STM32G0 USART2 LIN = true,
        AVR-DA USART0 LIN = false)
      - framesize / databits / parity / stop array contents match the
        family overlay
      - max baud is non-zero on every device with admitted UART/SPI
- [ ] 9.2 Regenerate 18 emit-fixture goldens (`tests/fixtures/emitted/
      */generated/runtime/devices/*/driver_semantics/{uart,spi}.hpp`).
      Diff scope: ONLY new constexpr lines + populated arrays; no
      register/field churn.
- [ ] 9.3 Update `metadata/capabilities.json` golden expectations for
      every family touching a `*_mode_flags` block (spec.md scenario:
      "uart-mode-lin = true" surfaces on capabilities sidecar for
      STM32G0 and SAME70 USART devices)

## Phase 10: Spec delta + final checks

- [ ] 10.1 Spec delta in `specs/artifact-contract/spec.md` extending the
      existing UART / SPI requirements with the new Tier 2/3/4
      surface scenarios
- [ ] 10.2 `openspec validate add-uart-spi-tier-2-3-4-data --strict`
      passes
- [ ] 10.3 Full `pytest -q` passes (no regressions across the 325-test
      baseline)
- [ ] 10.4 `ruff check src tests` + `ruff format --check src tests`
      both clean
- [ ] 10.5 Archive entry notes that this unblocks the alloy
      `add-async-uart-hal` and `add-async-spi-hal` HAL changes (which
      are gated on the new trait surface)
