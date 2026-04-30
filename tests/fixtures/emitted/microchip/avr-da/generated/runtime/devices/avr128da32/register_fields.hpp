#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "registers.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
enum class FieldId : std::uint16_t {
  none,
  field_spi0_ctrla_enable,
  field_spi0_ctrla_clk2x,
  field_spi0_ctrla_master,
  field_spi0_ctrlb_ssd,
  field_tca0_ctrla_enable,
  field_tca0_ctrla_clksel,
  field_twi0_ctrla_fmpen,
  field_twi0_ctrla_sdahold,
  field_twi0_mctrla_enable,
  field_twi0_mctrla_smen,
  field_usart0_ctrla_dreie,
  field_usart0_ctrla_txcie,
  field_usart0_ctrla_rxcie,
  field_usart0_ctrlb_txen,
  field_usart0_ctrlb_rxen,
  field_usart0_status_dreif,
  field_usart0_status_txcif,
  field_usart0_status_rxcif,
  field_usart1_ctrla_dreie,
  field_usart1_ctrla_txcie,
  field_usart1_ctrla_rxcie,
  field_usart1_ctrlb_txen,
  field_usart1_ctrlb_rxen,
  field_usart1_status_dreif,
  field_usart1_status_txcif,
  field_usart1_status_rxcif,
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
struct RegisterFieldTraits<FieldId::field_spi0_ctrla_enable> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrla;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrla_clk2x> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrla;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrla_master> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrla;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrlb_ssd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrlb;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_tca0_ctrla_enable> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_tca0_ctrla;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_tca0_ctrla_clksel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_tca0_ctrla;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_twi0_ctrla_fmpen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_twi0_ctrla;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_twi0_ctrla_sdahold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_twi0_ctrla;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_twi0_mctrla_enable> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_twi0_mctrla;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_twi0_mctrla_smen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_twi0_mctrla;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart0_ctrla_dreie> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart0_ctrla;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart0_ctrla_txcie> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart0_ctrla;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart0_ctrla_rxcie> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart0_ctrla;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart0_ctrlb_txen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart0_ctrlb;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart0_ctrlb_rxen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart0_ctrlb;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart0_status_dreif> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart0_status;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart0_status_txcif> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart0_status;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart0_status_rxcif> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart0_status;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart1_ctrla_dreie> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart1_ctrla;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart1_ctrla_txcie> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart1_ctrla;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart1_ctrla_rxcie> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart1_ctrla;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart1_ctrlb_txen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart1_ctrlb;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart1_ctrlb_rxen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart1_ctrlb;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart1_status_dreif> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart1_status;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart1_status_txcif> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart1_status;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

template<>
struct RegisterFieldTraits<FieldId::field_usart1_status_rxcif> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_usart1_status;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_rw;
};

inline constexpr std::array<FieldId, 26> kRegisterFields = {{
  FieldId::field_spi0_ctrla_enable,
  FieldId::field_spi0_ctrla_clk2x,
  FieldId::field_spi0_ctrla_master,
  FieldId::field_spi0_ctrlb_ssd,
  FieldId::field_tca0_ctrla_enable,
  FieldId::field_tca0_ctrla_clksel,
  FieldId::field_twi0_ctrla_fmpen,
  FieldId::field_twi0_ctrla_sdahold,
  FieldId::field_twi0_mctrla_enable,
  FieldId::field_twi0_mctrla_smen,
  FieldId::field_usart0_ctrla_dreie,
  FieldId::field_usart0_ctrla_txcie,
  FieldId::field_usart0_ctrla_rxcie,
  FieldId::field_usart0_ctrlb_txen,
  FieldId::field_usart0_ctrlb_rxen,
  FieldId::field_usart0_status_dreif,
  FieldId::field_usart0_status_txcif,
  FieldId::field_usart0_status_rxcif,
  FieldId::field_usart1_ctrla_dreie,
  FieldId::field_usart1_ctrla_txcie,
  FieldId::field_usart1_ctrla_rxcie,
  FieldId::field_usart1_ctrlb_txen,
  FieldId::field_usart1_ctrlb_rxen,
  FieldId::field_usart1_status_dreif,
  FieldId::field_usart1_status_txcif,
  FieldId::field_usart1_status_rxcif,
}};
}
}
}
}
}
}
