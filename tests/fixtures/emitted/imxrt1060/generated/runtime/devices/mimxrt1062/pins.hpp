#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
enum class PinId : std::uint16_t {
  none,
  GPIO_AD_B0_00,
  GPIO_AD_B0_01,
  GPIO_EMC_00,
  GPIO_EMC_01,
};

template<PinId Id>
struct PinTraits {
  static constexpr bool kPresent = false;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = -1;
};

template<>
struct PinTraits<PinId::GPIO_AD_B0_00> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 0;
};

template<>
struct PinTraits<PinId::GPIO_AD_B0_01> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 1;
};

template<>
struct PinTraits<PinId::GPIO_EMC_00> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 0;
};

template<>
struct PinTraits<PinId::GPIO_EMC_01> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 1;
};

inline constexpr std::array<PinId, 4> kPins = {{
  PinId::GPIO_AD_B0_00,
  PinId::GPIO_AD_B0_01,
  PinId::GPIO_EMC_00,
  PinId::GPIO_EMC_01,
}};
}
}
}
}
}
}
