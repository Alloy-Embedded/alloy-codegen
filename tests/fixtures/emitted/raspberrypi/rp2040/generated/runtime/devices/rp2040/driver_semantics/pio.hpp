#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
namespace driver_semantics {
enum class PioId : std::uint8_t {
  Pio0 = 0,
  Pio1 = 1,
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

template<>
struct PioSemanticTraits<PioId::Pio0> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kStateMachineCount = 4;
  static constexpr std::uint8_t kInstructionMemoryDepth = 32;
  static constexpr std::uint8_t kTxFifoDepth = 4;
  static constexpr std::uint8_t kRxFifoDepth = 4;
  static constexpr std::uint8_t kGpioBase = 0;
  static constexpr std::uint8_t kGpioCount = 30;
  static constexpr std::uint32_t kBaseAddress = 0x50200000u;
  static constexpr std::uint8_t kDreqTx = 0;
  static constexpr std::uint8_t kDreqRx = 4;
};

template<>
struct PioSemanticTraits<PioId::Pio1> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kStateMachineCount = 4;
  static constexpr std::uint8_t kInstructionMemoryDepth = 32;
  static constexpr std::uint8_t kTxFifoDepth = 4;
  static constexpr std::uint8_t kRxFifoDepth = 4;
  static constexpr std::uint8_t kGpioBase = 0;
  static constexpr std::uint8_t kGpioCount = 30;
  static constexpr std::uint32_t kBaseAddress = 0x50300000u;
  static constexpr std::uint8_t kDreqTx = 8;
  static constexpr std::uint8_t kDreqRx = 12;
};

template<PioId Pio, std::uint8_t Sm>
struct StateMachineSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint8_t kDreqTx = 0;
  static constexpr std::uint8_t kDreqRx = 0;
};

template<>
struct StateMachineSemanticTraits<PioId::Pio0, 0> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kDreqTx = 0;
  static constexpr std::uint8_t kDreqRx = 4;
};

template<>
struct StateMachineSemanticTraits<PioId::Pio0, 1> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kDreqTx = 1;
  static constexpr std::uint8_t kDreqRx = 5;
};

template<>
struct StateMachineSemanticTraits<PioId::Pio0, 2> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kDreqTx = 2;
  static constexpr std::uint8_t kDreqRx = 6;
};

template<>
struct StateMachineSemanticTraits<PioId::Pio0, 3> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kDreqTx = 3;
  static constexpr std::uint8_t kDreqRx = 7;
};

template<>
struct StateMachineSemanticTraits<PioId::Pio1, 0> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kDreqTx = 8;
  static constexpr std::uint8_t kDreqRx = 12;
};

template<>
struct StateMachineSemanticTraits<PioId::Pio1, 1> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kDreqTx = 9;
  static constexpr std::uint8_t kDreqRx = 13;
};

template<>
struct StateMachineSemanticTraits<PioId::Pio1, 2> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kDreqTx = 10;
  static constexpr std::uint8_t kDreqRx = 14;
};

template<>
struct StateMachineSemanticTraits<PioId::Pio1, 3> {
  static constexpr bool kPresent = true;
  static constexpr std::uint8_t kDreqTx = 11;
  static constexpr std::uint8_t kDreqRx = 15;
};

inline constexpr std::array<PioId, 2> kPioSemanticPeripherals = {{
  PioId::Pio0,
  PioId::Pio1,
}};
}
}
}
}
}
}
}
