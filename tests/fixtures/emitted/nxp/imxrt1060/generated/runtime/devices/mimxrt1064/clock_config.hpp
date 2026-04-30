#pragma once

#include "clock_profiles.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1064 {
template<ClockProfileId Id>
inline bool apply_clock_profile() {
  return apply_system_clock_profile<Id>();
}

inline bool apply_default_clock_profile() {
  return apply_clock_profile<ClockProfileId::default_arm_pll_600mhz>();
}

inline bool apply_safe_clock_profile() {
  return apply_clock_profile<ClockProfileId::safe_osc24m>();
}

inline bool apply_max_clock_profile() {
  return apply_clock_profile<ClockProfileId::default_arm_pll_600mhz>();
}

inline bool apply_clock_profile_default_arm_pll_600mhz() {
  return apply_clock_profile<ClockProfileId::default_arm_pll_600mhz>();
}

inline bool apply_clock_profile_safe_osc24m() {
  return apply_clock_profile<ClockProfileId::safe_osc24m>();
}

}
}
}
}
}
}
