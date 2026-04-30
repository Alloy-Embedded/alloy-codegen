#pragma once

#include <array>
#include <cstdint>
#include "system_clock.hpp"

namespace espressif {
namespace esp32c3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32c3 {
using ClockProfileId = SystemClockProfileId;
using ClockProfileKindId = SystemClockProfileKindId;
using ClockProfileSourceKindId = SystemClockSourceKindId;
using ClockProfileDescriptor = SystemClockProfileDescriptor;

template<ClockProfileId Id>
using ClockProfileTraits = SystemClockProfileTraits<Id>;

inline constexpr std::array<ClockProfileId, 2> kClockProfileIds = {{
  ClockProfileId::default_pll_160mhz,
  ClockProfileId::safe_rc_fast_8mhz,
}};

inline constexpr auto kClockProfiles = kSystemClockProfiles;
inline constexpr ClockProfileId kDefaultClockProfileId = ClockProfileId::default_pll_160mhz;
inline constexpr ClockProfileId kSafeClockProfileId = ClockProfileId::safe_rc_fast_8mhz;
inline constexpr ClockProfileId kMaxClockProfileId = ClockProfileId::default_pll_160mhz;
inline constexpr std::uint32_t kMaxClockFrequencyHz = 160000000u;
}
}
}
}
}
}
