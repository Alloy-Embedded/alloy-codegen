#pragma once

#include "clock_profiles.hpp"

namespace espressif {
namespace esp32 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32 {
template<ClockProfileId Id>
inline bool apply_clock_profile() {
  return apply_system_clock_profile<Id>();
}

inline bool apply_default_clock_profile() {
  return apply_clock_profile<ClockProfileId::default_pll_240mhz>();
}

inline bool apply_safe_clock_profile() {
  return apply_clock_profile<ClockProfileId::safe_rc_fast_8mhz>();
}

inline bool apply_max_clock_profile() {
  return apply_clock_profile<ClockProfileId::default_pll_240mhz>();
}

inline bool apply_clock_profile_default_pll_240mhz() {
  return apply_clock_profile<ClockProfileId::default_pll_240mhz>();
}

inline bool apply_clock_profile_safe_rc_fast_8mhz() {
  return apply_clock_profile<ClockProfileId::safe_rc_fast_8mhz>();
}

}
}
}
}
}
}
