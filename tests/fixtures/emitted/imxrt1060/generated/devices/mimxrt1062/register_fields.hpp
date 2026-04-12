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
  field_ccm_cbcmr_lpspi_clk_sel,
  field_ccm_ccgr0_cg6,
  field_ccm_ccgr0_cg14,
  field_ccm_ccgr0_cg15,
  field_ccm_ccgr1_cg0,
  field_ccm_ccgr1_cg1,
  field_ccm_ccgr1_cg2,
  field_ccm_ccgr1_cg3,
  field_ccm_ccgr1_cg12,
  field_ccm_ccgr1_cg13,
  field_ccm_ccgr1_cg15,
  field_ccm_ccgr2_cg2,
  field_ccm_ccgr2_cg3,
  field_ccm_ccgr2_cg4,
  field_ccm_ccgr2_cg13,
  field_ccm_ccgr3_cg1,
  field_ccm_ccgr3_cg3,
  field_ccm_ccgr3_cg13,
  field_ccm_ccgr5_cg12,
  field_ccm_ccgr5_cg13,
  field_ccm_ccgr6_cg5,
  field_ccm_ccgr6_cg7,
  field_ccm_ccgr6_cg12,
  field_ccm_ccgr7_cg3,
  field_ccm_cscdr1_uart_clk_sel,
  field_ccm_cscdr2_lpi2c_clk_sel,
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
inline constexpr std::array<RegisterFieldDescriptor, 30> kRegisterFields = {{
  {FieldId::field_ccm_cbcmr_lpspi_clk_sel, RegisterId::register_ccm_cbcmr, PeripheralId::CCM, 4u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr0_cg6, RegisterId::register_ccm_ccgr0, PeripheralId::CCM, 12u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr0_cg14, RegisterId::register_ccm_ccgr0, PeripheralId::CCM, 28u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr0_cg15, RegisterId::register_ccm_ccgr0, PeripheralId::CCM, 30u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr1_cg0, RegisterId::register_ccm_ccgr1, PeripheralId::CCM, 0u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr1_cg1, RegisterId::register_ccm_ccgr1, PeripheralId::CCM, 2u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr1_cg2, RegisterId::register_ccm_ccgr1, PeripheralId::CCM, 4u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr1_cg3, RegisterId::register_ccm_ccgr1, PeripheralId::CCM, 6u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr1_cg12, RegisterId::register_ccm_ccgr1, PeripheralId::CCM, 24u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr1_cg13, RegisterId::register_ccm_ccgr1, PeripheralId::CCM, 26u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr1_cg15, RegisterId::register_ccm_ccgr1, PeripheralId::CCM, 30u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr2_cg2, RegisterId::register_ccm_ccgr2, PeripheralId::CCM, 4u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr2_cg3, RegisterId::register_ccm_ccgr2, PeripheralId::CCM, 6u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr2_cg4, RegisterId::register_ccm_ccgr2, PeripheralId::CCM, 8u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr2_cg13, RegisterId::register_ccm_ccgr2, PeripheralId::CCM, 26u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr3_cg1, RegisterId::register_ccm_ccgr3, PeripheralId::CCM, 2u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr3_cg3, RegisterId::register_ccm_ccgr3, PeripheralId::CCM, 6u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr3_cg13, RegisterId::register_ccm_ccgr3, PeripheralId::CCM, 26u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr5_cg12, RegisterId::register_ccm_ccgr5, PeripheralId::CCM, 24u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr5_cg13, RegisterId::register_ccm_ccgr5, PeripheralId::CCM, 26u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr6_cg5, RegisterId::register_ccm_ccgr6, PeripheralId::CCM, 10u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr6_cg7, RegisterId::register_ccm_ccgr6, PeripheralId::CCM, 14u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr6_cg12, RegisterId::register_ccm_ccgr6, PeripheralId::CCM, 24u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_ccgr7_cg3, RegisterId::register_ccm_ccgr7, PeripheralId::CCM, 6u, 2u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_cscdr1_uart_clk_sel, RegisterId::register_ccm_cscdr1, PeripheralId::CCM, 6u, 1u, AccessKindId::access_kind_read_write},
  {FieldId::field_ccm_cscdr2_lpi2c_clk_sel, RegisterId::register_ccm_cscdr2, PeripheralId::CCM, 18u, 1u, AccessKindId::access_kind_read_write},
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
