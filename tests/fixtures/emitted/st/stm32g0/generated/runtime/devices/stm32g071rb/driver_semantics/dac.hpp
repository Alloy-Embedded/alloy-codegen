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
struct DacSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr std::uint32_t kChannelCount = 0u;
  static constexpr bool kHasHardwareTrigger = false;
  static constexpr bool kHasDma = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTriggerRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kChannelEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kChannelDisableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kChannelStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDataRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kWordModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelEnablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelDisablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelReadyPattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kTriggerEnablePattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kTriggerSelectPattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kDataPattern = kInvalidIndexedFieldRef;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};
};

template<>
struct DacSemanticTraits<PeripheralId::DAC> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dac_st_dac;
  static constexpr std::uint32_t kChannelCount = 1u;
  static constexpr bool kHasHardwareTrigger = true;
  static constexpr bool kHasDma = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_dac_cr, 0x40007400u, 0u, true};
  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTriggerRegister = RuntimeRegisterRef{RegisterId::none, 0x40007400u, 4u, true};
  static constexpr RuntimeRegisterRef kChannelEnableRegister = RuntimeRegisterRef{RegisterId::register_dac_cr, 0x40007400u, 0u, true};
  static constexpr RuntimeRegisterRef kChannelDisableRegister = RuntimeRegisterRef{RegisterId::register_dac_cr, 0x40007400u, 0u, true};
  static constexpr RuntimeRegisterRef kChannelStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x40007400u, 52u, true};
  static constexpr RuntimeRegisterRef kDataRegister = RuntimeRegisterRef{RegisterId::none, 0x40007400u, 8u, true};
  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kWordModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeIndexedFieldRef kChannelEnablePattern = RuntimeIndexedFieldRef{0x40007400u, 0u, 0u, 0u, 1u, 16u, true};
  static constexpr RuntimeIndexedFieldRef kChannelDisablePattern = RuntimeIndexedFieldRef{0x40007400u, 0u, 0u, 0u, 1u, 16u, true};
  static constexpr RuntimeIndexedFieldRef kChannelReadyPattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kTriggerEnablePattern = RuntimeIndexedFieldRef{0x40007400u, 0u, 0u, 2u, 1u, 16u, true};
  static constexpr RuntimeIndexedFieldRef kTriggerSelectPattern = RuntimeIndexedFieldRef{0x40007400u, 0u, 0u, 3u, 3u, 16u, true};
  static constexpr RuntimeIndexedFieldRef kDataPattern = RuntimeIndexedFieldRef{0x40007400u, 8u, 0u, 0u, 12u, 0u, true};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};
};

template<PeripheralId Id, std::size_t ChannelIndex>
struct DacChannelSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kReadyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTriggerEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTriggerSelectField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataField = kInvalidFieldRef;
};

template<>
struct DacChannelSemanticTraits<PeripheralId::DAC, 0u> {
  static constexpr bool kPresent = true;
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_dac_cr, 0x40007400u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kDisableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_dac_cr, 0x40007400u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kReadyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTriggerEnableField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_dac_cr, 0x40007400u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kTriggerSelectField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::register_dac_cr, 0x40007400u, 0u, true}, 3u, 3u, true};
  static constexpr RuntimeFieldRef kDataField = RuntimeFieldRef{FieldId::none, RuntimeRegisterRef{RegisterId::none, 0x40007400u, 8u, true}, 0u, 12u, true};
};

inline constexpr std::array<PeripheralId, 1> kDacSemanticPeripherals = {{
  PeripheralId::DAC,
}};
}
}
}
}
}
}
}
