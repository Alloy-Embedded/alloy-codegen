#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g0b1re {
enum class PinId : std::uint16_t {
  none,
  PA0,
  PA11,
  PA12,
  PA8,
  PB8,
  PB9,
};

template<PinId Id>
struct PinTraits {
  static constexpr bool kPresent = false;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = -1;
};

template<>
struct PinTraits<PinId::PA0> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 0;
};

template<>
struct PinTraits<PinId::PA11> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 11;
};

template<>
struct PinTraits<PinId::PA12> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 12;
};

template<>
struct PinTraits<PinId::PA8> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 8;
};

template<>
struct PinTraits<PinId::PB8> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_B;
  static constexpr int kPinNumber = 8;
};

template<>
struct PinTraits<PinId::PB9> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_B;
  static constexpr int kPinNumber = 9;
};

inline constexpr std::array<PinId, 6> kPins = {{
  PinId::PA0,
  PinId::PA11,
  PinId::PA12,
  PinId::PA8,
  PinId::PB8,
  PinId::PB9,
}};
}
}
}
}
}
}
