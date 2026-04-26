# Complete RP2040 Semantic Trait Coverage

## Why

RP2040 is admitted to alloy-codegen and has generated artifacts, but semantic
trait coverage is severely incomplete. Current state:

| Semantic header | RP2040 populated? |
|-----------------|-------------------|
| gpio.hpp        | Empty             |
| uart.hpp        | Empty             |
| spi.hpp         | Empty             |
| i2c.hpp         | Empty (see `fill-i2c-semantic-gaps`) |
| adc.hpp         | Empty             |
| dma.hpp         | Partial (DREQ values only) |
| timer.hpp       | Partial (PWM slice periods) |
| pwm.hpp         | Partial (PWM slice periods) |
| usb.hpp         | Empty (see `add-usb-semantic-traits`) |
| pio.hpp         | Empty (see `define-pio-semantic-struct`) |

The partial entries in DMA/Timer/PWM are stubs with `kPresent=true` but missing
critical fields that alloy's HAL concept checks require.

Without these traits, every RP2040 HAL peripheral in alloy operates with runtime
fallbacks and no compile-time validation — the core differentiator of alloy over
mbed OS and libhal.

Note: I2C is handled in `fill-i2c-semantic-gaps`. USB in `add-usb-semantic-traits`.
PIO in `define-pio-semantic-struct`. This openspec covers GPIO, UART, SPI, ADC,
and completing DMA/Timer/PWM.

## What Changes

### GPIO traits (RP2040)

RP2040 GPIOs are routed via the SIO/GPIO pad controller and the IO_BANK0 function
select. Each GPIO (0–29) supports 9 functions (F1–F9): SPI, UART, I2C, PWM, SIO,
PIO0, PIO1, GPCK, USB.

`GpioSemanticTraits<GpioPinId::Gpio{N}>`:
- `kPresent = true`
- `kGpioNum = N`
- `kIsInputOnly = false` (all RP2040 GPIOs are bidirectional)
- `kFunctionCount = 9`
- `kFunctions` — constexpr array of `GpioFunction` enum values for this pin
  (e.g. GPIO0: {SPI0_RX, UART0_TX, I2C0_SDA, PWM0_A, SIO, PIO0, PIO1, GPCK, USB_OVCUR})
- `kSioIndex = N` — SIO register bit index (same as GPIO number on RP2040)

### UART traits

RP2040 has UART0 and UART1 with fixed pin assignments (each UART can be on one
of several pin pairs, configured via `IO_BANK0_GPIOx_CTRL`).

`UartSemanticTraits<UartId::Uart0>`:
- `kPresent = true`
- `kBaseAddress = 0x40034000`
- `kFifoDepth = 32`
- `kValidTxPins` — {0, 12, 16, 28} (GPIO numbers with UART0_TX function)
- `kValidRxPins` — {1, 13, 17, 29}
- `kDreqTx = 20`, `kDreqRx = 21`
- `kSupportsDma = true`

UART1: base=`0x40038000`, TX pins={4,8,20,24}, RX pins={5,9,21,25}, DREQ TX=22, RX=23.

### SPI traits

RP2040 has SPI0 and SPI1.

`SpiSemanticTraits<SpiId::Spi0>`:
- `kPresent = true`
- `kBaseAddress = 0x4003C000`
- `kMaxClockHz = 62_500_000` (PCLK/2, PCLK max 125 MHz)
- `kValidMosiPins` — {3, 7, 19, 23}
- `kValidMisoPins` — {0, 4, 16, 20}
- `kValidClkPins` — {2, 6, 18, 22}
- `kValidCsPins` — {1, 5, 17, 21}
- `kDreqTx = 16`, `kDreqRx = 17`

SPI1: base=`0x40040000`, pins shifted by 8, DREQ TX=18, RX=19.

### ADC traits

RP2040 ADC has 5 inputs: GPIO26–29 (4 external) + temperature sensor.

`AdcSemanticTraits<AdcId::Adc>`:
- `kPresent = true`
- `kBaseAddress = 0x4004C000`
- `kChannelCount = 5`
- `kResolutionBits = 12`
- `kChannelPins` — {26, 27, 28, 29, 255} (255 = internal temperature)
- `kDreq = 36`
- `kSupportsFifo = true`
- `kFifoDepth = 4`

### DMA completion (fill missing fields)

Current `DmaSemanticTraits<DmaChannelId::Ch{N}>` stubs have `kPresent=true` but
are missing:
- `kBaseAddress = 0x50000000`
- `kChannelCount = 12`
- `kMaxTransferCount = 0xFFFFFFFF` (32-bit count register)
- `kSupportsChaining = true`
- `kSupportsByteSwap = true`

### Timer/PWM completion (fill missing fields)

RP2040 has one system timer (`TIMER`) and 8 PWM slices (each slice = 2 channels A/B).

`TimerSemanticTraits<TimerId::Timer>`:
- `kPresent = true`
- `kBaseAddress = 0x40054000`
- `kBits = 64`
- `kDreq = 39` (ALARM0; ALARM1=40, ALARM2=41, ALARM3=42)
- `kAlarmCount = 4`

`PwmSemanticTraits<PwmId::Slice{N}>`:
- `kPresent = true`
- `kSliceIndex = N` (0–7)
- `kChannelA_Pin`, `kChannelB_Pin` — GPIO pin for each channel
  (Slice 0: A=GPIO0, B=GPIO1; Slice 1: A=GPIO2, B=GPIO3; …)
- `kCounterBits = 16`
- `kClockDivMin`, `kClockDivMax` — 1/256 to 256 (fractional divider)

## What Does NOT Change

- I2C, USB, PIO traits for RP2040 — handled in separate openspecs.
- Other families — RP2040-specific emitter only.

## Dependencies

- `fill-i2c-semantic-gaps` must be merged first (I2C traits for RP2040 there).
- `add-usb-semantic-traits` must be merged first (USB traits there).
- `define-pio-semantic-struct` must be merged first (PIO traits there).

## Alternatives Considered

**Merge all RP2040 gaps into one openspec:** Including I2C, USB, and PIO here
makes this openspec dependent-free but creates conflicts with the cross-family
openspecs for those peripherals. The split-by-peripheral approach allows parallel
PRs across families.
