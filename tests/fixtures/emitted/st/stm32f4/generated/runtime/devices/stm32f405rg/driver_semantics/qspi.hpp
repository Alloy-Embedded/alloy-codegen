#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../pins.hpp"

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f405rg {
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

inline constexpr std::array<PeripheralId, 0> kQspiSemanticPeripherals = {};
}
}
}
}
}
}
}
