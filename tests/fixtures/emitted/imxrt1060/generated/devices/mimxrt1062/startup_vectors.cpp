// Generated descriptor-only startup vector unit.

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
struct StartupVectorDescriptor {
  int slot;
  const char* symbol_name;
};
inline constexpr StartupVectorDescriptor kStartupVectorTable[] = {
  {0, "__stack_top"},
  {1, "Reset_Handler"},
  {2, "NMI_Handler"},
  {3, "HardFault_Handler"},
  {4, "MemManage_Handler"},
  {5, "BusFault_Handler"},
  {6, "UsageFault_Handler"},
  {7, "Reserved_Handler_7"},
  {8, "Reserved_Handler_8"},
  {9, "Reserved_Handler_9"},
  {10, "Reserved_Handler_10"},
  {11, "SVCall_Handler"},
  {12, "DebugMon_Handler"},
  {13, "Reserved_Handler_13"},
  {14, "PendSV_Handler"},
  {15, "SysTick_Handler"},
  {36, "LPUART1_IRQHandler"},
  {38, "LPUART3_IRQHandler"},
  {44, "LPI2C1_IRQHandler"},
  {48, "LPSPI1_IRQHandler"},
};
}
}
}
}
}
