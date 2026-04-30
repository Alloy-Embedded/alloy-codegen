#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace nordic {
namespace nrf52 {
namespace generated {
namespace runtime {
namespace devices {
namespace nrf52840 {
enum class RegisterId : std::uint16_t {
  none,
};

enum class RegisterRole : std::uint16_t {
  none,
  general,
  secondary_core_release,
};

template<RegisterId Id>
struct RegisterTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

inline constexpr std::array<RegisterId, 0> kRegisters = {};
}
}
}
}
}
}
