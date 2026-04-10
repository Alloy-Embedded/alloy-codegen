#pragma once

#include <array>

namespace nxp {
namespace imxrt1060 {
namespace generated {
struct PackageDescriptor {
  const char* device;
  const char* package_name;
  int pin_count;
};
inline constexpr PackageDescriptor kPackageMap[] = {
  {"mimxrt1062", "bga196", 196},
};

struct PackagePadDescriptor {
  const char* device;
  const char* package_name;
  const char* pad_id;
  const char* position_label;
  int physical_index;
  const char* pad_kind;
  const char* bonded_pin;
  const char* bonding_state;
};
inline constexpr PackagePadDescriptor kPackagePads[] = {
  {"mimxrt1062", "bga196", "GPIO_AD_B0_00", "GPIO_AD_B0_00", -1, "io", "GPIO_AD_B0_00", "bonded"},
  {"mimxrt1062", "bga196", "GPIO_AD_B0_01", "GPIO_AD_B0_01", -1, "io", "GPIO_AD_B0_01", "bonded"},
  {"mimxrt1062", "bga196", "GPIO_EMC_00", "GPIO_EMC_00", -1, "io", "GPIO_EMC_00", "bonded"},
  {"mimxrt1062", "bga196", "GPIO_EMC_01", "GPIO_EMC_01", -1, "io", "GPIO_EMC_01", "bonded"},
};

struct PinConstraintDescriptor {
  const char* device;
  const char* pin_name;
  const char* kind;
  const char* value;
};
inline constexpr std::array<PinConstraintDescriptor, 0> kPinConstraints = {};
}
}
}
