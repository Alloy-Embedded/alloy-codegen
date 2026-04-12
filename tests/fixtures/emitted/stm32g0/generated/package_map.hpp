#pragma once

#include <array>
#include "runtime_refs.hpp"
#include "runtime_semantics.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
struct PackageDescriptor {
  DeviceRefId device_id;
  PackageRefId package_id;
  int pin_count;
};
inline constexpr PackageDescriptor kPackageMap[] = {
  {DeviceRefId::stm32g071rb, PackageRefId::stm32g071rb_lqfp64, 64},
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
  {DeviceRefId::stm32g071rb, PackageRefId::stm32g071rb_lqfp64, PackagePadRefId::stm32g071rb_17, PinRefId::stm32g071rb_PA0, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded, 17},
  {DeviceRefId::stm32g071rb, PackageRefId::stm32g071rb_lqfp64, PackagePadRefId::stm32g071rb_18, PinRefId::stm32g071rb_PA1, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded, 18},
  {DeviceRefId::stm32g071rb, PackageRefId::stm32g071rb_lqfp64, PackagePadRefId::stm32g071rb_19, PinRefId::stm32g071rb_PA2, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded, 19},
  {DeviceRefId::stm32g071rb, PackageRefId::stm32g071rb_lqfp64, PackagePadRefId::stm32g071rb_20, PinRefId::stm32g071rb_PA3, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded, 20},
  {DeviceRefId::stm32g071rb, PackageRefId::stm32g071rb_lqfp64, PackagePadRefId::stm32g071rb_29, PinRefId::stm32g071rb_PB6, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded, 29},
  {DeviceRefId::stm32g071rb, PackageRefId::stm32g071rb_lqfp64, PackagePadRefId::stm32g071rb_30, PinRefId::stm32g071rb_PB7, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded, 30},
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
