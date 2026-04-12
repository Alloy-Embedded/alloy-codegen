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
  field_gpioa_moder_mode2,
  field_gpiob_moder_mode6,
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
struct RegisterFieldTraits<FieldId::field_usart1_cr1_ue> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart1_cr1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

inline constexpr std::array<FieldId, 3> kRegisterFields = {{
  FieldId::field_gpioa_moder_mode2,
  FieldId::field_gpiob_moder_mode6,
  FieldId::field_usart1_cr1_ue,
}};
}
}
}
}
}
}
