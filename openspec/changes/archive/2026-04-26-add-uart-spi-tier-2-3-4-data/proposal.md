# Add UART + SPI Tier 2/3/4 Data Across Admitted Families

## Why

`UartSemanticTraits` and `SpiSemanticTraits` ship the register/field
plumbing today, plus the hardware-feature constexprs that landed via
`fill-espressif-semantic-gaps` (`kHardwarePresent`, `kBaseAddress`,
`kFifoDepth`, `kSupportsDma`, …) and `complete-rp2040-semantics`
(`kValidTxPins`, `kValidMosiPins`, `kDreqTx`, `kDreqRx`, …).  But every
non-trivial alloy HAL feature beyond "set baud and write a byte" is
blocked because the higher-tier data is missing:

- **DMA bindings** — `kSupportsDma=true` says *can*, not *which channel
  / which trigger / what transfer width*.  `device.dma_requests` already
  carries the routing for ADC; the same data exists for UART/SPI but no
  builder consumes it for these peripherals yet.
- **Mode capability flags** — LIN, IrDA, smartcard, half-duplex,
  synchronous, auto-baud (UART); CRC, TI frame format, I²S sub-mode,
  NSS hardware management, bidirectional 3-wire (SPI).  Today the
  generated traits give the consumer no way to ask "does this UART
  support LIN break detection?" at compile time.
- **Per-peripheral baud / clock options** — `kFifoDepth` is uniform per
  family, but `kMaxBaudHz`, `kBaudClockSourceOptions` (PCLK / HSI /
  LSE / SYSCLK) and `kBaudOversamplingOptions` (8x / 16x) vary per
  family and steer the alloy clock tree validator.
- **FIFO / wake / threshold options** — STM32G0/F4 USART FIFO has
  configurable trigger levels (1/4, 1/2, 3/4, full); STM32 SPI has a
  receive FIFO threshold (FRXTH); RP2040 PL011 UART has 32-byte FIFO
  with FF/HF/QF/EF triggers; SAME70 USART has receive timeout.  None
  of these are surfaced today.
- **Frame / character options** — UART data bits (5 / 6 / 7 / 8 / 9),
  parity (none / even / odd / mark / space), stop bits (½ / 1 / 1½ / 2);
  SPI frame size (4..16 on STM32, fixed 8/16 on others), bit ordering,
  CPOL/CPHA combinations admitted.

Without these, `UartController<T>::lin_mode<>()` /
`SpiBus<T>::with_crc<Polynomial>()` / `Uart::oversample<8x>()` can't
even be exposed, let alone compile.  This change repeats the
`add-adc-tier-2-3-4-data` pattern: opt-in patch blocks, per-family
data population, builder integration, DMA bindings auto-derived from
`device.dma_requests`, goldens regenerated.

## What Changes

### IR plumbing

New patch dataclasses in `patches.py` (analogous to the seven added by
`add-adc-tier-2-3-4-data`):

**UART:**
- `UartDmaBindingPatch` *(auto-derived; here for symmetry / overrides)*
- `UartBaudClockSourcePatch` (clock-source enum value + Hz)
- `UartBaudOversamplingOptionPatch` (8x / 16x field values)
- `UartFifoTriggerOptionPatch` (1/4 / 1/2 / 3/4 / full level → field)
- `UartDataBitsOptionPatch` (5 / 6 / 7 / 8 / 9 → field combo)
- `UartParityOptionPatch` (none / even / odd → PCE+PS field combo)
- `UartStopBitsOptionPatch` (0.5 / 1 / 1.5 / 2 → STOP field)
- `UartModeFlagsPatch` (single block: lin / irda / smartcard /
  half_duplex / synchronous / auto_baud / wake_from_stop)

**SPI:**
- `SpiDmaBindingPatch` *(auto-derived)*
- `SpiBaudPrescalerOptionPatch` (BR field → divisor)
- `SpiFrameSizeOptionPatch` (4..16 bits → DS / DFF field)
- `SpiFifoThresholdOptionPatch` (FRXTH 8-bit / 16-bit on STM32)
- `SpiModeFlagsPatch` (crc / ti_frame / i2s_submode /
  bidirectional_3wire / lsb_first / nss_hw_management / motorola_frame)

`DevicePatch` gains the corresponding optional tuples; `CanonicalDeviceIR`
carries them through every device builder
(`_build_st_device_ir`, `_build_microchip_device_ir`,
`_build_avr_da_device_ir`, `_build_esp32_device_ir`,
`_build_rp2040_device_ir`, `_build_imxrt1060_device_ir`).

### Trait surface (delta)

`UartSemanticTraits` gains:
- `kSupportedDataBits` — `std::array<UartDataBits, N>`
- `kSupportedParity` — `std::array<UartParity, N>`
- `kSupportedStopBits` — `std::array<UartStopBits, N>`
- `kBaudClockSources` — `std::array<UartBaudClockSource, N>`
- `kBaudOversamplingOptions` — `std::array<std::uint8_t, N>` (8 / 16)
- `kFifoTriggerLevels` — `std::array<UartFifoTrigger, N>`
- `kSupportsLin` / `kSupportsIrda` / `kSupportsSmartcard` /
  `kSupportsHalfDuplex` / `kSupportsSynchronous` / `kSupportsAutoBaud` /
  `kSupportsWakeFromStop` — `bool` flags
- `kMaxBaudHz` — `std::uint32_t`
- `kDmaBindings` — `std::array<UartDmaBinding, N>`

`SpiSemanticTraits` gains:
- `kSupportedFrameSizes` — `std::array<std::uint8_t, N>` (bits)
- `kBaudPrescalerOptions` — `std::array<SpiBaudPrescaler, N>`
- `kFifoThresholdOptions` — `std::array<SpiFifoThreshold, N>`
- `kSupportsCrc` / `kSupportsTiFrame` / `kSupportsI2sSubmode` /
  `kSupportsBidirectional3Wire` / `kSupportsLsbFirst` /
  `kSupportsNssHwManagement` / `kSupportsMotorolaFrame` — `bool` flags
- `kDmaBindings` — `std::array<SpiDmaBinding, N>`

Each new field defaults to `std::array<X, 0>{}` / `false` / `0` on the
unspecialized template so existing fixtures stay byte-stable.

### Builder integration

- Each per-family UART/SPI builder reads the new IR fields and populates
  the corresponding Tier 2/3/4 tuples on the `UartSemanticRow` /
  `SpiSemanticRow` it returns.
- A new `_dma_bindings_for_uart_peripheral` /
  `_dma_bindings_for_spi_peripheral` helper auto-derives `kDmaBindings`
  from `device.dma_requests` filtered by peripheral name (mirrors the
  ADC `_dma_bindings_for_peripheral` helper added in
  `add-adc-tier-2-3-4-data`).

### Per-family data population

| Family | UART data | SPI data |
|--------|-----------|----------|
| `st/stm32g0` | USART1/2/3/4 — DMA via DMA1/DMAMUX, FIFO 8-byte trigger 1/4-1/2-3/4-full, data 7/8/9 bits, parity N/E/O, stop ½/1/1½/2, oversampling 8x/16x, baud-clock {PCLK, SYSCLK, HSI16, LSE}, max baud 4 Mbps, modes: lin, irda, smartcard, half-duplex, synchronous, wake | SPI1/2 — DMA via DMA1/DMAMUX, FIFO 8-byte FRXTH 8/16-bit, frame 4..16 bits, BR /2../256, modes: crc, ti, motorola, lsb_first, nss_hw, bidirectional |
| `st/stm32f4` | USART1/2/6 — DMA via DMA1/2 (stream/channel), no FIFO trigger admitted, data 8/9 bits, parity N/E/O, stop 1/2, oversampling 8x/16x, baud-clock {PCLK1/2}, max baud 10.5 Mbps, modes: lin, irda, smartcard, half-duplex, synchronous | SPI1/2/3/4/5 — DMA, no FIFO trigger, frame 8/16 bits, BR /2../256, modes: crc, ti, motorola, lsb_first, nss_hw, bidirectional, i2s_submode (SPI2/3 on F405/F407 only) |
| `microchip/same70` | USART0/1/2 + UART0..4 — DMA via XDMAC, no FIFO, data 5/6/7/8/9 (USART) or 8 (UART), parity N/E/O/Mark/Space, stop 1/1.5/2, oversampling 8/16, baud-clock {PCK4, MCK, MCK/DIV}, max baud 8 Mbps, modes: lin, irda, hw_handshake (USART), wake | SPI0/1 — DMA via XDMAC, frame 8..16 bits, modes: lsb_first, motorola; PCS on PSDEC mode |
| `nxp/imxrt1060` | LPUART1..8 — DMA via eDMA + DMAMUX, FIFO 4-byte (LPUART), data 7/8/9/10, parity N/E/O, stop 1/2, oversampling 4..32 (OSR field), baud-clock {OSC24M / IPG / SYS_CLK}, max baud 24 Mbps, modes: lin, idle_line_detect, single_wire | LPSPI1..4 — DMA via eDMA, FIFO 16 deep, frame 2..32 bits, modes: lsb_first, ti, master_slave_mode |
| `microchip/avr-da` | USART0..3 — no DMA (AVR-DA has no DMA controller), no FIFO, data 5..9, parity N/E/O, stop 1/2, oversampling N/A, baud-clock {CLK_PER}, max baud per OSR, modes: synchronous, IrDA-via-SOFTUART | SPI0/1 — no DMA, frame 8 bits fixed, modes: lsb_first, master_slave_mode (no CRC, no TI) |
| `raspberrypi/rp2040` | UART0/1 — DMA via DREQ TX/RX, FIFO 32-byte trigger 1/8/2/8/4/8/6/8/7/8, data 5..8, parity N/E/O, stop 1/2, no oversampling field (PL011 fixed 16x), baud-clock {PERI_CLK = 125MHz/XOSC}, max baud 7.8 Mbps, modes: half_duplex, IrDA via SIRLP | SPI0/1 — DMA via DREQ, FIFO 8-deep, frame 4..16 bits, modes: lsb_first, motorola, ti, microwire (PL022) |
| `espressif/esp32` `esp32c3` `esp32s3` | UART0..2 — DMA via UHCI / GDMA, FIFO 128/256-byte threshold field, data 5..8, parity N/E/O, stop 1/1.5/2, baud-clock {APB / REF_TICK / XTAL / RC_FAST}, max baud 5 Mbps, modes: irda, autobaud, lin (S3 only), half-duplex, wake-from-light-sleep | SPI2/3 (host) — DMA via SPI_DMA / GDMA, FIFO 64 bytes, frame 1..32 bits, modes: lsb_first, half_duplex, gpio_matrix_routing, lcd_camera_submode (S3) |

### Cross-cutting

- **DMA bindings** auto-derive in every existing builder by walking
  `device.dma_requests` filtered by UART/SPI peripheral — mirrors the
  ADC pattern; no per-family code beyond the helpers.
- **Mode flags** ride on a single `*ModeFlagsPatch` block per peripheral
  (one per UART, one per SPI) so per-device patches stay terse.

## What Does NOT Change

- I²C tier-2 data — covered by `fill-i2c-semantic-gaps`.
- USB / PIO / GPIO trait completion — separate openspecs.
- The struct layout of `UartSemanticTraits` / `SpiSemanticTraits` in
  alloy — codegen fills new specialization fields only; the consumer
  side adds the typed enums (`UartParity`, `SpiBaudPrescaler`, …) in
  parallel.
- ESP32 ADC2 / Wi-Fi conflict modelling — out of scope (different
  contention layer).
- Runtime baud-rate computation — lives in alloy consumer; codegen
  only ships the static silicon facts.

## Impact

- Affected specs: `artifact-contract` (delta extends the existing
  Tier-1-emitted UART / SPI requirements with concrete population
  scenarios, mirrors the `add-adc-tier-2-3-4-data` delta shape)
- Affected code:
  - `src/alloy_codegen/patches.py` — ~14 new patch dataclasses + parsers
  - `src/alloy_codegen/ir/model.py` — extend `CanonicalDeviceIR` with
    ~14 new optional tuples
  - `src/alloy_codegen/stages/normalize.py` — forward patch fields to
    IR in every device builder (same pass-through pattern as ADC)
  - `src/alloy_codegen/runtime_driver_semantics.py` — extend
    `UartSemanticRow` / `SpiSemanticRow` with the new fields, plumb
    through every per-family builder, add two new
    `_dma_bindings_for_*_peripheral` helpers, extend
    `_uart_specialization_builder` / `_spi_specialization_builder`
    + their `default_lines` to emit the new constexprs
  - 18 device.json patches expanded with the new opt-in blocks
    (9 admitted families × 2 peripherals — UART + SPI)
  - Tests: per-family regression for DMA bindings, mode flags,
    framesize / databits / parity / stop arrays, baud sources, max
    baud, FIFO trigger options
  - 18 emit-fixture goldens regenerated (uart.hpp + spi.hpp per device)

## Implementation Phases

| Phase | Scope | Deliverable |
|-------|-------|-------------|
| 1 | Patch parser plumbing | ~14 new dataclasses, `DevicePatch` extended, `CanonicalDeviceIR` extended, every device IR builder forwards the fields |
| 2 | DMA bindings helpers | `_dma_bindings_for_uart_peripheral` + `_dma_bindings_for_spi_peripheral` + transfer-width inference + tests (mirrors ADC Phase 2) |
| 3 | UART / SPI row + spec_builder + default_lines extensions | Trait surface lands with safe-default emission across every existing fixture (no-op until per-family blocks ship) |
| 4 | STM32 G0/F4 population | device patches + `_st_uart_row` / `_st_spi_row` consuming them |
| 5 | SAME70 + iMXRT1060 population | device patches + `_microchip_uart_row` / `_microchip_spi_row` / `_nxp_uart_row` / `_nxp_spi_row` consuming |
| 6 | AVR-DA population | device patch + `_microchip_avr_uart_row` / `_microchip_avr_spi_row` consuming |
| 7 | ESP32 family population | family.json blocks (UART/SPI mode flags + baud sources + frame sizes) + 3 ESP UART/SPI builders consuming; DMA bindings derive automatically |
| 8 | RP2040 population | family.json blocks + RP2040 UART/SPI builders consuming |
| 9 | Tests + goldens (18 fixtures regenerated) |
| 10 | Spec delta + final checks (validate --strict + full pytest) |

## Non-Goals

- LIN frame ID filtering / smartcard ETU programming — runtime config,
  not silicon facts.
- SPI quad / octal modes — covered by the QSPI semantic trait, not SPI.
- I²S full duplex / TDM — separate `add-i2s-semantic-traits` (not
  proposed yet).
- Runtime baud calculation algorithms — alloy consumer concern.
- ESP32 hardware flow-control RTS/CTS GPIO selection at runtime —
  belongs in connector model, not the trait surface.
- DMAMUX runtime reconfiguration — `kDmaBindings` stays static, same
  posture as ADC.
