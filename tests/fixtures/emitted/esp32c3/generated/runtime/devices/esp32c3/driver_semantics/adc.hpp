#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace espressif {
namespace esp32c3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32c3 {
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
struct AdcSemanticTraits<PeripheralId::APB_SARADC> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_adc_espressif_esp32c3_saradc_v1;
  static constexpr std::uint32_t kChannelCount = 5u;
  static constexpr std::uint32_t kResultBits = 12u;
  static constexpr bool kHasDma = true;
  static constexpr bool kHasHardwareTrigger = false;
  static constexpr bool kHasChannelBitmaskSelect = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_apb_saradc_ctrl, 0x60040000u, 0u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::register_apb_saradc_int_st, 0x60040000u, 72u, true};
  static constexpr RuntimeRegisterRef kConfigRegister = RuntimeRegisterRef{RegisterId::register_apb_saradc_ctrl2, 0x60040000u, 4u, true};
  static constexpr RuntimeRegisterRef kSampleTimeRegister = RuntimeRegisterRef{RegisterId::register_apb_saradc_fsm_wait, 0x60040000u, 12u, true};
  static constexpr RuntimeRegisterRef kSequenceRegister = RuntimeRegisterRef{RegisterId::register_apb_saradc_sar_patt_tab1, 0x60040000u, 24u, true};
  static constexpr RuntimeRegisterRef kDataRegister = RuntimeRegisterRef{RegisterId::register_apb_saradc_sar1_status, 0x60040000u, 16u, true};
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kReadyField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_apb_saradc_int_st, 0x60040000u, 72u, true}, 31u, 1u, true};
  static constexpr RuntimeFieldRef kStartField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_apb_saradc_ctrl, 0x60040000u, 0u, true}, 29u, 1u, true};
  static constexpr RuntimeFieldRef kStopField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kContinuousField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_apb_saradc_ctrl, 0x60040000u, 0u, true}, 3u, 2u, true};
  static constexpr RuntimeFieldRef kResolutionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAlignField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDmaEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDmaModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kExternalTriggerEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kExternalTriggerSelectField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEndOfConversionField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_apb_saradc_int_st, 0x60040000u, 72u, true}, 31u, 1u, true};
  static constexpr RuntimeFieldRef kEndOfSequenceField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOverrunField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_apb_saradc_sar1_status, 0x60040000u, 16u, true}, 0u, 12u, true};
  static constexpr RuntimeFieldRef kChannelSelectField = kInvalidFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelBitPattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelEnablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelDisablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelStatusPattern = kInvalidIndexedFieldRef;
  static constexpr std::uint32_t kInternalChannelCount = 0u;
  static constexpr std::array<InternalAdcChannel, 0> kInternalChannels = {};
  static constexpr std::uint32_t kCalibrationDataPointCount = 0u;
  static constexpr std::array<CalibrationDataPoint, 0> kCalibrationDataPoints = {};
  static constexpr CalibrationContext kCalibrationContext = CalibrationContext{};
  static constexpr std::uint32_t kSupportedResolutionCount = 1u;
  static constexpr std::array<AdcResolutionOption, 1> kSupportedResolutions = {{
    AdcResolutionOption{12u, 0u, true},
  }};
  static constexpr std::uint32_t kSupportedSampleTimeCount = 0u;
  static constexpr std::array<AdcSampleTimeOption, 0> kSupportedSampleTimes = {};
  static constexpr std::uint32_t kSupportedOversamplingCount = 0u;
  static constexpr std::array<AdcOversamplingOption, 0> kSupportedOversamplings = {};
  static constexpr std::uint32_t kAdcMaxClockHz = 5000000u;
  static constexpr std::uint32_t kDmaBindingCount = 0u;
  static constexpr std::array<AdcDmaBinding, 0> kDmaBindings = {};
  static constexpr std::uint32_t kExternalTriggerCount = 0u;
  static constexpr std::array<AdcExternalTrigger, 0> kExternalTriggers = {};
  static constexpr std::uint32_t kSupportedDmaModeCount = 0u;
  static constexpr std::array<AdcDmaModeOption, 0> kSupportedDmaModes = {};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

inline constexpr std::array<PeripheralId, 1> kAdcSemanticPeripherals = {{
  PeripheralId::APB_SARADC,
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

}
}
}
}
}
}
}
