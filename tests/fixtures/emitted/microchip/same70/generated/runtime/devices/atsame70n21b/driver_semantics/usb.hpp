#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70n21b {
namespace driver_semantics {
template<PeripheralId Id>
struct UsbSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr bool kSupportsDeviceMode = false;
  static constexpr bool kSupportsHostMode = false;
  static constexpr bool kHasDedicatedEndpointConfig = false;
  static constexpr bool kHasClockFreeze = false;
  static constexpr bool kHardwarePresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0u;
  static constexpr std::uint16_t kEndpointCount = 0u;
  static constexpr bool kSupportsHighSpeed = false;
  static constexpr bool kSupportsDma = false;
  static constexpr bool kCrystalless = false;
  static constexpr std::uintptr_t kDpramBaseAddress = 0u;
  static constexpr std::uint32_t kDpramSizeBytes = 0u;
  static constexpr std::uint8_t kDmaChannelCount = 0u;
  static constexpr PinId kDmPin = PinId::none;
  static constexpr PinId kDpPin = PinId::none;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDeviceControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDeviceStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDeviceInterruptStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDeviceInterruptMaskRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDeviceInterruptEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDeviceInterruptDisableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kHostControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kHostStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kHostInterruptStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kHostInterruptMaskRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kHostInterruptEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kHostInterruptDisableRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kFreezeClockField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kForceDeviceModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kForceHostModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeStatusField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSoftDisconnectField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRemoteWakeupField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAddressEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAddressField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClockUsableField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

template<>
struct UsbSemanticTraits<PeripheralId::USBHS> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_usb_microchip_usbhs_g;
  static constexpr bool kSupportsDeviceMode = true;
  static constexpr bool kSupportsHostMode = true;
  static constexpr bool kHasDedicatedEndpointConfig = true;
  static constexpr bool kHasClockFreeze = true;
  static constexpr bool kHardwarePresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40038000u;
  static constexpr std::uint16_t kEndpointCount = 7u;
  static constexpr bool kSupportsHighSpeed = true;
  static constexpr bool kSupportsDma = true;
  static constexpr bool kCrystalless = false;
  static constexpr std::uintptr_t kDpramBaseAddress = 0u;
  static constexpr std::uint32_t kDpramSizeBytes = 0u;
  static constexpr std::uint8_t kDmaChannelCount = 7u;
  static constexpr PinId kDmPin = PinId::none;
  static constexpr PinId kDpPin = PinId::none;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_usbhs_ctrl, 0x40038000u, 2048u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::register_usbhs_sr, 0x40038000u, 2052u, true};
  static constexpr RuntimeRegisterRef kInterruptStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDeviceControlRegister = RuntimeRegisterRef{RegisterId::register_usbhs_devctrl, 0x40038000u, 0u, true};
  static constexpr RuntimeRegisterRef kDeviceStatusRegister = RuntimeRegisterRef{RegisterId::register_usbhs_devisr, 0x40038000u, 4u, true};
  static constexpr RuntimeRegisterRef kDeviceInterruptStatusRegister = RuntimeRegisterRef{RegisterId::register_usbhs_devisr, 0x40038000u, 4u, true};
  static constexpr RuntimeRegisterRef kDeviceInterruptMaskRegister = RuntimeRegisterRef{RegisterId::register_usbhs_devimr, 0x40038000u, 16u, true};
  static constexpr RuntimeRegisterRef kDeviceInterruptEnableRegister = RuntimeRegisterRef{RegisterId::register_usbhs_devier, 0x40038000u, 24u, true};
  static constexpr RuntimeRegisterRef kDeviceInterruptDisableRegister = RuntimeRegisterRef{RegisterId::register_usbhs_devidr, 0x40038000u, 20u, true};
  static constexpr RuntimeRegisterRef kHostControlRegister = RuntimeRegisterRef{RegisterId::register_usbhs_hstctrl, 0x40038000u, 1024u, true};
  static constexpr RuntimeRegisterRef kHostStatusRegister = RuntimeRegisterRef{RegisterId::register_usbhs_hstisr, 0x40038000u, 1028u, true};
  static constexpr RuntimeRegisterRef kHostInterruptStatusRegister = RuntimeRegisterRef{RegisterId::register_usbhs_hstisr, 0x40038000u, 1028u, true};
  static constexpr RuntimeRegisterRef kHostInterruptMaskRegister = RuntimeRegisterRef{RegisterId::register_usbhs_hstimr, 0x40038000u, 1040u, true};
  static constexpr RuntimeRegisterRef kHostInterruptEnableRegister = RuntimeRegisterRef{RegisterId::register_usbhs_hstier, 0x40038000u, 1048u, true};
  static constexpr RuntimeRegisterRef kHostInterruptDisableRegister = RuntimeRegisterRef{RegisterId::register_usbhs_hstidr, 0x40038000u, 1044u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::field_usbhs_ctrl_usbe, RuntimeRegisterRef{RegisterId::register_usbhs_ctrl, 0x40038000u, 2048u, true}, 15u, 1u, true};
  static constexpr RuntimeFieldRef kFreezeClockField = RuntimeFieldRef{FieldId::field_usbhs_ctrl_frzclk, RuntimeRegisterRef{RegisterId::register_usbhs_ctrl, 0x40038000u, 2048u, true}, 14u, 1u, true};
  static constexpr RuntimeFieldRef kForceDeviceModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kForceHostModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeStatusField = RuntimeFieldRef{FieldId::field_usbhs_ctrl_uimod, RuntimeRegisterRef{RegisterId::register_usbhs_ctrl, 0x40038000u, 2048u, true}, 25u, 1u, true};
  static constexpr RuntimeFieldRef kSoftDisconnectField = RuntimeFieldRef{FieldId::field_usbhs_devctrl_detach, RuntimeRegisterRef{RegisterId::register_usbhs_devctrl, 0x40038000u, 0u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kRemoteWakeupField = RuntimeFieldRef{FieldId::field_usbhs_devctrl_rmwkup, RuntimeRegisterRef{RegisterId::register_usbhs_devctrl, 0x40038000u, 0u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kAddressEnableField = RuntimeFieldRef{FieldId::field_usbhs_devctrl_adden, RuntimeRegisterRef{RegisterId::register_usbhs_devctrl, 0x40038000u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kAddressField = RuntimeFieldRef{FieldId::field_usbhs_devctrl_uadd, RuntimeRegisterRef{RegisterId::register_usbhs_devctrl, 0x40038000u, 0u, true}, 0u, 7u, true};
  static constexpr RuntimeFieldRef kClockUsableField = RuntimeFieldRef{FieldId::field_usbhs_sr_clkusable, RuntimeRegisterRef{RegisterId::register_usbhs_sr, 0x40038000u, 2052u, true}, 14u, 1u, true};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

inline constexpr std::array<PeripheralId, 1> kUsbSemanticPeripherals = {{
  PeripheralId::USBHS,
}};
}
}
}
}
}
}
}
