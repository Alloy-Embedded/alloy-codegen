#pragma once

#include <array>
#include <cstdint>
#include "driver_semantics/common.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
enum class SystemClockProfileId : std::uint16_t {
  none,
  default_arm_pll_600mhz,
  safe_osc24m,
};

enum class SystemClockProfileKindId : std::uint16_t {
  none,
  default_value,
  safe,
};

enum class SystemClockSourceKindId : std::uint16_t {
  none,
  external_oscillator,
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
  {SystemClockProfileId::default_arm_pll_600mhz, SystemClockProfileKindId::default_value, SystemClockSourceKindId::pll_external, 600000000u, 600000000u, 0u, 0u, 150000000u},
  {SystemClockProfileId::safe_osc24m, SystemClockProfileKindId::safe, SystemClockSourceKindId::external_oscillator, 24000000u, 24000000u, 0u, 0u, 24000000u},
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
struct SystemClockProfileTraits<SystemClockProfileId::default_arm_pll_600mhz> {
  static constexpr bool kPresent = true;
  static constexpr SystemClockProfileKindId kKindId = SystemClockProfileKindId::default_value;
  static constexpr SystemClockSourceKindId kSourceKindId = SystemClockSourceKindId::pll_external;
  static constexpr std::uint32_t kSysclkHz = 600000000u;
  static constexpr std::uint32_t kHclkHz = 600000000u;
  static constexpr std::uint32_t kApb1Hz = 0u;
  static constexpr std::uint32_t kApb2Hz = 0u;
  static constexpr std::uint32_t kPclkHz = 150000000u;
  static constexpr std::uint32_t kSourceHz = 24000000u;
  static constexpr std::uint32_t kAhbPrescaler = 1u;
  static constexpr std::uint32_t kApb1Prescaler = 1u;
  static constexpr std::uint32_t kApb2Prescaler = 1u;
  static constexpr std::uint32_t kOscillatorStartupCycles = 0u;
  static constexpr std::uint32_t kMckPrescaler = 1u;
  static constexpr std::uint32_t kCpuPrescaler = 2u;
  static constexpr std::uint32_t kIpgPrescaler = 4u;
  static constexpr std::uint32_t kPllM = 0u;
  static constexpr std::uint32_t kPllN = 100u;
  static constexpr std::uint32_t kPllP = 0u;
  static constexpr std::uint32_t kPllQ = 0u;
  static constexpr std::uint32_t kPllR = 0u;
  static constexpr std::uint32_t kFlashLatency = 0u;
};

template<>
struct SystemClockProfileTraits<SystemClockProfileId::safe_osc24m> {
  static constexpr bool kPresent = true;
  static constexpr SystemClockProfileKindId kKindId = SystemClockProfileKindId::safe;
  static constexpr SystemClockSourceKindId kSourceKindId = SystemClockSourceKindId::external_oscillator;
  static constexpr std::uint32_t kSysclkHz = 24000000u;
  static constexpr std::uint32_t kHclkHz = 24000000u;
  static constexpr std::uint32_t kApb1Hz = 0u;
  static constexpr std::uint32_t kApb2Hz = 0u;
  static constexpr std::uint32_t kPclkHz = 24000000u;
  static constexpr std::uint32_t kSourceHz = 24000000u;
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

inline constexpr auto kCcmCacrrRegister = RuntimeRegisterRef{RegisterId::register_ccm_cacrr, 0x400FC000u, 16u, true};
inline constexpr auto kCcmCbcdrRegister = RuntimeRegisterRef{RegisterId::register_ccm_cbcdr, 0x400FC000u, 20u, true};
inline constexpr auto kCcmCbcmrRegister = RuntimeRegisterRef{RegisterId::register_ccm_cbcmr, 0x400FC000u, 24u, true};
inline constexpr auto kCcmCdhiprRegister = RuntimeRegisterRef{RegisterId::register_ccm_cdhipr, 0x400FC000u, 72u, true};
inline constexpr auto kCcmAnalogPllArmRegister = RuntimeRegisterRef{RegisterId::register_ccm_analog_pll_arm, 0x400D8000u, 0u, true};
inline constexpr auto kDcdcReg0Register = RuntimeRegisterRef{RegisterId::register_dcdc_reg0, 0x40080000u, 0u, true};
inline constexpr auto kDcdcReg3Register = RuntimeRegisterRef{RegisterId::register_dcdc_reg3, 0x40080000u, 12u, true};
inline constexpr auto kArmPodfField = RuntimeFieldRef{FieldId::field_ccm_cacrr_arm_podf, RuntimeRegisterRef{RegisterId::register_ccm_cacrr, 0x400FC000u, 16u, true}, 0u, 3u, true};
inline constexpr auto kIpgPodfField = RuntimeFieldRef{FieldId::field_ccm_cbcdr_ipg_podf, RuntimeRegisterRef{RegisterId::register_ccm_cbcdr, 0x400FC000u, 20u, true}, 8u, 2u, true};
inline constexpr auto kAhbPodfField = RuntimeFieldRef{FieldId::field_ccm_cbcdr_ahb_podf, RuntimeRegisterRef{RegisterId::register_ccm_cbcdr, 0x400FC000u, 20u, true}, 10u, 3u, true};
inline constexpr auto kPeriphClockSelField = RuntimeFieldRef{FieldId::field_ccm_cbcdr_periph_clk_sel, RuntimeRegisterRef{RegisterId::register_ccm_cbcdr, 0x400FC000u, 20u, true}, 25u, 1u, true};
inline constexpr auto kPeriphClock2PodfField = RuntimeFieldRef{FieldId::field_ccm_cbcdr_periph_clk2_podf, RuntimeRegisterRef{RegisterId::register_ccm_cbcdr, 0x400FC000u, 20u, true}, 27u, 3u, true};
inline constexpr auto kPeriphClock2SelField = RuntimeFieldRef{FieldId::field_ccm_cbcmr_periph_clk2_sel, RuntimeRegisterRef{RegisterId::register_ccm_cbcmr, 0x400FC000u, 24u, true}, 12u, 2u, true};
inline constexpr auto kPrePeriphClockSelField = RuntimeFieldRef{FieldId::field_ccm_cbcmr_pre_periph_clk_sel, RuntimeRegisterRef{RegisterId::register_ccm_cbcmr, 0x400FC000u, 24u, true}, 18u, 2u, true};
inline constexpr auto kAhbPodfBusyField = RuntimeFieldRef{FieldId::field_ccm_cdhipr_ahb_podf_busy, RuntimeRegisterRef{RegisterId::register_ccm_cdhipr, 0x400FC000u, 72u, true}, 1u, 1u, true};
inline constexpr auto kPeriph2ClockSelBusyField = RuntimeFieldRef{FieldId::field_ccm_cdhipr_periph2_clk_sel_busy, RuntimeRegisterRef{RegisterId::register_ccm_cdhipr, 0x400FC000u, 72u, true}, 3u, 1u, true};
inline constexpr auto kPeriphClockSelBusyField = RuntimeFieldRef{FieldId::field_ccm_cdhipr_periph_clk_sel_busy, RuntimeRegisterRef{RegisterId::register_ccm_cdhipr, 0x400FC000u, 72u, true}, 5u, 1u, true};
inline constexpr auto kArmPodfBusyField = RuntimeFieldRef{FieldId::field_ccm_cdhipr_arm_podf_busy, RuntimeRegisterRef{RegisterId::register_ccm_cdhipr, 0x400FC000u, 72u, true}, 16u, 1u, true};
inline constexpr auto kPllArmDivSelectField = RuntimeFieldRef{FieldId::field_ccm_analog_pll_arm_div_select, RuntimeRegisterRef{RegisterId::register_ccm_analog_pll_arm, 0x400D8000u, 0u, true}, 0u, 7u, true};
inline constexpr auto kPllArmPowerdownField = RuntimeFieldRef{FieldId::field_ccm_analog_pll_arm_powerdown, RuntimeRegisterRef{RegisterId::register_ccm_analog_pll_arm, 0x400D8000u, 0u, true}, 12u, 1u, true};
inline constexpr auto kPllArmEnableField = RuntimeFieldRef{FieldId::field_ccm_analog_pll_arm_enable, RuntimeRegisterRef{RegisterId::register_ccm_analog_pll_arm, 0x400D8000u, 0u, true}, 13u, 1u, true};
inline constexpr auto kPllArmBypassField = RuntimeFieldRef{FieldId::field_ccm_analog_pll_arm_bypass, RuntimeRegisterRef{RegisterId::register_ccm_analog_pll_arm, 0x400D8000u, 0u, true}, 16u, 1u, true};
inline constexpr auto kPllArmLockField = RuntimeFieldRef{FieldId::field_ccm_analog_pll_arm_lock, RuntimeRegisterRef{RegisterId::register_ccm_analog_pll_arm, 0x400D8000u, 0u, true}, 31u, 1u, true};
inline constexpr auto kDcdcStatusOkField = RuntimeFieldRef{FieldId::field_dcdc_reg0_sts_dc_ok, RuntimeRegisterRef{RegisterId::register_dcdc_reg0, 0x40080000u, 0u, true}, 31u, 1u, true};
inline constexpr auto kDcdcTargetVoltageField = RuntimeFieldRef{FieldId::field_dcdc_reg3_trg, RuntimeRegisterRef{RegisterId::register_dcdc_reg3, 0x40080000u, 12u, true}, 0u, 5u, true};

inline constexpr std::uint32_t kImxrtPeriphClockSelPrePeriph = 0u;
inline constexpr std::uint32_t kImxrtPeriphClockSelPeriphClock2 = 1u;
inline constexpr std::uint32_t kImxrtPeriphClock2SelOsc24M = 1u;
inline constexpr std::uint32_t kImxrtPrePeriphClockSelPll1 = 0x3u;

inline std::uint32_t encode_field_value(driver_semantics::RuntimeFieldRef field, std::uint32_t value) {
  return (value << field.bit_offset) & field_mask(field);
}

inline bool imxrt_wait_transition_complete(driver_semantics::RuntimeFieldRef field) {
  return wait_field_value(field, 0u);
}

inline std::uint32_t imxrt_target_voltage_mv(std::uint32_t sysclk_hz) {
  return sysclk_hz > 528000000u ? 1250u : 1150u;
}

inline bool imxrt_set_core_voltage(std::uint32_t millivolts) {
  const std::uint32_t target = (millivolts - 800u) / 25u;
  write_field(kDcdcTargetVoltageField, target);
  return wait_field_value(kDcdcStatusOkField, 1u);
}

inline bool imxrt_switch_to_periph_clk2_osc24m() {
  write_field(kPeriphClock2PodfField, 0u);
  write_field(kPeriphClock2SelField, kImxrtPeriphClock2SelOsc24M);
  if (!imxrt_wait_transition_complete(kPeriph2ClockSelBusyField)) {
    return false;
  }
  write_field(kPeriphClockSelField, kImxrtPeriphClockSelPeriphClock2);
  return imxrt_wait_transition_complete(kPeriphClockSelBusyField);
}

inline bool imxrt_program_arm_pll(std::uint32_t div_select) {
  write_register(
      kCcmAnalogPllArmRegister,
      encode_field_value(kPllArmPowerdownField, 1u));
  std::uint32_t pll_arm = 0u;
  pll_arm |= encode_field_value(kPllArmEnableField, 1u);
  pll_arm |= encode_field_value(kPllArmDivSelectField, div_select);
  write_register(kCcmAnalogPllArmRegister, pll_arm);
  if (!wait_field_value(kPllArmLockField, 1u)) {
    return false;
  }
  write_field(kPllArmBypassField, 0u);
  return true;
}

inline bool imxrt_apply_prescalers(
    std::uint32_t cpu_divisor,
    std::uint32_t ahb_divisor,
    std::uint32_t ipg_divisor) {
  write_field(kArmPodfField, cpu_divisor - 1u);
  if (!imxrt_wait_transition_complete(kArmPodfBusyField)) {
    return false;
  }
  const auto current_cbcdr = read_register(kCcmCbcdrRegister);
  const auto ahb_mask = field_mask(kAhbPodfField);
  const auto ipg_mask = field_mask(kIpgPodfField);
  std::uint32_t next_cbcdr = current_cbcdr & ~(ahb_mask | ipg_mask);
  next_cbcdr |= encode_field_value(kAhbPodfField, ahb_divisor - 1u);
  next_cbcdr |= encode_field_value(kIpgPodfField, ipg_divisor - 1u);
  write_register(kCcmCbcdrRegister, next_cbcdr);
  return imxrt_wait_transition_complete(kAhbPodfBusyField);
}

inline bool imxrt_switch_to_arm_pll_root() {
  write_field(kPrePeriphClockSelField, kImxrtPrePeriphClockSelPll1);
  write_field(kPeriphClockSelField, kImxrtPeriphClockSelPrePeriph);
  return imxrt_wait_transition_complete(kPeriphClockSelBusyField);
}

template<SystemClockProfileId Id>
inline bool apply_system_clock_profile() {
  if constexpr (!SystemClockProfileTraits<Id>::kPresent) {
    return false;
  } else if constexpr (Id == SystemClockProfileId::safe_osc24m) {
    if (!imxrt_switch_to_periph_clk2_osc24m()) {
      return false;
    }
    return imxrt_apply_prescalers(
        SystemClockProfileTraits<Id>::kCpuPrescaler,
        SystemClockProfileTraits<Id>::kAhbPrescaler,
        SystemClockProfileTraits<Id>::kIpgPrescaler);
  } else if constexpr (Id == SystemClockProfileId::default_arm_pll_600mhz) {
    if (!imxrt_switch_to_periph_clk2_osc24m()) {
      return false;
    }
    if (!imxrt_set_core_voltage(imxrt_target_voltage_mv(SystemClockProfileTraits<Id>::kSysclkHz))) {
      return false;
    }
    if (!imxrt_program_arm_pll(SystemClockProfileTraits<Id>::kPllN)) {
      return false;
    }
    if (!imxrt_apply_prescalers(
            SystemClockProfileTraits<Id>::kCpuPrescaler,
            SystemClockProfileTraits<Id>::kAhbPrescaler,
            SystemClockProfileTraits<Id>::kIpgPrescaler)) {
      return false;
    }
    return imxrt_switch_to_arm_pll_root();
  } else {
    return false;
  }
}

inline bool apply_default_system_clock() {
  return apply_system_clock_profile<SystemClockProfileId::default_arm_pll_600mhz>();
}

inline bool apply_safe_system_clock() {
  return apply_system_clock_profile<SystemClockProfileId::safe_osc24m>();
}
}
}
}
}
}
}
