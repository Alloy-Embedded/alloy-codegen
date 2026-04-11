#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace devices {
namespace stm32g071rb {
inline constexpr const char* kDevice = "stm32g071rb";
struct PeripheralBase {
  PeripheralId peripheral_id;
  const char* name;
  std::uintptr_t address;
};
inline constexpr std::array<PeripheralBase, 6> kPeripheralBases = {{
  {PeripheralId::DMA1, "DMA1", 0x40020000u},
  {PeripheralId::DMAMUX1, "DMAMUX1", 0x40020800u},
  {PeripheralId::GPIOA, "GPIOA", 0x50000000u},
  {PeripheralId::GPIOB, "GPIOB", 0x50000400u},
  {PeripheralId::RCC, "RCC", 0x40021000u},
  {PeripheralId::USART1, "USART1", 0x40013800u},
}};

enum class RegisterId : std::uint16_t {
  register_gpioa_moder,
  register_gpioa_afrl,
  register_gpioa_afrh,
  register_gpiob_moder,
  register_gpiob_afrl,
  register_gpiob_afrh,
  register_rcc_ioprstr,
  register_rcc_ahbrstr,
  register_rcc_apbrstr1,
  register_rcc_apbrstr2,
  register_rcc_iopenr,
  register_rcc_ahbenr,
  register_rcc_apbenr1,
  register_rcc_apbenr2,
  register_usart1_cr1,
  register_usart1_cr2,
  register_usart1_brr,
  register_usart1_isr,
  register_usart1_rdr,
  register_usart1_tdr,
};

struct RegisterDescriptor {
  RegisterId register_id;
  PeripheralId peripheral_id;
  const char* peripheral_name;
  const char* register_name;
  std::uint32_t offset_bytes;
  const char* access;
  int size_bits;
};
inline constexpr std::array<RegisterDescriptor, 20> kRegisters = {{
  {RegisterId::register_gpioa_moder, PeripheralId::GPIOA, "GPIOA", "MODER", 0u, nullptr, -1},
  {RegisterId::register_gpioa_afrl, PeripheralId::GPIOA, "GPIOA", "AFRL", 32u, nullptr, -1},
  {RegisterId::register_gpioa_afrh, PeripheralId::GPIOA, "GPIOA", "AFRH", 36u, nullptr, -1},
  {RegisterId::register_gpiob_moder, PeripheralId::GPIOB, "GPIOB", "MODER", 0u, nullptr, -1},
  {RegisterId::register_gpiob_afrl, PeripheralId::GPIOB, "GPIOB", "AFRL", 32u, nullptr, -1},
  {RegisterId::register_gpiob_afrh, PeripheralId::GPIOB, "GPIOB", "AFRH", 36u, nullptr, -1},
  {RegisterId::register_rcc_ioprstr, PeripheralId::RCC, "RCC", "IOPRSTR", 36u, nullptr, -1},
  {RegisterId::register_rcc_ahbrstr, PeripheralId::RCC, "RCC", "AHBRSTR", 40u, nullptr, -1},
  {RegisterId::register_rcc_apbrstr1, PeripheralId::RCC, "RCC", "APBRSTR1", 44u, nullptr, -1},
  {RegisterId::register_rcc_apbrstr2, PeripheralId::RCC, "RCC", "APBRSTR2", 48u, nullptr, -1},
  {RegisterId::register_rcc_iopenr, PeripheralId::RCC, "RCC", "IOPENR", 52u, nullptr, -1},
  {RegisterId::register_rcc_ahbenr, PeripheralId::RCC, "RCC", "AHBENR", 56u, nullptr, -1},
  {RegisterId::register_rcc_apbenr1, PeripheralId::RCC, "RCC", "APBENR1", 60u, nullptr, -1},
  {RegisterId::register_rcc_apbenr2, PeripheralId::RCC, "RCC", "APBENR2", 64u, nullptr, -1},
  {RegisterId::register_usart1_cr1, PeripheralId::USART1, "USART1", "CR1", 0u, nullptr, -1},
  {RegisterId::register_usart1_cr2, PeripheralId::USART1, "USART1", "CR2", 4u, nullptr, -1},
  {RegisterId::register_usart1_brr, PeripheralId::USART1, "USART1", "BRR", 12u, nullptr, -1},
  {RegisterId::register_usart1_isr, PeripheralId::USART1, "USART1", "ISR", 28u, nullptr, -1},
  {RegisterId::register_usart1_rdr, PeripheralId::USART1, "USART1", "RDR", 36u, nullptr, -1},
  {RegisterId::register_usart1_tdr, PeripheralId::USART1, "USART1", "TDR", 40u, nullptr, -1},
}};
}
}
}
}
}
