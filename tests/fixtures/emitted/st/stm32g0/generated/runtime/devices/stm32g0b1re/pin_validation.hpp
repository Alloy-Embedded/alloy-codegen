#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g0b1re {
enum class PeripheralSignal : std::uint16_t {
  FDCAN1_RX = 0u,
  FDCAN1_TX = 1u,
};

enum class RouteKind : std::uint8_t {
  alternate_function = 0u,
};

template<PinId Pin, PeripheralSignal Signal>
struct PinAssignmentValid : std::false_type {};

template<>
struct PinAssignmentValid<PinId::PA11, PeripheralSignal::FDCAN1_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PA12, PeripheralSignal::FDCAN1_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
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
  {PinId::PA11, PeripheralSignal::FDCAN1_RX, RouteKind::alternate_function, 3u},
  {PinId::PA12, PeripheralSignal::FDCAN1_TX, RouteKind::alternate_function, 3u},
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
