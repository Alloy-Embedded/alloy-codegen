#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
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
};

inline constexpr std::array<PeripheralId, 0> kUsbSemanticPeripherals = {};
}
}
}
}
}
}
}
