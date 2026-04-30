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
namespace stm32g0b1re {
namespace driver_semantics {
template<PeripheralId Id>
struct CanSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr bool kHasFlexibleDataRate = false;
  static constexpr RuntimeRegisterRef kControlRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kNominalTimingRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kDataTimingRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTestRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kErrorCounterRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kProtocolStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptLineSelectRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptLineEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kGlobalFilterRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kStandardFilterConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kExtendedFilterConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kExtendedIdMaskRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRxFifo0ConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRxFifo0StatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kRxFifo0AckRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxBufferConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxFifoQueueStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxBufferAddRequestRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxBufferPendingRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxEventFifoConfigRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxEventFifoStatusRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxEventFifoAckRegister = kInvalidRegisterRef;
  static constexpr RuntimeFieldRef kInitField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kConfigEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRestrictedOperationField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRestrictedOperationAckField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBusMonitorField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kFdOperationEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBitRateSwitchEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNominalPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNominalTimeSeg1Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNominalTimeSeg2Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNominalSyncJumpWidthField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataTimeSeg1Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataTimeSeg2Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataSyncJumpWidthField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0NewInterruptField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxCompleteInterruptField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxEventFifoNewInterruptField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0NewInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxCompleteInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxEventFifoNewInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0FillLevelField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0GetIndexField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0MessageLostField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0AckIndexField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxFifoQueuePutIndexField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxFifoQueueFreeLevelField = kInvalidFieldRef;
  static constexpr RuntimeIndexedFieldRef kTxBufferAddRequestPattern = kInvalidIndexedFieldRef;
  static constexpr RuntimeIndexedFieldRef kTxBufferPendingPattern = kInvalidIndexedFieldRef;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

template<>
struct CanSemanticTraits<PeripheralId::FDCAN1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_can_st_fdcan_v1_0;
  static constexpr bool kHasFlexibleDataRate = true;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 24u, true};
  static constexpr RuntimeRegisterRef kNominalTimingRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 28u, true};
  static constexpr RuntimeRegisterRef kDataTimingRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 12u, true};
  static constexpr RuntimeRegisterRef kTestRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 16u, true};
  static constexpr RuntimeRegisterRef kErrorCounterRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 64u, true};
  static constexpr RuntimeRegisterRef kProtocolStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 68u, true};
  static constexpr RuntimeRegisterRef kInterruptRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 80u, true};
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 84u, true};
  static constexpr RuntimeRegisterRef kInterruptLineSelectRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 88u, true};
  static constexpr RuntimeRegisterRef kInterruptLineEnableRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 92u, true};
  static constexpr RuntimeRegisterRef kGlobalFilterRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 128u, true};
  static constexpr RuntimeRegisterRef kStandardFilterConfigRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 132u, true};
  static constexpr RuntimeRegisterRef kExtendedFilterConfigRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 136u, true};
  static constexpr RuntimeRegisterRef kExtendedIdMaskRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 144u, true};
  static constexpr RuntimeRegisterRef kRxFifo0ConfigRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 160u, true};
  static constexpr RuntimeRegisterRef kRxFifo0StatusRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 164u, true};
  static constexpr RuntimeRegisterRef kRxFifo0AckRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 168u, true};
  static constexpr RuntimeRegisterRef kTxBufferConfigRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 192u, true};
  static constexpr RuntimeRegisterRef kTxFifoQueueStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 196u, true};
  static constexpr RuntimeRegisterRef kTxBufferAddRequestRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 208u, true};
  static constexpr RuntimeRegisterRef kTxBufferPendingRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 204u, true};
  static constexpr RuntimeRegisterRef kTxEventFifoConfigRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 240u, true};
  static constexpr RuntimeRegisterRef kTxEventFifoStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 244u, true};
  static constexpr RuntimeRegisterRef kTxEventFifoAckRegister = RuntimeRegisterRef{RegisterId::none, 0x4000A000u, 248u, true};
  static constexpr RuntimeFieldRef kInitField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kConfigEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRestrictedOperationField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRestrictedOperationAckField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBusMonitorField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kFdOperationEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kBitRateSwitchEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNominalPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNominalTimeSeg1Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNominalTimeSeg2Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kNominalSyncJumpWidthField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataPrescalerField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataTimeSeg1Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataTimeSeg2Field = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kDataSyncJumpWidthField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0NewInterruptField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxCompleteInterruptField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxEventFifoNewInterruptField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0NewInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxCompleteInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxEventFifoNewInterruptEnableField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0FillLevelField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0GetIndexField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0MessageLostField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kRxFifo0AckIndexField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxFifoQueuePutIndexField = kInvalidFieldRef;
  static constexpr RuntimeFieldRef kTxFifoQueueFreeLevelField = kInvalidFieldRef;
  static constexpr RuntimeIndexedFieldRef kTxBufferAddRequestPattern = RuntimeIndexedFieldRef{0x4000A000u, 208u, 0u, 0u, 1u, 1u, true};
  static constexpr RuntimeIndexedFieldRef kTxBufferPendingPattern = RuntimeIndexedFieldRef{0x4000A000u, 204u, 0u, 0u, 1u, 1u, true};
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
};

inline constexpr std::array<PeripheralId, 1> kCanSemanticPeripherals = {{
  PeripheralId::FDCAN1,
}};
}
}
}
}
}
}
}
