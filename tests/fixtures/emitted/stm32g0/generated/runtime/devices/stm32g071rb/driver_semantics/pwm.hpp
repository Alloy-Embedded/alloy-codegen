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

inline constexpr std::array<PwmHardwareLut, 1> kPwmHardwareLut = {{
  {BackendSchemaId::schema_alloy_timer_st_tim, 16u, 4u, true, true, true, true, true, RuntimeRegisterRef{RegisterId::register_tim1_cr1, 0x40012C00u, 0u, true}, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 16u, true}, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 40u, true}, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 20u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 15u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 20u, true}, 0u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 40u, true}, 0u, 16u, true}, 65535u, 65535u, true, true, true, true, true},
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
struct PwmSemanticTraits<PeripheralId::TIM1> : PwmTraitsBase<0> {
  static constexpr std::array<std::uint8_t, 4> kDeadtimeOptions = {{0u, 1u, 2u, 3u}};
  static constexpr std::array<std::uint8_t, 4> kSupportedAlignments = {{0u, 1u, 2u, 3u}};
  static constexpr std::array<std::uint8_t, 1> kBreakInputs = {{0u}};
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

inline constexpr std::array<PwmChannelHardwareLut, 4> kPwmChannelHardwareLut = {{
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 24u, true}, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 52u, true}, kInvalidRegisterRef, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true}, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 0u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 12u, true}, 1u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 16u, true}, 1u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 24u, true}, 4u, 3u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 1u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 2u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_tim1_cr1, 0x40012C00u, 0u, true}, 5u, 2u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 52u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 24u, true}, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 56u, true}, kInvalidRegisterRef, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true}, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 12u, true}, 2u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 16u, true}, 2u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 24u, true}, 12u, 3u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 5u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 6u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_tim1_cr1, 0x40012C00u, 0u, true}, 5u, 2u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 56u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true}},
  {true, true, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 28u, true}, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 60u, true}, kInvalidRegisterRef, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true}, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 8u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 12u, true}, 3u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 16u, true}, 3u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 28u, true}, 4u, 3u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 9u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 10u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_tim1_cr1, 0x40012C00u, 0u, true}, 5u, 2u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 60u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true}},
  {false, true, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 28u, true}, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 64u, true}, kInvalidRegisterRef, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true}, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 12u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 12u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 16u, true}, 4u, 1u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 28u, true}, 12u, 3u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 32u, true}, 13u, 1u, true}, kInvalidFieldRef, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_tim1_cr1, 0x40012C00u, 0u, true}, 5u, 2u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 44u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 64u, true}, 0u, 16u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true}, RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012C00u, 68u, true}, 0u, 8u, true}},
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

template<> struct PwmChannelSemanticTraits<PeripheralId::TIM1, 0u> : PwmChannelTraitsBase<0> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::TIM1, 1u> : PwmChannelTraitsBase<1> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::TIM1, 2u> : PwmChannelTraitsBase<2> {};
template<> struct PwmChannelSemanticTraits<PeripheralId::TIM1, 3u> : PwmChannelTraitsBase<3> {};

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


// add-typed-peripheral-enums-everywhere: typed PwmAlignmentOf per peripheral.
template<PeripheralId Id>
struct PwmAlignmentOf {
  enum class type : std::uint8_t {};
};

template<>
struct PwmAlignmentOf<PeripheralId::TIM1> {
  enum class type : std::uint8_t {
    edge = 0u,
    center_down = 1u,
    center_up = 2u,
    center_up_down = 3u,
  };
};

template<PeripheralId Id>
using PwmAlignment = typename PwmAlignmentOf<Id>::type;

// add-typed-peripheral-enums-everywhere: typed PwmBreakInputOf per peripheral.
template<PeripheralId Id>
struct PwmBreakInputOf {
  enum class type : std::uint8_t {};
};

template<>
struct PwmBreakInputOf<PeripheralId::TIM1> {
  enum class type : std::uint8_t {
    bkin = 0u,
  };
};

template<PeripheralId Id>
using PwmBreakInput = typename PwmBreakInputOf<Id>::type;

}
}
}
}
}
}
}
