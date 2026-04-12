#pragma once

#include "clock_tree_lite.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
struct RccDescriptor {
  const char* device;
  const char* peripheral;
  ClockGateId gate_id;
  ResetId reset_id;
};
inline constexpr RccDescriptor kRccMap[] = {
  {"stm32g071rb", "DMA1", ClockGateId::stm32g071rb_gate_dma1, ResetId::stm32g071rb_reset_dma1},
  {"stm32g071rb", "DMAMUX1", ClockGateId::stm32g071rb_gate_dmamux1, ResetId::stm32g071rb_reset_dmamux1},
  {"stm32g071rb", "GPIOA", ClockGateId::stm32g071rb_gate_gpioa, ResetId::stm32g071rb_reset_gpioa},
  {"stm32g071rb", "GPIOB", ClockGateId::stm32g071rb_gate_gpiob, ResetId::stm32g071rb_reset_gpiob},
  {"stm32g071rb", "USART1", ClockGateId::stm32g071rb_gate_usart1, ResetId::stm32g071rb_reset_usart1},
};
}
}
}
