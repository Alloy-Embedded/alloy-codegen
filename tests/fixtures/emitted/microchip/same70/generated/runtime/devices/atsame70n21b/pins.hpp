#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70n21b {
enum class PinId : std::uint16_t {
  none,
  PA0,
  PA1,
  PA10,
  PA11,
  PA12,
  PA13,
  PA14,
  PA15,
  PA16,
  PA17,
  PA18,
  PA19,
  PA2,
  PA20,
  PA21,
  PA22,
  PA23,
  PA24,
  PA25,
  PA26,
  PA27,
  PA28,
  PA3,
  PA30,
  PA31,
  PA4,
  PA5,
  PA7,
  PA8,
  PA9,
  PB0,
  PB1,
  PB12,
  PB13,
  PB2,
  PB3,
  PB4,
  PB5,
  PB6,
  PB7,
  PB8,
  PB9,
  PD0,
  PD1,
  PD10,
  PD11,
  PD12,
  PD13,
  PD14,
  PD15,
  PD16,
  PD17,
  PD18,
  PD19,
  PD2,
  PD20,
  PD21,
  PD22,
  PD24,
  PD25,
  PD26,
  PD27,
  PD28,
  PD3,
  PD30,
  PD31,
  PD4,
  PD5,
  PD6,
  PD7,
  PD8,
  PD9,
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
struct PinTraits<PinId::PA10> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 10;
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
struct PinTraits<PinId::PA13> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 13;
};

template<>
struct PinTraits<PinId::PA14> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 14;
};

template<>
struct PinTraits<PinId::PA15> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 15;
};

template<>
struct PinTraits<PinId::PA16> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 16;
};

template<>
struct PinTraits<PinId::PA17> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 17;
};

template<>
struct PinTraits<PinId::PA18> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 18;
};

template<>
struct PinTraits<PinId::PA19> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 19;
};

template<>
struct PinTraits<PinId::PA2> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 2;
};

template<>
struct PinTraits<PinId::PA20> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 20;
};

template<>
struct PinTraits<PinId::PA21> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 21;
};

template<>
struct PinTraits<PinId::PA22> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 22;
};

template<>
struct PinTraits<PinId::PA23> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 23;
};

template<>
struct PinTraits<PinId::PA24> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 24;
};

template<>
struct PinTraits<PinId::PA25> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 25;
};

template<>
struct PinTraits<PinId::PA26> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 26;
};

template<>
struct PinTraits<PinId::PA27> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 27;
};

template<>
struct PinTraits<PinId::PA28> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 28;
};

template<>
struct PinTraits<PinId::PA3> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 3;
};

template<>
struct PinTraits<PinId::PA30> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 30;
};

template<>
struct PinTraits<PinId::PA31> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 31;
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
struct PinTraits<PinId::PA7> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 7;
};

template<>
struct PinTraits<PinId::PA8> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 8;
};

template<>
struct PinTraits<PinId::PA9> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_A;
  static constexpr int kPinNumber = 9;
};

template<>
struct PinTraits<PinId::PB0> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_B;
  static constexpr int kPinNumber = 0;
};

template<>
struct PinTraits<PinId::PB1> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_B;
  static constexpr int kPinNumber = 1;
};

template<>
struct PinTraits<PinId::PB12> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_B;
  static constexpr int kPinNumber = 12;
};

template<>
struct PinTraits<PinId::PB13> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_B;
  static constexpr int kPinNumber = 13;
};

template<>
struct PinTraits<PinId::PB2> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_B;
  static constexpr int kPinNumber = 2;
};

template<>
struct PinTraits<PinId::PB3> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_B;
  static constexpr int kPinNumber = 3;
};

template<>
struct PinTraits<PinId::PB4> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_B;
  static constexpr int kPinNumber = 4;
};

template<>
struct PinTraits<PinId::PB5> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_B;
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

template<>
struct PinTraits<PinId::PD0> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 0;
};

template<>
struct PinTraits<PinId::PD1> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 1;
};

template<>
struct PinTraits<PinId::PD10> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 10;
};

template<>
struct PinTraits<PinId::PD11> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 11;
};

template<>
struct PinTraits<PinId::PD12> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 12;
};

template<>
struct PinTraits<PinId::PD13> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 13;
};

template<>
struct PinTraits<PinId::PD14> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 14;
};

template<>
struct PinTraits<PinId::PD15> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 15;
};

template<>
struct PinTraits<PinId::PD16> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 16;
};

template<>
struct PinTraits<PinId::PD17> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 17;
};

template<>
struct PinTraits<PinId::PD18> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 18;
};

template<>
struct PinTraits<PinId::PD19> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 19;
};

template<>
struct PinTraits<PinId::PD2> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 2;
};

template<>
struct PinTraits<PinId::PD20> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 20;
};

template<>
struct PinTraits<PinId::PD21> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 21;
};

template<>
struct PinTraits<PinId::PD22> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 22;
};

template<>
struct PinTraits<PinId::PD24> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 24;
};

template<>
struct PinTraits<PinId::PD25> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 25;
};

template<>
struct PinTraits<PinId::PD26> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 26;
};

template<>
struct PinTraits<PinId::PD27> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 27;
};

template<>
struct PinTraits<PinId::PD28> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 28;
};

template<>
struct PinTraits<PinId::PD3> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 3;
};

template<>
struct PinTraits<PinId::PD30> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 30;
};

template<>
struct PinTraits<PinId::PD31> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 31;
};

template<>
struct PinTraits<PinId::PD4> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 4;
};

template<>
struct PinTraits<PinId::PD5> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 5;
};

template<>
struct PinTraits<PinId::PD6> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 6;
};

template<>
struct PinTraits<PinId::PD7> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 7;
};

template<>
struct PinTraits<PinId::PD8> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 8;
};

template<>
struct PinTraits<PinId::PD9> {
  static constexpr bool kPresent = true;
  static constexpr PortId kPortId = PortId::port_D;
  static constexpr int kPinNumber = 9;
};

inline constexpr std::array<PinId, 72> kPins = {{
  PinId::PA0,
  PinId::PA1,
  PinId::PA10,
  PinId::PA11,
  PinId::PA12,
  PinId::PA13,
  PinId::PA14,
  PinId::PA15,
  PinId::PA16,
  PinId::PA17,
  PinId::PA18,
  PinId::PA19,
  PinId::PA2,
  PinId::PA20,
  PinId::PA21,
  PinId::PA22,
  PinId::PA23,
  PinId::PA24,
  PinId::PA25,
  PinId::PA26,
  PinId::PA27,
  PinId::PA28,
  PinId::PA3,
  PinId::PA30,
  PinId::PA31,
  PinId::PA4,
  PinId::PA5,
  PinId::PA7,
  PinId::PA8,
  PinId::PA9,
  PinId::PB0,
  PinId::PB1,
  PinId::PB12,
  PinId::PB13,
  PinId::PB2,
  PinId::PB3,
  PinId::PB4,
  PinId::PB5,
  PinId::PB6,
  PinId::PB7,
  PinId::PB8,
  PinId::PB9,
  PinId::PD0,
  PinId::PD1,
  PinId::PD10,
  PinId::PD11,
  PinId::PD12,
  PinId::PD13,
  PinId::PD14,
  PinId::PD15,
  PinId::PD16,
  PinId::PD17,
  PinId::PD18,
  PinId::PD19,
  PinId::PD2,
  PinId::PD20,
  PinId::PD21,
  PinId::PD22,
  PinId::PD24,
  PinId::PD25,
  PinId::PD26,
  PinId::PD27,
  PinId::PD28,
  PinId::PD3,
  PinId::PD30,
  PinId::PD31,
  PinId::PD4,
  PinId::PD5,
  PinId::PD6,
  PinId::PD7,
  PinId::PD8,
  PinId::PD9,
}};
}
}
}
}
}
}
