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
enum class LowPowerModeId : std::uint16_t {
  none,
  sleep,
  deep_sleep,
};

struct LowPowerModeDescriptor {
  LowPowerModeId mode_id;
  bool uses_sleepdeep;
};

template<LowPowerModeId Id>
struct LowPowerModeTraits {
  static constexpr bool kPresent = false;
  static constexpr bool kUsesSleepdeep = false;
};

template<>
struct LowPowerModeTraits<LowPowerModeId::sleep> {
  static constexpr bool kPresent = true;
  static constexpr bool kUsesSleepdeep = false;
};

template<>
struct LowPowerModeTraits<LowPowerModeId::deep_sleep> {
  static constexpr bool kPresent = true;
  static constexpr bool kUsesSleepdeep = true;
};

inline constexpr std::array<LowPowerModeDescriptor, 2> kLowPowerModes = {{
  {LowPowerModeId::sleep, false},
  {LowPowerModeId::deep_sleep, true},
}};

enum class WakeupTagId : std::uint16_t {
  none,
  WKUP0,
  WKUP1,
  WKUP7,
  WKUP8,
  WKUP9,
  WKUP2,
  WKUP10,
  WKUP11,
  WKUP3,
  WKUP4,
  WKUP6,
  WKUP12,
  WKUP13,
  WKUP5,
};

enum class WakeupSourceId : std::uint16_t {
  none,
  PA0_WKUP0,
  PA1_WKUP1,
  PA11_WKUP7,
  PA14_WKUP8,
  PA19_WKUP9,
  PA2_WKUP2,
  PA20_WKUP10,
  PA30_WKUP11,
  PA4_WKUP3,
  PA5_WKUP4,
  PA9_WKUP6,
  PB3_WKUP12,
  PB5_WKUP13,
  PD28_WKUP5,
};

struct WakeupSourceDescriptor {
  WakeupSourceId wakeup_source_id;
  PinId pin_id;
  WakeupTagId tag_id;
};

template<WakeupSourceId Id>
struct WakeupSourceTraits {
  static constexpr bool kPresent = false;
  static constexpr PinId kPinId = PinId::none;
  static constexpr WakeupTagId kTagId = WakeupTagId::none;
};

template<PinId Pin>
struct WakeupPinTraits {
  static constexpr bool kPresent = false;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::none;
  static constexpr WakeupTagId kTagId = WakeupTagId::none;
};

template<>
struct WakeupSourceTraits<WakeupSourceId::PA0_WKUP0> {
  static constexpr bool kPresent = true;
  static constexpr PinId kPinId = PinId::PA0;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP0;
};

template<>
struct WakeupPinTraits<PinId::PA0> {
  static constexpr bool kPresent = true;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::PA0_WKUP0;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP0;
};

template<>
struct WakeupSourceTraits<WakeupSourceId::PA1_WKUP1> {
  static constexpr bool kPresent = true;
  static constexpr PinId kPinId = PinId::PA1;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP1;
};

template<>
struct WakeupPinTraits<PinId::PA1> {
  static constexpr bool kPresent = true;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::PA1_WKUP1;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP1;
};

template<>
struct WakeupSourceTraits<WakeupSourceId::PA11_WKUP7> {
  static constexpr bool kPresent = true;
  static constexpr PinId kPinId = PinId::PA11;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP7;
};

template<>
struct WakeupPinTraits<PinId::PA11> {
  static constexpr bool kPresent = true;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::PA11_WKUP7;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP7;
};

template<>
struct WakeupSourceTraits<WakeupSourceId::PA14_WKUP8> {
  static constexpr bool kPresent = true;
  static constexpr PinId kPinId = PinId::PA14;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP8;
};

template<>
struct WakeupPinTraits<PinId::PA14> {
  static constexpr bool kPresent = true;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::PA14_WKUP8;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP8;
};

template<>
struct WakeupSourceTraits<WakeupSourceId::PA19_WKUP9> {
  static constexpr bool kPresent = true;
  static constexpr PinId kPinId = PinId::PA19;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP9;
};

template<>
struct WakeupPinTraits<PinId::PA19> {
  static constexpr bool kPresent = true;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::PA19_WKUP9;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP9;
};

template<>
struct WakeupSourceTraits<WakeupSourceId::PA2_WKUP2> {
  static constexpr bool kPresent = true;
  static constexpr PinId kPinId = PinId::PA2;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP2;
};

template<>
struct WakeupPinTraits<PinId::PA2> {
  static constexpr bool kPresent = true;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::PA2_WKUP2;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP2;
};

template<>
struct WakeupSourceTraits<WakeupSourceId::PA20_WKUP10> {
  static constexpr bool kPresent = true;
  static constexpr PinId kPinId = PinId::PA20;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP10;
};

template<>
struct WakeupPinTraits<PinId::PA20> {
  static constexpr bool kPresent = true;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::PA20_WKUP10;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP10;
};

template<>
struct WakeupSourceTraits<WakeupSourceId::PA30_WKUP11> {
  static constexpr bool kPresent = true;
  static constexpr PinId kPinId = PinId::PA30;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP11;
};

template<>
struct WakeupPinTraits<PinId::PA30> {
  static constexpr bool kPresent = true;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::PA30_WKUP11;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP11;
};

template<>
struct WakeupSourceTraits<WakeupSourceId::PA4_WKUP3> {
  static constexpr bool kPresent = true;
  static constexpr PinId kPinId = PinId::PA4;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP3;
};

template<>
struct WakeupPinTraits<PinId::PA4> {
  static constexpr bool kPresent = true;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::PA4_WKUP3;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP3;
};

template<>
struct WakeupSourceTraits<WakeupSourceId::PA5_WKUP4> {
  static constexpr bool kPresent = true;
  static constexpr PinId kPinId = PinId::PA5;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP4;
};

template<>
struct WakeupPinTraits<PinId::PA5> {
  static constexpr bool kPresent = true;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::PA5_WKUP4;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP4;
};

template<>
struct WakeupSourceTraits<WakeupSourceId::PA9_WKUP6> {
  static constexpr bool kPresent = true;
  static constexpr PinId kPinId = PinId::PA9;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP6;
};

template<>
struct WakeupPinTraits<PinId::PA9> {
  static constexpr bool kPresent = true;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::PA9_WKUP6;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP6;
};

template<>
struct WakeupSourceTraits<WakeupSourceId::PB3_WKUP12> {
  static constexpr bool kPresent = true;
  static constexpr PinId kPinId = PinId::PB3;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP12;
};

template<>
struct WakeupPinTraits<PinId::PB3> {
  static constexpr bool kPresent = true;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::PB3_WKUP12;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP12;
};

template<>
struct WakeupSourceTraits<WakeupSourceId::PB5_WKUP13> {
  static constexpr bool kPresent = true;
  static constexpr PinId kPinId = PinId::PB5;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP13;
};

template<>
struct WakeupPinTraits<PinId::PB5> {
  static constexpr bool kPresent = true;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::PB5_WKUP13;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP13;
};

template<>
struct WakeupSourceTraits<WakeupSourceId::PD28_WKUP5> {
  static constexpr bool kPresent = true;
  static constexpr PinId kPinId = PinId::PD28;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP5;
};

template<>
struct WakeupPinTraits<PinId::PD28> {
  static constexpr bool kPresent = true;
  static constexpr WakeupSourceId kWakeupSourceId = WakeupSourceId::PD28_WKUP5;
  static constexpr WakeupTagId kTagId = WakeupTagId::WKUP5;
};

inline constexpr std::array<WakeupSourceDescriptor, 14> kWakeupSources = {{
  {WakeupSourceId::PA0_WKUP0, PinId::PA0, WakeupTagId::WKUP0},
  {WakeupSourceId::PA1_WKUP1, PinId::PA1, WakeupTagId::WKUP1},
  {WakeupSourceId::PA11_WKUP7, PinId::PA11, WakeupTagId::WKUP7},
  {WakeupSourceId::PA14_WKUP8, PinId::PA14, WakeupTagId::WKUP8},
  {WakeupSourceId::PA19_WKUP9, PinId::PA19, WakeupTagId::WKUP9},
  {WakeupSourceId::PA2_WKUP2, PinId::PA2, WakeupTagId::WKUP2},
  {WakeupSourceId::PA20_WKUP10, PinId::PA20, WakeupTagId::WKUP10},
  {WakeupSourceId::PA30_WKUP11, PinId::PA30, WakeupTagId::WKUP11},
  {WakeupSourceId::PA4_WKUP3, PinId::PA4, WakeupTagId::WKUP3},
  {WakeupSourceId::PA5_WKUP4, PinId::PA5, WakeupTagId::WKUP4},
  {WakeupSourceId::PA9_WKUP6, PinId::PA9, WakeupTagId::WKUP6},
  {WakeupSourceId::PB3_WKUP12, PinId::PB3, WakeupTagId::WKUP12},
  {WakeupSourceId::PB5_WKUP13, PinId::PB5, WakeupTagId::WKUP13},
  {WakeupSourceId::PD28_WKUP5, PinId::PD28, WakeupTagId::WKUP5},
}};
}
}
}
}
}
}
