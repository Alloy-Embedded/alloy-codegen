#pragma once

#include <array>
#include <cstdint>
#include "driver_semantics/common.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70q21b {
enum class SystemClockProfileId : std::uint16_t {
  none,
  crystal_12mhz,
  default_safe_internal_12mhz,
  plla_150mhz,
  safe_internal_12mhz,
};

enum class SystemClockProfileKindId : std::uint16_t {
  none,
  default_value,
  direct,
  performance,
  safe,
};

enum class SystemClockSourceKindId : std::uint16_t {
  none,
  external_oscillator,
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
inline constexpr std::array<SystemClockProfileDescriptor, 4> kSystemClockProfiles = {{
  {SystemClockProfileId::crystal_12mhz, SystemClockProfileKindId::direct, SystemClockSourceKindId::external_oscillator, 12000000u, 12000000u, 0u, 0u, 12000000u},
  {SystemClockProfileId::default_safe_internal_12mhz, SystemClockProfileKindId::default_value, SystemClockSourceKindId::internal_oscillator, 12000000u, 12000000u, 0u, 0u, 12000000u},
  {SystemClockProfileId::plla_150mhz, SystemClockProfileKindId::performance, SystemClockSourceKindId::pll_external, 150000000u, 150000000u, 0u, 0u, 150000000u},
  {SystemClockProfileId::safe_internal_12mhz, SystemClockProfileKindId::safe, SystemClockSourceKindId::internal_oscillator, 12000000u, 12000000u, 0u, 0u, 12000000u},
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
struct SystemClockProfileTraits<SystemClockProfileId::crystal_12mhz> {
  static constexpr bool kPresent = true;
  static constexpr SystemClockProfileKindId kKindId = SystemClockProfileKindId::direct;
  static constexpr SystemClockSourceKindId kSourceKindId = SystemClockSourceKindId::external_oscillator;
  static constexpr std::uint32_t kSysclkHz = 12000000u;
  static constexpr std::uint32_t kHclkHz = 12000000u;
  static constexpr std::uint32_t kApb1Hz = 0u;
  static constexpr std::uint32_t kApb2Hz = 0u;
  static constexpr std::uint32_t kPclkHz = 12000000u;
  static constexpr std::uint32_t kSourceHz = 12000000u;
  static constexpr std::uint32_t kAhbPrescaler = 1u;
  static constexpr std::uint32_t kApb1Prescaler = 1u;
  static constexpr std::uint32_t kApb2Prescaler = 1u;
  static constexpr std::uint32_t kOscillatorStartupCycles = 255u;
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
struct SystemClockProfileTraits<SystemClockProfileId::default_safe_internal_12mhz> {
  static constexpr bool kPresent = true;
  static constexpr SystemClockProfileKindId kKindId = SystemClockProfileKindId::default_value;
  static constexpr SystemClockSourceKindId kSourceKindId = SystemClockSourceKindId::internal_oscillator;
  static constexpr std::uint32_t kSysclkHz = 12000000u;
  static constexpr std::uint32_t kHclkHz = 12000000u;
  static constexpr std::uint32_t kApb1Hz = 0u;
  static constexpr std::uint32_t kApb2Hz = 0u;
  static constexpr std::uint32_t kPclkHz = 12000000u;
  static constexpr std::uint32_t kSourceHz = 12000000u;
  static constexpr std::uint32_t kAhbPrescaler = 1u;
  static constexpr std::uint32_t kApb1Prescaler = 1u;
  static constexpr std::uint32_t kApb2Prescaler = 1u;
  static constexpr std::uint32_t kOscillatorStartupCycles = 255u;
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
struct SystemClockProfileTraits<SystemClockProfileId::plla_150mhz> {
  static constexpr bool kPresent = true;
  static constexpr SystemClockProfileKindId kKindId = SystemClockProfileKindId::performance;
  static constexpr SystemClockSourceKindId kSourceKindId = SystemClockSourceKindId::pll_external;
  static constexpr std::uint32_t kSysclkHz = 150000000u;
  static constexpr std::uint32_t kHclkHz = 150000000u;
  static constexpr std::uint32_t kApb1Hz = 0u;
  static constexpr std::uint32_t kApb2Hz = 0u;
  static constexpr std::uint32_t kPclkHz = 150000000u;
  static constexpr std::uint32_t kSourceHz = 12000000u;
  static constexpr std::uint32_t kAhbPrescaler = 1u;
  static constexpr std::uint32_t kApb1Prescaler = 1u;
  static constexpr std::uint32_t kApb2Prescaler = 1u;
  static constexpr std::uint32_t kOscillatorStartupCycles = 255u;
  static constexpr std::uint32_t kMckPrescaler = 2u;
  static constexpr std::uint32_t kCpuPrescaler = 1u;
  static constexpr std::uint32_t kIpgPrescaler = 1u;
  static constexpr std::uint32_t kPllM = 1u;
  static constexpr std::uint32_t kPllN = 24u;
  static constexpr std::uint32_t kPllP = 0u;
  static constexpr std::uint32_t kPllQ = 0u;
  static constexpr std::uint32_t kPllR = 0u;
  static constexpr std::uint32_t kFlashLatency = 6u;
};

template<>
struct SystemClockProfileTraits<SystemClockProfileId::safe_internal_12mhz> {
  static constexpr bool kPresent = true;
  static constexpr SystemClockProfileKindId kKindId = SystemClockProfileKindId::safe;
  static constexpr SystemClockSourceKindId kSourceKindId = SystemClockSourceKindId::internal_oscillator;
  static constexpr std::uint32_t kSysclkHz = 12000000u;
  static constexpr std::uint32_t kHclkHz = 12000000u;
  static constexpr std::uint32_t kApb1Hz = 0u;
  static constexpr std::uint32_t kApb2Hz = 0u;
  static constexpr std::uint32_t kPclkHz = 12000000u;
  static constexpr std::uint32_t kSourceHz = 12000000u;
  static constexpr std::uint32_t kAhbPrescaler = 1u;
  static constexpr std::uint32_t kApb1Prescaler = 1u;
  static constexpr std::uint32_t kApb2Prescaler = 1u;
  static constexpr std::uint32_t kOscillatorStartupCycles = 255u;
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

inline constexpr auto kPmcCkgrMorRegister = RuntimeRegisterRef{RegisterId::register_pmc_ckgr_mor, 0x400E0600u, 32u, true};
inline constexpr auto kPmcCkgrPllarRegister = RuntimeRegisterRef{RegisterId::register_pmc_ckgr_pllar, 0x400E0600u, 40u, true};
inline constexpr auto kPmcMckrRegister = RuntimeRegisterRef{RegisterId::register_pmc_mckr, 0x400E0600u, 48u, true};
inline constexpr auto kPmcSrRegister = RuntimeRegisterRef{RegisterId::register_pmc_sr, 0x400E0600u, 104u, true};
inline constexpr auto kEfcFmrRegister = RuntimeRegisterRef{RegisterId::register_efc_eefc_fmr, 0x400E0C00u, 0u, true};
inline constexpr auto kMorMoscxtenField = RuntimeFieldRef{FieldId::field_pmc_ckgr_mor_moscxten, RuntimeRegisterRef{RegisterId::register_pmc_ckgr_mor, 0x400E0600u, 32u, true}, 0u, 1u, true};
inline constexpr auto kMorMoscrcenField = RuntimeFieldRef{FieldId::field_pmc_ckgr_mor_moscrcen, RuntimeRegisterRef{RegisterId::register_pmc_ckgr_mor, 0x400E0600u, 32u, true}, 3u, 1u, true};
inline constexpr auto kMorMoscrcfField = RuntimeFieldRef{FieldId::field_pmc_ckgr_mor_moscrcf, RuntimeRegisterRef{RegisterId::register_pmc_ckgr_mor, 0x400E0600u, 32u, true}, 4u, 3u, true};
inline constexpr auto kMorMoscxtstField = RuntimeFieldRef{FieldId::field_pmc_ckgr_mor_moscxtst, RuntimeRegisterRef{RegisterId::register_pmc_ckgr_mor, 0x400E0600u, 32u, true}, 8u, 8u, true};
inline constexpr auto kMorKeyField = RuntimeFieldRef{FieldId::field_pmc_ckgr_mor_key, RuntimeRegisterRef{RegisterId::register_pmc_ckgr_mor, 0x400E0600u, 32u, true}, 16u, 8u, true};
inline constexpr auto kMorMoscselField = RuntimeFieldRef{FieldId::field_pmc_ckgr_mor_moscsel, RuntimeRegisterRef{RegisterId::register_pmc_ckgr_mor, 0x400E0600u, 32u, true}, 24u, 1u, true};
inline constexpr auto kPllarDivaField = RuntimeFieldRef{FieldId::field_pmc_ckgr_pllar_diva, RuntimeRegisterRef{RegisterId::register_pmc_ckgr_pllar, 0x400E0600u, 40u, true}, 0u, 8u, true};
inline constexpr auto kPllarPllacountField = RuntimeFieldRef{FieldId::field_pmc_ckgr_pllar_pllacount, RuntimeRegisterRef{RegisterId::register_pmc_ckgr_pllar, 0x400E0600u, 40u, true}, 8u, 6u, true};
inline constexpr auto kPllarMulaField = RuntimeFieldRef{FieldId::field_pmc_ckgr_pllar_mula, RuntimeRegisterRef{RegisterId::register_pmc_ckgr_pllar, 0x400E0600u, 40u, true}, 16u, 11u, true};
inline constexpr auto kPllarOneField = RuntimeFieldRef{FieldId::field_pmc_ckgr_pllar_one, RuntimeRegisterRef{RegisterId::register_pmc_ckgr_pllar, 0x400E0600u, 40u, true}, 29u, 1u, true};
inline constexpr auto kMckrCssField = RuntimeFieldRef{FieldId::field_pmc_mckr_css, RuntimeRegisterRef{RegisterId::register_pmc_mckr, 0x400E0600u, 48u, true}, 0u, 2u, true};
inline constexpr auto kMckrPresField = RuntimeFieldRef{FieldId::field_pmc_mckr_pres, RuntimeRegisterRef{RegisterId::register_pmc_mckr, 0x400E0600u, 48u, true}, 4u, 3u, true};
inline constexpr auto kMckrMdivField = RuntimeFieldRef{FieldId::field_pmc_mckr_mdiv, RuntimeRegisterRef{RegisterId::register_pmc_mckr, 0x400E0600u, 48u, true}, 8u, 2u, true};
inline constexpr auto kSrMoscxtsField = RuntimeFieldRef{FieldId::field_pmc_sr_moscxts, RuntimeRegisterRef{RegisterId::register_pmc_sr, 0x400E0600u, 104u, true}, 0u, 1u, true};
inline constexpr auto kSrLockaField = RuntimeFieldRef{FieldId::field_pmc_sr_locka, RuntimeRegisterRef{RegisterId::register_pmc_sr, 0x400E0600u, 104u, true}, 1u, 1u, true};
inline constexpr auto kSrMckrdyField = RuntimeFieldRef{FieldId::field_pmc_sr_mckrdy, RuntimeRegisterRef{RegisterId::register_pmc_sr, 0x400E0600u, 104u, true}, 3u, 1u, true};
inline constexpr auto kSrMoscselsField = RuntimeFieldRef{FieldId::field_pmc_sr_moscsels, RuntimeRegisterRef{RegisterId::register_pmc_sr, 0x400E0600u, 104u, true}, 16u, 1u, true};
inline constexpr auto kSrMoscrcsField = RuntimeFieldRef{FieldId::field_pmc_sr_moscrcs, RuntimeRegisterRef{RegisterId::register_pmc_sr, 0x400E0600u, 104u, true}, 17u, 1u, true};
inline constexpr auto kEfcFwsField = RuntimeFieldRef{FieldId::field_efc_eefc_fmr_fws, RuntimeRegisterRef{RegisterId::register_efc_eefc_fmr, 0x400E0C00u, 0u, true}, 8u, 4u, true};

inline constexpr std::uint32_t kPmcMorKeyPasswd = 0x37u;
inline constexpr std::uint32_t kPmcMainRc12MHz = 0x2u;
inline constexpr std::uint32_t kPmcMckCssMain = 0x1u;
inline constexpr std::uint32_t kPmcMckCssPlla = 0x2u;
inline constexpr std::uint32_t kPmcMckMdivEqPck = 0x0u;

inline std::uint32_t encode_same70_mck_prescaler(std::uint32_t divisor) {
  switch (divisor) {
    case 1u: return 0x0u;
    case 2u: return 0x1u;
    case 4u: return 0x2u;
    case 8u: return 0x3u;
    case 16u: return 0x4u;
    case 32u: return 0x5u;
    case 64u: return 0x6u;
    case 3u: return 0x7u;
    default: return 0x0u;
  }
}

inline std::uint32_t encode_field_value(driver_semantics::RuntimeFieldRef field, std::uint32_t value) {
  return (value << field.bit_offset) & field_mask(field);
}

inline bool same70_wait_mck_ready() {
  return wait_field_value(kSrMckrdyField, 1u);
}

inline void same70_write_main_oscillator(bool use_external, std::uint32_t startup_cycles) {
  std::uint32_t mor = 0u;
  mor |= encode_field_value(kMorKeyField, kPmcMorKeyPasswd);
  mor |= encode_field_value(kMorMoscxtstField, startup_cycles);
  mor |= encode_field_value(kMorMoscrcfField, kPmcMainRc12MHz);
  mor |= encode_field_value(kMorMoscrcenField, 1u);
  if (use_external) {
    mor |= encode_field_value(kMorMoscxtenField, 1u);
  }
  write_register(kPmcCkgrMorRegister, mor);
}

inline bool same70_enable_internal_rc(std::uint32_t startup_cycles) {
  same70_write_main_oscillator(false, startup_cycles);
  return wait_field_value(kSrMoscrcsField, 1u);
}

inline bool same70_enable_external_crystal(std::uint32_t startup_cycles) {
  same70_write_main_oscillator(true, startup_cycles);
  if (!wait_field_value(kSrMoscxtsField, 1u)) {
    return false;
  }
  std::uint32_t mor = 0u;
  mor |= encode_field_value(kMorKeyField, kPmcMorKeyPasswd);
  mor |= encode_field_value(kMorMoscxtstField, startup_cycles);
  mor |= encode_field_value(kMorMoscrcfField, kPmcMainRc12MHz);
  mor |= encode_field_value(kMorMoscrcenField, 1u);
  mor |= encode_field_value(kMorMoscxtenField, 1u);
  mor |= encode_field_value(kMorMoscselField, 1u);
  write_register(kPmcCkgrMorRegister, mor);
  return wait_field_value(kSrMoscselsField, 1u);
}

inline bool same70_switch_mck(std::uint32_t css_value, std::uint32_t prescaler_divisor) {
  write_field(kMckrCssField, kPmcMckCssMain);
  if (!same70_wait_mck_ready()) {
    return false;
  }
  write_field(kMckrPresField, encode_same70_mck_prescaler(prescaler_divisor));
  write_field(kMckrMdivField, kPmcMckMdivEqPck);
  if (!same70_wait_mck_ready()) {
    return false;
  }
  write_field(kMckrCssField, css_value);
  return same70_wait_mck_ready();
}

template<SystemClockProfileId Id>
inline bool apply_system_clock_profile() {
  if constexpr (!SystemClockProfileTraits<Id>::kPresent) {
    return false;
  } else if constexpr (
      Id == SystemClockProfileId::safe_internal_12mhz ||
      Id == SystemClockProfileId::default_safe_internal_12mhz) {
    if (!same70_enable_internal_rc(SystemClockProfileTraits<Id>::kOscillatorStartupCycles)) {
      return false;
    }
    return same70_switch_mck(kPmcMckCssMain, SystemClockProfileTraits<Id>::kMckPrescaler);
  } else if constexpr (Id == SystemClockProfileId::crystal_12mhz) {
    if (!same70_enable_external_crystal(SystemClockProfileTraits<Id>::kOscillatorStartupCycles)) {
      return false;
    }
    return same70_switch_mck(kPmcMckCssMain, SystemClockProfileTraits<Id>::kMckPrescaler);
  } else if constexpr (Id == SystemClockProfileId::plla_150mhz) {
    if (!same70_enable_external_crystal(SystemClockProfileTraits<Id>::kOscillatorStartupCycles)) {
      return false;
    }
    write_field(kEfcFwsField, SystemClockProfileTraits<Id>::kFlashLatency);
    std::uint32_t pllar = 0u;
    pllar |= encode_field_value(kPllarDivaField, SystemClockProfileTraits<Id>::kPllM);
    pllar |= encode_field_value(kPllarPllacountField, 0x3Fu);
    pllar |= encode_field_value(kPllarMulaField, SystemClockProfileTraits<Id>::kPllN);
    pllar |= encode_field_value(kPllarOneField, 1u);
    write_register(kPmcCkgrPllarRegister, pllar);
    if (!wait_field_value(kSrLockaField, 1u)) {
      return false;
    }
    return same70_switch_mck(kPmcMckCssPlla, SystemClockProfileTraits<Id>::kMckPrescaler);
  } else {
    return false;
  }
}

inline bool apply_default_system_clock() {
  return apply_system_clock_profile<SystemClockProfileId::default_safe_internal_12mhz>();
}

inline bool apply_safe_system_clock() {
  return apply_system_clock_profile<SystemClockProfileId::safe_internal_12mhz>();
}
}
}
}
}
}
}
