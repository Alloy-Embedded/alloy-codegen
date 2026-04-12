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
inline constexpr std::array<RegisterFieldDescriptor, 3> kRegisterFields = {{
  {FieldId::field_gpioa_moder_mode2, RegisterId::register_gpioa_moder, PeripheralId::GPIOA, 4u, 2u, AccessKindId::none},
  {FieldId::field_gpiob_moder_mode6, RegisterId::register_gpiob_moder, PeripheralId::GPIOB, 12u, 2u, AccessKindId::none},
  {FieldId::field_usart1_cr1_ue, RegisterId::register_usart1_cr1, PeripheralId::USART1, 0u, 1u, AccessKindId::none},
}};
}
}
}
}
}
