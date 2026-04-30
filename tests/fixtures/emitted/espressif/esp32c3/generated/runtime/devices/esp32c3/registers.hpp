#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace espressif {
namespace esp32c3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32c3 {
enum class RegisterId : std::uint16_t {
  none,
  register_apb_saradc_ctrl,
  register_apb_saradc_ctrl2,
  register_apb_saradc_filter_ctrl1,
  register_apb_saradc_fsm_wait,
  register_apb_saradc_sar1_status,
  register_apb_saradc_sar2_status,
  register_apb_saradc_sar_patt_tab1,
  register_apb_saradc_sar_patt_tab2,
  register_apb_saradc_onetime_sample,
  register_apb_saradc_arb_ctrl,
  register_apb_saradc_filter_ctrl0,
  register_apb_saradc_sar1data_status,
  register_apb_saradc_sar2data_status,
  register_apb_saradc_thres0_ctrl,
  register_apb_saradc_thres1_ctrl,
  register_apb_saradc_thres_ctrl,
  register_apb_saradc_int_ena,
  register_apb_saradc_int_raw,
  register_apb_saradc_int_st,
  register_apb_saradc_int_clr,
  register_apb_saradc_dma_conf,
  register_apb_saradc_clkm_conf,
  register_apb_saradc_apb_tsens_ctrl,
  register_apb_saradc_tsens_ctrl2,
  register_apb_saradc_cali,
  register_apb_saradc_ctrl_date,
  register_dma_int_raw_ch_s,
  register_dma_int_st_ch0,
  register_dma_int_ena_ch_s,
  register_dma_int_clr_ch_s,
  register_dma_int_st_ch1,
  register_dma_int_st_ch2,
  register_dma_ahb_test,
  register_dma_misc_conf,
  register_dma_date,
  register_dma_in_conf0_ch_s,
  register_dma_in_conf1_ch0,
  register_dma_infifo_status_ch0,
  register_dma_in_pop_ch0,
  register_dma_in_link_ch_s,
  register_dma_in_state_ch0,
  register_dma_in_suc_eof_des_addr_ch0,
  register_dma_in_err_eof_des_addr_ch0,
  register_dma_in_dscr_ch0,
  register_dma_in_dscr_bf0_ch_s,
  register_dma_in_dscr_bf1_ch0,
  register_dma_in_pri_ch_s,
  register_dma_in_peri_sel_ch_s,
  register_dma_out_conf0_ch_s,
  register_dma_out_conf1_ch_s,
  register_dma_outfifo_status_ch0,
  register_dma_out_push_ch0,
  register_dma_out_link_ch_s,
  register_dma_out_state_ch0,
  register_dma_out_eof_des_addr_ch_s,
  register_dma_out_eof_bfr_des_addr_ch0,
  register_dma_out_dscr_ch0,
  register_dma_out_dscr_bf0_ch0,
  register_dma_out_dscr_bf1_ch0,
  register_dma_out_pri_ch_s,
  register_dma_out_peri_sel_ch_s,
  register_dma_in_conf1_ch1,
  register_dma_infifo_status_ch1,
  register_dma_in_pop_ch1,
  register_dma_in_state_ch1,
  register_dma_in_suc_eof_des_addr_ch1,
  register_dma_in_err_eof_des_addr_ch1,
  register_dma_in_dscr_ch1,
  register_dma_in_dscr_bf1_ch1,
  register_dma_outfifo_status_ch1,
  register_dma_out_push_ch1,
  register_dma_out_state_ch1,
  register_dma_out_eof_bfr_des_addr_ch1,
  register_dma_out_dscr_ch1,
  register_dma_out_dscr_bf0_ch1,
  register_dma_out_dscr_bf1_ch1,
  register_dma_in_conf1_ch2,
  register_dma_infifo_status_ch2,
  register_dma_in_pop_ch2,
  register_dma_in_state_ch2,
  register_dma_in_suc_eof_des_addr_ch2,
  register_dma_in_err_eof_des_addr_ch2,
  register_dma_in_dscr_ch2,
  register_dma_in_dscr_bf1_ch2,
  register_dma_outfifo_status_ch2,
  register_dma_out_push_ch2,
  register_dma_out_state_ch2,
  register_dma_out_eof_bfr_des_addr_ch2,
  register_dma_out_dscr_ch2,
  register_dma_out_dscr_bf0_ch2,
  register_dma_out_dscr_bf1_ch2,
  register_gpio_bt_select,
  register_gpio_out,
  register_gpio_out_w1ts,
  register_gpio_out_w1tc,
  register_gpio_sdio_select,
  register_gpio_enable,
  register_gpio_enable_w1ts,
  register_gpio_enable_w1tc,
  register_gpio_strap,
  register_gpio_in,
  register_gpio_status,
  register_gpio_status_w1ts,
  register_gpio_status_w1tc,
  register_gpio_pcpu_int,
  register_gpio_pcpu_nmi_int,
  register_gpio_cpusdio_int,
  register_gpio_pin_s,
  register_gpio_status_next,
  register_gpio_func_s_in_sel_cfg,
  register_gpio_func_s_out_sel_cfg,
  register_gpio_clock_gate,
  register_gpio_reg_date,
  register_i2c0_scl_low_period,
  register_i2c0_ctr,
  register_i2c0_sr,
  register_i2c0_to,
  register_i2c0_slave_addr,
  register_i2c0_fifo_st,
  register_i2c0_fifo_conf,
  register_i2c0_data,
  register_i2c0_int_raw,
  register_i2c0_int_clr,
  register_i2c0_int_ena,
  register_i2c0_int_status,
  register_i2c0_sda_hold,
  register_i2c0_sda_sample,
  register_i2c0_scl_high_period,
  register_i2c0_scl_start_hold,
  register_i2c0_scl_rstart_setup,
  register_i2c0_scl_stop_hold,
  register_i2c0_scl_stop_setup,
  register_i2c0_filter_cfg,
  register_i2c0_clk_conf,
  register_i2c0_comd_s,
  register_i2c0_scl_st_time_out,
  register_i2c0_scl_main_st_time_out,
  register_i2c0_scl_sp_conf,
  register_i2c0_scl_stretch_conf,
  register_i2c0_date,
  register_i2c0_txfifo_start_addr,
  register_i2c0_rxfifo_start_addr,
  register_pcr_uart0_conf0_reg,
  register_pcr_uart1_conf0_reg,
  register_pcr_spi2_conf_reg,
  register_pcr_i2c0_conf_reg,
  register_spi0_ctrl,
  register_spi0_ctrl1,
  register_spi0_ctrl2,
  register_spi0_clock,
  register_spi0_user,
  register_spi0_user1,
  register_spi0_user2,
  register_spi0_rd_status,
  register_spi0_misc,
  register_spi0_cache_fctrl,
  register_spi0_fsm,
  register_spi0_timing_cali,
  register_spi0_din_mode,
  register_spi0_din_num,
  register_spi0_dout_mode,
  register_spi0_clock_gate,
  register_spi0_core_clk_sel,
  register_spi0_date,
  register_spi1_cmd,
  register_spi1_addr,
  register_spi1_ctrl,
  register_spi1_ctrl1,
  register_spi1_ctrl2,
  register_spi1_clock,
  register_spi1_user,
  register_spi1_user1,
  register_spi1_user2,
  register_spi1_mosi_dlen,
  register_spi1_miso_dlen,
  register_spi1_rd_status,
  register_spi1_misc,
  register_spi1_tx_crc,
  register_spi1_cache_fctrl,
  register_spi1_w0,
  register_spi1_w1,
  register_spi1_w2,
  register_spi1_w3,
  register_spi1_w4,
  register_spi1_w5,
  register_spi1_w6,
  register_spi1_w7,
  register_spi1_w8,
  register_spi1_w9,
  register_spi1_w10,
  register_spi1_w11,
  register_spi1_w12,
  register_spi1_w13,
  register_spi1_w14,
  register_spi1_w15,
  register_spi1_flash_waiti_ctrl,
  register_spi1_flash_sus_ctrl,
  register_spi1_flash_sus_cmd,
  register_spi1_sus_status,
  register_spi1_timing_cali,
  register_spi1_int_ena,
  register_spi1_int_clr,
  register_spi1_int_raw,
  register_spi1_int_st,
  register_spi1_clock_gate,
  register_spi1_date,
  register_spi2_cmd,
  register_spi2_addr,
  register_spi2_ctrl,
  register_spi2_clock,
  register_spi2_user,
  register_spi2_user1,
  register_spi2_user2,
  register_spi2_ms_dlen,
  register_spi2_misc,
  register_spi2_din_mode,
  register_spi2_din_num,
  register_spi2_dout_mode,
  register_spi2_dma_conf,
  register_spi2_dma_int_ena,
  register_spi2_dma_int_clr,
  register_spi2_dma_int_raw,
  register_spi2_dma_int_st,
  register_spi2_w0,
  register_spi2_w1,
  register_spi2_w2,
  register_spi2_w3,
  register_spi2_w4,
  register_spi2_w5,
  register_spi2_w6,
  register_spi2_w7,
  register_spi2_w8,
  register_spi2_w9,
  register_spi2_w10,
  register_spi2_w11,
  register_spi2_w12,
  register_spi2_w13,
  register_spi2_w14,
  register_spi2_w15,
  register_spi2_slave,
  register_spi2_slave1,
  register_spi2_clk_gate,
  register_spi2_date,
  register_uart0_fifo,
  register_uart0_int_raw,
  register_uart0_int_st,
  register_uart0_int_ena,
  register_uart0_int_clr,
  register_uart0_clkdiv,
  register_uart0_rx_filt,
  register_uart0_status,
  register_uart0_conf0,
  register_uart0_conf1,
  register_uart0_lowpulse,
  register_uart0_highpulse,
  register_uart0_rxd_cnt,
  register_uart0_flow_conf,
  register_uart0_sleep_conf,
  register_uart0_swfc_conf0,
  register_uart0_swfc_conf1,
  register_uart0_txbrk_conf,
  register_uart0_idle_conf,
  register_uart0_rs485_conf,
  register_uart0_at_cmd_precnt,
  register_uart0_at_cmd_postcnt,
  register_uart0_at_cmd_gaptout,
  register_uart0_at_cmd_char,
  register_uart0_mem_conf,
  register_uart0_mem_tx_status,
  register_uart0_mem_rx_status,
  register_uart0_fsm_status,
  register_uart0_pospulse,
  register_uart0_negpulse,
  register_uart0_clk_conf,
  register_uart0_date,
  register_uart0_id,
  register_uart1_fifo,
  register_uart1_int_raw,
  register_uart1_int_st,
  register_uart1_int_ena,
  register_uart1_int_clr,
  register_uart1_clkdiv,
  register_uart1_rx_filt,
  register_uart1_status,
  register_uart1_conf0,
  register_uart1_conf1,
  register_uart1_lowpulse,
  register_uart1_highpulse,
  register_uart1_rxd_cnt,
  register_uart1_flow_conf,
  register_uart1_sleep_conf,
  register_uart1_swfc_conf0,
  register_uart1_swfc_conf1,
  register_uart1_txbrk_conf,
  register_uart1_idle_conf,
  register_uart1_rs485_conf,
  register_uart1_at_cmd_precnt,
  register_uart1_at_cmd_postcnt,
  register_uart1_at_cmd_gaptout,
  register_uart1_at_cmd_char,
  register_uart1_mem_conf,
  register_uart1_mem_tx_status,
  register_uart1_mem_rx_status,
  register_uart1_fsm_status,
  register_uart1_pospulse,
  register_uart1_negpulse,
  register_uart1_clk_conf,
  register_uart1_date,
  register_uart1_id,
};

enum class RegisterRole : std::uint16_t {
  none,
  general,
  secondary_core_release,
};

template<RegisterId Id>
struct RegisterTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uintptr_t kBaseAddress = 0u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = -1;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_filter_ctrl1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_fsm_wait> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_sar1_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_sar2_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_sar_patt_tab1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_sar_patt_tab2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_onetime_sample> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_arb_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_filter_ctrl0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_sar1data_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_sar2data_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_thres0_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_thres1_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_thres_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_dma_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_clkm_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_apb_tsens_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_tsens_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_cali> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_ctrl_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 1020u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_int_raw_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_int_st_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_int_ena_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_int_clr_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_int_st_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_int_st_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_ahb_test> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_misc_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_conf0_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 112u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_conf1_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 116u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_infifo_status_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_pop_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_link_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_state_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 132u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_suc_eof_des_addr_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 136u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_err_eof_des_addr_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 140u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_dscr_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 144u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_dscr_bf0_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 148u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_dscr_bf1_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 152u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_pri_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 156u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_peri_sel_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 160u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_conf0_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 208u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_conf1_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 212u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_outfifo_status_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 216u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_push_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 220u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_link_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 224u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_state_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 228u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_eof_des_addr_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 232u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_eof_bfr_des_addr_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 236u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_dscr_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 240u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_dscr_bf0_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 244u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_dscr_bf1_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 248u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_pri_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 252u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_peri_sel_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 256u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_conf1_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 308u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_infifo_status_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 312u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_pop_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 316u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_state_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 324u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_suc_eof_des_addr_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 328u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_err_eof_des_addr_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 332u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_dscr_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 336u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_dscr_bf1_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 344u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_outfifo_status_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 408u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_push_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 412u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_state_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 420u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_eof_bfr_des_addr_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 428u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_dscr_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 432u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_dscr_bf0_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 436u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_dscr_bf1_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 440u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_conf1_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 500u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_infifo_status_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 504u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_pop_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 508u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_state_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 516u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_suc_eof_des_addr_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 520u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_err_eof_des_addr_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 524u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_dscr_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 528u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_dscr_bf1_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 536u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_outfifo_status_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 600u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_push_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 604u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_state_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 612u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_eof_bfr_des_addr_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 620u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_dscr_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 624u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_dscr_bf0_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 628u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_dscr_bf1_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 632u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_bt_select> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_out> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_out_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_out_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_sdio_select> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_enable> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_enable_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_enable_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_strap> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_in> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_status_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_status_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_pcpu_int> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_pcpu_nmi_int> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_cpusdio_int> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_pin_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 116u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_status_next> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 332u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_func_s_in_sel_cfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 340u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_func_s_out_sel_cfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 1364u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_clock_gate> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 1580u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_reg_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 1788u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_low_period> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_ctr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_sr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_to> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_slave_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_fifo_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_fifo_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_data> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_int_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_sda_hold> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_sda_sample> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_high_period> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_start_hold> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_rstart_setup> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_stop_hold> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_stop_setup> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_filter_cfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_clk_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_comd_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_st_time_out> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_main_st_time_out> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_sp_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_stretch_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 132u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 248u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_txfifo_start_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 256u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_rxfifo_start_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr std::uint32_t kOffsetBytes = 384u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_pcr_uart0_conf0_reg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x600A0000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_pcr_uart1_conf0_reg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x600A0000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_pcr_spi2_conf_reg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x600A0000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_pcr_i2c0_conf_reg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x600A0000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ctrl1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_clock> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_user> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_user1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_user2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_rd_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_misc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_cache_fctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_fsm> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_timing_cali> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 168u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_din_mode> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 172u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_din_num> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 176u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_dout_mode> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 180u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_clock_gate> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 220u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_core_clk_sel> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 224u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 1020u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_ctrl1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_clock> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_user> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_user1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_user2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_mosi_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_miso_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_rd_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_misc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_tx_crc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_cache_fctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 104u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 108u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 112u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 116u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w8> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w9> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w10> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w11> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 132u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w12> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 136u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w13> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 140u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w14> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 144u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w15> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 148u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_flash_waiti_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 152u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_flash_sus_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 156u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_flash_sus_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 160u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_sus_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 164u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_timing_cali> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 168u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 192u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 196u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 200u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 204u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_clock_gate> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 220u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 1020u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_clock> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_user> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_user1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_user2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_ms_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_misc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_din_mode> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_din_num> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dout_mode> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 152u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 156u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 160u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 164u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 168u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 172u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 176u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 180u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w8> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 184u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w9> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 188u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w10> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 192u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w11> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 196u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w12> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 200u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w13> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 204u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w14> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 208u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w15> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 212u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_slave> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 224u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_slave1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 228u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_clk_gate> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 232u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 240u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_fifo> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_clkdiv> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_rx_filt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_conf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_conf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_lowpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_highpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_rxd_cnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_flow_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_sleep_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_swfc_conf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_swfc_conf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_txbrk_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_idle_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_rs485_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_at_cmd_precnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_at_cmd_postcnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_at_cmd_gaptout> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_at_cmd_char> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_mem_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_mem_tx_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_mem_rx_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 104u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_fsm_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 108u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_pospulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 112u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_negpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 116u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_clk_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_id> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_fifo> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_clkdiv> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_rx_filt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_conf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_conf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_lowpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_highpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_rxd_cnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_flow_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_sleep_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_swfc_conf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_swfc_conf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_txbrk_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_idle_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_rs485_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_at_cmd_precnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_at_cmd_postcnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_at_cmd_gaptout> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_at_cmd_char> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_mem_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_mem_tx_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_mem_rx_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 104u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_fsm_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 108u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_pospulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 112u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_negpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 116u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_clk_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_id> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

inline constexpr std::array<RegisterId, 309> kRegisters = {{
  RegisterId::register_apb_saradc_ctrl,
  RegisterId::register_apb_saradc_ctrl2,
  RegisterId::register_apb_saradc_filter_ctrl1,
  RegisterId::register_apb_saradc_fsm_wait,
  RegisterId::register_apb_saradc_sar1_status,
  RegisterId::register_apb_saradc_sar2_status,
  RegisterId::register_apb_saradc_sar_patt_tab1,
  RegisterId::register_apb_saradc_sar_patt_tab2,
  RegisterId::register_apb_saradc_onetime_sample,
  RegisterId::register_apb_saradc_arb_ctrl,
  RegisterId::register_apb_saradc_filter_ctrl0,
  RegisterId::register_apb_saradc_sar1data_status,
  RegisterId::register_apb_saradc_sar2data_status,
  RegisterId::register_apb_saradc_thres0_ctrl,
  RegisterId::register_apb_saradc_thres1_ctrl,
  RegisterId::register_apb_saradc_thres_ctrl,
  RegisterId::register_apb_saradc_int_ena,
  RegisterId::register_apb_saradc_int_raw,
  RegisterId::register_apb_saradc_int_st,
  RegisterId::register_apb_saradc_int_clr,
  RegisterId::register_apb_saradc_dma_conf,
  RegisterId::register_apb_saradc_clkm_conf,
  RegisterId::register_apb_saradc_apb_tsens_ctrl,
  RegisterId::register_apb_saradc_tsens_ctrl2,
  RegisterId::register_apb_saradc_cali,
  RegisterId::register_apb_saradc_ctrl_date,
  RegisterId::register_dma_int_raw_ch_s,
  RegisterId::register_dma_int_st_ch0,
  RegisterId::register_dma_int_ena_ch_s,
  RegisterId::register_dma_int_clr_ch_s,
  RegisterId::register_dma_int_st_ch1,
  RegisterId::register_dma_int_st_ch2,
  RegisterId::register_dma_ahb_test,
  RegisterId::register_dma_misc_conf,
  RegisterId::register_dma_date,
  RegisterId::register_dma_in_conf0_ch_s,
  RegisterId::register_dma_in_conf1_ch0,
  RegisterId::register_dma_infifo_status_ch0,
  RegisterId::register_dma_in_pop_ch0,
  RegisterId::register_dma_in_link_ch_s,
  RegisterId::register_dma_in_state_ch0,
  RegisterId::register_dma_in_suc_eof_des_addr_ch0,
  RegisterId::register_dma_in_err_eof_des_addr_ch0,
  RegisterId::register_dma_in_dscr_ch0,
  RegisterId::register_dma_in_dscr_bf0_ch_s,
  RegisterId::register_dma_in_dscr_bf1_ch0,
  RegisterId::register_dma_in_pri_ch_s,
  RegisterId::register_dma_in_peri_sel_ch_s,
  RegisterId::register_dma_out_conf0_ch_s,
  RegisterId::register_dma_out_conf1_ch_s,
  RegisterId::register_dma_outfifo_status_ch0,
  RegisterId::register_dma_out_push_ch0,
  RegisterId::register_dma_out_link_ch_s,
  RegisterId::register_dma_out_state_ch0,
  RegisterId::register_dma_out_eof_des_addr_ch_s,
  RegisterId::register_dma_out_eof_bfr_des_addr_ch0,
  RegisterId::register_dma_out_dscr_ch0,
  RegisterId::register_dma_out_dscr_bf0_ch0,
  RegisterId::register_dma_out_dscr_bf1_ch0,
  RegisterId::register_dma_out_pri_ch_s,
  RegisterId::register_dma_out_peri_sel_ch_s,
  RegisterId::register_dma_in_conf1_ch1,
  RegisterId::register_dma_infifo_status_ch1,
  RegisterId::register_dma_in_pop_ch1,
  RegisterId::register_dma_in_state_ch1,
  RegisterId::register_dma_in_suc_eof_des_addr_ch1,
  RegisterId::register_dma_in_err_eof_des_addr_ch1,
  RegisterId::register_dma_in_dscr_ch1,
  RegisterId::register_dma_in_dscr_bf1_ch1,
  RegisterId::register_dma_outfifo_status_ch1,
  RegisterId::register_dma_out_push_ch1,
  RegisterId::register_dma_out_state_ch1,
  RegisterId::register_dma_out_eof_bfr_des_addr_ch1,
  RegisterId::register_dma_out_dscr_ch1,
  RegisterId::register_dma_out_dscr_bf0_ch1,
  RegisterId::register_dma_out_dscr_bf1_ch1,
  RegisterId::register_dma_in_conf1_ch2,
  RegisterId::register_dma_infifo_status_ch2,
  RegisterId::register_dma_in_pop_ch2,
  RegisterId::register_dma_in_state_ch2,
  RegisterId::register_dma_in_suc_eof_des_addr_ch2,
  RegisterId::register_dma_in_err_eof_des_addr_ch2,
  RegisterId::register_dma_in_dscr_ch2,
  RegisterId::register_dma_in_dscr_bf1_ch2,
  RegisterId::register_dma_outfifo_status_ch2,
  RegisterId::register_dma_out_push_ch2,
  RegisterId::register_dma_out_state_ch2,
  RegisterId::register_dma_out_eof_bfr_des_addr_ch2,
  RegisterId::register_dma_out_dscr_ch2,
  RegisterId::register_dma_out_dscr_bf0_ch2,
  RegisterId::register_dma_out_dscr_bf1_ch2,
  RegisterId::register_gpio_bt_select,
  RegisterId::register_gpio_out,
  RegisterId::register_gpio_out_w1ts,
  RegisterId::register_gpio_out_w1tc,
  RegisterId::register_gpio_sdio_select,
  RegisterId::register_gpio_enable,
  RegisterId::register_gpio_enable_w1ts,
  RegisterId::register_gpio_enable_w1tc,
  RegisterId::register_gpio_strap,
  RegisterId::register_gpio_in,
  RegisterId::register_gpio_status,
  RegisterId::register_gpio_status_w1ts,
  RegisterId::register_gpio_status_w1tc,
  RegisterId::register_gpio_pcpu_int,
  RegisterId::register_gpio_pcpu_nmi_int,
  RegisterId::register_gpio_cpusdio_int,
  RegisterId::register_gpio_pin_s,
  RegisterId::register_gpio_status_next,
  RegisterId::register_gpio_func_s_in_sel_cfg,
  RegisterId::register_gpio_func_s_out_sel_cfg,
  RegisterId::register_gpio_clock_gate,
  RegisterId::register_gpio_reg_date,
  RegisterId::register_i2c0_scl_low_period,
  RegisterId::register_i2c0_ctr,
  RegisterId::register_i2c0_sr,
  RegisterId::register_i2c0_to,
  RegisterId::register_i2c0_slave_addr,
  RegisterId::register_i2c0_fifo_st,
  RegisterId::register_i2c0_fifo_conf,
  RegisterId::register_i2c0_data,
  RegisterId::register_i2c0_int_raw,
  RegisterId::register_i2c0_int_clr,
  RegisterId::register_i2c0_int_ena,
  RegisterId::register_i2c0_int_status,
  RegisterId::register_i2c0_sda_hold,
  RegisterId::register_i2c0_sda_sample,
  RegisterId::register_i2c0_scl_high_period,
  RegisterId::register_i2c0_scl_start_hold,
  RegisterId::register_i2c0_scl_rstart_setup,
  RegisterId::register_i2c0_scl_stop_hold,
  RegisterId::register_i2c0_scl_stop_setup,
  RegisterId::register_i2c0_filter_cfg,
  RegisterId::register_i2c0_clk_conf,
  RegisterId::register_i2c0_comd_s,
  RegisterId::register_i2c0_scl_st_time_out,
  RegisterId::register_i2c0_scl_main_st_time_out,
  RegisterId::register_i2c0_scl_sp_conf,
  RegisterId::register_i2c0_scl_stretch_conf,
  RegisterId::register_i2c0_date,
  RegisterId::register_i2c0_txfifo_start_addr,
  RegisterId::register_i2c0_rxfifo_start_addr,
  RegisterId::register_pcr_uart0_conf0_reg,
  RegisterId::register_pcr_uart1_conf0_reg,
  RegisterId::register_pcr_spi2_conf_reg,
  RegisterId::register_pcr_i2c0_conf_reg,
  RegisterId::register_spi0_ctrl,
  RegisterId::register_spi0_ctrl1,
  RegisterId::register_spi0_ctrl2,
  RegisterId::register_spi0_clock,
  RegisterId::register_spi0_user,
  RegisterId::register_spi0_user1,
  RegisterId::register_spi0_user2,
  RegisterId::register_spi0_rd_status,
  RegisterId::register_spi0_misc,
  RegisterId::register_spi0_cache_fctrl,
  RegisterId::register_spi0_fsm,
  RegisterId::register_spi0_timing_cali,
  RegisterId::register_spi0_din_mode,
  RegisterId::register_spi0_din_num,
  RegisterId::register_spi0_dout_mode,
  RegisterId::register_spi0_clock_gate,
  RegisterId::register_spi0_core_clk_sel,
  RegisterId::register_spi0_date,
  RegisterId::register_spi1_cmd,
  RegisterId::register_spi1_addr,
  RegisterId::register_spi1_ctrl,
  RegisterId::register_spi1_ctrl1,
  RegisterId::register_spi1_ctrl2,
  RegisterId::register_spi1_clock,
  RegisterId::register_spi1_user,
  RegisterId::register_spi1_user1,
  RegisterId::register_spi1_user2,
  RegisterId::register_spi1_mosi_dlen,
  RegisterId::register_spi1_miso_dlen,
  RegisterId::register_spi1_rd_status,
  RegisterId::register_spi1_misc,
  RegisterId::register_spi1_tx_crc,
  RegisterId::register_spi1_cache_fctrl,
  RegisterId::register_spi1_w0,
  RegisterId::register_spi1_w1,
  RegisterId::register_spi1_w2,
  RegisterId::register_spi1_w3,
  RegisterId::register_spi1_w4,
  RegisterId::register_spi1_w5,
  RegisterId::register_spi1_w6,
  RegisterId::register_spi1_w7,
  RegisterId::register_spi1_w8,
  RegisterId::register_spi1_w9,
  RegisterId::register_spi1_w10,
  RegisterId::register_spi1_w11,
  RegisterId::register_spi1_w12,
  RegisterId::register_spi1_w13,
  RegisterId::register_spi1_w14,
  RegisterId::register_spi1_w15,
  RegisterId::register_spi1_flash_waiti_ctrl,
  RegisterId::register_spi1_flash_sus_ctrl,
  RegisterId::register_spi1_flash_sus_cmd,
  RegisterId::register_spi1_sus_status,
  RegisterId::register_spi1_timing_cali,
  RegisterId::register_spi1_int_ena,
  RegisterId::register_spi1_int_clr,
  RegisterId::register_spi1_int_raw,
  RegisterId::register_spi1_int_st,
  RegisterId::register_spi1_clock_gate,
  RegisterId::register_spi1_date,
  RegisterId::register_spi2_cmd,
  RegisterId::register_spi2_addr,
  RegisterId::register_spi2_ctrl,
  RegisterId::register_spi2_clock,
  RegisterId::register_spi2_user,
  RegisterId::register_spi2_user1,
  RegisterId::register_spi2_user2,
  RegisterId::register_spi2_ms_dlen,
  RegisterId::register_spi2_misc,
  RegisterId::register_spi2_din_mode,
  RegisterId::register_spi2_din_num,
  RegisterId::register_spi2_dout_mode,
  RegisterId::register_spi2_dma_conf,
  RegisterId::register_spi2_dma_int_ena,
  RegisterId::register_spi2_dma_int_clr,
  RegisterId::register_spi2_dma_int_raw,
  RegisterId::register_spi2_dma_int_st,
  RegisterId::register_spi2_w0,
  RegisterId::register_spi2_w1,
  RegisterId::register_spi2_w2,
  RegisterId::register_spi2_w3,
  RegisterId::register_spi2_w4,
  RegisterId::register_spi2_w5,
  RegisterId::register_spi2_w6,
  RegisterId::register_spi2_w7,
  RegisterId::register_spi2_w8,
  RegisterId::register_spi2_w9,
  RegisterId::register_spi2_w10,
  RegisterId::register_spi2_w11,
  RegisterId::register_spi2_w12,
  RegisterId::register_spi2_w13,
  RegisterId::register_spi2_w14,
  RegisterId::register_spi2_w15,
  RegisterId::register_spi2_slave,
  RegisterId::register_spi2_slave1,
  RegisterId::register_spi2_clk_gate,
  RegisterId::register_spi2_date,
  RegisterId::register_uart0_fifo,
  RegisterId::register_uart0_int_raw,
  RegisterId::register_uart0_int_st,
  RegisterId::register_uart0_int_ena,
  RegisterId::register_uart0_int_clr,
  RegisterId::register_uart0_clkdiv,
  RegisterId::register_uart0_rx_filt,
  RegisterId::register_uart0_status,
  RegisterId::register_uart0_conf0,
  RegisterId::register_uart0_conf1,
  RegisterId::register_uart0_lowpulse,
  RegisterId::register_uart0_highpulse,
  RegisterId::register_uart0_rxd_cnt,
  RegisterId::register_uart0_flow_conf,
  RegisterId::register_uart0_sleep_conf,
  RegisterId::register_uart0_swfc_conf0,
  RegisterId::register_uart0_swfc_conf1,
  RegisterId::register_uart0_txbrk_conf,
  RegisterId::register_uart0_idle_conf,
  RegisterId::register_uart0_rs485_conf,
  RegisterId::register_uart0_at_cmd_precnt,
  RegisterId::register_uart0_at_cmd_postcnt,
  RegisterId::register_uart0_at_cmd_gaptout,
  RegisterId::register_uart0_at_cmd_char,
  RegisterId::register_uart0_mem_conf,
  RegisterId::register_uart0_mem_tx_status,
  RegisterId::register_uart0_mem_rx_status,
  RegisterId::register_uart0_fsm_status,
  RegisterId::register_uart0_pospulse,
  RegisterId::register_uart0_negpulse,
  RegisterId::register_uart0_clk_conf,
  RegisterId::register_uart0_date,
  RegisterId::register_uart0_id,
  RegisterId::register_uart1_fifo,
  RegisterId::register_uart1_int_raw,
  RegisterId::register_uart1_int_st,
  RegisterId::register_uart1_int_ena,
  RegisterId::register_uart1_int_clr,
  RegisterId::register_uart1_clkdiv,
  RegisterId::register_uart1_rx_filt,
  RegisterId::register_uart1_status,
  RegisterId::register_uart1_conf0,
  RegisterId::register_uart1_conf1,
  RegisterId::register_uart1_lowpulse,
  RegisterId::register_uart1_highpulse,
  RegisterId::register_uart1_rxd_cnt,
  RegisterId::register_uart1_flow_conf,
  RegisterId::register_uart1_sleep_conf,
  RegisterId::register_uart1_swfc_conf0,
  RegisterId::register_uart1_swfc_conf1,
  RegisterId::register_uart1_txbrk_conf,
  RegisterId::register_uart1_idle_conf,
  RegisterId::register_uart1_rs485_conf,
  RegisterId::register_uart1_at_cmd_precnt,
  RegisterId::register_uart1_at_cmd_postcnt,
  RegisterId::register_uart1_at_cmd_gaptout,
  RegisterId::register_uart1_at_cmd_char,
  RegisterId::register_uart1_mem_conf,
  RegisterId::register_uart1_mem_tx_status,
  RegisterId::register_uart1_mem_rx_status,
  RegisterId::register_uart1_fsm_status,
  RegisterId::register_uart1_pospulse,
  RegisterId::register_uart1_negpulse,
  RegisterId::register_uart1_clk_conf,
  RegisterId::register_uart1_date,
  RegisterId::register_uart1_id,
}};
}
}
}
}
}
}
