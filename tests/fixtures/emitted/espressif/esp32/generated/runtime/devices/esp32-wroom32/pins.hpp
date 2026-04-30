#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace espressif {
namespace esp32 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32_wroom32 {
enum class PinId : std::uint16_t {
  none,
  GPIO1,
  GPIO3,
};

template<PinId Id>
struct PinTraits {
  static constexpr bool kPresent = false;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = -1;
};

template<>
struct PinTraits<PinId::GPIO1> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 1;
};

template<>
struct PinTraits<PinId::GPIO3> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 3;
};

inline constexpr std::array<PinId, 2> kPins = {{
  PinId::GPIO1,
  PinId::GPIO3,
}};
}
}
}
}
}
}
