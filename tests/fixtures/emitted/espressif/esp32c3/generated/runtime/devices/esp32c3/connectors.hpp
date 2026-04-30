#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "routes.hpp"

namespace espressif {
namespace esp32c3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32c3 {
enum class ConnectorId : std::uint16_t {
  none,
  candidate_gpio10_spi2_cs,
  candidate_gpio20_uart0_rx,
  candidate_gpio21_uart0_tx,
  candidate_gpio2_spi2_miso,
  candidate_gpio4_uart1_tx,
  candidate_gpio5_uart1_rx,
  candidate_gpio6_spi2_sck,
  candidate_gpio7_spi2_mosi,
  candidate_gpio8_i2c0_sda,
  candidate_gpio9_i2c0_scl,
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
struct ConnectorTraits<PinId::GPIO10, PeripheralId::SPI2, SignalId::signal_cs> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio10_spi2_cs;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio10_spi2_cs;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::GPIO20, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio20_uart0_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio20_uart0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_qfn32_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GPIO21, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio21_uart0_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio21_uart0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_qfn32_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GPIO2, PeripheralId::SPI2, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio2_spi2_miso;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio2_spi2_miso;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi2_qfn32_sck_mosi_miso;
};

template<>
struct ConnectorTraits<PinId::GPIO4, PeripheralId::UART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio4_uart1_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio4_uart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_qfn32_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GPIO5, PeripheralId::UART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio5_uart1_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio5_uart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart1_qfn32_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GPIO6, PeripheralId::SPI2, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio6_spi2_sck;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio6_spi2_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi2_qfn32_sck_mosi_miso;
};

template<>
struct ConnectorTraits<PinId::GPIO7, PeripheralId::SPI2, SignalId::signal_mosi> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio7_spi2_mosi;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio7_spi2_mosi;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi2_qfn32_sck_mosi_miso;
};

template<>
struct ConnectorTraits<PinId::GPIO8, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio8_i2c0_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio8_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_qfn32_scl_sda;
};

template<>
struct ConnectorTraits<PinId::GPIO9, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio9_i2c0_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio9_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_i2c0_qfn32_scl_sda;
};

template<>
struct ConnectorSignalTraits<PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO9,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio9_i2c0_scl,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for I2C0 scl. Valid pins: GPIO9. Provenance: espressif-svd; patches=espressif-esp32c3-bootstrap, espressif-esp32c3-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO8,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio8_i2c0_sda,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for I2C0 sda. Valid pins: GPIO8. Provenance: espressif-svd; patches=espressif-esp32c3-bootstrap, espressif-esp32c3-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI2, SignalId::signal_cs> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO10,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio10_spi2_cs,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI2, SignalId::signal_cs> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI2 cs. Valid pins: GPIO10. Provenance: espressif-svd; patches=espressif-esp32c3-bootstrap, espressif-esp32c3-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI2, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO2,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio2_spi2_miso,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI2, SignalId::signal_miso> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI2 miso. Valid pins: GPIO2. Provenance: espressif-svd; patches=espressif-esp32c3-bootstrap, espressif-esp32c3-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI2, SignalId::signal_mosi> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO7,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio7_spi2_mosi,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI2, SignalId::signal_mosi> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI2 mosi. Valid pins: GPIO7. Provenance: espressif-svd; patches=espressif-esp32c3-bootstrap, espressif-esp32c3-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI2, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO6,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio6_spi2_sck,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI2, SignalId::signal_sck> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI2 sck. Valid pins: GPIO6. Provenance: espressif-svd; patches=espressif-esp32c3-bootstrap, espressif-esp32c3-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO20,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio20_uart0_rx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART0 rx. Valid pins: GPIO20. Provenance: espressif-svd; patches=espressif-esp32c3-bootstrap, espressif-esp32c3-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO21,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio21_uart0_tx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART0 tx. Valid pins: GPIO21. Provenance: espressif-svd; patches=espressif-esp32c3-bootstrap, espressif-esp32c3-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO5,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio5_uart1_rx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART1, SignalId::signal_rx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART1 rx. Valid pins: GPIO5. Provenance: espressif-svd; patches=espressif-esp32c3-bootstrap, espressif-esp32c3-family-bootstrap-v1.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO4,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio4_uart1_tx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART1, SignalId::signal_tx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART1 tx. Valid pins: GPIO4. Provenance: espressif-svd; patches=espressif-esp32c3-bootstrap, espressif-esp32c3-family-bootstrap-v1.");
};

inline constexpr std::array<ConnectorDescriptor, 10> kConnectors = {{
  {ConnectorId::candidate_gpio10_spi2_cs, PinId::GPIO10, PeripheralId::SPI2, SignalId::signal_cs, RouteId::candidate_gpio10_spi2_cs, RouteKindId::route_kind_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_gpio20_uart0_rx, PinId::GPIO20, PeripheralId::UART0, SignalId::signal_rx, RouteId::candidate_gpio20_uart0_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_qfn32_tx_rx},
  {ConnectorId::candidate_gpio21_uart0_tx, PinId::GPIO21, PeripheralId::UART0, SignalId::signal_tx, RouteId::candidate_gpio21_uart0_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_qfn32_tx_rx},
  {ConnectorId::candidate_gpio2_spi2_miso, PinId::GPIO2, PeripheralId::SPI2, SignalId::signal_miso, RouteId::candidate_gpio2_spi2_miso, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi2_qfn32_sck_mosi_miso},
  {ConnectorId::candidate_gpio4_uart1_tx, PinId::GPIO4, PeripheralId::UART1, SignalId::signal_tx, RouteId::candidate_gpio4_uart1_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart1_qfn32_tx_rx},
  {ConnectorId::candidate_gpio5_uart1_rx, PinId::GPIO5, PeripheralId::UART1, SignalId::signal_rx, RouteId::candidate_gpio5_uart1_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart1_qfn32_tx_rx},
  {ConnectorId::candidate_gpio6_spi2_sck, PinId::GPIO6, PeripheralId::SPI2, SignalId::signal_sck, RouteId::candidate_gpio6_spi2_sck, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi2_qfn32_sck_mosi_miso},
  {ConnectorId::candidate_gpio7_spi2_mosi, PinId::GPIO7, PeripheralId::SPI2, SignalId::signal_mosi, RouteId::candidate_gpio7_spi2_mosi, RouteKindId::route_kind_mux, ConnectionGroupId::group_spi2_qfn32_sck_mosi_miso},
  {ConnectorId::candidate_gpio8_i2c0_sda, PinId::GPIO8, PeripheralId::I2C0, SignalId::signal_sda, RouteId::candidate_gpio8_i2c0_sda, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_qfn32_scl_sda},
  {ConnectorId::candidate_gpio9_i2c0_scl, PinId::GPIO9, PeripheralId::I2C0, SignalId::signal_scl, RouteId::candidate_gpio9_i2c0_scl, RouteKindId::route_kind_mux, ConnectionGroupId::group_i2c0_qfn32_scl_sda},
}};
}
}
}
}
}
}
