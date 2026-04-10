#pragma once

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
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
  {4, "MemManage_Handler", nullptr, "system-exception"},
  {5, "BusFault_Handler", nullptr, "system-exception"},
  {6, "UsageFault_Handler", nullptr, "system-exception"},
  {7, "Reserved_Handler_7", nullptr, "reserved"},
  {8, "Reserved_Handler_8", nullptr, "reserved"},
  {9, "Reserved_Handler_9", nullptr, "reserved"},
  {10, "Reserved_Handler_10", nullptr, "reserved"},
  {11, "SVCall_Handler", nullptr, "system-exception"},
  {12, "DebugMon_Handler", nullptr, "system-exception"},
  {13, "Reserved_Handler_13", nullptr, "reserved"},
  {14, "PendSV_Handler", nullptr, "system-exception"},
  {15, "SysTick_Handler", nullptr, "system-exception"},
  {36, "LPUART1_IRQHandler", "LPUART1", "external-interrupt"},
  {38, "LPUART3_IRQHandler", "LPUART3", "external-interrupt"},
  {44, "LPI2C1_IRQHandler", "LPI2C1", "external-interrupt"},
  {48, "LPSPI1_IRQHandler", "LPSPI1", "external-interrupt"},
};

struct StartupDescriptor {
  const char* descriptor_id;
  const char* kind;
  const char* source_region;
  const char* target_region;
  const char* symbol;
};
inline constexpr StartupDescriptor kStartupDescriptors[] = {
  {"startup:copy-target:ocram", "copy-target-region", nullptr, "OCRAM", nullptr},
  {"startup:stack-top", "initial-stack-pointer", nullptr, nullptr, "__stack_top"},
  {"startup:vectors", "vector-table", nullptr, nullptr, "_vectors"},
  {"startup:zero-target:ocram", "zero-target-region", nullptr, "OCRAM", nullptr},
};
}
}
}
}
}
