#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "routes.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace pico {
enum class ConnectorId : std::uint16_t {
  none,
  candidate_gp0_i2c0_sda,
  candidate_gp0_spi0_rx,
  candidate_gp0_uart0_tx,
  candidate_gp10_i2c1_sda,
  candidate_gp10_spi1_sck,
  candidate_gp10_uart1_cts,
  candidate_gp11_i2c1_scl,
  candidate_gp11_spi1_tx,
  candidate_gp11_uart1_rts,
  candidate_gp12_i2c0_sda,
  candidate_gp12_spi1_rx,
  candidate_gp12_uart0_tx,
  candidate_gp13_i2c0_scl,
  candidate_gp13_spi1_csn,
  candidate_gp13_uart0_rx,
  candidate_gp14_i2c1_sda,
  candidate_gp14_spi1_sck,
  candidate_gp14_uart0_cts,
  candidate_gp15_i2c1_scl,
  candidate_gp15_spi1_tx,
  candidate_gp15_uart0_rts,
  candidate_gp16_i2c0_sda,
  candidate_gp16_spi0_rx,
  candidate_gp16_uart0_tx,
  candidate_gp17_i2c0_scl,
  candidate_gp17_spi0_csn,
  candidate_gp17_uart0_rx,
  candidate_gp18_i2c1_sda,
  candidate_gp18_spi0_sck,
  candidate_gp18_uart0_cts,
  candidate_gp19_i2c1_scl,
  candidate_gp19_spi0_tx,
  candidate_gp19_uart0_rts,
  candidate_gp1_i2c0_scl,
  candidate_gp1_spi0_csn,
  candidate_gp1_uart0_rx,
  candidate_gp20_i2c0_sda,
  candidate_gp20_spi0_rx,
  candidate_gp20_uart1_tx,
  candidate_gp21_i2c0_scl,
  candidate_gp21_spi0_csn,
  candidate_gp21_uart1_rx,
  candidate_gp22_i2c1_sda,
  candidate_gp22_spi0_sck,
  candidate_gp22_uart1_cts,
  candidate_gp25_i2c0_scl,
  candidate_gp25_spi1_csn,
  candidate_gp25_uart1_tx,
  candidate_gp26_adc_ch0,
  candidate_gp27_adc_ch1,
  candidate_gp28_adc_ch2,
  candidate_gp2_i2c1_sda,
  candidate_gp2_spi0_sck,
  candidate_gp2_uart0_cts,
  candidate_gp3_i2c1_scl,
  candidate_gp3_spi0_tx,
  candidate_gp3_uart0_rts,
  candidate_gp4_i2c0_sda,
  candidate_gp4_spi0_rx,
  candidate_gp4_uart1_tx,
  candidate_gp5_i2c0_scl,
  candidate_gp5_spi0_csn,
  candidate_gp5_uart1_rx,
  candidate_gp6_i2c1_sda,
  candidate_gp6_spi0_sck,
  candidate_gp6_uart1_cts,
  candidate_gp7_i2c1_scl,
  candidate_gp7_spi0_tx,
  candidate_gp7_uart1_rts,
  candidate_gp8_i2c0_sda,
  candidate_gp8_spi1_rx,
  candidate_gp8_uart1_tx,
  candidate_gp9_i2c0_scl,
  candidate_gp9_spi1_csn,
  candidate_gp9_uart1_rx,
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
struct ConnectorTraits<PinId::GP0, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp0_i2c0_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_gp0_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP0, PeripheralId::SPI0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp0_spi0_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp0_spi0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP0, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp0_uart0_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp0_uart0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_pico_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GP10, PeripheralId::I2C1, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp10_i2c1_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_gp10_i2c1_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c1_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP10, PeripheralId::SPI1, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp10_spi1_sck;
  static constexpr RouteId kRouteId = RouteId::candidate_gp10_spi1_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi1_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP10, PeripheralId::UART1, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp10_uart1_cts;
  static constexpr RouteId kRouteId = RouteId::candidate_gp10_uart1_cts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_pico_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::GP11, PeripheralId::I2C1, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp11_i2c1_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_gp11_i2c1_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c1_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP11, PeripheralId::SPI1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp11_spi1_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp11_spi1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi1_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP11, PeripheralId::UART1, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp11_uart1_rts;
  static constexpr RouteId kRouteId = RouteId::candidate_gp11_uart1_rts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_pico_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::GP12, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp12_i2c0_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_gp12_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP12, PeripheralId::SPI1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp12_spi1_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp12_spi1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi1_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP12, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp12_uart0_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp12_uart0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_pico_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GP13, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp13_i2c0_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_gp13_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP13, PeripheralId::SPI1, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp13_spi1_csn;
  static constexpr RouteId kRouteId = RouteId::candidate_gp13_spi1_csn;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi1_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP13, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp13_uart0_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp13_uart0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_pico_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GP14, PeripheralId::I2C1, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp14_i2c1_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_gp14_i2c1_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c1_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP14, PeripheralId::SPI1, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp14_spi1_sck;
  static constexpr RouteId kRouteId = RouteId::candidate_gp14_spi1_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi1_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP14, PeripheralId::UART0, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp14_uart0_cts;
  static constexpr RouteId kRouteId = RouteId::candidate_gp14_uart0_cts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_pico_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::GP15, PeripheralId::I2C1, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp15_i2c1_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_gp15_i2c1_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c1_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP15, PeripheralId::SPI1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp15_spi1_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp15_spi1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi1_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP15, PeripheralId::UART0, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp15_uart0_rts;
  static constexpr RouteId kRouteId = RouteId::candidate_gp15_uart0_rts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_pico_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::GP16, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp16_i2c0_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_gp16_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP16, PeripheralId::SPI0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp16_spi0_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp16_spi0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP16, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp16_uart0_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp16_uart0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_pico_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GP17, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp17_i2c0_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_gp17_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP17, PeripheralId::SPI0, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp17_spi0_csn;
  static constexpr RouteId kRouteId = RouteId::candidate_gp17_spi0_csn;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP17, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp17_uart0_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp17_uart0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_pico_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GP18, PeripheralId::I2C1, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp18_i2c1_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_gp18_i2c1_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c1_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP18, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp18_spi0_sck;
  static constexpr RouteId kRouteId = RouteId::candidate_gp18_spi0_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP18, PeripheralId::UART0, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp18_uart0_cts;
  static constexpr RouteId kRouteId = RouteId::candidate_gp18_uart0_cts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_pico_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::GP19, PeripheralId::I2C1, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp19_i2c1_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_gp19_i2c1_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c1_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP19, PeripheralId::SPI0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp19_spi0_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp19_spi0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP19, PeripheralId::UART0, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp19_uart0_rts;
  static constexpr RouteId kRouteId = RouteId::candidate_gp19_uart0_rts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_pico_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::GP1, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp1_i2c0_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_gp1_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP1, PeripheralId::SPI0, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp1_spi0_csn;
  static constexpr RouteId kRouteId = RouteId::candidate_gp1_spi0_csn;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP1, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp1_uart0_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp1_uart0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_pico_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GP20, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp20_i2c0_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_gp20_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP20, PeripheralId::SPI0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp20_spi0_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp20_spi0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP20, PeripheralId::UART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp20_uart1_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp20_uart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_pico_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GP21, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp21_i2c0_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_gp21_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP21, PeripheralId::SPI0, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp21_spi0_csn;
  static constexpr RouteId kRouteId = RouteId::candidate_gp21_spi0_csn;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP21, PeripheralId::UART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp21_uart1_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp21_uart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_pico_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GP22, PeripheralId::I2C1, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp22_i2c1_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_gp22_i2c1_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c1_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP22, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp22_spi0_sck;
  static constexpr RouteId kRouteId = RouteId::candidate_gp22_spi0_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP22, PeripheralId::UART1, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp22_uart1_cts;
  static constexpr RouteId kRouteId = RouteId::candidate_gp22_uart1_cts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_pico_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::GP25, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp25_i2c0_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_gp25_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP25, PeripheralId::SPI1, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp25_spi1_csn;
  static constexpr RouteId kRouteId = RouteId::candidate_gp25_spi1_csn;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi1_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP25, PeripheralId::UART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp25_uart1_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp25_uart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_pico_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GP26, PeripheralId::ADC, SignalId::signal_ch0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp26_adc_ch0;
  static constexpr RouteId kRouteId = RouteId::candidate_gp26_adc_ch0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_adc_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP27, PeripheralId::ADC, SignalId::signal_ch1> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp27_adc_ch1;
  static constexpr RouteId kRouteId = RouteId::candidate_gp27_adc_ch1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_adc_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP28, PeripheralId::ADC, SignalId::signal_ch2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp28_adc_ch2;
  static constexpr RouteId kRouteId = RouteId::candidate_gp28_adc_ch2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_adc_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP2, PeripheralId::I2C1, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp2_i2c1_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_gp2_i2c1_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c1_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP2, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp2_spi0_sck;
  static constexpr RouteId kRouteId = RouteId::candidate_gp2_spi0_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP2, PeripheralId::UART0, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp2_uart0_cts;
  static constexpr RouteId kRouteId = RouteId::candidate_gp2_uart0_cts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_pico_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::GP3, PeripheralId::I2C1, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp3_i2c1_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_gp3_i2c1_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c1_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP3, PeripheralId::SPI0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp3_spi0_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp3_spi0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP3, PeripheralId::UART0, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp3_uart0_rts;
  static constexpr RouteId kRouteId = RouteId::candidate_gp3_uart0_rts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_pico_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::GP4, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp4_i2c0_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_gp4_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP4, PeripheralId::SPI0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp4_spi0_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp4_spi0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP4, PeripheralId::UART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp4_uart1_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp4_uart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_pico_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GP5, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp5_i2c0_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_gp5_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP5, PeripheralId::SPI0, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp5_spi0_csn;
  static constexpr RouteId kRouteId = RouteId::candidate_gp5_spi0_csn;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP5, PeripheralId::UART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp5_uart1_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp5_uart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_pico_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GP6, PeripheralId::I2C1, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp6_i2c1_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_gp6_i2c1_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c1_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP6, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp6_spi0_sck;
  static constexpr RouteId kRouteId = RouteId::candidate_gp6_spi0_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP6, PeripheralId::UART1, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp6_uart1_cts;
  static constexpr RouteId kRouteId = RouteId::candidate_gp6_uart1_cts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_pico_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::GP7, PeripheralId::I2C1, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp7_i2c1_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_gp7_i2c1_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c1_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP7, PeripheralId::SPI0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp7_spi0_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp7_spi0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP7, PeripheralId::UART1, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp7_uart1_rts;
  static constexpr RouteId kRouteId = RouteId::candidate_gp7_uart1_rts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_pico_tx_rx_cts_rts;
};

template<>
struct ConnectorTraits<PinId::GP8, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp8_i2c0_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_gp8_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP8, PeripheralId::SPI1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp8_spi1_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp8_spi1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi1_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP8, PeripheralId::UART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp8_uart1_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp8_uart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_pico_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GP9, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp9_i2c0_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_gp9_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_pico_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GP9, PeripheralId::SPI1, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp9_spi1_csn;
  static constexpr RouteId kRouteId = RouteId::candidate_gp9_spi1_csn;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi1_pico_all_signals;
};

template<>
struct ConnectorTraits<PinId::GP9, PeripheralId::UART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gp9_uart1_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gp9_uart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_pico_tx_rx;
};

template<>
struct ConnectorSignalTraits<PeripheralId::ADC, SignalId::signal_ch0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GP26,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gp26_adc_ch0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::ADC, SignalId::signal_ch0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for ADC ch0. Valid pins: GP26. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::ADC, SignalId::signal_ch1> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GP27,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gp27_adc_ch1,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::ADC, SignalId::signal_ch1> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for ADC ch1. Valid pins: GP27. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::ADC, SignalId::signal_ch2> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GP28,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gp28_adc_ch2,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::ADC, SignalId::signal_ch2> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for ADC ch2. Valid pins: GP28. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 7> kPins = {{
    PinId::GP13,
    PinId::GP17,
    PinId::GP1,
    PinId::GP21,
    PinId::GP25,
    PinId::GP5,
    PinId::GP9,
  }};
  static constexpr std::array<ConnectorId, 7> kConnectors = {{
    ConnectorId::candidate_gp13_i2c0_scl,
    ConnectorId::candidate_gp17_i2c0_scl,
    ConnectorId::candidate_gp1_i2c0_scl,
    ConnectorId::candidate_gp21_i2c0_scl,
    ConnectorId::candidate_gp25_i2c0_scl,
    ConnectorId::candidate_gp5_i2c0_scl,
    ConnectorId::candidate_gp9_i2c0_scl,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for I2C0 scl. Valid pins: GP13, GP17, GP1, GP21, GP25, GP5, GP9. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 6> kPins = {{
    PinId::GP0,
    PinId::GP12,
    PinId::GP16,
    PinId::GP20,
    PinId::GP4,
    PinId::GP8,
  }};
  static constexpr std::array<ConnectorId, 6> kConnectors = {{
    ConnectorId::candidate_gp0_i2c0_sda,
    ConnectorId::candidate_gp12_i2c0_sda,
    ConnectorId::candidate_gp16_i2c0_sda,
    ConnectorId::candidate_gp20_i2c0_sda,
    ConnectorId::candidate_gp4_i2c0_sda,
    ConnectorId::candidate_gp8_i2c0_sda,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for I2C0 sda. Valid pins: GP0, GP12, GP16, GP20, GP4, GP8. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::I2C1, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 5> kPins = {{
    PinId::GP11,
    PinId::GP15,
    PinId::GP19,
    PinId::GP3,
    PinId::GP7,
  }};
  static constexpr std::array<ConnectorId, 5> kConnectors = {{
    ConnectorId::candidate_gp11_i2c1_scl,
    ConnectorId::candidate_gp15_i2c1_scl,
    ConnectorId::candidate_gp19_i2c1_scl,
    ConnectorId::candidate_gp3_i2c1_scl,
    ConnectorId::candidate_gp7_i2c1_scl,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::I2C1, SignalId::signal_scl> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for I2C1 scl. Valid pins: GP11, GP15, GP19, GP3, GP7. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::I2C1, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 6> kPins = {{
    PinId::GP10,
    PinId::GP14,
    PinId::GP18,
    PinId::GP22,
    PinId::GP2,
    PinId::GP6,
  }};
  static constexpr std::array<ConnectorId, 6> kConnectors = {{
    ConnectorId::candidate_gp10_i2c1_sda,
    ConnectorId::candidate_gp14_i2c1_sda,
    ConnectorId::candidate_gp18_i2c1_sda,
    ConnectorId::candidate_gp22_i2c1_sda,
    ConnectorId::candidate_gp2_i2c1_sda,
    ConnectorId::candidate_gp6_i2c1_sda,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::I2C1, SignalId::signal_sda> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for I2C1 sda. Valid pins: GP10, GP14, GP18, GP22, GP2, GP6. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 4> kPins = {{
    PinId::GP17,
    PinId::GP1,
    PinId::GP21,
    PinId::GP5,
  }};
  static constexpr std::array<ConnectorId, 4> kConnectors = {{
    ConnectorId::candidate_gp17_spi0_csn,
    ConnectorId::candidate_gp1_spi0_csn,
    ConnectorId::candidate_gp21_spi0_csn,
    ConnectorId::candidate_gp5_spi0_csn,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_csn> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 csn. Valid pins: GP17, GP1, GP21, GP5. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 4> kPins = {{
    PinId::GP0,
    PinId::GP16,
    PinId::GP20,
    PinId::GP4,
  }};
  static constexpr std::array<ConnectorId, 4> kConnectors = {{
    ConnectorId::candidate_gp0_spi0_rx,
    ConnectorId::candidate_gp16_spi0_rx,
    ConnectorId::candidate_gp20_spi0_rx,
    ConnectorId::candidate_gp4_spi0_rx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_rx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 rx. Valid pins: GP0, GP16, GP20, GP4. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 4> kPins = {{
    PinId::GP18,
    PinId::GP22,
    PinId::GP2,
    PinId::GP6,
  }};
  static constexpr std::array<ConnectorId, 4> kConnectors = {{
    ConnectorId::candidate_gp18_spi0_sck,
    ConnectorId::candidate_gp22_spi0_sck,
    ConnectorId::candidate_gp2_spi0_sck,
    ConnectorId::candidate_gp6_spi0_sck,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 sck. Valid pins: GP18, GP22, GP2, GP6. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 3> kPins = {{
    PinId::GP19,
    PinId::GP3,
    PinId::GP7,
  }};
  static constexpr std::array<ConnectorId, 3> kConnectors = {{
    ConnectorId::candidate_gp19_spi0_tx,
    ConnectorId::candidate_gp3_spi0_tx,
    ConnectorId::candidate_gp7_spi0_tx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_tx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 tx. Valid pins: GP19, GP3, GP7. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI1, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 3> kPins = {{
    PinId::GP13,
    PinId::GP25,
    PinId::GP9,
  }};
  static constexpr std::array<ConnectorId, 3> kConnectors = {{
    ConnectorId::candidate_gp13_spi1_csn,
    ConnectorId::candidate_gp25_spi1_csn,
    ConnectorId::candidate_gp9_spi1_csn,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI1, SignalId::signal_csn> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI1 csn. Valid pins: GP13, GP25, GP9. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::GP12,
    PinId::GP8,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_gp12_spi1_rx,
    ConnectorId::candidate_gp8_spi1_rx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI1, SignalId::signal_rx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI1 rx. Valid pins: GP12, GP8. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI1, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::GP10,
    PinId::GP14,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_gp10_spi1_sck,
    ConnectorId::candidate_gp14_spi1_sck,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI1, SignalId::signal_sck> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI1 sck. Valid pins: GP10, GP14. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::GP11,
    PinId::GP15,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_gp11_spi1_tx,
    ConnectorId::candidate_gp15_spi1_tx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI1, SignalId::signal_tx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI1 tx. Valid pins: GP11, GP15. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART0, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 3> kPins = {{
    PinId::GP14,
    PinId::GP18,
    PinId::GP2,
  }};
  static constexpr std::array<ConnectorId, 3> kConnectors = {{
    ConnectorId::candidate_gp14_uart0_cts,
    ConnectorId::candidate_gp18_uart0_cts,
    ConnectorId::candidate_gp2_uart0_cts,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART0, SignalId::signal_cts> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART0 cts. Valid pins: GP14, GP18, GP2. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART0, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 3> kPins = {{
    PinId::GP15,
    PinId::GP19,
    PinId::GP3,
  }};
  static constexpr std::array<ConnectorId, 3> kConnectors = {{
    ConnectorId::candidate_gp15_uart0_rts,
    ConnectorId::candidate_gp19_uart0_rts,
    ConnectorId::candidate_gp3_uart0_rts,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART0, SignalId::signal_rts> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART0 rts. Valid pins: GP15, GP19, GP3. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 3> kPins = {{
    PinId::GP13,
    PinId::GP17,
    PinId::GP1,
  }};
  static constexpr std::array<ConnectorId, 3> kConnectors = {{
    ConnectorId::candidate_gp13_uart0_rx,
    ConnectorId::candidate_gp17_uart0_rx,
    ConnectorId::candidate_gp1_uart0_rx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART0 rx. Valid pins: GP13, GP17, GP1. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 3> kPins = {{
    PinId::GP0,
    PinId::GP12,
    PinId::GP16,
  }};
  static constexpr std::array<ConnectorId, 3> kConnectors = {{
    ConnectorId::candidate_gp0_uart0_tx,
    ConnectorId::candidate_gp12_uart0_tx,
    ConnectorId::candidate_gp16_uart0_tx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART0 tx. Valid pins: GP0, GP12, GP16. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART1, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 3> kPins = {{
    PinId::GP10,
    PinId::GP22,
    PinId::GP6,
  }};
  static constexpr std::array<ConnectorId, 3> kConnectors = {{
    ConnectorId::candidate_gp10_uart1_cts,
    ConnectorId::candidate_gp22_uart1_cts,
    ConnectorId::candidate_gp6_uart1_cts,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART1, SignalId::signal_cts> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART1 cts. Valid pins: GP10, GP22, GP6. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART1, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 2> kPins = {{
    PinId::GP11,
    PinId::GP7,
  }};
  static constexpr std::array<ConnectorId, 2> kConnectors = {{
    ConnectorId::candidate_gp11_uart1_rts,
    ConnectorId::candidate_gp7_uart1_rts,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART1, SignalId::signal_rts> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART1 rts. Valid pins: GP11, GP7. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 3> kPins = {{
    PinId::GP21,
    PinId::GP5,
    PinId::GP9,
  }};
  static constexpr std::array<ConnectorId, 3> kConnectors = {{
    ConnectorId::candidate_gp21_uart1_rx,
    ConnectorId::candidate_gp5_uart1_rx,
    ConnectorId::candidate_gp9_uart1_rx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART1, SignalId::signal_rx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART1 rx. Valid pins: GP21, GP5, GP9. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 4> kPins = {{
    PinId::GP20,
    PinId::GP25,
    PinId::GP4,
    PinId::GP8,
  }};
  static constexpr std::array<ConnectorId, 4> kConnectors = {{
    ConnectorId::candidate_gp20_uart1_tx,
    ConnectorId::candidate_gp25_uart1_tx,
    ConnectorId::candidate_gp4_uart1_tx,
    ConnectorId::candidate_gp8_uart1_tx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART1, SignalId::signal_tx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART1 tx. Valid pins: GP20, GP25, GP4, GP8. Provenance: pico-sdk; patches=raspberrypi-pico-bootstrap, raspberrypi-rp2040-family-bootstrap-v1.");
};

inline constexpr std::array<ConnectorDescriptor, 75> kConnectors = {{
  {ConnectorId::candidate_gp0_i2c0_sda, PinId::GP0, PeripheralId::I2C0, SignalId::signal_sda, RouteId::candidate_gp0_i2c0_sda, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_pico_scl_sda},
  {ConnectorId::candidate_gp0_spi0_rx, PinId::GP0, PeripheralId::SPI0, SignalId::signal_rx, RouteId::candidate_gp0_spi0_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp0_uart0_tx, PinId::GP0, PeripheralId::UART0, SignalId::signal_tx, RouteId::candidate_gp0_uart0_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_pico_tx_rx},
  {ConnectorId::candidate_gp10_i2c1_sda, PinId::GP10, PeripheralId::I2C1, SignalId::signal_sda, RouteId::candidate_gp10_i2c1_sda, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c1_pico_scl_sda},
  {ConnectorId::candidate_gp10_spi1_sck, PinId::GP10, PeripheralId::SPI1, SignalId::signal_sck, RouteId::candidate_gp10_spi1_sck, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi1_pico_all_signals},
  {ConnectorId::candidate_gp10_uart1_cts, PinId::GP10, PeripheralId::UART1, SignalId::signal_cts, RouteId::candidate_gp10_uart1_cts, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart1_pico_tx_rx_cts_rts},
  {ConnectorId::candidate_gp11_i2c1_scl, PinId::GP11, PeripheralId::I2C1, SignalId::signal_scl, RouteId::candidate_gp11_i2c1_scl, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c1_pico_scl_sda},
  {ConnectorId::candidate_gp11_spi1_tx, PinId::GP11, PeripheralId::SPI1, SignalId::signal_tx, RouteId::candidate_gp11_spi1_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi1_pico_all_signals},
  {ConnectorId::candidate_gp11_uart1_rts, PinId::GP11, PeripheralId::UART1, SignalId::signal_rts, RouteId::candidate_gp11_uart1_rts, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart1_pico_tx_rx_cts_rts},
  {ConnectorId::candidate_gp12_i2c0_sda, PinId::GP12, PeripheralId::I2C0, SignalId::signal_sda, RouteId::candidate_gp12_i2c0_sda, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_pico_scl_sda},
  {ConnectorId::candidate_gp12_spi1_rx, PinId::GP12, PeripheralId::SPI1, SignalId::signal_rx, RouteId::candidate_gp12_spi1_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi1_pico_all_signals},
  {ConnectorId::candidate_gp12_uart0_tx, PinId::GP12, PeripheralId::UART0, SignalId::signal_tx, RouteId::candidate_gp12_uart0_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_pico_tx_rx},
  {ConnectorId::candidate_gp13_i2c0_scl, PinId::GP13, PeripheralId::I2C0, SignalId::signal_scl, RouteId::candidate_gp13_i2c0_scl, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_pico_scl_sda},
  {ConnectorId::candidate_gp13_spi1_csn, PinId::GP13, PeripheralId::SPI1, SignalId::signal_csn, RouteId::candidate_gp13_spi1_csn, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi1_pico_all_signals},
  {ConnectorId::candidate_gp13_uart0_rx, PinId::GP13, PeripheralId::UART0, SignalId::signal_rx, RouteId::candidate_gp13_uart0_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_pico_tx_rx},
  {ConnectorId::candidate_gp14_i2c1_sda, PinId::GP14, PeripheralId::I2C1, SignalId::signal_sda, RouteId::candidate_gp14_i2c1_sda, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c1_pico_scl_sda},
  {ConnectorId::candidate_gp14_spi1_sck, PinId::GP14, PeripheralId::SPI1, SignalId::signal_sck, RouteId::candidate_gp14_spi1_sck, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi1_pico_all_signals},
  {ConnectorId::candidate_gp14_uart0_cts, PinId::GP14, PeripheralId::UART0, SignalId::signal_cts, RouteId::candidate_gp14_uart0_cts, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_pico_tx_rx_cts_rts},
  {ConnectorId::candidate_gp15_i2c1_scl, PinId::GP15, PeripheralId::I2C1, SignalId::signal_scl, RouteId::candidate_gp15_i2c1_scl, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c1_pico_scl_sda},
  {ConnectorId::candidate_gp15_spi1_tx, PinId::GP15, PeripheralId::SPI1, SignalId::signal_tx, RouteId::candidate_gp15_spi1_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi1_pico_all_signals},
  {ConnectorId::candidate_gp15_uart0_rts, PinId::GP15, PeripheralId::UART0, SignalId::signal_rts, RouteId::candidate_gp15_uart0_rts, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_pico_tx_rx_cts_rts},
  {ConnectorId::candidate_gp16_i2c0_sda, PinId::GP16, PeripheralId::I2C0, SignalId::signal_sda, RouteId::candidate_gp16_i2c0_sda, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_pico_scl_sda},
  {ConnectorId::candidate_gp16_spi0_rx, PinId::GP16, PeripheralId::SPI0, SignalId::signal_rx, RouteId::candidate_gp16_spi0_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp16_uart0_tx, PinId::GP16, PeripheralId::UART0, SignalId::signal_tx, RouteId::candidate_gp16_uart0_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_pico_tx_rx},
  {ConnectorId::candidate_gp17_i2c0_scl, PinId::GP17, PeripheralId::I2C0, SignalId::signal_scl, RouteId::candidate_gp17_i2c0_scl, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_pico_scl_sda},
  {ConnectorId::candidate_gp17_spi0_csn, PinId::GP17, PeripheralId::SPI0, SignalId::signal_csn, RouteId::candidate_gp17_spi0_csn, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp17_uart0_rx, PinId::GP17, PeripheralId::UART0, SignalId::signal_rx, RouteId::candidate_gp17_uart0_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_pico_tx_rx},
  {ConnectorId::candidate_gp18_i2c1_sda, PinId::GP18, PeripheralId::I2C1, SignalId::signal_sda, RouteId::candidate_gp18_i2c1_sda, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c1_pico_scl_sda},
  {ConnectorId::candidate_gp18_spi0_sck, PinId::GP18, PeripheralId::SPI0, SignalId::signal_sck, RouteId::candidate_gp18_spi0_sck, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp18_uart0_cts, PinId::GP18, PeripheralId::UART0, SignalId::signal_cts, RouteId::candidate_gp18_uart0_cts, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_pico_tx_rx_cts_rts},
  {ConnectorId::candidate_gp19_i2c1_scl, PinId::GP19, PeripheralId::I2C1, SignalId::signal_scl, RouteId::candidate_gp19_i2c1_scl, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c1_pico_scl_sda},
  {ConnectorId::candidate_gp19_spi0_tx, PinId::GP19, PeripheralId::SPI0, SignalId::signal_tx, RouteId::candidate_gp19_spi0_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp19_uart0_rts, PinId::GP19, PeripheralId::UART0, SignalId::signal_rts, RouteId::candidate_gp19_uart0_rts, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_pico_tx_rx_cts_rts},
  {ConnectorId::candidate_gp1_i2c0_scl, PinId::GP1, PeripheralId::I2C0, SignalId::signal_scl, RouteId::candidate_gp1_i2c0_scl, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_pico_scl_sda},
  {ConnectorId::candidate_gp1_spi0_csn, PinId::GP1, PeripheralId::SPI0, SignalId::signal_csn, RouteId::candidate_gp1_spi0_csn, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp1_uart0_rx, PinId::GP1, PeripheralId::UART0, SignalId::signal_rx, RouteId::candidate_gp1_uart0_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_pico_tx_rx},
  {ConnectorId::candidate_gp20_i2c0_sda, PinId::GP20, PeripheralId::I2C0, SignalId::signal_sda, RouteId::candidate_gp20_i2c0_sda, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_pico_scl_sda},
  {ConnectorId::candidate_gp20_spi0_rx, PinId::GP20, PeripheralId::SPI0, SignalId::signal_rx, RouteId::candidate_gp20_spi0_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp20_uart1_tx, PinId::GP20, PeripheralId::UART1, SignalId::signal_tx, RouteId::candidate_gp20_uart1_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart1_pico_tx_rx},
  {ConnectorId::candidate_gp21_i2c0_scl, PinId::GP21, PeripheralId::I2C0, SignalId::signal_scl, RouteId::candidate_gp21_i2c0_scl, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_pico_scl_sda},
  {ConnectorId::candidate_gp21_spi0_csn, PinId::GP21, PeripheralId::SPI0, SignalId::signal_csn, RouteId::candidate_gp21_spi0_csn, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp21_uart1_rx, PinId::GP21, PeripheralId::UART1, SignalId::signal_rx, RouteId::candidate_gp21_uart1_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart1_pico_tx_rx},
  {ConnectorId::candidate_gp22_i2c1_sda, PinId::GP22, PeripheralId::I2C1, SignalId::signal_sda, RouteId::candidate_gp22_i2c1_sda, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c1_pico_scl_sda},
  {ConnectorId::candidate_gp22_spi0_sck, PinId::GP22, PeripheralId::SPI0, SignalId::signal_sck, RouteId::candidate_gp22_spi0_sck, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp22_uart1_cts, PinId::GP22, PeripheralId::UART1, SignalId::signal_cts, RouteId::candidate_gp22_uart1_cts, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart1_pico_tx_rx_cts_rts},
  {ConnectorId::candidate_gp25_i2c0_scl, PinId::GP25, PeripheralId::I2C0, SignalId::signal_scl, RouteId::candidate_gp25_i2c0_scl, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_pico_scl_sda},
  {ConnectorId::candidate_gp25_spi1_csn, PinId::GP25, PeripheralId::SPI1, SignalId::signal_csn, RouteId::candidate_gp25_spi1_csn, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi1_pico_all_signals},
  {ConnectorId::candidate_gp25_uart1_tx, PinId::GP25, PeripheralId::UART1, SignalId::signal_tx, RouteId::candidate_gp25_uart1_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart1_pico_tx_rx},
  {ConnectorId::candidate_gp26_adc_ch0, PinId::GP26, PeripheralId::ADC, SignalId::signal_ch0, RouteId::candidate_gp26_adc_ch0, RouteKindId::route_kind_mux, ConnectionGroupId::group_adc_pico_all_signals},
  {ConnectorId::candidate_gp27_adc_ch1, PinId::GP27, PeripheralId::ADC, SignalId::signal_ch1, RouteId::candidate_gp27_adc_ch1, RouteKindId::route_kind_mux, ConnectionGroupId::group_adc_pico_all_signals},
  {ConnectorId::candidate_gp28_adc_ch2, PinId::GP28, PeripheralId::ADC, SignalId::signal_ch2, RouteId::candidate_gp28_adc_ch2, RouteKindId::route_kind_mux, ConnectionGroupId::group_adc_pico_all_signals},
  {ConnectorId::candidate_gp2_i2c1_sda, PinId::GP2, PeripheralId::I2C1, SignalId::signal_sda, RouteId::candidate_gp2_i2c1_sda, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c1_pico_scl_sda},
  {ConnectorId::candidate_gp2_spi0_sck, PinId::GP2, PeripheralId::SPI0, SignalId::signal_sck, RouteId::candidate_gp2_spi0_sck, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp2_uart0_cts, PinId::GP2, PeripheralId::UART0, SignalId::signal_cts, RouteId::candidate_gp2_uart0_cts, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_pico_tx_rx_cts_rts},
  {ConnectorId::candidate_gp3_i2c1_scl, PinId::GP3, PeripheralId::I2C1, SignalId::signal_scl, RouteId::candidate_gp3_i2c1_scl, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c1_pico_scl_sda},
  {ConnectorId::candidate_gp3_spi0_tx, PinId::GP3, PeripheralId::SPI0, SignalId::signal_tx, RouteId::candidate_gp3_spi0_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp3_uart0_rts, PinId::GP3, PeripheralId::UART0, SignalId::signal_rts, RouteId::candidate_gp3_uart0_rts, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_pico_tx_rx_cts_rts},
  {ConnectorId::candidate_gp4_i2c0_sda, PinId::GP4, PeripheralId::I2C0, SignalId::signal_sda, RouteId::candidate_gp4_i2c0_sda, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_pico_scl_sda},
  {ConnectorId::candidate_gp4_spi0_rx, PinId::GP4, PeripheralId::SPI0, SignalId::signal_rx, RouteId::candidate_gp4_spi0_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp4_uart1_tx, PinId::GP4, PeripheralId::UART1, SignalId::signal_tx, RouteId::candidate_gp4_uart1_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart1_pico_tx_rx},
  {ConnectorId::candidate_gp5_i2c0_scl, PinId::GP5, PeripheralId::I2C0, SignalId::signal_scl, RouteId::candidate_gp5_i2c0_scl, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_pico_scl_sda},
  {ConnectorId::candidate_gp5_spi0_csn, PinId::GP5, PeripheralId::SPI0, SignalId::signal_csn, RouteId::candidate_gp5_spi0_csn, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp5_uart1_rx, PinId::GP5, PeripheralId::UART1, SignalId::signal_rx, RouteId::candidate_gp5_uart1_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart1_pico_tx_rx},
  {ConnectorId::candidate_gp6_i2c1_sda, PinId::GP6, PeripheralId::I2C1, SignalId::signal_sda, RouteId::candidate_gp6_i2c1_sda, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c1_pico_scl_sda},
  {ConnectorId::candidate_gp6_spi0_sck, PinId::GP6, PeripheralId::SPI0, SignalId::signal_sck, RouteId::candidate_gp6_spi0_sck, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp6_uart1_cts, PinId::GP6, PeripheralId::UART1, SignalId::signal_cts, RouteId::candidate_gp6_uart1_cts, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart1_pico_tx_rx_cts_rts},
  {ConnectorId::candidate_gp7_i2c1_scl, PinId::GP7, PeripheralId::I2C1, SignalId::signal_scl, RouteId::candidate_gp7_i2c1_scl, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c1_pico_scl_sda},
  {ConnectorId::candidate_gp7_spi0_tx, PinId::GP7, PeripheralId::SPI0, SignalId::signal_tx, RouteId::candidate_gp7_spi0_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_pico_all_signals},
  {ConnectorId::candidate_gp7_uart1_rts, PinId::GP7, PeripheralId::UART1, SignalId::signal_rts, RouteId::candidate_gp7_uart1_rts, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart1_pico_tx_rx_cts_rts},
  {ConnectorId::candidate_gp8_i2c0_sda, PinId::GP8, PeripheralId::I2C0, SignalId::signal_sda, RouteId::candidate_gp8_i2c0_sda, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_pico_scl_sda},
  {ConnectorId::candidate_gp8_spi1_rx, PinId::GP8, PeripheralId::SPI1, SignalId::signal_rx, RouteId::candidate_gp8_spi1_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi1_pico_all_signals},
  {ConnectorId::candidate_gp8_uart1_tx, PinId::GP8, PeripheralId::UART1, SignalId::signal_tx, RouteId::candidate_gp8_uart1_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart1_pico_tx_rx},
  {ConnectorId::candidate_gp9_i2c0_scl, PinId::GP9, PeripheralId::I2C0, SignalId::signal_scl, RouteId::candidate_gp9_i2c0_scl, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_pico_scl_sda},
  {ConnectorId::candidate_gp9_spi1_csn, PinId::GP9, PeripheralId::SPI1, SignalId::signal_csn, RouteId::candidate_gp9_spi1_csn, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi1_pico_all_signals},
  {ConnectorId::candidate_gp9_uart1_rx, PinId::GP9, PeripheralId::UART1, SignalId::signal_rx, RouteId::candidate_gp9_uart1_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart1_pico_tx_rx},
}};
}
}
}
}
}
}
