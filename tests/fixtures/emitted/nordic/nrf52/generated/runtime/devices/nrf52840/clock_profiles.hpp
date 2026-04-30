#pragma once

#include <array>
#include <cstdint>
#include "system_clock.hpp"

namespace nordic {
namespace nrf52 {
namespace generated {
namespace runtime {
namespace devices {
namespace nrf52840 {
using ClockProfileId = SystemClockProfileId;
using ClockProfileKindId = SystemClockProfileKindId;
using ClockProfileSourceKindId = SystemClockSourceKindId;
using ClockProfileDescriptor = SystemClockProfileDescriptor;

template<ClockProfileId Id>
using ClockProfileTraits = SystemClockProfileTraits<Id>;

inline constexpr std::array<ClockProfileId, 0> kClockProfileIds = {};

inline constexpr auto kClockProfiles = kSystemClockProfiles;
inline constexpr ClockProfileId kDefaultClockProfileId = ClockProfileId::none;
inline constexpr ClockProfileId kSafeClockProfileId = ClockProfileId::none;
inline constexpr ClockProfileId kMaxClockProfileId = ClockProfileId::none;
inline constexpr std::uint32_t kMaxClockFrequencyHz = 0u;
}
}
}
}
}
}
