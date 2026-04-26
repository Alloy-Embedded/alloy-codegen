#pragma once

#include <array>
#include <cstdint>
#include "driver_semantics/common.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
enum class SystemClockProfileId : std::uint16_t {
  none,
  default_pll_125mhz,
  safe_rosc_6mhz,
};

enum class SystemClockProfileKindId : std::uint16_t {
  none,
  default_value,
  safe,
};

enum class SystemClockSourceKindId : std::uint16_t {
  none,
  internal_oscillator,
  pll_external,
};

struct SystemClockProfileDescriptor {
  SystemClockProfileId profile_id;
  SystemClockProfileKindId kind_id;
  SystemClockSourceKindId source_kind_id;
  std::uint32_t sysclk_hz;
  std::uint32_t hclk_hz;
  std::uint32_t apb1_hz;
  std::uint32_t apb2_hz;
  std::uint32_t pclk_hz;
};
inline constexpr std::array<SystemClockProfileDescriptor, 2> kSystemClockProfiles = {{
  {SystemClockProfileId::default_pll_125mhz, SystemClockProfileKindId::default_value, SystemClockSourceKindId::pll_external, 125000000u, 125000000u, 0u, 0u, 125000000u},
  {SystemClockProfileId::safe_rosc_6mhz, SystemClockProfileKindId::safe, SystemClockSourceKindId::internal_oscillator, 6000000u, 6000000u, 0u, 0u, 6000000u},
}};

using RuntimeRegisterRef = driver_semantics::RuntimeRegisterRef;
using RuntimeFieldRef = driver_semantics::RuntimeFieldRef;

template<SystemClockProfileId Id>
struct SystemClockProfileTraits {
  static constexpr bool kPresent = false;
  static constexpr SystemClockProfileKindId kKindId = SystemClockProfileKindId::none;
  static constexpr SystemClockSourceKindId kSourceKindId = SystemClockSourceKindId::none;
  static constexpr std::uint32_t kSysclkHz = 0u;
  static constexpr std::uint32_t kHclkHz = 0u;
  static constexpr std::uint32_t kApb1Hz = 0u;
  static constexpr std::uint32_t kApb2Hz = 0u;
  static constexpr std::uint32_t kPclkHz = 0u;
  static constexpr std::uint32_t kSourceHz = 0u;
  static constexpr std::uint32_t kAhbPrescaler = 1u;
  static constexpr std::uint32_t kApb1Prescaler = 1u;
  static constexpr std::uint32_t kApb2Prescaler = 1u;
  static constexpr std::uint32_t kOscillatorStartupCycles = 0u;
  static constexpr std::uint32_t kMckPrescaler = 1u;
  static constexpr std::uint32_t kCpuPrescaler = 1u;
  static constexpr std::uint32_t kIpgPrescaler = 1u;
  static constexpr std::uint32_t kPllM = 0u;
  static constexpr std::uint32_t kPllN = 0u;
  static constexpr std::uint32_t kPllP = 0u;
  static constexpr std::uint32_t kPllQ = 0u;
  static constexpr std::uint32_t kPllR = 0u;
  static constexpr std::uint32_t kFlashLatency = 0u;
};

template<>
struct SystemClockProfileTraits<SystemClockProfileId::default_pll_125mhz> {
  static constexpr bool kPresent = true;
  static constexpr SystemClockProfileKindId kKindId = SystemClockProfileKindId::default_value;
  static constexpr SystemClockSourceKindId kSourceKindId = SystemClockSourceKindId::pll_external;
  static constexpr std::uint32_t kSysclkHz = 125000000u;
  static constexpr std::uint32_t kHclkHz = 125000000u;
  static constexpr std::uint32_t kApb1Hz = 0u;
  static constexpr std::uint32_t kApb2Hz = 0u;
  static constexpr std::uint32_t kPclkHz = 125000000u;
  static constexpr std::uint32_t kSourceHz = 12000000u;
  static constexpr std::uint32_t kAhbPrescaler = 1u;
  static constexpr std::uint32_t kApb1Prescaler = 1u;
  static constexpr std::uint32_t kApb2Prescaler = 1u;
  static constexpr std::uint32_t kOscillatorStartupCycles = 0u;
  static constexpr std::uint32_t kMckPrescaler = 1u;
  static constexpr std::uint32_t kCpuPrescaler = 1u;
  static constexpr std::uint32_t kIpgPrescaler = 1u;
  static constexpr std::uint32_t kPllM = 0u;
  static constexpr std::uint32_t kPllN = 125u;
  static constexpr std::uint32_t kPllP = 6u;
  static constexpr std::uint32_t kPllQ = 2u;
  static constexpr std::uint32_t kPllR = 0u;
  static constexpr std::uint32_t kFlashLatency = 0u;
};

template<>
struct SystemClockProfileTraits<SystemClockProfileId::safe_rosc_6mhz> {
  static constexpr bool kPresent = true;
  static constexpr SystemClockProfileKindId kKindId = SystemClockProfileKindId::safe;
  static constexpr SystemClockSourceKindId kSourceKindId = SystemClockSourceKindId::internal_oscillator;
  static constexpr std::uint32_t kSysclkHz = 6000000u;
  static constexpr std::uint32_t kHclkHz = 6000000u;
  static constexpr std::uint32_t kApb1Hz = 0u;
  static constexpr std::uint32_t kApb2Hz = 0u;
  static constexpr std::uint32_t kPclkHz = 6000000u;
  static constexpr std::uint32_t kSourceHz = 6000000u;
  static constexpr std::uint32_t kAhbPrescaler = 1u;
  static constexpr std::uint32_t kApb1Prescaler = 1u;
  static constexpr std::uint32_t kApb2Prescaler = 1u;
  static constexpr std::uint32_t kOscillatorStartupCycles = 0u;
  static constexpr std::uint32_t kMckPrescaler = 1u;
  static constexpr std::uint32_t kCpuPrescaler = 1u;
  static constexpr std::uint32_t kIpgPrescaler = 1u;
  static constexpr std::uint32_t kPllM = 0u;
  static constexpr std::uint32_t kPllN = 0u;
  static constexpr std::uint32_t kPllP = 0u;
  static constexpr std::uint32_t kPllQ = 0u;
  static constexpr std::uint32_t kPllR = 0u;
  static constexpr std::uint32_t kFlashLatency = 0u;
};

inline std::uint32_t read_register(driver_semantics::RuntimeRegisterRef reg) {
  return *reinterpret_cast<volatile std::uint32_t*>(reg.base_address + reg.offset_bytes);
}

inline void write_register(driver_semantics::RuntimeRegisterRef reg, std::uint32_t value) {
  *reinterpret_cast<volatile std::uint32_t*>(reg.base_address + reg.offset_bytes) = value;
}

inline std::uint32_t field_mask(driver_semantics::RuntimeFieldRef field) {
  return ((field.bit_width >= 32u ? 0xFFFF'FFFFu : ((1u << field.bit_width) - 1u)) << field.bit_offset);
}

inline std::uint32_t read_field(driver_semantics::RuntimeFieldRef field) {
  return (read_register(field.reg) & field_mask(field)) >> field.bit_offset;
}

inline void write_field(driver_semantics::RuntimeFieldRef field, std::uint32_t value) {
  const auto current = read_register(field.reg);
  const auto mask = field_mask(field);
  write_register(field.reg, (current & ~mask) | ((value << field.bit_offset) & mask));
}

inline void set_field_bits(driver_semantics::RuntimeFieldRef field) {
  write_field(field, (field.bit_width >= 32u ? 0xFFFF'FFFFu : ((1u << field.bit_width) - 1u)));
}

inline bool wait_field_value(
    driver_semantics::RuntimeFieldRef field,
    std::uint32_t expected,
    std::uint32_t timeout = 100000u) {
  while (timeout-- > 0u) {
    if (read_field(field) == expected) {
      return true;
    }
  }
  return false;
}

template<SystemClockProfileId Id>
inline bool apply_system_clock_profile() {
  return SystemClockProfileTraits<Id>::kPresent;
}

inline bool apply_default_system_clock() {
  return apply_system_clock_profile<SystemClockProfileId::default_pll_125mhz>();
}

inline bool apply_safe_system_clock() {
  return apply_system_clock_profile<SystemClockProfileId::safe_rosc_6mhz>();
}
}
}
}
}
}
}
