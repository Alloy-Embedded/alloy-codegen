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
namespace stm32g0b1re {
enum class ConnectorId : std::uint16_t {
  none,
  candidate_pa11_fdcan1_rx,
  candidate_pa12_fdcan1_tx,
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
struct ConnectorTraits<PinId::PA11, PeripheralId::FDCAN1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa11_fdcan1_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_pa11_fdcan1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_fdcan1_lqfp64_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PA12, PeripheralId::FDCAN1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa12_fdcan1_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_pa12_fdcan1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_fdcan1_lqfp64_tx_rx;
};

template<>
struct ConnectorSignalTraits<PeripheralId::FDCAN1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA11,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa11_fdcan1_rx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::FDCAN1, SignalId::signal_rx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for FDCAN1 rx. Valid pins: PA11. Provenance: stm32-open-pin-data; patches=st-stm32g0-family-bootstrap-v1, st-stm32g0-stm32g0b1re-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::FDCAN1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA12,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa12_fdcan1_tx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::FDCAN1, SignalId::signal_tx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for FDCAN1 tx. Valid pins: PA12. Provenance: stm32-open-pin-data; patches=st-stm32g0-family-bootstrap-v1, st-stm32g0-stm32g0b1re-bootstrap.");
};

inline constexpr std::array<ConnectorDescriptor, 2> kConnectors = {{
  {ConnectorId::candidate_pa11_fdcan1_rx, PinId::PA11, PeripheralId::FDCAN1, SignalId::signal_rx, RouteId::candidate_pa11_fdcan1_rx, RouteKindId::route_kind_alternate_function, ConnectionGroupId::group_fdcan1_lqfp64_tx_rx},
  {ConnectorId::candidate_pa12_fdcan1_tx, PinId::PA12, PeripheralId::FDCAN1, SignalId::signal_tx, RouteId::candidate_pa12_fdcan1_tx, RouteKindId::route_kind_alternate_function, ConnectionGroupId::group_fdcan1_lqfp64_tx_rx},
}};
}
}
}
}
}
}
