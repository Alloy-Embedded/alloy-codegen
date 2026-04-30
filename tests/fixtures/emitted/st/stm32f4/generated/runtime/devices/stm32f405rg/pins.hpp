#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f405rg {
enum class PinId : std::uint16_t {
  none,
  PA10,
  PA2,
  PA3,
  PA9,
};

template<PinId Id>
struct PinTraits {
  static constexpr bool kPresent = false;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = -1;
};

template<>
struct PinTraits<PinId::PA10> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 10;
};

template<>
struct PinTraits<PinId::PA2> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 2;
};

template<>
struct PinTraits<PinId::PA3> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 3;
};

template<>
struct PinTraits<PinId::PA9> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 9;
};

inline constexpr std::array<PinId, 4> kPins = {{
  PinId::PA10,
  PinId::PA2,
  PinId::PA3,
  PinId::PA9,
}};
}
}
}
}
}
}
