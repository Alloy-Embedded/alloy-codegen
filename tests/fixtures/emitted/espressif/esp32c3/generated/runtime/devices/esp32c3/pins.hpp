#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace espressif {
namespace esp32c3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32c3 {
enum class PinId : std::uint16_t {
  none,
  GPIO10,
  GPIO2,
  GPIO20,
  GPIO21,
  GPIO4,
  GPIO5,
  GPIO6,
  GPIO7,
  GPIO8,
  GPIO9,
};

template<PinId Id>
struct PinTraits {
  static constexpr bool kPresent = false;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = -1;
};

template<>
struct PinTraits<PinId::GPIO10> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 10;
};

template<>
struct PinTraits<PinId::GPIO2> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 2;
};

template<>
struct PinTraits<PinId::GPIO20> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 20;
};

template<>
struct PinTraits<PinId::GPIO21> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 21;
};

template<>
struct PinTraits<PinId::GPIO4> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 4;
};

template<>
struct PinTraits<PinId::GPIO5> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 5;
};

template<>
struct PinTraits<PinId::GPIO6> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 6;
};

template<>
struct PinTraits<PinId::GPIO7> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 7;
};

template<>
struct PinTraits<PinId::GPIO8> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 8;
};

template<>
struct PinTraits<PinId::GPIO9> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 9;
};

inline constexpr std::array<PinId, 10> kPins = {{
  PinId::GPIO10,
  PinId::GPIO2,
  PinId::GPIO20,
  PinId::GPIO21,
  PinId::GPIO4,
  PinId::GPIO5,
  PinId::GPIO6,
  PinId::GPIO7,
  PinId::GPIO8,
  PinId::GPIO9,
}};
}
}
}
}
}
}
