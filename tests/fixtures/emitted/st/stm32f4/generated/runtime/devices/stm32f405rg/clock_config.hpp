#pragma once

#include "clock_profiles.hpp"

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f405rg {
template<ClockProfileId Id>
inline bool apply_clock_profile() {
  return apply_system_clock_profile<Id>();
}

inline bool apply_default_clock_profile() {
  return apply_clock_profile<ClockProfileId::default_hse_pll_84mhz>();
}

inline bool apply_safe_clock_profile() {
  return apply_clock_profile<ClockProfileId::safe_reset_default>();
}

inline bool apply_max_clock_profile() {
  return apply_clock_profile<ClockProfileId::default_hse_pll_84mhz>();
}

inline bool apply_clock_profile_default_hse_pll_84mhz() {
  return apply_clock_profile<ClockProfileId::default_hse_pll_84mhz>();
}

inline bool apply_clock_profile_safe_reset_default() {
  return apply_clock_profile<ClockProfileId::safe_reset_default>();
}

}
}
}
}
}
}
