#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include "common.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70q21b {
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
struct DacSemanticTraits<PeripheralId::DACC> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dac_microchip_dacc_e;
  static constexpr std::uint32_t kChannelCount = 2u;
  static constexpr bool kHasHardwareTrigger = true;
  static constexpr bool kHasDma = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_dacc_cr, 0x40040000u, 0u, true};
  static constexpr RuntimeRegisterRef kModeRegister = RuntimeRegisterRef{RegisterId::register_dacc_mr, 0x40040000u, 4u, true};
  static constexpr RuntimeRegisterRef kTriggerRegister = RuntimeRegisterRef{RegisterId::register_dacc_trigr, 0x40040000u, 8u, true};
  static constexpr RuntimeRegisterRef kChannelEnableRegister = RuntimeRegisterRef{RegisterId::register_dacc_cher, 0x40040000u, 16u, true};
  static constexpr RuntimeRegisterRef kChannelDisableRegister = RuntimeRegisterRef{RegisterId::register_dacc_chdr, 0x40040000u, 20u, true};
  static constexpr RuntimeRegisterRef kChannelStatusRegister = RuntimeRegisterRef{RegisterId::register_dacc_chsr, 0x40040000u, 24u, true};
  static constexpr RuntimeRegisterRef kDataRegister = RuntimeRegisterRef{RegisterId::register_dacc_cdr__s, 0x40040000u, 28u, true};
  static constexpr RuntimeFieldRef kSoftwareResetField = RuntimeFieldRef{FieldId::field_dacc_cr_swrst, RuntimeRegisterRef{RegisterId::register_dacc_cr, 0x40040000u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kWordModeField = RuntimeFieldRef{FieldId::field_dacc_mr_word, RuntimeRegisterRef{RegisterId::register_dacc_mr, 0x40040000u, 4u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kPrescalerField = RuntimeFieldRef{FieldId::field_dacc_mr_prescaler, RuntimeRegisterRef{RegisterId::register_dacc_mr, 0x40040000u, 4u, true}, 24u, 4u, true};
  static constexpr RuntimeIndexedFieldRef kChannelEnablePattern = RuntimeIndexedFieldRef{0x40040000u, 16u, 0u, 0u, 1u, 1u, true};
  static constexpr RuntimeIndexedFieldRef kChannelDisablePattern = RuntimeIndexedFieldRef{0x40040000u, 20u, 0u, 0u, 1u, 1u, true};
  static constexpr RuntimeIndexedFieldRef kChannelReadyPattern = RuntimeIndexedFieldRef{0x40040000u, 24u, 0u, 16u, 1u, 1u, true};
  static constexpr RuntimeIndexedFieldRef kTriggerEnablePattern = RuntimeIndexedFieldRef{0x40040000u, 8u, 0u, 0u, 1u, 1u, true};
  static constexpr RuntimeIndexedFieldRef kTriggerSelectPattern = RuntimeIndexedFieldRef{0x40040000u, 8u, 0u, 4u, 3u, 4u, true};
  static constexpr RuntimeIndexedFieldRef kDataPattern = RuntimeIndexedFieldRef{0x40040000u, 28u, 0u, 0u, 16u, 16u, true};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr std::array<DmaBindingRef, 2> kDmaBindings = {{
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_dacc_ch0_tx_xdmac_perid_30, 30u, DmaBindingDirection::none, 16u, true},
    DmaBindingRef{DmaControllerId::XDMAC, DmaBindingId::dma_binding_dacc_ch1_tx_xdmac_perid_31, 31u, DmaBindingDirection::none, 16u, true},
  }};
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
struct DacChannelSemanticTraits<PeripheralId::DACC, 0u> {
  static constexpr bool kPresent = true;
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::field_dacc_cher_ch0, RuntimeRegisterRef{RegisterId::register_dacc_cher, 0x40040000u, 16u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kDisableField = RuntimeFieldRef{FieldId::field_dacc_chdr_ch0, RuntimeRegisterRef{RegisterId::register_dacc_chdr, 0x40040000u, 20u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kReadyField = RuntimeFieldRef{FieldId::field_dacc_chsr_dacrdy0, RuntimeRegisterRef{RegisterId::register_dacc_chsr, 0x40040000u, 24u, true}, 8u, 1u, true};
  static constexpr RuntimeFieldRef kTriggerEnableField = RuntimeFieldRef{FieldId::field_dacc_trigr_trgen0, RuntimeRegisterRef{RegisterId::register_dacc_trigr, 0x40040000u, 8u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kTriggerSelectField = RuntimeFieldRef{FieldId::field_dacc_trigr_trgsel0, RuntimeRegisterRef{RegisterId::register_dacc_trigr, 0x40040000u, 8u, true}, 4u, 3u, true};
  static constexpr RuntimeFieldRef kDataField = RuntimeFieldRef{FieldId::field_dacc_cdr__s_data0, RuntimeRegisterRef{RegisterId::register_dacc_cdr__s, 0x40040000u, 28u, true}, 0u, 16u, true};
};

template<>
struct DacChannelSemanticTraits<PeripheralId::DACC, 1u> {
  static constexpr bool kPresent = true;
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::field_dacc_cher_ch1, RuntimeRegisterRef{RegisterId::register_dacc_cher, 0x40040000u, 16u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kDisableField = RuntimeFieldRef{FieldId::field_dacc_chdr_ch1, RuntimeRegisterRef{RegisterId::register_dacc_chdr, 0x40040000u, 20u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kReadyField = RuntimeFieldRef{FieldId::field_dacc_chsr_dacrdy1, RuntimeRegisterRef{RegisterId::register_dacc_chsr, 0x40040000u, 24u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kTriggerEnableField = RuntimeFieldRef{FieldId::field_dacc_trigr_trgen1, RuntimeRegisterRef{RegisterId::register_dacc_trigr, 0x40040000u, 8u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kTriggerSelectField = RuntimeFieldRef{FieldId::field_dacc_trigr_trgsel1, RuntimeRegisterRef{RegisterId::register_dacc_trigr, 0x40040000u, 8u, true}, 8u, 3u, true};
  static constexpr RuntimeFieldRef kDataField = RuntimeFieldRef{FieldId::field_dacc_cdr__s_data1, RuntimeRegisterRef{RegisterId::register_dacc_cdr__s, 0x40040000u, 28u, true}, 16u, 16u, true};
};

inline constexpr std::array<PeripheralId, 1> kDacSemanticPeripherals = {{
  PeripheralId::DACC,
}};
}
}
}
}
}
}
}
