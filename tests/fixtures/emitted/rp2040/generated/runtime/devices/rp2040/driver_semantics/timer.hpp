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
struct TimerSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kCounterBits = 0u;
  static constexpr std::uint32_t kChannelCount = 0u;
  static constexpr bool kHasCompare = false;
  static constexpr bool kHasCapture = false;
  static constexpr bool kHasEncoder = false;
  static constexpr bool kHasPwm = false;
  static constexpr bool kHasOnePulse = false;
  static constexpr bool kHasCenterAligned = false;
  static constexpr bool kHasComplementaryOutputs = false;
  static constexpr bool kHasDeadtime = false;
  static constexpr bool kHasBreakInput = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kEventRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCounterRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModuleDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateGenerationField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOnePulseField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAutoReloadPreloadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClockSourceField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderPositionEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderSpeedEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderPhaseEdgeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr std::uint32_t kUpdateIrqNumber = 0xFFFFFFFFu;
  static constexpr std::uint32_t kCaptureIrqNumber = 0xFFFFFFFFu;
  static constexpr std::uint32_t kBreakIrqNumber = 0xFFFFFFFFu;
  static constexpr std::uint32_t kTriggerIrqNumber = 0xFFFFFFFFu;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

template<>
struct TimerSemanticTraits<PeripheralId::TIMER> {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_timer_raspberrypi_rp2040_timer_v1;
  static constexpr std::uint32_t kCounterBits = 0u;
  static constexpr std::uint32_t kChannelCount = 0u;
  static constexpr bool kHasCompare = false;
  static constexpr bool kHasCapture = false;
  static constexpr bool kHasEncoder = false;
  static constexpr bool kHasPwm = false;
  static constexpr bool kHasOnePulse = false;
  static constexpr bool kHasCenterAligned = false;
  static constexpr bool kHasComplementaryOutputs = false;
  static constexpr bool kHasDeadtime = false;
  static constexpr bool kHasBreakInput = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kEventRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCounterRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModuleDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateGenerationField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOnePulseField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAutoReloadPreloadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClockSourceField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderPositionEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderSpeedEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEncoderPhaseEdgeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDirectionField = kInvalidFieldRef;
  static constexpr std::uint32_t kUpdateIrqNumber = 0xFFFFFFFFu;
  static constexpr std::uint32_t kCaptureIrqNumber = 0xFFFFFFFFu;
  static constexpr std::uint32_t kBreakIrqNumber = 0xFFFFFFFFu;
  static constexpr std::uint32_t kTriggerIrqNumber = 0xFFFFFFFFu;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

template<PeripheralId Id, std::size_t ChannelIndex>
struct TimerChannelSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr bool kSupportsCompare = false;
  static constexpr bool kSupportsCapture = false;
  static constexpr bool kSupportsEncoderInput = false;
  static constexpr bool kSupportsPwm = false;
  static constexpr bool kSupportsComplementaryOutput = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCounterRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCaptureRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPreloadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCaptureSelectField = kInvalidFieldRef;
};

template<>
struct TimerChannelSemanticTraits<PeripheralId::TIMER, 0u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsCompare = false;
  static constexpr bool kSupportsCapture = false;
  static constexpr bool kSupportsEncoderInput = false;
  static constexpr bool kSupportsPwm = false;
  static constexpr bool kSupportsComplementaryOutput = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCounterRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCaptureRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPreloadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCaptureSelectField = kInvalidFieldRef;
};

inline constexpr std::array<PeripheralId, 0> kTimerSemanticPeripherals = {};

// complete-rp2040-semantics Phase D: per-controller timer HW facts.
enum class RuntimeTimerCtrlId : std::uint8_t {
  None = 0,
  TIMER = 1,
};

template<RuntimeTimerCtrlId Id>
struct TimerControllerHwTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint32_t kBaseAddress = 0u;
  static constexpr std::uint8_t kCounterBits = 0u;
  static constexpr std::uint8_t kAlarmCount = 0u;
  static constexpr std::uint8_t kDreqAlarmBase = 0u;
};

template<>
struct TimerControllerHwTraits<RuntimeTimerCtrlId::TIMER> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x40054000u;
  static constexpr std::uint8_t kCounterBits = 64u;
  static constexpr std::uint8_t kAlarmCount = 4u;
  static constexpr std::uint8_t kDreqAlarmBase = 39u;
};

}
}
}
}
}
}
}
