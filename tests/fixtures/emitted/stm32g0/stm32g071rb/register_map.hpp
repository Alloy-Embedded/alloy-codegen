#pragma once

#include <cstdint>

namespace st {
namespace stm32g0 {
namespace stm32g071rb {
inline constexpr const char* kDevice = "stm32g071rb";
struct PeripheralBase {
  const char* name;
  std::uintptr_t address;
};
inline constexpr PeripheralBase kPeripheralBases[] = {
  {"DMA1", 0x40020000u},
  {"DMAMUX1", 0x40020800u},
  {"GPIOA", 0x50000000u},
  {"GPIOB", 0x50000400u},
  {"RCC", 0x40021000u},
  {"USART1", 0x40013800u},
};
}
}
}
