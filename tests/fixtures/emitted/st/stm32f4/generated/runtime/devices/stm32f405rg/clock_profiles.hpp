#pragma once

#include <array>
#include <cstdint>
#include "system_clock.hpp"

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f405rg {
using ClockProfileId = SystemClockProfileId;
using ClockProfileKindId = SystemClockProfileKindId;
using ClockProfileSourceKindId = SystemClockSourceKindId;
using ClockProfileDescriptor = SystemClockProfileDescriptor;

template<ClockProfileId Id>
using ClockProfileTraits = SystemClockProfileTraits<Id>;

inline constexpr std::array<ClockProfileId, 2> kClockProfileIds = {{
  ClockProfileId::default_hse_pll_84mhz,
  ClockProfileId::safe_reset_default,
}};

inline constexpr auto kClockProfiles = kSystemClockProfiles;
inline constexpr ClockProfileId kDefaultClockProfileId = ClockProfileId::default_hse_pll_84mhz;
inline constexpr ClockProfileId kSafeClockProfileId = ClockProfileId::safe_reset_default;
inline constexpr ClockProfileId kMaxClockProfileId = ClockProfileId::default_hse_pll_84mhz;
inline constexpr std::uint32_t kMaxClockFrequencyHz = 84000000u;
}
}
}
}
}
}
