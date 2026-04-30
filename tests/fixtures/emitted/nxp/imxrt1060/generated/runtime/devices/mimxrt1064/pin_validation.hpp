#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1064 {
enum class PeripheralSignal : std::uint16_t {
  GPIO1_IO00 = 0u,
  GPIO1_IO01 = 1u,
  GPIO4_IO00 = 2u,
  GPIO4_IO01 = 3u,
  LPI2C1_SCL = 4u,
  LPI2C1_SDA = 5u,
  LPSPI1_PCS0 = 6u,
  LPSPI1_SCK = 7u,
  LPUART1_RX = 8u,
  LPUART1_TX = 9u,
};

enum class RouteKind : std::uint8_t {
  iomuxc_mux = 0u,
};

template<PinId Pin, PeripheralSignal Signal>
struct PinAssignmentValid : std::false_type {};

template<>
struct PinAssignmentValid<PinId::GPIO_AD_B0_00, PeripheralSignal::GPIO1_IO00> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::iomuxc_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 5u;
};

template<>
struct PinAssignmentValid<PinId::GPIO_AD_B0_01, PeripheralSignal::GPIO1_IO01> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::iomuxc_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 5u;
};

template<>
struct PinAssignmentValid<PinId::GPIO_EMC_00, PeripheralSignal::GPIO4_IO00> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::iomuxc_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 5u;
};

template<>
struct PinAssignmentValid<PinId::GPIO_EMC_01, PeripheralSignal::GPIO4_IO01> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::iomuxc_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 5u;
};

template<>
struct PinAssignmentValid<PinId::GPIO_AD_B0_00, PeripheralSignal::LPI2C1_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::iomuxc_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::GPIO_AD_B0_01, PeripheralSignal::LPI2C1_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::iomuxc_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::GPIO_EMC_01, PeripheralSignal::LPSPI1_PCS0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::iomuxc_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GPIO_EMC_00, PeripheralSignal::LPSPI1_SCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::iomuxc_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GPIO_AD_B0_01, PeripheralSignal::LPUART1_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::iomuxc_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GPIO_AD_B0_00, PeripheralSignal::LPUART1_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::iomuxc_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<PinId Pin, PeripheralSignal Signal>
concept ValidPinAssignment = PinAssignmentValid<Pin, Signal>::value;

struct PinAssignmentEntry {
  PinId pin;
  PeripheralSignal signal;
  RouteKind route_kind;
  std::uint8_t route_selector_index;
};

inline constexpr std::array<PinAssignmentEntry, 10> kPinAssignments = {{
  {PinId::GPIO_AD_B0_00, PeripheralSignal::GPIO1_IO00, RouteKind::iomuxc_mux, 5u},
  {PinId::GPIO_AD_B0_01, PeripheralSignal::GPIO1_IO01, RouteKind::iomuxc_mux, 5u},
  {PinId::GPIO_EMC_00, PeripheralSignal::GPIO4_IO00, RouteKind::iomuxc_mux, 5u},
  {PinId::GPIO_EMC_01, PeripheralSignal::GPIO4_IO01, RouteKind::iomuxc_mux, 5u},
  {PinId::GPIO_AD_B0_00, PeripheralSignal::LPI2C1_SCL, RouteKind::iomuxc_mux, 0u},
  {PinId::GPIO_AD_B0_01, PeripheralSignal::LPI2C1_SDA, RouteKind::iomuxc_mux, 0u},
  {PinId::GPIO_EMC_01, PeripheralSignal::LPSPI1_PCS0, RouteKind::iomuxc_mux, 2u},
  {PinId::GPIO_EMC_00, PeripheralSignal::LPSPI1_SCK, RouteKind::iomuxc_mux, 2u},
  {PinId::GPIO_AD_B0_01, PeripheralSignal::LPUART1_RX, RouteKind::iomuxc_mux, 2u},
  {PinId::GPIO_AD_B0_00, PeripheralSignal::LPUART1_TX, RouteKind::iomuxc_mux, 2u},
}};

constexpr bool is_valid_pin_assignment(PinId pin, PeripheralSignal signal) noexcept {
  for (auto const& entry : kPinAssignments) {
    if (entry.pin == pin && entry.signal == signal) {
      return true;
    }
  }
  return false;
}
}
}
}
}
}
}
