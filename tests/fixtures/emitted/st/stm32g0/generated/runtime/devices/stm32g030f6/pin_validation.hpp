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
namespace stm32g030f6 {
enum class PeripheralSignal : std::uint16_t {
  SPI1_NSS = 0u,
  SPI1_SCK = 1u,
  USART2_CTS = 2u,
  USART2_RTS = 3u,
  USART2_RX = 4u,
  USART2_TX = 5u,
};

enum class RouteKind : std::uint8_t {
  alternate_function = 0u,
};

template<PinId Pin, PeripheralSignal Signal>
struct PinAssignmentValid : std::false_type {};

template<>
struct PinAssignmentValid<PinId::PA4, PeripheralSignal::SPI1_NSS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA5, PeripheralSignal::SPI1_SCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA0, PeripheralSignal::USART2_CTS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA1, PeripheralSignal::USART2_RTS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA3, PeripheralSignal::USART2_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA2, PeripheralSignal::USART2_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::alternate_function;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<PinId Pin, PeripheralSignal Signal>
concept ValidPinAssignment = PinAssignmentValid<Pin, Signal>::value;

struct PinAssignmentEntry {
  PinId pin;
  PeripheralSignal signal;
  RouteKind route_kind;
  std::uint8_t route_selector_index;
};

inline constexpr std::array<PinAssignmentEntry, 6> kPinAssignments = {{
  {PinId::PA4, PeripheralSignal::SPI1_NSS, RouteKind::alternate_function, 0u},
  {PinId::PA5, PeripheralSignal::SPI1_SCK, RouteKind::alternate_function, 0u},
  {PinId::PA0, PeripheralSignal::USART2_CTS, RouteKind::alternate_function, 1u},
  {PinId::PA1, PeripheralSignal::USART2_RTS, RouteKind::alternate_function, 1u},
  {PinId::PA3, PeripheralSignal::USART2_RX, RouteKind::alternate_function, 1u},
  {PinId::PA2, PeripheralSignal::USART2_TX, RouteKind::alternate_function, 1u},
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
