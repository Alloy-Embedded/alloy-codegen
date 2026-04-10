#pragma once

namespace nxp {
namespace imxrt1060 {
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
  {"mimxrt1062", "LPUART1", 20, "LPUART1", nullptr, "LPUART1_IRQHandler", 36, "LPUART1_IRQHandler"},
  {"mimxrt1062", "LPUART3", 22, "LPUART3", nullptr, "LPUART3_IRQHandler", 38, "LPUART3_IRQHandler"},
  {"mimxrt1062", "LPI2C1", 28, "LPI2C1", nullptr, "LPI2C1_IRQHandler", 44, "LPI2C1_IRQHandler"},
  {"mimxrt1062", "LPSPI1", 32, "LPSPI1", nullptr, "LPSPI1_IRQHandler", 48, "LPSPI1_IRQHandler"},
};
}
}
}
