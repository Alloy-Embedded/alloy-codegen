#pragma once

namespace st {
namespace stm32g0 {
namespace generated {
struct SignalDescriptor {
  const char* peripheral;
  const char* signal;
  const char* pin_name;
  int af_number;
};
inline constexpr SignalDescriptor kSignalMap[] = {
  {"USART1", "RX", "PB7", 0},
  {"USART1", "TX", "PB6", 0},
};
}
}
}
