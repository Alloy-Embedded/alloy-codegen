#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "registers.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
enum class FieldId : std::uint16_t {
  none,
  field_adc_cs_en,
  field_adc_cs_ainsel,
  field_dma_ch0_ctrl_trig_en,
  field_dma_ch0_ctrl_trig_chain_to,
  field_dma_ch0_ctrl_trig_treq_sel,
  field_i2c0_ic_con_master_mode,
  field_resets_reset_adc,
  field_resets_reset_dma,
  field_resets_reset_i2c0,
  field_resets_reset_i2c1,
  field_resets_reset_pwm,
  field_resets_reset_rtc,
  field_resets_reset_spi0,
  field_resets_reset_spi1,
  field_resets_reset_timer,
  field_resets_reset_uart0,
  field_resets_reset_uart1,
  field_spi0_sspcr0_dss,
  field_uart0_uartdr_data,
  field_uart1_uartdr_data,
  field_watchdog_ctrl_time,
  field_watchdog_ctrl_enable,
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
struct RegisterFieldTraits<FieldId::field_adc_cs_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_adc_cs;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_adc_cs_ainsel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_adc_cs;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_ch0_ctrl_trig_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_ch0_ctrl_trig;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_ch0_ctrl_trig_chain_to> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_ch0_ctrl_trig;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_ch0_ctrl_trig_treq_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_ch0_ctrl_trig;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ic_con_master_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ic_con;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_resets_reset_adc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_resets_reset_dma> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_resets_reset_i2c0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_resets_reset_i2c1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_resets_reset_pwm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_resets_reset_rtc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_resets_reset_spi0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_resets_reset_spi1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_resets_reset_timer> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_resets_reset_uart0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_resets_reset_uart1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_sspcr0_dss> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_sspcr0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_uartdr_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_uartdr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_uartdr_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_uartdr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_watchdog_ctrl_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_watchdog_ctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

template<>
struct RegisterFieldTraits<FieldId::field_watchdog_ctrl_enable> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_watchdog_ctrl;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
};

inline constexpr std::array<FieldId, 22> kRegisterFields = {{
  FieldId::field_adc_cs_en,
  FieldId::field_adc_cs_ainsel,
  FieldId::field_dma_ch0_ctrl_trig_en,
  FieldId::field_dma_ch0_ctrl_trig_chain_to,
  FieldId::field_dma_ch0_ctrl_trig_treq_sel,
  FieldId::field_i2c0_ic_con_master_mode,
  FieldId::field_resets_reset_adc,
  FieldId::field_resets_reset_dma,
  FieldId::field_resets_reset_i2c0,
  FieldId::field_resets_reset_i2c1,
  FieldId::field_resets_reset_pwm,
  FieldId::field_resets_reset_rtc,
  FieldId::field_resets_reset_spi0,
  FieldId::field_resets_reset_spi1,
  FieldId::field_resets_reset_timer,
  FieldId::field_resets_reset_uart0,
  FieldId::field_resets_reset_uart1,
  FieldId::field_spi0_sspcr0_dss,
  FieldId::field_uart0_uartdr_data,
  FieldId::field_uart1_uartdr_data,
  FieldId::field_watchdog_ctrl_time,
  FieldId::field_watchdog_ctrl_enable,
}};
}
}
}
}
}
}
