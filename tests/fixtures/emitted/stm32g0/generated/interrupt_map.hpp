#pragma once

namespace st {
namespace stm32g0 {
namespace generated {
struct InterruptDescriptor {
  const char* device;
  const char* interrupt_name;
  int line;
  const char* peripheral;
  const char* shared_group;
  const char* alias_names;
  int vector_slot;
  const char* symbol_name;
};
inline constexpr InterruptDescriptor kInterruptMap[] = {
  {"stm32g071rb", "RCC_CRS", 4, "RCC", nullptr, "RCC_CRS_IRQHandler", 20, "RCC_CRS_IRQHandler"},
  {"stm32g071rb", "DMA1_Channel1", 9, "DMA1", "interrupt-group:dma1", "DMA1_Channel1_IRQHandler", 25, "DMA1_Channel1_IRQHandler"},
  {"stm32g071rb", "DMA1_Channel2_3", 10, "DMA1", "interrupt-group:dma1", "DMA1_Channel2_3_IRQHandler", 26, "DMA1_Channel2_3_IRQHandler"},
  {"stm32g071rb", "USART1", 27, "USART1", nullptr, "USART1_IRQHandler", 43, "USART1_IRQHandler"},
};
}
}
}
