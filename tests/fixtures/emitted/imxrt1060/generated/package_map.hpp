#pragma once

#include <array>
#include "runtime_refs.hpp"
#include "runtime_semantics.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
struct PackageDescriptor {
  DeviceRefId device_id;
  PackageRefId package_id;
  int pin_count;
};
inline constexpr PackageDescriptor kPackageMap[] = {
  {DeviceRefId::mimxrt1062, PackageRefId::mimxrt1062_bga196, 196},
};

struct PackagePadDescriptor {
  DeviceRefId device_id;
  PackageRefId package_id;
  PackagePadRefId pad_id;
  PinRefId pin_id;
  PackagePadKindId pad_kind_id;
  BondingStateId bonding_state_id;
  int physical_index;
};
inline constexpr PackagePadDescriptor kPackagePads[] = {
  {DeviceRefId::mimxrt1062, PackageRefId::mimxrt1062_bga196, PackagePadRefId::mimxrt1062_GPIO_AD_B0_00, PinRefId::mimxrt1062_GPIO_AD_B0_00, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded, -1},
  {DeviceRefId::mimxrt1062, PackageRefId::mimxrt1062_bga196, PackagePadRefId::mimxrt1062_GPIO_AD_B0_01, PinRefId::mimxrt1062_GPIO_AD_B0_01, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded, -1},
  {DeviceRefId::mimxrt1062, PackageRefId::mimxrt1062_bga196, PackagePadRefId::mimxrt1062_GPIO_EMC_00, PinRefId::mimxrt1062_GPIO_EMC_00, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded, -1},
  {DeviceRefId::mimxrt1062, PackageRefId::mimxrt1062_bga196, PackagePadRefId::mimxrt1062_GPIO_EMC_01, PinRefId::mimxrt1062_GPIO_EMC_01, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded, -1},
};

struct PinConstraintDescriptor {
  DeviceRefId device_id;
  PinRefId pin_id;
  ConstraintRefId constraint_id;
  ConstraintKindId kind_id;
  ConstraintValueId value_id;
};
inline constexpr std::array<PinConstraintDescriptor, 0> kPinConstraints = {};
}
}
}
