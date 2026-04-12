#pragma once

#include <cstdint>
#include "../clock_tree_lite.hpp"

namespace nxp {
namespace imxrt1060 {
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
  "mimxrt1062",
  "GPIO4",
  "alloy.gpio.nxp-imxrt-gpio-v1",
  0x401C4000u,
  ClockGateId::mimxrt1062_gate_gpio4,
  ResetId::none,
};
}
}
}
}
