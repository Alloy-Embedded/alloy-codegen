#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
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
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

template<>
struct AdcSemanticTraits<PeripheralId::ADC1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_adc_nxp_adc;
  static constexpr std::uint32_t kChannelCount = 16u;
  static constexpr std::uint32_t kResultBits = 12u;
  static constexpr bool kHasDma = false;
  static constexpr bool kHasHardwareTrigger = true;
  static constexpr bool kHasChannelBitmaskSelect = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x400C4000u, 72u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x400C4000u, 32u, true};
  static constexpr RuntimeRegisterRef kConfigRegister = RuntimeRegisterRef{RegisterId::none, 0x400C4000u, 68u, true};
  static constexpr RuntimeRegisterRef kSampleTimeRegister = RuntimeRegisterRef{RegisterId::none, 0x400C4000u, 68u, true};
  static constexpr RuntimeRegisterRef kSequenceRegister = RuntimeRegisterRef{RegisterId::register_adc1_hc0, 0x400C4000u, 0u, true};
  static constexpr RuntimeRegisterRef kDataRegister = RuntimeRegisterRef{RegisterId::none, 0x400C4000u, 36u, true};
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kReadyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kContinuousField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x400C4000u, 72u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kResolutionField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x400C4000u, 68u, true}, 2u, 2u, true};
  static constexpr RuntimeFieldRef kAlignField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDmaEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x400C4000u, 72u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kDmaModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kExternalTriggerEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x400C4000u, 68u, true}, 13u, 1u, true};
  static constexpr RuntimeFieldRef kExternalTriggerSelectField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEndOfConversionField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x400C4000u, 32u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kEndOfSequenceField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOverrunField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x400C4000u, 36u, true}, 0u, 12u, true};
  static constexpr RuntimeFieldRef kChannelSelectField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_adc1_hc0, 0x400C4000u, 0u, true}, 0u, 5u, true};
  static constexpr RuntimeIndexedFieldRef kChannelBitPattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelEnablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelDisablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelStatusPattern = RuntimeIndexedFieldRef{0x400C4000u, 32u, 0u, 0u, 1u, 1u, true};
  static constexpr std::uint32_t kInternalChannelCount = 0u;
  static constexpr std::array<InternalAdcChannel, 0> kInternalChannels = {};
  static constexpr std::uint32_t kCalibrationDataPointCount = 0u;
  static constexpr std::array<CalibrationDataPoint, 0> kCalibrationDataPoints = {};
  static constexpr CalibrationContext kCalibrationContext = CalibrationContext{};
  static constexpr std::uint32_t kSupportedResolutionCount = 3u;
  static constexpr std::array<AdcResolutionOption, 3> kSupportedResolutions = {{
    AdcResolutionOption{8u, 0u, true},
    AdcResolutionOption{10u, 1u, true},
    AdcResolutionOption{12u, 2u, true},
  }};
  static constexpr std::uint32_t kSupportedSampleTimeCount = 4u;
  static constexpr std::array<AdcSampleTimeOption, 4> kSupportedSampleTimes = {{
    AdcSampleTimeOption{512u, 0u, true},
    AdcSampleTimeOption{1024u, 1u, true},
    AdcSampleTimeOption{2048u, 2u, true},
    AdcSampleTimeOption{4096u, 3u, true},
  }};
  static constexpr std::uint32_t kSupportedOversamplingCount = 0u;
  static constexpr std::array<AdcOversamplingOption, 0> kSupportedOversamplings = {};
  static constexpr std::uint32_t kAdcMaxClockHz = 40000000u;
  static constexpr std::uint32_t kDmaBindingCount = 0u;
  static constexpr std::array<AdcDmaBinding, 0> kDmaBindings = {};
  static constexpr std::uint32_t kExternalTriggerCount = 0u;
  static constexpr std::array<AdcExternalTrigger, 0> kExternalTriggers = {};
  static constexpr std::uint32_t kSupportedDmaModeCount = 0u;
  static constexpr std::array<AdcDmaModeOption, 0> kSupportedDmaModes = {};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

template<>
struct AdcSemanticTraits<PeripheralId::ADC2> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_adc_nxp_adc;
  static constexpr std::uint32_t kChannelCount = 16u;
  static constexpr std::uint32_t kResultBits = 12u;
  static constexpr bool kHasDma = false;
  static constexpr bool kHasHardwareTrigger = true;
  static constexpr bool kHasChannelBitmaskSelect = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x400C8000u, 72u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x400C8000u, 32u, true};
  static constexpr RuntimeRegisterRef kConfigRegister = RuntimeRegisterRef{RegisterId::none, 0x400C8000u, 68u, true};
  static constexpr RuntimeRegisterRef kSampleTimeRegister = RuntimeRegisterRef{RegisterId::none, 0x400C8000u, 68u, true};
  static constexpr RuntimeRegisterRef kSequenceRegister = RuntimeRegisterRef{RegisterId::register_adc2_hc0, 0x400C8000u, 0u, true};
  static constexpr RuntimeRegisterRef kDataRegister = RuntimeRegisterRef{RegisterId::none, 0x400C8000u, 36u, true};
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kReadyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStartField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kContinuousField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x400C8000u, 72u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kResolutionField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x400C8000u, 68u, true}, 2u, 2u, true};
  static constexpr RuntimeFieldRef kAlignField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDmaEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x400C8000u, 72u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kDmaModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kExternalTriggerEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x400C8000u, 68u, true}, 13u, 1u, true};
  static constexpr RuntimeFieldRef kExternalTriggerSelectField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEndOfConversionField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x400C8000u, 32u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kEndOfSequenceField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOverrunField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x400C8000u, 36u, true}, 0u, 12u, true};
  static constexpr RuntimeFieldRef kChannelSelectField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_adc2_hc0, 0x400C8000u, 0u, true}, 0u, 5u, true};
  static constexpr RuntimeIndexedFieldRef kChannelBitPattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelEnablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelDisablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelStatusPattern = RuntimeIndexedFieldRef{0x400C8000u, 32u, 0u, 0u, 1u, 1u, true};
  static constexpr std::uint32_t kInternalChannelCount = 0u;
  static constexpr std::array<InternalAdcChannel, 0> kInternalChannels = {};
  static constexpr std::uint32_t kCalibrationDataPointCount = 0u;
  static constexpr std::array<CalibrationDataPoint, 0> kCalibrationDataPoints = {};
  static constexpr CalibrationContext kCalibrationContext = CalibrationContext{};
  static constexpr std::uint32_t kSupportedResolutionCount = 3u;
  static constexpr std::array<AdcResolutionOption, 3> kSupportedResolutions = {{
    AdcResolutionOption{8u, 0u, true},
    AdcResolutionOption{10u, 1u, true},
    AdcResolutionOption{12u, 2u, true},
  }};
  static constexpr std::uint32_t kSupportedSampleTimeCount = 4u;
  static constexpr std::array<AdcSampleTimeOption, 4> kSupportedSampleTimes = {{
    AdcSampleTimeOption{512u, 0u, true},
    AdcSampleTimeOption{1024u, 1u, true},
    AdcSampleTimeOption{2048u, 2u, true},
    AdcSampleTimeOption{4096u, 3u, true},
  }};
  static constexpr std::uint32_t kSupportedOversamplingCount = 0u;
  static constexpr std::array<AdcOversamplingOption, 0> kSupportedOversamplings = {};
  static constexpr std::uint32_t kAdcMaxClockHz = 40000000u;
  static constexpr std::uint32_t kDmaBindingCount = 0u;
  static constexpr std::array<AdcDmaBinding, 0> kDmaBindings = {};
  static constexpr std::uint32_t kExternalTriggerCount = 0u;
  static constexpr std::array<AdcExternalTrigger, 0> kExternalTriggers = {};
  static constexpr std::uint32_t kSupportedDmaModeCount = 0u;
  static constexpr std::array<AdcDmaModeOption, 0> kSupportedDmaModes = {};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

inline constexpr std::array<PeripheralId, 2> kAdcSemanticPeripherals = {{
  PeripheralId::ADC1,
  PeripheralId::ADC2,
}};

// complete-rp2040-semantics Phase C: per-controller ADC facts.
enum class RuntimeAdcId : std::uint8_t {
  None = 0,
};

template<RuntimeAdcId Id>
struct AdcPeripheralTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint32_t kBaseAddress = 0u;
  static constexpr std::uint8_t kChannelCount = 0u;
  static constexpr std::uint8_t kResolutionBits = 0u;
  static constexpr std::uint8_t kDreq = 0u;
  static constexpr std::uint8_t kFifoDepth = 0u;
  static constexpr bool kSupportsFifo = false;
  static constexpr std::array<std::uint8_t, 0> kChannelPins = {};
};


// add-adc-channel-typed-enum: typed per-peripheral channel enum.
// Each specialization scopes the channel set so
// AdcChannel<ADC1> and AdcChannel<ADC2> are distinct types and
// the type system rejects cross-peripheral channel mixing.
template<PeripheralId Id>
struct AdcChannelOf {
  enum class type : std::uint8_t {};
};

template<>
struct AdcChannelOf<PeripheralId::ADC1> {
  enum class type : std::uint8_t {
    CH0 = 0u,
    CH1 = 1u,
    CH2 = 2u,
    CH3 = 3u,
    CH4 = 4u,
    CH5 = 5u,
    CH6 = 6u,
    CH7 = 7u,
    CH8 = 8u,
    CH9 = 9u,
    CH10 = 10u,
    CH11 = 11u,
    CH12 = 12u,
    CH13 = 13u,
    CH14 = 14u,
    CH15 = 15u,
  };
};

template<>
struct AdcChannelOf<PeripheralId::ADC2> {
  enum class type : std::uint8_t {
    CH0 = 0u,
    CH1 = 1u,
    CH2 = 2u,
    CH3 = 3u,
    CH4 = 4u,
    CH5 = 5u,
    CH6 = 6u,
    CH7 = 7u,
    CH8 = 8u,
    CH9 = 9u,
    CH10 = 10u,
    CH11 = 11u,
    CH12 = 12u,
    CH13 = 13u,
    CH14 = 14u,
    CH15 = 15u,
  };
};

template<PeripheralId Id>
using AdcChannel = typename AdcChannelOf<Id>::type;
}
}
}
}
}
}
}
