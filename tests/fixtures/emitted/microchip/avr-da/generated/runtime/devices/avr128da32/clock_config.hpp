#pragma once

#include "clock_profiles.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
template<ClockProfileId Id>
inline bool apply_clock_profile() {
  return apply_system_clock_profile<Id>();
}

inline bool apply_default_clock_profile() {
  return apply_clock_profile<ClockProfileId::default_osc20m_24mhz>();
}

inline bool apply_safe_clock_profile() {
  return apply_clock_profile<ClockProfileId::safe_osc20m_20mhz>();
}

inline bool apply_max_clock_profile() {
  return apply_clock_profile<ClockProfileId::default_osc20m_24mhz>();
}

inline bool apply_clock_profile_default_osc20m_24mhz() {
  return apply_clock_profile<ClockProfileId::default_osc20m_24mhz>();
}

inline bool apply_clock_profile_safe_osc20m_20mhz() {
  return apply_clock_profile<ClockProfileId::safe_osc20m_20mhz>();
}

}
}
}
}
}
}
