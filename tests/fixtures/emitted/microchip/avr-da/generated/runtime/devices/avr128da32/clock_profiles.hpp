#pragma once

#include <array>
#include <cstdint>
#include "system_clock.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
using ClockProfileId = SystemClockProfileId;
using ClockProfileKindId = SystemClockProfileKindId;
using ClockProfileSourceKindId = SystemClockSourceKindId;
using ClockProfileDescriptor = SystemClockProfileDescriptor;

template<ClockProfileId Id>
using ClockProfileTraits = SystemClockProfileTraits<Id>;

inline constexpr std::array<ClockProfileId, 2> kClockProfileIds = {{
  ClockProfileId::default_osc20m_24mhz,
  ClockProfileId::safe_osc20m_20mhz,
}};

inline constexpr auto kClockProfiles = kSystemClockProfiles;
inline constexpr ClockProfileId kDefaultClockProfileId = ClockProfileId::default_osc20m_24mhz;
inline constexpr ClockProfileId kSafeClockProfileId = ClockProfileId::safe_osc20m_20mhz;
inline constexpr ClockProfileId kMaxClockProfileId = ClockProfileId::default_osc20m_24mhz;
inline constexpr std::uint32_t kMaxClockFrequencyHz = 24000000u;
}
}
}
}
}
}
