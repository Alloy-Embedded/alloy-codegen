#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "routes.hpp"

namespace nordic {
namespace nrf52 {
namespace generated {
namespace runtime {
namespace devices {
namespace nrf52840 {
enum class ConnectorId : std::uint16_t {
  none,
  candidate_p0_06_uart0_tx,
  candidate_p0_08_uart0_rx,
  candidate_p0_19_spi0_sck,
  candidate_p0_20_spi0_mosi,
  candidate_p0_21_spi0_miso,
  candidate_p0_26_i2c0_sda,
  candidate_p0_27_i2c0_scl,
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
struct ConnectorTraits<PinId::P0_06, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_p0_06_uart0_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_p0_06_uart0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_aqfn73_tx_rx;
};

template<>
struct ConnectorTraits<PinId::P0_08, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_p0_08_uart0_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_p0_08_uart0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_aqfn73_tx_rx;
};

template<>
struct ConnectorTraits<PinId::P0_19, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_p0_19_spi0_sck;
  static constexpr RouteId kRouteId = RouteId::candidate_p0_19_spi0_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_aqfn73_sck_mosi_miso;
};

template<>
struct ConnectorTraits<PinId::P0_20, PeripheralId::SPI0, SignalId::signal_mosi> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_p0_20_spi0_mosi;
  static constexpr RouteId kRouteId = RouteId::candidate_p0_20_spi0_mosi;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_aqfn73_sck_mosi_miso;
};

template<>
struct ConnectorTraits<PinId::P0_21, PeripheralId::SPI0, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_p0_21_spi0_miso;
  static constexpr RouteId kRouteId = RouteId::candidate_p0_21_spi0_miso;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_aqfn73_sck_mosi_miso;
};

template<>
struct ConnectorTraits<PinId::P0_26, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_p0_26_i2c0_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_p0_26_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_aqfn73_scl_sda;
};

template<>
struct ConnectorTraits<PinId::P0_27, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_p0_27_i2c0_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_p0_27_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_aqfn73_scl_sda;
};

template<>
struct ConnectorSignalTraits<PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::P0_27,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_p0_27_i2c0_scl,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for I2C0 scl. Valid pins: P0_27. Provenance: zephyr-dts; patches=nordic-nrf52-family-bootstrap-v1, nordic-nrf52-nrf52840-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::P0_26,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_p0_26_i2c0_sda,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for I2C0 sda. Valid pins: P0_26. Provenance: zephyr-dts; patches=nordic-nrf52-family-bootstrap-v1, nordic-nrf52-nrf52840-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::P0_21,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_p0_21_spi0_miso,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_miso> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 miso. Valid pins: P0_21. Provenance: zephyr-dts; patches=nordic-nrf52-family-bootstrap-v1, nordic-nrf52-nrf52840-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_mosi> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::P0_20,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_p0_20_spi0_mosi,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_mosi> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 mosi. Valid pins: P0_20. Provenance: zephyr-dts; patches=nordic-nrf52-family-bootstrap-v1, nordic-nrf52-nrf52840-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::P0_19,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_p0_19_spi0_sck,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 sck. Valid pins: P0_19. Provenance: zephyr-dts; patches=nordic-nrf52-family-bootstrap-v1, nordic-nrf52-nrf52840-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::P0_08,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_p0_08_uart0_rx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART0 rx. Valid pins: P0_08. Provenance: zephyr-dts; patches=nordic-nrf52-family-bootstrap-v1, nordic-nrf52-nrf52840-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::P0_06,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_p0_06_uart0_tx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART0 tx. Valid pins: P0_06. Provenance: zephyr-dts; patches=nordic-nrf52-family-bootstrap-v1, nordic-nrf52-nrf52840-bootstrap.");
};

inline constexpr std::array<ConnectorDescriptor, 7> kConnectors = {{
  {ConnectorId::candidate_p0_06_uart0_tx, PinId::P0_06, PeripheralId::UART0, SignalId::signal_tx, RouteId::candidate_p0_06_uart0_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_aqfn73_tx_rx},
  {ConnectorId::candidate_p0_08_uart0_rx, PinId::P0_08, PeripheralId::UART0, SignalId::signal_rx, RouteId::candidate_p0_08_uart0_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_aqfn73_tx_rx},
  {ConnectorId::candidate_p0_19_spi0_sck, PinId::P0_19, PeripheralId::SPI0, SignalId::signal_sck, RouteId::candidate_p0_19_spi0_sck, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_aqfn73_sck_mosi_miso},
  {ConnectorId::candidate_p0_20_spi0_mosi, PinId::P0_20, PeripheralId::SPI0, SignalId::signal_mosi, RouteId::candidate_p0_20_spi0_mosi, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_aqfn73_sck_mosi_miso},
  {ConnectorId::candidate_p0_21_spi0_miso, PinId::P0_21, PeripheralId::SPI0, SignalId::signal_miso, RouteId::candidate_p0_21_spi0_miso, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi0_aqfn73_sck_mosi_miso},
  {ConnectorId::candidate_p0_26_i2c0_sda, PinId::P0_26, PeripheralId::I2C0, SignalId::signal_sda, RouteId::candidate_p0_26_i2c0_sda, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_aqfn73_scl_sda},
  {ConnectorId::candidate_p0_27_i2c0_scl, PinId::P0_27, PeripheralId::I2C0, SignalId::signal_scl, RouteId::candidate_p0_27_i2c0_scl, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_aqfn73_scl_sda},
}};
}
}
}
}
}
}
