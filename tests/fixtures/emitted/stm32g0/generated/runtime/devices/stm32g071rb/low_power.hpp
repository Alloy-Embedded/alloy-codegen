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
enum class LowPowerModeId : std::uint16_t {
  none,
  sleep,
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

inline constexpr std::array<LowPowerModeDescriptor, 1> kLowPowerModes = {{
  {LowPowerModeId::sleep, false},
}};

enum class WakeupTagId : std::uint16_t {
  none,
};

enum class WakeupSourceId : std::uint16_t {
  none,
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

inline constexpr std::array<WakeupSourceDescriptor, 0> kWakeupSources = {};
}
}
}
}
}
}
