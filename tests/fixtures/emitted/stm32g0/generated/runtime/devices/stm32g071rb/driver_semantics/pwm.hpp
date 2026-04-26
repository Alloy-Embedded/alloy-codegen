#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include "common.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g071rb {
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
  static constexpr std::uint32_t kMaxPrescaler = 0u;
  static constexpr std::uint32_t kMaxPeriod = 0u;
  static constexpr std::array<std::uint8_t, 0> kDeadtimeOptions = {};
  static constexpr std::array<std::uint8_t, 0> kSupportedAlignments = {};
  static constexpr std::array<std::uint8_t, 0> kBreakInputs = {};
  static constexpr bool kSupportsDeadtime = false;
  static constexpr bool kSupportsBreakInput = false;
  static constexpr bool kSupportsComplementaryOutputs = false;
  static constexpr bool kSupportsAsymmetricPwm = false;
  static constexpr bool kSupportsCombinedPwm = false;
};

template<>
struct PwmSemanticTraits<PeripheralId::TIM1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_timer_st_tim;
  static constexpr std::uint32_t kCounterBits = 16u;
  static constexpr std::uint32_t kChannelCount = 4u;
  static constexpr bool kHasComplementaryOutputs = true;
  static constexpr bool kHasDeadtime = true;
  static constexpr bool kHasFaultInput = true;
  static constexpr bool kHasCenterAligned = true;
  static constexpr bool kHasSynchronizedUpdate = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_tim1_cr1, 0x40012C00u, 0u, true};
  static constexpr RuntimeRegisterRef kOutputEnableRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 16u, true};
  static constexpr RuntimeRegisterRef kClockRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 40u, true};
  static constexpr RuntimeRegisterRef kSyncRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 20u, true};
  static constexpr RuntimeFieldRef kMasterOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 15u, 1u, true};
  static constexpr RuntimeFieldRef kLoadField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 20u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kClearLoadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClockPrescalerField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 40u, true}, 0u, 16u, true};
  static constexpr std::uint32_t kMaxPrescaler = 65535u;
  static constexpr std::uint32_t kMaxPeriod = 65535u;
  static constexpr std::array<std::uint8_t, 4> kDeadtimeOptions = {{0u, 1u, 2u, 3u}};
  static constexpr std::array<std::uint8_t, 4> kSupportedAlignments = {{0u, 1u, 2u, 3u}};
  static constexpr std::array<std::uint8_t, 1> kBreakInputs = {{0u}};
  static constexpr bool kSupportsDeadtime = true;
  static constexpr bool kSupportsBreakInput = true;
  static constexpr bool kSupportsComplementaryOutputs = true;
  static constexpr bool kSupportsAsymmetricPwm = true;
  static constexpr bool kSupportsCombinedPwm = true;
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
struct PwmChannelSemanticTraits<PeripheralId::TIM1, 0u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 24u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 52u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 12u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptFlagField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 16u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kModeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 24u, true}, 4u, 3u, true};
  static constexpr RuntimeFieldRef kPolarityField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_tim1_cr1, 0x40012C00u, 0u, true}, 5u, 2u, true};
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 52u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::TIM1, 1u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 24u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 56u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 12u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptFlagField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 16u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kModeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 24u, true}, 12u, 3u, true};
  static constexpr RuntimeFieldRef kPolarityField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_tim1_cr1, 0x40012C00u, 0u, true}, 5u, 2u, true};
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 56u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::TIM1, 2u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 28u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 60u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 12u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptFlagField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 16u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kModeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 28u, true}, 4u, 3u, true};
  static constexpr RuntimeFieldRef kPolarityField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 10u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_tim1_cr1, 0x40012C00u, 0u, true}, 5u, 2u, true};
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 60u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::TIM1, 3u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = false;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 28u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 64u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 12u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 12u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptFlagField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 16u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kModeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 28u, true}, 12u, 3u, true};
  static constexpr RuntimeFieldRef kPolarityField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 13u, 1u, true};
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCenterAlignedField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_tim1_cr1, 0x40012C00u, 0u, true}, 5u, 2u, true};
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 64u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true};
};

inline constexpr std::array<PeripheralId, 1> kPwmSemanticPeripherals = {{
  PeripheralId::TIM1,
}};

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


// extend-pwm-coverage-all-mcus Phase A: STM32 TIM PWM facts.
enum class RuntimeStmTimerKind : std::uint8_t {
  None = 0,
  Advanced = 1,
  General = 2,
};

enum class RuntimeStmTimerPwmId : std::uint8_t {
  None = 0,
  TIM1 = 1,
};

template<RuntimeStmTimerPwmId Id>
struct StmTimerPwmTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint32_t kBaseAddress = 0u;
  static constexpr RuntimeStmTimerKind kKind = RuntimeStmTimerKind::None;
  static constexpr std::uint8_t kChannelCount = 0u;
  static constexpr std::uint8_t kCounterBits = 0u;
  static constexpr std::array<PinId, 0> kValidCh1Pins = {};
  static constexpr std::array<PinId, 0> kValidCh2Pins = {};
  static constexpr std::array<PinId, 0> kValidCh3Pins = {};
  static constexpr std::array<PinId, 0> kValidCh4Pins = {};
  static constexpr std::array<PinId, 0> kValidCh1NPins = {};
  static constexpr std::array<PinId, 0> kValidCh2NPins = {};
  static constexpr std::array<PinId, 0> kValidCh3NPins = {};
  static constexpr bool kSupportsComplementary = false;
  static constexpr bool kSupportsDeadtime = false;
  static constexpr bool kSupportsBrake = false;
  static constexpr bool kSupportsCenterAligned = false;
  static constexpr std::uint32_t kMaxClockHz = 0u;
};

template<>
struct StmTimerPwmTraits<RuntimeStmTimerPwmId::TIM1> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x40012c00u;
  static constexpr RuntimeStmTimerKind kKind = RuntimeStmTimerKind::Advanced;
  static constexpr std::uint8_t kChannelCount = 4u;
  static constexpr std::uint8_t kCounterBits = 16u;
  static constexpr std::array<PinId, 0> kValidCh1Pins = {};
  static constexpr std::array<PinId, 0> kValidCh2Pins = {};
  static constexpr std::array<PinId, 0> kValidCh3Pins = {};
  static constexpr std::array<PinId, 0> kValidCh4Pins = {};
  static constexpr std::array<PinId, 0> kValidCh1NPins = {};
  static constexpr std::array<PinId, 0> kValidCh2NPins = {};
  static constexpr std::array<PinId, 0> kValidCh3NPins = {};
  static constexpr bool kSupportsComplementary = false;
  static constexpr bool kSupportsDeadtime = false;
  static constexpr bool kSupportsBrake = false;
  static constexpr bool kSupportsCenterAligned = true;
  static constexpr std::uint32_t kMaxClockHz = 0u;
};


// extend-pwm-coverage-all-mcus Phase B: Espressif MCPWM facts.
enum class RuntimeMcpwmId : std::uint8_t {
  None = 0,
};

template<RuntimeMcpwmId Id>
struct McpwmTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint32_t kBaseAddress = 0u;
  static constexpr std::uint8_t kTimerCount = 0u;
  static constexpr std::uint8_t kOutputSignalCount = 0u;
  static constexpr std::array<std::uint16_t, 0> kGpioMatrixSignals = {};
  static constexpr std::array<std::uint16_t, 0> kCaptureSignals = {};
  static constexpr bool kSupportsDeadtime = false;
  static constexpr bool kSupportsCarrierModulation = false;
  static constexpr bool kSupportsFaultInput = false;
};


// extend-pwm-coverage-all-mcus Phase C: NXP iMXRT FlexPWM facts.
enum class RuntimeFlexPwmId : std::uint8_t {
  None = 0,
};

template<RuntimeFlexPwmId Id>
struct FlexPwmTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint32_t kBaseAddress = 0u;
  static constexpr std::uint8_t kSubmoduleCount = 0u;
  static constexpr bool kPairedChannels = false;
  static constexpr bool kSupportsComplementary = false;
  static constexpr bool kSupportsDeadtime = false;
  static constexpr bool kSupportsFaultInput = false;
  static constexpr bool kSupportsForceInitialization = false;
};


// extend-pwm-coverage-all-mcus Phase D: Microchip AVR-DA TCA PWM facts.
enum class RuntimeAvrDaTcaPwmId : std::uint8_t {
  None = 0,
};

template<RuntimeAvrDaTcaPwmId Id>
struct AvrDaTcaPwmTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint32_t kBaseAddress = 0u;
  static constexpr std::array<PinId, 0> kDefaultChannelPins = {};
  static constexpr std::uint8_t kSplitModeChannels = 0u;
  static constexpr std::uint8_t kSingleModeChannels = 0u;
  static constexpr std::uint8_t kCounterBits = 0u;
  static constexpr bool kPortmuxAlt = false;
};


// extend-pwm-coverage-all-mcus Phase D: Microchip SAM E70 PWM/TC facts.
enum class RuntimeSame70PwmKind : std::uint8_t {
  None = 0,
  Pwm = 1,
  Tc = 2,
};

enum class RuntimeSame70PwmId : std::uint8_t {
  None = 0,
};

template<RuntimeSame70PwmId Id>
struct Same70PwmTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint32_t kBaseAddress = 0u;
  static constexpr RuntimeSame70PwmKind kKind = RuntimeSame70PwmKind::None;
  static constexpr std::uint8_t kChannelCount = 0u;
  static constexpr bool kSupportsDeadTime = false;
  static constexpr bool kSupportsFaultInput = false;
  static constexpr bool kSupportsDma = false;
};

}
}
}
}
}
}
}
