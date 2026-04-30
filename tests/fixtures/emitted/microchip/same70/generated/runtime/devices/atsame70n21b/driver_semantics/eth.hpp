#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70n21b {
namespace driver_semantics {
template<PeripheralId Id>
struct EthSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr bool kSupportsMii = false;
  static constexpr bool kSupportsRmii = false;
  static constexpr bool kHasDmaEngine = false;
  static constexpr bool kHasStatisticsCounters = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kUserIoRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDmaConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRxStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRxDescriptorBaseRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxDescriptorBaseRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kRxEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kManagementPortEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClearStatisticsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kWriteEnableStatisticsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxStartField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSpeedField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kFullDuplexField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kMdcClockDividerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRmiiEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kManagementDoneField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxCompleteInterruptField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxCompleteInterruptField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxCompleteInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxCompleteInterruptEnableField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};
};

template<>
struct EthSemanticTraits<PeripheralId::GMAC> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_eth_microchip_gmac_s;
  static constexpr bool kSupportsMii = true;
  static constexpr bool kSupportsRmii = true;
  static constexpr bool kHasDmaEngine = true;
  static constexpr bool kHasStatisticsCounters = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_gmac_ncr, 0x40050000u, 0u, true};
  static constexpr RuntimeRegisterRef kConfigRegister = RuntimeRegisterRef{RegisterId::register_gmac_ncfgr, 0x40050000u, 4u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::register_gmac_nsr, 0x40050000u, 8u, true};
  static constexpr RuntimeRegisterRef kUserIoRegister = RuntimeRegisterRef{RegisterId::register_gmac_ur, 0x40050000u, 12u, true};
  static constexpr RuntimeRegisterRef kDmaConfigRegister = RuntimeRegisterRef{RegisterId::register_gmac_dcfgr, 0x40050000u, 16u, true};
  static constexpr RuntimeRegisterRef kTxStatusRegister = RuntimeRegisterRef{RegisterId::register_gmac_tsr, 0x40050000u, 20u, true};
  static constexpr RuntimeRegisterRef kRxStatusRegister = RuntimeRegisterRef{RegisterId::register_gmac_rsr, 0x40050000u, 32u, true};
  static constexpr RuntimeRegisterRef kInterruptStatusRegister = RuntimeRegisterRef{RegisterId::register_gmac_isr, 0x40050000u, 36u, true};
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = RuntimeRegisterRef{RegisterId::register_gmac_ier, 0x40050000u, 40u, true};
  static constexpr RuntimeRegisterRef kInterruptDisableRegister = RuntimeRegisterRef{RegisterId::register_gmac_idr, 0x40050000u, 44u, true};
  static constexpr RuntimeRegisterRef kInterruptMaskRegister = RuntimeRegisterRef{RegisterId::register_gmac_imr, 0x40050000u, 48u, true};
  static constexpr RuntimeRegisterRef kRxDescriptorBaseRegister = RuntimeRegisterRef{RegisterId::register_gmac_rbqb, 0x40050000u, 24u, true};
  static constexpr RuntimeRegisterRef kTxDescriptorBaseRegister = RuntimeRegisterRef{RegisterId::register_gmac_tbqb, 0x40050000u, 28u, true};
  static constexpr RuntimeFieldRef kRxEnableField = RuntimeFieldRef{FieldId::field_gmac_ncr_rxen, RuntimeRegisterRef{RegisterId::register_gmac_ncr, 0x40050000u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kTxEnableField = RuntimeFieldRef{FieldId::field_gmac_ncr_txen, RuntimeRegisterRef{RegisterId::register_gmac_ncr, 0x40050000u, 0u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kManagementPortEnableField = RuntimeFieldRef{FieldId::field_gmac_ncr_mpe, RuntimeRegisterRef{RegisterId::register_gmac_ncr, 0x40050000u, 0u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kClearStatisticsField = RuntimeFieldRef{FieldId::field_gmac_ncr_clrstat, RuntimeRegisterRef{RegisterId::register_gmac_ncr, 0x40050000u, 0u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kWriteEnableStatisticsField = RuntimeFieldRef{FieldId::field_gmac_ncr_westat, RuntimeRegisterRef{RegisterId::register_gmac_ncr, 0x40050000u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kTxStartField = RuntimeFieldRef{FieldId::field_gmac_ncr_tstart, RuntimeRegisterRef{RegisterId::register_gmac_ncr, 0x40050000u, 0u, true}, 9u, 1u, true};
  static constexpr RuntimeFieldRef kSpeedField = RuntimeFieldRef{FieldId::field_gmac_ncfgr_spd, RuntimeRegisterRef{RegisterId::register_gmac_ncfgr, 0x40050000u, 4u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kFullDuplexField = RuntimeFieldRef{FieldId::field_gmac_ncfgr_fd, RuntimeRegisterRef{RegisterId::register_gmac_ncfgr, 0x40050000u, 4u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kMdcClockDividerField = RuntimeFieldRef{FieldId::field_gmac_ncfgr_clk, RuntimeRegisterRef{RegisterId::register_gmac_ncfgr, 0x40050000u, 4u, true}, 18u, 3u, true};
  static constexpr RuntimeFieldRef kRmiiEnableField = RuntimeFieldRef{FieldId::field_gmac_ur_rmii, RuntimeRegisterRef{RegisterId::register_gmac_ur, 0x40050000u, 12u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kManagementDoneField = RuntimeFieldRef{FieldId::field_gmac_nsr_idle, RuntimeRegisterRef{RegisterId::register_gmac_nsr, 0x40050000u, 8u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kRxCompleteInterruptField = RuntimeFieldRef{FieldId::field_gmac_isr_rcomp, RuntimeRegisterRef{RegisterId::register_gmac_isr, 0x40050000u, 36u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kTxCompleteInterruptField = RuntimeFieldRef{FieldId::field_gmac_isr_tcomp, RuntimeRegisterRef{RegisterId::register_gmac_isr, 0x40050000u, 36u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kRxCompleteInterruptEnableField = RuntimeFieldRef{FieldId::field_gmac_ier_rcomp, RuntimeRegisterRef{RegisterId::register_gmac_ier, 0x40050000u, 40u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kTxCompleteInterruptEnableField = RuntimeFieldRef{FieldId::field_gmac_ier_tcomp, RuntimeRegisterRef{RegisterId::register_gmac_ier, 0x40050000u, 40u, true}, 7u, 1u, true};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr std::array<DmaBindingRef, 0> kDmaBindings = {};
};

inline constexpr std::array<PeripheralId, 1> kEthSemanticPeripherals = {{
  PeripheralId::GMAC,
}};
}
}
}
}
}
}
}
