# Tasks: Fill Espressif Semantic Gaps

## 1. IR model extension for Espressif peripherals

- [x] 1.1 Add `UartPeripheralDescriptor` to IR: `peripheral_id`, `base_address`,
      `fifo_depth`, `tx_signal_idx`, `rx_signal_idx`, `supports_dma: bool`.
      Add `Device.uart_peripherals: list[UartPeripheralDescriptor] = []`.
- [x] 1.2 Add `SpiPeripheralDescriptor`: `peripheral_id`, `base_address`,
      `max_clock_hz`, `mosi_out_signal`, `miso_in_signal`, `clk_out_signal`,
      `cs_out_signal`, `has_iomux_fast_path: bool`, `iomux_pins: dict | None`,
      `supports_dma: bool`. Add `Device.spi_peripherals`.
- [x] 1.3 Add `AdcDescriptor`: `unit_id`, `channel_count`, `resolution_bits`,
      `conflicts_with_wifi: bool`, `channel_pins: list[int]`.
      Add `Device.adc_units`.
- [x] 1.4 Add `TimerDescriptor`: `timer_id`, `group_idx`, `timer_idx`,
      `base_address`, `bits`, `clock_sources: list[str]`.
      Add `Device.timer_units`.
- [x] 1.5 Add `LedcDescriptor`: `channel_count`, `resolution_bits`,
      `clock_sources: list[str]`, `output_signals: list[int]`.
      Add `Device.ledc`.
- [x] 1.6 Add `DmaChannelDescriptor`: `channel_id`, `channel_index`,
      `is_gdma: bool`, `max_transfer_bytes`, `peripheral_requests: dict[str,int]`.
      Add `Device.dma_channels`.
- [x] 1.7 Update JSON schema and round-trip tests for all new fields.

## 2. ESP32 classic normalizer extensions

- [x] 2.1 Extend `esp_idf.py` UART pass: parse `gpio_sig_map.h` for
      `U0TXD_OUT_IDX`, `U0RXD_IN_IDX`, …, `U2TXD_OUT_IDX`, `U2RXD_IN_IDX`.
      Populate three `UartPeripheralDescriptor`s (UART0=0x3FF40000,
      UART1=0x3FF50000, UART2=0x3FF6E000). `kFifoDepth=128`.
- [x] 2.2 SPI pass: extract SPI2 signal indices for MOSI/MISO/CLK/CS from
      `gpio_sig_map.h`. Base addresses: SPI2=0x3FF64000, SPI3=0x3FF65000.
      IO_MUX fast path pins: SPI2 MOSI=13, MISO=12, CLK=14, CS=15.
- [x] 2.3 ADC pass: hardcode from classic TRM. ADC1 channels 0–7 → GPIO36,37,
      38,39,32,33,34,35. ADC2 channels 0–9 → GPIO4,0,2,15,13,12,14,27,25,26.
      `kConflictsWithWifi=true` for ADC2.
- [x] 2.4 Timer pass: TG0 base=0x3FF5F000, TG1 base=0x3FF60000. Two timers per
      group. `kBits=64`. Clock sources: APB, XTAL.
- [x] 2.5 LEDC pass: base=0x3FF59000. 8 HS channels + 8 LS channels.
      Parse out signal indices from `gpio_sig_map.h`.
- [x] 2.6 DMA pass: classic has legacy SPI DMA (not GDMA). Mark `is_gdma=false`.
      `kMaxTransferBytes=4095`. Request lines per peripheral from TRM Table 3.

## 3. ESP32-C3 normalizer extensions

- [x] 3.1 UART0 (0x60000000), UART1 (0x10000000). `kFifoDepth=256`. Parse C3
      `gpio_sig_map.h` for signal indices.
- [x] 3.2 SPI2 only (`kBaseAddress=0x60024000`). No SPI3 on C3.
      IO_MUX fast path: C3 has no dedicated SPI IO_MUX pins — `kHasIoMuxFastPath=false`.
- [x] 3.3 ADC1 only: 6 channels → GPIO0,1,2,3,4,5. `kConflictsWithWifi=false`.
- [x] 3.4 Timer: TG0 base=0x6001F000, TG1=0x60020000. `kBits=54`.
- [x] 3.5 LEDC base=0x60019000. 8 channels (no HS/LS split on C3).
- [x] 3.6 GDMA: 3 channels, `is_gdma=true`, base=0x6003F000. Request lines
      from C3 TRM Table 3.

## 4. ESP32-S3 normalizer extensions

- [x] 4.1 UART0/1/2 (bases 0x60000000, 0x10000000, 0x6002E000). `kFifoDepth=128`.
- [x] 4.2 SPI2 (`0x60024000`), SPI3 (`0x60025000`). IO_MUX fast-path pins:
      SPI2 MOSI=11, MISO=13, CLK=12, CS=10. S3 has IO_MUX. `kMaxClockHz=80_000_000`.
- [x] 4.3 ADC1 (10ch → GPIO1–10), ADC2 (10ch → GPIO11–20). `kConflictsWithWifi=true`
      for ADC2.
- [x] 4.4 Timer: same group layout as classic. `kBits=54` on S3.
- [x] 4.5 LEDC base=0x60019000. 8 channels.
- [x] 4.6 GDMA: 5 channels, base=0x6003F000. Request lines from S3 TRM.

## 5. Emitters (one per peripheral type, shared across Espressif families)

- [x] 5.1 `EspressifUartSemanticEmitter` in
      `src/alloy_codegen/emitters/uart_semantics.py`. Reads `Device.uart_peripherals`,
      emits `UartSemanticTraits<UartId::Uart0>`, etc. into `uart.hpp`.
- [x] 5.2 `EspressifSpiSemanticEmitter` → `spi.hpp`.
- [x] 5.3 `EspressifAdcSemanticEmitter` → `adc.hpp`.
- [x] 5.4 `EspressifTimerSemanticEmitter` → `timer.hpp`.
- [x] 5.5 `EspressifLedcSemanticEmitter` → `pwm.hpp`.
- [x] 5.6 `EspressifDmaSemanticEmitter` → `dma.hpp`.

## 6. Goldens and compile tests

- [x] 6.1 Regenerate goldens for esp32, esp32c3, esp32s3 for all 6 new headers.
- [x] 6.2 Assert in goldens: ESP32 UART0 `kBaseAddress=0x3FF40000`,
      ESP32-C3 SPI has `kHasIoMuxFastPath=false`,
      ESP32-S3 ADC2 `kConflictsWithWifi=true`.
- [x] 6.3 Compile tests:
      `test_esp32_uart_traits.cpp`, `test_esp32_spi_traits.cpp`,
      `test_esp32_adc_traits.cpp`, `test_esp32c3_peripheral_traits.cpp`,
      `test_esp32s3_peripheral_traits.cpp`.

## 7. CI

- [x] 7.1 Extend `gpio-semantic-coverage` CI job to check all 6 new header
      types for Espressif families.
- [x] 7.2 Update `docs/COVERAGE_MATRIX.md`: all Espressif cells for uart/spi/
      adc/timer/pwm/dma → ✓.
