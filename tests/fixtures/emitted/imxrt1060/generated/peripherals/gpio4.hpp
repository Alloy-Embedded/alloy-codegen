#pragma once

#include <cstdint>
#include "../clock_tree_lite.hpp"
#include "../runtime_semantics.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace peripherals {
struct PeripheralDescriptor {
  PeripheralClassId peripheral_class_id;
  BackendSchemaId schema_id;
  std::uintptr_t base_address;
  ClockGateId clock_gate_id;
  ResetId reset_id;
};
inline constexpr PeripheralDescriptor kPeripheral = {
  PeripheralClassId::class_gpio,
  BackendSchemaId::schema_alloy_gpio_nxp_imxrt_gpio_v1,
  0x401C4000u,
  ClockGateId::mimxrt1062_gate_gpio4,
  ResetId::none,
};
}
}
}
}
