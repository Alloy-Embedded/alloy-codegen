#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include "common.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
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
  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};
  static constexpr std::uint32_t kMaxPrescaler = 0u;
  static constexpr std::uint32_t kMaxAutoReload = 0u;
  static constexpr std::array<std::uint8_t, 0> kTriggerSources = {};
  static constexpr std::array<std::uint8_t, 0> kMasterOutputModes = {};
  static constexpr bool kSupportsDmaBurst = false;
  static constexpr bool kSupportsRepetitionCounter = false;
  static constexpr bool kSupportsXorInput = false;
};

template<>
struct TimerSemanticTraits<PeripheralId::TCA0> {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_timer_microchip_avr_da_tca_v1;
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
  static constexpr std::uint32_t kMaxPrescaler = 0u;
  static constexpr std::uint32_t kMaxAutoReload = 0u;
  static constexpr std::array<std::uint8_t, 0> kTriggerSources = {};
  static constexpr std::array<std::uint8_t, 0> kMasterOutputModes = {};
  static constexpr bool kSupportsDmaBurst = false;
  static constexpr bool kSupportsRepetitionCounter = false;
  static constexpr bool kSupportsXorInput = false;
  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};
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

struct TimerChannelHardwareLut {
  bool supports_compare;
  bool supports_capture;
  bool supports_encoder_input;
  bool supports_pwm;
  bool supports_complementary_output;
  RuntimeRegisterRef control_register;
  RuntimeRegisterRef status_register;
  RuntimeRegisterRef compare_register;
  RuntimeRegisterRef secondary_compare_register;
  RuntimeRegisterRef period_register;
  RuntimeRegisterRef counter_register;
  RuntimeRegisterRef capture_register;
  RuntimeFieldRef enable_field;
  RuntimeFieldRef interrupt_enable_field;
  RuntimeFieldRef interrupt_flag_field;
  RuntimeFieldRef mode_field;
  RuntimeFieldRef preload_field;
  RuntimeFieldRef output_enable_field;
  RuntimeFieldRef output_polarity_field;
  RuntimeFieldRef complementary_output_enable_field;
  RuntimeFieldRef capture_select_field;
};

inline constexpr std::array<TimerChannelHardwareLut, 1> kTimerChannelHardwareLut = {{
  {false, false, false, false, false, kInvalidRegisterRef, kInvalidRegisterRef, kInvalidRegisterRef, kInvalidRegisterRef, kInvalidRegisterRef, kInvalidRegisterRef, kInvalidRegisterRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef},
}};

template<std::size_t Index>
struct TimerChannelTraitsBase {
  static constexpr auto& kFacts = kTimerChannelHardwareLut[Index];
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsCompare = kFacts.supports_compare;
  static constexpr bool kSupportsCapture = kFacts.supports_capture;
  static constexpr bool kSupportsEncoderInput = kFacts.supports_encoder_input;
  static constexpr bool kSupportsPwm = kFacts.supports_pwm;
  static constexpr bool kSupportsComplementaryOutput = kFacts.supports_complementary_output;
  static constexpr RuntimeRegisterRef kControlRegister = kFacts.control_register;
  static constexpr RuntimeRegisterRef kStatusRegister = kFacts.status_register;
  static constexpr RuntimeRegisterRef kCompareRegister = kFacts.compare_register;
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kFacts.secondary_compare_register;
  static constexpr RuntimeRegisterRef kPeriodRegister = kFacts.period_register;
  static constexpr RuntimeRegisterRef kCounterRegister = kFacts.counter_register;
  static constexpr RuntimeRegisterRef kCaptureRegister = kFacts.capture_register;
  static constexpr RuntimeFieldRef kEnableField = kFacts.enable_field;
  static constexpr RuntimeFieldRef kInterruptEnableField = kFacts.interrupt_enable_field;
  static constexpr RuntimeFieldRef kInterruptFlagField = kFacts.interrupt_flag_field;
  static constexpr RuntimeFieldRef kModeField = kFacts.mode_field;
  static constexpr RuntimeFieldRef kPreloadField = kFacts.preload_field;
  static constexpr RuntimeFieldRef kOutputEnableField = kFacts.output_enable_field;
  static constexpr RuntimeFieldRef kOutputPolarityField = kFacts.output_polarity_field;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kFacts.complementary_output_enable_field;
  static constexpr RuntimeFieldRef kCaptureSelectField = kFacts.capture_select_field;
};

template<> struct TimerChannelSemanticTraits<PeripheralId::TCA0, 0u> : TimerChannelTraitsBase<0> {};

inline constexpr std::array<PeripheralId, 0> kTimerSemanticPeripherals = {};

// complete-rp2040-semantics Phase D: per-controller timer HW facts.
enum class RuntimeTimerCtrlId : std::uint8_t {
  None = 0,
};

template<RuntimeTimerCtrlId Id>
struct TimerControllerHwTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint32_t kBaseAddress = 0u;
  static constexpr std::uint8_t kCounterBits = 0u;
  static constexpr std::uint8_t kAlarmCount = 0u;
  static constexpr std::uint8_t kDreqAlarmBase = 0u;
};

}
}
}
}
}
}
}
