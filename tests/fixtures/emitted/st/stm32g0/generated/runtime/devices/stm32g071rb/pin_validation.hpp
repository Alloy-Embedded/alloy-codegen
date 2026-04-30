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
namespace stm32g071rb {
enum class PeripheralSignal : std::uint16_t {
  SPI1_SCK = 0u,
  USART1_RX = 1u,
  USART1_TX = 2u,
};

enum class RouteKind : std::uint8_t {
  alternate_function = 0u,
};

template<PinId Pin, PeripheralSignal Signal>
struct PinAssignmentValid : std::false_type {};

template<>
struct PinAssignmentValid<PinId::PA1, PeripheralSignal::SPI1_SCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PB7, PeripheralSignal::USART1_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PB6, PeripheralSignal::USART1_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
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

inline constexpr std::array<PinAssignmentEntry, 3> kPinAssignments = {{
  {PinId::PA1, PeripheralSignal::SPI1_SCK, RouteKind::alternate_function, 0u},
  {PinId::PB7, PeripheralSignal::USART1_RX, RouteKind::alternate_function, 0u},
  {PinId::PB6, PeripheralSignal::USART1_TX, RouteKind::alternate_function, 0u},
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
