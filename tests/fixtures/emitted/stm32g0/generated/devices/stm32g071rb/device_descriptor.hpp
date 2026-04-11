#pragma once

namespace st {
namespace stm32g0 {
namespace generated {
namespace devices {
namespace stm32g071rb {
struct DeviceDescriptor {
  const char* vendor;
  const char* family;
  const char* device;
  const char* package_name;
  const char* core;
  const char* summary;
  int pin_count;
  int peripheral_count;
  int interrupt_count;
  int memory_region_count;
  int capability_overlay_count;
  int startup_descriptor_count;
};
inline constexpr DeviceDescriptor kDeviceDescriptor = {
  "st",
  "stm32g0",
  "stm32g071rb",
  "lqfp64",
  "cortex-m0plus",
  "Representative mid-range bootstrap device.",
  6,
  6,
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
