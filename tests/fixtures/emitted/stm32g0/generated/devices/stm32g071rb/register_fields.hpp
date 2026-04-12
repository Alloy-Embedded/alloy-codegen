#pragma once

#include <array>
#include <cstdint>
#include "../../runtime_semantics.hpp"
#include "register_map.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace devices {
namespace stm32g071rb {
enum class FieldId : std::uint16_t {
  field_gpioa_moder_mode2,
  field_gpiob_moder_mode6,
  field_rcc_ahbenr_dma1en,
  field_rcc_ahbrstr_dma1rst,
  field_rcc_apbenr1_fdcanen,
  field_rcc_apbenr1_usart2en,
  field_rcc_apbenr2_usart1en,
  field_rcc_apbrstr1_fdcanrst,
  field_rcc_apbrstr1_usart2rst,
  field_rcc_apbrstr2_usart1rst,
  field_rcc_iopenr_gpioaen,
  field_rcc_iopenr_gpioben,
  field_rcc_iopenr_gpiocen,
  field_rcc_iopenr_gpioden,
  field_rcc_iopenr_gpiofen,
  field_rcc_ioprstr_gpioarst,
  field_rcc_ioprstr_gpiobrst,
  field_rcc_ioprstr_gpiocrst,
  field_rcc_ioprstr_gpiodrst,
  field_rcc_ioprstr_gpiofrst,
  field_usart1_cr1_ue,
};

struct RegisterFieldDescriptor {
  FieldId field_id;
  RegisterId register_id;
  PeripheralId peripheral_id;
  std::uint16_t bit_offset;
  std::uint16_t bit_width;
  AccessKindId access_id;
};
inline constexpr std::array<RegisterFieldDescriptor, 21> kRegisterFields = {{
  {FieldId::field_gpioa_moder_mode2, RegisterId::register_gpioa_moder, PeripheralId::GPIOA, 4u, 2u, AccessKindId::none},
  {FieldId::field_gpiob_moder_mode6, RegisterId::register_gpiob_moder, PeripheralId::GPIOB, 12u, 2u, AccessKindId::none},
  {FieldId::field_rcc_ahbenr_dma1en, RegisterId::register_rcc_ahbenr, PeripheralId::RCC, 0u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_ahbrstr_dma1rst, RegisterId::register_rcc_ahbrstr, PeripheralId::RCC, 0u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_apbenr1_fdcanen, RegisterId::register_rcc_apbenr1, PeripheralId::RCC, 12u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_apbenr1_usart2en, RegisterId::register_rcc_apbenr1, PeripheralId::RCC, 17u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_apbenr2_usart1en, RegisterId::register_rcc_apbenr2, PeripheralId::RCC, 14u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_apbrstr1_fdcanrst, RegisterId::register_rcc_apbrstr1, PeripheralId::RCC, 12u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_apbrstr1_usart2rst, RegisterId::register_rcc_apbrstr1, PeripheralId::RCC, 17u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_apbrstr2_usart1rst, RegisterId::register_rcc_apbrstr2, PeripheralId::RCC, 14u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_iopenr_gpioaen, RegisterId::register_rcc_iopenr, PeripheralId::RCC, 0u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_iopenr_gpioben, RegisterId::register_rcc_iopenr, PeripheralId::RCC, 1u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_iopenr_gpiocen, RegisterId::register_rcc_iopenr, PeripheralId::RCC, 2u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_iopenr_gpioden, RegisterId::register_rcc_iopenr, PeripheralId::RCC, 3u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_iopenr_gpiofen, RegisterId::register_rcc_iopenr, PeripheralId::RCC, 5u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_ioprstr_gpioarst, RegisterId::register_rcc_ioprstr, PeripheralId::RCC, 0u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_ioprstr_gpiobrst, RegisterId::register_rcc_ioprstr, PeripheralId::RCC, 1u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_ioprstr_gpiocrst, RegisterId::register_rcc_ioprstr, PeripheralId::RCC, 2u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_ioprstr_gpiodrst, RegisterId::register_rcc_ioprstr, PeripheralId::RCC, 3u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_rcc_ioprstr_gpiofrst, RegisterId::register_rcc_ioprstr, PeripheralId::RCC, 5u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_usart1_cr1_ue, RegisterId::register_usart1_cr1, PeripheralId::USART1, 0u, 1u, AccessKindId::none},
}};
}
}
}
}
}
