#pragma once

#include <array>
#include <cstdint>
#include "system_clock.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g071rb {
using ClockProfileId = SystemClockProfileId;
using ClockProfileKindId = SystemClockProfileKindId;
using ClockProfileSourceKindId = SystemClockSourceKindId;
using ClockProfileDescriptor = SystemClockProfileDescriptor;

template<ClockProfileId Id>
using ClockProfileTraits = SystemClockProfileTraits<Id>;

inline constexpr std::array<ClockProfileId, 2> kClockProfileIds = {{
  ClockProfileId::default_pll_64mhz,
  ClockProfileId::safe_hsi16,
}};

inline constexpr auto kClockProfiles = kSystemClockProfiles;
inline constexpr ClockProfileId kDefaultClockProfileId = ClockProfileId::safe_hsi16;
inline constexpr ClockProfileId kSafeClockProfileId = ClockProfileId::none;
inline constexpr ClockProfileId kMaxClockProfileId = ClockProfileId::default_pll_64mhz;
inline constexpr std::uint32_t kMaxClockFrequencyHz = 64000000u;
}
}
}
}
}
}
