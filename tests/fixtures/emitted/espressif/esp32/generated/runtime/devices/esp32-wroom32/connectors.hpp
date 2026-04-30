#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "routes.hpp"

namespace espressif {
namespace esp32 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32_wroom32 {
enum class ConnectorId : std::uint16_t {
  none,
  candidate_gpio1_uart0_tx,
  candidate_gpio3_uart0_rx,
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
struct ConnectorTraits<PinId::GPIO1, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio1_uart0_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio1_uart0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_wroom_32_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GPIO3, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio3_uart0_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio3_uart0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_uart0_wroom_32_tx_rx;
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO3,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio3_uart0_rx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART0 rx. Valid pins: GPIO3. Provenance: espressif-svd; patches=espressif-esp32-family-bootstrap-v1, espressif-esp32-wroom32-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO1,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio1_uart0_tx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for UART0 tx. Valid pins: GPIO1. Provenance: espressif-svd; patches=espressif-esp32-family-bootstrap-v1, espressif-esp32-wroom32-bootstrap.");
};

inline constexpr std::array<ConnectorDescriptor, 2> kConnectors = {{
  {ConnectorId::candidate_gpio1_uart0_tx, PinId::GPIO1, PeripheralId::UART0, SignalId::signal_tx, RouteId::candidate_gpio1_uart0_tx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_wroom_32_tx_rx},
  {ConnectorId::candidate_gpio3_uart0_rx, PinId::GPIO3, PeripheralId::UART0, SignalId::signal_rx, RouteId::candidate_gpio3_uart0_rx, RouteKindId::route_kind_mux, ConnectionGroupId::group_uart0_wroom_32_tx_rx},
}};
}
}
}
}
}
}
