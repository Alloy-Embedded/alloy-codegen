#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include "common.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
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
struct PwmSemanticTraits<PeripheralId::PWM1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_pwm_nxp_pwm;
  static constexpr std::uint32_t kCounterBits = 16u;
  static constexpr std::uint32_t kChannelCount = 4u;
  static constexpr bool kHasComplementaryOutputs = true;
  static constexpr bool kHasDeadtime = true;
  static constexpr bool kHasFaultInput = true;
  static constexpr bool kHasCenterAligned = true;
  static constexpr bool kHasSynchronizedUpdate = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_pwm1_mctrl, 0x403DC000u, 0u, true};
  static constexpr RuntimeRegisterRef kOutputEnableRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 398u, true};
  static constexpr RuntimeRegisterRef kClockRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSyncRegister = RuntimeRegisterRef{RegisterId::register_pwm1_mctrl, 0x403DC000u, 0u, true};
  static constexpr RuntimeFieldRef kMasterOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kLoadField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm1_mctrl, 0x403DC000u, 0u, true}, 0u, 4u, true};
  static constexpr RuntimeFieldRef kClearLoadField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm1_mctrl, 0x403DC000u, 0u, true}, 4u, 4u, true};
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
struct PwmSemanticTraits<PeripheralId::PWM2> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_pwm_nxp_pwm;
  static constexpr std::uint32_t kCounterBits = 16u;
  static constexpr std::uint32_t kChannelCount = 4u;
  static constexpr bool kHasComplementaryOutputs = true;
  static constexpr bool kHasDeadtime = true;
  static constexpr bool kHasFaultInput = true;
  static constexpr bool kHasCenterAligned = true;
  static constexpr bool kHasSynchronizedUpdate = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_pwm2_mctrl, 0x403E0000u, 0u, true};
  static constexpr RuntimeRegisterRef kOutputEnableRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 398u, true};
  static constexpr RuntimeRegisterRef kClockRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSyncRegister = RuntimeRegisterRef{RegisterId::register_pwm2_mctrl, 0x403E0000u, 0u, true};
  static constexpr RuntimeFieldRef kMasterOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kLoadField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm2_mctrl, 0x403E0000u, 0u, true}, 0u, 4u, true};
  static constexpr RuntimeFieldRef kClearLoadField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm2_mctrl, 0x403E0000u, 0u, true}, 4u, 4u, true};
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
struct PwmSemanticTraits<PeripheralId::PWM3> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_pwm_nxp_pwm;
  static constexpr std::uint32_t kCounterBits = 16u;
  static constexpr std::uint32_t kChannelCount = 4u;
  static constexpr bool kHasComplementaryOutputs = true;
  static constexpr bool kHasDeadtime = true;
  static constexpr bool kHasFaultInput = true;
  static constexpr bool kHasCenterAligned = true;
  static constexpr bool kHasSynchronizedUpdate = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_pwm3_mctrl, 0x403E4000u, 0u, true};
  static constexpr RuntimeRegisterRef kOutputEnableRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 398u, true};
  static constexpr RuntimeRegisterRef kClockRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSyncRegister = RuntimeRegisterRef{RegisterId::register_pwm3_mctrl, 0x403E4000u, 0u, true};
  static constexpr RuntimeFieldRef kMasterOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kLoadField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm3_mctrl, 0x403E4000u, 0u, true}, 0u, 4u, true};
  static constexpr RuntimeFieldRef kClearLoadField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm3_mctrl, 0x403E4000u, 0u, true}, 4u, 4u, true};
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
struct PwmSemanticTraits<PeripheralId::PWM4> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_pwm_nxp_pwm;
  static constexpr std::uint32_t kCounterBits = 16u;
  static constexpr std::uint32_t kChannelCount = 4u;
  static constexpr bool kHasComplementaryOutputs = true;
  static constexpr bool kHasDeadtime = true;
  static constexpr bool kHasFaultInput = true;
  static constexpr bool kHasCenterAligned = true;
  static constexpr bool kHasSynchronizedUpdate = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_pwm4_mctrl, 0x403E8000u, 0u, true};
  static constexpr RuntimeRegisterRef kOutputEnableRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 398u, true};
  static constexpr RuntimeRegisterRef kClockRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSyncRegister = RuntimeRegisterRef{RegisterId::register_pwm4_mctrl, 0x403E8000u, 0u, true};
  static constexpr RuntimeFieldRef kMasterOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kLoadField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm4_mctrl, 0x403E8000u, 0u, true}, 0u, 4u, true};
  static constexpr RuntimeFieldRef kClearLoadField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm4_mctrl, 0x403E8000u, 0u, true}, 4u, 4u, true};
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
struct PwmChannelSemanticTraits<PeripheralId::PWM1, 0u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 6u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 16u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 18u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 12u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 40u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 12u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 16u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 40u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 42u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM1, 1u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 102u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 112u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 114u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 108u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 136u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 108u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 112u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 136u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 138u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM1, 2u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 198u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 208u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 210u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 204u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 232u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 10u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 204u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 208u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 232u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 234u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM1, 3u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 294u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 304u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 306u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 300u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 328u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 11u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 300u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 304u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 328u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 330u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM2, 0u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 6u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 16u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 18u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 12u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 40u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 12u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 16u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 40u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 42u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM2, 1u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 102u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 112u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 114u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 108u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 136u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 108u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 112u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 136u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 138u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM2, 2u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 198u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 208u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 210u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 204u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 232u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 10u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 204u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 208u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 232u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 234u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM2, 3u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 294u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 304u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 306u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 300u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 328u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 11u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 300u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 304u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 328u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 330u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM3, 0u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 6u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 16u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 18u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 12u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 40u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 12u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 16u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 40u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 42u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM3, 1u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 102u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 112u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 114u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 108u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 136u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 108u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 112u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 136u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 138u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM3, 2u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 198u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 208u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 210u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 204u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 232u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 10u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 204u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 208u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 232u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 234u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM3, 3u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 294u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 304u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 306u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 300u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 328u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 11u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 300u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 304u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 328u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 330u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM4, 0u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 6u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 16u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 18u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 12u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 40u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 12u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 16u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 40u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 42u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM4, 1u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 102u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 112u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 114u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 108u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 136u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 108u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 112u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 136u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 138u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM4, 2u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 198u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 208u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 210u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 204u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 232u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 10u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 204u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 208u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 232u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 234u, true}, 0u, 16u, true};
};

template<>
struct PwmChannelSemanticTraits<PeripheralId::PWM4, 3u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 294u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 304u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 306u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 300u, true};
  static constexpr RuntimeRegisterRef kDeadtimeRegister = RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 328u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 11u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInterruptFlagField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 300u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDutyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 304u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeRiseField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 328u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kDeadtimeFallField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 330u, true}, 0u, 16u, true};
};

inline constexpr std::array<PeripheralId, 4> kPwmSemanticPeripherals = {{
  PeripheralId::PWM1,
  PeripheralId::PWM2,
  PeripheralId::PWM3,
  PeripheralId::PWM4,
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
  PWM1 = 1,
  PWM2 = 2,
  PWM3 = 3,
  PWM4 = 4,
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

template<>
struct FlexPwmTraits<RuntimeFlexPwmId::PWM1> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x403dc000u;
  static constexpr std::uint8_t kSubmoduleCount = 4u;
  static constexpr bool kPairedChannels = true;
  static constexpr bool kSupportsComplementary = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr bool kSupportsFaultInput = true;
  static constexpr bool kSupportsForceInitialization = true;
};

template<>
struct FlexPwmTraits<RuntimeFlexPwmId::PWM2> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x403e0000u;
  static constexpr std::uint8_t kSubmoduleCount = 4u;
  static constexpr bool kPairedChannels = true;
  static constexpr bool kSupportsComplementary = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr bool kSupportsFaultInput = true;
  static constexpr bool kSupportsForceInitialization = true;
};

template<>
struct FlexPwmTraits<RuntimeFlexPwmId::PWM3> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x403e4000u;
  static constexpr std::uint8_t kSubmoduleCount = 4u;
  static constexpr bool kPairedChannels = true;
  static constexpr bool kSupportsComplementary = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr bool kSupportsFaultInput = true;
  static constexpr bool kSupportsForceInitialization = true;
};

template<>
struct FlexPwmTraits<RuntimeFlexPwmId::PWM4> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x403e8000u;
  static constexpr std::uint8_t kSubmoduleCount = 4u;
  static constexpr bool kPairedChannels = true;
  static constexpr bool kSupportsComplementary = true;
  static constexpr bool kSupportsDeadtime = true;
  static constexpr bool kSupportsFaultInput = true;
  static constexpr bool kSupportsForceInitialization = true;
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
