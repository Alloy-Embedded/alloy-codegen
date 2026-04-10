#pragma once

namespace st {
namespace stm32g0 {
namespace stm32g071rb {
struct VectorSlotDescriptor {
  int slot;
  const char* symbol_name;
  const char* interrupt_name;
  const char* kind;
};
inline constexpr VectorSlotDescriptor kVectorSlots[] = {
  {20, "RCC_CRS_IRQHandler", "RCC_CRS", "external-interrupt"},
  {25, "DMA1_Channel1_IRQHandler", "DMA1_Channel1", "external-interrupt"},
  {26, "DMA1_Channel2_3_IRQHandler", "DMA1_Channel2_3", "external-interrupt"},
  {43, "USART1_IRQHandler", "USART1", "external-interrupt"},
};

struct StartupDescriptor {
  const char* descriptor_id;
  const char* kind;
  const char* source_region;
  const char* target_region;
  const char* symbol;
};
inline constexpr StartupDescriptor kStartupDescriptors[] = {
  {"startup:memory:flash", "memory-region", "flash", "flash", nullptr},
  {"startup:memory:sram", "memory-region", "sram", "sram", nullptr},
  {"startup:vectors", "vector-table", nullptr, nullptr, "_vectors"},
};
}
}
}
