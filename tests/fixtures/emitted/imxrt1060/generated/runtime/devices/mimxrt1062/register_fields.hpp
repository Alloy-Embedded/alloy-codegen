#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "registers.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
enum class FieldId : std::uint16_t {
  none,
  field_ccm_cbcmr_lpspi_clk_sel,
  field_ccm_ccgr0_cg6,
  field_ccm_ccgr1_cg0,
  field_ccm_ccgr1_cg13,
  field_ccm_ccgr3_cg13,
  field_ccm_ccgr5_cg12,
  field_ccm_cscdr1_uart_clk_sel,
  field_gpio1_dr_data,
  field_gpio4_dr_data,
  field_lpuart1_baud_sbr,
  field_lpuart3_baud_sbr,
};

template<FieldId Id>
struct RegisterFieldTraits {
  static constexpr bool kPresent = false;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_ccm_cbcmr_lpspi_clk_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_cbcmr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_ccm_ccgr0_cg6> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr0;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_ccm_ccgr1_cg0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_ccm_ccgr1_cg13> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_ccm_ccgr3_cg13> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr3;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_ccm_ccgr5_cg12> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr5;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_ccm_cscdr1_uart_clk_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_cscdr1;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio1_dr_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio1_dr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio4_dr_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio4_dr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_lpuart1_baud_sbr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_lpuart1_baud;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 13u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_lpuart3_baud_sbr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_lpuart3_baud;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 13u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

inline constexpr std::array<FieldId, 11> kRegisterFields = {{
  FieldId::field_ccm_cbcmr_lpspi_clk_sel,
  FieldId::field_ccm_ccgr0_cg6,
  FieldId::field_ccm_ccgr1_cg0,
  FieldId::field_ccm_ccgr1_cg13,
  FieldId::field_ccm_ccgr3_cg13,
  FieldId::field_ccm_ccgr5_cg12,
  FieldId::field_ccm_cscdr1_uart_clk_sel,
  FieldId::field_gpio1_dr_data,
  FieldId::field_gpio4_dr_data,
  FieldId::field_lpuart1_baud_sbr,
  FieldId::field_lpuart3_baud_sbr,
}};
}
}
}
}
}
}
