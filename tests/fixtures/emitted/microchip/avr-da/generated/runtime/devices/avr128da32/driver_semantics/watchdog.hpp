#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
namespace driver_semantics {
template<PeripheralId Id>
struct WatchdogSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr bool kHasWindow = false;
  static constexpr std::uint32_t kRequiredConfigValue = 0u;
  static constexpr std::uint32_t kStartKeyValue = 0u;
  static constexpr std::uint32_t kRefreshKeyValue = 0u;
  static constexpr std::uint32_t kUnlockKeyValue = 0u;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kReloadRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kWindowRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRestartField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kKeyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTimeoutField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kWindowField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEarlyWarningInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kResetEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusPrescalerUpdateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusReloadUpdateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusWindowUpdateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusTimeoutField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusErrorField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRequiredConfigField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

inline constexpr std::array<PeripheralId, 0> kWatchdogSemanticPeripherals = {};
}
}
}
}
}
}
}
