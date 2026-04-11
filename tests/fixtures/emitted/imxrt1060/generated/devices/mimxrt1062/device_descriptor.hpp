#pragma once

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
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
  "nxp",
  "imxrt1060",
  "mimxrt1062",
  "bga196",
  "cortex-m7f",
  "NXP MIMXRT1062DVL6B i.MX RT1060 Crossover MCU with 1 MB OCRAM.",
  4,
  6,
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
