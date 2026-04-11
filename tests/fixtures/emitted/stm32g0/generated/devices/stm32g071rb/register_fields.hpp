#pragma once

#include <array>
#include <cstdint>
#include "register_map.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace devices {
namespace stm32g071rb {
enum class FieldId : std::uint16_t {
  field_gpioa_moder_mode2,
  field_gpiob_moder_mode6,
  field_usart1_cr1_ue,
};

struct RegisterFieldDescriptor {
  FieldId field_id;
  RegisterId register_id;
  PeripheralId peripheral_id;
  const char* peripheral_name;
  const char* register_name;
  const char* field_name;
  std::uint16_t bit_offset;
  std::uint16_t bit_width;
  const char* access;
};
inline constexpr std::array<RegisterFieldDescriptor, 3> kRegisterFields = {{
  {FieldId::field_gpioa_moder_mode2, RegisterId::register_gpioa_moder, PeripheralId::GPIOA, "GPIOA", "MODER", "MODE2", 4u, 2u, nullptr},
  {FieldId::field_gpiob_moder_mode6, RegisterId::register_gpiob_moder, PeripheralId::GPIOB, "GPIOB", "MODER", "MODE6", 12u, 2u, nullptr},
  {FieldId::field_usart1_cr1_ue, RegisterId::register_usart1_cr1, PeripheralId::USART1, "USART1", "CR1", "UE", 0u, 1u, nullptr},
}};
}
}
}
}
}
