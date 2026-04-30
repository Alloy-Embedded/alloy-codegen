#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"

namespace nordic {
namespace nrf52 {
namespace generated {
namespace runtime {
namespace devices {
namespace nrf52840 {
enum class PeripheralSignal : std::uint16_t {
  I2C0_SCL = 0u,
  I2C0_SDA = 1u,
  SPI0_MISO = 2u,
  SPI0_MOSI = 3u,
  SPI0_SCK = 4u,
  UART0_RX = 5u,
  UART0_TX = 6u,
};

enum class RouteKind : std::uint8_t {
  mux = 0u,
};

template<PinId Pin, PeripheralSignal Signal>
struct PinAssignmentValid : std::false_type {};

template<>
struct PinAssignmentValid<PinId::P0_27, PeripheralSignal::I2C0_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::P0_26, PeripheralSignal::I2C0_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::P0_21, PeripheralSignal::SPI0_MISO> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::P0_20, PeripheralSignal::SPI0_MOSI> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::P0_19, PeripheralSignal::SPI0_SCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::P0_08, PeripheralSignal::UART0_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::P0_06, PeripheralSignal::UART0_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<PinId Pin, PeripheralSignal Signal>
concept ValidPinAssignment = PinAssignmentValid<Pin, Signal>::value;

struct PinAssignmentEntry {
  PinId pin;
  PeripheralSignal signal;
  RouteKind route_kind;
  std::uint8_t route_selector_index;
};

inline constexpr std::array<PinAssignmentEntry, 7> kPinAssignments = {{
  {PinId::P0_27, PeripheralSignal::I2C0_SCL, RouteKind::mux, 0u},
  {PinId::P0_26, PeripheralSignal::I2C0_SDA, RouteKind::mux, 0u},
  {PinId::P0_21, PeripheralSignal::SPI0_MISO, RouteKind::mux, 0u},
  {PinId::P0_20, PeripheralSignal::SPI0_MOSI, RouteKind::mux, 0u},
  {PinId::P0_19, PeripheralSignal::SPI0_SCK, RouteKind::mux, 0u},
  {PinId::P0_08, PeripheralSignal::UART0_RX, RouteKind::mux, 0u},
  {PinId::P0_06, PeripheralSignal::UART0_TX, RouteKind::mux, 0u},
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
