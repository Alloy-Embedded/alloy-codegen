#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "routes.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70n21b {
enum class ConnectorId : std::uint16_t {
  none,
  candidate_pa0_pwm0_pwmh0,
  candidate_pa0_tc0_tioa0,
  candidate_pa10_gpioa_piodc4,
  candidate_pa10_pwm0_pwmextrg0,
  candidate_pa10_uart0_utxd0,
  candidate_pa11_gpioa_piodc5,
  candidate_pa11_pwm0_pwmh0,
  candidate_pa11_pwm1_pwml0,
  candidate_pa11_qspi_qcs,
  candidate_pa12_gpioa_piodc6,
  candidate_pa12_pwm0_pwmh1,
  candidate_pa12_pwm1_pwmh0,
  candidate_pa12_qspi_qio1,
  candidate_pa13_gpioa_piodc7,
  candidate_pa13_pwm0_pwmh2,
  candidate_pa13_pwm1_pwml1,
  candidate_pa13_qspi_qio0,
  candidate_pa14_gpioa_piodcen1,
  candidate_pa14_pwm0_pwmh3,
  candidate_pa14_pwm1_pwmh1,
  candidate_pa14_qspi_qsck,
  candidate_pa15_pwm0_pwml3,
  candidate_pa15_tc0_tioa1,
  candidate_pa16_pwm0_pwml2,
  candidate_pa16_tc0_tiob1,
  candidate_pa17_afec0_ad6,
  candidate_pa17_pwm0_pwmh3,
  candidate_pa17_qspi_qio2,
  candidate_pa18_afec0_ad7,
  candidate_pa18_pwm1_pwmextrg1,
  candidate_pa19_afec0_ad8,
  candidate_pa19_pwm0_pwml0,
  candidate_pa1_pwm0_pwml0,
  candidate_pa1_tc0_tiob0,
  candidate_pa20_afec0_ad9,
  candidate_pa20_pwm0_pwml1,
  candidate_pa21_afec0_ad1,
  candidate_pa21_gpioa_piodcen2,
  candidate_pa21_pwm1_pwmfi0,
  candidate_pa21_usart1_rxd1,
  candidate_pa22_gpioa_piodcclk,
  candidate_pa22_pwm0_pwmextrg1,
  candidate_pa23_pwm0_pwmh0,
  candidate_pa23_pwm1_pwml2,
  candidate_pa23_usart1_sck1,
  candidate_pa24_pwm0_pwmh1,
  candidate_pa24_usart1_rts1,
  candidate_pa25_hsmci_mcck,
  candidate_pa25_pwm0_pwmh2,
  candidate_pa25_usart1_cts1,
  candidate_pa26_hsmci_mcda2,
  candidate_pa26_pwm1_pwmfi1,
  candidate_pa26_tc0_tioa2,
  candidate_pa26_usart1_dcd1,
  candidate_pa27_hsmci_mcda3,
  candidate_pa27_tc0_tiob2,
  candidate_pa27_usart1_dtr1,
  candidate_pa28_hsmci_mccda,
  candidate_pa28_pwm1_pwmfi2,
  candidate_pa28_tc0_tclk1,
  candidate_pa28_usart1_dsr1,
  candidate_pa2_dacc_datrg,
  candidate_pa2_pwm0_pwmh1,
  candidate_pa30_hsmci_mcda0,
  candidate_pa30_pwm0_pwml2,
  candidate_pa30_pwm1_pwmextrg0,
  candidate_pa31_hsmci_mcda1,
  candidate_pa31_pwm1_pwmh2,
  candidate_pa31_spi0_npcs1,
  candidate_pa3_gpioa_piodc0,
  candidate_pa3_twihs0_twd0,
  candidate_pa3_usart1_loncol1,
  candidate_pa4_gpioa_piodc1,
  candidate_pa4_tc0_tclk0,
  candidate_pa4_twihs0_twck0,
  candidate_pa4_uart1_utxd1,
  candidate_pa5_gpioa_piodc2,
  candidate_pa5_pwm1_pwml3,
  candidate_pa5_uart1_urxd1,
  candidate_pa7_pwm0_pwmh3,
  candidate_pa8_afec0_adtrg,
  candidate_pa8_pwm1_pwmh3,
  candidate_pa9_gpioa_piodc3,
  candidate_pa9_pwm0_pwmfi0,
  candidate_pa9_uart0_urxd0,
  candidate_pb0_afec0_ad10,
  candidate_pb0_pwm0_pwmh0,
  candidate_pb0_rtc_rtcout0,
  candidate_pb0_usart0_rxd0,
  candidate_pb12_gmac_gtsucomp,
  candidate_pb12_pwm0_pwml1,
  candidate_pb13_dacc_dac0,
  candidate_pb13_pwm0_pwml2,
  candidate_pb13_usart0_sck0,
  candidate_pb1_afec1_ad0,
  candidate_pb1_gmac_gtsucomp,
  candidate_pb1_pwm0_pwmh1,
  candidate_pb1_rtc_rtcout1,
  candidate_pb1_usart0_txd0,
  candidate_pb2_afec0_ad5,
  candidate_pb2_mcan0_cantx0,
  candidate_pb2_spi0_npcs0,
  candidate_pb2_usart0_cts0,
  candidate_pb3_afec0_ad2,
  candidate_pb3_mcan0_canrx0,
  candidate_pb3_usart0_rts0,
  candidate_pb4_pwm0_pwmh2,
  candidate_pb4_twihs1_twd1,
  candidate_pb4_usart1_txd1,
  candidate_pb5_pwm0_pwml0,
  candidate_pb5_twihs1_twck1,
  candidate_pd0_dacc_dac1,
  candidate_pd0_gmac_gtxck,
  candidate_pd0_pwm1_pwml0,
  candidate_pd0_usart0_dcd0,
  candidate_pd10_gmac_gcrs,
  candidate_pd10_pwm0_pwml0,
  candidate_pd11_gmac_grx2,
  candidate_pd11_gmac_gtsucomp,
  candidate_pd11_pwm0_pwmh0,
  candidate_pd12_gmac_grx3,
  candidate_pd12_mcan1_cantx1,
  candidate_pd12_spi0_npcs2,
  candidate_pd13_gmac_gcol,
  candidate_pd14_gmac_grxck,
  candidate_pd15_gmac_gtx2,
  candidate_pd15_usart2_rxd2,
  candidate_pd16_gmac_gtx3,
  candidate_pd16_usart2_txd2,
  candidate_pd17_gmac_gtxer,
  candidate_pd17_usart2_sck2,
  candidate_pd18_uart4_urxd4,
  candidate_pd18_usart2_rts2,
  candidate_pd19_uart4_utxd4,
  candidate_pd19_usart2_cts2,
  candidate_pd1_gmac_gtxen,
  candidate_pd1_pwm1_pwmh0,
  candidate_pd1_usart0_dtr0,
  candidate_pd20_gmac_gtsucomp,
  candidate_pd20_pwm0_pwmh0,
  candidate_pd20_spi0_miso,
  candidate_pd21_pwm0_pwmh1,
  candidate_pd21_spi0_mosi,
  candidate_pd21_tc3_tioa11,
  candidate_pd22_pwm0_pwmh2,
  candidate_pd22_spi0_spck,
  candidate_pd22_tc3_tiob11,
  candidate_pd24_pwm0_pwml0,
  candidate_pd24_tc3_tclk11,
  candidate_pd25_pwm0_pwml1,
  candidate_pd25_spi0_npcs1,
  candidate_pd25_uart2_urxd2,
  candidate_pd26_pwm0_pwml2,
  candidate_pd26_uart1_utxd1,
  candidate_pd26_uart2_utxd2,
  candidate_pd27_pwm0_pwml3,
  candidate_pd27_spi0_npcs3,
  candidate_pd27_twihs2_twd2,
  candidate_pd28_mcan1_canrx1,
  candidate_pd28_twihs2_twck2,
  candidate_pd28_uart3_urxd3,
  candidate_pd2_gmac_gtx0,
  candidate_pd2_pwm1_pwml1,
  candidate_pd2_usart0_dsr0,
  candidate_pd30_afec0_ad0,
  candidate_pd30_uart3_utxd3,
  candidate_pd31_qspi_qio3,
  candidate_pd31_uart3_utxd3,
  candidate_pd3_gmac_gtx1,
  candidate_pd3_pwm1_pwmh1,
  candidate_pd3_uart4_utxd4,
  candidate_pd3_usart0_ri0,
  candidate_pd4_gmac_grxdv,
  candidate_pd4_pwm1_pwml2,
  candidate_pd4_usart2_dcd2,
  candidate_pd5_gmac_grx0,
  candidate_pd5_pwm1_pwmh2,
  candidate_pd5_usart2_dtr2,
  candidate_pd6_gmac_grx1,
  candidate_pd6_pwm1_pwml3,
  candidate_pd6_usart2_dsr2,
  candidate_pd7_gmac_grxer,
  candidate_pd7_pwm1_pwmh3,
  candidate_pd7_usart2_ri2,
  candidate_pd8_gmac_gmdc,
  candidate_pd8_pwm0_pwmfi1,
  candidate_pd9_afec1_adtrg,
  candidate_pd9_gmac_gmdio,
  candidate_pd9_pwm0_pwmfi2,
};

struct ConnectorDescriptor {
  ConnectorId connector_id;
  PinId pin_id;
  PeripheralId peripheral_id;
  SignalId signal_id;
  RouteId route_id;
  RouteKindId route_kind_id;
  ConnectionGroupId group_id;
};

template<PinId Pin, PeripheralId Peripheral, SignalId Signal>
struct ConnectorTraits {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

namespace detail {
template<auto Value>
inline constexpr bool kInvalidConnector = false;
}  // namespace detail

template<PeripheralId Peripheral, SignalId Signal>
struct ConnectorSignalTraits {
  static constexpr bool kPresent = false;
  static constexpr std::array<PinId, 0> kPins = {};
  static constexpr std::array<ConnectorId, 0> kConnectors = {};
};

template<>
struct ConnectorTraits<PinId::PA0, PeripheralId::PWM0, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa0_pwm0_pwmh0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa0_pwm0_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA0, PeripheralId::TC0, SignalId::signal_tioa0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa0_tc0_tioa0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa0_tc0_tioa0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_tc0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA10, PeripheralId::GPIOA, SignalId::signal_piodc4> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa10_gpioa_piodc4;
  static constexpr RouteId kRouteId = RouteId::candidate_pa10_gpioa_piodc4;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpioa_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA10, PeripheralId::PWM0, SignalId::signal_pwmextrg0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa10_pwm0_pwmextrg0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa10_pwm0_pwmextrg0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA10, PeripheralId::UART0, SignalId::signal_utxd0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa10_uart0_utxd0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa10_uart0_utxd0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA11, PeripheralId::GPIOA, SignalId::signal_piodc5> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa11_gpioa_piodc5;
  static constexpr RouteId kRouteId = RouteId::candidate_pa11_gpioa_piodc5;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpioa_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA11, PeripheralId::PWM0, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa11_pwm0_pwmh0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa11_pwm0_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA11, PeripheralId::PWM1, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa11_pwm1_pwml0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa11_pwm1_pwml0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA11, PeripheralId::QSPI, SignalId::signal_qcs> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa11_qspi_qcs;
  static constexpr RouteId kRouteId = RouteId::candidate_pa11_qspi_qcs;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_qspi_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA12, PeripheralId::GPIOA, SignalId::signal_piodc6> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa12_gpioa_piodc6;
  static constexpr RouteId kRouteId = RouteId::candidate_pa12_gpioa_piodc6;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpioa_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA12, PeripheralId::PWM0, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa12_pwm0_pwmh1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa12_pwm0_pwmh1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA12, PeripheralId::PWM1, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa12_pwm1_pwmh0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa12_pwm1_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA12, PeripheralId::QSPI, SignalId::signal_qio1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa12_qspi_qio1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa12_qspi_qio1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_qspi_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA13, PeripheralId::GPIOA, SignalId::signal_piodc7> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa13_gpioa_piodc7;
  static constexpr RouteId kRouteId = RouteId::candidate_pa13_gpioa_piodc7;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpioa_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA13, PeripheralId::PWM0, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa13_pwm0_pwmh2;
  static constexpr RouteId kRouteId = RouteId::candidate_pa13_pwm0_pwmh2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA13, PeripheralId::PWM1, SignalId::signal_pwml1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa13_pwm1_pwml1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa13_pwm1_pwml1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA13, PeripheralId::QSPI, SignalId::signal_qio0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa13_qspi_qio0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa13_qspi_qio0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_qspi_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA14, PeripheralId::GPIOA, SignalId::signal_piodcen1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa14_gpioa_piodcen1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa14_gpioa_piodcen1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpioa_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA14, PeripheralId::PWM0, SignalId::signal_pwmh3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa14_pwm0_pwmh3;
  static constexpr RouteId kRouteId = RouteId::candidate_pa14_pwm0_pwmh3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA14, PeripheralId::PWM1, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa14_pwm1_pwmh1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa14_pwm1_pwmh1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA14, PeripheralId::QSPI, SignalId::signal_qsck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa14_qspi_qsck;
  static constexpr RouteId kRouteId = RouteId::candidate_pa14_qspi_qsck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_qspi_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA15, PeripheralId::PWM0, SignalId::signal_pwml3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa15_pwm0_pwml3;
  static constexpr RouteId kRouteId = RouteId::candidate_pa15_pwm0_pwml3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA15, PeripheralId::TC0, SignalId::signal_tioa1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa15_tc0_tioa1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa15_tc0_tioa1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_tc0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA16, PeripheralId::PWM0, SignalId::signal_pwml2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa16_pwm0_pwml2;
  static constexpr RouteId kRouteId = RouteId::candidate_pa16_pwm0_pwml2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA16, PeripheralId::TC0, SignalId::signal_tiob1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa16_tc0_tiob1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa16_tc0_tiob1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_tc0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA17, PeripheralId::AFEC0, SignalId::signal_ad6> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa17_afec0_ad6;
  static constexpr RouteId kRouteId = RouteId::candidate_pa17_afec0_ad6;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_afec0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA17, PeripheralId::PWM0, SignalId::signal_pwmh3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa17_pwm0_pwmh3;
  static constexpr RouteId kRouteId = RouteId::candidate_pa17_pwm0_pwmh3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA17, PeripheralId::QSPI, SignalId::signal_qio2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa17_qspi_qio2;
  static constexpr RouteId kRouteId = RouteId::candidate_pa17_qspi_qio2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_qspi_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA18, PeripheralId::AFEC0, SignalId::signal_ad7> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa18_afec0_ad7;
  static constexpr RouteId kRouteId = RouteId::candidate_pa18_afec0_ad7;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_afec0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA18, PeripheralId::PWM1, SignalId::signal_pwmextrg1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa18_pwm1_pwmextrg1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa18_pwm1_pwmextrg1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA19, PeripheralId::AFEC0, SignalId::signal_ad8> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa19_afec0_ad8;
  static constexpr RouteId kRouteId = RouteId::candidate_pa19_afec0_ad8;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_afec0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA19, PeripheralId::PWM0, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa19_pwm0_pwml0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa19_pwm0_pwml0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA1, PeripheralId::PWM0, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa1_pwm0_pwml0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa1_pwm0_pwml0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA1, PeripheralId::TC0, SignalId::signal_tiob0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa1_tc0_tiob0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa1_tc0_tiob0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_tc0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA20, PeripheralId::AFEC0, SignalId::signal_ad9> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa20_afec0_ad9;
  static constexpr RouteId kRouteId = RouteId::candidate_pa20_afec0_ad9;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_afec0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA20, PeripheralId::PWM0, SignalId::signal_pwml1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa20_pwm0_pwml1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa20_pwm0_pwml1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA21, PeripheralId::AFEC0, SignalId::signal_ad1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa21_afec0_ad1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa21_afec0_ad1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_afec0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA21, PeripheralId::GPIOA, SignalId::signal_piodcen2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa21_gpioa_piodcen2;
  static constexpr RouteId kRouteId = RouteId::candidate_pa21_gpioa_piodcen2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpioa_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA21, PeripheralId::PWM1, SignalId::signal_pwmfi0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa21_pwm1_pwmfi0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa21_pwm1_pwmfi0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA21, PeripheralId::USART1, SignalId::signal_rxd1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa21_usart1_rxd1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa21_usart1_rxd1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart1_lqfp100_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PA22, PeripheralId::GPIOA, SignalId::signal_piodcclk> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa22_gpioa_piodcclk;
  static constexpr RouteId kRouteId = RouteId::candidate_pa22_gpioa_piodcclk;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpioa_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA22, PeripheralId::PWM0, SignalId::signal_pwmextrg1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa22_pwm0_pwmextrg1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa22_pwm0_pwmextrg1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA23, PeripheralId::PWM0, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa23_pwm0_pwmh0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa23_pwm0_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA23, PeripheralId::PWM1, SignalId::signal_pwml2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa23_pwm1_pwml2;
  static constexpr RouteId kRouteId = RouteId::candidate_pa23_pwm1_pwml2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA23, PeripheralId::USART1, SignalId::signal_sck1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa23_usart1_sck1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa23_usart1_sck1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PA24, PeripheralId::PWM0, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa24_pwm0_pwmh1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa24_pwm0_pwmh1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA24, PeripheralId::USART1, SignalId::signal_rts1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa24_usart1_rts1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa24_usart1_rts1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart1_lqfp100_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::PA25, PeripheralId::HSMCI, SignalId::signal_mcck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa25_hsmci_mcck;
  static constexpr RouteId kRouteId = RouteId::candidate_pa25_hsmci_mcck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_hsmci_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA25, PeripheralId::PWM0, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa25_pwm0_pwmh2;
  static constexpr RouteId kRouteId = RouteId::candidate_pa25_pwm0_pwmh2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA25, PeripheralId::USART1, SignalId::signal_cts1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa25_usart1_cts1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa25_usart1_cts1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart1_lqfp100_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::PA26, PeripheralId::HSMCI, SignalId::signal_mcda2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa26_hsmci_mcda2;
  static constexpr RouteId kRouteId = RouteId::candidate_pa26_hsmci_mcda2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_hsmci_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA26, PeripheralId::PWM1, SignalId::signal_pwmfi1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa26_pwm1_pwmfi1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa26_pwm1_pwmfi1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA26, PeripheralId::TC0, SignalId::signal_tioa2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa26_tc0_tioa2;
  static constexpr RouteId kRouteId = RouteId::candidate_pa26_tc0_tioa2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_tc0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA26, PeripheralId::USART1, SignalId::signal_dcd1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa26_usart1_dcd1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa26_usart1_dcd1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PA27, PeripheralId::HSMCI, SignalId::signal_mcda3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa27_hsmci_mcda3;
  static constexpr RouteId kRouteId = RouteId::candidate_pa27_hsmci_mcda3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_hsmci_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA27, PeripheralId::TC0, SignalId::signal_tiob2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa27_tc0_tiob2;
  static constexpr RouteId kRouteId = RouteId::candidate_pa27_tc0_tiob2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_tc0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA27, PeripheralId::USART1, SignalId::signal_dtr1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa27_usart1_dtr1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa27_usart1_dtr1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PA28, PeripheralId::HSMCI, SignalId::signal_mccda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa28_hsmci_mccda;
  static constexpr RouteId kRouteId = RouteId::candidate_pa28_hsmci_mccda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_hsmci_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA28, PeripheralId::PWM1, SignalId::signal_pwmfi2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa28_pwm1_pwmfi2;
  static constexpr RouteId kRouteId = RouteId::candidate_pa28_pwm1_pwmfi2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA28, PeripheralId::TC0, SignalId::signal_tclk1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa28_tc0_tclk1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa28_tc0_tclk1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_tc0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA28, PeripheralId::USART1, SignalId::signal_dsr1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa28_usart1_dsr1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa28_usart1_dsr1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PA2, PeripheralId::DACC, SignalId::signal_datrg> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa2_dacc_datrg;
  static constexpr RouteId kRouteId = RouteId::candidate_pa2_dacc_datrg;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_dacc_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA2, PeripheralId::PWM0, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa2_pwm0_pwmh1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa2_pwm0_pwmh1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA30, PeripheralId::HSMCI, SignalId::signal_mcda0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa30_hsmci_mcda0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa30_hsmci_mcda0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_hsmci_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA30, PeripheralId::PWM0, SignalId::signal_pwml2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa30_pwm0_pwml2;
  static constexpr RouteId kRouteId = RouteId::candidate_pa30_pwm0_pwml2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA30, PeripheralId::PWM1, SignalId::signal_pwmextrg0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa30_pwm1_pwmextrg0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa30_pwm1_pwmextrg0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA31, PeripheralId::HSMCI, SignalId::signal_mcda1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa31_hsmci_mcda1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa31_hsmci_mcda1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_hsmci_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA31, PeripheralId::PWM1, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa31_pwm1_pwmh2;
  static constexpr RouteId kRouteId = RouteId::candidate_pa31_pwm1_pwmh2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA31, PeripheralId::SPI0, SignalId::signal_npcs1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa31_spi0_npcs1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa31_spi0_npcs1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_lqfp100_sck_cs;
};

template<>
struct ConnectorTraits<PinId::PA3, PeripheralId::GPIOA, SignalId::signal_piodc0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa3_gpioa_piodc0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa3_gpioa_piodc0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpioa_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA3, PeripheralId::TWIHS0, SignalId::signal_twd0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa3_twihs0_twd0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa3_twihs0_twd0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_twihs0_lqfp100_scl_sda;
};

template<>
struct ConnectorTraits<PinId::PA3, PeripheralId::USART1, SignalId::signal_loncol1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa3_usart1_loncol1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa3_usart1_loncol1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PA4, PeripheralId::GPIOA, SignalId::signal_piodc1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa4_gpioa_piodc1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa4_gpioa_piodc1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpioa_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA4, PeripheralId::TC0, SignalId::signal_tclk0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa4_tc0_tclk0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa4_tc0_tclk0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_tc0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA4, PeripheralId::TWIHS0, SignalId::signal_twck0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa4_twihs0_twck0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa4_twihs0_twck0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_twihs0_lqfp100_scl_sda;
};

template<>
struct ConnectorTraits<PinId::PA4, PeripheralId::UART1, SignalId::signal_utxd1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa4_uart1_utxd1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa4_uart1_utxd1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA5, PeripheralId::GPIOA, SignalId::signal_piodc2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa5_gpioa_piodc2;
  static constexpr RouteId kRouteId = RouteId::candidate_pa5_gpioa_piodc2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpioa_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA5, PeripheralId::PWM1, SignalId::signal_pwml3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa5_pwm1_pwml3;
  static constexpr RouteId kRouteId = RouteId::candidate_pa5_pwm1_pwml3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA5, PeripheralId::UART1, SignalId::signal_urxd1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa5_uart1_urxd1;
  static constexpr RouteId kRouteId = RouteId::candidate_pa5_uart1_urxd1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA7, PeripheralId::PWM0, SignalId::signal_pwmh3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa7_pwm0_pwmh3;
  static constexpr RouteId kRouteId = RouteId::candidate_pa7_pwm0_pwmh3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA8, PeripheralId::AFEC0, SignalId::signal_adtrg> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa8_afec0_adtrg;
  static constexpr RouteId kRouteId = RouteId::candidate_pa8_afec0_adtrg;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_afec0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA8, PeripheralId::PWM1, SignalId::signal_pwmh3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa8_pwm1_pwmh3;
  static constexpr RouteId kRouteId = RouteId::candidate_pa8_pwm1_pwmh3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA9, PeripheralId::GPIOA, SignalId::signal_piodc3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa9_gpioa_piodc3;
  static constexpr RouteId kRouteId = RouteId::candidate_pa9_gpioa_piodc3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpioa_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA9, PeripheralId::PWM0, SignalId::signal_pwmfi0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa9_pwm0_pwmfi0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa9_pwm0_pwmfi0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PA9, PeripheralId::UART0, SignalId::signal_urxd0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa9_uart0_urxd0;
  static constexpr RouteId kRouteId = RouteId::candidate_pa9_uart0_urxd0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB0, PeripheralId::AFEC0, SignalId::signal_ad10> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb0_afec0_ad10;
  static constexpr RouteId kRouteId = RouteId::candidate_pb0_afec0_ad10;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_afec0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB0, PeripheralId::PWM0, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb0_pwm0_pwmh0;
  static constexpr RouteId kRouteId = RouteId::candidate_pb0_pwm0_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB0, PeripheralId::RTC, SignalId::signal_rtcout0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb0_rtc_rtcout0;
  static constexpr RouteId kRouteId = RouteId::candidate_pb0_rtc_rtcout0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_rtc_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB0, PeripheralId::USART0, SignalId::signal_rxd0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb0_usart0_rxd0;
  static constexpr RouteId kRouteId = RouteId::candidate_pb0_usart0_rxd0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart0_lqfp100_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PB12, PeripheralId::GMAC, SignalId::signal_gtsucomp> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb12_gmac_gtsucomp;
  static constexpr RouteId kRouteId = RouteId::candidate_pb12_gmac_gtsucomp;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB12, PeripheralId::PWM0, SignalId::signal_pwml1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb12_pwm0_pwml1;
  static constexpr RouteId kRouteId = RouteId::candidate_pb12_pwm0_pwml1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB13, PeripheralId::DACC, SignalId::signal_dac0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb13_dacc_dac0;
  static constexpr RouteId kRouteId = RouteId::candidate_pb13_dacc_dac0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_dacc_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB13, PeripheralId::PWM0, SignalId::signal_pwml2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb13_pwm0_pwml2;
  static constexpr RouteId kRouteId = RouteId::candidate_pb13_pwm0_pwml2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB13, PeripheralId::USART0, SignalId::signal_sck0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb13_usart0_sck0;
  static constexpr RouteId kRouteId = RouteId::candidate_pb13_usart0_sck0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PB1, PeripheralId::AFEC1, SignalId::signal_ad0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb1_afec1_ad0;
  static constexpr RouteId kRouteId = RouteId::candidate_pb1_afec1_ad0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_afec1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB1, PeripheralId::GMAC, SignalId::signal_gtsucomp> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb1_gmac_gtsucomp;
  static constexpr RouteId kRouteId = RouteId::candidate_pb1_gmac_gtsucomp;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB1, PeripheralId::PWM0, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb1_pwm0_pwmh1;
  static constexpr RouteId kRouteId = RouteId::candidate_pb1_pwm0_pwmh1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB1, PeripheralId::RTC, SignalId::signal_rtcout1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb1_rtc_rtcout1;
  static constexpr RouteId kRouteId = RouteId::candidate_pb1_rtc_rtcout1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_rtc_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB1, PeripheralId::USART0, SignalId::signal_txd0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb1_usart0_txd0;
  static constexpr RouteId kRouteId = RouteId::candidate_pb1_usart0_txd0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart0_lqfp100_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PB2, PeripheralId::AFEC0, SignalId::signal_ad5> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb2_afec0_ad5;
  static constexpr RouteId kRouteId = RouteId::candidate_pb2_afec0_ad5;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_afec0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB2, PeripheralId::MCAN0, SignalId::signal_cantx0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb2_mcan0_cantx0;
  static constexpr RouteId kRouteId = RouteId::candidate_pb2_mcan0_cantx0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_mcan0_lqfp100_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PB2, PeripheralId::SPI0, SignalId::signal_npcs0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb2_spi0_npcs0;
  static constexpr RouteId kRouteId = RouteId::candidate_pb2_spi0_npcs0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_lqfp100_sck_cs;
};

template<>
struct ConnectorTraits<PinId::PB2, PeripheralId::USART0, SignalId::signal_cts0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb2_usart0_cts0;
  static constexpr RouteId kRouteId = RouteId::candidate_pb2_usart0_cts0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart0_lqfp100_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::PB3, PeripheralId::AFEC0, SignalId::signal_ad2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb3_afec0_ad2;
  static constexpr RouteId kRouteId = RouteId::candidate_pb3_afec0_ad2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_afec0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB3, PeripheralId::MCAN0, SignalId::signal_canrx0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb3_mcan0_canrx0;
  static constexpr RouteId kRouteId = RouteId::candidate_pb3_mcan0_canrx0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_mcan0_lqfp100_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PB3, PeripheralId::USART0, SignalId::signal_rts0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb3_usart0_rts0;
  static constexpr RouteId kRouteId = RouteId::candidate_pb3_usart0_rts0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart0_lqfp100_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::PB4, PeripheralId::PWM0, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb4_pwm0_pwmh2;
  static constexpr RouteId kRouteId = RouteId::candidate_pb4_pwm0_pwmh2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB4, PeripheralId::TWIHS1, SignalId::signal_twd1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb4_twihs1_twd1;
  static constexpr RouteId kRouteId = RouteId::candidate_pb4_twihs1_twd1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_twihs1_lqfp100_scl_sda;
};

template<>
struct ConnectorTraits<PinId::PB4, PeripheralId::USART1, SignalId::signal_txd1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb4_usart1_txd1;
  static constexpr RouteId kRouteId = RouteId::candidate_pb4_usart1_txd1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart1_lqfp100_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PB5, PeripheralId::PWM0, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb5_pwm0_pwml0;
  static constexpr RouteId kRouteId = RouteId::candidate_pb5_pwm0_pwml0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PB5, PeripheralId::TWIHS1, SignalId::signal_twck1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb5_twihs1_twck1;
  static constexpr RouteId kRouteId = RouteId::candidate_pb5_twihs1_twck1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_twihs1_lqfp100_scl_sda;
};

template<>
struct ConnectorTraits<PinId::PD0, PeripheralId::DACC, SignalId::signal_dac1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd0_dacc_dac1;
  static constexpr RouteId kRouteId = RouteId::candidate_pd0_dacc_dac1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_dacc_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD0, PeripheralId::GMAC, SignalId::signal_gtxck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd0_gmac_gtxck;
  static constexpr RouteId kRouteId = RouteId::candidate_pd0_gmac_gtxck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD0, PeripheralId::PWM1, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd0_pwm1_pwml0;
  static constexpr RouteId kRouteId = RouteId::candidate_pd0_pwm1_pwml0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD0, PeripheralId::USART0, SignalId::signal_dcd0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd0_usart0_dcd0;
  static constexpr RouteId kRouteId = RouteId::candidate_pd0_usart0_dcd0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PD10, PeripheralId::GMAC, SignalId::signal_gcrs> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd10_gmac_gcrs;
  static constexpr RouteId kRouteId = RouteId::candidate_pd10_gmac_gcrs;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD10, PeripheralId::PWM0, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd10_pwm0_pwml0;
  static constexpr RouteId kRouteId = RouteId::candidate_pd10_pwm0_pwml0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD11, PeripheralId::GMAC, SignalId::signal_grx2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd11_gmac_grx2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd11_gmac_grx2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD11, PeripheralId::GMAC, SignalId::signal_gtsucomp> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd11_gmac_gtsucomp;
  static constexpr RouteId kRouteId = RouteId::candidate_pd11_gmac_gtsucomp;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD11, PeripheralId::PWM0, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd11_pwm0_pwmh0;
  static constexpr RouteId kRouteId = RouteId::candidate_pd11_pwm0_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD12, PeripheralId::GMAC, SignalId::signal_grx3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd12_gmac_grx3;
  static constexpr RouteId kRouteId = RouteId::candidate_pd12_gmac_grx3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD12, PeripheralId::MCAN1, SignalId::signal_cantx1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd12_mcan1_cantx1;
  static constexpr RouteId kRouteId = RouteId::candidate_pd12_mcan1_cantx1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_mcan1_lqfp100_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PD12, PeripheralId::SPI0, SignalId::signal_npcs2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd12_spi0_npcs2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd12_spi0_npcs2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_lqfp100_sck_cs;
};

template<>
struct ConnectorTraits<PinId::PD13, PeripheralId::GMAC, SignalId::signal_gcol> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd13_gmac_gcol;
  static constexpr RouteId kRouteId = RouteId::candidate_pd13_gmac_gcol;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD14, PeripheralId::GMAC, SignalId::signal_grxck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd14_gmac_grxck;
  static constexpr RouteId kRouteId = RouteId::candidate_pd14_gmac_grxck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD15, PeripheralId::GMAC, SignalId::signal_gtx2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd15_gmac_gtx2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd15_gmac_gtx2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD15, PeripheralId::USART2, SignalId::signal_rxd2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd15_usart2_rxd2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd15_usart2_rxd2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart2_lqfp100_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PD16, PeripheralId::GMAC, SignalId::signal_gtx3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd16_gmac_gtx3;
  static constexpr RouteId kRouteId = RouteId::candidate_pd16_gmac_gtx3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD16, PeripheralId::USART2, SignalId::signal_txd2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd16_usart2_txd2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd16_usart2_txd2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart2_lqfp100_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PD17, PeripheralId::GMAC, SignalId::signal_gtxer> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd17_gmac_gtxer;
  static constexpr RouteId kRouteId = RouteId::candidate_pd17_gmac_gtxer;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD17, PeripheralId::USART2, SignalId::signal_sck2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd17_usart2_sck2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd17_usart2_sck2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PD18, PeripheralId::UART4, SignalId::signal_urxd4> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd18_uart4_urxd4;
  static constexpr RouteId kRouteId = RouteId::candidate_pd18_uart4_urxd4;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart4_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD18, PeripheralId::USART2, SignalId::signal_rts2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd18_usart2_rts2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd18_usart2_rts2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart2_lqfp100_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::PD19, PeripheralId::UART4, SignalId::signal_utxd4> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd19_uart4_utxd4;
  static constexpr RouteId kRouteId = RouteId::candidate_pd19_uart4_utxd4;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart4_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD19, PeripheralId::USART2, SignalId::signal_cts2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd19_usart2_cts2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd19_usart2_cts2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart2_lqfp100_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::PD1, PeripheralId::GMAC, SignalId::signal_gtxen> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd1_gmac_gtxen;
  static constexpr RouteId kRouteId = RouteId::candidate_pd1_gmac_gtxen;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD1, PeripheralId::PWM1, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd1_pwm1_pwmh0;
  static constexpr RouteId kRouteId = RouteId::candidate_pd1_pwm1_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD1, PeripheralId::USART0, SignalId::signal_dtr0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd1_usart0_dtr0;
  static constexpr RouteId kRouteId = RouteId::candidate_pd1_usart0_dtr0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PD20, PeripheralId::GMAC, SignalId::signal_gtsucomp> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd20_gmac_gtsucomp;
  static constexpr RouteId kRouteId = RouteId::candidate_pd20_gmac_gtsucomp;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD20, PeripheralId::PWM0, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd20_pwm0_pwmh0;
  static constexpr RouteId kRouteId = RouteId::candidate_pd20_pwm0_pwmh0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD20, PeripheralId::SPI0, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd20_spi0_miso;
  static constexpr RouteId kRouteId = RouteId::candidate_pd20_spi0_miso;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_lqfp100_sck_mosi_miso;
};

template<>
struct ConnectorTraits<PinId::PD21, PeripheralId::PWM0, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd21_pwm0_pwmh1;
  static constexpr RouteId kRouteId = RouteId::candidate_pd21_pwm0_pwmh1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD21, PeripheralId::SPI0, SignalId::signal_mosi> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd21_spi0_mosi;
  static constexpr RouteId kRouteId = RouteId::candidate_pd21_spi0_mosi;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_lqfp100_sck_mosi_miso;
};

template<>
struct ConnectorTraits<PinId::PD21, PeripheralId::TC3, SignalId::signal_tioa11> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd21_tc3_tioa11;
  static constexpr RouteId kRouteId = RouteId::candidate_pd21_tc3_tioa11;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_tc3_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD22, PeripheralId::PWM0, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd22_pwm0_pwmh2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd22_pwm0_pwmh2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD22, PeripheralId::SPI0, SignalId::signal_spck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd22_spi0_spck;
  static constexpr RouteId kRouteId = RouteId::candidate_pd22_spi0_spck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_lqfp100_sck_mosi_miso;
};

template<>
struct ConnectorTraits<PinId::PD22, PeripheralId::TC3, SignalId::signal_tiob11> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd22_tc3_tiob11;
  static constexpr RouteId kRouteId = RouteId::candidate_pd22_tc3_tiob11;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_tc3_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD24, PeripheralId::PWM0, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd24_pwm0_pwml0;
  static constexpr RouteId kRouteId = RouteId::candidate_pd24_pwm0_pwml0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD24, PeripheralId::TC3, SignalId::signal_tclk11> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd24_tc3_tclk11;
  static constexpr RouteId kRouteId = RouteId::candidate_pd24_tc3_tclk11;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_tc3_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD25, PeripheralId::PWM0, SignalId::signal_pwml1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd25_pwm0_pwml1;
  static constexpr RouteId kRouteId = RouteId::candidate_pd25_pwm0_pwml1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD25, PeripheralId::SPI0, SignalId::signal_npcs1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd25_spi0_npcs1;
  static constexpr RouteId kRouteId = RouteId::candidate_pd25_spi0_npcs1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_lqfp100_sck_cs;
};

template<>
struct ConnectorTraits<PinId::PD25, PeripheralId::UART2, SignalId::signal_urxd2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd25_uart2_urxd2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd25_uart2_urxd2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart2_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD26, PeripheralId::PWM0, SignalId::signal_pwml2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd26_pwm0_pwml2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd26_pwm0_pwml2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD26, PeripheralId::UART1, SignalId::signal_utxd1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd26_uart1_utxd1;
  static constexpr RouteId kRouteId = RouteId::candidate_pd26_uart1_utxd1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD26, PeripheralId::UART2, SignalId::signal_utxd2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd26_uart2_utxd2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd26_uart2_utxd2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart2_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD27, PeripheralId::PWM0, SignalId::signal_pwml3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd27_pwm0_pwml3;
  static constexpr RouteId kRouteId = RouteId::candidate_pd27_pwm0_pwml3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD27, PeripheralId::SPI0, SignalId::signal_npcs3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd27_spi0_npcs3;
  static constexpr RouteId kRouteId = RouteId::candidate_pd27_spi0_npcs3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_lqfp100_sck_cs;
};

template<>
struct ConnectorTraits<PinId::PD27, PeripheralId::TWIHS2, SignalId::signal_twd2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd27_twihs2_twd2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd27_twihs2_twd2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_twihs2_lqfp100_scl_sda;
};

template<>
struct ConnectorTraits<PinId::PD28, PeripheralId::MCAN1, SignalId::signal_canrx1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd28_mcan1_canrx1;
  static constexpr RouteId kRouteId = RouteId::candidate_pd28_mcan1_canrx1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_mcan1_lqfp100_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PD28, PeripheralId::TWIHS2, SignalId::signal_twck2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd28_twihs2_twck2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd28_twihs2_twck2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_twihs2_lqfp100_scl_sda;
};

template<>
struct ConnectorTraits<PinId::PD28, PeripheralId::UART3, SignalId::signal_urxd3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd28_uart3_urxd3;
  static constexpr RouteId kRouteId = RouteId::candidate_pd28_uart3_urxd3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart3_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD2, PeripheralId::GMAC, SignalId::signal_gtx0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd2_gmac_gtx0;
  static constexpr RouteId kRouteId = RouteId::candidate_pd2_gmac_gtx0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD2, PeripheralId::PWM1, SignalId::signal_pwml1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd2_pwm1_pwml1;
  static constexpr RouteId kRouteId = RouteId::candidate_pd2_pwm1_pwml1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD2, PeripheralId::USART0, SignalId::signal_dsr0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd2_usart0_dsr0;
  static constexpr RouteId kRouteId = RouteId::candidate_pd2_usart0_dsr0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PD30, PeripheralId::AFEC0, SignalId::signal_ad0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd30_afec0_ad0;
  static constexpr RouteId kRouteId = RouteId::candidate_pd30_afec0_ad0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_afec0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD30, PeripheralId::UART3, SignalId::signal_utxd3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd30_uart3_utxd3;
  static constexpr RouteId kRouteId = RouteId::candidate_pd30_uart3_utxd3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart3_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD31, PeripheralId::QSPI, SignalId::signal_qio3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd31_qspi_qio3;
  static constexpr RouteId kRouteId = RouteId::candidate_pd31_qspi_qio3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_qspi_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD31, PeripheralId::UART3, SignalId::signal_utxd3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd31_uart3_utxd3;
  static constexpr RouteId kRouteId = RouteId::candidate_pd31_uart3_utxd3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart3_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD3, PeripheralId::GMAC, SignalId::signal_gtx1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd3_gmac_gtx1;
  static constexpr RouteId kRouteId = RouteId::candidate_pd3_gmac_gtx1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD3, PeripheralId::PWM1, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd3_pwm1_pwmh1;
  static constexpr RouteId kRouteId = RouteId::candidate_pd3_pwm1_pwmh1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD3, PeripheralId::UART4, SignalId::signal_utxd4> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd3_uart4_utxd4;
  static constexpr RouteId kRouteId = RouteId::candidate_pd3_uart4_utxd4;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart4_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD3, PeripheralId::USART0, SignalId::signal_ri0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd3_usart0_ri0;
  static constexpr RouteId kRouteId = RouteId::candidate_pd3_usart0_ri0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PD4, PeripheralId::GMAC, SignalId::signal_grxdv> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd4_gmac_grxdv;
  static constexpr RouteId kRouteId = RouteId::candidate_pd4_gmac_grxdv;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD4, PeripheralId::PWM1, SignalId::signal_pwml2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd4_pwm1_pwml2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd4_pwm1_pwml2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD4, PeripheralId::USART2, SignalId::signal_dcd2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd4_usart2_dcd2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd4_usart2_dcd2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PD5, PeripheralId::GMAC, SignalId::signal_grx0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd5_gmac_grx0;
  static constexpr RouteId kRouteId = RouteId::candidate_pd5_gmac_grx0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD5, PeripheralId::PWM1, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd5_pwm1_pwmh2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd5_pwm1_pwmh2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD5, PeripheralId::USART2, SignalId::signal_dtr2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd5_usart2_dtr2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd5_usart2_dtr2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PD6, PeripheralId::GMAC, SignalId::signal_grx1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd6_gmac_grx1;
  static constexpr RouteId kRouteId = RouteId::candidate_pd6_gmac_grx1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD6, PeripheralId::PWM1, SignalId::signal_pwml3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd6_pwm1_pwml3;
  static constexpr RouteId kRouteId = RouteId::candidate_pd6_pwm1_pwml3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD6, PeripheralId::USART2, SignalId::signal_dsr2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd6_usart2_dsr2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd6_usart2_dsr2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PD7, PeripheralId::GMAC, SignalId::signal_grxer> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd7_gmac_grxer;
  static constexpr RouteId kRouteId = RouteId::candidate_pd7_gmac_grxer;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD7, PeripheralId::PWM1, SignalId::signal_pwmh3> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd7_pwm1_pwmh3;
  static constexpr RouteId kRouteId = RouteId::candidate_pd7_pwm1_pwmh3;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD7, PeripheralId::USART2, SignalId::signal_ri2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd7_usart2_ri2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd7_usart2_ri2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PD8, PeripheralId::GMAC, SignalId::signal_gmdc> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd8_gmac_gmdc;
  static constexpr RouteId kRouteId = RouteId::candidate_pd8_gmac_gmdc;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD8, PeripheralId::PWM0, SignalId::signal_pwmfi1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd8_pwm0_pwmfi1;
  static constexpr RouteId kRouteId = RouteId::candidate_pd8_pwm0_pwmfi1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD9, PeripheralId::AFEC1, SignalId::signal_adtrg> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd9_afec1_adtrg;
  static constexpr RouteId kRouteId = RouteId::candidate_pd9_afec1_adtrg;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_afec1_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD9, PeripheralId::GMAC, SignalId::signal_gmdio> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd9_gmac_gmdio;
  static constexpr RouteId kRouteId = RouteId::candidate_pd9_gmac_gmdio;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gmac_lqfp100_all_signals;
};

template<>
struct ConnectorTraits<PinId::PD9, PeripheralId::PWM0, SignalId::signal_pwmfi2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pd9_pwm0_pwmfi2;
  static constexpr RouteId kRouteId = RouteId::candidate_pd9_pwm0_pwmfi2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_pwm0_lqfp100_all_signals;
};

template<>
struct ConnectorSignalTraits<PeripheralId::AFEC0, SignalId::signal_ad0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD30,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd30_afec0_ad0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::AFEC0, SignalId::signal_ad0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for AFEC0 ad0. Valid pins: PD30. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::AFEC0, SignalId::signal_ad1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA21,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa21_afec0_ad1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::AFEC0, SignalId::signal_ad1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for AFEC0 ad1. Valid pins: PA21. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::AFEC0, SignalId::signal_ad10> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB0,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb0_afec0_ad10,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::AFEC0, SignalId::signal_ad10> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for AFEC0 ad10. Valid pins: PB0. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::AFEC0, SignalId::signal_ad2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB3,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb3_afec0_ad2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::AFEC0, SignalId::signal_ad2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for AFEC0 ad2. Valid pins: PB3. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::AFEC0, SignalId::signal_ad5> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB2,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb2_afec0_ad5,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::AFEC0, SignalId::signal_ad5> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for AFEC0 ad5. Valid pins: PB2. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::AFEC0, SignalId::signal_ad6> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA17,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa17_afec0_ad6,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::AFEC0, SignalId::signal_ad6> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for AFEC0 ad6. Valid pins: PA17. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::AFEC0, SignalId::signal_ad7> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA18,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa18_afec0_ad7,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::AFEC0, SignalId::signal_ad7> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for AFEC0 ad7. Valid pins: PA18. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::AFEC0, SignalId::signal_ad8> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA19,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa19_afec0_ad8,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::AFEC0, SignalId::signal_ad8> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for AFEC0 ad8. Valid pins: PA19. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::AFEC0, SignalId::signal_ad9> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA20,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa20_afec0_ad9,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::AFEC0, SignalId::signal_ad9> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for AFEC0 ad9. Valid pins: PA20. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::AFEC0, SignalId::signal_adtrg> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA8,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa8_afec0_adtrg,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::AFEC0, SignalId::signal_adtrg> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for AFEC0 adtrg. Valid pins: PA8. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::AFEC1, SignalId::signal_ad0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB1,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb1_afec1_ad0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::AFEC1, SignalId::signal_ad0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for AFEC1 ad0. Valid pins: PB1. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::AFEC1, SignalId::signal_adtrg> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD9,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd9_afec1_adtrg,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::AFEC1, SignalId::signal_adtrg> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for AFEC1 adtrg. Valid pins: PD9. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::DACC, SignalId::signal_dac0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB13,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb13_dacc_dac0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::DACC, SignalId::signal_dac0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for DACC dac0. Valid pins: PB13. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::DACC, SignalId::signal_dac1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD0,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd0_dacc_dac1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::DACC, SignalId::signal_dac1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for DACC dac1. Valid pins: PD0. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::DACC, SignalId::signal_datrg> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA2,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa2_dacc_datrg,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::DACC, SignalId::signal_datrg> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for DACC datrg. Valid pins: PA2. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_gcol> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD13,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd13_gmac_gcol,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_gcol> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC gcol. Valid pins: PD13. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_gcrs> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD10,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd10_gmac_gcrs,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_gcrs> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC gcrs. Valid pins: PD10. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_gmdc> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD8,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd8_gmac_gmdc,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_gmdc> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC gmdc. Valid pins: PD8. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_gmdio> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD9,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd9_gmac_gmdio,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_gmdio> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC gmdio. Valid pins: PD9. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_grx0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD5,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd5_gmac_grx0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_grx0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC grx0. Valid pins: PD5. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_grx1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD6,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd6_gmac_grx1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_grx1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC grx1. Valid pins: PD6. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_grx2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD11,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd11_gmac_grx2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_grx2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC grx2. Valid pins: PD11. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_grx3> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD12,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd12_gmac_grx3,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_grx3> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC grx3. Valid pins: PD12. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_grxck> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD14,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd14_gmac_grxck,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_grxck> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC grxck. Valid pins: PD14. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_grxdv> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD4,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd4_gmac_grxdv,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_grxdv> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC grxdv. Valid pins: PD4. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_grxer> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD7,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd7_gmac_grxer,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_grxer> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC grxer. Valid pins: PD7. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_gtsucomp> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 4> kPins = {{
    PinId::PB12,
    PinId::PB1,
    PinId::PD11,
    PinId::PD20,
  }};
  static constexpr std::array<ConnectorId, 4> kConnectors = {{
    ConnectorId::candidate_pb12_gmac_gtsucomp,
    ConnectorId::candidate_pb1_gmac_gtsucomp,
    ConnectorId::candidate_pd11_gmac_gtsucomp,
    ConnectorId::candidate_pd20_gmac_gtsucomp,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_gtsucomp> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC gtsucomp. Valid pins: PB12, PB1, PD11, PD20. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_gtx0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD2,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd2_gmac_gtx0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_gtx0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC gtx0. Valid pins: PD2. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_gtx1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD3,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd3_gmac_gtx1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_gtx1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC gtx1. Valid pins: PD3. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_gtx2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD15,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd15_gmac_gtx2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_gtx2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC gtx2. Valid pins: PD15. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_gtx3> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD16,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd16_gmac_gtx3,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_gtx3> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC gtx3. Valid pins: PD16. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_gtxck> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD0,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd0_gmac_gtxck,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_gtxck> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC gtxck. Valid pins: PD0. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_gtxen> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD1,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd1_gmac_gtxen,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_gtxen> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC gtxen. Valid pins: PD1. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GMAC, SignalId::signal_gtxer> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD17,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd17_gmac_gtxer,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GMAC, SignalId::signal_gtxer> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GMAC gtxer. Valid pins: PD17. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIOA, SignalId::signal_piodc0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA3,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa3_gpioa_piodc0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIOA, SignalId::signal_piodc0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIOA piodc0. Valid pins: PA3. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIOA, SignalId::signal_piodc1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA4,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa4_gpioa_piodc1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIOA, SignalId::signal_piodc1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIOA piodc1. Valid pins: PA4. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIOA, SignalId::signal_piodc2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA5,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa5_gpioa_piodc2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIOA, SignalId::signal_piodc2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIOA piodc2. Valid pins: PA5. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIOA, SignalId::signal_piodc3> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA9,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa9_gpioa_piodc3,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIOA, SignalId::signal_piodc3> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIOA piodc3. Valid pins: PA9. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIOA, SignalId::signal_piodc4> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA10,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa10_gpioa_piodc4,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIOA, SignalId::signal_piodc4> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIOA piodc4. Valid pins: PA10. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIOA, SignalId::signal_piodc5> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA11,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa11_gpioa_piodc5,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIOA, SignalId::signal_piodc5> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIOA piodc5. Valid pins: PA11. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIOA, SignalId::signal_piodc6> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA12,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa12_gpioa_piodc6,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIOA, SignalId::signal_piodc6> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIOA piodc6. Valid pins: PA12. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIOA, SignalId::signal_piodc7> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA13,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa13_gpioa_piodc7,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIOA, SignalId::signal_piodc7> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIOA piodc7. Valid pins: PA13. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIOA, SignalId::signal_piodcclk> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA22,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa22_gpioa_piodcclk,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIOA, SignalId::signal_piodcclk> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIOA piodcclk. Valid pins: PA22. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIOA, SignalId::signal_piodcen1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA14,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa14_gpioa_piodcen1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIOA, SignalId::signal_piodcen1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIOA piodcen1. Valid pins: PA14. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIOA, SignalId::signal_piodcen2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA21,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa21_gpioa_piodcen2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIOA, SignalId::signal_piodcen2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIOA piodcen2. Valid pins: PA21. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::HSMCI, SignalId::signal_mccda> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA28,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa28_hsmci_mccda,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::HSMCI, SignalId::signal_mccda> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for HSMCI mccda. Valid pins: PA28. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::HSMCI, SignalId::signal_mcck> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA25,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa25_hsmci_mcck,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::HSMCI, SignalId::signal_mcck> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for HSMCI mcck. Valid pins: PA25. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::HSMCI, SignalId::signal_mcda0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA30,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa30_hsmci_mcda0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::HSMCI, SignalId::signal_mcda0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for HSMCI mcda0. Valid pins: PA30. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::HSMCI, SignalId::signal_mcda1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA31,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa31_hsmci_mcda1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::HSMCI, SignalId::signal_mcda1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for HSMCI mcda1. Valid pins: PA31. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::HSMCI, SignalId::signal_mcda2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA26,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa26_hsmci_mcda2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::HSMCI, SignalId::signal_mcda2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for HSMCI mcda2. Valid pins: PA26. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::HSMCI, SignalId::signal_mcda3> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA27,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa27_hsmci_mcda3,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::HSMCI, SignalId::signal_mcda3> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for HSMCI mcda3. Valid pins: PA27. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::MCAN0, SignalId::signal_canrx0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB3,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb3_mcan0_canrx0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::MCAN0, SignalId::signal_canrx0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for MCAN0 canrx0. Valid pins: PB3. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::MCAN0, SignalId::signal_cantx0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB2,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb2_mcan0_cantx0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::MCAN0, SignalId::signal_cantx0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for MCAN0 cantx0. Valid pins: PB2. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::MCAN1, SignalId::signal_canrx1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD28,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd28_mcan1_canrx1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::MCAN1, SignalId::signal_canrx1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for MCAN1 canrx1. Valid pins: PD28. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::MCAN1, SignalId::signal_cantx1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD12,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd12_mcan1_cantx1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::MCAN1, SignalId::signal_cantx1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for MCAN1 cantx1. Valid pins: PD12. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM0, SignalId::signal_pwmextrg0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA10,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa10_pwm0_pwmextrg0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM0, SignalId::signal_pwmextrg0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM0 pwmextrg0. Valid pins: PA10. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM0, SignalId::signal_pwmextrg1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA22,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa22_pwm0_pwmextrg1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM0, SignalId::signal_pwmextrg1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM0 pwmextrg1. Valid pins: PA22. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM0, SignalId::signal_pwmfi0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA9,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa9_pwm0_pwmfi0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM0, SignalId::signal_pwmfi0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM0 pwmfi0. Valid pins: PA9. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM0, SignalId::signal_pwmfi1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD8,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd8_pwm0_pwmfi1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM0, SignalId::signal_pwmfi1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM0 pwmfi1. Valid pins: PD8. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM0, SignalId::signal_pwmfi2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD9,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd9_pwm0_pwmfi2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM0, SignalId::signal_pwmfi2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM0 pwmfi2. Valid pins: PD9. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM0, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 6> kPins = {{
    PinId::PA0,
    PinId::PA11,
    PinId::PA23,
    PinId::PB0,
    PinId::PD11,
    PinId::PD20,
  }};
  static constexpr std::array<ConnectorId, 6> kConnectors = {{
    ConnectorId::candidate_pa0_pwm0_pwmh0,
    ConnectorId::candidate_pa11_pwm0_pwmh0,
    ConnectorId::candidate_pa23_pwm0_pwmh0,
    ConnectorId::candidate_pb0_pwm0_pwmh0,
    ConnectorId::candidate_pd11_pwm0_pwmh0,
    ConnectorId::candidate_pd20_pwm0_pwmh0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM0, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM0 pwmh0. Valid pins: PA0, PA11, PA23, PB0, PD11, PD20. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM0, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 5> kPins = {{
    PinId::PA12,
    PinId::PA24,
    PinId::PA2,
    PinId::PB1,
    PinId::PD21,
  }};
  static constexpr std::array<ConnectorId, 5> kConnectors = {{
    ConnectorId::candidate_pa12_pwm0_pwmh1,
    ConnectorId::candidate_pa24_pwm0_pwmh1,
    ConnectorId::candidate_pa2_pwm0_pwmh1,
    ConnectorId::candidate_pb1_pwm0_pwmh1,
    ConnectorId::candidate_pd21_pwm0_pwmh1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM0, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM0 pwmh1. Valid pins: PA12, PA24, PA2, PB1, PD21. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM0, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 4> kPins = {{
    PinId::PA13,
    PinId::PA25,
    PinId::PB4,
    PinId::PD22,
  }};
  static constexpr std::array<ConnectorId, 4> kConnectors = {{
    ConnectorId::candidate_pa13_pwm0_pwmh2,
    ConnectorId::candidate_pa25_pwm0_pwmh2,
    ConnectorId::candidate_pb4_pwm0_pwmh2,
    ConnectorId::candidate_pd22_pwm0_pwmh2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM0, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM0 pwmh2. Valid pins: PA13, PA25, PB4, PD22. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM0, SignalId::signal_pwmh3> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 3> kPins = {{
    PinId::PA14,
    PinId::PA17,
    PinId::PA7,
  }};
  static constexpr std::array<ConnectorId, 3> kConnectors = {{
    ConnectorId::candidate_pa14_pwm0_pwmh3,
    ConnectorId::candidate_pa17_pwm0_pwmh3,
    ConnectorId::candidate_pa7_pwm0_pwmh3,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM0, SignalId::signal_pwmh3> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM0 pwmh3. Valid pins: PA14, PA17, PA7. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM0, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 5> kPins = {{
    PinId::PA19,
    PinId::PA1,
    PinId::PB5,
    PinId::PD10,
    PinId::PD24,
  }};
  static constexpr std::array<ConnectorId, 5> kConnectors = {{
    ConnectorId::candidate_pa19_pwm0_pwml0,
    ConnectorId::candidate_pa1_pwm0_pwml0,
    ConnectorId::candidate_pb5_pwm0_pwml0,
    ConnectorId::candidate_pd10_pwm0_pwml0,
    ConnectorId::candidate_pd24_pwm0_pwml0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM0, SignalId::signal_pwml0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM0 pwml0. Valid pins: PA19, PA1, PB5, PD10, PD24. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM0, SignalId::signal_pwml1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 3> kPins = {{
    PinId::PA20,
    PinId::PB12,
    PinId::PD25,
  }};
  static constexpr std::array<ConnectorId, 3> kConnectors = {{
    ConnectorId::candidate_pa20_pwm0_pwml1,
    ConnectorId::candidate_pb12_pwm0_pwml1,
    ConnectorId::candidate_pd25_pwm0_pwml1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM0, SignalId::signal_pwml1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM0 pwml1. Valid pins: PA20, PB12, PD25. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM0, SignalId::signal_pwml2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 4> kPins = {{
    PinId::PA16,
    PinId::PA30,
    PinId::PB13,
    PinId::PD26,
  }};
  static constexpr std::array<ConnectorId, 4> kConnectors = {{
    ConnectorId::candidate_pa16_pwm0_pwml2,
    ConnectorId::candidate_pa30_pwm0_pwml2,
    ConnectorId::candidate_pb13_pwm0_pwml2,
    ConnectorId::candidate_pd26_pwm0_pwml2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM0, SignalId::signal_pwml2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM0 pwml2. Valid pins: PA16, PA30, PB13, PD26. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM0, SignalId::signal_pwml3> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::PA15,
    PinId::PD27,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_pa15_pwm0_pwml3,
    ConnectorId::candidate_pd27_pwm0_pwml3,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM0, SignalId::signal_pwml3> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM0 pwml3. Valid pins: PA15, PD27. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM1, SignalId::signal_pwmextrg0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA30,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa30_pwm1_pwmextrg0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM1, SignalId::signal_pwmextrg0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM1 pwmextrg0. Valid pins: PA30. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM1, SignalId::signal_pwmextrg1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA18,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa18_pwm1_pwmextrg1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM1, SignalId::signal_pwmextrg1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM1 pwmextrg1. Valid pins: PA18. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM1, SignalId::signal_pwmfi0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA21,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa21_pwm1_pwmfi0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM1, SignalId::signal_pwmfi0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM1 pwmfi0. Valid pins: PA21. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM1, SignalId::signal_pwmfi1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA26,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa26_pwm1_pwmfi1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM1, SignalId::signal_pwmfi1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM1 pwmfi1. Valid pins: PA26. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM1, SignalId::signal_pwmfi2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA28,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa28_pwm1_pwmfi2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM1, SignalId::signal_pwmfi2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM1 pwmfi2. Valid pins: PA28. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM1, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::PA12,
    PinId::PD1,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_pa12_pwm1_pwmh0,
    ConnectorId::candidate_pd1_pwm1_pwmh0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM1, SignalId::signal_pwmh0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM1 pwmh0. Valid pins: PA12, PD1. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM1, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::PA14,
    PinId::PD3,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_pa14_pwm1_pwmh1,
    ConnectorId::candidate_pd3_pwm1_pwmh1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM1, SignalId::signal_pwmh1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM1 pwmh1. Valid pins: PA14, PD3. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM1, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::PA31,
    PinId::PD5,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_pa31_pwm1_pwmh2,
    ConnectorId::candidate_pd5_pwm1_pwmh2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM1, SignalId::signal_pwmh2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM1 pwmh2. Valid pins: PA31, PD5. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM1, SignalId::signal_pwmh3> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::PA8,
    PinId::PD7,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_pa8_pwm1_pwmh3,
    ConnectorId::candidate_pd7_pwm1_pwmh3,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM1, SignalId::signal_pwmh3> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM1 pwmh3. Valid pins: PA8, PD7. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM1, SignalId::signal_pwml0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::PA11,
    PinId::PD0,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_pa11_pwm1_pwml0,
    ConnectorId::candidate_pd0_pwm1_pwml0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM1, SignalId::signal_pwml0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM1 pwml0. Valid pins: PA11, PD0. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM1, SignalId::signal_pwml1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::PA13,
    PinId::PD2,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_pa13_pwm1_pwml1,
    ConnectorId::candidate_pd2_pwm1_pwml1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM1, SignalId::signal_pwml1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM1 pwml1. Valid pins: PA13, PD2. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM1, SignalId::signal_pwml2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::PA23,
    PinId::PD4,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_pa23_pwm1_pwml2,
    ConnectorId::candidate_pd4_pwm1_pwml2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM1, SignalId::signal_pwml2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM1 pwml2. Valid pins: PA23, PD4. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::PWM1, SignalId::signal_pwml3> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::PA5,
    PinId::PD6,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_pa5_pwm1_pwml3,
    ConnectorId::candidate_pd6_pwm1_pwml3,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::PWM1, SignalId::signal_pwml3> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for PWM1 pwml3. Valid pins: PA5, PD6. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::QSPI, SignalId::signal_qcs> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA11,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa11_qspi_qcs,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::QSPI, SignalId::signal_qcs> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for QSPI qcs. Valid pins: PA11. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::QSPI, SignalId::signal_qio0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA13,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa13_qspi_qio0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::QSPI, SignalId::signal_qio0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for QSPI qio0. Valid pins: PA13. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::QSPI, SignalId::signal_qio1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA12,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa12_qspi_qio1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::QSPI, SignalId::signal_qio1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for QSPI qio1. Valid pins: PA12. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::QSPI, SignalId::signal_qio2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA17,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa17_qspi_qio2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::QSPI, SignalId::signal_qio2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for QSPI qio2. Valid pins: PA17. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::QSPI, SignalId::signal_qio3> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD31,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd31_qspi_qio3,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::QSPI, SignalId::signal_qio3> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for QSPI qio3. Valid pins: PD31. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::QSPI, SignalId::signal_qsck> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA14,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa14_qspi_qsck,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::QSPI, SignalId::signal_qsck> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for QSPI qsck. Valid pins: PA14. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::RTC, SignalId::signal_rtcout0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB0,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb0_rtc_rtcout0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::RTC, SignalId::signal_rtcout0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for RTC rtcout0. Valid pins: PB0. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::RTC, SignalId::signal_rtcout1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB1,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb1_rtc_rtcout1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::RTC, SignalId::signal_rtcout1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for RTC rtcout1. Valid pins: PB1. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD20,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd20_spi0_miso,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_miso> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 miso. Valid pins: PD20. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_mosi> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD21,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd21_spi0_mosi,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_mosi> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 mosi. Valid pins: PD21. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_npcs0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB2,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb2_spi0_npcs0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_npcs0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 npcs0. Valid pins: PB2. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_npcs1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::PA31,
    PinId::PD25,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_pa31_spi0_npcs1,
    ConnectorId::candidate_pd25_spi0_npcs1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_npcs1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 npcs1. Valid pins: PA31, PD25. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_npcs2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD12,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd12_spi0_npcs2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_npcs2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 npcs2. Valid pins: PD12. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_npcs3> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD27,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd27_spi0_npcs3,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_npcs3> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 npcs3. Valid pins: PD27. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_spck> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD22,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd22_spi0_spck,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_spck> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 spck. Valid pins: PD22. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TC0, SignalId::signal_tclk0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA4,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa4_tc0_tclk0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TC0, SignalId::signal_tclk0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TC0 tclk0. Valid pins: PA4. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TC0, SignalId::signal_tclk1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA28,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa28_tc0_tclk1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TC0, SignalId::signal_tclk1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TC0 tclk1. Valid pins: PA28. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TC0, SignalId::signal_tioa0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA0,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa0_tc0_tioa0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TC0, SignalId::signal_tioa0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TC0 tioa0. Valid pins: PA0. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TC0, SignalId::signal_tioa1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA15,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa15_tc0_tioa1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TC0, SignalId::signal_tioa1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TC0 tioa1. Valid pins: PA15. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TC0, SignalId::signal_tioa2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA26,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa26_tc0_tioa2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TC0, SignalId::signal_tioa2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TC0 tioa2. Valid pins: PA26. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TC0, SignalId::signal_tiob0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA1,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa1_tc0_tiob0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TC0, SignalId::signal_tiob0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TC0 tiob0. Valid pins: PA1. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TC0, SignalId::signal_tiob1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA16,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa16_tc0_tiob1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TC0, SignalId::signal_tiob1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TC0 tiob1. Valid pins: PA16. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TC0, SignalId::signal_tiob2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA27,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa27_tc0_tiob2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TC0, SignalId::signal_tiob2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TC0 tiob2. Valid pins: PA27. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TC3, SignalId::signal_tclk11> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD24,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd24_tc3_tclk11,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TC3, SignalId::signal_tclk11> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TC3 tclk11. Valid pins: PD24. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TC3, SignalId::signal_tioa11> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD21,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd21_tc3_tioa11,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TC3, SignalId::signal_tioa11> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TC3 tioa11. Valid pins: PD21. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TC3, SignalId::signal_tiob11> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD22,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd22_tc3_tiob11,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TC3, SignalId::signal_tiob11> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TC3 tiob11. Valid pins: PD22. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TWIHS0, SignalId::signal_twck0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA4,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa4_twihs0_twck0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TWIHS0, SignalId::signal_twck0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TWIHS0 twck0. Valid pins: PA4. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TWIHS0, SignalId::signal_twd0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA3,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa3_twihs0_twd0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TWIHS0, SignalId::signal_twd0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TWIHS0 twd0. Valid pins: PA3. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TWIHS1, SignalId::signal_twck1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB5,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb5_twihs1_twck1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TWIHS1, SignalId::signal_twck1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TWIHS1 twck1. Valid pins: PB5. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TWIHS1, SignalId::signal_twd1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB4,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb4_twihs1_twd1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TWIHS1, SignalId::signal_twd1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TWIHS1 twd1. Valid pins: PB4. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TWIHS2, SignalId::signal_twck2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD28,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd28_twihs2_twck2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TWIHS2, SignalId::signal_twck2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TWIHS2 twck2. Valid pins: PD28. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TWIHS2, SignalId::signal_twd2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD27,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd27_twihs2_twd2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TWIHS2, SignalId::signal_twd2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TWIHS2 twd2. Valid pins: PD27. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART0, SignalId::signal_urxd0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA9,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa9_uart0_urxd0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART0, SignalId::signal_urxd0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART0 urxd0. Valid pins: PA9. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART0, SignalId::signal_utxd0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA10,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa10_uart0_utxd0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART0, SignalId::signal_utxd0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART0 utxd0. Valid pins: PA10. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART1, SignalId::signal_urxd1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA5,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa5_uart1_urxd1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART1, SignalId::signal_urxd1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART1 urxd1. Valid pins: PA5. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART1, SignalId::signal_utxd1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::PA4,
    PinId::PD26,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_pa4_uart1_utxd1,
    ConnectorId::candidate_pd26_uart1_utxd1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART1, SignalId::signal_utxd1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART1 utxd1. Valid pins: PA4, PD26. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART2, SignalId::signal_urxd2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD25,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd25_uart2_urxd2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART2, SignalId::signal_urxd2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART2 urxd2. Valid pins: PD25. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART2, SignalId::signal_utxd2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD26,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd26_uart2_utxd2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART2, SignalId::signal_utxd2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART2 utxd2. Valid pins: PD26. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART3, SignalId::signal_urxd3> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD28,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd28_uart3_urxd3,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART3, SignalId::signal_urxd3> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART3 urxd3. Valid pins: PD28. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART3, SignalId::signal_utxd3> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::PD30,
    PinId::PD31,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_pd30_uart3_utxd3,
    ConnectorId::candidate_pd31_uart3_utxd3,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART3, SignalId::signal_utxd3> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART3 utxd3. Valid pins: PD30, PD31. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART4, SignalId::signal_urxd4> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD18,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd18_uart4_urxd4,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART4, SignalId::signal_urxd4> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART4 urxd4. Valid pins: PD18. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART4, SignalId::signal_utxd4> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::PD19,
    PinId::PD3,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_pd19_uart4_utxd4,
    ConnectorId::candidate_pd3_uart4_utxd4,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART4, SignalId::signal_utxd4> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART4 utxd4. Valid pins: PD19, PD3. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART0, SignalId::signal_cts0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB2,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb2_usart0_cts0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART0, SignalId::signal_cts0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART0 cts0. Valid pins: PB2. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART0, SignalId::signal_dcd0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD0,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd0_usart0_dcd0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART0, SignalId::signal_dcd0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART0 dcd0. Valid pins: PD0. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART0, SignalId::signal_dsr0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD2,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd2_usart0_dsr0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART0, SignalId::signal_dsr0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART0 dsr0. Valid pins: PD2. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART0, SignalId::signal_dtr0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD1,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd1_usart0_dtr0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART0, SignalId::signal_dtr0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART0 dtr0. Valid pins: PD1. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART0, SignalId::signal_ri0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD3,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd3_usart0_ri0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART0, SignalId::signal_ri0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART0 ri0. Valid pins: PD3. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART0, SignalId::signal_rts0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB3,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb3_usart0_rts0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART0, SignalId::signal_rts0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART0 rts0. Valid pins: PB3. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART0, SignalId::signal_rxd0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB0,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb0_usart0_rxd0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART0, SignalId::signal_rxd0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART0 rxd0. Valid pins: PB0. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART0, SignalId::signal_sck0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB13,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb13_usart0_sck0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART0, SignalId::signal_sck0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART0 sck0. Valid pins: PB13. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART0, SignalId::signal_txd0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB1,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb1_usart0_txd0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART0, SignalId::signal_txd0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART0 txd0. Valid pins: PB1. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART1, SignalId::signal_cts1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA25,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa25_usart1_cts1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART1, SignalId::signal_cts1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART1 cts1. Valid pins: PA25. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART1, SignalId::signal_dcd1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA26,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa26_usart1_dcd1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART1, SignalId::signal_dcd1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART1 dcd1. Valid pins: PA26. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART1, SignalId::signal_dsr1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA28,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa28_usart1_dsr1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART1, SignalId::signal_dsr1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART1 dsr1. Valid pins: PA28. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART1, SignalId::signal_dtr1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA27,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa27_usart1_dtr1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART1, SignalId::signal_dtr1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART1 dtr1. Valid pins: PA27. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART1, SignalId::signal_loncol1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA3,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa3_usart1_loncol1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART1, SignalId::signal_loncol1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART1 loncol1. Valid pins: PA3. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART1, SignalId::signal_rts1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA24,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa24_usart1_rts1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART1, SignalId::signal_rts1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART1 rts1. Valid pins: PA24. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART1, SignalId::signal_rxd1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA21,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa21_usart1_rxd1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART1, SignalId::signal_rxd1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART1 rxd1. Valid pins: PA21. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART1, SignalId::signal_sck1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA23,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa23_usart1_sck1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART1, SignalId::signal_sck1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART1 sck1. Valid pins: PA23. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART1, SignalId::signal_txd1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB4,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb4_usart1_txd1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART1, SignalId::signal_txd1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART1 txd1. Valid pins: PB4. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART2, SignalId::signal_cts2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD19,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd19_usart2_cts2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART2, SignalId::signal_cts2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART2 cts2. Valid pins: PD19. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART2, SignalId::signal_dcd2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD4,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd4_usart2_dcd2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART2, SignalId::signal_dcd2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART2 dcd2. Valid pins: PD4. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART2, SignalId::signal_dsr2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD6,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd6_usart2_dsr2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART2, SignalId::signal_dsr2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART2 dsr2. Valid pins: PD6. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART2, SignalId::signal_dtr2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD5,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd5_usart2_dtr2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART2, SignalId::signal_dtr2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART2 dtr2. Valid pins: PD5. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART2, SignalId::signal_ri2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD7,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd7_usart2_ri2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART2, SignalId::signal_ri2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART2 ri2. Valid pins: PD7. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART2, SignalId::signal_rts2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD18,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd18_usart2_rts2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART2, SignalId::signal_rts2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART2 rts2. Valid pins: PD18. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART2, SignalId::signal_rxd2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD15,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd15_usart2_rxd2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART2, SignalId::signal_rxd2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART2 rxd2. Valid pins: PD15. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART2, SignalId::signal_sck2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD17,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd17_usart2_sck2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART2, SignalId::signal_sck2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART2 sck2. Valid pins: PD17. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART2, SignalId::signal_txd2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PD16,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pd16_usart2_txd2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART2, SignalId::signal_txd2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART2 txd2. Valid pins: PD16. Provenance: microchip-dfp-extract; patches=microchip-same70-atsame70n21b-bootstrap, microchip-same70-family-bootstrap-v1.");
};

inline constexpr std::array<ConnectorDescriptor, 189> kConnectors = {{
  {ConnectorId::candidate_pa0_pwm0_pwmh0, PinId::PA0, PeripheralId::PWM0, SignalId::signal_pwmh0, RouteId::candidate_pa0_pwm0_pwmh0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa0_tc0_tioa0, PinId::PA0, PeripheralId::TC0, SignalId::signal_tioa0, RouteId::candidate_pa0_tc0_tioa0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_tc0_lqfp100_all_signals},
  {ConnectorId::candidate_pa10_gpioa_piodc4, PinId::PA10, PeripheralId::GPIOA, SignalId::signal_piodc4, RouteId::candidate_pa10_gpioa_piodc4, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gpioa_lqfp100_all_signals},
  {ConnectorId::candidate_pa10_pwm0_pwmextrg0, PinId::PA10, PeripheralId::PWM0, SignalId::signal_pwmextrg0, RouteId::candidate_pa10_pwm0_pwmextrg0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa10_uart0_utxd0, PinId::PA10, PeripheralId::UART0, SignalId::signal_utxd0, RouteId::candidate_pa10_uart0_utxd0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_uart0_lqfp100_all_signals},
  {ConnectorId::candidate_pa11_gpioa_piodc5, PinId::PA11, PeripheralId::GPIOA, SignalId::signal_piodc5, RouteId::candidate_pa11_gpioa_piodc5, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gpioa_lqfp100_all_signals},
  {ConnectorId::candidate_pa11_pwm0_pwmh0, PinId::PA11, PeripheralId::PWM0, SignalId::signal_pwmh0, RouteId::candidate_pa11_pwm0_pwmh0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa11_pwm1_pwml0, PinId::PA11, PeripheralId::PWM1, SignalId::signal_pwml0, RouteId::candidate_pa11_pwm1_pwml0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pa11_qspi_qcs, PinId::PA11, PeripheralId::QSPI, SignalId::signal_qcs, RouteId::candidate_pa11_qspi_qcs, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_qspi_lqfp100_all_signals},
  {ConnectorId::candidate_pa12_gpioa_piodc6, PinId::PA12, PeripheralId::GPIOA, SignalId::signal_piodc6, RouteId::candidate_pa12_gpioa_piodc6, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gpioa_lqfp100_all_signals},
  {ConnectorId::candidate_pa12_pwm0_pwmh1, PinId::PA12, PeripheralId::PWM0, SignalId::signal_pwmh1, RouteId::candidate_pa12_pwm0_pwmh1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa12_pwm1_pwmh0, PinId::PA12, PeripheralId::PWM1, SignalId::signal_pwmh0, RouteId::candidate_pa12_pwm1_pwmh0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pa12_qspi_qio1, PinId::PA12, PeripheralId::QSPI, SignalId::signal_qio1, RouteId::candidate_pa12_qspi_qio1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_qspi_lqfp100_all_signals},
  {ConnectorId::candidate_pa13_gpioa_piodc7, PinId::PA13, PeripheralId::GPIOA, SignalId::signal_piodc7, RouteId::candidate_pa13_gpioa_piodc7, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gpioa_lqfp100_all_signals},
  {ConnectorId::candidate_pa13_pwm0_pwmh2, PinId::PA13, PeripheralId::PWM0, SignalId::signal_pwmh2, RouteId::candidate_pa13_pwm0_pwmh2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa13_pwm1_pwml1, PinId::PA13, PeripheralId::PWM1, SignalId::signal_pwml1, RouteId::candidate_pa13_pwm1_pwml1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pa13_qspi_qio0, PinId::PA13, PeripheralId::QSPI, SignalId::signal_qio0, RouteId::candidate_pa13_qspi_qio0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_qspi_lqfp100_all_signals},
  {ConnectorId::candidate_pa14_gpioa_piodcen1, PinId::PA14, PeripheralId::GPIOA, SignalId::signal_piodcen1, RouteId::candidate_pa14_gpioa_piodcen1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gpioa_lqfp100_all_signals},
  {ConnectorId::candidate_pa14_pwm0_pwmh3, PinId::PA14, PeripheralId::PWM0, SignalId::signal_pwmh3, RouteId::candidate_pa14_pwm0_pwmh3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa14_pwm1_pwmh1, PinId::PA14, PeripheralId::PWM1, SignalId::signal_pwmh1, RouteId::candidate_pa14_pwm1_pwmh1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pa14_qspi_qsck, PinId::PA14, PeripheralId::QSPI, SignalId::signal_qsck, RouteId::candidate_pa14_qspi_qsck, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_qspi_lqfp100_all_signals},
  {ConnectorId::candidate_pa15_pwm0_pwml3, PinId::PA15, PeripheralId::PWM0, SignalId::signal_pwml3, RouteId::candidate_pa15_pwm0_pwml3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa15_tc0_tioa1, PinId::PA15, PeripheralId::TC0, SignalId::signal_tioa1, RouteId::candidate_pa15_tc0_tioa1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_tc0_lqfp100_all_signals},
  {ConnectorId::candidate_pa16_pwm0_pwml2, PinId::PA16, PeripheralId::PWM0, SignalId::signal_pwml2, RouteId::candidate_pa16_pwm0_pwml2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa16_tc0_tiob1, PinId::PA16, PeripheralId::TC0, SignalId::signal_tiob1, RouteId::candidate_pa16_tc0_tiob1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_tc0_lqfp100_all_signals},
  {ConnectorId::candidate_pa17_afec0_ad6, PinId::PA17, PeripheralId::AFEC0, SignalId::signal_ad6, RouteId::candidate_pa17_afec0_ad6, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_afec0_lqfp100_all_signals},
  {ConnectorId::candidate_pa17_pwm0_pwmh3, PinId::PA17, PeripheralId::PWM0, SignalId::signal_pwmh3, RouteId::candidate_pa17_pwm0_pwmh3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa17_qspi_qio2, PinId::PA17, PeripheralId::QSPI, SignalId::signal_qio2, RouteId::candidate_pa17_qspi_qio2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_qspi_lqfp100_all_signals},
  {ConnectorId::candidate_pa18_afec0_ad7, PinId::PA18, PeripheralId::AFEC0, SignalId::signal_ad7, RouteId::candidate_pa18_afec0_ad7, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_afec0_lqfp100_all_signals},
  {ConnectorId::candidate_pa18_pwm1_pwmextrg1, PinId::PA18, PeripheralId::PWM1, SignalId::signal_pwmextrg1, RouteId::candidate_pa18_pwm1_pwmextrg1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pa19_afec0_ad8, PinId::PA19, PeripheralId::AFEC0, SignalId::signal_ad8, RouteId::candidate_pa19_afec0_ad8, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_afec0_lqfp100_all_signals},
  {ConnectorId::candidate_pa19_pwm0_pwml0, PinId::PA19, PeripheralId::PWM0, SignalId::signal_pwml0, RouteId::candidate_pa19_pwm0_pwml0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa1_pwm0_pwml0, PinId::PA1, PeripheralId::PWM0, SignalId::signal_pwml0, RouteId::candidate_pa1_pwm0_pwml0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa1_tc0_tiob0, PinId::PA1, PeripheralId::TC0, SignalId::signal_tiob0, RouteId::candidate_pa1_tc0_tiob0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_tc0_lqfp100_all_signals},
  {ConnectorId::candidate_pa20_afec0_ad9, PinId::PA20, PeripheralId::AFEC0, SignalId::signal_ad9, RouteId::candidate_pa20_afec0_ad9, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_afec0_lqfp100_all_signals},
  {ConnectorId::candidate_pa20_pwm0_pwml1, PinId::PA20, PeripheralId::PWM0, SignalId::signal_pwml1, RouteId::candidate_pa20_pwm0_pwml1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa21_afec0_ad1, PinId::PA21, PeripheralId::AFEC0, SignalId::signal_ad1, RouteId::candidate_pa21_afec0_ad1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_afec0_lqfp100_all_signals},
  {ConnectorId::candidate_pa21_gpioa_piodcen2, PinId::PA21, PeripheralId::GPIOA, SignalId::signal_piodcen2, RouteId::candidate_pa21_gpioa_piodcen2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gpioa_lqfp100_all_signals},
  {ConnectorId::candidate_pa21_pwm1_pwmfi0, PinId::PA21, PeripheralId::PWM1, SignalId::signal_pwmfi0, RouteId::candidate_pa21_pwm1_pwmfi0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pa21_usart1_rxd1, PinId::PA21, PeripheralId::USART1, SignalId::signal_rxd1, RouteId::candidate_pa21_usart1_rxd1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart1_lqfp100_tx_rx},
  {ConnectorId::candidate_pa22_gpioa_piodcclk, PinId::PA22, PeripheralId::GPIOA, SignalId::signal_piodcclk, RouteId::candidate_pa22_gpioa_piodcclk, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gpioa_lqfp100_all_signals},
  {ConnectorId::candidate_pa22_pwm0_pwmextrg1, PinId::PA22, PeripheralId::PWM0, SignalId::signal_pwmextrg1, RouteId::candidate_pa22_pwm0_pwmextrg1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa23_pwm0_pwmh0, PinId::PA23, PeripheralId::PWM0, SignalId::signal_pwmh0, RouteId::candidate_pa23_pwm0_pwmh0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa23_pwm1_pwml2, PinId::PA23, PeripheralId::PWM1, SignalId::signal_pwml2, RouteId::candidate_pa23_pwm1_pwml2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pa23_usart1_sck1, PinId::PA23, PeripheralId::USART1, SignalId::signal_sck1, RouteId::candidate_pa23_usart1_sck1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pa24_pwm0_pwmh1, PinId::PA24, PeripheralId::PWM0, SignalId::signal_pwmh1, RouteId::candidate_pa24_pwm0_pwmh1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa24_usart1_rts1, PinId::PA24, PeripheralId::USART1, SignalId::signal_rts1, RouteId::candidate_pa24_usart1_rts1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart1_lqfp100_tx_rx_cts_rts},
  {ConnectorId::candidate_pa25_hsmci_mcck, PinId::PA25, PeripheralId::HSMCI, SignalId::signal_mcck, RouteId::candidate_pa25_hsmci_mcck, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_hsmci_lqfp100_all_signals},
  {ConnectorId::candidate_pa25_pwm0_pwmh2, PinId::PA25, PeripheralId::PWM0, SignalId::signal_pwmh2, RouteId::candidate_pa25_pwm0_pwmh2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa25_usart1_cts1, PinId::PA25, PeripheralId::USART1, SignalId::signal_cts1, RouteId::candidate_pa25_usart1_cts1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart1_lqfp100_tx_rx_cts_rts},
  {ConnectorId::candidate_pa26_hsmci_mcda2, PinId::PA26, PeripheralId::HSMCI, SignalId::signal_mcda2, RouteId::candidate_pa26_hsmci_mcda2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_hsmci_lqfp100_all_signals},
  {ConnectorId::candidate_pa26_pwm1_pwmfi1, PinId::PA26, PeripheralId::PWM1, SignalId::signal_pwmfi1, RouteId::candidate_pa26_pwm1_pwmfi1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pa26_tc0_tioa2, PinId::PA26, PeripheralId::TC0, SignalId::signal_tioa2, RouteId::candidate_pa26_tc0_tioa2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_tc0_lqfp100_all_signals},
  {ConnectorId::candidate_pa26_usart1_dcd1, PinId::PA26, PeripheralId::USART1, SignalId::signal_dcd1, RouteId::candidate_pa26_usart1_dcd1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pa27_hsmci_mcda3, PinId::PA27, PeripheralId::HSMCI, SignalId::signal_mcda3, RouteId::candidate_pa27_hsmci_mcda3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_hsmci_lqfp100_all_signals},
  {ConnectorId::candidate_pa27_tc0_tiob2, PinId::PA27, PeripheralId::TC0, SignalId::signal_tiob2, RouteId::candidate_pa27_tc0_tiob2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_tc0_lqfp100_all_signals},
  {ConnectorId::candidate_pa27_usart1_dtr1, PinId::PA27, PeripheralId::USART1, SignalId::signal_dtr1, RouteId::candidate_pa27_usart1_dtr1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pa28_hsmci_mccda, PinId::PA28, PeripheralId::HSMCI, SignalId::signal_mccda, RouteId::candidate_pa28_hsmci_mccda, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_hsmci_lqfp100_all_signals},
  {ConnectorId::candidate_pa28_pwm1_pwmfi2, PinId::PA28, PeripheralId::PWM1, SignalId::signal_pwmfi2, RouteId::candidate_pa28_pwm1_pwmfi2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pa28_tc0_tclk1, PinId::PA28, PeripheralId::TC0, SignalId::signal_tclk1, RouteId::candidate_pa28_tc0_tclk1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_tc0_lqfp100_all_signals},
  {ConnectorId::candidate_pa28_usart1_dsr1, PinId::PA28, PeripheralId::USART1, SignalId::signal_dsr1, RouteId::candidate_pa28_usart1_dsr1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pa2_dacc_datrg, PinId::PA2, PeripheralId::DACC, SignalId::signal_datrg, RouteId::candidate_pa2_dacc_datrg, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_dacc_lqfp100_all_signals},
  {ConnectorId::candidate_pa2_pwm0_pwmh1, PinId::PA2, PeripheralId::PWM0, SignalId::signal_pwmh1, RouteId::candidate_pa2_pwm0_pwmh1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa30_hsmci_mcda0, PinId::PA30, PeripheralId::HSMCI, SignalId::signal_mcda0, RouteId::candidate_pa30_hsmci_mcda0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_hsmci_lqfp100_all_signals},
  {ConnectorId::candidate_pa30_pwm0_pwml2, PinId::PA30, PeripheralId::PWM0, SignalId::signal_pwml2, RouteId::candidate_pa30_pwm0_pwml2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa30_pwm1_pwmextrg0, PinId::PA30, PeripheralId::PWM1, SignalId::signal_pwmextrg0, RouteId::candidate_pa30_pwm1_pwmextrg0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pa31_hsmci_mcda1, PinId::PA31, PeripheralId::HSMCI, SignalId::signal_mcda1, RouteId::candidate_pa31_hsmci_mcda1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_hsmci_lqfp100_all_signals},
  {ConnectorId::candidate_pa31_pwm1_pwmh2, PinId::PA31, PeripheralId::PWM1, SignalId::signal_pwmh2, RouteId::candidate_pa31_pwm1_pwmh2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pa31_spi0_npcs1, PinId::PA31, PeripheralId::SPI0, SignalId::signal_npcs1, RouteId::candidate_pa31_spi0_npcs1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_spi0_lqfp100_sck_cs},
  {ConnectorId::candidate_pa3_gpioa_piodc0, PinId::PA3, PeripheralId::GPIOA, SignalId::signal_piodc0, RouteId::candidate_pa3_gpioa_piodc0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gpioa_lqfp100_all_signals},
  {ConnectorId::candidate_pa3_twihs0_twd0, PinId::PA3, PeripheralId::TWIHS0, SignalId::signal_twd0, RouteId::candidate_pa3_twihs0_twd0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_twihs0_lqfp100_scl_sda},
  {ConnectorId::candidate_pa3_usart1_loncol1, PinId::PA3, PeripheralId::USART1, SignalId::signal_loncol1, RouteId::candidate_pa3_usart1_loncol1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pa4_gpioa_piodc1, PinId::PA4, PeripheralId::GPIOA, SignalId::signal_piodc1, RouteId::candidate_pa4_gpioa_piodc1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gpioa_lqfp100_all_signals},
  {ConnectorId::candidate_pa4_tc0_tclk0, PinId::PA4, PeripheralId::TC0, SignalId::signal_tclk0, RouteId::candidate_pa4_tc0_tclk0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_tc0_lqfp100_all_signals},
  {ConnectorId::candidate_pa4_twihs0_twck0, PinId::PA4, PeripheralId::TWIHS0, SignalId::signal_twck0, RouteId::candidate_pa4_twihs0_twck0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_twihs0_lqfp100_scl_sda},
  {ConnectorId::candidate_pa4_uart1_utxd1, PinId::PA4, PeripheralId::UART1, SignalId::signal_utxd1, RouteId::candidate_pa4_uart1_utxd1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_uart1_lqfp100_all_signals},
  {ConnectorId::candidate_pa5_gpioa_piodc2, PinId::PA5, PeripheralId::GPIOA, SignalId::signal_piodc2, RouteId::candidate_pa5_gpioa_piodc2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gpioa_lqfp100_all_signals},
  {ConnectorId::candidate_pa5_pwm1_pwml3, PinId::PA5, PeripheralId::PWM1, SignalId::signal_pwml3, RouteId::candidate_pa5_pwm1_pwml3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pa5_uart1_urxd1, PinId::PA5, PeripheralId::UART1, SignalId::signal_urxd1, RouteId::candidate_pa5_uart1_urxd1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_uart1_lqfp100_all_signals},
  {ConnectorId::candidate_pa7_pwm0_pwmh3, PinId::PA7, PeripheralId::PWM0, SignalId::signal_pwmh3, RouteId::candidate_pa7_pwm0_pwmh3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa8_afec0_adtrg, PinId::PA8, PeripheralId::AFEC0, SignalId::signal_adtrg, RouteId::candidate_pa8_afec0_adtrg, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_afec0_lqfp100_all_signals},
  {ConnectorId::candidate_pa8_pwm1_pwmh3, PinId::PA8, PeripheralId::PWM1, SignalId::signal_pwmh3, RouteId::candidate_pa8_pwm1_pwmh3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pa9_gpioa_piodc3, PinId::PA9, PeripheralId::GPIOA, SignalId::signal_piodc3, RouteId::candidate_pa9_gpioa_piodc3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gpioa_lqfp100_all_signals},
  {ConnectorId::candidate_pa9_pwm0_pwmfi0, PinId::PA9, PeripheralId::PWM0, SignalId::signal_pwmfi0, RouteId::candidate_pa9_pwm0_pwmfi0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pa9_uart0_urxd0, PinId::PA9, PeripheralId::UART0, SignalId::signal_urxd0, RouteId::candidate_pa9_uart0_urxd0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_uart0_lqfp100_all_signals},
  {ConnectorId::candidate_pb0_afec0_ad10, PinId::PB0, PeripheralId::AFEC0, SignalId::signal_ad10, RouteId::candidate_pb0_afec0_ad10, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_afec0_lqfp100_all_signals},
  {ConnectorId::candidate_pb0_pwm0_pwmh0, PinId::PB0, PeripheralId::PWM0, SignalId::signal_pwmh0, RouteId::candidate_pb0_pwm0_pwmh0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pb0_rtc_rtcout0, PinId::PB0, PeripheralId::RTC, SignalId::signal_rtcout0, RouteId::candidate_pb0_rtc_rtcout0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_rtc_lqfp100_all_signals},
  {ConnectorId::candidate_pb0_usart0_rxd0, PinId::PB0, PeripheralId::USART0, SignalId::signal_rxd0, RouteId::candidate_pb0_usart0_rxd0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart0_lqfp100_tx_rx},
  {ConnectorId::candidate_pb12_gmac_gtsucomp, PinId::PB12, PeripheralId::GMAC, SignalId::signal_gtsucomp, RouteId::candidate_pb12_gmac_gtsucomp, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pb12_pwm0_pwml1, PinId::PB12, PeripheralId::PWM0, SignalId::signal_pwml1, RouteId::candidate_pb12_pwm0_pwml1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pb13_dacc_dac0, PinId::PB13, PeripheralId::DACC, SignalId::signal_dac0, RouteId::candidate_pb13_dacc_dac0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_dacc_lqfp100_all_signals},
  {ConnectorId::candidate_pb13_pwm0_pwml2, PinId::PB13, PeripheralId::PWM0, SignalId::signal_pwml2, RouteId::candidate_pb13_pwm0_pwml2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pb13_usart0_sck0, PinId::PB13, PeripheralId::USART0, SignalId::signal_sck0, RouteId::candidate_pb13_usart0_sck0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pb1_afec1_ad0, PinId::PB1, PeripheralId::AFEC1, SignalId::signal_ad0, RouteId::candidate_pb1_afec1_ad0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_afec1_lqfp100_all_signals},
  {ConnectorId::candidate_pb1_gmac_gtsucomp, PinId::PB1, PeripheralId::GMAC, SignalId::signal_gtsucomp, RouteId::candidate_pb1_gmac_gtsucomp, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pb1_pwm0_pwmh1, PinId::PB1, PeripheralId::PWM0, SignalId::signal_pwmh1, RouteId::candidate_pb1_pwm0_pwmh1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pb1_rtc_rtcout1, PinId::PB1, PeripheralId::RTC, SignalId::signal_rtcout1, RouteId::candidate_pb1_rtc_rtcout1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_rtc_lqfp100_all_signals},
  {ConnectorId::candidate_pb1_usart0_txd0, PinId::PB1, PeripheralId::USART0, SignalId::signal_txd0, RouteId::candidate_pb1_usart0_txd0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart0_lqfp100_tx_rx},
  {ConnectorId::candidate_pb2_afec0_ad5, PinId::PB2, PeripheralId::AFEC0, SignalId::signal_ad5, RouteId::candidate_pb2_afec0_ad5, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_afec0_lqfp100_all_signals},
  {ConnectorId::candidate_pb2_mcan0_cantx0, PinId::PB2, PeripheralId::MCAN0, SignalId::signal_cantx0, RouteId::candidate_pb2_mcan0_cantx0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_mcan0_lqfp100_tx_rx},
  {ConnectorId::candidate_pb2_spi0_npcs0, PinId::PB2, PeripheralId::SPI0, SignalId::signal_npcs0, RouteId::candidate_pb2_spi0_npcs0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_spi0_lqfp100_sck_cs},
  {ConnectorId::candidate_pb2_usart0_cts0, PinId::PB2, PeripheralId::USART0, SignalId::signal_cts0, RouteId::candidate_pb2_usart0_cts0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart0_lqfp100_tx_rx_cts_rts},
  {ConnectorId::candidate_pb3_afec0_ad2, PinId::PB3, PeripheralId::AFEC0, SignalId::signal_ad2, RouteId::candidate_pb3_afec0_ad2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_afec0_lqfp100_all_signals},
  {ConnectorId::candidate_pb3_mcan0_canrx0, PinId::PB3, PeripheralId::MCAN0, SignalId::signal_canrx0, RouteId::candidate_pb3_mcan0_canrx0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_mcan0_lqfp100_tx_rx},
  {ConnectorId::candidate_pb3_usart0_rts0, PinId::PB3, PeripheralId::USART0, SignalId::signal_rts0, RouteId::candidate_pb3_usart0_rts0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart0_lqfp100_tx_rx_cts_rts},
  {ConnectorId::candidate_pb4_pwm0_pwmh2, PinId::PB4, PeripheralId::PWM0, SignalId::signal_pwmh2, RouteId::candidate_pb4_pwm0_pwmh2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pb4_twihs1_twd1, PinId::PB4, PeripheralId::TWIHS1, SignalId::signal_twd1, RouteId::candidate_pb4_twihs1_twd1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_twihs1_lqfp100_scl_sda},
  {ConnectorId::candidate_pb4_usart1_txd1, PinId::PB4, PeripheralId::USART1, SignalId::signal_txd1, RouteId::candidate_pb4_usart1_txd1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart1_lqfp100_tx_rx},
  {ConnectorId::candidate_pb5_pwm0_pwml0, PinId::PB5, PeripheralId::PWM0, SignalId::signal_pwml0, RouteId::candidate_pb5_pwm0_pwml0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pb5_twihs1_twck1, PinId::PB5, PeripheralId::TWIHS1, SignalId::signal_twck1, RouteId::candidate_pb5_twihs1_twck1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_twihs1_lqfp100_scl_sda},
  {ConnectorId::candidate_pd0_dacc_dac1, PinId::PD0, PeripheralId::DACC, SignalId::signal_dac1, RouteId::candidate_pd0_dacc_dac1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_dacc_lqfp100_all_signals},
  {ConnectorId::candidate_pd0_gmac_gtxck, PinId::PD0, PeripheralId::GMAC, SignalId::signal_gtxck, RouteId::candidate_pd0_gmac_gtxck, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd0_pwm1_pwml0, PinId::PD0, PeripheralId::PWM1, SignalId::signal_pwml0, RouteId::candidate_pd0_pwm1_pwml0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pd0_usart0_dcd0, PinId::PD0, PeripheralId::USART0, SignalId::signal_dcd0, RouteId::candidate_pd0_usart0_dcd0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pd10_gmac_gcrs, PinId::PD10, PeripheralId::GMAC, SignalId::signal_gcrs, RouteId::candidate_pd10_gmac_gcrs, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd10_pwm0_pwml0, PinId::PD10, PeripheralId::PWM0, SignalId::signal_pwml0, RouteId::candidate_pd10_pwm0_pwml0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pd11_gmac_grx2, PinId::PD11, PeripheralId::GMAC, SignalId::signal_grx2, RouteId::candidate_pd11_gmac_grx2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd11_gmac_gtsucomp, PinId::PD11, PeripheralId::GMAC, SignalId::signal_gtsucomp, RouteId::candidate_pd11_gmac_gtsucomp, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd11_pwm0_pwmh0, PinId::PD11, PeripheralId::PWM0, SignalId::signal_pwmh0, RouteId::candidate_pd11_pwm0_pwmh0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pd12_gmac_grx3, PinId::PD12, PeripheralId::GMAC, SignalId::signal_grx3, RouteId::candidate_pd12_gmac_grx3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd12_mcan1_cantx1, PinId::PD12, PeripheralId::MCAN1, SignalId::signal_cantx1, RouteId::candidate_pd12_mcan1_cantx1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_mcan1_lqfp100_tx_rx},
  {ConnectorId::candidate_pd12_spi0_npcs2, PinId::PD12, PeripheralId::SPI0, SignalId::signal_npcs2, RouteId::candidate_pd12_spi0_npcs2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_spi0_lqfp100_sck_cs},
  {ConnectorId::candidate_pd13_gmac_gcol, PinId::PD13, PeripheralId::GMAC, SignalId::signal_gcol, RouteId::candidate_pd13_gmac_gcol, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd14_gmac_grxck, PinId::PD14, PeripheralId::GMAC, SignalId::signal_grxck, RouteId::candidate_pd14_gmac_grxck, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd15_gmac_gtx2, PinId::PD15, PeripheralId::GMAC, SignalId::signal_gtx2, RouteId::candidate_pd15_gmac_gtx2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd15_usart2_rxd2, PinId::PD15, PeripheralId::USART2, SignalId::signal_rxd2, RouteId::candidate_pd15_usart2_rxd2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart2_lqfp100_tx_rx},
  {ConnectorId::candidate_pd16_gmac_gtx3, PinId::PD16, PeripheralId::GMAC, SignalId::signal_gtx3, RouteId::candidate_pd16_gmac_gtx3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd16_usart2_txd2, PinId::PD16, PeripheralId::USART2, SignalId::signal_txd2, RouteId::candidate_pd16_usart2_txd2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart2_lqfp100_tx_rx},
  {ConnectorId::candidate_pd17_gmac_gtxer, PinId::PD17, PeripheralId::GMAC, SignalId::signal_gtxer, RouteId::candidate_pd17_gmac_gtxer, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd17_usart2_sck2, PinId::PD17, PeripheralId::USART2, SignalId::signal_sck2, RouteId::candidate_pd17_usart2_sck2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pd18_uart4_urxd4, PinId::PD18, PeripheralId::UART4, SignalId::signal_urxd4, RouteId::candidate_pd18_uart4_urxd4, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_uart4_lqfp100_all_signals},
  {ConnectorId::candidate_pd18_usart2_rts2, PinId::PD18, PeripheralId::USART2, SignalId::signal_rts2, RouteId::candidate_pd18_usart2_rts2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart2_lqfp100_tx_rx_cts_rts},
  {ConnectorId::candidate_pd19_uart4_utxd4, PinId::PD19, PeripheralId::UART4, SignalId::signal_utxd4, RouteId::candidate_pd19_uart4_utxd4, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_uart4_lqfp100_all_signals},
  {ConnectorId::candidate_pd19_usart2_cts2, PinId::PD19, PeripheralId::USART2, SignalId::signal_cts2, RouteId::candidate_pd19_usart2_cts2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart2_lqfp100_tx_rx_cts_rts},
  {ConnectorId::candidate_pd1_gmac_gtxen, PinId::PD1, PeripheralId::GMAC, SignalId::signal_gtxen, RouteId::candidate_pd1_gmac_gtxen, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd1_pwm1_pwmh0, PinId::PD1, PeripheralId::PWM1, SignalId::signal_pwmh0, RouteId::candidate_pd1_pwm1_pwmh0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pd1_usart0_dtr0, PinId::PD1, PeripheralId::USART0, SignalId::signal_dtr0, RouteId::candidate_pd1_usart0_dtr0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pd20_gmac_gtsucomp, PinId::PD20, PeripheralId::GMAC, SignalId::signal_gtsucomp, RouteId::candidate_pd20_gmac_gtsucomp, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd20_pwm0_pwmh0, PinId::PD20, PeripheralId::PWM0, SignalId::signal_pwmh0, RouteId::candidate_pd20_pwm0_pwmh0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pd20_spi0_miso, PinId::PD20, PeripheralId::SPI0, SignalId::signal_miso, RouteId::candidate_pd20_spi0_miso, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_spi0_lqfp100_sck_mosi_miso},
  {ConnectorId::candidate_pd21_pwm0_pwmh1, PinId::PD21, PeripheralId::PWM0, SignalId::signal_pwmh1, RouteId::candidate_pd21_pwm0_pwmh1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pd21_spi0_mosi, PinId::PD21, PeripheralId::SPI0, SignalId::signal_mosi, RouteId::candidate_pd21_spi0_mosi, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_spi0_lqfp100_sck_mosi_miso},
  {ConnectorId::candidate_pd21_tc3_tioa11, PinId::PD21, PeripheralId::TC3, SignalId::signal_tioa11, RouteId::candidate_pd21_tc3_tioa11, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_tc3_lqfp100_all_signals},
  {ConnectorId::candidate_pd22_pwm0_pwmh2, PinId::PD22, PeripheralId::PWM0, SignalId::signal_pwmh2, RouteId::candidate_pd22_pwm0_pwmh2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pd22_spi0_spck, PinId::PD22, PeripheralId::SPI0, SignalId::signal_spck, RouteId::candidate_pd22_spi0_spck, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_spi0_lqfp100_sck_mosi_miso},
  {ConnectorId::candidate_pd22_tc3_tiob11, PinId::PD22, PeripheralId::TC3, SignalId::signal_tiob11, RouteId::candidate_pd22_tc3_tiob11, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_tc3_lqfp100_all_signals},
  {ConnectorId::candidate_pd24_pwm0_pwml0, PinId::PD24, PeripheralId::PWM0, SignalId::signal_pwml0, RouteId::candidate_pd24_pwm0_pwml0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pd24_tc3_tclk11, PinId::PD24, PeripheralId::TC3, SignalId::signal_tclk11, RouteId::candidate_pd24_tc3_tclk11, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_tc3_lqfp100_all_signals},
  {ConnectorId::candidate_pd25_pwm0_pwml1, PinId::PD25, PeripheralId::PWM0, SignalId::signal_pwml1, RouteId::candidate_pd25_pwm0_pwml1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pd25_spi0_npcs1, PinId::PD25, PeripheralId::SPI0, SignalId::signal_npcs1, RouteId::candidate_pd25_spi0_npcs1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_spi0_lqfp100_sck_cs},
  {ConnectorId::candidate_pd25_uart2_urxd2, PinId::PD25, PeripheralId::UART2, SignalId::signal_urxd2, RouteId::candidate_pd25_uart2_urxd2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_uart2_lqfp100_all_signals},
  {ConnectorId::candidate_pd26_pwm0_pwml2, PinId::PD26, PeripheralId::PWM0, SignalId::signal_pwml2, RouteId::candidate_pd26_pwm0_pwml2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pd26_uart1_utxd1, PinId::PD26, PeripheralId::UART1, SignalId::signal_utxd1, RouteId::candidate_pd26_uart1_utxd1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_uart1_lqfp100_all_signals},
  {ConnectorId::candidate_pd26_uart2_utxd2, PinId::PD26, PeripheralId::UART2, SignalId::signal_utxd2, RouteId::candidate_pd26_uart2_utxd2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_uart2_lqfp100_all_signals},
  {ConnectorId::candidate_pd27_pwm0_pwml3, PinId::PD27, PeripheralId::PWM0, SignalId::signal_pwml3, RouteId::candidate_pd27_pwm0_pwml3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pd27_spi0_npcs3, PinId::PD27, PeripheralId::SPI0, SignalId::signal_npcs3, RouteId::candidate_pd27_spi0_npcs3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_spi0_lqfp100_sck_cs},
  {ConnectorId::candidate_pd27_twihs2_twd2, PinId::PD27, PeripheralId::TWIHS2, SignalId::signal_twd2, RouteId::candidate_pd27_twihs2_twd2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_twihs2_lqfp100_scl_sda},
  {ConnectorId::candidate_pd28_mcan1_canrx1, PinId::PD28, PeripheralId::MCAN1, SignalId::signal_canrx1, RouteId::candidate_pd28_mcan1_canrx1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_mcan1_lqfp100_tx_rx},
  {ConnectorId::candidate_pd28_twihs2_twck2, PinId::PD28, PeripheralId::TWIHS2, SignalId::signal_twck2, RouteId::candidate_pd28_twihs2_twck2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_twihs2_lqfp100_scl_sda},
  {ConnectorId::candidate_pd28_uart3_urxd3, PinId::PD28, PeripheralId::UART3, SignalId::signal_urxd3, RouteId::candidate_pd28_uart3_urxd3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_uart3_lqfp100_all_signals},
  {ConnectorId::candidate_pd2_gmac_gtx0, PinId::PD2, PeripheralId::GMAC, SignalId::signal_gtx0, RouteId::candidate_pd2_gmac_gtx0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd2_pwm1_pwml1, PinId::PD2, PeripheralId::PWM1, SignalId::signal_pwml1, RouteId::candidate_pd2_pwm1_pwml1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pd2_usart0_dsr0, PinId::PD2, PeripheralId::USART0, SignalId::signal_dsr0, RouteId::candidate_pd2_usart0_dsr0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pd30_afec0_ad0, PinId::PD30, PeripheralId::AFEC0, SignalId::signal_ad0, RouteId::candidate_pd30_afec0_ad0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_afec0_lqfp100_all_signals},
  {ConnectorId::candidate_pd30_uart3_utxd3, PinId::PD30, PeripheralId::UART3, SignalId::signal_utxd3, RouteId::candidate_pd30_uart3_utxd3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_uart3_lqfp100_all_signals},
  {ConnectorId::candidate_pd31_qspi_qio3, PinId::PD31, PeripheralId::QSPI, SignalId::signal_qio3, RouteId::candidate_pd31_qspi_qio3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_qspi_lqfp100_all_signals},
  {ConnectorId::candidate_pd31_uart3_utxd3, PinId::PD31, PeripheralId::UART3, SignalId::signal_utxd3, RouteId::candidate_pd31_uart3_utxd3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_uart3_lqfp100_all_signals},
  {ConnectorId::candidate_pd3_gmac_gtx1, PinId::PD3, PeripheralId::GMAC, SignalId::signal_gtx1, RouteId::candidate_pd3_gmac_gtx1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd3_pwm1_pwmh1, PinId::PD3, PeripheralId::PWM1, SignalId::signal_pwmh1, RouteId::candidate_pd3_pwm1_pwmh1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pd3_uart4_utxd4, PinId::PD3, PeripheralId::UART4, SignalId::signal_utxd4, RouteId::candidate_pd3_uart4_utxd4, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_uart4_lqfp100_all_signals},
  {ConnectorId::candidate_pd3_usart0_ri0, PinId::PD3, PeripheralId::USART0, SignalId::signal_ri0, RouteId::candidate_pd3_usart0_ri0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pd4_gmac_grxdv, PinId::PD4, PeripheralId::GMAC, SignalId::signal_grxdv, RouteId::candidate_pd4_gmac_grxdv, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd4_pwm1_pwml2, PinId::PD4, PeripheralId::PWM1, SignalId::signal_pwml2, RouteId::candidate_pd4_pwm1_pwml2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pd4_usart2_dcd2, PinId::PD4, PeripheralId::USART2, SignalId::signal_dcd2, RouteId::candidate_pd4_usart2_dcd2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pd5_gmac_grx0, PinId::PD5, PeripheralId::GMAC, SignalId::signal_grx0, RouteId::candidate_pd5_gmac_grx0, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd5_pwm1_pwmh2, PinId::PD5, PeripheralId::PWM1, SignalId::signal_pwmh2, RouteId::candidate_pd5_pwm1_pwmh2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pd5_usart2_dtr2, PinId::PD5, PeripheralId::USART2, SignalId::signal_dtr2, RouteId::candidate_pd5_usart2_dtr2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pd6_gmac_grx1, PinId::PD6, PeripheralId::GMAC, SignalId::signal_grx1, RouteId::candidate_pd6_gmac_grx1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd6_pwm1_pwml3, PinId::PD6, PeripheralId::PWM1, SignalId::signal_pwml3, RouteId::candidate_pd6_pwm1_pwml3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pd6_usart2_dsr2, PinId::PD6, PeripheralId::USART2, SignalId::signal_dsr2, RouteId::candidate_pd6_usart2_dsr2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pd7_gmac_grxer, PinId::PD7, PeripheralId::GMAC, SignalId::signal_grxer, RouteId::candidate_pd7_gmac_grxer, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd7_pwm1_pwmh3, PinId::PD7, PeripheralId::PWM1, SignalId::signal_pwmh3, RouteId::candidate_pd7_pwm1_pwmh3, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm1_lqfp100_all_signals},
  {ConnectorId::candidate_pd7_usart2_ri2, PinId::PD7, PeripheralId::USART2, SignalId::signal_ri2, RouteId::candidate_pd7_usart2_ri2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pd8_gmac_gmdc, PinId::PD8, PeripheralId::GMAC, SignalId::signal_gmdc, RouteId::candidate_pd8_gmac_gmdc, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd8_pwm0_pwmfi1, PinId::PD8, PeripheralId::PWM0, SignalId::signal_pwmfi1, RouteId::candidate_pd8_pwm0_pwmfi1, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
  {ConnectorId::candidate_pd9_afec1_adtrg, PinId::PD9, PeripheralId::AFEC1, SignalId::signal_adtrg, RouteId::candidate_pd9_afec1_adtrg, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_afec1_lqfp100_all_signals},
  {ConnectorId::candidate_pd9_gmac_gmdio, PinId::PD9, PeripheralId::GMAC, SignalId::signal_gmdio, RouteId::candidate_pd9_gmac_gmdio, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_gmac_lqfp100_all_signals},
  {ConnectorId::candidate_pd9_pwm0_pwmfi2, PinId::PD9, PeripheralId::PWM0, SignalId::signal_pwmfi2, RouteId::candidate_pd9_pwm0_pwmfi2, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_pwm0_lqfp100_all_signals},
}};
}
}
}
}
}
}
