#pragma once

#include "clock_profiles.hpp"

namespace nordic {
namespace nrf52 {
namespace generated {
namespace runtime {
namespace devices {
namespace nrf52840 {
template<ClockProfileId Id>
inline bool apply_clock_profile() {
  return apply_system_clock_profile<Id>();
}

inline bool apply_default_clock_profile() {
  return false;
}

inline bool apply_safe_clock_profile() {
  return false;
}

inline bool apply_max_clock_profile() {
  return false;
}

}
}
}
}
}
}
