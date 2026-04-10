#pragma once

namespace st {
namespace stm32g0 {
namespace stm32g071rb {
struct PinFunctionDescriptor {
  const char* pin_name;
  const char* function;
  const char* peripheral;
  const char* signal;
  int af_number;
};
inline constexpr PinFunctionDescriptor kPinFunctions[] = {
  {"PA0", "gpio", "GPIOA", "IN0", -1},
  {"PA0", "usart1_tx", "USART1", "TX", 1},
  {"PA1", "gpio", "GPIOA", "IN1", -1},
  {"PA1", "usart1_rx", "USART1", "RX", 1},
  {"PB6", "gpio", "GPIOB", "IN6", -1},
};
}
}
}
