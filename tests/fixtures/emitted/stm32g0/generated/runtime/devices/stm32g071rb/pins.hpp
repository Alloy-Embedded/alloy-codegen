#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g071rb {
enum class PinId : std::uint16_t {
  none,
  PA0,
  PA1,
  PA2,
  PA3,
  PA5,
  PB6,
  PB7,
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
struct PinTraits<PinId::PA1> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 1;
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
struct PinTraits<PinId::PA5> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 5;
};

template<>
struct PinTraits<PinId::PB6> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_B;
  static constexpr int kPinNumber = 6;
};

template<>
struct PinTraits<PinId::PB7> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_B;
  static constexpr int kPinNumber = 7;
};

inline constexpr std::array<PinId, 7> kPins = {{
  PinId::PA0,
  PinId::PA1,
  PinId::PA2,
  PinId::PA3,
  PinId::PA5,
  PinId::PB6,
  PinId::PB7,
}};
}
}
}
}
}
}
