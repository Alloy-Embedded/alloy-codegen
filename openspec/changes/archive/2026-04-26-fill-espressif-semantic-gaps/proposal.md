# Fill Espressif Semantic Gaps (UART, SPI, ADC, Timer, PWM)

## Why

Espressif targets (ESP32 classic, ESP32-C3, ESP32-S3) are among the most popular
MCUs in the alloy target matrix. Yet virtually every semantic header except GPIO
is empty for these families:

| Semantic header | ESP32 classic | ESP32-C3 | ESP32-S3 |
|-----------------|---------------|----------|----------|
| uart.hpp        | Empty         | Empty    | Empty    |
| spi.hpp         | Empty         | Empty    | Empty    |
| adc.hpp         | Empty         | Empty    | Empty    |
| timer.hpp       | Empty         | Empty    | Empty    |
| pwm.hpp (MCPWM) | Empty         | N/A      | Empty    |
| dma.hpp         | Empty         | Empty    | Empty    |

Without these traits, alloy consumers on ESP32 cannot use any concept-validated
HAL peripheral — only the raw register board layer works. This severely limits
the value of alloy's zero-overhead HAL model on the most popular non-ARM MCU.

## What Changes

### UART traits (all three Espressif families)

ESP32 UART is GPIO-matrix routed. Each UART peripheral has:
- A base address (from SVD).
- TX/RX/RTS/CTS GPIO matrix signal indices (from `gpio_sig_map.h`).
- A FIFO depth (128 bytes on classic/S3, 256 bytes on C3 UART).
- DMA support flag (all Espressif UARTs support DMA RX; TX via linked-list DMA).

`UartSemanticTraits<UartId>`:
- `kPresent = true`
- `kBaseAddress`
- `kFifoDepth`
- `kTxSignalIndex`, `kRxSignalIndex` — GPIO matrix out/in indices.
- `kSupportsDma = true`

Families: ESP32 classic has UART0/1/2. C3 has UART0/1. S3 has UART0/1/2.

### SPI traits (all three families)

ESP32 exposes SPI2 (HSPI) and SPI3 (VSPI) for user firmware (SPI0/1 reserved
for flash). Each has:
- Base address.
- MOSI/MISO/CLK/CS GPIO matrix signal indices.
- Maximum clock speed (80 MHz for IO_MUX path, 40 MHz via GPIO matrix on classic;
  80 MHz on C3/S3 for both paths).
- DMA channel support (ESP32 classic: DMA ch1/2; C3/S3: GDMA).

`SpiSemanticTraits<SpiId>`:
- `kPresent = true`
- `kBaseAddress`
- `kMaxClockHz` — per-path maximum.
- `kMosiOutSignal`, `kMisoInSignal`, `kClkOutSignal`, `kCsOutSignal` — GPIO matrix.
- `kHasIoMuxFastPath` — `true` for SPI2 on all families (fixed pins bypass matrix).
- `kIoMuxMosiPin`, `kIoMuxMisoPin`, `kIoMuxClkPin` — fast-path pin numbers.
- `kSupportsDma = true`

### ADC traits (all three families)

ESP32 ADC is complex: ADC1 (8 channels, GPIO32–39 on classic), ADC2 (10 channels
but conflicts with Wi-Fi). C3 has ADC1 only (6 channels). S3 has ADC1+ADC2.

`AdcSemanticTraits<AdcId>`:
- `kPresent = true`
- `kChannelCount`
- `kResolutionBits` — 12 bits on all Espressif.
- `kConflictsWithWifi` — `true` for ADC2 on classic/S3.
- `kChannelPins` — constexpr array mapping channel index → GPIO pad number.

### Timer/Counter traits (ESP32 classic and S3)

ESP32 has two timer groups (TG0, TG1), each with two general-purpose timers and a
watchdog. `TimerSemanticTraits<TimerId>`:
- `kPresent = true`
- `kGroupIndex`, `kTimerIndex` — (0 or 1) × (0 or 1).
- `kBaseAddress`
- `kBits` — 64 on classic/S3, 54 on C3.
- `kClockSource` — `APB` (80 MHz typical) or `XTAL` (40 MHz).

### PWM / MCPWM traits (ESP32 classic and S3)

MCPWM is the high-resolution motor-control PWM on ESP32 classic and S3. C3 does
not have MCPWM (it has LEDC only). LEDC (LED Controller) is available on all.

`LedcSemanticTraits<LedcTimerId>`:
- `kPresent = true`
- `kChannelCount` — 8 high-speed + 8 low-speed on classic; 8 total on C3/S3.
- `kResolutionBits` — up to 20 bits.
- `kClockSource` — APB, REF_TICK, XTAL.
- `kOutputSignals` — GPIO matrix out signal indices per channel.

### DMA traits (all three families)

ESP32 classic has two DMA engines (SPI2-DMA and SPI3-DMA legacy style). C3 and
S3 use the Generalized DMA (GDMA) subsystem with 3 channels each.

`DmaSemanticTraits<DmaChannelId>`:
- `kPresent = true`
- `kChannelIndex`
- `kIsGdma` — `false` on classic, `true` on C3/S3.
- `kMaxTransferBytes` — 4095 on classic, 4095 on GDMA.
- `kPeripheralRequestLines` — constexpr map of peripheral → GDMA request line
  (used by alloy's `complete-async-hal` DMA engine).

## What Does NOT Change

- GPIO traits for Espressif — covered by `fill-gpio-semantic-gaps`.
- I2C traits for Espressif — covered by `fill-i2c-semantic-gaps`.
- USB traits for Espressif — covered by `add-usb-semantic-traits`.
- The `UartSemanticTraits`, `SpiSemanticTraits` struct layouts in alloy —
  codegen fills specializations only.

## Alternatives Considered

**Separate openspec per peripheral:** Splitting UART/SPI/ADC into individual
openspecs for Espressif would produce 5 tiny PRs with identical boilerplate
setup in the IR. Grouping by vendor keeps the normalizer extension in one place
while remaining reviewable (each peripheral type is a separate emitter class).
