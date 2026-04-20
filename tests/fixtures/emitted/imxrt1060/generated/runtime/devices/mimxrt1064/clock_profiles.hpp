#pragma once

#include <array>
#include <cstdint>
#include "system_clock.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1064 {
using ClockProfileId = SystemClockProfileId;
using ClockProfileKindId = SystemClockProfileKindId;
using ClockProfileSourceKindId = SystemClockSourceKindId;
using ClockProfileDescriptor = SystemClockProfileDescriptor;

template<ClockProfileId Id>
using ClockProfileTraits = SystemClockProfileTraits<Id>;

inline constexpr std::array<ClockProfileId, 2> kClockProfileIds = {{
  ClockProfileId::default_arm_pll_600mhz,
  ClockProfileId::safe_osc24m,
}};

inline constexpr auto kClockProfiles = kSystemClockProfiles;
inline constexpr ClockProfileId kDefaultClockProfileId = ClockProfileId::default_arm_pll_600mhz;
inline constexpr ClockProfileId kSafeClockProfileId = ClockProfileId::safe_osc24m;
inline constexpr ClockProfileId kMaxClockProfileId = ClockProfileId::default_arm_pll_600mhz;
inline constexpr std::uint32_t kMaxClockFrequencyHz = 600000000u;
}
}
}
}
}
}
