#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g030f6 {
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
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_adc_st_adc;
  static constexpr std::uint32_t kChannelCount = 19u;
  static constexpr std::uint32_t kResultBits = 12u;
  static constexpr bool kHasDma = false;
  static constexpr bool kHasHardwareTrigger = true;
  static constexpr bool kHasChannelBitmaskSelect = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x40012400u, 8u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x40012400u, 0u, true};
  static constexpr RuntimeRegisterRef kConfigRegister = RuntimeRegisterRef{RegisterId::none, 0x40012400u, 8u, true};
  static constexpr RuntimeRegisterRef kSampleTimeRegister = RuntimeRegisterRef{RegisterId::none, 0x40012400u, 16u, true};
  static constexpr RuntimeRegisterRef kSequenceRegister = RuntimeRegisterRef{RegisterId::none, 0x40012400u, 52u, true};
  static constexpr RuntimeRegisterRef kDataRegister = RuntimeRegisterRef{RegisterId::none, 0x40012400u, 76u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012400u, 8u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kReadyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kStartField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012400u, 8u, true}, 30u, 1u, true};
  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kContinuousField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012400u, 8u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kResolutionField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012400u, 4u, true}, 24u, 2u, true};
  static constexpr RuntimeFieldRef kAlignField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012400u, 8u, true}, 11u, 1u, true};
  static constexpr RuntimeFieldRef kDmaEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012400u, 8u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kDmaModeField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012400u, 8u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kExternalTriggerEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012400u, 8u, true}, 28u, 2u, true};
  static constexpr RuntimeFieldRef kExternalTriggerSelectField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012400u, 8u, true}, 24u, 4u, true};
  static constexpr RuntimeFieldRef kEndOfConversionField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012400u, 0u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kEndOfSequenceField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOverrunField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012400u, 0u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kDataField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012400u, 76u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kChannelSelectField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40012400u, 52u, true}, 0u, 5u, true};
  static constexpr RuntimeIndexedFieldRef kChannelBitPattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelEnablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelDisablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelStatusPattern = kInvalidIndexedFieldRef;
  static constexpr std::uint32_t kInternalChannelCount = 3u;
  static constexpr std::array<InternalAdcChannel, 3> kInternalChannels = {{
    InternalAdcChannel{InternalAdcChannelKind::temperature_sensor, 12u, true},
    InternalAdcChannel{InternalAdcChannelKind::vrefint, 13u, true},
    InternalAdcChannel{InternalAdcChannelKind::vbat, 14u, true},
  }};
  static constexpr std::uint32_t kCalibrationDataPointCount = 3u;
  static constexpr std::array<CalibrationDataPoint, 3> kCalibrationDataPoints = {{
    CalibrationDataPoint{AdcCalibrationKind::vrefint_cal, RuntimeRegisterRef{RegisterId::none, 0x1FFF75AAu, 0u, true}, 3000, true},
    CalibrationDataPoint{AdcCalibrationKind::ts_cal_low, RuntimeRegisterRef{RegisterId::none, 0x1FFF75A8u, 0u, true}, 30, true},
    CalibrationDataPoint{AdcCalibrationKind::ts_cal_high, RuntimeRegisterRef{RegisterId::none, 0x1FFF75CAu, 0u, true}, 130, true},
  }};
  static constexpr CalibrationContext kCalibrationContext = CalibrationContext{30, 130, 3000u, 1212u, true};
  static constexpr std::uint32_t kSupportedResolutionCount = 4u;
  static constexpr std::array<AdcResolutionOption, 4> kSupportedResolutions = {{
    AdcResolutionOption{12u, 0u, true},
    AdcResolutionOption{10u, 1u, true},
    AdcResolutionOption{8u, 2u, true},
    AdcResolutionOption{6u, 3u, true},
  }};
  static constexpr std::uint32_t kSupportedSampleTimeCount = 8u;
  static constexpr std::array<AdcSampleTimeOption, 8> kSupportedSampleTimes = {{
    AdcSampleTimeOption{384u, 0u, true},
    AdcSampleTimeOption{896u, 1u, true},
    AdcSampleTimeOption{1920u, 2u, true},
    AdcSampleTimeOption{3200u, 3u, true},
    AdcSampleTimeOption{4992u, 4u, true},
    AdcSampleTimeOption{10112u, 5u, true},
    AdcSampleTimeOption{20352u, 6u, true},
    AdcSampleTimeOption{41088u, 7u, true},
  }};
  static constexpr std::uint32_t kSupportedOversamplingCount = 8u;
  static constexpr std::array<AdcOversamplingOption, 8> kSupportedOversamplings = {{
    AdcOversamplingOption{2u, 0u, true},
    AdcOversamplingOption{4u, 1u, true},
    AdcOversamplingOption{8u, 2u, true},
    AdcOversamplingOption{16u, 3u, true},
    AdcOversamplingOption{32u, 4u, true},
    AdcOversamplingOption{64u, 5u, true},
    AdcOversamplingOption{128u, 6u, true},
    AdcOversamplingOption{256u, 7u, true},
  }};
  static constexpr std::uint32_t kAdcMaxClockHz = 35000000u;
  static constexpr std::uint32_t kDmaBindingCount = 0u;
  static constexpr std::array<AdcDmaBinding, 0> kDmaBindings = {};
  static constexpr std::uint32_t kExternalTriggerCount = 4u;
  static constexpr std::array<AdcExternalTrigger, 4> kExternalTriggers = {{
    AdcExternalTrigger{AdcExternalTriggerSource::tim1_trgo, 0u, 1u, true},
    AdcExternalTrigger{AdcExternalTriggerSource::tim1_cc4, 1u, 1u, true},
    AdcExternalTrigger{AdcExternalTriggerSource::tim3_trgo, 3u, 1u, true},
    AdcExternalTrigger{AdcExternalTriggerSource::exti11, 7u, 1u, true},
  }};
  static constexpr std::uint32_t kSupportedDmaModeCount = 0u;
  static constexpr std::array<AdcDmaModeOption, 0> kSupportedDmaModes = {};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

inline constexpr std::array<PeripheralId, 1> kAdcSemanticPeripherals = {{
  PeripheralId::ADC1,
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
    CH16 = 16u,
    CH17 = 17u,
    CH18 = 18u,
    TempSensor = 12u,
    Vrefint = 13u,
    VBat = 14u,
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
