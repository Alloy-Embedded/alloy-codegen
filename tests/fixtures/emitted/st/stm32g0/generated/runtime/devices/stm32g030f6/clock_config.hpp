#pragma once

#include "clock_profiles.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g030f6 {
template<ClockProfileId Id>
inline bool apply_clock_profile() {
  return apply_system_clock_profile<Id>();
}

inline bool apply_default_clock_profile() {
  return apply_clock_profile<ClockProfileId::default_pll_64mhz>();
}

inline bool apply_safe_clock_profile() {
  return apply_clock_profile<ClockProfileId::safe_hsi16>();
}

inline bool apply_max_clock_profile() {
  return apply_clock_profile<ClockProfileId::default_pll_64mhz>();
}

inline bool apply_clock_profile_default_pll_64mhz() {
  return apply_clock_profile<ClockProfileId::default_pll_64mhz>();
}

inline bool apply_clock_profile_safe_hsi16() {
  return apply_clock_profile<ClockProfileId::safe_hsi16>();
}

}
}
}
}
}
}
