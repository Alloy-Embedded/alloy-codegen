#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
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
};

inline constexpr std::array<PeripheralId, 0> kSdmmcSemanticPeripherals = {};
}
}
}
}
}
}
}
