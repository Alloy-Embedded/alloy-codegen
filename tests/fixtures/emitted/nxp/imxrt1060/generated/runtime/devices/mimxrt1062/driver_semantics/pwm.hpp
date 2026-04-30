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

struct PwmHardwareLut {
  BackendSchemaId schema_id;
  std::uint32_t counter_bits;
  std::uint32_t channel_count;
  bool has_complementary_outputs;
  bool has_deadtime;
  bool has_fault_input;
  bool has_center_aligned;
  bool has_synchronized_update;
  RuntimeRegisterRef control_register;
  RuntimeRegisterRef output_enable_register;
  RuntimeRegisterRef status_register;
  RuntimeRegisterRef clock_register;
  RuntimeRegisterRef sync_register;
  RuntimeFieldRef master_output_enable_field;
  RuntimeFieldRef load_field;
  RuntimeFieldRef clear_load_field;
  RuntimeFieldRef clock_prescaler_field;
  std::uint32_t max_prescaler;
  std::uint32_t max_period;
  bool supports_deadtime;
  bool supports_break_input;
  bool supports_complementary_outputs;
  bool supports_asymmetric_pwm;
  bool supports_combined_pwm;
};

inline constexpr std::array<PwmHardwareLut, 4> kPwmHardwareLut = {{
  {BackendSchemaId::schema_alloy_pwm_nxp_pwm, 16u, 4u, true, true, true, true, true, RuntimeRegisterRef{RegisterId::register_pwm1_mctrl, 0x403DC000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 398u, true}, kInvalidRegisterRef, RuntimeRegisterRef{RegisterId::register_pwm1_mctrl, 0x403DC000u, 0u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm1_mctrl, 0x403DC000u, 0u, true}, 0u, 4u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm1_mctrl, 0x403DC000u, 0u, true}, 4u, 4u, true}, kInvalidFieldRef, 0u, 0u, false, false, false, false, false},
  {BackendSchemaId::schema_alloy_pwm_nxp_pwm, 16u, 4u, true, true, true, true, true, RuntimeRegisterRef{RegisterId::register_pwm2_mctrl, 0x403E0000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 398u, true}, kInvalidRegisterRef, RuntimeRegisterRef{RegisterId::register_pwm2_mctrl, 0x403E0000u, 0u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm2_mctrl, 0x403E0000u, 0u, true}, 0u, 4u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm2_mctrl, 0x403E0000u, 0u, true}, 4u, 4u, true}, kInvalidFieldRef, 0u, 0u, false, false, false, false, false},
  {BackendSchemaId::schema_alloy_pwm_nxp_pwm, 16u, 4u, true, true, true, true, true, RuntimeRegisterRef{RegisterId::register_pwm3_mctrl, 0x403E4000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 398u, true}, kInvalidRegisterRef, RuntimeRegisterRef{RegisterId::register_pwm3_mctrl, 0x403E4000u, 0u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm3_mctrl, 0x403E4000u, 0u, true}, 0u, 4u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm3_mctrl, 0x403E4000u, 0u, true}, 4u, 4u, true}, kInvalidFieldRef, 0u, 0u, false, false, false, false, false},
  {BackendSchemaId::schema_alloy_pwm_nxp_pwm, 16u, 4u, true, true, true, true, true, RuntimeRegisterRef{RegisterId::register_pwm4_mctrl, 0x403E8000u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 398u, true}, kInvalidRegisterRef, RuntimeRegisterRef{RegisterId::register_pwm4_mctrl, 0x403E8000u, 0u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm4_mctrl, 0x403E8000u, 0u, true}, 0u, 4u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pwm4_mctrl, 0x403E8000u, 0u, true}, 4u, 4u, true}, kInvalidFieldRef, 0u, 0u, false, false, false, false, false},
}};

template<std::size_t Index>
struct PwmTraitsBase {
  static constexpr auto& kFacts = kPwmHardwareLut[Index];
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = kFacts.schema_id;
  static constexpr std::uint32_t kCounterBits = kFacts.counter_bits;
  static constexpr std::uint32_t kChannelCount = kFacts.channel_count;
  static constexpr bool kHasComplementaryOutputs = kFacts.has_complementary_outputs;
  static constexpr bool kHasDeadtime = kFacts.has_deadtime;
  static constexpr bool kHasFaultInput = kFacts.has_fault_input;
  static constexpr bool kHasCenterAligned = kFacts.has_center_aligned;
  static constexpr bool kHasSynchronizedUpdate = kFacts.has_synchronized_update;
  static constexpr RuntimeRegisterRef kControlRegister = kFacts.control_register;
  static constexpr RuntimeRegisterRef kOutputEnableRegister = kFacts.output_enable_register;
  static constexpr RuntimeRegisterRef kStatusRegister = kFacts.status_register;
  static constexpr RuntimeRegisterRef kClockRegister = kFacts.clock_register;
  static constexpr RuntimeRegisterRef kSyncRegister = kFacts.sync_register;
  static constexpr RuntimeFieldRef kMasterOutputEnableField = kFacts.master_output_enable_field;
  static constexpr RuntimeFieldRef kLoadField = kFacts.load_field;
  static constexpr RuntimeFieldRef kClearLoadField = kFacts.clear_load_field;
  static constexpr RuntimeFieldRef kClockPrescalerField = kFacts.clock_prescaler_field;
  static constexpr std::uint32_t kMaxPrescaler = kFacts.max_prescaler;
  static constexpr std::uint32_t kMaxPeriod = kFacts.max_period;
  static constexpr bool kSupportsDeadtime = kFacts.supports_deadtime;
  static constexpr bool kSupportsBreakInput = kFacts.supports_break_input;
  static constexpr bool kSupportsComplementaryOutputs = kFacts.supports_complementary_outputs;
  static constexpr bool kSupportsAsymmetricPwm = kFacts.supports_asymmetric_pwm;
  static constexpr bool kSupportsCombinedPwm = kFacts.supports_combined_pwm;
};

template<>
struct PwmSemanticTraits<PeripheralId::PWM1> : PwmTraitsBase<0> {
  static constexpr std::array<std::uint8_t, 0> kDeadtimeOptions = {};
  static constexpr std::array<std::uint8_t, 0> kSupportedAlignments = {};
  static constexpr std::array<std::uint8_t, 0> kBreakInputs = {};
};

template<>
struct PwmSemanticTraits<PeripheralId::PWM2> : PwmTraitsBase<1> {
  static constexpr std::array<std::uint8_t, 0> kDeadtimeOptions = {};
  static constexpr std::array<std::uint8_t, 0> kSupportedAlignments = {};
  static constexpr std::array<std::uint8_t, 0> kBreakInputs = {};
};

template<>
struct PwmSemanticTraits<PeripheralId::PWM3> : PwmTraitsBase<2> {
  static constexpr std::array<std::uint8_t, 0> kDeadtimeOptions = {};
  static constexpr std::array<std::uint8_t, 0> kSupportedAlignments = {};
  static constexpr std::array<std::uint8_t, 0> kBreakInputs = {};
};

template<>
struct PwmSemanticTraits<PeripheralId::PWM4> : PwmTraitsBase<3> {
  static constexpr std::array<std::uint8_t, 0> kDeadtimeOptions = {};
  static constexpr std::array<std::uint8_t, 0> kSupportedAlignments = {};
  static constexpr std::array<std::uint8_t, 0> kBreakInputs = {};
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

struct PwmChannelHardwareLut {
  bool supports_complementary_output;
  bool supports_deadtime;
  RuntimeRegisterRef control_register;
  RuntimeRegisterRef compare_register;
  RuntimeRegisterRef secondary_compare_register;
  RuntimeRegisterRef period_register;
  RuntimeRegisterRef deadtime_register;
  RuntimeFieldRef enable_field;
  RuntimeFieldRef interrupt_enable_field;
  RuntimeFieldRef interrupt_flag_field;
  RuntimeFieldRef mode_field;
  RuntimeFieldRef polarity_field;
  RuntimeFieldRef complementary_output_enable_field;
  RuntimeFieldRef center_aligned_field;
  RuntimeFieldRef period_field;
  RuntimeFieldRef duty_field;
  RuntimeFieldRef deadtime_rise_field;
  RuntimeFieldRef deadtime_fall_field;
};

inline constexpr std::array<PwmChannelHardwareLut, 16> kPwmChannelHardwareLut = {{
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 6u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 16u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 18u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 12u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 40u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 8u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 4u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 12u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 16u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 40u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 42u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 102u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 112u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 114u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 108u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 136u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 9u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 5u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 108u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 112u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 136u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 138u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 198u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 208u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 210u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 204u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 232u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 10u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 6u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 204u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 208u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 232u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 234u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 294u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 304u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 306u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 300u, true}, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 328u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 11u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 384u, true}, 7u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 300u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 304u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 328u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403DC000u, 330u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 6u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 16u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 18u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 12u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 40u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 8u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 4u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 12u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 16u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 40u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 42u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 102u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 112u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 114u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 108u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 136u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 9u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 5u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 108u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 112u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 136u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 138u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 198u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 208u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 210u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 204u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 232u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 10u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 6u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 204u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 208u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 232u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 234u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 294u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 304u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 306u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 300u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 328u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 11u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 384u, true}, 7u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 300u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 304u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 328u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E0000u, 330u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 6u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 16u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 18u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 12u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 40u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 8u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 4u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 12u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 16u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 40u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 42u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 102u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 112u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 114u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 108u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 136u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 9u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 5u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 108u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 112u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 136u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 138u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 198u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 208u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 210u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 204u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 232u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 10u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 6u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 204u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 208u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 232u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 234u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 294u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 304u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 306u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 300u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 328u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 11u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 384u, true}, 7u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 300u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 304u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 328u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E4000u, 330u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 6u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 16u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 18u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 12u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 40u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 8u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 4u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 12u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 16u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 40u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 42u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 102u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 112u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 114u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 108u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 136u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 9u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 5u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 108u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 112u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 136u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 138u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 198u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 208u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 210u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 204u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 232u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 10u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 6u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 204u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 208u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 232u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 234u, true}, 0u, 16u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 294u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 304u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 306u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 300u, true}, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 328u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 11u, 1u, true}, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 384u, true}, 7u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 300u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 304u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 328u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x403E8000u, 330u, true}, 0u, 16u, true}},
}};

template<std::size_t Index>
struct PwmChannelTraitsBase {
  static constexpr auto& kFacts = kPwmChannelHardwareLut[Index];
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsComplementaryOutput = kFacts.supports_complementary_output;
  static constexpr bool kSupportsDeadtime = kFacts.supports_deadtime;
  static constexpr RuntimeRegisterRef kControlRegister = kFacts.control_register;
  static constexpr RuntimeRegisterRef kCompareRegister = kFacts.compare_register;
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kFacts.secondary_compare_register;
  static constexpr RuntimeRegisterRef kPeriodRegister = kFacts.period_register;
  static constexpr RuntimeRegisterRef kDeadtimeRegister = kFacts.deadtime_register;
  static constexpr RuntimeFieldRef kEnableField = kFacts.enable_field;
  static constexpr RuntimeFieldRef kInterruptEnableField = kFacts.interrupt_enable_field;
  static constexpr RuntimeFieldRef kInterruptFlagField = kFacts.interrupt_flag_field;
  static constexpr RuntimeFieldRef kModeField = kFacts.mode_field;
  static constexpr RuntimeFieldRef kPolarityField = kFacts.polarity_field;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kFacts.complementary_output_enable_field;
  static constexpr RuntimeFieldRef kCenterAlignedField = kFacts.center_aligned_field;
  static constexpr RuntimeFieldRef kPeriodField = kFacts.period_field;
  static constexpr RuntimeFieldRef kDutyField = kFacts.duty_field;
  static constexpr RuntimeFieldRef kDeadtimeRiseField = kFacts.deadtime_rise_field;
  static constexpr RuntimeFieldRef kDeadtimeFallField = kFacts.deadtime_fall_field;
};

template<> struct PwmChannelSemanticTraits<PeripheralId::PWM1, 0u> : PwmChannelTraitsBase<0> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM1, 1u> : PwmChannelTraitsBase<1> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM1, 2u> : PwmChannelTraitsBase<2> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM1, 3u> : PwmChannelTraitsBase<3> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM2, 0u> : PwmChannelTraitsBase<4> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM2, 1u> : PwmChannelTraitsBase<5> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM2, 2u> : PwmChannelTraitsBase<6> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM2, 3u> : PwmChannelTraitsBase<7> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM3, 0u> : PwmChannelTraitsBase<8> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM3, 1u> : PwmChannelTraitsBase<9> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM3, 2u> : PwmChannelTraitsBase<10> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM3, 3u> : PwmChannelTraitsBase<11> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM4, 0u> : PwmChannelTraitsBase<12> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM4, 1u> : PwmChannelTraitsBase<13> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM4, 2u> : PwmChannelTraitsBase<14> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::PWM4, 3u> : PwmChannelTraitsBase<15> {};

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
