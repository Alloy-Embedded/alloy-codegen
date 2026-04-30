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
struct WatchdogSemanticTraits<PeripheralId::RSWDT> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_watchdog_microchip_rswdt_g;
  static constexpr bool kHasWindow = false;
  static constexpr std::uint32_t kRequiredConfigValue = 0x00000FFFu;
  static constexpr std::uint32_t kStartKeyValue = 0x00000000u;
  static constexpr std::uint32_t kRefreshKeyValue = 0x000000C4u;
  static constexpr std::uint32_t kUnlockKeyValue = 0x00000000u;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_rswdt_cr, 0x400E1900u, 0u, true};
  static constexpr RuntimeRegisterRef kConfigRegister = RuntimeRegisterRef{RegisterId::register_rswdt_mr, 0x400E1900u, 4u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::register_rswdt_sr, 0x400E1900u, 8u, true};
  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kReloadRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kWindowRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDisableField = RuntimeFieldRef{FieldId::field_rswdt_mr_wddis, RuntimeRegisterRef{RegisterId::register_rswdt_mr, 0x400E1900u, 4u, true}, 15u, 1u, true};
  static constexpr RuntimeFieldRef kRestartField = RuntimeFieldRef{FieldId::field_rswdt_cr_wdrstt, RuntimeRegisterRef{RegisterId::register_rswdt_cr, 0x400E1900u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kKeyField = RuntimeFieldRef{FieldId::field_rswdt_cr_key, RuntimeRegisterRef{RegisterId::register_rswdt_cr, 0x400E1900u, 0u, true}, 24u, 8u, true};
  static constexpr RuntimeFieldRef kTimeoutField = RuntimeFieldRef{FieldId::field_rswdt_mr_wdv, RuntimeRegisterRef{RegisterId::register_rswdt_mr, 0x400E1900u, 4u, true}, 0u, 12u, true};
  static constexpr RuntimeFieldRef kWindowField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEarlyWarningInterruptEnableField = RuntimeFieldRef{FieldId::field_rswdt_mr_wdfien, RuntimeRegisterRef{RegisterId::register_rswdt_mr, 0x400E1900u, 4u, true}, 12u, 1u, true};
  static constexpr RuntimeFieldRef kResetEnableField = RuntimeFieldRef{FieldId::field_rswdt_mr_wdrsten, RuntimeRegisterRef{RegisterId::register_rswdt_mr, 0x400E1900u, 4u, true}, 13u, 1u, true};
  static constexpr RuntimeFieldRef kStatusPrescalerUpdateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusReloadUpdateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusWindowUpdateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusTimeoutField = RuntimeFieldRef{FieldId::field_rswdt_sr_wdunf, RuntimeRegisterRef{RegisterId::register_rswdt_sr, 0x400E1900u, 8u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kStatusErrorField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRequiredConfigField = RuntimeFieldRef{FieldId::field_rswdt_mr_allones, RuntimeRegisterRef{RegisterId::register_rswdt_mr, 0x400E1900u, 4u, true}, 16u, 12u, true};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

template<>
struct WatchdogSemanticTraits<PeripheralId::WDT> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_watchdog_microchip_wdt_n;
  static constexpr bool kHasWindow = true;
  static constexpr std::uint32_t kRequiredConfigValue = 0x00000000u;
  static constexpr std::uint32_t kStartKeyValue = 0x00000000u;
  static constexpr std::uint32_t kRefreshKeyValue = 0x000000A5u;
  static constexpr std::uint32_t kUnlockKeyValue = 0x00000000u;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_wdt_cr, 0x400E1850u, 0u, true};
  static constexpr RuntimeRegisterRef kConfigRegister = RuntimeRegisterRef{RegisterId::register_wdt_mr, 0x400E1850u, 4u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::register_wdt_sr, 0x400E1850u, 8u, true};
  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kReloadRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kWindowRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDisableField = RuntimeFieldRef{FieldId::field_wdt_mr_wddis, RuntimeRegisterRef{RegisterId::register_wdt_mr, 0x400E1850u, 4u, true}, 15u, 1u, true};
  static constexpr RuntimeFieldRef kRestartField = RuntimeFieldRef{FieldId::field_wdt_cr_wdrstt, RuntimeRegisterRef{RegisterId::register_wdt_cr, 0x400E1850u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kKeyField = RuntimeFieldRef{FieldId::field_wdt_cr_key, RuntimeRegisterRef{RegisterId::register_wdt_cr, 0x400E1850u, 0u, true}, 24u, 8u, true};
  static constexpr RuntimeFieldRef kTimeoutField = RuntimeFieldRef{FieldId::field_wdt_mr_wdv, RuntimeRegisterRef{RegisterId::register_wdt_mr, 0x400E1850u, 4u, true}, 0u, 12u, true};
  static constexpr RuntimeFieldRef kWindowField = RuntimeFieldRef{FieldId::field_wdt_mr_wdd, RuntimeRegisterRef{RegisterId::register_wdt_mr, 0x400E1850u, 4u, true}, 16u, 12u, true};
  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEarlyWarningInterruptEnableField = RuntimeFieldRef{FieldId::field_wdt_mr_wdfien, RuntimeRegisterRef{RegisterId::register_wdt_mr, 0x400E1850u, 4u, true}, 12u, 1u, true};
  static constexpr RuntimeFieldRef kResetEnableField = RuntimeFieldRef{FieldId::field_wdt_mr_wdrsten, RuntimeRegisterRef{RegisterId::register_wdt_mr, 0x400E1850u, 4u, true}, 13u, 1u, true};
  static constexpr RuntimeFieldRef kStatusPrescalerUpdateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusReloadUpdateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusWindowUpdateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusTimeoutField = RuntimeFieldRef{FieldId::field_wdt_sr_wdunf, RuntimeRegisterRef{RegisterId::register_wdt_sr, 0x400E1850u, 8u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kStatusErrorField = RuntimeFieldRef{FieldId::field_wdt_sr_wderr, RuntimeRegisterRef{RegisterId::register_wdt_sr, 0x400E1850u, 8u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kRequiredConfigField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

inline constexpr std::array<PeripheralId, 2> kWatchdogSemanticPeripherals = {{
  PeripheralId::RSWDT,
  PeripheralId::WDT,
}};
}
}
}
}
}
}
}
