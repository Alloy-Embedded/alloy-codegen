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
  {"PA1", "gpio", "GPIOA", "IN1", -1},
  {"PA2", "gpio", "GPIOA", "IN2", -1},
  {"PA3", "gpio", "GPIOA", "IN3", -1},
  {"PB6", "gpio", "GPIOB", "IN6", -1},
  {"PB6", "usart1_tx", "USART1", "TX", 0},
  {"PB7", "gpio", "GPIOB", "IN7", -1},
  {"PB7", "usart1_rx", "USART1", "RX", 0},
};
}
}
}
