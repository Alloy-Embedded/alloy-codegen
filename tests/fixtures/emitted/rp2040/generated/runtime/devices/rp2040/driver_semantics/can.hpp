#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
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

inline constexpr std::array<PeripheralId, 0> kCanSemanticPeripherals = {};
}
}
}
}
}
}
}
