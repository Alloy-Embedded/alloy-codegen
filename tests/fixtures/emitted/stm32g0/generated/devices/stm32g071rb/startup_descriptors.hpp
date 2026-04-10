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
  {0, "__stack_top", nullptr, "initial-stack-pointer"},
  {1, "Reset_Handler", nullptr, "reset-handler"},
  {2, "NMI_Handler", nullptr, "system-exception"},
  {3, "HardFault_Handler", nullptr, "system-exception"},
  {4, "Reserved_Handler_4", nullptr, "reserved"},
  {5, "Reserved_Handler_5", nullptr, "reserved"},
  {6, "Reserved_Handler_6", nullptr, "reserved"},
  {7, "Reserved_Handler_7", nullptr, "reserved"},
  {8, "Reserved_Handler_8", nullptr, "reserved"},
  {9, "Reserved_Handler_9", nullptr, "reserved"},
  {10, "Reserved_Handler_10", nullptr, "reserved"},
  {11, "SVCall_Handler", nullptr, "system-exception"},
  {12, "Reserved_Handler_12", nullptr, "reserved"},
  {13, "Reserved_Handler_13", nullptr, "reserved"},
  {14, "PendSV_Handler", nullptr, "system-exception"},
  {15, "SysTick_Handler", nullptr, "system-exception"},
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
  {"startup:copy-source:flash", "copy-source-region", "flash", nullptr, nullptr},
  {"startup:copy-target:sram", "copy-target-region", nullptr, "sram", nullptr},
  {"startup:stack-top", "initial-stack-pointer", nullptr, nullptr, "__stack_top"},
  {"startup:vector-source:flash", "vector-source-region", "flash", nullptr, nullptr},
  {"startup:vectors", "vector-table", nullptr, nullptr, "_vectors"},
  {"startup:zero-target:sram", "zero-target-region", nullptr, "sram", nullptr},
};
}
}
}
