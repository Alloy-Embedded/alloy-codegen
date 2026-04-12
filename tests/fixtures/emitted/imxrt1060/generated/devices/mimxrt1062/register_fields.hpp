#pragma once

#include <array>
#include <cstdint>
#include "../../runtime_semantics.hpp"
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
  std::uint16_t bit_offset;
  std::uint16_t bit_width;
  AccessKindId access_id;
};
inline constexpr std::array<RegisterFieldDescriptor, 4> kRegisterFields = {{
  {FieldId::field_gpio1_dr_data, RegisterId::register_gpio1_dr, PeripheralId::GPIO1, 0u, 32u, AccessKindId::none},
  {FieldId::field_gpio4_dr_data, RegisterId::register_gpio4_dr, PeripheralId::GPIO4, 0u, 32u, AccessKindId::none},
  {FieldId::field_lpuart1_baud_sbr, RegisterId::register_lpuart1_baud, PeripheralId::LPUART1, 0u, 13u, AccessKindId::none},
  {FieldId::field_lpuart3_baud_sbr, RegisterId::register_lpuart3_baud, PeripheralId::LPUART3, 0u, 13u, AccessKindId::none},
}};
}
}
}
}
}
