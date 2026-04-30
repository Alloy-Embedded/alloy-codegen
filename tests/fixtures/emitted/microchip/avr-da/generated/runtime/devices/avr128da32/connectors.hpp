#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "routes.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
enum class ConnectorId : std::uint16_t {
  none,
  candidate_pa0_usart0_tx,
  candidate_pa1_usart0_rx,
  candidate_pa2_twi0_sda,
  candidate_pa3_twi0_scl,
  candidate_pa4_spi0_mosi,
  candidate_pa5_spi0_miso,
  candidate_pa6_spi0_sck,
  candidate_pa7_spi0_cs,
  candidate_pc0_usart1_tx,
  candidate_pc1_usart1_rx,
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
struct ConnectorTraits<PinId::PA0, PeripheralId::USART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa0_usart0_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_pa0_usart0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart0_tqfp32_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PA1, PeripheralId::USART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa1_usart0_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_pa1_usart0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart0_tqfp32_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PA2, PeripheralId::TWI0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa2_twi0_sda;
  static constexpr RouteId kRouteId = RouteId::candidate_pa2_twi0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_twi0_tqfp32_scl_sda;
};

template<>
struct ConnectorTraits<PinId::PA3, PeripheralId::TWI0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa3_twi0_scl;
  static constexpr RouteId kRouteId = RouteId::candidate_pa3_twi0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_twi0_tqfp32_scl_sda;
};

template<>
struct ConnectorTraits<PinId::PA4, PeripheralId::SPI0, SignalId::signal_mosi> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa4_spi0_mosi;
  static constexpr RouteId kRouteId = RouteId::candidate_pa4_spi0_mosi;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_tqfp32_sck_mosi_miso;
};

template<>
struct ConnectorTraits<PinId::PA5, PeripheralId::SPI0, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa5_spi0_miso;
  static constexpr RouteId kRouteId = RouteId::candidate_pa5_spi0_miso;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_tqfp32_sck_mosi_miso;
};

template<>
struct ConnectorTraits<PinId::PA6, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa6_spi0_sck;
  static constexpr RouteId kRouteId = RouteId::candidate_pa6_spi0_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_spi0_tqfp32_sck_mosi_miso;
};

template<>
struct ConnectorTraits<PinId::PA7, PeripheralId::SPI0, SignalId::signal_cs> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pa7_spi0_cs;
  static constexpr RouteId kRouteId = RouteId::candidate_pa7_spi0_cs;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
};

template<>
struct ConnectorTraits<PinId::PC0, PeripheralId::USART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pc0_usart1_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_pc0_usart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart1_tqfp32_tx_rx;
};

template<>
struct ConnectorTraits<PinId::PC1, PeripheralId::USART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_pc1_usart1_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_pc1_usart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_usart1_tqfp32_tx_rx;
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_cs> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA7,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa7_spi0_cs,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_cs> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 cs. Valid pins: PA7. Provenance: microchip-dfp-extract; patches=microchip-avr-da-family-bootstrap-v1, microchip-avr128da32-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA5,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa5_spi0_miso,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_miso> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 miso. Valid pins: PA5. Provenance: microchip-dfp-extract; patches=microchip-avr-da-family-bootstrap-v1, microchip-avr128da32-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_mosi> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA4,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa4_spi0_mosi,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_mosi> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 mosi. Valid pins: PA4. Provenance: microchip-dfp-extract; patches=microchip-avr-da-family-bootstrap-v1, microchip-avr128da32-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA6,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa6_spi0_sck,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for SPI0 sck. Valid pins: PA6. Provenance: microchip-dfp-extract; patches=microchip-avr-da-family-bootstrap-v1, microchip-avr128da32-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TWI0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA3,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa3_twi0_scl,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TWI0, SignalId::signal_scl> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TWI0 scl. Valid pins: PA3. Provenance: microchip-dfp-extract; patches=microchip-avr-da-family-bootstrap-v1, microchip-avr128da32-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::TWI0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA2,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa2_twi0_sda,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::TWI0, SignalId::signal_sda> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for TWI0 sda. Valid pins: PA2. Provenance: microchip-dfp-extract; patches=microchip-avr-da-family-bootstrap-v1, microchip-avr128da32-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA1,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa1_usart0_rx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART0, SignalId::signal_rx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART0 rx. Valid pins: PA1. Provenance: microchip-dfp-extract; patches=microchip-avr-da-family-bootstrap-v1, microchip-avr128da32-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PA0,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pa0_usart0_tx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART0, SignalId::signal_tx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART0 tx. Valid pins: PA0. Provenance: microchip-dfp-extract; patches=microchip-avr-da-family-bootstrap-v1, microchip-avr128da32-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PC1,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pc1_usart1_rx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART1, SignalId::signal_rx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART1 rx. Valid pins: PC1. Provenance: microchip-dfp-extract; patches=microchip-avr-da-family-bootstrap-v1, microchip-avr128da32-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::USART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::PC0,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_pc0_usart1_tx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::USART1, SignalId::signal_tx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for USART1 tx. Valid pins: PC0. Provenance: microchip-dfp-extract; patches=microchip-avr-da-family-bootstrap-v1, microchip-avr128da32-bootstrap.");
};

inline constexpr std::array<ConnectorDescriptor, 10> kConnectors = {{
  {ConnectorId::candidate_pa0_usart0_tx, PinId::PA0, PeripheralId::USART0, SignalId::signal_tx, RouteId::candidate_pa0_usart0_tx, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart0_tqfp32_tx_rx},
  {ConnectorId::candidate_pa1_usart0_rx, PinId::PA1, PeripheralId::USART0, SignalId::signal_rx, RouteId::candidate_pa1_usart0_rx, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart0_tqfp32_tx_rx},
  {ConnectorId::candidate_pa2_twi0_sda, PinId::PA2, PeripheralId::TWI0, SignalId::signal_sda, RouteId::candidate_pa2_twi0_sda, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_twi0_tqfp32_scl_sda},
  {ConnectorId::candidate_pa3_twi0_scl, PinId::PA3, PeripheralId::TWI0, SignalId::signal_scl, RouteId::candidate_pa3_twi0_scl, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_twi0_tqfp32_scl_sda},
  {ConnectorId::candidate_pa4_spi0_mosi, PinId::PA4, PeripheralId::SPI0, SignalId::signal_mosi, RouteId::candidate_pa4_spi0_mosi, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_spi0_tqfp32_sck_mosi_miso},
  {ConnectorId::candidate_pa5_spi0_miso, PinId::PA5, PeripheralId::SPI0, SignalId::signal_miso, RouteId::candidate_pa5_spi0_miso, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_spi0_tqfp32_sck_mosi_miso},
  {ConnectorId::candidate_pa6_spi0_sck, PinId::PA6, PeripheralId::SPI0, SignalId::signal_sck, RouteId::candidate_pa6_spi0_sck, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_spi0_tqfp32_sck_mosi_miso},
  {ConnectorId::candidate_pa7_spi0_cs, PinId::PA7, PeripheralId::SPI0, SignalId::signal_cs, RouteId::candidate_pa7_spi0_cs, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::none},
  {ConnectorId::candidate_pc0_usart1_tx, PinId::PC0, PeripheralId::USART1, SignalId::signal_tx, RouteId::candidate_pc0_usart1_tx, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart1_tqfp32_tx_rx},
  {ConnectorId::candidate_pc1_usart1_rx, PinId::PC1, PeripheralId::USART1, SignalId::signal_rx, RouteId::candidate_pc1_usart1_rx, RouteKindId::route_kind_peripheral_mux, ConnectionGroupId::group_usart1_tqfp32_tx_rx},
}};
}
}
}
}
}
}
