#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70n21b {
enum class CapabilityId : std::uint16_t {
  none,
  capability_afec_afec_s_ad0,
  capability_afec_afec_s_ad1,
  capability_afec_afec_s_ad10,
  capability_afec_afec_s_ad2,
  capability_afec_afec_s_ad5,
  capability_afec_afec_s_ad6,
  capability_afec_afec_s_ad7,
  capability_afec_afec_s_ad8,
  capability_afec_afec_s_ad9,
  capability_afec_afec_s_adtrg,
  runtime_support_adc,
  runtime_dma_AFEC0_XDMAC_PERID_35_RX,
  capability_instance_afec0_lqfp100_ad0,
  capability_instance_afec0_lqfp100_ad1,
  capability_instance_afec0_lqfp100_ad10,
  capability_instance_afec0_lqfp100_ad2,
  capability_instance_afec0_lqfp100_ad5,
  capability_instance_afec0_lqfp100_ad6,
  capability_instance_afec0_lqfp100_ad7,
  capability_instance_afec0_lqfp100_ad8,
  capability_instance_afec0_lqfp100_ad9,
  capability_instance_afec0_lqfp100_adtrg,
  runtime_dma_AFEC1_XDMAC_PERID_36_RX,
  capability_instance_afec1_lqfp100_ad0,
  capability_instance_afec1_lqfp100_adtrg,
  capability_mcan_mcan_n_rx,
  capability_mcan_mcan_n_tx,
  runtime_support_can,
  capability_instance_mcan0_lqfp100_rx,
  capability_instance_mcan0_lqfp100_tx,
  capability_instance_mcan1_lqfp100_rx,
  capability_instance_mcan1_lqfp100_tx,
  capability_dacc_dacc_e_dac0,
  capability_dacc_dacc_e_dac1,
  capability_dacc_dacc_e_datrg,
  runtime_support_dac,
  runtime_dma_DACC_XDMAC_PERID_30_CH0_TX,
  runtime_dma_DACC_XDMAC_PERID_31_CH1_TX,
  capability_instance_dacc_lqfp100_dac0,
  capability_instance_dacc_lqfp100_dac1,
  capability_instance_dacc_lqfp100_datrg,
  device_core_count,
  device_multicore_topology,
  runtime_support_dma,
  capability_gmac_gmac_s_gcol,
  capability_gmac_gmac_s_gcrs,
  capability_gmac_gmac_s_gmdc,
  capability_gmac_gmac_s_gmdio,
  capability_gmac_gmac_s_grx0,
  capability_gmac_gmac_s_grx1,
  capability_gmac_gmac_s_grx2,
  capability_gmac_gmac_s_grx3,
  capability_gmac_gmac_s_grxck,
  capability_gmac_gmac_s_grxdv,
  capability_gmac_gmac_s_grxer,
  capability_gmac_gmac_s_gtsucomp,
  capability_gmac_gmac_s_gtx0,
  capability_gmac_gmac_s_gtx1,
  capability_gmac_gmac_s_gtx2,
  capability_gmac_gmac_s_gtx3,
  capability_gmac_gmac_s_gtxck,
  capability_gmac_gmac_s_gtxen,
  capability_gmac_gmac_s_gtxer,
  runtime_support_eth,
  capability_instance_gmac_lqfp100_gcol,
  capability_instance_gmac_lqfp100_gcrs,
  capability_instance_gmac_lqfp100_gmdc,
  capability_instance_gmac_lqfp100_gmdio,
  capability_instance_gmac_lqfp100_grx0,
  capability_instance_gmac_lqfp100_grx1,
  capability_instance_gmac_lqfp100_grx2,
  capability_instance_gmac_lqfp100_grx3,
  capability_instance_gmac_lqfp100_grxck,
  capability_instance_gmac_lqfp100_grxdv,
  capability_instance_gmac_lqfp100_grxer,
  capability_instance_gmac_lqfp100_gtsucomp,
  capability_instance_gmac_lqfp100_gtx0,
  capability_instance_gmac_lqfp100_gtx1,
  capability_instance_gmac_lqfp100_gtx2,
  capability_instance_gmac_lqfp100_gtx3,
  capability_instance_gmac_lqfp100_gtxck,
  capability_instance_gmac_lqfp100_gtxen,
  capability_instance_gmac_lqfp100_gtxer,
  capability_gpio_pio_v_piodc0,
  capability_gpio_pio_v_piodc1,
  capability_gpio_pio_v_piodc2,
  capability_gpio_pio_v_piodc3,
  capability_gpio_pio_v_piodc4,
  capability_gpio_pio_v_piodc5,
  capability_gpio_pio_v_piodc6,
  capability_gpio_pio_v_piodc7,
  capability_gpio_pio_v_piodcclk,
  capability_gpio_pio_v_piodcen1,
  capability_gpio_pio_v_piodcen2,
  runtime_support_gpio,
  runtime_dma_GPIOA_XDMAC_PERID_34_RX,
  capability_instance_gpioa_lqfp100_piodc0,
  capability_instance_gpioa_lqfp100_piodc1,
  capability_instance_gpioa_lqfp100_piodc2,
  capability_instance_gpioa_lqfp100_piodc3,
  capability_instance_gpioa_lqfp100_piodc4,
  capability_instance_gpioa_lqfp100_piodc5,
  capability_instance_gpioa_lqfp100_piodc6,
  capability_instance_gpioa_lqfp100_piodc7,
  capability_instance_gpioa_lqfp100_piodcclk,
  capability_instance_gpioa_lqfp100_piodcen1,
  capability_instance_gpioa_lqfp100_piodcen2,
  capability_twihs_twihs_z_scl,
  capability_twihs_twihs_z_sda,
  runtime_support_i2c,
  runtime_dma_TWIHS0_XDMAC_PERID_15_RX,
  runtime_dma_TWIHS0_XDMAC_PERID_14_TX,
  capability_instance_twihs0_lqfp100_scl,
  capability_instance_twihs0_lqfp100_sda,
  runtime_dma_TWIHS1_XDMAC_PERID_17_RX,
  runtime_dma_TWIHS1_XDMAC_PERID_16_TX,
  capability_instance_twihs1_lqfp100_scl,
  capability_instance_twihs1_lqfp100_sda,
  runtime_dma_TWIHS2_XDMAC_PERID_19_RX,
  runtime_dma_TWIHS2_XDMAC_PERID_18_TX,
  capability_instance_twihs2_lqfp100_scl,
  capability_instance_twihs2_lqfp100_sda,
  capability_pwm_pwm_y_pwmextrg0,
  capability_pwm_pwm_y_pwmextrg1,
  capability_pwm_pwm_y_pwmfi0,
  capability_pwm_pwm_y_pwmfi1,
  capability_pwm_pwm_y_pwmfi2,
  capability_pwm_pwm_y_pwmh0,
  capability_pwm_pwm_y_pwmh1,
  capability_pwm_pwm_y_pwmh2,
  capability_pwm_pwm_y_pwmh3,
  capability_pwm_pwm_y_pwml0,
  capability_pwm_pwm_y_pwml1,
  capability_pwm_pwm_y_pwml2,
  capability_pwm_pwm_y_pwml3,
  runtime_support_pwm,
  runtime_dma_PWM0_XDMAC_PERID_13_TX,
  capability_instance_pwm0_lqfp100_pwmextrg0,
  capability_instance_pwm0_lqfp100_pwmextrg1,
  capability_instance_pwm0_lqfp100_pwmfi0,
  capability_instance_pwm0_lqfp100_pwmfi1,
  capability_instance_pwm0_lqfp100_pwmfi2,
  capability_instance_pwm0_lqfp100_pwmh0,
  capability_instance_pwm0_lqfp100_pwmh1,
  capability_instance_pwm0_lqfp100_pwmh2,
  capability_instance_pwm0_lqfp100_pwmh3,
  capability_instance_pwm0_lqfp100_pwml0,
  capability_instance_pwm0_lqfp100_pwml1,
  capability_instance_pwm0_lqfp100_pwml2,
  capability_instance_pwm0_lqfp100_pwml3,
  runtime_dma_PWM1_XDMAC_PERID_39_TX,
  capability_instance_pwm1_lqfp100_pwmextrg0,
  capability_instance_pwm1_lqfp100_pwmextrg1,
  capability_instance_pwm1_lqfp100_pwmfi0,
  capability_instance_pwm1_lqfp100_pwmfi1,
  capability_instance_pwm1_lqfp100_pwmfi2,
  capability_instance_pwm1_lqfp100_pwmh0,
  capability_instance_pwm1_lqfp100_pwmh1,
  capability_instance_pwm1_lqfp100_pwmh2,
  capability_instance_pwm1_lqfp100_pwmh3,
  capability_instance_pwm1_lqfp100_pwml0,
  capability_instance_pwm1_lqfp100_pwml1,
  capability_instance_pwm1_lqfp100_pwml2,
  capability_instance_pwm1_lqfp100_pwml3,
  capability_qspi_qspi_j_qcs,
  capability_qspi_qspi_j_qio0,
  capability_qspi_qspi_j_qio1,
  capability_qspi_qspi_j_qio2,
  capability_qspi_qspi_j_qio3,
  capability_qspi_qspi_j_qsck,
  runtime_support_qspi,
  runtime_dma_QSPI_XDMAC_PERID_6_RX,
  runtime_dma_QSPI_XDMAC_PERID_5_TX,
  capability_instance_qspi_lqfp100_qcs,
  capability_instance_qspi_lqfp100_qio0,
  capability_instance_qspi_lqfp100_qio1,
  capability_instance_qspi_lqfp100_qio2,
  capability_instance_qspi_lqfp100_qio3,
  capability_instance_qspi_lqfp100_qsck,
  capability_rtc_rtc_zb_rtcout0,
  capability_rtc_rtc_zb_rtcout1,
  runtime_support_rtc,
  capability_instance_rtc_lqfp100_rtcout0,
  capability_instance_rtc_lqfp100_rtcout1,
  capability_hsmci_hsmci_r_mccda,
  capability_hsmci_hsmci_r_mcck,
  capability_hsmci_hsmci_r_mcda0,
  capability_hsmci_hsmci_r_mcda1,
  capability_hsmci_hsmci_r_mcda2,
  capability_hsmci_hsmci_r_mcda3,
  runtime_support_sdmmc,
  runtime_dma_HSMCI_XDMAC_PERID_0_RX,
  capability_instance_hsmci_lqfp100_mccda,
  capability_instance_hsmci_lqfp100_mcck,
  capability_instance_hsmci_lqfp100_mcda0,
  capability_instance_hsmci_lqfp100_mcda1,
  capability_instance_hsmci_lqfp100_mcda2,
  capability_instance_hsmci_lqfp100_mcda3,
  capability_spi_spi_zm_cs,
  capability_spi_spi_zm_miso,
  capability_spi_spi_zm_mosi,
  capability_spi_spi_zm_sck,
  runtime_support_spi,
  runtime_dma_SPI0_XDMAC_PERID_2_RX,
  runtime_dma_SPI0_XDMAC_PERID_1_TX,
  capability_instance_spi0_lqfp100_cs,
  capability_instance_spi0_lqfp100_miso,
  capability_instance_spi0_lqfp100_mosi,
  capability_instance_spi0_lqfp100_sck,
  capability_tc_tc_zl_tclk0,
  capability_tc_tc_zl_tclk1,
  capability_tc_tc_zl_tclk11,
  capability_tc_tc_zl_tioa0,
  capability_tc_tc_zl_tioa1,
  capability_tc_tc_zl_tioa11,
  capability_tc_tc_zl_tioa2,
  capability_tc_tc_zl_tiob0,
  capability_tc_tc_zl_tiob1,
  capability_tc_tc_zl_tiob11,
  capability_tc_tc_zl_tiob2,
  runtime_support_timer,
  runtime_dma_TC0_XDMAC_PERID_40_RX,
  capability_instance_tc0_lqfp100_tclk0,
  capability_instance_tc0_lqfp100_tclk1,
  capability_instance_tc0_lqfp100_tioa0,
  capability_instance_tc0_lqfp100_tioa1,
  capability_instance_tc0_lqfp100_tioa2,
  capability_instance_tc0_lqfp100_tiob0,
  capability_instance_tc0_lqfp100_tiob1,
  capability_instance_tc0_lqfp100_tiob2,
  runtime_dma_TC1_XDMAC_PERID_41_RX,
  runtime_dma_TC2_XDMAC_PERID_42_RX,
  runtime_dma_TC3_XDMAC_PERID_43_RX,
  capability_instance_tc3_lqfp100_tclk11,
  capability_instance_tc3_lqfp100_tioa11,
  capability_instance_tc3_lqfp100_tiob11,
  capability_usart_usart_zw_cts,
  capability_usart_usart_zw_dcd0,
  capability_usart_usart_zw_dcd1,
  capability_usart_usart_zw_dcd2,
  capability_usart_usart_zw_dsr0,
  capability_usart_usart_zw_dsr1,
  capability_usart_usart_zw_dsr2,
  capability_usart_usart_zw_dtr0,
  capability_usart_usart_zw_dtr1,
  capability_usart_usart_zw_dtr2,
  capability_usart_usart_zw_loncol1,
  capability_usart_usart_zw_ri0,
  capability_usart_usart_zw_ri2,
  capability_usart_usart_zw_rts,
  capability_usart_usart_zw_rx,
  capability_usart_usart_zw_sck0,
  capability_usart_usart_zw_sck1,
  capability_usart_usart_zw_sck2,
  capability_usart_usart_zw_tx,
  capability_uart_uart_r_urxd0,
  capability_uart_uart_r_urxd1,
  capability_uart_uart_r_urxd2,
  capability_uart_uart_r_urxd3,
  capability_uart_uart_r_urxd4,
  capability_uart_uart_r_utxd0,
  capability_uart_uart_r_utxd1,
  capability_uart_uart_r_utxd2,
  capability_uart_uart_r_utxd3,
  capability_uart_uart_r_utxd4,
  runtime_support_uart,
  runtime_dma_UART0_XDMAC_PERID_21_RX,
  runtime_dma_UART0_XDMAC_PERID_20_TX,
  capability_instance_uart0_lqfp100_urxd0,
  capability_instance_uart0_lqfp100_utxd0,
  runtime_dma_UART1_XDMAC_PERID_23_RX,
  runtime_dma_UART1_XDMAC_PERID_22_TX,
  capability_instance_uart1_lqfp100_urxd1,
  capability_instance_uart1_lqfp100_utxd1,
  runtime_dma_UART2_XDMAC_PERID_25_RX,
  runtime_dma_UART2_XDMAC_PERID_24_TX,
  capability_instance_uart2_lqfp100_urxd2,
  capability_instance_uart2_lqfp100_utxd2,
  runtime_dma_UART3_XDMAC_PERID_27_RX,
  runtime_dma_UART3_XDMAC_PERID_26_TX,
  capability_instance_uart3_lqfp100_urxd3,
  capability_instance_uart3_lqfp100_utxd3,
  runtime_dma_UART4_XDMAC_PERID_29_RX,
  runtime_dma_UART4_XDMAC_PERID_28_TX,
  capability_instance_uart4_lqfp100_urxd4,
  capability_instance_uart4_lqfp100_utxd4,
  runtime_dma_USART0_XDMAC_PERID_8_RX,
  runtime_dma_USART0_XDMAC_PERID_7_TX,
  capability_instance_usart0_lqfp100_cts,
  capability_instance_usart0_lqfp100_dcd0,
  capability_instance_usart0_lqfp100_dsr0,
  capability_instance_usart0_lqfp100_dtr0,
  capability_instance_usart0_lqfp100_ri0,
  capability_instance_usart0_lqfp100_rts,
  capability_instance_usart0_lqfp100_rx,
  capability_instance_usart0_lqfp100_sck0,
  capability_instance_usart0_lqfp100_tx,
  runtime_dma_USART1_XDMAC_PERID_10_RX,
  runtime_dma_USART1_XDMAC_PERID_9_TX,
  capability_instance_usart1_lqfp100_cts,
  capability_instance_usart1_lqfp100_dcd1,
  capability_instance_usart1_lqfp100_dsr1,
  capability_instance_usart1_lqfp100_dtr1,
  capability_instance_usart1_lqfp100_loncol1,
  capability_instance_usart1_lqfp100_rts,
  capability_instance_usart1_lqfp100_rx,
  capability_instance_usart1_lqfp100_sck1,
  capability_instance_usart1_lqfp100_tx,
  runtime_dma_USART2_XDMAC_PERID_12_RX,
  runtime_dma_USART2_XDMAC_PERID_11_TX,
  capability_instance_usart2_lqfp100_cts,
  capability_instance_usart2_lqfp100_dcd2,
  capability_instance_usart2_lqfp100_dsr2,
  capability_instance_usart2_lqfp100_dtr2,
  capability_instance_usart2_lqfp100_ri2,
  capability_instance_usart2_lqfp100_rts,
  capability_instance_usart2_lqfp100_rx,
  capability_instance_usart2_lqfp100_sck2,
  capability_instance_usart2_lqfp100_tx,
  runtime_support_usb,
  runtime_support_watchdog,
};

enum class CapabilityScopeId : std::uint16_t {
  none,
  device,
  dma_binding,
  instance_overlay,
  ip_block,
  runtime_contract,
};

enum class CapabilityNameId : std::uint16_t {
  none,
  available_signal,
  core_count,
  dma_compatible_signal,
  multicore_topology,
  runtime_supported,
  signal_role,
};

enum class CapabilityValueId : std::uint16_t {
  none,
  _1,
  CH0_TX,
  CH1_TX,
  RX,
  TX,
  ad0,
  ad1,
  ad10,
  ad2,
  ad5,
  ad6,
  ad7,
  ad8,
  ad9,
  adtrg,
  cs,
  cts,
  dac0,
  dac1,
  datrg,
  dcd0,
  dcd1,
  dcd2,
  dsr0,
  dsr1,
  dsr2,
  dtr0,
  dtr1,
  dtr2,
  gcol,
  gcrs,
  gmdc,
  gmdio,
  grx0,
  grx1,
  grx2,
  grx3,
  grxck,
  grxdv,
  grxer,
  gtsucomp,
  gtx0,
  gtx1,
  gtx2,
  gtx3,
  gtxck,
  gtxen,
  gtxer,
  loncol1,
  mccda,
  mcck,
  mcda0,
  mcda1,
  mcda2,
  mcda3,
  miso,
  mosi,
  piodc0,
  piodc1,
  piodc2,
  piodc3,
  piodc4,
  piodc5,
  piodc6,
  piodc7,
  piodcclk,
  piodcen1,
  piodcen2,
  pwmextrg0,
  pwmextrg1,
  pwmfi0,
  pwmfi1,
  pwmfi2,
  pwmh0,
  pwmh1,
  pwmh2,
  pwmh3,
  pwml0,
  pwml1,
  pwml2,
  pwml3,
  qcs,
  qio0,
  qio1,
  qio2,
  qio3,
  qsck,
  ri0,
  ri2,
  rtcout0,
  rtcout1,
  rts,
  rx,
  sck,
  sck0,
  sck1,
  sck2,
  scl,
  sda,
  single_core,
  tclk0,
  tclk1,
  tclk11,
  tioa0,
  tioa1,
  tioa11,
  tioa2,
  tiob0,
  tiob1,
  tiob11,
  tiob2,
  true_value,
  tx,
  urxd0,
  urxd1,
  urxd2,
  urxd3,
  urxd4,
  utxd0,
  utxd1,
  utxd2,
  utxd3,
  utxd4,
};

struct CapabilityDescriptor {
  CapabilityId capability_id;
  CapabilityScopeId scope_id;
  PeripheralClassId peripheral_class_id;
  CapabilityNameId name_id;
  CapabilityValueId value_id;
  PeripheralId peripheral_id;
};
inline constexpr std::array<CapabilityDescriptor, 321> kCapabilities = {{
  {CapabilityId::capability_afec_afec_s_ad0, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad0, PeripheralId::none},
  {CapabilityId::capability_afec_afec_s_ad1, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad1, PeripheralId::none},
  {CapabilityId::capability_afec_afec_s_ad10, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad10, PeripheralId::none},
  {CapabilityId::capability_afec_afec_s_ad2, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad2, PeripheralId::none},
  {CapabilityId::capability_afec_afec_s_ad5, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad5, PeripheralId::none},
  {CapabilityId::capability_afec_afec_s_ad6, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad6, PeripheralId::none},
  {CapabilityId::capability_afec_afec_s_ad7, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad7, PeripheralId::none},
  {CapabilityId::capability_afec_afec_s_ad8, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad8, PeripheralId::none},
  {CapabilityId::capability_afec_afec_s_ad9, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad9, PeripheralId::none},
  {CapabilityId::capability_afec_afec_s_adtrg, CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::adtrg, PeripheralId::none},
  {CapabilityId::runtime_support_adc, CapabilityScopeId::runtime_contract, PeripheralClassId::class_adc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_AFEC0_XDMAC_PERID_35_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_adc, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::AFEC0},
  {CapabilityId::capability_instance_afec0_lqfp100_ad0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad0, PeripheralId::AFEC0},
  {CapabilityId::capability_instance_afec0_lqfp100_ad1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad1, PeripheralId::AFEC0},
  {CapabilityId::capability_instance_afec0_lqfp100_ad10, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad10, PeripheralId::AFEC0},
  {CapabilityId::capability_instance_afec0_lqfp100_ad2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad2, PeripheralId::AFEC0},
  {CapabilityId::capability_instance_afec0_lqfp100_ad5, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad5, PeripheralId::AFEC0},
  {CapabilityId::capability_instance_afec0_lqfp100_ad6, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad6, PeripheralId::AFEC0},
  {CapabilityId::capability_instance_afec0_lqfp100_ad7, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad7, PeripheralId::AFEC0},
  {CapabilityId::capability_instance_afec0_lqfp100_ad8, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad8, PeripheralId::AFEC0},
  {CapabilityId::capability_instance_afec0_lqfp100_ad9, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad9, PeripheralId::AFEC0},
  {CapabilityId::capability_instance_afec0_lqfp100_adtrg, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::adtrg, PeripheralId::AFEC0},
  {CapabilityId::runtime_dma_AFEC1_XDMAC_PERID_36_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_adc, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::AFEC1},
  {CapabilityId::capability_instance_afec1_lqfp100_ad0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad0, PeripheralId::AFEC1},
  {CapabilityId::capability_instance_afec1_lqfp100_adtrg, CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::adtrg, PeripheralId::AFEC1},
  {CapabilityId::capability_mcan_mcan_n_rx, CapabilityScopeId::ip_block, PeripheralClassId::class_can, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityId::capability_mcan_mcan_n_tx, CapabilityScopeId::ip_block, PeripheralClassId::class_can, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityId::runtime_support_can, CapabilityScopeId::runtime_contract, PeripheralClassId::class_can, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_instance_mcan0_lqfp100_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_can, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::MCAN0},
  {CapabilityId::capability_instance_mcan0_lqfp100_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_can, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::MCAN0},
  {CapabilityId::capability_instance_mcan1_lqfp100_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_can, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::MCAN1},
  {CapabilityId::capability_instance_mcan1_lqfp100_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_can, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::MCAN1},
  {CapabilityId::capability_dacc_dacc_e_dac0, CapabilityScopeId::ip_block, PeripheralClassId::class_dac, CapabilityNameId::signal_role, CapabilityValueId::dac0, PeripheralId::none},
  {CapabilityId::capability_dacc_dacc_e_dac1, CapabilityScopeId::ip_block, PeripheralClassId::class_dac, CapabilityNameId::signal_role, CapabilityValueId::dac1, PeripheralId::none},
  {CapabilityId::capability_dacc_dacc_e_datrg, CapabilityScopeId::ip_block, PeripheralClassId::class_dac, CapabilityNameId::signal_role, CapabilityValueId::datrg, PeripheralId::none},
  {CapabilityId::runtime_support_dac, CapabilityScopeId::runtime_contract, PeripheralClassId::class_dac, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_DACC_XDMAC_PERID_30_CH0_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_dac, CapabilityNameId::dma_compatible_signal, CapabilityValueId::CH0_TX, PeripheralId::DACC},
  {CapabilityId::runtime_dma_DACC_XDMAC_PERID_31_CH1_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_dac, CapabilityNameId::dma_compatible_signal, CapabilityValueId::CH1_TX, PeripheralId::DACC},
  {CapabilityId::capability_instance_dacc_lqfp100_dac0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_dac, CapabilityNameId::available_signal, CapabilityValueId::dac0, PeripheralId::DACC},
  {CapabilityId::capability_instance_dacc_lqfp100_dac1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_dac, CapabilityNameId::available_signal, CapabilityValueId::dac1, PeripheralId::DACC},
  {CapabilityId::capability_instance_dacc_lqfp100_datrg, CapabilityScopeId::instance_overlay, PeripheralClassId::class_dac, CapabilityNameId::available_signal, CapabilityValueId::datrg, PeripheralId::DACC},
  {CapabilityId::device_core_count, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::core_count, CapabilityValueId::_1, PeripheralId::none},
  {CapabilityId::device_multicore_topology, CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::multicore_topology, CapabilityValueId::single_core, PeripheralId::none},
  {CapabilityId::runtime_support_dma, CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_gcol, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gcol, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_gcrs, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gcrs, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_gmdc, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gmdc, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_gmdio, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gmdio, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_grx0, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::grx0, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_grx1, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::grx1, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_grx2, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::grx2, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_grx3, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::grx3, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_grxck, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::grxck, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_grxdv, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::grxdv, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_grxer, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::grxer, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_gtsucomp, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtsucomp, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_gtx0, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtx0, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_gtx1, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtx1, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_gtx2, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtx2, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_gtx3, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtx3, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_gtxck, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtxck, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_gtxen, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtxen, PeripheralId::none},
  {CapabilityId::capability_gmac_gmac_s_gtxer, CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtxer, PeripheralId::none},
  {CapabilityId::runtime_support_eth, CapabilityScopeId::runtime_contract, PeripheralClassId::class_eth, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_instance_gmac_lqfp100_gcol, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gcol, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_gcrs, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gcrs, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_gmdc, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gmdc, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_gmdio, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gmdio, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_grx0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::grx0, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_grx1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::grx1, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_grx2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::grx2, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_grx3, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::grx3, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_grxck, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::grxck, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_grxdv, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::grxdv, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_grxer, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::grxer, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_gtsucomp, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtsucomp, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_gtx0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtx0, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_gtx1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtx1, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_gtx2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtx2, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_gtx3, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtx3, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_gtxck, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtxck, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_gtxen, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtxen, PeripheralId::GMAC},
  {CapabilityId::capability_instance_gmac_lqfp100_gtxer, CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtxer, PeripheralId::GMAC},
  {CapabilityId::capability_gpio_pio_v_piodc0, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc0, PeripheralId::none},
  {CapabilityId::capability_gpio_pio_v_piodc1, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc1, PeripheralId::none},
  {CapabilityId::capability_gpio_pio_v_piodc2, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc2, PeripheralId::none},
  {CapabilityId::capability_gpio_pio_v_piodc3, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc3, PeripheralId::none},
  {CapabilityId::capability_gpio_pio_v_piodc4, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc4, PeripheralId::none},
  {CapabilityId::capability_gpio_pio_v_piodc5, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc5, PeripheralId::none},
  {CapabilityId::capability_gpio_pio_v_piodc6, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc6, PeripheralId::none},
  {CapabilityId::capability_gpio_pio_v_piodc7, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc7, PeripheralId::none},
  {CapabilityId::capability_gpio_pio_v_piodcclk, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodcclk, PeripheralId::none},
  {CapabilityId::capability_gpio_pio_v_piodcen1, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodcen1, PeripheralId::none},
  {CapabilityId::capability_gpio_pio_v_piodcen2, CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodcen2, PeripheralId::none},
  {CapabilityId::runtime_support_gpio, CapabilityScopeId::runtime_contract, PeripheralClassId::class_gpio, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_GPIOA_XDMAC_PERID_34_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_gpio, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::GPIOA},
  {CapabilityId::capability_instance_gpioa_lqfp100_piodc0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc0, PeripheralId::GPIOA},
  {CapabilityId::capability_instance_gpioa_lqfp100_piodc1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc1, PeripheralId::GPIOA},
  {CapabilityId::capability_instance_gpioa_lqfp100_piodc2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc2, PeripheralId::GPIOA},
  {CapabilityId::capability_instance_gpioa_lqfp100_piodc3, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc3, PeripheralId::GPIOA},
  {CapabilityId::capability_instance_gpioa_lqfp100_piodc4, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc4, PeripheralId::GPIOA},
  {CapabilityId::capability_instance_gpioa_lqfp100_piodc5, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc5, PeripheralId::GPIOA},
  {CapabilityId::capability_instance_gpioa_lqfp100_piodc6, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc6, PeripheralId::GPIOA},
  {CapabilityId::capability_instance_gpioa_lqfp100_piodc7, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc7, PeripheralId::GPIOA},
  {CapabilityId::capability_instance_gpioa_lqfp100_piodcclk, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodcclk, PeripheralId::GPIOA},
  {CapabilityId::capability_instance_gpioa_lqfp100_piodcen1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodcen1, PeripheralId::GPIOA},
  {CapabilityId::capability_instance_gpioa_lqfp100_piodcen2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodcen2, PeripheralId::GPIOA},
  {CapabilityId::capability_twihs_twihs_z_scl, CapabilityScopeId::ip_block, PeripheralClassId::class_i2c, CapabilityNameId::signal_role, CapabilityValueId::scl, PeripheralId::none},
  {CapabilityId::capability_twihs_twihs_z_sda, CapabilityScopeId::ip_block, PeripheralClassId::class_i2c, CapabilityNameId::signal_role, CapabilityValueId::sda, PeripheralId::none},
  {CapabilityId::runtime_support_i2c, CapabilityScopeId::runtime_contract, PeripheralClassId::class_i2c, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_TWIHS0_XDMAC_PERID_15_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_i2c, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::TWIHS0},
  {CapabilityId::runtime_dma_TWIHS0_XDMAC_PERID_14_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_i2c, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::TWIHS0},
  {CapabilityId::capability_instance_twihs0_lqfp100_scl, CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::scl, PeripheralId::TWIHS0},
  {CapabilityId::capability_instance_twihs0_lqfp100_sda, CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::sda, PeripheralId::TWIHS0},
  {CapabilityId::runtime_dma_TWIHS1_XDMAC_PERID_17_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_i2c, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::TWIHS1},
  {CapabilityId::runtime_dma_TWIHS1_XDMAC_PERID_16_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_i2c, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::TWIHS1},
  {CapabilityId::capability_instance_twihs1_lqfp100_scl, CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::scl, PeripheralId::TWIHS1},
  {CapabilityId::capability_instance_twihs1_lqfp100_sda, CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::sda, PeripheralId::TWIHS1},
  {CapabilityId::runtime_dma_TWIHS2_XDMAC_PERID_19_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_i2c, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::TWIHS2},
  {CapabilityId::runtime_dma_TWIHS2_XDMAC_PERID_18_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_i2c, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::TWIHS2},
  {CapabilityId::capability_instance_twihs2_lqfp100_scl, CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::scl, PeripheralId::TWIHS2},
  {CapabilityId::capability_instance_twihs2_lqfp100_sda, CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::sda, PeripheralId::TWIHS2},
  {CapabilityId::capability_pwm_pwm_y_pwmextrg0, CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmextrg0, PeripheralId::none},
  {CapabilityId::capability_pwm_pwm_y_pwmextrg1, CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmextrg1, PeripheralId::none},
  {CapabilityId::capability_pwm_pwm_y_pwmfi0, CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmfi0, PeripheralId::none},
  {CapabilityId::capability_pwm_pwm_y_pwmfi1, CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmfi1, PeripheralId::none},
  {CapabilityId::capability_pwm_pwm_y_pwmfi2, CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmfi2, PeripheralId::none},
  {CapabilityId::capability_pwm_pwm_y_pwmh0, CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmh0, PeripheralId::none},
  {CapabilityId::capability_pwm_pwm_y_pwmh1, CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmh1, PeripheralId::none},
  {CapabilityId::capability_pwm_pwm_y_pwmh2, CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmh2, PeripheralId::none},
  {CapabilityId::capability_pwm_pwm_y_pwmh3, CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmh3, PeripheralId::none},
  {CapabilityId::capability_pwm_pwm_y_pwml0, CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwml0, PeripheralId::none},
  {CapabilityId::capability_pwm_pwm_y_pwml1, CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwml1, PeripheralId::none},
  {CapabilityId::capability_pwm_pwm_y_pwml2, CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwml2, PeripheralId::none},
  {CapabilityId::capability_pwm_pwm_y_pwml3, CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwml3, PeripheralId::none},
  {CapabilityId::runtime_support_pwm, CapabilityScopeId::runtime_contract, PeripheralClassId::class_pwm, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_PWM0_XDMAC_PERID_13_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_pwm, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::PWM0},
  {CapabilityId::capability_instance_pwm0_lqfp100_pwmextrg0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmextrg0, PeripheralId::PWM0},
  {CapabilityId::capability_instance_pwm0_lqfp100_pwmextrg1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmextrg1, PeripheralId::PWM0},
  {CapabilityId::capability_instance_pwm0_lqfp100_pwmfi0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmfi0, PeripheralId::PWM0},
  {CapabilityId::capability_instance_pwm0_lqfp100_pwmfi1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmfi1, PeripheralId::PWM0},
  {CapabilityId::capability_instance_pwm0_lqfp100_pwmfi2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmfi2, PeripheralId::PWM0},
  {CapabilityId::capability_instance_pwm0_lqfp100_pwmh0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh0, PeripheralId::PWM0},
  {CapabilityId::capability_instance_pwm0_lqfp100_pwmh1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh1, PeripheralId::PWM0},
  {CapabilityId::capability_instance_pwm0_lqfp100_pwmh2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh2, PeripheralId::PWM0},
  {CapabilityId::capability_instance_pwm0_lqfp100_pwmh3, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh3, PeripheralId::PWM0},
  {CapabilityId::capability_instance_pwm0_lqfp100_pwml0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml0, PeripheralId::PWM0},
  {CapabilityId::capability_instance_pwm0_lqfp100_pwml1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml1, PeripheralId::PWM0},
  {CapabilityId::capability_instance_pwm0_lqfp100_pwml2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml2, PeripheralId::PWM0},
  {CapabilityId::capability_instance_pwm0_lqfp100_pwml3, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml3, PeripheralId::PWM0},
  {CapabilityId::runtime_dma_PWM1_XDMAC_PERID_39_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_pwm, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::PWM1},
  {CapabilityId::capability_instance_pwm1_lqfp100_pwmextrg0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmextrg0, PeripheralId::PWM1},
  {CapabilityId::capability_instance_pwm1_lqfp100_pwmextrg1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmextrg1, PeripheralId::PWM1},
  {CapabilityId::capability_instance_pwm1_lqfp100_pwmfi0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmfi0, PeripheralId::PWM1},
  {CapabilityId::capability_instance_pwm1_lqfp100_pwmfi1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmfi1, PeripheralId::PWM1},
  {CapabilityId::capability_instance_pwm1_lqfp100_pwmfi2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmfi2, PeripheralId::PWM1},
  {CapabilityId::capability_instance_pwm1_lqfp100_pwmh0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh0, PeripheralId::PWM1},
  {CapabilityId::capability_instance_pwm1_lqfp100_pwmh1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh1, PeripheralId::PWM1},
  {CapabilityId::capability_instance_pwm1_lqfp100_pwmh2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh2, PeripheralId::PWM1},
  {CapabilityId::capability_instance_pwm1_lqfp100_pwmh3, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh3, PeripheralId::PWM1},
  {CapabilityId::capability_instance_pwm1_lqfp100_pwml0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml0, PeripheralId::PWM1},
  {CapabilityId::capability_instance_pwm1_lqfp100_pwml1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml1, PeripheralId::PWM1},
  {CapabilityId::capability_instance_pwm1_lqfp100_pwml2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml2, PeripheralId::PWM1},
  {CapabilityId::capability_instance_pwm1_lqfp100_pwml3, CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml3, PeripheralId::PWM1},
  {CapabilityId::capability_qspi_qspi_j_qcs, CapabilityScopeId::ip_block, PeripheralClassId::class_qspi, CapabilityNameId::signal_role, CapabilityValueId::qcs, PeripheralId::none},
  {CapabilityId::capability_qspi_qspi_j_qio0, CapabilityScopeId::ip_block, PeripheralClassId::class_qspi, CapabilityNameId::signal_role, CapabilityValueId::qio0, PeripheralId::none},
  {CapabilityId::capability_qspi_qspi_j_qio1, CapabilityScopeId::ip_block, PeripheralClassId::class_qspi, CapabilityNameId::signal_role, CapabilityValueId::qio1, PeripheralId::none},
  {CapabilityId::capability_qspi_qspi_j_qio2, CapabilityScopeId::ip_block, PeripheralClassId::class_qspi, CapabilityNameId::signal_role, CapabilityValueId::qio2, PeripheralId::none},
  {CapabilityId::capability_qspi_qspi_j_qio3, CapabilityScopeId::ip_block, PeripheralClassId::class_qspi, CapabilityNameId::signal_role, CapabilityValueId::qio3, PeripheralId::none},
  {CapabilityId::capability_qspi_qspi_j_qsck, CapabilityScopeId::ip_block, PeripheralClassId::class_qspi, CapabilityNameId::signal_role, CapabilityValueId::qsck, PeripheralId::none},
  {CapabilityId::runtime_support_qspi, CapabilityScopeId::runtime_contract, PeripheralClassId::class_qspi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_QSPI_XDMAC_PERID_6_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_qspi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::QSPI},
  {CapabilityId::runtime_dma_QSPI_XDMAC_PERID_5_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_qspi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::QSPI},
  {CapabilityId::capability_instance_qspi_lqfp100_qcs, CapabilityScopeId::instance_overlay, PeripheralClassId::class_qspi, CapabilityNameId::available_signal, CapabilityValueId::qcs, PeripheralId::QSPI},
  {CapabilityId::capability_instance_qspi_lqfp100_qio0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_qspi, CapabilityNameId::available_signal, CapabilityValueId::qio0, PeripheralId::QSPI},
  {CapabilityId::capability_instance_qspi_lqfp100_qio1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_qspi, CapabilityNameId::available_signal, CapabilityValueId::qio1, PeripheralId::QSPI},
  {CapabilityId::capability_instance_qspi_lqfp100_qio2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_qspi, CapabilityNameId::available_signal, CapabilityValueId::qio2, PeripheralId::QSPI},
  {CapabilityId::capability_instance_qspi_lqfp100_qio3, CapabilityScopeId::instance_overlay, PeripheralClassId::class_qspi, CapabilityNameId::available_signal, CapabilityValueId::qio3, PeripheralId::QSPI},
  {CapabilityId::capability_instance_qspi_lqfp100_qsck, CapabilityScopeId::instance_overlay, PeripheralClassId::class_qspi, CapabilityNameId::available_signal, CapabilityValueId::qsck, PeripheralId::QSPI},
  {CapabilityId::capability_rtc_rtc_zb_rtcout0, CapabilityScopeId::ip_block, PeripheralClassId::class_rtc, CapabilityNameId::signal_role, CapabilityValueId::rtcout0, PeripheralId::none},
  {CapabilityId::capability_rtc_rtc_zb_rtcout1, CapabilityScopeId::ip_block, PeripheralClassId::class_rtc, CapabilityNameId::signal_role, CapabilityValueId::rtcout1, PeripheralId::none},
  {CapabilityId::runtime_support_rtc, CapabilityScopeId::runtime_contract, PeripheralClassId::class_rtc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::capability_instance_rtc_lqfp100_rtcout0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_rtc, CapabilityNameId::available_signal, CapabilityValueId::rtcout0, PeripheralId::RTC},
  {CapabilityId::capability_instance_rtc_lqfp100_rtcout1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_rtc, CapabilityNameId::available_signal, CapabilityValueId::rtcout1, PeripheralId::RTC},
  {CapabilityId::capability_hsmci_hsmci_r_mccda, CapabilityScopeId::ip_block, PeripheralClassId::class_sdmmc, CapabilityNameId::signal_role, CapabilityValueId::mccda, PeripheralId::none},
  {CapabilityId::capability_hsmci_hsmci_r_mcck, CapabilityScopeId::ip_block, PeripheralClassId::class_sdmmc, CapabilityNameId::signal_role, CapabilityValueId::mcck, PeripheralId::none},
  {CapabilityId::capability_hsmci_hsmci_r_mcda0, CapabilityScopeId::ip_block, PeripheralClassId::class_sdmmc, CapabilityNameId::signal_role, CapabilityValueId::mcda0, PeripheralId::none},
  {CapabilityId::capability_hsmci_hsmci_r_mcda1, CapabilityScopeId::ip_block, PeripheralClassId::class_sdmmc, CapabilityNameId::signal_role, CapabilityValueId::mcda1, PeripheralId::none},
  {CapabilityId::capability_hsmci_hsmci_r_mcda2, CapabilityScopeId::ip_block, PeripheralClassId::class_sdmmc, CapabilityNameId::signal_role, CapabilityValueId::mcda2, PeripheralId::none},
  {CapabilityId::capability_hsmci_hsmci_r_mcda3, CapabilityScopeId::ip_block, PeripheralClassId::class_sdmmc, CapabilityNameId::signal_role, CapabilityValueId::mcda3, PeripheralId::none},
  {CapabilityId::runtime_support_sdmmc, CapabilityScopeId::runtime_contract, PeripheralClassId::class_sdmmc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_HSMCI_XDMAC_PERID_0_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_sdmmc, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::HSMCI},
  {CapabilityId::capability_instance_hsmci_lqfp100_mccda, CapabilityScopeId::instance_overlay, PeripheralClassId::class_sdmmc, CapabilityNameId::available_signal, CapabilityValueId::mccda, PeripheralId::HSMCI},
  {CapabilityId::capability_instance_hsmci_lqfp100_mcck, CapabilityScopeId::instance_overlay, PeripheralClassId::class_sdmmc, CapabilityNameId::available_signal, CapabilityValueId::mcck, PeripheralId::HSMCI},
  {CapabilityId::capability_instance_hsmci_lqfp100_mcda0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_sdmmc, CapabilityNameId::available_signal, CapabilityValueId::mcda0, PeripheralId::HSMCI},
  {CapabilityId::capability_instance_hsmci_lqfp100_mcda1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_sdmmc, CapabilityNameId::available_signal, CapabilityValueId::mcda1, PeripheralId::HSMCI},
  {CapabilityId::capability_instance_hsmci_lqfp100_mcda2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_sdmmc, CapabilityNameId::available_signal, CapabilityValueId::mcda2, PeripheralId::HSMCI},
  {CapabilityId::capability_instance_hsmci_lqfp100_mcda3, CapabilityScopeId::instance_overlay, PeripheralClassId::class_sdmmc, CapabilityNameId::available_signal, CapabilityValueId::mcda3, PeripheralId::HSMCI},
  {CapabilityId::capability_spi_spi_zm_cs, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::cs, PeripheralId::none},
  {CapabilityId::capability_spi_spi_zm_miso, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::miso, PeripheralId::none},
  {CapabilityId::capability_spi_spi_zm_mosi, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::mosi, PeripheralId::none},
  {CapabilityId::capability_spi_spi_zm_sck, CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::sck, PeripheralId::none},
  {CapabilityId::runtime_support_spi, CapabilityScopeId::runtime_contract, PeripheralClassId::class_spi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_SPI0_XDMAC_PERID_2_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::SPI0},
  {CapabilityId::runtime_dma_SPI0_XDMAC_PERID_1_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::SPI0},
  {CapabilityId::capability_instance_spi0_lqfp100_cs, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::cs, PeripheralId::SPI0},
  {CapabilityId::capability_instance_spi0_lqfp100_miso, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::miso, PeripheralId::SPI0},
  {CapabilityId::capability_instance_spi0_lqfp100_mosi, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::mosi, PeripheralId::SPI0},
  {CapabilityId::capability_instance_spi0_lqfp100_sck, CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::sck, PeripheralId::SPI0},
  {CapabilityId::capability_tc_tc_zl_tclk0, CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tclk0, PeripheralId::none},
  {CapabilityId::capability_tc_tc_zl_tclk1, CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tclk1, PeripheralId::none},
  {CapabilityId::capability_tc_tc_zl_tclk11, CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tclk11, PeripheralId::none},
  {CapabilityId::capability_tc_tc_zl_tioa0, CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tioa0, PeripheralId::none},
  {CapabilityId::capability_tc_tc_zl_tioa1, CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tioa1, PeripheralId::none},
  {CapabilityId::capability_tc_tc_zl_tioa11, CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tioa11, PeripheralId::none},
  {CapabilityId::capability_tc_tc_zl_tioa2, CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tioa2, PeripheralId::none},
  {CapabilityId::capability_tc_tc_zl_tiob0, CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tiob0, PeripheralId::none},
  {CapabilityId::capability_tc_tc_zl_tiob1, CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tiob1, PeripheralId::none},
  {CapabilityId::capability_tc_tc_zl_tiob11, CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tiob11, PeripheralId::none},
  {CapabilityId::capability_tc_tc_zl_tiob2, CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tiob2, PeripheralId::none},
  {CapabilityId::runtime_support_timer, CapabilityScopeId::runtime_contract, PeripheralClassId::class_timer, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_TC0_XDMAC_PERID_40_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_timer, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::TC0},
  {CapabilityId::capability_instance_tc0_lqfp100_tclk0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tclk0, PeripheralId::TC0},
  {CapabilityId::capability_instance_tc0_lqfp100_tclk1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tclk1, PeripheralId::TC0},
  {CapabilityId::capability_instance_tc0_lqfp100_tioa0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tioa0, PeripheralId::TC0},
  {CapabilityId::capability_instance_tc0_lqfp100_tioa1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tioa1, PeripheralId::TC0},
  {CapabilityId::capability_instance_tc0_lqfp100_tioa2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tioa2, PeripheralId::TC0},
  {CapabilityId::capability_instance_tc0_lqfp100_tiob0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tiob0, PeripheralId::TC0},
  {CapabilityId::capability_instance_tc0_lqfp100_tiob1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tiob1, PeripheralId::TC0},
  {CapabilityId::capability_instance_tc0_lqfp100_tiob2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tiob2, PeripheralId::TC0},
  {CapabilityId::runtime_dma_TC1_XDMAC_PERID_41_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_timer, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::TC1},
  {CapabilityId::runtime_dma_TC2_XDMAC_PERID_42_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_timer, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::TC2},
  {CapabilityId::runtime_dma_TC3_XDMAC_PERID_43_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_timer, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::TC3},
  {CapabilityId::capability_instance_tc3_lqfp100_tclk11, CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tclk11, PeripheralId::TC3},
  {CapabilityId::capability_instance_tc3_lqfp100_tioa11, CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tioa11, PeripheralId::TC3},
  {CapabilityId::capability_instance_tc3_lqfp100_tiob11, CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tiob11, PeripheralId::TC3},
  {CapabilityId::capability_usart_usart_zw_cts, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::cts, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_dcd0, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dcd0, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_dcd1, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dcd1, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_dcd2, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dcd2, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_dsr0, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dsr0, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_dsr1, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dsr1, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_dsr2, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dsr2, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_dtr0, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dtr0, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_dtr1, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dtr1, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_dtr2, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dtr2, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_loncol1, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::loncol1, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_ri0, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::ri0, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_ri2, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::ri2, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_rts, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rts, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_rx, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_sck0, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::sck0, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_sck1, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::sck1, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_sck2, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::sck2, PeripheralId::none},
  {CapabilityId::capability_usart_usart_zw_tx, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityId::capability_uart_uart_r_urxd0, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::urxd0, PeripheralId::none},
  {CapabilityId::capability_uart_uart_r_urxd1, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::urxd1, PeripheralId::none},
  {CapabilityId::capability_uart_uart_r_urxd2, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::urxd2, PeripheralId::none},
  {CapabilityId::capability_uart_uart_r_urxd3, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::urxd3, PeripheralId::none},
  {CapabilityId::capability_uart_uart_r_urxd4, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::urxd4, PeripheralId::none},
  {CapabilityId::capability_uart_uart_r_utxd0, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::utxd0, PeripheralId::none},
  {CapabilityId::capability_uart_uart_r_utxd1, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::utxd1, PeripheralId::none},
  {CapabilityId::capability_uart_uart_r_utxd2, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::utxd2, PeripheralId::none},
  {CapabilityId::capability_uart_uart_r_utxd3, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::utxd3, PeripheralId::none},
  {CapabilityId::capability_uart_uart_r_utxd4, CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::utxd4, PeripheralId::none},
  {CapabilityId::runtime_support_uart, CapabilityScopeId::runtime_contract, PeripheralClassId::class_uart, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_dma_UART0_XDMAC_PERID_21_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART0},
  {CapabilityId::runtime_dma_UART0_XDMAC_PERID_20_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART0},
  {CapabilityId::capability_instance_uart0_lqfp100_urxd0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::urxd0, PeripheralId::UART0},
  {CapabilityId::capability_instance_uart0_lqfp100_utxd0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::utxd0, PeripheralId::UART0},
  {CapabilityId::runtime_dma_UART1_XDMAC_PERID_23_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART1},
  {CapabilityId::runtime_dma_UART1_XDMAC_PERID_22_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART1},
  {CapabilityId::capability_instance_uart1_lqfp100_urxd1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::urxd1, PeripheralId::UART1},
  {CapabilityId::capability_instance_uart1_lqfp100_utxd1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::utxd1, PeripheralId::UART1},
  {CapabilityId::runtime_dma_UART2_XDMAC_PERID_25_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART2},
  {CapabilityId::runtime_dma_UART2_XDMAC_PERID_24_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART2},
  {CapabilityId::capability_instance_uart2_lqfp100_urxd2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::urxd2, PeripheralId::UART2},
  {CapabilityId::capability_instance_uart2_lqfp100_utxd2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::utxd2, PeripheralId::UART2},
  {CapabilityId::runtime_dma_UART3_XDMAC_PERID_27_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART3},
  {CapabilityId::runtime_dma_UART3_XDMAC_PERID_26_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART3},
  {CapabilityId::capability_instance_uart3_lqfp100_urxd3, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::urxd3, PeripheralId::UART3},
  {CapabilityId::capability_instance_uart3_lqfp100_utxd3, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::utxd3, PeripheralId::UART3},
  {CapabilityId::runtime_dma_UART4_XDMAC_PERID_29_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART4},
  {CapabilityId::runtime_dma_UART4_XDMAC_PERID_28_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART4},
  {CapabilityId::capability_instance_uart4_lqfp100_urxd4, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::urxd4, PeripheralId::UART4},
  {CapabilityId::capability_instance_uart4_lqfp100_utxd4, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::utxd4, PeripheralId::UART4},
  {CapabilityId::runtime_dma_USART0_XDMAC_PERID_8_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::USART0},
  {CapabilityId::runtime_dma_USART0_XDMAC_PERID_7_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::USART0},
  {CapabilityId::capability_instance_usart0_lqfp100_cts, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::cts, PeripheralId::USART0},
  {CapabilityId::capability_instance_usart0_lqfp100_dcd0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dcd0, PeripheralId::USART0},
  {CapabilityId::capability_instance_usart0_lqfp100_dsr0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dsr0, PeripheralId::USART0},
  {CapabilityId::capability_instance_usart0_lqfp100_dtr0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dtr0, PeripheralId::USART0},
  {CapabilityId::capability_instance_usart0_lqfp100_ri0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::ri0, PeripheralId::USART0},
  {CapabilityId::capability_instance_usart0_lqfp100_rts, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rts, PeripheralId::USART0},
  {CapabilityId::capability_instance_usart0_lqfp100_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::USART0},
  {CapabilityId::capability_instance_usart0_lqfp100_sck0, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::sck0, PeripheralId::USART0},
  {CapabilityId::capability_instance_usart0_lqfp100_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::USART0},
  {CapabilityId::runtime_dma_USART1_XDMAC_PERID_10_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::USART1},
  {CapabilityId::runtime_dma_USART1_XDMAC_PERID_9_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::USART1},
  {CapabilityId::capability_instance_usart1_lqfp100_cts, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::cts, PeripheralId::USART1},
  {CapabilityId::capability_instance_usart1_lqfp100_dcd1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dcd1, PeripheralId::USART1},
  {CapabilityId::capability_instance_usart1_lqfp100_dsr1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dsr1, PeripheralId::USART1},
  {CapabilityId::capability_instance_usart1_lqfp100_dtr1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dtr1, PeripheralId::USART1},
  {CapabilityId::capability_instance_usart1_lqfp100_loncol1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::loncol1, PeripheralId::USART1},
  {CapabilityId::capability_instance_usart1_lqfp100_rts, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rts, PeripheralId::USART1},
  {CapabilityId::capability_instance_usart1_lqfp100_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::USART1},
  {CapabilityId::capability_instance_usart1_lqfp100_sck1, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::sck1, PeripheralId::USART1},
  {CapabilityId::capability_instance_usart1_lqfp100_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::USART1},
  {CapabilityId::runtime_dma_USART2_XDMAC_PERID_12_RX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::USART2},
  {CapabilityId::runtime_dma_USART2_XDMAC_PERID_11_TX, CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::USART2},
  {CapabilityId::capability_instance_usart2_lqfp100_cts, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::cts, PeripheralId::USART2},
  {CapabilityId::capability_instance_usart2_lqfp100_dcd2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dcd2, PeripheralId::USART2},
  {CapabilityId::capability_instance_usart2_lqfp100_dsr2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dsr2, PeripheralId::USART2},
  {CapabilityId::capability_instance_usart2_lqfp100_dtr2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dtr2, PeripheralId::USART2},
  {CapabilityId::capability_instance_usart2_lqfp100_ri2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::ri2, PeripheralId::USART2},
  {CapabilityId::capability_instance_usart2_lqfp100_rts, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rts, PeripheralId::USART2},
  {CapabilityId::capability_instance_usart2_lqfp100_rx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::USART2},
  {CapabilityId::capability_instance_usart2_lqfp100_sck2, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::sck2, PeripheralId::USART2},
  {CapabilityId::capability_instance_usart2_lqfp100_tx, CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::USART2},
  {CapabilityId::runtime_support_usb, CapabilityScopeId::runtime_contract, PeripheralClassId::class_usb, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityId::runtime_support_watchdog, CapabilityScopeId::runtime_contract, PeripheralClassId::class_watchdog, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
}};

template<CapabilityId Id>
struct CapabilityTraits {
  static constexpr bool kPresent = false;
  static constexpr CapabilityScopeId kScopeId = CapabilityScopeId::none;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::none;
  static constexpr CapabilityNameId kNameId = CapabilityNameId::none;
  static constexpr CapabilityValueId kValueId = CapabilityValueId::none;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
};

struct CapabilityHardwareLut {
  CapabilityScopeId scope_id;
  PeripheralClassId peripheral_class_id;
  CapabilityNameId name_id;
  CapabilityValueId value_id;
  PeripheralId peripheral_id;
};

inline constexpr std::array<CapabilityHardwareLut, 321> kCapabilityHardwareLut = {{
  {CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad10, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad5, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad6, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad7, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad8, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::ad9, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_adc, CapabilityNameId::signal_role, CapabilityValueId::adtrg, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_adc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_adc, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::AFEC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad0, PeripheralId::AFEC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad1, PeripheralId::AFEC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad10, PeripheralId::AFEC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad2, PeripheralId::AFEC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad5, PeripheralId::AFEC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad6, PeripheralId::AFEC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad7, PeripheralId::AFEC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad8, PeripheralId::AFEC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad9, PeripheralId::AFEC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::adtrg, PeripheralId::AFEC0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_adc, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::AFEC1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::ad0, PeripheralId::AFEC1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_adc, CapabilityNameId::available_signal, CapabilityValueId::adtrg, PeripheralId::AFEC1},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_can, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_can, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_can, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_can, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::MCAN0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_can, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::MCAN0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_can, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::MCAN1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_can, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::MCAN1},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_dac, CapabilityNameId::signal_role, CapabilityValueId::dac0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_dac, CapabilityNameId::signal_role, CapabilityValueId::dac1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_dac, CapabilityNameId::signal_role, CapabilityValueId::datrg, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_dac, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_dac, CapabilityNameId::dma_compatible_signal, CapabilityValueId::CH0_TX, PeripheralId::DACC},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_dac, CapabilityNameId::dma_compatible_signal, CapabilityValueId::CH1_TX, PeripheralId::DACC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_dac, CapabilityNameId::available_signal, CapabilityValueId::dac0, PeripheralId::DACC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_dac, CapabilityNameId::available_signal, CapabilityValueId::dac1, PeripheralId::DACC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_dac, CapabilityNameId::available_signal, CapabilityValueId::datrg, PeripheralId::DACC},
  {CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::core_count, CapabilityValueId::_1, PeripheralId::none},
  {CapabilityScopeId::device, PeripheralClassId::class_device, CapabilityNameId::multicore_topology, CapabilityValueId::single_core, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_dma, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gcol, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gcrs, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gmdc, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gmdio, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::grx0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::grx1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::grx2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::grx3, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::grxck, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::grxdv, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::grxer, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtsucomp, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtx0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtx1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtx2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtx3, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtxck, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtxen, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_eth, CapabilityNameId::signal_role, CapabilityValueId::gtxer, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_eth, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gcol, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gcrs, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gmdc, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gmdio, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::grx0, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::grx1, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::grx2, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::grx3, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::grxck, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::grxdv, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::grxer, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtsucomp, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtx0, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtx1, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtx2, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtx3, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtxck, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtxen, PeripheralId::GMAC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_eth, CapabilityNameId::available_signal, CapabilityValueId::gtxer, PeripheralId::GMAC},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc3, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc4, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc5, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc6, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodc7, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodcclk, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodcen1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_gpio, CapabilityNameId::signal_role, CapabilityValueId::piodcen2, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_gpio, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_gpio, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::GPIOA},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc0, PeripheralId::GPIOA},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc1, PeripheralId::GPIOA},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc2, PeripheralId::GPIOA},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc3, PeripheralId::GPIOA},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc4, PeripheralId::GPIOA},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc5, PeripheralId::GPIOA},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc6, PeripheralId::GPIOA},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodc7, PeripheralId::GPIOA},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodcclk, PeripheralId::GPIOA},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodcen1, PeripheralId::GPIOA},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_gpio, CapabilityNameId::available_signal, CapabilityValueId::piodcen2, PeripheralId::GPIOA},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_i2c, CapabilityNameId::signal_role, CapabilityValueId::scl, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_i2c, CapabilityNameId::signal_role, CapabilityValueId::sda, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_i2c, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_i2c, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::TWIHS0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_i2c, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::TWIHS0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::scl, PeripheralId::TWIHS0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::sda, PeripheralId::TWIHS0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_i2c, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::TWIHS1},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_i2c, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::TWIHS1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::scl, PeripheralId::TWIHS1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::sda, PeripheralId::TWIHS1},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_i2c, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::TWIHS2},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_i2c, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::TWIHS2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::scl, PeripheralId::TWIHS2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_i2c, CapabilityNameId::available_signal, CapabilityValueId::sda, PeripheralId::TWIHS2},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmextrg0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmextrg1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmfi0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmfi1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmfi2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmh0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmh1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmh2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwmh3, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwml0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwml1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwml2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_pwm, CapabilityNameId::signal_role, CapabilityValueId::pwml3, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_pwm, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_pwm, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::PWM0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmextrg0, PeripheralId::PWM0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmextrg1, PeripheralId::PWM0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmfi0, PeripheralId::PWM0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmfi1, PeripheralId::PWM0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmfi2, PeripheralId::PWM0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh0, PeripheralId::PWM0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh1, PeripheralId::PWM0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh2, PeripheralId::PWM0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh3, PeripheralId::PWM0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml0, PeripheralId::PWM0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml1, PeripheralId::PWM0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml2, PeripheralId::PWM0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml3, PeripheralId::PWM0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_pwm, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::PWM1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmextrg0, PeripheralId::PWM1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmextrg1, PeripheralId::PWM1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmfi0, PeripheralId::PWM1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmfi1, PeripheralId::PWM1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmfi2, PeripheralId::PWM1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh0, PeripheralId::PWM1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh1, PeripheralId::PWM1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh2, PeripheralId::PWM1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwmh3, PeripheralId::PWM1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml0, PeripheralId::PWM1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml1, PeripheralId::PWM1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml2, PeripheralId::PWM1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_pwm, CapabilityNameId::available_signal, CapabilityValueId::pwml3, PeripheralId::PWM1},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_qspi, CapabilityNameId::signal_role, CapabilityValueId::qcs, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_qspi, CapabilityNameId::signal_role, CapabilityValueId::qio0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_qspi, CapabilityNameId::signal_role, CapabilityValueId::qio1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_qspi, CapabilityNameId::signal_role, CapabilityValueId::qio2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_qspi, CapabilityNameId::signal_role, CapabilityValueId::qio3, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_qspi, CapabilityNameId::signal_role, CapabilityValueId::qsck, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_qspi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_qspi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::QSPI},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_qspi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::QSPI},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_qspi, CapabilityNameId::available_signal, CapabilityValueId::qcs, PeripheralId::QSPI},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_qspi, CapabilityNameId::available_signal, CapabilityValueId::qio0, PeripheralId::QSPI},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_qspi, CapabilityNameId::available_signal, CapabilityValueId::qio1, PeripheralId::QSPI},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_qspi, CapabilityNameId::available_signal, CapabilityValueId::qio2, PeripheralId::QSPI},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_qspi, CapabilityNameId::available_signal, CapabilityValueId::qio3, PeripheralId::QSPI},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_qspi, CapabilityNameId::available_signal, CapabilityValueId::qsck, PeripheralId::QSPI},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_rtc, CapabilityNameId::signal_role, CapabilityValueId::rtcout0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_rtc, CapabilityNameId::signal_role, CapabilityValueId::rtcout1, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_rtc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_rtc, CapabilityNameId::available_signal, CapabilityValueId::rtcout0, PeripheralId::RTC},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_rtc, CapabilityNameId::available_signal, CapabilityValueId::rtcout1, PeripheralId::RTC},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_sdmmc, CapabilityNameId::signal_role, CapabilityValueId::mccda, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_sdmmc, CapabilityNameId::signal_role, CapabilityValueId::mcck, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_sdmmc, CapabilityNameId::signal_role, CapabilityValueId::mcda0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_sdmmc, CapabilityNameId::signal_role, CapabilityValueId::mcda1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_sdmmc, CapabilityNameId::signal_role, CapabilityValueId::mcda2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_sdmmc, CapabilityNameId::signal_role, CapabilityValueId::mcda3, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_sdmmc, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_sdmmc, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::HSMCI},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_sdmmc, CapabilityNameId::available_signal, CapabilityValueId::mccda, PeripheralId::HSMCI},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_sdmmc, CapabilityNameId::available_signal, CapabilityValueId::mcck, PeripheralId::HSMCI},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_sdmmc, CapabilityNameId::available_signal, CapabilityValueId::mcda0, PeripheralId::HSMCI},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_sdmmc, CapabilityNameId::available_signal, CapabilityValueId::mcda1, PeripheralId::HSMCI},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_sdmmc, CapabilityNameId::available_signal, CapabilityValueId::mcda2, PeripheralId::HSMCI},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_sdmmc, CapabilityNameId::available_signal, CapabilityValueId::mcda3, PeripheralId::HSMCI},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::cs, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::miso, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::mosi, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_spi, CapabilityNameId::signal_role, CapabilityValueId::sck, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_spi, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::SPI0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_spi, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::SPI0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::cs, PeripheralId::SPI0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::miso, PeripheralId::SPI0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::mosi, PeripheralId::SPI0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_spi, CapabilityNameId::available_signal, CapabilityValueId::sck, PeripheralId::SPI0},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tclk0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tclk1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tclk11, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tioa0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tioa1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tioa11, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tioa2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tiob0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tiob1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tiob11, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_timer, CapabilityNameId::signal_role, CapabilityValueId::tiob2, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_timer, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_timer, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::TC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tclk0, PeripheralId::TC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tclk1, PeripheralId::TC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tioa0, PeripheralId::TC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tioa1, PeripheralId::TC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tioa2, PeripheralId::TC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tiob0, PeripheralId::TC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tiob1, PeripheralId::TC0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tiob2, PeripheralId::TC0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_timer, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::TC1},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_timer, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::TC2},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_timer, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::TC3},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tclk11, PeripheralId::TC3},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tioa11, PeripheralId::TC3},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_timer, CapabilityNameId::available_signal, CapabilityValueId::tiob11, PeripheralId::TC3},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::cts, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dcd0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dcd1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dcd2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dsr0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dsr1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dsr2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dtr0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dtr1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::dtr2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::loncol1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::ri0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::ri2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rts, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::rx, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::sck0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::sck1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::sck2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::tx, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::urxd0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::urxd1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::urxd2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::urxd3, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::urxd4, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::utxd0, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::utxd1, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::utxd2, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::utxd3, PeripheralId::none},
  {CapabilityScopeId::ip_block, PeripheralClassId::class_uart, CapabilityNameId::signal_role, CapabilityValueId::utxd4, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_uart, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::urxd0, PeripheralId::UART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::utxd0, PeripheralId::UART0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART1},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::urxd1, PeripheralId::UART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::utxd1, PeripheralId::UART1},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART2},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::urxd2, PeripheralId::UART2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::utxd2, PeripheralId::UART2},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART3},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART3},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::urxd3, PeripheralId::UART3},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::utxd3, PeripheralId::UART3},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::UART4},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::UART4},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::urxd4, PeripheralId::UART4},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::utxd4, PeripheralId::UART4},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::USART0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::USART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::cts, PeripheralId::USART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dcd0, PeripheralId::USART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dsr0, PeripheralId::USART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dtr0, PeripheralId::USART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::ri0, PeripheralId::USART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rts, PeripheralId::USART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::USART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::sck0, PeripheralId::USART0},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::USART0},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::USART1},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::USART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::cts, PeripheralId::USART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dcd1, PeripheralId::USART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dsr1, PeripheralId::USART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dtr1, PeripheralId::USART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::loncol1, PeripheralId::USART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rts, PeripheralId::USART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::USART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::sck1, PeripheralId::USART1},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::USART1},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::RX, PeripheralId::USART2},
  {CapabilityScopeId::dma_binding, PeripheralClassId::class_uart, CapabilityNameId::dma_compatible_signal, CapabilityValueId::TX, PeripheralId::USART2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::cts, PeripheralId::USART2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dcd2, PeripheralId::USART2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dsr2, PeripheralId::USART2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::dtr2, PeripheralId::USART2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::ri2, PeripheralId::USART2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rts, PeripheralId::USART2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::rx, PeripheralId::USART2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::sck2, PeripheralId::USART2},
  {CapabilityScopeId::instance_overlay, PeripheralClassId::class_uart, CapabilityNameId::available_signal, CapabilityValueId::tx, PeripheralId::USART2},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_usb, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
  {CapabilityScopeId::runtime_contract, PeripheralClassId::class_watchdog, CapabilityNameId::runtime_supported, CapabilityValueId::true_value, PeripheralId::none},
}};

template<std::size_t Index>
struct CapabilityTraitsBase {
  static constexpr auto& kFacts = kCapabilityHardwareLut[Index];
  static constexpr bool kPresent = true;
  static constexpr CapabilityScopeId kScopeId = kFacts.scope_id;
  static constexpr PeripheralClassId kPeripheralClassId = kFacts.peripheral_class_id;
  static constexpr CapabilityNameId kNameId = kFacts.name_id;
  static constexpr CapabilityValueId kValueId = kFacts.value_id;
  static constexpr PeripheralId kPeripheralId = kFacts.peripheral_id;
};

template<> struct CapabilityTraits<CapabilityId::capability_afec_afec_s_ad0> : CapabilityTraitsBase<0> {};
template<> struct CapabilityTraits<CapabilityId::capability_afec_afec_s_ad1> : CapabilityTraitsBase<1> {};
template<> struct CapabilityTraits<CapabilityId::capability_afec_afec_s_ad10> : CapabilityTraitsBase<2> {};
template<> struct CapabilityTraits<CapabilityId::capability_afec_afec_s_ad2> : CapabilityTraitsBase<3> {};
template<> struct CapabilityTraits<CapabilityId::capability_afec_afec_s_ad5> : CapabilityTraitsBase<4> {};
template<> struct CapabilityTraits<CapabilityId::capability_afec_afec_s_ad6> : CapabilityTraitsBase<5> {};
template<> struct CapabilityTraits<CapabilityId::capability_afec_afec_s_ad7> : CapabilityTraitsBase<6> {};
template<> struct CapabilityTraits<CapabilityId::capability_afec_afec_s_ad8> : CapabilityTraitsBase<7> {};
template<> struct CapabilityTraits<CapabilityId::capability_afec_afec_s_ad9> : CapabilityTraitsBase<8> {};
template<> struct CapabilityTraits<CapabilityId::capability_afec_afec_s_adtrg> : CapabilityTraitsBase<9> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_adc> : CapabilityTraitsBase<10> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_AFEC0_XDMAC_PERID_35_RX> : CapabilityTraitsBase<11> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_afec0_lqfp100_ad0> : CapabilityTraitsBase<12> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_afec0_lqfp100_ad1> : CapabilityTraitsBase<13> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_afec0_lqfp100_ad10> : CapabilityTraitsBase<14> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_afec0_lqfp100_ad2> : CapabilityTraitsBase<15> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_afec0_lqfp100_ad5> : CapabilityTraitsBase<16> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_afec0_lqfp100_ad6> : CapabilityTraitsBase<17> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_afec0_lqfp100_ad7> : CapabilityTraitsBase<18> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_afec0_lqfp100_ad8> : CapabilityTraitsBase<19> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_afec0_lqfp100_ad9> : CapabilityTraitsBase<20> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_afec0_lqfp100_adtrg> : CapabilityTraitsBase<21> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_AFEC1_XDMAC_PERID_36_RX> : CapabilityTraitsBase<22> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_afec1_lqfp100_ad0> : CapabilityTraitsBase<23> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_afec1_lqfp100_adtrg> : CapabilityTraitsBase<24> {};
template<> struct CapabilityTraits<CapabilityId::capability_mcan_mcan_n_rx> : CapabilityTraitsBase<25> {};
template<> struct CapabilityTraits<CapabilityId::capability_mcan_mcan_n_tx> : CapabilityTraitsBase<26> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_can> : CapabilityTraitsBase<27> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_mcan0_lqfp100_rx> : CapabilityTraitsBase<28> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_mcan0_lqfp100_tx> : CapabilityTraitsBase<29> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_mcan1_lqfp100_rx> : CapabilityTraitsBase<30> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_mcan1_lqfp100_tx> : CapabilityTraitsBase<31> {};
template<> struct CapabilityTraits<CapabilityId::capability_dacc_dacc_e_dac0> : CapabilityTraitsBase<32> {};
template<> struct CapabilityTraits<CapabilityId::capability_dacc_dacc_e_dac1> : CapabilityTraitsBase<33> {};
template<> struct CapabilityTraits<CapabilityId::capability_dacc_dacc_e_datrg> : CapabilityTraitsBase<34> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_dac> : CapabilityTraitsBase<35> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_DACC_XDMAC_PERID_30_CH0_TX> : CapabilityTraitsBase<36> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_DACC_XDMAC_PERID_31_CH1_TX> : CapabilityTraitsBase<37> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_dacc_lqfp100_dac0> : CapabilityTraitsBase<38> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_dacc_lqfp100_dac1> : CapabilityTraitsBase<39> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_dacc_lqfp100_datrg> : CapabilityTraitsBase<40> {};
template<> struct CapabilityTraits<CapabilityId::device_core_count> : CapabilityTraitsBase<41> {};
template<> struct CapabilityTraits<CapabilityId::device_multicore_topology> : CapabilityTraitsBase<42> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_dma> : CapabilityTraitsBase<43> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_gcol> : CapabilityTraitsBase<44> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_gcrs> : CapabilityTraitsBase<45> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_gmdc> : CapabilityTraitsBase<46> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_gmdio> : CapabilityTraitsBase<47> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_grx0> : CapabilityTraitsBase<48> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_grx1> : CapabilityTraitsBase<49> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_grx2> : CapabilityTraitsBase<50> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_grx3> : CapabilityTraitsBase<51> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_grxck> : CapabilityTraitsBase<52> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_grxdv> : CapabilityTraitsBase<53> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_grxer> : CapabilityTraitsBase<54> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_gtsucomp> : CapabilityTraitsBase<55> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_gtx0> : CapabilityTraitsBase<56> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_gtx1> : CapabilityTraitsBase<57> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_gtx2> : CapabilityTraitsBase<58> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_gtx3> : CapabilityTraitsBase<59> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_gtxck> : CapabilityTraitsBase<60> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_gtxen> : CapabilityTraitsBase<61> {};
template<> struct CapabilityTraits<CapabilityId::capability_gmac_gmac_s_gtxer> : CapabilityTraitsBase<62> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_eth> : CapabilityTraitsBase<63> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_gcol> : CapabilityTraitsBase<64> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_gcrs> : CapabilityTraitsBase<65> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_gmdc> : CapabilityTraitsBase<66> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_gmdio> : CapabilityTraitsBase<67> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_grx0> : CapabilityTraitsBase<68> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_grx1> : CapabilityTraitsBase<69> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_grx2> : CapabilityTraitsBase<70> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_grx3> : CapabilityTraitsBase<71> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_grxck> : CapabilityTraitsBase<72> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_grxdv> : CapabilityTraitsBase<73> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_grxer> : CapabilityTraitsBase<74> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_gtsucomp> : CapabilityTraitsBase<75> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_gtx0> : CapabilityTraitsBase<76> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_gtx1> : CapabilityTraitsBase<77> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_gtx2> : CapabilityTraitsBase<78> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_gtx3> : CapabilityTraitsBase<79> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_gtxck> : CapabilityTraitsBase<80> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_gtxen> : CapabilityTraitsBase<81> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gmac_lqfp100_gtxer> : CapabilityTraitsBase<82> {};
template<> struct CapabilityTraits<CapabilityId::capability_gpio_pio_v_piodc0> : CapabilityTraitsBase<83> {};
template<> struct CapabilityTraits<CapabilityId::capability_gpio_pio_v_piodc1> : CapabilityTraitsBase<84> {};
template<> struct CapabilityTraits<CapabilityId::capability_gpio_pio_v_piodc2> : CapabilityTraitsBase<85> {};
template<> struct CapabilityTraits<CapabilityId::capability_gpio_pio_v_piodc3> : CapabilityTraitsBase<86> {};
template<> struct CapabilityTraits<CapabilityId::capability_gpio_pio_v_piodc4> : CapabilityTraitsBase<87> {};
template<> struct CapabilityTraits<CapabilityId::capability_gpio_pio_v_piodc5> : CapabilityTraitsBase<88> {};
template<> struct CapabilityTraits<CapabilityId::capability_gpio_pio_v_piodc6> : CapabilityTraitsBase<89> {};
template<> struct CapabilityTraits<CapabilityId::capability_gpio_pio_v_piodc7> : CapabilityTraitsBase<90> {};
template<> struct CapabilityTraits<CapabilityId::capability_gpio_pio_v_piodcclk> : CapabilityTraitsBase<91> {};
template<> struct CapabilityTraits<CapabilityId::capability_gpio_pio_v_piodcen1> : CapabilityTraitsBase<92> {};
template<> struct CapabilityTraits<CapabilityId::capability_gpio_pio_v_piodcen2> : CapabilityTraitsBase<93> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_gpio> : CapabilityTraitsBase<94> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_GPIOA_XDMAC_PERID_34_RX> : CapabilityTraitsBase<95> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpioa_lqfp100_piodc0> : CapabilityTraitsBase<96> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpioa_lqfp100_piodc1> : CapabilityTraitsBase<97> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpioa_lqfp100_piodc2> : CapabilityTraitsBase<98> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpioa_lqfp100_piodc3> : CapabilityTraitsBase<99> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpioa_lqfp100_piodc4> : CapabilityTraitsBase<100> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpioa_lqfp100_piodc5> : CapabilityTraitsBase<101> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpioa_lqfp100_piodc6> : CapabilityTraitsBase<102> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpioa_lqfp100_piodc7> : CapabilityTraitsBase<103> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpioa_lqfp100_piodcclk> : CapabilityTraitsBase<104> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpioa_lqfp100_piodcen1> : CapabilityTraitsBase<105> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_gpioa_lqfp100_piodcen2> : CapabilityTraitsBase<106> {};
template<> struct CapabilityTraits<CapabilityId::capability_twihs_twihs_z_scl> : CapabilityTraitsBase<107> {};
template<> struct CapabilityTraits<CapabilityId::capability_twihs_twihs_z_sda> : CapabilityTraitsBase<108> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_i2c> : CapabilityTraitsBase<109> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_TWIHS0_XDMAC_PERID_15_RX> : CapabilityTraitsBase<110> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_TWIHS0_XDMAC_PERID_14_TX> : CapabilityTraitsBase<111> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_twihs0_lqfp100_scl> : CapabilityTraitsBase<112> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_twihs0_lqfp100_sda> : CapabilityTraitsBase<113> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_TWIHS1_XDMAC_PERID_17_RX> : CapabilityTraitsBase<114> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_TWIHS1_XDMAC_PERID_16_TX> : CapabilityTraitsBase<115> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_twihs1_lqfp100_scl> : CapabilityTraitsBase<116> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_twihs1_lqfp100_sda> : CapabilityTraitsBase<117> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_TWIHS2_XDMAC_PERID_19_RX> : CapabilityTraitsBase<118> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_TWIHS2_XDMAC_PERID_18_TX> : CapabilityTraitsBase<119> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_twihs2_lqfp100_scl> : CapabilityTraitsBase<120> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_twihs2_lqfp100_sda> : CapabilityTraitsBase<121> {};
template<> struct CapabilityTraits<CapabilityId::capability_pwm_pwm_y_pwmextrg0> : CapabilityTraitsBase<122> {};
template<> struct CapabilityTraits<CapabilityId::capability_pwm_pwm_y_pwmextrg1> : CapabilityTraitsBase<123> {};
template<> struct CapabilityTraits<CapabilityId::capability_pwm_pwm_y_pwmfi0> : CapabilityTraitsBase<124> {};
template<> struct CapabilityTraits<CapabilityId::capability_pwm_pwm_y_pwmfi1> : CapabilityTraitsBase<125> {};
template<> struct CapabilityTraits<CapabilityId::capability_pwm_pwm_y_pwmfi2> : CapabilityTraitsBase<126> {};
template<> struct CapabilityTraits<CapabilityId::capability_pwm_pwm_y_pwmh0> : CapabilityTraitsBase<127> {};
template<> struct CapabilityTraits<CapabilityId::capability_pwm_pwm_y_pwmh1> : CapabilityTraitsBase<128> {};
template<> struct CapabilityTraits<CapabilityId::capability_pwm_pwm_y_pwmh2> : CapabilityTraitsBase<129> {};
template<> struct CapabilityTraits<CapabilityId::capability_pwm_pwm_y_pwmh3> : CapabilityTraitsBase<130> {};
template<> struct CapabilityTraits<CapabilityId::capability_pwm_pwm_y_pwml0> : CapabilityTraitsBase<131> {};
template<> struct CapabilityTraits<CapabilityId::capability_pwm_pwm_y_pwml1> : CapabilityTraitsBase<132> {};
template<> struct CapabilityTraits<CapabilityId::capability_pwm_pwm_y_pwml2> : CapabilityTraitsBase<133> {};
template<> struct CapabilityTraits<CapabilityId::capability_pwm_pwm_y_pwml3> : CapabilityTraitsBase<134> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_pwm> : CapabilityTraitsBase<135> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_PWM0_XDMAC_PERID_13_TX> : CapabilityTraitsBase<136> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm0_lqfp100_pwmextrg0> : CapabilityTraitsBase<137> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm0_lqfp100_pwmextrg1> : CapabilityTraitsBase<138> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm0_lqfp100_pwmfi0> : CapabilityTraitsBase<139> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm0_lqfp100_pwmfi1> : CapabilityTraitsBase<140> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm0_lqfp100_pwmfi2> : CapabilityTraitsBase<141> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm0_lqfp100_pwmh0> : CapabilityTraitsBase<142> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm0_lqfp100_pwmh1> : CapabilityTraitsBase<143> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm0_lqfp100_pwmh2> : CapabilityTraitsBase<144> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm0_lqfp100_pwmh3> : CapabilityTraitsBase<145> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm0_lqfp100_pwml0> : CapabilityTraitsBase<146> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm0_lqfp100_pwml1> : CapabilityTraitsBase<147> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm0_lqfp100_pwml2> : CapabilityTraitsBase<148> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm0_lqfp100_pwml3> : CapabilityTraitsBase<149> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_PWM1_XDMAC_PERID_39_TX> : CapabilityTraitsBase<150> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm1_lqfp100_pwmextrg0> : CapabilityTraitsBase<151> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm1_lqfp100_pwmextrg1> : CapabilityTraitsBase<152> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm1_lqfp100_pwmfi0> : CapabilityTraitsBase<153> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm1_lqfp100_pwmfi1> : CapabilityTraitsBase<154> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm1_lqfp100_pwmfi2> : CapabilityTraitsBase<155> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm1_lqfp100_pwmh0> : CapabilityTraitsBase<156> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm1_lqfp100_pwmh1> : CapabilityTraitsBase<157> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm1_lqfp100_pwmh2> : CapabilityTraitsBase<158> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm1_lqfp100_pwmh3> : CapabilityTraitsBase<159> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm1_lqfp100_pwml0> : CapabilityTraitsBase<160> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm1_lqfp100_pwml1> : CapabilityTraitsBase<161> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm1_lqfp100_pwml2> : CapabilityTraitsBase<162> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_pwm1_lqfp100_pwml3> : CapabilityTraitsBase<163> {};
template<> struct CapabilityTraits<CapabilityId::capability_qspi_qspi_j_qcs> : CapabilityTraitsBase<164> {};
template<> struct CapabilityTraits<CapabilityId::capability_qspi_qspi_j_qio0> : CapabilityTraitsBase<165> {};
template<> struct CapabilityTraits<CapabilityId::capability_qspi_qspi_j_qio1> : CapabilityTraitsBase<166> {};
template<> struct CapabilityTraits<CapabilityId::capability_qspi_qspi_j_qio2> : CapabilityTraitsBase<167> {};
template<> struct CapabilityTraits<CapabilityId::capability_qspi_qspi_j_qio3> : CapabilityTraitsBase<168> {};
template<> struct CapabilityTraits<CapabilityId::capability_qspi_qspi_j_qsck> : CapabilityTraitsBase<169> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_qspi> : CapabilityTraitsBase<170> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_QSPI_XDMAC_PERID_6_RX> : CapabilityTraitsBase<171> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_QSPI_XDMAC_PERID_5_TX> : CapabilityTraitsBase<172> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_qspi_lqfp100_qcs> : CapabilityTraitsBase<173> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_qspi_lqfp100_qio0> : CapabilityTraitsBase<174> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_qspi_lqfp100_qio1> : CapabilityTraitsBase<175> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_qspi_lqfp100_qio2> : CapabilityTraitsBase<176> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_qspi_lqfp100_qio3> : CapabilityTraitsBase<177> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_qspi_lqfp100_qsck> : CapabilityTraitsBase<178> {};
template<> struct CapabilityTraits<CapabilityId::capability_rtc_rtc_zb_rtcout0> : CapabilityTraitsBase<179> {};
template<> struct CapabilityTraits<CapabilityId::capability_rtc_rtc_zb_rtcout1> : CapabilityTraitsBase<180> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_rtc> : CapabilityTraitsBase<181> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_rtc_lqfp100_rtcout0> : CapabilityTraitsBase<182> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_rtc_lqfp100_rtcout1> : CapabilityTraitsBase<183> {};
template<> struct CapabilityTraits<CapabilityId::capability_hsmci_hsmci_r_mccda> : CapabilityTraitsBase<184> {};
template<> struct CapabilityTraits<CapabilityId::capability_hsmci_hsmci_r_mcck> : CapabilityTraitsBase<185> {};
template<> struct CapabilityTraits<CapabilityId::capability_hsmci_hsmci_r_mcda0> : CapabilityTraitsBase<186> {};
template<> struct CapabilityTraits<CapabilityId::capability_hsmci_hsmci_r_mcda1> : CapabilityTraitsBase<187> {};
template<> struct CapabilityTraits<CapabilityId::capability_hsmci_hsmci_r_mcda2> : CapabilityTraitsBase<188> {};
template<> struct CapabilityTraits<CapabilityId::capability_hsmci_hsmci_r_mcda3> : CapabilityTraitsBase<189> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_sdmmc> : CapabilityTraitsBase<190> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_HSMCI_XDMAC_PERID_0_RX> : CapabilityTraitsBase<191> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_hsmci_lqfp100_mccda> : CapabilityTraitsBase<192> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_hsmci_lqfp100_mcck> : CapabilityTraitsBase<193> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_hsmci_lqfp100_mcda0> : CapabilityTraitsBase<194> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_hsmci_lqfp100_mcda1> : CapabilityTraitsBase<195> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_hsmci_lqfp100_mcda2> : CapabilityTraitsBase<196> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_hsmci_lqfp100_mcda3> : CapabilityTraitsBase<197> {};
template<> struct CapabilityTraits<CapabilityId::capability_spi_spi_zm_cs> : CapabilityTraitsBase<198> {};
template<> struct CapabilityTraits<CapabilityId::capability_spi_spi_zm_miso> : CapabilityTraitsBase<199> {};
template<> struct CapabilityTraits<CapabilityId::capability_spi_spi_zm_mosi> : CapabilityTraitsBase<200> {};
template<> struct CapabilityTraits<CapabilityId::capability_spi_spi_zm_sck> : CapabilityTraitsBase<201> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_spi> : CapabilityTraitsBase<202> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_SPI0_XDMAC_PERID_2_RX> : CapabilityTraitsBase<203> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_SPI0_XDMAC_PERID_1_TX> : CapabilityTraitsBase<204> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi0_lqfp100_cs> : CapabilityTraitsBase<205> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi0_lqfp100_miso> : CapabilityTraitsBase<206> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi0_lqfp100_mosi> : CapabilityTraitsBase<207> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_spi0_lqfp100_sck> : CapabilityTraitsBase<208> {};
template<> struct CapabilityTraits<CapabilityId::capability_tc_tc_zl_tclk0> : CapabilityTraitsBase<209> {};
template<> struct CapabilityTraits<CapabilityId::capability_tc_tc_zl_tclk1> : CapabilityTraitsBase<210> {};
template<> struct CapabilityTraits<CapabilityId::capability_tc_tc_zl_tclk11> : CapabilityTraitsBase<211> {};
template<> struct CapabilityTraits<CapabilityId::capability_tc_tc_zl_tioa0> : CapabilityTraitsBase<212> {};
template<> struct CapabilityTraits<CapabilityId::capability_tc_tc_zl_tioa1> : CapabilityTraitsBase<213> {};
template<> struct CapabilityTraits<CapabilityId::capability_tc_tc_zl_tioa11> : CapabilityTraitsBase<214> {};
template<> struct CapabilityTraits<CapabilityId::capability_tc_tc_zl_tioa2> : CapabilityTraitsBase<215> {};
template<> struct CapabilityTraits<CapabilityId::capability_tc_tc_zl_tiob0> : CapabilityTraitsBase<216> {};
template<> struct CapabilityTraits<CapabilityId::capability_tc_tc_zl_tiob1> : CapabilityTraitsBase<217> {};
template<> struct CapabilityTraits<CapabilityId::capability_tc_tc_zl_tiob11> : CapabilityTraitsBase<218> {};
template<> struct CapabilityTraits<CapabilityId::capability_tc_tc_zl_tiob2> : CapabilityTraitsBase<219> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_timer> : CapabilityTraitsBase<220> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_TC0_XDMAC_PERID_40_RX> : CapabilityTraitsBase<221> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_tc0_lqfp100_tclk0> : CapabilityTraitsBase<222> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_tc0_lqfp100_tclk1> : CapabilityTraitsBase<223> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_tc0_lqfp100_tioa0> : CapabilityTraitsBase<224> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_tc0_lqfp100_tioa1> : CapabilityTraitsBase<225> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_tc0_lqfp100_tioa2> : CapabilityTraitsBase<226> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_tc0_lqfp100_tiob0> : CapabilityTraitsBase<227> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_tc0_lqfp100_tiob1> : CapabilityTraitsBase<228> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_tc0_lqfp100_tiob2> : CapabilityTraitsBase<229> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_TC1_XDMAC_PERID_41_RX> : CapabilityTraitsBase<230> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_TC2_XDMAC_PERID_42_RX> : CapabilityTraitsBase<231> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_TC3_XDMAC_PERID_43_RX> : CapabilityTraitsBase<232> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_tc3_lqfp100_tclk11> : CapabilityTraitsBase<233> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_tc3_lqfp100_tioa11> : CapabilityTraitsBase<234> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_tc3_lqfp100_tiob11> : CapabilityTraitsBase<235> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_cts> : CapabilityTraitsBase<236> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_dcd0> : CapabilityTraitsBase<237> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_dcd1> : CapabilityTraitsBase<238> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_dcd2> : CapabilityTraitsBase<239> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_dsr0> : CapabilityTraitsBase<240> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_dsr1> : CapabilityTraitsBase<241> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_dsr2> : CapabilityTraitsBase<242> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_dtr0> : CapabilityTraitsBase<243> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_dtr1> : CapabilityTraitsBase<244> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_dtr2> : CapabilityTraitsBase<245> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_loncol1> : CapabilityTraitsBase<246> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_ri0> : CapabilityTraitsBase<247> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_ri2> : CapabilityTraitsBase<248> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_rts> : CapabilityTraitsBase<249> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_rx> : CapabilityTraitsBase<250> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_sck0> : CapabilityTraitsBase<251> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_sck1> : CapabilityTraitsBase<252> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_sck2> : CapabilityTraitsBase<253> {};
template<> struct CapabilityTraits<CapabilityId::capability_usart_usart_zw_tx> : CapabilityTraitsBase<254> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_uart_r_urxd0> : CapabilityTraitsBase<255> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_uart_r_urxd1> : CapabilityTraitsBase<256> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_uart_r_urxd2> : CapabilityTraitsBase<257> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_uart_r_urxd3> : CapabilityTraitsBase<258> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_uart_r_urxd4> : CapabilityTraitsBase<259> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_uart_r_utxd0> : CapabilityTraitsBase<260> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_uart_r_utxd1> : CapabilityTraitsBase<261> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_uart_r_utxd2> : CapabilityTraitsBase<262> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_uart_r_utxd3> : CapabilityTraitsBase<263> {};
template<> struct CapabilityTraits<CapabilityId::capability_uart_uart_r_utxd4> : CapabilityTraitsBase<264> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_uart> : CapabilityTraitsBase<265> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART0_XDMAC_PERID_21_RX> : CapabilityTraitsBase<266> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART0_XDMAC_PERID_20_TX> : CapabilityTraitsBase<267> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart0_lqfp100_urxd0> : CapabilityTraitsBase<268> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart0_lqfp100_utxd0> : CapabilityTraitsBase<269> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART1_XDMAC_PERID_23_RX> : CapabilityTraitsBase<270> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART1_XDMAC_PERID_22_TX> : CapabilityTraitsBase<271> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart1_lqfp100_urxd1> : CapabilityTraitsBase<272> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart1_lqfp100_utxd1> : CapabilityTraitsBase<273> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART2_XDMAC_PERID_25_RX> : CapabilityTraitsBase<274> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART2_XDMAC_PERID_24_TX> : CapabilityTraitsBase<275> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart2_lqfp100_urxd2> : CapabilityTraitsBase<276> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart2_lqfp100_utxd2> : CapabilityTraitsBase<277> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART3_XDMAC_PERID_27_RX> : CapabilityTraitsBase<278> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART3_XDMAC_PERID_26_TX> : CapabilityTraitsBase<279> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart3_lqfp100_urxd3> : CapabilityTraitsBase<280> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart3_lqfp100_utxd3> : CapabilityTraitsBase<281> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART4_XDMAC_PERID_29_RX> : CapabilityTraitsBase<282> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_UART4_XDMAC_PERID_28_TX> : CapabilityTraitsBase<283> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart4_lqfp100_urxd4> : CapabilityTraitsBase<284> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_uart4_lqfp100_utxd4> : CapabilityTraitsBase<285> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_USART0_XDMAC_PERID_8_RX> : CapabilityTraitsBase<286> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_USART0_XDMAC_PERID_7_TX> : CapabilityTraitsBase<287> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart0_lqfp100_cts> : CapabilityTraitsBase<288> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart0_lqfp100_dcd0> : CapabilityTraitsBase<289> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart0_lqfp100_dsr0> : CapabilityTraitsBase<290> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart0_lqfp100_dtr0> : CapabilityTraitsBase<291> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart0_lqfp100_ri0> : CapabilityTraitsBase<292> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart0_lqfp100_rts> : CapabilityTraitsBase<293> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart0_lqfp100_rx> : CapabilityTraitsBase<294> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart0_lqfp100_sck0> : CapabilityTraitsBase<295> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart0_lqfp100_tx> : CapabilityTraitsBase<296> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_USART1_XDMAC_PERID_10_RX> : CapabilityTraitsBase<297> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_USART1_XDMAC_PERID_9_TX> : CapabilityTraitsBase<298> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart1_lqfp100_cts> : CapabilityTraitsBase<299> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart1_lqfp100_dcd1> : CapabilityTraitsBase<300> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart1_lqfp100_dsr1> : CapabilityTraitsBase<301> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart1_lqfp100_dtr1> : CapabilityTraitsBase<302> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart1_lqfp100_loncol1> : CapabilityTraitsBase<303> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart1_lqfp100_rts> : CapabilityTraitsBase<304> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart1_lqfp100_rx> : CapabilityTraitsBase<305> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart1_lqfp100_sck1> : CapabilityTraitsBase<306> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart1_lqfp100_tx> : CapabilityTraitsBase<307> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_USART2_XDMAC_PERID_12_RX> : CapabilityTraitsBase<308> {};
template<> struct CapabilityTraits<CapabilityId::runtime_dma_USART2_XDMAC_PERID_11_TX> : CapabilityTraitsBase<309> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart2_lqfp100_cts> : CapabilityTraitsBase<310> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart2_lqfp100_dcd2> : CapabilityTraitsBase<311> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart2_lqfp100_dsr2> : CapabilityTraitsBase<312> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart2_lqfp100_dtr2> : CapabilityTraitsBase<313> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart2_lqfp100_ri2> : CapabilityTraitsBase<314> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart2_lqfp100_rts> : CapabilityTraitsBase<315> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart2_lqfp100_rx> : CapabilityTraitsBase<316> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart2_lqfp100_sck2> : CapabilityTraitsBase<317> {};
template<> struct CapabilityTraits<CapabilityId::capability_instance_usart2_lqfp100_tx> : CapabilityTraitsBase<318> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_usb> : CapabilityTraitsBase<319> {};
template<> struct CapabilityTraits<CapabilityId::runtime_support_watchdog> : CapabilityTraitsBase<320> {};

template<PeripheralClassId Id>
struct PeripheralClassCapabilityTraits {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_adc> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 25> kCapabilityIds = {{
    CapabilityId::capability_afec_afec_s_ad0,
    CapabilityId::capability_afec_afec_s_ad1,
    CapabilityId::capability_afec_afec_s_ad10,
    CapabilityId::capability_afec_afec_s_ad2,
    CapabilityId::capability_afec_afec_s_ad5,
    CapabilityId::capability_afec_afec_s_ad6,
    CapabilityId::capability_afec_afec_s_ad7,
    CapabilityId::capability_afec_afec_s_ad8,
    CapabilityId::capability_afec_afec_s_ad9,
    CapabilityId::capability_afec_afec_s_adtrg,
    CapabilityId::runtime_support_adc,
    CapabilityId::runtime_dma_AFEC0_XDMAC_PERID_35_RX,
    CapabilityId::capability_instance_afec0_lqfp100_ad0,
    CapabilityId::capability_instance_afec0_lqfp100_ad1,
    CapabilityId::capability_instance_afec0_lqfp100_ad10,
    CapabilityId::capability_instance_afec0_lqfp100_ad2,
    CapabilityId::capability_instance_afec0_lqfp100_ad5,
    CapabilityId::capability_instance_afec0_lqfp100_ad6,
    CapabilityId::capability_instance_afec0_lqfp100_ad7,
    CapabilityId::capability_instance_afec0_lqfp100_ad8,
    CapabilityId::capability_instance_afec0_lqfp100_ad9,
    CapabilityId::capability_instance_afec0_lqfp100_adtrg,
    CapabilityId::runtime_dma_AFEC1_XDMAC_PERID_36_RX,
    CapabilityId::capability_instance_afec1_lqfp100_ad0,
    CapabilityId::capability_instance_afec1_lqfp100_adtrg,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_can> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 7> kCapabilityIds = {{
    CapabilityId::capability_mcan_mcan_n_rx,
    CapabilityId::capability_mcan_mcan_n_tx,
    CapabilityId::runtime_support_can,
    CapabilityId::capability_instance_mcan0_lqfp100_rx,
    CapabilityId::capability_instance_mcan0_lqfp100_tx,
    CapabilityId::capability_instance_mcan1_lqfp100_rx,
    CapabilityId::capability_instance_mcan1_lqfp100_tx,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_dac> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 9> kCapabilityIds = {{
    CapabilityId::capability_dacc_dacc_e_dac0,
    CapabilityId::capability_dacc_dacc_e_dac1,
    CapabilityId::capability_dacc_dacc_e_datrg,
    CapabilityId::runtime_support_dac,
    CapabilityId::runtime_dma_DACC_XDMAC_PERID_30_CH0_TX,
    CapabilityId::runtime_dma_DACC_XDMAC_PERID_31_CH1_TX,
    CapabilityId::capability_instance_dacc_lqfp100_dac0,
    CapabilityId::capability_instance_dacc_lqfp100_dac1,
    CapabilityId::capability_instance_dacc_lqfp100_datrg,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_dma> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_dma,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_eth> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 39> kCapabilityIds = {{
    CapabilityId::capability_gmac_gmac_s_gcol,
    CapabilityId::capability_gmac_gmac_s_gcrs,
    CapabilityId::capability_gmac_gmac_s_gmdc,
    CapabilityId::capability_gmac_gmac_s_gmdio,
    CapabilityId::capability_gmac_gmac_s_grx0,
    CapabilityId::capability_gmac_gmac_s_grx1,
    CapabilityId::capability_gmac_gmac_s_grx2,
    CapabilityId::capability_gmac_gmac_s_grx3,
    CapabilityId::capability_gmac_gmac_s_grxck,
    CapabilityId::capability_gmac_gmac_s_grxdv,
    CapabilityId::capability_gmac_gmac_s_grxer,
    CapabilityId::capability_gmac_gmac_s_gtsucomp,
    CapabilityId::capability_gmac_gmac_s_gtx0,
    CapabilityId::capability_gmac_gmac_s_gtx1,
    CapabilityId::capability_gmac_gmac_s_gtx2,
    CapabilityId::capability_gmac_gmac_s_gtx3,
    CapabilityId::capability_gmac_gmac_s_gtxck,
    CapabilityId::capability_gmac_gmac_s_gtxen,
    CapabilityId::capability_gmac_gmac_s_gtxer,
    CapabilityId::runtime_support_eth,
    CapabilityId::capability_instance_gmac_lqfp100_gcol,
    CapabilityId::capability_instance_gmac_lqfp100_gcrs,
    CapabilityId::capability_instance_gmac_lqfp100_gmdc,
    CapabilityId::capability_instance_gmac_lqfp100_gmdio,
    CapabilityId::capability_instance_gmac_lqfp100_grx0,
    CapabilityId::capability_instance_gmac_lqfp100_grx1,
    CapabilityId::capability_instance_gmac_lqfp100_grx2,
    CapabilityId::capability_instance_gmac_lqfp100_grx3,
    CapabilityId::capability_instance_gmac_lqfp100_grxck,
    CapabilityId::capability_instance_gmac_lqfp100_grxdv,
    CapabilityId::capability_instance_gmac_lqfp100_grxer,
    CapabilityId::capability_instance_gmac_lqfp100_gtsucomp,
    CapabilityId::capability_instance_gmac_lqfp100_gtx0,
    CapabilityId::capability_instance_gmac_lqfp100_gtx1,
    CapabilityId::capability_instance_gmac_lqfp100_gtx2,
    CapabilityId::capability_instance_gmac_lqfp100_gtx3,
    CapabilityId::capability_instance_gmac_lqfp100_gtxck,
    CapabilityId::capability_instance_gmac_lqfp100_gtxen,
    CapabilityId::capability_instance_gmac_lqfp100_gtxer,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_gpio> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 24> kCapabilityIds = {{
    CapabilityId::capability_gpio_pio_v_piodc0,
    CapabilityId::capability_gpio_pio_v_piodc1,
    CapabilityId::capability_gpio_pio_v_piodc2,
    CapabilityId::capability_gpio_pio_v_piodc3,
    CapabilityId::capability_gpio_pio_v_piodc4,
    CapabilityId::capability_gpio_pio_v_piodc5,
    CapabilityId::capability_gpio_pio_v_piodc6,
    CapabilityId::capability_gpio_pio_v_piodc7,
    CapabilityId::capability_gpio_pio_v_piodcclk,
    CapabilityId::capability_gpio_pio_v_piodcen1,
    CapabilityId::capability_gpio_pio_v_piodcen2,
    CapabilityId::runtime_support_gpio,
    CapabilityId::runtime_dma_GPIOA_XDMAC_PERID_34_RX,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc0,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc1,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc2,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc3,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc4,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc5,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc6,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc7,
    CapabilityId::capability_instance_gpioa_lqfp100_piodcclk,
    CapabilityId::capability_instance_gpioa_lqfp100_piodcen1,
    CapabilityId::capability_instance_gpioa_lqfp100_piodcen2,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_i2c> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 15> kCapabilityIds = {{
    CapabilityId::capability_twihs_twihs_z_scl,
    CapabilityId::capability_twihs_twihs_z_sda,
    CapabilityId::runtime_support_i2c,
    CapabilityId::runtime_dma_TWIHS0_XDMAC_PERID_15_RX,
    CapabilityId::runtime_dma_TWIHS0_XDMAC_PERID_14_TX,
    CapabilityId::capability_instance_twihs0_lqfp100_scl,
    CapabilityId::capability_instance_twihs0_lqfp100_sda,
    CapabilityId::runtime_dma_TWIHS1_XDMAC_PERID_17_RX,
    CapabilityId::runtime_dma_TWIHS1_XDMAC_PERID_16_TX,
    CapabilityId::capability_instance_twihs1_lqfp100_scl,
    CapabilityId::capability_instance_twihs1_lqfp100_sda,
    CapabilityId::runtime_dma_TWIHS2_XDMAC_PERID_19_RX,
    CapabilityId::runtime_dma_TWIHS2_XDMAC_PERID_18_TX,
    CapabilityId::capability_instance_twihs2_lqfp100_scl,
    CapabilityId::capability_instance_twihs2_lqfp100_sda,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_pwm> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 42> kCapabilityIds = {{
    CapabilityId::capability_pwm_pwm_y_pwmextrg0,
    CapabilityId::capability_pwm_pwm_y_pwmextrg1,
    CapabilityId::capability_pwm_pwm_y_pwmfi0,
    CapabilityId::capability_pwm_pwm_y_pwmfi1,
    CapabilityId::capability_pwm_pwm_y_pwmfi2,
    CapabilityId::capability_pwm_pwm_y_pwmh0,
    CapabilityId::capability_pwm_pwm_y_pwmh1,
    CapabilityId::capability_pwm_pwm_y_pwmh2,
    CapabilityId::capability_pwm_pwm_y_pwmh3,
    CapabilityId::capability_pwm_pwm_y_pwml0,
    CapabilityId::capability_pwm_pwm_y_pwml1,
    CapabilityId::capability_pwm_pwm_y_pwml2,
    CapabilityId::capability_pwm_pwm_y_pwml3,
    CapabilityId::runtime_support_pwm,
    CapabilityId::runtime_dma_PWM0_XDMAC_PERID_13_TX,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmextrg0,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmextrg1,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmfi0,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmfi1,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmfi2,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmh0,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmh1,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmh2,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmh3,
    CapabilityId::capability_instance_pwm0_lqfp100_pwml0,
    CapabilityId::capability_instance_pwm0_lqfp100_pwml1,
    CapabilityId::capability_instance_pwm0_lqfp100_pwml2,
    CapabilityId::capability_instance_pwm0_lqfp100_pwml3,
    CapabilityId::runtime_dma_PWM1_XDMAC_PERID_39_TX,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmextrg0,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmextrg1,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmfi0,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmfi1,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmfi2,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmh0,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmh1,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmh2,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmh3,
    CapabilityId::capability_instance_pwm1_lqfp100_pwml0,
    CapabilityId::capability_instance_pwm1_lqfp100_pwml1,
    CapabilityId::capability_instance_pwm1_lqfp100_pwml2,
    CapabilityId::capability_instance_pwm1_lqfp100_pwml3,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_qspi> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 15> kCapabilityIds = {{
    CapabilityId::capability_qspi_qspi_j_qcs,
    CapabilityId::capability_qspi_qspi_j_qio0,
    CapabilityId::capability_qspi_qspi_j_qio1,
    CapabilityId::capability_qspi_qspi_j_qio2,
    CapabilityId::capability_qspi_qspi_j_qio3,
    CapabilityId::capability_qspi_qspi_j_qsck,
    CapabilityId::runtime_support_qspi,
    CapabilityId::runtime_dma_QSPI_XDMAC_PERID_6_RX,
    CapabilityId::runtime_dma_QSPI_XDMAC_PERID_5_TX,
    CapabilityId::capability_instance_qspi_lqfp100_qcs,
    CapabilityId::capability_instance_qspi_lqfp100_qio0,
    CapabilityId::capability_instance_qspi_lqfp100_qio1,
    CapabilityId::capability_instance_qspi_lqfp100_qio2,
    CapabilityId::capability_instance_qspi_lqfp100_qio3,
    CapabilityId::capability_instance_qspi_lqfp100_qsck,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_rtc> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 5> kCapabilityIds = {{
    CapabilityId::capability_rtc_rtc_zb_rtcout0,
    CapabilityId::capability_rtc_rtc_zb_rtcout1,
    CapabilityId::runtime_support_rtc,
    CapabilityId::capability_instance_rtc_lqfp100_rtcout0,
    CapabilityId::capability_instance_rtc_lqfp100_rtcout1,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_sdmmc> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 14> kCapabilityIds = {{
    CapabilityId::capability_hsmci_hsmci_r_mccda,
    CapabilityId::capability_hsmci_hsmci_r_mcck,
    CapabilityId::capability_hsmci_hsmci_r_mcda0,
    CapabilityId::capability_hsmci_hsmci_r_mcda1,
    CapabilityId::capability_hsmci_hsmci_r_mcda2,
    CapabilityId::capability_hsmci_hsmci_r_mcda3,
    CapabilityId::runtime_support_sdmmc,
    CapabilityId::runtime_dma_HSMCI_XDMAC_PERID_0_RX,
    CapabilityId::capability_instance_hsmci_lqfp100_mccda,
    CapabilityId::capability_instance_hsmci_lqfp100_mcck,
    CapabilityId::capability_instance_hsmci_lqfp100_mcda0,
    CapabilityId::capability_instance_hsmci_lqfp100_mcda1,
    CapabilityId::capability_instance_hsmci_lqfp100_mcda2,
    CapabilityId::capability_instance_hsmci_lqfp100_mcda3,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_spi> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 11> kCapabilityIds = {{
    CapabilityId::capability_spi_spi_zm_cs,
    CapabilityId::capability_spi_spi_zm_miso,
    CapabilityId::capability_spi_spi_zm_mosi,
    CapabilityId::capability_spi_spi_zm_sck,
    CapabilityId::runtime_support_spi,
    CapabilityId::runtime_dma_SPI0_XDMAC_PERID_2_RX,
    CapabilityId::runtime_dma_SPI0_XDMAC_PERID_1_TX,
    CapabilityId::capability_instance_spi0_lqfp100_cs,
    CapabilityId::capability_instance_spi0_lqfp100_miso,
    CapabilityId::capability_instance_spi0_lqfp100_mosi,
    CapabilityId::capability_instance_spi0_lqfp100_sck,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_timer> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 27> kCapabilityIds = {{
    CapabilityId::capability_tc_tc_zl_tclk0,
    CapabilityId::capability_tc_tc_zl_tclk1,
    CapabilityId::capability_tc_tc_zl_tclk11,
    CapabilityId::capability_tc_tc_zl_tioa0,
    CapabilityId::capability_tc_tc_zl_tioa1,
    CapabilityId::capability_tc_tc_zl_tioa11,
    CapabilityId::capability_tc_tc_zl_tioa2,
    CapabilityId::capability_tc_tc_zl_tiob0,
    CapabilityId::capability_tc_tc_zl_tiob1,
    CapabilityId::capability_tc_tc_zl_tiob11,
    CapabilityId::capability_tc_tc_zl_tiob2,
    CapabilityId::runtime_support_timer,
    CapabilityId::runtime_dma_TC0_XDMAC_PERID_40_RX,
    CapabilityId::capability_instance_tc0_lqfp100_tclk0,
    CapabilityId::capability_instance_tc0_lqfp100_tclk1,
    CapabilityId::capability_instance_tc0_lqfp100_tioa0,
    CapabilityId::capability_instance_tc0_lqfp100_tioa1,
    CapabilityId::capability_instance_tc0_lqfp100_tioa2,
    CapabilityId::capability_instance_tc0_lqfp100_tiob0,
    CapabilityId::capability_instance_tc0_lqfp100_tiob1,
    CapabilityId::capability_instance_tc0_lqfp100_tiob2,
    CapabilityId::runtime_dma_TC1_XDMAC_PERID_41_RX,
    CapabilityId::runtime_dma_TC2_XDMAC_PERID_42_RX,
    CapabilityId::runtime_dma_TC3_XDMAC_PERID_43_RX,
    CapabilityId::capability_instance_tc3_lqfp100_tclk11,
    CapabilityId::capability_instance_tc3_lqfp100_tioa11,
    CapabilityId::capability_instance_tc3_lqfp100_tiob11,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_uart> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 83> kCapabilityIds = {{
    CapabilityId::capability_usart_usart_zw_cts,
    CapabilityId::capability_usart_usart_zw_dcd0,
    CapabilityId::capability_usart_usart_zw_dcd1,
    CapabilityId::capability_usart_usart_zw_dcd2,
    CapabilityId::capability_usart_usart_zw_dsr0,
    CapabilityId::capability_usart_usart_zw_dsr1,
    CapabilityId::capability_usart_usart_zw_dsr2,
    CapabilityId::capability_usart_usart_zw_dtr0,
    CapabilityId::capability_usart_usart_zw_dtr1,
    CapabilityId::capability_usart_usart_zw_dtr2,
    CapabilityId::capability_usart_usart_zw_loncol1,
    CapabilityId::capability_usart_usart_zw_ri0,
    CapabilityId::capability_usart_usart_zw_ri2,
    CapabilityId::capability_usart_usart_zw_rts,
    CapabilityId::capability_usart_usart_zw_rx,
    CapabilityId::capability_usart_usart_zw_sck0,
    CapabilityId::capability_usart_usart_zw_sck1,
    CapabilityId::capability_usart_usart_zw_sck2,
    CapabilityId::capability_usart_usart_zw_tx,
    CapabilityId::capability_uart_uart_r_urxd0,
    CapabilityId::capability_uart_uart_r_urxd1,
    CapabilityId::capability_uart_uart_r_urxd2,
    CapabilityId::capability_uart_uart_r_urxd3,
    CapabilityId::capability_uart_uart_r_urxd4,
    CapabilityId::capability_uart_uart_r_utxd0,
    CapabilityId::capability_uart_uart_r_utxd1,
    CapabilityId::capability_uart_uart_r_utxd2,
    CapabilityId::capability_uart_uart_r_utxd3,
    CapabilityId::capability_uart_uart_r_utxd4,
    CapabilityId::runtime_support_uart,
    CapabilityId::runtime_dma_UART0_XDMAC_PERID_21_RX,
    CapabilityId::runtime_dma_UART0_XDMAC_PERID_20_TX,
    CapabilityId::capability_instance_uart0_lqfp100_urxd0,
    CapabilityId::capability_instance_uart0_lqfp100_utxd0,
    CapabilityId::runtime_dma_UART1_XDMAC_PERID_23_RX,
    CapabilityId::runtime_dma_UART1_XDMAC_PERID_22_TX,
    CapabilityId::capability_instance_uart1_lqfp100_urxd1,
    CapabilityId::capability_instance_uart1_lqfp100_utxd1,
    CapabilityId::runtime_dma_UART2_XDMAC_PERID_25_RX,
    CapabilityId::runtime_dma_UART2_XDMAC_PERID_24_TX,
    CapabilityId::capability_instance_uart2_lqfp100_urxd2,
    CapabilityId::capability_instance_uart2_lqfp100_utxd2,
    CapabilityId::runtime_dma_UART3_XDMAC_PERID_27_RX,
    CapabilityId::runtime_dma_UART3_XDMAC_PERID_26_TX,
    CapabilityId::capability_instance_uart3_lqfp100_urxd3,
    CapabilityId::capability_instance_uart3_lqfp100_utxd3,
    CapabilityId::runtime_dma_UART4_XDMAC_PERID_29_RX,
    CapabilityId::runtime_dma_UART4_XDMAC_PERID_28_TX,
    CapabilityId::capability_instance_uart4_lqfp100_urxd4,
    CapabilityId::capability_instance_uart4_lqfp100_utxd4,
    CapabilityId::runtime_dma_USART0_XDMAC_PERID_8_RX,
    CapabilityId::runtime_dma_USART0_XDMAC_PERID_7_TX,
    CapabilityId::capability_instance_usart0_lqfp100_cts,
    CapabilityId::capability_instance_usart0_lqfp100_dcd0,
    CapabilityId::capability_instance_usart0_lqfp100_dsr0,
    CapabilityId::capability_instance_usart0_lqfp100_dtr0,
    CapabilityId::capability_instance_usart0_lqfp100_ri0,
    CapabilityId::capability_instance_usart0_lqfp100_rts,
    CapabilityId::capability_instance_usart0_lqfp100_rx,
    CapabilityId::capability_instance_usart0_lqfp100_sck0,
    CapabilityId::capability_instance_usart0_lqfp100_tx,
    CapabilityId::runtime_dma_USART1_XDMAC_PERID_10_RX,
    CapabilityId::runtime_dma_USART1_XDMAC_PERID_9_TX,
    CapabilityId::capability_instance_usart1_lqfp100_cts,
    CapabilityId::capability_instance_usart1_lqfp100_dcd1,
    CapabilityId::capability_instance_usart1_lqfp100_dsr1,
    CapabilityId::capability_instance_usart1_lqfp100_dtr1,
    CapabilityId::capability_instance_usart1_lqfp100_loncol1,
    CapabilityId::capability_instance_usart1_lqfp100_rts,
    CapabilityId::capability_instance_usart1_lqfp100_rx,
    CapabilityId::capability_instance_usart1_lqfp100_sck1,
    CapabilityId::capability_instance_usart1_lqfp100_tx,
    CapabilityId::runtime_dma_USART2_XDMAC_PERID_12_RX,
    CapabilityId::runtime_dma_USART2_XDMAC_PERID_11_TX,
    CapabilityId::capability_instance_usart2_lqfp100_cts,
    CapabilityId::capability_instance_usart2_lqfp100_dcd2,
    CapabilityId::capability_instance_usart2_lqfp100_dsr2,
    CapabilityId::capability_instance_usart2_lqfp100_dtr2,
    CapabilityId::capability_instance_usart2_lqfp100_ri2,
    CapabilityId::capability_instance_usart2_lqfp100_rts,
    CapabilityId::capability_instance_usart2_lqfp100_rx,
    CapabilityId::capability_instance_usart2_lqfp100_sck2,
    CapabilityId::capability_instance_usart2_lqfp100_tx,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_usb> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_usb,
  }};
};

template<>
struct PeripheralClassCapabilityTraits<PeripheralClassId::class_watchdog> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_support_watchdog,
  }};
};

template<PeripheralId Id>
struct PeripheralCapabilityTraits {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::AFEC0> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 11> kCapabilityIds = {{
    CapabilityId::runtime_dma_AFEC0_XDMAC_PERID_35_RX,
    CapabilityId::capability_instance_afec0_lqfp100_ad0,
    CapabilityId::capability_instance_afec0_lqfp100_ad1,
    CapabilityId::capability_instance_afec0_lqfp100_ad10,
    CapabilityId::capability_instance_afec0_lqfp100_ad2,
    CapabilityId::capability_instance_afec0_lqfp100_ad5,
    CapabilityId::capability_instance_afec0_lqfp100_ad6,
    CapabilityId::capability_instance_afec0_lqfp100_ad7,
    CapabilityId::capability_instance_afec0_lqfp100_ad8,
    CapabilityId::capability_instance_afec0_lqfp100_ad9,
    CapabilityId::capability_instance_afec0_lqfp100_adtrg,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::AFEC1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 3> kCapabilityIds = {{
    CapabilityId::runtime_dma_AFEC1_XDMAC_PERID_36_RX,
    CapabilityId::capability_instance_afec1_lqfp100_ad0,
    CapabilityId::capability_instance_afec1_lqfp100_adtrg,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::DACC> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 5> kCapabilityIds = {{
    CapabilityId::runtime_dma_DACC_XDMAC_PERID_30_CH0_TX,
    CapabilityId::runtime_dma_DACC_XDMAC_PERID_31_CH1_TX,
    CapabilityId::capability_instance_dacc_lqfp100_dac0,
    CapabilityId::capability_instance_dacc_lqfp100_dac1,
    CapabilityId::capability_instance_dacc_lqfp100_datrg,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::GMAC> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 19> kCapabilityIds = {{
    CapabilityId::capability_instance_gmac_lqfp100_gcol,
    CapabilityId::capability_instance_gmac_lqfp100_gcrs,
    CapabilityId::capability_instance_gmac_lqfp100_gmdc,
    CapabilityId::capability_instance_gmac_lqfp100_gmdio,
    CapabilityId::capability_instance_gmac_lqfp100_grx0,
    CapabilityId::capability_instance_gmac_lqfp100_grx1,
    CapabilityId::capability_instance_gmac_lqfp100_grx2,
    CapabilityId::capability_instance_gmac_lqfp100_grx3,
    CapabilityId::capability_instance_gmac_lqfp100_grxck,
    CapabilityId::capability_instance_gmac_lqfp100_grxdv,
    CapabilityId::capability_instance_gmac_lqfp100_grxer,
    CapabilityId::capability_instance_gmac_lqfp100_gtsucomp,
    CapabilityId::capability_instance_gmac_lqfp100_gtx0,
    CapabilityId::capability_instance_gmac_lqfp100_gtx1,
    CapabilityId::capability_instance_gmac_lqfp100_gtx2,
    CapabilityId::capability_instance_gmac_lqfp100_gtx3,
    CapabilityId::capability_instance_gmac_lqfp100_gtxck,
    CapabilityId::capability_instance_gmac_lqfp100_gtxen,
    CapabilityId::capability_instance_gmac_lqfp100_gtxer,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::GPIOA> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 12> kCapabilityIds = {{
    CapabilityId::runtime_dma_GPIOA_XDMAC_PERID_34_RX,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc0,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc1,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc2,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc3,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc4,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc5,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc6,
    CapabilityId::capability_instance_gpioa_lqfp100_piodc7,
    CapabilityId::capability_instance_gpioa_lqfp100_piodcclk,
    CapabilityId::capability_instance_gpioa_lqfp100_piodcen1,
    CapabilityId::capability_instance_gpioa_lqfp100_piodcen2,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::GPIOB> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::GPIOD> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::HSMCI> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 7> kCapabilityIds = {{
    CapabilityId::runtime_dma_HSMCI_XDMAC_PERID_0_RX,
    CapabilityId::capability_instance_hsmci_lqfp100_mccda,
    CapabilityId::capability_instance_hsmci_lqfp100_mcck,
    CapabilityId::capability_instance_hsmci_lqfp100_mcda0,
    CapabilityId::capability_instance_hsmci_lqfp100_mcda1,
    CapabilityId::capability_instance_hsmci_lqfp100_mcda2,
    CapabilityId::capability_instance_hsmci_lqfp100_mcda3,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::MCAN0> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::capability_instance_mcan0_lqfp100_rx,
    CapabilityId::capability_instance_mcan0_lqfp100_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::MCAN1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::capability_instance_mcan1_lqfp100_rx,
    CapabilityId::capability_instance_mcan1_lqfp100_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::PWM0> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 14> kCapabilityIds = {{
    CapabilityId::runtime_dma_PWM0_XDMAC_PERID_13_TX,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmextrg0,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmextrg1,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmfi0,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmfi1,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmfi2,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmh0,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmh1,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmh2,
    CapabilityId::capability_instance_pwm0_lqfp100_pwmh3,
    CapabilityId::capability_instance_pwm0_lqfp100_pwml0,
    CapabilityId::capability_instance_pwm0_lqfp100_pwml1,
    CapabilityId::capability_instance_pwm0_lqfp100_pwml2,
    CapabilityId::capability_instance_pwm0_lqfp100_pwml3,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::PWM1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 14> kCapabilityIds = {{
    CapabilityId::runtime_dma_PWM1_XDMAC_PERID_39_TX,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmextrg0,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmextrg1,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmfi0,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmfi1,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmfi2,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmh0,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmh1,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmh2,
    CapabilityId::capability_instance_pwm1_lqfp100_pwmh3,
    CapabilityId::capability_instance_pwm1_lqfp100_pwml0,
    CapabilityId::capability_instance_pwm1_lqfp100_pwml1,
    CapabilityId::capability_instance_pwm1_lqfp100_pwml2,
    CapabilityId::capability_instance_pwm1_lqfp100_pwml3,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::QSPI> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 8> kCapabilityIds = {{
    CapabilityId::runtime_dma_QSPI_XDMAC_PERID_6_RX,
    CapabilityId::runtime_dma_QSPI_XDMAC_PERID_5_TX,
    CapabilityId::capability_instance_qspi_lqfp100_qcs,
    CapabilityId::capability_instance_qspi_lqfp100_qio0,
    CapabilityId::capability_instance_qspi_lqfp100_qio1,
    CapabilityId::capability_instance_qspi_lqfp100_qio2,
    CapabilityId::capability_instance_qspi_lqfp100_qio3,
    CapabilityId::capability_instance_qspi_lqfp100_qsck,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::RSWDT> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::RTC> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 2> kCapabilityIds = {{
    CapabilityId::capability_instance_rtc_lqfp100_rtcout0,
    CapabilityId::capability_instance_rtc_lqfp100_rtcout1,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::SPI0> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 6> kCapabilityIds = {{
    CapabilityId::runtime_dma_SPI0_XDMAC_PERID_2_RX,
    CapabilityId::runtime_dma_SPI0_XDMAC_PERID_1_TX,
    CapabilityId::capability_instance_spi0_lqfp100_cs,
    CapabilityId::capability_instance_spi0_lqfp100_miso,
    CapabilityId::capability_instance_spi0_lqfp100_mosi,
    CapabilityId::capability_instance_spi0_lqfp100_sck,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::TC0> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 9> kCapabilityIds = {{
    CapabilityId::runtime_dma_TC0_XDMAC_PERID_40_RX,
    CapabilityId::capability_instance_tc0_lqfp100_tclk0,
    CapabilityId::capability_instance_tc0_lqfp100_tclk1,
    CapabilityId::capability_instance_tc0_lqfp100_tioa0,
    CapabilityId::capability_instance_tc0_lqfp100_tioa1,
    CapabilityId::capability_instance_tc0_lqfp100_tioa2,
    CapabilityId::capability_instance_tc0_lqfp100_tiob0,
    CapabilityId::capability_instance_tc0_lqfp100_tiob1,
    CapabilityId::capability_instance_tc0_lqfp100_tiob2,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::TC1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_dma_TC1_XDMAC_PERID_41_RX,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::TC2> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 1> kCapabilityIds = {{
    CapabilityId::runtime_dma_TC2_XDMAC_PERID_42_RX,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::TC3> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 4> kCapabilityIds = {{
    CapabilityId::runtime_dma_TC3_XDMAC_PERID_43_RX,
    CapabilityId::capability_instance_tc3_lqfp100_tclk11,
    CapabilityId::capability_instance_tc3_lqfp100_tioa11,
    CapabilityId::capability_instance_tc3_lqfp100_tiob11,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::TWIHS0> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 4> kCapabilityIds = {{
    CapabilityId::runtime_dma_TWIHS0_XDMAC_PERID_15_RX,
    CapabilityId::runtime_dma_TWIHS0_XDMAC_PERID_14_TX,
    CapabilityId::capability_instance_twihs0_lqfp100_scl,
    CapabilityId::capability_instance_twihs0_lqfp100_sda,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::TWIHS1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 4> kCapabilityIds = {{
    CapabilityId::runtime_dma_TWIHS1_XDMAC_PERID_17_RX,
    CapabilityId::runtime_dma_TWIHS1_XDMAC_PERID_16_TX,
    CapabilityId::capability_instance_twihs1_lqfp100_scl,
    CapabilityId::capability_instance_twihs1_lqfp100_sda,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::TWIHS2> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 4> kCapabilityIds = {{
    CapabilityId::runtime_dma_TWIHS2_XDMAC_PERID_19_RX,
    CapabilityId::runtime_dma_TWIHS2_XDMAC_PERID_18_TX,
    CapabilityId::capability_instance_twihs2_lqfp100_scl,
    CapabilityId::capability_instance_twihs2_lqfp100_sda,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::UART0> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 4> kCapabilityIds = {{
    CapabilityId::runtime_dma_UART0_XDMAC_PERID_21_RX,
    CapabilityId::runtime_dma_UART0_XDMAC_PERID_20_TX,
    CapabilityId::capability_instance_uart0_lqfp100_urxd0,
    CapabilityId::capability_instance_uart0_lqfp100_utxd0,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::UART1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 4> kCapabilityIds = {{
    CapabilityId::runtime_dma_UART1_XDMAC_PERID_23_RX,
    CapabilityId::runtime_dma_UART1_XDMAC_PERID_22_TX,
    CapabilityId::capability_instance_uart1_lqfp100_urxd1,
    CapabilityId::capability_instance_uart1_lqfp100_utxd1,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::UART2> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 4> kCapabilityIds = {{
    CapabilityId::runtime_dma_UART2_XDMAC_PERID_25_RX,
    CapabilityId::runtime_dma_UART2_XDMAC_PERID_24_TX,
    CapabilityId::capability_instance_uart2_lqfp100_urxd2,
    CapabilityId::capability_instance_uart2_lqfp100_utxd2,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::UART3> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 4> kCapabilityIds = {{
    CapabilityId::runtime_dma_UART3_XDMAC_PERID_27_RX,
    CapabilityId::runtime_dma_UART3_XDMAC_PERID_26_TX,
    CapabilityId::capability_instance_uart3_lqfp100_urxd3,
    CapabilityId::capability_instance_uart3_lqfp100_utxd3,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::UART4> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 4> kCapabilityIds = {{
    CapabilityId::runtime_dma_UART4_XDMAC_PERID_29_RX,
    CapabilityId::runtime_dma_UART4_XDMAC_PERID_28_TX,
    CapabilityId::capability_instance_uart4_lqfp100_urxd4,
    CapabilityId::capability_instance_uart4_lqfp100_utxd4,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::USART0> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 11> kCapabilityIds = {{
    CapabilityId::runtime_dma_USART0_XDMAC_PERID_8_RX,
    CapabilityId::runtime_dma_USART0_XDMAC_PERID_7_TX,
    CapabilityId::capability_instance_usart0_lqfp100_cts,
    CapabilityId::capability_instance_usart0_lqfp100_dcd0,
    CapabilityId::capability_instance_usart0_lqfp100_dsr0,
    CapabilityId::capability_instance_usart0_lqfp100_dtr0,
    CapabilityId::capability_instance_usart0_lqfp100_ri0,
    CapabilityId::capability_instance_usart0_lqfp100_rts,
    CapabilityId::capability_instance_usart0_lqfp100_rx,
    CapabilityId::capability_instance_usart0_lqfp100_sck0,
    CapabilityId::capability_instance_usart0_lqfp100_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::USART1> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 11> kCapabilityIds = {{
    CapabilityId::runtime_dma_USART1_XDMAC_PERID_10_RX,
    CapabilityId::runtime_dma_USART1_XDMAC_PERID_9_TX,
    CapabilityId::capability_instance_usart1_lqfp100_cts,
    CapabilityId::capability_instance_usart1_lqfp100_dcd1,
    CapabilityId::capability_instance_usart1_lqfp100_dsr1,
    CapabilityId::capability_instance_usart1_lqfp100_dtr1,
    CapabilityId::capability_instance_usart1_lqfp100_loncol1,
    CapabilityId::capability_instance_usart1_lqfp100_rts,
    CapabilityId::capability_instance_usart1_lqfp100_rx,
    CapabilityId::capability_instance_usart1_lqfp100_sck1,
    CapabilityId::capability_instance_usart1_lqfp100_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::USART2> {
  static constexpr bool kPresent = true;
  inline static constexpr std::array<CapabilityId, 11> kCapabilityIds = {{
    CapabilityId::runtime_dma_USART2_XDMAC_PERID_12_RX,
    CapabilityId::runtime_dma_USART2_XDMAC_PERID_11_TX,
    CapabilityId::capability_instance_usart2_lqfp100_cts,
    CapabilityId::capability_instance_usart2_lqfp100_dcd2,
    CapabilityId::capability_instance_usart2_lqfp100_dsr2,
    CapabilityId::capability_instance_usart2_lqfp100_dtr2,
    CapabilityId::capability_instance_usart2_lqfp100_ri2,
    CapabilityId::capability_instance_usart2_lqfp100_rts,
    CapabilityId::capability_instance_usart2_lqfp100_rx,
    CapabilityId::capability_instance_usart2_lqfp100_sck2,
    CapabilityId::capability_instance_usart2_lqfp100_tx,
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::USBHS> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::WDT> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

template<>
struct PeripheralCapabilityTraits<PeripheralId::XDMAC> {
  static constexpr bool kPresent = false;
  inline static constexpr std::array<CapabilityId, 0> kCapabilityIds = {{
  }};
};

}
}
}
}
}
}
