#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"

namespace espressif {
namespace esp32 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32_wroom32 {
enum class PeripheralSignal : std::uint16_t {
  UART0_RX = 0u,
  UART0_TX = 1u,
};

enum class RouteKind : std::uint8_t {
  mux = 0u,
};

template<PinId Pin, PeripheralSignal Signal>
struct PinAssignmentValid : std::false_type {};

template<>
struct PinAssignmentValid<PinId::GPIO3, PeripheralSignal::UART0_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 14u;
};

template<>
struct PinAssignmentValid<PinId::GPIO1, PeripheralSignal::UART0_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 14u;
};

template<PinId Pin, PeripheralSignal Signal>
concept ValidPinAssignment = PinAssignmentValid<Pin, Signal>::value;

struct PinAssignmentEntry {
  PinId pin;
  PeripheralSignal signal;
  RouteKind route_kind;
  std::uint8_t route_selector_index;
};

inline constexpr std::array<PinAssignmentEntry, 2> kPinAssignments = {{
  {PinId::GPIO3, PeripheralSignal::UART0_RX, RouteKind::mux, 14u},
  {PinId::GPIO1, PeripheralSignal::UART0_TX, RouteKind::mux, 14u},
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
