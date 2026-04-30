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
struct SdmmcSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr bool kSupports1Bit = false;
  static constexpr bool kSupports4Bit = false;
  static constexpr bool kSupports8Bit = false;
  static constexpr bool kHasDma = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDataTimeoutRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSdCardRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kArgumentRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCommandRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kBlockRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kCompletionTimeoutRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDmaRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kReadDataRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kWriteDataRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPowerSaveEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPowerSaveDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kClockDividerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kPowerSaveDividerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kReadProofField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kWriteProofField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSlotSelectField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBusWidthField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kArgumentField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCommandIndexField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kResponseTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSpecialCommandField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOpenDrainField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kMaxLatencyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTransferCommandField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTransferDirectionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTransferTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSdioInterruptCommandField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAtacsField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBlockCountField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBlockLengthField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kCommandReadyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxReadyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxReadyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTransferDoneField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNotBusyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDmaEnableField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 0u;
  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;
};

template<>
struct SdmmcSemanticTraits<PeripheralId::HSMCI> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_hsmci_microchip_hsmci_r;
  static constexpr bool kSupports1Bit = true;
  static constexpr bool kSupports4Bit = true;
  static constexpr bool kSupports8Bit = false;
  static constexpr bool kHasDma = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_hsmci_cr, 0x40000000u, 0u, true};
  static constexpr RuntimeRegisterRef kModeRegister = RuntimeRegisterRef{RegisterId::register_hsmci_mr, 0x40000000u, 4u, true};
  static constexpr RuntimeRegisterRef kDataTimeoutRegister = RuntimeRegisterRef{RegisterId::register_hsmci_dtor, 0x40000000u, 8u, true};
  static constexpr RuntimeRegisterRef kSdCardRegister = RuntimeRegisterRef{RegisterId::register_hsmci_sdcr, 0x40000000u, 12u, true};
  static constexpr RuntimeRegisterRef kArgumentRegister = RuntimeRegisterRef{RegisterId::register_hsmci_argr, 0x40000000u, 16u, true};
  static constexpr RuntimeRegisterRef kCommandRegister = RuntimeRegisterRef{RegisterId::register_hsmci_cmdr, 0x40000000u, 20u, true};
  static constexpr RuntimeRegisterRef kBlockRegister = RuntimeRegisterRef{RegisterId::register_hsmci_blkr, 0x40000000u, 24u, true};
  static constexpr RuntimeRegisterRef kCompletionTimeoutRegister = RuntimeRegisterRef{RegisterId::register_hsmci_cstor, 0x40000000u, 28u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::register_hsmci_sr, 0x40000000u, 64u, true};
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = RuntimeRegisterRef{RegisterId::register_hsmci_ier, 0x40000000u, 68u, true};
  static constexpr RuntimeRegisterRef kInterruptDisableRegister = RuntimeRegisterRef{RegisterId::register_hsmci_idr, 0x40000000u, 72u, true};
  static constexpr RuntimeRegisterRef kInterruptMaskRegister = RuntimeRegisterRef{RegisterId::register_hsmci_imr, 0x40000000u, 76u, true};
  static constexpr RuntimeRegisterRef kDmaRegister = RuntimeRegisterRef{RegisterId::register_hsmci_dma, 0x40000000u, 80u, true};
  static constexpr RuntimeRegisterRef kConfigRegister = RuntimeRegisterRef{RegisterId::register_hsmci_cfg, 0x40000000u, 84u, true};
  static constexpr RuntimeRegisterRef kReadDataRegister = RuntimeRegisterRef{RegisterId::register_hsmci_rdr, 0x40000000u, 48u, true};
  static constexpr RuntimeRegisterRef kWriteDataRegister = RuntimeRegisterRef{RegisterId::register_hsmci_tdr, 0x40000000u, 52u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::field_hsmci_cr_mcien, RuntimeRegisterRef{RegisterId::register_hsmci_cr, 0x40000000u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kDisableField = RuntimeFieldRef{FieldId::field_hsmci_cr_mcidis, RuntimeRegisterRef{RegisterId::register_hsmci_cr, 0x40000000u, 0u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kPowerSaveEnableField = RuntimeFieldRef{FieldId::field_hsmci_cr_pwsen, RuntimeRegisterRef{RegisterId::register_hsmci_cr, 0x40000000u, 0u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kPowerSaveDisableField = RuntimeFieldRef{FieldId::field_hsmci_cr_pwsdis, RuntimeRegisterRef{RegisterId::register_hsmci_cr, 0x40000000u, 0u, true}, 3u, 1u, true};
  static constexpr RuntimeFieldRef kSoftwareResetField = RuntimeFieldRef{FieldId::field_hsmci_cr_swrst, RuntimeRegisterRef{RegisterId::register_hsmci_cr, 0x40000000u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kClockDividerField = RuntimeFieldRef{FieldId::field_hsmci_mr_clkdiv, RuntimeRegisterRef{RegisterId::register_hsmci_mr, 0x40000000u, 4u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kPowerSaveDividerField = RuntimeFieldRef{FieldId::field_hsmci_mr_pwsdiv, RuntimeRegisterRef{RegisterId::register_hsmci_mr, 0x40000000u, 4u, true}, 8u, 3u, true};
  static constexpr RuntimeFieldRef kReadProofField = RuntimeFieldRef{FieldId::field_hsmci_mr_rdproof, RuntimeRegisterRef{RegisterId::register_hsmci_mr, 0x40000000u, 4u, true}, 11u, 1u, true};
  static constexpr RuntimeFieldRef kWriteProofField = RuntimeFieldRef{FieldId::field_hsmci_mr_wrproof, RuntimeRegisterRef{RegisterId::register_hsmci_mr, 0x40000000u, 4u, true}, 12u, 1u, true};
  static constexpr RuntimeFieldRef kSlotSelectField = RuntimeFieldRef{FieldId::field_hsmci_sdcr_sdcsel, RuntimeRegisterRef{RegisterId::register_hsmci_sdcr, 0x40000000u, 12u, true}, 0u, 2u, true};
  static constexpr RuntimeFieldRef kBusWidthField = RuntimeFieldRef{FieldId::field_hsmci_sdcr_sdcbus, RuntimeRegisterRef{RegisterId::register_hsmci_sdcr, 0x40000000u, 12u, true}, 6u, 2u, true};
  static constexpr RuntimeFieldRef kArgumentField = RuntimeFieldRef{FieldId::field_hsmci_argr_arg, RuntimeRegisterRef{RegisterId::register_hsmci_argr, 0x40000000u, 16u, true}, 0u, 32u, true};
  static constexpr RuntimeFieldRef kCommandIndexField = RuntimeFieldRef{FieldId::field_hsmci_cmdr_cmdnb, RuntimeRegisterRef{RegisterId::register_hsmci_cmdr, 0x40000000u, 20u, true}, 0u, 6u, true};
  static constexpr RuntimeFieldRef kResponseTypeField = RuntimeFieldRef{FieldId::field_hsmci_cmdr_rsptyp, RuntimeRegisterRef{RegisterId::register_hsmci_cmdr, 0x40000000u, 20u, true}, 6u, 2u, true};
  static constexpr RuntimeFieldRef kSpecialCommandField = RuntimeFieldRef{FieldId::field_hsmci_cmdr_spcmd, RuntimeRegisterRef{RegisterId::register_hsmci_cmdr, 0x40000000u, 20u, true}, 8u, 3u, true};
  static constexpr RuntimeFieldRef kOpenDrainField = RuntimeFieldRef{FieldId::field_hsmci_cmdr_opdcmd, RuntimeRegisterRef{RegisterId::register_hsmci_cmdr, 0x40000000u, 20u, true}, 11u, 1u, true};
  static constexpr RuntimeFieldRef kMaxLatencyField = RuntimeFieldRef{FieldId::field_hsmci_cmdr_maxlat, RuntimeRegisterRef{RegisterId::register_hsmci_cmdr, 0x40000000u, 20u, true}, 12u, 1u, true};
  static constexpr RuntimeFieldRef kTransferCommandField = RuntimeFieldRef{FieldId::field_hsmci_cmdr_trcmd, RuntimeRegisterRef{RegisterId::register_hsmci_cmdr, 0x40000000u, 20u, true}, 16u, 2u, true};
  static constexpr RuntimeFieldRef kTransferDirectionField = RuntimeFieldRef{FieldId::field_hsmci_cmdr_trdir, RuntimeRegisterRef{RegisterId::register_hsmci_cmdr, 0x40000000u, 20u, true}, 18u, 1u, true};
  static constexpr RuntimeFieldRef kTransferTypeField = RuntimeFieldRef{FieldId::field_hsmci_cmdr_trtyp, RuntimeRegisterRef{RegisterId::register_hsmci_cmdr, 0x40000000u, 20u, true}, 19u, 3u, true};
  static constexpr RuntimeFieldRef kSdioInterruptCommandField = RuntimeFieldRef{FieldId::field_hsmci_cmdr_iospcmd, RuntimeRegisterRef{RegisterId::register_hsmci_cmdr, 0x40000000u, 20u, true}, 24u, 2u, true};
  static constexpr RuntimeFieldRef kAtacsField = RuntimeFieldRef{FieldId::field_hsmci_cmdr_atacs, RuntimeRegisterRef{RegisterId::register_hsmci_cmdr, 0x40000000u, 20u, true}, 26u, 1u, true};
  static constexpr RuntimeFieldRef kBlockCountField = RuntimeFieldRef{FieldId::field_hsmci_blkr_bcnt, RuntimeRegisterRef{RegisterId::register_hsmci_blkr, 0x40000000u, 24u, true}, 0u, 16u, true};
  static constexpr RuntimeFieldRef kBlockLengthField = RuntimeFieldRef{FieldId::field_hsmci_blkr_blklen, RuntimeRegisterRef{RegisterId::register_hsmci_blkr, 0x40000000u, 24u, true}, 16u, 16u, true};
  static constexpr RuntimeFieldRef kCommandReadyField = RuntimeFieldRef{FieldId::field_hsmci_sr_cmdrdy, RuntimeRegisterRef{RegisterId::register_hsmci_sr, 0x40000000u, 64u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kRxReadyField = RuntimeFieldRef{FieldId::field_hsmci_sr_rxrdy, RuntimeRegisterRef{RegisterId::register_hsmci_sr, 0x40000000u, 64u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kTxReadyField = RuntimeFieldRef{FieldId::field_hsmci_sr_txrdy, RuntimeRegisterRef{RegisterId::register_hsmci_sr, 0x40000000u, 64u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kTransferDoneField = RuntimeFieldRef{FieldId::field_hsmci_sr_xfrdone, RuntimeRegisterRef{RegisterId::register_hsmci_sr, 0x40000000u, 64u, true}, 27u, 1u, true};
  static constexpr RuntimeFieldRef kNotBusyField = RuntimeFieldRef{FieldId::field_hsmci_sr_notbusy, RuntimeRegisterRef{RegisterId::register_hsmci_sr, 0x40000000u, 64u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kDmaEnableField = RuntimeFieldRef{FieldId::field_hsmci_dma_dmaen, RuntimeRegisterRef{RegisterId::register_hsmci_dma, 0x40000000u, 80u, true}, 8u, 1u, true};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 0u;
  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;
};

inline constexpr std::array<PeripheralId, 1> kSdmmcSemanticPeripherals = {{
  PeripheralId::HSMCI,
}};
}
}
}
}
}
}
}
