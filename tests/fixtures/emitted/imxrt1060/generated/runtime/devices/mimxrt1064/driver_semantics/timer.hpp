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
namespace mimxrt1064 {
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
};

template<>
struct TimerSemanticTraits<PeripheralId::GPT1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpt_nxp_gpt;
  static constexpr std::uint32_t kCounterBits = 32u;
  static constexpr std::uint32_t kChannelCount = 1u;
  static constexpr bool kHasCompare = true;
  static constexpr bool kHasCapture = true;
  static constexpr bool kHasEncoder = false;
  static constexpr bool kHasPwm = false;
  static constexpr bool kHasOnePulse = false;
  static constexpr bool kHasCenterAligned = false;
  static constexpr bool kHasComplementaryOutputs = false;
  static constexpr bool kHasDeadtime = false;
  static constexpr bool kHasBreakInput = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_gpt1_cr, 0x401EC000u, 0u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 8u, true};
  static constexpr RuntimeRegisterRef kEventRegister = RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 12u, true};
  static constexpr RuntimeRegisterRef kCounterRegister = RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 36u, true};
  static constexpr RuntimeRegisterRef kPrescalerRegister = RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 4u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 16u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpt1_cr, 0x401EC000u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModuleDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSoftwareResetField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpt1_cr, 0x401EC000u, 0u, true}, 15u, 1u, true};
  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateInterruptEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 12u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kUpdateFlagField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 8u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kUpdateGenerationField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPrescalerField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 4u, true}, 0u, 12u, true};
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 16u, true}, 0u, 32u, true};
  static constexpr RuntimeFieldRef kOnePulseField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAutoReloadPreloadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClockSourceField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpt1_cr, 0x401EC000u, 0u, true}, 6u, 3u, true};
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
};

template<>
struct TimerSemanticTraits<PeripheralId::GPT2> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpt_nxp_gpt;
  static constexpr std::uint32_t kCounterBits = 32u;
  static constexpr std::uint32_t kChannelCount = 1u;
  static constexpr bool kHasCompare = true;
  static constexpr bool kHasCapture = true;
  static constexpr bool kHasEncoder = false;
  static constexpr bool kHasPwm = false;
  static constexpr bool kHasOnePulse = false;
  static constexpr bool kHasCenterAligned = false;
  static constexpr bool kHasComplementaryOutputs = false;
  static constexpr bool kHasDeadtime = false;
  static constexpr bool kHasBreakInput = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_gpt2_cr, 0x401F0000u, 0u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 8u, true};
  static constexpr RuntimeRegisterRef kEventRegister = RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 12u, true};
  static constexpr RuntimeRegisterRef kCounterRegister = RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 36u, true};
  static constexpr RuntimeRegisterRef kPrescalerRegister = RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 4u, true};
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 16u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpt2_cr, 0x401F0000u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModuleDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSoftwareResetField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpt2_cr, 0x401F0000u, 0u, true}, 15u, 1u, true};
  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateInterruptEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 12u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kUpdateFlagField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 8u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kUpdateGenerationField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPrescalerField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 4u, true}, 0u, 12u, true};
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 16u, true}, 0u, 32u, true};
  static constexpr RuntimeFieldRef kOnePulseField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCenterAlignedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAutoReloadPreloadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClockSourceField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpt2_cr, 0x401F0000u, 0u, true}, 6u, 3u, true};
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
};

template<>
struct TimerSemanticTraits<PeripheralId::PIT> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_pit_nxp_pit;
  static constexpr std::uint32_t kCounterBits = 32u;
  static constexpr std::uint32_t kChannelCount = 4u;
  static constexpr bool kHasCompare = false;
  static constexpr bool kHasCapture = false;
  static constexpr bool kHasEncoder = false;
  static constexpr bool kHasPwm = false;
  static constexpr bool kHasOnePulse = false;
  static constexpr bool kHasCenterAligned = false;
  static constexpr bool kHasComplementaryOutputs = false;
  static constexpr bool kHasDeadtime = false;
  static constexpr bool kHasBreakInput = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 264u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 268u, true};
  static constexpr RuntimeRegisterRef kEventRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCounterRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 260u, true};
  static constexpr RuntimeRegisterRef kPrescalerRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 256u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 264u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kModuleDisableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_pit_mcr, 0x40084000u, 0u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kUpdateInterruptEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 264u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kUpdateFlagField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 268u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kUpdateGenerationField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPeriodField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 256u, true}, 0u, 32u, true};
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
struct TimerChannelSemanticTraits<PeripheralId::GPT1, 0u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsCompare = true;
  static constexpr bool kSupportsCapture = true;
  static constexpr bool kSupportsEncoderInput = false;
  static constexpr bool kSupportsPwm = false;
  static constexpr bool kSupportsComplementaryOutput = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_gpt1_cr, 0x401EC000u, 0u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 8u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 16u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 16u, true};
  static constexpr RuntimeRegisterRef kCounterRegister = RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 36u, true};
  static constexpr RuntimeRegisterRef kCaptureRegister = RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 28u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpt1_cr, 0x401EC000u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 12u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptFlagField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x401EC000u, 8u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPreloadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCaptureSelectField = kInvalidFieldRef;
};

template<>
struct TimerChannelSemanticTraits<PeripheralId::GPT2, 0u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsCompare = true;
  static constexpr bool kSupportsCapture = true;
  static constexpr bool kSupportsEncoderInput = false;
  static constexpr bool kSupportsPwm = false;
  static constexpr bool kSupportsComplementaryOutput = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_gpt2_cr, 0x401F0000u, 0u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 8u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 16u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 16u, true};
  static constexpr RuntimeRegisterRef kCounterRegister = RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 36u, true};
  static constexpr RuntimeRegisterRef kCaptureRegister = RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 28u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_gpt2_cr, 0x401F0000u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 12u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptFlagField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x401F0000u, 8u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPreloadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCaptureSelectField = kInvalidFieldRef;
};

template<>
struct TimerChannelSemanticTraits<PeripheralId::PIT, 0u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsCompare = false;
  static constexpr bool kSupportsCapture = false;
  static constexpr bool kSupportsEncoderInput = false;
  static constexpr bool kSupportsPwm = false;
  static constexpr bool kSupportsComplementaryOutput = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 264u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 268u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 256u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 256u, true};
  static constexpr RuntimeRegisterRef kCounterRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 260u, true};
  static constexpr RuntimeRegisterRef kCaptureRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 264u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 264u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptFlagField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 268u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPreloadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCaptureSelectField = kInvalidFieldRef;
};

template<>
struct TimerChannelSemanticTraits<PeripheralId::PIT, 1u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsCompare = false;
  static constexpr bool kSupportsCapture = false;
  static constexpr bool kSupportsEncoderInput = false;
  static constexpr bool kSupportsPwm = false;
  static constexpr bool kSupportsComplementaryOutput = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 280u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 284u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 272u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 272u, true};
  static constexpr RuntimeRegisterRef kCounterRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 276u, true};
  static constexpr RuntimeRegisterRef kCaptureRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 280u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 280u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptFlagField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 284u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPreloadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCaptureSelectField = kInvalidFieldRef;
};

template<>
struct TimerChannelSemanticTraits<PeripheralId::PIT, 2u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsCompare = false;
  static constexpr bool kSupportsCapture = false;
  static constexpr bool kSupportsEncoderInput = false;
  static constexpr bool kSupportsPwm = false;
  static constexpr bool kSupportsComplementaryOutput = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 296u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 300u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 288u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 288u, true};
  static constexpr RuntimeRegisterRef kCounterRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 292u, true};
  static constexpr RuntimeRegisterRef kCaptureRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 296u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 296u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptFlagField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 300u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPreloadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCaptureSelectField = kInvalidFieldRef;
};

template<>
struct TimerChannelSemanticTraits<PeripheralId::PIT, 3u> {
  static constexpr bool kPresent = true;
  static constexpr bool kSupportsCompare = false;
  static constexpr bool kSupportsCapture = false;
  static constexpr bool kSupportsEncoderInput = false;
  static constexpr bool kSupportsPwm = false;
  static constexpr bool kSupportsComplementaryOutput = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 312u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 316u, true};
  static constexpr RuntimeRegisterRef kCompareRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 304u, true};
  static constexpr RuntimeRegisterRef kSecondaryCompareRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kPeriodRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 304u, true};
  static constexpr RuntimeRegisterRef kCounterRegister = RuntimeRegisterRef{RegisterId::none, 0x40084000u, 308u, true};
  static constexpr RuntimeRegisterRef kCaptureRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 312u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 312u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kInterruptFlagField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40084000u, 316u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPreloadField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOutputPolarityField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kComplementaryOutputEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCaptureSelectField = kInvalidFieldRef;
};

inline constexpr std::array<PeripheralId, 3> kTimerSemanticPeripherals = {{
  PeripheralId::GPT1,
  PeripheralId::GPT2,
  PeripheralId::PIT,
}};

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
