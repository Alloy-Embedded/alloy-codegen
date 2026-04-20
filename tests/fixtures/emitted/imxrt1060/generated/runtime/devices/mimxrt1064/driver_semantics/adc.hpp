#pragma once

#include <array>
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
};

inline constexpr std::array<PeripheralId, 2> kAdcSemanticPeripherals = {{
  PeripheralId::ADC1,
  PeripheralId::ADC2,
}};
}
}
}
}
}
}
}
