# Add USB Semantic Traits

## Why

The alloy `add-usb-hal` openspec defines a `UsbDeviceController<T>` concept and
requires `UsbSemanticTraits<PeripheralId>` to enable compile-time validation of
USB peripheral configuration. Today `usb.hpp` is generated but every specialization
has `kPresent = false`:

| Family       | USB hardware          | USB traits populated? |
|--------------|-----------------------|-----------------------|
| STM32G0      | USB FS (Crystal-less) | Empty                 |
| STM32F4      | USB OTG FS            | Empty                 |
| RP2040       | USB 1.1 Device+Host   | Empty                 |
| SAME70       | UOTGHS (HS + FS)      | Empty                 |
| ESP32 classic| No USB               | N/A                   |
| ESP32-C3     | USB Serial/JTAG only  | Partial (CDC bridge)  |
| ESP32-S3     | USB OTG FS            | Empty                 |
| AVR-DA       | No USB               | N/A                   |

The `add-usb-hal` alloy openspec is blocked on these traits being populated.
Without them, the alloy `UsbDeviceController<T>` concept check evaluates with no
specialization → the `kPresent = false` default causes a compile error for any
code that tries to obtain a typed USB peripheral handle.

## What Changes

### STM32G0 USB FS traits

STM32G0 (G071/G081) has a Crystal-less USB FS controller:
- Base: `USB_BASE = 0x40005C00`, DPRAM at `0x40006000`.
- Internal PMA (Packet Memory Area): 1024 bytes.
- Endpoints: 8 bidirectional.
- No external crystal required (uses HSI48 with CRS).
- DMA: not available (PMA is accessed via 16-bit FIFO registers).
- Speed: Full-Speed only (12 Mbps).

`UsbSemanticTraits<UsbId::Usb>`:
- `kPresent = true`
- `kBaseAddress = 0x40005C00`
- `kPmaBaseAddress = 0x40006000`
- `kPmaSizeBytes = 1024`
- `kEndpointCount = 8`
- `kSupportsHighSpeed = false`
- `kSupportsDma = false`
- `kCrystalless = true`
- `kClockSource` = `I2cClockSource::Hsi48WithCrs`

### STM32F4 USB OTG FS traits

STM32F401 has USB OTG FS:
- Base: `USB_OTG_FS_BASE = 0x50000000`.
- FIFO: 1.25 KB per endpoint direction.
- Endpoints: 4 IN + 4 OUT.
- DMA: available in OTG DMA mode.
- Pins: PA11 (DM), PA12 (DP) — fixed, not GPIO matrix.

`UsbSemanticTraits<UsbId::UsbOtgFs>`:
- `kPresent = true`
- `kBaseAddress = 0x50000000`
- `kEndpointCount = 4`
- `kSupportsHighSpeed = false`
- `kSupportsDma = true`
- `kCrystalless = false`
- `kDmPin = GpioPinId::GPIOA_11`, `kDpPin = GpioPinId::GPIOA_12`

### RP2040 USB traits

RP2040 USB 1.1 controller:
- Base: `USBCTRL_REGS_BASE = 0x50110000`. DPRAM at `0x50100000`.
- DPRAM: 4096 bytes, 16 double-buffered endpoints.
- Supports both Device and Host mode.
- No external crystal required (uses PLL + 48 MHz).
- DMA: not applicable (DPRAM is accessed directly by CPU and USB controller).

`UsbSemanticTraits<UsbId::Usb>`:
- `kPresent = true`
- `kBaseAddress = 0x50110000`
- `kDpramBaseAddress = 0x50100000`
- `kDpramSizeBytes = 4096`
- `kEndpointCount = 16`
- `kSupportsHighSpeed = false`
- `kSupportsHostMode = true`
- `kCrystalless = true`

### SAME70 UOTGHS traits

SAME70 UOTGHS supports both FS (12 Mbps) and HS (480 Mbps):
- Base: `UOTGHS_BASE = 0x40038000`.
- 7 configurable endpoints.
- HS requires external 12 MHz crystal.
- DMA: 7 DMA channels (one per endpoint).

`UsbSemanticTraits<UsbId::Uotghs>`:
- `kPresent = true`
- `kBaseAddress = 0x40038000`
- `kEndpointCount = 7`
- `kSupportsHighSpeed = true`
- `kSupportsDma = true`
- `kCrystalless = false`
- `kDmaChannelCount = 7`

### ESP32-S3 USB OTG FS traits

ESP32-S3 includes a USB OTG FS controller (distinct from the USB Serial/JTAG):
- Base: `USB_OTG_BASE = 0x60080000`.
- Pins: GPIO19 (DM), GPIO20 (DP) — fixed IO_MUX.
- 6 endpoints. No DMA (CPU-driven FIFO).
- FS only.

`UsbSemanticTraits<UsbId::UsbOtg>`:
- `kPresent = true`
- `kBaseAddress = 0x60080000`
- `kEndpointCount = 6`
- `kSupportsHighSpeed = false`
- `kSupportsDma = false`
- `kDmPin = GpioPinId::Gpio19`, `kDpPin = GpioPinId::Gpio20`

## What Does NOT Change

- ESP32 classic — no USB hardware, `kPresent=false` unchanged.
- AVR-DA — no USB hardware, `kPresent=false` unchanged.
- ESP32-C3 — USB Serial/JTAG is a fixed ROM peripheral, not a programmable
  USB controller; it remains CDC-only with `kPresent=false` for OTG traits.
- The `UsbSemanticTraits` struct layout in alloy — codegen fills specializations.
- USB class drivers (CDC-ACM, DFU, HID) — those are in alloy's `add-usb-hal`.

## Alternatives Considered

**Include USB in `fill-espressif-semantic-gaps`:** ESP32-S3 USB is architecturally
different from the ESP32 classic (which has no USB). Keeping USB in its own
openspec keeps the vendor-gap and USB-specific logic separate, and aligns with the
alloy `add-usb-hal` openspec dependency tracking.
