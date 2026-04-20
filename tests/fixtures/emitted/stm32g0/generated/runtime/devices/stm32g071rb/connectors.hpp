#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "routes.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g071rb {
enum class ConnectorId : std::uint16_t {
  none,
  candidate_pb6_usart1_tx,
  candidate_pb7_usart1_rx,
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

template<PeripheralId Peripheral, SignalId Signal>
struct ConnectorSignalTraits {
  static constexpr bool kPresent = false;
  static constexpr std::array<PinId, 0> kPins = {};
  static constexpr std::array<ConnectorId, 0> kConnectors = {};
};

template<>
struct ConnectorTraits<PinId::PB6, PeripheralId::USART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb6_usart1_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_pb6_usart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart1_lqfp64_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PB7, PeripheralId::USART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pb7_usart1_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_pb7_usart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart1_lqfp64_tx_rx;
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB7,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb7_usart1_rx,
  }};
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PB6,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pb6_usart1_tx,
  }};
};

inline constexpr std::array<ConnectorDescriptor, 2> kConnectors = {{
  {ConnectorId::candidate_pb6_usart1_tx, PinId::PB6, PeripheralId::USART1, SignalId::signal_tx, RouteId::candidate_pb6_usart1_tx, RouteKindId::route_kind_alternate_function, ConnectionGroupId::group_usart1_lqfp64_tx_rx},
  {ConnectorId::candidate_pb7_usart1_rx, PinId::PB7, PeripheralId::USART1, SignalId::signal_rx, RouteId::candidate_pb7_usart1_rx, RouteKindId::route_kind_alternate_function, ConnectionGroupId::group_usart1_lqfp64_tx_rx},
}};
}
}
}
}
}
}
