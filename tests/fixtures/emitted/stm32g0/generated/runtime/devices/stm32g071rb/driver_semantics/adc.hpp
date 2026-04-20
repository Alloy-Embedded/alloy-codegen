#pragma once

#include <array>
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
};

inline constexpr std::array<PeripheralId, 1> kAdcSemanticPeripherals = {{
  PeripheralId::ADC1,
}};
}
}
}
}
}
}
}
