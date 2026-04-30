#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace espressif {
namespace esp32s3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32s3 {
enum class RegisterId : std::uint16_t {
  none,
  register_apb_saradc_ctrl,
  register_apb_saradc_ctrl2,
  register_apb_saradc_filter_ctrl1,
  register_apb_saradc_fsm_wait,
  register_apb_saradc_sar1_status,
  register_apb_saradc_sar2_status,
  register_apb_saradc_sar1_patt_tab1,
  register_apb_saradc_sar1_patt_tab2,
  register_apb_saradc_sar1_patt_tab3,
  register_apb_saradc_sar1_patt_tab4,
  register_apb_saradc_sar2_patt_tab1,
  register_apb_saradc_sar2_patt_tab2,
  register_apb_saradc_sar2_patt_tab3,
  register_apb_saradc_sar2_patt_tab4,
  register_apb_saradc_arb_ctrl,
  register_apb_saradc_filter_ctrl0,
  register_apb_saradc_apb_saradc1_data_status,
  register_apb_saradc_thres0_ctrl,
  register_apb_saradc_thres1_ctrl,
  register_apb_saradc_thres_ctrl,
  register_apb_saradc_int_ena,
  register_apb_saradc_int_raw,
  register_apb_saradc_int_st,
  register_apb_saradc_int_clr,
  register_apb_saradc_dma_conf,
  register_apb_saradc_clkm_conf,
  register_apb_saradc_apb_saradc2_data_status,
  register_apb_saradc_apb_ctrl_date,
  register_dma_in_conf0_ch_s,
  register_dma_in_conf1_ch_s,
  register_dma_in_int_raw_ch_s,
  register_dma_in_int_st_ch_s,
  register_dma_in_int_ena_ch_s,
  register_dma_in_int_clr_ch_s,
  register_dma_infifo_status_ch_s,
  register_dma_in_pop_ch_s,
  register_dma_in_link_ch_s,
  register_dma_in_state_ch_s,
  register_dma_in_suc_eof_des_addr_ch_s,
  register_dma_in_err_eof_des_addr_ch_s,
  register_dma_in_dscr_ch_s,
  register_dma_in_dscr_bf0_ch_s,
  register_dma_in_dscr_bf1_ch_s,
  register_dma_in_wight_ch_s,
  register_dma_in_pri_ch_s,
  register_dma_in_peri_sel_ch_s,
  register_dma_out_conf0_ch_s,
  register_dma_out_conf1_ch_s,
  register_dma_out_int_raw_ch_s,
  register_dma_out_int_st_ch_s,
  register_dma_out_int_ena_ch_s,
  register_dma_out_int_clr_ch_s,
  register_dma_outfifo_status_ch_s,
  register_dma_out_push_ch_s,
  register_dma_out_link_ch_s,
  register_dma_out_state_ch_s,
  register_dma_out_eof_des_addr_ch_s,
  register_dma_out_eof_bfr_des_addr_ch_s,
  register_dma_out_dscr_ch_s,
  register_dma_out_dscr_bf0_ch_s,
  register_dma_out_dscr_bf1_ch_s,
  register_dma_out_wight_ch_s,
  register_dma_out_pri_ch_s,
  register_dma_out_peri_sel_ch_s,
  register_dma_ahb_test,
  register_dma_pd_conf,
  register_dma_misc_conf,
  register_dma_in_sram_size_ch_s,
  register_dma_out_sram_size_ch_s,
  register_dma_extmem_reject_addr,
  register_dma_extmem_reject_st,
  register_dma_extmem_reject_int_raw,
  register_dma_extmem_reject_int_st,
  register_dma_extmem_reject_int_ena,
  register_dma_extmem_reject_int_clr,
  register_dma_date,
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
  register_gpio_pcpu_int,
  register_gpio_pcpu_nmi_int,
  register_gpio_cpusdio_int,
  register_gpio_pcpu_int1,
  register_gpio_pcpu_nmi_int1,
  register_gpio_cpusdio_int1,
  register_gpio_pin_s,
  register_gpio_status_next,
  register_gpio_status_next1,
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
  register_i2c1_scl_low_period,
  register_i2c1_ctr,
  register_i2c1_sr,
  register_i2c1_to,
  register_i2c1_slave_addr,
  register_i2c1_fifo_st,
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
  register_i2c1_filter_cfg,
  register_i2c1_clk_conf,
  register_i2c1_comd_s,
  register_i2c1_scl_st_time_out,
  register_i2c1_scl_main_st_time_out,
  register_i2c1_scl_sp_conf,
  register_i2c1_scl_stretch_conf,
  register_i2c1_date,
  register_i2c1_txfifo_start_addr,
  register_i2c1_rxfifo_start_addr,
  register_sens_sar_reader1_ctrl,
  register_sens_sar_reader1_status,
  register_sens_sar_meas1_ctrl1,
  register_sens_sar_meas1_ctrl2,
  register_sens_sar_meas1_mux,
  register_sens_sar_atten1,
  register_sens_sar_amp_ctrl1,
  register_sens_sar_amp_ctrl2,
  register_sens_sar_amp_ctrl3,
  register_sens_sar_reader2_ctrl,
  register_sens_sar_reader2_status,
  register_sens_sar_meas2_ctrl1,
  register_sens_sar_meas2_ctrl2,
  register_sens_sar_meas2_mux,
  register_sens_sar_atten2,
  register_sens_sar_power_xpd_sar,
  register_sens_sar_slave_addr1,
  register_sens_sar_slave_addr2,
  register_sens_sar_slave_addr3,
  register_sens_sar_slave_addr4,
  register_sens_sar_tsens_ctrl,
  register_sens_sar_tsens_ctrl2,
  register_sens_sar_i2c_ctrl,
  register_sens_sar_touch_conf,
  register_sens_sar_touch_denoise,
  register_sens_sar_touch_thres1,
  register_sens_sar_touch_thres2,
  register_sens_sar_touch_thres3,
  register_sens_sar_touch_thres4,
  register_sens_sar_touch_thres5,
  register_sens_sar_touch_thres6,
  register_sens_sar_touch_thres7,
  register_sens_sar_touch_thres8,
  register_sens_sar_touch_thres9,
  register_sens_sar_touch_thres10,
  register_sens_sar_touch_thres11,
  register_sens_sar_touch_thres12,
  register_sens_sar_touch_thres13,
  register_sens_sar_touch_thres14,
  register_sens_sar_touch_chn_st,
  register_sens_sar_touch_status0,
  register_sens_sar_touch_status1,
  register_sens_sar_touch_status2,
  register_sens_sar_touch_status3,
  register_sens_sar_touch_status4,
  register_sens_sar_touch_status5,
  register_sens_sar_touch_status6,
  register_sens_sar_touch_status7,
  register_sens_sar_touch_status8,
  register_sens_sar_touch_status9,
  register_sens_sar_touch_status10,
  register_sens_sar_touch_status11,
  register_sens_sar_touch_status12,
  register_sens_sar_touch_status13,
  register_sens_sar_touch_status14,
  register_sens_sar_touch_status15,
  register_sens_sar_touch_status16,
  register_sens_sar_cocpu_state,
  register_sens_sar_cocpu_int_raw,
  register_sens_sar_cocpu_int_ena,
  register_sens_sar_cocpu_int_st,
  register_sens_sar_cocpu_int_clr,
  register_sens_sar_cocpu_debug,
  register_sens_sar_hall_ctrl,
  register_sens_sar_nouse,
  register_sens_sar_peri_clk_gate_conf,
  register_sens_sar_peri_reset_conf,
  register_sens_sar_cocpu_int_ena_w1ts,
  register_sens_sar_cocpu_int_ena_w1tc,
  register_sens_sar_debug_conf,
  register_sens_sar_sardate,
  register_spi0_ctrl,
  register_spi0_ctrl1,
  register_spi0_ctrl2,
  register_spi0_clock,
  register_spi0_user,
  register_spi0_user1,
  register_spi0_user2,
  register_spi0_rd_status,
  register_spi0_ext_addr,
  register_spi0_misc,
  register_spi0_cache_fctrl,
  register_spi0_cache_sctrl,
  register_spi0_sram_cmd,
  register_spi0_sram_drd_cmd,
  register_spi0_sram_dwr_cmd,
  register_spi0_sram_clk,
  register_spi0_fsm,
  register_spi0_timing_cali,
  register_spi0_din_mode,
  register_spi0_din_num,
  register_spi0_dout_mode,
  register_spi0_spi_smem_timing_cali,
  register_spi0_spi_smem_din_mode,
  register_spi0_spi_smem_din_num,
  register_spi0_spi_smem_dout_mode,
  register_spi0_ecc_ctrl,
  register_spi0_ecc_err_addr,
  register_spi0_ecc_err_bit,
  register_spi0_spi_smem_ac,
  register_spi0_ddr,
  register_spi0_spi_smem_ddr,
  register_spi0_clock_gate,
  register_spi0_core_clk_sel,
  register_spi0_int_ena,
  register_spi0_int_clr,
  register_spi0_int_raw,
  register_spi0_int_st,
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
  register_spi1_ext_addr,
  register_spi1_misc,
  register_spi1_tx_crc,
  register_spi1_cache_fctrl,
  register_spi1_fsm,
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
  register_spi1_flash_sus_cmd,
  register_spi1_flash_sus_ctrl,
  register_spi1_sus_status,
  register_spi1_timing_cali,
  register_spi1_ddr,
  register_spi1_clock_gate,
  register_spi1_int_ena,
  register_spi1_int_clr,
  register_spi1_int_raw,
  register_spi1_int_st,
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
  register_spi2_dma_int_set,
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
  register_spi3_cmd,
  register_spi3_addr,
  register_spi3_ctrl,
  register_spi3_clock,
  register_spi3_user,
  register_spi3_user1,
  register_spi3_user2,
  register_spi3_ms_dlen,
  register_spi3_misc,
  register_spi3_din_mode,
  register_spi3_din_num,
  register_spi3_dout_mode,
  register_spi3_dma_conf,
  register_spi3_dma_int_ena,
  register_spi3_dma_int_clr,
  register_spi3_dma_int_raw,
  register_spi3_dma_int_st,
  register_spi3_dma_int_set,
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
  register_spi3_slave,
  register_spi3_slave1,
  register_spi3_clk_gate,
  register_spi3_date,
  register_system_core_1_control_0,
  register_system_core_1_control_1,
  register_system_perip_clk_en0,
  register_system_perip_clk_en1,
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
  register_uart2_fifo,
  register_uart2_int_raw,
  register_uart2_int_st,
  register_uart2_int_ena,
  register_uart2_int_clr,
  register_uart2_clkdiv,
  register_uart2_rx_filt,
  register_uart2_status,
  register_uart2_conf0,
  register_uart2_conf1,
  register_uart2_lowpulse,
  register_uart2_highpulse,
  register_uart2_rxd_cnt,
  register_uart2_flow_conf,
  register_uart2_sleep_conf,
  register_uart2_swfc_conf0,
  register_uart2_swfc_conf1,
  register_uart2_txbrk_conf,
  register_uart2_idle_conf,
  register_uart2_rs485_conf,
  register_uart2_at_cmd_precnt,
  register_uart2_at_cmd_postcnt,
  register_uart2_at_cmd_gaptout,
  register_uart2_at_cmd_char,
  register_uart2_mem_conf,
  register_uart2_mem_tx_status,
  register_uart2_mem_rx_status,
  register_uart2_fsm_status,
  register_uart2_pospulse,
  register_uart2_negpulse,
  register_uart2_clk_conf,
  register_uart2_date,
  register_uart2_id,
  register_usb0_gotgctl,
  register_usb0_gotgint,
  register_usb0_gahbcfg,
  register_usb0_gusbcfg,
  register_usb0_grstctl,
  register_usb0_gintsts,
  register_usb0_gintmsk,
  register_usb0_grxstsr,
  register_usb0_grxstsp,
  register_usb0_grxfsiz,
  register_usb0_gnptxfsiz,
  register_usb0_gnptxsts,
  register_usb0_gsnpsid,
  register_usb0_ghwcfg1,
  register_usb0_ghwcfg2,
  register_usb0_ghwcfg3,
  register_usb0_ghwcfg4,
  register_usb0_gdfifocfg,
  register_usb0_hptxfsiz,
  register_usb0_dieptxf1,
  register_usb0_dieptxf2,
  register_usb0_dieptxf3,
  register_usb0_dieptxf4,
  register_usb0_hcfg,
  register_usb0_hfir,
  register_usb0_hfnum,
  register_usb0_hptxsts,
  register_usb0_haint,
  register_usb0_haintmsk,
  register_usb0_hflbaddr,
  register_usb0_hprt,
  register_usb0_hcchar0,
  register_usb0_hcint0,
  register_usb0_hcintmsk0,
  register_usb0_hctsiz0,
  register_usb0_hcdma0,
  register_usb0_hcdmab0,
  register_usb0_hcchar1,
  register_usb0_hcint1,
  register_usb0_hcintmsk1,
  register_usb0_hctsiz1,
  register_usb0_hcdma1,
  register_usb0_hcdmab1,
  register_usb0_hcchar2,
  register_usb0_hcint2,
  register_usb0_hcintmsk2,
  register_usb0_hctsiz2,
  register_usb0_hcdma2,
  register_usb0_hcdmab2,
  register_usb0_hcchar3,
  register_usb0_hcint3,
  register_usb0_hcintmsk3,
  register_usb0_hctsiz3,
  register_usb0_hcdma3,
  register_usb0_hcdmab3,
  register_usb0_hcchar4,
  register_usb0_hcint4,
  register_usb0_hcintmsk4,
  register_usb0_hctsiz4,
  register_usb0_hcdma4,
  register_usb0_hcdmab4,
  register_usb0_hcchar5,
  register_usb0_hcint5,
  register_usb0_hcintmsk5,
  register_usb0_hctsiz5,
  register_usb0_hcdma5,
  register_usb0_hcdmab5,
  register_usb0_hcchar6,
  register_usb0_hcint6,
  register_usb0_hcintmsk6,
  register_usb0_hctsiz6,
  register_usb0_hcdma6,
  register_usb0_hcdmab6,
  register_usb0_hcchar7,
  register_usb0_hcint7,
  register_usb0_hcintmsk7,
  register_usb0_hctsiz7,
  register_usb0_hcdma7,
  register_usb0_hcdmab7,
  register_usb0_dcfg,
  register_usb0_dctl,
  register_usb0_dsts,
  register_usb0_diepmsk,
  register_usb0_doepmsk,
  register_usb0_daint,
  register_usb0_daintmsk,
  register_usb0_dvbusdis,
  register_usb0_dvbuspulse,
  register_usb0_dthrctl,
  register_usb0_diepempmsk,
  register_usb0_diepctl0,
  register_usb0_diepint0,
  register_usb0_dieptsiz0,
  register_usb0_diepdma0,
  register_usb0_dtxfsts0,
  register_usb0_diepdmab0,
  register_usb0_diepctl1,
  register_usb0_diepint1,
  register_usb0_dieptsiz1,
  register_usb0_diepdma1,
  register_usb0_dtxfsts1,
  register_usb0_diepdmab1,
  register_usb0_diepctl2,
  register_usb0_diepint2,
  register_usb0_dieptsiz2,
  register_usb0_diepdma2,
  register_usb0_dtxfsts2,
  register_usb0_diepdmab2,
  register_usb0_diepctl3,
  register_usb0_diepint3,
  register_usb0_dieptsiz3,
  register_usb0_diepdma3,
  register_usb0_dtxfsts3,
  register_usb0_diepdmab3,
  register_usb0_diepctl4,
  register_usb0_diepint4,
  register_usb0_dieptsiz4,
  register_usb0_diepdma4,
  register_usb0_dtxfsts4,
  register_usb0_diepdmab4,
  register_usb0_diepctl5,
  register_usb0_diepint5,
  register_usb0_dieptsiz5,
  register_usb0_diepdma5,
  register_usb0_dtxfsts5,
  register_usb0_diepdmab5,
  register_usb0_diepctl6,
  register_usb0_diepint6,
  register_usb0_dieptsiz6,
  register_usb0_diepdma6,
  register_usb0_dtxfsts6,
  register_usb0_diepdmab6,
  register_usb0_doepctl0,
  register_usb0_doepint0,
  register_usb0_doeptsiz0,
  register_usb0_doepdma0,
  register_usb0_doepdmab0,
  register_usb0_doepctl1,
  register_usb0_doepint1,
  register_usb0_doeptsiz1,
  register_usb0_doepdma1,
  register_usb0_doepdmab1,
  register_usb0_doepctl2,
  register_usb0_doepint2,
  register_usb0_doeptsiz2,
  register_usb0_doepdma2,
  register_usb0_doepdmab2,
  register_usb0_doepctl3,
  register_usb0_doepint3,
  register_usb0_doeptsiz3,
  register_usb0_doepdma3,
  register_usb0_doepdmab3,
  register_usb0_doepctl4,
  register_usb0_doepint4,
  register_usb0_doeptsiz4,
  register_usb0_doepdma4,
  register_usb0_doepdmab4,
  register_usb0_doepctl5,
  register_usb0_doepint5,
  register_usb0_doeptsiz5,
  register_usb0_doepdma5,
  register_usb0_doepdmab5,
  register_usb0_doepctl6,
  register_usb0_doepint6,
  register_usb0_doeptsiz6,
  register_usb0_doepdma6,
  register_usb0_doepdmab6,
  register_usb0_pcgcctl,
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
struct RegisterTraits<RegisterId::register_apb_saradc_sar1_patt_tab1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_sar1_patt_tab2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_sar1_patt_tab3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_sar1_patt_tab4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_sar2_patt_tab1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_sar2_patt_tab2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_sar2_patt_tab3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_sar2_patt_tab4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_arb_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_filter_ctrl0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_apb_saradc1_data_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_thres0_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_thres1_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_thres_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 104u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_dma_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 108u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_clkm_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 112u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_apb_saradc2_data_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_apb_saradc_apb_ctrl_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr std::uint32_t kOffsetBytes = 1020u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_conf0_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_conf1_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_int_raw_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_int_st_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_int_ena_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_int_clr_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_infifo_status_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_pop_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_link_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_state_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_suc_eof_des_addr_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_err_eof_des_addr_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_dscr_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_dscr_bf0_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_dscr_bf1_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_wight_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_pri_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_peri_sel_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_conf0_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_conf1_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_int_raw_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 104u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_int_st_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 108u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_int_ena_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 112u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_int_clr_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 116u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_outfifo_status_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_push_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_link_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_state_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 132u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_eof_des_addr_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 136u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_eof_bfr_des_addr_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 140u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_dscr_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 144u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_dscr_bf0_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 148u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_dscr_bf1_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 152u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_wight_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 156u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_pri_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 164u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_peri_sel_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 168u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_ahb_test> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 960u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_pd_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 964u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_misc_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 968u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_in_sram_size_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 972u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_out_sram_size_ch_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 976u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_extmem_reject_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 1012u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_extmem_reject_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 1016u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_extmem_reject_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 1020u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_extmem_reject_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 1024u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_extmem_reject_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 1028u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_extmem_reject_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 1032u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_dma_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr std::uint32_t kOffsetBytes = 1036u;
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
struct RegisterTraits<RegisterId::register_gpio_out1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_out1_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_out1_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
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
struct RegisterTraits<RegisterId::register_gpio_enable1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_enable1_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_enable1_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
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
struct RegisterTraits<RegisterId::register_gpio_in1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
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
struct RegisterTraits<RegisterId::register_gpio_status1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_status1_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_status1_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
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
struct RegisterTraits<RegisterId::register_gpio_pcpu_int1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 104u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_pcpu_nmi_int1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 108u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_gpio_cpusdio_int1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 112u;
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
struct RegisterTraits<RegisterId::register_gpio_status_next1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr std::uint32_t kOffsetBytes = 336u;
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
struct RegisterTraits<RegisterId::register_i2c1_scl_low_period> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_ctr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_sr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_to> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_slave_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_fifo_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_fifo_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_data> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_int_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_sda_hold> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_sda_sample> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_high_period> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_start_hold> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_rstart_setup> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_stop_hold> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_stop_setup> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_filter_cfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_clk_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_comd_s> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_st_time_out> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_main_st_time_out> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_sp_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_scl_stretch_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 132u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 248u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_txfifo_start_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 256u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_i2c1_rxfifo_start_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr std::uint32_t kOffsetBytes = 384u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_reader1_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_reader1_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_meas1_ctrl1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_meas1_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_meas1_mux> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_atten1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_amp_ctrl1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_amp_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_amp_ctrl3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_reader2_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_reader2_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_meas2_ctrl1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_meas2_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_meas2_mux> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_atten2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_power_xpd_sar> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_slave_addr1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_slave_addr2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_slave_addr3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_slave_addr4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_tsens_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_tsens_ctrl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_i2c_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_denoise> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 104u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 108u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 112u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 116u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres8> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres9> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 132u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres10> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 136u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres11> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 140u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres12> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 144u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres13> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 148u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_thres14> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 152u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_chn_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 156u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 160u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 164u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 168u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 172u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 176u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 180u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 184u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 188u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status8> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 192u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status9> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 196u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status10> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 200u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status11> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 204u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status12> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 208u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status13> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 212u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status14> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 216u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status15> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 220u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_touch_status16> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 224u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_cocpu_state> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 228u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_cocpu_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 232u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_cocpu_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 236u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_cocpu_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 240u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_cocpu_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 244u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_cocpu_debug> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 248u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_hall_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 252u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_nouse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 256u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_peri_clk_gate_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 260u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_peri_reset_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 264u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_cocpu_int_ena_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 268u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_cocpu_int_ena_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 272u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_debug_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 276u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_sens_sar_sardate> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr std::uint32_t kOffsetBytes = 508u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
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
struct RegisterTraits<RegisterId::register_spi0_ext_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
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
struct RegisterTraits<RegisterId::register_spi0_cache_sctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_sram_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_sram_drd_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_sram_dwr_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_sram_clk> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
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
struct RegisterTraits<RegisterId::register_spi0_spi_smem_timing_cali> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 188u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_spi_smem_din_mode> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 192u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_spi_smem_din_num> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 196u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_spi_smem_dout_mode> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 200u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ecc_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 204u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ecc_err_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 208u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ecc_err_bit> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 212u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_spi_smem_ac> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 220u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_ddr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 224u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_spi_smem_ddr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 228u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_clock_gate> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 232u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_core_clk_sel> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 236u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 240u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 244u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 248u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi0_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr std::uint32_t kOffsetBytes = 252u;
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
struct RegisterTraits<RegisterId::register_spi1_ext_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
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
struct RegisterTraits<RegisterId::register_spi1_fsm> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
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
struct RegisterTraits<RegisterId::register_spi1_flash_sus_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 156u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_flash_sus_ctrl> {
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
struct RegisterTraits<RegisterId::register_spi1_ddr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 224u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_clock_gate> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 232u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 240u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 244u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 248u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi1_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr std::uint32_t kOffsetBytes = 252u;
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
struct RegisterTraits<RegisterId::register_spi2_dma_int_set> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
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
struct RegisterTraits<RegisterId::register_spi3_cmd> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_addr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_clock> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_user> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_user1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_user2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_ms_dlen> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_misc> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_din_mode> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_din_num> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dout_mode> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_dma_int_set> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 152u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 156u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 160u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 164u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 168u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 172u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 176u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 180u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w8> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 184u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w9> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 188u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w10> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 192u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w11> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 196u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w12> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 200u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w13> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 204u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w14> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 208u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_w15> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 212u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_slave> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 224u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_slave1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 228u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_clk_gate> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 232u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_spi3_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr std::uint32_t kOffsetBytes = 240u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_system_core_1_control_0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x600C0000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::secondary_core_release;
};

template<>
struct RegisterTraits<RegisterId::register_system_core_1_control_1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x600C0000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::secondary_core_release;
};

template<>
struct RegisterTraits<RegisterId::register_system_perip_clk_en0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x600C0000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_system_perip_clk_en1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x600C0000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
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

template<>
struct RegisterTraits<RegisterId::register_uart2_fifo> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_int_st> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_clkdiv> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_rx_filt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_conf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_conf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_lowpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_highpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_rxd_cnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 48u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_flow_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 52u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_sleep_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 56u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_swfc_conf0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 60u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_swfc_conf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_txbrk_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_idle_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_rs485_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_at_cmd_precnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_at_cmd_postcnt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 84u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_at_cmd_gaptout> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 88u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_at_cmd_char> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_mem_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 96u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_mem_tx_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_mem_rx_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 104u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_fsm_status> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 108u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_pospulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 112u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_negpulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 116u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_clk_conf> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 120u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_date> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 124u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_uart2_id> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr std::uint32_t kOffsetBytes = 128u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_gotgctl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 0u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_gotgint> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_gahbcfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_gusbcfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_grstctl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_gintsts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_gintmsk> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_grxstsr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_grxstsp> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_grxfsiz> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 36u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_gnptxfsiz> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 40u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_gnptxsts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 44u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_gsnpsid> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 64u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_ghwcfg1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 68u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_ghwcfg2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 72u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_ghwcfg3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 76u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_ghwcfg4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 80u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_gdfifocfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 92u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hptxfsiz> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 256u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dieptxf1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 260u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dieptxf2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 264u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dieptxf3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 268u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dieptxf4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 272u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1024u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hfir> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1028u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hfnum> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1032u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hptxsts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1040u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_haint> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1044u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_haintmsk> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1048u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hflbaddr> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1052u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hprt> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1088u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcchar0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1280u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcint0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1288u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcintmsk0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1292u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hctsiz0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1296u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdma0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1300u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdmab0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1308u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcchar1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1312u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcint1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1320u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcintmsk1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1324u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hctsiz1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1328u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdma1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1332u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdmab1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1340u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcchar2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1344u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcint2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1352u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcintmsk2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1356u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hctsiz2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1360u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdma2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1364u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdmab2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1372u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcchar3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1376u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcint3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1384u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcintmsk3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1388u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hctsiz3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1392u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdma3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1396u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdmab3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1404u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcchar4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1408u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcint4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1416u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcintmsk4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1420u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hctsiz4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1424u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdma4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1428u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdmab4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1436u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcchar5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1440u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcint5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1448u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcintmsk5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1452u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hctsiz5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1456u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdma5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1460u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdmab5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1468u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcchar6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1472u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcint6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1480u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcintmsk6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1484u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hctsiz6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1488u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdma6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1492u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdmab6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1500u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcchar7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1504u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcint7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1512u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcintmsk7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1516u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hctsiz7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1520u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdma7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1524u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_hcdmab7> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 1532u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dcfg> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2048u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dctl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2052u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dsts> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2056u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepmsk> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2064u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepmsk> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2068u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_daint> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2072u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_daintmsk> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2076u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dvbusdis> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2088u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dvbuspulse> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2092u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dthrctl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2096u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepempmsk> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2100u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepctl0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2304u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepint0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2312u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dieptsiz0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2320u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepdma0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2324u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dtxfsts0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2328u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepdmab0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2332u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepctl1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2336u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepint1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2344u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dieptsiz1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2352u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepdma1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2356u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dtxfsts1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2360u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepdmab1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2364u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepctl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2368u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepint2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2376u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dieptsiz2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2384u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepdma2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2388u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dtxfsts2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2392u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepdmab2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2396u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepctl3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2400u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepint3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2408u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dieptsiz3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2416u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepdma3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2420u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dtxfsts3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2424u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepdmab3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2428u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepctl4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2432u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepint4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2440u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dieptsiz4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2448u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepdma4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2452u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dtxfsts4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2456u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepdmab4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2460u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepctl5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2464u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepint5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2472u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dieptsiz5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2480u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepdma5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2484u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dtxfsts5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2488u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepdmab5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2492u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepctl6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2496u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepint6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2504u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dieptsiz6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2512u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepdma6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2516u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_dtxfsts6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2520u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_diepdmab6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2524u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepctl0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2816u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepint0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2824u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doeptsiz0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2832u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepdma0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2836u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepdmab0> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2844u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepctl1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2848u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepint1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2856u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doeptsiz1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2864u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepdma1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2868u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepdmab1> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2876u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepctl2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2880u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepint2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2888u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doeptsiz2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2896u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepdma2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2900u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepdmab2> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2908u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepctl3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2912u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepint3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2920u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doeptsiz3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2928u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepdma3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2932u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepdmab3> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2940u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepctl4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2944u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepint4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2952u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doeptsiz4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2960u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepdma4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2964u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepdmab4> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2972u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepctl5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2976u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepint5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2984u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doeptsiz5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2992u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepdma5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 2996u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepdmab5> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 3004u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepctl6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 3008u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepint6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 3016u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doeptsiz6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 3024u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepdma6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 3028u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_doepdmab6> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 3036u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

template<>
struct RegisterTraits<RegisterId::register_usb0_pcgcctl> {
  static constexpr bool kPresent = true;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr std::uint32_t kOffsetBytes = 3584u;
  static constexpr AccessKindId kAccessId = AccessKindId::none;
  static constexpr int kSizeBits = 32;
  static constexpr RegisterRole kRole = RegisterRole::general;
};

inline constexpr std::array<RegisterId, 671> kRegisters = {{
  RegisterId::register_apb_saradc_ctrl,
  RegisterId::register_apb_saradc_ctrl2,
  RegisterId::register_apb_saradc_filter_ctrl1,
  RegisterId::register_apb_saradc_fsm_wait,
  RegisterId::register_apb_saradc_sar1_status,
  RegisterId::register_apb_saradc_sar2_status,
  RegisterId::register_apb_saradc_sar1_patt_tab1,
  RegisterId::register_apb_saradc_sar1_patt_tab2,
  RegisterId::register_apb_saradc_sar1_patt_tab3,
  RegisterId::register_apb_saradc_sar1_patt_tab4,
  RegisterId::register_apb_saradc_sar2_patt_tab1,
  RegisterId::register_apb_saradc_sar2_patt_tab2,
  RegisterId::register_apb_saradc_sar2_patt_tab3,
  RegisterId::register_apb_saradc_sar2_patt_tab4,
  RegisterId::register_apb_saradc_arb_ctrl,
  RegisterId::register_apb_saradc_filter_ctrl0,
  RegisterId::register_apb_saradc_apb_saradc1_data_status,
  RegisterId::register_apb_saradc_thres0_ctrl,
  RegisterId::register_apb_saradc_thres1_ctrl,
  RegisterId::register_apb_saradc_thres_ctrl,
  RegisterId::register_apb_saradc_int_ena,
  RegisterId::register_apb_saradc_int_raw,
  RegisterId::register_apb_saradc_int_st,
  RegisterId::register_apb_saradc_int_clr,
  RegisterId::register_apb_saradc_dma_conf,
  RegisterId::register_apb_saradc_clkm_conf,
  RegisterId::register_apb_saradc_apb_saradc2_data_status,
  RegisterId::register_apb_saradc_apb_ctrl_date,
  RegisterId::register_dma_in_conf0_ch_s,
  RegisterId::register_dma_in_conf1_ch_s,
  RegisterId::register_dma_in_int_raw_ch_s,
  RegisterId::register_dma_in_int_st_ch_s,
  RegisterId::register_dma_in_int_ena_ch_s,
  RegisterId::register_dma_in_int_clr_ch_s,
  RegisterId::register_dma_infifo_status_ch_s,
  RegisterId::register_dma_in_pop_ch_s,
  RegisterId::register_dma_in_link_ch_s,
  RegisterId::register_dma_in_state_ch_s,
  RegisterId::register_dma_in_suc_eof_des_addr_ch_s,
  RegisterId::register_dma_in_err_eof_des_addr_ch_s,
  RegisterId::register_dma_in_dscr_ch_s,
  RegisterId::register_dma_in_dscr_bf0_ch_s,
  RegisterId::register_dma_in_dscr_bf1_ch_s,
  RegisterId::register_dma_in_wight_ch_s,
  RegisterId::register_dma_in_pri_ch_s,
  RegisterId::register_dma_in_peri_sel_ch_s,
  RegisterId::register_dma_out_conf0_ch_s,
  RegisterId::register_dma_out_conf1_ch_s,
  RegisterId::register_dma_out_int_raw_ch_s,
  RegisterId::register_dma_out_int_st_ch_s,
  RegisterId::register_dma_out_int_ena_ch_s,
  RegisterId::register_dma_out_int_clr_ch_s,
  RegisterId::register_dma_outfifo_status_ch_s,
  RegisterId::register_dma_out_push_ch_s,
  RegisterId::register_dma_out_link_ch_s,
  RegisterId::register_dma_out_state_ch_s,
  RegisterId::register_dma_out_eof_des_addr_ch_s,
  RegisterId::register_dma_out_eof_bfr_des_addr_ch_s,
  RegisterId::register_dma_out_dscr_ch_s,
  RegisterId::register_dma_out_dscr_bf0_ch_s,
  RegisterId::register_dma_out_dscr_bf1_ch_s,
  RegisterId::register_dma_out_wight_ch_s,
  RegisterId::register_dma_out_pri_ch_s,
  RegisterId::register_dma_out_peri_sel_ch_s,
  RegisterId::register_dma_ahb_test,
  RegisterId::register_dma_pd_conf,
  RegisterId::register_dma_misc_conf,
  RegisterId::register_dma_in_sram_size_ch_s,
  RegisterId::register_dma_out_sram_size_ch_s,
  RegisterId::register_dma_extmem_reject_addr,
  RegisterId::register_dma_extmem_reject_st,
  RegisterId::register_dma_extmem_reject_int_raw,
  RegisterId::register_dma_extmem_reject_int_st,
  RegisterId::register_dma_extmem_reject_int_ena,
  RegisterId::register_dma_extmem_reject_int_clr,
  RegisterId::register_dma_date,
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
  RegisterId::register_gpio_pcpu_int,
  RegisterId::register_gpio_pcpu_nmi_int,
  RegisterId::register_gpio_cpusdio_int,
  RegisterId::register_gpio_pcpu_int1,
  RegisterId::register_gpio_pcpu_nmi_int1,
  RegisterId::register_gpio_cpusdio_int1,
  RegisterId::register_gpio_pin_s,
  RegisterId::register_gpio_status_next,
  RegisterId::register_gpio_status_next1,
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
  RegisterId::register_i2c1_scl_low_period,
  RegisterId::register_i2c1_ctr,
  RegisterId::register_i2c1_sr,
  RegisterId::register_i2c1_to,
  RegisterId::register_i2c1_slave_addr,
  RegisterId::register_i2c1_fifo_st,
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
  RegisterId::register_i2c1_filter_cfg,
  RegisterId::register_i2c1_clk_conf,
  RegisterId::register_i2c1_comd_s,
  RegisterId::register_i2c1_scl_st_time_out,
  RegisterId::register_i2c1_scl_main_st_time_out,
  RegisterId::register_i2c1_scl_sp_conf,
  RegisterId::register_i2c1_scl_stretch_conf,
  RegisterId::register_i2c1_date,
  RegisterId::register_i2c1_txfifo_start_addr,
  RegisterId::register_i2c1_rxfifo_start_addr,
  RegisterId::register_sens_sar_reader1_ctrl,
  RegisterId::register_sens_sar_reader1_status,
  RegisterId::register_sens_sar_meas1_ctrl1,
  RegisterId::register_sens_sar_meas1_ctrl2,
  RegisterId::register_sens_sar_meas1_mux,
  RegisterId::register_sens_sar_atten1,
  RegisterId::register_sens_sar_amp_ctrl1,
  RegisterId::register_sens_sar_amp_ctrl2,
  RegisterId::register_sens_sar_amp_ctrl3,
  RegisterId::register_sens_sar_reader2_ctrl,
  RegisterId::register_sens_sar_reader2_status,
  RegisterId::register_sens_sar_meas2_ctrl1,
  RegisterId::register_sens_sar_meas2_ctrl2,
  RegisterId::register_sens_sar_meas2_mux,
  RegisterId::register_sens_sar_atten2,
  RegisterId::register_sens_sar_power_xpd_sar,
  RegisterId::register_sens_sar_slave_addr1,
  RegisterId::register_sens_sar_slave_addr2,
  RegisterId::register_sens_sar_slave_addr3,
  RegisterId::register_sens_sar_slave_addr4,
  RegisterId::register_sens_sar_tsens_ctrl,
  RegisterId::register_sens_sar_tsens_ctrl2,
  RegisterId::register_sens_sar_i2c_ctrl,
  RegisterId::register_sens_sar_touch_conf,
  RegisterId::register_sens_sar_touch_denoise,
  RegisterId::register_sens_sar_touch_thres1,
  RegisterId::register_sens_sar_touch_thres2,
  RegisterId::register_sens_sar_touch_thres3,
  RegisterId::register_sens_sar_touch_thres4,
  RegisterId::register_sens_sar_touch_thres5,
  RegisterId::register_sens_sar_touch_thres6,
  RegisterId::register_sens_sar_touch_thres7,
  RegisterId::register_sens_sar_touch_thres8,
  RegisterId::register_sens_sar_touch_thres9,
  RegisterId::register_sens_sar_touch_thres10,
  RegisterId::register_sens_sar_touch_thres11,
  RegisterId::register_sens_sar_touch_thres12,
  RegisterId::register_sens_sar_touch_thres13,
  RegisterId::register_sens_sar_touch_thres14,
  RegisterId::register_sens_sar_touch_chn_st,
  RegisterId::register_sens_sar_touch_status0,
  RegisterId::register_sens_sar_touch_status1,
  RegisterId::register_sens_sar_touch_status2,
  RegisterId::register_sens_sar_touch_status3,
  RegisterId::register_sens_sar_touch_status4,
  RegisterId::register_sens_sar_touch_status5,
  RegisterId::register_sens_sar_touch_status6,
  RegisterId::register_sens_sar_touch_status7,
  RegisterId::register_sens_sar_touch_status8,
  RegisterId::register_sens_sar_touch_status9,
  RegisterId::register_sens_sar_touch_status10,
  RegisterId::register_sens_sar_touch_status11,
  RegisterId::register_sens_sar_touch_status12,
  RegisterId::register_sens_sar_touch_status13,
  RegisterId::register_sens_sar_touch_status14,
  RegisterId::register_sens_sar_touch_status15,
  RegisterId::register_sens_sar_touch_status16,
  RegisterId::register_sens_sar_cocpu_state,
  RegisterId::register_sens_sar_cocpu_int_raw,
  RegisterId::register_sens_sar_cocpu_int_ena,
  RegisterId::register_sens_sar_cocpu_int_st,
  RegisterId::register_sens_sar_cocpu_int_clr,
  RegisterId::register_sens_sar_cocpu_debug,
  RegisterId::register_sens_sar_hall_ctrl,
  RegisterId::register_sens_sar_nouse,
  RegisterId::register_sens_sar_peri_clk_gate_conf,
  RegisterId::register_sens_sar_peri_reset_conf,
  RegisterId::register_sens_sar_cocpu_int_ena_w1ts,
  RegisterId::register_sens_sar_cocpu_int_ena_w1tc,
  RegisterId::register_sens_sar_debug_conf,
  RegisterId::register_sens_sar_sardate,
  RegisterId::register_spi0_ctrl,
  RegisterId::register_spi0_ctrl1,
  RegisterId::register_spi0_ctrl2,
  RegisterId::register_spi0_clock,
  RegisterId::register_spi0_user,
  RegisterId::register_spi0_user1,
  RegisterId::register_spi0_user2,
  RegisterId::register_spi0_rd_status,
  RegisterId::register_spi0_ext_addr,
  RegisterId::register_spi0_misc,
  RegisterId::register_spi0_cache_fctrl,
  RegisterId::register_spi0_cache_sctrl,
  RegisterId::register_spi0_sram_cmd,
  RegisterId::register_spi0_sram_drd_cmd,
  RegisterId::register_spi0_sram_dwr_cmd,
  RegisterId::register_spi0_sram_clk,
  RegisterId::register_spi0_fsm,
  RegisterId::register_spi0_timing_cali,
  RegisterId::register_spi0_din_mode,
  RegisterId::register_spi0_din_num,
  RegisterId::register_spi0_dout_mode,
  RegisterId::register_spi0_spi_smem_timing_cali,
  RegisterId::register_spi0_spi_smem_din_mode,
  RegisterId::register_spi0_spi_smem_din_num,
  RegisterId::register_spi0_spi_smem_dout_mode,
  RegisterId::register_spi0_ecc_ctrl,
  RegisterId::register_spi0_ecc_err_addr,
  RegisterId::register_spi0_ecc_err_bit,
  RegisterId::register_spi0_spi_smem_ac,
  RegisterId::register_spi0_ddr,
  RegisterId::register_spi0_spi_smem_ddr,
  RegisterId::register_spi0_clock_gate,
  RegisterId::register_spi0_core_clk_sel,
  RegisterId::register_spi0_int_ena,
  RegisterId::register_spi0_int_clr,
  RegisterId::register_spi0_int_raw,
  RegisterId::register_spi0_int_st,
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
  RegisterId::register_spi1_ext_addr,
  RegisterId::register_spi1_misc,
  RegisterId::register_spi1_tx_crc,
  RegisterId::register_spi1_cache_fctrl,
  RegisterId::register_spi1_fsm,
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
  RegisterId::register_spi1_flash_sus_cmd,
  RegisterId::register_spi1_flash_sus_ctrl,
  RegisterId::register_spi1_sus_status,
  RegisterId::register_spi1_timing_cali,
  RegisterId::register_spi1_ddr,
  RegisterId::register_spi1_clock_gate,
  RegisterId::register_spi1_int_ena,
  RegisterId::register_spi1_int_clr,
  RegisterId::register_spi1_int_raw,
  RegisterId::register_spi1_int_st,
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
  RegisterId::register_spi2_dma_int_set,
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
  RegisterId::register_spi3_cmd,
  RegisterId::register_spi3_addr,
  RegisterId::register_spi3_ctrl,
  RegisterId::register_spi3_clock,
  RegisterId::register_spi3_user,
  RegisterId::register_spi3_user1,
  RegisterId::register_spi3_user2,
  RegisterId::register_spi3_ms_dlen,
  RegisterId::register_spi3_misc,
  RegisterId::register_spi3_din_mode,
  RegisterId::register_spi3_din_num,
  RegisterId::register_spi3_dout_mode,
  RegisterId::register_spi3_dma_conf,
  RegisterId::register_spi3_dma_int_ena,
  RegisterId::register_spi3_dma_int_clr,
  RegisterId::register_spi3_dma_int_raw,
  RegisterId::register_spi3_dma_int_st,
  RegisterId::register_spi3_dma_int_set,
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
  RegisterId::register_spi3_slave,
  RegisterId::register_spi3_slave1,
  RegisterId::register_spi3_clk_gate,
  RegisterId::register_spi3_date,
  RegisterId::register_system_core_1_control_0,
  RegisterId::register_system_core_1_control_1,
  RegisterId::register_system_perip_clk_en0,
  RegisterId::register_system_perip_clk_en1,
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
  RegisterId::register_uart2_fifo,
  RegisterId::register_uart2_int_raw,
  RegisterId::register_uart2_int_st,
  RegisterId::register_uart2_int_ena,
  RegisterId::register_uart2_int_clr,
  RegisterId::register_uart2_clkdiv,
  RegisterId::register_uart2_rx_filt,
  RegisterId::register_uart2_status,
  RegisterId::register_uart2_conf0,
  RegisterId::register_uart2_conf1,
  RegisterId::register_uart2_lowpulse,
  RegisterId::register_uart2_highpulse,
  RegisterId::register_uart2_rxd_cnt,
  RegisterId::register_uart2_flow_conf,
  RegisterId::register_uart2_sleep_conf,
  RegisterId::register_uart2_swfc_conf0,
  RegisterId::register_uart2_swfc_conf1,
  RegisterId::register_uart2_txbrk_conf,
  RegisterId::register_uart2_idle_conf,
  RegisterId::register_uart2_rs485_conf,
  RegisterId::register_uart2_at_cmd_precnt,
  RegisterId::register_uart2_at_cmd_postcnt,
  RegisterId::register_uart2_at_cmd_gaptout,
  RegisterId::register_uart2_at_cmd_char,
  RegisterId::register_uart2_mem_conf,
  RegisterId::register_uart2_mem_tx_status,
  RegisterId::register_uart2_mem_rx_status,
  RegisterId::register_uart2_fsm_status,
  RegisterId::register_uart2_pospulse,
  RegisterId::register_uart2_negpulse,
  RegisterId::register_uart2_clk_conf,
  RegisterId::register_uart2_date,
  RegisterId::register_uart2_id,
  RegisterId::register_usb0_gotgctl,
  RegisterId::register_usb0_gotgint,
  RegisterId::register_usb0_gahbcfg,
  RegisterId::register_usb0_gusbcfg,
  RegisterId::register_usb0_grstctl,
  RegisterId::register_usb0_gintsts,
  RegisterId::register_usb0_gintmsk,
  RegisterId::register_usb0_grxstsr,
  RegisterId::register_usb0_grxstsp,
  RegisterId::register_usb0_grxfsiz,
  RegisterId::register_usb0_gnptxfsiz,
  RegisterId::register_usb0_gnptxsts,
  RegisterId::register_usb0_gsnpsid,
  RegisterId::register_usb0_ghwcfg1,
  RegisterId::register_usb0_ghwcfg2,
  RegisterId::register_usb0_ghwcfg3,
  RegisterId::register_usb0_ghwcfg4,
  RegisterId::register_usb0_gdfifocfg,
  RegisterId::register_usb0_hptxfsiz,
  RegisterId::register_usb0_dieptxf1,
  RegisterId::register_usb0_dieptxf2,
  RegisterId::register_usb0_dieptxf3,
  RegisterId::register_usb0_dieptxf4,
  RegisterId::register_usb0_hcfg,
  RegisterId::register_usb0_hfir,
  RegisterId::register_usb0_hfnum,
  RegisterId::register_usb0_hptxsts,
  RegisterId::register_usb0_haint,
  RegisterId::register_usb0_haintmsk,
  RegisterId::register_usb0_hflbaddr,
  RegisterId::register_usb0_hprt,
  RegisterId::register_usb0_hcchar0,
  RegisterId::register_usb0_hcint0,
  RegisterId::register_usb0_hcintmsk0,
  RegisterId::register_usb0_hctsiz0,
  RegisterId::register_usb0_hcdma0,
  RegisterId::register_usb0_hcdmab0,
  RegisterId::register_usb0_hcchar1,
  RegisterId::register_usb0_hcint1,
  RegisterId::register_usb0_hcintmsk1,
  RegisterId::register_usb0_hctsiz1,
  RegisterId::register_usb0_hcdma1,
  RegisterId::register_usb0_hcdmab1,
  RegisterId::register_usb0_hcchar2,
  RegisterId::register_usb0_hcint2,
  RegisterId::register_usb0_hcintmsk2,
  RegisterId::register_usb0_hctsiz2,
  RegisterId::register_usb0_hcdma2,
  RegisterId::register_usb0_hcdmab2,
  RegisterId::register_usb0_hcchar3,
  RegisterId::register_usb0_hcint3,
  RegisterId::register_usb0_hcintmsk3,
  RegisterId::register_usb0_hctsiz3,
  RegisterId::register_usb0_hcdma3,
  RegisterId::register_usb0_hcdmab3,
  RegisterId::register_usb0_hcchar4,
  RegisterId::register_usb0_hcint4,
  RegisterId::register_usb0_hcintmsk4,
  RegisterId::register_usb0_hctsiz4,
  RegisterId::register_usb0_hcdma4,
  RegisterId::register_usb0_hcdmab4,
  RegisterId::register_usb0_hcchar5,
  RegisterId::register_usb0_hcint5,
  RegisterId::register_usb0_hcintmsk5,
  RegisterId::register_usb0_hctsiz5,
  RegisterId::register_usb0_hcdma5,
  RegisterId::register_usb0_hcdmab5,
  RegisterId::register_usb0_hcchar6,
  RegisterId::register_usb0_hcint6,
  RegisterId::register_usb0_hcintmsk6,
  RegisterId::register_usb0_hctsiz6,
  RegisterId::register_usb0_hcdma6,
  RegisterId::register_usb0_hcdmab6,
  RegisterId::register_usb0_hcchar7,
  RegisterId::register_usb0_hcint7,
  RegisterId::register_usb0_hcintmsk7,
  RegisterId::register_usb0_hctsiz7,
  RegisterId::register_usb0_hcdma7,
  RegisterId::register_usb0_hcdmab7,
  RegisterId::register_usb0_dcfg,
  RegisterId::register_usb0_dctl,
  RegisterId::register_usb0_dsts,
  RegisterId::register_usb0_diepmsk,
  RegisterId::register_usb0_doepmsk,
  RegisterId::register_usb0_daint,
  RegisterId::register_usb0_daintmsk,
  RegisterId::register_usb0_dvbusdis,
  RegisterId::register_usb0_dvbuspulse,
  RegisterId::register_usb0_dthrctl,
  RegisterId::register_usb0_diepempmsk,
  RegisterId::register_usb0_diepctl0,
  RegisterId::register_usb0_diepint0,
  RegisterId::register_usb0_dieptsiz0,
  RegisterId::register_usb0_diepdma0,
  RegisterId::register_usb0_dtxfsts0,
  RegisterId::register_usb0_diepdmab0,
  RegisterId::register_usb0_diepctl1,
  RegisterId::register_usb0_diepint1,
  RegisterId::register_usb0_dieptsiz1,
  RegisterId::register_usb0_diepdma1,
  RegisterId::register_usb0_dtxfsts1,
  RegisterId::register_usb0_diepdmab1,
  RegisterId::register_usb0_diepctl2,
  RegisterId::register_usb0_diepint2,
  RegisterId::register_usb0_dieptsiz2,
  RegisterId::register_usb0_diepdma2,
  RegisterId::register_usb0_dtxfsts2,
  RegisterId::register_usb0_diepdmab2,
  RegisterId::register_usb0_diepctl3,
  RegisterId::register_usb0_diepint3,
  RegisterId::register_usb0_dieptsiz3,
  RegisterId::register_usb0_diepdma3,
  RegisterId::register_usb0_dtxfsts3,
  RegisterId::register_usb0_diepdmab3,
  RegisterId::register_usb0_diepctl4,
  RegisterId::register_usb0_diepint4,
  RegisterId::register_usb0_dieptsiz4,
  RegisterId::register_usb0_diepdma4,
  RegisterId::register_usb0_dtxfsts4,
  RegisterId::register_usb0_diepdmab4,
  RegisterId::register_usb0_diepctl5,
  RegisterId::register_usb0_diepint5,
  RegisterId::register_usb0_dieptsiz5,
  RegisterId::register_usb0_diepdma5,
  RegisterId::register_usb0_dtxfsts5,
  RegisterId::register_usb0_diepdmab5,
  RegisterId::register_usb0_diepctl6,
  RegisterId::register_usb0_diepint6,
  RegisterId::register_usb0_dieptsiz6,
  RegisterId::register_usb0_diepdma6,
  RegisterId::register_usb0_dtxfsts6,
  RegisterId::register_usb0_diepdmab6,
  RegisterId::register_usb0_doepctl0,
  RegisterId::register_usb0_doepint0,
  RegisterId::register_usb0_doeptsiz0,
  RegisterId::register_usb0_doepdma0,
  RegisterId::register_usb0_doepdmab0,
  RegisterId::register_usb0_doepctl1,
  RegisterId::register_usb0_doepint1,
  RegisterId::register_usb0_doeptsiz1,
  RegisterId::register_usb0_doepdma1,
  RegisterId::register_usb0_doepdmab1,
  RegisterId::register_usb0_doepctl2,
  RegisterId::register_usb0_doepint2,
  RegisterId::register_usb0_doeptsiz2,
  RegisterId::register_usb0_doepdma2,
  RegisterId::register_usb0_doepdmab2,
  RegisterId::register_usb0_doepctl3,
  RegisterId::register_usb0_doepint3,
  RegisterId::register_usb0_doeptsiz3,
  RegisterId::register_usb0_doepdma3,
  RegisterId::register_usb0_doepdmab3,
  RegisterId::register_usb0_doepctl4,
  RegisterId::register_usb0_doepint4,
  RegisterId::register_usb0_doeptsiz4,
  RegisterId::register_usb0_doepdma4,
  RegisterId::register_usb0_doepdmab4,
  RegisterId::register_usb0_doepctl5,
  RegisterId::register_usb0_doepint5,
  RegisterId::register_usb0_doeptsiz5,
  RegisterId::register_usb0_doepdma5,
  RegisterId::register_usb0_doepdmab5,
  RegisterId::register_usb0_doepctl6,
  RegisterId::register_usb0_doepint6,
  RegisterId::register_usb0_doeptsiz6,
  RegisterId::register_usb0_doepdma6,
  RegisterId::register_usb0_doepdmab6,
  RegisterId::register_usb0_pcgcctl,
}};
}
}
}
}
}
}
