#pragma once

#include <array>
#include <cstdint>
#include "clock_tree_lite.hpp"
#include "runtime_refs.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
enum class PackageRefId : std::uint16_t {
  none,
  mimxrt1062_bga196,
};

enum class StateRefId : std::uint16_t {
  none,
  selected,
};

enum class PinRefId : std::uint16_t {
  none,
  mimxrt1062_GPIO_AD_B0_00,
  mimxrt1062_GPIO_AD_B0_01,
  mimxrt1062_GPIO_EMC_00,
  mimxrt1062_GPIO_EMC_01,
};

enum class ConstraintRefId : std::uint16_t {
  none,
};

enum class SelectorRefId : std::uint16_t {
  none,
  mimxrt1062_selector_0,
  mimxrt1062_selector_2,
  mimxrt1062_selector_5,
};

enum class RegisterRefId : std::uint16_t {
  none,
  mimxrt1062_register_gpio1_dr,
  mimxrt1062_register_gpio1_gdir,
  mimxrt1062_register_gpio1_psr,
  mimxrt1062_register_gpio4_dr,
  mimxrt1062_register_gpio4_gdir,
  mimxrt1062_register_gpio4_psr,
  mimxrt1062_register_lpuart1_baud,
  mimxrt1062_register_lpuart1_ctrl,
  mimxrt1062_register_lpuart1_data,
  mimxrt1062_register_lpuart1_stat,
  mimxrt1062_register_lpuart3_baud,
  mimxrt1062_register_lpuart3_ctrl,
  mimxrt1062_register_lpuart3_data,
  mimxrt1062_register_lpuart3_stat,
};

enum class RegisterFieldRefId : std::uint16_t {
  none,
  mimxrt1062_field_gpio1_dr_data,
  mimxrt1062_field_gpio4_dr_data,
  mimxrt1062_field_lpuart1_baud_sbr,
  mimxrt1062_field_lpuart3_baud_sbr,
};

struct PackageRefDescriptor {
  PackageRefId package_id;
  const char* device;
  const char* package_name;
};
inline constexpr std::array<PackageRefDescriptor, 2> kPackageRefs = {{
  {PackageRefId::none, nullptr, nullptr},
  {PackageRefId::mimxrt1062_bga196, "mimxrt1062", "bga196"},
}};

struct StateRefDescriptor {
  StateRefId state_id;
  const char* state_name;
};
inline constexpr std::array<StateRefDescriptor, 2> kStateRefs = {{
  {StateRefId::none, nullptr},
  {StateRefId::selected, "selected"},
}};

struct PinRefDescriptor {
  PinRefId pin_id;
  const char* device;
  const char* pin_name;
  const char* port;
  int pin_number;
};
inline constexpr std::array<PinRefDescriptor, 5> kPinRefs = {{
  {PinRefId::none, nullptr, nullptr, nullptr, -1},
  {PinRefId::mimxrt1062_GPIO_AD_B0_00, "mimxrt1062", "GPIO_AD_B0_00", nullptr, 0},
  {PinRefId::mimxrt1062_GPIO_AD_B0_01, "mimxrt1062", "GPIO_AD_B0_01", nullptr, 1},
  {PinRefId::mimxrt1062_GPIO_EMC_00, "mimxrt1062", "GPIO_EMC_00", nullptr, 0},
  {PinRefId::mimxrt1062_GPIO_EMC_01, "mimxrt1062", "GPIO_EMC_01", nullptr, 1},
}};

struct ConstraintRefDescriptor {
  ConstraintRefId constraint_id;
  const char* device;
  PinRefId pin_id;
  const char* kind;
  const char* value;
};
inline constexpr std::array<ConstraintRefDescriptor, 1> kConstraintRefs = {{
  {ConstraintRefId::none, nullptr, PinRefId::none, nullptr, nullptr},
}};

struct SelectorRefDescriptor {
  SelectorRefId selector_id;
  const char* device;
  const char* selector_name;
  int selector_value;
};
inline constexpr std::array<SelectorRefDescriptor, 4> kSelectorRefs = {{
  {SelectorRefId::none, nullptr, nullptr, -1},
  {SelectorRefId::mimxrt1062_selector_0, "mimxrt1062", "selector:0", 0},
  {SelectorRefId::mimxrt1062_selector_2, "mimxrt1062", "selector:2", 2},
  {SelectorRefId::mimxrt1062_selector_5, "mimxrt1062", "selector:5", 5},
}};

struct RegisterRefDescriptor {
  RegisterRefId register_id;
  const char* device;
  const char* peripheral_name;
  const char* register_name;
  std::uint32_t offset_bytes;
};
inline constexpr std::array<RegisterRefDescriptor, 15> kRegisterRefs = {{
  {RegisterRefId::none, nullptr, nullptr, nullptr, 0u},
  {RegisterRefId::mimxrt1062_register_gpio1_dr, "mimxrt1062", "GPIO1", "DR", 0u},
  {RegisterRefId::mimxrt1062_register_gpio1_gdir, "mimxrt1062", "GPIO1", "GDIR", 4u},
  {RegisterRefId::mimxrt1062_register_gpio1_psr, "mimxrt1062", "GPIO1", "PSR", 8u},
  {RegisterRefId::mimxrt1062_register_gpio4_dr, "mimxrt1062", "GPIO4", "DR", 0u},
  {RegisterRefId::mimxrt1062_register_gpio4_gdir, "mimxrt1062", "GPIO4", "GDIR", 4u},
  {RegisterRefId::mimxrt1062_register_gpio4_psr, "mimxrt1062", "GPIO4", "PSR", 8u},
  {RegisterRefId::mimxrt1062_register_lpuart1_baud, "mimxrt1062", "LPUART1", "BAUD", 16u},
  {RegisterRefId::mimxrt1062_register_lpuart1_ctrl, "mimxrt1062", "LPUART1", "CTRL", 24u},
  {RegisterRefId::mimxrt1062_register_lpuart1_data, "mimxrt1062", "LPUART1", "DATA", 28u},
  {RegisterRefId::mimxrt1062_register_lpuart1_stat, "mimxrt1062", "LPUART1", "STAT", 20u},
  {RegisterRefId::mimxrt1062_register_lpuart3_baud, "mimxrt1062", "LPUART3", "BAUD", 16u},
  {RegisterRefId::mimxrt1062_register_lpuart3_ctrl, "mimxrt1062", "LPUART3", "CTRL", 24u},
  {RegisterRefId::mimxrt1062_register_lpuart3_data, "mimxrt1062", "LPUART3", "DATA", 28u},
  {RegisterRefId::mimxrt1062_register_lpuart3_stat, "mimxrt1062", "LPUART3", "STAT", 20u},
}};

struct RegisterFieldRefDescriptor {
  RegisterFieldRefId field_id;
  const char* device;
  RegisterRefId register_id;
  const char* peripheral_name;
  const char* field_name;
  std::uint16_t bit_offset;
  std::uint16_t bit_width;
};
inline constexpr std::array<RegisterFieldRefDescriptor, 5> kRegisterFieldRefs = {{
  {RegisterFieldRefId::none, nullptr, RegisterRefId::none, nullptr, nullptr, 0u, 0u},
  {RegisterFieldRefId::mimxrt1062_field_gpio1_dr_data, "mimxrt1062", RegisterRefId::mimxrt1062_register_gpio1_dr, "GPIO1", "DATA", 0u, 32u},
  {RegisterFieldRefId::mimxrt1062_field_gpio4_dr_data, "mimxrt1062", RegisterRefId::mimxrt1062_register_gpio4_dr, "GPIO4", "DATA", 0u, 32u},
  {RegisterFieldRefId::mimxrt1062_field_lpuart1_baud_sbr, "mimxrt1062", RegisterRefId::mimxrt1062_register_lpuart1_baud, "LPUART1", "SBR", 0u, 13u},
  {RegisterFieldRefId::mimxrt1062_field_lpuart3_baud_sbr, "mimxrt1062", RegisterRefId::mimxrt1062_register_lpuart3_baud, "LPUART3", "SBR", 0u, 13u},
}};
}
}
}
