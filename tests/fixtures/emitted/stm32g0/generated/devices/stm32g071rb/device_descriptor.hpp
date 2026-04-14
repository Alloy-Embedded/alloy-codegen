#pragma once

#include "../../runtime_refs.hpp"
#include "../../runtime_semantics.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace devices {
namespace stm32g071rb {
struct DeviceDescriptor {
  PackageRefId package_id;
  CoreId core_id;
  int pin_count;
  int peripheral_count;
  int interrupt_count;
  int memory_region_count;
  int capability_overlay_count;
  int startup_descriptor_count;
};
inline constexpr DeviceDescriptor kDeviceDescriptor = {
  PackageRefId::stm32g071rb_lqfp64,
  CoreId::core_cortex_m0plus,
  6,
  7,
  4,
  2,
  2,
  6,
};
}
}
}
}
}
