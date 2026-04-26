## ADDED Requirements

### Requirement: uart.hpp SHALL surface Tier 2/3/4 silicon facts

The emitted `uart.hpp` SHALL extend every populated
`UartSemanticTraits` specialization with the Tier 2/3/4 facts the
alloy concept-validated HAL needs at compile time: supported data
bits, parity options, stop-bit options, baud-clock sources, baud
oversampling options, FIFO trigger levels (when present), max baud
rate, mode-capability flags (LIN / IrDA / smartcard / half-duplex /
synchronous / auto-baud / wake-from-stop), and a typed
`kDmaBindings` array auto-derived from `device.dma_requests`. These
constexprs MUST default to safe falsy values
(`std::array<X, 0>{}` / `false` / `0`) on the unspecialized template
so consumer code that branches on them compiles even when no
descriptor is admitted.

#### Scenario: STM32G0 USART2 advertises LIN + 8x oversampling + FIFO triggers

- **WHEN** the pipeline emits `uart.hpp` for an STM32G0 device that
  admits USART2
- **THEN** `UartSemanticTraits<PeripheralId::USART2>` carries
  `kSupportsLin = true`, `kSupportsIrda = true`,
  `kSupportsSmartcard = true`, `kBaudOversamplingOptions.size() == 2`,
  `kFifoTriggerLevels.size() >= 4`, `kMaxBaudHz == 4'000'000u`,
  `kSupportedDataBits` contains `7`, `8`, and `9`

#### Scenario: AVR-DA USART0 carries no LIN and no DMA bindings

- **WHEN** the pipeline emits `uart.hpp` for an AVR-DA device
- **THEN** `UartSemanticTraits<PeripheralId::USART0>::kSupportsLin == false`
- **AND** `kDmaBindings.size() == 0` (AVR-DA has no DMA controller)
- **AND** `kSupportedDataBits` contains `5`, `6`, `7`, `8`, and `9`

#### Scenario: RP2040 UART0 surfaces 32-byte FIFO trigger options

- **WHEN** the pipeline emits `uart.hpp` for RP2040
- **THEN** `UartSemanticTraits<PeripheralId::UART0>::kFifoTriggerLevels`
  contains the five PL011 trigger levels (1/8, 2/8, 4/8, 6/8, 7/8)
- **AND** `kDmaBindings` contains exactly two entries (TX + RX) with
  the DREQ values from `device.dma_requests`

#### Scenario: Devices without admitted UART hardware see only safe defaults

- **WHEN** the pipeline emits `uart.hpp` for a device with no UART
  peripheral admitted
- **THEN** the unspecialized template carries `kSupportedDataBits`,
  `kSupportedParity`, `kSupportedStopBits`, `kBaudClockSources`,
  `kFifoTriggerLevels`, `kDmaBindings` all as `std::array<X, 0>{}`
- **AND** every `kSupports*` flag is `false`
- **AND** `kMaxBaudHz` is `0u`

### Requirement: spi.hpp SHALL surface Tier 2/3/4 silicon facts

The emitted `spi.hpp` SHALL extend every populated
`SpiSemanticTraits` specialization with the Tier 2/3/4 facts: a
typed `kSupportedFrameSizes` array (data-bits per frame), baud
prescaler options, FIFO threshold options (when present),
mode-capability flags (CRC / TI frame / I²S sub-mode / bidirectional
3-wire / LSB-first / NSS hardware management / Motorola frame), and
a typed `kDmaBindings` array auto-derived from
`device.dma_requests`. Defaults follow the same safe-falsy pattern
as UART.

#### Scenario: STM32G0 SPI1 advertises 4..16 bit frame sizes and CRC

- **WHEN** the pipeline emits `spi.hpp` for an STM32G0 device
- **THEN** `SpiSemanticTraits<PeripheralId::SPI1>::kSupportedFrameSizes`
  contains every integer from `4` to `16` inclusive
- **AND** `kSupportsCrc == true`, `kSupportsTiFrame == true`,
  `kSupportsMotorolaFrame == true`, `kSupportsLsbFirst == true`,
  `kSupportsNssHwManagement == true`,
  `kSupportsBidirectional3Wire == true`
- **AND** `kFifoThresholdOptions.size() == 2` (8-bit / 16-bit FRXTH)
- **AND** `kBaudPrescalerOptions.size() == 8` (BR=0..7 → /2 .. /256)

#### Scenario: AVR-DA SPI0 emits an 8-bit-only frame size and no CRC

- **WHEN** the pipeline emits `spi.hpp` for an AVR-DA device
- **THEN** `SpiSemanticTraits<PeripheralId::SPI0>::kSupportedFrameSizes`
  is the single-element array `{8}`
- **AND** `kSupportsCrc == false`, `kSupportsTiFrame == false`,
  `kSupportsI2sSubmode == false`
- **AND** `kSupportsLsbFirst == true` (DORD bit on AVR SPI)

#### Scenario: ESP32-S3 SPI2 advertises 1..32 bit frames and DMA bindings

- **WHEN** the pipeline emits `spi.hpp` for ESP32-S3
- **THEN** `SpiSemanticTraits<PeripheralId::SPI2>::kSupportedFrameSizes`
  contains every integer from `1` to `32` inclusive
- **AND** `kDmaBindings.size() == 2` (TX + RX, derived from the
  `gdma-spi2-tx` / `gdma-spi2-rx` entries in `dma_requests`)
- **AND** `kSupportsLsbFirst == true`,
  `kSupportsBidirectional3Wire == true`

#### Scenario: SPI peripherals with no DMA route emit empty kDmaBindings

- **WHEN** the pipeline emits `spi.hpp` for a device whose
  `device.dma_requests` carries no entry for the SPI peripheral
- **THEN** the corresponding specialization's `kDmaBindings` is
  `std::array<SpiDmaBinding, 0>{}`
- **AND** `kSupportsDma` (the existing flag) MAY remain `true` —
  hardware can support DMA even when no static binding is admitted
  yet; consumers that need a binding MUST gate on
  `kDmaBindings.size() > 0u`
