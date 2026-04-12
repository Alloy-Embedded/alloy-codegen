#pragma once

#include <array>
#include <cstdint>
#include "clock_tree_lite.hpp"
#include "runtime_refs.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
enum class PackageRefId : std::uint16_t {
  none,
  stm32g071rb_lqfp64,
};

enum class StateRefId : std::uint16_t {
  none,
  selected,
};

enum class PinRefId : std::uint16_t {
  none,
  stm32g071rb_PA0,
  stm32g071rb_PA1,
  stm32g071rb_PA2,
  stm32g071rb_PA3,
  stm32g071rb_PB6,
  stm32g071rb_PB7,
};

enum class ConstraintRefId : std::uint16_t {
  none,
};

enum class SelectorRefId : std::uint16_t {
  none,
  stm32g071rb_selector_0,
};

enum class RegisterRefId : std::uint16_t {
  none,
  stm32g071rb_register_gpioa_afrh,
  stm32g071rb_register_gpioa_afrl,
  stm32g071rb_register_gpioa_moder,
  stm32g071rb_register_gpiob_afrh,
  stm32g071rb_register_gpiob_afrl,
  stm32g071rb_register_gpiob_moder,
  stm32g071rb_register_rcc_ahbenr,
  stm32g071rb_register_rcc_ahbrstr,
  stm32g071rb_register_rcc_apbenr1,
  stm32g071rb_register_rcc_apbenr2,
  stm32g071rb_register_rcc_apbrstr1,
  stm32g071rb_register_rcc_apbrstr2,
  stm32g071rb_register_rcc_iopenr,
  stm32g071rb_register_rcc_ioprstr,
  stm32g071rb_register_usart1_brr,
  stm32g071rb_register_usart1_cr1,
  stm32g071rb_register_usart1_cr2,
  stm32g071rb_register_usart1_isr,
  stm32g071rb_register_usart1_rdr,
  stm32g071rb_register_usart1_tdr,
};

enum class RegisterFieldRefId : std::uint16_t {
  none,
  stm32g071rb_field_gpioa_moder_mode2,
  stm32g071rb_field_gpiob_moder_mode6,
  stm32g071rb_field_usart1_cr1_ue,
};

struct PackageRefDescriptor {
  PackageRefId package_id;
  const char* device;
  const char* package_name;
};
inline constexpr std::array<PackageRefDescriptor, 2> kPackageRefs = {{
  {PackageRefId::none, nullptr, nullptr},
  {PackageRefId::stm32g071rb_lqfp64, "stm32g071rb", "lqfp64"},
}};

struct StateRefDescriptor {
  StateRefId state_id;
  const char* state_name;
};
inline constexpr std::array<StateRefDescriptor, 2> kStateRefs = {{
  {StateRefId::none, nullptr},
  {StateRefId::selected, "selected"},
}};

struct PinRefDescriptor {
  PinRefId pin_id;
  const char* device;
  const char* pin_name;
  const char* port;
  int pin_number;
};
inline constexpr std::array<PinRefDescriptor, 7> kPinRefs = {{
  {PinRefId::none, nullptr, nullptr, nullptr, -1},
  {PinRefId::stm32g071rb_PA0, "stm32g071rb", "PA0", "A", 0},
  {PinRefId::stm32g071rb_PA1, "stm32g071rb", "PA1", "A", 1},
  {PinRefId::stm32g071rb_PA2, "stm32g071rb", "PA2", "A", 2},
  {PinRefId::stm32g071rb_PA3, "stm32g071rb", "PA3", "A", 3},
  {PinRefId::stm32g071rb_PB6, "stm32g071rb", "PB6", "B", 6},
  {PinRefId::stm32g071rb_PB7, "stm32g071rb", "PB7", "B", 7},
}};

struct ConstraintRefDescriptor {
  ConstraintRefId constraint_id;
  const char* device;
  PinRefId pin_id;
  const char* kind;
  const char* value;
};
inline constexpr std::array<ConstraintRefDescriptor, 1> kConstraintRefs = {{
  {ConstraintRefId::none, nullptr, PinRefId::none, nullptr, nullptr},
}};

struct SelectorRefDescriptor {
  SelectorRefId selector_id;
  const char* device;
  const char* selector_name;
  int selector_value;
};
inline constexpr std::array<SelectorRefDescriptor, 2> kSelectorRefs = {{
  {SelectorRefId::none, nullptr, nullptr, -1},
  {SelectorRefId::stm32g071rb_selector_0, "stm32g071rb", "selector:0", 0},
}};

struct RegisterRefDescriptor {
  RegisterRefId register_id;
  const char* device;
  const char* peripheral_name;
  const char* register_name;
  std::uint32_t offset_bytes;
};
inline constexpr std::array<RegisterRefDescriptor, 21> kRegisterRefs = {{
  {RegisterRefId::none, nullptr, nullptr, nullptr, 0u},
  {RegisterRefId::stm32g071rb_register_gpioa_afrh, "stm32g071rb", "GPIOA", "AFRH", 36u},
  {RegisterRefId::stm32g071rb_register_gpioa_afrl, "stm32g071rb", "GPIOA", "AFRL", 32u},
  {RegisterRefId::stm32g071rb_register_gpioa_moder, "stm32g071rb", "GPIOA", "MODER", 0u},
  {RegisterRefId::stm32g071rb_register_gpiob_afrh, "stm32g071rb", "GPIOB", "AFRH", 36u},
  {RegisterRefId::stm32g071rb_register_gpiob_afrl, "stm32g071rb", "GPIOB", "AFRL", 32u},
  {RegisterRefId::stm32g071rb_register_gpiob_moder, "stm32g071rb", "GPIOB", "MODER", 0u},
  {RegisterRefId::stm32g071rb_register_rcc_ahbenr, "stm32g071rb", "RCC", "AHBENR", 56u},
  {RegisterRefId::stm32g071rb_register_rcc_ahbrstr, "stm32g071rb", "RCC", "AHBRSTR", 40u},
  {RegisterRefId::stm32g071rb_register_rcc_apbenr1, "stm32g071rb", "RCC", "APBENR1", 60u},
  {RegisterRefId::stm32g071rb_register_rcc_apbenr2, "stm32g071rb", "RCC", "APBENR2", 64u},
  {RegisterRefId::stm32g071rb_register_rcc_apbrstr1, "stm32g071rb", "RCC", "APBRSTR1", 44u},
  {RegisterRefId::stm32g071rb_register_rcc_apbrstr2, "stm32g071rb", "RCC", "APBRSTR2", 48u},
  {RegisterRefId::stm32g071rb_register_rcc_iopenr, "stm32g071rb", "RCC", "IOPENR", 52u},
  {RegisterRefId::stm32g071rb_register_rcc_ioprstr, "stm32g071rb", "RCC", "IOPRSTR", 36u},
  {RegisterRefId::stm32g071rb_register_usart1_brr, "stm32g071rb", "USART1", "BRR", 12u},
  {RegisterRefId::stm32g071rb_register_usart1_cr1, "stm32g071rb", "USART1", "CR1", 0u},
  {RegisterRefId::stm32g071rb_register_usart1_cr2, "stm32g071rb", "USART1", "CR2", 4u},
  {RegisterRefId::stm32g071rb_register_usart1_isr, "stm32g071rb", "USART1", "ISR", 28u},
  {RegisterRefId::stm32g071rb_register_usart1_rdr, "stm32g071rb", "USART1", "RDR", 36u},
  {RegisterRefId::stm32g071rb_register_usart1_tdr, "stm32g071rb", "USART1", "TDR", 40u},
}};

struct RegisterFieldRefDescriptor {
  RegisterFieldRefId field_id;
  const char* device;
  RegisterRefId register_id;
  const char* peripheral_name;
  const char* field_name;
  std::uint16_t bit_offset;
  std::uint16_t bit_width;
};
inline constexpr std::array<RegisterFieldRefDescriptor, 4> kRegisterFieldRefs = {{
  {RegisterFieldRefId::none, nullptr, RegisterRefId::none, nullptr, nullptr, 0u, 0u},
  {RegisterFieldRefId::stm32g071rb_field_gpioa_moder_mode2, "stm32g071rb", RegisterRefId::stm32g071rb_register_gpioa_moder, "GPIOA", "MODE2", 4u, 2u},
  {RegisterFieldRefId::stm32g071rb_field_gpiob_moder_mode6, "stm32g071rb", RegisterRefId::stm32g071rb_register_gpiob_moder, "GPIOB", "MODE6", 12u, 2u},
  {RegisterFieldRefId::stm32g071rb_field_usart1_cr1_ue, "stm32g071rb", RegisterRefId::stm32g071rb_register_usart1_cr1, "USART1", "UE", 0u, 1u},
}};
}
}
}
