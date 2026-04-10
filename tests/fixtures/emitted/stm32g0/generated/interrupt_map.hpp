#pragma once

namespace st {
namespace stm32g0 {
namespace generated {
struct InterruptDescriptor {
  const char* device;
  const char* interrupt_name;
  int line;
  const char* peripheral;
  int vector_slot;
  const char* symbol_name;
};
inline constexpr InterruptDescriptor kInterruptMap[] = {
  {"stm32g071rb", "RCC_CRS", 4, "RCC", 20, "RCC_CRS_IRQHandler"},
  {"stm32g071rb", "DMA1_Channel1", 9, "DMA1", 25, "DMA1_Channel1_IRQHandler"},
  {"stm32g071rb", "DMA1_Channel2_3", 10, "DMA1", 26, "DMA1_Channel2_3_IRQHandler"},
  {"stm32g071rb", "USART1", 27, "USART1", 43, "USART1_IRQHandler"},
};
}
}
}
