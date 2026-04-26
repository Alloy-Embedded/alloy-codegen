# Tasks: Add USB Semantic Traits

## 1. IR model extension

- [x] 1.1 Add `UsbControllerDescriptor` to `src/alloy_codegen/ir/model.py`:
      `controller_id`, `base_address`, `dpram_base: int | None`,
      `dpram_size_bytes: int | None`, `endpoint_count`, `supports_high_speed: bool`,
      `supports_host_mode: bool`, `supports_dma: bool`, `crystalless: bool`,
      `dma_channel_count: int`, `dm_pin: str | None`, `dp_pin: str | None`,
      `clock_source: str`.
- [x] 1.2 Add `Device.usb_controllers: list[UsbControllerDescriptor] = []`.
      Existing fixtures valid (empty list).
- [x] 1.3 Update JSON schema and round-trip tests.

## 2. STM32G0 USB FS traits

- [x] 2.1 Create `patches/st/stm32g0/usb.json`: hardcoded USB FS facts
      (base address, PMA address and size, endpoint count, clock source = HSI48+CRS).
- [x] 2.2 Extend STM32 normalizer to read `usb.json` and populate
      `Device.usb_controllers` for STM32G0.
- [x] 2.3 Implement `UsbSemanticEmitter.emit_stm32g0(device)`: writes
      `UsbSemanticTraits<UsbId::Usb>` specialization into `usb.hpp`.
- [x] 2.4 Golden: `tests/fixtures/emitted/stm32g071rb/driver_semantics/usb.hpp`.
      Assert `kPresent=true`, `kCrystalless=true`, `kPmaSizeBytes=1024`.
- [x] 2.5 Compile test: `test_stm32g0_usb_traits.cpp`.

## 3. STM32F4 USB OTG FS traits

- [x] 3.1 Create `patches/st/stm32f401re/usb.json`: OTG FS facts.
- [x] 3.2 Extend normalizer for F4. DM/DP pins: GPIOA_11, GPIOA_12.
- [x] 3.3 Implement `UsbSemanticEmitter.emit_stm32f4(device)`.
- [x] 3.4 Golden + compile test.

## 4. RP2040 USB traits

- [x] 4.1 Create `patches/raspberrypi/rp2040/usb.json`: USBCTRL_REGS base,
      DPRAM base, DPRAM size, endpoint count=16, host mode=true, crystalless=true.
- [x] 4.2 Extend RP2040 normalizer to populate `Device.usb_controllers`.
- [x] 4.3 Implement `UsbSemanticEmitter.emit_rp2040(device)`.
- [x] 4.4 Golden: assert `kEndpointCount=16`, `kSupportsHostMode=true`.
- [x] 4.5 Compile test.

## 5. SAME70 UOTGHS traits

- [x] 5.1 Create `patches/microchip/same70/usb.json`: UOTGHS base, 7 endpoints,
      HS support, DMA channel count=7, crystalless=false.
- [x] 5.2 Extend SAME70 normalizer (ATDF adapter) to populate USB controller.
- [x] 5.3 Implement `UsbSemanticEmitter.emit_same70(device)`.
- [x] 5.4 Golden: assert `kSupportsHighSpeed=true`, `kDmaChannelCount=7`.
- [x] 5.5 Compile test.

## 6. ESP32-S3 USB OTG FS traits

- [x] 6.1 Extend `esp_idf.py` S3 normalizer: populate `UsbControllerDescriptor`
      for USB OTG at `0x60080000`. DM=GPIO19, DP=GPIO20. `endpoints=6`,
      `crystalless=true` (uses internal PHY).
- [x] 6.2 Implement `UsbSemanticEmitter.emit_esp32s3(device)`.
- [x] 6.3 Golden + compile test.

## 7. CI gate

- [x] 7.1 Add `usb-semantic-coverage` assertion: for any admitted family with
      USB hardware, `usb.hpp` MUST have at least one `kPresent=true` entry.
      Blocks PR admission of families with USB and no traits.
- [x] 7.2 Update `docs/COVERAGE_MATRIX.md`: `usb_traits` column —
      STM32G0=✓, STM32F4=✓, RP2040=✓, SAME70=✓, ESP32-S3=✓,
      ESP32/C3/AVR-DA=N/A.
