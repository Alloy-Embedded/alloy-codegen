#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include "common.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
namespace driver_semantics {
template<PeripheralId Id>
struct PwmSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kCounterBits = 0u;
  static constexpr std::uint32_t kChannelCount = 0u;
  static constexpr bool kHasComplementaryOutputs = false;
  static constexpr bool kHasDeadtime = false;
  static constexpr bool kHasFaultInput = false;
  static constexpr bool kHasCenterAligned = false;
  static constexpr bool kHasSynchronizedUpdate = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kOutputEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kClockRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSyncRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kMasterOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kLoadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClearLoadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClockPrescalerField = kInvalidFieldRef;
};

template<>
struct PwmSemanticTraits<PeripheralId::PWM> {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_pwm_raspberrypi_rp2040_pwm_v1;
  static constexpr std::uint32_t kCounterBits = 0u;
  static constexpr std::uint32_t kChannelCount = 0u;
  static constexpr bool kHasComplementaryOutputs = false;
  static constexpr bool kHasDeadtime = false;
  static constexpr bool kHasFaultInput = false;
  static constexpr bool kHasCenterAligned = false;
  static constexpr bool kHasSynchronizedUpdate = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kOutputEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kClockRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSyncRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kMasterOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kLoadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClearLoadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClockPrescalerField = kInvalidFieldRef;
};

template<PeripheralId Id, std::size_t ChannelIndex>
struct PwmChannelSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr bool kSupportsComplementaryOutput = false;
  static constexpr bool kSupportsDeadtime = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDeadtimeRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDutyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDeadtimeRiseField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDeadtimeFallField = kInvalidFieldRef;
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM, 0u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = false;
  static constexpr bool kSupportsDeadtime = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDeadtimeRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDutyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDeadtimeRiseField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDeadtimeFallField = kInvalidFieldRef;
};

inline constexpr std::array<PeripheralId, 0> kPwmSemanticPeripherals = {};

// complete-rp2040-semantics Phase D: per-slice PWM HW facts.
template<std::uint8_t SliceIndex>
struct PwmSliceHwTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint8_t kChannelAPin = 0u;
  static constexpr std::uint8_t kChannelBPin = 0u;
  static constexpr std::uint8_t kCounterBits = 0u;
  static constexpr std::uint16_t kClockDivMinQ4 = 0u;
  static constexpr std::uint16_t kClockDivMaxQ4 = 0u;
};

template<>
struct PwmSliceHwTraits<0> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kChannelAPin = 0u;
  static constexpr std::uint8_t kChannelBPin = 1u;
  static constexpr std::uint8_t kCounterBits = 16u;
  static constexpr std::uint16_t kClockDivMinQ4 = 16u;
  static constexpr std::uint16_t kClockDivMaxQ4 = 4080u;
};

template<>
struct PwmSliceHwTraits<1> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kChannelAPin = 2u;
  static constexpr std::uint8_t kChannelBPin = 3u;
  static constexpr std::uint8_t kCounterBits = 16u;
  static constexpr std::uint16_t kClockDivMinQ4 = 16u;
  static constexpr std::uint16_t kClockDivMaxQ4 = 4080u;
};

template<>
struct PwmSliceHwTraits<2> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kChannelAPin = 4u;
  static constexpr std::uint8_t kChannelBPin = 5u;
  static constexpr std::uint8_t kCounterBits = 16u;
  static constexpr std::uint16_t kClockDivMinQ4 = 16u;
  static constexpr std::uint16_t kClockDivMaxQ4 = 4080u;
};

template<>
struct PwmSliceHwTraits<3> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kChannelAPin = 6u;
  static constexpr std::uint8_t kChannelBPin = 7u;
  static constexpr std::uint8_t kCounterBits = 16u;
  static constexpr std::uint16_t kClockDivMinQ4 = 16u;
  static constexpr std::uint16_t kClockDivMaxQ4 = 4080u;
};

template<>
struct PwmSliceHwTraits<4> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kChannelAPin = 8u;
  static constexpr std::uint8_t kChannelBPin = 9u;
  static constexpr std::uint8_t kCounterBits = 16u;
  static constexpr std::uint16_t kClockDivMinQ4 = 16u;
  static constexpr std::uint16_t kClockDivMaxQ4 = 4080u;
};

template<>
struct PwmSliceHwTraits<5> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kChannelAPin = 10u;
  static constexpr std::uint8_t kChannelBPin = 11u;
  static constexpr std::uint8_t kCounterBits = 16u;
  static constexpr std::uint16_t kClockDivMinQ4 = 16u;
  static constexpr std::uint16_t kClockDivMaxQ4 = 4080u;
};

template<>
struct PwmSliceHwTraits<6> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kChannelAPin = 12u;
  static constexpr std::uint8_t kChannelBPin = 13u;
  static constexpr std::uint8_t kCounterBits = 16u;
  static constexpr std::uint16_t kClockDivMinQ4 = 16u;
  static constexpr std::uint16_t kClockDivMaxQ4 = 4080u;
};

template<>
struct PwmSliceHwTraits<7> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kChannelAPin = 14u;
  static constexpr std::uint8_t kChannelBPin = 15u;
  static constexpr std::uint8_t kCounterBits = 16u;
  static constexpr std::uint16_t kClockDivMinQ4 = 16u;
  static constexpr std::uint16_t kClockDivMaxQ4 = 4080u;
};

}
}
}
}
}
}
}
