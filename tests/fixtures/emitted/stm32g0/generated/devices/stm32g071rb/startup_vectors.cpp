// Generated descriptor-only startup vector unit.

namespace st {
namespace stm32g0 {
namespace stm32g071rb {
struct StartupVectorDescriptor {
  int slot;
  const char* symbol_name;
};
inline constexpr StartupVectorDescriptor kStartupVectorTable[] = {
  {20, "RCC_CRS_IRQHandler"},
  {25, "DMA1_Channel1_IRQHandler"},
  {26, "DMA1_Channel2_3_IRQHandler"},
  {43, "USART1_IRQHandler"},
};
}
}
}
