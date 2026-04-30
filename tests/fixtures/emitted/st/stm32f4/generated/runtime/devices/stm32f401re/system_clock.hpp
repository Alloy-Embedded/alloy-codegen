#pragma once

#include <array>
#include <cstdint>
#include "driver_semantics/common.hpp"

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f401re {
enum class SystemClockProfileId : std::uint16_t {
  none,
  default_hse_pll_84mhz,
  safe_reset_default,
};

enum class SystemClockProfileKindId : std::uint16_t {
  none,
  default_value,
  safe,
};

enum class SystemClockSourceKindId : std::uint16_t {
  none,
  pll_external,
  reset_default,
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
  {SystemClockProfileId::default_hse_pll_84mhz, SystemClockProfileKindId::default_value, SystemClockSourceKindId::pll_external, 84000000u, 84000000u, 42000000u, 84000000u, 0u},
  {SystemClockProfileId::safe_reset_default, SystemClockProfileKindId::safe, SystemClockSourceKindId::reset_default, 16000000u, 16000000u, 16000000u, 16000000u, 0u},
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
struct SystemClockProfileTraits<SystemClockProfileId::default_hse_pll_84mhz> {
  static constexpr bool kPresent = true;
  static constexpr SystemClockProfileKindId kKindId = SystemClockProfileKindId::default_value;
  static constexpr SystemClockSourceKindId kSourceKindId = SystemClockSourceKindId::pll_external;
  static constexpr std::uint32_t kSysclkHz = 84000000u;
  static constexpr std::uint32_t kHclkHz = 84000000u;
  static constexpr std::uint32_t kApb1Hz = 42000000u;
  static constexpr std::uint32_t kApb2Hz = 84000000u;
  static constexpr std::uint32_t kPclkHz = 0u;
  static constexpr std::uint32_t kSourceHz = 8000000u;
  static constexpr std::uint32_t kAhbPrescaler = 1u;
  static constexpr std::uint32_t kApb1Prescaler = 2u;
  static constexpr std::uint32_t kApb2Prescaler = 1u;
  static constexpr std::uint32_t kOscillatorStartupCycles = 0u;
  static constexpr std::uint32_t kMckPrescaler = 1u;
  static constexpr std::uint32_t kCpuPrescaler = 1u;
  static constexpr std::uint32_t kIpgPrescaler = 1u;
  static constexpr std::uint32_t kPllM = 4u;
  static constexpr std::uint32_t kPllN = 168u;
  static constexpr std::uint32_t kPllP = 4u;
  static constexpr std::uint32_t kPllQ = 7u;
  static constexpr std::uint32_t kPllR = 0u;
  static constexpr std::uint32_t kFlashLatency = 2u;
};

template<>
struct SystemClockProfileTraits<SystemClockProfileId::safe_reset_default> {
  static constexpr bool kPresent = true;
  static constexpr SystemClockProfileKindId kKindId = SystemClockProfileKindId::safe;
  static constexpr SystemClockSourceKindId kSourceKindId = SystemClockSourceKindId::reset_default;
  static constexpr std::uint32_t kSysclkHz = 16000000u;
  static constexpr std::uint32_t kHclkHz = 16000000u;
  static constexpr std::uint32_t kApb1Hz = 16000000u;
  static constexpr std::uint32_t kApb2Hz = 16000000u;
  static constexpr std::uint32_t kPclkHz = 0u;
  static constexpr std::uint32_t kSourceHz = 16000000u;
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

inline constexpr auto kRccCrRegister = RuntimeRegisterRef{RegisterId::register_rcc_cr, 0x40023800u, 0u, true};
inline constexpr auto kRccPllcfgrRegister = RuntimeRegisterRef{RegisterId::register_rcc_pllcfgr, 0x40023800u, 4u, true};
inline constexpr auto kRccCfgrRegister = RuntimeRegisterRef{RegisterId::register_rcc_cfgr, 0x40023800u, 8u, true};
inline constexpr auto kFlashAcrRegister = RuntimeRegisterRef{RegisterId::register_flash_acr, 0x40023C00u, 0u, true};
inline constexpr auto kHseonField = RuntimeFieldRef{FieldId::field_rcc_cr_hseon, RuntimeRegisterRef{RegisterId::register_rcc_cr, 0x40023800u, 0u, true}, 16u, 1u, true};
inline constexpr auto kHserdyField = RuntimeFieldRef{FieldId::field_rcc_cr_hserdy, RuntimeRegisterRef{RegisterId::register_rcc_cr, 0x40023800u, 0u, true}, 17u, 1u, true};
inline constexpr auto kPllonField = RuntimeFieldRef{FieldId::field_rcc_cr_pllon, RuntimeRegisterRef{RegisterId::register_rcc_cr, 0x40023800u, 0u, true}, 24u, 1u, true};
inline constexpr auto kPllrdyField = RuntimeFieldRef{FieldId::field_rcc_cr_pllrdy, RuntimeRegisterRef{RegisterId::register_rcc_cr, 0x40023800u, 0u, true}, 25u, 1u, true};
inline constexpr auto kPllmField = RuntimeFieldRef{FieldId::field_rcc_pllcfgr_pllm, RuntimeRegisterRef{RegisterId::register_rcc_pllcfgr, 0x40023800u, 4u, true}, 0u, 6u, true};
inline constexpr auto kPllnField = RuntimeFieldRef{FieldId::field_rcc_pllcfgr_plln, RuntimeRegisterRef{RegisterId::register_rcc_pllcfgr, 0x40023800u, 4u, true}, 6u, 9u, true};
inline constexpr auto kPllpField = RuntimeFieldRef{FieldId::field_rcc_pllcfgr_pllp, RuntimeRegisterRef{RegisterId::register_rcc_pllcfgr, 0x40023800u, 4u, true}, 16u, 2u, true};
inline constexpr auto kPllsrcField = RuntimeFieldRef{FieldId::field_rcc_pllcfgr_pllsrc, RuntimeRegisterRef{RegisterId::register_rcc_pllcfgr, 0x40023800u, 4u, true}, 22u, 1u, true};
inline constexpr auto kPllqField = RuntimeFieldRef{FieldId::field_rcc_pllcfgr_pllq, RuntimeRegisterRef{RegisterId::register_rcc_pllcfgr, 0x40023800u, 4u, true}, 24u, 4u, true};
inline constexpr auto kSwField = RuntimeFieldRef{FieldId::field_rcc_cfgr_sw, RuntimeRegisterRef{RegisterId::register_rcc_cfgr, 0x40023800u, 8u, true}, 0u, 2u, true};
inline constexpr auto kSwsField = RuntimeFieldRef{FieldId::field_rcc_cfgr_sws, RuntimeRegisterRef{RegisterId::register_rcc_cfgr, 0x40023800u, 8u, true}, 2u, 2u, true};
inline constexpr auto kHpreField = RuntimeFieldRef{FieldId::field_rcc_cfgr_hpre, RuntimeRegisterRef{RegisterId::register_rcc_cfgr, 0x40023800u, 8u, true}, 4u, 4u, true};
inline constexpr auto kPpre1Field = RuntimeFieldRef{FieldId::field_rcc_cfgr_ppre1, RuntimeRegisterRef{RegisterId::register_rcc_cfgr, 0x40023800u, 8u, true}, 10u, 3u, true};
inline constexpr auto kPpre2Field = RuntimeFieldRef{FieldId::field_rcc_cfgr_ppre2, RuntimeRegisterRef{RegisterId::register_rcc_cfgr, 0x40023800u, 8u, true}, 13u, 3u, true};
inline constexpr auto kFlashLatencyField = RuntimeFieldRef{FieldId::field_flash_acr_latency, RuntimeRegisterRef{RegisterId::register_flash_acr, 0x40023C00u, 0u, true}, 0u, 4u, true};

inline constexpr std::uint32_t encode_apb_prescaler(std::uint32_t divisor) {
  return divisor == 1u ? 0u : divisor == 2u ? 4u : divisor == 4u ? 5u : divisor == 8u ? 6u : 7u;
}

template<SystemClockProfileId Id>
inline bool apply_system_clock_profile() {
  if constexpr (!SystemClockProfileTraits<Id>::kPresent) {
    return false;
  } else if constexpr (Id == SystemClockProfileId::safe_reset_default) {
    return true;
  } else if constexpr (Id == SystemClockProfileId::default_hse_pll_84mhz) {
    set_field_bits(kHseonField);
    if (!wait_field_value(kHserdyField, 1u)) {
      return false;
    }
    write_field(kFlashLatencyField, SystemClockProfileTraits<Id>::kFlashLatency);
    write_field(kPllmField, SystemClockProfileTraits<Id>::kPllM);
    write_field(kPllnField, SystemClockProfileTraits<Id>::kPllN);
    write_field(kPllpField, (SystemClockProfileTraits<Id>::kPllP / 2u) - 1u);
    write_field(kPllsrcField, 1u);
    write_field(kPllqField, SystemClockProfileTraits<Id>::kPllQ);
    set_field_bits(kPllonField);
    if (!wait_field_value(kPllrdyField, 1u)) {
      return false;
    }
    write_field(kHpreField, 0u);
    write_field(kPpre1Field, encode_apb_prescaler(SystemClockProfileTraits<Id>::kApb1Prescaler));
    write_field(kPpre2Field, encode_apb_prescaler(SystemClockProfileTraits<Id>::kApb2Prescaler));
    write_field(kSwField, 0x2u);
    return wait_field_value(kSwsField, 0x2u);
  } else {
    return false;
  }
}

inline bool apply_default_system_clock() {
  return apply_system_clock_profile<SystemClockProfileId::default_hse_pll_84mhz>();
}

inline bool apply_safe_system_clock() {
  return apply_system_clock_profile<SystemClockProfileId::safe_reset_default>();
}
}
}
}
}
}
}
