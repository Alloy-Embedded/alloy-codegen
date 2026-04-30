#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace espressif {
namespace esp32 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32_wroom32 {
enum class RegisterId : std::uint16_t {
  none,
  register_dport_appcpu_ctrl_b,
  register_dport_perip_clk_en,
  register_gpio_bt_select,
  register_gpio_out,
  register_gpio_out_w1ts,
  register_gpio_out_w1tc,
  register_gpio_out1,
  register_gpio_out1_w1ts,
  register_gpio_out1_w1tc,
  register_gpio_sdio_select,
  register_gpio_enable,
  register_gpio_enable_w1ts,
  register_gpio_enable_w1tc,
  register_gpio_enable1,
  register_gpio_enable1_w1ts,
  register_gpio_enable1_w1tc,
  register_gpio_strap,
  register_gpio_in,
  register_gpio_in1,
  register_gpio_status,
  register_gpio_status_w1ts,
  register_gpio_status_w1tc,
  register_gpio_status1,
  register_gpio_status1_w1ts,
  register_gpio_status1_w1tc,
  register_gpio_acpu_int,
  register_gpio_acpu_nmi_int,
  register_gpio_pcpu_int,
  register_gpio_pcpu_nmi_int,
  register_gpio_cpusdio_int,
  register_gpio_acpu_int1,
  register_gpio_acpu_nmi_int1,
  register_gpio_pcpu_int1,
  register_gpio_pcpu_nmi_int1,
  register_gpio_cpusdio_int1,
  register_gpio_pin_s,
  register_gpio_cali_conf,
  register_gpio_cali_data,
  register_gpio_func_s_in_sel_cfg,
  register_gpio_func_s_out_sel_cfg,
  register_i2c0_scl_low_period,
  register_i2c0_ctr,
  register_i2c0_sr,
  register_i2c0_to,
  register_i2c0_slave_addr,
  register_i2c0_rxfifo_st,
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
  register_i2c0_scl_filter_cfg,
  register_i2c0_sda_filter_cfg,
  register_i2c0_comd_s,
  register_i2c0_date,
  register_i2c0_fifo_start_addr,
  register_i2c1_scl_low_period,
  register_i2c1_ctr,
  register_i2c1_sr,
  register_i2c1_to,
  register_i2c1_slave_addr,
  register_i2c1_rxfifo_st,
  register_i2c1_fifo_conf,
  register_i2c1_data,
  register_i2c1_int_raw,
  register_i2c1_int_clr,
  register_i2c1_int_ena,
  register_i2c1_int_status,
  register_i2c1_sda_hold,
  register_i2c1_sda_sample,
  register_i2c1_scl_high_period,
  register_i2c1_scl_start_hold,
  register_i2c1_scl_rstart_setup,
  register_i2c1_scl_stop_hold,
  register_i2c1_scl_stop_setup,
  register_i2c1_scl_filter_cfg,
  register_i2c1_sda_filter_cfg,
  register_i2c1_comd_s,
  register_i2c1_date,
  register_i2c1_fifo_start_addr,
  register_sens_sar_read_ctrl,
  register_sens_sar_read_status1,
  register_sens_sar_meas_wait1,
  register_sens_sar_meas_wait2,
  register_sens_sar_meas_ctrl,
  register_sens_sar_read_status2,
  register_sens_ulp_cp_sleep_cyc0,
  register_sens_ulp_cp_sleep_cyc1,
  register_sens_ulp_cp_sleep_cyc2,
  register_sens_ulp_cp_sleep_cyc3,
  register_sens_ulp_cp_sleep_cyc4,
  register_sens_sar_start_force,
  register_sens_sar_mem_wr_ctrl,
  register_sens_sar_atten1,
  register_sens_sar_atten2,
  register_sens_sar_slave_addr1,
  register_sens_sar_slave_addr2,
  register_sens_sar_slave_addr3,
  register_sens_sar_slave_addr4,
  register_sens_sar_tsens_ctrl,
  register_sens_sar_i2c_ctrl,
  register_sens_sar_meas_start1,
  register_sens_sar_touch_ctrl1,
  register_sens_sar_touch_thres1,
  register_sens_sar_touch_thres2,
  register_sens_sar_touch_thres3,
  register_sens_sar_touch_thres4,
  register_sens_sar_touch_thres5,
  register_sens_sar_touch_out1,
  register_sens_sar_touch_out2,
  register_sens_sar_touch_out3,
  register_sens_sar_touch_out4,
  register_sens_sar_touch_out5,
  register_sens_sar_touch_ctrl2,
  register_sens_sar_touch_enable,
  register_sens_sar_read_ctrl2,
  register_sens_sar_meas_start2,
  register_sens_sar_dac_ctrl1,
  register_sens_sar_dac_ctrl2,
  register_sens_sar_meas_ctrl2,
  register_sens_sar_nouse,
  register_sens_sardate,
  register_spi0_cmd,
  register_spi0_addr,
  register_spi0_ctrl,
  register_spi0_ctrl1,
  register_spi0_rd_status,
  register_spi0_ctrl2,
  register_spi0_clock,
  register_spi0_user,
  register_spi0_user1,
  register_spi0_user2,
  register_spi0_mosi_dlen,
  register_spi0_miso_dlen,
  register_spi0_slv_wr_status,
  register_spi0_pin,
  register_spi0_slave,
  register_spi0_slave1,
  register_spi0_slave2,
  register_spi0_slave3,
  register_spi0_slv_wrbuf_dlen,
  register_spi0_slv_rdbuf_dlen,
  register_spi0_cache_fctrl,
  register_spi0_cache_sctrl,
  register_spi0_sram_cmd,
  register_spi0_sram_drd_cmd,
  register_spi0_sram_dwr_cmd,
  register_spi0_slv_rd_bit,
  register_spi0_w0,
  register_spi0_w1,
  register_spi0_w2,
  register_spi0_w3,
  register_spi0_w4,
  register_spi0_w5,
  register_spi0_w6,
  register_spi0_w7,
  register_spi0_w8,
  register_spi0_w9,
  register_spi0_w10,
  register_spi0_w11,
  register_spi0_w12,
  register_spi0_w13,
  register_spi0_w14,
  register_spi0_w15,
  register_spi0_tx_crc,
  register_spi0_ext0,
  register_spi0_ext1,
  register_spi0_ext2,
  register_spi0_ext3,
  register_spi0_dma_conf,
  register_spi0_dma_out_link,
  register_spi0_dma_in_link,
  register_spi0_dma_status,
  register_spi0_dma_int_ena,
  register_spi0_dma_int_raw,
  register_spi0_dma_int_st,
  register_spi0_dma_int_clr,
  register_spi0_in_err_eof_des_addr,
  register_spi0_in_suc_eof_des_addr,
  register_spi0_inlink_dscr,
  register_spi0_inlink_dscr_bf0,
  register_spi0_inlink_dscr_bf1,
  register_spi0_out_eof_bfr_des_addr,
  register_spi0_out_eof_des_addr,
  register_spi0_outlink_dscr,
  register_spi0_outlink_dscr_bf0,
  register_spi0_outlink_dscr_bf1,
  register_spi0_dma_rstatus,
  register_spi0_dma_tstatus,
  register_spi0_date,
  register_spi1_cmd,
  register_spi1_addr,
  register_spi1_ctrl,
  register_spi1_ctrl1,
  register_spi1_rd_status,
  register_spi1_ctrl2,
  register_spi1_clock,
  register_spi1_user,
  register_spi1_user1,
  register_spi1_user2,
  register_spi1_mosi_dlen,
  register_spi1_miso_dlen,
  register_spi1_slv_wr_status,
  register_spi1_pin,
  register_spi1_slave,
  register_spi1_slave1,
  register_spi1_slave2,
  register_spi1_slave3,
  register_spi1_slv_wrbuf_dlen,
  register_spi1_slv_rdbuf_dlen,
  register_spi1_cache_fctrl,
  register_spi1_cache_sctrl,
  register_spi1_sram_cmd,
  register_spi1_sram_drd_cmd,
  register_spi1_sram_dwr_cmd,
  register_spi1_slv_rd_bit,
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
  register_spi1_tx_crc,
  register_spi1_ext0,
  register_spi1_ext1,
  register_spi1_ext2,
  register_spi1_ext3,
  register_spi1_dma_conf,
  register_spi1_dma_out_link,
  register_spi1_dma_in_link,
  register_spi1_dma_status,
  register_spi1_dma_int_ena,
  register_spi1_dma_int_raw,
  register_spi1_dma_int_st,
  register_spi1_dma_int_clr,
  register_spi1_in_err_eof_des_addr,
  register_spi1_in_suc_eof_des_addr,
  register_spi1_inlink_dscr,
  register_spi1_inlink_dscr_bf0,
  register_spi1_inlink_dscr_bf1,
  register_spi1_out_eof_bfr_des_addr,
  register_spi1_out_eof_des_addr,
  register_spi1_outlink_dscr,
  register_spi1_outlink_dscr_bf0,
  register_spi1_outlink_dscr_bf1,
  register_spi1_dma_rstatus,
  register_spi1_dma_tstatus,
  register_spi1_date,
  register_spi2_cmd,
  register_spi2_addr,
  register_spi2_ctrl,
  register_spi2_ctrl1,
  register_spi2_rd_status,
  register_spi2_ctrl2,
  register_spi2_clock,
  register_spi2_user,
  register_spi2_user1,
  register_spi2_user2,
  register_spi2_mosi_dlen,
  register_spi2_miso_dlen,
  register_spi2_slv_wr_status,
  register_spi2_pin,
  register_spi2_slave,
  register_spi2_slave1,
  register_spi2_slave2,
  register_spi2_slave3,
  register_spi2_slv_wrbuf_dlen,
  register_spi2_slv_rdbuf_dlen,
  register_spi2_cache_fctrl,
  register_spi2_cache_sctrl,
  register_spi2_sram_cmd,
  register_spi2_sram_drd_cmd,
  register_spi2_sram_dwr_cmd,
  register_spi2_slv_rd_bit,
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
  register_spi2_tx_crc,
  register_spi2_ext0,
  register_spi2_ext1,
  register_spi2_ext2,
  register_spi2_ext3,
  register_spi2_dma_conf,
  register_spi2_dma_out_link,
  register_spi2_dma_in_link,
  register_spi2_dma_status,
  register_spi2_dma_int_ena,
  register_spi2_dma_int_raw,
  register_spi2_dma_int_st,
  register_spi2_dma_int_clr,
  register_spi2_in_err_eof_des_addr,
  register_spi2_in_suc_eof_des_addr,
  register_spi2_inlink_dscr,
  register_spi2_inlink_dscr_bf0,
  register_spi2_inlink_dscr_bf1,
  register_spi2_out_eof_bfr_des_addr,
  register_spi2_out_eof_des_addr,
  register_spi2_outlink_dscr,
  register_spi2_outlink_dscr_bf0,
  register_spi2_outlink_dscr_bf1,
  register_spi2_dma_rstatus,
  register_spi2_dma_tstatus,
  register_spi2_date,
  register_spi3_cmd,
  register_spi3_addr,
  register_spi3_ctrl,
  register_spi3_ctrl1,
  register_spi3_rd_status,
  register_spi3_ctrl2,
  register_spi3_clock,
  register_spi3_user,
  register_spi3_user1,
  register_spi3_user2,
  register_spi3_mosi_dlen,
  register_spi3_miso_dlen,
  register_spi3_slv_wr_status,
  register_spi3_pin,
  register_spi3_slave,
  register_spi3_slave1,
  register_spi3_slave2,
  register_spi3_slave3,
  register_spi3_slv_wrbuf_dlen,
  register_spi3_slv_rdbuf_dlen,
  register_spi3_cache_fctrl,
  register_spi3_cache_sctrl,
  register_spi3_sram_cmd,
  register_spi3_sram_drd_cmd,
  register_spi3_sram_dwr_cmd,
  register_spi3_slv_rd_bit,
  register_spi3_w0,
  register_spi3_w1,
  register_spi3_w2,
  register_spi3_w3,
  register_spi3_w4,
  register_spi3_w5,
  register_spi3_w6,
  register_spi3_w7,
  register_spi3_w8,
  register_spi3_w9,
  register_spi3_w10,
  register_spi3_w11,
  register_spi3_w12,
  register_spi3_w13,
  register_spi3_w14,
  register_spi3_w15,
  register_spi3_tx_crc,
  register_spi3_ext0,
  register_spi3_ext1,
  register_spi3_ext2,
  register_spi3_ext3,
  register_spi3_dma_conf,
  register_spi3_dma_out_link,
  register_spi3_dma_in_link,
  register_spi3_dma_status,
  register_spi3_dma_int_ena,
  register_spi3_dma_int_raw,
  register_spi3_dma_int_st,
  register_spi3_dma_int_clr,
  register_spi3_in_err_eof_des_addr,
  register_spi3_in_suc_eof_des_addr,
  register_spi3_inlink_dscr,
  register_spi3_inlink_dscr_bf0,
  register_spi3_inlink_dscr_bf1,
  register_spi3_out_eof_bfr_des_addr,
  register_spi3_out_eof_des_addr,
  register_spi3_outlink_dscr,
  register_spi3_outlink_dscr_bf0,
  register_spi3_outlink_dscr_bf1,
  register_spi3_dma_rstatus,
  register_spi3_dma_tstatus,
  register_spi3_date,
  register_uart0_fifo,
  register_uart0_int_raw,
  register_uart0_int_st,
  register_uart0_int_ena,
  register_uart0_int_clr,
  register_uart0_clkdiv,
  register_uart0_autobaud,
  register_uart0_status,
  register_uart0_conf0,
  register_uart0_conf1,
  register_uart0_lowpulse,
  register_uart0_highpulse,
  register_uart0_rxd_cnt,
  register_uart0_flow_conf,
  register_uart0_sleep_conf,
  register_uart0_swfc_conf,
  register_uart0_idle_conf,
  register_uart0_rs485_conf,
  register_uart0_at_cmd_precnt,
  register_uart0_at_cmd_postcnt,
  register_uart0_at_cmd_gaptout,
  register_uart0_at_cmd_char,
  register_uart0_mem_conf,
  register_uart0_mem_tx_status,
  register_uart0_mem_rx_status,
  register_uart0_mem_cnt_status,
  register_uart0_pospulse,
  register_uart0_negpulse,
  register_uart0_date,
  register_uart0_id,
  register_uart1_fifo,
  register_uart1_int_raw,
  register_uart1_int_st,
  register_uart1_int_ena,
  register_uart1_int_clr,
  register_uart1_clkdiv,
  register_uart1_autobaud,
  register_uart1_status,
  register_uart1_conf0,
  register_uart1_conf1,
  register_uart1_lowpulse,
  register_uart1_highpulse,
  register_uart1_rxd_cnt,
  register_uart1_flow_conf,
  register_uart1_sleep_conf,
  register_uart1_swfc_conf,
  register_uart1_idle_conf,
  register_uart1_rs485_conf,
  register_uart1_at_cmd_precnt,
  register_uart1_at_cmd_postcnt,
  register_uart1_at_cmd_gaptout,
  register_uart1_at_cmd_char,
  register_uart1_mem_conf,
  register_uart1_mem_tx_status,
  register_uart1_mem_rx_status,
  register_uart1_mem_cnt_status,
  register_uart1_pospulse,
  register_uart1_negpulse,
  register_uart1_date,
  register_uart1_id,
  register_uart2_fifo,
  register_uart2_int_raw,
  register_uart2_int_st,
  register_uart2_int_ena,
  register_uart2_int_clr,
  register_uart2_clkdiv,
  register_uart2_autobaud,
  register_uart2_status,
  register_uart2_conf0,
  register_uart2_conf1,
  register_uart2_lowpulse,
  register_uart2_highpulse,
  register_uart2_rxd_cnt,
  register_uart2_flow_conf,
  register_uart2_sleep_conf,
  register_uart2_swfc_conf,
  register_uart2_idle_conf,
  register_uart2_rs485_conf,
  register_uart2_at_cmd_precnt,
  register_uart2_at_cmd_postcnt,
  register_uart2_at_cmd_gaptout,
  register_uart2_at_cmd_char,
  register_uart2_mem_conf,
  register_uart2_mem_tx_status,
  register_uart2_mem_rx_status,
  register_uart2_mem_cnt_status,
  register_uart2_pospulse,
  register_uart2_negpulse,
  register_uart2_date,
  register_uart2_id,
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
struct RegisterTraits<RegisterId::register_dport_appcpu_ctrl_b> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF00000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::secondary_core_release;
};

template<>
struct RegisterTraits<RegisterId::register_dport_perip_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF00000u;
  static constexpr std::uint32_t kOffsetBytes = 192u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_bt_select> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_out> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_out_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_out_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_out1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_out1_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_out1_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_sdio_select> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_enable> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_enable_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_enable_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_enable1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_enable1_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_enable1_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_strap> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_in> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_in1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_status_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_status_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_status1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_status1_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_status1_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_acpu_int> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_acpu_nmi_int> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_pcpu_int> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 104u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_pcpu_nmi_int> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 108u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_cpusdio_int> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 112u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_acpu_int1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 116u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_acpu_nmi_int1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_pcpu_int1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_pcpu_nmi_int1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_cpusdio_int1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 132u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_pin_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 136u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_cali_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 296u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_cali_data> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 300u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_func_s_in_sel_cfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 304u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_func_s_out_sel_cfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF44000u;
  static constexpr std::uint32_t kOffsetBytes = 1328u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_low_period> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_ctr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_sr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_to> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_slave_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_rxfifo_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_fifo_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_data> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_int_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_sda_hold> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_sda_sample> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_high_period> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_start_hold> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_rstart_setup> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_stop_hold> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_stop_setup> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_scl_filter_cfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_sda_filter_cfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_comd_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 248u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c0_fifo_start_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF53000u;
  static constexpr std::uint32_t kOffsetBytes = 256u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_low_period> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_ctr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_sr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_to> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_slave_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_rxfifo_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_fifo_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_data> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_int_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_sda_hold> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_sda_sample> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_high_period> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_start_hold> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_rstart_setup> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_stop_hold> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_stop_setup> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_filter_cfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_sda_filter_cfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_comd_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 248u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_fifo_start_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF67000u;
  static constexpr std::uint32_t kOffsetBytes = 256u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_read_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_read_status1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_meas_wait1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_meas_wait2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_meas_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_read_status2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_ulp_cp_sleep_cyc0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_ulp_cp_sleep_cyc1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_ulp_cp_sleep_cyc2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_ulp_cp_sleep_cyc3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_ulp_cp_sleep_cyc4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_start_force> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_mem_wr_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_atten1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_atten2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_slave_addr1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_slave_addr2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_slave_addr3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_slave_addr4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_tsens_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_i2c_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_meas_start1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_ctrl1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 104u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 108u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_out1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 112u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_out2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 116u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_out3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_out4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_out5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 132u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_enable> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 140u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_read_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 144u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_meas_start2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 148u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_dac_ctrl1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 152u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_dac_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 156u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_meas_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 160u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_nouse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 248u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sardate> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF48800u;
  static constexpr std::uint32_t kOffsetBytes = 252u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ctrl1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_rd_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_clock> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_user> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_user1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_user2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_mosi_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_miso_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_slv_wr_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_pin> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_slave> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_slave1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_slave2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_slave3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_slv_wrbuf_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_slv_rdbuf_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_cache_fctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_cache_sctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_sram_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_sram_drd_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_sram_dwr_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_slv_rd_bit> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 132u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 136u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 140u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 144u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 148u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 152u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 156u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w8> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 160u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w9> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 164u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w10> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 168u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w11> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 172u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w12> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 176u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w13> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 180u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w14> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 184u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_w15> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 188u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_tx_crc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 192u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ext0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 240u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ext1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 244u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ext2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 248u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ext3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 252u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_dma_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 256u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_dma_out_link> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 260u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_dma_in_link> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 264u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_dma_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 268u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_dma_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 272u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_dma_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 276u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_dma_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 280u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_dma_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 284u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_in_err_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 288u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_in_suc_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 292u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_inlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 296u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_inlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 300u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_inlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 304u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_out_eof_bfr_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 308u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_out_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 312u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_outlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 316u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_outlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 320u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_outlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 324u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_dma_rstatus> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 328u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_dma_tstatus> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 332u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF43000u;
  static constexpr std::uint32_t kOffsetBytes = 1020u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_ctrl1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_rd_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_clock> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_user> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_user1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_user2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_mosi_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_miso_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_slv_wr_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_pin> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_slave> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_slave1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_slave2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_slave3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_slv_wrbuf_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_slv_rdbuf_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_cache_fctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_cache_sctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_sram_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_sram_drd_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_sram_dwr_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_slv_rd_bit> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 132u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 136u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 140u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 144u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 148u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 152u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 156u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w8> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 160u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w9> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 164u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w10> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 168u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w11> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 172u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w12> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 176u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w13> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 180u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w14> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 184u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_w15> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 188u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_tx_crc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 192u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_ext0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 240u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_ext1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 244u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_ext2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 248u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_ext3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 252u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_dma_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 256u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_dma_out_link> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 260u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_dma_in_link> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 264u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_dma_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 268u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_dma_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 272u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_dma_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 276u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_dma_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 280u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_dma_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 284u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_in_err_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 288u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_in_suc_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 292u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_inlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 296u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_inlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 300u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_inlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 304u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_out_eof_bfr_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 308u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_out_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 312u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_outlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 316u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_outlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 320u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_outlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 324u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_dma_rstatus> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 328u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_dma_tstatus> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 332u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF42000u;
  static constexpr std::uint32_t kOffsetBytes = 1020u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_ctrl1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_rd_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_clock> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_user> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_user1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_user2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_mosi_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_miso_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_slv_wr_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_pin> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_slave> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_slave1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_slave2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_slave3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_slv_wrbuf_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_slv_rdbuf_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_cache_fctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_cache_sctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_sram_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_sram_drd_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_sram_dwr_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_slv_rd_bit> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 132u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 136u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 140u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 144u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 148u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 152u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 156u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w8> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 160u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w9> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 164u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w10> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 168u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w11> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 172u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w12> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 176u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w13> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 180u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w14> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 184u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_w15> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 188u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_tx_crc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 192u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_ext0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 240u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_ext1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 244u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_ext2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 248u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_ext3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 252u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 256u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_out_link> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 260u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_in_link> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 264u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 268u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 272u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 276u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 280u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 284u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_in_err_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 288u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_in_suc_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 292u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_inlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 296u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_inlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 300u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_inlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 304u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_out_eof_bfr_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 308u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_out_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 312u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_outlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 316u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_outlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 320u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_outlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 324u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_rstatus> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 328u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_dma_tstatus> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 332u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi2_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF64000u;
  static constexpr std::uint32_t kOffsetBytes = 1020u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_ctrl1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_rd_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_clock> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_user> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_user1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_user2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_mosi_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_miso_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_slv_wr_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_pin> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_slave> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_slave1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_slave2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_slave3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_slv_wrbuf_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_slv_rdbuf_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_cache_fctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_cache_sctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_sram_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_sram_drd_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_sram_dwr_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_slv_rd_bit> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 132u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 136u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 140u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 144u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 148u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 152u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 156u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w8> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 160u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w9> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 164u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w10> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 168u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w11> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 172u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w12> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 176u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w13> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 180u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w14> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 184u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w15> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 188u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_tx_crc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 192u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_ext0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 240u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_ext1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 244u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_ext2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 248u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_ext3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 252u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 256u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_out_link> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 260u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_in_link> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 264u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 268u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 272u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 276u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 280u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 284u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_in_err_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 288u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_in_suc_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 292u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_inlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 296u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_inlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 300u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_inlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 304u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_out_eof_bfr_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 308u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_out_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 312u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_outlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 316u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_outlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 320u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_outlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 324u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_rstatus> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 328u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_tstatus> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 332u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF65000u;
  static constexpr std::uint32_t kOffsetBytes = 1020u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_fifo> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_clkdiv> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_autobaud> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_conf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_conf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_lowpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_highpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_rxd_cnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_flow_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_sleep_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_swfc_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_idle_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_rs485_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_at_cmd_precnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_at_cmd_postcnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_at_cmd_gaptout> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_at_cmd_char> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_mem_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_mem_tx_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_mem_rx_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_mem_cnt_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_pospulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 104u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_negpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 108u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart0_id> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF40000u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_fifo> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_clkdiv> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_autobaud> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_conf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_conf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_lowpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_highpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_rxd_cnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_flow_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_sleep_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_swfc_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_idle_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_rs485_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_at_cmd_precnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_at_cmd_postcnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_at_cmd_gaptout> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_at_cmd_char> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_mem_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_mem_tx_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_mem_rx_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_mem_cnt_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_pospulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 104u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_negpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 108u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart1_id> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF50000u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_fifo> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_clkdiv> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_autobaud> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_conf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_conf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_lowpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_highpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_rxd_cnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_flow_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_sleep_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_swfc_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_idle_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_rs485_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_at_cmd_precnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_at_cmd_postcnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_at_cmd_gaptout> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_at_cmd_char> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_mem_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_mem_tx_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_mem_rx_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_mem_cnt_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_pospulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 104u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_negpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 108u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_id> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x3FF6E000u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

inline constexpr std::array<RegisterId, 492> kRegisters = {{
  RegisterId::register_dport_appcpu_ctrl_b,
  RegisterId::register_dport_perip_clk_en,
  RegisterId::register_gpio_bt_select,
  RegisterId::register_gpio_out,
  RegisterId::register_gpio_out_w1ts,
  RegisterId::register_gpio_out_w1tc,
  RegisterId::register_gpio_out1,
  RegisterId::register_gpio_out1_w1ts,
  RegisterId::register_gpio_out1_w1tc,
  RegisterId::register_gpio_sdio_select,
  RegisterId::register_gpio_enable,
  RegisterId::register_gpio_enable_w1ts,
  RegisterId::register_gpio_enable_w1tc,
  RegisterId::register_gpio_enable1,
  RegisterId::register_gpio_enable1_w1ts,
  RegisterId::register_gpio_enable1_w1tc,
  RegisterId::register_gpio_strap,
  RegisterId::register_gpio_in,
  RegisterId::register_gpio_in1,
  RegisterId::register_gpio_status,
  RegisterId::register_gpio_status_w1ts,
  RegisterId::register_gpio_status_w1tc,
  RegisterId::register_gpio_status1,
  RegisterId::register_gpio_status1_w1ts,
  RegisterId::register_gpio_status1_w1tc,
  RegisterId::register_gpio_acpu_int,
  RegisterId::register_gpio_acpu_nmi_int,
  RegisterId::register_gpio_pcpu_int,
  RegisterId::register_gpio_pcpu_nmi_int,
  RegisterId::register_gpio_cpusdio_int,
  RegisterId::register_gpio_acpu_int1,
  RegisterId::register_gpio_acpu_nmi_int1,
  RegisterId::register_gpio_pcpu_int1,
  RegisterId::register_gpio_pcpu_nmi_int1,
  RegisterId::register_gpio_cpusdio_int1,
  RegisterId::register_gpio_pin_s,
  RegisterId::register_gpio_cali_conf,
  RegisterId::register_gpio_cali_data,
  RegisterId::register_gpio_func_s_in_sel_cfg,
  RegisterId::register_gpio_func_s_out_sel_cfg,
  RegisterId::register_i2c0_scl_low_period,
  RegisterId::register_i2c0_ctr,
  RegisterId::register_i2c0_sr,
  RegisterId::register_i2c0_to,
  RegisterId::register_i2c0_slave_addr,
  RegisterId::register_i2c0_rxfifo_st,
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
  RegisterId::register_i2c0_scl_filter_cfg,
  RegisterId::register_i2c0_sda_filter_cfg,
  RegisterId::register_i2c0_comd_s,
  RegisterId::register_i2c0_date,
  RegisterId::register_i2c0_fifo_start_addr,
  RegisterId::register_i2c1_scl_low_period,
  RegisterId::register_i2c1_ctr,
  RegisterId::register_i2c1_sr,
  RegisterId::register_i2c1_to,
  RegisterId::register_i2c1_slave_addr,
  RegisterId::register_i2c1_rxfifo_st,
  RegisterId::register_i2c1_fifo_conf,
  RegisterId::register_i2c1_data,
  RegisterId::register_i2c1_int_raw,
  RegisterId::register_i2c1_int_clr,
  RegisterId::register_i2c1_int_ena,
  RegisterId::register_i2c1_int_status,
  RegisterId::register_i2c1_sda_hold,
  RegisterId::register_i2c1_sda_sample,
  RegisterId::register_i2c1_scl_high_period,
  RegisterId::register_i2c1_scl_start_hold,
  RegisterId::register_i2c1_scl_rstart_setup,
  RegisterId::register_i2c1_scl_stop_hold,
  RegisterId::register_i2c1_scl_stop_setup,
  RegisterId::register_i2c1_scl_filter_cfg,
  RegisterId::register_i2c1_sda_filter_cfg,
  RegisterId::register_i2c1_comd_s,
  RegisterId::register_i2c1_date,
  RegisterId::register_i2c1_fifo_start_addr,
  RegisterId::register_sens_sar_read_ctrl,
  RegisterId::register_sens_sar_read_status1,
  RegisterId::register_sens_sar_meas_wait1,
  RegisterId::register_sens_sar_meas_wait2,
  RegisterId::register_sens_sar_meas_ctrl,
  RegisterId::register_sens_sar_read_status2,
  RegisterId::register_sens_ulp_cp_sleep_cyc0,
  RegisterId::register_sens_ulp_cp_sleep_cyc1,
  RegisterId::register_sens_ulp_cp_sleep_cyc2,
  RegisterId::register_sens_ulp_cp_sleep_cyc3,
  RegisterId::register_sens_ulp_cp_sleep_cyc4,
  RegisterId::register_sens_sar_start_force,
  RegisterId::register_sens_sar_mem_wr_ctrl,
  RegisterId::register_sens_sar_atten1,
  RegisterId::register_sens_sar_atten2,
  RegisterId::register_sens_sar_slave_addr1,
  RegisterId::register_sens_sar_slave_addr2,
  RegisterId::register_sens_sar_slave_addr3,
  RegisterId::register_sens_sar_slave_addr4,
  RegisterId::register_sens_sar_tsens_ctrl,
  RegisterId::register_sens_sar_i2c_ctrl,
  RegisterId::register_sens_sar_meas_start1,
  RegisterId::register_sens_sar_touch_ctrl1,
  RegisterId::register_sens_sar_touch_thres1,
  RegisterId::register_sens_sar_touch_thres2,
  RegisterId::register_sens_sar_touch_thres3,
  RegisterId::register_sens_sar_touch_thres4,
  RegisterId::register_sens_sar_touch_thres5,
  RegisterId::register_sens_sar_touch_out1,
  RegisterId::register_sens_sar_touch_out2,
  RegisterId::register_sens_sar_touch_out3,
  RegisterId::register_sens_sar_touch_out4,
  RegisterId::register_sens_sar_touch_out5,
  RegisterId::register_sens_sar_touch_ctrl2,
  RegisterId::register_sens_sar_touch_enable,
  RegisterId::register_sens_sar_read_ctrl2,
  RegisterId::register_sens_sar_meas_start2,
  RegisterId::register_sens_sar_dac_ctrl1,
  RegisterId::register_sens_sar_dac_ctrl2,
  RegisterId::register_sens_sar_meas_ctrl2,
  RegisterId::register_sens_sar_nouse,
  RegisterId::register_sens_sardate,
  RegisterId::register_spi0_cmd,
  RegisterId::register_spi0_addr,
  RegisterId::register_spi0_ctrl,
  RegisterId::register_spi0_ctrl1,
  RegisterId::register_spi0_rd_status,
  RegisterId::register_spi0_ctrl2,
  RegisterId::register_spi0_clock,
  RegisterId::register_spi0_user,
  RegisterId::register_spi0_user1,
  RegisterId::register_spi0_user2,
  RegisterId::register_spi0_mosi_dlen,
  RegisterId::register_spi0_miso_dlen,
  RegisterId::register_spi0_slv_wr_status,
  RegisterId::register_spi0_pin,
  RegisterId::register_spi0_slave,
  RegisterId::register_spi0_slave1,
  RegisterId::register_spi0_slave2,
  RegisterId::register_spi0_slave3,
  RegisterId::register_spi0_slv_wrbuf_dlen,
  RegisterId::register_spi0_slv_rdbuf_dlen,
  RegisterId::register_spi0_cache_fctrl,
  RegisterId::register_spi0_cache_sctrl,
  RegisterId::register_spi0_sram_cmd,
  RegisterId::register_spi0_sram_drd_cmd,
  RegisterId::register_spi0_sram_dwr_cmd,
  RegisterId::register_spi0_slv_rd_bit,
  RegisterId::register_spi0_w0,
  RegisterId::register_spi0_w1,
  RegisterId::register_spi0_w2,
  RegisterId::register_spi0_w3,
  RegisterId::register_spi0_w4,
  RegisterId::register_spi0_w5,
  RegisterId::register_spi0_w6,
  RegisterId::register_spi0_w7,
  RegisterId::register_spi0_w8,
  RegisterId::register_spi0_w9,
  RegisterId::register_spi0_w10,
  RegisterId::register_spi0_w11,
  RegisterId::register_spi0_w12,
  RegisterId::register_spi0_w13,
  RegisterId::register_spi0_w14,
  RegisterId::register_spi0_w15,
  RegisterId::register_spi0_tx_crc,
  RegisterId::register_spi0_ext0,
  RegisterId::register_spi0_ext1,
  RegisterId::register_spi0_ext2,
  RegisterId::register_spi0_ext3,
  RegisterId::register_spi0_dma_conf,
  RegisterId::register_spi0_dma_out_link,
  RegisterId::register_spi0_dma_in_link,
  RegisterId::register_spi0_dma_status,
  RegisterId::register_spi0_dma_int_ena,
  RegisterId::register_spi0_dma_int_raw,
  RegisterId::register_spi0_dma_int_st,
  RegisterId::register_spi0_dma_int_clr,
  RegisterId::register_spi0_in_err_eof_des_addr,
  RegisterId::register_spi0_in_suc_eof_des_addr,
  RegisterId::register_spi0_inlink_dscr,
  RegisterId::register_spi0_inlink_dscr_bf0,
  RegisterId::register_spi0_inlink_dscr_bf1,
  RegisterId::register_spi0_out_eof_bfr_des_addr,
  RegisterId::register_spi0_out_eof_des_addr,
  RegisterId::register_spi0_outlink_dscr,
  RegisterId::register_spi0_outlink_dscr_bf0,
  RegisterId::register_spi0_outlink_dscr_bf1,
  RegisterId::register_spi0_dma_rstatus,
  RegisterId::register_spi0_dma_tstatus,
  RegisterId::register_spi0_date,
  RegisterId::register_spi1_cmd,
  RegisterId::register_spi1_addr,
  RegisterId::register_spi1_ctrl,
  RegisterId::register_spi1_ctrl1,
  RegisterId::register_spi1_rd_status,
  RegisterId::register_spi1_ctrl2,
  RegisterId::register_spi1_clock,
  RegisterId::register_spi1_user,
  RegisterId::register_spi1_user1,
  RegisterId::register_spi1_user2,
  RegisterId::register_spi1_mosi_dlen,
  RegisterId::register_spi1_miso_dlen,
  RegisterId::register_spi1_slv_wr_status,
  RegisterId::register_spi1_pin,
  RegisterId::register_spi1_slave,
  RegisterId::register_spi1_slave1,
  RegisterId::register_spi1_slave2,
  RegisterId::register_spi1_slave3,
  RegisterId::register_spi1_slv_wrbuf_dlen,
  RegisterId::register_spi1_slv_rdbuf_dlen,
  RegisterId::register_spi1_cache_fctrl,
  RegisterId::register_spi1_cache_sctrl,
  RegisterId::register_spi1_sram_cmd,
  RegisterId::register_spi1_sram_drd_cmd,
  RegisterId::register_spi1_sram_dwr_cmd,
  RegisterId::register_spi1_slv_rd_bit,
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
  RegisterId::register_spi1_tx_crc,
  RegisterId::register_spi1_ext0,
  RegisterId::register_spi1_ext1,
  RegisterId::register_spi1_ext2,
  RegisterId::register_spi1_ext3,
  RegisterId::register_spi1_dma_conf,
  RegisterId::register_spi1_dma_out_link,
  RegisterId::register_spi1_dma_in_link,
  RegisterId::register_spi1_dma_status,
  RegisterId::register_spi1_dma_int_ena,
  RegisterId::register_spi1_dma_int_raw,
  RegisterId::register_spi1_dma_int_st,
  RegisterId::register_spi1_dma_int_clr,
  RegisterId::register_spi1_in_err_eof_des_addr,
  RegisterId::register_spi1_in_suc_eof_des_addr,
  RegisterId::register_spi1_inlink_dscr,
  RegisterId::register_spi1_inlink_dscr_bf0,
  RegisterId::register_spi1_inlink_dscr_bf1,
  RegisterId::register_spi1_out_eof_bfr_des_addr,
  RegisterId::register_spi1_out_eof_des_addr,
  RegisterId::register_spi1_outlink_dscr,
  RegisterId::register_spi1_outlink_dscr_bf0,
  RegisterId::register_spi1_outlink_dscr_bf1,
  RegisterId::register_spi1_dma_rstatus,
  RegisterId::register_spi1_dma_tstatus,
  RegisterId::register_spi1_date,
  RegisterId::register_spi2_cmd,
  RegisterId::register_spi2_addr,
  RegisterId::register_spi2_ctrl,
  RegisterId::register_spi2_ctrl1,
  RegisterId::register_spi2_rd_status,
  RegisterId::register_spi2_ctrl2,
  RegisterId::register_spi2_clock,
  RegisterId::register_spi2_user,
  RegisterId::register_spi2_user1,
  RegisterId::register_spi2_user2,
  RegisterId::register_spi2_mosi_dlen,
  RegisterId::register_spi2_miso_dlen,
  RegisterId::register_spi2_slv_wr_status,
  RegisterId::register_spi2_pin,
  RegisterId::register_spi2_slave,
  RegisterId::register_spi2_slave1,
  RegisterId::register_spi2_slave2,
  RegisterId::register_spi2_slave3,
  RegisterId::register_spi2_slv_wrbuf_dlen,
  RegisterId::register_spi2_slv_rdbuf_dlen,
  RegisterId::register_spi2_cache_fctrl,
  RegisterId::register_spi2_cache_sctrl,
  RegisterId::register_spi2_sram_cmd,
  RegisterId::register_spi2_sram_drd_cmd,
  RegisterId::register_spi2_sram_dwr_cmd,
  RegisterId::register_spi2_slv_rd_bit,
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
  RegisterId::register_spi2_tx_crc,
  RegisterId::register_spi2_ext0,
  RegisterId::register_spi2_ext1,
  RegisterId::register_spi2_ext2,
  RegisterId::register_spi2_ext3,
  RegisterId::register_spi2_dma_conf,
  RegisterId::register_spi2_dma_out_link,
  RegisterId::register_spi2_dma_in_link,
  RegisterId::register_spi2_dma_status,
  RegisterId::register_spi2_dma_int_ena,
  RegisterId::register_spi2_dma_int_raw,
  RegisterId::register_spi2_dma_int_st,
  RegisterId::register_spi2_dma_int_clr,
  RegisterId::register_spi2_in_err_eof_des_addr,
  RegisterId::register_spi2_in_suc_eof_des_addr,
  RegisterId::register_spi2_inlink_dscr,
  RegisterId::register_spi2_inlink_dscr_bf0,
  RegisterId::register_spi2_inlink_dscr_bf1,
  RegisterId::register_spi2_out_eof_bfr_des_addr,
  RegisterId::register_spi2_out_eof_des_addr,
  RegisterId::register_spi2_outlink_dscr,
  RegisterId::register_spi2_outlink_dscr_bf0,
  RegisterId::register_spi2_outlink_dscr_bf1,
  RegisterId::register_spi2_dma_rstatus,
  RegisterId::register_spi2_dma_tstatus,
  RegisterId::register_spi2_date,
  RegisterId::register_spi3_cmd,
  RegisterId::register_spi3_addr,
  RegisterId::register_spi3_ctrl,
  RegisterId::register_spi3_ctrl1,
  RegisterId::register_spi3_rd_status,
  RegisterId::register_spi3_ctrl2,
  RegisterId::register_spi3_clock,
  RegisterId::register_spi3_user,
  RegisterId::register_spi3_user1,
  RegisterId::register_spi3_user2,
  RegisterId::register_spi3_mosi_dlen,
  RegisterId::register_spi3_miso_dlen,
  RegisterId::register_spi3_slv_wr_status,
  RegisterId::register_spi3_pin,
  RegisterId::register_spi3_slave,
  RegisterId::register_spi3_slave1,
  RegisterId::register_spi3_slave2,
  RegisterId::register_spi3_slave3,
  RegisterId::register_spi3_slv_wrbuf_dlen,
  RegisterId::register_spi3_slv_rdbuf_dlen,
  RegisterId::register_spi3_cache_fctrl,
  RegisterId::register_spi3_cache_sctrl,
  RegisterId::register_spi3_sram_cmd,
  RegisterId::register_spi3_sram_drd_cmd,
  RegisterId::register_spi3_sram_dwr_cmd,
  RegisterId::register_spi3_slv_rd_bit,
  RegisterId::register_spi3_w0,
  RegisterId::register_spi3_w1,
  RegisterId::register_spi3_w2,
  RegisterId::register_spi3_w3,
  RegisterId::register_spi3_w4,
  RegisterId::register_spi3_w5,
  RegisterId::register_spi3_w6,
  RegisterId::register_spi3_w7,
  RegisterId::register_spi3_w8,
  RegisterId::register_spi3_w9,
  RegisterId::register_spi3_w10,
  RegisterId::register_spi3_w11,
  RegisterId::register_spi3_w12,
  RegisterId::register_spi3_w13,
  RegisterId::register_spi3_w14,
  RegisterId::register_spi3_w15,
  RegisterId::register_spi3_tx_crc,
  RegisterId::register_spi3_ext0,
  RegisterId::register_spi3_ext1,
  RegisterId::register_spi3_ext2,
  RegisterId::register_spi3_ext3,
  RegisterId::register_spi3_dma_conf,
  RegisterId::register_spi3_dma_out_link,
  RegisterId::register_spi3_dma_in_link,
  RegisterId::register_spi3_dma_status,
  RegisterId::register_spi3_dma_int_ena,
  RegisterId::register_spi3_dma_int_raw,
  RegisterId::register_spi3_dma_int_st,
  RegisterId::register_spi3_dma_int_clr,
  RegisterId::register_spi3_in_err_eof_des_addr,
  RegisterId::register_spi3_in_suc_eof_des_addr,
  RegisterId::register_spi3_inlink_dscr,
  RegisterId::register_spi3_inlink_dscr_bf0,
  RegisterId::register_spi3_inlink_dscr_bf1,
  RegisterId::register_spi3_out_eof_bfr_des_addr,
  RegisterId::register_spi3_out_eof_des_addr,
  RegisterId::register_spi3_outlink_dscr,
  RegisterId::register_spi3_outlink_dscr_bf0,
  RegisterId::register_spi3_outlink_dscr_bf1,
  RegisterId::register_spi3_dma_rstatus,
  RegisterId::register_spi3_dma_tstatus,
  RegisterId::register_spi3_date,
  RegisterId::register_uart0_fifo,
  RegisterId::register_uart0_int_raw,
  RegisterId::register_uart0_int_st,
  RegisterId::register_uart0_int_ena,
  RegisterId::register_uart0_int_clr,
  RegisterId::register_uart0_clkdiv,
  RegisterId::register_uart0_autobaud,
  RegisterId::register_uart0_status,
  RegisterId::register_uart0_conf0,
  RegisterId::register_uart0_conf1,
  RegisterId::register_uart0_lowpulse,
  RegisterId::register_uart0_highpulse,
  RegisterId::register_uart0_rxd_cnt,
  RegisterId::register_uart0_flow_conf,
  RegisterId::register_uart0_sleep_conf,
  RegisterId::register_uart0_swfc_conf,
  RegisterId::register_uart0_idle_conf,
  RegisterId::register_uart0_rs485_conf,
  RegisterId::register_uart0_at_cmd_precnt,
  RegisterId::register_uart0_at_cmd_postcnt,
  RegisterId::register_uart0_at_cmd_gaptout,
  RegisterId::register_uart0_at_cmd_char,
  RegisterId::register_uart0_mem_conf,
  RegisterId::register_uart0_mem_tx_status,
  RegisterId::register_uart0_mem_rx_status,
  RegisterId::register_uart0_mem_cnt_status,
  RegisterId::register_uart0_pospulse,
  RegisterId::register_uart0_negpulse,
  RegisterId::register_uart0_date,
  RegisterId::register_uart0_id,
  RegisterId::register_uart1_fifo,
  RegisterId::register_uart1_int_raw,
  RegisterId::register_uart1_int_st,
  RegisterId::register_uart1_int_ena,
  RegisterId::register_uart1_int_clr,
  RegisterId::register_uart1_clkdiv,
  RegisterId::register_uart1_autobaud,
  RegisterId::register_uart1_status,
  RegisterId::register_uart1_conf0,
  RegisterId::register_uart1_conf1,
  RegisterId::register_uart1_lowpulse,
  RegisterId::register_uart1_highpulse,
  RegisterId::register_uart1_rxd_cnt,
  RegisterId::register_uart1_flow_conf,
  RegisterId::register_uart1_sleep_conf,
  RegisterId::register_uart1_swfc_conf,
  RegisterId::register_uart1_idle_conf,
  RegisterId::register_uart1_rs485_conf,
  RegisterId::register_uart1_at_cmd_precnt,
  RegisterId::register_uart1_at_cmd_postcnt,
  RegisterId::register_uart1_at_cmd_gaptout,
  RegisterId::register_uart1_at_cmd_char,
  RegisterId::register_uart1_mem_conf,
  RegisterId::register_uart1_mem_tx_status,
  RegisterId::register_uart1_mem_rx_status,
  RegisterId::register_uart1_mem_cnt_status,
  RegisterId::register_uart1_pospulse,
  RegisterId::register_uart1_negpulse,
  RegisterId::register_uart1_date,
  RegisterId::register_uart1_id,
  RegisterId::register_uart2_fifo,
  RegisterId::register_uart2_int_raw,
  RegisterId::register_uart2_int_st,
  RegisterId::register_uart2_int_ena,
  RegisterId::register_uart2_int_clr,
  RegisterId::register_uart2_clkdiv,
  RegisterId::register_uart2_autobaud,
  RegisterId::register_uart2_status,
  RegisterId::register_uart2_conf0,
  RegisterId::register_uart2_conf1,
  RegisterId::register_uart2_lowpulse,
  RegisterId::register_uart2_highpulse,
  RegisterId::register_uart2_rxd_cnt,
  RegisterId::register_uart2_flow_conf,
  RegisterId::register_uart2_sleep_conf,
  RegisterId::register_uart2_swfc_conf,
  RegisterId::register_uart2_idle_conf,
  RegisterId::register_uart2_rs485_conf,
  RegisterId::register_uart2_at_cmd_precnt,
  RegisterId::register_uart2_at_cmd_postcnt,
  RegisterId::register_uart2_at_cmd_gaptout,
  RegisterId::register_uart2_at_cmd_char,
  RegisterId::register_uart2_mem_conf,
  RegisterId::register_uart2_mem_tx_status,
  RegisterId::register_uart2_mem_rx_status,
  RegisterId::register_uart2_mem_cnt_status,
  RegisterId::register_uart2_pospulse,
  RegisterId::register_uart2_negpulse,
  RegisterId::register_uart2_date,
  RegisterId::register_uart2_id,
}};
}
}
}
}
}
}
