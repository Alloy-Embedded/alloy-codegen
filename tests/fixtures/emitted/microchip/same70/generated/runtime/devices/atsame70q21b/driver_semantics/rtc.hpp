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
namespace atsame70q21b {
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
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_rtc_microchip_rtc_zb;
  static constexpr bool kHasCalendar = true;
  static constexpr bool kHasAlarm = true;
  static constexpr bool kHasWriteProtection = false;
  static constexpr std::uint32_t kWriteProtectDisableKey0 = 0x00000000u;
  static constexpr std::uint32_t kWriteProtectDisableKey1 = 0x00000000u;
  static constexpr std::uint32_t kWriteProtectEnableKey = 0x00000000u;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_rtc_cr, 0x400E1860u, 0u, true};
  static constexpr RuntimeRegisterRef kModeRegister = RuntimeRegisterRef{RegisterId::register_rtc_mr, 0x400E1860u, 4u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::register_rtc_sr, 0x400E1860u, 24u, true};
  static constexpr RuntimeRegisterRef kTimeRegister = RuntimeRegisterRef{RegisterId::register_rtc_timr, 0x400E1860u, 8u, true};
  static constexpr RuntimeRegisterRef kDateRegister = RuntimeRegisterRef{RegisterId::register_rtc_calr, 0x400E1860u, 12u, true};
  static constexpr RuntimeRegisterRef kAlarmTimeRegister = RuntimeRegisterRef{RegisterId::register_rtc_timalr, 0x400E1860u, 16u, true};
  static constexpr RuntimeRegisterRef kAlarmDateRegister = RuntimeRegisterRef{RegisterId::register_rtc_calalr, 0x400E1860u, 20u, true};
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = RuntimeRegisterRef{RegisterId::register_rtc_ier, 0x400E1860u, 32u, true};
  static constexpr RuntimeRegisterRef kInterruptDisableRegister = RuntimeRegisterRef{RegisterId::register_rtc_idr, 0x400E1860u, 36u, true};
  static constexpr RuntimeRegisterRef kInterruptMaskRegister = RuntimeRegisterRef{RegisterId::register_rtc_imr, 0x400E1860u, 40u, true};
  static constexpr RuntimeRegisterRef kClearRegister = RuntimeRegisterRef{RegisterId::register_rtc_sccr, 0x400E1860u, 28u, true};
  static constexpr RuntimeRegisterRef kWriteProtectRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kHourModeField = RuntimeFieldRef{FieldId::field_rtc_mr_hrmod, RuntimeRegisterRef{RegisterId::register_rtc_mr, 0x400E1860u, 4u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kInitField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInitReadyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kShadowBypassField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateTimeField = RuntimeFieldRef{FieldId::field_rtc_cr_updtim, RuntimeRegisterRef{RegisterId::register_rtc_cr, 0x400E1860u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kUpdateCalendarField = RuntimeFieldRef{FieldId::field_rtc_cr_updcal, RuntimeRegisterRef{RegisterId::register_rtc_cr, 0x400E1860u, 0u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kUpdateAckField = RuntimeFieldRef{FieldId::field_rtc_sr_ackupd, RuntimeRegisterRef{RegisterId::register_rtc_sr, 0x400E1860u, 24u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kAlarmEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAlarmInterruptEnableField = RuntimeFieldRef{FieldId::field_rtc_ier_alren, RuntimeRegisterRef{RegisterId::register_rtc_ier, 0x400E1860u, 32u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kSecondInterruptEnableField = RuntimeFieldRef{FieldId::field_rtc_ier_secen, RuntimeRegisterRef{RegisterId::register_rtc_ier, 0x400E1860u, 32u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kTimeEventInterruptEnableField = RuntimeFieldRef{FieldId::field_rtc_ier_timen, RuntimeRegisterRef{RegisterId::register_rtc_ier, 0x400E1860u, 32u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kCalendarEventInterruptEnableField = RuntimeFieldRef{FieldId::field_rtc_ier_calen, RuntimeRegisterRef{RegisterId::register_rtc_ier, 0x400E1860u, 32u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kStatusAlarmField = RuntimeFieldRef{FieldId::field_rtc_sr_alarm, RuntimeRegisterRef{RegisterId::register_rtc_sr, 0x400E1860u, 24u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kStatusSecondField = RuntimeFieldRef{FieldId::field_rtc_sr_sec, RuntimeRegisterRef{RegisterId::register_rtc_sr, 0x400E1860u, 24u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kStatusTimeEventField = RuntimeFieldRef{FieldId::field_rtc_sr_timev, RuntimeRegisterRef{RegisterId::register_rtc_sr, 0x400E1860u, 24u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kStatusCalendarEventField = RuntimeFieldRef{FieldId::field_rtc_sr_calev, RuntimeRegisterRef{RegisterId::register_rtc_sr, 0x400E1860u, 24u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kStatusTamperErrorField = RuntimeFieldRef{FieldId::field_rtc_sr_tderr, RuntimeRegisterRef{RegisterId::register_rtc_sr, 0x400E1860u, 24u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kClearAlarmField = RuntimeFieldRef{FieldId::field_rtc_sccr_alrclr, RuntimeRegisterRef{RegisterId::register_rtc_sccr, 0x400E1860u, 28u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kClearSecondField = RuntimeFieldRef{FieldId::field_rtc_sccr_secclr, RuntimeRegisterRef{RegisterId::register_rtc_sccr, 0x400E1860u, 28u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kClearTimeEventField = RuntimeFieldRef{FieldId::field_rtc_sccr_timclr, RuntimeRegisterRef{RegisterId::register_rtc_sccr, 0x400E1860u, 28u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kClearCalendarEventField = RuntimeFieldRef{FieldId::field_rtc_sccr_calclr, RuntimeRegisterRef{RegisterId::register_rtc_sccr, 0x400E1860u, 28u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kClearTamperErrorField = RuntimeFieldRef{FieldId::field_rtc_sccr_tderrclr, RuntimeRegisterRef{RegisterId::register_rtc_sccr, 0x400E1860u, 28u, true}, 5u, 1u, true};
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
