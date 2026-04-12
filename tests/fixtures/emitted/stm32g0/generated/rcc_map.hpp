#pragma once

#include "runtime_refs.hpp"
#include "clock_tree_lite.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
struct RccDescriptor {
  DeviceRefId device_id;
  PeripheralRefId peripheral_id;
  ClockGateId gate_id;
  ResetId reset_id;
};
inline constexpr RccDescriptor kRccMap[] = {
  {DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_DMA1, ClockGateId::stm32g071rb_gate_dma1, ResetId::stm32g071rb_reset_dma1},
  {DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_DMAMUX1, ClockGateId::stm32g071rb_gate_dmamux1, ResetId::stm32g071rb_reset_dmamux1},
  {DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_GPIOA, ClockGateId::stm32g071rb_gate_gpioa, ResetId::stm32g071rb_reset_gpioa},
  {DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_GPIOB, ClockGateId::stm32g071rb_gate_gpiob, ResetId::stm32g071rb_reset_gpiob},
  {DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_USART1, ClockGateId::stm32g071rb_gate_usart1, ResetId::stm32g071rb_reset_usart1},
};
}
}
}
