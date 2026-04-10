#pragma once

#include <cstdint>

namespace st {
namespace stm32g0 {
namespace generated {
namespace peripherals {
struct PeripheralDescriptor {
  const char* name;
  std::uintptr_t base_address;
  const char* rcc_enable_signal;
  const char* rcc_reset_signal;
};
inline constexpr PeripheralDescriptor kPeripheral = {
  "GPIOB",
  0x50000400u,
  "RCC_IOPENR.GPIOBEN",
  "RCC_IOPRSTR.GPIOBRST",
};
}
}
}
}
