#pragma once

#include <cstdint>
#include "../clock_tree_lite.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace peripherals {
struct PeripheralDescriptor {
  const char* device;
  const char* name;
  const char* backend_schema_id;
  std::uintptr_t base_address;
  ClockGateId clock_gate_id;
  ResetId reset_id;
};
inline constexpr PeripheralDescriptor kPeripheral = {
  "stm32g071rb",
  "GPIOB",
  "alloy.gpio.st-stm32g07x-gpio-v1-0",
  0x50000400u,
  ClockGateId::stm32g071rb_gate_gpiob,
  ResetId::stm32g071rb_reset_gpiob,
};
}
}
}
}
