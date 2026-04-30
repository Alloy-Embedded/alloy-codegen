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
enum class PinId : std::uint16_t {
  none,
  P0_06,
  P0_08,
  P0_19,
  P0_20,
  P0_21,
  P0_26,
  P0_27,
};

template<PinId Id>
struct PinTraits {
  static constexpr bool kPresent = false;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = -1;
};

template<>
struct PinTraits<PinId::P0_06> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_0;
  static constexpr int kPinNumber = 6;
};

template<>
struct PinTraits<PinId::P0_08> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_0;
  static constexpr int kPinNumber = 8;
};

template<>
struct PinTraits<PinId::P0_19> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_0;
  static constexpr int kPinNumber = 19;
};

template<>
struct PinTraits<PinId::P0_20> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_0;
  static constexpr int kPinNumber = 20;
};

template<>
struct PinTraits<PinId::P0_21> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_0;
  static constexpr int kPinNumber = 21;
};

template<>
struct PinTraits<PinId::P0_26> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_0;
  static constexpr int kPinNumber = 26;
};

template<>
struct PinTraits<PinId::P0_27> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_0;
  static constexpr int kPinNumber = 27;
};

inline constexpr std::array<PinId, 7> kPins = {{
  PinId::P0_06,
  PinId::P0_08,
  PinId::P0_19,
  PinId::P0_20,
  PinId::P0_21,
  PinId::P0_26,
  PinId::P0_27,
}};
}
}
}
}
}
}
