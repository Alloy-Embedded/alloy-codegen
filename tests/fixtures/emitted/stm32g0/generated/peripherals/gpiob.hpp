#pragma once

#include <cstdint>
#include "../clock_tree_lite.hpp"
#include "../runtime_semantics.hpp"

namespace st {
namespace stm32g0 {
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
  BackendSchemaId::schema_alloy_gpio_st_stm32g07x_gpio_v1_0,
  0x50000400u,
  ClockGateId::stm32g071rb_gate_gpiob,
  ResetId::stm32g071rb_reset_gpiob,
};
}
}
}
}
