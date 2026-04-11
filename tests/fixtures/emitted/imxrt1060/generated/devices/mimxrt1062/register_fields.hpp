#pragma once

#include <array>
#include <cstdint>
#include "register_map.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
enum class FieldId : std::uint16_t {
  field_gpio1_dr_data,
  field_gpio4_dr_data,
  field_lpuart1_baud_sbr,
  field_lpuart3_baud_sbr,
};

struct RegisterFieldDescriptor {
  FieldId field_id;
  RegisterId register_id;
  PeripheralId peripheral_id;
  const char* peripheral_name;
  const char* register_name;
  const char* field_name;
  std::uint16_t bit_offset;
  std::uint16_t bit_width;
  const char* access;
};
inline constexpr std::array<RegisterFieldDescriptor, 4> kRegisterFields = {{
  {FieldId::field_gpio1_dr_data, RegisterId::register_gpio1_dr, PeripheralId::GPIO1, "GPIO1", "DR", "DATA", 0u, 32u, nullptr},
  {FieldId::field_gpio4_dr_data, RegisterId::register_gpio4_dr, PeripheralId::GPIO4, "GPIO4", "DR", "DATA", 0u, 32u, nullptr},
  {FieldId::field_lpuart1_baud_sbr, RegisterId::register_lpuart1_baud, PeripheralId::LPUART1, "LPUART1", "BAUD", "SBR", 0u, 13u, nullptr},
  {FieldId::field_lpuart3_baud_sbr, RegisterId::register_lpuart3_baud, PeripheralId::LPUART3, "LPUART3", "BAUD", "SBR", 0u, 13u, nullptr},
}};
}
}
}
}
}
