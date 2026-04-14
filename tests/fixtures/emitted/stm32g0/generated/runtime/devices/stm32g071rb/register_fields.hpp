#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "registers.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g071rb {
enum class FieldId : std::uint16_t {
  none,
  field_flash_acr_latency,
  field_gpioa_moder_mode2,
  field_gpiob_moder_mode6,
  field_rcc_ahbenr_dma1en,
  field_rcc_ahbrstr_dma1rst,
  field_rcc_apbenr2_usart1en,
  field_rcc_apbrstr2_usart1rst,
  field_rcc_cfgr_sw,
  field_rcc_cfgr_sws,
  field_rcc_cr_hsion,
  field_rcc_cr_hsirdy,
  field_rcc_cr_pllon,
  field_rcc_cr_pllrdy,
  field_rcc_iopenr_gpioaen,
  field_rcc_iopenr_gpioben,
  field_rcc_ioprstr_gpioarst,
  field_rcc_ioprstr_gpiobrst,
  field_rcc_pllcfgr_pllsrc,
  field_rcc_pllcfgr_pllm,
  field_rcc_pllcfgr_plln,
  field_rcc_pllcfgr_pllren,
  field_rcc_pllcfgr_pllr,
  field_usart1_cr1_ue,
};

template<FieldId Id>
struct RegisterFieldTraits {
  static constexpr bool kPresent = false;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_flash_acr_latency> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_flash_acr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpioa_moder_mode2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpioa_moder;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpiob_moder_mode6> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpiob_moder;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_ahbenr_dma1en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahbenr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_ahbrstr_dma1rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahbrstr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_apbenr2_usart1en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apbenr2;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_apbrstr2_usart1rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apbrstr2;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_cfgr_sw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_cfgr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_cfgr_sws> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_cfgr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_cr_hsion> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_cr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_cr_hsirdy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_cr;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_cr_pllon> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_cr;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_cr_pllrdy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_cr;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_iopenr_gpioaen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_iopenr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_iopenr_gpioben> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_iopenr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_ioprstr_gpioarst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ioprstr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_ioprstr_gpiobrst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ioprstr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_pllcfgr_pllsrc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_pllcfgr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_pllcfgr_pllm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_pllcfgr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_pllcfgr_plln> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_pllcfgr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_pllcfgr_pllren> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_pllcfgr;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_rcc_pllcfgr_pllr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_pllcfgr;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart1_cr1_ue> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart1_cr1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

inline constexpr std::array<FieldId, 23> kRegisterFields = {{
  FieldId::field_flash_acr_latency,
  FieldId::field_gpioa_moder_mode2,
  FieldId::field_gpiob_moder_mode6,
  FieldId::field_rcc_ahbenr_dma1en,
  FieldId::field_rcc_ahbrstr_dma1rst,
  FieldId::field_rcc_apbenr2_usart1en,
  FieldId::field_rcc_apbrstr2_usart1rst,
  FieldId::field_rcc_cfgr_sw,
  FieldId::field_rcc_cfgr_sws,
  FieldId::field_rcc_cr_hsion,
  FieldId::field_rcc_cr_hsirdy,
  FieldId::field_rcc_cr_pllon,
  FieldId::field_rcc_cr_pllrdy,
  FieldId::field_rcc_iopenr_gpioaen,
  FieldId::field_rcc_iopenr_gpioben,
  FieldId::field_rcc_ioprstr_gpioarst,
  FieldId::field_rcc_ioprstr_gpiobrst,
  FieldId::field_rcc_pllcfgr_pllsrc,
  FieldId::field_rcc_pllcfgr_pllm,
  FieldId::field_rcc_pllcfgr_plln,
  FieldId::field_rcc_pllcfgr_pllren,
  FieldId::field_rcc_pllcfgr_pllr,
  FieldId::field_usart1_cr1_ue,
}};
}
}
}
}
}
}
