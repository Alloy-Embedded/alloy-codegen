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

template<>
struct WatchdogSemanticTraits<PeripheralId::RTWDOG> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_watchdog_nxp_rtwdog;
  static constexpr bool kHasWindow = true;
  static constexpr std::uint32_t kRequiredConfigValue = 0x00000001u;
  static constexpr std::uint32_t kStartKeyValue = 0x00000000u;
  static constexpr std::uint32_t kRefreshKeyValue = 0x0000A602u;
  static constexpr std::uint32_t kUnlockKeyValue = 0x0000C520u;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_rtwdog_cs, 0x400BC000u, 0u, true};
  static constexpr RuntimeRegisterRef kConfigRegister = RuntimeRegisterRef{RegisterId::register_rtwdog_cs, 0x400BC000u, 0u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::register_rtwdog_cs, 0x400BC000u, 0u, true};
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

template<>
struct WatchdogSemanticTraits<PeripheralId::WDOG1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_watchdog_nxp_wdog;
  static constexpr bool kHasWindow = true;
  static constexpr std::uint32_t kRequiredConfigValue = 0x00000000u;
  static constexpr std::uint32_t kStartKeyValue = 0x00000000u;
  static constexpr std::uint32_t kRefreshKeyValue = 0x00005555u;
  static constexpr std::uint32_t kUnlockKeyValue = 0x0000C520u;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_wdog1_wcr, 0x400B8000u, 0u, true};
  static constexpr RuntimeRegisterRef kConfigRegister = RuntimeRegisterRef{RegisterId::register_wdog1_wcr, 0x400B8000u, 0u, true};
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

template<>
struct WatchdogSemanticTraits<PeripheralId::WDOG2> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_watchdog_nxp_wdog;
  static constexpr bool kHasWindow = true;
  static constexpr std::uint32_t kRequiredConfigValue = 0x00000000u;
  static constexpr std::uint32_t kStartKeyValue = 0x00000000u;
  static constexpr std::uint32_t kRefreshKeyValue = 0x00005555u;
  static constexpr std::uint32_t kUnlockKeyValue = 0x0000C520u;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_wdog2_wcr, 0x400D0000u, 0u, true};
  static constexpr RuntimeRegisterRef kConfigRegister = RuntimeRegisterRef{RegisterId::register_wdog2_wcr, 0x400D0000u, 0u, true};
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

inline constexpr std::array<PeripheralId, 3> kWatchdogSemanticPeripherals = {{
  PeripheralId::RTWDOG,
  PeripheralId::WDOG1,
  PeripheralId::WDOG2,
}};
}
}
}
}
}
}
}
