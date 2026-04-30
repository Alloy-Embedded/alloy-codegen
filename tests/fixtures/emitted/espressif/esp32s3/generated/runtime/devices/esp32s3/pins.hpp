#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace espressif {
namespace esp32s3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32s3 {
enum class PinId : std::uint16_t {
  none,
  GPIO11,
  GPIO12,
  GPIO13,
  GPIO14,
  GPIO17,
  GPIO18,
  GPIO43,
  GPIO44,
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
struct PinTraits<PinId::GPIO11> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 11;
};

template<>
struct PinTraits<PinId::GPIO12> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 12;
};

template<>
struct PinTraits<PinId::GPIO13> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 13;
};

template<>
struct PinTraits<PinId::GPIO14> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 14;
};

template<>
struct PinTraits<PinId::GPIO17> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 17;
};

template<>
struct PinTraits<PinId::GPIO18> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 18;
};

template<>
struct PinTraits<PinId::GPIO43> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 43;
};

template<>
struct PinTraits<PinId::GPIO44> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 44;
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
  PinId::GPIO11,
  PinId::GPIO12,
  PinId::GPIO13,
  PinId::GPIO14,
  PinId::GPIO17,
  PinId::GPIO18,
  PinId::GPIO43,
  PinId::GPIO44,
  PinId::GPIO8,
  PinId::GPIO9,
}};
}
}
}
}
}
}
