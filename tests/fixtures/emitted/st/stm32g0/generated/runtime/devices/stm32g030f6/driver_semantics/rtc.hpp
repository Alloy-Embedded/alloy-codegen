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
namespace stm32g030f6 {
namespace driver_semantics {
template<PeripheralId Id>
struct RtcSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr bool kHasCalendar = false;
  static constexpr bool kHasAlarm = false;
  static constexpr bool kHasWriteProtection = false;
  static constexpr std::uint32_t kWriteProtectDisableKey0 = 0u;
  static constexpr std::uint32_t kWriteProtectDisableKey1 = 0u;
  static constexpr std::uint32_t kWriteProtectEnableKey = 0u;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTimeRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDateRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kAlarmTimeRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kAlarmDateRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kClearRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kWriteProtectRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kHourModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInitField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInitReadyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kShadowBypassField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateTimeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateCalendarField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateAckField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAlarmEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAlarmInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSecondInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTimeEventInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCalendarEventInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusAlarmField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusSecondField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusTimeEventField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusCalendarEventField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusTamperErrorField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClearAlarmField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClearSecondField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClearTimeEventField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClearCalendarEventField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClearTamperErrorField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kWriteProtectKeyField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

template<>
struct RtcSemanticTraits<PeripheralId::RTC> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_rtc_st_rtc;
  static constexpr bool kHasCalendar = true;
  static constexpr bool kHasAlarm = true;
  static constexpr bool kHasWriteProtection = true;
  static constexpr std::uint32_t kWriteProtectDisableKey0 = 0x000000CAu;
  static constexpr std::uint32_t kWriteProtectDisableKey1 = 0x00000053u;
  static constexpr std::uint32_t kWriteProtectEnableKey = 0x000000FFu;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTimeRegister = RuntimeRegisterRef{RegisterId::register_rtc_tr, 0x40002800u, 0u, true};
  static constexpr RuntimeRegisterRef kDateRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kAlarmTimeRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kAlarmDateRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kClearRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kWriteProtectRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kHourModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInitField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInitReadyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kShadowBypassField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateTimeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateCalendarField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateAckField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAlarmEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAlarmInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSecondInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTimeEventInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCalendarEventInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusAlarmField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusSecondField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusTimeEventField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusCalendarEventField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStatusTamperErrorField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClearAlarmField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClearSecondField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClearTimeEventField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClearCalendarEventField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClearTamperErrorField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kWriteProtectKeyField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

inline constexpr std::array<PeripheralId, 1> kRtcSemanticPeripherals = {{
  PeripheralId::RTC,
}};
}
}
}
}
}
}
}
