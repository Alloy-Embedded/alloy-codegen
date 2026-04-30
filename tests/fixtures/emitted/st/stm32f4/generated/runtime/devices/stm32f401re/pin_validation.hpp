#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f401re {
enum class PeripheralSignal : std::uint16_t {
  USART1_RX = 0u,
  USART1_TX = 1u,
  USART2_RX = 2u,
  USART2_TX = 3u,
};

enum class RouteKind : std::uint8_t {
  alternate_function = 0u,
};

template<PinId Pin, PeripheralSignal Signal>
struct PinAssignmentValid : std::false_type {};

template<>
struct PinAssignmentValid<PinId::PA10, PeripheralSignal::USART1_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
  static constexpr std::uint8_t kRouteSelectorIndex = 7u;
};

template<>
struct PinAssignmentValid<PinId::PA9, PeripheralSignal::USART1_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
  static constexpr std::uint8_t kRouteSelectorIndex = 7u;
};

template<>
struct PinAssignmentValid<PinId::PA3, PeripheralSignal::USART2_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
  static constexpr std::uint8_t kRouteSelectorIndex = 7u;
};

template<>
struct PinAssignmentValid<PinId::PA2, PeripheralSignal::USART2_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
  static constexpr std::uint8_t kRouteSelectorIndex = 7u;
};

template<PinId Pin, PeripheralSignal Signal>
concept ValidPinAssignment = PinAssignmentValid<Pin, Signal>::value;

struct PinAssignmentEntry {
  PinId pin;
  PeripheralSignal signal;
  RouteKind route_kind;
  std::uint8_t route_selector_index;
};

inline constexpr std::array<PinAssignmentEntry, 4> kPinAssignments = {{
  {PinId::PA10, PeripheralSignal::USART1_RX, RouteKind::alternate_function, 7u},
  {PinId::PA9, PeripheralSignal::USART1_TX, RouteKind::alternate_function, 7u},
  {PinId::PA3, PeripheralSignal::USART2_RX, RouteKind::alternate_function, 7u},
  {PinId::PA2, PeripheralSignal::USART2_TX, RouteKind::alternate_function, 7u},
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
