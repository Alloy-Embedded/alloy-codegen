## ADDED Requirements

### Requirement: uart.hpp SHALL emit hardware-feature constexprs from Device.uart_peripherals

The emitted `uart.hpp` SHALL surface `kHardwarePresent = true` plus
`kBaseAddress`, `kFifoDepth`, `kTxSignalIdx`, `kRxSignalIdx`,
`kSupportsDma` on every `UartSemanticTraits` specialization whose
peripheral has a matching `UartPeripheralDescriptor` on the device IR.
These constexprs MUST default to safe falsy values on the unspecialized
template so consumer code that branches on `kHardwarePresent` compiles
even when no descriptor is admitted.

`kBaseAddress` MUST be sourced from the peripheral IR (which mirrors
the SVD) rather than the patch overlay so a hand-typed patch base
address can never disagree with the silicon spec.

#### Scenario: ESP32 UART0 emits the SVD-correct base address and 128-byte FIFO depth

- **WHEN** the pipeline emits `uart.hpp` for ESP32 classic
- **THEN** `UartSemanticTraits<PeripheralId::UART0>` carries
  `kHardwarePresent = true`, `kBaseAddress = 0x3FF40000u`,
  `kFifoDepth = 128u`, `kSupportsDma = true`

#### Scenario: ESP32-C3 UART0 emits the larger 256-byte FIFO depth

- **WHEN** the pipeline emits `uart.hpp` for ESP32-C3
- **THEN** `UartSemanticTraits<PeripheralId::UART0>` carries
  `kFifoDepth = 256u` (vs 128 on classic/S3)

### Requirement: spi.hpp SHALL emit hardware-feature constexprs from Device.spi_peripherals

The emitted `spi.hpp` SHALL surface `kHardwarePresent = true` plus
`kBaseAddress`, `kMaxClockHz`, `kHasIomuxFastPath`, IO-MUX fast-path
pin numbers (`kIomuxMosiPin`, `kIomuxMisoPin`, `kIomuxClkPin`,
`kIomuxCsPin`), GPIO-matrix signal indices (`kMosiOutSignal`,
`kMisoInSignal`, `kClkOutSignal`, `kCsOutSignal`), and `kSupportsDma`
on every `SpiSemanticTraits` specialization whose peripheral has a
matching `SpiPeripheralDescriptor` on the device IR. These constexprs
MUST default to safe falsy values on the unspecialized template.

#### Scenario: ESP32 SPI2 advertises its IO_MUX fast-path pins

- **WHEN** the pipeline emits `spi.hpp` for ESP32 classic
- **THEN** `SpiSemanticTraits<PeripheralId::SPI2>` carries
  `kHasIomuxFastPath = true`, `kIomuxMosiPin = 13`,
  `kIomuxMisoPin = 12`, `kIomuxClkPin = 14`,
  `kIomuxCsPin = 15`, `kMaxClockHz = 80000000u`

#### Scenario: ESP32-C3 SPI2 has no dedicated IO_MUX pins

- **WHEN** the pipeline emits `spi.hpp` for ESP32-C3
- **THEN** `SpiSemanticTraits<PeripheralId::SPI2>` carries
  `kHasIomuxFastPath = false`
