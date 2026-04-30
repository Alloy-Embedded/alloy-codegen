#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "registers.hpp"

namespace espressif {
namespace esp32c3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32c3 {
enum class FieldId : std::uint16_t {
  none,
  field_apb_saradc_apb_tsens_ctrl_tsens_out,
  field_apb_saradc_apb_tsens_ctrl_tsens_in_inv,
  field_apb_saradc_apb_tsens_ctrl_tsens_clk_div,
  field_apb_saradc_apb_tsens_ctrl_tsens_pu,
  field_apb_saradc_arb_ctrl_adc_arb_apb_force,
  field_apb_saradc_arb_ctrl_adc_arb_rtc_force,
  field_apb_saradc_arb_ctrl_adc_arb_wifi_force,
  field_apb_saradc_arb_ctrl_adc_arb_grant_force,
  field_apb_saradc_arb_ctrl_adc_arb_apb_priority,
  field_apb_saradc_arb_ctrl_adc_arb_rtc_priority,
  field_apb_saradc_arb_ctrl_adc_arb_wifi_priority,
  field_apb_saradc_arb_ctrl_adc_arb_fix_priority,
  field_apb_saradc_cali_apb_saradc_cali_cfg,
  field_apb_saradc_clkm_conf_clkm_div_num,
  field_apb_saradc_clkm_conf_clkm_div_b,
  field_apb_saradc_clkm_conf_clkm_div_a,
  field_apb_saradc_clkm_conf_clk_en,
  field_apb_saradc_clkm_conf_clk_sel,
  field_apb_saradc_ctrl_saradc_start_force,
  field_apb_saradc_ctrl_saradc_start,
  field_apb_saradc_ctrl_saradc_sar_clk_gated,
  field_apb_saradc_ctrl_saradc_sar_clk_div,
  field_apb_saradc_ctrl_saradc_sar_patt_len,
  field_apb_saradc_ctrl_saradc_sar_patt_p_clear,
  field_apb_saradc_ctrl_saradc_xpd_sar_force,
  field_apb_saradc_ctrl_saradc_wait_arb_cycle,
  field_apb_saradc_ctrl2_saradc_meas_num_limit,
  field_apb_saradc_ctrl2_saradc_max_meas_num,
  field_apb_saradc_ctrl2_saradc_sar1_inv,
  field_apb_saradc_ctrl2_saradc_sar2_inv,
  field_apb_saradc_ctrl2_saradc_timer_target,
  field_apb_saradc_ctrl2_saradc_timer_en,
  field_apb_saradc_ctrl_date_date,
  field_apb_saradc_dma_conf_apb_adc_eof_num,
  field_apb_saradc_dma_conf_apb_adc_reset_fsm,
  field_apb_saradc_dma_conf_apb_adc_trans,
  field_apb_saradc_filter_ctrl0_apb_saradc_filter_channel1,
  field_apb_saradc_filter_ctrl0_apb_saradc_filter_channel0,
  field_apb_saradc_filter_ctrl0_apb_saradc_filter_reset,
  field_apb_saradc_filter_ctrl1_apb_saradc_filter_factor1,
  field_apb_saradc_filter_ctrl1_apb_saradc_filter_factor0,
  field_apb_saradc_fsm_wait_saradc_xpd_wait,
  field_apb_saradc_fsm_wait_saradc_rstb_wait,
  field_apb_saradc_fsm_wait_saradc_standby_wait,
  field_apb_saradc_int_clr_apb_saradc_thres1_low_int_clr,
  field_apb_saradc_int_clr_apb_saradc_thres0_low_int_clr,
  field_apb_saradc_int_clr_apb_saradc_thres1_high_int_clr,
  field_apb_saradc_int_clr_apb_saradc_thres0_high_int_clr,
  field_apb_saradc_int_clr_apb_saradc2_done_int_clr,
  field_apb_saradc_int_clr_apb_saradc1_done_int_clr,
  field_apb_saradc_int_ena_apb_saradc_thres1_low_int_ena,
  field_apb_saradc_int_ena_apb_saradc_thres0_low_int_ena,
  field_apb_saradc_int_ena_apb_saradc_thres1_high_int_ena,
  field_apb_saradc_int_ena_apb_saradc_thres0_high_int_ena,
  field_apb_saradc_int_ena_apb_saradc2_done_int_ena,
  field_apb_saradc_int_ena_apb_saradc1_done_int_ena,
  field_apb_saradc_int_raw_apb_saradc_thres1_low_int_raw,
  field_apb_saradc_int_raw_apb_saradc_thres0_low_int_raw,
  field_apb_saradc_int_raw_apb_saradc_thres1_high_int_raw,
  field_apb_saradc_int_raw_apb_saradc_thres0_high_int_raw,
  field_apb_saradc_int_raw_apb_saradc2_done_int_raw,
  field_apb_saradc_int_raw_apb_saradc1_done_int_raw,
  field_apb_saradc_int_st_apb_saradc_thres1_low_int_st,
  field_apb_saradc_int_st_apb_saradc_thres0_low_int_st,
  field_apb_saradc_int_st_apb_saradc_thres1_high_int_st,
  field_apb_saradc_int_st_apb_saradc_thres0_high_int_st,
  field_apb_saradc_int_st_apb_saradc2_done_int_st,
  field_apb_saradc_int_st_apb_saradc1_done_int_st,
  field_apb_saradc_onetime_sample_saradc_onetime_atten,
  field_apb_saradc_onetime_sample_saradc_onetime_channel,
  field_apb_saradc_onetime_sample_saradc_onetime_start,
  field_apb_saradc_onetime_sample_saradc2_onetime_sample,
  field_apb_saradc_onetime_sample_saradc1_onetime_sample,
  field_apb_saradc_sar1data_status_apb_saradc1_data,
  field_apb_saradc_sar1_status_saradc_sar1_status,
  field_apb_saradc_sar2data_status_apb_saradc2_data,
  field_apb_saradc_sar2_status_saradc_sar2_status,
  field_apb_saradc_sar_patt_tab1_saradc_sar_patt_tab1,
  field_apb_saradc_sar_patt_tab2_saradc_sar_patt_tab2,
  field_apb_saradc_thres0_ctrl_apb_saradc_thres0_channel,
  field_apb_saradc_thres0_ctrl_apb_saradc_thres0_high,
  field_apb_saradc_thres0_ctrl_apb_saradc_thres0_low,
  field_apb_saradc_thres1_ctrl_apb_saradc_thres1_channel,
  field_apb_saradc_thres1_ctrl_apb_saradc_thres1_high,
  field_apb_saradc_thres1_ctrl_apb_saradc_thres1_low,
  field_apb_saradc_thres_ctrl_apb_saradc_thres_all_en,
  field_apb_saradc_thres_ctrl_apb_saradc_thres1_en,
  field_apb_saradc_thres_ctrl_apb_saradc_thres0_en,
  field_apb_saradc_tsens_ctrl2_tsens_xpd_wait,
  field_apb_saradc_tsens_ctrl2_tsens_xpd_force,
  field_apb_saradc_tsens_ctrl2_tsens_clk_inv,
  field_apb_saradc_tsens_ctrl2_tsens_clk_sel,
  field_dma_ahb_test_ahb_testmode,
  field_dma_ahb_test_ahb_testaddr,
  field_dma_date_date,
  field_dma_infifo_status_ch0_infifo_full,
  field_dma_infifo_status_ch0_infifo_empty,
  field_dma_infifo_status_ch0_infifo_cnt,
  field_dma_infifo_status_ch0_in_remain_under_1b,
  field_dma_infifo_status_ch0_in_remain_under_2b,
  field_dma_infifo_status_ch0_in_remain_under_3b,
  field_dma_infifo_status_ch0_in_remain_under_4b,
  field_dma_infifo_status_ch0_in_buf_hungry,
  field_dma_infifo_status_ch1_infifo_full,
  field_dma_infifo_status_ch1_infifo_empty,
  field_dma_infifo_status_ch1_infifo_cnt,
  field_dma_infifo_status_ch1_in_remain_under_1b,
  field_dma_infifo_status_ch1_in_remain_under_2b,
  field_dma_infifo_status_ch1_in_remain_under_3b,
  field_dma_infifo_status_ch1_in_remain_under_4b,
  field_dma_infifo_status_ch1_in_buf_hungry,
  field_dma_infifo_status_ch2_infifo_full,
  field_dma_infifo_status_ch2_infifo_empty,
  field_dma_infifo_status_ch2_infifo_cnt,
  field_dma_infifo_status_ch2_in_remain_under_1b,
  field_dma_infifo_status_ch2_in_remain_under_2b,
  field_dma_infifo_status_ch2_in_remain_under_3b,
  field_dma_infifo_status_ch2_in_remain_under_4b,
  field_dma_infifo_status_ch2_in_buf_hungry,
  field_dma_int_clr_ch_s_in_done,
  field_dma_int_clr_ch_s_in_suc_eof,
  field_dma_int_clr_ch_s_in_err_eof,
  field_dma_int_clr_ch_s_out_done,
  field_dma_int_clr_ch_s_out_eof,
  field_dma_int_clr_ch_s_in_dscr_err,
  field_dma_int_clr_ch_s_out_dscr_err,
  field_dma_int_clr_ch_s_in_dscr_empty,
  field_dma_int_clr_ch_s_out_total_eof,
  field_dma_int_clr_ch_s_infifo_ovf,
  field_dma_int_clr_ch_s_infifo_udf,
  field_dma_int_clr_ch_s_outfifo_ovf,
  field_dma_int_clr_ch_s_outfifo_udf,
  field_dma_int_ena_ch_s_in_done,
  field_dma_int_ena_ch_s_in_suc_eof,
  field_dma_int_ena_ch_s_in_err_eof,
  field_dma_int_ena_ch_s_out_done,
  field_dma_int_ena_ch_s_out_eof,
  field_dma_int_ena_ch_s_in_dscr_err,
  field_dma_int_ena_ch_s_out_dscr_err,
  field_dma_int_ena_ch_s_in_dscr_empty,
  field_dma_int_ena_ch_s_out_total_eof,
  field_dma_int_ena_ch_s_infifo_ovf,
  field_dma_int_ena_ch_s_infifo_udf,
  field_dma_int_ena_ch_s_outfifo_ovf,
  field_dma_int_ena_ch_s_outfifo_udf,
  field_dma_int_raw_ch_s_in_done,
  field_dma_int_raw_ch_s_in_suc_eof,
  field_dma_int_raw_ch_s_in_err_eof,
  field_dma_int_raw_ch_s_out_done,
  field_dma_int_raw_ch_s_out_eof,
  field_dma_int_raw_ch_s_in_dscr_err,
  field_dma_int_raw_ch_s_out_dscr_err,
  field_dma_int_raw_ch_s_in_dscr_empty,
  field_dma_int_raw_ch_s_out_total_eof,
  field_dma_int_raw_ch_s_infifo_ovf,
  field_dma_int_raw_ch_s_infifo_udf,
  field_dma_int_raw_ch_s_outfifo_ovf,
  field_dma_int_raw_ch_s_outfifo_udf,
  field_dma_int_st_ch0_in_done,
  field_dma_int_st_ch0_in_suc_eof,
  field_dma_int_st_ch0_in_err_eof,
  field_dma_int_st_ch0_out_done,
  field_dma_int_st_ch0_out_eof,
  field_dma_int_st_ch0_in_dscr_err,
  field_dma_int_st_ch0_out_dscr_err,
  field_dma_int_st_ch0_in_dscr_empty,
  field_dma_int_st_ch0_out_total_eof,
  field_dma_int_st_ch0_infifo_ovf,
  field_dma_int_st_ch0_infifo_udf,
  field_dma_int_st_ch0_outfifo_ovf,
  field_dma_int_st_ch0_outfifo_udf,
  field_dma_int_st_ch1_in_done,
  field_dma_int_st_ch1_in_suc_eof,
  field_dma_int_st_ch1_in_err_eof,
  field_dma_int_st_ch1_out_done,
  field_dma_int_st_ch1_out_eof,
  field_dma_int_st_ch1_in_dscr_err,
  field_dma_int_st_ch1_out_dscr_err,
  field_dma_int_st_ch1_in_dscr_empty,
  field_dma_int_st_ch1_out_total_eof,
  field_dma_int_st_ch1_infifo_ovf,
  field_dma_int_st_ch1_infifo_udf,
  field_dma_int_st_ch1_outfifo_ovf,
  field_dma_int_st_ch1_outfifo_udf,
  field_dma_int_st_ch2_in_done,
  field_dma_int_st_ch2_in_suc_eof,
  field_dma_int_st_ch2_in_err_eof,
  field_dma_int_st_ch2_out_done,
  field_dma_int_st_ch2_out_eof,
  field_dma_int_st_ch2_in_dscr_err,
  field_dma_int_st_ch2_out_dscr_err,
  field_dma_int_st_ch2_in_dscr_empty,
  field_dma_int_st_ch2_out_total_eof,
  field_dma_int_st_ch2_infifo_ovf,
  field_dma_int_st_ch2_infifo_udf,
  field_dma_int_st_ch2_outfifo_ovf,
  field_dma_int_st_ch2_outfifo_udf,
  field_dma_in_conf0_ch_s_in_rst,
  field_dma_in_conf0_ch_s_in_loop_test,
  field_dma_in_conf0_ch_s_indscr_burst_en,
  field_dma_in_conf0_ch_s_in_data_burst_en,
  field_dma_in_conf0_ch_s_mem_trans_en,
  field_dma_in_conf1_ch0_in_check_owner,
  field_dma_in_conf1_ch1_in_check_owner,
  field_dma_in_conf1_ch2_in_check_owner,
  field_dma_in_dscr_bf0_ch_s_inlink_dscr_bf0,
  field_dma_in_dscr_bf1_ch0_inlink_dscr_bf1,
  field_dma_in_dscr_bf1_ch1_inlink_dscr_bf1,
  field_dma_in_dscr_bf1_ch2_inlink_dscr_bf1,
  field_dma_in_dscr_ch0_inlink_dscr,
  field_dma_in_dscr_ch1_inlink_dscr,
  field_dma_in_dscr_ch2_inlink_dscr,
  field_dma_in_err_eof_des_addr_ch0_in_err_eof_des_addr,
  field_dma_in_err_eof_des_addr_ch1_in_err_eof_des_addr,
  field_dma_in_err_eof_des_addr_ch2_in_err_eof_des_addr,
  field_dma_in_link_ch_s_inlink_addr,
  field_dma_in_link_ch_s_inlink_auto_ret,
  field_dma_in_link_ch_s_inlink_stop,
  field_dma_in_link_ch_s_inlink_start,
  field_dma_in_link_ch_s_inlink_restart,
  field_dma_in_link_ch_s_inlink_park,
  field_dma_in_peri_sel_ch_s_peri_in_sel,
  field_dma_in_pop_ch0_infifo_rdata,
  field_dma_in_pop_ch0_infifo_pop,
  field_dma_in_pop_ch1_infifo_rdata,
  field_dma_in_pop_ch1_infifo_pop,
  field_dma_in_pop_ch2_infifo_rdata,
  field_dma_in_pop_ch2_infifo_pop,
  field_dma_in_pri_ch_s_rx_pri,
  field_dma_in_state_ch0_inlink_dscr_addr,
  field_dma_in_state_ch0_in_dscr_state,
  field_dma_in_state_ch0_in_state,
  field_dma_in_state_ch1_inlink_dscr_addr,
  field_dma_in_state_ch1_in_dscr_state,
  field_dma_in_state_ch1_in_state,
  field_dma_in_state_ch2_inlink_dscr_addr,
  field_dma_in_state_ch2_in_dscr_state,
  field_dma_in_state_ch2_in_state,
  field_dma_in_suc_eof_des_addr_ch0_in_suc_eof_des_addr,
  field_dma_in_suc_eof_des_addr_ch1_in_suc_eof_des_addr,
  field_dma_in_suc_eof_des_addr_ch2_in_suc_eof_des_addr,
  field_dma_misc_conf_ahbm_rst_inter,
  field_dma_misc_conf_arb_pri_dis,
  field_dma_misc_conf_clk_en,
  field_dma_outfifo_status_ch0_outfifo_full,
  field_dma_outfifo_status_ch0_outfifo_empty,
  field_dma_outfifo_status_ch0_outfifo_cnt,
  field_dma_outfifo_status_ch0_out_remain_under_1b,
  field_dma_outfifo_status_ch0_out_remain_under_2b,
  field_dma_outfifo_status_ch0_out_remain_under_3b,
  field_dma_outfifo_status_ch0_out_remain_under_4b,
  field_dma_outfifo_status_ch1_outfifo_full,
  field_dma_outfifo_status_ch1_outfifo_empty,
  field_dma_outfifo_status_ch1_outfifo_cnt,
  field_dma_outfifo_status_ch1_out_remain_under_1b,
  field_dma_outfifo_status_ch1_out_remain_under_2b,
  field_dma_outfifo_status_ch1_out_remain_under_3b,
  field_dma_outfifo_status_ch1_out_remain_under_4b,
  field_dma_outfifo_status_ch2_outfifo_full,
  field_dma_outfifo_status_ch2_outfifo_empty,
  field_dma_outfifo_status_ch2_outfifo_cnt,
  field_dma_outfifo_status_ch2_out_remain_under_1b,
  field_dma_outfifo_status_ch2_out_remain_under_2b,
  field_dma_outfifo_status_ch2_out_remain_under_3b,
  field_dma_outfifo_status_ch2_out_remain_under_4b,
  field_dma_out_conf0_ch_s_out_rst,
  field_dma_out_conf0_ch_s_out_loop_test,
  field_dma_out_conf0_ch_s_out_auto_wrback,
  field_dma_out_conf0_ch_s_out_eof_mode,
  field_dma_out_conf0_ch_s_outdscr_burst_en,
  field_dma_out_conf0_ch_s_out_data_burst_en,
  field_dma_out_conf1_ch_s_out_check_owner,
  field_dma_out_dscr_bf0_ch0_outlink_dscr_bf0,
  field_dma_out_dscr_bf0_ch1_outlink_dscr_bf0,
  field_dma_out_dscr_bf0_ch2_outlink_dscr_bf0,
  field_dma_out_dscr_bf1_ch0_outlink_dscr_bf1,
  field_dma_out_dscr_bf1_ch1_outlink_dscr_bf1,
  field_dma_out_dscr_bf1_ch2_outlink_dscr_bf1,
  field_dma_out_dscr_ch0_outlink_dscr,
  field_dma_out_dscr_ch1_outlink_dscr,
  field_dma_out_dscr_ch2_outlink_dscr,
  field_dma_out_eof_bfr_des_addr_ch0_out_eof_bfr_des_addr,
  field_dma_out_eof_bfr_des_addr_ch1_out_eof_bfr_des_addr,
  field_dma_out_eof_bfr_des_addr_ch2_out_eof_bfr_des_addr,
  field_dma_out_eof_des_addr_ch_s_out_eof_des_addr,
  field_dma_out_link_ch_s_outlink_addr,
  field_dma_out_link_ch_s_outlink_stop,
  field_dma_out_link_ch_s_outlink_start,
  field_dma_out_link_ch_s_outlink_restart,
  field_dma_out_link_ch_s_outlink_park,
  field_dma_out_peri_sel_ch_s_peri_out_sel,
  field_dma_out_pri_ch_s_tx_pri,
  field_dma_out_push_ch0_outfifo_wdata,
  field_dma_out_push_ch0_outfifo_push,
  field_dma_out_push_ch1_outfifo_wdata,
  field_dma_out_push_ch1_outfifo_push,
  field_dma_out_push_ch2_outfifo_wdata,
  field_dma_out_push_ch2_outfifo_push,
  field_dma_out_state_ch0_outlink_dscr_addr,
  field_dma_out_state_ch0_out_dscr_state,
  field_dma_out_state_ch0_out_state,
  field_dma_out_state_ch1_outlink_dscr_addr,
  field_dma_out_state_ch1_out_dscr_state,
  field_dma_out_state_ch1_out_state,
  field_dma_out_state_ch2_outlink_dscr_addr,
  field_dma_out_state_ch2_out_dscr_state,
  field_dma_out_state_ch2_out_state,
  field_gpio_bt_select_bt_sel,
  field_gpio_clock_gate_clk_en,
  field_gpio_cpusdio_int_sdio_int,
  field_gpio_enable_data,
  field_gpio_enable_w1tc_enable_w1tc,
  field_gpio_enable_w1ts_enable_w1ts,
  field_gpio_func_s_in_sel_cfg_in_sel,
  field_gpio_func_s_in_sel_cfg_in_inv_sel,
  field_gpio_func_s_in_sel_cfg_sel,
  field_gpio_func_s_out_sel_cfg_out_sel,
  field_gpio_func_s_out_sel_cfg_inv_sel,
  field_gpio_func_s_out_sel_cfg_oen_sel,
  field_gpio_func_s_out_sel_cfg_oen_inv_sel,
  field_gpio_in_data_next,
  field_gpio_out_data_orig,
  field_gpio_out_w1tc_out_w1tc,
  field_gpio_out_w1ts_out_w1ts,
  field_gpio_pcpu_int_procpu_int,
  field_gpio_pcpu_nmi_int_procpu_nmi_int,
  field_gpio_pin_s_sync2_bypass,
  field_gpio_pin_s_pad_driver,
  field_gpio_pin_s_sync1_bypass,
  field_gpio_pin_s_int_type,
  field_gpio_pin_s_wakeup_enable,
  field_gpio_pin_s_config,
  field_gpio_pin_s_int_ena,
  field_gpio_reg_date_reg_date,
  field_gpio_sdio_select_sdio_sel,
  field_gpio_status_interrupt,
  field_gpio_status_next_status_interrupt_next,
  field_gpio_status_w1tc_status_w1tc,
  field_gpio_status_w1ts_status_w1ts,
  field_gpio_strap_strapping,
  field_i2c0_clk_conf_sclk_div_num,
  field_i2c0_clk_conf_sclk_div_a,
  field_i2c0_clk_conf_sclk_div_b,
  field_i2c0_clk_conf_sclk_sel,
  field_i2c0_clk_conf_sclk_active,
  field_i2c0_comd_s_command,
  field_i2c0_comd_s_command_done,
  field_i2c0_ctr_sda_force_out,
  field_i2c0_ctr_scl_force_out,
  field_i2c0_ctr_sample_scl_level,
  field_i2c0_ctr_rx_full_ack_level,
  field_i2c0_ctr_ms_mode,
  field_i2c0_ctr_trans_start,
  field_i2c0_ctr_tx_lsb_first,
  field_i2c0_ctr_rx_lsb_first,
  field_i2c0_ctr_clk_en,
  field_i2c0_ctr_arbitration_en,
  field_i2c0_ctr_fsm_rst,
  field_i2c0_ctr_conf_upgate,
  field_i2c0_ctr_slv_tx_auto_start_en,
  field_i2c0_ctr_addr_10bit_rw_check_en,
  field_i2c0_ctr_addr_broadcasting_en,
  field_i2c0_data_fifo_rdata,
  field_i2c0_date_date,
  field_i2c0_fifo_conf_rxfifo_wm_thrhd,
  field_i2c0_fifo_conf_txfifo_wm_thrhd,
  field_i2c0_fifo_conf_nonfifo_en,
  field_i2c0_fifo_conf_fifo_addr_cfg_en,
  field_i2c0_fifo_conf_rx_fifo_rst,
  field_i2c0_fifo_conf_tx_fifo_rst,
  field_i2c0_fifo_conf_fifo_prt_en,
  field_i2c0_fifo_st_rxfifo_raddr,
  field_i2c0_fifo_st_rxfifo_waddr,
  field_i2c0_fifo_st_txfifo_raddr,
  field_i2c0_fifo_st_txfifo_waddr,
  field_i2c0_fifo_st_slave_rw_point,
  field_i2c0_filter_cfg_scl_filter_thres,
  field_i2c0_filter_cfg_sda_filter_thres,
  field_i2c0_filter_cfg_scl_filter_en,
  field_i2c0_filter_cfg_sda_filter_en,
  field_i2c0_int_clr_rxfifo_wm_int_clr,
  field_i2c0_int_clr_txfifo_wm_int_clr,
  field_i2c0_int_clr_rxfifo_ovf_int_clr,
  field_i2c0_int_clr_end_detect_int_clr,
  field_i2c0_int_clr_byte_trans_done_int_clr,
  field_i2c0_int_clr_arbitration_lost_int_clr,
  field_i2c0_int_clr_mst_txfifo_udf_int_clr,
  field_i2c0_int_clr_trans_complete_int_clr,
  field_i2c0_int_clr_time_out_int_clr,
  field_i2c0_int_clr_trans_start_int_clr,
  field_i2c0_int_clr_nack_int_clr,
  field_i2c0_int_clr_txfifo_ovf_int_clr,
  field_i2c0_int_clr_rxfifo_udf_int_clr,
  field_i2c0_int_clr_scl_st_to_int_clr,
  field_i2c0_int_clr_scl_main_st_to_int_clr,
  field_i2c0_int_clr_det_start_int_clr,
  field_i2c0_int_clr_slave_stretch_int_clr,
  field_i2c0_int_clr_general_call_int_clr,
  field_i2c0_int_ena_rxfifo_wm_int_ena,
  field_i2c0_int_ena_txfifo_wm_int_ena,
  field_i2c0_int_ena_rxfifo_ovf_int_ena,
  field_i2c0_int_ena_end_detect_int_ena,
  field_i2c0_int_ena_byte_trans_done_int_ena,
  field_i2c0_int_ena_arbitration_lost_int_ena,
  field_i2c0_int_ena_mst_txfifo_udf_int_ena,
  field_i2c0_int_ena_trans_complete_int_ena,
  field_i2c0_int_ena_time_out_int_ena,
  field_i2c0_int_ena_trans_start_int_ena,
  field_i2c0_int_ena_nack_int_ena,
  field_i2c0_int_ena_txfifo_ovf_int_ena,
  field_i2c0_int_ena_rxfifo_udf_int_ena,
  field_i2c0_int_ena_scl_st_to_int_ena,
  field_i2c0_int_ena_scl_main_st_to_int_ena,
  field_i2c0_int_ena_det_start_int_ena,
  field_i2c0_int_ena_slave_stretch_int_ena,
  field_i2c0_int_ena_general_call_int_ena,
  field_i2c0_int_raw_rxfifo_wm_int_raw,
  field_i2c0_int_raw_txfifo_wm_int_raw,
  field_i2c0_int_raw_rxfifo_ovf_int_raw,
  field_i2c0_int_raw_end_detect_int_raw,
  field_i2c0_int_raw_byte_trans_done_int_raw,
  field_i2c0_int_raw_arbitration_lost_int_raw,
  field_i2c0_int_raw_mst_txfifo_udf_int_raw,
  field_i2c0_int_raw_trans_complete_int_raw,
  field_i2c0_int_raw_time_out_int_raw,
  field_i2c0_int_raw_trans_start_int_raw,
  field_i2c0_int_raw_nack_int_raw,
  field_i2c0_int_raw_txfifo_ovf_int_raw,
  field_i2c0_int_raw_rxfifo_udf_int_raw,
  field_i2c0_int_raw_scl_st_to_int_raw,
  field_i2c0_int_raw_scl_main_st_to_int_raw,
  field_i2c0_int_raw_det_start_int_raw,
  field_i2c0_int_raw_slave_stretch_int_raw,
  field_i2c0_int_raw_general_call_int_raw,
  field_i2c0_int_status_rxfifo_wm_int_st,
  field_i2c0_int_status_txfifo_wm_int_st,
  field_i2c0_int_status_rxfifo_ovf_int_st,
  field_i2c0_int_status_end_detect_int_st,
  field_i2c0_int_status_byte_trans_done_int_st,
  field_i2c0_int_status_arbitration_lost_int_st,
  field_i2c0_int_status_mst_txfifo_udf_int_st,
  field_i2c0_int_status_trans_complete_int_st,
  field_i2c0_int_status_time_out_int_st,
  field_i2c0_int_status_trans_start_int_st,
  field_i2c0_int_status_nack_int_st,
  field_i2c0_int_status_txfifo_ovf_int_st,
  field_i2c0_int_status_rxfifo_udf_int_st,
  field_i2c0_int_status_scl_st_to_int_st,
  field_i2c0_int_status_scl_main_st_to_int_st,
  field_i2c0_int_status_det_start_int_st,
  field_i2c0_int_status_slave_stretch_int_st,
  field_i2c0_int_status_general_call_int_st,
  field_i2c0_rxfifo_start_addr_rxfifo_start_addr,
  field_i2c0_scl_high_period_scl_high_period,
  field_i2c0_scl_high_period_scl_wait_high_period,
  field_i2c0_scl_low_period_scl_low_period,
  field_i2c0_scl_main_st_time_out_scl_main_st_to_i2c,
  field_i2c0_scl_rstart_setup_time,
  field_i2c0_scl_sp_conf_scl_rst_slv_en,
  field_i2c0_scl_sp_conf_scl_rst_slv_num,
  field_i2c0_scl_sp_conf_scl_pd_en,
  field_i2c0_scl_sp_conf_sda_pd_en,
  field_i2c0_scl_start_hold_time,
  field_i2c0_scl_stop_hold_time,
  field_i2c0_scl_stop_setup_time,
  field_i2c0_scl_stretch_conf_stretch_protect_num,
  field_i2c0_scl_stretch_conf_slave_scl_stretch_en,
  field_i2c0_scl_stretch_conf_slave_scl_stretch_clr,
  field_i2c0_scl_stretch_conf_slave_byte_ack_ctl_en,
  field_i2c0_scl_stretch_conf_slave_byte_ack_lvl,
  field_i2c0_scl_st_time_out_scl_st_to_i2c,
  field_i2c0_sda_hold_time,
  field_i2c0_sda_sample_time,
  field_i2c0_slave_addr_slave_addr,
  field_i2c0_slave_addr_addr_10bit_en,
  field_i2c0_sr_resp_rec,
  field_i2c0_sr_slave_rw,
  field_i2c0_sr_arb_lost,
  field_i2c0_sr_bus_busy,
  field_i2c0_sr_slave_addressed,
  field_i2c0_sr_rxfifo_cnt,
  field_i2c0_sr_stretch_cause,
  field_i2c0_sr_txfifo_cnt,
  field_i2c0_sr_scl_main_state_last,
  field_i2c0_sr_scl_state_last,
  field_i2c0_to_time_out_value,
  field_i2c0_to_time_out_en,
  field_i2c0_txfifo_start_addr_txfifo_start_addr,
  field_pcr_i2c0_conf_reg_i2c0_clk_en,
  field_pcr_spi2_conf_reg_spi2_clk_en,
  field_pcr_uart0_conf0_reg_uart0_clk_en,
  field_pcr_uart1_conf0_reg_uart1_clk_en,
  field_spi0_cache_fctrl_cache_req_en,
  field_spi0_cache_fctrl_cache_usr_addr_4byte,
  field_spi0_cache_fctrl_cache_flash_usr_cmd,
  field_spi0_cache_fctrl_fdin_dual,
  field_spi0_cache_fctrl_fdout_dual,
  field_spi0_cache_fctrl_faddr_dual,
  field_spi0_cache_fctrl_fdin_quad,
  field_spi0_cache_fctrl_fdout_quad,
  field_spi0_cache_fctrl_faddr_quad,
  field_spi0_clock_clkcnt_l,
  field_spi0_clock_clkcnt_h,
  field_spi0_clock_clkcnt_n,
  field_spi0_clock_clk_equ_sysclk,
  field_spi0_clock_gate_clk_en,
  field_spi0_core_clk_sel_spi01_clk_sel,
  field_spi0_ctrl_fdummy_out,
  field_spi0_ctrl_fcmd_dual,
  field_spi0_ctrl_fcmd_quad,
  field_spi0_ctrl_fastrd_mode,
  field_spi0_ctrl_fread_dual,
  field_spi0_ctrl_q_pol,
  field_spi0_ctrl_d_pol,
  field_spi0_ctrl_fread_quad,
  field_spi0_ctrl_wp,
  field_spi0_ctrl_fread_dio,
  field_spi0_ctrl_fread_qio,
  field_spi0_ctrl1_clk_mode,
  field_spi0_ctrl1_rxfifo_rst,
  field_spi0_ctrl2_cs_setup_time,
  field_spi0_ctrl2_cs_hold_time,
  field_spi0_ctrl2_cs_hold_delay,
  field_spi0_ctrl2_sync_reset,
  field_spi0_date_date,
  field_spi0_din_mode_din0_mode,
  field_spi0_din_mode_din1_mode,
  field_spi0_din_mode_din2_mode,
  field_spi0_din_mode_din3_mode,
  field_spi0_din_num_din0_num,
  field_spi0_din_num_din1_num,
  field_spi0_din_num_din2_num,
  field_spi0_din_num_din3_num,
  field_spi0_dout_mode_dout0_mode,
  field_spi0_dout_mode_dout1_mode,
  field_spi0_dout_mode_dout2_mode,
  field_spi0_dout_mode_dout3_mode,
  field_spi0_fsm_cspi_st,
  field_spi0_fsm_em_st,
  field_spi0_fsm_cspi_lock_delay_time,
  field_spi0_misc_trans_end,
  field_spi0_misc_trans_end_int_ena,
  field_spi0_misc_cspi_st_trans_end,
  field_spi0_misc_cspi_st_trans_end_int_ena,
  field_spi0_misc_ck_idle_edge,
  field_spi0_misc_cs_keep_active,
  field_spi0_rd_status_wb_mode,
  field_spi0_timing_cali_timing_clk_ena,
  field_spi0_timing_cali_timing_cali,
  field_spi0_timing_cali_extra_dummy_cyclelen,
  field_spi0_user_cs_hold,
  field_spi0_user_cs_setup,
  field_spi0_user_ck_out_edge,
  field_spi0_user_usr_dummy_idle,
  field_spi0_user_usr_dummy,
  field_spi0_user1_usr_dummy_cyclelen,
  field_spi0_user1_usr_addr_bitlen,
  field_spi0_user2_usr_command_value,
  field_spi0_user2_usr_command_bitlen,
  field_spi1_addr_usr_addr_value,
  field_spi1_cache_fctrl_cache_usr_addr_4byte,
  field_spi1_cache_fctrl_fdin_dual,
  field_spi1_cache_fctrl_fdout_dual,
  field_spi1_cache_fctrl_faddr_dual,
  field_spi1_cache_fctrl_fdin_quad,
  field_spi1_cache_fctrl_fdout_quad,
  field_spi1_cache_fctrl_faddr_quad,
  field_spi1_clock_clkcnt_l,
  field_spi1_clock_clkcnt_h,
  field_spi1_clock_clkcnt_n,
  field_spi1_clock_clk_equ_sysclk,
  field_spi1_clock_gate_clk_en,
  field_spi1_cmd_spi1_mst_st,
  field_spi1_cmd_mspi_st,
  field_spi1_cmd_flash_pe,
  field_spi1_cmd_usr,
  field_spi1_cmd_flash_hpm,
  field_spi1_cmd_flash_res,
  field_spi1_cmd_flash_dp,
  field_spi1_cmd_flash_ce,
  field_spi1_cmd_flash_be,
  field_spi1_cmd_flash_se,
  field_spi1_cmd_flash_pp,
  field_spi1_cmd_flash_wrsr,
  field_spi1_cmd_flash_rdsr,
  field_spi1_cmd_flash_rdid,
  field_spi1_cmd_flash_wrdi,
  field_spi1_cmd_flash_wren,
  field_spi1_cmd_flash_read,
  field_spi1_ctrl_fdummy_out,
  field_spi1_ctrl_fcmd_dual,
  field_spi1_ctrl_fcmd_quad,
  field_spi1_ctrl_fcs_crc_en,
  field_spi1_ctrl_tx_crc_en,
  field_spi1_ctrl_fastrd_mode,
  field_spi1_ctrl_fread_dual,
  field_spi1_ctrl_resandres,
  field_spi1_ctrl_q_pol,
  field_spi1_ctrl_d_pol,
  field_spi1_ctrl_fread_quad,
  field_spi1_ctrl_wp,
  field_spi1_ctrl_wrsr_2b,
  field_spi1_ctrl_fread_dio,
  field_spi1_ctrl_fread_qio,
  field_spi1_ctrl1_clk_mode,
  field_spi1_ctrl1_cs_hold_dly_res,
  field_spi1_ctrl2_sync_reset,
  field_spi1_date_date,
  field_spi1_flash_sus_cmd_flash_per_command,
  field_spi1_flash_sus_cmd_flash_pes_command,
  field_spi1_flash_sus_cmd_wait_pesr_command,
  field_spi1_flash_sus_ctrl_flash_per,
  field_spi1_flash_sus_ctrl_flash_pes,
  field_spi1_flash_sus_ctrl_flash_per_wait_en,
  field_spi1_flash_sus_ctrl_flash_pes_wait_en,
  field_spi1_flash_sus_ctrl_pes_per_en,
  field_spi1_flash_sus_ctrl_flash_pes_en,
  field_spi1_flash_sus_ctrl_pesr_end_msk,
  field_spi1_flash_sus_ctrl_rd_sus_2b,
  field_spi1_flash_sus_ctrl_per_end_en,
  field_spi1_flash_sus_ctrl_pes_end_en,
  field_spi1_flash_sus_ctrl_sus_timeout_cnt,
  field_spi1_flash_waiti_ctrl_waiti_dummy,
  field_spi1_flash_waiti_ctrl_waiti_cmd,
  field_spi1_flash_waiti_ctrl_waiti_dummy_cyclelen,
  field_spi1_int_clr_per_end_int_clr,
  field_spi1_int_clr_pes_end_int_clr,
  field_spi1_int_clr_wpe_end_int_clr,
  field_spi1_int_clr_slv_st_end_int_clr,
  field_spi1_int_clr_mst_st_end_int_clr,
  field_spi1_int_ena_per_end_int_ena,
  field_spi1_int_ena_pes_end_int_ena,
  field_spi1_int_ena_wpe_end_int_ena,
  field_spi1_int_ena_slv_st_end_int_ena,
  field_spi1_int_ena_mst_st_end_int_ena,
  field_spi1_int_raw_per_end_int_raw,
  field_spi1_int_raw_pes_end_int_raw,
  field_spi1_int_raw_wpe_end_int_raw,
  field_spi1_int_raw_slv_st_end_int_raw,
  field_spi1_int_raw_mst_st_end_int_raw,
  field_spi1_int_st_per_end_int_st,
  field_spi1_int_st_pes_end_int_st,
  field_spi1_int_st_wpe_end_int_st,
  field_spi1_int_st_slv_st_end_int_st,
  field_spi1_int_st_mst_st_end_int_st,
  field_spi1_misc_cs0_dis,
  field_spi1_misc_cs1_dis,
  field_spi1_misc_ck_idle_edge,
  field_spi1_misc_cs_keep_active,
  field_spi1_miso_dlen_usr_miso_dbitlen,
  field_spi1_mosi_dlen_usr_mosi_dbitlen,
  field_spi1_rd_status_status,
  field_spi1_rd_status_wb_mode,
  field_spi1_sus_status_flash_sus,
  field_spi1_sus_status_wait_pesr_cmd_2b,
  field_spi1_sus_status_flash_hpm_dly_128,
  field_spi1_sus_status_flash_res_dly_128,
  field_spi1_sus_status_flash_dp_dly_128,
  field_spi1_sus_status_flash_per_dly_128,
  field_spi1_sus_status_flash_pes_dly_128,
  field_spi1_sus_status_spi0_lock_en,
  field_spi1_timing_cali_timing_cali,
  field_spi1_timing_cali_extra_dummy_cyclelen,
  field_spi1_tx_crc_data,
  field_spi1_user_ck_out_edge,
  field_spi1_user_fwrite_dual,
  field_spi1_user_fwrite_quad,
  field_spi1_user_fwrite_dio,
  field_spi1_user_fwrite_qio,
  field_spi1_user_usr_miso_highpart,
  field_spi1_user_usr_mosi_highpart,
  field_spi1_user_usr_dummy_idle,
  field_spi1_user_usr_mosi,
  field_spi1_user_usr_miso,
  field_spi1_user_usr_dummy,
  field_spi1_user_usr_addr,
  field_spi1_user_usr_command,
  field_spi1_user1_usr_dummy_cyclelen,
  field_spi1_user1_usr_addr_bitlen,
  field_spi1_user2_usr_command_value,
  field_spi1_user2_usr_command_bitlen,
  field_spi1_w0_buf0,
  field_spi1_w1_buf1,
  field_spi1_w10_buf10,
  field_spi1_w11_buf11,
  field_spi1_w12_buf12,
  field_spi1_w13_buf13,
  field_spi1_w14_buf14,
  field_spi1_w15_buf15,
  field_spi1_w2_buf2,
  field_spi1_w3_buf3,
  field_spi1_w4_buf4,
  field_spi1_w5_buf5,
  field_spi1_w6_buf6,
  field_spi1_w7_buf7,
  field_spi1_w8_buf8,
  field_spi1_w9_buf9,
  field_spi2_addr_usr_addr_value,
  field_spi2_clk_gate_clk_en,
  field_spi2_clk_gate_mst_clk_active,
  field_spi2_clk_gate_mst_clk_sel,
  field_spi2_clock_clkcnt_l,
  field_spi2_clock_clkcnt_h,
  field_spi2_clock_clkcnt_n,
  field_spi2_clock_clkdiv_pre,
  field_spi2_clock_clk_equ_sysclk,
  field_spi2_cmd_conf_bitlen,
  field_spi2_cmd_update,
  field_spi2_cmd_usr,
  field_spi2_ctrl_dummy_out,
  field_spi2_ctrl_faddr_dual,
  field_spi2_ctrl_faddr_quad,
  field_spi2_ctrl_fcmd_dual,
  field_spi2_ctrl_fcmd_quad,
  field_spi2_ctrl_fread_dual,
  field_spi2_ctrl_fread_quad,
  field_spi2_ctrl_q_pol,
  field_spi2_ctrl_d_pol,
  field_spi2_ctrl_hold_pol,
  field_spi2_ctrl_wp_pol,
  field_spi2_ctrl_rd_bit_order,
  field_spi2_ctrl_wr_bit_order,
  field_spi2_date_date,
  field_spi2_din_mode_din0_mode,
  field_spi2_din_mode_din1_mode,
  field_spi2_din_mode_din2_mode,
  field_spi2_din_mode_din3_mode,
  field_spi2_din_mode_timing_hclk_active,
  field_spi2_din_num_din0_num,
  field_spi2_din_num_din1_num,
  field_spi2_din_num_din2_num,
  field_spi2_din_num_din3_num,
  field_spi2_dma_conf_dma_slv_seg_trans_en,
  field_spi2_dma_conf_slv_rx_seg_trans_clr_en,
  field_spi2_dma_conf_slv_tx_seg_trans_clr_en,
  field_spi2_dma_conf_rx_eof_en,
  field_spi2_dma_conf_dma_rx_ena,
  field_spi2_dma_conf_dma_tx_ena,
  field_spi2_dma_conf_rx_afifo_rst,
  field_spi2_dma_conf_buf_afifo_rst,
  field_spi2_dma_conf_dma_afifo_rst,
  field_spi2_dma_int_clr_dma_infifo_full_err_int_clr,
  field_spi2_dma_int_clr_dma_outfifo_empty_err_int_clr,
  field_spi2_dma_int_clr_slv_ex_qpi_int_clr,
  field_spi2_dma_int_clr_slv_en_qpi_int_clr,
  field_spi2_dma_int_clr_slv_cmd7_int_clr,
  field_spi2_dma_int_clr_slv_cmd8_int_clr,
  field_spi2_dma_int_clr_slv_cmd9_int_clr,
  field_spi2_dma_int_clr_slv_cmda_int_clr,
  field_spi2_dma_int_clr_slv_rd_dma_done_int_clr,
  field_spi2_dma_int_clr_slv_wr_dma_done_int_clr,
  field_spi2_dma_int_clr_slv_rd_buf_done_int_clr,
  field_spi2_dma_int_clr_slv_wr_buf_done_int_clr,
  field_spi2_dma_int_clr_trans_done_int_clr,
  field_spi2_dma_int_clr_dma_seg_trans_done_int_clr,
  field_spi2_dma_int_clr_seg_magic_err_int_clr,
  field_spi2_dma_int_clr_slv_buf_addr_err_int_clr,
  field_spi2_dma_int_clr_slv_cmd_err_int_clr,
  field_spi2_dma_int_clr_mst_rx_afifo_wfull_err_int_clr,
  field_spi2_dma_int_clr_mst_tx_afifo_rempty_err_int_clr,
  field_spi2_dma_int_clr_app2_int_clr,
  field_spi2_dma_int_clr_app1_int_clr,
  field_spi2_dma_int_ena_dma_infifo_full_err_int_ena,
  field_spi2_dma_int_ena_dma_outfifo_empty_err_int_ena,
  field_spi2_dma_int_ena_slv_ex_qpi_int_ena,
  field_spi2_dma_int_ena_slv_en_qpi_int_ena,
  field_spi2_dma_int_ena_slv_cmd7_int_ena,
  field_spi2_dma_int_ena_slv_cmd8_int_ena,
  field_spi2_dma_int_ena_slv_cmd9_int_ena,
  field_spi2_dma_int_ena_slv_cmda_int_ena,
  field_spi2_dma_int_ena_slv_rd_dma_done_int_ena,
  field_spi2_dma_int_ena_slv_wr_dma_done_int_ena,
  field_spi2_dma_int_ena_slv_rd_buf_done_int_ena,
  field_spi2_dma_int_ena_slv_wr_buf_done_int_ena,
  field_spi2_dma_int_ena_trans_done_int_ena,
  field_spi2_dma_int_ena_dma_seg_trans_done_int_ena,
  field_spi2_dma_int_ena_seg_magic_err_int_ena,
  field_spi2_dma_int_ena_slv_buf_addr_err_int_ena,
  field_spi2_dma_int_ena_slv_cmd_err_int_ena,
  field_spi2_dma_int_ena_mst_rx_afifo_wfull_err_int_ena,
  field_spi2_dma_int_ena_mst_tx_afifo_rempty_err_int_ena,
  field_spi2_dma_int_ena_app2_int_ena,
  field_spi2_dma_int_ena_app1_int_ena,
  field_spi2_dma_int_raw_dma_infifo_full_err_int_raw,
  field_spi2_dma_int_raw_dma_outfifo_empty_err_int_raw,
  field_spi2_dma_int_raw_slv_ex_qpi_int_raw,
  field_spi2_dma_int_raw_slv_en_qpi_int_raw,
  field_spi2_dma_int_raw_slv_cmd7_int_raw,
  field_spi2_dma_int_raw_slv_cmd8_int_raw,
  field_spi2_dma_int_raw_slv_cmd9_int_raw,
  field_spi2_dma_int_raw_slv_cmda_int_raw,
  field_spi2_dma_int_raw_slv_rd_dma_done_int_raw,
  field_spi2_dma_int_raw_slv_wr_dma_done_int_raw,
  field_spi2_dma_int_raw_slv_rd_buf_done_int_raw,
  field_spi2_dma_int_raw_slv_wr_buf_done_int_raw,
  field_spi2_dma_int_raw_trans_done_int_raw,
  field_spi2_dma_int_raw_dma_seg_trans_done_int_raw,
  field_spi2_dma_int_raw_seg_magic_err_int_raw,
  field_spi2_dma_int_raw_slv_buf_addr_err_int_raw,
  field_spi2_dma_int_raw_slv_cmd_err_int_raw,
  field_spi2_dma_int_raw_mst_rx_afifo_wfull_err_int_raw,
  field_spi2_dma_int_raw_mst_tx_afifo_rempty_err_int_raw,
  field_spi2_dma_int_raw_app2_int_raw,
  field_spi2_dma_int_raw_app1_int_raw,
  field_spi2_dma_int_st_dma_infifo_full_err_int_st,
  field_spi2_dma_int_st_dma_outfifo_empty_err_int_st,
  field_spi2_dma_int_st_slv_ex_qpi_int_st,
  field_spi2_dma_int_st_slv_en_qpi_int_st,
  field_spi2_dma_int_st_slv_cmd7_int_st,
  field_spi2_dma_int_st_slv_cmd8_int_st,
  field_spi2_dma_int_st_slv_cmd9_int_st,
  field_spi2_dma_int_st_slv_cmda_int_st,
  field_spi2_dma_int_st_slv_rd_dma_done_int_st,
  field_spi2_dma_int_st_slv_wr_dma_done_int_st,
  field_spi2_dma_int_st_slv_rd_buf_done_int_st,
  field_spi2_dma_int_st_slv_wr_buf_done_int_st,
  field_spi2_dma_int_st_trans_done_int_st,
  field_spi2_dma_int_st_dma_seg_trans_done_int_st,
  field_spi2_dma_int_st_seg_magic_err_int_st,
  field_spi2_dma_int_st_slv_buf_addr_err_int_st,
  field_spi2_dma_int_st_slv_cmd_err_int_st,
  field_spi2_dma_int_st_mst_rx_afifo_wfull_err_int_st,
  field_spi2_dma_int_st_mst_tx_afifo_rempty_err_int_st,
  field_spi2_dma_int_st_app2_int_st,
  field_spi2_dma_int_st_app1_int_st,
  field_spi2_dout_mode_dout0_mode,
  field_spi2_dout_mode_dout1_mode,
  field_spi2_dout_mode_dout2_mode,
  field_spi2_dout_mode_dout3_mode,
  field_spi2_misc_cs0_dis,
  field_spi2_misc_cs1_dis,
  field_spi2_misc_cs2_dis,
  field_spi2_misc_cs3_dis,
  field_spi2_misc_cs4_dis,
  field_spi2_misc_cs5_dis,
  field_spi2_misc_ck_dis,
  field_spi2_misc_master_cs_pol,
  field_spi2_misc_slave_cs_pol,
  field_spi2_misc_ck_idle_edge,
  field_spi2_misc_cs_keep_active,
  field_spi2_misc_quad_din_pin_swap,
  field_spi2_ms_dlen_ms_data_bitlen,
  field_spi2_slave_clk_mode,
  field_spi2_slave_clk_mode_13,
  field_spi2_slave_rsck_data_out,
  field_spi2_slave_slv_rddma_bitlen_en,
  field_spi2_slave_slv_wrdma_bitlen_en,
  field_spi2_slave_slv_rdbuf_bitlen_en,
  field_spi2_slave_slv_wrbuf_bitlen_en,
  field_spi2_slave_dma_seg_magic_value,
  field_spi2_slave_mode,
  field_spi2_slave_soft_reset,
  field_spi2_slave_usr_conf,
  field_spi2_slave1_slv_data_bitlen,
  field_spi2_slave1_slv_last_command,
  field_spi2_slave1_slv_last_addr,
  field_spi2_user_doutdin,
  field_spi2_user_qpi_mode,
  field_spi2_user_tsck_i_edge,
  field_spi2_user_cs_hold,
  field_spi2_user_cs_setup,
  field_spi2_user_rsck_i_edge,
  field_spi2_user_ck_out_edge,
  field_spi2_user_fwrite_dual,
  field_spi2_user_fwrite_quad,
  field_spi2_user_usr_conf_nxt,
  field_spi2_user_sio,
  field_spi2_user_usr_miso_highpart,
  field_spi2_user_usr_mosi_highpart,
  field_spi2_user_usr_dummy_idle,
  field_spi2_user_usr_mosi,
  field_spi2_user_usr_miso,
  field_spi2_user_usr_dummy,
  field_spi2_user_usr_addr,
  field_spi2_user_usr_command,
  field_spi2_user1_usr_dummy_cyclelen,
  field_spi2_user1_mst_wfull_err_end_en,
  field_spi2_user1_cs_setup_time,
  field_spi2_user1_cs_hold_time,
  field_spi2_user1_usr_addr_bitlen,
  field_spi2_user2_usr_command_value,
  field_spi2_user2_mst_rempty_err_end_en,
  field_spi2_user2_usr_command_bitlen,
  field_spi2_w0_buf0,
  field_spi2_w1_buf1,
  field_spi2_w10_buf10,
  field_spi2_w11_buf11,
  field_spi2_w12_buf12,
  field_spi2_w13_buf13,
  field_spi2_w14_buf14,
  field_spi2_w15_buf15,
  field_spi2_w2_buf2,
  field_spi2_w3_buf3,
  field_spi2_w4_buf4,
  field_spi2_w5_buf5,
  field_spi2_w6_buf6,
  field_spi2_w7_buf7,
  field_spi2_w8_buf8,
  field_spi2_w9_buf9,
  field_uart0_at_cmd_char_at_cmd_char,
  field_uart0_at_cmd_char_char_num,
  field_uart0_at_cmd_gaptout_rx_gap_tout,
  field_uart0_at_cmd_postcnt_post_idle_num,
  field_uart0_at_cmd_precnt_pre_idle_num,
  field_uart0_clkdiv_clkdiv,
  field_uart0_clkdiv_frag,
  field_uart0_clk_conf_sclk_div_b,
  field_uart0_clk_conf_sclk_div_a,
  field_uart0_clk_conf_sclk_div_num,
  field_uart0_clk_conf_sclk_sel,
  field_uart0_clk_conf_sclk_en,
  field_uart0_clk_conf_rst_core,
  field_uart0_clk_conf_tx_sclk_en,
  field_uart0_clk_conf_rx_sclk_en,
  field_uart0_clk_conf_tx_rst_core,
  field_uart0_clk_conf_rx_rst_core,
  field_uart0_conf0_parity,
  field_uart0_conf0_parity_en,
  field_uart0_conf0_bit_num,
  field_uart0_conf0_stop_bit_num,
  field_uart0_conf0_sw_rts,
  field_uart0_conf0_sw_dtr,
  field_uart0_conf0_txd_brk,
  field_uart0_conf0_irda_dplx,
  field_uart0_conf0_irda_tx_en,
  field_uart0_conf0_irda_wctl,
  field_uart0_conf0_irda_tx_inv,
  field_uart0_conf0_irda_rx_inv,
  field_uart0_conf0_loopback,
  field_uart0_conf0_tx_flow_en,
  field_uart0_conf0_irda_en,
  field_uart0_conf0_rxfifo_rst,
  field_uart0_conf0_txfifo_rst,
  field_uart0_conf0_rxd_inv,
  field_uart0_conf0_cts_inv,
  field_uart0_conf0_dsr_inv,
  field_uart0_conf0_txd_inv,
  field_uart0_conf0_rts_inv,
  field_uart0_conf0_dtr_inv,
  field_uart0_conf0_clk_en,
  field_uart0_conf0_err_wr_mask,
  field_uart0_conf0_autobaud_en,
  field_uart0_conf0_mem_clk_en,
  field_uart0_conf1_rxfifo_full_thrhd,
  field_uart0_conf1_txfifo_empty_thrhd,
  field_uart0_conf1_dis_rx_dat_ovf,
  field_uart0_conf1_rx_tout_flow_dis,
  field_uart0_conf1_rx_flow_en,
  field_uart0_conf1_rx_tout_en,
  field_uart0_date_date,
  field_uart0_fifo_rxfifo_rd_byte,
  field_uart0_flow_conf_sw_flow_con_en,
  field_uart0_flow_conf_xonoff_del,
  field_uart0_flow_conf_force_xon,
  field_uart0_flow_conf_force_xoff,
  field_uart0_flow_conf_send_xon,
  field_uart0_flow_conf_send_xoff,
  field_uart0_fsm_status_st_urx_out,
  field_uart0_fsm_status_st_utx_out,
  field_uart0_highpulse_min_cnt,
  field_uart0_id_id,
  field_uart0_id_high_speed,
  field_uart0_id_reg_update,
  field_uart0_idle_conf_rx_idle_thrhd,
  field_uart0_idle_conf_tx_idle_num,
  field_uart0_int_clr_rxfifo_full_int_clr,
  field_uart0_int_clr_txfifo_empty_int_clr,
  field_uart0_int_clr_parity_err_int_clr,
  field_uart0_int_clr_frm_err_int_clr,
  field_uart0_int_clr_rxfifo_ovf_int_clr,
  field_uart0_int_clr_dsr_chg_int_clr,
  field_uart0_int_clr_cts_chg_int_clr,
  field_uart0_int_clr_brk_det_int_clr,
  field_uart0_int_clr_rxfifo_tout_int_clr,
  field_uart0_int_clr_sw_xon_int_clr,
  field_uart0_int_clr_sw_xoff_int_clr,
  field_uart0_int_clr_glitch_det_int_clr,
  field_uart0_int_clr_tx_brk_done_int_clr,
  field_uart0_int_clr_tx_brk_idle_done_int_clr,
  field_uart0_int_clr_tx_done_int_clr,
  field_uart0_int_clr_rs485_parity_err_int_clr,
  field_uart0_int_clr_rs485_frm_err_int_clr,
  field_uart0_int_clr_rs485_clash_int_clr,
  field_uart0_int_clr_at_cmd_char_det_int_clr,
  field_uart0_int_clr_wakeup_int_clr,
  field_uart0_int_ena_rxfifo_full_int_ena,
  field_uart0_int_ena_txfifo_empty_int_ena,
  field_uart0_int_ena_parity_err_int_ena,
  field_uart0_int_ena_frm_err_int_ena,
  field_uart0_int_ena_rxfifo_ovf_int_ena,
  field_uart0_int_ena_dsr_chg_int_ena,
  field_uart0_int_ena_cts_chg_int_ena,
  field_uart0_int_ena_brk_det_int_ena,
  field_uart0_int_ena_rxfifo_tout_int_ena,
  field_uart0_int_ena_sw_xon_int_ena,
  field_uart0_int_ena_sw_xoff_int_ena,
  field_uart0_int_ena_glitch_det_int_ena,
  field_uart0_int_ena_tx_brk_done_int_ena,
  field_uart0_int_ena_tx_brk_idle_done_int_ena,
  field_uart0_int_ena_tx_done_int_ena,
  field_uart0_int_ena_rs485_parity_err_int_ena,
  field_uart0_int_ena_rs485_frm_err_int_ena,
  field_uart0_int_ena_rs485_clash_int_ena,
  field_uart0_int_ena_at_cmd_char_det_int_ena,
  field_uart0_int_ena_wakeup_int_ena,
  field_uart0_int_raw_rxfifo_full_int_raw,
  field_uart0_int_raw_txfifo_empty_int_raw,
  field_uart0_int_raw_parity_err_int_raw,
  field_uart0_int_raw_frm_err_int_raw,
  field_uart0_int_raw_rxfifo_ovf_int_raw,
  field_uart0_int_raw_dsr_chg_int_raw,
  field_uart0_int_raw_cts_chg_int_raw,
  field_uart0_int_raw_brk_det_int_raw,
  field_uart0_int_raw_rxfifo_tout_int_raw,
  field_uart0_int_raw_sw_xon_int_raw,
  field_uart0_int_raw_sw_xoff_int_raw,
  field_uart0_int_raw_glitch_det_int_raw,
  field_uart0_int_raw_tx_brk_done_int_raw,
  field_uart0_int_raw_tx_brk_idle_done_int_raw,
  field_uart0_int_raw_tx_done_int_raw,
  field_uart0_int_raw_rs485_parity_err_int_raw,
  field_uart0_int_raw_rs485_frm_err_int_raw,
  field_uart0_int_raw_rs485_clash_int_raw,
  field_uart0_int_raw_at_cmd_char_det_int_raw,
  field_uart0_int_raw_wakeup_int_raw,
  field_uart0_int_st_rxfifo_full_int_st,
  field_uart0_int_st_txfifo_empty_int_st,
  field_uart0_int_st_parity_err_int_st,
  field_uart0_int_st_frm_err_int_st,
  field_uart0_int_st_rxfifo_ovf_int_st,
  field_uart0_int_st_dsr_chg_int_st,
  field_uart0_int_st_cts_chg_int_st,
  field_uart0_int_st_brk_det_int_st,
  field_uart0_int_st_rxfifo_tout_int_st,
  field_uart0_int_st_sw_xon_int_st,
  field_uart0_int_st_sw_xoff_int_st,
  field_uart0_int_st_glitch_det_int_st,
  field_uart0_int_st_tx_brk_done_int_st,
  field_uart0_int_st_tx_brk_idle_done_int_st,
  field_uart0_int_st_tx_done_int_st,
  field_uart0_int_st_rs485_parity_err_int_st,
  field_uart0_int_st_rs485_frm_err_int_st,
  field_uart0_int_st_rs485_clash_int_st,
  field_uart0_int_st_at_cmd_char_det_int_st,
  field_uart0_int_st_wakeup_int_st,
  field_uart0_lowpulse_min_cnt,
  field_uart0_mem_conf_rx_size,
  field_uart0_mem_conf_tx_size,
  field_uart0_mem_conf_rx_flow_thrhd,
  field_uart0_mem_conf_rx_tout_thrhd,
  field_uart0_mem_conf_mem_force_pd,
  field_uart0_mem_conf_mem_force_pu,
  field_uart0_mem_rx_status_apb_rx_raddr,
  field_uart0_mem_rx_status_rx_waddr,
  field_uart0_mem_tx_status_apb_tx_waddr,
  field_uart0_mem_tx_status_tx_raddr,
  field_uart0_negpulse_negedge_min_cnt,
  field_uart0_pospulse_posedge_min_cnt,
  field_uart0_rs485_conf_rs485_en,
  field_uart0_rs485_conf_dl0_en,
  field_uart0_rs485_conf_dl1_en,
  field_uart0_rs485_conf_rs485tx_rx_en,
  field_uart0_rs485_conf_rs485rxby_tx_en,
  field_uart0_rs485_conf_rs485_rx_dly_num,
  field_uart0_rs485_conf_rs485_tx_dly_num,
  field_uart0_rxd_cnt_rxd_edge_cnt,
  field_uart0_rx_filt_glitch_filt,
  field_uart0_rx_filt_glitch_filt_en,
  field_uart0_sleep_conf_active_threshold,
  field_uart0_status_rxfifo_cnt,
  field_uart0_status_dsrn,
  field_uart0_status_ctsn,
  field_uart0_status_rxd,
  field_uart0_status_txfifo_cnt,
  field_uart0_status_dtrn,
  field_uart0_status_rtsn,
  field_uart0_status_txd,
  field_uart0_swfc_conf0_xoff_threshold,
  field_uart0_swfc_conf0_xoff_char,
  field_uart0_swfc_conf1_xon_threshold,
  field_uart0_swfc_conf1_xon_char,
  field_uart0_txbrk_conf_tx_brk_num,
  field_uart1_at_cmd_char_at_cmd_char,
  field_uart1_at_cmd_char_char_num,
  field_uart1_at_cmd_gaptout_rx_gap_tout,
  field_uart1_at_cmd_postcnt_post_idle_num,
  field_uart1_at_cmd_precnt_pre_idle_num,
  field_uart1_clkdiv_clkdiv,
  field_uart1_clkdiv_frag,
  field_uart1_clk_conf_sclk_div_b,
  field_uart1_clk_conf_sclk_div_a,
  field_uart1_clk_conf_sclk_div_num,
  field_uart1_clk_conf_sclk_sel,
  field_uart1_clk_conf_sclk_en,
  field_uart1_clk_conf_rst_core,
  field_uart1_clk_conf_tx_sclk_en,
  field_uart1_clk_conf_rx_sclk_en,
  field_uart1_clk_conf_tx_rst_core,
  field_uart1_clk_conf_rx_rst_core,
  field_uart1_conf0_parity,
  field_uart1_conf0_parity_en,
  field_uart1_conf0_bit_num,
  field_uart1_conf0_stop_bit_num,
  field_uart1_conf0_sw_rts,
  field_uart1_conf0_sw_dtr,
  field_uart1_conf0_txd_brk,
  field_uart1_conf0_irda_dplx,
  field_uart1_conf0_irda_tx_en,
  field_uart1_conf0_irda_wctl,
  field_uart1_conf0_irda_tx_inv,
  field_uart1_conf0_irda_rx_inv,
  field_uart1_conf0_loopback,
  field_uart1_conf0_tx_flow_en,
  field_uart1_conf0_irda_en,
  field_uart1_conf0_rxfifo_rst,
  field_uart1_conf0_txfifo_rst,
  field_uart1_conf0_rxd_inv,
  field_uart1_conf0_cts_inv,
  field_uart1_conf0_dsr_inv,
  field_uart1_conf0_txd_inv,
  field_uart1_conf0_rts_inv,
  field_uart1_conf0_dtr_inv,
  field_uart1_conf0_clk_en,
  field_uart1_conf0_err_wr_mask,
  field_uart1_conf0_autobaud_en,
  field_uart1_conf0_mem_clk_en,
  field_uart1_conf1_rxfifo_full_thrhd,
  field_uart1_conf1_txfifo_empty_thrhd,
  field_uart1_conf1_dis_rx_dat_ovf,
  field_uart1_conf1_rx_tout_flow_dis,
  field_uart1_conf1_rx_flow_en,
  field_uart1_conf1_rx_tout_en,
  field_uart1_date_date,
  field_uart1_fifo_rxfifo_rd_byte,
  field_uart1_flow_conf_sw_flow_con_en,
  field_uart1_flow_conf_xonoff_del,
  field_uart1_flow_conf_force_xon,
  field_uart1_flow_conf_force_xoff,
  field_uart1_flow_conf_send_xon,
  field_uart1_flow_conf_send_xoff,
  field_uart1_fsm_status_st_urx_out,
  field_uart1_fsm_status_st_utx_out,
  field_uart1_highpulse_min_cnt,
  field_uart1_id_id,
  field_uart1_id_high_speed,
  field_uart1_id_reg_update,
  field_uart1_idle_conf_rx_idle_thrhd,
  field_uart1_idle_conf_tx_idle_num,
  field_uart1_int_clr_rxfifo_full_int_clr,
  field_uart1_int_clr_txfifo_empty_int_clr,
  field_uart1_int_clr_parity_err_int_clr,
  field_uart1_int_clr_frm_err_int_clr,
  field_uart1_int_clr_rxfifo_ovf_int_clr,
  field_uart1_int_clr_dsr_chg_int_clr,
  field_uart1_int_clr_cts_chg_int_clr,
  field_uart1_int_clr_brk_det_int_clr,
  field_uart1_int_clr_rxfifo_tout_int_clr,
  field_uart1_int_clr_sw_xon_int_clr,
  field_uart1_int_clr_sw_xoff_int_clr,
  field_uart1_int_clr_glitch_det_int_clr,
  field_uart1_int_clr_tx_brk_done_int_clr,
  field_uart1_int_clr_tx_brk_idle_done_int_clr,
  field_uart1_int_clr_tx_done_int_clr,
  field_uart1_int_clr_rs485_parity_err_int_clr,
  field_uart1_int_clr_rs485_frm_err_int_clr,
  field_uart1_int_clr_rs485_clash_int_clr,
  field_uart1_int_clr_at_cmd_char_det_int_clr,
  field_uart1_int_clr_wakeup_int_clr,
  field_uart1_int_ena_rxfifo_full_int_ena,
  field_uart1_int_ena_txfifo_empty_int_ena,
  field_uart1_int_ena_parity_err_int_ena,
  field_uart1_int_ena_frm_err_int_ena,
  field_uart1_int_ena_rxfifo_ovf_int_ena,
  field_uart1_int_ena_dsr_chg_int_ena,
  field_uart1_int_ena_cts_chg_int_ena,
  field_uart1_int_ena_brk_det_int_ena,
  field_uart1_int_ena_rxfifo_tout_int_ena,
  field_uart1_int_ena_sw_xon_int_ena,
  field_uart1_int_ena_sw_xoff_int_ena,
  field_uart1_int_ena_glitch_det_int_ena,
  field_uart1_int_ena_tx_brk_done_int_ena,
  field_uart1_int_ena_tx_brk_idle_done_int_ena,
  field_uart1_int_ena_tx_done_int_ena,
  field_uart1_int_ena_rs485_parity_err_int_ena,
  field_uart1_int_ena_rs485_frm_err_int_ena,
  field_uart1_int_ena_rs485_clash_int_ena,
  field_uart1_int_ena_at_cmd_char_det_int_ena,
  field_uart1_int_ena_wakeup_int_ena,
  field_uart1_int_raw_rxfifo_full_int_raw,
  field_uart1_int_raw_txfifo_empty_int_raw,
  field_uart1_int_raw_parity_err_int_raw,
  field_uart1_int_raw_frm_err_int_raw,
  field_uart1_int_raw_rxfifo_ovf_int_raw,
  field_uart1_int_raw_dsr_chg_int_raw,
  field_uart1_int_raw_cts_chg_int_raw,
  field_uart1_int_raw_brk_det_int_raw,
  field_uart1_int_raw_rxfifo_tout_int_raw,
  field_uart1_int_raw_sw_xon_int_raw,
  field_uart1_int_raw_sw_xoff_int_raw,
  field_uart1_int_raw_glitch_det_int_raw,
  field_uart1_int_raw_tx_brk_done_int_raw,
  field_uart1_int_raw_tx_brk_idle_done_int_raw,
  field_uart1_int_raw_tx_done_int_raw,
  field_uart1_int_raw_rs485_parity_err_int_raw,
  field_uart1_int_raw_rs485_frm_err_int_raw,
  field_uart1_int_raw_rs485_clash_int_raw,
  field_uart1_int_raw_at_cmd_char_det_int_raw,
  field_uart1_int_raw_wakeup_int_raw,
  field_uart1_int_st_rxfifo_full_int_st,
  field_uart1_int_st_txfifo_empty_int_st,
  field_uart1_int_st_parity_err_int_st,
  field_uart1_int_st_frm_err_int_st,
  field_uart1_int_st_rxfifo_ovf_int_st,
  field_uart1_int_st_dsr_chg_int_st,
  field_uart1_int_st_cts_chg_int_st,
  field_uart1_int_st_brk_det_int_st,
  field_uart1_int_st_rxfifo_tout_int_st,
  field_uart1_int_st_sw_xon_int_st,
  field_uart1_int_st_sw_xoff_int_st,
  field_uart1_int_st_glitch_det_int_st,
  field_uart1_int_st_tx_brk_done_int_st,
  field_uart1_int_st_tx_brk_idle_done_int_st,
  field_uart1_int_st_tx_done_int_st,
  field_uart1_int_st_rs485_parity_err_int_st,
  field_uart1_int_st_rs485_frm_err_int_st,
  field_uart1_int_st_rs485_clash_int_st,
  field_uart1_int_st_at_cmd_char_det_int_st,
  field_uart1_int_st_wakeup_int_st,
  field_uart1_lowpulse_min_cnt,
  field_uart1_mem_conf_rx_size,
  field_uart1_mem_conf_tx_size,
  field_uart1_mem_conf_rx_flow_thrhd,
  field_uart1_mem_conf_rx_tout_thrhd,
  field_uart1_mem_conf_mem_force_pd,
  field_uart1_mem_conf_mem_force_pu,
  field_uart1_mem_rx_status_apb_rx_raddr,
  field_uart1_mem_rx_status_rx_waddr,
  field_uart1_mem_tx_status_apb_tx_waddr,
  field_uart1_mem_tx_status_tx_raddr,
  field_uart1_negpulse_negedge_min_cnt,
  field_uart1_pospulse_posedge_min_cnt,
  field_uart1_rs485_conf_rs485_en,
  field_uart1_rs485_conf_dl0_en,
  field_uart1_rs485_conf_dl1_en,
  field_uart1_rs485_conf_rs485tx_rx_en,
  field_uart1_rs485_conf_rs485rxby_tx_en,
  field_uart1_rs485_conf_rs485_rx_dly_num,
  field_uart1_rs485_conf_rs485_tx_dly_num,
  field_uart1_rxd_cnt_rxd_edge_cnt,
  field_uart1_rx_filt_glitch_filt,
  field_uart1_rx_filt_glitch_filt_en,
  field_uart1_sleep_conf_active_threshold,
  field_uart1_status_rxfifo_cnt,
  field_uart1_status_dsrn,
  field_uart1_status_ctsn,
  field_uart1_status_rxd,
  field_uart1_status_txfifo_cnt,
  field_uart1_status_dtrn,
  field_uart1_status_rtsn,
  field_uart1_status_txd,
  field_uart1_swfc_conf0_xoff_threshold,
  field_uart1_swfc_conf0_xoff_char,
  field_uart1_swfc_conf1_xon_threshold,
  field_uart1_swfc_conf1_xon_char,
  field_uart1_txbrk_conf_tx_brk_num,
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
struct RegisterFieldTraits<FieldId::field_apb_saradc_apb_tsens_ctrl_tsens_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_apb_tsens_ctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_apb_tsens_ctrl_tsens_in_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_apb_tsens_ctrl;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_apb_tsens_ctrl_tsens_clk_div> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_apb_tsens_ctrl;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_apb_tsens_ctrl_tsens_pu> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_apb_tsens_ctrl;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_arb_ctrl_adc_arb_apb_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_arb_ctrl;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_arb_ctrl_adc_arb_rtc_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_arb_ctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_arb_ctrl_adc_arb_wifi_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_arb_ctrl;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_arb_ctrl_adc_arb_grant_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_arb_ctrl;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_arb_ctrl_adc_arb_apb_priority> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_arb_ctrl;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_arb_ctrl_adc_arb_rtc_priority> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_arb_ctrl;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_arb_ctrl_adc_arb_wifi_priority> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_arb_ctrl;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_arb_ctrl_adc_arb_fix_priority> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_arb_ctrl;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_cali_apb_saradc_cali_cfg> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_cali;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 17u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_clkm_conf_clkm_div_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_clkm_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_clkm_conf_clkm_div_b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_clkm_conf;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_clkm_conf_clkm_div_a> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_clkm_conf;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_clkm_conf_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_clkm_conf;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_clkm_conf_clk_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_clkm_conf;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl_saradc_start_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl_saradc_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl_saradc_sar_clk_gated> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl_saradc_sar_clk_div> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl_saradc_sar_patt_len> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl_saradc_sar_patt_p_clear> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl_saradc_xpd_sar_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl_saradc_wait_arb_cycle> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl2_saradc_meas_num_limit> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl2_saradc_max_meas_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl2;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl2_saradc_sar1_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl2;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl2_saradc_sar2_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl2;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl2_saradc_timer_target> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl2;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl2_saradc_timer_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl2;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_ctrl_date_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_ctrl_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_dma_conf_apb_adc_eof_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_dma_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_dma_conf_apb_adc_reset_fsm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_dma_conf;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_dma_conf_apb_adc_trans> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_dma_conf;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_filter_ctrl0_apb_saradc_filter_channel1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_filter_ctrl0;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_filter_ctrl0_apb_saradc_filter_channel0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_filter_ctrl0;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_filter_ctrl0_apb_saradc_filter_reset> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_filter_ctrl0;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_filter_ctrl1_apb_saradc_filter_factor1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_filter_ctrl1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_filter_ctrl1_apb_saradc_filter_factor0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_filter_ctrl1;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_fsm_wait_saradc_xpd_wait> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_fsm_wait;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_fsm_wait_saradc_rstb_wait> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_fsm_wait;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_fsm_wait_saradc_standby_wait> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_fsm_wait;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_clr_apb_saradc_thres1_low_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_clr;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_clr_apb_saradc_thres0_low_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_clr;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_clr_apb_saradc_thres1_high_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_clr;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_clr_apb_saradc_thres0_high_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_clr;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_clr_apb_saradc2_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_clr;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_clr_apb_saradc1_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_clr;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_ena_apb_saradc_thres1_low_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_ena;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_ena_apb_saradc_thres0_low_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_ena;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_ena_apb_saradc_thres1_high_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_ena;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_ena_apb_saradc_thres0_high_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_ena;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_ena_apb_saradc2_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_ena;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_ena_apb_saradc1_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_ena;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_raw_apb_saradc_thres1_low_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_raw;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_raw_apb_saradc_thres0_low_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_raw;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_raw_apb_saradc_thres1_high_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_raw;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_raw_apb_saradc_thres0_high_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_raw;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_raw_apb_saradc2_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_raw;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_raw_apb_saradc1_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_raw;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_st_apb_saradc_thres1_low_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_st;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_st_apb_saradc_thres0_low_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_st;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_st_apb_saradc_thres1_high_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_st;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_st_apb_saradc_thres0_high_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_st;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_st_apb_saradc2_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_st;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_int_st_apb_saradc1_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_int_st;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_onetime_sample_saradc_onetime_atten> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_onetime_sample;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_onetime_sample_saradc_onetime_channel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_onetime_sample;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_onetime_sample_saradc_onetime_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_onetime_sample;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_onetime_sample_saradc2_onetime_sample> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_onetime_sample;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_onetime_sample_saradc1_onetime_sample> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_onetime_sample;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_sar1data_status_apb_saradc1_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_sar1data_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 17u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_sar1_status_saradc_sar1_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_sar1_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_sar2data_status_apb_saradc2_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_sar2data_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 17u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_sar2_status_saradc_sar2_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_sar2_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_sar_patt_tab1_saradc_sar_patt_tab1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_sar_patt_tab1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_sar_patt_tab2_saradc_sar_patt_tab2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_sar_patt_tab2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_thres0_ctrl_apb_saradc_thres0_channel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_thres0_ctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_thres0_ctrl_apb_saradc_thres0_high> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_thres0_ctrl;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 13u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_thres0_ctrl_apb_saradc_thres0_low> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_thres0_ctrl;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 13u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_thres1_ctrl_apb_saradc_thres1_channel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_thres1_ctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_thres1_ctrl_apb_saradc_thres1_high> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_thres1_ctrl;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 13u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_thres1_ctrl_apb_saradc_thres1_low> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_thres1_ctrl;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 13u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_thres_ctrl_apb_saradc_thres_all_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_thres_ctrl;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_thres_ctrl_apb_saradc_thres1_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_thres_ctrl;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_thres_ctrl_apb_saradc_thres0_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_thres_ctrl;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_tsens_ctrl2_tsens_xpd_wait> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_tsens_ctrl2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_tsens_ctrl2_tsens_xpd_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_tsens_ctrl2;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_tsens_ctrl2_tsens_clk_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_tsens_ctrl2;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_apb_saradc_tsens_ctrl2_tsens_clk_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_apb_saradc_tsens_ctrl2;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_ahb_test_ahb_testmode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_ahb_test;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_ahb_test_ahb_testaddr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_ahb_test;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_date_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch0_infifo_full> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch0_infifo_empty> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch0_infifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch0_in_remain_under_1b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch0_in_remain_under_2b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch0_in_remain_under_3b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch0_in_remain_under_4b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch0_in_buf_hungry> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch1_infifo_full> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch1_infifo_empty> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch1_infifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch1_in_remain_under_1b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch1_in_remain_under_2b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch1_in_remain_under_3b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch1_in_remain_under_4b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch1_in_buf_hungry> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch2_infifo_full> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch2_infifo_empty> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch2_infifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch2_in_remain_under_1b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch2_in_remain_under_2b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch2_in_remain_under_3b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch2_in_remain_under_4b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_infifo_status_ch2_in_buf_hungry> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_infifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_clr_ch_s_in_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_clr_ch_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_clr_ch_s_in_suc_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_clr_ch_s;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_clr_ch_s_in_err_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_clr_ch_s;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_clr_ch_s_out_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_clr_ch_s;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_clr_ch_s_out_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_clr_ch_s;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_clr_ch_s_in_dscr_err> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_clr_ch_s;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_clr_ch_s_out_dscr_err> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_clr_ch_s;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_clr_ch_s_in_dscr_empty> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_clr_ch_s;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_clr_ch_s_out_total_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_clr_ch_s;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_clr_ch_s_infifo_ovf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_clr_ch_s;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_clr_ch_s_infifo_udf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_clr_ch_s;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_clr_ch_s_outfifo_ovf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_clr_ch_s;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_clr_ch_s_outfifo_udf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_clr_ch_s;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_ena_ch_s_in_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_ena_ch_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_ena_ch_s_in_suc_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_ena_ch_s;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_ena_ch_s_in_err_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_ena_ch_s;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_ena_ch_s_out_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_ena_ch_s;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_ena_ch_s_out_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_ena_ch_s;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_ena_ch_s_in_dscr_err> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_ena_ch_s;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_ena_ch_s_out_dscr_err> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_ena_ch_s;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_ena_ch_s_in_dscr_empty> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_ena_ch_s;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_ena_ch_s_out_total_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_ena_ch_s;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_ena_ch_s_infifo_ovf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_ena_ch_s;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_ena_ch_s_infifo_udf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_ena_ch_s;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_ena_ch_s_outfifo_ovf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_ena_ch_s;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_ena_ch_s_outfifo_udf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_ena_ch_s;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_raw_ch_s_in_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_raw_ch_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_raw_ch_s_in_suc_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_raw_ch_s;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_raw_ch_s_in_err_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_raw_ch_s;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_raw_ch_s_out_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_raw_ch_s;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_raw_ch_s_out_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_raw_ch_s;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_raw_ch_s_in_dscr_err> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_raw_ch_s;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_raw_ch_s_out_dscr_err> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_raw_ch_s;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_raw_ch_s_in_dscr_empty> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_raw_ch_s;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_raw_ch_s_out_total_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_raw_ch_s;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_raw_ch_s_infifo_ovf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_raw_ch_s;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_raw_ch_s_infifo_udf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_raw_ch_s;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_raw_ch_s_outfifo_ovf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_raw_ch_s;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_raw_ch_s_outfifo_udf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_raw_ch_s;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch0_in_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch0_in_suc_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch0;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch0_in_err_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch0;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch0_out_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch0;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch0_out_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch0;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch0_in_dscr_err> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch0;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch0_out_dscr_err> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch0;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch0_in_dscr_empty> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch0;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch0_out_total_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch0;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch0_infifo_ovf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch0;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch0_infifo_udf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch0;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch0_outfifo_ovf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch0;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch0_outfifo_udf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch0;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch1_in_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch1_in_suc_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch1;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch1_in_err_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch1;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch1_out_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch1;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch1_out_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch1;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch1_in_dscr_err> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch1;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch1_out_dscr_err> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch1;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch1_in_dscr_empty> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch1;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch1_out_total_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch1;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch1_infifo_ovf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch1;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch1_infifo_udf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch1;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch1_outfifo_ovf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch1;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch1_outfifo_udf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch1;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch2_in_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch2_in_suc_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch2;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch2_in_err_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch2;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch2_out_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch2;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch2_out_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch2;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch2_in_dscr_err> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch2;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch2_out_dscr_err> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch2;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch2_in_dscr_empty> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch2;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch2_out_total_eof> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch2;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch2_infifo_ovf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch2;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch2_infifo_udf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch2;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch2_outfifo_ovf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch2;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_int_st_ch2_outfifo_udf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_int_st_ch2;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_conf0_ch_s_in_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_conf0_ch_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_conf0_ch_s_in_loop_test> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_conf0_ch_s;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_conf0_ch_s_indscr_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_conf0_ch_s;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_conf0_ch_s_in_data_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_conf0_ch_s;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_conf0_ch_s_mem_trans_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_conf0_ch_s;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_conf1_ch0_in_check_owner> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_conf1_ch0;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_conf1_ch1_in_check_owner> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_conf1_ch1;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_conf1_ch2_in_check_owner> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_conf1_ch2;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_dscr_bf0_ch_s_inlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_dscr_bf0_ch_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_dscr_bf1_ch0_inlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_dscr_bf1_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_dscr_bf1_ch1_inlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_dscr_bf1_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_dscr_bf1_ch2_inlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_dscr_bf1_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_dscr_ch0_inlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_dscr_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_dscr_ch1_inlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_dscr_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_dscr_ch2_inlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_dscr_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_err_eof_des_addr_ch0_in_err_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_err_eof_des_addr_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_err_eof_des_addr_ch1_in_err_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_err_eof_des_addr_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_err_eof_des_addr_ch2_in_err_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_err_eof_des_addr_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_link_ch_s_inlink_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_link_ch_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_link_ch_s_inlink_auto_ret> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_link_ch_s;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_link_ch_s_inlink_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_link_ch_s;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_link_ch_s_inlink_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_link_ch_s;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_link_ch_s_inlink_restart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_link_ch_s;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_link_ch_s_inlink_park> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_link_ch_s;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_peri_sel_ch_s_peri_in_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_peri_sel_ch_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_pop_ch0_infifo_rdata> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_pop_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_pop_ch0_infifo_pop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_pop_ch0;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_pop_ch1_infifo_rdata> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_pop_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_pop_ch1_infifo_pop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_pop_ch1;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_pop_ch2_infifo_rdata> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_pop_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_pop_ch2_infifo_pop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_pop_ch2;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_pri_ch_s_rx_pri> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_pri_ch_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_state_ch0_inlink_dscr_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_state_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 18u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_state_ch0_in_dscr_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_state_ch0;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_state_ch0_in_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_state_ch0;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_state_ch1_inlink_dscr_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_state_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 18u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_state_ch1_in_dscr_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_state_ch1;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_state_ch1_in_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_state_ch1;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_state_ch2_inlink_dscr_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_state_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 18u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_state_ch2_in_dscr_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_state_ch2;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_state_ch2_in_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_state_ch2;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_suc_eof_des_addr_ch0_in_suc_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_suc_eof_des_addr_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_suc_eof_des_addr_ch1_in_suc_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_suc_eof_des_addr_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_in_suc_eof_des_addr_ch2_in_suc_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_in_suc_eof_des_addr_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_misc_conf_ahbm_rst_inter> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_misc_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_misc_conf_arb_pri_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_misc_conf;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_misc_conf_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_misc_conf;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch0_outfifo_full> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch0_outfifo_empty> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch0_outfifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch0_out_remain_under_1b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch0_out_remain_under_2b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch0_out_remain_under_3b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch0_out_remain_under_4b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch0;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch1_outfifo_full> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch1_outfifo_empty> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch1_outfifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch1_out_remain_under_1b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch1_out_remain_under_2b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch1_out_remain_under_3b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch1_out_remain_under_4b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch2_outfifo_full> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch2_outfifo_empty> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch2_outfifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch2_out_remain_under_1b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch2_out_remain_under_2b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch2_out_remain_under_3b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_outfifo_status_ch2_out_remain_under_4b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_outfifo_status_ch2;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_conf0_ch_s_out_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_conf0_ch_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_conf0_ch_s_out_loop_test> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_conf0_ch_s;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_conf0_ch_s_out_auto_wrback> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_conf0_ch_s;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_conf0_ch_s_out_eof_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_conf0_ch_s;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_conf0_ch_s_outdscr_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_conf0_ch_s;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_conf0_ch_s_out_data_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_conf0_ch_s;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_conf1_ch_s_out_check_owner> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_conf1_ch_s;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_dscr_bf0_ch0_outlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_dscr_bf0_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_dscr_bf0_ch1_outlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_dscr_bf0_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_dscr_bf0_ch2_outlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_dscr_bf0_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_dscr_bf1_ch0_outlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_dscr_bf1_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_dscr_bf1_ch1_outlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_dscr_bf1_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_dscr_bf1_ch2_outlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_dscr_bf1_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_dscr_ch0_outlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_dscr_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_dscr_ch1_outlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_dscr_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_dscr_ch2_outlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_dscr_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_eof_bfr_des_addr_ch0_out_eof_bfr_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_eof_bfr_des_addr_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_eof_bfr_des_addr_ch1_out_eof_bfr_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_eof_bfr_des_addr_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_eof_bfr_des_addr_ch2_out_eof_bfr_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_eof_bfr_des_addr_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_eof_des_addr_ch_s_out_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_eof_des_addr_ch_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_link_ch_s_outlink_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_link_ch_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_link_ch_s_outlink_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_link_ch_s;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_link_ch_s_outlink_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_link_ch_s;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_link_ch_s_outlink_restart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_link_ch_s;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_link_ch_s_outlink_park> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_link_ch_s;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_peri_sel_ch_s_peri_out_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_peri_sel_ch_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_pri_ch_s_tx_pri> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_pri_ch_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_push_ch0_outfifo_wdata> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_push_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_push_ch0_outfifo_push> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_push_ch0;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_push_ch1_outfifo_wdata> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_push_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_push_ch1_outfifo_push> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_push_ch1;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_push_ch2_outfifo_wdata> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_push_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_push_ch2_outfifo_push> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_push_ch2;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_state_ch0_outlink_dscr_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_state_ch0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 18u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_state_ch0_out_dscr_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_state_ch0;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_state_ch0_out_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_state_ch0;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_state_ch1_outlink_dscr_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_state_ch1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 18u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_state_ch1_out_dscr_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_state_ch1;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_state_ch1_out_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_state_ch1;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_state_ch2_outlink_dscr_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_state_ch2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 18u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_state_ch2_out_dscr_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_state_ch2;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_dma_out_state_ch2_out_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dma_out_state_ch2;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_bt_select_bt_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_bt_select;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_clock_gate_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_clock_gate;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_cpusdio_int_sdio_int> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_cpusdio_int;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 26u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_enable_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_enable;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 26u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_enable_w1tc_enable_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_enable_w1tc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 26u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_enable_w1ts_enable_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_enable_w1ts;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 26u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_func_s_in_sel_cfg_in_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_func_s_in_sel_cfg;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_func_s_in_sel_cfg_in_inv_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_func_s_in_sel_cfg;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_func_s_in_sel_cfg_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_func_s_in_sel_cfg;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_func_s_out_sel_cfg_out_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_func_s_out_sel_cfg;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_func_s_out_sel_cfg_inv_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_func_s_out_sel_cfg;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_func_s_out_sel_cfg_oen_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_func_s_out_sel_cfg;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_func_s_out_sel_cfg_oen_inv_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_func_s_out_sel_cfg;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_in_data_next> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_in;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 26u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_out_data_orig> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_out;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 26u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_out_w1tc_out_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_out_w1tc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 26u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_out_w1ts_out_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_out_w1ts;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 26u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_pcpu_int_procpu_int> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_pcpu_int;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 26u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_pcpu_nmi_int_procpu_nmi_int> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_pcpu_nmi_int;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 26u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_pin_s_sync2_bypass> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_pin_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_pin_s_pad_driver> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_pin_s;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_pin_s_sync1_bypass> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_pin_s;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_pin_s_int_type> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_pin_s;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_pin_s_wakeup_enable> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_pin_s;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_pin_s_config> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_pin_s;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_pin_s_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_pin_s;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_reg_date_reg_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_reg_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_sdio_select_sdio_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_sdio_select;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_status_interrupt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 26u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_status_next_status_interrupt_next> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_status_next;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 26u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_status_w1tc_status_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_status_w1tc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 26u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_status_w1ts_status_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_status_w1ts;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 26u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_strap_strapping> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_strap;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_clk_conf_sclk_div_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_clk_conf_sclk_div_a> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_clk_conf_sclk_div_b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_clk_conf_sclk_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_clk_conf_sclk_active> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_comd_s_command> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_comd_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 14u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_comd_s_command_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_comd_s;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_sda_force_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_scl_force_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_sample_scl_level> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_rx_full_ack_level> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_ms_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_trans_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_tx_lsb_first> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_rx_lsb_first> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_arbitration_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_fsm_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_conf_upgate> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_slv_tx_auto_start_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_addr_10bit_rw_check_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_ctr_addr_broadcasting_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_ctr;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_data_fifo_rdata> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_data;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_date_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_conf_rxfifo_wm_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_conf_txfifo_wm_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_conf_nonfifo_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_conf_fifo_addr_cfg_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_conf_rx_fifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_conf_tx_fifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_conf_fifo_prt_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_st_rxfifo_raddr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_st;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_st_rxfifo_waddr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_st;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_st_txfifo_raddr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_st;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_st_txfifo_waddr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_st;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_st_slave_rw_point> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_st;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_filter_cfg_scl_filter_thres> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_filter_cfg;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_filter_cfg_sda_filter_thres> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_filter_cfg;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_filter_cfg_scl_filter_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_filter_cfg;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_filter_cfg_sda_filter_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_filter_cfg;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_rxfifo_wm_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_txfifo_wm_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_rxfifo_ovf_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_end_detect_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_byte_trans_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_arbitration_lost_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_mst_txfifo_udf_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_trans_complete_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_time_out_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_trans_start_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_nack_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_txfifo_ovf_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_rxfifo_udf_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_scl_st_to_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_scl_main_st_to_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_det_start_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_slave_stretch_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_general_call_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_rxfifo_wm_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_txfifo_wm_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_rxfifo_ovf_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_end_detect_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_byte_trans_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_arbitration_lost_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_mst_txfifo_udf_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_trans_complete_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_time_out_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_trans_start_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_nack_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_txfifo_ovf_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_rxfifo_udf_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_scl_st_to_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_scl_main_st_to_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_det_start_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_slave_stretch_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_general_call_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_rxfifo_wm_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_txfifo_wm_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_rxfifo_ovf_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_end_detect_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_byte_trans_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_arbitration_lost_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_mst_txfifo_udf_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_trans_complete_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_time_out_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_trans_start_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_nack_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_txfifo_ovf_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_rxfifo_udf_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_scl_st_to_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_scl_main_st_to_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_det_start_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_slave_stretch_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_general_call_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_rxfifo_wm_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_txfifo_wm_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_rxfifo_ovf_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_end_detect_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_byte_trans_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_arbitration_lost_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_mst_txfifo_udf_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_trans_complete_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_time_out_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_trans_start_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_nack_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_txfifo_ovf_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_rxfifo_udf_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_scl_st_to_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_scl_main_st_to_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_det_start_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_slave_stretch_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_general_call_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_rxfifo_start_addr_rxfifo_start_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_rxfifo_start_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_high_period_scl_high_period> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_high_period;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_high_period_scl_wait_high_period> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_high_period;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_low_period_scl_low_period> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_low_period;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_main_st_time_out_scl_main_st_to_i2c> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_main_st_time_out;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_rstart_setup_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_rstart_setup;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_sp_conf_scl_rst_slv_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_sp_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_sp_conf_scl_rst_slv_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_sp_conf;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_sp_conf_scl_pd_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_sp_conf;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_sp_conf_sda_pd_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_sp_conf;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_start_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_start_hold;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_stop_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_stop_hold;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_stop_setup_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_stop_setup;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_stretch_conf_stretch_protect_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_stretch_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_stretch_conf_slave_scl_stretch_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_stretch_conf;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_stretch_conf_slave_scl_stretch_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_stretch_conf;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_stretch_conf_slave_byte_ack_ctl_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_stretch_conf;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_stretch_conf_slave_byte_ack_lvl> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_stretch_conf;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_st_time_out_scl_st_to_i2c> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_st_time_out;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sda_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sda_hold;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sda_sample_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sda_sample;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_slave_addr_slave_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_slave_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 15u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_slave_addr_addr_10bit_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_slave_addr;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sr_resp_rec> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sr_slave_rw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sr_arb_lost> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sr_bus_busy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sr_slave_addressed> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sr;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sr_rxfifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sr_stretch_cause> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sr;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sr_txfifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sr;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sr_scl_main_state_last> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sr;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sr_scl_state_last> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sr;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_to_time_out_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_to;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_to_time_out_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_to;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_txfifo_start_addr_txfifo_start_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_txfifo_start_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_pcr_i2c0_conf_reg_i2c0_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_pcr_i2c0_conf_reg;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_pcr_spi2_conf_reg_spi2_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_pcr_spi2_conf_reg;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_pcr_uart0_conf0_reg_uart0_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_pcr_uart0_conf0_reg;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_pcr_uart1_conf0_reg_uart1_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_pcr_uart1_conf0_reg;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_fctrl_cache_req_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_fctrl_cache_usr_addr_4byte> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_fctrl_cache_flash_usr_cmd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_fctrl_fdin_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_fctrl_fdout_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_fctrl_faddr_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_fctrl_fdin_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_fctrl_fdout_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_fctrl_faddr_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_clock_clkcnt_l> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_clock;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_clock_clkcnt_h> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_clock;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_clock_clkcnt_n> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_clock;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_clock_clk_equ_sysclk> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_clock;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_clock_gate_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_clock_gate;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_core_clk_sel_spi01_clk_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_core_clk_sel;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_fdummy_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_fcmd_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_fcmd_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_fastrd_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_fread_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_q_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_d_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_fread_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_wp> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_fread_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_fread_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl1_clk_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl1_rxfifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl1;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl2_cs_setup_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl2_cs_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl2;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl2_cs_hold_delay> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl2;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl2_sync_reset> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl2;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_date_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_din_mode_din0_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_din_mode;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_din_mode_din1_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_din_mode;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_din_mode_din2_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_din_mode;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_din_mode_din3_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_din_mode;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_din_num_din0_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_din_num;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_din_num_din1_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_din_num;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_din_num_din2_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_din_num;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_din_num_din3_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_din_num;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dout_mode_dout0_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dout_mode;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dout_mode_dout1_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dout_mode;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dout_mode_dout2_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dout_mode;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dout_mode_dout3_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dout_mode;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_fsm_cspi_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_fsm;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_fsm_em_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_fsm;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_fsm_cspi_lock_delay_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_fsm;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_misc_trans_end> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_misc;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_misc_trans_end_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_misc;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_misc_cspi_st_trans_end> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_misc;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_misc_cspi_st_trans_end_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_misc;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_misc_ck_idle_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_misc;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_misc_cs_keep_active> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_misc;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_rd_status_wb_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_rd_status;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_timing_cali_timing_clk_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_timing_cali;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_timing_cali_timing_cali> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_timing_cali;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_timing_cali_extra_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_timing_cali;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_cs_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_cs_setup> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_ck_out_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_dummy_idle> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_dummy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user1_usr_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user1_usr_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user2_usr_command_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user2_usr_command_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user2;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_addr_usr_addr_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_fctrl_cache_usr_addr_4byte> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_fctrl_fdin_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_fctrl_fdout_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_fctrl_faddr_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_fctrl_fdin_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_fctrl_fdout_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_fctrl_faddr_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_clock_clkcnt_l> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_clock;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_clock_clkcnt_h> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_clock;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_clock_clkcnt_n> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_clock;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_clock_clk_equ_sysclk> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_clock;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_clock_gate_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_clock_gate;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_spi1_mst_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_mspi_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_pe> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_usr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_hpm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_res> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_dp> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_ce> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_be> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_se> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_pp> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_wrsr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_rdsr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_rdid> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_wrdi> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_wren> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_read> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_fdummy_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_fcmd_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_fcmd_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_fcs_crc_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_tx_crc_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_fastrd_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_fread_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_resandres> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_q_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_d_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_fread_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_wp> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_wrsr_2b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_fread_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_fread_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl1_clk_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl1_cs_hold_dly_res> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl1;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl2_sync_reset> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl2;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_date_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_sus_cmd_flash_per_command> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_sus_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_sus_cmd_flash_pes_command> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_sus_cmd;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_sus_cmd_wait_pesr_command> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_sus_cmd;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_sus_ctrl_flash_per> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_sus_ctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_sus_ctrl_flash_pes> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_sus_ctrl;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_sus_ctrl_flash_per_wait_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_sus_ctrl;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_sus_ctrl_flash_pes_wait_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_sus_ctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_sus_ctrl_pes_per_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_sus_ctrl;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_sus_ctrl_flash_pes_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_sus_ctrl;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_sus_ctrl_pesr_end_msk> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_sus_ctrl;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_sus_ctrl_rd_sus_2b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_sus_ctrl;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_sus_ctrl_per_end_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_sus_ctrl;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_sus_ctrl_pes_end_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_sus_ctrl;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_sus_ctrl_sus_timeout_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_sus_ctrl;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_waiti_ctrl_waiti_dummy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_waiti_ctrl;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_waiti_ctrl_waiti_cmd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_waiti_ctrl;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_flash_waiti_ctrl_waiti_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_flash_waiti_ctrl;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_clr_per_end_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_clr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_clr_pes_end_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_clr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_clr_wpe_end_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_clr;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_clr_slv_st_end_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_clr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_clr_mst_st_end_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_clr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_ena_per_end_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_ena;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_ena_pes_end_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_ena;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_ena_wpe_end_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_ena;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_ena_slv_st_end_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_ena;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_ena_mst_st_end_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_ena;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_raw_per_end_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_raw;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_raw_pes_end_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_raw;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_raw_wpe_end_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_raw;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_raw_slv_st_end_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_raw;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_raw_mst_st_end_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_raw;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_st_per_end_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_st;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_st_pes_end_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_st;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_st_wpe_end_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_st;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_st_slv_st_end_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_st;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_int_st_mst_st_end_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_int_st;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_misc_cs0_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_misc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_misc_cs1_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_misc;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_misc_ck_idle_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_misc;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_misc_cs_keep_active> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_misc;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_miso_dlen_usr_miso_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_miso_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_mosi_dlen_usr_mosi_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_mosi_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_rd_status_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_rd_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_rd_status_wb_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_rd_status;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sus_status_flash_sus> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sus_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sus_status_wait_pesr_cmd_2b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sus_status;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sus_status_flash_hpm_dly_128> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sus_status;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sus_status_flash_res_dly_128> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sus_status;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sus_status_flash_dp_dly_128> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sus_status;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sus_status_flash_per_dly_128> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sus_status;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sus_status_flash_pes_dly_128> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sus_status;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sus_status_spi0_lock_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sus_status;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_timing_cali_timing_cali> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_timing_cali;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_timing_cali_extra_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_timing_cali;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_tx_crc_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_tx_crc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_ck_out_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_fwrite_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_fwrite_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_fwrite_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_fwrite_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_miso_highpart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_mosi_highpart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_dummy_idle> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_mosi> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_miso> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_dummy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_command> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user1_usr_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user1_usr_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user2_usr_command_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user2_usr_command_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user2;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w0_buf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w1_buf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w10_buf10> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w10;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w11_buf11> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w11;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w12_buf12> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w12;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w13_buf13> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w13;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w14_buf14> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w14;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w15_buf15> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w15;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w2_buf2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w3_buf3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w4_buf4> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w4;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w5_buf5> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w5;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w6_buf6> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w6;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w7_buf7> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w7;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w8_buf8> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w8;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_w9_buf9> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_w9;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_addr_usr_addr_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_clk_gate_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_clk_gate;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_clk_gate_mst_clk_active> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_clk_gate;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_clk_gate_mst_clk_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_clk_gate;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_clock_clkcnt_l> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_clock;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_clock_clkcnt_h> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_clock;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_clock_clkcnt_n> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_clock;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_clock_clkdiv_pre> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_clock;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_clock_clk_equ_sysclk> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_clock;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_conf_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 18u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_update> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_usr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_dummy_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_faddr_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_faddr_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_fcmd_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_fcmd_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_fread_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_fread_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_q_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_d_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_hold_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_wp_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_rd_bit_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_wr_bit_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_date_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_din_mode_din0_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_din_mode;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_din_mode_din1_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_din_mode;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_din_mode_din2_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_din_mode;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_din_mode_din3_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_din_mode;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_din_mode_timing_hclk_active> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_din_mode;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_din_num_din0_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_din_num;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_din_num_din1_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_din_num;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_din_num_din2_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_din_num;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_din_num_din3_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_din_num;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_dma_slv_seg_trans_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_slv_rx_seg_trans_clr_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_slv_tx_seg_trans_clr_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_rx_eof_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_dma_rx_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_dma_tx_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_rx_afifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_buf_afifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_dma_afifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_dma_infifo_full_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_dma_outfifo_empty_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_slv_ex_qpi_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_slv_en_qpi_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_slv_cmd7_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_slv_cmd8_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_slv_cmd9_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_slv_cmda_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_slv_rd_dma_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_slv_wr_dma_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_slv_rd_buf_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_slv_wr_buf_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_trans_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_dma_seg_trans_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_seg_magic_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_slv_buf_addr_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_slv_cmd_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_mst_rx_afifo_wfull_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_mst_tx_afifo_rempty_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_app2_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_app1_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_dma_infifo_full_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_dma_outfifo_empty_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_slv_ex_qpi_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_slv_en_qpi_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_slv_cmd7_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_slv_cmd8_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_slv_cmd9_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_slv_cmda_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_slv_rd_dma_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_slv_wr_dma_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_slv_rd_buf_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_slv_wr_buf_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_trans_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_dma_seg_trans_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_seg_magic_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_slv_buf_addr_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_slv_cmd_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_mst_rx_afifo_wfull_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_mst_tx_afifo_rempty_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_app2_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_app1_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_dma_infifo_full_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_dma_outfifo_empty_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_slv_ex_qpi_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_slv_en_qpi_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_slv_cmd7_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_slv_cmd8_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_slv_cmd9_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_slv_cmda_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_slv_rd_dma_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_slv_wr_dma_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_slv_rd_buf_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_slv_wr_buf_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_trans_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_dma_seg_trans_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_seg_magic_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_slv_buf_addr_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_slv_cmd_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_mst_rx_afifo_wfull_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_mst_tx_afifo_rempty_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_app2_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_app1_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_dma_infifo_full_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_dma_outfifo_empty_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_slv_ex_qpi_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_slv_en_qpi_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_slv_cmd7_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_slv_cmd8_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_slv_cmd9_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_slv_cmda_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_slv_rd_dma_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_slv_wr_dma_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_slv_rd_buf_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_slv_wr_buf_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_trans_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_dma_seg_trans_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_seg_magic_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_slv_buf_addr_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_slv_cmd_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_mst_rx_afifo_wfull_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_mst_tx_afifo_rempty_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_app2_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_app1_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dout_mode_dout0_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dout_mode;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dout_mode_dout1_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dout_mode;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dout_mode_dout2_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dout_mode;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dout_mode_dout3_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dout_mode;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_misc_cs0_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_misc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_misc_cs1_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_misc;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_misc_cs2_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_misc;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_misc_cs3_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_misc;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_misc_cs4_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_misc;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_misc_cs5_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_misc;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_misc_ck_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_misc;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_misc_master_cs_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_misc;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_misc_slave_cs_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_misc;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_misc_ck_idle_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_misc;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_misc_cs_keep_active> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_misc;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_misc_quad_din_pin_swap> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_misc;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ms_dlen_ms_data_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ms_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 18u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_clk_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_clk_mode_13> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_rsck_data_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_slv_rddma_bitlen_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_slv_wrdma_bitlen_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_slv_rdbuf_bitlen_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_slv_wrbuf_bitlen_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_dma_seg_magic_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_soft_reset> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_usr_conf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave1_slv_data_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 18u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave1_slv_last_command> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave1;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave1_slv_last_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_doutdin> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_qpi_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_tsck_i_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_cs_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_cs_setup> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_rsck_i_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_ck_out_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_fwrite_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_fwrite_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_conf_nxt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_sio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_miso_highpart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_mosi_highpart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_dummy_idle> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_mosi> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_miso> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_dummy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_command> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user1_usr_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user1_mst_wfull_err_end_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user1_cs_setup_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user1;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user1_cs_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user1;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user1_usr_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user1;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user2_usr_command_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user2_mst_rempty_err_end_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user2;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user2_usr_command_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user2;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w0_buf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w1_buf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w10_buf10> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w10;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w11_buf11> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w11;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w12_buf12> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w12;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w13_buf13> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w13;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w14_buf14> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w14;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w15_buf15> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w15;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w2_buf2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w3_buf3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w4_buf4> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w4;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w5_buf5> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w5;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w6_buf6> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w6;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w7_buf7> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w7;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w8_buf8> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w8;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_w9_buf9> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_w9;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_at_cmd_char_at_cmd_char> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_at_cmd_char;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_at_cmd_char_char_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_at_cmd_char;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_at_cmd_gaptout_rx_gap_tout> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_at_cmd_gaptout;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_at_cmd_postcnt_post_idle_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_at_cmd_postcnt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_at_cmd_precnt_pre_idle_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_at_cmd_precnt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_clkdiv_clkdiv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_clkdiv;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_clkdiv_frag> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_clkdiv;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_clk_conf_sclk_div_b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_clk_conf_sclk_div_a> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_clk_conf_sclk_div_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_clk_conf_sclk_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_clk_conf_sclk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_clk_conf_rst_core> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_clk_conf_tx_sclk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_clk_conf_rx_sclk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_clk_conf_tx_rst_core> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_clk_conf_rx_rst_core> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_clk_conf;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_parity> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_parity_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_bit_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_stop_bit_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_sw_rts> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_sw_dtr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_txd_brk> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_irda_dplx> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_irda_tx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_irda_wctl> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_irda_tx_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_irda_rx_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_loopback> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_tx_flow_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_irda_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_rxfifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_txfifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_rxd_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_cts_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_dsr_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_txd_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_rts_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_dtr_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_err_wr_mask> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_autobaud_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf0_mem_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf1_rxfifo_full_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf1_txfifo_empty_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf1;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf1_dis_rx_dat_ovf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf1;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf1_rx_tout_flow_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf1;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf1_rx_flow_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf1;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf1_rx_tout_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf1;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_date_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_fifo_rxfifo_rd_byte> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_fifo;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_flow_conf_sw_flow_con_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_flow_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_flow_conf_xonoff_del> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_flow_conf;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_flow_conf_force_xon> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_flow_conf;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_flow_conf_force_xoff> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_flow_conf;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_flow_conf_send_xon> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_flow_conf;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_flow_conf_send_xoff> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_flow_conf;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_fsm_status_st_urx_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_fsm_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_fsm_status_st_utx_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_fsm_status;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_highpulse_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_highpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_id_id> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_id;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 30u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_id_high_speed> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_id;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_id_reg_update> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_id;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_idle_conf_rx_idle_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_idle_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_idle_conf_tx_idle_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_idle_conf;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_rxfifo_full_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_txfifo_empty_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_parity_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_frm_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_rxfifo_ovf_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_dsr_chg_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_cts_chg_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_brk_det_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_rxfifo_tout_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_sw_xon_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_sw_xoff_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_glitch_det_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_tx_brk_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_tx_brk_idle_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_tx_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_rs485_parity_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_rs485_frm_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_rs485_clash_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_at_cmd_char_det_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_clr_wakeup_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_clr;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_rxfifo_full_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_txfifo_empty_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_parity_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_frm_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_rxfifo_ovf_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_dsr_chg_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_cts_chg_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_brk_det_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_rxfifo_tout_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_sw_xon_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_sw_xoff_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_glitch_det_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_tx_brk_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_tx_brk_idle_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_tx_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_rs485_parity_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_rs485_frm_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_rs485_clash_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_at_cmd_char_det_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_ena_wakeup_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_ena;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_rxfifo_full_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_txfifo_empty_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_parity_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_frm_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_rxfifo_ovf_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_dsr_chg_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_cts_chg_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_brk_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_rxfifo_tout_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_sw_xon_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_sw_xoff_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_glitch_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_tx_brk_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_tx_brk_idle_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_tx_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_rs485_parity_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_rs485_frm_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_rs485_clash_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_at_cmd_char_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_wakeup_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_rxfifo_full_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_txfifo_empty_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_parity_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_frm_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_rxfifo_ovf_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_dsr_chg_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_cts_chg_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_brk_det_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_rxfifo_tout_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_sw_xon_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_sw_xoff_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_glitch_det_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_tx_brk_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_tx_brk_idle_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_tx_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_rs485_parity_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_rs485_frm_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_rs485_clash_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_at_cmd_char_det_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_st_wakeup_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_st;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_lowpulse_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_lowpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_rx_size> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_tx_size> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_rx_flow_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_rx_tout_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_mem_force_pd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_mem_force_pu> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_rx_status_apb_rx_raddr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_rx_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_rx_status_rx_waddr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_rx_status;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_tx_status_apb_tx_waddr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_tx_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_tx_status_tx_raddr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_tx_status;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_negpulse_negedge_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_negpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_pospulse_posedge_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_pospulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_rs485_conf_rs485_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_rs485_conf_dl0_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_rs485_conf_dl1_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_rs485_conf_rs485tx_rx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_rs485_conf_rs485rxby_tx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_rs485_conf_rs485_rx_dly_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_rs485_conf_rs485_tx_dly_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_rxd_cnt_rxd_edge_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_rxd_cnt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_rx_filt_glitch_filt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_rx_filt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_rx_filt_glitch_filt_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_rx_filt;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_sleep_conf_active_threshold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_sleep_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_status_rxfifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_status_dsrn> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_status;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_status_ctsn> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_status;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_status_rxd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_status;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_status_txfifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_status;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_status_dtrn> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_status;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_status_rtsn> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_status;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_status_txd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_status;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_swfc_conf0_xoff_threshold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_swfc_conf0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_swfc_conf0_xoff_char> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_swfc_conf0;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_swfc_conf1_xon_threshold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_swfc_conf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_swfc_conf1_xon_char> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_swfc_conf1;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_txbrk_conf_tx_brk_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_txbrk_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_at_cmd_char_at_cmd_char> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_at_cmd_char;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_at_cmd_char_char_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_at_cmd_char;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_at_cmd_gaptout_rx_gap_tout> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_at_cmd_gaptout;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_at_cmd_postcnt_post_idle_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_at_cmd_postcnt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_at_cmd_precnt_pre_idle_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_at_cmd_precnt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_clkdiv_clkdiv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_clkdiv;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_clkdiv_frag> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_clkdiv;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_clk_conf_sclk_div_b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_clk_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_clk_conf_sclk_div_a> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_clk_conf;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_clk_conf_sclk_div_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_clk_conf;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_clk_conf_sclk_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_clk_conf;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_clk_conf_sclk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_clk_conf;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_clk_conf_rst_core> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_clk_conf;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_clk_conf_tx_sclk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_clk_conf;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_clk_conf_rx_sclk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_clk_conf;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_clk_conf_tx_rst_core> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_clk_conf;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_clk_conf_rx_rst_core> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_clk_conf;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_parity> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_parity_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_bit_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_stop_bit_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_sw_rts> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_sw_dtr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_txd_brk> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_irda_dplx> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_irda_tx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_irda_wctl> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_irda_tx_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_irda_rx_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_loopback> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_tx_flow_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_irda_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_rxfifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_txfifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_rxd_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_cts_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_dsr_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_txd_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_rts_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_dtr_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_err_wr_mask> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_autobaud_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf0_mem_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf1_rxfifo_full_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf1_txfifo_empty_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf1;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf1_dis_rx_dat_ovf> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf1;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf1_rx_tout_flow_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf1;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf1_rx_flow_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf1;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf1_rx_tout_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf1;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_date_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_fifo_rxfifo_rd_byte> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_fifo;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_flow_conf_sw_flow_con_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_flow_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_flow_conf_xonoff_del> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_flow_conf;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_flow_conf_force_xon> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_flow_conf;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_flow_conf_force_xoff> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_flow_conf;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_flow_conf_send_xon> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_flow_conf;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_flow_conf_send_xoff> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_flow_conf;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_fsm_status_st_urx_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_fsm_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_fsm_status_st_utx_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_fsm_status;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_highpulse_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_highpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_id_id> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_id;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 30u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_id_high_speed> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_id;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_id_reg_update> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_id;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_idle_conf_rx_idle_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_idle_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_idle_conf_tx_idle_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_idle_conf;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_rxfifo_full_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_txfifo_empty_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_parity_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_frm_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_rxfifo_ovf_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_dsr_chg_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_cts_chg_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_brk_det_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_rxfifo_tout_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_sw_xon_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_sw_xoff_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_glitch_det_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_tx_brk_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_tx_brk_idle_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_tx_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_rs485_parity_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_rs485_frm_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_rs485_clash_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_at_cmd_char_det_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_clr_wakeup_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_clr;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_rxfifo_full_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_txfifo_empty_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_parity_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_frm_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_rxfifo_ovf_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_dsr_chg_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_cts_chg_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_brk_det_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_rxfifo_tout_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_sw_xon_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_sw_xoff_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_glitch_det_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_tx_brk_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_tx_brk_idle_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_tx_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_rs485_parity_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_rs485_frm_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_rs485_clash_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_at_cmd_char_det_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_ena_wakeup_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_ena;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_rxfifo_full_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_txfifo_empty_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_parity_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_frm_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_rxfifo_ovf_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_dsr_chg_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_cts_chg_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_brk_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_rxfifo_tout_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_sw_xon_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_sw_xoff_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_glitch_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_tx_brk_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_tx_brk_idle_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_tx_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_rs485_parity_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_rs485_frm_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_rs485_clash_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_at_cmd_char_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_wakeup_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_rxfifo_full_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_txfifo_empty_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_parity_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_frm_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_rxfifo_ovf_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_dsr_chg_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_cts_chg_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_brk_det_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_rxfifo_tout_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_sw_xon_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_sw_xoff_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_glitch_det_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_tx_brk_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_tx_brk_idle_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_tx_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_rs485_parity_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_rs485_frm_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_rs485_clash_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_at_cmd_char_det_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_st_wakeup_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_st;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_lowpulse_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_lowpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_rx_size> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_tx_size> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_rx_flow_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_rx_tout_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_mem_force_pd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_mem_force_pu> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_rx_status_apb_rx_raddr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_rx_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_rx_status_rx_waddr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_rx_status;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_tx_status_apb_tx_waddr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_tx_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_tx_status_tx_raddr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_tx_status;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_negpulse_negedge_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_negpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_pospulse_posedge_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_pospulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_rs485_conf_rs485_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_rs485_conf_dl0_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_rs485_conf_dl1_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_rs485_conf_rs485tx_rx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_rs485_conf_rs485rxby_tx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_rs485_conf_rs485_rx_dly_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_rs485_conf_rs485_tx_dly_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_rxd_cnt_rxd_edge_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_rxd_cnt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_rx_filt_glitch_filt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_rx_filt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_rx_filt_glitch_filt_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_rx_filt;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_sleep_conf_active_threshold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_sleep_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_status_rxfifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_status_dsrn> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_status;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_status_ctsn> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_status;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_status_rxd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_status;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_status_txfifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_status;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_status_dtrn> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_status;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_status_rtsn> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_status;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_status_txd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_status;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_swfc_conf0_xoff_threshold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_swfc_conf0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_swfc_conf0_xoff_char> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_swfc_conf0;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_swfc_conf1_xon_threshold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_swfc_conf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_swfc_conf1_xon_char> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_swfc_conf1;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_txbrk_conf_tx_brk_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_txbrk_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

inline constexpr std::array<FieldId, 1265> kRegisterFields = {{
  FieldId::field_apb_saradc_apb_tsens_ctrl_tsens_out,
  FieldId::field_apb_saradc_apb_tsens_ctrl_tsens_in_inv,
  FieldId::field_apb_saradc_apb_tsens_ctrl_tsens_clk_div,
  FieldId::field_apb_saradc_apb_tsens_ctrl_tsens_pu,
  FieldId::field_apb_saradc_arb_ctrl_adc_arb_apb_force,
  FieldId::field_apb_saradc_arb_ctrl_adc_arb_rtc_force,
  FieldId::field_apb_saradc_arb_ctrl_adc_arb_wifi_force,
  FieldId::field_apb_saradc_arb_ctrl_adc_arb_grant_force,
  FieldId::field_apb_saradc_arb_ctrl_adc_arb_apb_priority,
  FieldId::field_apb_saradc_arb_ctrl_adc_arb_rtc_priority,
  FieldId::field_apb_saradc_arb_ctrl_adc_arb_wifi_priority,
  FieldId::field_apb_saradc_arb_ctrl_adc_arb_fix_priority,
  FieldId::field_apb_saradc_cali_apb_saradc_cali_cfg,
  FieldId::field_apb_saradc_clkm_conf_clkm_div_num,
  FieldId::field_apb_saradc_clkm_conf_clkm_div_b,
  FieldId::field_apb_saradc_clkm_conf_clkm_div_a,
  FieldId::field_apb_saradc_clkm_conf_clk_en,
  FieldId::field_apb_saradc_clkm_conf_clk_sel,
  FieldId::field_apb_saradc_ctrl_saradc_start_force,
  FieldId::field_apb_saradc_ctrl_saradc_start,
  FieldId::field_apb_saradc_ctrl_saradc_sar_clk_gated,
  FieldId::field_apb_saradc_ctrl_saradc_sar_clk_div,
  FieldId::field_apb_saradc_ctrl_saradc_sar_patt_len,
  FieldId::field_apb_saradc_ctrl_saradc_sar_patt_p_clear,
  FieldId::field_apb_saradc_ctrl_saradc_xpd_sar_force,
  FieldId::field_apb_saradc_ctrl_saradc_wait_arb_cycle,
  FieldId::field_apb_saradc_ctrl2_saradc_meas_num_limit,
  FieldId::field_apb_saradc_ctrl2_saradc_max_meas_num,
  FieldId::field_apb_saradc_ctrl2_saradc_sar1_inv,
  FieldId::field_apb_saradc_ctrl2_saradc_sar2_inv,
  FieldId::field_apb_saradc_ctrl2_saradc_timer_target,
  FieldId::field_apb_saradc_ctrl2_saradc_timer_en,
  FieldId::field_apb_saradc_ctrl_date_date,
  FieldId::field_apb_saradc_dma_conf_apb_adc_eof_num,
  FieldId::field_apb_saradc_dma_conf_apb_adc_reset_fsm,
  FieldId::field_apb_saradc_dma_conf_apb_adc_trans,
  FieldId::field_apb_saradc_filter_ctrl0_apb_saradc_filter_channel1,
  FieldId::field_apb_saradc_filter_ctrl0_apb_saradc_filter_channel0,
  FieldId::field_apb_saradc_filter_ctrl0_apb_saradc_filter_reset,
  FieldId::field_apb_saradc_filter_ctrl1_apb_saradc_filter_factor1,
  FieldId::field_apb_saradc_filter_ctrl1_apb_saradc_filter_factor0,
  FieldId::field_apb_saradc_fsm_wait_saradc_xpd_wait,
  FieldId::field_apb_saradc_fsm_wait_saradc_rstb_wait,
  FieldId::field_apb_saradc_fsm_wait_saradc_standby_wait,
  FieldId::field_apb_saradc_int_clr_apb_saradc_thres1_low_int_clr,
  FieldId::field_apb_saradc_int_clr_apb_saradc_thres0_low_int_clr,
  FieldId::field_apb_saradc_int_clr_apb_saradc_thres1_high_int_clr,
  FieldId::field_apb_saradc_int_clr_apb_saradc_thres0_high_int_clr,
  FieldId::field_apb_saradc_int_clr_apb_saradc2_done_int_clr,
  FieldId::field_apb_saradc_int_clr_apb_saradc1_done_int_clr,
  FieldId::field_apb_saradc_int_ena_apb_saradc_thres1_low_int_ena,
  FieldId::field_apb_saradc_int_ena_apb_saradc_thres0_low_int_ena,
  FieldId::field_apb_saradc_int_ena_apb_saradc_thres1_high_int_ena,
  FieldId::field_apb_saradc_int_ena_apb_saradc_thres0_high_int_ena,
  FieldId::field_apb_saradc_int_ena_apb_saradc2_done_int_ena,
  FieldId::field_apb_saradc_int_ena_apb_saradc1_done_int_ena,
  FieldId::field_apb_saradc_int_raw_apb_saradc_thres1_low_int_raw,
  FieldId::field_apb_saradc_int_raw_apb_saradc_thres0_low_int_raw,
  FieldId::field_apb_saradc_int_raw_apb_saradc_thres1_high_int_raw,
  FieldId::field_apb_saradc_int_raw_apb_saradc_thres0_high_int_raw,
  FieldId::field_apb_saradc_int_raw_apb_saradc2_done_int_raw,
  FieldId::field_apb_saradc_int_raw_apb_saradc1_done_int_raw,
  FieldId::field_apb_saradc_int_st_apb_saradc_thres1_low_int_st,
  FieldId::field_apb_saradc_int_st_apb_saradc_thres0_low_int_st,
  FieldId::field_apb_saradc_int_st_apb_saradc_thres1_high_int_st,
  FieldId::field_apb_saradc_int_st_apb_saradc_thres0_high_int_st,
  FieldId::field_apb_saradc_int_st_apb_saradc2_done_int_st,
  FieldId::field_apb_saradc_int_st_apb_saradc1_done_int_st,
  FieldId::field_apb_saradc_onetime_sample_saradc_onetime_atten,
  FieldId::field_apb_saradc_onetime_sample_saradc_onetime_channel,
  FieldId::field_apb_saradc_onetime_sample_saradc_onetime_start,
  FieldId::field_apb_saradc_onetime_sample_saradc2_onetime_sample,
  FieldId::field_apb_saradc_onetime_sample_saradc1_onetime_sample,
  FieldId::field_apb_saradc_sar1data_status_apb_saradc1_data,
  FieldId::field_apb_saradc_sar1_status_saradc_sar1_status,
  FieldId::field_apb_saradc_sar2data_status_apb_saradc2_data,
  FieldId::field_apb_saradc_sar2_status_saradc_sar2_status,
  FieldId::field_apb_saradc_sar_patt_tab1_saradc_sar_patt_tab1,
  FieldId::field_apb_saradc_sar_patt_tab2_saradc_sar_patt_tab2,
  FieldId::field_apb_saradc_thres0_ctrl_apb_saradc_thres0_channel,
  FieldId::field_apb_saradc_thres0_ctrl_apb_saradc_thres0_high,
  FieldId::field_apb_saradc_thres0_ctrl_apb_saradc_thres0_low,
  FieldId::field_apb_saradc_thres1_ctrl_apb_saradc_thres1_channel,
  FieldId::field_apb_saradc_thres1_ctrl_apb_saradc_thres1_high,
  FieldId::field_apb_saradc_thres1_ctrl_apb_saradc_thres1_low,
  FieldId::field_apb_saradc_thres_ctrl_apb_saradc_thres_all_en,
  FieldId::field_apb_saradc_thres_ctrl_apb_saradc_thres1_en,
  FieldId::field_apb_saradc_thres_ctrl_apb_saradc_thres0_en,
  FieldId::field_apb_saradc_tsens_ctrl2_tsens_xpd_wait,
  FieldId::field_apb_saradc_tsens_ctrl2_tsens_xpd_force,
  FieldId::field_apb_saradc_tsens_ctrl2_tsens_clk_inv,
  FieldId::field_apb_saradc_tsens_ctrl2_tsens_clk_sel,
  FieldId::field_dma_ahb_test_ahb_testmode,
  FieldId::field_dma_ahb_test_ahb_testaddr,
  FieldId::field_dma_date_date,
  FieldId::field_dma_infifo_status_ch0_infifo_full,
  FieldId::field_dma_infifo_status_ch0_infifo_empty,
  FieldId::field_dma_infifo_status_ch0_infifo_cnt,
  FieldId::field_dma_infifo_status_ch0_in_remain_under_1b,
  FieldId::field_dma_infifo_status_ch0_in_remain_under_2b,
  FieldId::field_dma_infifo_status_ch0_in_remain_under_3b,
  FieldId::field_dma_infifo_status_ch0_in_remain_under_4b,
  FieldId::field_dma_infifo_status_ch0_in_buf_hungry,
  FieldId::field_dma_infifo_status_ch1_infifo_full,
  FieldId::field_dma_infifo_status_ch1_infifo_empty,
  FieldId::field_dma_infifo_status_ch1_infifo_cnt,
  FieldId::field_dma_infifo_status_ch1_in_remain_under_1b,
  FieldId::field_dma_infifo_status_ch1_in_remain_under_2b,
  FieldId::field_dma_infifo_status_ch1_in_remain_under_3b,
  FieldId::field_dma_infifo_status_ch1_in_remain_under_4b,
  FieldId::field_dma_infifo_status_ch1_in_buf_hungry,
  FieldId::field_dma_infifo_status_ch2_infifo_full,
  FieldId::field_dma_infifo_status_ch2_infifo_empty,
  FieldId::field_dma_infifo_status_ch2_infifo_cnt,
  FieldId::field_dma_infifo_status_ch2_in_remain_under_1b,
  FieldId::field_dma_infifo_status_ch2_in_remain_under_2b,
  FieldId::field_dma_infifo_status_ch2_in_remain_under_3b,
  FieldId::field_dma_infifo_status_ch2_in_remain_under_4b,
  FieldId::field_dma_infifo_status_ch2_in_buf_hungry,
  FieldId::field_dma_int_clr_ch_s_in_done,
  FieldId::field_dma_int_clr_ch_s_in_suc_eof,
  FieldId::field_dma_int_clr_ch_s_in_err_eof,
  FieldId::field_dma_int_clr_ch_s_out_done,
  FieldId::field_dma_int_clr_ch_s_out_eof,
  FieldId::field_dma_int_clr_ch_s_in_dscr_err,
  FieldId::field_dma_int_clr_ch_s_out_dscr_err,
  FieldId::field_dma_int_clr_ch_s_in_dscr_empty,
  FieldId::field_dma_int_clr_ch_s_out_total_eof,
  FieldId::field_dma_int_clr_ch_s_infifo_ovf,
  FieldId::field_dma_int_clr_ch_s_infifo_udf,
  FieldId::field_dma_int_clr_ch_s_outfifo_ovf,
  FieldId::field_dma_int_clr_ch_s_outfifo_udf,
  FieldId::field_dma_int_ena_ch_s_in_done,
  FieldId::field_dma_int_ena_ch_s_in_suc_eof,
  FieldId::field_dma_int_ena_ch_s_in_err_eof,
  FieldId::field_dma_int_ena_ch_s_out_done,
  FieldId::field_dma_int_ena_ch_s_out_eof,
  FieldId::field_dma_int_ena_ch_s_in_dscr_err,
  FieldId::field_dma_int_ena_ch_s_out_dscr_err,
  FieldId::field_dma_int_ena_ch_s_in_dscr_empty,
  FieldId::field_dma_int_ena_ch_s_out_total_eof,
  FieldId::field_dma_int_ena_ch_s_infifo_ovf,
  FieldId::field_dma_int_ena_ch_s_infifo_udf,
  FieldId::field_dma_int_ena_ch_s_outfifo_ovf,
  FieldId::field_dma_int_ena_ch_s_outfifo_udf,
  FieldId::field_dma_int_raw_ch_s_in_done,
  FieldId::field_dma_int_raw_ch_s_in_suc_eof,
  FieldId::field_dma_int_raw_ch_s_in_err_eof,
  FieldId::field_dma_int_raw_ch_s_out_done,
  FieldId::field_dma_int_raw_ch_s_out_eof,
  FieldId::field_dma_int_raw_ch_s_in_dscr_err,
  FieldId::field_dma_int_raw_ch_s_out_dscr_err,
  FieldId::field_dma_int_raw_ch_s_in_dscr_empty,
  FieldId::field_dma_int_raw_ch_s_out_total_eof,
  FieldId::field_dma_int_raw_ch_s_infifo_ovf,
  FieldId::field_dma_int_raw_ch_s_infifo_udf,
  FieldId::field_dma_int_raw_ch_s_outfifo_ovf,
  FieldId::field_dma_int_raw_ch_s_outfifo_udf,
  FieldId::field_dma_int_st_ch0_in_done,
  FieldId::field_dma_int_st_ch0_in_suc_eof,
  FieldId::field_dma_int_st_ch0_in_err_eof,
  FieldId::field_dma_int_st_ch0_out_done,
  FieldId::field_dma_int_st_ch0_out_eof,
  FieldId::field_dma_int_st_ch0_in_dscr_err,
  FieldId::field_dma_int_st_ch0_out_dscr_err,
  FieldId::field_dma_int_st_ch0_in_dscr_empty,
  FieldId::field_dma_int_st_ch0_out_total_eof,
  FieldId::field_dma_int_st_ch0_infifo_ovf,
  FieldId::field_dma_int_st_ch0_infifo_udf,
  FieldId::field_dma_int_st_ch0_outfifo_ovf,
  FieldId::field_dma_int_st_ch0_outfifo_udf,
  FieldId::field_dma_int_st_ch1_in_done,
  FieldId::field_dma_int_st_ch1_in_suc_eof,
  FieldId::field_dma_int_st_ch1_in_err_eof,
  FieldId::field_dma_int_st_ch1_out_done,
  FieldId::field_dma_int_st_ch1_out_eof,
  FieldId::field_dma_int_st_ch1_in_dscr_err,
  FieldId::field_dma_int_st_ch1_out_dscr_err,
  FieldId::field_dma_int_st_ch1_in_dscr_empty,
  FieldId::field_dma_int_st_ch1_out_total_eof,
  FieldId::field_dma_int_st_ch1_infifo_ovf,
  FieldId::field_dma_int_st_ch1_infifo_udf,
  FieldId::field_dma_int_st_ch1_outfifo_ovf,
  FieldId::field_dma_int_st_ch1_outfifo_udf,
  FieldId::field_dma_int_st_ch2_in_done,
  FieldId::field_dma_int_st_ch2_in_suc_eof,
  FieldId::field_dma_int_st_ch2_in_err_eof,
  FieldId::field_dma_int_st_ch2_out_done,
  FieldId::field_dma_int_st_ch2_out_eof,
  FieldId::field_dma_int_st_ch2_in_dscr_err,
  FieldId::field_dma_int_st_ch2_out_dscr_err,
  FieldId::field_dma_int_st_ch2_in_dscr_empty,
  FieldId::field_dma_int_st_ch2_out_total_eof,
  FieldId::field_dma_int_st_ch2_infifo_ovf,
  FieldId::field_dma_int_st_ch2_infifo_udf,
  FieldId::field_dma_int_st_ch2_outfifo_ovf,
  FieldId::field_dma_int_st_ch2_outfifo_udf,
  FieldId::field_dma_in_conf0_ch_s_in_rst,
  FieldId::field_dma_in_conf0_ch_s_in_loop_test,
  FieldId::field_dma_in_conf0_ch_s_indscr_burst_en,
  FieldId::field_dma_in_conf0_ch_s_in_data_burst_en,
  FieldId::field_dma_in_conf0_ch_s_mem_trans_en,
  FieldId::field_dma_in_conf1_ch0_in_check_owner,
  FieldId::field_dma_in_conf1_ch1_in_check_owner,
  FieldId::field_dma_in_conf1_ch2_in_check_owner,
  FieldId::field_dma_in_dscr_bf0_ch_s_inlink_dscr_bf0,
  FieldId::field_dma_in_dscr_bf1_ch0_inlink_dscr_bf1,
  FieldId::field_dma_in_dscr_bf1_ch1_inlink_dscr_bf1,
  FieldId::field_dma_in_dscr_bf1_ch2_inlink_dscr_bf1,
  FieldId::field_dma_in_dscr_ch0_inlink_dscr,
  FieldId::field_dma_in_dscr_ch1_inlink_dscr,
  FieldId::field_dma_in_dscr_ch2_inlink_dscr,
  FieldId::field_dma_in_err_eof_des_addr_ch0_in_err_eof_des_addr,
  FieldId::field_dma_in_err_eof_des_addr_ch1_in_err_eof_des_addr,
  FieldId::field_dma_in_err_eof_des_addr_ch2_in_err_eof_des_addr,
  FieldId::field_dma_in_link_ch_s_inlink_addr,
  FieldId::field_dma_in_link_ch_s_inlink_auto_ret,
  FieldId::field_dma_in_link_ch_s_inlink_stop,
  FieldId::field_dma_in_link_ch_s_inlink_start,
  FieldId::field_dma_in_link_ch_s_inlink_restart,
  FieldId::field_dma_in_link_ch_s_inlink_park,
  FieldId::field_dma_in_peri_sel_ch_s_peri_in_sel,
  FieldId::field_dma_in_pop_ch0_infifo_rdata,
  FieldId::field_dma_in_pop_ch0_infifo_pop,
  FieldId::field_dma_in_pop_ch1_infifo_rdata,
  FieldId::field_dma_in_pop_ch1_infifo_pop,
  FieldId::field_dma_in_pop_ch2_infifo_rdata,
  FieldId::field_dma_in_pop_ch2_infifo_pop,
  FieldId::field_dma_in_pri_ch_s_rx_pri,
  FieldId::field_dma_in_state_ch0_inlink_dscr_addr,
  FieldId::field_dma_in_state_ch0_in_dscr_state,
  FieldId::field_dma_in_state_ch0_in_state,
  FieldId::field_dma_in_state_ch1_inlink_dscr_addr,
  FieldId::field_dma_in_state_ch1_in_dscr_state,
  FieldId::field_dma_in_state_ch1_in_state,
  FieldId::field_dma_in_state_ch2_inlink_dscr_addr,
  FieldId::field_dma_in_state_ch2_in_dscr_state,
  FieldId::field_dma_in_state_ch2_in_state,
  FieldId::field_dma_in_suc_eof_des_addr_ch0_in_suc_eof_des_addr,
  FieldId::field_dma_in_suc_eof_des_addr_ch1_in_suc_eof_des_addr,
  FieldId::field_dma_in_suc_eof_des_addr_ch2_in_suc_eof_des_addr,
  FieldId::field_dma_misc_conf_ahbm_rst_inter,
  FieldId::field_dma_misc_conf_arb_pri_dis,
  FieldId::field_dma_misc_conf_clk_en,
  FieldId::field_dma_outfifo_status_ch0_outfifo_full,
  FieldId::field_dma_outfifo_status_ch0_outfifo_empty,
  FieldId::field_dma_outfifo_status_ch0_outfifo_cnt,
  FieldId::field_dma_outfifo_status_ch0_out_remain_under_1b,
  FieldId::field_dma_outfifo_status_ch0_out_remain_under_2b,
  FieldId::field_dma_outfifo_status_ch0_out_remain_under_3b,
  FieldId::field_dma_outfifo_status_ch0_out_remain_under_4b,
  FieldId::field_dma_outfifo_status_ch1_outfifo_full,
  FieldId::field_dma_outfifo_status_ch1_outfifo_empty,
  FieldId::field_dma_outfifo_status_ch1_outfifo_cnt,
  FieldId::field_dma_outfifo_status_ch1_out_remain_under_1b,
  FieldId::field_dma_outfifo_status_ch1_out_remain_under_2b,
  FieldId::field_dma_outfifo_status_ch1_out_remain_under_3b,
  FieldId::field_dma_outfifo_status_ch1_out_remain_under_4b,
  FieldId::field_dma_outfifo_status_ch2_outfifo_full,
  FieldId::field_dma_outfifo_status_ch2_outfifo_empty,
  FieldId::field_dma_outfifo_status_ch2_outfifo_cnt,
  FieldId::field_dma_outfifo_status_ch2_out_remain_under_1b,
  FieldId::field_dma_outfifo_status_ch2_out_remain_under_2b,
  FieldId::field_dma_outfifo_status_ch2_out_remain_under_3b,
  FieldId::field_dma_outfifo_status_ch2_out_remain_under_4b,
  FieldId::field_dma_out_conf0_ch_s_out_rst,
  FieldId::field_dma_out_conf0_ch_s_out_loop_test,
  FieldId::field_dma_out_conf0_ch_s_out_auto_wrback,
  FieldId::field_dma_out_conf0_ch_s_out_eof_mode,
  FieldId::field_dma_out_conf0_ch_s_outdscr_burst_en,
  FieldId::field_dma_out_conf0_ch_s_out_data_burst_en,
  FieldId::field_dma_out_conf1_ch_s_out_check_owner,
  FieldId::field_dma_out_dscr_bf0_ch0_outlink_dscr_bf0,
  FieldId::field_dma_out_dscr_bf0_ch1_outlink_dscr_bf0,
  FieldId::field_dma_out_dscr_bf0_ch2_outlink_dscr_bf0,
  FieldId::field_dma_out_dscr_bf1_ch0_outlink_dscr_bf1,
  FieldId::field_dma_out_dscr_bf1_ch1_outlink_dscr_bf1,
  FieldId::field_dma_out_dscr_bf1_ch2_outlink_dscr_bf1,
  FieldId::field_dma_out_dscr_ch0_outlink_dscr,
  FieldId::field_dma_out_dscr_ch1_outlink_dscr,
  FieldId::field_dma_out_dscr_ch2_outlink_dscr,
  FieldId::field_dma_out_eof_bfr_des_addr_ch0_out_eof_bfr_des_addr,
  FieldId::field_dma_out_eof_bfr_des_addr_ch1_out_eof_bfr_des_addr,
  FieldId::field_dma_out_eof_bfr_des_addr_ch2_out_eof_bfr_des_addr,
  FieldId::field_dma_out_eof_des_addr_ch_s_out_eof_des_addr,
  FieldId::field_dma_out_link_ch_s_outlink_addr,
  FieldId::field_dma_out_link_ch_s_outlink_stop,
  FieldId::field_dma_out_link_ch_s_outlink_start,
  FieldId::field_dma_out_link_ch_s_outlink_restart,
  FieldId::field_dma_out_link_ch_s_outlink_park,
  FieldId::field_dma_out_peri_sel_ch_s_peri_out_sel,
  FieldId::field_dma_out_pri_ch_s_tx_pri,
  FieldId::field_dma_out_push_ch0_outfifo_wdata,
  FieldId::field_dma_out_push_ch0_outfifo_push,
  FieldId::field_dma_out_push_ch1_outfifo_wdata,
  FieldId::field_dma_out_push_ch1_outfifo_push,
  FieldId::field_dma_out_push_ch2_outfifo_wdata,
  FieldId::field_dma_out_push_ch2_outfifo_push,
  FieldId::field_dma_out_state_ch0_outlink_dscr_addr,
  FieldId::field_dma_out_state_ch0_out_dscr_state,
  FieldId::field_dma_out_state_ch0_out_state,
  FieldId::field_dma_out_state_ch1_outlink_dscr_addr,
  FieldId::field_dma_out_state_ch1_out_dscr_state,
  FieldId::field_dma_out_state_ch1_out_state,
  FieldId::field_dma_out_state_ch2_outlink_dscr_addr,
  FieldId::field_dma_out_state_ch2_out_dscr_state,
  FieldId::field_dma_out_state_ch2_out_state,
  FieldId::field_gpio_bt_select_bt_sel,
  FieldId::field_gpio_clock_gate_clk_en,
  FieldId::field_gpio_cpusdio_int_sdio_int,
  FieldId::field_gpio_enable_data,
  FieldId::field_gpio_enable_w1tc_enable_w1tc,
  FieldId::field_gpio_enable_w1ts_enable_w1ts,
  FieldId::field_gpio_func_s_in_sel_cfg_in_sel,
  FieldId::field_gpio_func_s_in_sel_cfg_in_inv_sel,
  FieldId::field_gpio_func_s_in_sel_cfg_sel,
  FieldId::field_gpio_func_s_out_sel_cfg_out_sel,
  FieldId::field_gpio_func_s_out_sel_cfg_inv_sel,
  FieldId::field_gpio_func_s_out_sel_cfg_oen_sel,
  FieldId::field_gpio_func_s_out_sel_cfg_oen_inv_sel,
  FieldId::field_gpio_in_data_next,
  FieldId::field_gpio_out_data_orig,
  FieldId::field_gpio_out_w1tc_out_w1tc,
  FieldId::field_gpio_out_w1ts_out_w1ts,
  FieldId::field_gpio_pcpu_int_procpu_int,
  FieldId::field_gpio_pcpu_nmi_int_procpu_nmi_int,
  FieldId::field_gpio_pin_s_sync2_bypass,
  FieldId::field_gpio_pin_s_pad_driver,
  FieldId::field_gpio_pin_s_sync1_bypass,
  FieldId::field_gpio_pin_s_int_type,
  FieldId::field_gpio_pin_s_wakeup_enable,
  FieldId::field_gpio_pin_s_config,
  FieldId::field_gpio_pin_s_int_ena,
  FieldId::field_gpio_reg_date_reg_date,
  FieldId::field_gpio_sdio_select_sdio_sel,
  FieldId::field_gpio_status_interrupt,
  FieldId::field_gpio_status_next_status_interrupt_next,
  FieldId::field_gpio_status_w1tc_status_w1tc,
  FieldId::field_gpio_status_w1ts_status_w1ts,
  FieldId::field_gpio_strap_strapping,
  FieldId::field_i2c0_clk_conf_sclk_div_num,
  FieldId::field_i2c0_clk_conf_sclk_div_a,
  FieldId::field_i2c0_clk_conf_sclk_div_b,
  FieldId::field_i2c0_clk_conf_sclk_sel,
  FieldId::field_i2c0_clk_conf_sclk_active,
  FieldId::field_i2c0_comd_s_command,
  FieldId::field_i2c0_comd_s_command_done,
  FieldId::field_i2c0_ctr_sda_force_out,
  FieldId::field_i2c0_ctr_scl_force_out,
  FieldId::field_i2c0_ctr_sample_scl_level,
  FieldId::field_i2c0_ctr_rx_full_ack_level,
  FieldId::field_i2c0_ctr_ms_mode,
  FieldId::field_i2c0_ctr_trans_start,
  FieldId::field_i2c0_ctr_tx_lsb_first,
  FieldId::field_i2c0_ctr_rx_lsb_first,
  FieldId::field_i2c0_ctr_clk_en,
  FieldId::field_i2c0_ctr_arbitration_en,
  FieldId::field_i2c0_ctr_fsm_rst,
  FieldId::field_i2c0_ctr_conf_upgate,
  FieldId::field_i2c0_ctr_slv_tx_auto_start_en,
  FieldId::field_i2c0_ctr_addr_10bit_rw_check_en,
  FieldId::field_i2c0_ctr_addr_broadcasting_en,
  FieldId::field_i2c0_data_fifo_rdata,
  FieldId::field_i2c0_date_date,
  FieldId::field_i2c0_fifo_conf_rxfifo_wm_thrhd,
  FieldId::field_i2c0_fifo_conf_txfifo_wm_thrhd,
  FieldId::field_i2c0_fifo_conf_nonfifo_en,
  FieldId::field_i2c0_fifo_conf_fifo_addr_cfg_en,
  FieldId::field_i2c0_fifo_conf_rx_fifo_rst,
  FieldId::field_i2c0_fifo_conf_tx_fifo_rst,
  FieldId::field_i2c0_fifo_conf_fifo_prt_en,
  FieldId::field_i2c0_fifo_st_rxfifo_raddr,
  FieldId::field_i2c0_fifo_st_rxfifo_waddr,
  FieldId::field_i2c0_fifo_st_txfifo_raddr,
  FieldId::field_i2c0_fifo_st_txfifo_waddr,
  FieldId::field_i2c0_fifo_st_slave_rw_point,
  FieldId::field_i2c0_filter_cfg_scl_filter_thres,
  FieldId::field_i2c0_filter_cfg_sda_filter_thres,
  FieldId::field_i2c0_filter_cfg_scl_filter_en,
  FieldId::field_i2c0_filter_cfg_sda_filter_en,
  FieldId::field_i2c0_int_clr_rxfifo_wm_int_clr,
  FieldId::field_i2c0_int_clr_txfifo_wm_int_clr,
  FieldId::field_i2c0_int_clr_rxfifo_ovf_int_clr,
  FieldId::field_i2c0_int_clr_end_detect_int_clr,
  FieldId::field_i2c0_int_clr_byte_trans_done_int_clr,
  FieldId::field_i2c0_int_clr_arbitration_lost_int_clr,
  FieldId::field_i2c0_int_clr_mst_txfifo_udf_int_clr,
  FieldId::field_i2c0_int_clr_trans_complete_int_clr,
  FieldId::field_i2c0_int_clr_time_out_int_clr,
  FieldId::field_i2c0_int_clr_trans_start_int_clr,
  FieldId::field_i2c0_int_clr_nack_int_clr,
  FieldId::field_i2c0_int_clr_txfifo_ovf_int_clr,
  FieldId::field_i2c0_int_clr_rxfifo_udf_int_clr,
  FieldId::field_i2c0_int_clr_scl_st_to_int_clr,
  FieldId::field_i2c0_int_clr_scl_main_st_to_int_clr,
  FieldId::field_i2c0_int_clr_det_start_int_clr,
  FieldId::field_i2c0_int_clr_slave_stretch_int_clr,
  FieldId::field_i2c0_int_clr_general_call_int_clr,
  FieldId::field_i2c0_int_ena_rxfifo_wm_int_ena,
  FieldId::field_i2c0_int_ena_txfifo_wm_int_ena,
  FieldId::field_i2c0_int_ena_rxfifo_ovf_int_ena,
  FieldId::field_i2c0_int_ena_end_detect_int_ena,
  FieldId::field_i2c0_int_ena_byte_trans_done_int_ena,
  FieldId::field_i2c0_int_ena_arbitration_lost_int_ena,
  FieldId::field_i2c0_int_ena_mst_txfifo_udf_int_ena,
  FieldId::field_i2c0_int_ena_trans_complete_int_ena,
  FieldId::field_i2c0_int_ena_time_out_int_ena,
  FieldId::field_i2c0_int_ena_trans_start_int_ena,
  FieldId::field_i2c0_int_ena_nack_int_ena,
  FieldId::field_i2c0_int_ena_txfifo_ovf_int_ena,
  FieldId::field_i2c0_int_ena_rxfifo_udf_int_ena,
  FieldId::field_i2c0_int_ena_scl_st_to_int_ena,
  FieldId::field_i2c0_int_ena_scl_main_st_to_int_ena,
  FieldId::field_i2c0_int_ena_det_start_int_ena,
  FieldId::field_i2c0_int_ena_slave_stretch_int_ena,
  FieldId::field_i2c0_int_ena_general_call_int_ena,
  FieldId::field_i2c0_int_raw_rxfifo_wm_int_raw,
  FieldId::field_i2c0_int_raw_txfifo_wm_int_raw,
  FieldId::field_i2c0_int_raw_rxfifo_ovf_int_raw,
  FieldId::field_i2c0_int_raw_end_detect_int_raw,
  FieldId::field_i2c0_int_raw_byte_trans_done_int_raw,
  FieldId::field_i2c0_int_raw_arbitration_lost_int_raw,
  FieldId::field_i2c0_int_raw_mst_txfifo_udf_int_raw,
  FieldId::field_i2c0_int_raw_trans_complete_int_raw,
  FieldId::field_i2c0_int_raw_time_out_int_raw,
  FieldId::field_i2c0_int_raw_trans_start_int_raw,
  FieldId::field_i2c0_int_raw_nack_int_raw,
  FieldId::field_i2c0_int_raw_txfifo_ovf_int_raw,
  FieldId::field_i2c0_int_raw_rxfifo_udf_int_raw,
  FieldId::field_i2c0_int_raw_scl_st_to_int_raw,
  FieldId::field_i2c0_int_raw_scl_main_st_to_int_raw,
  FieldId::field_i2c0_int_raw_det_start_int_raw,
  FieldId::field_i2c0_int_raw_slave_stretch_int_raw,
  FieldId::field_i2c0_int_raw_general_call_int_raw,
  FieldId::field_i2c0_int_status_rxfifo_wm_int_st,
  FieldId::field_i2c0_int_status_txfifo_wm_int_st,
  FieldId::field_i2c0_int_status_rxfifo_ovf_int_st,
  FieldId::field_i2c0_int_status_end_detect_int_st,
  FieldId::field_i2c0_int_status_byte_trans_done_int_st,
  FieldId::field_i2c0_int_status_arbitration_lost_int_st,
  FieldId::field_i2c0_int_status_mst_txfifo_udf_int_st,
  FieldId::field_i2c0_int_status_trans_complete_int_st,
  FieldId::field_i2c0_int_status_time_out_int_st,
  FieldId::field_i2c0_int_status_trans_start_int_st,
  FieldId::field_i2c0_int_status_nack_int_st,
  FieldId::field_i2c0_int_status_txfifo_ovf_int_st,
  FieldId::field_i2c0_int_status_rxfifo_udf_int_st,
  FieldId::field_i2c0_int_status_scl_st_to_int_st,
  FieldId::field_i2c0_int_status_scl_main_st_to_int_st,
  FieldId::field_i2c0_int_status_det_start_int_st,
  FieldId::field_i2c0_int_status_slave_stretch_int_st,
  FieldId::field_i2c0_int_status_general_call_int_st,
  FieldId::field_i2c0_rxfifo_start_addr_rxfifo_start_addr,
  FieldId::field_i2c0_scl_high_period_scl_high_period,
  FieldId::field_i2c0_scl_high_period_scl_wait_high_period,
  FieldId::field_i2c0_scl_low_period_scl_low_period,
  FieldId::field_i2c0_scl_main_st_time_out_scl_main_st_to_i2c,
  FieldId::field_i2c0_scl_rstart_setup_time,
  FieldId::field_i2c0_scl_sp_conf_scl_rst_slv_en,
  FieldId::field_i2c0_scl_sp_conf_scl_rst_slv_num,
  FieldId::field_i2c0_scl_sp_conf_scl_pd_en,
  FieldId::field_i2c0_scl_sp_conf_sda_pd_en,
  FieldId::field_i2c0_scl_start_hold_time,
  FieldId::field_i2c0_scl_stop_hold_time,
  FieldId::field_i2c0_scl_stop_setup_time,
  FieldId::field_i2c0_scl_stretch_conf_stretch_protect_num,
  FieldId::field_i2c0_scl_stretch_conf_slave_scl_stretch_en,
  FieldId::field_i2c0_scl_stretch_conf_slave_scl_stretch_clr,
  FieldId::field_i2c0_scl_stretch_conf_slave_byte_ack_ctl_en,
  FieldId::field_i2c0_scl_stretch_conf_slave_byte_ack_lvl,
  FieldId::field_i2c0_scl_st_time_out_scl_st_to_i2c,
  FieldId::field_i2c0_sda_hold_time,
  FieldId::field_i2c0_sda_sample_time,
  FieldId::field_i2c0_slave_addr_slave_addr,
  FieldId::field_i2c0_slave_addr_addr_10bit_en,
  FieldId::field_i2c0_sr_resp_rec,
  FieldId::field_i2c0_sr_slave_rw,
  FieldId::field_i2c0_sr_arb_lost,
  FieldId::field_i2c0_sr_bus_busy,
  FieldId::field_i2c0_sr_slave_addressed,
  FieldId::field_i2c0_sr_rxfifo_cnt,
  FieldId::field_i2c0_sr_stretch_cause,
  FieldId::field_i2c0_sr_txfifo_cnt,
  FieldId::field_i2c0_sr_scl_main_state_last,
  FieldId::field_i2c0_sr_scl_state_last,
  FieldId::field_i2c0_to_time_out_value,
  FieldId::field_i2c0_to_time_out_en,
  FieldId::field_i2c0_txfifo_start_addr_txfifo_start_addr,
  FieldId::field_pcr_i2c0_conf_reg_i2c0_clk_en,
  FieldId::field_pcr_spi2_conf_reg_spi2_clk_en,
  FieldId::field_pcr_uart0_conf0_reg_uart0_clk_en,
  FieldId::field_pcr_uart1_conf0_reg_uart1_clk_en,
  FieldId::field_spi0_cache_fctrl_cache_req_en,
  FieldId::field_spi0_cache_fctrl_cache_usr_addr_4byte,
  FieldId::field_spi0_cache_fctrl_cache_flash_usr_cmd,
  FieldId::field_spi0_cache_fctrl_fdin_dual,
  FieldId::field_spi0_cache_fctrl_fdout_dual,
  FieldId::field_spi0_cache_fctrl_faddr_dual,
  FieldId::field_spi0_cache_fctrl_fdin_quad,
  FieldId::field_spi0_cache_fctrl_fdout_quad,
  FieldId::field_spi0_cache_fctrl_faddr_quad,
  FieldId::field_spi0_clock_clkcnt_l,
  FieldId::field_spi0_clock_clkcnt_h,
  FieldId::field_spi0_clock_clkcnt_n,
  FieldId::field_spi0_clock_clk_equ_sysclk,
  FieldId::field_spi0_clock_gate_clk_en,
  FieldId::field_spi0_core_clk_sel_spi01_clk_sel,
  FieldId::field_spi0_ctrl_fdummy_out,
  FieldId::field_spi0_ctrl_fcmd_dual,
  FieldId::field_spi0_ctrl_fcmd_quad,
  FieldId::field_spi0_ctrl_fastrd_mode,
  FieldId::field_spi0_ctrl_fread_dual,
  FieldId::field_spi0_ctrl_q_pol,
  FieldId::field_spi0_ctrl_d_pol,
  FieldId::field_spi0_ctrl_fread_quad,
  FieldId::field_spi0_ctrl_wp,
  FieldId::field_spi0_ctrl_fread_dio,
  FieldId::field_spi0_ctrl_fread_qio,
  FieldId::field_spi0_ctrl1_clk_mode,
  FieldId::field_spi0_ctrl1_rxfifo_rst,
  FieldId::field_spi0_ctrl2_cs_setup_time,
  FieldId::field_spi0_ctrl2_cs_hold_time,
  FieldId::field_spi0_ctrl2_cs_hold_delay,
  FieldId::field_spi0_ctrl2_sync_reset,
  FieldId::field_spi0_date_date,
  FieldId::field_spi0_din_mode_din0_mode,
  FieldId::field_spi0_din_mode_din1_mode,
  FieldId::field_spi0_din_mode_din2_mode,
  FieldId::field_spi0_din_mode_din3_mode,
  FieldId::field_spi0_din_num_din0_num,
  FieldId::field_spi0_din_num_din1_num,
  FieldId::field_spi0_din_num_din2_num,
  FieldId::field_spi0_din_num_din3_num,
  FieldId::field_spi0_dout_mode_dout0_mode,
  FieldId::field_spi0_dout_mode_dout1_mode,
  FieldId::field_spi0_dout_mode_dout2_mode,
  FieldId::field_spi0_dout_mode_dout3_mode,
  FieldId::field_spi0_fsm_cspi_st,
  FieldId::field_spi0_fsm_em_st,
  FieldId::field_spi0_fsm_cspi_lock_delay_time,
  FieldId::field_spi0_misc_trans_end,
  FieldId::field_spi0_misc_trans_end_int_ena,
  FieldId::field_spi0_misc_cspi_st_trans_end,
  FieldId::field_spi0_misc_cspi_st_trans_end_int_ena,
  FieldId::field_spi0_misc_ck_idle_edge,
  FieldId::field_spi0_misc_cs_keep_active,
  FieldId::field_spi0_rd_status_wb_mode,
  FieldId::field_spi0_timing_cali_timing_clk_ena,
  FieldId::field_spi0_timing_cali_timing_cali,
  FieldId::field_spi0_timing_cali_extra_dummy_cyclelen,
  FieldId::field_spi0_user_cs_hold,
  FieldId::field_spi0_user_cs_setup,
  FieldId::field_spi0_user_ck_out_edge,
  FieldId::field_spi0_user_usr_dummy_idle,
  FieldId::field_spi0_user_usr_dummy,
  FieldId::field_spi0_user1_usr_dummy_cyclelen,
  FieldId::field_spi0_user1_usr_addr_bitlen,
  FieldId::field_spi0_user2_usr_command_value,
  FieldId::field_spi0_user2_usr_command_bitlen,
  FieldId::field_spi1_addr_usr_addr_value,
  FieldId::field_spi1_cache_fctrl_cache_usr_addr_4byte,
  FieldId::field_spi1_cache_fctrl_fdin_dual,
  FieldId::field_spi1_cache_fctrl_fdout_dual,
  FieldId::field_spi1_cache_fctrl_faddr_dual,
  FieldId::field_spi1_cache_fctrl_fdin_quad,
  FieldId::field_spi1_cache_fctrl_fdout_quad,
  FieldId::field_spi1_cache_fctrl_faddr_quad,
  FieldId::field_spi1_clock_clkcnt_l,
  FieldId::field_spi1_clock_clkcnt_h,
  FieldId::field_spi1_clock_clkcnt_n,
  FieldId::field_spi1_clock_clk_equ_sysclk,
  FieldId::field_spi1_clock_gate_clk_en,
  FieldId::field_spi1_cmd_spi1_mst_st,
  FieldId::field_spi1_cmd_mspi_st,
  FieldId::field_spi1_cmd_flash_pe,
  FieldId::field_spi1_cmd_usr,
  FieldId::field_spi1_cmd_flash_hpm,
  FieldId::field_spi1_cmd_flash_res,
  FieldId::field_spi1_cmd_flash_dp,
  FieldId::field_spi1_cmd_flash_ce,
  FieldId::field_spi1_cmd_flash_be,
  FieldId::field_spi1_cmd_flash_se,
  FieldId::field_spi1_cmd_flash_pp,
  FieldId::field_spi1_cmd_flash_wrsr,
  FieldId::field_spi1_cmd_flash_rdsr,
  FieldId::field_spi1_cmd_flash_rdid,
  FieldId::field_spi1_cmd_flash_wrdi,
  FieldId::field_spi1_cmd_flash_wren,
  FieldId::field_spi1_cmd_flash_read,
  FieldId::field_spi1_ctrl_fdummy_out,
  FieldId::field_spi1_ctrl_fcmd_dual,
  FieldId::field_spi1_ctrl_fcmd_quad,
  FieldId::field_spi1_ctrl_fcs_crc_en,
  FieldId::field_spi1_ctrl_tx_crc_en,
  FieldId::field_spi1_ctrl_fastrd_mode,
  FieldId::field_spi1_ctrl_fread_dual,
  FieldId::field_spi1_ctrl_resandres,
  FieldId::field_spi1_ctrl_q_pol,
  FieldId::field_spi1_ctrl_d_pol,
  FieldId::field_spi1_ctrl_fread_quad,
  FieldId::field_spi1_ctrl_wp,
  FieldId::field_spi1_ctrl_wrsr_2b,
  FieldId::field_spi1_ctrl_fread_dio,
  FieldId::field_spi1_ctrl_fread_qio,
  FieldId::field_spi1_ctrl1_clk_mode,
  FieldId::field_spi1_ctrl1_cs_hold_dly_res,
  FieldId::field_spi1_ctrl2_sync_reset,
  FieldId::field_spi1_date_date,
  FieldId::field_spi1_flash_sus_cmd_flash_per_command,
  FieldId::field_spi1_flash_sus_cmd_flash_pes_command,
  FieldId::field_spi1_flash_sus_cmd_wait_pesr_command,
  FieldId::field_spi1_flash_sus_ctrl_flash_per,
  FieldId::field_spi1_flash_sus_ctrl_flash_pes,
  FieldId::field_spi1_flash_sus_ctrl_flash_per_wait_en,
  FieldId::field_spi1_flash_sus_ctrl_flash_pes_wait_en,
  FieldId::field_spi1_flash_sus_ctrl_pes_per_en,
  FieldId::field_spi1_flash_sus_ctrl_flash_pes_en,
  FieldId::field_spi1_flash_sus_ctrl_pesr_end_msk,
  FieldId::field_spi1_flash_sus_ctrl_rd_sus_2b,
  FieldId::field_spi1_flash_sus_ctrl_per_end_en,
  FieldId::field_spi1_flash_sus_ctrl_pes_end_en,
  FieldId::field_spi1_flash_sus_ctrl_sus_timeout_cnt,
  FieldId::field_spi1_flash_waiti_ctrl_waiti_dummy,
  FieldId::field_spi1_flash_waiti_ctrl_waiti_cmd,
  FieldId::field_spi1_flash_waiti_ctrl_waiti_dummy_cyclelen,
  FieldId::field_spi1_int_clr_per_end_int_clr,
  FieldId::field_spi1_int_clr_pes_end_int_clr,
  FieldId::field_spi1_int_clr_wpe_end_int_clr,
  FieldId::field_spi1_int_clr_slv_st_end_int_clr,
  FieldId::field_spi1_int_clr_mst_st_end_int_clr,
  FieldId::field_spi1_int_ena_per_end_int_ena,
  FieldId::field_spi1_int_ena_pes_end_int_ena,
  FieldId::field_spi1_int_ena_wpe_end_int_ena,
  FieldId::field_spi1_int_ena_slv_st_end_int_ena,
  FieldId::field_spi1_int_ena_mst_st_end_int_ena,
  FieldId::field_spi1_int_raw_per_end_int_raw,
  FieldId::field_spi1_int_raw_pes_end_int_raw,
  FieldId::field_spi1_int_raw_wpe_end_int_raw,
  FieldId::field_spi1_int_raw_slv_st_end_int_raw,
  FieldId::field_spi1_int_raw_mst_st_end_int_raw,
  FieldId::field_spi1_int_st_per_end_int_st,
  FieldId::field_spi1_int_st_pes_end_int_st,
  FieldId::field_spi1_int_st_wpe_end_int_st,
  FieldId::field_spi1_int_st_slv_st_end_int_st,
  FieldId::field_spi1_int_st_mst_st_end_int_st,
  FieldId::field_spi1_misc_cs0_dis,
  FieldId::field_spi1_misc_cs1_dis,
  FieldId::field_spi1_misc_ck_idle_edge,
  FieldId::field_spi1_misc_cs_keep_active,
  FieldId::field_spi1_miso_dlen_usr_miso_dbitlen,
  FieldId::field_spi1_mosi_dlen_usr_mosi_dbitlen,
  FieldId::field_spi1_rd_status_status,
  FieldId::field_spi1_rd_status_wb_mode,
  FieldId::field_spi1_sus_status_flash_sus,
  FieldId::field_spi1_sus_status_wait_pesr_cmd_2b,
  FieldId::field_spi1_sus_status_flash_hpm_dly_128,
  FieldId::field_spi1_sus_status_flash_res_dly_128,
  FieldId::field_spi1_sus_status_flash_dp_dly_128,
  FieldId::field_spi1_sus_status_flash_per_dly_128,
  FieldId::field_spi1_sus_status_flash_pes_dly_128,
  FieldId::field_spi1_sus_status_spi0_lock_en,
  FieldId::field_spi1_timing_cali_timing_cali,
  FieldId::field_spi1_timing_cali_extra_dummy_cyclelen,
  FieldId::field_spi1_tx_crc_data,
  FieldId::field_spi1_user_ck_out_edge,
  FieldId::field_spi1_user_fwrite_dual,
  FieldId::field_spi1_user_fwrite_quad,
  FieldId::field_spi1_user_fwrite_dio,
  FieldId::field_spi1_user_fwrite_qio,
  FieldId::field_spi1_user_usr_miso_highpart,
  FieldId::field_spi1_user_usr_mosi_highpart,
  FieldId::field_spi1_user_usr_dummy_idle,
  FieldId::field_spi1_user_usr_mosi,
  FieldId::field_spi1_user_usr_miso,
  FieldId::field_spi1_user_usr_dummy,
  FieldId::field_spi1_user_usr_addr,
  FieldId::field_spi1_user_usr_command,
  FieldId::field_spi1_user1_usr_dummy_cyclelen,
  FieldId::field_spi1_user1_usr_addr_bitlen,
  FieldId::field_spi1_user2_usr_command_value,
  FieldId::field_spi1_user2_usr_command_bitlen,
  FieldId::field_spi1_w0_buf0,
  FieldId::field_spi1_w1_buf1,
  FieldId::field_spi1_w10_buf10,
  FieldId::field_spi1_w11_buf11,
  FieldId::field_spi1_w12_buf12,
  FieldId::field_spi1_w13_buf13,
  FieldId::field_spi1_w14_buf14,
  FieldId::field_spi1_w15_buf15,
  FieldId::field_spi1_w2_buf2,
  FieldId::field_spi1_w3_buf3,
  FieldId::field_spi1_w4_buf4,
  FieldId::field_spi1_w5_buf5,
  FieldId::field_spi1_w6_buf6,
  FieldId::field_spi1_w7_buf7,
  FieldId::field_spi1_w8_buf8,
  FieldId::field_spi1_w9_buf9,
  FieldId::field_spi2_addr_usr_addr_value,
  FieldId::field_spi2_clk_gate_clk_en,
  FieldId::field_spi2_clk_gate_mst_clk_active,
  FieldId::field_spi2_clk_gate_mst_clk_sel,
  FieldId::field_spi2_clock_clkcnt_l,
  FieldId::field_spi2_clock_clkcnt_h,
  FieldId::field_spi2_clock_clkcnt_n,
  FieldId::field_spi2_clock_clkdiv_pre,
  FieldId::field_spi2_clock_clk_equ_sysclk,
  FieldId::field_spi2_cmd_conf_bitlen,
  FieldId::field_spi2_cmd_update,
  FieldId::field_spi2_cmd_usr,
  FieldId::field_spi2_ctrl_dummy_out,
  FieldId::field_spi2_ctrl_faddr_dual,
  FieldId::field_spi2_ctrl_faddr_quad,
  FieldId::field_spi2_ctrl_fcmd_dual,
  FieldId::field_spi2_ctrl_fcmd_quad,
  FieldId::field_spi2_ctrl_fread_dual,
  FieldId::field_spi2_ctrl_fread_quad,
  FieldId::field_spi2_ctrl_q_pol,
  FieldId::field_spi2_ctrl_d_pol,
  FieldId::field_spi2_ctrl_hold_pol,
  FieldId::field_spi2_ctrl_wp_pol,
  FieldId::field_spi2_ctrl_rd_bit_order,
  FieldId::field_spi2_ctrl_wr_bit_order,
  FieldId::field_spi2_date_date,
  FieldId::field_spi2_din_mode_din0_mode,
  FieldId::field_spi2_din_mode_din1_mode,
  FieldId::field_spi2_din_mode_din2_mode,
  FieldId::field_spi2_din_mode_din3_mode,
  FieldId::field_spi2_din_mode_timing_hclk_active,
  FieldId::field_spi2_din_num_din0_num,
  FieldId::field_spi2_din_num_din1_num,
  FieldId::field_spi2_din_num_din2_num,
  FieldId::field_spi2_din_num_din3_num,
  FieldId::field_spi2_dma_conf_dma_slv_seg_trans_en,
  FieldId::field_spi2_dma_conf_slv_rx_seg_trans_clr_en,
  FieldId::field_spi2_dma_conf_slv_tx_seg_trans_clr_en,
  FieldId::field_spi2_dma_conf_rx_eof_en,
  FieldId::field_spi2_dma_conf_dma_rx_ena,
  FieldId::field_spi2_dma_conf_dma_tx_ena,
  FieldId::field_spi2_dma_conf_rx_afifo_rst,
  FieldId::field_spi2_dma_conf_buf_afifo_rst,
  FieldId::field_spi2_dma_conf_dma_afifo_rst,
  FieldId::field_spi2_dma_int_clr_dma_infifo_full_err_int_clr,
  FieldId::field_spi2_dma_int_clr_dma_outfifo_empty_err_int_clr,
  FieldId::field_spi2_dma_int_clr_slv_ex_qpi_int_clr,
  FieldId::field_spi2_dma_int_clr_slv_en_qpi_int_clr,
  FieldId::field_spi2_dma_int_clr_slv_cmd7_int_clr,
  FieldId::field_spi2_dma_int_clr_slv_cmd8_int_clr,
  FieldId::field_spi2_dma_int_clr_slv_cmd9_int_clr,
  FieldId::field_spi2_dma_int_clr_slv_cmda_int_clr,
  FieldId::field_spi2_dma_int_clr_slv_rd_dma_done_int_clr,
  FieldId::field_spi2_dma_int_clr_slv_wr_dma_done_int_clr,
  FieldId::field_spi2_dma_int_clr_slv_rd_buf_done_int_clr,
  FieldId::field_spi2_dma_int_clr_slv_wr_buf_done_int_clr,
  FieldId::field_spi2_dma_int_clr_trans_done_int_clr,
  FieldId::field_spi2_dma_int_clr_dma_seg_trans_done_int_clr,
  FieldId::field_spi2_dma_int_clr_seg_magic_err_int_clr,
  FieldId::field_spi2_dma_int_clr_slv_buf_addr_err_int_clr,
  FieldId::field_spi2_dma_int_clr_slv_cmd_err_int_clr,
  FieldId::field_spi2_dma_int_clr_mst_rx_afifo_wfull_err_int_clr,
  FieldId::field_spi2_dma_int_clr_mst_tx_afifo_rempty_err_int_clr,
  FieldId::field_spi2_dma_int_clr_app2_int_clr,
  FieldId::field_spi2_dma_int_clr_app1_int_clr,
  FieldId::field_spi2_dma_int_ena_dma_infifo_full_err_int_ena,
  FieldId::field_spi2_dma_int_ena_dma_outfifo_empty_err_int_ena,
  FieldId::field_spi2_dma_int_ena_slv_ex_qpi_int_ena,
  FieldId::field_spi2_dma_int_ena_slv_en_qpi_int_ena,
  FieldId::field_spi2_dma_int_ena_slv_cmd7_int_ena,
  FieldId::field_spi2_dma_int_ena_slv_cmd8_int_ena,
  FieldId::field_spi2_dma_int_ena_slv_cmd9_int_ena,
  FieldId::field_spi2_dma_int_ena_slv_cmda_int_ena,
  FieldId::field_spi2_dma_int_ena_slv_rd_dma_done_int_ena,
  FieldId::field_spi2_dma_int_ena_slv_wr_dma_done_int_ena,
  FieldId::field_spi2_dma_int_ena_slv_rd_buf_done_int_ena,
  FieldId::field_spi2_dma_int_ena_slv_wr_buf_done_int_ena,
  FieldId::field_spi2_dma_int_ena_trans_done_int_ena,
  FieldId::field_spi2_dma_int_ena_dma_seg_trans_done_int_ena,
  FieldId::field_spi2_dma_int_ena_seg_magic_err_int_ena,
  FieldId::field_spi2_dma_int_ena_slv_buf_addr_err_int_ena,
  FieldId::field_spi2_dma_int_ena_slv_cmd_err_int_ena,
  FieldId::field_spi2_dma_int_ena_mst_rx_afifo_wfull_err_int_ena,
  FieldId::field_spi2_dma_int_ena_mst_tx_afifo_rempty_err_int_ena,
  FieldId::field_spi2_dma_int_ena_app2_int_ena,
  FieldId::field_spi2_dma_int_ena_app1_int_ena,
  FieldId::field_spi2_dma_int_raw_dma_infifo_full_err_int_raw,
  FieldId::field_spi2_dma_int_raw_dma_outfifo_empty_err_int_raw,
  FieldId::field_spi2_dma_int_raw_slv_ex_qpi_int_raw,
  FieldId::field_spi2_dma_int_raw_slv_en_qpi_int_raw,
  FieldId::field_spi2_dma_int_raw_slv_cmd7_int_raw,
  FieldId::field_spi2_dma_int_raw_slv_cmd8_int_raw,
  FieldId::field_spi2_dma_int_raw_slv_cmd9_int_raw,
  FieldId::field_spi2_dma_int_raw_slv_cmda_int_raw,
  FieldId::field_spi2_dma_int_raw_slv_rd_dma_done_int_raw,
  FieldId::field_spi2_dma_int_raw_slv_wr_dma_done_int_raw,
  FieldId::field_spi2_dma_int_raw_slv_rd_buf_done_int_raw,
  FieldId::field_spi2_dma_int_raw_slv_wr_buf_done_int_raw,
  FieldId::field_spi2_dma_int_raw_trans_done_int_raw,
  FieldId::field_spi2_dma_int_raw_dma_seg_trans_done_int_raw,
  FieldId::field_spi2_dma_int_raw_seg_magic_err_int_raw,
  FieldId::field_spi2_dma_int_raw_slv_buf_addr_err_int_raw,
  FieldId::field_spi2_dma_int_raw_slv_cmd_err_int_raw,
  FieldId::field_spi2_dma_int_raw_mst_rx_afifo_wfull_err_int_raw,
  FieldId::field_spi2_dma_int_raw_mst_tx_afifo_rempty_err_int_raw,
  FieldId::field_spi2_dma_int_raw_app2_int_raw,
  FieldId::field_spi2_dma_int_raw_app1_int_raw,
  FieldId::field_spi2_dma_int_st_dma_infifo_full_err_int_st,
  FieldId::field_spi2_dma_int_st_dma_outfifo_empty_err_int_st,
  FieldId::field_spi2_dma_int_st_slv_ex_qpi_int_st,
  FieldId::field_spi2_dma_int_st_slv_en_qpi_int_st,
  FieldId::field_spi2_dma_int_st_slv_cmd7_int_st,
  FieldId::field_spi2_dma_int_st_slv_cmd8_int_st,
  FieldId::field_spi2_dma_int_st_slv_cmd9_int_st,
  FieldId::field_spi2_dma_int_st_slv_cmda_int_st,
  FieldId::field_spi2_dma_int_st_slv_rd_dma_done_int_st,
  FieldId::field_spi2_dma_int_st_slv_wr_dma_done_int_st,
  FieldId::field_spi2_dma_int_st_slv_rd_buf_done_int_st,
  FieldId::field_spi2_dma_int_st_slv_wr_buf_done_int_st,
  FieldId::field_spi2_dma_int_st_trans_done_int_st,
  FieldId::field_spi2_dma_int_st_dma_seg_trans_done_int_st,
  FieldId::field_spi2_dma_int_st_seg_magic_err_int_st,
  FieldId::field_spi2_dma_int_st_slv_buf_addr_err_int_st,
  FieldId::field_spi2_dma_int_st_slv_cmd_err_int_st,
  FieldId::field_spi2_dma_int_st_mst_rx_afifo_wfull_err_int_st,
  FieldId::field_spi2_dma_int_st_mst_tx_afifo_rempty_err_int_st,
  FieldId::field_spi2_dma_int_st_app2_int_st,
  FieldId::field_spi2_dma_int_st_app1_int_st,
  FieldId::field_spi2_dout_mode_dout0_mode,
  FieldId::field_spi2_dout_mode_dout1_mode,
  FieldId::field_spi2_dout_mode_dout2_mode,
  FieldId::field_spi2_dout_mode_dout3_mode,
  FieldId::field_spi2_misc_cs0_dis,
  FieldId::field_spi2_misc_cs1_dis,
  FieldId::field_spi2_misc_cs2_dis,
  FieldId::field_spi2_misc_cs3_dis,
  FieldId::field_spi2_misc_cs4_dis,
  FieldId::field_spi2_misc_cs5_dis,
  FieldId::field_spi2_misc_ck_dis,
  FieldId::field_spi2_misc_master_cs_pol,
  FieldId::field_spi2_misc_slave_cs_pol,
  FieldId::field_spi2_misc_ck_idle_edge,
  FieldId::field_spi2_misc_cs_keep_active,
  FieldId::field_spi2_misc_quad_din_pin_swap,
  FieldId::field_spi2_ms_dlen_ms_data_bitlen,
  FieldId::field_spi2_slave_clk_mode,
  FieldId::field_spi2_slave_clk_mode_13,
  FieldId::field_spi2_slave_rsck_data_out,
  FieldId::field_spi2_slave_slv_rddma_bitlen_en,
  FieldId::field_spi2_slave_slv_wrdma_bitlen_en,
  FieldId::field_spi2_slave_slv_rdbuf_bitlen_en,
  FieldId::field_spi2_slave_slv_wrbuf_bitlen_en,
  FieldId::field_spi2_slave_dma_seg_magic_value,
  FieldId::field_spi2_slave_mode,
  FieldId::field_spi2_slave_soft_reset,
  FieldId::field_spi2_slave_usr_conf,
  FieldId::field_spi2_slave1_slv_data_bitlen,
  FieldId::field_spi2_slave1_slv_last_command,
  FieldId::field_spi2_slave1_slv_last_addr,
  FieldId::field_spi2_user_doutdin,
  FieldId::field_spi2_user_qpi_mode,
  FieldId::field_spi2_user_tsck_i_edge,
  FieldId::field_spi2_user_cs_hold,
  FieldId::field_spi2_user_cs_setup,
  FieldId::field_spi2_user_rsck_i_edge,
  FieldId::field_spi2_user_ck_out_edge,
  FieldId::field_spi2_user_fwrite_dual,
  FieldId::field_spi2_user_fwrite_quad,
  FieldId::field_spi2_user_usr_conf_nxt,
  FieldId::field_spi2_user_sio,
  FieldId::field_spi2_user_usr_miso_highpart,
  FieldId::field_spi2_user_usr_mosi_highpart,
  FieldId::field_spi2_user_usr_dummy_idle,
  FieldId::field_spi2_user_usr_mosi,
  FieldId::field_spi2_user_usr_miso,
  FieldId::field_spi2_user_usr_dummy,
  FieldId::field_spi2_user_usr_addr,
  FieldId::field_spi2_user_usr_command,
  FieldId::field_spi2_user1_usr_dummy_cyclelen,
  FieldId::field_spi2_user1_mst_wfull_err_end_en,
  FieldId::field_spi2_user1_cs_setup_time,
  FieldId::field_spi2_user1_cs_hold_time,
  FieldId::field_spi2_user1_usr_addr_bitlen,
  FieldId::field_spi2_user2_usr_command_value,
  FieldId::field_spi2_user2_mst_rempty_err_end_en,
  FieldId::field_spi2_user2_usr_command_bitlen,
  FieldId::field_spi2_w0_buf0,
  FieldId::field_spi2_w1_buf1,
  FieldId::field_spi2_w10_buf10,
  FieldId::field_spi2_w11_buf11,
  FieldId::field_spi2_w12_buf12,
  FieldId::field_spi2_w13_buf13,
  FieldId::field_spi2_w14_buf14,
  FieldId::field_spi2_w15_buf15,
  FieldId::field_spi2_w2_buf2,
  FieldId::field_spi2_w3_buf3,
  FieldId::field_spi2_w4_buf4,
  FieldId::field_spi2_w5_buf5,
  FieldId::field_spi2_w6_buf6,
  FieldId::field_spi2_w7_buf7,
  FieldId::field_spi2_w8_buf8,
  FieldId::field_spi2_w9_buf9,
  FieldId::field_uart0_at_cmd_char_at_cmd_char,
  FieldId::field_uart0_at_cmd_char_char_num,
  FieldId::field_uart0_at_cmd_gaptout_rx_gap_tout,
  FieldId::field_uart0_at_cmd_postcnt_post_idle_num,
  FieldId::field_uart0_at_cmd_precnt_pre_idle_num,
  FieldId::field_uart0_clkdiv_clkdiv,
  FieldId::field_uart0_clkdiv_frag,
  FieldId::field_uart0_clk_conf_sclk_div_b,
  FieldId::field_uart0_clk_conf_sclk_div_a,
  FieldId::field_uart0_clk_conf_sclk_div_num,
  FieldId::field_uart0_clk_conf_sclk_sel,
  FieldId::field_uart0_clk_conf_sclk_en,
  FieldId::field_uart0_clk_conf_rst_core,
  FieldId::field_uart0_clk_conf_tx_sclk_en,
  FieldId::field_uart0_clk_conf_rx_sclk_en,
  FieldId::field_uart0_clk_conf_tx_rst_core,
  FieldId::field_uart0_clk_conf_rx_rst_core,
  FieldId::field_uart0_conf0_parity,
  FieldId::field_uart0_conf0_parity_en,
  FieldId::field_uart0_conf0_bit_num,
  FieldId::field_uart0_conf0_stop_bit_num,
  FieldId::field_uart0_conf0_sw_rts,
  FieldId::field_uart0_conf0_sw_dtr,
  FieldId::field_uart0_conf0_txd_brk,
  FieldId::field_uart0_conf0_irda_dplx,
  FieldId::field_uart0_conf0_irda_tx_en,
  FieldId::field_uart0_conf0_irda_wctl,
  FieldId::field_uart0_conf0_irda_tx_inv,
  FieldId::field_uart0_conf0_irda_rx_inv,
  FieldId::field_uart0_conf0_loopback,
  FieldId::field_uart0_conf0_tx_flow_en,
  FieldId::field_uart0_conf0_irda_en,
  FieldId::field_uart0_conf0_rxfifo_rst,
  FieldId::field_uart0_conf0_txfifo_rst,
  FieldId::field_uart0_conf0_rxd_inv,
  FieldId::field_uart0_conf0_cts_inv,
  FieldId::field_uart0_conf0_dsr_inv,
  FieldId::field_uart0_conf0_txd_inv,
  FieldId::field_uart0_conf0_rts_inv,
  FieldId::field_uart0_conf0_dtr_inv,
  FieldId::field_uart0_conf0_clk_en,
  FieldId::field_uart0_conf0_err_wr_mask,
  FieldId::field_uart0_conf0_autobaud_en,
  FieldId::field_uart0_conf0_mem_clk_en,
  FieldId::field_uart0_conf1_rxfifo_full_thrhd,
  FieldId::field_uart0_conf1_txfifo_empty_thrhd,
  FieldId::field_uart0_conf1_dis_rx_dat_ovf,
  FieldId::field_uart0_conf1_rx_tout_flow_dis,
  FieldId::field_uart0_conf1_rx_flow_en,
  FieldId::field_uart0_conf1_rx_tout_en,
  FieldId::field_uart0_date_date,
  FieldId::field_uart0_fifo_rxfifo_rd_byte,
  FieldId::field_uart0_flow_conf_sw_flow_con_en,
  FieldId::field_uart0_flow_conf_xonoff_del,
  FieldId::field_uart0_flow_conf_force_xon,
  FieldId::field_uart0_flow_conf_force_xoff,
  FieldId::field_uart0_flow_conf_send_xon,
  FieldId::field_uart0_flow_conf_send_xoff,
  FieldId::field_uart0_fsm_status_st_urx_out,
  FieldId::field_uart0_fsm_status_st_utx_out,
  FieldId::field_uart0_highpulse_min_cnt,
  FieldId::field_uart0_id_id,
  FieldId::field_uart0_id_high_speed,
  FieldId::field_uart0_id_reg_update,
  FieldId::field_uart0_idle_conf_rx_idle_thrhd,
  FieldId::field_uart0_idle_conf_tx_idle_num,
  FieldId::field_uart0_int_clr_rxfifo_full_int_clr,
  FieldId::field_uart0_int_clr_txfifo_empty_int_clr,
  FieldId::field_uart0_int_clr_parity_err_int_clr,
  FieldId::field_uart0_int_clr_frm_err_int_clr,
  FieldId::field_uart0_int_clr_rxfifo_ovf_int_clr,
  FieldId::field_uart0_int_clr_dsr_chg_int_clr,
  FieldId::field_uart0_int_clr_cts_chg_int_clr,
  FieldId::field_uart0_int_clr_brk_det_int_clr,
  FieldId::field_uart0_int_clr_rxfifo_tout_int_clr,
  FieldId::field_uart0_int_clr_sw_xon_int_clr,
  FieldId::field_uart0_int_clr_sw_xoff_int_clr,
  FieldId::field_uart0_int_clr_glitch_det_int_clr,
  FieldId::field_uart0_int_clr_tx_brk_done_int_clr,
  FieldId::field_uart0_int_clr_tx_brk_idle_done_int_clr,
  FieldId::field_uart0_int_clr_tx_done_int_clr,
  FieldId::field_uart0_int_clr_rs485_parity_err_int_clr,
  FieldId::field_uart0_int_clr_rs485_frm_err_int_clr,
  FieldId::field_uart0_int_clr_rs485_clash_int_clr,
  FieldId::field_uart0_int_clr_at_cmd_char_det_int_clr,
  FieldId::field_uart0_int_clr_wakeup_int_clr,
  FieldId::field_uart0_int_ena_rxfifo_full_int_ena,
  FieldId::field_uart0_int_ena_txfifo_empty_int_ena,
  FieldId::field_uart0_int_ena_parity_err_int_ena,
  FieldId::field_uart0_int_ena_frm_err_int_ena,
  FieldId::field_uart0_int_ena_rxfifo_ovf_int_ena,
  FieldId::field_uart0_int_ena_dsr_chg_int_ena,
  FieldId::field_uart0_int_ena_cts_chg_int_ena,
  FieldId::field_uart0_int_ena_brk_det_int_ena,
  FieldId::field_uart0_int_ena_rxfifo_tout_int_ena,
  FieldId::field_uart0_int_ena_sw_xon_int_ena,
  FieldId::field_uart0_int_ena_sw_xoff_int_ena,
  FieldId::field_uart0_int_ena_glitch_det_int_ena,
  FieldId::field_uart0_int_ena_tx_brk_done_int_ena,
  FieldId::field_uart0_int_ena_tx_brk_idle_done_int_ena,
  FieldId::field_uart0_int_ena_tx_done_int_ena,
  FieldId::field_uart0_int_ena_rs485_parity_err_int_ena,
  FieldId::field_uart0_int_ena_rs485_frm_err_int_ena,
  FieldId::field_uart0_int_ena_rs485_clash_int_ena,
  FieldId::field_uart0_int_ena_at_cmd_char_det_int_ena,
  FieldId::field_uart0_int_ena_wakeup_int_ena,
  FieldId::field_uart0_int_raw_rxfifo_full_int_raw,
  FieldId::field_uart0_int_raw_txfifo_empty_int_raw,
  FieldId::field_uart0_int_raw_parity_err_int_raw,
  FieldId::field_uart0_int_raw_frm_err_int_raw,
  FieldId::field_uart0_int_raw_rxfifo_ovf_int_raw,
  FieldId::field_uart0_int_raw_dsr_chg_int_raw,
  FieldId::field_uart0_int_raw_cts_chg_int_raw,
  FieldId::field_uart0_int_raw_brk_det_int_raw,
  FieldId::field_uart0_int_raw_rxfifo_tout_int_raw,
  FieldId::field_uart0_int_raw_sw_xon_int_raw,
  FieldId::field_uart0_int_raw_sw_xoff_int_raw,
  FieldId::field_uart0_int_raw_glitch_det_int_raw,
  FieldId::field_uart0_int_raw_tx_brk_done_int_raw,
  FieldId::field_uart0_int_raw_tx_brk_idle_done_int_raw,
  FieldId::field_uart0_int_raw_tx_done_int_raw,
  FieldId::field_uart0_int_raw_rs485_parity_err_int_raw,
  FieldId::field_uart0_int_raw_rs485_frm_err_int_raw,
  FieldId::field_uart0_int_raw_rs485_clash_int_raw,
  FieldId::field_uart0_int_raw_at_cmd_char_det_int_raw,
  FieldId::field_uart0_int_raw_wakeup_int_raw,
  FieldId::field_uart0_int_st_rxfifo_full_int_st,
  FieldId::field_uart0_int_st_txfifo_empty_int_st,
  FieldId::field_uart0_int_st_parity_err_int_st,
  FieldId::field_uart0_int_st_frm_err_int_st,
  FieldId::field_uart0_int_st_rxfifo_ovf_int_st,
  FieldId::field_uart0_int_st_dsr_chg_int_st,
  FieldId::field_uart0_int_st_cts_chg_int_st,
  FieldId::field_uart0_int_st_brk_det_int_st,
  FieldId::field_uart0_int_st_rxfifo_tout_int_st,
  FieldId::field_uart0_int_st_sw_xon_int_st,
  FieldId::field_uart0_int_st_sw_xoff_int_st,
  FieldId::field_uart0_int_st_glitch_det_int_st,
  FieldId::field_uart0_int_st_tx_brk_done_int_st,
  FieldId::field_uart0_int_st_tx_brk_idle_done_int_st,
  FieldId::field_uart0_int_st_tx_done_int_st,
  FieldId::field_uart0_int_st_rs485_parity_err_int_st,
  FieldId::field_uart0_int_st_rs485_frm_err_int_st,
  FieldId::field_uart0_int_st_rs485_clash_int_st,
  FieldId::field_uart0_int_st_at_cmd_char_det_int_st,
  FieldId::field_uart0_int_st_wakeup_int_st,
  FieldId::field_uart0_lowpulse_min_cnt,
  FieldId::field_uart0_mem_conf_rx_size,
  FieldId::field_uart0_mem_conf_tx_size,
  FieldId::field_uart0_mem_conf_rx_flow_thrhd,
  FieldId::field_uart0_mem_conf_rx_tout_thrhd,
  FieldId::field_uart0_mem_conf_mem_force_pd,
  FieldId::field_uart0_mem_conf_mem_force_pu,
  FieldId::field_uart0_mem_rx_status_apb_rx_raddr,
  FieldId::field_uart0_mem_rx_status_rx_waddr,
  FieldId::field_uart0_mem_tx_status_apb_tx_waddr,
  FieldId::field_uart0_mem_tx_status_tx_raddr,
  FieldId::field_uart0_negpulse_negedge_min_cnt,
  FieldId::field_uart0_pospulse_posedge_min_cnt,
  FieldId::field_uart0_rs485_conf_rs485_en,
  FieldId::field_uart0_rs485_conf_dl0_en,
  FieldId::field_uart0_rs485_conf_dl1_en,
  FieldId::field_uart0_rs485_conf_rs485tx_rx_en,
  FieldId::field_uart0_rs485_conf_rs485rxby_tx_en,
  FieldId::field_uart0_rs485_conf_rs485_rx_dly_num,
  FieldId::field_uart0_rs485_conf_rs485_tx_dly_num,
  FieldId::field_uart0_rxd_cnt_rxd_edge_cnt,
  FieldId::field_uart0_rx_filt_glitch_filt,
  FieldId::field_uart0_rx_filt_glitch_filt_en,
  FieldId::field_uart0_sleep_conf_active_threshold,
  FieldId::field_uart0_status_rxfifo_cnt,
  FieldId::field_uart0_status_dsrn,
  FieldId::field_uart0_status_ctsn,
  FieldId::field_uart0_status_rxd,
  FieldId::field_uart0_status_txfifo_cnt,
  FieldId::field_uart0_status_dtrn,
  FieldId::field_uart0_status_rtsn,
  FieldId::field_uart0_status_txd,
  FieldId::field_uart0_swfc_conf0_xoff_threshold,
  FieldId::field_uart0_swfc_conf0_xoff_char,
  FieldId::field_uart0_swfc_conf1_xon_threshold,
  FieldId::field_uart0_swfc_conf1_xon_char,
  FieldId::field_uart0_txbrk_conf_tx_brk_num,
  FieldId::field_uart1_at_cmd_char_at_cmd_char,
  FieldId::field_uart1_at_cmd_char_char_num,
  FieldId::field_uart1_at_cmd_gaptout_rx_gap_tout,
  FieldId::field_uart1_at_cmd_postcnt_post_idle_num,
  FieldId::field_uart1_at_cmd_precnt_pre_idle_num,
  FieldId::field_uart1_clkdiv_clkdiv,
  FieldId::field_uart1_clkdiv_frag,
  FieldId::field_uart1_clk_conf_sclk_div_b,
  FieldId::field_uart1_clk_conf_sclk_div_a,
  FieldId::field_uart1_clk_conf_sclk_div_num,
  FieldId::field_uart1_clk_conf_sclk_sel,
  FieldId::field_uart1_clk_conf_sclk_en,
  FieldId::field_uart1_clk_conf_rst_core,
  FieldId::field_uart1_clk_conf_tx_sclk_en,
  FieldId::field_uart1_clk_conf_rx_sclk_en,
  FieldId::field_uart1_clk_conf_tx_rst_core,
  FieldId::field_uart1_clk_conf_rx_rst_core,
  FieldId::field_uart1_conf0_parity,
  FieldId::field_uart1_conf0_parity_en,
  FieldId::field_uart1_conf0_bit_num,
  FieldId::field_uart1_conf0_stop_bit_num,
  FieldId::field_uart1_conf0_sw_rts,
  FieldId::field_uart1_conf0_sw_dtr,
  FieldId::field_uart1_conf0_txd_brk,
  FieldId::field_uart1_conf0_irda_dplx,
  FieldId::field_uart1_conf0_irda_tx_en,
  FieldId::field_uart1_conf0_irda_wctl,
  FieldId::field_uart1_conf0_irda_tx_inv,
  FieldId::field_uart1_conf0_irda_rx_inv,
  FieldId::field_uart1_conf0_loopback,
  FieldId::field_uart1_conf0_tx_flow_en,
  FieldId::field_uart1_conf0_irda_en,
  FieldId::field_uart1_conf0_rxfifo_rst,
  FieldId::field_uart1_conf0_txfifo_rst,
  FieldId::field_uart1_conf0_rxd_inv,
  FieldId::field_uart1_conf0_cts_inv,
  FieldId::field_uart1_conf0_dsr_inv,
  FieldId::field_uart1_conf0_txd_inv,
  FieldId::field_uart1_conf0_rts_inv,
  FieldId::field_uart1_conf0_dtr_inv,
  FieldId::field_uart1_conf0_clk_en,
  FieldId::field_uart1_conf0_err_wr_mask,
  FieldId::field_uart1_conf0_autobaud_en,
  FieldId::field_uart1_conf0_mem_clk_en,
  FieldId::field_uart1_conf1_rxfifo_full_thrhd,
  FieldId::field_uart1_conf1_txfifo_empty_thrhd,
  FieldId::field_uart1_conf1_dis_rx_dat_ovf,
  FieldId::field_uart1_conf1_rx_tout_flow_dis,
  FieldId::field_uart1_conf1_rx_flow_en,
  FieldId::field_uart1_conf1_rx_tout_en,
  FieldId::field_uart1_date_date,
  FieldId::field_uart1_fifo_rxfifo_rd_byte,
  FieldId::field_uart1_flow_conf_sw_flow_con_en,
  FieldId::field_uart1_flow_conf_xonoff_del,
  FieldId::field_uart1_flow_conf_force_xon,
  FieldId::field_uart1_flow_conf_force_xoff,
  FieldId::field_uart1_flow_conf_send_xon,
  FieldId::field_uart1_flow_conf_send_xoff,
  FieldId::field_uart1_fsm_status_st_urx_out,
  FieldId::field_uart1_fsm_status_st_utx_out,
  FieldId::field_uart1_highpulse_min_cnt,
  FieldId::field_uart1_id_id,
  FieldId::field_uart1_id_high_speed,
  FieldId::field_uart1_id_reg_update,
  FieldId::field_uart1_idle_conf_rx_idle_thrhd,
  FieldId::field_uart1_idle_conf_tx_idle_num,
  FieldId::field_uart1_int_clr_rxfifo_full_int_clr,
  FieldId::field_uart1_int_clr_txfifo_empty_int_clr,
  FieldId::field_uart1_int_clr_parity_err_int_clr,
  FieldId::field_uart1_int_clr_frm_err_int_clr,
  FieldId::field_uart1_int_clr_rxfifo_ovf_int_clr,
  FieldId::field_uart1_int_clr_dsr_chg_int_clr,
  FieldId::field_uart1_int_clr_cts_chg_int_clr,
  FieldId::field_uart1_int_clr_brk_det_int_clr,
  FieldId::field_uart1_int_clr_rxfifo_tout_int_clr,
  FieldId::field_uart1_int_clr_sw_xon_int_clr,
  FieldId::field_uart1_int_clr_sw_xoff_int_clr,
  FieldId::field_uart1_int_clr_glitch_det_int_clr,
  FieldId::field_uart1_int_clr_tx_brk_done_int_clr,
  FieldId::field_uart1_int_clr_tx_brk_idle_done_int_clr,
  FieldId::field_uart1_int_clr_tx_done_int_clr,
  FieldId::field_uart1_int_clr_rs485_parity_err_int_clr,
  FieldId::field_uart1_int_clr_rs485_frm_err_int_clr,
  FieldId::field_uart1_int_clr_rs485_clash_int_clr,
  FieldId::field_uart1_int_clr_at_cmd_char_det_int_clr,
  FieldId::field_uart1_int_clr_wakeup_int_clr,
  FieldId::field_uart1_int_ena_rxfifo_full_int_ena,
  FieldId::field_uart1_int_ena_txfifo_empty_int_ena,
  FieldId::field_uart1_int_ena_parity_err_int_ena,
  FieldId::field_uart1_int_ena_frm_err_int_ena,
  FieldId::field_uart1_int_ena_rxfifo_ovf_int_ena,
  FieldId::field_uart1_int_ena_dsr_chg_int_ena,
  FieldId::field_uart1_int_ena_cts_chg_int_ena,
  FieldId::field_uart1_int_ena_brk_det_int_ena,
  FieldId::field_uart1_int_ena_rxfifo_tout_int_ena,
  FieldId::field_uart1_int_ena_sw_xon_int_ena,
  FieldId::field_uart1_int_ena_sw_xoff_int_ena,
  FieldId::field_uart1_int_ena_glitch_det_int_ena,
  FieldId::field_uart1_int_ena_tx_brk_done_int_ena,
  FieldId::field_uart1_int_ena_tx_brk_idle_done_int_ena,
  FieldId::field_uart1_int_ena_tx_done_int_ena,
  FieldId::field_uart1_int_ena_rs485_parity_err_int_ena,
  FieldId::field_uart1_int_ena_rs485_frm_err_int_ena,
  FieldId::field_uart1_int_ena_rs485_clash_int_ena,
  FieldId::field_uart1_int_ena_at_cmd_char_det_int_ena,
  FieldId::field_uart1_int_ena_wakeup_int_ena,
  FieldId::field_uart1_int_raw_rxfifo_full_int_raw,
  FieldId::field_uart1_int_raw_txfifo_empty_int_raw,
  FieldId::field_uart1_int_raw_parity_err_int_raw,
  FieldId::field_uart1_int_raw_frm_err_int_raw,
  FieldId::field_uart1_int_raw_rxfifo_ovf_int_raw,
  FieldId::field_uart1_int_raw_dsr_chg_int_raw,
  FieldId::field_uart1_int_raw_cts_chg_int_raw,
  FieldId::field_uart1_int_raw_brk_det_int_raw,
  FieldId::field_uart1_int_raw_rxfifo_tout_int_raw,
  FieldId::field_uart1_int_raw_sw_xon_int_raw,
  FieldId::field_uart1_int_raw_sw_xoff_int_raw,
  FieldId::field_uart1_int_raw_glitch_det_int_raw,
  FieldId::field_uart1_int_raw_tx_brk_done_int_raw,
  FieldId::field_uart1_int_raw_tx_brk_idle_done_int_raw,
  FieldId::field_uart1_int_raw_tx_done_int_raw,
  FieldId::field_uart1_int_raw_rs485_parity_err_int_raw,
  FieldId::field_uart1_int_raw_rs485_frm_err_int_raw,
  FieldId::field_uart1_int_raw_rs485_clash_int_raw,
  FieldId::field_uart1_int_raw_at_cmd_char_det_int_raw,
  FieldId::field_uart1_int_raw_wakeup_int_raw,
  FieldId::field_uart1_int_st_rxfifo_full_int_st,
  FieldId::field_uart1_int_st_txfifo_empty_int_st,
  FieldId::field_uart1_int_st_parity_err_int_st,
  FieldId::field_uart1_int_st_frm_err_int_st,
  FieldId::field_uart1_int_st_rxfifo_ovf_int_st,
  FieldId::field_uart1_int_st_dsr_chg_int_st,
  FieldId::field_uart1_int_st_cts_chg_int_st,
  FieldId::field_uart1_int_st_brk_det_int_st,
  FieldId::field_uart1_int_st_rxfifo_tout_int_st,
  FieldId::field_uart1_int_st_sw_xon_int_st,
  FieldId::field_uart1_int_st_sw_xoff_int_st,
  FieldId::field_uart1_int_st_glitch_det_int_st,
  FieldId::field_uart1_int_st_tx_brk_done_int_st,
  FieldId::field_uart1_int_st_tx_brk_idle_done_int_st,
  FieldId::field_uart1_int_st_tx_done_int_st,
  FieldId::field_uart1_int_st_rs485_parity_err_int_st,
  FieldId::field_uart1_int_st_rs485_frm_err_int_st,
  FieldId::field_uart1_int_st_rs485_clash_int_st,
  FieldId::field_uart1_int_st_at_cmd_char_det_int_st,
  FieldId::field_uart1_int_st_wakeup_int_st,
  FieldId::field_uart1_lowpulse_min_cnt,
  FieldId::field_uart1_mem_conf_rx_size,
  FieldId::field_uart1_mem_conf_tx_size,
  FieldId::field_uart1_mem_conf_rx_flow_thrhd,
  FieldId::field_uart1_mem_conf_rx_tout_thrhd,
  FieldId::field_uart1_mem_conf_mem_force_pd,
  FieldId::field_uart1_mem_conf_mem_force_pu,
  FieldId::field_uart1_mem_rx_status_apb_rx_raddr,
  FieldId::field_uart1_mem_rx_status_rx_waddr,
  FieldId::field_uart1_mem_tx_status_apb_tx_waddr,
  FieldId::field_uart1_mem_tx_status_tx_raddr,
  FieldId::field_uart1_negpulse_negedge_min_cnt,
  FieldId::field_uart1_pospulse_posedge_min_cnt,
  FieldId::field_uart1_rs485_conf_rs485_en,
  FieldId::field_uart1_rs485_conf_dl0_en,
  FieldId::field_uart1_rs485_conf_dl1_en,
  FieldId::field_uart1_rs485_conf_rs485tx_rx_en,
  FieldId::field_uart1_rs485_conf_rs485rxby_tx_en,
  FieldId::field_uart1_rs485_conf_rs485_rx_dly_num,
  FieldId::field_uart1_rs485_conf_rs485_tx_dly_num,
  FieldId::field_uart1_rxd_cnt_rxd_edge_cnt,
  FieldId::field_uart1_rx_filt_glitch_filt,
  FieldId::field_uart1_rx_filt_glitch_filt_en,
  FieldId::field_uart1_sleep_conf_active_threshold,
  FieldId::field_uart1_status_rxfifo_cnt,
  FieldId::field_uart1_status_dsrn,
  FieldId::field_uart1_status_ctsn,
  FieldId::field_uart1_status_rxd,
  FieldId::field_uart1_status_txfifo_cnt,
  FieldId::field_uart1_status_dtrn,
  FieldId::field_uart1_status_rtsn,
  FieldId::field_uart1_status_txd,
  FieldId::field_uart1_swfc_conf0_xoff_threshold,
  FieldId::field_uart1_swfc_conf0_xoff_char,
  FieldId::field_uart1_swfc_conf1_xon_threshold,
  FieldId::field_uart1_swfc_conf1_xon_char,
  FieldId::field_uart1_txbrk_conf_tx_brk_num,
}};
}
}
}
}
}
}
