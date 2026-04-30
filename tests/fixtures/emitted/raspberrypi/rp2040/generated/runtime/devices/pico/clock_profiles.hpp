#pragma once

#include <array>
#include <cstdint>
#include "system_clock.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace pico {
using ClockProfileId = SystemClockProfileId;
using ClockProfileKindId = SystemClockProfileKindId;
using ClockProfileSourceKindId = SystemClockSourceKindId;
using ClockProfileDescriptor = SystemClockProfileDescriptor;

template<ClockProfileId Id>
using ClockProfileTraits = SystemClockProfileTraits<Id>;

inline constexpr std::array<ClockProfileId, 2> kClockProfileIds = {{
  ClockProfileId::default_pll_125mhz,
  ClockProfileId::safe_rosc_6mhz,
}};

inline constexpr auto kClockProfiles = kSystemClockProfiles;
inline constexpr ClockProfileId kDefaultClockProfileId = ClockProfileId::default_pll_125mhz;
inline constexpr ClockProfileId kSafeClockProfileId = ClockProfileId::safe_rosc_6mhz;
inline constexpr ClockProfileId kMaxClockProfileId = ClockProfileId::default_pll_125mhz;
inline constexpr std::uint32_t kMaxClockFrequencyHz = 125000000u;
}
}
}
}
}
}
