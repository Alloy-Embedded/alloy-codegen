#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "routes.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
enum class ConnectorId : std::uint16_t {
  none,
  candidate_gpio_ad_b0_00_gpio1_io00,
  candidate_gpio_ad_b0_00_lpuart1_tx,
  candidate_gpio_ad_b0_01_gpio1_io01,
  candidate_gpio_ad_b0_01_lpuart1_rx,
  candidate_gpio_emc_00_gpio4_io00,
  candidate_gpio_emc_00_lpspi1_sck,
  candidate_gpio_emc_01_gpio4_io01,
  candidate_gpio_emc_01_lpspi1_pcs0,
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
struct ConnectorTraits<PinId::GPIO_AD_B0_00, PeripheralId::GPIO1, SignalId::signal_io00> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio_ad_b0_00_gpio1_io00;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_ad_b0_00_gpio1_io00;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpio1_bga196_all_signals;
};

template<>
struct ConnectorTraits<PinId::GPIO_AD_B0_00, PeripheralId::LPUART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio_ad_b0_00_lpuart1_tx;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_ad_b0_00_lpuart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_lpuart1_bga196_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GPIO_AD_B0_01, PeripheralId::GPIO1, SignalId::signal_io01> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio_ad_b0_01_gpio1_io01;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_ad_b0_01_gpio1_io01;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpio1_bga196_all_signals;
};

template<>
struct ConnectorTraits<PinId::GPIO_AD_B0_01, PeripheralId::LPUART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio_ad_b0_01_lpuart1_rx;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_ad_b0_01_lpuart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_lpuart1_bga196_tx_rx;
};

template<>
struct ConnectorTraits<PinId::GPIO_EMC_00, PeripheralId::GPIO4, SignalId::signal_io00> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio_emc_00_gpio4_io00;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_emc_00_gpio4_io00;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpio4_bga196_all_signals;
};

template<>
struct ConnectorTraits<PinId::GPIO_EMC_00, PeripheralId::LPSPI1, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio_emc_00_lpspi1_sck;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_emc_00_lpspi1_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_lpspi1_bga196_sck_cs;
};

template<>
struct ConnectorTraits<PinId::GPIO_EMC_01, PeripheralId::GPIO4, SignalId::signal_io01> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio_emc_01_gpio4_io01;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_emc_01_gpio4_io01;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_gpio4_bga196_all_signals;
};

template<>
struct ConnectorTraits<PinId::GPIO_EMC_01, PeripheralId::LPSPI1, SignalId::signal_pcs0> {
  static constexpr bool kPresent = true;
  static constexpr ConnectorId kConnectorId = ConnectorId::candidate_gpio_emc_01_lpspi1_pcs0;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio_emc_01_lpspi1_pcs0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_iomuxc_mux;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::group_lpspi1_bga196_sck_cs;
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIO1, SignalId::signal_io00> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO_AD_B0_00,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio_ad_b0_00_gpio1_io00,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIO1, SignalId::signal_io00> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIO1 io00. Valid pins: GPIO_AD_B0_00. Provenance: nxp-mcux-sdk; patches=nxp-imxrt1060-family-bootstrap-v1, nxp-imxrt1060-mimxrt1062-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIO1, SignalId::signal_io01> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO_AD_B0_01,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio_ad_b0_01_gpio1_io01,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIO1, SignalId::signal_io01> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIO1 io01. Valid pins: GPIO_AD_B0_01. Provenance: nxp-mcux-sdk; patches=nxp-imxrt1060-family-bootstrap-v1, nxp-imxrt1060-mimxrt1062-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIO4, SignalId::signal_io00> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO_EMC_00,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio_emc_00_gpio4_io00,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIO4, SignalId::signal_io00> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIO4 io00. Valid pins: GPIO_EMC_00. Provenance: nxp-mcux-sdk; patches=nxp-imxrt1060-family-bootstrap-v1, nxp-imxrt1060-mimxrt1062-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::GPIO4, SignalId::signal_io01> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO_EMC_01,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio_emc_01_gpio4_io01,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::GPIO4, SignalId::signal_io01> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for GPIO4 io01. Valid pins: GPIO_EMC_01. Provenance: nxp-mcux-sdk; patches=nxp-imxrt1060-family-bootstrap-v1, nxp-imxrt1060-mimxrt1062-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::LPSPI1, SignalId::signal_pcs0> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO_EMC_01,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio_emc_01_lpspi1_pcs0,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::LPSPI1, SignalId::signal_pcs0> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for LPSPI1 pcs0. Valid pins: GPIO_EMC_01. Provenance: nxp-mcux-sdk; patches=nxp-imxrt1060-family-bootstrap-v1, nxp-imxrt1060-mimxrt1062-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::LPSPI1, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO_EMC_00,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio_emc_00_lpspi1_sck,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::LPSPI1, SignalId::signal_sck> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for LPSPI1 sck. Valid pins: GPIO_EMC_00. Provenance: nxp-mcux-sdk; patches=nxp-imxrt1060-family-bootstrap-v1, nxp-imxrt1060-mimxrt1062-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::LPUART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO_AD_B0_01,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio_ad_b0_01_lpuart1_rx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::LPUART1, SignalId::signal_rx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for LPUART1 rx. Valid pins: GPIO_AD_B0_01. Provenance: nxp-mcux-sdk; patches=nxp-imxrt1060-family-bootstrap-v1, nxp-imxrt1060-mimxrt1062-bootstrap.");
};

template<>
struct ConnectorSignalTraits<PeripheralId::LPUART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr std::array<PinId, 1> kPins = {{
    PinId::GPIO_AD_B0_00,
  }};
  static constexpr std::array<ConnectorId, 1> kConnectors = {{
    ConnectorId::candidate_gpio_ad_b0_00_lpuart1_tx,
  }};
};

template<PinId Pin>
struct ConnectorTraits<Pin, PeripheralId::LPUART1, SignalId::signal_tx> {
  static constexpr bool kPresent = false;
  static constexpr ConnectorId kConnectorId = ConnectorId::none;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr ConnectionGroupId kConnectionGroupId = ConnectionGroupId::none;
  static_assert(detail::kInvalidConnector<Pin>, "Invalid connector for LPUART1 tx. Valid pins: GPIO_AD_B0_00. Provenance: nxp-mcux-sdk; patches=nxp-imxrt1060-family-bootstrap-v1, nxp-imxrt1060-mimxrt1062-bootstrap.");
};

inline constexpr std::array<ConnectorDescriptor, 8> kConnectors = {{
  {ConnectorId::candidate_gpio_ad_b0_00_gpio1_io00, PinId::GPIO_AD_B0_00, PeripheralId::GPIO1, SignalId::signal_io00, RouteId::candidate_gpio_ad_b0_00_gpio1_io00, RouteKindId::route_kind_iomuxc_mux, ConnectionGroupId::group_gpio1_bga196_all_signals},
  {ConnectorId::candidate_gpio_ad_b0_00_lpuart1_tx, PinId::GPIO_AD_B0_00, PeripheralId::LPUART1, SignalId::signal_tx, RouteId::candidate_gpio_ad_b0_00_lpuart1_tx, RouteKindId::route_kind_iomuxc_mux, ConnectionGroupId::group_lpuart1_bga196_tx_rx},
  {ConnectorId::candidate_gpio_ad_b0_01_gpio1_io01, PinId::GPIO_AD_B0_01, PeripheralId::GPIO1, SignalId::signal_io01, RouteId::candidate_gpio_ad_b0_01_gpio1_io01, RouteKindId::route_kind_iomuxc_mux, ConnectionGroupId::group_gpio1_bga196_all_signals},
  {ConnectorId::candidate_gpio_ad_b0_01_lpuart1_rx, PinId::GPIO_AD_B0_01, PeripheralId::LPUART1, SignalId::signal_rx, RouteId::candidate_gpio_ad_b0_01_lpuart1_rx, RouteKindId::route_kind_iomuxc_mux, ConnectionGroupId::group_lpuart1_bga196_tx_rx},
  {ConnectorId::candidate_gpio_emc_00_gpio4_io00, PinId::GPIO_EMC_00, PeripheralId::GPIO4, SignalId::signal_io00, RouteId::candidate_gpio_emc_00_gpio4_io00, RouteKindId::route_kind_iomuxc_mux, ConnectionGroupId::group_gpio4_bga196_all_signals},
  {ConnectorId::candidate_gpio_emc_00_lpspi1_sck, PinId::GPIO_EMC_00, PeripheralId::LPSPI1, SignalId::signal_sck, RouteId::candidate_gpio_emc_00_lpspi1_sck, RouteKindId::route_kind_iomuxc_mux, ConnectionGroupId::group_lpspi1_bga196_sck_cs},
  {ConnectorId::candidate_gpio_emc_01_gpio4_io01, PinId::GPIO_EMC_01, PeripheralId::GPIO4, SignalId::signal_io01, RouteId::candidate_gpio_emc_01_gpio4_io01, RouteKindId::route_kind_iomuxc_mux, ConnectionGroupId::group_gpio4_bga196_all_signals},
  {ConnectorId::candidate_gpio_emc_01_lpspi1_pcs0, PinId::GPIO_EMC_01, PeripheralId::LPSPI1, SignalId::signal_pcs0, RouteId::candidate_gpio_emc_01_lpspi1_pcs0, RouteKindId::route_kind_iomuxc_mux, ConnectionGroupId::group_lpspi1_bga196_sck_cs},
}};
}
}
}
}
}
}
