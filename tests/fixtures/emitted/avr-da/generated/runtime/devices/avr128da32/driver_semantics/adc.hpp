#pragma once

#include <array>
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
struct AdcSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kChannelCount = 0u;
  static constexpr std::uint32_t kResultBits = 0u;
  static constexpr bool kHasDma = false;
  static constexpr bool kHasHardwareTrigger = false;
  static constexpr bool kHasChannelBitmaskSelect = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSampleTimeRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSequenceRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDataRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kReadyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kContinuousField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kResolutionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAlignField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDmaEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDmaModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kExternalTriggerEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kExternalTriggerSelectField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEndOfConversionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEndOfSequenceField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOverrunField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kChannelSelectField = kInvalidFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelBitPattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelEnablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelDisablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelStatusPattern = kInvalidIndexedFieldRef;
  static constexpr std::uint32_t kInternalChannelCount = 0u;
  static constexpr std::array<InternalAdcChannel, 0> kInternalChannels = {};
  static constexpr std::uint32_t kCalibrationDataPointCount = 0u;
  static constexpr std::array<CalibrationDataPoint, 0> kCalibrationDataPoints = {};
  static constexpr CalibrationContext kCalibrationContext = {};
  static constexpr std::uint32_t kSupportedResolutionCount = 0u;
  static constexpr std::array<AdcResolutionOption, 0> kSupportedResolutions = {};
  static constexpr std::uint32_t kSupportedSampleTimeCount = 0u;
  static constexpr std::array<AdcSampleTimeOption, 0> kSupportedSampleTimes = {};
  static constexpr std::uint32_t kSupportedOversamplingCount = 0u;
  static constexpr std::array<AdcOversamplingOption, 0> kSupportedOversamplings = {};
  static constexpr std::uint32_t kAdcMaxClockHz = 0u;
  static constexpr std::uint32_t kDmaBindingCount = 0u;
  static constexpr std::array<AdcDmaBinding, 0> kDmaBindings = {};
  static constexpr std::uint32_t kExternalTriggerCount = 0u;
  static constexpr std::array<AdcExternalTrigger, 0> kExternalTriggers = {};
  static constexpr std::uint32_t kSupportedDmaModeCount = 0u;
  static constexpr std::array<AdcDmaModeOption, 0> kSupportedDmaModes = {};
};

template<>
struct AdcSemanticTraits<PeripheralId::ADC0> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_adc_microchip_avr_da_adc_v1;
  static constexpr std::uint32_t kChannelCount = 28u;
  static constexpr std::uint32_t kResultBits = 12u;
  static constexpr bool kHasDma = false;
  static constexpr bool kHasHardwareTrigger = false;
  static constexpr bool kHasChannelBitmaskSelect = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_adc0_ctrla, 0x00000600u, 0u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::register_adc0_intflags, 0x00000600u, 13u, true};
  static constexpr RuntimeRegisterRef kConfigRegister = RuntimeRegisterRef{RegisterId::register_adc0_ctrlb, 0x00000600u, 1u, true};
  static constexpr RuntimeRegisterRef kSampleTimeRegister = RuntimeRegisterRef{RegisterId::register_adc0_sampctrl, 0x00000600u, 5u, true};
  static constexpr RuntimeRegisterRef kSequenceRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDataRegister = RuntimeRegisterRef{RegisterId::register_adc0_res, 0x00000600u, 16u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::field_adc0_ctrla_enable, RuntimeRegisterRef{RegisterId::register_adc0_ctrla, 0x00000600u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kReadyField = RuntimeFieldRef{FieldId::field_adc0_intflags_resrdy, RuntimeRegisterRef{RegisterId::register_adc0_intflags, 0x00000600u, 13u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kStartField = RuntimeFieldRef{FieldId::field_adc0_command_stconv, RuntimeRegisterRef{RegisterId::register_adc0_command, 0x00000600u, 10u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kContinuousField = RuntimeFieldRef{FieldId::field_adc0_ctrla_freerun, RuntimeRegisterRef{RegisterId::register_adc0_ctrla, 0x00000600u, 0u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kResolutionField = RuntimeFieldRef{FieldId::field_adc0_ctrla_ressel, RuntimeRegisterRef{RegisterId::register_adc0_ctrla, 0x00000600u, 0u, true}, 2u, 2u, true};
  static constexpr RuntimeFieldRef kAlignField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDmaEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDmaModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kExternalTriggerEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kExternalTriggerSelectField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEndOfConversionField = RuntimeFieldRef{FieldId::field_adc0_intflags_resrdy, RuntimeRegisterRef{RegisterId::register_adc0_intflags, 0x00000600u, 13u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kEndOfSequenceField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOverrunField = RuntimeFieldRef{FieldId::field_adc0_intflags_wcmp, RuntimeRegisterRef{RegisterId::register_adc0_intflags, 0x00000600u, 13u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kDataField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kChannelSelectField = RuntimeFieldRef{FieldId::field_adc0_muxpos_muxpos, RuntimeRegisterRef{RegisterId::register_adc0_muxpos, 0x00000600u, 8u, true}, 0u, 7u, true};
  static constexpr RuntimeIndexedFieldRef kChannelBitPattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelEnablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelDisablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelStatusPattern = kInvalidIndexedFieldRef;
  static constexpr std::uint32_t kInternalChannelCount = 0u;
  static constexpr std::array<InternalAdcChannel, 0> kInternalChannels = {};
  static constexpr std::uint32_t kCalibrationDataPointCount = 0u;
  static constexpr std::array<CalibrationDataPoint, 0> kCalibrationDataPoints = {};
  static constexpr CalibrationContext kCalibrationContext = CalibrationContext{};
  static constexpr std::uint32_t kSupportedResolutionCount = 0u;
  static constexpr std::array<AdcResolutionOption, 0> kSupportedResolutions = {};
  static constexpr std::uint32_t kSupportedSampleTimeCount = 0u;
  static constexpr std::array<AdcSampleTimeOption, 0> kSupportedSampleTimes = {};
  static constexpr std::uint32_t kSupportedOversamplingCount = 0u;
  static constexpr std::array<AdcOversamplingOption, 0> kSupportedOversamplings = {};
  static constexpr std::uint32_t kAdcMaxClockHz = 0u;
  static constexpr std::uint32_t kDmaBindingCount = 0u;
  static constexpr std::array<AdcDmaBinding, 0> kDmaBindings = {};
  static constexpr std::uint32_t kExternalTriggerCount = 0u;
  static constexpr std::array<AdcExternalTrigger, 0> kExternalTriggers = {};
  static constexpr std::uint32_t kSupportedDmaModeCount = 0u;
  static constexpr std::array<AdcDmaModeOption, 0> kSupportedDmaModes = {};
};

inline constexpr std::array<PeripheralId, 1> kAdcSemanticPeripherals = {{
  PeripheralId::ADC0,
}};
}
}
}
}
}
}
}
