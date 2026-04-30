#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g030f6 {
enum class RegisterId : std::uint16_t {
  none,
  register_adc1_isr,
  register_dma1_isr,
  register_dmamux1_c0cr,
  register_flash_acr,
  register_gpioa_moder,
  register_gpioa_afrl,
  register_gpioa_afrh,
  register_i2c1_cr1,
  register_iwdg_kr,
  register_rcc_cr,
  register_rcc_cfgr,
  register_rcc_pllcfgr,
  register_rcc_ioprstr,
  register_rcc_ahbrstr,
  register_rcc_apbrstr1,
  register_rcc_iopenr,
  register_rcc_ahbenr,
  register_rcc_apbenr1,
  register_rtc_tr,
  register_spi1_cr1,
  register_tim1_cr1,
  register_usart2_cr1,
  register_usart2_cr2,
  register_usart2_brr,
  register_usart2_isr,
  register_usart2_rdr,
  register_usart2_tdr,
};

enum class RegisterRole : std::uint16_t {
  none,
  general,
  secondary_core_release,
};

template<RegisterId Id>
struct RegisterTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_adc1_isr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40012400u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma1_isr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40020000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dmamux1_c0cr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40020800u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_flash_acr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40022000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpioa_moder> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x50000000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpioa_afrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x50000000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpioa_afrh> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x50000000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_cr1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40005400u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_iwdg_kr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40003000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_rcc_cr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40021000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_rcc_cfgr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40021000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_rcc_pllcfgr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40021000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_rcc_ioprstr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40021000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_rcc_ahbrstr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40021000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_rcc_apbrstr1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40021000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_rcc_iopenr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40021000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_rcc_ahbenr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40021000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_rcc_apbenr1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40021000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_rtc_tr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40002800u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_cr1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40013000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_tim1_cr1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40012C00u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usart2_cr1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40004400u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usart2_cr2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40004400u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usart2_brr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40004400u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usart2_isr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40004400u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usart2_rdr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40004400u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usart2_tdr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x40004400u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

inline constexpr std::array<RegisterId, 27> kRegisters = {{
  RegisterId::register_adc1_isr,
  RegisterId::register_dma1_isr,
  RegisterId::register_dmamux1_c0cr,
  RegisterId::register_flash_acr,
  RegisterId::register_gpioa_moder,
  RegisterId::register_gpioa_afrl,
  RegisterId::register_gpioa_afrh,
  RegisterId::register_i2c1_cr1,
  RegisterId::register_iwdg_kr,
  RegisterId::register_rcc_cr,
  RegisterId::register_rcc_cfgr,
  RegisterId::register_rcc_pllcfgr,
  RegisterId::register_rcc_ioprstr,
  RegisterId::register_rcc_ahbrstr,
  RegisterId::register_rcc_apbrstr1,
  RegisterId::register_rcc_iopenr,
  RegisterId::register_rcc_ahbenr,
  RegisterId::register_rcc_apbenr1,
  RegisterId::register_rtc_tr,
  RegisterId::register_spi1_cr1,
  RegisterId::register_tim1_cr1,
  RegisterId::register_usart2_cr1,
  RegisterId::register_usart2_cr2,
  RegisterId::register_usart2_brr,
  RegisterId::register_usart2_isr,
  RegisterId::register_usart2_rdr,
  RegisterId::register_usart2_tdr,
}};
}
}
}
}
}
}
