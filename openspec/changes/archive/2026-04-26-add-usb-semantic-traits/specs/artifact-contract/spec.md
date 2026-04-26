## ADDED Requirements

### Requirement: usb.hpp SHALL emit USB hardware-feature constexprs alongside register references

The emitted `driver_semantics/usb.hpp` MUST expose hardware-feature
constexprs on every `UsbSemanticTraits` specialization for devices whose
`Device.usb_controllers` carries a matching `UsbControllerDescriptor`.
The constexprs (`kHardwarePresent`, `kBaseAddress`, `kEndpointCount`,
`kSupportsHighSpeed`, `kSupportsDma`, `kCrystalless`,
`kDpramBaseAddress`, `kDpramSizeBytes`, `kDmaChannelCount`, `kDmPin`,
`kDpPin`) MUST default to safe falsy values on the unspecialized
template so consumer code that branches on `kHardwarePresent` compiles
even when no controller is admitted.

`kDmPin` / `kDpPin` MUST resolve to typed `PinId` enum values when the
documented pin is admitted in the device's `PinId` enum, and to
`PinId::none` otherwise (preserving compile-time correctness across
package variants where the pad isn't bonded out).

#### Scenario: STM32G0B1 emits hardware-feature constexprs on the USB specialization

- **WHEN** the pipeline emits `usb.hpp` for STM32G0B1
- **THEN** `UsbSemanticTraits<PeripheralId::USB>` carries
  `kHardwarePresent = true`, `kBaseAddress = 0x40005C00u`,
  `kEndpointCount = 8u`, `kCrystalless = true`,
  `kDpramBaseAddress = 0x40006000u`, `kDpramSizeBytes = 1024u`

#### Scenario: STM32F401RE emits OTG FS facts and gracefully drops missing pins

- **WHEN** the pipeline emits `usb.hpp` for STM32F401RE
- **THEN** `UsbSemanticTraits<PeripheralId::OTG_FS>` carries
  `kBaseAddress = 0x50000000u`, `kEndpointCount = 4u`,
  `kSupportsDma = true`
- **AND** `kDmPin` / `kDpPin` resolve to `PinId::none` when PA11/PA12
  are not in the admitted package's pin set

#### Scenario: Devices without admitted USB peripherals see only the default trait

- **WHEN** the pipeline emits `usb.hpp` for a device with no admitted
  USB peripheral (e.g. ESP32 classic, AVR-DA)
- **THEN** the file contains only the unspecialized template with
  `kPresent = false` and `kHardwarePresent = false`
- **AND** `kUsbSemanticPeripherals` is the empty array
