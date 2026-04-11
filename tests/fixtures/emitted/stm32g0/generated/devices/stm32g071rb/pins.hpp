#pragma once

#include <array>

namespace st {
namespace stm32g0 {
namespace generated {
namespace devices {
namespace stm32g071rb {
struct PinDescriptor {
  const char* pin_name;
  const char* port;
  int number;
  const char* package_pad_ids;
  const char* constraint_ids;
};
inline constexpr std::array<PinDescriptor, 6> kPins = {{
  {"PA0", "A", 0, "17", ""},
  {"PA1", "A", 1, "18", ""},
  {"PA2", "A", 2, "19", ""},
  {"PA3", "A", 3, "20", ""},
  {"PB6", "B", 6, "29", ""},
  {"PB7", "B", 7, "30", ""},
}};

struct PinSignalDescriptor {
  const char* pin_name;
  const char* function;
  const char* peripheral;
  const char* signal;
  int af_number;
};
inline constexpr std::array<PinSignalDescriptor, 8> kPinSignals = {{
  {"PA0", "gpio", "GPIOA", "IN0", -1},
  {"PA1", "gpio", "GPIOA", "IN1", -1},
  {"PA2", "gpio", "GPIOA", "IN2", -1},
  {"PA3", "gpio", "GPIOA", "IN3", -1},
  {"PB6", "gpio", "GPIOB", "IN6", -1},
  {"PB6", "usart1_tx", "USART1", "TX", 0},
  {"PB7", "gpio", "GPIOB", "IN7", -1},
  {"PB7", "usart1_rx", "USART1", "RX", 0},
}};
}
}
}
}
}
