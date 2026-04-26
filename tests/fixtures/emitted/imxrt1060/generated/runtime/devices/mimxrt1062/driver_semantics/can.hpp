#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
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
struct CanSemanticTraits<PeripheralId::CAN1> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_can_nxp_can;
  static constexpr bool kHasFlexibleDataRate = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_can1_mcr, 0x401D0000u, 0u, true};
  static constexpr RuntimeRegisterRef kNominalTimingRegister = RuntimeRegisterRef{RegisterId::none, 0x401D0000u, 4u, true};
  static constexpr RuntimeRegisterRef kDataTimingRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTestRegister = RuntimeRegisterRef{RegisterId::none, 0x401D0000u, 4u, true};
  static constexpr RuntimeRegisterRef kErrorCounterRegister = RuntimeRegisterRef{RegisterId::none, 0x401D0000u, 28u, true};
  static constexpr RuntimeRegisterRef kProtocolStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x401D0000u, 32u, true};
  static constexpr RuntimeRegisterRef kInterruptRegister = RuntimeRegisterRef{RegisterId::none, 0x401D0000u, 48u, true};
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = RuntimeRegisterRef{RegisterId::none, 0x401D0000u, 40u, true};
  static constexpr RuntimeRegisterRef kInterruptLineSelectRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptLineEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kGlobalFilterRegister = RuntimeRegisterRef{RegisterId::none, 0x401D0000u, 72u, true};
  static constexpr RuntimeRegisterRef kStandardFilterConfigRegister = RuntimeRegisterRef{RegisterId::none, 0x401D0000u, 16u, true};
  static constexpr RuntimeRegisterRef kExtendedFilterConfigRegister = RuntimeRegisterRef{RegisterId::none, 0x401D0000u, 20u, true};
  static constexpr RuntimeRegisterRef kExtendedIdMaskRegister = RuntimeRegisterRef{RegisterId::none, 0x401D0000u, 24u, true};
  static constexpr RuntimeRegisterRef kRxFifo0ConfigRegister = RuntimeRegisterRef{RegisterId::register_can1_mcr, 0x401D0000u, 0u, true};
  static constexpr RuntimeRegisterRef kRxFifo0StatusRegister = RuntimeRegisterRef{RegisterId::none, 0x401D0000u, 76u, true};
  static constexpr RuntimeRegisterRef kRxFifo0AckRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxBufferConfigRegister = RuntimeRegisterRef{RegisterId::register_can1_mcr, 0x401D0000u, 0u, true};
  static constexpr RuntimeRegisterRef kTxFifoQueueStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x401D0000u, 48u, true};
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
struct CanSemanticTraits<PeripheralId::CAN2> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_can_nxp_can;
  static constexpr bool kHasFlexibleDataRate = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_can2_mcr, 0x401D4000u, 0u, true};
  static constexpr RuntimeRegisterRef kNominalTimingRegister = RuntimeRegisterRef{RegisterId::none, 0x401D4000u, 4u, true};
  static constexpr RuntimeRegisterRef kDataTimingRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTestRegister = RuntimeRegisterRef{RegisterId::none, 0x401D4000u, 4u, true};
  static constexpr RuntimeRegisterRef kErrorCounterRegister = RuntimeRegisterRef{RegisterId::none, 0x401D4000u, 28u, true};
  static constexpr RuntimeRegisterRef kProtocolStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x401D4000u, 32u, true};
  static constexpr RuntimeRegisterRef kInterruptRegister = RuntimeRegisterRef{RegisterId::none, 0x401D4000u, 48u, true};
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = RuntimeRegisterRef{RegisterId::none, 0x401D4000u, 40u, true};
  static constexpr RuntimeRegisterRef kInterruptLineSelectRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptLineEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kGlobalFilterRegister = RuntimeRegisterRef{RegisterId::none, 0x401D4000u, 72u, true};
  static constexpr RuntimeRegisterRef kStandardFilterConfigRegister = RuntimeRegisterRef{RegisterId::none, 0x401D4000u, 16u, true};
  static constexpr RuntimeRegisterRef kExtendedFilterConfigRegister = RuntimeRegisterRef{RegisterId::none, 0x401D4000u, 20u, true};
  static constexpr RuntimeRegisterRef kExtendedIdMaskRegister = RuntimeRegisterRef{RegisterId::none, 0x401D4000u, 24u, true};
  static constexpr RuntimeRegisterRef kRxFifo0ConfigRegister = RuntimeRegisterRef{RegisterId::register_can2_mcr, 0x401D4000u, 0u, true};
  static constexpr RuntimeRegisterRef kRxFifo0StatusRegister = RuntimeRegisterRef{RegisterId::none, 0x401D4000u, 76u, true};
  static constexpr RuntimeRegisterRef kRxFifo0AckRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxBufferConfigRegister = RuntimeRegisterRef{RegisterId::register_can2_mcr, 0x401D4000u, 0u, true};
  static constexpr RuntimeRegisterRef kTxFifoQueueStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x401D4000u, 48u, true};
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
struct CanSemanticTraits<PeripheralId::CAN3> {
  static constexpr bool kPresent = true;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_can_nxp_can;
  static constexpr bool kHasFlexibleDataRate = false;
  static constexpr RuntimeRegisterRef kControlRegister = RuntimeRegisterRef{RegisterId::register_can3_mcr, 0x401D8000u, 0u, true};
  static constexpr RuntimeRegisterRef kNominalTimingRegister = RuntimeRegisterRef{RegisterId::none, 0x401D8000u, 4u, true};
  static constexpr RuntimeRegisterRef kDataTimingRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTestRegister = RuntimeRegisterRef{RegisterId::none, 0x401D8000u, 4u, true};
  static constexpr RuntimeRegisterRef kErrorCounterRegister = RuntimeRegisterRef{RegisterId::none, 0x401D8000u, 28u, true};
  static constexpr RuntimeRegisterRef kProtocolStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x401D8000u, 32u, true};
  static constexpr RuntimeRegisterRef kInterruptRegister = RuntimeRegisterRef{RegisterId::none, 0x401D8000u, 48u, true};
  static constexpr RuntimeRegisterRef kInterruptEnableRegister = RuntimeRegisterRef{RegisterId::none, 0x401D8000u, 40u, true};
  static constexpr RuntimeRegisterRef kInterruptLineSelectRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kInterruptLineEnableRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kGlobalFilterRegister = RuntimeRegisterRef{RegisterId::none, 0x401D8000u, 72u, true};
  static constexpr RuntimeRegisterRef kStandardFilterConfigRegister = RuntimeRegisterRef{RegisterId::none, 0x401D8000u, 16u, true};
  static constexpr RuntimeRegisterRef kExtendedFilterConfigRegister = RuntimeRegisterRef{RegisterId::none, 0x401D8000u, 20u, true};
  static constexpr RuntimeRegisterRef kExtendedIdMaskRegister = RuntimeRegisterRef{RegisterId::none, 0x401D8000u, 24u, true};
  static constexpr RuntimeRegisterRef kRxFifo0ConfigRegister = RuntimeRegisterRef{RegisterId::register_can3_mcr, 0x401D8000u, 0u, true};
  static constexpr RuntimeRegisterRef kRxFifo0StatusRegister = RuntimeRegisterRef{RegisterId::none, 0x401D8000u, 76u, true};
  static constexpr RuntimeRegisterRef kRxFifo0AckRegister = kInvalidRegisterRef;
  static constexpr RuntimeRegisterRef kTxBufferConfigRegister = RuntimeRegisterRef{RegisterId::register_can3_mcr, 0x401D8000u, 0u, true};
  static constexpr RuntimeRegisterRef kTxFifoQueueStatusRegister = RuntimeRegisterRef{RegisterId::none, 0x401D8000u, 48u, true};
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

inline constexpr std::array<PeripheralId, 3> kCanSemanticPeripherals = {{
  PeripheralId::CAN1,
  PeripheralId::CAN2,
  PeripheralId::CAN3,
}};
}
}
}
}
}
}
}
