// Generated startup metadata bootstrap unit.
#include <cstdint>

namespace st {
namespace stm32g0 {
namespace stm32g071rb {
struct InterruptDescriptor {
  const char* name;
  int line;
  const char* peripheral;
};
inline constexpr InterruptDescriptor kInterruptTable[] = {
  {"RCC_CRS", 4, "RCC"},
  {"DMA1_Channel1", 9, "DMA1"},
  {"DMA1_Channel2_3", 10, "DMA1"},
  {"USART1", 27, "USART1"},
};
}
}
}
