#pragma once

#include "../../runtime_refs.hpp"
#include "../../runtime_semantics.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
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
  PackageRefId::mimxrt1062_bga196,
  CoreId::core_cortex_m7f,
  4,
  7,
  4,
  1,
  10,
  4,
};
}
}
}
}
}
