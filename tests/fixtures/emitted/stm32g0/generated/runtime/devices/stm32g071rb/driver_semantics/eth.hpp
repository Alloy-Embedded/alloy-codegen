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
namespace stm32g071rb {
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
};

inline constexpr std::array<PeripheralId, 0> kEthSemanticPeripherals = {};
}
}
}
}
}
}
}
