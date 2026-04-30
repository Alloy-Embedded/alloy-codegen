#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
enum class PinId : std::uint16_t {
  none,
  PA0,
  PA1,
  PA2,
  PA3,
  PA4,
  PA5,
  PA6,
  PA7,
  PC0,
  PC1,
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
struct PinTraits<PinId::PA4> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 4;
};

template<>
struct PinTraits<PinId::PA5> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 5;
};

template<>
struct PinTraits<PinId::PA6> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 6;
};

template<>
struct PinTraits<PinId::PA7> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 7;
};

template<>
struct PinTraits<PinId::PC0> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_C;
  static constexpr int kPinNumber = 0;
};

template<>
struct PinTraits<PinId::PC1> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_C;
  static constexpr int kPinNumber = 1;
};

inline constexpr std::array<PinId, 10> kPins = {{
  PinId::PA0,
  PinId::PA1,
  PinId::PA2,
  PinId::PA3,
  PinId::PA4,
  PinId::PA5,
  PinId::PA6,
  PinId::PA7,
  PinId::PC0,
  PinId::PC1,
}};
}
}
}
}
}
}
