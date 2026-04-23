#pragma once

#include <array>
#include <cstdint>
#include "driver_semantics/common.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g071rb {
enum class SystemClockProfileId : std::uint16_t {
  none,
  default_pll_64mhz,
  safe_hsi16,
};

enum class SystemClockProfileKindId : std::uint16_t {
  none,
  default_value,
  performance,
};

enum class SystemClockSourceKindId : std::uint16_t {
  none,
  internal_oscillator,
  pll_internal,
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
  {SystemClockProfileId::default_pll_64mhz, SystemClockProfileKindId::performance, SystemClockSourceKindId::pll_internal, 64000000u, 64000000u, 0u, 0u, 64000000u},
  {SystemClockProfileId::safe_hsi16, SystemClockProfileKindId::default_value, SystemClockSourceKindId::internal_oscillator, 16000000u, 16000000u, 0u, 0u, 16000000u},
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
  static constexpr std::uint32_t kPllSource = 0u;
  static constexpr std::uint32_t kFlashLatency = 0u;
};

template<>
struct SystemClockProfileTraits<SystemClockProfileId::default_pll_64mhz> {
  static constexpr bool kPresent = true;
  static constexpr SystemClockProfileKindId kKindId = SystemClockProfileKindId::performance;
  static constexpr SystemClockSourceKindId kSourceKindId = SystemClockSourceKindId::pll_internal;
  static constexpr std::uint32_t kSysclkHz = 64000000u;
  static constexpr std::uint32_t kHclkHz = 64000000u;
  static constexpr std::uint32_t kApb1Hz = 0u;
  static constexpr std::uint32_t kApb2Hz = 0u;
  static constexpr std::uint32_t kPclkHz = 64000000u;
  static constexpr std::uint32_t kSourceHz = 16000000u;
  static constexpr std::uint32_t kAhbPrescaler = 1u;
  static constexpr std::uint32_t kApb1Prescaler = 1u;
  static constexpr std::uint32_t kApb2Prescaler = 1u;
  static constexpr std::uint32_t kOscillatorStartupCycles = 0u;
  static constexpr std::uint32_t kMckPrescaler = 1u;
  static constexpr std::uint32_t kCpuPrescaler = 1u;
  static constexpr std::uint32_t kIpgPrescaler = 1u;
  static constexpr std::uint32_t kPllM = 0u;
  static constexpr std::uint32_t kPllN = 8u;
  static constexpr std::uint32_t kPllP = 0u;
  static constexpr std::uint32_t kPllQ = 0u;
  static constexpr std::uint32_t kPllR = 0u;
  static constexpr std::uint32_t kPllSource = 2u;
  static constexpr std::uint32_t kFlashLatency = 2u;
};

template<>
struct SystemClockProfileTraits<SystemClockProfileId::safe_hsi16> {
  static constexpr bool kPresent = true;
  static constexpr SystemClockProfileKindId kKindId = SystemClockProfileKindId::default_value;
  static constexpr SystemClockSourceKindId kSourceKindId = SystemClockSourceKindId::internal_oscillator;
  static constexpr std::uint32_t kSysclkHz = 16000000u;
  static constexpr std::uint32_t kHclkHz = 16000000u;
  static constexpr std::uint32_t kApb1Hz = 0u;
  static constexpr std::uint32_t kApb2Hz = 0u;
  static constexpr std::uint32_t kPclkHz = 16000000u;
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
  static constexpr std::uint32_t kPllSource = 0u;
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

inline constexpr auto kRccCrRegister = RuntimeRegisterRef{RegisterId::register_rcc_cr, 0x40021000u, 0u, true};
inline constexpr auto kRccCfgrRegister = RuntimeRegisterRef{RegisterId::register_rcc_cfgr, 0x40021000u, 8u, true};
inline constexpr auto kRccPllcfgrRegister = RuntimeRegisterRef{RegisterId::register_rcc_pllcfgr, 0x40021000u, 12u, true};
inline constexpr auto kFlashAcrRegister = RuntimeRegisterRef{RegisterId::register_flash_acr, 0x40022000u, 0u, true};
inline constexpr auto kHsionField = RuntimeFieldRef{FieldId::field_rcc_cr_hsion, RuntimeRegisterRef{RegisterId::register_rcc_cr, 0x40021000u, 0u, true}, 8u, 1u, true};
inline constexpr auto kHsirdyField = RuntimeFieldRef{FieldId::field_rcc_cr_hsirdy, RuntimeRegisterRef{RegisterId::register_rcc_cr, 0x40021000u, 0u, true}, 10u, 1u, true};
inline constexpr auto kPllonField = RuntimeFieldRef{FieldId::field_rcc_cr_pllon, RuntimeRegisterRef{RegisterId::register_rcc_cr, 0x40021000u, 0u, true}, 24u, 1u, true};
inline constexpr auto kPllrdyField = RuntimeFieldRef{FieldId::field_rcc_cr_pllrdy, RuntimeRegisterRef{RegisterId::register_rcc_cr, 0x40021000u, 0u, true}, 25u, 1u, true};
inline constexpr auto kSwField = RuntimeFieldRef{FieldId::field_rcc_cfgr_sw, RuntimeRegisterRef{RegisterId::register_rcc_cfgr, 0x40021000u, 8u, true}, 0u, 3u, true};
inline constexpr auto kSwsField = RuntimeFieldRef{FieldId::field_rcc_cfgr_sws, RuntimeRegisterRef{RegisterId::register_rcc_cfgr, 0x40021000u, 8u, true}, 3u, 3u, true};
inline constexpr auto kPllsrcField = RuntimeFieldRef{FieldId::field_rcc_pllcfgr_pllsrc, RuntimeRegisterRef{RegisterId::register_rcc_pllcfgr, 0x40021000u, 12u, true}, 0u, 2u, true};
inline constexpr auto kPllmField = RuntimeFieldRef{FieldId::field_rcc_pllcfgr_pllm, RuntimeRegisterRef{RegisterId::register_rcc_pllcfgr, 0x40021000u, 12u, true}, 4u, 3u, true};
inline constexpr auto kPllnField = RuntimeFieldRef{FieldId::field_rcc_pllcfgr_plln, RuntimeRegisterRef{RegisterId::register_rcc_pllcfgr, 0x40021000u, 12u, true}, 8u, 7u, true};
inline constexpr auto kPllrenField = RuntimeFieldRef{FieldId::field_rcc_pllcfgr_pllren, RuntimeRegisterRef{RegisterId::register_rcc_pllcfgr, 0x40021000u, 12u, true}, 24u, 1u, true};
inline constexpr auto kPllrField = RuntimeFieldRef{FieldId::field_rcc_pllcfgr_pllr, RuntimeRegisterRef{RegisterId::register_rcc_pllcfgr, 0x40021000u, 12u, true}, 25u, 2u, true};
inline constexpr auto kFlashLatencyField = RuntimeFieldRef{FieldId::field_flash_acr_latency, RuntimeRegisterRef{RegisterId::register_flash_acr, 0x40022000u, 0u, true}, 0u, 3u, true};

template<SystemClockProfileId Id>
inline bool apply_system_clock_profile() {
  if constexpr (!SystemClockProfileTraits<Id>::kPresent) {
    return false;
  } else if constexpr (Id == SystemClockProfileId::safe_hsi16) {
    set_field_bits(kHsionField);
    return wait_field_value(kHsirdyField, 1u);
  } else if constexpr (Id == SystemClockProfileId::default_pll_64mhz) {
    set_field_bits(kHsionField);
    if (!wait_field_value(kHsirdyField, 1u)) {
      return false;
    }
    write_field(kFlashLatencyField, SystemClockProfileTraits<Id>::kFlashLatency);
    write_field(kPllsrcField, SystemClockProfileTraits<Id>::kPllSource);
    write_field(kPllmField, SystemClockProfileTraits<Id>::kPllM);
    write_field(kPllnField, SystemClockProfileTraits<Id>::kPllN);
    write_field(kPllrField, SystemClockProfileTraits<Id>::kPllR);
    set_field_bits(kPllrenField);
    set_field_bits(kPllonField);
    if (!wait_field_value(kPllrdyField, 1u)) {
      return false;
    }
    write_field(kSwField, 0x2u);
    return wait_field_value(kSwsField, 0x2u);
  } else {
    return false;
  }
}

inline bool apply_default_system_clock() {
  return apply_system_clock_profile<SystemClockProfileId::safe_hsi16>();
}

inline bool apply_safe_system_clock() {
  return false;
}
}
}
}
}
}
}
