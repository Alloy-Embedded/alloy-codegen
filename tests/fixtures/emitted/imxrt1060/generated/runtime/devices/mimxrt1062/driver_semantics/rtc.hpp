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

inline constexpr std::array<PeripheralId, 0> kRtcSemanticPeripherals = {};
}
}
}
}
}
}
}
