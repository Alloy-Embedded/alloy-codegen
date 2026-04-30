#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "registers.hpp"

namespace espressif {
namespace esp32 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32 {
enum class FieldId : std::uint16_t {
  none,
  field_dport_perip_clk_en_spi01_clk_en,
  field_dport_perip_clk_en_uart_clk_en,
  field_dport_perip_clk_en_i2c0_ext0_clk_en,
  field_gpio_acpu_int_appcpu_int,
  field_gpio_acpu_int1_appcpu_int_h,
  field_gpio_acpu_nmi_int_appcpu_nmi_int,
  field_gpio_acpu_nmi_int1_appcpu_nmi_int_h,
  field_gpio_bt_select_bt_sel,
  field_gpio_cpusdio_int_sdio_int,
  field_gpio_cpusdio_int1_sdio_int_h,
  field_gpio_cpusdio_int1_pin_pad_driver,
  field_gpio_cpusdio_int1_pin_int_type,
  field_gpio_cpusdio_int1_pin_wakeup_enable,
  field_gpio_cpusdio_int1_pin_config,
  field_gpio_cpusdio_int1_pin_int_ena,
  field_gpio_enable_data,
  field_gpio_enable1_data,
  field_gpio_enable1_w1tc_enable1_data_w1tc,
  field_gpio_enable1_w1ts_enable1_data_w1ts,
  field_gpio_enable_w1tc_enable_data_w1tc,
  field_gpio_enable_w1ts_enable_data_w1ts,
  field_gpio_func_s_in_sel_cfg_in_sel,
  field_gpio_func_s_in_sel_cfg_in_inv_sel,
  field_gpio_func_s_in_sel_cfg_sel,
  field_gpio_func_s_out_sel_cfg_out_sel,
  field_gpio_func_s_out_sel_cfg_inv_sel,
  field_gpio_func_s_out_sel_cfg_oen_sel,
  field_gpio_func_s_out_sel_cfg_oen_inv_sel,
  field_gpio_in_data_next,
  field_gpio_in1_data_next,
  field_gpio_out_data,
  field_gpio_out1_data,
  field_gpio_out1_w1tc_out1_data_w1tc,
  field_gpio_out1_w1ts_out1_data_w1ts,
  field_gpio_out_w1tc_out_data_w1tc,
  field_gpio_out_w1ts_out_data_w1ts,
  field_gpio_pcpu_int_procpu_int,
  field_gpio_pcpu_int1_procpu_int_h,
  field_gpio_pcpu_nmi_int_procpu_nmi_int,
  field_gpio_pcpu_nmi_int1_procpu_nmi_int_h,
  field_gpio_pin_s_pad_driver,
  field_gpio_pin_s_int_type,
  field_gpio_pin_s_wakeup_enable,
  field_gpio_pin_s_config,
  field_gpio_pin_s_int_ena,
  field_gpio_sdio_select_sdio_sel,
  field_gpio_status_int,
  field_gpio_status1_int,
  field_gpio_status1_w1tc_status1_int_w1tc,
  field_gpio_status1_w1ts_status1_int_w1ts,
  field_gpio_status_w1tc_status_int_w1tc,
  field_gpio_status_w1ts_status_int_w1ts,
  field_gpio_strap_strapping,
  field_gpio_cali_conf_cali_rtc_max,
  field_gpio_cali_conf_cali_start,
  field_gpio_cali_data_cali_value_sync2,
  field_gpio_cali_data_cali_rdy_real,
  field_gpio_cali_data_cali_rdy_sync2,
  field_i2c0_comd_s_command,
  field_i2c0_comd_s_command_done,
  field_i2c0_ctr_sda_force_out,
  field_i2c0_ctr_scl_force_out,
  field_i2c0_ctr_sample_scl_level,
  field_i2c0_ctr_ms_mode,
  field_i2c0_ctr_trans_start,
  field_i2c0_ctr_tx_lsb_first,
  field_i2c0_ctr_rx_lsb_first,
  field_i2c0_ctr_clk_en,
  field_i2c0_data_fifo_rdata,
  field_i2c0_date_date,
  field_i2c0_fifo_conf_rxfifo_full_thrhd,
  field_i2c0_fifo_conf_txfifo_empty_thrhd,
  field_i2c0_fifo_conf_nonfifo_en,
  field_i2c0_fifo_conf_fifo_addr_cfg_en,
  field_i2c0_fifo_conf_rx_fifo_rst,
  field_i2c0_fifo_conf_tx_fifo_rst,
  field_i2c0_fifo_conf_nonfifo_rx_thres,
  field_i2c0_fifo_conf_nonfifo_tx_thres,
  field_i2c0_int_clr_rxfifo_full_int_clr,
  field_i2c0_int_clr_txfifo_empty_int_clr,
  field_i2c0_int_clr_rxfifo_ovf_int_clr,
  field_i2c0_int_clr_end_detect_int_clr,
  field_i2c0_int_clr_slave_tran_comp_int_clr,
  field_i2c0_int_clr_arbitration_lost_int_clr,
  field_i2c0_int_clr_master_tran_comp_int_clr,
  field_i2c0_int_clr_trans_complete_int_clr,
  field_i2c0_int_clr_time_out_int_clr,
  field_i2c0_int_clr_trans_start_int_clr,
  field_i2c0_int_clr_ack_err_int_clr,
  field_i2c0_int_clr_rx_rec_full_int_clr,
  field_i2c0_int_clr_tx_send_empty_int_clr,
  field_i2c0_int_ena_rxfifo_full_int_ena,
  field_i2c0_int_ena_txfifo_empty_int_ena,
  field_i2c0_int_ena_rxfifo_ovf_int_ena,
  field_i2c0_int_ena_end_detect_int_ena,
  field_i2c0_int_ena_slave_tran_comp_int_ena,
  field_i2c0_int_ena_arbitration_lost_int_ena,
  field_i2c0_int_ena_master_tran_comp_int_ena,
  field_i2c0_int_ena_trans_complete_int_ena,
  field_i2c0_int_ena_time_out_int_ena,
  field_i2c0_int_ena_trans_start_int_ena,
  field_i2c0_int_ena_ack_err_int_ena,
  field_i2c0_int_ena_rx_rec_full_int_ena,
  field_i2c0_int_ena_tx_send_empty_int_ena,
  field_i2c0_int_raw_rxfifo_full_int_raw,
  field_i2c0_int_raw_txfifo_empty_int_raw,
  field_i2c0_int_raw_rxfifo_ovf_int_raw,
  field_i2c0_int_raw_end_detect_int_raw,
  field_i2c0_int_raw_slave_tran_comp_int_raw,
  field_i2c0_int_raw_arbitration_lost_int_raw,
  field_i2c0_int_raw_master_tran_comp_int_raw,
  field_i2c0_int_raw_trans_complete_int_raw,
  field_i2c0_int_raw_time_out_int_raw,
  field_i2c0_int_raw_trans_start_int_raw,
  field_i2c0_int_raw_ack_err_int_raw,
  field_i2c0_int_raw_rx_rec_full_int_raw,
  field_i2c0_int_raw_tx_send_empty_int_raw,
  field_i2c0_int_status_rxfifo_full_int_st,
  field_i2c0_int_status_txfifo_empty_int_st,
  field_i2c0_int_status_rxfifo_ovf_int_st,
  field_i2c0_int_status_end_detect_int_st,
  field_i2c0_int_status_slave_tran_comp_int_st,
  field_i2c0_int_status_arbitration_lost_int_st,
  field_i2c0_int_status_master_tran_comp_int_st,
  field_i2c0_int_status_trans_complete_int_st,
  field_i2c0_int_status_time_out_int_st,
  field_i2c0_int_status_trans_start_int_st,
  field_i2c0_int_status_ack_err_int_st,
  field_i2c0_int_status_rx_rec_full_int_st,
  field_i2c0_int_status_tx_send_empty_int_st,
  field_i2c0_rxfifo_st_rxfifo_start_addr,
  field_i2c0_rxfifo_st_rxfifo_end_addr,
  field_i2c0_rxfifo_st_txfifo_start_addr,
  field_i2c0_rxfifo_st_txfifo_end_addr,
  field_i2c0_scl_filter_cfg_scl_filter_thres,
  field_i2c0_scl_filter_cfg_scl_filter_en,
  field_i2c0_scl_high_period_scl_high_period,
  field_i2c0_scl_low_period_scl_low_period,
  field_i2c0_scl_rstart_setup_time,
  field_i2c0_scl_start_hold_time,
  field_i2c0_scl_stop_hold_time,
  field_i2c0_scl_stop_setup_time,
  field_i2c0_sda_filter_cfg_sda_filter_thres,
  field_i2c0_sda_filter_cfg_sda_filter_en,
  field_i2c0_sda_hold_time,
  field_i2c0_sda_sample_time,
  field_i2c0_slave_addr_slave_addr,
  field_i2c0_slave_addr_addr_10bit_en,
  field_i2c0_sr_ack_rec,
  field_i2c0_sr_slave_rw,
  field_i2c0_sr_time_out,
  field_i2c0_sr_arb_lost,
  field_i2c0_sr_bus_busy,
  field_i2c0_sr_slave_addressed,
  field_i2c0_sr_byte_trans,
  field_i2c0_sr_rxfifo_cnt,
  field_i2c0_sr_txfifo_cnt,
  field_i2c0_sr_scl_main_state_last,
  field_i2c0_sr_scl_state_last,
  field_i2c0_to_time_out,
  field_i2c1_comd_s_command,
  field_i2c1_comd_s_command_done,
  field_i2c1_ctr_sda_force_out,
  field_i2c1_ctr_scl_force_out,
  field_i2c1_ctr_sample_scl_level,
  field_i2c1_ctr_ms_mode,
  field_i2c1_ctr_trans_start,
  field_i2c1_ctr_tx_lsb_first,
  field_i2c1_ctr_rx_lsb_first,
  field_i2c1_ctr_clk_en,
  field_i2c1_data_fifo_rdata,
  field_i2c1_date_date,
  field_i2c1_fifo_conf_rxfifo_full_thrhd,
  field_i2c1_fifo_conf_txfifo_empty_thrhd,
  field_i2c1_fifo_conf_nonfifo_en,
  field_i2c1_fifo_conf_fifo_addr_cfg_en,
  field_i2c1_fifo_conf_rx_fifo_rst,
  field_i2c1_fifo_conf_tx_fifo_rst,
  field_i2c1_fifo_conf_nonfifo_rx_thres,
  field_i2c1_fifo_conf_nonfifo_tx_thres,
  field_i2c1_int_clr_rxfifo_full_int_clr,
  field_i2c1_int_clr_txfifo_empty_int_clr,
  field_i2c1_int_clr_rxfifo_ovf_int_clr,
  field_i2c1_int_clr_end_detect_int_clr,
  field_i2c1_int_clr_slave_tran_comp_int_clr,
  field_i2c1_int_clr_arbitration_lost_int_clr,
  field_i2c1_int_clr_master_tran_comp_int_clr,
  field_i2c1_int_clr_trans_complete_int_clr,
  field_i2c1_int_clr_time_out_int_clr,
  field_i2c1_int_clr_trans_start_int_clr,
  field_i2c1_int_clr_ack_err_int_clr,
  field_i2c1_int_clr_rx_rec_full_int_clr,
  field_i2c1_int_clr_tx_send_empty_int_clr,
  field_i2c1_int_ena_rxfifo_full_int_ena,
  field_i2c1_int_ena_txfifo_empty_int_ena,
  field_i2c1_int_ena_rxfifo_ovf_int_ena,
  field_i2c1_int_ena_end_detect_int_ena,
  field_i2c1_int_ena_slave_tran_comp_int_ena,
  field_i2c1_int_ena_arbitration_lost_int_ena,
  field_i2c1_int_ena_master_tran_comp_int_ena,
  field_i2c1_int_ena_trans_complete_int_ena,
  field_i2c1_int_ena_time_out_int_ena,
  field_i2c1_int_ena_trans_start_int_ena,
  field_i2c1_int_ena_ack_err_int_ena,
  field_i2c1_int_ena_rx_rec_full_int_ena,
  field_i2c1_int_ena_tx_send_empty_int_ena,
  field_i2c1_int_raw_rxfifo_full_int_raw,
  field_i2c1_int_raw_txfifo_empty_int_raw,
  field_i2c1_int_raw_rxfifo_ovf_int_raw,
  field_i2c1_int_raw_end_detect_int_raw,
  field_i2c1_int_raw_slave_tran_comp_int_raw,
  field_i2c1_int_raw_arbitration_lost_int_raw,
  field_i2c1_int_raw_master_tran_comp_int_raw,
  field_i2c1_int_raw_trans_complete_int_raw,
  field_i2c1_int_raw_time_out_int_raw,
  field_i2c1_int_raw_trans_start_int_raw,
  field_i2c1_int_raw_ack_err_int_raw,
  field_i2c1_int_raw_rx_rec_full_int_raw,
  field_i2c1_int_raw_tx_send_empty_int_raw,
  field_i2c1_int_status_rxfifo_full_int_st,
  field_i2c1_int_status_txfifo_empty_int_st,
  field_i2c1_int_status_rxfifo_ovf_int_st,
  field_i2c1_int_status_end_detect_int_st,
  field_i2c1_int_status_slave_tran_comp_int_st,
  field_i2c1_int_status_arbitration_lost_int_st,
  field_i2c1_int_status_master_tran_comp_int_st,
  field_i2c1_int_status_trans_complete_int_st,
  field_i2c1_int_status_time_out_int_st,
  field_i2c1_int_status_trans_start_int_st,
  field_i2c1_int_status_ack_err_int_st,
  field_i2c1_int_status_rx_rec_full_int_st,
  field_i2c1_int_status_tx_send_empty_int_st,
  field_i2c1_rxfifo_st_rxfifo_start_addr,
  field_i2c1_rxfifo_st_rxfifo_end_addr,
  field_i2c1_rxfifo_st_txfifo_start_addr,
  field_i2c1_rxfifo_st_txfifo_end_addr,
  field_i2c1_scl_filter_cfg_scl_filter_thres,
  field_i2c1_scl_filter_cfg_scl_filter_en,
  field_i2c1_scl_high_period_scl_high_period,
  field_i2c1_scl_low_period_scl_low_period,
  field_i2c1_scl_rstart_setup_time,
  field_i2c1_scl_start_hold_time,
  field_i2c1_scl_stop_hold_time,
  field_i2c1_scl_stop_setup_time,
  field_i2c1_sda_filter_cfg_sda_filter_thres,
  field_i2c1_sda_filter_cfg_sda_filter_en,
  field_i2c1_sda_hold_time,
  field_i2c1_sda_sample_time,
  field_i2c1_slave_addr_slave_addr,
  field_i2c1_slave_addr_addr_10bit_en,
  field_i2c1_sr_ack_rec,
  field_i2c1_sr_slave_rw,
  field_i2c1_sr_time_out,
  field_i2c1_sr_arb_lost,
  field_i2c1_sr_bus_busy,
  field_i2c1_sr_slave_addressed,
  field_i2c1_sr_byte_trans,
  field_i2c1_sr_rxfifo_cnt,
  field_i2c1_sr_txfifo_cnt,
  field_i2c1_sr_scl_main_state_last,
  field_i2c1_sr_scl_state_last,
  field_i2c1_to_time_out,
  field_sens_sardate_sar_date,
  field_sens_sar_atten1_sar1_atten,
  field_sens_sar_atten2_sar2_atten,
  field_sens_sar_dac_ctrl1_sw_fstep,
  field_sens_sar_dac_ctrl1_sw_tone_en,
  field_sens_sar_dac_ctrl1_debug_bit_sel,
  field_sens_sar_dac_ctrl1_dac_dig_force,
  field_sens_sar_dac_ctrl1_dac_clk_force_low,
  field_sens_sar_dac_ctrl1_dac_clk_force_high,
  field_sens_sar_dac_ctrl1_dac_clk_inv,
  field_sens_sar_dac_ctrl2_dac_dc1,
  field_sens_sar_dac_ctrl2_dac_dc2,
  field_sens_sar_dac_ctrl2_dac_scale1,
  field_sens_sar_dac_ctrl2_dac_scale2,
  field_sens_sar_dac_ctrl2_dac_inv1,
  field_sens_sar_dac_ctrl2_dac_inv2,
  field_sens_sar_dac_ctrl2_dac_cw_en1,
  field_sens_sar_dac_ctrl2_dac_cw_en2,
  field_sens_sar_i2c_ctrl_sar_i2c_ctrl,
  field_sens_sar_i2c_ctrl_sar_i2c_start,
  field_sens_sar_i2c_ctrl_sar_i2c_start_force,
  field_sens_sar_meas_ctrl_xpd_sar_amp_fsm,
  field_sens_sar_meas_ctrl_amp_rst_fb_fsm,
  field_sens_sar_meas_ctrl_amp_short_ref_fsm,
  field_sens_sar_meas_ctrl_amp_short_ref_gnd_fsm,
  field_sens_sar_meas_ctrl_xpd_sar_fsm,
  field_sens_sar_meas_ctrl_sar_rstb_fsm,
  field_sens_sar_meas_ctrl_sar2_xpd_wait,
  field_sens_sar_meas_ctrl2_sar1_dac_xpd_fsm,
  field_sens_sar_meas_ctrl2_sar1_dac_xpd_fsm_idle,
  field_sens_sar_meas_ctrl2_xpd_sar_amp_fsm_idle,
  field_sens_sar_meas_ctrl2_amp_rst_fb_fsm_idle,
  field_sens_sar_meas_ctrl2_amp_short_ref_fsm_idle,
  field_sens_sar_meas_ctrl2_amp_short_ref_gnd_fsm_idle,
  field_sens_sar_meas_ctrl2_xpd_sar_fsm_idle,
  field_sens_sar_meas_ctrl2_sar_rstb_fsm_idle,
  field_sens_sar_meas_ctrl2_sar2_rstb_force,
  field_sens_sar_meas_ctrl2_amp_rst_fb_force,
  field_sens_sar_meas_ctrl2_amp_short_ref_force,
  field_sens_sar_meas_ctrl2_amp_short_ref_gnd_force,
  field_sens_sar_meas_start1_meas1_data_sar,
  field_sens_sar_meas_start1_meas1_done_sar,
  field_sens_sar_meas_start1_meas1_start_sar,
  field_sens_sar_meas_start1_meas1_start_force,
  field_sens_sar_meas_start1_sar1_en_pad,
  field_sens_sar_meas_start1_sar1_en_pad_force,
  field_sens_sar_meas_start2_meas2_data_sar,
  field_sens_sar_meas_start2_meas2_done_sar,
  field_sens_sar_meas_start2_meas2_start_sar,
  field_sens_sar_meas_start2_meas2_start_force,
  field_sens_sar_meas_start2_sar2_en_pad,
  field_sens_sar_meas_start2_sar2_en_pad_force,
  field_sens_sar_meas_wait1_sar_amp_wait1,
  field_sens_sar_meas_wait1_sar_amp_wait2,
  field_sens_sar_meas_wait2_force_xpd_sar_sw,
  field_sens_sar_meas_wait2_sar_amp_wait3,
  field_sens_sar_meas_wait2_force_xpd_amp,
  field_sens_sar_meas_wait2_force_xpd_sar,
  field_sens_sar_meas_wait2_sar2_rstb_wait,
  field_sens_sar_mem_wr_ctrl_mem_wr_addr_init,
  field_sens_sar_mem_wr_ctrl_mem_wr_addr_size,
  field_sens_sar_mem_wr_ctrl_rtc_mem_wr_offst_clr,
  field_sens_sar_nouse_sar_nouse,
  field_sens_sar_read_ctrl_sar1_clk_div,
  field_sens_sar_read_ctrl_sar1_sample_cycle,
  field_sens_sar_read_ctrl_sar1_sample_bit,
  field_sens_sar_read_ctrl_sar1_clk_gated,
  field_sens_sar_read_ctrl_sar1_sample_num,
  field_sens_sar_read_ctrl_sar1_dig_force,
  field_sens_sar_read_ctrl_sar1_data_inv,
  field_sens_sar_read_ctrl2_sar2_clk_div,
  field_sens_sar_read_ctrl2_sar2_sample_cycle,
  field_sens_sar_read_ctrl2_sar2_sample_bit,
  field_sens_sar_read_ctrl2_sar2_clk_gated,
  field_sens_sar_read_ctrl2_sar2_sample_num,
  field_sens_sar_read_ctrl2_sar2_pwdet_force,
  field_sens_sar_read_ctrl2_sar2_dig_force,
  field_sens_sar_read_ctrl2_sar2_data_inv,
  field_sens_sar_read_status1_sar1_reader_status,
  field_sens_sar_read_status2_sar2_reader_status,
  field_sens_sar_slave_addr1_i2c_slave_addr1,
  field_sens_sar_slave_addr1_i2c_slave_addr0,
  field_sens_sar_slave_addr1_meas_status,
  field_sens_sar_slave_addr2_i2c_slave_addr3,
  field_sens_sar_slave_addr2_i2c_slave_addr2,
  field_sens_sar_slave_addr3_i2c_slave_addr5,
  field_sens_sar_slave_addr3_i2c_slave_addr4,
  field_sens_sar_slave_addr3_tsens_out,
  field_sens_sar_slave_addr3_tsens_rdy_out,
  field_sens_sar_slave_addr4_i2c_slave_addr7,
  field_sens_sar_slave_addr4_i2c_slave_addr6,
  field_sens_sar_slave_addr4_i2c_rdata,
  field_sens_sar_slave_addr4_i2c_done,
  field_sens_sar_start_force_sar1_bit_width,
  field_sens_sar_start_force_sar2_bit_width,
  field_sens_sar_start_force_sar2_en_test,
  field_sens_sar_start_force_sar2_pwdet_cct,
  field_sens_sar_start_force_ulp_cp_force_start_top,
  field_sens_sar_start_force_ulp_cp_start_top,
  field_sens_sar_start_force_sarclk_en,
  field_sens_sar_start_force_pc_init,
  field_sens_sar_start_force_sar2_stop,
  field_sens_sar_start_force_sar1_stop,
  field_sens_sar_start_force_sar2_pwdet_en,
  field_sens_sar_touch_ctrl1_touch_meas_delay,
  field_sens_sar_touch_ctrl1_touch_xpd_wait,
  field_sens_sar_touch_ctrl1_touch_out_sel,
  field_sens_sar_touch_ctrl1_touch_out_1en,
  field_sens_sar_touch_ctrl1_xpd_hall_force,
  field_sens_sar_touch_ctrl1_hall_phase_force,
  field_sens_sar_touch_ctrl2_touch_meas_en,
  field_sens_sar_touch_ctrl2_touch_meas_done,
  field_sens_sar_touch_ctrl2_touch_start_fsm_en,
  field_sens_sar_touch_ctrl2_touch_start_en,
  field_sens_sar_touch_ctrl2_touch_start_force,
  field_sens_sar_touch_ctrl2_touch_sleep_cycles,
  field_sens_sar_touch_ctrl2_touch_meas_en_clr,
  field_sens_sar_touch_enable_touch_pad_worken,
  field_sens_sar_touch_enable_touch_pad_outen2,
  field_sens_sar_touch_enable_touch_pad_outen1,
  field_sens_sar_touch_out1_touch_meas_out1,
  field_sens_sar_touch_out1_touch_meas_out0,
  field_sens_sar_touch_out2_touch_meas_out3,
  field_sens_sar_touch_out2_touch_meas_out2,
  field_sens_sar_touch_out3_touch_meas_out5,
  field_sens_sar_touch_out3_touch_meas_out4,
  field_sens_sar_touch_out4_touch_meas_out7,
  field_sens_sar_touch_out4_touch_meas_out6,
  field_sens_sar_touch_out5_touch_meas_out9,
  field_sens_sar_touch_out5_touch_meas_out8,
  field_sens_sar_touch_thres1_touch_out_th1,
  field_sens_sar_touch_thres1_touch_out_th0,
  field_sens_sar_touch_thres2_touch_out_th3,
  field_sens_sar_touch_thres2_touch_out_th2,
  field_sens_sar_touch_thres3_touch_out_th5,
  field_sens_sar_touch_thres3_touch_out_th4,
  field_sens_sar_touch_thres4_touch_out_th7,
  field_sens_sar_touch_thres4_touch_out_th6,
  field_sens_sar_touch_thres5_touch_out_th9,
  field_sens_sar_touch_thres5_touch_out_th8,
  field_sens_sar_tsens_ctrl_tsens_xpd_wait,
  field_sens_sar_tsens_ctrl_tsens_xpd_force,
  field_sens_sar_tsens_ctrl_tsens_clk_inv,
  field_sens_sar_tsens_ctrl_tsens_clk_gated,
  field_sens_sar_tsens_ctrl_tsens_in_inv,
  field_sens_sar_tsens_ctrl_tsens_clk_div,
  field_sens_sar_tsens_ctrl_tsens_power_up,
  field_sens_sar_tsens_ctrl_tsens_power_up_force,
  field_sens_sar_tsens_ctrl_tsens_dump_out,
  field_sens_ulp_cp_sleep_cyc0_sleep_cycles_s0,
  field_sens_ulp_cp_sleep_cyc1_sleep_cycles_s1,
  field_sens_ulp_cp_sleep_cyc2_sleep_cycles_s2,
  field_sens_ulp_cp_sleep_cyc3_sleep_cycles_s3,
  field_sens_ulp_cp_sleep_cyc4_sleep_cycles_s4,
  field_spi0_cache_fctrl_cache_req_en,
  field_spi0_cache_fctrl_cache_usr_cmd_4byte,
  field_spi0_cache_fctrl_cache_flash_usr_cmd,
  field_spi0_cache_fctrl_cache_flash_pes_en,
  field_spi0_cache_sctrl_usr_sram_dio,
  field_spi0_cache_sctrl_usr_sram_qio,
  field_spi0_cache_sctrl_usr_wr_sram_dummy,
  field_spi0_cache_sctrl_usr_rd_sram_dummy,
  field_spi0_cache_sctrl_cache_sram_usr_rcmd,
  field_spi0_cache_sctrl_sram_bytes_len,
  field_spi0_cache_sctrl_sram_dummy_cyclelen,
  field_spi0_cache_sctrl_sram_addr_bitlen,
  field_spi0_cache_sctrl_cache_sram_usr_wcmd,
  field_spi0_clock_clkcnt_l,
  field_spi0_clock_clkcnt_h,
  field_spi0_clock_clkcnt_n,
  field_spi0_clock_clkdiv_pre,
  field_spi0_clock_clk_equ_sysclk,
  field_spi0_cmd_flash_per,
  field_spi0_cmd_flash_pes,
  field_spi0_cmd_usr,
  field_spi0_cmd_flash_hpm,
  field_spi0_cmd_flash_res,
  field_spi0_cmd_flash_dp,
  field_spi0_cmd_flash_ce,
  field_spi0_cmd_flash_be,
  field_spi0_cmd_flash_se,
  field_spi0_cmd_flash_pp,
  field_spi0_cmd_flash_wrsr,
  field_spi0_cmd_flash_rdsr,
  field_spi0_cmd_flash_rdid,
  field_spi0_cmd_flash_wrdi,
  field_spi0_cmd_flash_wren,
  field_spi0_cmd_flash_read,
  field_spi0_ctrl_fcs_crc_en,
  field_spi0_ctrl_tx_crc_en,
  field_spi0_ctrl_wait_flash_idle_en,
  field_spi0_ctrl_fastrd_mode,
  field_spi0_ctrl_fread_dual,
  field_spi0_ctrl_resandres,
  field_spi0_ctrl_fread_quad,
  field_spi0_ctrl_wp,
  field_spi0_ctrl_wrsr_2b,
  field_spi0_ctrl_fread_dio,
  field_spi0_ctrl_fread_qio,
  field_spi0_ctrl_rd_bit_order,
  field_spi0_ctrl_wr_bit_order,
  field_spi0_ctrl1_cs_hold_delay_res,
  field_spi0_ctrl1_cs_hold_delay,
  field_spi0_ctrl2_setup_time,
  field_spi0_ctrl2_hold_time,
  field_spi0_ctrl2_ck_out_low_mode,
  field_spi0_ctrl2_ck_out_high_mode,
  field_spi0_ctrl2_miso_delay_mode,
  field_spi0_ctrl2_miso_delay_num,
  field_spi0_ctrl2_mosi_delay_mode,
  field_spi0_ctrl2_mosi_delay_num,
  field_spi0_ctrl2_cs_delay_mode,
  field_spi0_ctrl2_cs_delay_num,
  field_spi0_date_date,
  field_spi0_dma_conf_in_rst,
  field_spi0_dma_conf_out_rst,
  field_spi0_dma_conf_ahbm_fifo_rst,
  field_spi0_dma_conf_ahbm_rst,
  field_spi0_dma_conf_in_loop_test,
  field_spi0_dma_conf_out_loop_test,
  field_spi0_dma_conf_out_auto_wrback,
  field_spi0_dma_conf_out_eof_mode,
  field_spi0_dma_conf_outdscr_burst_en,
  field_spi0_dma_conf_indscr_burst_en,
  field_spi0_dma_conf_out_data_burst_en,
  field_spi0_dma_conf_dma_rx_stop,
  field_spi0_dma_conf_dma_tx_stop,
  field_spi0_dma_conf_dma_continue,
  field_spi0_dma_int_clr_inlink_dscr_empty_int_clr,
  field_spi0_dma_int_clr_outlink_dscr_error_int_clr,
  field_spi0_dma_int_clr_inlink_dscr_error_int_clr,
  field_spi0_dma_int_clr_in_done_int_clr,
  field_spi0_dma_int_clr_in_err_eof_int_clr,
  field_spi0_dma_int_clr_in_suc_eof_int_clr,
  field_spi0_dma_int_clr_out_done_int_clr,
  field_spi0_dma_int_clr_out_eof_int_clr,
  field_spi0_dma_int_clr_out_total_eof_int_clr,
  field_spi0_dma_int_ena_inlink_dscr_empty_int_ena,
  field_spi0_dma_int_ena_outlink_dscr_error_int_ena,
  field_spi0_dma_int_ena_inlink_dscr_error_int_ena,
  field_spi0_dma_int_ena_in_done_int_ena,
  field_spi0_dma_int_ena_in_err_eof_int_ena,
  field_spi0_dma_int_ena_in_suc_eof_int_ena,
  field_spi0_dma_int_ena_out_done_int_ena,
  field_spi0_dma_int_ena_out_eof_int_ena,
  field_spi0_dma_int_ena_out_total_eof_int_ena,
  field_spi0_dma_int_raw_inlink_dscr_empty_int_raw,
  field_spi0_dma_int_raw_outlink_dscr_error_int_raw,
  field_spi0_dma_int_raw_inlink_dscr_error_int_raw,
  field_spi0_dma_int_raw_in_done_int_raw,
  field_spi0_dma_int_raw_in_err_eof_int_raw,
  field_spi0_dma_int_raw_in_suc_eof_int_raw,
  field_spi0_dma_int_raw_out_done_int_raw,
  field_spi0_dma_int_raw_out_eof_int_raw,
  field_spi0_dma_int_raw_out_total_eof_int_raw,
  field_spi0_dma_int_st_inlink_dscr_empty_int_st,
  field_spi0_dma_int_st_outlink_dscr_error_int_st,
  field_spi0_dma_int_st_inlink_dscr_error_int_st,
  field_spi0_dma_int_st_in_done_int_st,
  field_spi0_dma_int_st_in_err_eof_int_st,
  field_spi0_dma_int_st_in_suc_eof_int_st,
  field_spi0_dma_int_st_out_done_int_st,
  field_spi0_dma_int_st_out_eof_int_st,
  field_spi0_dma_int_st_out_total_eof_int_st,
  field_spi0_dma_in_link_inlink_addr,
  field_spi0_dma_in_link_inlink_auto_ret,
  field_spi0_dma_in_link_inlink_stop,
  field_spi0_dma_in_link_inlink_start,
  field_spi0_dma_in_link_inlink_restart,
  field_spi0_dma_out_link_outlink_addr,
  field_spi0_dma_out_link_outlink_stop,
  field_spi0_dma_out_link_outlink_start,
  field_spi0_dma_out_link_outlink_restart,
  field_spi0_dma_rstatus_dma_out_status,
  field_spi0_dma_status_dma_rx_en,
  field_spi0_dma_status_dma_tx_en,
  field_spi0_dma_tstatus_dma_in_status,
  field_spi0_ext0_t_pp_time,
  field_spi0_ext0_t_pp_shift,
  field_spi0_ext0_t_pp_ena,
  field_spi0_ext1_t_erase_time,
  field_spi0_ext1_t_erase_shift,
  field_spi0_ext1_t_erase_ena,
  field_spi0_ext2_st,
  field_spi0_ext3_int_hold_ena,
  field_spi0_inlink_dscr_dma_inlink_dscr,
  field_spi0_inlink_dscr_bf0_dma_inlink_dscr_bf0,
  field_spi0_inlink_dscr_bf1_dma_inlink_dscr_bf1,
  field_spi0_in_err_eof_des_addr_dma_in_err_eof_des_addr,
  field_spi0_in_suc_eof_des_addr_dma_in_suc_eof_des_addr,
  field_spi0_miso_dlen_usr_miso_dbitlen,
  field_spi0_mosi_dlen_usr_mosi_dbitlen,
  field_spi0_outlink_dscr_dma_outlink_dscr,
  field_spi0_outlink_dscr_bf0_dma_outlink_dscr_bf0,
  field_spi0_outlink_dscr_bf1_dma_outlink_dscr_bf1,
  field_spi0_out_eof_bfr_des_addr_dma_out_eof_bfr_des_addr,
  field_spi0_out_eof_des_addr_dma_out_eof_des_addr,
  field_spi0_pin_cs0_dis,
  field_spi0_pin_cs1_dis,
  field_spi0_pin_cs2_dis,
  field_spi0_pin_ck_dis,
  field_spi0_pin_master_cs_pol,
  field_spi0_pin_master_ck_sel,
  field_spi0_pin_ck_idle_edge,
  field_spi0_pin_cs_keep_active,
  field_spi0_rd_status_status,
  field_spi0_rd_status_wb_mode,
  field_spi0_rd_status_status_ext,
  field_spi0_slave_slv_rd_buf_done,
  field_spi0_slave_slv_wr_buf_done,
  field_spi0_slave_slv_rd_sta_done,
  field_spi0_slave_slv_wr_sta_done,
  field_spi0_slave_trans_done,
  field_spi0_slave_int_en,
  field_spi0_slave_cs_i_mode,
  field_spi0_slave_slv_last_command,
  field_spi0_slave_slv_last_state,
  field_spi0_slave_trans_cnt,
  field_spi0_slave_slv_cmd_define,
  field_spi0_slave_slv_wr_rd_sta_en,
  field_spi0_slave_slv_wr_rd_buf_en,
  field_spi0_slave_mode,
  field_spi0_slave_sync_reset,
  field_spi0_slave1_slv_rdbuf_dummy_en,
  field_spi0_slave1_slv_wrbuf_dummy_en,
  field_spi0_slave1_slv_rdsta_dummy_en,
  field_spi0_slave1_slv_wrsta_dummy_en,
  field_spi0_slave1_slv_wr_addr_bitlen,
  field_spi0_slave1_slv_rd_addr_bitlen,
  field_spi0_slave1_slv_status_readback,
  field_spi0_slave1_slv_status_fast_en,
  field_spi0_slave1_slv_status_bitlen,
  field_spi0_slave2_slv_rdsta_dummy_cyclelen,
  field_spi0_slave2_slv_wrsta_dummy_cyclelen,
  field_spi0_slave2_slv_rdbuf_dummy_cyclelen,
  field_spi0_slave2_slv_wrbuf_dummy_cyclelen,
  field_spi0_slave3_slv_rdbuf_cmd_value,
  field_spi0_slave3_slv_wrbuf_cmd_value,
  field_spi0_slave3_slv_rdsta_cmd_value,
  field_spi0_slave3_slv_wrsta_cmd_value,
  field_spi0_slv_rdbuf_dlen_slv_rdbuf_dbitlen,
  field_spi0_slv_rd_bit_slv_rdata_bit,
  field_spi0_slv_wrbuf_dlen_slv_wrbuf_dbitlen,
  field_spi0_slv_wr_status_slv_wr_st,
  field_spi0_sram_cmd_sram_dio,
  field_spi0_sram_cmd_sram_qio,
  field_spi0_sram_cmd_sram_rstio,
  field_spi0_sram_drd_cmd_cache_sram_usr_rd_cmd_value,
  field_spi0_sram_drd_cmd_cache_sram_usr_rd_cmd_bitlen,
  field_spi0_sram_dwr_cmd_cache_sram_usr_wr_cmd_value,
  field_spi0_sram_dwr_cmd_cache_sram_usr_wr_cmd_bitlen,
  field_spi0_tx_crc_data,
  field_spi0_user_doutdin,
  field_spi0_user_cs_hold,
  field_spi0_user_cs_setup,
  field_spi0_user_ck_i_edge,
  field_spi0_user_ck_out_edge,
  field_spi0_user_rd_byte_order,
  field_spi0_user_wr_byte_order,
  field_spi0_user_fwrite_dual,
  field_spi0_user_fwrite_quad,
  field_spi0_user_fwrite_dio,
  field_spi0_user_fwrite_qio,
  field_spi0_user_sio,
  field_spi0_user_usr_hold_pol,
  field_spi0_user_usr_dout_hold,
  field_spi0_user_usr_din_hold,
  field_spi0_user_usr_dummy_hold,
  field_spi0_user_usr_addr_hold,
  field_spi0_user_usr_cmd_hold,
  field_spi0_user_usr_prep_hold,
  field_spi0_user_usr_miso_highpart,
  field_spi0_user_usr_mosi_highpart,
  field_spi0_user_usr_dummy_idle,
  field_spi0_user_usr_mosi,
  field_spi0_user_usr_miso,
  field_spi0_user_usr_dummy,
  field_spi0_user_usr_addr,
  field_spi0_user_usr_command,
  field_spi0_user1_usr_dummy_cyclelen,
  field_spi0_user1_usr_addr_bitlen,
  field_spi0_user2_usr_command_value,
  field_spi0_user2_usr_command_bitlen,
  field_spi0_w0_buf0,
  field_spi0_w1_buf1,
  field_spi0_w10_buf10,
  field_spi0_w11_buf11,
  field_spi0_w12_buf12,
  field_spi0_w13_buf13,
  field_spi0_w14_buf14,
  field_spi0_w15_buf15,
  field_spi0_w2_buf2,
  field_spi0_w3_buf3,
  field_spi0_w4_buf4,
  field_spi0_w5_buf5,
  field_spi0_w6_buf6,
  field_spi0_w7_buf7,
  field_spi0_w8_buf8,
  field_spi0_w9_buf9,
  field_spi1_cache_fctrl_cache_req_en,
  field_spi1_cache_fctrl_cache_usr_cmd_4byte,
  field_spi1_cache_fctrl_cache_flash_usr_cmd,
  field_spi1_cache_fctrl_cache_flash_pes_en,
  field_spi1_cache_sctrl_usr_sram_dio,
  field_spi1_cache_sctrl_usr_sram_qio,
  field_spi1_cache_sctrl_usr_wr_sram_dummy,
  field_spi1_cache_sctrl_usr_rd_sram_dummy,
  field_spi1_cache_sctrl_cache_sram_usr_rcmd,
  field_spi1_cache_sctrl_sram_bytes_len,
  field_spi1_cache_sctrl_sram_dummy_cyclelen,
  field_spi1_cache_sctrl_sram_addr_bitlen,
  field_spi1_cache_sctrl_cache_sram_usr_wcmd,
  field_spi1_clock_clkcnt_l,
  field_spi1_clock_clkcnt_h,
  field_spi1_clock_clkcnt_n,
  field_spi1_clock_clkdiv_pre,
  field_spi1_clock_clk_equ_sysclk,
  field_spi1_cmd_flash_per,
  field_spi1_cmd_flash_pes,
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
  field_spi1_ctrl_fcs_crc_en,
  field_spi1_ctrl_tx_crc_en,
  field_spi1_ctrl_wait_flash_idle_en,
  field_spi1_ctrl_fastrd_mode,
  field_spi1_ctrl_fread_dual,
  field_spi1_ctrl_resandres,
  field_spi1_ctrl_fread_quad,
  field_spi1_ctrl_wp,
  field_spi1_ctrl_wrsr_2b,
  field_spi1_ctrl_fread_dio,
  field_spi1_ctrl_fread_qio,
  field_spi1_ctrl_rd_bit_order,
  field_spi1_ctrl_wr_bit_order,
  field_spi1_ctrl1_cs_hold_delay_res,
  field_spi1_ctrl1_cs_hold_delay,
  field_spi1_ctrl2_setup_time,
  field_spi1_ctrl2_hold_time,
  field_spi1_ctrl2_ck_out_low_mode,
  field_spi1_ctrl2_ck_out_high_mode,
  field_spi1_ctrl2_miso_delay_mode,
  field_spi1_ctrl2_miso_delay_num,
  field_spi1_ctrl2_mosi_delay_mode,
  field_spi1_ctrl2_mosi_delay_num,
  field_spi1_ctrl2_cs_delay_mode,
  field_spi1_ctrl2_cs_delay_num,
  field_spi1_date_date,
  field_spi1_dma_conf_in_rst,
  field_spi1_dma_conf_out_rst,
  field_spi1_dma_conf_ahbm_fifo_rst,
  field_spi1_dma_conf_ahbm_rst,
  field_spi1_dma_conf_in_loop_test,
  field_spi1_dma_conf_out_loop_test,
  field_spi1_dma_conf_out_auto_wrback,
  field_spi1_dma_conf_out_eof_mode,
  field_spi1_dma_conf_outdscr_burst_en,
  field_spi1_dma_conf_indscr_burst_en,
  field_spi1_dma_conf_out_data_burst_en,
  field_spi1_dma_conf_dma_rx_stop,
  field_spi1_dma_conf_dma_tx_stop,
  field_spi1_dma_conf_dma_continue,
  field_spi1_dma_int_clr_inlink_dscr_empty_int_clr,
  field_spi1_dma_int_clr_outlink_dscr_error_int_clr,
  field_spi1_dma_int_clr_inlink_dscr_error_int_clr,
  field_spi1_dma_int_clr_in_done_int_clr,
  field_spi1_dma_int_clr_in_err_eof_int_clr,
  field_spi1_dma_int_clr_in_suc_eof_int_clr,
  field_spi1_dma_int_clr_out_done_int_clr,
  field_spi1_dma_int_clr_out_eof_int_clr,
  field_spi1_dma_int_clr_out_total_eof_int_clr,
  field_spi1_dma_int_ena_inlink_dscr_empty_int_ena,
  field_spi1_dma_int_ena_outlink_dscr_error_int_ena,
  field_spi1_dma_int_ena_inlink_dscr_error_int_ena,
  field_spi1_dma_int_ena_in_done_int_ena,
  field_spi1_dma_int_ena_in_err_eof_int_ena,
  field_spi1_dma_int_ena_in_suc_eof_int_ena,
  field_spi1_dma_int_ena_out_done_int_ena,
  field_spi1_dma_int_ena_out_eof_int_ena,
  field_spi1_dma_int_ena_out_total_eof_int_ena,
  field_spi1_dma_int_raw_inlink_dscr_empty_int_raw,
  field_spi1_dma_int_raw_outlink_dscr_error_int_raw,
  field_spi1_dma_int_raw_inlink_dscr_error_int_raw,
  field_spi1_dma_int_raw_in_done_int_raw,
  field_spi1_dma_int_raw_in_err_eof_int_raw,
  field_spi1_dma_int_raw_in_suc_eof_int_raw,
  field_spi1_dma_int_raw_out_done_int_raw,
  field_spi1_dma_int_raw_out_eof_int_raw,
  field_spi1_dma_int_raw_out_total_eof_int_raw,
  field_spi1_dma_int_st_inlink_dscr_empty_int_st,
  field_spi1_dma_int_st_outlink_dscr_error_int_st,
  field_spi1_dma_int_st_inlink_dscr_error_int_st,
  field_spi1_dma_int_st_in_done_int_st,
  field_spi1_dma_int_st_in_err_eof_int_st,
  field_spi1_dma_int_st_in_suc_eof_int_st,
  field_spi1_dma_int_st_out_done_int_st,
  field_spi1_dma_int_st_out_eof_int_st,
  field_spi1_dma_int_st_out_total_eof_int_st,
  field_spi1_dma_in_link_inlink_addr,
  field_spi1_dma_in_link_inlink_auto_ret,
  field_spi1_dma_in_link_inlink_stop,
  field_spi1_dma_in_link_inlink_start,
  field_spi1_dma_in_link_inlink_restart,
  field_spi1_dma_out_link_outlink_addr,
  field_spi1_dma_out_link_outlink_stop,
  field_spi1_dma_out_link_outlink_start,
  field_spi1_dma_out_link_outlink_restart,
  field_spi1_dma_rstatus_dma_out_status,
  field_spi1_dma_status_dma_rx_en,
  field_spi1_dma_status_dma_tx_en,
  field_spi1_dma_tstatus_dma_in_status,
  field_spi1_ext0_t_pp_time,
  field_spi1_ext0_t_pp_shift,
  field_spi1_ext0_t_pp_ena,
  field_spi1_ext1_t_erase_time,
  field_spi1_ext1_t_erase_shift,
  field_spi1_ext1_t_erase_ena,
  field_spi1_ext2_st,
  field_spi1_ext3_int_hold_ena,
  field_spi1_inlink_dscr_dma_inlink_dscr,
  field_spi1_inlink_dscr_bf0_dma_inlink_dscr_bf0,
  field_spi1_inlink_dscr_bf1_dma_inlink_dscr_bf1,
  field_spi1_in_err_eof_des_addr_dma_in_err_eof_des_addr,
  field_spi1_in_suc_eof_des_addr_dma_in_suc_eof_des_addr,
  field_spi1_miso_dlen_usr_miso_dbitlen,
  field_spi1_mosi_dlen_usr_mosi_dbitlen,
  field_spi1_outlink_dscr_dma_outlink_dscr,
  field_spi1_outlink_dscr_bf0_dma_outlink_dscr_bf0,
  field_spi1_outlink_dscr_bf1_dma_outlink_dscr_bf1,
  field_spi1_out_eof_bfr_des_addr_dma_out_eof_bfr_des_addr,
  field_spi1_out_eof_des_addr_dma_out_eof_des_addr,
  field_spi1_pin_cs0_dis,
  field_spi1_pin_cs1_dis,
  field_spi1_pin_cs2_dis,
  field_spi1_pin_ck_dis,
  field_spi1_pin_master_cs_pol,
  field_spi1_pin_master_ck_sel,
  field_spi1_pin_ck_idle_edge,
  field_spi1_pin_cs_keep_active,
  field_spi1_rd_status_status,
  field_spi1_rd_status_wb_mode,
  field_spi1_rd_status_status_ext,
  field_spi1_slave_slv_rd_buf_done,
  field_spi1_slave_slv_wr_buf_done,
  field_spi1_slave_slv_rd_sta_done,
  field_spi1_slave_slv_wr_sta_done,
  field_spi1_slave_trans_done,
  field_spi1_slave_int_en,
  field_spi1_slave_cs_i_mode,
  field_spi1_slave_slv_last_command,
  field_spi1_slave_slv_last_state,
  field_spi1_slave_trans_cnt,
  field_spi1_slave_slv_cmd_define,
  field_spi1_slave_slv_wr_rd_sta_en,
  field_spi1_slave_slv_wr_rd_buf_en,
  field_spi1_slave_mode,
  field_spi1_slave_sync_reset,
  field_spi1_slave1_slv_rdbuf_dummy_en,
  field_spi1_slave1_slv_wrbuf_dummy_en,
  field_spi1_slave1_slv_rdsta_dummy_en,
  field_spi1_slave1_slv_wrsta_dummy_en,
  field_spi1_slave1_slv_wr_addr_bitlen,
  field_spi1_slave1_slv_rd_addr_bitlen,
  field_spi1_slave1_slv_status_readback,
  field_spi1_slave1_slv_status_fast_en,
  field_spi1_slave1_slv_status_bitlen,
  field_spi1_slave2_slv_rdsta_dummy_cyclelen,
  field_spi1_slave2_slv_wrsta_dummy_cyclelen,
  field_spi1_slave2_slv_rdbuf_dummy_cyclelen,
  field_spi1_slave2_slv_wrbuf_dummy_cyclelen,
  field_spi1_slave3_slv_rdbuf_cmd_value,
  field_spi1_slave3_slv_wrbuf_cmd_value,
  field_spi1_slave3_slv_rdsta_cmd_value,
  field_spi1_slave3_slv_wrsta_cmd_value,
  field_spi1_slv_rdbuf_dlen_slv_rdbuf_dbitlen,
  field_spi1_slv_rd_bit_slv_rdata_bit,
  field_spi1_slv_wrbuf_dlen_slv_wrbuf_dbitlen,
  field_spi1_slv_wr_status_slv_wr_st,
  field_spi1_sram_cmd_sram_dio,
  field_spi1_sram_cmd_sram_qio,
  field_spi1_sram_cmd_sram_rstio,
  field_spi1_sram_drd_cmd_cache_sram_usr_rd_cmd_value,
  field_spi1_sram_drd_cmd_cache_sram_usr_rd_cmd_bitlen,
  field_spi1_sram_dwr_cmd_cache_sram_usr_wr_cmd_value,
  field_spi1_sram_dwr_cmd_cache_sram_usr_wr_cmd_bitlen,
  field_spi1_tx_crc_data,
  field_spi1_user_doutdin,
  field_spi1_user_cs_hold,
  field_spi1_user_cs_setup,
  field_spi1_user_ck_i_edge,
  field_spi1_user_ck_out_edge,
  field_spi1_user_rd_byte_order,
  field_spi1_user_wr_byte_order,
  field_spi1_user_fwrite_dual,
  field_spi1_user_fwrite_quad,
  field_spi1_user_fwrite_dio,
  field_spi1_user_fwrite_qio,
  field_spi1_user_sio,
  field_spi1_user_usr_hold_pol,
  field_spi1_user_usr_dout_hold,
  field_spi1_user_usr_din_hold,
  field_spi1_user_usr_dummy_hold,
  field_spi1_user_usr_addr_hold,
  field_spi1_user_usr_cmd_hold,
  field_spi1_user_usr_prep_hold,
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
  field_spi2_cache_fctrl_cache_req_en,
  field_spi2_cache_fctrl_cache_usr_cmd_4byte,
  field_spi2_cache_fctrl_cache_flash_usr_cmd,
  field_spi2_cache_fctrl_cache_flash_pes_en,
  field_spi2_cache_sctrl_usr_sram_dio,
  field_spi2_cache_sctrl_usr_sram_qio,
  field_spi2_cache_sctrl_usr_wr_sram_dummy,
  field_spi2_cache_sctrl_usr_rd_sram_dummy,
  field_spi2_cache_sctrl_cache_sram_usr_rcmd,
  field_spi2_cache_sctrl_sram_bytes_len,
  field_spi2_cache_sctrl_sram_dummy_cyclelen,
  field_spi2_cache_sctrl_sram_addr_bitlen,
  field_spi2_cache_sctrl_cache_sram_usr_wcmd,
  field_spi2_clock_clkcnt_l,
  field_spi2_clock_clkcnt_h,
  field_spi2_clock_clkcnt_n,
  field_spi2_clock_clkdiv_pre,
  field_spi2_clock_clk_equ_sysclk,
  field_spi2_cmd_flash_per,
  field_spi2_cmd_flash_pes,
  field_spi2_cmd_usr,
  field_spi2_cmd_flash_hpm,
  field_spi2_cmd_flash_res,
  field_spi2_cmd_flash_dp,
  field_spi2_cmd_flash_ce,
  field_spi2_cmd_flash_be,
  field_spi2_cmd_flash_se,
  field_spi2_cmd_flash_pp,
  field_spi2_cmd_flash_wrsr,
  field_spi2_cmd_flash_rdsr,
  field_spi2_cmd_flash_rdid,
  field_spi2_cmd_flash_wrdi,
  field_spi2_cmd_flash_wren,
  field_spi2_cmd_flash_read,
  field_spi2_ctrl_fcs_crc_en,
  field_spi2_ctrl_tx_crc_en,
  field_spi2_ctrl_wait_flash_idle_en,
  field_spi2_ctrl_fastrd_mode,
  field_spi2_ctrl_fread_dual,
  field_spi2_ctrl_resandres,
  field_spi2_ctrl_fread_quad,
  field_spi2_ctrl_wp,
  field_spi2_ctrl_wrsr_2b,
  field_spi2_ctrl_fread_dio,
  field_spi2_ctrl_fread_qio,
  field_spi2_ctrl_rd_bit_order,
  field_spi2_ctrl_wr_bit_order,
  field_spi2_ctrl1_cs_hold_delay_res,
  field_spi2_ctrl1_cs_hold_delay,
  field_spi2_ctrl2_setup_time,
  field_spi2_ctrl2_hold_time,
  field_spi2_ctrl2_ck_out_low_mode,
  field_spi2_ctrl2_ck_out_high_mode,
  field_spi2_ctrl2_miso_delay_mode,
  field_spi2_ctrl2_miso_delay_num,
  field_spi2_ctrl2_mosi_delay_mode,
  field_spi2_ctrl2_mosi_delay_num,
  field_spi2_ctrl2_cs_delay_mode,
  field_spi2_ctrl2_cs_delay_num,
  field_spi2_date_date,
  field_spi2_dma_conf_in_rst,
  field_spi2_dma_conf_out_rst,
  field_spi2_dma_conf_ahbm_fifo_rst,
  field_spi2_dma_conf_ahbm_rst,
  field_spi2_dma_conf_in_loop_test,
  field_spi2_dma_conf_out_loop_test,
  field_spi2_dma_conf_out_auto_wrback,
  field_spi2_dma_conf_out_eof_mode,
  field_spi2_dma_conf_outdscr_burst_en,
  field_spi2_dma_conf_indscr_burst_en,
  field_spi2_dma_conf_out_data_burst_en,
  field_spi2_dma_conf_dma_rx_stop,
  field_spi2_dma_conf_dma_tx_stop,
  field_spi2_dma_conf_dma_continue,
  field_spi2_dma_int_clr_inlink_dscr_empty_int_clr,
  field_spi2_dma_int_clr_outlink_dscr_error_int_clr,
  field_spi2_dma_int_clr_inlink_dscr_error_int_clr,
  field_spi2_dma_int_clr_in_done_int_clr,
  field_spi2_dma_int_clr_in_err_eof_int_clr,
  field_spi2_dma_int_clr_in_suc_eof_int_clr,
  field_spi2_dma_int_clr_out_done_int_clr,
  field_spi2_dma_int_clr_out_eof_int_clr,
  field_spi2_dma_int_clr_out_total_eof_int_clr,
  field_spi2_dma_int_ena_inlink_dscr_empty_int_ena,
  field_spi2_dma_int_ena_outlink_dscr_error_int_ena,
  field_spi2_dma_int_ena_inlink_dscr_error_int_ena,
  field_spi2_dma_int_ena_in_done_int_ena,
  field_spi2_dma_int_ena_in_err_eof_int_ena,
  field_spi2_dma_int_ena_in_suc_eof_int_ena,
  field_spi2_dma_int_ena_out_done_int_ena,
  field_spi2_dma_int_ena_out_eof_int_ena,
  field_spi2_dma_int_ena_out_total_eof_int_ena,
  field_spi2_dma_int_raw_inlink_dscr_empty_int_raw,
  field_spi2_dma_int_raw_outlink_dscr_error_int_raw,
  field_spi2_dma_int_raw_inlink_dscr_error_int_raw,
  field_spi2_dma_int_raw_in_done_int_raw,
  field_spi2_dma_int_raw_in_err_eof_int_raw,
  field_spi2_dma_int_raw_in_suc_eof_int_raw,
  field_spi2_dma_int_raw_out_done_int_raw,
  field_spi2_dma_int_raw_out_eof_int_raw,
  field_spi2_dma_int_raw_out_total_eof_int_raw,
  field_spi2_dma_int_st_inlink_dscr_empty_int_st,
  field_spi2_dma_int_st_outlink_dscr_error_int_st,
  field_spi2_dma_int_st_inlink_dscr_error_int_st,
  field_spi2_dma_int_st_in_done_int_st,
  field_spi2_dma_int_st_in_err_eof_int_st,
  field_spi2_dma_int_st_in_suc_eof_int_st,
  field_spi2_dma_int_st_out_done_int_st,
  field_spi2_dma_int_st_out_eof_int_st,
  field_spi2_dma_int_st_out_total_eof_int_st,
  field_spi2_dma_in_link_inlink_addr,
  field_spi2_dma_in_link_inlink_auto_ret,
  field_spi2_dma_in_link_inlink_stop,
  field_spi2_dma_in_link_inlink_start,
  field_spi2_dma_in_link_inlink_restart,
  field_spi2_dma_out_link_outlink_addr,
  field_spi2_dma_out_link_outlink_stop,
  field_spi2_dma_out_link_outlink_start,
  field_spi2_dma_out_link_outlink_restart,
  field_spi2_dma_rstatus_dma_out_status,
  field_spi2_dma_status_dma_rx_en,
  field_spi2_dma_status_dma_tx_en,
  field_spi2_dma_tstatus_dma_in_status,
  field_spi2_ext0_t_pp_time,
  field_spi2_ext0_t_pp_shift,
  field_spi2_ext0_t_pp_ena,
  field_spi2_ext1_t_erase_time,
  field_spi2_ext1_t_erase_shift,
  field_spi2_ext1_t_erase_ena,
  field_spi2_ext2_st,
  field_spi2_ext3_int_hold_ena,
  field_spi2_inlink_dscr_dma_inlink_dscr,
  field_spi2_inlink_dscr_bf0_dma_inlink_dscr_bf0,
  field_spi2_inlink_dscr_bf1_dma_inlink_dscr_bf1,
  field_spi2_in_err_eof_des_addr_dma_in_err_eof_des_addr,
  field_spi2_in_suc_eof_des_addr_dma_in_suc_eof_des_addr,
  field_spi2_miso_dlen_usr_miso_dbitlen,
  field_spi2_mosi_dlen_usr_mosi_dbitlen,
  field_spi2_outlink_dscr_dma_outlink_dscr,
  field_spi2_outlink_dscr_bf0_dma_outlink_dscr_bf0,
  field_spi2_outlink_dscr_bf1_dma_outlink_dscr_bf1,
  field_spi2_out_eof_bfr_des_addr_dma_out_eof_bfr_des_addr,
  field_spi2_out_eof_des_addr_dma_out_eof_des_addr,
  field_spi2_pin_cs0_dis,
  field_spi2_pin_cs1_dis,
  field_spi2_pin_cs2_dis,
  field_spi2_pin_ck_dis,
  field_spi2_pin_master_cs_pol,
  field_spi2_pin_master_ck_sel,
  field_spi2_pin_ck_idle_edge,
  field_spi2_pin_cs_keep_active,
  field_spi2_rd_status_status,
  field_spi2_rd_status_wb_mode,
  field_spi2_rd_status_status_ext,
  field_spi2_slave_slv_rd_buf_done,
  field_spi2_slave_slv_wr_buf_done,
  field_spi2_slave_slv_rd_sta_done,
  field_spi2_slave_slv_wr_sta_done,
  field_spi2_slave_trans_done,
  field_spi2_slave_int_en,
  field_spi2_slave_cs_i_mode,
  field_spi2_slave_slv_last_command,
  field_spi2_slave_slv_last_state,
  field_spi2_slave_trans_cnt,
  field_spi2_slave_slv_cmd_define,
  field_spi2_slave_slv_wr_rd_sta_en,
  field_spi2_slave_slv_wr_rd_buf_en,
  field_spi2_slave_mode,
  field_spi2_slave_sync_reset,
  field_spi2_slave1_slv_rdbuf_dummy_en,
  field_spi2_slave1_slv_wrbuf_dummy_en,
  field_spi2_slave1_slv_rdsta_dummy_en,
  field_spi2_slave1_slv_wrsta_dummy_en,
  field_spi2_slave1_slv_wr_addr_bitlen,
  field_spi2_slave1_slv_rd_addr_bitlen,
  field_spi2_slave1_slv_status_readback,
  field_spi2_slave1_slv_status_fast_en,
  field_spi2_slave1_slv_status_bitlen,
  field_spi2_slave2_slv_rdsta_dummy_cyclelen,
  field_spi2_slave2_slv_wrsta_dummy_cyclelen,
  field_spi2_slave2_slv_rdbuf_dummy_cyclelen,
  field_spi2_slave2_slv_wrbuf_dummy_cyclelen,
  field_spi2_slave3_slv_rdbuf_cmd_value,
  field_spi2_slave3_slv_wrbuf_cmd_value,
  field_spi2_slave3_slv_rdsta_cmd_value,
  field_spi2_slave3_slv_wrsta_cmd_value,
  field_spi2_slv_rdbuf_dlen_slv_rdbuf_dbitlen,
  field_spi2_slv_rd_bit_slv_rdata_bit,
  field_spi2_slv_wrbuf_dlen_slv_wrbuf_dbitlen,
  field_spi2_slv_wr_status_slv_wr_st,
  field_spi2_sram_cmd_sram_dio,
  field_spi2_sram_cmd_sram_qio,
  field_spi2_sram_cmd_sram_rstio,
  field_spi2_sram_drd_cmd_cache_sram_usr_rd_cmd_value,
  field_spi2_sram_drd_cmd_cache_sram_usr_rd_cmd_bitlen,
  field_spi2_sram_dwr_cmd_cache_sram_usr_wr_cmd_value,
  field_spi2_sram_dwr_cmd_cache_sram_usr_wr_cmd_bitlen,
  field_spi2_tx_crc_data,
  field_spi2_user_doutdin,
  field_spi2_user_cs_hold,
  field_spi2_user_cs_setup,
  field_spi2_user_ck_i_edge,
  field_spi2_user_ck_out_edge,
  field_spi2_user_rd_byte_order,
  field_spi2_user_wr_byte_order,
  field_spi2_user_fwrite_dual,
  field_spi2_user_fwrite_quad,
  field_spi2_user_fwrite_dio,
  field_spi2_user_fwrite_qio,
  field_spi2_user_sio,
  field_spi2_user_usr_hold_pol,
  field_spi2_user_usr_dout_hold,
  field_spi2_user_usr_din_hold,
  field_spi2_user_usr_dummy_hold,
  field_spi2_user_usr_addr_hold,
  field_spi2_user_usr_cmd_hold,
  field_spi2_user_usr_prep_hold,
  field_spi2_user_usr_miso_highpart,
  field_spi2_user_usr_mosi_highpart,
  field_spi2_user_usr_dummy_idle,
  field_spi2_user_usr_mosi,
  field_spi2_user_usr_miso,
  field_spi2_user_usr_dummy,
  field_spi2_user_usr_addr,
  field_spi2_user_usr_command,
  field_spi2_user1_usr_dummy_cyclelen,
  field_spi2_user1_usr_addr_bitlen,
  field_spi2_user2_usr_command_value,
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
  field_spi3_cache_fctrl_cache_req_en,
  field_spi3_cache_fctrl_cache_usr_cmd_4byte,
  field_spi3_cache_fctrl_cache_flash_usr_cmd,
  field_spi3_cache_fctrl_cache_flash_pes_en,
  field_spi3_cache_sctrl_usr_sram_dio,
  field_spi3_cache_sctrl_usr_sram_qio,
  field_spi3_cache_sctrl_usr_wr_sram_dummy,
  field_spi3_cache_sctrl_usr_rd_sram_dummy,
  field_spi3_cache_sctrl_cache_sram_usr_rcmd,
  field_spi3_cache_sctrl_sram_bytes_len,
  field_spi3_cache_sctrl_sram_dummy_cyclelen,
  field_spi3_cache_sctrl_sram_addr_bitlen,
  field_spi3_cache_sctrl_cache_sram_usr_wcmd,
  field_spi3_clock_clkcnt_l,
  field_spi3_clock_clkcnt_h,
  field_spi3_clock_clkcnt_n,
  field_spi3_clock_clkdiv_pre,
  field_spi3_clock_clk_equ_sysclk,
  field_spi3_cmd_flash_per,
  field_spi3_cmd_flash_pes,
  field_spi3_cmd_usr,
  field_spi3_cmd_flash_hpm,
  field_spi3_cmd_flash_res,
  field_spi3_cmd_flash_dp,
  field_spi3_cmd_flash_ce,
  field_spi3_cmd_flash_be,
  field_spi3_cmd_flash_se,
  field_spi3_cmd_flash_pp,
  field_spi3_cmd_flash_wrsr,
  field_spi3_cmd_flash_rdsr,
  field_spi3_cmd_flash_rdid,
  field_spi3_cmd_flash_wrdi,
  field_spi3_cmd_flash_wren,
  field_spi3_cmd_flash_read,
  field_spi3_ctrl_fcs_crc_en,
  field_spi3_ctrl_tx_crc_en,
  field_spi3_ctrl_wait_flash_idle_en,
  field_spi3_ctrl_fastrd_mode,
  field_spi3_ctrl_fread_dual,
  field_spi3_ctrl_resandres,
  field_spi3_ctrl_fread_quad,
  field_spi3_ctrl_wp,
  field_spi3_ctrl_wrsr_2b,
  field_spi3_ctrl_fread_dio,
  field_spi3_ctrl_fread_qio,
  field_spi3_ctrl_rd_bit_order,
  field_spi3_ctrl_wr_bit_order,
  field_spi3_ctrl1_cs_hold_delay_res,
  field_spi3_ctrl1_cs_hold_delay,
  field_spi3_ctrl2_setup_time,
  field_spi3_ctrl2_hold_time,
  field_spi3_ctrl2_ck_out_low_mode,
  field_spi3_ctrl2_ck_out_high_mode,
  field_spi3_ctrl2_miso_delay_mode,
  field_spi3_ctrl2_miso_delay_num,
  field_spi3_ctrl2_mosi_delay_mode,
  field_spi3_ctrl2_mosi_delay_num,
  field_spi3_ctrl2_cs_delay_mode,
  field_spi3_ctrl2_cs_delay_num,
  field_spi3_date_date,
  field_spi3_dma_conf_in_rst,
  field_spi3_dma_conf_out_rst,
  field_spi3_dma_conf_ahbm_fifo_rst,
  field_spi3_dma_conf_ahbm_rst,
  field_spi3_dma_conf_in_loop_test,
  field_spi3_dma_conf_out_loop_test,
  field_spi3_dma_conf_out_auto_wrback,
  field_spi3_dma_conf_out_eof_mode,
  field_spi3_dma_conf_outdscr_burst_en,
  field_spi3_dma_conf_indscr_burst_en,
  field_spi3_dma_conf_out_data_burst_en,
  field_spi3_dma_conf_dma_rx_stop,
  field_spi3_dma_conf_dma_tx_stop,
  field_spi3_dma_conf_dma_continue,
  field_spi3_dma_int_clr_inlink_dscr_empty_int_clr,
  field_spi3_dma_int_clr_outlink_dscr_error_int_clr,
  field_spi3_dma_int_clr_inlink_dscr_error_int_clr,
  field_spi3_dma_int_clr_in_done_int_clr,
  field_spi3_dma_int_clr_in_err_eof_int_clr,
  field_spi3_dma_int_clr_in_suc_eof_int_clr,
  field_spi3_dma_int_clr_out_done_int_clr,
  field_spi3_dma_int_clr_out_eof_int_clr,
  field_spi3_dma_int_clr_out_total_eof_int_clr,
  field_spi3_dma_int_ena_inlink_dscr_empty_int_ena,
  field_spi3_dma_int_ena_outlink_dscr_error_int_ena,
  field_spi3_dma_int_ena_inlink_dscr_error_int_ena,
  field_spi3_dma_int_ena_in_done_int_ena,
  field_spi3_dma_int_ena_in_err_eof_int_ena,
  field_spi3_dma_int_ena_in_suc_eof_int_ena,
  field_spi3_dma_int_ena_out_done_int_ena,
  field_spi3_dma_int_ena_out_eof_int_ena,
  field_spi3_dma_int_ena_out_total_eof_int_ena,
  field_spi3_dma_int_raw_inlink_dscr_empty_int_raw,
  field_spi3_dma_int_raw_outlink_dscr_error_int_raw,
  field_spi3_dma_int_raw_inlink_dscr_error_int_raw,
  field_spi3_dma_int_raw_in_done_int_raw,
  field_spi3_dma_int_raw_in_err_eof_int_raw,
  field_spi3_dma_int_raw_in_suc_eof_int_raw,
  field_spi3_dma_int_raw_out_done_int_raw,
  field_spi3_dma_int_raw_out_eof_int_raw,
  field_spi3_dma_int_raw_out_total_eof_int_raw,
  field_spi3_dma_int_st_inlink_dscr_empty_int_st,
  field_spi3_dma_int_st_outlink_dscr_error_int_st,
  field_spi3_dma_int_st_inlink_dscr_error_int_st,
  field_spi3_dma_int_st_in_done_int_st,
  field_spi3_dma_int_st_in_err_eof_int_st,
  field_spi3_dma_int_st_in_suc_eof_int_st,
  field_spi3_dma_int_st_out_done_int_st,
  field_spi3_dma_int_st_out_eof_int_st,
  field_spi3_dma_int_st_out_total_eof_int_st,
  field_spi3_dma_in_link_inlink_addr,
  field_spi3_dma_in_link_inlink_auto_ret,
  field_spi3_dma_in_link_inlink_stop,
  field_spi3_dma_in_link_inlink_start,
  field_spi3_dma_in_link_inlink_restart,
  field_spi3_dma_out_link_outlink_addr,
  field_spi3_dma_out_link_outlink_stop,
  field_spi3_dma_out_link_outlink_start,
  field_spi3_dma_out_link_outlink_restart,
  field_spi3_dma_rstatus_dma_out_status,
  field_spi3_dma_status_dma_rx_en,
  field_spi3_dma_status_dma_tx_en,
  field_spi3_dma_tstatus_dma_in_status,
  field_spi3_ext0_t_pp_time,
  field_spi3_ext0_t_pp_shift,
  field_spi3_ext0_t_pp_ena,
  field_spi3_ext1_t_erase_time,
  field_spi3_ext1_t_erase_shift,
  field_spi3_ext1_t_erase_ena,
  field_spi3_ext2_st,
  field_spi3_ext3_int_hold_ena,
  field_spi3_inlink_dscr_dma_inlink_dscr,
  field_spi3_inlink_dscr_bf0_dma_inlink_dscr_bf0,
  field_spi3_inlink_dscr_bf1_dma_inlink_dscr_bf1,
  field_spi3_in_err_eof_des_addr_dma_in_err_eof_des_addr,
  field_spi3_in_suc_eof_des_addr_dma_in_suc_eof_des_addr,
  field_spi3_miso_dlen_usr_miso_dbitlen,
  field_spi3_mosi_dlen_usr_mosi_dbitlen,
  field_spi3_outlink_dscr_dma_outlink_dscr,
  field_spi3_outlink_dscr_bf0_dma_outlink_dscr_bf0,
  field_spi3_outlink_dscr_bf1_dma_outlink_dscr_bf1,
  field_spi3_out_eof_bfr_des_addr_dma_out_eof_bfr_des_addr,
  field_spi3_out_eof_des_addr_dma_out_eof_des_addr,
  field_spi3_pin_cs0_dis,
  field_spi3_pin_cs1_dis,
  field_spi3_pin_cs2_dis,
  field_spi3_pin_ck_dis,
  field_spi3_pin_master_cs_pol,
  field_spi3_pin_master_ck_sel,
  field_spi3_pin_ck_idle_edge,
  field_spi3_pin_cs_keep_active,
  field_spi3_rd_status_status,
  field_spi3_rd_status_wb_mode,
  field_spi3_rd_status_status_ext,
  field_spi3_slave_slv_rd_buf_done,
  field_spi3_slave_slv_wr_buf_done,
  field_spi3_slave_slv_rd_sta_done,
  field_spi3_slave_slv_wr_sta_done,
  field_spi3_slave_trans_done,
  field_spi3_slave_int_en,
  field_spi3_slave_cs_i_mode,
  field_spi3_slave_slv_last_command,
  field_spi3_slave_slv_last_state,
  field_spi3_slave_trans_cnt,
  field_spi3_slave_slv_cmd_define,
  field_spi3_slave_slv_wr_rd_sta_en,
  field_spi3_slave_slv_wr_rd_buf_en,
  field_spi3_slave_mode,
  field_spi3_slave_sync_reset,
  field_spi3_slave1_slv_rdbuf_dummy_en,
  field_spi3_slave1_slv_wrbuf_dummy_en,
  field_spi3_slave1_slv_rdsta_dummy_en,
  field_spi3_slave1_slv_wrsta_dummy_en,
  field_spi3_slave1_slv_wr_addr_bitlen,
  field_spi3_slave1_slv_rd_addr_bitlen,
  field_spi3_slave1_slv_status_readback,
  field_spi3_slave1_slv_status_fast_en,
  field_spi3_slave1_slv_status_bitlen,
  field_spi3_slave2_slv_rdsta_dummy_cyclelen,
  field_spi3_slave2_slv_wrsta_dummy_cyclelen,
  field_spi3_slave2_slv_rdbuf_dummy_cyclelen,
  field_spi3_slave2_slv_wrbuf_dummy_cyclelen,
  field_spi3_slave3_slv_rdbuf_cmd_value,
  field_spi3_slave3_slv_wrbuf_cmd_value,
  field_spi3_slave3_slv_rdsta_cmd_value,
  field_spi3_slave3_slv_wrsta_cmd_value,
  field_spi3_slv_rdbuf_dlen_slv_rdbuf_dbitlen,
  field_spi3_slv_rd_bit_slv_rdata_bit,
  field_spi3_slv_wrbuf_dlen_slv_wrbuf_dbitlen,
  field_spi3_slv_wr_status_slv_wr_st,
  field_spi3_sram_cmd_sram_dio,
  field_spi3_sram_cmd_sram_qio,
  field_spi3_sram_cmd_sram_rstio,
  field_spi3_sram_drd_cmd_cache_sram_usr_rd_cmd_value,
  field_spi3_sram_drd_cmd_cache_sram_usr_rd_cmd_bitlen,
  field_spi3_sram_dwr_cmd_cache_sram_usr_wr_cmd_value,
  field_spi3_sram_dwr_cmd_cache_sram_usr_wr_cmd_bitlen,
  field_spi3_tx_crc_data,
  field_spi3_user_doutdin,
  field_spi3_user_cs_hold,
  field_spi3_user_cs_setup,
  field_spi3_user_ck_i_edge,
  field_spi3_user_ck_out_edge,
  field_spi3_user_rd_byte_order,
  field_spi3_user_wr_byte_order,
  field_spi3_user_fwrite_dual,
  field_spi3_user_fwrite_quad,
  field_spi3_user_fwrite_dio,
  field_spi3_user_fwrite_qio,
  field_spi3_user_sio,
  field_spi3_user_usr_hold_pol,
  field_spi3_user_usr_dout_hold,
  field_spi3_user_usr_din_hold,
  field_spi3_user_usr_dummy_hold,
  field_spi3_user_usr_addr_hold,
  field_spi3_user_usr_cmd_hold,
  field_spi3_user_usr_prep_hold,
  field_spi3_user_usr_miso_highpart,
  field_spi3_user_usr_mosi_highpart,
  field_spi3_user_usr_dummy_idle,
  field_spi3_user_usr_mosi,
  field_spi3_user_usr_miso,
  field_spi3_user_usr_dummy,
  field_spi3_user_usr_addr,
  field_spi3_user_usr_command,
  field_spi3_user1_usr_dummy_cyclelen,
  field_spi3_user1_usr_addr_bitlen,
  field_spi3_user2_usr_command_value,
  field_spi3_user2_usr_command_bitlen,
  field_spi3_w0_buf0,
  field_spi3_w1_buf1,
  field_spi3_w10_buf10,
  field_spi3_w11_buf11,
  field_spi3_w12_buf12,
  field_spi3_w13_buf13,
  field_spi3_w14_buf14,
  field_spi3_w15_buf15,
  field_spi3_w2_buf2,
  field_spi3_w3_buf3,
  field_spi3_w4_buf4,
  field_spi3_w5_buf5,
  field_spi3_w6_buf6,
  field_spi3_w7_buf7,
  field_spi3_w8_buf8,
  field_spi3_w9_buf9,
  field_uart0_at_cmd_char_at_cmd_char,
  field_uart0_at_cmd_char_char_num,
  field_uart0_at_cmd_gaptout_rx_gap_tout,
  field_uart0_at_cmd_postcnt_post_idle_num,
  field_uart0_at_cmd_precnt_pre_idle_num,
  field_uart0_autobaud_en,
  field_uart0_autobaud_glitch_filt,
  field_uart0_clkdiv_clkdiv,
  field_uart0_clkdiv_frag,
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
  field_uart0_conf0_tick_ref_always_on,
  field_uart0_conf1_rxfifo_full_thrhd,
  field_uart0_conf1_txfifo_empty_thrhd,
  field_uart0_conf1_rx_flow_thrhd,
  field_uart0_conf1_rx_flow_en,
  field_uart0_conf1_rx_tout_thrhd,
  field_uart0_conf1_rx_tout_en,
  field_uart0_date_date,
  field_uart0_fifo_rxfifo_rd_byte,
  field_uart0_flow_conf_sw_flow_con_en,
  field_uart0_flow_conf_xonoff_del,
  field_uart0_flow_conf_force_xon,
  field_uart0_flow_conf_force_xoff,
  field_uart0_flow_conf_send_xon,
  field_uart0_flow_conf_send_xoff,
  field_uart0_highpulse_min_cnt,
  field_uart0_id_id,
  field_uart0_idle_conf_rx_idle_thrhd,
  field_uart0_idle_conf_tx_idle_num,
  field_uart0_idle_conf_tx_brk_num,
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
  field_uart0_lowpulse_min_cnt,
  field_uart0_mem_cnt_status_rx_mem_cnt,
  field_uart0_mem_cnt_status_tx_mem_cnt,
  field_uart0_mem_conf_mem_pd,
  field_uart0_mem_conf_rx_size,
  field_uart0_mem_conf_tx_size,
  field_uart0_mem_conf_rx_flow_thrhd_h3,
  field_uart0_mem_conf_rx_tout_thrhd_h3,
  field_uart0_mem_conf_xon_threshold_h2,
  field_uart0_mem_conf_xoff_threshold_h2,
  field_uart0_mem_conf_rx_mem_full_thrhd,
  field_uart0_mem_conf_tx_mem_empty_thrhd,
  field_uart0_mem_rx_status_mem_rx_status,
  field_uart0_mem_rx_status_mem_rx_rd_addr,
  field_uart0_mem_rx_status_mem_rx_wr_addr,
  field_uart0_mem_tx_status_mem_tx_status,
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
  field_uart0_sleep_conf_active_threshold,
  field_uart0_status_rxfifo_cnt,
  field_uart0_status_st_urx_out,
  field_uart0_status_dsrn,
  field_uart0_status_ctsn,
  field_uart0_status_rxd,
  field_uart0_status_txfifo_cnt,
  field_uart0_status_st_utx_out,
  field_uart0_status_dtrn,
  field_uart0_status_rtsn,
  field_uart0_status_txd,
  field_uart0_swfc_conf_xon_threshold,
  field_uart0_swfc_conf_xoff_threshold,
  field_uart0_swfc_conf_xon_char,
  field_uart0_swfc_conf_xoff_char,
  field_uart1_at_cmd_char_at_cmd_char,
  field_uart1_at_cmd_char_char_num,
  field_uart1_at_cmd_gaptout_rx_gap_tout,
  field_uart1_at_cmd_postcnt_post_idle_num,
  field_uart1_at_cmd_precnt_pre_idle_num,
  field_uart1_autobaud_en,
  field_uart1_autobaud_glitch_filt,
  field_uart1_clkdiv_clkdiv,
  field_uart1_clkdiv_frag,
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
  field_uart1_conf0_tick_ref_always_on,
  field_uart1_conf1_rxfifo_full_thrhd,
  field_uart1_conf1_txfifo_empty_thrhd,
  field_uart1_conf1_rx_flow_thrhd,
  field_uart1_conf1_rx_flow_en,
  field_uart1_conf1_rx_tout_thrhd,
  field_uart1_conf1_rx_tout_en,
  field_uart1_date_date,
  field_uart1_fifo_rxfifo_rd_byte,
  field_uart1_flow_conf_sw_flow_con_en,
  field_uart1_flow_conf_xonoff_del,
  field_uart1_flow_conf_force_xon,
  field_uart1_flow_conf_force_xoff,
  field_uart1_flow_conf_send_xon,
  field_uart1_flow_conf_send_xoff,
  field_uart1_highpulse_min_cnt,
  field_uart1_id_id,
  field_uart1_idle_conf_rx_idle_thrhd,
  field_uart1_idle_conf_tx_idle_num,
  field_uart1_idle_conf_tx_brk_num,
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
  field_uart1_lowpulse_min_cnt,
  field_uart1_mem_cnt_status_rx_mem_cnt,
  field_uart1_mem_cnt_status_tx_mem_cnt,
  field_uart1_mem_conf_mem_pd,
  field_uart1_mem_conf_rx_size,
  field_uart1_mem_conf_tx_size,
  field_uart1_mem_conf_rx_flow_thrhd_h3,
  field_uart1_mem_conf_rx_tout_thrhd_h3,
  field_uart1_mem_conf_xon_threshold_h2,
  field_uart1_mem_conf_xoff_threshold_h2,
  field_uart1_mem_conf_rx_mem_full_thrhd,
  field_uart1_mem_conf_tx_mem_empty_thrhd,
  field_uart1_mem_rx_status_mem_rx_status,
  field_uart1_mem_rx_status_mem_rx_rd_addr,
  field_uart1_mem_rx_status_mem_rx_wr_addr,
  field_uart1_mem_tx_status_mem_tx_status,
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
  field_uart1_sleep_conf_active_threshold,
  field_uart1_status_rxfifo_cnt,
  field_uart1_status_st_urx_out,
  field_uart1_status_dsrn,
  field_uart1_status_ctsn,
  field_uart1_status_rxd,
  field_uart1_status_txfifo_cnt,
  field_uart1_status_st_utx_out,
  field_uart1_status_dtrn,
  field_uart1_status_rtsn,
  field_uart1_status_txd,
  field_uart1_swfc_conf_xon_threshold,
  field_uart1_swfc_conf_xoff_threshold,
  field_uart1_swfc_conf_xon_char,
  field_uart1_swfc_conf_xoff_char,
  field_uart2_at_cmd_char_at_cmd_char,
  field_uart2_at_cmd_char_char_num,
  field_uart2_at_cmd_gaptout_rx_gap_tout,
  field_uart2_at_cmd_postcnt_post_idle_num,
  field_uart2_at_cmd_precnt_pre_idle_num,
  field_uart2_autobaud_en,
  field_uart2_autobaud_glitch_filt,
  field_uart2_clkdiv_clkdiv,
  field_uart2_clkdiv_frag,
  field_uart2_conf0_parity,
  field_uart2_conf0_parity_en,
  field_uart2_conf0_bit_num,
  field_uart2_conf0_stop_bit_num,
  field_uart2_conf0_sw_rts,
  field_uart2_conf0_sw_dtr,
  field_uart2_conf0_txd_brk,
  field_uart2_conf0_irda_dplx,
  field_uart2_conf0_irda_tx_en,
  field_uart2_conf0_irda_wctl,
  field_uart2_conf0_irda_tx_inv,
  field_uart2_conf0_irda_rx_inv,
  field_uart2_conf0_loopback,
  field_uart2_conf0_tx_flow_en,
  field_uart2_conf0_irda_en,
  field_uart2_conf0_rxfifo_rst,
  field_uart2_conf0_txfifo_rst,
  field_uart2_conf0_rxd_inv,
  field_uart2_conf0_cts_inv,
  field_uart2_conf0_dsr_inv,
  field_uart2_conf0_txd_inv,
  field_uart2_conf0_rts_inv,
  field_uart2_conf0_dtr_inv,
  field_uart2_conf0_clk_en,
  field_uart2_conf0_err_wr_mask,
  field_uart2_conf0_tick_ref_always_on,
  field_uart2_conf1_rxfifo_full_thrhd,
  field_uart2_conf1_txfifo_empty_thrhd,
  field_uart2_conf1_rx_flow_thrhd,
  field_uart2_conf1_rx_flow_en,
  field_uart2_conf1_rx_tout_thrhd,
  field_uart2_conf1_rx_tout_en,
  field_uart2_date_date,
  field_uart2_fifo_rxfifo_rd_byte,
  field_uart2_flow_conf_sw_flow_con_en,
  field_uart2_flow_conf_xonoff_del,
  field_uart2_flow_conf_force_xon,
  field_uart2_flow_conf_force_xoff,
  field_uart2_flow_conf_send_xon,
  field_uart2_flow_conf_send_xoff,
  field_uart2_highpulse_min_cnt,
  field_uart2_id_id,
  field_uart2_idle_conf_rx_idle_thrhd,
  field_uart2_idle_conf_tx_idle_num,
  field_uart2_idle_conf_tx_brk_num,
  field_uart2_int_clr_rxfifo_full_int_clr,
  field_uart2_int_clr_txfifo_empty_int_clr,
  field_uart2_int_clr_parity_err_int_clr,
  field_uart2_int_clr_frm_err_int_clr,
  field_uart2_int_clr_rxfifo_ovf_int_clr,
  field_uart2_int_clr_dsr_chg_int_clr,
  field_uart2_int_clr_cts_chg_int_clr,
  field_uart2_int_clr_brk_det_int_clr,
  field_uart2_int_clr_rxfifo_tout_int_clr,
  field_uart2_int_clr_sw_xon_int_clr,
  field_uart2_int_clr_sw_xoff_int_clr,
  field_uart2_int_clr_glitch_det_int_clr,
  field_uart2_int_clr_tx_brk_done_int_clr,
  field_uart2_int_clr_tx_brk_idle_done_int_clr,
  field_uart2_int_clr_tx_done_int_clr,
  field_uart2_int_clr_rs485_parity_err_int_clr,
  field_uart2_int_clr_rs485_frm_err_int_clr,
  field_uart2_int_clr_rs485_clash_int_clr,
  field_uart2_int_clr_at_cmd_char_det_int_clr,
  field_uart2_int_ena_rxfifo_full_int_ena,
  field_uart2_int_ena_txfifo_empty_int_ena,
  field_uart2_int_ena_parity_err_int_ena,
  field_uart2_int_ena_frm_err_int_ena,
  field_uart2_int_ena_rxfifo_ovf_int_ena,
  field_uart2_int_ena_dsr_chg_int_ena,
  field_uart2_int_ena_cts_chg_int_ena,
  field_uart2_int_ena_brk_det_int_ena,
  field_uart2_int_ena_rxfifo_tout_int_ena,
  field_uart2_int_ena_sw_xon_int_ena,
  field_uart2_int_ena_sw_xoff_int_ena,
  field_uart2_int_ena_glitch_det_int_ena,
  field_uart2_int_ena_tx_brk_done_int_ena,
  field_uart2_int_ena_tx_brk_idle_done_int_ena,
  field_uart2_int_ena_tx_done_int_ena,
  field_uart2_int_ena_rs485_parity_err_int_ena,
  field_uart2_int_ena_rs485_frm_err_int_ena,
  field_uart2_int_ena_rs485_clash_int_ena,
  field_uart2_int_ena_at_cmd_char_det_int_ena,
  field_uart2_int_raw_rxfifo_full_int_raw,
  field_uart2_int_raw_txfifo_empty_int_raw,
  field_uart2_int_raw_parity_err_int_raw,
  field_uart2_int_raw_frm_err_int_raw,
  field_uart2_int_raw_rxfifo_ovf_int_raw,
  field_uart2_int_raw_dsr_chg_int_raw,
  field_uart2_int_raw_cts_chg_int_raw,
  field_uart2_int_raw_brk_det_int_raw,
  field_uart2_int_raw_rxfifo_tout_int_raw,
  field_uart2_int_raw_sw_xon_int_raw,
  field_uart2_int_raw_sw_xoff_int_raw,
  field_uart2_int_raw_glitch_det_int_raw,
  field_uart2_int_raw_tx_brk_done_int_raw,
  field_uart2_int_raw_tx_brk_idle_done_int_raw,
  field_uart2_int_raw_tx_done_int_raw,
  field_uart2_int_raw_rs485_parity_err_int_raw,
  field_uart2_int_raw_rs485_frm_err_int_raw,
  field_uart2_int_raw_rs485_clash_int_raw,
  field_uart2_int_raw_at_cmd_char_det_int_raw,
  field_uart2_int_st_rxfifo_full_int_st,
  field_uart2_int_st_txfifo_empty_int_st,
  field_uart2_int_st_parity_err_int_st,
  field_uart2_int_st_frm_err_int_st,
  field_uart2_int_st_rxfifo_ovf_int_st,
  field_uart2_int_st_dsr_chg_int_st,
  field_uart2_int_st_cts_chg_int_st,
  field_uart2_int_st_brk_det_int_st,
  field_uart2_int_st_rxfifo_tout_int_st,
  field_uart2_int_st_sw_xon_int_st,
  field_uart2_int_st_sw_xoff_int_st,
  field_uart2_int_st_glitch_det_int_st,
  field_uart2_int_st_tx_brk_done_int_st,
  field_uart2_int_st_tx_brk_idle_done_int_st,
  field_uart2_int_st_tx_done_int_st,
  field_uart2_int_st_rs485_parity_err_int_st,
  field_uart2_int_st_rs485_frm_err_int_st,
  field_uart2_int_st_rs485_clash_int_st,
  field_uart2_int_st_at_cmd_char_det_int_st,
  field_uart2_lowpulse_min_cnt,
  field_uart2_mem_cnt_status_rx_mem_cnt,
  field_uart2_mem_cnt_status_tx_mem_cnt,
  field_uart2_mem_conf_mem_pd,
  field_uart2_mem_conf_rx_size,
  field_uart2_mem_conf_tx_size,
  field_uart2_mem_conf_rx_flow_thrhd_h3,
  field_uart2_mem_conf_rx_tout_thrhd_h3,
  field_uart2_mem_conf_xon_threshold_h2,
  field_uart2_mem_conf_xoff_threshold_h2,
  field_uart2_mem_conf_rx_mem_full_thrhd,
  field_uart2_mem_conf_tx_mem_empty_thrhd,
  field_uart2_mem_rx_status_mem_rx_status,
  field_uart2_mem_rx_status_mem_rx_rd_addr,
  field_uart2_mem_rx_status_mem_rx_wr_addr,
  field_uart2_mem_tx_status_mem_tx_status,
  field_uart2_negpulse_negedge_min_cnt,
  field_uart2_pospulse_posedge_min_cnt,
  field_uart2_rs485_conf_rs485_en,
  field_uart2_rs485_conf_dl0_en,
  field_uart2_rs485_conf_dl1_en,
  field_uart2_rs485_conf_rs485tx_rx_en,
  field_uart2_rs485_conf_rs485rxby_tx_en,
  field_uart2_rs485_conf_rs485_rx_dly_num,
  field_uart2_rs485_conf_rs485_tx_dly_num,
  field_uart2_rxd_cnt_rxd_edge_cnt,
  field_uart2_sleep_conf_active_threshold,
  field_uart2_status_rxfifo_cnt,
  field_uart2_status_st_urx_out,
  field_uart2_status_dsrn,
  field_uart2_status_ctsn,
  field_uart2_status_rxd,
  field_uart2_status_txfifo_cnt,
  field_uart2_status_st_utx_out,
  field_uart2_status_dtrn,
  field_uart2_status_rtsn,
  field_uart2_status_txd,
  field_uart2_swfc_conf_xon_threshold,
  field_uart2_swfc_conf_xoff_threshold,
  field_uart2_swfc_conf_xon_char,
  field_uart2_swfc_conf_xoff_char,
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
struct RegisterFieldTraits<FieldId::field_dport_perip_clk_en_spi01_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dport_perip_clk_en;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dport_perip_clk_en_uart_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dport_perip_clk_en;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_dport_perip_clk_en_i2c0_ext0_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_dport_perip_clk_en;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_acpu_int_appcpu_int> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_acpu_int;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_acpu_int1_appcpu_int_h> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_acpu_int1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_acpu_nmi_int_appcpu_nmi_int> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_acpu_nmi_int;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_acpu_nmi_int1_appcpu_nmi_int_h> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_acpu_nmi_int1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
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
struct RegisterFieldTraits<FieldId::field_gpio_cpusdio_int_sdio_int> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_cpusdio_int;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_cpusdio_int1_sdio_int_h> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_cpusdio_int1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_cpusdio_int1_pin_pad_driver> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_cpusdio_int1;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_cpusdio_int1_pin_int_type> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_cpusdio_int1;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_cpusdio_int1_pin_wakeup_enable> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_cpusdio_int1;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_cpusdio_int1_pin_config> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_cpusdio_int1;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_cpusdio_int1_pin_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_cpusdio_int1;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_enable_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_enable;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_enable1_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_enable1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_enable1_w1tc_enable1_data_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_enable1_w1tc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_enable1_w1ts_enable1_data_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_enable1_w1ts;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_enable_w1tc_enable_data_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_enable_w1tc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_enable_w1ts_enable_data_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_enable_w1ts;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_func_s_in_sel_cfg_in_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_func_s_in_sel_cfg;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_func_s_in_sel_cfg_in_inv_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_func_s_in_sel_cfg;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_func_s_in_sel_cfg_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_func_s_in_sel_cfg;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_func_s_out_sel_cfg_out_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_func_s_out_sel_cfg;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 9u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_func_s_out_sel_cfg_inv_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_func_s_out_sel_cfg;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_func_s_out_sel_cfg_oen_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_func_s_out_sel_cfg;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_func_s_out_sel_cfg_oen_inv_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_func_s_out_sel_cfg;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_in_data_next> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_in;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_in1_data_next> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_in1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_out_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_out;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_out1_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_out1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_out1_w1tc_out1_data_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_out1_w1tc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_out1_w1ts_out1_data_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_out1_w1ts;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_out_w1tc_out_data_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_out_w1tc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_out_w1ts_out_data_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_out_w1ts;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_pcpu_int_procpu_int> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_pcpu_int;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_pcpu_int1_procpu_int_h> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_pcpu_int1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_pcpu_nmi_int_procpu_nmi_int> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_pcpu_nmi_int;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_pcpu_nmi_int1_procpu_nmi_int_h> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_pcpu_nmi_int1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
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
struct RegisterFieldTraits<FieldId::field_gpio_sdio_select_sdio_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_sdio_select;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_status_int> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_status1_int> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_status1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_status1_w1tc_status1_int_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_status1_w1tc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_status1_w1ts_status1_int_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_status1_w1ts;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_status_w1tc_status_int_w1tc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_status_w1tc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_status_w1ts_status_int_w1ts> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_status_w1ts;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
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
struct RegisterFieldTraits<FieldId::field_gpio_cali_conf_cali_rtc_max> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_cali_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_cali_conf_cali_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_cali_conf;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_cali_data_cali_value_sync2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_cali_data;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_cali_data_cali_rdy_real> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_cali_data;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_gpio_cali_data_cali_rdy_sync2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_gpio_cali_data;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
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
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
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
struct RegisterFieldTraits<FieldId::field_i2c0_data_fifo_rdata> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_data;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
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
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_conf_rxfifo_full_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_conf_txfifo_empty_thrhd> {
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
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_conf_nonfifo_rx_thres> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_fifo_conf_nonfifo_tx_thres> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_rxfifo_full_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_txfifo_empty_int_clr> {
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
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_slave_tran_comp_int_clr> {
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
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_master_tran_comp_int_clr> {
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
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_ack_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_rx_rec_full_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_clr_tx_send_empty_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_clr;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_rxfifo_full_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_txfifo_empty_int_ena> {
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
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_slave_tran_comp_int_ena> {
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
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_master_tran_comp_int_ena> {
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
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_ack_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_rx_rec_full_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_ena_tx_send_empty_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_ena;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_rxfifo_full_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_txfifo_empty_int_raw> {
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
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_slave_tran_comp_int_raw> {
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
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_master_tran_comp_int_raw> {
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
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_ack_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_rx_rec_full_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_raw_tx_send_empty_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_raw;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_rxfifo_full_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_txfifo_empty_int_st> {
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
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_slave_tran_comp_int_st> {
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
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_master_tran_comp_int_st> {
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
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_ack_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_rx_rec_full_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_int_status_tx_send_empty_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_int_status;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_rxfifo_st_rxfifo_start_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_rxfifo_st;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_rxfifo_st_rxfifo_end_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_rxfifo_st;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_rxfifo_st_txfifo_start_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_rxfifo_st;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_rxfifo_st_txfifo_end_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_rxfifo_st;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_filter_cfg_scl_filter_thres> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_filter_cfg;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_filter_cfg_scl_filter_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_filter_cfg;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_high_period_scl_high_period> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_high_period;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 14u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_low_period_scl_low_period> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_low_period;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 14u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_rstart_setup_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_rstart_setup;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_start_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_start_hold;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_stop_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_stop_hold;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 14u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_scl_stop_setup_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_scl_stop_setup;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sda_filter_cfg_sda_filter_thres> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sda_filter_cfg;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sda_filter_cfg_sda_filter_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sda_filter_cfg;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sda_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sda_hold;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c0_sda_sample_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sda_sample;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
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
struct RegisterFieldTraits<FieldId::field_i2c0_sr_ack_rec> {
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
struct RegisterFieldTraits<FieldId::field_i2c0_sr_time_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sr;
  static constexpr std::uint16_t kBitOffset = 2u;
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
struct RegisterFieldTraits<FieldId::field_i2c0_sr_byte_trans> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_sr;
  static constexpr std::uint16_t kBitOffset = 6u;
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
struct RegisterFieldTraits<FieldId::field_i2c0_to_time_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c0_to;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_comd_s_command> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_comd_s;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 14u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_comd_s_command_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_comd_s;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_ctr_sda_force_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_ctr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_ctr_scl_force_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_ctr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_ctr_sample_scl_level> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_ctr;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_ctr_ms_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_ctr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_ctr_trans_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_ctr;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_ctr_tx_lsb_first> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_ctr;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_ctr_rx_lsb_first> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_ctr;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_ctr_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_ctr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_data_fifo_rdata> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_data;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_date_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_fifo_conf_rxfifo_full_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_fifo_conf_txfifo_empty_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_fifo_conf_nonfifo_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_fifo_conf_fifo_addr_cfg_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_fifo_conf_rx_fifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_fifo_conf_tx_fifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_fifo_conf_nonfifo_rx_thres> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_fifo_conf_nonfifo_tx_thres> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_fifo_conf;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_clr_rxfifo_full_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_clr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_clr_txfifo_empty_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_clr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_clr_rxfifo_ovf_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_clr;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_clr_end_detect_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_clr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_clr_slave_tran_comp_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_clr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_clr_arbitration_lost_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_clr;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_clr_master_tran_comp_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_clr;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_clr_trans_complete_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_clr;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_clr_time_out_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_clr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_clr_trans_start_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_clr;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_clr_ack_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_clr;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_clr_rx_rec_full_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_clr;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_clr_tx_send_empty_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_clr;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_ena_rxfifo_full_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_ena;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_ena_txfifo_empty_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_ena;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_ena_rxfifo_ovf_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_ena;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_ena_end_detect_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_ena;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_ena_slave_tran_comp_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_ena;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_ena_arbitration_lost_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_ena;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_ena_master_tran_comp_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_ena;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_ena_trans_complete_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_ena;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_ena_time_out_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_ena;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_ena_trans_start_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_ena;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_ena_ack_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_ena;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_ena_rx_rec_full_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_ena;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_ena_tx_send_empty_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_ena;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_raw_rxfifo_full_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_raw;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_raw_txfifo_empty_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_raw;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_raw_rxfifo_ovf_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_raw;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_raw_end_detect_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_raw;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_raw_slave_tran_comp_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_raw;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_raw_arbitration_lost_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_raw;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_raw_master_tran_comp_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_raw;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_raw_trans_complete_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_raw;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_raw_time_out_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_raw;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_raw_trans_start_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_raw;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_raw_ack_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_raw;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_raw_rx_rec_full_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_raw;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_raw_tx_send_empty_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_raw;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_status_rxfifo_full_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_status_txfifo_empty_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_status;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_status_rxfifo_ovf_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_status;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_status_end_detect_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_status;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_status_slave_tran_comp_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_status;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_status_arbitration_lost_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_status;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_status_master_tran_comp_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_status;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_status_trans_complete_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_status;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_status_time_out_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_status;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_status_trans_start_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_status;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_status_ack_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_status;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_status_rx_rec_full_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_status;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_int_status_tx_send_empty_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_int_status;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_rxfifo_st_rxfifo_start_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_rxfifo_st;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_rxfifo_st_rxfifo_end_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_rxfifo_st;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_rxfifo_st_txfifo_start_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_rxfifo_st;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_rxfifo_st_txfifo_end_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_rxfifo_st;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_scl_filter_cfg_scl_filter_thres> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_scl_filter_cfg;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_scl_filter_cfg_scl_filter_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_scl_filter_cfg;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_scl_high_period_scl_high_period> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_scl_high_period;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 14u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_scl_low_period_scl_low_period> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_scl_low_period;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 14u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_scl_rstart_setup_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_scl_rstart_setup;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_scl_start_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_scl_start_hold;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_scl_stop_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_scl_stop_hold;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 14u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_scl_stop_setup_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_scl_stop_setup;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sda_filter_cfg_sda_filter_thres> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sda_filter_cfg;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sda_filter_cfg_sda_filter_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sda_filter_cfg;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sda_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sda_hold;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sda_sample_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sda_sample;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_slave_addr_slave_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_slave_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 15u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_slave_addr_addr_10bit_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_slave_addr;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sr_ack_rec> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sr_slave_rw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sr_time_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sr;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sr_arb_lost> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sr_bus_busy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sr_slave_addressed> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sr;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sr_byte_trans> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sr;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sr_rxfifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sr_txfifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sr;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sr_scl_main_state_last> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sr;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_sr_scl_state_last> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_sr;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_i2c1_to_time_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_i2c1_to;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sardate_sar_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sardate;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_atten1_sar1_atten> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_atten1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_atten2_sar2_atten> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_atten2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl1_sw_fstep> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl1_sw_tone_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl1_debug_bit_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl1;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl1_dac_dig_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl1;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl1_dac_clk_force_low> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl1;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl1_dac_clk_force_high> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl1;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl1_dac_clk_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl1;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl2_dac_dc1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl2_dac_dc2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl2;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl2_dac_scale1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl2;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl2_dac_scale2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl2;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl2_dac_inv1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl2;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl2_dac_inv2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl2;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl2_dac_cw_en1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl2;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_dac_ctrl2_dac_cw_en2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_dac_ctrl2;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_i2c_ctrl_sar_i2c_ctrl> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_i2c_ctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_i2c_ctrl_sar_i2c_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_i2c_ctrl;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_i2c_ctrl_sar_i2c_start_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_i2c_ctrl;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl_xpd_sar_amp_fsm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl_amp_rst_fb_fsm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl_amp_short_ref_fsm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl_amp_short_ref_gnd_fsm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl_xpd_sar_fsm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl_sar_rstb_fsm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl_sar2_xpd_wait> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl2_sar1_dac_xpd_fsm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl2_sar1_dac_xpd_fsm_idle> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl2;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl2_xpd_sar_amp_fsm_idle> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl2;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl2_amp_rst_fb_fsm_idle> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl2;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl2_amp_short_ref_fsm_idle> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl2;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl2_amp_short_ref_gnd_fsm_idle> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl2;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl2_xpd_sar_fsm_idle> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl2;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl2_sar_rstb_fsm_idle> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl2;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl2_sar2_rstb_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl2;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl2_amp_rst_fb_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl2;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl2_amp_short_ref_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl2;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_ctrl2_amp_short_ref_gnd_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_ctrl2;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_start1_meas1_data_sar> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_start1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_start1_meas1_done_sar> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_start1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_start1_meas1_start_sar> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_start1;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_start1_meas1_start_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_start1;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_start1_sar1_en_pad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_start1;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_start1_sar1_en_pad_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_start1;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_start2_meas2_data_sar> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_start2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_start2_meas2_done_sar> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_start2;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_start2_meas2_start_sar> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_start2;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_start2_meas2_start_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_start2;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_start2_sar2_en_pad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_start2;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_start2_sar2_en_pad_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_start2;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_wait1_sar_amp_wait1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_wait1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_wait1_sar_amp_wait2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_wait1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_wait2_force_xpd_sar_sw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_wait2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_wait2_sar_amp_wait3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_wait2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_wait2_force_xpd_amp> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_wait2;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_wait2_force_xpd_sar> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_wait2;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_meas_wait2_sar2_rstb_wait> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_meas_wait2;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_mem_wr_ctrl_mem_wr_addr_init> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_mem_wr_ctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_mem_wr_ctrl_mem_wr_addr_size> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_mem_wr_ctrl;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_mem_wr_ctrl_rtc_mem_wr_offst_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_mem_wr_ctrl;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_nouse_sar_nouse> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_nouse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl_sar1_clk_div> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl_sar1_sample_cycle> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl_sar1_sample_bit> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl_sar1_clk_gated> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl_sar1_sample_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl_sar1_dig_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl_sar1_data_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl2_sar2_clk_div> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl2_sar2_sample_cycle> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl2;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl2_sar2_sample_bit> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl2;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl2_sar2_clk_gated> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl2;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl2_sar2_sample_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl2;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl2_sar2_pwdet_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl2;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl2_sar2_dig_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl2;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_ctrl2_sar2_data_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_ctrl2;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_status1_sar1_reader_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_status1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_read_status2_sar2_reader_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_read_status2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_slave_addr1_i2c_slave_addr1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_slave_addr1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_slave_addr1_i2c_slave_addr0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_slave_addr1;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_slave_addr1_meas_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_slave_addr1;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_slave_addr2_i2c_slave_addr3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_slave_addr2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_slave_addr2_i2c_slave_addr2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_slave_addr2;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_slave_addr3_i2c_slave_addr5> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_slave_addr3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_slave_addr3_i2c_slave_addr4> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_slave_addr3;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_slave_addr3_tsens_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_slave_addr3;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_slave_addr3_tsens_rdy_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_slave_addr3;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_slave_addr4_i2c_slave_addr7> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_slave_addr4;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_slave_addr4_i2c_slave_addr6> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_slave_addr4;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_slave_addr4_i2c_rdata> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_slave_addr4;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_slave_addr4_i2c_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_slave_addr4;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_start_force_sar1_bit_width> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_start_force;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_start_force_sar2_bit_width> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_start_force;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_start_force_sar2_en_test> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_start_force;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_start_force_sar2_pwdet_cct> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_start_force;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_start_force_ulp_cp_force_start_top> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_start_force;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_start_force_ulp_cp_start_top> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_start_force;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_start_force_sarclk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_start_force;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_start_force_pc_init> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_start_force;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_start_force_sar2_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_start_force;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_start_force_sar1_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_start_force;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_start_force_sar2_pwdet_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_start_force;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_ctrl1_touch_meas_delay> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_ctrl1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_ctrl1_touch_xpd_wait> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_ctrl1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_ctrl1_touch_out_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_ctrl1;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_ctrl1_touch_out_1en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_ctrl1;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_ctrl1_xpd_hall_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_ctrl1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_ctrl1_hall_phase_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_ctrl1;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_ctrl2_touch_meas_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_ctrl2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_ctrl2_touch_meas_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_ctrl2;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_ctrl2_touch_start_fsm_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_ctrl2;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_ctrl2_touch_start_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_ctrl2;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_ctrl2_touch_start_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_ctrl2;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_ctrl2_touch_sleep_cycles> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_ctrl2;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_ctrl2_touch_meas_en_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_ctrl2;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_enable_touch_pad_worken> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_enable;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_enable_touch_pad_outen2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_enable;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_enable_touch_pad_outen1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_enable;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_out1_touch_meas_out1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_out1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_out1_touch_meas_out0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_out1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_out2_touch_meas_out3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_out2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_out2_touch_meas_out2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_out2;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_out3_touch_meas_out5> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_out3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_out3_touch_meas_out4> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_out3;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_out4_touch_meas_out7> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_out4;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_out4_touch_meas_out6> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_out4;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_out5_touch_meas_out9> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_out5;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_out5_touch_meas_out8> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_out5;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_thres1_touch_out_th1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_thres1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_thres1_touch_out_th0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_thres1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_thres2_touch_out_th3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_thres2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_thres2_touch_out_th2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_thres2;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_thres3_touch_out_th5> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_thres3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_thres3_touch_out_th4> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_thres3;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_thres4_touch_out_th7> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_thres4;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_thres4_touch_out_th6> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_thres4;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_thres5_touch_out_th9> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_thres5;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_touch_thres5_touch_out_th8> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_touch_thres5;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_tsens_ctrl_tsens_xpd_wait> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_tsens_ctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_tsens_ctrl_tsens_xpd_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_tsens_ctrl;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_tsens_ctrl_tsens_clk_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_tsens_ctrl;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_tsens_ctrl_tsens_clk_gated> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_tsens_ctrl;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_tsens_ctrl_tsens_in_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_tsens_ctrl;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_tsens_ctrl_tsens_clk_div> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_tsens_ctrl;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_tsens_ctrl_tsens_power_up> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_tsens_ctrl;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_tsens_ctrl_tsens_power_up_force> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_tsens_ctrl;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_sar_tsens_ctrl_tsens_dump_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_sar_tsens_ctrl;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_ulp_cp_sleep_cyc0_sleep_cycles_s0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_ulp_cp_sleep_cyc0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_ulp_cp_sleep_cyc1_sleep_cycles_s1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_ulp_cp_sleep_cyc1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_ulp_cp_sleep_cyc2_sleep_cycles_s2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_ulp_cp_sleep_cyc2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_ulp_cp_sleep_cyc3_sleep_cycles_s3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_ulp_cp_sleep_cyc3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_sens_ulp_cp_sleep_cyc4_sleep_cycles_s4> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_sens_ulp_cp_sleep_cyc4;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
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
struct RegisterFieldTraits<FieldId::field_spi0_cache_fctrl_cache_usr_cmd_4byte> {
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
struct RegisterFieldTraits<FieldId::field_spi0_cache_fctrl_cache_flash_pes_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_sctrl_usr_sram_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_sctrl_usr_sram_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_sctrl_usr_wr_sram_dummy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_sctrl_usr_rd_sram_dummy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_sctrl_cache_sram_usr_rcmd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_sctrl_sram_bytes_len> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_sctrl_sram_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_sctrl_sram_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cache_sctrl_cache_sram_usr_wcmd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_clock_clkcnt_l> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_clock;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_clock_clkcnt_h> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_clock;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_clock_clkcnt_n> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_clock;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_clock_clkdiv_pre> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_clock;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 13u;
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
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_per> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_pes> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_usr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_hpm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_res> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_dp> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_ce> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_be> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_se> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_pp> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_wrsr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_rdsr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_rdid> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_wrdi> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_wren> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_cmd_flash_read> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_cmd;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_fcs_crc_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_tx_crc_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_wait_flash_idle_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 12u;
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
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_resandres> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 15u;
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
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_wrsr_2b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 22u;
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
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_rd_bit_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl_wr_bit_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl1_cs_hold_delay_res> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl1_cs_hold_delay> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl1;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl2_setup_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl2_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl2;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl2_ck_out_low_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl2;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl2_ck_out_high_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl2;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl2_miso_delay_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl2;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl2_miso_delay_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl2;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl2_mosi_delay_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl2;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl2_mosi_delay_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl2;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl2_cs_delay_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl2;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ctrl2_cs_delay_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ctrl2;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_date_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_conf_in_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_conf;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_conf_out_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_conf;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_conf_ahbm_fifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_conf;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_conf_ahbm_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_conf;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_conf_in_loop_test> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_conf;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_conf_out_loop_test> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_conf;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_conf_out_auto_wrback> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_conf;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_conf_out_eof_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_conf;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_conf_outdscr_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_conf;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_conf_indscr_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_conf;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_conf_out_data_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_conf;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_conf_dma_rx_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_conf;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_conf_dma_tx_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_conf;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_conf_dma_continue> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_conf;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_clr_inlink_dscr_empty_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_clr_outlink_dscr_error_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_clr_inlink_dscr_error_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_clr_in_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_clr_in_err_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_clr_in_suc_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_clr_out_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_clr_out_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_clr_out_total_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_ena_inlink_dscr_empty_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_ena_outlink_dscr_error_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_ena_inlink_dscr_error_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_ena_in_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_ena_in_err_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_ena_in_suc_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_ena_out_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_ena_out_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_ena_out_total_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_raw_inlink_dscr_empty_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_raw_outlink_dscr_error_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_raw_inlink_dscr_error_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_raw_in_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_raw_in_err_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_raw_in_suc_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_raw_out_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_raw_out_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_raw_out_total_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_st_inlink_dscr_empty_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_st_outlink_dscr_error_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_st_inlink_dscr_error_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_st_in_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_st_in_err_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_st_in_suc_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_st_out_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_st_out_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_int_st_out_total_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_in_link_inlink_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_in_link_inlink_auto_ret> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_in_link_inlink_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_in_link_inlink_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_in_link_inlink_restart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_out_link_outlink_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_out_link_outlink_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_out_link_outlink_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_out_link_outlink_restart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_rstatus_dma_out_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_rstatus;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_status_dma_rx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_status_dma_tx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_status;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_dma_tstatus_dma_in_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_dma_tstatus;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ext0_t_pp_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ext0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ext0_t_pp_shift> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ext0;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ext0_t_pp_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ext0;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ext1_t_erase_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ext1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ext1_t_erase_shift> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ext1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ext1_t_erase_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ext1;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ext2_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ext2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_ext3_int_hold_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_ext3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_inlink_dscr_dma_inlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_inlink_dscr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_inlink_dscr_bf0_dma_inlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_inlink_dscr_bf0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_inlink_dscr_bf1_dma_inlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_inlink_dscr_bf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_in_err_eof_des_addr_dma_in_err_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_in_err_eof_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_in_suc_eof_des_addr_dma_in_suc_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_in_suc_eof_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_miso_dlen_usr_miso_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_miso_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_mosi_dlen_usr_mosi_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_mosi_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_outlink_dscr_dma_outlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_outlink_dscr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_outlink_dscr_bf0_dma_outlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_outlink_dscr_bf0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_outlink_dscr_bf1_dma_outlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_outlink_dscr_bf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_out_eof_bfr_des_addr_dma_out_eof_bfr_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_out_eof_bfr_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_out_eof_des_addr_dma_out_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_out_eof_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_pin_cs0_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_pin;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_pin_cs1_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_pin;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_pin_cs2_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_pin;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_pin_ck_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_pin;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_pin_master_cs_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_pin;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_pin_master_ck_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_pin;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_pin_ck_idle_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_pin;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_pin_cs_keep_active> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_pin;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_rd_status_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_rd_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
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
struct RegisterFieldTraits<FieldId::field_spi0_rd_status_status_ext> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_rd_status;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_slv_rd_buf_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_slv_wr_buf_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_slv_rd_sta_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_slv_wr_sta_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_trans_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_int_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_cs_i_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_slv_last_command> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_slv_last_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_trans_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_slv_cmd_define> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_slv_wr_rd_sta_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_slv_wr_rd_buf_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave_sync_reset> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave1_slv_rdbuf_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave1_slv_wrbuf_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave1;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave1_slv_rdsta_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave1;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave1_slv_wrsta_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave1;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave1_slv_wr_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave1;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave1_slv_rd_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave1;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave1_slv_status_readback> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave1;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave1_slv_status_fast_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave1_slv_status_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave1;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave2_slv_rdsta_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave2_slv_wrsta_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave2;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave2_slv_rdbuf_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave2;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave2_slv_wrbuf_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave2;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave3_slv_rdbuf_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave3_slv_wrbuf_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave3;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave3_slv_rdsta_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave3;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slave3_slv_wrsta_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slave3;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slv_rdbuf_dlen_slv_rdbuf_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slv_rdbuf_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slv_rd_bit_slv_rdata_bit> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slv_rd_bit;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slv_wrbuf_dlen_slv_wrbuf_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slv_wrbuf_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_slv_wr_status_slv_wr_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_slv_wr_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_sram_cmd_sram_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_sram_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_sram_cmd_sram_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_sram_cmd;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_sram_cmd_sram_rstio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_sram_cmd;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_sram_drd_cmd_cache_sram_usr_rd_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_sram_drd_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_sram_drd_cmd_cache_sram_usr_rd_cmd_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_sram_drd_cmd;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_sram_dwr_cmd_cache_sram_usr_wr_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_sram_dwr_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_sram_dwr_cmd_cache_sram_usr_wr_cmd_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_sram_dwr_cmd;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_tx_crc_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_tx_crc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_doutdin> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_cs_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_cs_setup> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_ck_i_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_ck_out_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_rd_byte_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_wr_byte_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_fwrite_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_fwrite_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_fwrite_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_fwrite_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_sio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_hold_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_dout_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_din_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_dummy_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_addr_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_cmd_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_prep_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_miso_highpart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_mosi_highpart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 25u;
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
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_mosi> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_miso> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 28u;
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
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user_usr_command> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user1_usr_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_user1_usr_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_user1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
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
struct RegisterFieldTraits<FieldId::field_spi0_w0_buf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w1_buf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w10_buf10> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w10;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w11_buf11> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w11;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w12_buf12> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w12;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w13_buf13> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w13;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w14_buf14> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w14;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w15_buf15> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w15;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w2_buf2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w3_buf3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w4_buf4> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w4;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w5_buf5> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w5;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w6_buf6> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w6;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w7_buf7> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w7;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w8_buf8> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w8;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi0_w9_buf9> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi0_w9;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_fctrl_cache_req_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_fctrl_cache_usr_cmd_4byte> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_fctrl_cache_flash_usr_cmd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_fctrl_cache_flash_pes_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_sctrl_usr_sram_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_sctrl_usr_sram_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_sctrl_usr_wr_sram_dummy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_sctrl_usr_rd_sram_dummy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_sctrl_cache_sram_usr_rcmd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_sctrl_sram_bytes_len> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_sctrl_sram_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_sctrl_sram_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cache_sctrl_cache_sram_usr_wcmd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_clock_clkcnt_l> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_clock;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_clock_clkcnt_h> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_clock;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_clock_clkcnt_n> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_clock;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_clock_clkdiv_pre> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_clock;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 13u;
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
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_per> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_cmd;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_cmd_flash_pes> {
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
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_wait_flash_idle_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 12u;
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
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_rd_bit_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl_wr_bit_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl1_cs_hold_delay_res> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl1_cs_hold_delay> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl1;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl2_setup_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl2_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl2;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl2_ck_out_low_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl2;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl2_ck_out_high_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl2;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl2_miso_delay_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl2;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl2_miso_delay_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl2;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl2_mosi_delay_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl2;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl2_mosi_delay_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl2;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl2_cs_delay_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl2;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ctrl2_cs_delay_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ctrl2;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_date_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_conf_in_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_conf;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_conf_out_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_conf;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_conf_ahbm_fifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_conf;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_conf_ahbm_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_conf;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_conf_in_loop_test> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_conf;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_conf_out_loop_test> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_conf;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_conf_out_auto_wrback> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_conf;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_conf_out_eof_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_conf;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_conf_outdscr_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_conf;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_conf_indscr_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_conf;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_conf_out_data_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_conf;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_conf_dma_rx_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_conf;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_conf_dma_tx_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_conf;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_conf_dma_continue> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_conf;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_clr_inlink_dscr_empty_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_clr_outlink_dscr_error_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_clr_inlink_dscr_error_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_clr_in_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_clr_in_err_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_clr_in_suc_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_clr_out_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_clr_out_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_clr_out_total_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_ena_inlink_dscr_empty_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_ena_outlink_dscr_error_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_ena_inlink_dscr_error_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_ena_in_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_ena_in_err_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_ena_in_suc_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_ena_out_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_ena_out_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_ena_out_total_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_raw_inlink_dscr_empty_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_raw_outlink_dscr_error_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_raw_inlink_dscr_error_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_raw_in_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_raw_in_err_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_raw_in_suc_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_raw_out_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_raw_out_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_raw_out_total_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_st_inlink_dscr_empty_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_st_outlink_dscr_error_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_st_inlink_dscr_error_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_st_in_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_st_in_err_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_st_in_suc_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_st_out_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_st_out_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_int_st_out_total_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_in_link_inlink_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_in_link_inlink_auto_ret> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_in_link_inlink_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_in_link_inlink_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_in_link_inlink_restart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_out_link_outlink_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_out_link_outlink_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_out_link_outlink_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_out_link_outlink_restart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_rstatus_dma_out_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_rstatus;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_status_dma_rx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_status_dma_tx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_status;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_dma_tstatus_dma_in_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_dma_tstatus;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ext0_t_pp_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ext0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ext0_t_pp_shift> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ext0;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ext0_t_pp_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ext0;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ext1_t_erase_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ext1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ext1_t_erase_shift> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ext1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ext1_t_erase_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ext1;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ext2_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ext2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_ext3_int_hold_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_ext3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_inlink_dscr_dma_inlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_inlink_dscr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_inlink_dscr_bf0_dma_inlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_inlink_dscr_bf0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_inlink_dscr_bf1_dma_inlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_inlink_dscr_bf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_in_err_eof_des_addr_dma_in_err_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_in_err_eof_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_in_suc_eof_des_addr_dma_in_suc_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_in_suc_eof_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_miso_dlen_usr_miso_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_miso_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_mosi_dlen_usr_mosi_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_mosi_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_outlink_dscr_dma_outlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_outlink_dscr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_outlink_dscr_bf0_dma_outlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_outlink_dscr_bf0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_outlink_dscr_bf1_dma_outlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_outlink_dscr_bf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_out_eof_bfr_des_addr_dma_out_eof_bfr_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_out_eof_bfr_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_out_eof_des_addr_dma_out_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_out_eof_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_pin_cs0_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_pin;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_pin_cs1_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_pin;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_pin_cs2_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_pin;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_pin_ck_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_pin;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_pin_master_cs_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_pin;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_pin_master_ck_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_pin;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_pin_ck_idle_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_pin;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_pin_cs_keep_active> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_pin;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
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
struct RegisterFieldTraits<FieldId::field_spi1_rd_status_status_ext> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_rd_status;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_slv_rd_buf_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_slv_wr_buf_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_slv_rd_sta_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_slv_wr_sta_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_trans_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_int_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_cs_i_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_slv_last_command> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_slv_last_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_trans_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_slv_cmd_define> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_slv_wr_rd_sta_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_slv_wr_rd_buf_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave_sync_reset> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave1_slv_rdbuf_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave1_slv_wrbuf_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave1;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave1_slv_rdsta_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave1;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave1_slv_wrsta_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave1;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave1_slv_wr_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave1;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave1_slv_rd_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave1;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave1_slv_status_readback> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave1;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave1_slv_status_fast_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave1_slv_status_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave1;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave2_slv_rdsta_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave2_slv_wrsta_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave2;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave2_slv_rdbuf_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave2;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave2_slv_wrbuf_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave2;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave3_slv_rdbuf_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave3_slv_wrbuf_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave3;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave3_slv_rdsta_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave3;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slave3_slv_wrsta_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slave3;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slv_rdbuf_dlen_slv_rdbuf_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slv_rdbuf_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slv_rd_bit_slv_rdata_bit> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slv_rd_bit;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slv_wrbuf_dlen_slv_wrbuf_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slv_wrbuf_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_slv_wr_status_slv_wr_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_slv_wr_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sram_cmd_sram_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sram_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sram_cmd_sram_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sram_cmd;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sram_cmd_sram_rstio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sram_cmd;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sram_drd_cmd_cache_sram_usr_rd_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sram_drd_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sram_drd_cmd_cache_sram_usr_rd_cmd_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sram_drd_cmd;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sram_dwr_cmd_cache_sram_usr_wr_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sram_dwr_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_sram_dwr_cmd_cache_sram_usr_wr_cmd_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_sram_dwr_cmd;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_tx_crc_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_tx_crc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_doutdin> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_cs_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_cs_setup> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_ck_i_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_ck_out_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_rd_byte_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_wr_byte_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 11u;
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
struct RegisterFieldTraits<FieldId::field_spi1_user_sio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_hold_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_dout_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_din_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_dummy_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_addr_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_cmd_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user_usr_prep_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user;
  static constexpr std::uint16_t kBitOffset = 23u;
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
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi1_user1_usr_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi1_user1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
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
struct RegisterFieldTraits<FieldId::field_spi2_cache_fctrl_cache_req_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cache_fctrl_cache_usr_cmd_4byte> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cache_fctrl_cache_flash_usr_cmd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cache_fctrl_cache_flash_pes_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cache_sctrl_usr_sram_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cache_sctrl_usr_sram_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cache_sctrl_usr_wr_sram_dummy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cache_sctrl_usr_rd_sram_dummy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cache_sctrl_cache_sram_usr_rcmd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cache_sctrl_sram_bytes_len> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cache_sctrl_sram_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cache_sctrl_sram_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cache_sctrl_cache_sram_usr_wcmd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 28u;
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
  static constexpr std::uint16_t kBitWidth = 13u;
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
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_per> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_pes> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_usr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_hpm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_res> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_dp> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_ce> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_be> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_se> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_pp> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_wrsr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_rdsr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_rdid> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_wrdi> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_wren> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_cmd_flash_read> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_cmd;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_fcs_crc_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_tx_crc_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_wait_flash_idle_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_fastrd_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 13u;
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
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_resandres> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_fread_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_wp> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_wrsr_2b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_fread_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl_fread_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl;
  static constexpr std::uint16_t kBitOffset = 24u;
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
struct RegisterFieldTraits<FieldId::field_spi2_ctrl1_cs_hold_delay_res> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl1_cs_hold_delay> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl1;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl2_setup_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl2_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl2;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl2_ck_out_low_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl2;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl2_ck_out_high_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl2;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl2_miso_delay_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl2;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl2_miso_delay_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl2;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl2_mosi_delay_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl2;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl2_mosi_delay_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl2;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl2_cs_delay_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl2;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ctrl2_cs_delay_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ctrl2;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_date_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_in_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_out_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_ahbm_fifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_ahbm_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_in_loop_test> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_out_loop_test> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_out_auto_wrback> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_out_eof_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_outdscr_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_indscr_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_out_data_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_dma_rx_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_dma_tx_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_conf_dma_continue> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_conf;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_inlink_dscr_empty_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_outlink_dscr_error_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_inlink_dscr_error_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_in_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_in_err_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_in_suc_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_out_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_out_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_clr_out_total_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_inlink_dscr_empty_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_outlink_dscr_error_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_inlink_dscr_error_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_in_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_in_err_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_in_suc_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_out_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_out_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_ena_out_total_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_inlink_dscr_empty_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_outlink_dscr_error_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_inlink_dscr_error_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_in_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_in_err_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_in_suc_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_out_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_out_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_raw_out_total_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_inlink_dscr_empty_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_outlink_dscr_error_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_inlink_dscr_error_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_in_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_in_err_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_in_suc_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_out_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_out_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_int_st_out_total_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_in_link_inlink_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_in_link_inlink_auto_ret> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_in_link_inlink_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_in_link_inlink_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_in_link_inlink_restart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_out_link_outlink_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_out_link_outlink_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_out_link_outlink_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_out_link_outlink_restart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_rstatus_dma_out_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_rstatus;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_status_dma_rx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_status_dma_tx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_status;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_dma_tstatus_dma_in_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_dma_tstatus;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ext0_t_pp_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ext0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ext0_t_pp_shift> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ext0;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ext0_t_pp_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ext0;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ext1_t_erase_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ext1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ext1_t_erase_shift> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ext1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ext1_t_erase_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ext1;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ext2_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ext2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_ext3_int_hold_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_ext3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_inlink_dscr_dma_inlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_inlink_dscr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_inlink_dscr_bf0_dma_inlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_inlink_dscr_bf0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_inlink_dscr_bf1_dma_inlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_inlink_dscr_bf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_in_err_eof_des_addr_dma_in_err_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_in_err_eof_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_in_suc_eof_des_addr_dma_in_suc_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_in_suc_eof_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_miso_dlen_usr_miso_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_miso_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_mosi_dlen_usr_mosi_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_mosi_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_outlink_dscr_dma_outlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_outlink_dscr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_outlink_dscr_bf0_dma_outlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_outlink_dscr_bf0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_outlink_dscr_bf1_dma_outlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_outlink_dscr_bf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_out_eof_bfr_des_addr_dma_out_eof_bfr_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_out_eof_bfr_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_out_eof_des_addr_dma_out_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_out_eof_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_pin_cs0_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_pin;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_pin_cs1_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_pin;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_pin_cs2_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_pin;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_pin_ck_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_pin;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_pin_master_cs_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_pin;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_pin_master_ck_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_pin;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_pin_ck_idle_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_pin;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_pin_cs_keep_active> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_pin;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_rd_status_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_rd_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_rd_status_wb_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_rd_status;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_rd_status_status_ext> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_rd_status;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_slv_rd_buf_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_slv_wr_buf_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_slv_rd_sta_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_slv_wr_sta_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_trans_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_int_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_cs_i_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_slv_last_command> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_slv_last_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_trans_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_slv_cmd_define> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_slv_wr_rd_sta_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_slv_wr_rd_buf_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave_sync_reset> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave1_slv_rdbuf_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave1_slv_wrbuf_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave1;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave1_slv_rdsta_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave1;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave1_slv_wrsta_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave1;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave1_slv_wr_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave1;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave1_slv_rd_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave1;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave1_slv_status_readback> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave1;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave1_slv_status_fast_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave1_slv_status_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave1;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave2_slv_rdsta_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave2_slv_wrsta_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave2;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave2_slv_rdbuf_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave2;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave2_slv_wrbuf_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave2;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave3_slv_rdbuf_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave3_slv_wrbuf_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave3;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave3_slv_rdsta_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave3;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slave3_slv_wrsta_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slave3;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slv_rdbuf_dlen_slv_rdbuf_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slv_rdbuf_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slv_rd_bit_slv_rdata_bit> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slv_rd_bit;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slv_wrbuf_dlen_slv_wrbuf_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slv_wrbuf_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_slv_wr_status_slv_wr_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_slv_wr_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_sram_cmd_sram_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_sram_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_sram_cmd_sram_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_sram_cmd;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_sram_cmd_sram_rstio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_sram_cmd;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_sram_drd_cmd_cache_sram_usr_rd_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_sram_drd_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_sram_drd_cmd_cache_sram_usr_rd_cmd_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_sram_drd_cmd;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_sram_dwr_cmd_cache_sram_usr_wr_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_sram_dwr_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_sram_dwr_cmd_cache_sram_usr_wr_cmd_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_sram_dwr_cmd;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_tx_crc_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_tx_crc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
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
struct RegisterFieldTraits<FieldId::field_spi2_user_cs_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_cs_setup> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_ck_i_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_ck_out_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_rd_byte_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_wr_byte_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 11u;
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
struct RegisterFieldTraits<FieldId::field_spi2_user_fwrite_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_fwrite_qio> {
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
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_hold_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_dout_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_din_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_dummy_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_addr_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_cmd_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi2_user_usr_prep_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user;
  static constexpr std::uint16_t kBitOffset = 23u;
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
struct RegisterFieldTraits<FieldId::field_spi2_user1_usr_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi2_user1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
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
struct RegisterFieldTraits<FieldId::field_spi3_cache_fctrl_cache_req_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cache_fctrl_cache_usr_cmd_4byte> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cache_fctrl_cache_flash_usr_cmd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cache_fctrl_cache_flash_pes_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cache_fctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cache_sctrl_usr_sram_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cache_sctrl_usr_sram_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cache_sctrl_usr_wr_sram_dummy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cache_sctrl_usr_rd_sram_dummy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cache_sctrl_cache_sram_usr_rcmd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cache_sctrl_sram_bytes_len> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cache_sctrl_sram_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cache_sctrl_sram_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cache_sctrl_cache_sram_usr_wcmd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cache_sctrl;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_clock_clkcnt_l> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_clock;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_clock_clkcnt_h> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_clock;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_clock_clkcnt_n> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_clock;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_clock_clkdiv_pre> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_clock;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 13u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_clock_clk_equ_sysclk> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_clock;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_per> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_pes> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_usr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_hpm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_res> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_dp> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_ce> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_be> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_se> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_pp> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_wrsr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_rdsr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_rdid> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_wrdi> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_wren> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_cmd_flash_read> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_cmd;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl_fcs_crc_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl_tx_crc_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl_wait_flash_idle_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl_fastrd_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl_fread_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl_resandres> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl_fread_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl_wp> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl_wrsr_2b> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl_fread_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl_fread_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl_rd_bit_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl_wr_bit_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl1_cs_hold_delay_res> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl1_cs_hold_delay> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl1;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl2_setup_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl2_hold_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl2;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl2_ck_out_low_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl2;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl2_ck_out_high_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl2;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl2_miso_delay_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl2;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl2_miso_delay_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl2;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl2_mosi_delay_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl2;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl2_mosi_delay_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl2;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl2_cs_delay_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl2;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ctrl2_cs_delay_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ctrl2;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_date_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 28u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_conf_in_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_conf;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_conf_out_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_conf;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_conf_ahbm_fifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_conf;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_conf_ahbm_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_conf;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_conf_in_loop_test> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_conf;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_conf_out_loop_test> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_conf;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_conf_out_auto_wrback> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_conf;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_conf_out_eof_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_conf;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_conf_outdscr_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_conf;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_conf_indscr_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_conf;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_conf_out_data_burst_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_conf;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_conf_dma_rx_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_conf;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_conf_dma_tx_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_conf;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_conf_dma_continue> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_conf;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_clr_inlink_dscr_empty_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_clr_outlink_dscr_error_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_clr_inlink_dscr_error_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_clr_in_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_clr_in_err_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_clr_in_suc_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_clr_out_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_clr_out_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_clr_out_total_eof_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_clr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_ena_inlink_dscr_empty_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_ena_outlink_dscr_error_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_ena_inlink_dscr_error_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_ena_in_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_ena_in_err_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_ena_in_suc_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_ena_out_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_ena_out_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_ena_out_total_eof_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_ena;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_raw_inlink_dscr_empty_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_raw_outlink_dscr_error_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_raw_inlink_dscr_error_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_raw_in_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_raw_in_err_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_raw_in_suc_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_raw_out_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_raw_out_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_raw_out_total_eof_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_raw;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_st_inlink_dscr_empty_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_st_outlink_dscr_error_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_st_inlink_dscr_error_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_st_in_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_st_in_err_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_st_in_suc_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_st_out_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_st_out_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_int_st_out_total_eof_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_int_st;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_in_link_inlink_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_in_link_inlink_auto_ret> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_in_link_inlink_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_in_link_inlink_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_in_link_inlink_restart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_in_link;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_out_link_outlink_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_out_link_outlink_stop> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_out_link_outlink_start> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_out_link_outlink_restart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_out_link;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_rstatus_dma_out_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_rstatus;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_status_dma_rx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_status_dma_tx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_status;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_dma_tstatus_dma_in_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_dma_tstatus;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ext0_t_pp_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ext0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ext0_t_pp_shift> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ext0;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ext0_t_pp_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ext0;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ext1_t_erase_time> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ext1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 12u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ext1_t_erase_shift> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ext1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ext1_t_erase_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ext1;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ext2_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ext2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_ext3_int_hold_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_ext3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_inlink_dscr_dma_inlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_inlink_dscr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_inlink_dscr_bf0_dma_inlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_inlink_dscr_bf0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_inlink_dscr_bf1_dma_inlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_inlink_dscr_bf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_in_err_eof_des_addr_dma_in_err_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_in_err_eof_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_in_suc_eof_des_addr_dma_in_suc_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_in_suc_eof_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_miso_dlen_usr_miso_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_miso_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_mosi_dlen_usr_mosi_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_mosi_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_outlink_dscr_dma_outlink_dscr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_outlink_dscr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_outlink_dscr_bf0_dma_outlink_dscr_bf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_outlink_dscr_bf0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_outlink_dscr_bf1_dma_outlink_dscr_bf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_outlink_dscr_bf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_out_eof_bfr_des_addr_dma_out_eof_bfr_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_out_eof_bfr_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_out_eof_des_addr_dma_out_eof_des_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_out_eof_des_addr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_pin_cs0_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_pin;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_pin_cs1_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_pin;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_pin_cs2_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_pin;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_pin_ck_dis> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_pin;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_pin_master_cs_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_pin;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_pin_master_ck_sel> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_pin;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_pin_ck_idle_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_pin;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_pin_cs_keep_active> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_pin;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_rd_status_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_rd_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_rd_status_wb_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_rd_status;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_rd_status_status_ext> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_rd_status;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_slv_rd_buf_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_slv_wr_buf_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_slv_rd_sta_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_slv_wr_sta_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_trans_done> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_int_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_cs_i_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_slv_last_command> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_slv_last_state> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_trans_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_slv_cmd_define> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_slv_wr_rd_sta_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_slv_wr_rd_buf_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_mode> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave_sync_reset> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave1_slv_rdbuf_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave1_slv_wrbuf_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave1;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave1_slv_rdsta_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave1;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave1_slv_wrsta_dummy_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave1;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave1_slv_wr_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave1;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave1_slv_rd_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave1;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave1_slv_status_readback> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave1;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave1_slv_status_fast_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave1_slv_status_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave1;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 5u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave2_slv_rdsta_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave2_slv_wrsta_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave2;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave2_slv_rdbuf_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave2;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave2_slv_wrbuf_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave2;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave3_slv_rdbuf_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave3_slv_wrbuf_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave3;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave3_slv_rdsta_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave3;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slave3_slv_wrsta_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slave3;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slv_rdbuf_dlen_slv_rdbuf_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slv_rdbuf_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slv_rd_bit_slv_rdata_bit> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slv_rd_bit;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slv_wrbuf_dlen_slv_wrbuf_dbitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slv_wrbuf_dlen;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_slv_wr_status_slv_wr_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_slv_wr_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_sram_cmd_sram_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_sram_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_sram_cmd_sram_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_sram_cmd;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_sram_cmd_sram_rstio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_sram_cmd;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_sram_drd_cmd_cache_sram_usr_rd_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_sram_drd_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_sram_drd_cmd_cache_sram_usr_rd_cmd_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_sram_drd_cmd;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_sram_dwr_cmd_cache_sram_usr_wr_cmd_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_sram_dwr_cmd;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_sram_dwr_cmd_cache_sram_usr_wr_cmd_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_sram_dwr_cmd;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_tx_crc_data> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_tx_crc;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_doutdin> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_cs_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_cs_setup> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_ck_i_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_ck_out_edge> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_rd_byte_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_wr_byte_order> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_fwrite_dual> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_fwrite_quad> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_fwrite_dio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_fwrite_qio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_sio> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_hold_pol> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_dout_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_din_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_dummy_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_addr_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_cmd_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_prep_hold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_miso_highpart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_mosi_highpart> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_dummy_idle> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_mosi> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_miso> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_dummy> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user_usr_command> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user1_usr_dummy_cyclelen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user1_usr_addr_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user1;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 6u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user2_usr_command_value> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 16u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_user2_usr_command_bitlen> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_user2;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w0_buf0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w1_buf1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w10_buf10> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w10;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w11_buf11> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w11;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w12_buf12> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w12;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w13_buf13> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w13;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w14_buf14> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w14;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w15_buf15> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w15;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w2_buf2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w2;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w3_buf3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w3;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w4_buf4> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w4;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w5_buf5> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w5;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w6_buf6> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w6;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w7_buf7> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w7;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w8_buf8> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w8;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_spi3_w9_buf9> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_spi3_w9;
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
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_at_cmd_postcnt_post_idle_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_at_cmd_postcnt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_at_cmd_precnt_pre_idle_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_at_cmd_precnt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_autobaud_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_autobaud;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_autobaud_glitch_filt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_autobaud;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_clkdiv_clkdiv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_clkdiv;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
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
struct RegisterFieldTraits<FieldId::field_uart0_conf0_tick_ref_always_on> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf0;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf1_rxfifo_full_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf1_txfifo_empty_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf1;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf1_rx_flow_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf1_rx_flow_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf1;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf1_rx_tout_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf1;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_conf1_rx_tout_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_conf1;
  static constexpr std::uint16_t kBitOffset = 31u;
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
struct RegisterFieldTraits<FieldId::field_uart0_highpulse_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_highpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_id_id> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_id;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
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
struct RegisterFieldTraits<FieldId::field_uart0_idle_conf_tx_brk_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_idle_conf;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 8u;
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
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_rxfifo_full_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_txfifo_empty_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_parity_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_frm_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_rxfifo_ovf_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_dsr_chg_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_cts_chg_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_brk_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_rxfifo_tout_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_sw_xon_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_sw_xoff_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_glitch_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_tx_brk_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_tx_brk_idle_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_tx_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_rs485_parity_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_rs485_frm_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_rs485_clash_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_int_raw_at_cmd_char_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_int_raw;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
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
struct RegisterFieldTraits<FieldId::field_uart0_lowpulse_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_lowpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_cnt_status_rx_mem_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_cnt_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_cnt_status_tx_mem_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_cnt_status;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_mem_pd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_rx_size> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_tx_size> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_rx_flow_thrhd_h3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_rx_tout_thrhd_h3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_xon_threshold_h2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_xoff_threshold_h2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_rx_mem_full_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_conf_tx_mem_empty_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_conf;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_rx_status_mem_rx_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_rx_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_rx_status_mem_rx_rd_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_rx_status;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_rx_status_mem_rx_wr_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_rx_status;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_mem_tx_status_mem_tx_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_mem_tx_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_negpulse_negedge_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_negpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_pospulse_posedge_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_pospulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
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
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_status_st_urx_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_status;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 4u;
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
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_status_st_utx_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_status;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 4u;
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
struct RegisterFieldTraits<FieldId::field_uart0_swfc_conf_xon_threshold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_swfc_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_swfc_conf_xoff_threshold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_swfc_conf;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_swfc_conf_xon_char> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_swfc_conf;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart0_swfc_conf_xoff_char> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart0_swfc_conf;
  static constexpr std::uint16_t kBitOffset = 24u;
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
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_at_cmd_postcnt_post_idle_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_at_cmd_postcnt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_at_cmd_precnt_pre_idle_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_at_cmd_precnt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_autobaud_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_autobaud;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_autobaud_glitch_filt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_autobaud;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_clkdiv_clkdiv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_clkdiv;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
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
struct RegisterFieldTraits<FieldId::field_uart1_conf0_tick_ref_always_on> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf0;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf1_rxfifo_full_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf1_txfifo_empty_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf1;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf1_rx_flow_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf1_rx_flow_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf1;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf1_rx_tout_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf1;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_conf1_rx_tout_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_conf1;
  static constexpr std::uint16_t kBitOffset = 31u;
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
struct RegisterFieldTraits<FieldId::field_uart1_highpulse_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_highpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_id_id> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_id;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
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
struct RegisterFieldTraits<FieldId::field_uart1_idle_conf_tx_brk_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_idle_conf;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 8u;
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
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_rxfifo_full_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_txfifo_empty_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_parity_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_frm_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_rxfifo_ovf_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_dsr_chg_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_cts_chg_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_brk_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_rxfifo_tout_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_sw_xon_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_sw_xoff_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_glitch_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_tx_brk_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_tx_brk_idle_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_tx_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_rs485_parity_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_rs485_frm_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_rs485_clash_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_int_raw_at_cmd_char_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_int_raw;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
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
struct RegisterFieldTraits<FieldId::field_uart1_lowpulse_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_lowpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_cnt_status_rx_mem_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_cnt_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_cnt_status_tx_mem_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_cnt_status;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_mem_pd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_rx_size> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_tx_size> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_rx_flow_thrhd_h3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_rx_tout_thrhd_h3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_xon_threshold_h2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_xoff_threshold_h2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_rx_mem_full_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_conf_tx_mem_empty_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_conf;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_rx_status_mem_rx_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_rx_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_rx_status_mem_rx_rd_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_rx_status;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_rx_status_mem_rx_wr_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_rx_status;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_mem_tx_status_mem_tx_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_mem_tx_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_negpulse_negedge_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_negpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_pospulse_posedge_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_pospulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
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
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_status_st_urx_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_status;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 4u;
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
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_status_st_utx_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_status;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 4u;
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
struct RegisterFieldTraits<FieldId::field_uart1_swfc_conf_xon_threshold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_swfc_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_swfc_conf_xoff_threshold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_swfc_conf;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_swfc_conf_xon_char> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_swfc_conf;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart1_swfc_conf_xoff_char> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart1_swfc_conf;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_at_cmd_char_at_cmd_char> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_at_cmd_char;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_at_cmd_char_char_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_at_cmd_char;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_at_cmd_gaptout_rx_gap_tout> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_at_cmd_gaptout;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_at_cmd_postcnt_post_idle_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_at_cmd_postcnt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_at_cmd_precnt_pre_idle_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_at_cmd_precnt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_autobaud_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_autobaud;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_autobaud_glitch_filt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_autobaud;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_clkdiv_clkdiv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_clkdiv;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_clkdiv_frag> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_clkdiv;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_parity> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_parity_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_bit_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_stop_bit_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_sw_rts> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_sw_dtr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_txd_brk> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_irda_dplx> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_irda_tx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_irda_wctl> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_irda_tx_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_irda_rx_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_loopback> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_tx_flow_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_irda_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_rxfifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_txfifo_rst> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_rxd_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 19u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_cts_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_dsr_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_txd_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 22u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_rts_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_dtr_inv> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_clk_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_err_wr_mask> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 26u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf0_tick_ref_always_on> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf0;
  static constexpr std::uint16_t kBitOffset = 27u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf1_rxfifo_full_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf1;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf1_txfifo_empty_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf1;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf1_rx_flow_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf1;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf1_rx_flow_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf1;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf1_rx_tout_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf1;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 7u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_conf1_rx_tout_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_conf1;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_date_date> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_date;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_fifo_rxfifo_rd_byte> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_fifo;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_flow_conf_sw_flow_con_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_flow_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_flow_conf_xonoff_del> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_flow_conf;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_flow_conf_force_xon> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_flow_conf;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_flow_conf_force_xoff> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_flow_conf;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_flow_conf_send_xon> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_flow_conf;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_flow_conf_send_xoff> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_flow_conf;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_highpulse_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_highpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_id_id> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_id;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 32u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_idle_conf_rx_idle_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_idle_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_idle_conf_tx_idle_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_idle_conf;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_idle_conf_tx_brk_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_idle_conf;
  static constexpr std::uint16_t kBitOffset = 20u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_rxfifo_full_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_txfifo_empty_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_parity_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_frm_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_rxfifo_ovf_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_dsr_chg_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_cts_chg_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_brk_det_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_rxfifo_tout_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_sw_xon_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_sw_xoff_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_glitch_det_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_tx_brk_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_tx_brk_idle_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_tx_done_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_rs485_parity_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_rs485_frm_err_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_rs485_clash_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_clr_at_cmd_char_det_int_clr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_clr;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_write_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_rxfifo_full_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_txfifo_empty_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_parity_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_frm_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_rxfifo_ovf_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_dsr_chg_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_cts_chg_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_brk_det_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_rxfifo_tout_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_sw_xon_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_sw_xoff_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_glitch_det_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_tx_brk_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_tx_brk_idle_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_tx_done_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_rs485_parity_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_rs485_frm_err_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_rs485_clash_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_ena_at_cmd_char_det_int_ena> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_ena;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_rxfifo_full_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_txfifo_empty_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_parity_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_frm_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_rxfifo_ovf_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_dsr_chg_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_cts_chg_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_brk_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_rxfifo_tout_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_sw_xon_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_sw_xoff_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_glitch_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_tx_brk_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_tx_brk_idle_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_tx_done_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_rs485_parity_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_rs485_frm_err_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_rs485_clash_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_raw_at_cmd_char_det_int_raw> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_raw;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_rxfifo_full_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_txfifo_empty_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_parity_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_frm_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_rxfifo_ovf_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_dsr_chg_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_cts_chg_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_brk_det_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_rxfifo_tout_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_sw_xon_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 9u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_sw_xoff_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 10u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_glitch_det_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 11u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_tx_brk_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 12u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_tx_brk_idle_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_tx_done_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_rs485_parity_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_rs485_frm_err_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_rs485_clash_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 17u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_int_st_at_cmd_char_det_int_st> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_int_st;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_lowpulse_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_lowpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_cnt_status_rx_mem_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_cnt_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_cnt_status_tx_mem_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_cnt_status;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_conf_mem_pd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_conf_rx_size> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_conf;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_conf_tx_size> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_conf;
  static constexpr std::uint16_t kBitOffset = 7u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_conf_rx_flow_thrhd_h3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_conf;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_conf_rx_tout_thrhd_h3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_conf;
  static constexpr std::uint16_t kBitOffset = 18u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_conf_xon_threshold_h2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_conf;
  static constexpr std::uint16_t kBitOffset = 21u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_conf_xoff_threshold_h2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_conf;
  static constexpr std::uint16_t kBitOffset = 23u;
  static constexpr std::uint16_t kBitWidth = 2u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_conf_rx_mem_full_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_conf;
  static constexpr std::uint16_t kBitOffset = 25u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_conf_tx_mem_empty_thrhd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_conf;
  static constexpr std::uint16_t kBitOffset = 28u;
  static constexpr std::uint16_t kBitWidth = 3u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_rx_status_mem_rx_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_rx_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_rx_status_mem_rx_rd_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_rx_status;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_rx_status_mem_rx_wr_addr> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_rx_status;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 11u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_mem_tx_status_mem_tx_status> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_mem_tx_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 24u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_negpulse_negedge_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_negpulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_pospulse_posedge_min_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_pospulse;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 20u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_rs485_conf_rs485_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_rs485_conf_dl0_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 1u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_rs485_conf_dl1_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 2u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_rs485_conf_rs485tx_rx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 3u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_rs485_conf_rs485rxby_tx_en> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 4u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_rs485_conf_rs485_rx_dly_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 5u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_rs485_conf_rs485_tx_dly_num> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_rs485_conf;
  static constexpr std::uint16_t kBitOffset = 6u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_rxd_cnt_rxd_edge_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_rxd_cnt;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_sleep_conf_active_threshold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_sleep_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 10u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_status_rxfifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_status;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_status_st_urx_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_status;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_status_dsrn> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_status;
  static constexpr std::uint16_t kBitOffset = 13u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_status_ctsn> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_status;
  static constexpr std::uint16_t kBitOffset = 14u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_status_rxd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_status;
  static constexpr std::uint16_t kBitOffset = 15u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_status_txfifo_cnt> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_status;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_status_st_utx_out> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_status;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 4u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_status_dtrn> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_status;
  static constexpr std::uint16_t kBitOffset = 29u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_status_rtsn> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_status;
  static constexpr std::uint16_t kBitOffset = 30u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_status_txd> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_status;
  static constexpr std::uint16_t kBitOffset = 31u;
  static constexpr std::uint16_t kBitWidth = 1u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_only;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_swfc_conf_xon_threshold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_swfc_conf;
  static constexpr std::uint16_t kBitOffset = 0u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_swfc_conf_xoff_threshold> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_swfc_conf;
  static constexpr std::uint16_t kBitOffset = 8u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_swfc_conf_xon_char> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_swfc_conf;
  static constexpr std::uint16_t kBitOffset = 16u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

template<>
struct RegisterFieldTraits<FieldId::field_uart2_swfc_conf_xoff_char> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_uart2_swfc_conf;
  static constexpr std::uint16_t kBitOffset = 24u;
  static constexpr std::uint16_t kBitWidth = 8u;
  static constexpr AccessKindId kAccessId = AccessKindId::access_kind_read_write;
};

inline constexpr std::array<FieldId, 1909> kRegisterFields = {{
  FieldId::field_dport_perip_clk_en_spi01_clk_en,
  FieldId::field_dport_perip_clk_en_uart_clk_en,
  FieldId::field_dport_perip_clk_en_i2c0_ext0_clk_en,
  FieldId::field_gpio_acpu_int_appcpu_int,
  FieldId::field_gpio_acpu_int1_appcpu_int_h,
  FieldId::field_gpio_acpu_nmi_int_appcpu_nmi_int,
  FieldId::field_gpio_acpu_nmi_int1_appcpu_nmi_int_h,
  FieldId::field_gpio_bt_select_bt_sel,
  FieldId::field_gpio_cpusdio_int_sdio_int,
  FieldId::field_gpio_cpusdio_int1_sdio_int_h,
  FieldId::field_gpio_cpusdio_int1_pin_pad_driver,
  FieldId::field_gpio_cpusdio_int1_pin_int_type,
  FieldId::field_gpio_cpusdio_int1_pin_wakeup_enable,
  FieldId::field_gpio_cpusdio_int1_pin_config,
  FieldId::field_gpio_cpusdio_int1_pin_int_ena,
  FieldId::field_gpio_enable_data,
  FieldId::field_gpio_enable1_data,
  FieldId::field_gpio_enable1_w1tc_enable1_data_w1tc,
  FieldId::field_gpio_enable1_w1ts_enable1_data_w1ts,
  FieldId::field_gpio_enable_w1tc_enable_data_w1tc,
  FieldId::field_gpio_enable_w1ts_enable_data_w1ts,
  FieldId::field_gpio_func_s_in_sel_cfg_in_sel,
  FieldId::field_gpio_func_s_in_sel_cfg_in_inv_sel,
  FieldId::field_gpio_func_s_in_sel_cfg_sel,
  FieldId::field_gpio_func_s_out_sel_cfg_out_sel,
  FieldId::field_gpio_func_s_out_sel_cfg_inv_sel,
  FieldId::field_gpio_func_s_out_sel_cfg_oen_sel,
  FieldId::field_gpio_func_s_out_sel_cfg_oen_inv_sel,
  FieldId::field_gpio_in_data_next,
  FieldId::field_gpio_in1_data_next,
  FieldId::field_gpio_out_data,
  FieldId::field_gpio_out1_data,
  FieldId::field_gpio_out1_w1tc_out1_data_w1tc,
  FieldId::field_gpio_out1_w1ts_out1_data_w1ts,
  FieldId::field_gpio_out_w1tc_out_data_w1tc,
  FieldId::field_gpio_out_w1ts_out_data_w1ts,
  FieldId::field_gpio_pcpu_int_procpu_int,
  FieldId::field_gpio_pcpu_int1_procpu_int_h,
  FieldId::field_gpio_pcpu_nmi_int_procpu_nmi_int,
  FieldId::field_gpio_pcpu_nmi_int1_procpu_nmi_int_h,
  FieldId::field_gpio_pin_s_pad_driver,
  FieldId::field_gpio_pin_s_int_type,
  FieldId::field_gpio_pin_s_wakeup_enable,
  FieldId::field_gpio_pin_s_config,
  FieldId::field_gpio_pin_s_int_ena,
  FieldId::field_gpio_sdio_select_sdio_sel,
  FieldId::field_gpio_status_int,
  FieldId::field_gpio_status1_int,
  FieldId::field_gpio_status1_w1tc_status1_int_w1tc,
  FieldId::field_gpio_status1_w1ts_status1_int_w1ts,
  FieldId::field_gpio_status_w1tc_status_int_w1tc,
  FieldId::field_gpio_status_w1ts_status_int_w1ts,
  FieldId::field_gpio_strap_strapping,
  FieldId::field_gpio_cali_conf_cali_rtc_max,
  FieldId::field_gpio_cali_conf_cali_start,
  FieldId::field_gpio_cali_data_cali_value_sync2,
  FieldId::field_gpio_cali_data_cali_rdy_real,
  FieldId::field_gpio_cali_data_cali_rdy_sync2,
  FieldId::field_i2c0_comd_s_command,
  FieldId::field_i2c0_comd_s_command_done,
  FieldId::field_i2c0_ctr_sda_force_out,
  FieldId::field_i2c0_ctr_scl_force_out,
  FieldId::field_i2c0_ctr_sample_scl_level,
  FieldId::field_i2c0_ctr_ms_mode,
  FieldId::field_i2c0_ctr_trans_start,
  FieldId::field_i2c0_ctr_tx_lsb_first,
  FieldId::field_i2c0_ctr_rx_lsb_first,
  FieldId::field_i2c0_ctr_clk_en,
  FieldId::field_i2c0_data_fifo_rdata,
  FieldId::field_i2c0_date_date,
  FieldId::field_i2c0_fifo_conf_rxfifo_full_thrhd,
  FieldId::field_i2c0_fifo_conf_txfifo_empty_thrhd,
  FieldId::field_i2c0_fifo_conf_nonfifo_en,
  FieldId::field_i2c0_fifo_conf_fifo_addr_cfg_en,
  FieldId::field_i2c0_fifo_conf_rx_fifo_rst,
  FieldId::field_i2c0_fifo_conf_tx_fifo_rst,
  FieldId::field_i2c0_fifo_conf_nonfifo_rx_thres,
  FieldId::field_i2c0_fifo_conf_nonfifo_tx_thres,
  FieldId::field_i2c0_int_clr_rxfifo_full_int_clr,
  FieldId::field_i2c0_int_clr_txfifo_empty_int_clr,
  FieldId::field_i2c0_int_clr_rxfifo_ovf_int_clr,
  FieldId::field_i2c0_int_clr_end_detect_int_clr,
  FieldId::field_i2c0_int_clr_slave_tran_comp_int_clr,
  FieldId::field_i2c0_int_clr_arbitration_lost_int_clr,
  FieldId::field_i2c0_int_clr_master_tran_comp_int_clr,
  FieldId::field_i2c0_int_clr_trans_complete_int_clr,
  FieldId::field_i2c0_int_clr_time_out_int_clr,
  FieldId::field_i2c0_int_clr_trans_start_int_clr,
  FieldId::field_i2c0_int_clr_ack_err_int_clr,
  FieldId::field_i2c0_int_clr_rx_rec_full_int_clr,
  FieldId::field_i2c0_int_clr_tx_send_empty_int_clr,
  FieldId::field_i2c0_int_ena_rxfifo_full_int_ena,
  FieldId::field_i2c0_int_ena_txfifo_empty_int_ena,
  FieldId::field_i2c0_int_ena_rxfifo_ovf_int_ena,
  FieldId::field_i2c0_int_ena_end_detect_int_ena,
  FieldId::field_i2c0_int_ena_slave_tran_comp_int_ena,
  FieldId::field_i2c0_int_ena_arbitration_lost_int_ena,
  FieldId::field_i2c0_int_ena_master_tran_comp_int_ena,
  FieldId::field_i2c0_int_ena_trans_complete_int_ena,
  FieldId::field_i2c0_int_ena_time_out_int_ena,
  FieldId::field_i2c0_int_ena_trans_start_int_ena,
  FieldId::field_i2c0_int_ena_ack_err_int_ena,
  FieldId::field_i2c0_int_ena_rx_rec_full_int_ena,
  FieldId::field_i2c0_int_ena_tx_send_empty_int_ena,
  FieldId::field_i2c0_int_raw_rxfifo_full_int_raw,
  FieldId::field_i2c0_int_raw_txfifo_empty_int_raw,
  FieldId::field_i2c0_int_raw_rxfifo_ovf_int_raw,
  FieldId::field_i2c0_int_raw_end_detect_int_raw,
  FieldId::field_i2c0_int_raw_slave_tran_comp_int_raw,
  FieldId::field_i2c0_int_raw_arbitration_lost_int_raw,
  FieldId::field_i2c0_int_raw_master_tran_comp_int_raw,
  FieldId::field_i2c0_int_raw_trans_complete_int_raw,
  FieldId::field_i2c0_int_raw_time_out_int_raw,
  FieldId::field_i2c0_int_raw_trans_start_int_raw,
  FieldId::field_i2c0_int_raw_ack_err_int_raw,
  FieldId::field_i2c0_int_raw_rx_rec_full_int_raw,
  FieldId::field_i2c0_int_raw_tx_send_empty_int_raw,
  FieldId::field_i2c0_int_status_rxfifo_full_int_st,
  FieldId::field_i2c0_int_status_txfifo_empty_int_st,
  FieldId::field_i2c0_int_status_rxfifo_ovf_int_st,
  FieldId::field_i2c0_int_status_end_detect_int_st,
  FieldId::field_i2c0_int_status_slave_tran_comp_int_st,
  FieldId::field_i2c0_int_status_arbitration_lost_int_st,
  FieldId::field_i2c0_int_status_master_tran_comp_int_st,
  FieldId::field_i2c0_int_status_trans_complete_int_st,
  FieldId::field_i2c0_int_status_time_out_int_st,
  FieldId::field_i2c0_int_status_trans_start_int_st,
  FieldId::field_i2c0_int_status_ack_err_int_st,
  FieldId::field_i2c0_int_status_rx_rec_full_int_st,
  FieldId::field_i2c0_int_status_tx_send_empty_int_st,
  FieldId::field_i2c0_rxfifo_st_rxfifo_start_addr,
  FieldId::field_i2c0_rxfifo_st_rxfifo_end_addr,
  FieldId::field_i2c0_rxfifo_st_txfifo_start_addr,
  FieldId::field_i2c0_rxfifo_st_txfifo_end_addr,
  FieldId::field_i2c0_scl_filter_cfg_scl_filter_thres,
  FieldId::field_i2c0_scl_filter_cfg_scl_filter_en,
  FieldId::field_i2c0_scl_high_period_scl_high_period,
  FieldId::field_i2c0_scl_low_period_scl_low_period,
  FieldId::field_i2c0_scl_rstart_setup_time,
  FieldId::field_i2c0_scl_start_hold_time,
  FieldId::field_i2c0_scl_stop_hold_time,
  FieldId::field_i2c0_scl_stop_setup_time,
  FieldId::field_i2c0_sda_filter_cfg_sda_filter_thres,
  FieldId::field_i2c0_sda_filter_cfg_sda_filter_en,
  FieldId::field_i2c0_sda_hold_time,
  FieldId::field_i2c0_sda_sample_time,
  FieldId::field_i2c0_slave_addr_slave_addr,
  FieldId::field_i2c0_slave_addr_addr_10bit_en,
  FieldId::field_i2c0_sr_ack_rec,
  FieldId::field_i2c0_sr_slave_rw,
  FieldId::field_i2c0_sr_time_out,
  FieldId::field_i2c0_sr_arb_lost,
  FieldId::field_i2c0_sr_bus_busy,
  FieldId::field_i2c0_sr_slave_addressed,
  FieldId::field_i2c0_sr_byte_trans,
  FieldId::field_i2c0_sr_rxfifo_cnt,
  FieldId::field_i2c0_sr_txfifo_cnt,
  FieldId::field_i2c0_sr_scl_main_state_last,
  FieldId::field_i2c0_sr_scl_state_last,
  FieldId::field_i2c0_to_time_out,
  FieldId::field_i2c1_comd_s_command,
  FieldId::field_i2c1_comd_s_command_done,
  FieldId::field_i2c1_ctr_sda_force_out,
  FieldId::field_i2c1_ctr_scl_force_out,
  FieldId::field_i2c1_ctr_sample_scl_level,
  FieldId::field_i2c1_ctr_ms_mode,
  FieldId::field_i2c1_ctr_trans_start,
  FieldId::field_i2c1_ctr_tx_lsb_first,
  FieldId::field_i2c1_ctr_rx_lsb_first,
  FieldId::field_i2c1_ctr_clk_en,
  FieldId::field_i2c1_data_fifo_rdata,
  FieldId::field_i2c1_date_date,
  FieldId::field_i2c1_fifo_conf_rxfifo_full_thrhd,
  FieldId::field_i2c1_fifo_conf_txfifo_empty_thrhd,
  FieldId::field_i2c1_fifo_conf_nonfifo_en,
  FieldId::field_i2c1_fifo_conf_fifo_addr_cfg_en,
  FieldId::field_i2c1_fifo_conf_rx_fifo_rst,
  FieldId::field_i2c1_fifo_conf_tx_fifo_rst,
  FieldId::field_i2c1_fifo_conf_nonfifo_rx_thres,
  FieldId::field_i2c1_fifo_conf_nonfifo_tx_thres,
  FieldId::field_i2c1_int_clr_rxfifo_full_int_clr,
  FieldId::field_i2c1_int_clr_txfifo_empty_int_clr,
  FieldId::field_i2c1_int_clr_rxfifo_ovf_int_clr,
  FieldId::field_i2c1_int_clr_end_detect_int_clr,
  FieldId::field_i2c1_int_clr_slave_tran_comp_int_clr,
  FieldId::field_i2c1_int_clr_arbitration_lost_int_clr,
  FieldId::field_i2c1_int_clr_master_tran_comp_int_clr,
  FieldId::field_i2c1_int_clr_trans_complete_int_clr,
  FieldId::field_i2c1_int_clr_time_out_int_clr,
  FieldId::field_i2c1_int_clr_trans_start_int_clr,
  FieldId::field_i2c1_int_clr_ack_err_int_clr,
  FieldId::field_i2c1_int_clr_rx_rec_full_int_clr,
  FieldId::field_i2c1_int_clr_tx_send_empty_int_clr,
  FieldId::field_i2c1_int_ena_rxfifo_full_int_ena,
  FieldId::field_i2c1_int_ena_txfifo_empty_int_ena,
  FieldId::field_i2c1_int_ena_rxfifo_ovf_int_ena,
  FieldId::field_i2c1_int_ena_end_detect_int_ena,
  FieldId::field_i2c1_int_ena_slave_tran_comp_int_ena,
  FieldId::field_i2c1_int_ena_arbitration_lost_int_ena,
  FieldId::field_i2c1_int_ena_master_tran_comp_int_ena,
  FieldId::field_i2c1_int_ena_trans_complete_int_ena,
  FieldId::field_i2c1_int_ena_time_out_int_ena,
  FieldId::field_i2c1_int_ena_trans_start_int_ena,
  FieldId::field_i2c1_int_ena_ack_err_int_ena,
  FieldId::field_i2c1_int_ena_rx_rec_full_int_ena,
  FieldId::field_i2c1_int_ena_tx_send_empty_int_ena,
  FieldId::field_i2c1_int_raw_rxfifo_full_int_raw,
  FieldId::field_i2c1_int_raw_txfifo_empty_int_raw,
  FieldId::field_i2c1_int_raw_rxfifo_ovf_int_raw,
  FieldId::field_i2c1_int_raw_end_detect_int_raw,
  FieldId::field_i2c1_int_raw_slave_tran_comp_int_raw,
  FieldId::field_i2c1_int_raw_arbitration_lost_int_raw,
  FieldId::field_i2c1_int_raw_master_tran_comp_int_raw,
  FieldId::field_i2c1_int_raw_trans_complete_int_raw,
  FieldId::field_i2c1_int_raw_time_out_int_raw,
  FieldId::field_i2c1_int_raw_trans_start_int_raw,
  FieldId::field_i2c1_int_raw_ack_err_int_raw,
  FieldId::field_i2c1_int_raw_rx_rec_full_int_raw,
  FieldId::field_i2c1_int_raw_tx_send_empty_int_raw,
  FieldId::field_i2c1_int_status_rxfifo_full_int_st,
  FieldId::field_i2c1_int_status_txfifo_empty_int_st,
  FieldId::field_i2c1_int_status_rxfifo_ovf_int_st,
  FieldId::field_i2c1_int_status_end_detect_int_st,
  FieldId::field_i2c1_int_status_slave_tran_comp_int_st,
  FieldId::field_i2c1_int_status_arbitration_lost_int_st,
  FieldId::field_i2c1_int_status_master_tran_comp_int_st,
  FieldId::field_i2c1_int_status_trans_complete_int_st,
  FieldId::field_i2c1_int_status_time_out_int_st,
  FieldId::field_i2c1_int_status_trans_start_int_st,
  FieldId::field_i2c1_int_status_ack_err_int_st,
  FieldId::field_i2c1_int_status_rx_rec_full_int_st,
  FieldId::field_i2c1_int_status_tx_send_empty_int_st,
  FieldId::field_i2c1_rxfifo_st_rxfifo_start_addr,
  FieldId::field_i2c1_rxfifo_st_rxfifo_end_addr,
  FieldId::field_i2c1_rxfifo_st_txfifo_start_addr,
  FieldId::field_i2c1_rxfifo_st_txfifo_end_addr,
  FieldId::field_i2c1_scl_filter_cfg_scl_filter_thres,
  FieldId::field_i2c1_scl_filter_cfg_scl_filter_en,
  FieldId::field_i2c1_scl_high_period_scl_high_period,
  FieldId::field_i2c1_scl_low_period_scl_low_period,
  FieldId::field_i2c1_scl_rstart_setup_time,
  FieldId::field_i2c1_scl_start_hold_time,
  FieldId::field_i2c1_scl_stop_hold_time,
  FieldId::field_i2c1_scl_stop_setup_time,
  FieldId::field_i2c1_sda_filter_cfg_sda_filter_thres,
  FieldId::field_i2c1_sda_filter_cfg_sda_filter_en,
  FieldId::field_i2c1_sda_hold_time,
  FieldId::field_i2c1_sda_sample_time,
  FieldId::field_i2c1_slave_addr_slave_addr,
  FieldId::field_i2c1_slave_addr_addr_10bit_en,
  FieldId::field_i2c1_sr_ack_rec,
  FieldId::field_i2c1_sr_slave_rw,
  FieldId::field_i2c1_sr_time_out,
  FieldId::field_i2c1_sr_arb_lost,
  FieldId::field_i2c1_sr_bus_busy,
  FieldId::field_i2c1_sr_slave_addressed,
  FieldId::field_i2c1_sr_byte_trans,
  FieldId::field_i2c1_sr_rxfifo_cnt,
  FieldId::field_i2c1_sr_txfifo_cnt,
  FieldId::field_i2c1_sr_scl_main_state_last,
  FieldId::field_i2c1_sr_scl_state_last,
  FieldId::field_i2c1_to_time_out,
  FieldId::field_sens_sardate_sar_date,
  FieldId::field_sens_sar_atten1_sar1_atten,
  FieldId::field_sens_sar_atten2_sar2_atten,
  FieldId::field_sens_sar_dac_ctrl1_sw_fstep,
  FieldId::field_sens_sar_dac_ctrl1_sw_tone_en,
  FieldId::field_sens_sar_dac_ctrl1_debug_bit_sel,
  FieldId::field_sens_sar_dac_ctrl1_dac_dig_force,
  FieldId::field_sens_sar_dac_ctrl1_dac_clk_force_low,
  FieldId::field_sens_sar_dac_ctrl1_dac_clk_force_high,
  FieldId::field_sens_sar_dac_ctrl1_dac_clk_inv,
  FieldId::field_sens_sar_dac_ctrl2_dac_dc1,
  FieldId::field_sens_sar_dac_ctrl2_dac_dc2,
  FieldId::field_sens_sar_dac_ctrl2_dac_scale1,
  FieldId::field_sens_sar_dac_ctrl2_dac_scale2,
  FieldId::field_sens_sar_dac_ctrl2_dac_inv1,
  FieldId::field_sens_sar_dac_ctrl2_dac_inv2,
  FieldId::field_sens_sar_dac_ctrl2_dac_cw_en1,
  FieldId::field_sens_sar_dac_ctrl2_dac_cw_en2,
  FieldId::field_sens_sar_i2c_ctrl_sar_i2c_ctrl,
  FieldId::field_sens_sar_i2c_ctrl_sar_i2c_start,
  FieldId::field_sens_sar_i2c_ctrl_sar_i2c_start_force,
  FieldId::field_sens_sar_meas_ctrl_xpd_sar_amp_fsm,
  FieldId::field_sens_sar_meas_ctrl_amp_rst_fb_fsm,
  FieldId::field_sens_sar_meas_ctrl_amp_short_ref_fsm,
  FieldId::field_sens_sar_meas_ctrl_amp_short_ref_gnd_fsm,
  FieldId::field_sens_sar_meas_ctrl_xpd_sar_fsm,
  FieldId::field_sens_sar_meas_ctrl_sar_rstb_fsm,
  FieldId::field_sens_sar_meas_ctrl_sar2_xpd_wait,
  FieldId::field_sens_sar_meas_ctrl2_sar1_dac_xpd_fsm,
  FieldId::field_sens_sar_meas_ctrl2_sar1_dac_xpd_fsm_idle,
  FieldId::field_sens_sar_meas_ctrl2_xpd_sar_amp_fsm_idle,
  FieldId::field_sens_sar_meas_ctrl2_amp_rst_fb_fsm_idle,
  FieldId::field_sens_sar_meas_ctrl2_amp_short_ref_fsm_idle,
  FieldId::field_sens_sar_meas_ctrl2_amp_short_ref_gnd_fsm_idle,
  FieldId::field_sens_sar_meas_ctrl2_xpd_sar_fsm_idle,
  FieldId::field_sens_sar_meas_ctrl2_sar_rstb_fsm_idle,
  FieldId::field_sens_sar_meas_ctrl2_sar2_rstb_force,
  FieldId::field_sens_sar_meas_ctrl2_amp_rst_fb_force,
  FieldId::field_sens_sar_meas_ctrl2_amp_short_ref_force,
  FieldId::field_sens_sar_meas_ctrl2_amp_short_ref_gnd_force,
  FieldId::field_sens_sar_meas_start1_meas1_data_sar,
  FieldId::field_sens_sar_meas_start1_meas1_done_sar,
  FieldId::field_sens_sar_meas_start1_meas1_start_sar,
  FieldId::field_sens_sar_meas_start1_meas1_start_force,
  FieldId::field_sens_sar_meas_start1_sar1_en_pad,
  FieldId::field_sens_sar_meas_start1_sar1_en_pad_force,
  FieldId::field_sens_sar_meas_start2_meas2_data_sar,
  FieldId::field_sens_sar_meas_start2_meas2_done_sar,
  FieldId::field_sens_sar_meas_start2_meas2_start_sar,
  FieldId::field_sens_sar_meas_start2_meas2_start_force,
  FieldId::field_sens_sar_meas_start2_sar2_en_pad,
  FieldId::field_sens_sar_meas_start2_sar2_en_pad_force,
  FieldId::field_sens_sar_meas_wait1_sar_amp_wait1,
  FieldId::field_sens_sar_meas_wait1_sar_amp_wait2,
  FieldId::field_sens_sar_meas_wait2_force_xpd_sar_sw,
  FieldId::field_sens_sar_meas_wait2_sar_amp_wait3,
  FieldId::field_sens_sar_meas_wait2_force_xpd_amp,
  FieldId::field_sens_sar_meas_wait2_force_xpd_sar,
  FieldId::field_sens_sar_meas_wait2_sar2_rstb_wait,
  FieldId::field_sens_sar_mem_wr_ctrl_mem_wr_addr_init,
  FieldId::field_sens_sar_mem_wr_ctrl_mem_wr_addr_size,
  FieldId::field_sens_sar_mem_wr_ctrl_rtc_mem_wr_offst_clr,
  FieldId::field_sens_sar_nouse_sar_nouse,
  FieldId::field_sens_sar_read_ctrl_sar1_clk_div,
  FieldId::field_sens_sar_read_ctrl_sar1_sample_cycle,
  FieldId::field_sens_sar_read_ctrl_sar1_sample_bit,
  FieldId::field_sens_sar_read_ctrl_sar1_clk_gated,
  FieldId::field_sens_sar_read_ctrl_sar1_sample_num,
  FieldId::field_sens_sar_read_ctrl_sar1_dig_force,
  FieldId::field_sens_sar_read_ctrl_sar1_data_inv,
  FieldId::field_sens_sar_read_ctrl2_sar2_clk_div,
  FieldId::field_sens_sar_read_ctrl2_sar2_sample_cycle,
  FieldId::field_sens_sar_read_ctrl2_sar2_sample_bit,
  FieldId::field_sens_sar_read_ctrl2_sar2_clk_gated,
  FieldId::field_sens_sar_read_ctrl2_sar2_sample_num,
  FieldId::field_sens_sar_read_ctrl2_sar2_pwdet_force,
  FieldId::field_sens_sar_read_ctrl2_sar2_dig_force,
  FieldId::field_sens_sar_read_ctrl2_sar2_data_inv,
  FieldId::field_sens_sar_read_status1_sar1_reader_status,
  FieldId::field_sens_sar_read_status2_sar2_reader_status,
  FieldId::field_sens_sar_slave_addr1_i2c_slave_addr1,
  FieldId::field_sens_sar_slave_addr1_i2c_slave_addr0,
  FieldId::field_sens_sar_slave_addr1_meas_status,
  FieldId::field_sens_sar_slave_addr2_i2c_slave_addr3,
  FieldId::field_sens_sar_slave_addr2_i2c_slave_addr2,
  FieldId::field_sens_sar_slave_addr3_i2c_slave_addr5,
  FieldId::field_sens_sar_slave_addr3_i2c_slave_addr4,
  FieldId::field_sens_sar_slave_addr3_tsens_out,
  FieldId::field_sens_sar_slave_addr3_tsens_rdy_out,
  FieldId::field_sens_sar_slave_addr4_i2c_slave_addr7,
  FieldId::field_sens_sar_slave_addr4_i2c_slave_addr6,
  FieldId::field_sens_sar_slave_addr4_i2c_rdata,
  FieldId::field_sens_sar_slave_addr4_i2c_done,
  FieldId::field_sens_sar_start_force_sar1_bit_width,
  FieldId::field_sens_sar_start_force_sar2_bit_width,
  FieldId::field_sens_sar_start_force_sar2_en_test,
  FieldId::field_sens_sar_start_force_sar2_pwdet_cct,
  FieldId::field_sens_sar_start_force_ulp_cp_force_start_top,
  FieldId::field_sens_sar_start_force_ulp_cp_start_top,
  FieldId::field_sens_sar_start_force_sarclk_en,
  FieldId::field_sens_sar_start_force_pc_init,
  FieldId::field_sens_sar_start_force_sar2_stop,
  FieldId::field_sens_sar_start_force_sar1_stop,
  FieldId::field_sens_sar_start_force_sar2_pwdet_en,
  FieldId::field_sens_sar_touch_ctrl1_touch_meas_delay,
  FieldId::field_sens_sar_touch_ctrl1_touch_xpd_wait,
  FieldId::field_sens_sar_touch_ctrl1_touch_out_sel,
  FieldId::field_sens_sar_touch_ctrl1_touch_out_1en,
  FieldId::field_sens_sar_touch_ctrl1_xpd_hall_force,
  FieldId::field_sens_sar_touch_ctrl1_hall_phase_force,
  FieldId::field_sens_sar_touch_ctrl2_touch_meas_en,
  FieldId::field_sens_sar_touch_ctrl2_touch_meas_done,
  FieldId::field_sens_sar_touch_ctrl2_touch_start_fsm_en,
  FieldId::field_sens_sar_touch_ctrl2_touch_start_en,
  FieldId::field_sens_sar_touch_ctrl2_touch_start_force,
  FieldId::field_sens_sar_touch_ctrl2_touch_sleep_cycles,
  FieldId::field_sens_sar_touch_ctrl2_touch_meas_en_clr,
  FieldId::field_sens_sar_touch_enable_touch_pad_worken,
  FieldId::field_sens_sar_touch_enable_touch_pad_outen2,
  FieldId::field_sens_sar_touch_enable_touch_pad_outen1,
  FieldId::field_sens_sar_touch_out1_touch_meas_out1,
  FieldId::field_sens_sar_touch_out1_touch_meas_out0,
  FieldId::field_sens_sar_touch_out2_touch_meas_out3,
  FieldId::field_sens_sar_touch_out2_touch_meas_out2,
  FieldId::field_sens_sar_touch_out3_touch_meas_out5,
  FieldId::field_sens_sar_touch_out3_touch_meas_out4,
  FieldId::field_sens_sar_touch_out4_touch_meas_out7,
  FieldId::field_sens_sar_touch_out4_touch_meas_out6,
  FieldId::field_sens_sar_touch_out5_touch_meas_out9,
  FieldId::field_sens_sar_touch_out5_touch_meas_out8,
  FieldId::field_sens_sar_touch_thres1_touch_out_th1,
  FieldId::field_sens_sar_touch_thres1_touch_out_th0,
  FieldId::field_sens_sar_touch_thres2_touch_out_th3,
  FieldId::field_sens_sar_touch_thres2_touch_out_th2,
  FieldId::field_sens_sar_touch_thres3_touch_out_th5,
  FieldId::field_sens_sar_touch_thres3_touch_out_th4,
  FieldId::field_sens_sar_touch_thres4_touch_out_th7,
  FieldId::field_sens_sar_touch_thres4_touch_out_th6,
  FieldId::field_sens_sar_touch_thres5_touch_out_th9,
  FieldId::field_sens_sar_touch_thres5_touch_out_th8,
  FieldId::field_sens_sar_tsens_ctrl_tsens_xpd_wait,
  FieldId::field_sens_sar_tsens_ctrl_tsens_xpd_force,
  FieldId::field_sens_sar_tsens_ctrl_tsens_clk_inv,
  FieldId::field_sens_sar_tsens_ctrl_tsens_clk_gated,
  FieldId::field_sens_sar_tsens_ctrl_tsens_in_inv,
  FieldId::field_sens_sar_tsens_ctrl_tsens_clk_div,
  FieldId::field_sens_sar_tsens_ctrl_tsens_power_up,
  FieldId::field_sens_sar_tsens_ctrl_tsens_power_up_force,
  FieldId::field_sens_sar_tsens_ctrl_tsens_dump_out,
  FieldId::field_sens_ulp_cp_sleep_cyc0_sleep_cycles_s0,
  FieldId::field_sens_ulp_cp_sleep_cyc1_sleep_cycles_s1,
  FieldId::field_sens_ulp_cp_sleep_cyc2_sleep_cycles_s2,
  FieldId::field_sens_ulp_cp_sleep_cyc3_sleep_cycles_s3,
  FieldId::field_sens_ulp_cp_sleep_cyc4_sleep_cycles_s4,
  FieldId::field_spi0_cache_fctrl_cache_req_en,
  FieldId::field_spi0_cache_fctrl_cache_usr_cmd_4byte,
  FieldId::field_spi0_cache_fctrl_cache_flash_usr_cmd,
  FieldId::field_spi0_cache_fctrl_cache_flash_pes_en,
  FieldId::field_spi0_cache_sctrl_usr_sram_dio,
  FieldId::field_spi0_cache_sctrl_usr_sram_qio,
  FieldId::field_spi0_cache_sctrl_usr_wr_sram_dummy,
  FieldId::field_spi0_cache_sctrl_usr_rd_sram_dummy,
  FieldId::field_spi0_cache_sctrl_cache_sram_usr_rcmd,
  FieldId::field_spi0_cache_sctrl_sram_bytes_len,
  FieldId::field_spi0_cache_sctrl_sram_dummy_cyclelen,
  FieldId::field_spi0_cache_sctrl_sram_addr_bitlen,
  FieldId::field_spi0_cache_sctrl_cache_sram_usr_wcmd,
  FieldId::field_spi0_clock_clkcnt_l,
  FieldId::field_spi0_clock_clkcnt_h,
  FieldId::field_spi0_clock_clkcnt_n,
  FieldId::field_spi0_clock_clkdiv_pre,
  FieldId::field_spi0_clock_clk_equ_sysclk,
  FieldId::field_spi0_cmd_flash_per,
  FieldId::field_spi0_cmd_flash_pes,
  FieldId::field_spi0_cmd_usr,
  FieldId::field_spi0_cmd_flash_hpm,
  FieldId::field_spi0_cmd_flash_res,
  FieldId::field_spi0_cmd_flash_dp,
  FieldId::field_spi0_cmd_flash_ce,
  FieldId::field_spi0_cmd_flash_be,
  FieldId::field_spi0_cmd_flash_se,
  FieldId::field_spi0_cmd_flash_pp,
  FieldId::field_spi0_cmd_flash_wrsr,
  FieldId::field_spi0_cmd_flash_rdsr,
  FieldId::field_spi0_cmd_flash_rdid,
  FieldId::field_spi0_cmd_flash_wrdi,
  FieldId::field_spi0_cmd_flash_wren,
  FieldId::field_spi0_cmd_flash_read,
  FieldId::field_spi0_ctrl_fcs_crc_en,
  FieldId::field_spi0_ctrl_tx_crc_en,
  FieldId::field_spi0_ctrl_wait_flash_idle_en,
  FieldId::field_spi0_ctrl_fastrd_mode,
  FieldId::field_spi0_ctrl_fread_dual,
  FieldId::field_spi0_ctrl_resandres,
  FieldId::field_spi0_ctrl_fread_quad,
  FieldId::field_spi0_ctrl_wp,
  FieldId::field_spi0_ctrl_wrsr_2b,
  FieldId::field_spi0_ctrl_fread_dio,
  FieldId::field_spi0_ctrl_fread_qio,
  FieldId::field_spi0_ctrl_rd_bit_order,
  FieldId::field_spi0_ctrl_wr_bit_order,
  FieldId::field_spi0_ctrl1_cs_hold_delay_res,
  FieldId::field_spi0_ctrl1_cs_hold_delay,
  FieldId::field_spi0_ctrl2_setup_time,
  FieldId::field_spi0_ctrl2_hold_time,
  FieldId::field_spi0_ctrl2_ck_out_low_mode,
  FieldId::field_spi0_ctrl2_ck_out_high_mode,
  FieldId::field_spi0_ctrl2_miso_delay_mode,
  FieldId::field_spi0_ctrl2_miso_delay_num,
  FieldId::field_spi0_ctrl2_mosi_delay_mode,
  FieldId::field_spi0_ctrl2_mosi_delay_num,
  FieldId::field_spi0_ctrl2_cs_delay_mode,
  FieldId::field_spi0_ctrl2_cs_delay_num,
  FieldId::field_spi0_date_date,
  FieldId::field_spi0_dma_conf_in_rst,
  FieldId::field_spi0_dma_conf_out_rst,
  FieldId::field_spi0_dma_conf_ahbm_fifo_rst,
  FieldId::field_spi0_dma_conf_ahbm_rst,
  FieldId::field_spi0_dma_conf_in_loop_test,
  FieldId::field_spi0_dma_conf_out_loop_test,
  FieldId::field_spi0_dma_conf_out_auto_wrback,
  FieldId::field_spi0_dma_conf_out_eof_mode,
  FieldId::field_spi0_dma_conf_outdscr_burst_en,
  FieldId::field_spi0_dma_conf_indscr_burst_en,
  FieldId::field_spi0_dma_conf_out_data_burst_en,
  FieldId::field_spi0_dma_conf_dma_rx_stop,
  FieldId::field_spi0_dma_conf_dma_tx_stop,
  FieldId::field_spi0_dma_conf_dma_continue,
  FieldId::field_spi0_dma_int_clr_inlink_dscr_empty_int_clr,
  FieldId::field_spi0_dma_int_clr_outlink_dscr_error_int_clr,
  FieldId::field_spi0_dma_int_clr_inlink_dscr_error_int_clr,
  FieldId::field_spi0_dma_int_clr_in_done_int_clr,
  FieldId::field_spi0_dma_int_clr_in_err_eof_int_clr,
  FieldId::field_spi0_dma_int_clr_in_suc_eof_int_clr,
  FieldId::field_spi0_dma_int_clr_out_done_int_clr,
  FieldId::field_spi0_dma_int_clr_out_eof_int_clr,
  FieldId::field_spi0_dma_int_clr_out_total_eof_int_clr,
  FieldId::field_spi0_dma_int_ena_inlink_dscr_empty_int_ena,
  FieldId::field_spi0_dma_int_ena_outlink_dscr_error_int_ena,
  FieldId::field_spi0_dma_int_ena_inlink_dscr_error_int_ena,
  FieldId::field_spi0_dma_int_ena_in_done_int_ena,
  FieldId::field_spi0_dma_int_ena_in_err_eof_int_ena,
  FieldId::field_spi0_dma_int_ena_in_suc_eof_int_ena,
  FieldId::field_spi0_dma_int_ena_out_done_int_ena,
  FieldId::field_spi0_dma_int_ena_out_eof_int_ena,
  FieldId::field_spi0_dma_int_ena_out_total_eof_int_ena,
  FieldId::field_spi0_dma_int_raw_inlink_dscr_empty_int_raw,
  FieldId::field_spi0_dma_int_raw_outlink_dscr_error_int_raw,
  FieldId::field_spi0_dma_int_raw_inlink_dscr_error_int_raw,
  FieldId::field_spi0_dma_int_raw_in_done_int_raw,
  FieldId::field_spi0_dma_int_raw_in_err_eof_int_raw,
  FieldId::field_spi0_dma_int_raw_in_suc_eof_int_raw,
  FieldId::field_spi0_dma_int_raw_out_done_int_raw,
  FieldId::field_spi0_dma_int_raw_out_eof_int_raw,
  FieldId::field_spi0_dma_int_raw_out_total_eof_int_raw,
  FieldId::field_spi0_dma_int_st_inlink_dscr_empty_int_st,
  FieldId::field_spi0_dma_int_st_outlink_dscr_error_int_st,
  FieldId::field_spi0_dma_int_st_inlink_dscr_error_int_st,
  FieldId::field_spi0_dma_int_st_in_done_int_st,
  FieldId::field_spi0_dma_int_st_in_err_eof_int_st,
  FieldId::field_spi0_dma_int_st_in_suc_eof_int_st,
  FieldId::field_spi0_dma_int_st_out_done_int_st,
  FieldId::field_spi0_dma_int_st_out_eof_int_st,
  FieldId::field_spi0_dma_int_st_out_total_eof_int_st,
  FieldId::field_spi0_dma_in_link_inlink_addr,
  FieldId::field_spi0_dma_in_link_inlink_auto_ret,
  FieldId::field_spi0_dma_in_link_inlink_stop,
  FieldId::field_spi0_dma_in_link_inlink_start,
  FieldId::field_spi0_dma_in_link_inlink_restart,
  FieldId::field_spi0_dma_out_link_outlink_addr,
  FieldId::field_spi0_dma_out_link_outlink_stop,
  FieldId::field_spi0_dma_out_link_outlink_start,
  FieldId::field_spi0_dma_out_link_outlink_restart,
  FieldId::field_spi0_dma_rstatus_dma_out_status,
  FieldId::field_spi0_dma_status_dma_rx_en,
  FieldId::field_spi0_dma_status_dma_tx_en,
  FieldId::field_spi0_dma_tstatus_dma_in_status,
  FieldId::field_spi0_ext0_t_pp_time,
  FieldId::field_spi0_ext0_t_pp_shift,
  FieldId::field_spi0_ext0_t_pp_ena,
  FieldId::field_spi0_ext1_t_erase_time,
  FieldId::field_spi0_ext1_t_erase_shift,
  FieldId::field_spi0_ext1_t_erase_ena,
  FieldId::field_spi0_ext2_st,
  FieldId::field_spi0_ext3_int_hold_ena,
  FieldId::field_spi0_inlink_dscr_dma_inlink_dscr,
  FieldId::field_spi0_inlink_dscr_bf0_dma_inlink_dscr_bf0,
  FieldId::field_spi0_inlink_dscr_bf1_dma_inlink_dscr_bf1,
  FieldId::field_spi0_in_err_eof_des_addr_dma_in_err_eof_des_addr,
  FieldId::field_spi0_in_suc_eof_des_addr_dma_in_suc_eof_des_addr,
  FieldId::field_spi0_miso_dlen_usr_miso_dbitlen,
  FieldId::field_spi0_mosi_dlen_usr_mosi_dbitlen,
  FieldId::field_spi0_outlink_dscr_dma_outlink_dscr,
  FieldId::field_spi0_outlink_dscr_bf0_dma_outlink_dscr_bf0,
  FieldId::field_spi0_outlink_dscr_bf1_dma_outlink_dscr_bf1,
  FieldId::field_spi0_out_eof_bfr_des_addr_dma_out_eof_bfr_des_addr,
  FieldId::field_spi0_out_eof_des_addr_dma_out_eof_des_addr,
  FieldId::field_spi0_pin_cs0_dis,
  FieldId::field_spi0_pin_cs1_dis,
  FieldId::field_spi0_pin_cs2_dis,
  FieldId::field_spi0_pin_ck_dis,
  FieldId::field_spi0_pin_master_cs_pol,
  FieldId::field_spi0_pin_master_ck_sel,
  FieldId::field_spi0_pin_ck_idle_edge,
  FieldId::field_spi0_pin_cs_keep_active,
  FieldId::field_spi0_rd_status_status,
  FieldId::field_spi0_rd_status_wb_mode,
  FieldId::field_spi0_rd_status_status_ext,
  FieldId::field_spi0_slave_slv_rd_buf_done,
  FieldId::field_spi0_slave_slv_wr_buf_done,
  FieldId::field_spi0_slave_slv_rd_sta_done,
  FieldId::field_spi0_slave_slv_wr_sta_done,
  FieldId::field_spi0_slave_trans_done,
  FieldId::field_spi0_slave_int_en,
  FieldId::field_spi0_slave_cs_i_mode,
  FieldId::field_spi0_slave_slv_last_command,
  FieldId::field_spi0_slave_slv_last_state,
  FieldId::field_spi0_slave_trans_cnt,
  FieldId::field_spi0_slave_slv_cmd_define,
  FieldId::field_spi0_slave_slv_wr_rd_sta_en,
  FieldId::field_spi0_slave_slv_wr_rd_buf_en,
  FieldId::field_spi0_slave_mode,
  FieldId::field_spi0_slave_sync_reset,
  FieldId::field_spi0_slave1_slv_rdbuf_dummy_en,
  FieldId::field_spi0_slave1_slv_wrbuf_dummy_en,
  FieldId::field_spi0_slave1_slv_rdsta_dummy_en,
  FieldId::field_spi0_slave1_slv_wrsta_dummy_en,
  FieldId::field_spi0_slave1_slv_wr_addr_bitlen,
  FieldId::field_spi0_slave1_slv_rd_addr_bitlen,
  FieldId::field_spi0_slave1_slv_status_readback,
  FieldId::field_spi0_slave1_slv_status_fast_en,
  FieldId::field_spi0_slave1_slv_status_bitlen,
  FieldId::field_spi0_slave2_slv_rdsta_dummy_cyclelen,
  FieldId::field_spi0_slave2_slv_wrsta_dummy_cyclelen,
  FieldId::field_spi0_slave2_slv_rdbuf_dummy_cyclelen,
  FieldId::field_spi0_slave2_slv_wrbuf_dummy_cyclelen,
  FieldId::field_spi0_slave3_slv_rdbuf_cmd_value,
  FieldId::field_spi0_slave3_slv_wrbuf_cmd_value,
  FieldId::field_spi0_slave3_slv_rdsta_cmd_value,
  FieldId::field_spi0_slave3_slv_wrsta_cmd_value,
  FieldId::field_spi0_slv_rdbuf_dlen_slv_rdbuf_dbitlen,
  FieldId::field_spi0_slv_rd_bit_slv_rdata_bit,
  FieldId::field_spi0_slv_wrbuf_dlen_slv_wrbuf_dbitlen,
  FieldId::field_spi0_slv_wr_status_slv_wr_st,
  FieldId::field_spi0_sram_cmd_sram_dio,
  FieldId::field_spi0_sram_cmd_sram_qio,
  FieldId::field_spi0_sram_cmd_sram_rstio,
  FieldId::field_spi0_sram_drd_cmd_cache_sram_usr_rd_cmd_value,
  FieldId::field_spi0_sram_drd_cmd_cache_sram_usr_rd_cmd_bitlen,
  FieldId::field_spi0_sram_dwr_cmd_cache_sram_usr_wr_cmd_value,
  FieldId::field_spi0_sram_dwr_cmd_cache_sram_usr_wr_cmd_bitlen,
  FieldId::field_spi0_tx_crc_data,
  FieldId::field_spi0_user_doutdin,
  FieldId::field_spi0_user_cs_hold,
  FieldId::field_spi0_user_cs_setup,
  FieldId::field_spi0_user_ck_i_edge,
  FieldId::field_spi0_user_ck_out_edge,
  FieldId::field_spi0_user_rd_byte_order,
  FieldId::field_spi0_user_wr_byte_order,
  FieldId::field_spi0_user_fwrite_dual,
  FieldId::field_spi0_user_fwrite_quad,
  FieldId::field_spi0_user_fwrite_dio,
  FieldId::field_spi0_user_fwrite_qio,
  FieldId::field_spi0_user_sio,
  FieldId::field_spi0_user_usr_hold_pol,
  FieldId::field_spi0_user_usr_dout_hold,
  FieldId::field_spi0_user_usr_din_hold,
  FieldId::field_spi0_user_usr_dummy_hold,
  FieldId::field_spi0_user_usr_addr_hold,
  FieldId::field_spi0_user_usr_cmd_hold,
  FieldId::field_spi0_user_usr_prep_hold,
  FieldId::field_spi0_user_usr_miso_highpart,
  FieldId::field_spi0_user_usr_mosi_highpart,
  FieldId::field_spi0_user_usr_dummy_idle,
  FieldId::field_spi0_user_usr_mosi,
  FieldId::field_spi0_user_usr_miso,
  FieldId::field_spi0_user_usr_dummy,
  FieldId::field_spi0_user_usr_addr,
  FieldId::field_spi0_user_usr_command,
  FieldId::field_spi0_user1_usr_dummy_cyclelen,
  FieldId::field_spi0_user1_usr_addr_bitlen,
  FieldId::field_spi0_user2_usr_command_value,
  FieldId::field_spi0_user2_usr_command_bitlen,
  FieldId::field_spi0_w0_buf0,
  FieldId::field_spi0_w1_buf1,
  FieldId::field_spi0_w10_buf10,
  FieldId::field_spi0_w11_buf11,
  FieldId::field_spi0_w12_buf12,
  FieldId::field_spi0_w13_buf13,
  FieldId::field_spi0_w14_buf14,
  FieldId::field_spi0_w15_buf15,
  FieldId::field_spi0_w2_buf2,
  FieldId::field_spi0_w3_buf3,
  FieldId::field_spi0_w4_buf4,
  FieldId::field_spi0_w5_buf5,
  FieldId::field_spi0_w6_buf6,
  FieldId::field_spi0_w7_buf7,
  FieldId::field_spi0_w8_buf8,
  FieldId::field_spi0_w9_buf9,
  FieldId::field_spi1_cache_fctrl_cache_req_en,
  FieldId::field_spi1_cache_fctrl_cache_usr_cmd_4byte,
  FieldId::field_spi1_cache_fctrl_cache_flash_usr_cmd,
  FieldId::field_spi1_cache_fctrl_cache_flash_pes_en,
  FieldId::field_spi1_cache_sctrl_usr_sram_dio,
  FieldId::field_spi1_cache_sctrl_usr_sram_qio,
  FieldId::field_spi1_cache_sctrl_usr_wr_sram_dummy,
  FieldId::field_spi1_cache_sctrl_usr_rd_sram_dummy,
  FieldId::field_spi1_cache_sctrl_cache_sram_usr_rcmd,
  FieldId::field_spi1_cache_sctrl_sram_bytes_len,
  FieldId::field_spi1_cache_sctrl_sram_dummy_cyclelen,
  FieldId::field_spi1_cache_sctrl_sram_addr_bitlen,
  FieldId::field_spi1_cache_sctrl_cache_sram_usr_wcmd,
  FieldId::field_spi1_clock_clkcnt_l,
  FieldId::field_spi1_clock_clkcnt_h,
  FieldId::field_spi1_clock_clkcnt_n,
  FieldId::field_spi1_clock_clkdiv_pre,
  FieldId::field_spi1_clock_clk_equ_sysclk,
  FieldId::field_spi1_cmd_flash_per,
  FieldId::field_spi1_cmd_flash_pes,
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
  FieldId::field_spi1_ctrl_fcs_crc_en,
  FieldId::field_spi1_ctrl_tx_crc_en,
  FieldId::field_spi1_ctrl_wait_flash_idle_en,
  FieldId::field_spi1_ctrl_fastrd_mode,
  FieldId::field_spi1_ctrl_fread_dual,
  FieldId::field_spi1_ctrl_resandres,
  FieldId::field_spi1_ctrl_fread_quad,
  FieldId::field_spi1_ctrl_wp,
  FieldId::field_spi1_ctrl_wrsr_2b,
  FieldId::field_spi1_ctrl_fread_dio,
  FieldId::field_spi1_ctrl_fread_qio,
  FieldId::field_spi1_ctrl_rd_bit_order,
  FieldId::field_spi1_ctrl_wr_bit_order,
  FieldId::field_spi1_ctrl1_cs_hold_delay_res,
  FieldId::field_spi1_ctrl1_cs_hold_delay,
  FieldId::field_spi1_ctrl2_setup_time,
  FieldId::field_spi1_ctrl2_hold_time,
  FieldId::field_spi1_ctrl2_ck_out_low_mode,
  FieldId::field_spi1_ctrl2_ck_out_high_mode,
  FieldId::field_spi1_ctrl2_miso_delay_mode,
  FieldId::field_spi1_ctrl2_miso_delay_num,
  FieldId::field_spi1_ctrl2_mosi_delay_mode,
  FieldId::field_spi1_ctrl2_mosi_delay_num,
  FieldId::field_spi1_ctrl2_cs_delay_mode,
  FieldId::field_spi1_ctrl2_cs_delay_num,
  FieldId::field_spi1_date_date,
  FieldId::field_spi1_dma_conf_in_rst,
  FieldId::field_spi1_dma_conf_out_rst,
  FieldId::field_spi1_dma_conf_ahbm_fifo_rst,
  FieldId::field_spi1_dma_conf_ahbm_rst,
  FieldId::field_spi1_dma_conf_in_loop_test,
  FieldId::field_spi1_dma_conf_out_loop_test,
  FieldId::field_spi1_dma_conf_out_auto_wrback,
  FieldId::field_spi1_dma_conf_out_eof_mode,
  FieldId::field_spi1_dma_conf_outdscr_burst_en,
  FieldId::field_spi1_dma_conf_indscr_burst_en,
  FieldId::field_spi1_dma_conf_out_data_burst_en,
  FieldId::field_spi1_dma_conf_dma_rx_stop,
  FieldId::field_spi1_dma_conf_dma_tx_stop,
  FieldId::field_spi1_dma_conf_dma_continue,
  FieldId::field_spi1_dma_int_clr_inlink_dscr_empty_int_clr,
  FieldId::field_spi1_dma_int_clr_outlink_dscr_error_int_clr,
  FieldId::field_spi1_dma_int_clr_inlink_dscr_error_int_clr,
  FieldId::field_spi1_dma_int_clr_in_done_int_clr,
  FieldId::field_spi1_dma_int_clr_in_err_eof_int_clr,
  FieldId::field_spi1_dma_int_clr_in_suc_eof_int_clr,
  FieldId::field_spi1_dma_int_clr_out_done_int_clr,
  FieldId::field_spi1_dma_int_clr_out_eof_int_clr,
  FieldId::field_spi1_dma_int_clr_out_total_eof_int_clr,
  FieldId::field_spi1_dma_int_ena_inlink_dscr_empty_int_ena,
  FieldId::field_spi1_dma_int_ena_outlink_dscr_error_int_ena,
  FieldId::field_spi1_dma_int_ena_inlink_dscr_error_int_ena,
  FieldId::field_spi1_dma_int_ena_in_done_int_ena,
  FieldId::field_spi1_dma_int_ena_in_err_eof_int_ena,
  FieldId::field_spi1_dma_int_ena_in_suc_eof_int_ena,
  FieldId::field_spi1_dma_int_ena_out_done_int_ena,
  FieldId::field_spi1_dma_int_ena_out_eof_int_ena,
  FieldId::field_spi1_dma_int_ena_out_total_eof_int_ena,
  FieldId::field_spi1_dma_int_raw_inlink_dscr_empty_int_raw,
  FieldId::field_spi1_dma_int_raw_outlink_dscr_error_int_raw,
  FieldId::field_spi1_dma_int_raw_inlink_dscr_error_int_raw,
  FieldId::field_spi1_dma_int_raw_in_done_int_raw,
  FieldId::field_spi1_dma_int_raw_in_err_eof_int_raw,
  FieldId::field_spi1_dma_int_raw_in_suc_eof_int_raw,
  FieldId::field_spi1_dma_int_raw_out_done_int_raw,
  FieldId::field_spi1_dma_int_raw_out_eof_int_raw,
  FieldId::field_spi1_dma_int_raw_out_total_eof_int_raw,
  FieldId::field_spi1_dma_int_st_inlink_dscr_empty_int_st,
  FieldId::field_spi1_dma_int_st_outlink_dscr_error_int_st,
  FieldId::field_spi1_dma_int_st_inlink_dscr_error_int_st,
  FieldId::field_spi1_dma_int_st_in_done_int_st,
  FieldId::field_spi1_dma_int_st_in_err_eof_int_st,
  FieldId::field_spi1_dma_int_st_in_suc_eof_int_st,
  FieldId::field_spi1_dma_int_st_out_done_int_st,
  FieldId::field_spi1_dma_int_st_out_eof_int_st,
  FieldId::field_spi1_dma_int_st_out_total_eof_int_st,
  FieldId::field_spi1_dma_in_link_inlink_addr,
  FieldId::field_spi1_dma_in_link_inlink_auto_ret,
  FieldId::field_spi1_dma_in_link_inlink_stop,
  FieldId::field_spi1_dma_in_link_inlink_start,
  FieldId::field_spi1_dma_in_link_inlink_restart,
  FieldId::field_spi1_dma_out_link_outlink_addr,
  FieldId::field_spi1_dma_out_link_outlink_stop,
  FieldId::field_spi1_dma_out_link_outlink_start,
  FieldId::field_spi1_dma_out_link_outlink_restart,
  FieldId::field_spi1_dma_rstatus_dma_out_status,
  FieldId::field_spi1_dma_status_dma_rx_en,
  FieldId::field_spi1_dma_status_dma_tx_en,
  FieldId::field_spi1_dma_tstatus_dma_in_status,
  FieldId::field_spi1_ext0_t_pp_time,
  FieldId::field_spi1_ext0_t_pp_shift,
  FieldId::field_spi1_ext0_t_pp_ena,
  FieldId::field_spi1_ext1_t_erase_time,
  FieldId::field_spi1_ext1_t_erase_shift,
  FieldId::field_spi1_ext1_t_erase_ena,
  FieldId::field_spi1_ext2_st,
  FieldId::field_spi1_ext3_int_hold_ena,
  FieldId::field_spi1_inlink_dscr_dma_inlink_dscr,
  FieldId::field_spi1_inlink_dscr_bf0_dma_inlink_dscr_bf0,
  FieldId::field_spi1_inlink_dscr_bf1_dma_inlink_dscr_bf1,
  FieldId::field_spi1_in_err_eof_des_addr_dma_in_err_eof_des_addr,
  FieldId::field_spi1_in_suc_eof_des_addr_dma_in_suc_eof_des_addr,
  FieldId::field_spi1_miso_dlen_usr_miso_dbitlen,
  FieldId::field_spi1_mosi_dlen_usr_mosi_dbitlen,
  FieldId::field_spi1_outlink_dscr_dma_outlink_dscr,
  FieldId::field_spi1_outlink_dscr_bf0_dma_outlink_dscr_bf0,
  FieldId::field_spi1_outlink_dscr_bf1_dma_outlink_dscr_bf1,
  FieldId::field_spi1_out_eof_bfr_des_addr_dma_out_eof_bfr_des_addr,
  FieldId::field_spi1_out_eof_des_addr_dma_out_eof_des_addr,
  FieldId::field_spi1_pin_cs0_dis,
  FieldId::field_spi1_pin_cs1_dis,
  FieldId::field_spi1_pin_cs2_dis,
  FieldId::field_spi1_pin_ck_dis,
  FieldId::field_spi1_pin_master_cs_pol,
  FieldId::field_spi1_pin_master_ck_sel,
  FieldId::field_spi1_pin_ck_idle_edge,
  FieldId::field_spi1_pin_cs_keep_active,
  FieldId::field_spi1_rd_status_status,
  FieldId::field_spi1_rd_status_wb_mode,
  FieldId::field_spi1_rd_status_status_ext,
  FieldId::field_spi1_slave_slv_rd_buf_done,
  FieldId::field_spi1_slave_slv_wr_buf_done,
  FieldId::field_spi1_slave_slv_rd_sta_done,
  FieldId::field_spi1_slave_slv_wr_sta_done,
  FieldId::field_spi1_slave_trans_done,
  FieldId::field_spi1_slave_int_en,
  FieldId::field_spi1_slave_cs_i_mode,
  FieldId::field_spi1_slave_slv_last_command,
  FieldId::field_spi1_slave_slv_last_state,
  FieldId::field_spi1_slave_trans_cnt,
  FieldId::field_spi1_slave_slv_cmd_define,
  FieldId::field_spi1_slave_slv_wr_rd_sta_en,
  FieldId::field_spi1_slave_slv_wr_rd_buf_en,
  FieldId::field_spi1_slave_mode,
  FieldId::field_spi1_slave_sync_reset,
  FieldId::field_spi1_slave1_slv_rdbuf_dummy_en,
  FieldId::field_spi1_slave1_slv_wrbuf_dummy_en,
  FieldId::field_spi1_slave1_slv_rdsta_dummy_en,
  FieldId::field_spi1_slave1_slv_wrsta_dummy_en,
  FieldId::field_spi1_slave1_slv_wr_addr_bitlen,
  FieldId::field_spi1_slave1_slv_rd_addr_bitlen,
  FieldId::field_spi1_slave1_slv_status_readback,
  FieldId::field_spi1_slave1_slv_status_fast_en,
  FieldId::field_spi1_slave1_slv_status_bitlen,
  FieldId::field_spi1_slave2_slv_rdsta_dummy_cyclelen,
  FieldId::field_spi1_slave2_slv_wrsta_dummy_cyclelen,
  FieldId::field_spi1_slave2_slv_rdbuf_dummy_cyclelen,
  FieldId::field_spi1_slave2_slv_wrbuf_dummy_cyclelen,
  FieldId::field_spi1_slave3_slv_rdbuf_cmd_value,
  FieldId::field_spi1_slave3_slv_wrbuf_cmd_value,
  FieldId::field_spi1_slave3_slv_rdsta_cmd_value,
  FieldId::field_spi1_slave3_slv_wrsta_cmd_value,
  FieldId::field_spi1_slv_rdbuf_dlen_slv_rdbuf_dbitlen,
  FieldId::field_spi1_slv_rd_bit_slv_rdata_bit,
  FieldId::field_spi1_slv_wrbuf_dlen_slv_wrbuf_dbitlen,
  FieldId::field_spi1_slv_wr_status_slv_wr_st,
  FieldId::field_spi1_sram_cmd_sram_dio,
  FieldId::field_spi1_sram_cmd_sram_qio,
  FieldId::field_spi1_sram_cmd_sram_rstio,
  FieldId::field_spi1_sram_drd_cmd_cache_sram_usr_rd_cmd_value,
  FieldId::field_spi1_sram_drd_cmd_cache_sram_usr_rd_cmd_bitlen,
  FieldId::field_spi1_sram_dwr_cmd_cache_sram_usr_wr_cmd_value,
  FieldId::field_spi1_sram_dwr_cmd_cache_sram_usr_wr_cmd_bitlen,
  FieldId::field_spi1_tx_crc_data,
  FieldId::field_spi1_user_doutdin,
  FieldId::field_spi1_user_cs_hold,
  FieldId::field_spi1_user_cs_setup,
  FieldId::field_spi1_user_ck_i_edge,
  FieldId::field_spi1_user_ck_out_edge,
  FieldId::field_spi1_user_rd_byte_order,
  FieldId::field_spi1_user_wr_byte_order,
  FieldId::field_spi1_user_fwrite_dual,
  FieldId::field_spi1_user_fwrite_quad,
  FieldId::field_spi1_user_fwrite_dio,
  FieldId::field_spi1_user_fwrite_qio,
  FieldId::field_spi1_user_sio,
  FieldId::field_spi1_user_usr_hold_pol,
  FieldId::field_spi1_user_usr_dout_hold,
  FieldId::field_spi1_user_usr_din_hold,
  FieldId::field_spi1_user_usr_dummy_hold,
  FieldId::field_spi1_user_usr_addr_hold,
  FieldId::field_spi1_user_usr_cmd_hold,
  FieldId::field_spi1_user_usr_prep_hold,
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
  FieldId::field_spi2_cache_fctrl_cache_req_en,
  FieldId::field_spi2_cache_fctrl_cache_usr_cmd_4byte,
  FieldId::field_spi2_cache_fctrl_cache_flash_usr_cmd,
  FieldId::field_spi2_cache_fctrl_cache_flash_pes_en,
  FieldId::field_spi2_cache_sctrl_usr_sram_dio,
  FieldId::field_spi2_cache_sctrl_usr_sram_qio,
  FieldId::field_spi2_cache_sctrl_usr_wr_sram_dummy,
  FieldId::field_spi2_cache_sctrl_usr_rd_sram_dummy,
  FieldId::field_spi2_cache_sctrl_cache_sram_usr_rcmd,
  FieldId::field_spi2_cache_sctrl_sram_bytes_len,
  FieldId::field_spi2_cache_sctrl_sram_dummy_cyclelen,
  FieldId::field_spi2_cache_sctrl_sram_addr_bitlen,
  FieldId::field_spi2_cache_sctrl_cache_sram_usr_wcmd,
  FieldId::field_spi2_clock_clkcnt_l,
  FieldId::field_spi2_clock_clkcnt_h,
  FieldId::field_spi2_clock_clkcnt_n,
  FieldId::field_spi2_clock_clkdiv_pre,
  FieldId::field_spi2_clock_clk_equ_sysclk,
  FieldId::field_spi2_cmd_flash_per,
  FieldId::field_spi2_cmd_flash_pes,
  FieldId::field_spi2_cmd_usr,
  FieldId::field_spi2_cmd_flash_hpm,
  FieldId::field_spi2_cmd_flash_res,
  FieldId::field_spi2_cmd_flash_dp,
  FieldId::field_spi2_cmd_flash_ce,
  FieldId::field_spi2_cmd_flash_be,
  FieldId::field_spi2_cmd_flash_se,
  FieldId::field_spi2_cmd_flash_pp,
  FieldId::field_spi2_cmd_flash_wrsr,
  FieldId::field_spi2_cmd_flash_rdsr,
  FieldId::field_spi2_cmd_flash_rdid,
  FieldId::field_spi2_cmd_flash_wrdi,
  FieldId::field_spi2_cmd_flash_wren,
  FieldId::field_spi2_cmd_flash_read,
  FieldId::field_spi2_ctrl_fcs_crc_en,
  FieldId::field_spi2_ctrl_tx_crc_en,
  FieldId::field_spi2_ctrl_wait_flash_idle_en,
  FieldId::field_spi2_ctrl_fastrd_mode,
  FieldId::field_spi2_ctrl_fread_dual,
  FieldId::field_spi2_ctrl_resandres,
  FieldId::field_spi2_ctrl_fread_quad,
  FieldId::field_spi2_ctrl_wp,
  FieldId::field_spi2_ctrl_wrsr_2b,
  FieldId::field_spi2_ctrl_fread_dio,
  FieldId::field_spi2_ctrl_fread_qio,
  FieldId::field_spi2_ctrl_rd_bit_order,
  FieldId::field_spi2_ctrl_wr_bit_order,
  FieldId::field_spi2_ctrl1_cs_hold_delay_res,
  FieldId::field_spi2_ctrl1_cs_hold_delay,
  FieldId::field_spi2_ctrl2_setup_time,
  FieldId::field_spi2_ctrl2_hold_time,
  FieldId::field_spi2_ctrl2_ck_out_low_mode,
  FieldId::field_spi2_ctrl2_ck_out_high_mode,
  FieldId::field_spi2_ctrl2_miso_delay_mode,
  FieldId::field_spi2_ctrl2_miso_delay_num,
  FieldId::field_spi2_ctrl2_mosi_delay_mode,
  FieldId::field_spi2_ctrl2_mosi_delay_num,
  FieldId::field_spi2_ctrl2_cs_delay_mode,
  FieldId::field_spi2_ctrl2_cs_delay_num,
  FieldId::field_spi2_date_date,
  FieldId::field_spi2_dma_conf_in_rst,
  FieldId::field_spi2_dma_conf_out_rst,
  FieldId::field_spi2_dma_conf_ahbm_fifo_rst,
  FieldId::field_spi2_dma_conf_ahbm_rst,
  FieldId::field_spi2_dma_conf_in_loop_test,
  FieldId::field_spi2_dma_conf_out_loop_test,
  FieldId::field_spi2_dma_conf_out_auto_wrback,
  FieldId::field_spi2_dma_conf_out_eof_mode,
  FieldId::field_spi2_dma_conf_outdscr_burst_en,
  FieldId::field_spi2_dma_conf_indscr_burst_en,
  FieldId::field_spi2_dma_conf_out_data_burst_en,
  FieldId::field_spi2_dma_conf_dma_rx_stop,
  FieldId::field_spi2_dma_conf_dma_tx_stop,
  FieldId::field_spi2_dma_conf_dma_continue,
  FieldId::field_spi2_dma_int_clr_inlink_dscr_empty_int_clr,
  FieldId::field_spi2_dma_int_clr_outlink_dscr_error_int_clr,
  FieldId::field_spi2_dma_int_clr_inlink_dscr_error_int_clr,
  FieldId::field_spi2_dma_int_clr_in_done_int_clr,
  FieldId::field_spi2_dma_int_clr_in_err_eof_int_clr,
  FieldId::field_spi2_dma_int_clr_in_suc_eof_int_clr,
  FieldId::field_spi2_dma_int_clr_out_done_int_clr,
  FieldId::field_spi2_dma_int_clr_out_eof_int_clr,
  FieldId::field_spi2_dma_int_clr_out_total_eof_int_clr,
  FieldId::field_spi2_dma_int_ena_inlink_dscr_empty_int_ena,
  FieldId::field_spi2_dma_int_ena_outlink_dscr_error_int_ena,
  FieldId::field_spi2_dma_int_ena_inlink_dscr_error_int_ena,
  FieldId::field_spi2_dma_int_ena_in_done_int_ena,
  FieldId::field_spi2_dma_int_ena_in_err_eof_int_ena,
  FieldId::field_spi2_dma_int_ena_in_suc_eof_int_ena,
  FieldId::field_spi2_dma_int_ena_out_done_int_ena,
  FieldId::field_spi2_dma_int_ena_out_eof_int_ena,
  FieldId::field_spi2_dma_int_ena_out_total_eof_int_ena,
  FieldId::field_spi2_dma_int_raw_inlink_dscr_empty_int_raw,
  FieldId::field_spi2_dma_int_raw_outlink_dscr_error_int_raw,
  FieldId::field_spi2_dma_int_raw_inlink_dscr_error_int_raw,
  FieldId::field_spi2_dma_int_raw_in_done_int_raw,
  FieldId::field_spi2_dma_int_raw_in_err_eof_int_raw,
  FieldId::field_spi2_dma_int_raw_in_suc_eof_int_raw,
  FieldId::field_spi2_dma_int_raw_out_done_int_raw,
  FieldId::field_spi2_dma_int_raw_out_eof_int_raw,
  FieldId::field_spi2_dma_int_raw_out_total_eof_int_raw,
  FieldId::field_spi2_dma_int_st_inlink_dscr_empty_int_st,
  FieldId::field_spi2_dma_int_st_outlink_dscr_error_int_st,
  FieldId::field_spi2_dma_int_st_inlink_dscr_error_int_st,
  FieldId::field_spi2_dma_int_st_in_done_int_st,
  FieldId::field_spi2_dma_int_st_in_err_eof_int_st,
  FieldId::field_spi2_dma_int_st_in_suc_eof_int_st,
  FieldId::field_spi2_dma_int_st_out_done_int_st,
  FieldId::field_spi2_dma_int_st_out_eof_int_st,
  FieldId::field_spi2_dma_int_st_out_total_eof_int_st,
  FieldId::field_spi2_dma_in_link_inlink_addr,
  FieldId::field_spi2_dma_in_link_inlink_auto_ret,
  FieldId::field_spi2_dma_in_link_inlink_stop,
  FieldId::field_spi2_dma_in_link_inlink_start,
  FieldId::field_spi2_dma_in_link_inlink_restart,
  FieldId::field_spi2_dma_out_link_outlink_addr,
  FieldId::field_spi2_dma_out_link_outlink_stop,
  FieldId::field_spi2_dma_out_link_outlink_start,
  FieldId::field_spi2_dma_out_link_outlink_restart,
  FieldId::field_spi2_dma_rstatus_dma_out_status,
  FieldId::field_spi2_dma_status_dma_rx_en,
  FieldId::field_spi2_dma_status_dma_tx_en,
  FieldId::field_spi2_dma_tstatus_dma_in_status,
  FieldId::field_spi2_ext0_t_pp_time,
  FieldId::field_spi2_ext0_t_pp_shift,
  FieldId::field_spi2_ext0_t_pp_ena,
  FieldId::field_spi2_ext1_t_erase_time,
  FieldId::field_spi2_ext1_t_erase_shift,
  FieldId::field_spi2_ext1_t_erase_ena,
  FieldId::field_spi2_ext2_st,
  FieldId::field_spi2_ext3_int_hold_ena,
  FieldId::field_spi2_inlink_dscr_dma_inlink_dscr,
  FieldId::field_spi2_inlink_dscr_bf0_dma_inlink_dscr_bf0,
  FieldId::field_spi2_inlink_dscr_bf1_dma_inlink_dscr_bf1,
  FieldId::field_spi2_in_err_eof_des_addr_dma_in_err_eof_des_addr,
  FieldId::field_spi2_in_suc_eof_des_addr_dma_in_suc_eof_des_addr,
  FieldId::field_spi2_miso_dlen_usr_miso_dbitlen,
  FieldId::field_spi2_mosi_dlen_usr_mosi_dbitlen,
  FieldId::field_spi2_outlink_dscr_dma_outlink_dscr,
  FieldId::field_spi2_outlink_dscr_bf0_dma_outlink_dscr_bf0,
  FieldId::field_spi2_outlink_dscr_bf1_dma_outlink_dscr_bf1,
  FieldId::field_spi2_out_eof_bfr_des_addr_dma_out_eof_bfr_des_addr,
  FieldId::field_spi2_out_eof_des_addr_dma_out_eof_des_addr,
  FieldId::field_spi2_pin_cs0_dis,
  FieldId::field_spi2_pin_cs1_dis,
  FieldId::field_spi2_pin_cs2_dis,
  FieldId::field_spi2_pin_ck_dis,
  FieldId::field_spi2_pin_master_cs_pol,
  FieldId::field_spi2_pin_master_ck_sel,
  FieldId::field_spi2_pin_ck_idle_edge,
  FieldId::field_spi2_pin_cs_keep_active,
  FieldId::field_spi2_rd_status_status,
  FieldId::field_spi2_rd_status_wb_mode,
  FieldId::field_spi2_rd_status_status_ext,
  FieldId::field_spi2_slave_slv_rd_buf_done,
  FieldId::field_spi2_slave_slv_wr_buf_done,
  FieldId::field_spi2_slave_slv_rd_sta_done,
  FieldId::field_spi2_slave_slv_wr_sta_done,
  FieldId::field_spi2_slave_trans_done,
  FieldId::field_spi2_slave_int_en,
  FieldId::field_spi2_slave_cs_i_mode,
  FieldId::field_spi2_slave_slv_last_command,
  FieldId::field_spi2_slave_slv_last_state,
  FieldId::field_spi2_slave_trans_cnt,
  FieldId::field_spi2_slave_slv_cmd_define,
  FieldId::field_spi2_slave_slv_wr_rd_sta_en,
  FieldId::field_spi2_slave_slv_wr_rd_buf_en,
  FieldId::field_spi2_slave_mode,
  FieldId::field_spi2_slave_sync_reset,
  FieldId::field_spi2_slave1_slv_rdbuf_dummy_en,
  FieldId::field_spi2_slave1_slv_wrbuf_dummy_en,
  FieldId::field_spi2_slave1_slv_rdsta_dummy_en,
  FieldId::field_spi2_slave1_slv_wrsta_dummy_en,
  FieldId::field_spi2_slave1_slv_wr_addr_bitlen,
  FieldId::field_spi2_slave1_slv_rd_addr_bitlen,
  FieldId::field_spi2_slave1_slv_status_readback,
  FieldId::field_spi2_slave1_slv_status_fast_en,
  FieldId::field_spi2_slave1_slv_status_bitlen,
  FieldId::field_spi2_slave2_slv_rdsta_dummy_cyclelen,
  FieldId::field_spi2_slave2_slv_wrsta_dummy_cyclelen,
  FieldId::field_spi2_slave2_slv_rdbuf_dummy_cyclelen,
  FieldId::field_spi2_slave2_slv_wrbuf_dummy_cyclelen,
  FieldId::field_spi2_slave3_slv_rdbuf_cmd_value,
  FieldId::field_spi2_slave3_slv_wrbuf_cmd_value,
  FieldId::field_spi2_slave3_slv_rdsta_cmd_value,
  FieldId::field_spi2_slave3_slv_wrsta_cmd_value,
  FieldId::field_spi2_slv_rdbuf_dlen_slv_rdbuf_dbitlen,
  FieldId::field_spi2_slv_rd_bit_slv_rdata_bit,
  FieldId::field_spi2_slv_wrbuf_dlen_slv_wrbuf_dbitlen,
  FieldId::field_spi2_slv_wr_status_slv_wr_st,
  FieldId::field_spi2_sram_cmd_sram_dio,
  FieldId::field_spi2_sram_cmd_sram_qio,
  FieldId::field_spi2_sram_cmd_sram_rstio,
  FieldId::field_spi2_sram_drd_cmd_cache_sram_usr_rd_cmd_value,
  FieldId::field_spi2_sram_drd_cmd_cache_sram_usr_rd_cmd_bitlen,
  FieldId::field_spi2_sram_dwr_cmd_cache_sram_usr_wr_cmd_value,
  FieldId::field_spi2_sram_dwr_cmd_cache_sram_usr_wr_cmd_bitlen,
  FieldId::field_spi2_tx_crc_data,
  FieldId::field_spi2_user_doutdin,
  FieldId::field_spi2_user_cs_hold,
  FieldId::field_spi2_user_cs_setup,
  FieldId::field_spi2_user_ck_i_edge,
  FieldId::field_spi2_user_ck_out_edge,
  FieldId::field_spi2_user_rd_byte_order,
  FieldId::field_spi2_user_wr_byte_order,
  FieldId::field_spi2_user_fwrite_dual,
  FieldId::field_spi2_user_fwrite_quad,
  FieldId::field_spi2_user_fwrite_dio,
  FieldId::field_spi2_user_fwrite_qio,
  FieldId::field_spi2_user_sio,
  FieldId::field_spi2_user_usr_hold_pol,
  FieldId::field_spi2_user_usr_dout_hold,
  FieldId::field_spi2_user_usr_din_hold,
  FieldId::field_spi2_user_usr_dummy_hold,
  FieldId::field_spi2_user_usr_addr_hold,
  FieldId::field_spi2_user_usr_cmd_hold,
  FieldId::field_spi2_user_usr_prep_hold,
  FieldId::field_spi2_user_usr_miso_highpart,
  FieldId::field_spi2_user_usr_mosi_highpart,
  FieldId::field_spi2_user_usr_dummy_idle,
  FieldId::field_spi2_user_usr_mosi,
  FieldId::field_spi2_user_usr_miso,
  FieldId::field_spi2_user_usr_dummy,
  FieldId::field_spi2_user_usr_addr,
  FieldId::field_spi2_user_usr_command,
  FieldId::field_spi2_user1_usr_dummy_cyclelen,
  FieldId::field_spi2_user1_usr_addr_bitlen,
  FieldId::field_spi2_user2_usr_command_value,
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
  FieldId::field_spi3_cache_fctrl_cache_req_en,
  FieldId::field_spi3_cache_fctrl_cache_usr_cmd_4byte,
  FieldId::field_spi3_cache_fctrl_cache_flash_usr_cmd,
  FieldId::field_spi3_cache_fctrl_cache_flash_pes_en,
  FieldId::field_spi3_cache_sctrl_usr_sram_dio,
  FieldId::field_spi3_cache_sctrl_usr_sram_qio,
  FieldId::field_spi3_cache_sctrl_usr_wr_sram_dummy,
  FieldId::field_spi3_cache_sctrl_usr_rd_sram_dummy,
  FieldId::field_spi3_cache_sctrl_cache_sram_usr_rcmd,
  FieldId::field_spi3_cache_sctrl_sram_bytes_len,
  FieldId::field_spi3_cache_sctrl_sram_dummy_cyclelen,
  FieldId::field_spi3_cache_sctrl_sram_addr_bitlen,
  FieldId::field_spi3_cache_sctrl_cache_sram_usr_wcmd,
  FieldId::field_spi3_clock_clkcnt_l,
  FieldId::field_spi3_clock_clkcnt_h,
  FieldId::field_spi3_clock_clkcnt_n,
  FieldId::field_spi3_clock_clkdiv_pre,
  FieldId::field_spi3_clock_clk_equ_sysclk,
  FieldId::field_spi3_cmd_flash_per,
  FieldId::field_spi3_cmd_flash_pes,
  FieldId::field_spi3_cmd_usr,
  FieldId::field_spi3_cmd_flash_hpm,
  FieldId::field_spi3_cmd_flash_res,
  FieldId::field_spi3_cmd_flash_dp,
  FieldId::field_spi3_cmd_flash_ce,
  FieldId::field_spi3_cmd_flash_be,
  FieldId::field_spi3_cmd_flash_se,
  FieldId::field_spi3_cmd_flash_pp,
  FieldId::field_spi3_cmd_flash_wrsr,
  FieldId::field_spi3_cmd_flash_rdsr,
  FieldId::field_spi3_cmd_flash_rdid,
  FieldId::field_spi3_cmd_flash_wrdi,
  FieldId::field_spi3_cmd_flash_wren,
  FieldId::field_spi3_cmd_flash_read,
  FieldId::field_spi3_ctrl_fcs_crc_en,
  FieldId::field_spi3_ctrl_tx_crc_en,
  FieldId::field_spi3_ctrl_wait_flash_idle_en,
  FieldId::field_spi3_ctrl_fastrd_mode,
  FieldId::field_spi3_ctrl_fread_dual,
  FieldId::field_spi3_ctrl_resandres,
  FieldId::field_spi3_ctrl_fread_quad,
  FieldId::field_spi3_ctrl_wp,
  FieldId::field_spi3_ctrl_wrsr_2b,
  FieldId::field_spi3_ctrl_fread_dio,
  FieldId::field_spi3_ctrl_fread_qio,
  FieldId::field_spi3_ctrl_rd_bit_order,
  FieldId::field_spi3_ctrl_wr_bit_order,
  FieldId::field_spi3_ctrl1_cs_hold_delay_res,
  FieldId::field_spi3_ctrl1_cs_hold_delay,
  FieldId::field_spi3_ctrl2_setup_time,
  FieldId::field_spi3_ctrl2_hold_time,
  FieldId::field_spi3_ctrl2_ck_out_low_mode,
  FieldId::field_spi3_ctrl2_ck_out_high_mode,
  FieldId::field_spi3_ctrl2_miso_delay_mode,
  FieldId::field_spi3_ctrl2_miso_delay_num,
  FieldId::field_spi3_ctrl2_mosi_delay_mode,
  FieldId::field_spi3_ctrl2_mosi_delay_num,
  FieldId::field_spi3_ctrl2_cs_delay_mode,
  FieldId::field_spi3_ctrl2_cs_delay_num,
  FieldId::field_spi3_date_date,
  FieldId::field_spi3_dma_conf_in_rst,
  FieldId::field_spi3_dma_conf_out_rst,
  FieldId::field_spi3_dma_conf_ahbm_fifo_rst,
  FieldId::field_spi3_dma_conf_ahbm_rst,
  FieldId::field_spi3_dma_conf_in_loop_test,
  FieldId::field_spi3_dma_conf_out_loop_test,
  FieldId::field_spi3_dma_conf_out_auto_wrback,
  FieldId::field_spi3_dma_conf_out_eof_mode,
  FieldId::field_spi3_dma_conf_outdscr_burst_en,
  FieldId::field_spi3_dma_conf_indscr_burst_en,
  FieldId::field_spi3_dma_conf_out_data_burst_en,
  FieldId::field_spi3_dma_conf_dma_rx_stop,
  FieldId::field_spi3_dma_conf_dma_tx_stop,
  FieldId::field_spi3_dma_conf_dma_continue,
  FieldId::field_spi3_dma_int_clr_inlink_dscr_empty_int_clr,
  FieldId::field_spi3_dma_int_clr_outlink_dscr_error_int_clr,
  FieldId::field_spi3_dma_int_clr_inlink_dscr_error_int_clr,
  FieldId::field_spi3_dma_int_clr_in_done_int_clr,
  FieldId::field_spi3_dma_int_clr_in_err_eof_int_clr,
  FieldId::field_spi3_dma_int_clr_in_suc_eof_int_clr,
  FieldId::field_spi3_dma_int_clr_out_done_int_clr,
  FieldId::field_spi3_dma_int_clr_out_eof_int_clr,
  FieldId::field_spi3_dma_int_clr_out_total_eof_int_clr,
  FieldId::field_spi3_dma_int_ena_inlink_dscr_empty_int_ena,
  FieldId::field_spi3_dma_int_ena_outlink_dscr_error_int_ena,
  FieldId::field_spi3_dma_int_ena_inlink_dscr_error_int_ena,
  FieldId::field_spi3_dma_int_ena_in_done_int_ena,
  FieldId::field_spi3_dma_int_ena_in_err_eof_int_ena,
  FieldId::field_spi3_dma_int_ena_in_suc_eof_int_ena,
  FieldId::field_spi3_dma_int_ena_out_done_int_ena,
  FieldId::field_spi3_dma_int_ena_out_eof_int_ena,
  FieldId::field_spi3_dma_int_ena_out_total_eof_int_ena,
  FieldId::field_spi3_dma_int_raw_inlink_dscr_empty_int_raw,
  FieldId::field_spi3_dma_int_raw_outlink_dscr_error_int_raw,
  FieldId::field_spi3_dma_int_raw_inlink_dscr_error_int_raw,
  FieldId::field_spi3_dma_int_raw_in_done_int_raw,
  FieldId::field_spi3_dma_int_raw_in_err_eof_int_raw,
  FieldId::field_spi3_dma_int_raw_in_suc_eof_int_raw,
  FieldId::field_spi3_dma_int_raw_out_done_int_raw,
  FieldId::field_spi3_dma_int_raw_out_eof_int_raw,
  FieldId::field_spi3_dma_int_raw_out_total_eof_int_raw,
  FieldId::field_spi3_dma_int_st_inlink_dscr_empty_int_st,
  FieldId::field_spi3_dma_int_st_outlink_dscr_error_int_st,
  FieldId::field_spi3_dma_int_st_inlink_dscr_error_int_st,
  FieldId::field_spi3_dma_int_st_in_done_int_st,
  FieldId::field_spi3_dma_int_st_in_err_eof_int_st,
  FieldId::field_spi3_dma_int_st_in_suc_eof_int_st,
  FieldId::field_spi3_dma_int_st_out_done_int_st,
  FieldId::field_spi3_dma_int_st_out_eof_int_st,
  FieldId::field_spi3_dma_int_st_out_total_eof_int_st,
  FieldId::field_spi3_dma_in_link_inlink_addr,
  FieldId::field_spi3_dma_in_link_inlink_auto_ret,
  FieldId::field_spi3_dma_in_link_inlink_stop,
  FieldId::field_spi3_dma_in_link_inlink_start,
  FieldId::field_spi3_dma_in_link_inlink_restart,
  FieldId::field_spi3_dma_out_link_outlink_addr,
  FieldId::field_spi3_dma_out_link_outlink_stop,
  FieldId::field_spi3_dma_out_link_outlink_start,
  FieldId::field_spi3_dma_out_link_outlink_restart,
  FieldId::field_spi3_dma_rstatus_dma_out_status,
  FieldId::field_spi3_dma_status_dma_rx_en,
  FieldId::field_spi3_dma_status_dma_tx_en,
  FieldId::field_spi3_dma_tstatus_dma_in_status,
  FieldId::field_spi3_ext0_t_pp_time,
  FieldId::field_spi3_ext0_t_pp_shift,
  FieldId::field_spi3_ext0_t_pp_ena,
  FieldId::field_spi3_ext1_t_erase_time,
  FieldId::field_spi3_ext1_t_erase_shift,
  FieldId::field_spi3_ext1_t_erase_ena,
  FieldId::field_spi3_ext2_st,
  FieldId::field_spi3_ext3_int_hold_ena,
  FieldId::field_spi3_inlink_dscr_dma_inlink_dscr,
  FieldId::field_spi3_inlink_dscr_bf0_dma_inlink_dscr_bf0,
  FieldId::field_spi3_inlink_dscr_bf1_dma_inlink_dscr_bf1,
  FieldId::field_spi3_in_err_eof_des_addr_dma_in_err_eof_des_addr,
  FieldId::field_spi3_in_suc_eof_des_addr_dma_in_suc_eof_des_addr,
  FieldId::field_spi3_miso_dlen_usr_miso_dbitlen,
  FieldId::field_spi3_mosi_dlen_usr_mosi_dbitlen,
  FieldId::field_spi3_outlink_dscr_dma_outlink_dscr,
  FieldId::field_spi3_outlink_dscr_bf0_dma_outlink_dscr_bf0,
  FieldId::field_spi3_outlink_dscr_bf1_dma_outlink_dscr_bf1,
  FieldId::field_spi3_out_eof_bfr_des_addr_dma_out_eof_bfr_des_addr,
  FieldId::field_spi3_out_eof_des_addr_dma_out_eof_des_addr,
  FieldId::field_spi3_pin_cs0_dis,
  FieldId::field_spi3_pin_cs1_dis,
  FieldId::field_spi3_pin_cs2_dis,
  FieldId::field_spi3_pin_ck_dis,
  FieldId::field_spi3_pin_master_cs_pol,
  FieldId::field_spi3_pin_master_ck_sel,
  FieldId::field_spi3_pin_ck_idle_edge,
  FieldId::field_spi3_pin_cs_keep_active,
  FieldId::field_spi3_rd_status_status,
  FieldId::field_spi3_rd_status_wb_mode,
  FieldId::field_spi3_rd_status_status_ext,
  FieldId::field_spi3_slave_slv_rd_buf_done,
  FieldId::field_spi3_slave_slv_wr_buf_done,
  FieldId::field_spi3_slave_slv_rd_sta_done,
  FieldId::field_spi3_slave_slv_wr_sta_done,
  FieldId::field_spi3_slave_trans_done,
  FieldId::field_spi3_slave_int_en,
  FieldId::field_spi3_slave_cs_i_mode,
  FieldId::field_spi3_slave_slv_last_command,
  FieldId::field_spi3_slave_slv_last_state,
  FieldId::field_spi3_slave_trans_cnt,
  FieldId::field_spi3_slave_slv_cmd_define,
  FieldId::field_spi3_slave_slv_wr_rd_sta_en,
  FieldId::field_spi3_slave_slv_wr_rd_buf_en,
  FieldId::field_spi3_slave_mode,
  FieldId::field_spi3_slave_sync_reset,
  FieldId::field_spi3_slave1_slv_rdbuf_dummy_en,
  FieldId::field_spi3_slave1_slv_wrbuf_dummy_en,
  FieldId::field_spi3_slave1_slv_rdsta_dummy_en,
  FieldId::field_spi3_slave1_slv_wrsta_dummy_en,
  FieldId::field_spi3_slave1_slv_wr_addr_bitlen,
  FieldId::field_spi3_slave1_slv_rd_addr_bitlen,
  FieldId::field_spi3_slave1_slv_status_readback,
  FieldId::field_spi3_slave1_slv_status_fast_en,
  FieldId::field_spi3_slave1_slv_status_bitlen,
  FieldId::field_spi3_slave2_slv_rdsta_dummy_cyclelen,
  FieldId::field_spi3_slave2_slv_wrsta_dummy_cyclelen,
  FieldId::field_spi3_slave2_slv_rdbuf_dummy_cyclelen,
  FieldId::field_spi3_slave2_slv_wrbuf_dummy_cyclelen,
  FieldId::field_spi3_slave3_slv_rdbuf_cmd_value,
  FieldId::field_spi3_slave3_slv_wrbuf_cmd_value,
  FieldId::field_spi3_slave3_slv_rdsta_cmd_value,
  FieldId::field_spi3_slave3_slv_wrsta_cmd_value,
  FieldId::field_spi3_slv_rdbuf_dlen_slv_rdbuf_dbitlen,
  FieldId::field_spi3_slv_rd_bit_slv_rdata_bit,
  FieldId::field_spi3_slv_wrbuf_dlen_slv_wrbuf_dbitlen,
  FieldId::field_spi3_slv_wr_status_slv_wr_st,
  FieldId::field_spi3_sram_cmd_sram_dio,
  FieldId::field_spi3_sram_cmd_sram_qio,
  FieldId::field_spi3_sram_cmd_sram_rstio,
  FieldId::field_spi3_sram_drd_cmd_cache_sram_usr_rd_cmd_value,
  FieldId::field_spi3_sram_drd_cmd_cache_sram_usr_rd_cmd_bitlen,
  FieldId::field_spi3_sram_dwr_cmd_cache_sram_usr_wr_cmd_value,
  FieldId::field_spi3_sram_dwr_cmd_cache_sram_usr_wr_cmd_bitlen,
  FieldId::field_spi3_tx_crc_data,
  FieldId::field_spi3_user_doutdin,
  FieldId::field_spi3_user_cs_hold,
  FieldId::field_spi3_user_cs_setup,
  FieldId::field_spi3_user_ck_i_edge,
  FieldId::field_spi3_user_ck_out_edge,
  FieldId::field_spi3_user_rd_byte_order,
  FieldId::field_spi3_user_wr_byte_order,
  FieldId::field_spi3_user_fwrite_dual,
  FieldId::field_spi3_user_fwrite_quad,
  FieldId::field_spi3_user_fwrite_dio,
  FieldId::field_spi3_user_fwrite_qio,
  FieldId::field_spi3_user_sio,
  FieldId::field_spi3_user_usr_hold_pol,
  FieldId::field_spi3_user_usr_dout_hold,
  FieldId::field_spi3_user_usr_din_hold,
  FieldId::field_spi3_user_usr_dummy_hold,
  FieldId::field_spi3_user_usr_addr_hold,
  FieldId::field_spi3_user_usr_cmd_hold,
  FieldId::field_spi3_user_usr_prep_hold,
  FieldId::field_spi3_user_usr_miso_highpart,
  FieldId::field_spi3_user_usr_mosi_highpart,
  FieldId::field_spi3_user_usr_dummy_idle,
  FieldId::field_spi3_user_usr_mosi,
  FieldId::field_spi3_user_usr_miso,
  FieldId::field_spi3_user_usr_dummy,
  FieldId::field_spi3_user_usr_addr,
  FieldId::field_spi3_user_usr_command,
  FieldId::field_spi3_user1_usr_dummy_cyclelen,
  FieldId::field_spi3_user1_usr_addr_bitlen,
  FieldId::field_spi3_user2_usr_command_value,
  FieldId::field_spi3_user2_usr_command_bitlen,
  FieldId::field_spi3_w0_buf0,
  FieldId::field_spi3_w1_buf1,
  FieldId::field_spi3_w10_buf10,
  FieldId::field_spi3_w11_buf11,
  FieldId::field_spi3_w12_buf12,
  FieldId::field_spi3_w13_buf13,
  FieldId::field_spi3_w14_buf14,
  FieldId::field_spi3_w15_buf15,
  FieldId::field_spi3_w2_buf2,
  FieldId::field_spi3_w3_buf3,
  FieldId::field_spi3_w4_buf4,
  FieldId::field_spi3_w5_buf5,
  FieldId::field_spi3_w6_buf6,
  FieldId::field_spi3_w7_buf7,
  FieldId::field_spi3_w8_buf8,
  FieldId::field_spi3_w9_buf9,
  FieldId::field_uart0_at_cmd_char_at_cmd_char,
  FieldId::field_uart0_at_cmd_char_char_num,
  FieldId::field_uart0_at_cmd_gaptout_rx_gap_tout,
  FieldId::field_uart0_at_cmd_postcnt_post_idle_num,
  FieldId::field_uart0_at_cmd_precnt_pre_idle_num,
  FieldId::field_uart0_autobaud_en,
  FieldId::field_uart0_autobaud_glitch_filt,
  FieldId::field_uart0_clkdiv_clkdiv,
  FieldId::field_uart0_clkdiv_frag,
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
  FieldId::field_uart0_conf0_tick_ref_always_on,
  FieldId::field_uart0_conf1_rxfifo_full_thrhd,
  FieldId::field_uart0_conf1_txfifo_empty_thrhd,
  FieldId::field_uart0_conf1_rx_flow_thrhd,
  FieldId::field_uart0_conf1_rx_flow_en,
  FieldId::field_uart0_conf1_rx_tout_thrhd,
  FieldId::field_uart0_conf1_rx_tout_en,
  FieldId::field_uart0_date_date,
  FieldId::field_uart0_fifo_rxfifo_rd_byte,
  FieldId::field_uart0_flow_conf_sw_flow_con_en,
  FieldId::field_uart0_flow_conf_xonoff_del,
  FieldId::field_uart0_flow_conf_force_xon,
  FieldId::field_uart0_flow_conf_force_xoff,
  FieldId::field_uart0_flow_conf_send_xon,
  FieldId::field_uart0_flow_conf_send_xoff,
  FieldId::field_uart0_highpulse_min_cnt,
  FieldId::field_uart0_id_id,
  FieldId::field_uart0_idle_conf_rx_idle_thrhd,
  FieldId::field_uart0_idle_conf_tx_idle_num,
  FieldId::field_uart0_idle_conf_tx_brk_num,
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
  FieldId::field_uart0_lowpulse_min_cnt,
  FieldId::field_uart0_mem_cnt_status_rx_mem_cnt,
  FieldId::field_uart0_mem_cnt_status_tx_mem_cnt,
  FieldId::field_uart0_mem_conf_mem_pd,
  FieldId::field_uart0_mem_conf_rx_size,
  FieldId::field_uart0_mem_conf_tx_size,
  FieldId::field_uart0_mem_conf_rx_flow_thrhd_h3,
  FieldId::field_uart0_mem_conf_rx_tout_thrhd_h3,
  FieldId::field_uart0_mem_conf_xon_threshold_h2,
  FieldId::field_uart0_mem_conf_xoff_threshold_h2,
  FieldId::field_uart0_mem_conf_rx_mem_full_thrhd,
  FieldId::field_uart0_mem_conf_tx_mem_empty_thrhd,
  FieldId::field_uart0_mem_rx_status_mem_rx_status,
  FieldId::field_uart0_mem_rx_status_mem_rx_rd_addr,
  FieldId::field_uart0_mem_rx_status_mem_rx_wr_addr,
  FieldId::field_uart0_mem_tx_status_mem_tx_status,
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
  FieldId::field_uart0_sleep_conf_active_threshold,
  FieldId::field_uart0_status_rxfifo_cnt,
  FieldId::field_uart0_status_st_urx_out,
  FieldId::field_uart0_status_dsrn,
  FieldId::field_uart0_status_ctsn,
  FieldId::field_uart0_status_rxd,
  FieldId::field_uart0_status_txfifo_cnt,
  FieldId::field_uart0_status_st_utx_out,
  FieldId::field_uart0_status_dtrn,
  FieldId::field_uart0_status_rtsn,
  FieldId::field_uart0_status_txd,
  FieldId::field_uart0_swfc_conf_xon_threshold,
  FieldId::field_uart0_swfc_conf_xoff_threshold,
  FieldId::field_uart0_swfc_conf_xon_char,
  FieldId::field_uart0_swfc_conf_xoff_char,
  FieldId::field_uart1_at_cmd_char_at_cmd_char,
  FieldId::field_uart1_at_cmd_char_char_num,
  FieldId::field_uart1_at_cmd_gaptout_rx_gap_tout,
  FieldId::field_uart1_at_cmd_postcnt_post_idle_num,
  FieldId::field_uart1_at_cmd_precnt_pre_idle_num,
  FieldId::field_uart1_autobaud_en,
  FieldId::field_uart1_autobaud_glitch_filt,
  FieldId::field_uart1_clkdiv_clkdiv,
  FieldId::field_uart1_clkdiv_frag,
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
  FieldId::field_uart1_conf0_tick_ref_always_on,
  FieldId::field_uart1_conf1_rxfifo_full_thrhd,
  FieldId::field_uart1_conf1_txfifo_empty_thrhd,
  FieldId::field_uart1_conf1_rx_flow_thrhd,
  FieldId::field_uart1_conf1_rx_flow_en,
  FieldId::field_uart1_conf1_rx_tout_thrhd,
  FieldId::field_uart1_conf1_rx_tout_en,
  FieldId::field_uart1_date_date,
  FieldId::field_uart1_fifo_rxfifo_rd_byte,
  FieldId::field_uart1_flow_conf_sw_flow_con_en,
  FieldId::field_uart1_flow_conf_xonoff_del,
  FieldId::field_uart1_flow_conf_force_xon,
  FieldId::field_uart1_flow_conf_force_xoff,
  FieldId::field_uart1_flow_conf_send_xon,
  FieldId::field_uart1_flow_conf_send_xoff,
  FieldId::field_uart1_highpulse_min_cnt,
  FieldId::field_uart1_id_id,
  FieldId::field_uart1_idle_conf_rx_idle_thrhd,
  FieldId::field_uart1_idle_conf_tx_idle_num,
  FieldId::field_uart1_idle_conf_tx_brk_num,
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
  FieldId::field_uart1_lowpulse_min_cnt,
  FieldId::field_uart1_mem_cnt_status_rx_mem_cnt,
  FieldId::field_uart1_mem_cnt_status_tx_mem_cnt,
  FieldId::field_uart1_mem_conf_mem_pd,
  FieldId::field_uart1_mem_conf_rx_size,
  FieldId::field_uart1_mem_conf_tx_size,
  FieldId::field_uart1_mem_conf_rx_flow_thrhd_h3,
  FieldId::field_uart1_mem_conf_rx_tout_thrhd_h3,
  FieldId::field_uart1_mem_conf_xon_threshold_h2,
  FieldId::field_uart1_mem_conf_xoff_threshold_h2,
  FieldId::field_uart1_mem_conf_rx_mem_full_thrhd,
  FieldId::field_uart1_mem_conf_tx_mem_empty_thrhd,
  FieldId::field_uart1_mem_rx_status_mem_rx_status,
  FieldId::field_uart1_mem_rx_status_mem_rx_rd_addr,
  FieldId::field_uart1_mem_rx_status_mem_rx_wr_addr,
  FieldId::field_uart1_mem_tx_status_mem_tx_status,
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
  FieldId::field_uart1_sleep_conf_active_threshold,
  FieldId::field_uart1_status_rxfifo_cnt,
  FieldId::field_uart1_status_st_urx_out,
  FieldId::field_uart1_status_dsrn,
  FieldId::field_uart1_status_ctsn,
  FieldId::field_uart1_status_rxd,
  FieldId::field_uart1_status_txfifo_cnt,
  FieldId::field_uart1_status_st_utx_out,
  FieldId::field_uart1_status_dtrn,
  FieldId::field_uart1_status_rtsn,
  FieldId::field_uart1_status_txd,
  FieldId::field_uart1_swfc_conf_xon_threshold,
  FieldId::field_uart1_swfc_conf_xoff_threshold,
  FieldId::field_uart1_swfc_conf_xon_char,
  FieldId::field_uart1_swfc_conf_xoff_char,
  FieldId::field_uart2_at_cmd_char_at_cmd_char,
  FieldId::field_uart2_at_cmd_char_char_num,
  FieldId::field_uart2_at_cmd_gaptout_rx_gap_tout,
  FieldId::field_uart2_at_cmd_postcnt_post_idle_num,
  FieldId::field_uart2_at_cmd_precnt_pre_idle_num,
  FieldId::field_uart2_autobaud_en,
  FieldId::field_uart2_autobaud_glitch_filt,
  FieldId::field_uart2_clkdiv_clkdiv,
  FieldId::field_uart2_clkdiv_frag,
  FieldId::field_uart2_conf0_parity,
  FieldId::field_uart2_conf0_parity_en,
  FieldId::field_uart2_conf0_bit_num,
  FieldId::field_uart2_conf0_stop_bit_num,
  FieldId::field_uart2_conf0_sw_rts,
  FieldId::field_uart2_conf0_sw_dtr,
  FieldId::field_uart2_conf0_txd_brk,
  FieldId::field_uart2_conf0_irda_dplx,
  FieldId::field_uart2_conf0_irda_tx_en,
  FieldId::field_uart2_conf0_irda_wctl,
  FieldId::field_uart2_conf0_irda_tx_inv,
  FieldId::field_uart2_conf0_irda_rx_inv,
  FieldId::field_uart2_conf0_loopback,
  FieldId::field_uart2_conf0_tx_flow_en,
  FieldId::field_uart2_conf0_irda_en,
  FieldId::field_uart2_conf0_rxfifo_rst,
  FieldId::field_uart2_conf0_txfifo_rst,
  FieldId::field_uart2_conf0_rxd_inv,
  FieldId::field_uart2_conf0_cts_inv,
  FieldId::field_uart2_conf0_dsr_inv,
  FieldId::field_uart2_conf0_txd_inv,
  FieldId::field_uart2_conf0_rts_inv,
  FieldId::field_uart2_conf0_dtr_inv,
  FieldId::field_uart2_conf0_clk_en,
  FieldId::field_uart2_conf0_err_wr_mask,
  FieldId::field_uart2_conf0_tick_ref_always_on,
  FieldId::field_uart2_conf1_rxfifo_full_thrhd,
  FieldId::field_uart2_conf1_txfifo_empty_thrhd,
  FieldId::field_uart2_conf1_rx_flow_thrhd,
  FieldId::field_uart2_conf1_rx_flow_en,
  FieldId::field_uart2_conf1_rx_tout_thrhd,
  FieldId::field_uart2_conf1_rx_tout_en,
  FieldId::field_uart2_date_date,
  FieldId::field_uart2_fifo_rxfifo_rd_byte,
  FieldId::field_uart2_flow_conf_sw_flow_con_en,
  FieldId::field_uart2_flow_conf_xonoff_del,
  FieldId::field_uart2_flow_conf_force_xon,
  FieldId::field_uart2_flow_conf_force_xoff,
  FieldId::field_uart2_flow_conf_send_xon,
  FieldId::field_uart2_flow_conf_send_xoff,
  FieldId::field_uart2_highpulse_min_cnt,
  FieldId::field_uart2_id_id,
  FieldId::field_uart2_idle_conf_rx_idle_thrhd,
  FieldId::field_uart2_idle_conf_tx_idle_num,
  FieldId::field_uart2_idle_conf_tx_brk_num,
  FieldId::field_uart2_int_clr_rxfifo_full_int_clr,
  FieldId::field_uart2_int_clr_txfifo_empty_int_clr,
  FieldId::field_uart2_int_clr_parity_err_int_clr,
  FieldId::field_uart2_int_clr_frm_err_int_clr,
  FieldId::field_uart2_int_clr_rxfifo_ovf_int_clr,
  FieldId::field_uart2_int_clr_dsr_chg_int_clr,
  FieldId::field_uart2_int_clr_cts_chg_int_clr,
  FieldId::field_uart2_int_clr_brk_det_int_clr,
  FieldId::field_uart2_int_clr_rxfifo_tout_int_clr,
  FieldId::field_uart2_int_clr_sw_xon_int_clr,
  FieldId::field_uart2_int_clr_sw_xoff_int_clr,
  FieldId::field_uart2_int_clr_glitch_det_int_clr,
  FieldId::field_uart2_int_clr_tx_brk_done_int_clr,
  FieldId::field_uart2_int_clr_tx_brk_idle_done_int_clr,
  FieldId::field_uart2_int_clr_tx_done_int_clr,
  FieldId::field_uart2_int_clr_rs485_parity_err_int_clr,
  FieldId::field_uart2_int_clr_rs485_frm_err_int_clr,
  FieldId::field_uart2_int_clr_rs485_clash_int_clr,
  FieldId::field_uart2_int_clr_at_cmd_char_det_int_clr,
  FieldId::field_uart2_int_ena_rxfifo_full_int_ena,
  FieldId::field_uart2_int_ena_txfifo_empty_int_ena,
  FieldId::field_uart2_int_ena_parity_err_int_ena,
  FieldId::field_uart2_int_ena_frm_err_int_ena,
  FieldId::field_uart2_int_ena_rxfifo_ovf_int_ena,
  FieldId::field_uart2_int_ena_dsr_chg_int_ena,
  FieldId::field_uart2_int_ena_cts_chg_int_ena,
  FieldId::field_uart2_int_ena_brk_det_int_ena,
  FieldId::field_uart2_int_ena_rxfifo_tout_int_ena,
  FieldId::field_uart2_int_ena_sw_xon_int_ena,
  FieldId::field_uart2_int_ena_sw_xoff_int_ena,
  FieldId::field_uart2_int_ena_glitch_det_int_ena,
  FieldId::field_uart2_int_ena_tx_brk_done_int_ena,
  FieldId::field_uart2_int_ena_tx_brk_idle_done_int_ena,
  FieldId::field_uart2_int_ena_tx_done_int_ena,
  FieldId::field_uart2_int_ena_rs485_parity_err_int_ena,
  FieldId::field_uart2_int_ena_rs485_frm_err_int_ena,
  FieldId::field_uart2_int_ena_rs485_clash_int_ena,
  FieldId::field_uart2_int_ena_at_cmd_char_det_int_ena,
  FieldId::field_uart2_int_raw_rxfifo_full_int_raw,
  FieldId::field_uart2_int_raw_txfifo_empty_int_raw,
  FieldId::field_uart2_int_raw_parity_err_int_raw,
  FieldId::field_uart2_int_raw_frm_err_int_raw,
  FieldId::field_uart2_int_raw_rxfifo_ovf_int_raw,
  FieldId::field_uart2_int_raw_dsr_chg_int_raw,
  FieldId::field_uart2_int_raw_cts_chg_int_raw,
  FieldId::field_uart2_int_raw_brk_det_int_raw,
  FieldId::field_uart2_int_raw_rxfifo_tout_int_raw,
  FieldId::field_uart2_int_raw_sw_xon_int_raw,
  FieldId::field_uart2_int_raw_sw_xoff_int_raw,
  FieldId::field_uart2_int_raw_glitch_det_int_raw,
  FieldId::field_uart2_int_raw_tx_brk_done_int_raw,
  FieldId::field_uart2_int_raw_tx_brk_idle_done_int_raw,
  FieldId::field_uart2_int_raw_tx_done_int_raw,
  FieldId::field_uart2_int_raw_rs485_parity_err_int_raw,
  FieldId::field_uart2_int_raw_rs485_frm_err_int_raw,
  FieldId::field_uart2_int_raw_rs485_clash_int_raw,
  FieldId::field_uart2_int_raw_at_cmd_char_det_int_raw,
  FieldId::field_uart2_int_st_rxfifo_full_int_st,
  FieldId::field_uart2_int_st_txfifo_empty_int_st,
  FieldId::field_uart2_int_st_parity_err_int_st,
  FieldId::field_uart2_int_st_frm_err_int_st,
  FieldId::field_uart2_int_st_rxfifo_ovf_int_st,
  FieldId::field_uart2_int_st_dsr_chg_int_st,
  FieldId::field_uart2_int_st_cts_chg_int_st,
  FieldId::field_uart2_int_st_brk_det_int_st,
  FieldId::field_uart2_int_st_rxfifo_tout_int_st,
  FieldId::field_uart2_int_st_sw_xon_int_st,
  FieldId::field_uart2_int_st_sw_xoff_int_st,
  FieldId::field_uart2_int_st_glitch_det_int_st,
  FieldId::field_uart2_int_st_tx_brk_done_int_st,
  FieldId::field_uart2_int_st_tx_brk_idle_done_int_st,
  FieldId::field_uart2_int_st_tx_done_int_st,
  FieldId::field_uart2_int_st_rs485_parity_err_int_st,
  FieldId::field_uart2_int_st_rs485_frm_err_int_st,
  FieldId::field_uart2_int_st_rs485_clash_int_st,
  FieldId::field_uart2_int_st_at_cmd_char_det_int_st,
  FieldId::field_uart2_lowpulse_min_cnt,
  FieldId::field_uart2_mem_cnt_status_rx_mem_cnt,
  FieldId::field_uart2_mem_cnt_status_tx_mem_cnt,
  FieldId::field_uart2_mem_conf_mem_pd,
  FieldId::field_uart2_mem_conf_rx_size,
  FieldId::field_uart2_mem_conf_tx_size,
  FieldId::field_uart2_mem_conf_rx_flow_thrhd_h3,
  FieldId::field_uart2_mem_conf_rx_tout_thrhd_h3,
  FieldId::field_uart2_mem_conf_xon_threshold_h2,
  FieldId::field_uart2_mem_conf_xoff_threshold_h2,
  FieldId::field_uart2_mem_conf_rx_mem_full_thrhd,
  FieldId::field_uart2_mem_conf_tx_mem_empty_thrhd,
  FieldId::field_uart2_mem_rx_status_mem_rx_status,
  FieldId::field_uart2_mem_rx_status_mem_rx_rd_addr,
  FieldId::field_uart2_mem_rx_status_mem_rx_wr_addr,
  FieldId::field_uart2_mem_tx_status_mem_tx_status,
  FieldId::field_uart2_negpulse_negedge_min_cnt,
  FieldId::field_uart2_pospulse_posedge_min_cnt,
  FieldId::field_uart2_rs485_conf_rs485_en,
  FieldId::field_uart2_rs485_conf_dl0_en,
  FieldId::field_uart2_rs485_conf_dl1_en,
  FieldId::field_uart2_rs485_conf_rs485tx_rx_en,
  FieldId::field_uart2_rs485_conf_rs485rxby_tx_en,
  FieldId::field_uart2_rs485_conf_rs485_rx_dly_num,
  FieldId::field_uart2_rs485_conf_rs485_tx_dly_num,
  FieldId::field_uart2_rxd_cnt_rxd_edge_cnt,
  FieldId::field_uart2_sleep_conf_active_threshold,
  FieldId::field_uart2_status_rxfifo_cnt,
  FieldId::field_uart2_status_st_urx_out,
  FieldId::field_uart2_status_dsrn,
  FieldId::field_uart2_status_ctsn,
  FieldId::field_uart2_status_rxd,
  FieldId::field_uart2_status_txfifo_cnt,
  FieldId::field_uart2_status_st_utx_out,
  FieldId::field_uart2_status_dtrn,
  FieldId::field_uart2_status_rtsn,
  FieldId::field_uart2_status_txd,
  FieldId::field_uart2_swfc_conf_xon_threshold,
  FieldId::field_uart2_swfc_conf_xoff_threshold,
  FieldId::field_uart2_swfc_conf_xon_char,
  FieldId::field_uart2_swfc_conf_xoff_char,
}};
}
}
}
}
}
}
