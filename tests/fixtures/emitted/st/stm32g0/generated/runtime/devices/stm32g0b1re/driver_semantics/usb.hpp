#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g0b1re {
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
struct UsbSemanticTraits<PeripheralId::USB> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_usb_st_usb;
  static constexpr bool kSupportsDeviceMode = true;
  static constexpr bool kSupportsHostMode = true;
  static constexpr bool kHasDedicatedEndpointConfig = true;
  static constexpr bool kHasClockFreeze = false;
  static constexpr bool kHardwarePresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40005C00u;
  static constexpr std::uint16_t kEndpointCount = 8u;
  static constexpr bool kSupportsHighSpeed = false;
  static constexpr bool kSupportsDma = false;
  static constexpr bool kCrystalless = true;
  static constexpr std::uintptr_t kDpramBaseAddress = 0x40006000u;
  static constexpr std::uint32_t kDpramSizeBytes = 1024u;
  static constexpr std::uint8_t kDmaChannelCount = 0u;
  static constexpr PinId kDmPin = PinId::none;
  static constexpr PinId kDpPin = PinId::none;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 12u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 20u, true};
  static constexpr RuntimeRegisterRef kInterruptStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 20u, true};
  static constexpr RuntimeRegisterRef kInterruptMaskRegister = RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 24u, true};
  static constexpr RuntimeRegisterRef kDeviceControlRegister = RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 2052u, true};
  static constexpr RuntimeRegisterRef kDeviceStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 2056u, true};
  static constexpr RuntimeRegisterRef kDeviceInterruptStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDeviceInterruptMaskRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDeviceInterruptEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDeviceInterruptDisableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kHostControlRegister = RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 1024u, true};
  static constexpr RuntimeRegisterRef kHostStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 1088u, true};
  static constexpr RuntimeRegisterRef kHostInterruptStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kHostInterruptMaskRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kHostInterruptEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kHostInterruptDisableRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 56u, true}, 16u, 1u, true};
  static constexpr RuntimeFieldRef kFreezeClockField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kForceDeviceModeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 12u, true}, 30u, 1u, true};
  static constexpr RuntimeFieldRef kForceHostModeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 12u, true}, 29u, 1u, true};
  static constexpr RuntimeFieldRef kModeStatusField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 20u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kSoftDisconnectField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 2052u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kRemoteWakeupField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 2052u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kAddressEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAddressField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40005C00u, 2048u, true}, 4u, 7u, true};
  static constexpr RuntimeFieldRef kClockUsableField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

inline constexpr std::array<PeripheralId, 1> kUsbSemanticPeripherals = {{
  PeripheralId::USB,
}};
}
}
}
}
}
}
}
