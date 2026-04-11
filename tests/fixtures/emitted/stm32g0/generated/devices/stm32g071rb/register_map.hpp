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

struct RegisterDescriptor {
  PeripheralId peripheral_id;
  const char* peripheral_name;
  const char* register_name;
  std::uint32_t offset_bytes;
  const char* access;
  int size_bits;
};
inline constexpr std::array<RegisterDescriptor, 20> kRegisters = {{
  {PeripheralId::GPIOA, "GPIOA", "MODER", 0u, nullptr, -1},
  {PeripheralId::GPIOA, "GPIOA", "AFRL", 32u, nullptr, -1},
  {PeripheralId::GPIOA, "GPIOA", "AFRH", 36u, nullptr, -1},
  {PeripheralId::GPIOB, "GPIOB", "MODER", 0u, nullptr, -1},
  {PeripheralId::GPIOB, "GPIOB", "AFRL", 32u, nullptr, -1},
  {PeripheralId::GPIOB, "GPIOB", "AFRH", 36u, nullptr, -1},
  {PeripheralId::RCC, "RCC", "IOPRSTR", 36u, nullptr, -1},
  {PeripheralId::RCC, "RCC", "AHBRSTR", 40u, nullptr, -1},
  {PeripheralId::RCC, "RCC", "APBRSTR1", 44u, nullptr, -1},
  {PeripheralId::RCC, "RCC", "APBRSTR2", 48u, nullptr, -1},
  {PeripheralId::RCC, "RCC", "IOPENR", 52u, nullptr, -1},
  {PeripheralId::RCC, "RCC", "AHBENR", 56u, nullptr, -1},
  {PeripheralId::RCC, "RCC", "APBENR1", 60u, nullptr, -1},
  {PeripheralId::RCC, "RCC", "APBENR2", 64u, nullptr, -1},
  {PeripheralId::USART1, "USART1", "CR1", 0u, nullptr, -1},
  {PeripheralId::USART1, "USART1", "CR2", 4u, nullptr, -1},
  {PeripheralId::USART1, "USART1", "BRR", 12u, nullptr, -1},
  {PeripheralId::USART1, "USART1", "ISR", 28u, nullptr, -1},
  {PeripheralId::USART1, "USART1", "RDR", 36u, nullptr, -1},
  {PeripheralId::USART1, "USART1", "TDR", 40u, nullptr, -1},
}};
}
}
}
}
}
