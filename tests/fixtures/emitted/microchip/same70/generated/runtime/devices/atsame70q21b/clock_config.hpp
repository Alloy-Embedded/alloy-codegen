#pragma once

#include "clock_profiles.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70q21b {
template<ClockProfileId Id>
inline bool apply_clock_profile() {
  return apply_system_clock_profile<Id>();
}

inline bool apply_default_clock_profile() {
  return apply_clock_profile<ClockProfileId::default_safe_internal_12mhz>();
}

inline bool apply_safe_clock_profile() {
  return apply_clock_profile<ClockProfileId::safe_internal_12mhz>();
}

inline bool apply_max_clock_profile() {
  return apply_clock_profile<ClockProfileId::plla_150mhz>();
}

inline bool apply_clock_profile_crystal_12mhz() {
  return apply_clock_profile<ClockProfileId::crystal_12mhz>();
}

inline bool apply_clock_profile_default_safe_internal_12mhz() {
  return apply_clock_profile<ClockProfileId::default_safe_internal_12mhz>();
}

inline bool apply_clock_profile_plla_150mhz() {
  return apply_clock_profile<ClockProfileId::plla_150mhz>();
}

inline bool apply_clock_profile_safe_internal_12mhz() {
  return apply_clock_profile<ClockProfileId::safe_internal_12mhz>();
}

}
}
}
}
}
}
