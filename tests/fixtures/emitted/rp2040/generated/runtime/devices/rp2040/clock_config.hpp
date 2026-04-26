#pragma once

#include "clock_profiles.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
template<ClockProfileId Id>
inline bool apply_clock_profile() {
  return apply_system_clock_profile<Id>();
}

inline bool apply_default_clock_profile() {
  return apply_clock_profile<ClockProfileId::default_pll_125mhz>();
}

inline bool apply_safe_clock_profile() {
  return apply_clock_profile<ClockProfileId::safe_rosc_6mhz>();
}

inline bool apply_max_clock_profile() {
  return apply_clock_profile<ClockProfileId::default_pll_125mhz>();
}

inline bool apply_clock_profile_default_pll_125mhz() {
  return apply_clock_profile<ClockProfileId::default_pll_125mhz>();
}

inline bool apply_clock_profile_safe_rosc_6mhz() {
  return apply_clock_profile<ClockProfileId::safe_rosc_6mhz>();
}

}
}
}
}
}
}
