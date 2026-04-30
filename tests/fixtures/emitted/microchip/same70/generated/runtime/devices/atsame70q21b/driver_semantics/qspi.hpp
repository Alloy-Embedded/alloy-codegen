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
namespace atsame70q21b {
namespace driver_semantics {
template<PeripheralId Id>
struct QspiSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr bool kSupportsSpiMode = false;
  static constexpr bool kSupportsMemoryMode = false;
  static constexpr bool kHasScrambling = false;
  static constexpr bool kHasDma = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kModeRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptDisableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptMaskRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kSerialClockRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInstructionAddressRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInstructionCodeRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInstructionFrameRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kScramblingModeRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kScramblingKeyRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kReceiveDataRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTransmitDataRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDisableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSoftwareResetField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kLastTransferField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kEnabledStatusField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSerialMemoryModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kChipSelectModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBitsPerTransferField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kReceiveReadyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTransmitReadyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTransmitEmptyField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kReceiveReadyInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTransmitReadyInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTransmitEmptyInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kSerialClockBaudRateField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInstructionField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAddressField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kWidthField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kInstructionEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kAddressEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kOptionEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTransferTypeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kContinuousReadModeField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDummyCyclesField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kScramblingEnableField = kInvalidFieldRef;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 0u;
  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;
};

template<>
struct QspiSemanticTraits<PeripheralId::QSPI> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_qspi_microchip_qspi_j;
  static constexpr bool kSupportsSpiMode = true;
  static constexpr bool kSupportsMemoryMode = true;
  static constexpr bool kHasScrambling = true;
  static constexpr bool kHasDma = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_qspi_cr, 0x4007C000u, 0u, true};
  static constexpr RuntimeRegisterRef kModeRegister = RuntimeRegisterRef{RegisterId::register_qspi_mr, 0x4007C000u, 4u, true};
  static constexpr RuntimeRegisterRef kStatusRegister = RuntimeRegisterRef{RegisterId::register_qspi_sr, 0x4007C000u, 16u, true};
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = RuntimeRegisterRef{RegisterId::register_qspi_ier, 0x4007C000u, 20u, true};
  static constexpr RuntimeRegisterRef kInterruptDisableRegister = RuntimeRegisterRef{RegisterId::register_qspi_idr, 0x4007C000u, 24u, true};
  static constexpr RuntimeRegisterRef kInterruptMaskRegister = RuntimeRegisterRef{RegisterId::register_qspi_imr, 0x4007C000u, 28u, true};
  static constexpr RuntimeRegisterRef kSerialClockRegister = RuntimeRegisterRef{RegisterId::register_qspi_scr, 0x4007C000u, 32u, true};
  static constexpr RuntimeRegisterRef kInstructionAddressRegister = RuntimeRegisterRef{RegisterId::register_qspi_iar, 0x4007C000u, 48u, true};
  static constexpr RuntimeRegisterRef kInstructionCodeRegister = RuntimeRegisterRef{RegisterId::register_qspi_icr, 0x4007C000u, 52u, true};
  static constexpr RuntimeRegisterRef kInstructionFrameRegister = RuntimeRegisterRef{RegisterId::register_qspi_ifr, 0x4007C000u, 56u, true};
  static constexpr RuntimeRegisterRef kScramblingModeRegister = RuntimeRegisterRef{RegisterId::register_qspi_smr, 0x4007C000u, 64u, true};
  static constexpr RuntimeRegisterRef kScramblingKeyRegister = RuntimeRegisterRef{RegisterId::register_qspi_skr, 0x4007C000u, 68u, true};
  static constexpr RuntimeRegisterRef kReceiveDataRegister = RuntimeRegisterRef{RegisterId::register_qspi_rdr, 0x4007C000u, 8u, true};
  static constexpr RuntimeRegisterRef kTransmitDataRegister = RuntimeRegisterRef{RegisterId::register_qspi_tdr, 0x4007C000u, 12u, true};
  static constexpr RuntimeFieldRef kEnableField = RuntimeFieldRef{FieldId::field_qspi_cr_qspien, RuntimeRegisterRef{RegisterId::register_qspi_cr, 0x4007C000u, 0u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kDisableField = RuntimeFieldRef{FieldId::field_qspi_cr_qspidis, RuntimeRegisterRef{RegisterId::register_qspi_cr, 0x4007C000u, 0u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kSoftwareResetField = RuntimeFieldRef{FieldId::field_qspi_cr_swrst, RuntimeRegisterRef{RegisterId::register_qspi_cr, 0x4007C000u, 0u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kLastTransferField = RuntimeFieldRef{FieldId::field_qspi_cr_lastxfer, RuntimeRegisterRef{RegisterId::register_qspi_cr, 0x4007C000u, 0u, true}, 24u, 1u, true};
  static constexpr RuntimeFieldRef kEnabledStatusField = RuntimeFieldRef{FieldId::field_qspi_sr_qspiens, RuntimeRegisterRef{RegisterId::register_qspi_sr, 0x4007C000u, 16u, true}, 24u, 1u, true};
  static constexpr RuntimeFieldRef kSerialMemoryModeField = RuntimeFieldRef{FieldId::field_qspi_mr_smm, RuntimeRegisterRef{RegisterId::register_qspi_mr, 0x4007C000u, 4u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kChipSelectModeField = RuntimeFieldRef{FieldId::field_qspi_mr_csmode, RuntimeRegisterRef{RegisterId::register_qspi_mr, 0x4007C000u, 4u, true}, 4u, 2u, true};
  static constexpr RuntimeFieldRef kBitsPerTransferField = RuntimeFieldRef{FieldId::field_qspi_mr_nbbits, RuntimeRegisterRef{RegisterId::register_qspi_mr, 0x4007C000u, 4u, true}, 8u, 4u, true};
  static constexpr RuntimeFieldRef kReceiveReadyField = RuntimeFieldRef{FieldId::field_qspi_sr_rdrf, RuntimeRegisterRef{RegisterId::register_qspi_sr, 0x4007C000u, 16u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kTransmitReadyField = RuntimeFieldRef{FieldId::field_qspi_sr_tdre, RuntimeRegisterRef{RegisterId::register_qspi_sr, 0x4007C000u, 16u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kTransmitEmptyField = RuntimeFieldRef{FieldId::field_qspi_sr_txempty, RuntimeRegisterRef{RegisterId::register_qspi_sr, 0x4007C000u, 16u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kReceiveReadyInterruptEnableField = RuntimeFieldRef{FieldId::field_qspi_ier_rdrf, RuntimeRegisterRef{RegisterId::register_qspi_ier, 0x4007C000u, 20u, true}, 0u, 1u, true};
  static constexpr RuntimeFieldRef kTransmitReadyInterruptEnableField = RuntimeFieldRef{FieldId::field_qspi_ier_tdre, RuntimeRegisterRef{RegisterId::register_qspi_ier, 0x4007C000u, 20u, true}, 1u, 1u, true};
  static constexpr RuntimeFieldRef kTransmitEmptyInterruptEnableField = RuntimeFieldRef{FieldId::field_qspi_ier_txempty, RuntimeRegisterRef{RegisterId::register_qspi_ier, 0x4007C000u, 20u, true}, 2u, 1u, true};
  static constexpr RuntimeFieldRef kSerialClockBaudRateField = RuntimeFieldRef{FieldId::field_qspi_scr_scbr, RuntimeRegisterRef{RegisterId::register_qspi_scr, 0x4007C000u, 32u, true}, 8u, 8u, true};
  static constexpr RuntimeFieldRef kInstructionField = RuntimeFieldRef{FieldId::field_qspi_icr_inst, RuntimeRegisterRef{RegisterId::register_qspi_icr, 0x4007C000u, 52u, true}, 0u, 8u, true};
  static constexpr RuntimeFieldRef kAddressField = RuntimeFieldRef{FieldId::field_qspi_iar_addr, RuntimeRegisterRef{RegisterId::register_qspi_iar, 0x4007C000u, 48u, true}, 0u, 32u, true};
  static constexpr RuntimeFieldRef kWidthField = RuntimeFieldRef{FieldId::field_qspi_ifr_width, RuntimeRegisterRef{RegisterId::register_qspi_ifr, 0x4007C000u, 56u, true}, 0u, 3u, true};
  static constexpr RuntimeFieldRef kInstructionEnableField = RuntimeFieldRef{FieldId::field_qspi_ifr_insten, RuntimeRegisterRef{RegisterId::register_qspi_ifr, 0x4007C000u, 56u, true}, 4u, 1u, true};
  static constexpr RuntimeFieldRef kAddressEnableField = RuntimeFieldRef{FieldId::field_qspi_ifr_addren, RuntimeRegisterRef{RegisterId::register_qspi_ifr, 0x4007C000u, 56u, true}, 5u, 1u, true};
  static constexpr RuntimeFieldRef kOptionEnableField = RuntimeFieldRef{FieldId::field_qspi_ifr_opten, RuntimeRegisterRef{RegisterId::register_qspi_ifr, 0x4007C000u, 56u, true}, 6u, 1u, true};
  static constexpr RuntimeFieldRef kDataEnableField = RuntimeFieldRef{FieldId::field_qspi_ifr_dataen, RuntimeRegisterRef{RegisterId::register_qspi_ifr, 0x4007C000u, 56u, true}, 7u, 1u, true};
  static constexpr RuntimeFieldRef kTransferTypeField = RuntimeFieldRef{FieldId::field_qspi_ifr_tfrtyp, RuntimeRegisterRef{RegisterId::register_qspi_ifr, 0x4007C000u, 56u, true}, 12u, 2u, true};
  static constexpr RuntimeFieldRef kContinuousReadModeField = RuntimeFieldRef{FieldId::field_qspi_ifr_crm, RuntimeRegisterRef{RegisterId::register_qspi_ifr, 0x4007C000u, 56u, true}, 14u, 1u, true};
  static constexpr RuntimeFieldRef kDummyCyclesField = RuntimeFieldRef{FieldId::field_qspi_ifr_nbdum, RuntimeRegisterRef{RegisterId::register_qspi_ifr, 0x4007C000u, 56u, true}, 16u, 5u, true};
  static constexpr RuntimeFieldRef kScramblingEnableField = RuntimeFieldRef{FieldId::field_qspi_smr_scren, RuntimeRegisterRef{RegisterId::register_qspi_smr, 0x4007C000u, 64u, true}, 0u, 1u, true};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr RuntimeFieldRef kKernelClockSelectorField = kInvalidFieldRef;
  static constexpr std::array<KernelClockSourceOption, 0> kKernelClockSourceOptions = {};
  static constexpr std::uint32_t kKernelMaxClockHz = 0u;
  static constexpr RuntimeFieldRef kClockGateField = kInvalidFieldRef;
};

inline constexpr std::array<PeripheralId, 1> kQspiSemanticPeripherals = {{
  PeripheralId::QSPI,
}};
}
}
}
}
}
}
}
