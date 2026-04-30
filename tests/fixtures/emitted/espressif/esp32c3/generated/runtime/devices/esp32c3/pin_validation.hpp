#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"

namespace espressif {
namespace esp32c3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32c3 {
enum class PeripheralSignal : std::uint16_t {
  I2C0_SCL = 0u,
  I2C0_SDA = 1u,
  SPI2_CS = 2u,
  SPI2_MISO = 3u,
  SPI2_MOSI = 4u,
  SPI2_SCK = 5u,
  UART0_RX = 6u,
  UART0_TX = 7u,
  UART1_RX = 8u,
  UART1_TX = 9u,
};

enum class RouteKind : std::uint8_t {
  mux = 0u,
};

template<PinId Pin, PeripheralSignal Signal>
struct PinAssignmentValid : std::false_type {};

template<>
struct PinAssignmentValid<PinId::GPIO9, PeripheralSignal::I2C0_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 14u;
};

template<>
struct PinAssignmentValid<PinId::GPIO8, PeripheralSignal::I2C0_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 15u;
};

template<>
struct PinAssignmentValid<PinId::GPIO10, PeripheralSignal::SPI2_CS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 68u;
};

template<>
struct PinAssignmentValid<PinId::GPIO2, PeripheralSignal::SPI2_MISO> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 63u;
};

template<>
struct PinAssignmentValid<PinId::GPIO7, PeripheralSignal::SPI2_MOSI> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 64u;
};

template<>
struct PinAssignmentValid<PinId::GPIO6, PeripheralSignal::SPI2_SCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 63u;
};

template<>
struct PinAssignmentValid<PinId::GPIO20, PeripheralSignal::UART0_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 6u;
};

template<>
struct PinAssignmentValid<PinId::GPIO21, PeripheralSignal::UART0_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 6u;
};

template<>
struct PinAssignmentValid<PinId::GPIO5, PeripheralSignal::UART1_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 9u;
};

template<>
struct PinAssignmentValid<PinId::GPIO4, PeripheralSignal::UART1_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 9u;
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
  {PinId::GPIO9, PeripheralSignal::I2C0_SCL, RouteKind::mux, 14u},
  {PinId::GPIO8, PeripheralSignal::I2C0_SDA, RouteKind::mux, 15u},
  {PinId::GPIO10, PeripheralSignal::SPI2_CS, RouteKind::mux, 68u},
  {PinId::GPIO2, PeripheralSignal::SPI2_MISO, RouteKind::mux, 63u},
  {PinId::GPIO7, PeripheralSignal::SPI2_MOSI, RouteKind::mux, 64u},
  {PinId::GPIO6, PeripheralSignal::SPI2_SCK, RouteKind::mux, 63u},
  {PinId::GPIO20, PeripheralSignal::UART0_RX, RouteKind::mux, 6u},
  {PinId::GPIO21, PeripheralSignal::UART0_TX, RouteKind::mux, 6u},
  {PinId::GPIO5, PeripheralSignal::UART1_RX, RouteKind::mux, 9u},
  {PinId::GPIO4, PeripheralSignal::UART1_TX, RouteKind::mux, 9u},
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
