#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
enum class RegisterId : std::uint16_t {
  none,
  register_ccm_cacrr,
  register_ccm_cbcdr,
  register_ccm_cbcmr,
  register_ccm_cscdr1,
  register_ccm_cdhipr,
  register_ccm_ccgr0,
  register_ccm_ccgr1,
  register_ccm_ccgr3,
  register_ccm_ccgr5,
  register_ccm_analog_pll_arm,
  register_dcdc_reg0,
  register_dcdc_reg3,
  register_gpio1_dr,
  register_gpio1_gdir,
  register_gpio1_psr,
  register_gpio4_dr,
  register_gpio4_gdir,
  register_gpio4_psr,
  register_lpuart1_baud,
  register_lpuart1_stat,
  register_lpuart1_ctrl,
  register_lpuart1_data,
  register_lpuart3_baud,
  register_lpuart3_stat,
  register_lpuart3_ctrl,
  register_lpuart3_data,
};

template<RegisterId Id>
struct RegisterTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

template<>
struct RegisterTraits<RegisterId::register_ccm_cacrr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x400FC000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
};

template<>
struct RegisterTraits<RegisterId::register_ccm_cbcdr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x400FC000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
};

template<>
struct RegisterTraits<RegisterId::register_ccm_cbcmr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x400FC000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
};

template<>
struct RegisterTraits<RegisterId::register_ccm_cscdr1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x400FC000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
};

template<>
struct RegisterTraits<RegisterId::register_ccm_cdhipr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x400FC000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
  static constexpr int kSizeBits = 32;
};

template<>
struct RegisterTraits<RegisterId::register_ccm_ccgr0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x400FC000u;
  static constexpr std::uint32_t kOffsetBytes = 104u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
};

template<>
struct RegisterTraits<RegisterId::register_ccm_ccgr1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x400FC000u;
  static constexpr std::uint32_t kOffsetBytes = 108u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
};

template<>
struct RegisterTraits<RegisterId::register_ccm_ccgr3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x400FC000u;
  static constexpr std::uint32_t kOffsetBytes = 116u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
};

template<>
struct RegisterTraits<RegisterId::register_ccm_ccgr5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x400FC000u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
};

template<>
struct RegisterTraits<RegisterId::register_ccm_analog_pll_arm> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x400D8000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
};

template<>
struct RegisterTraits<RegisterId::register_dcdc_reg0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40080000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
  static constexpr int kSizeBits = 32;
};

template<>
struct RegisterTraits<RegisterId::register_dcdc_reg3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40080000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
};

template<>
struct RegisterTraits<RegisterId::register_gpio1_dr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x401B8000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

template<>
struct RegisterTraits<RegisterId::register_gpio1_gdir> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x401B8000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

template<>
struct RegisterTraits<RegisterId::register_gpio1_psr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x401B8000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

template<>
struct RegisterTraits<RegisterId::register_gpio4_dr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x401C4000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

template<>
struct RegisterTraits<RegisterId::register_gpio4_gdir> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x401C4000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

template<>
struct RegisterTraits<RegisterId::register_gpio4_psr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x401C4000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

template<>
struct RegisterTraits<RegisterId::register_lpuart1_baud> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40184000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

template<>
struct RegisterTraits<RegisterId::register_lpuart1_stat> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40184000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

template<>
struct RegisterTraits<RegisterId::register_lpuart1_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40184000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

template<>
struct RegisterTraits<RegisterId::register_lpuart1_data> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40184000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

template<>
struct RegisterTraits<RegisterId::register_lpuart3_baud> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x4018C000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

template<>
struct RegisterTraits<RegisterId::register_lpuart3_stat> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x4018C000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

template<>
struct RegisterTraits<RegisterId::register_lpuart3_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x4018C000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

template<>
struct RegisterTraits<RegisterId::register_lpuart3_data> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x4018C000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
};

inline constexpr std::array<RegisterId, 26> kRegisters = {{
  RegisterId::register_ccm_cacrr,
  RegisterId::register_ccm_cbcdr,
  RegisterId::register_ccm_cbcmr,
  RegisterId::register_ccm_cscdr1,
  RegisterId::register_ccm_cdhipr,
  RegisterId::register_ccm_ccgr0,
  RegisterId::register_ccm_ccgr1,
  RegisterId::register_ccm_ccgr3,
  RegisterId::register_ccm_ccgr5,
  RegisterId::register_ccm_analog_pll_arm,
  RegisterId::register_dcdc_reg0,
  RegisterId::register_dcdc_reg3,
  RegisterId::register_gpio1_dr,
  RegisterId::register_gpio1_gdir,
  RegisterId::register_gpio1_psr,
  RegisterId::register_gpio4_dr,
  RegisterId::register_gpio4_gdir,
  RegisterId::register_gpio4_psr,
  RegisterId::register_lpuart1_baud,
  RegisterId::register_lpuart1_stat,
  RegisterId::register_lpuart1_ctrl,
  RegisterId::register_lpuart1_data,
  RegisterId::register_lpuart3_baud,
  RegisterId::register_lpuart3_stat,
  RegisterId::register_lpuart3_ctrl,
  RegisterId::register_lpuart3_data,
}};
}
}
}
}
}
}
