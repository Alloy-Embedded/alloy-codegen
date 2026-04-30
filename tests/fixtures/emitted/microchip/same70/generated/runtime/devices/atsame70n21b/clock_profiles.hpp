#pragma once

#include <array>
#include <cstdint>
#include "system_clock.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70n21b {
using ClockProfileId = SystemClockProfileId;
using ClockProfileKindId = SystemClockProfileKindId;
using ClockProfileSourceKindId = SystemClockSourceKindId;
using ClockProfileDescriptor = SystemClockProfileDescriptor;

template<ClockProfileId Id>
using ClockProfileTraits = SystemClockProfileTraits<Id>;

inline constexpr std::array<ClockProfileId, 4> kClockProfileIds = {{
  ClockProfileId::crystal_12mhz,
  ClockProfileId::default_safe_internal_12mhz,
  ClockProfileId::plla_150mhz,
  ClockProfileId::safe_internal_12mhz,
}};

inline constexpr auto kClockProfiles = kSystemClockProfiles;
inline constexpr ClockProfileId kDefaultClockProfileId = ClockProfileId::default_safe_internal_12mhz;
inline constexpr ClockProfileId kSafeClockProfileId = ClockProfileId::safe_internal_12mhz;
inline constexpr ClockProfileId kMaxClockProfileId = ClockProfileId::plla_150mhz;
inline constexpr std::uint32_t kMaxClockFrequencyHz = 150000000u;
}
}
}
}
}
}
