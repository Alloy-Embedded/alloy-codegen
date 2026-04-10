// Generated descriptor-only startup vector unit.

namespace st {
namespace stm32g0 {
namespace stm32g071rb {
struct StartupVectorDescriptor {
  int slot;
  const char* symbol_name;
};
inline constexpr StartupVectorDescriptor kStartupVectorTable[] = {
  {0, "__stack_top"},
  {1, "Reset_Handler"},
  {2, "NMI_Handler"},
  {3, "HardFault_Handler"},
  {4, "Reserved_Handler_4"},
  {5, "Reserved_Handler_5"},
  {6, "Reserved_Handler_6"},
  {7, "Reserved_Handler_7"},
  {8, "Reserved_Handler_8"},
  {9, "Reserved_Handler_9"},
  {10, "Reserved_Handler_10"},
  {11, "SVCall_Handler"},
  {12, "Reserved_Handler_12"},
  {13, "Reserved_Handler_13"},
  {14, "PendSV_Handler"},
  {15, "SysTick_Handler"},
  {20, "RCC_CRS_IRQHandler"},
  {25, "DMA1_Channel1_IRQHandler"},
  {26, "DMA1_Channel2_3_IRQHandler"},
  {43, "USART1_IRQHandler"},
};
}
}
}
