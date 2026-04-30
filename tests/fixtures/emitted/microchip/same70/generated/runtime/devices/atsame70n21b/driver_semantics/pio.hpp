#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70n21b {
namespace driver_semantics {
enum class PioId : std::uint8_t {
  None = 0,
};

template<PioId Id>
struct PioSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint8_t kStateMachineCount = 0;
  static constexpr std::uint8_t kInstructionMemoryDepth = 0;
  static constexpr std::uint8_t kTxFifoDepth = 0;
  static constexpr std::uint8_t kRxFifoDepth = 0;
  static constexpr std::uint8_t kGpioBase = 0;
  static constexpr std::uint8_t kGpioCount = 0;
  static constexpr std::uint32_t kBaseAddress = 0;
  static constexpr std::uint8_t kDreqTx = 0;
  static constexpr std::uint8_t kDreqRx = 0;
};

template<PioId Pio, std::uint8_t Sm>
struct StateMachineSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint8_t kDreqTx = 0;
  static constexpr std::uint8_t kDreqRx = 0;
};

inline constexpr std::array<PioId, 0> kPioSemanticPeripherals = {};
}
}
}
}
}
}
}
