#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
enum class PinId : std::uint16_t {
  none,
  GP0,
  GP1,
  GP10,
  GP11,
  GP12,
  GP13,
  GP14,
  GP15,
  GP16,
  GP17,
  GP18,
  GP19,
  GP2,
  GP20,
  GP21,
  GP22,
  GP23,
  GP24,
  GP25,
  GP26,
  GP27,
  GP28,
  GP29,
  GP3,
  GP4,
  GP5,
  GP6,
  GP7,
  GP8,
  GP9,
};

template<PinId Id>
struct PinTraits {
  static constexpr bool kPresent = false;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = -1;
};

template<>
struct PinTraits<PinId::GP0> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 0;
};

template<>
struct PinTraits<PinId::GP1> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 1;
};

template<>
struct PinTraits<PinId::GP10> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 10;
};

template<>
struct PinTraits<PinId::GP11> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 11;
};

template<>
struct PinTraits<PinId::GP12> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 12;
};

template<>
struct PinTraits<PinId::GP13> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 13;
};

template<>
struct PinTraits<PinId::GP14> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 14;
};

template<>
struct PinTraits<PinId::GP15> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 15;
};

template<>
struct PinTraits<PinId::GP16> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 16;
};

template<>
struct PinTraits<PinId::GP17> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 17;
};

template<>
struct PinTraits<PinId::GP18> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 18;
};

template<>
struct PinTraits<PinId::GP19> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 19;
};

template<>
struct PinTraits<PinId::GP2> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 2;
};

template<>
struct PinTraits<PinId::GP20> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 20;
};

template<>
struct PinTraits<PinId::GP21> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 21;
};

template<>
struct PinTraits<PinId::GP22> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 22;
};

template<>
struct PinTraits<PinId::GP23> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 23;
};

template<>
struct PinTraits<PinId::GP24> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 24;
};

template<>
struct PinTraits<PinId::GP25> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 25;
};

template<>
struct PinTraits<PinId::GP26> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 26;
};

template<>
struct PinTraits<PinId::GP27> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 27;
};

template<>
struct PinTraits<PinId::GP28> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 28;
};

template<>
struct PinTraits<PinId::GP29> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 29;
};

template<>
struct PinTraits<PinId::GP3> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 3;
};

template<>
struct PinTraits<PinId::GP4> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 4;
};

template<>
struct PinTraits<PinId::GP5> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 5;
};

template<>
struct PinTraits<PinId::GP6> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 6;
};

template<>
struct PinTraits<PinId::GP7> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 7;
};

template<>
struct PinTraits<PinId::GP8> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 8;
};

template<>
struct PinTraits<PinId::GP9> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::none;
  static constexpr int kPinNumber = 9;
};

inline constexpr std::array<PinId, 30> kPins = {{
  PinId::GP0,
  PinId::GP1,
  PinId::GP10,
  PinId::GP11,
  PinId::GP12,
  PinId::GP13,
  PinId::GP14,
  PinId::GP15,
  PinId::GP16,
  PinId::GP17,
  PinId::GP18,
  PinId::GP19,
  PinId::GP2,
  PinId::GP20,
  PinId::GP21,
  PinId::GP22,
  PinId::GP23,
  PinId::GP24,
  PinId::GP25,
  PinId::GP26,
  PinId::GP27,
  PinId::GP28,
  PinId::GP29,
  PinId::GP3,
  PinId::GP4,
  PinId::GP5,
  PinId::GP6,
  PinId::GP7,
  PinId::GP8,
  PinId::GP9,
}};
}
}
}
}
}
}
