#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include "common.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
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

inline constexpr std::array<PeripheralId, 0> kDacSemanticPeripherals = {};
}
}
}
}
}
}
}
