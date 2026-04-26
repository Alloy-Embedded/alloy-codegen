# Tasks: Complete RP2040 Semantic Trait Coverage

Depends on: `fill-i2c-semantic-gaps`, `add-usb-semantic-traits`, `define-pio-semantic-struct`.

## 1. Data overlays

- [ ] 1.1 Create `patches/raspberrypi/rp2040/gpio_functions.json`: for each GPIO
      0–29, list the 9 function names in order (F1–F9). Source from RP2040 datasheet
      Table 2-3 (IO Function Table). Machine-readable, used by the GPIO emitter.
- [ ] 1.2 Create `patches/raspberrypi/rp2040/uart_pins.json`: UART0 and UART1
      valid TX/RX/CTS/RTS pin lists. Source: datasheet Table 2-5.
- [ ] 1.3 Create `patches/raspberrypi/rp2040/spi_pins.json`: SPI0 and SPI1
      MOSI/MISO/CLK/CS valid pin lists.
- [ ] 1.4 Create `patches/raspberrypi/rp2040/adc.json`: channel → GPIO mapping,
      FIFO depth, DREQ value.
- [ ] 1.5 Create `patches/raspberrypi/rp2040/timer.json`: base address, alarm
      count, DREQ values for each alarm.
- [ ] 1.6 Create `patches/raspberrypi/rp2040/pwm.json`: for each slice 0–7,
      channel A and B GPIO numbers.

## 2. Normalizer extensions

- [ ] 2.1 Extend RP2040 normalizer (`src/alloy_codegen/sources/rp2040_sdk.py`
      or `pico_sdk.py`) to load all new JSON overlays and populate the respective
      IR descriptor lists: `Device.gpio_pins`, `Device.uart_peripherals`,
      `Device.spi_peripherals`, `Device.adc_units`, `Device.timer_units`,
      `Device.pwm_slices`.
- [ ] 2.2 Fill `Device.dma_channels` with 12 `DmaChannelDescriptor`s. Base address
      `0x50000000`, `is_gdma=false`, `max_transfer_count=0xFFFFFFFF`,
      `supports_chaining=true`. DREQ values from existing partial RP2040 DMA data.
- [ ] 2.3 Validate: normalizer asserts 30 GPIO pins populated, 2 UARTs, 2 SPIs,
      1 ADC with 5 channels, 1 timer with 4 alarms, 8 PWM slices.

## 3. Emitters

- [ ] 3.1 `RP2040GpioSemanticEmitter.emit(device)` → `gpio.hpp`. Reads `gpio_pins`
      IR list. For each GPIO, emits `GpioSemanticTraits<GpioPinId::Gpio{N}>` with
      `kFunctions` constexpr array populated from `gpio_functions.json`.
- [ ] 3.2 `RP2040UartSemanticEmitter.emit(device)` → `uart.hpp`. Two specializations
      (Uart0, Uart1). `kValidTxPins` and `kValidRxPins` are constexpr arrays.
- [ ] 3.3 `RP2040SpiSemanticEmitter.emit(device)` → `spi.hpp`. Two specializations.
- [ ] 3.4 `RP2040AdcSemanticEmitter.emit(device)` → `adc.hpp`. Single ADC unit.
      `kChannelPins` constexpr array with 5 entries (last = 255 for temp sensor).
- [ ] 3.5 `RP2040DmaSemanticEmitter.emit(device)` → extend existing `dma.hpp`
      stub to fill the missing fields (`kBaseAddress`, `kMaxTransferCount`,
      `kSupportsChaining`, `kSupportsByteSwap`).
- [ ] 3.6 `RP2040TimerSemanticEmitter.emit(device)` → extend existing `timer.hpp`
      stub (add `kAlarmCount`, `kDreq` per alarm).
- [ ] 3.7 `RP2040PwmSemanticEmitter.emit(device)` → extend existing `pwm.hpp`
      stub (add `kSliceIndex`, `kChannelA_Pin`, `kChannelB_Pin`, `kClockDivMin/Max`).

## 4. Goldens

- [ ] 4.1 Regenerate `tests/fixtures/emitted/rp2040/driver_semantics/gpio.hpp`.
      Assert GPIO0 has 9 functions, GPIO26 has ADC function present.
- [ ] 4.2 Regenerate `uart.hpp`. Assert UART0 `kValidTxPins` contains {0,12,16,28}.
- [ ] 4.3 Regenerate `spi.hpp`. Assert SPI0 `kMaxClockHz=62500000`.
- [ ] 4.4 Regenerate `adc.hpp`. Assert `kChannelCount=5`, `kFifoDepth=4`.
- [ ] 4.5 Regenerate `dma.hpp`. Assert `kSupportsChaining=true`.
- [ ] 4.6 Regenerate `timer.hpp` and `pwm.hpp`. Assert `kAlarmCount=4`,
      `PwmSemanticTraits<PwmId::Slice7>::kChannelA_Pin == 14`.

## 5. Compile tests

- [ ] 5.1 `test_rp2040_gpio_traits.cpp`:
      ```cpp
      static_assert(GpioSemanticTraits<GpioPinId::Gpio26>::kPresent);
      static_assert(GpioSemanticTraits<GpioPinId::Gpio26>::kGpioNum == 26);
      ```
- [ ] 5.2 `test_rp2040_uart_traits.cpp`, `test_rp2040_spi_traits.cpp`,
      `test_rp2040_adc_traits.cpp`, `test_rp2040_dma_traits.cpp`,
      `test_rp2040_timer_traits.cpp`, `test_rp2040_pwm_traits.cpp`.

## 6. CI

- [ ] 6.1 Update `docs/COVERAGE_MATRIX.md`: all RP2040 rows → ✓ (except i2c/usb/pio
      which are ✓ via their respective openspecs).
- [ ] 6.2 Add RP2040 to `gpio-semantic-coverage` CI assertion.
