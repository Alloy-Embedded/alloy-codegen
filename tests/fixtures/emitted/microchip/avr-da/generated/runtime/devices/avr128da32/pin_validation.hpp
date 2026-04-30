#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
enum class PeripheralSignal : std::uint16_t {
  SPI0_CS = 0u,
  SPI0_MISO = 1u,
  SPI0_MOSI = 2u,
  SPI0_SCK = 3u,
  TWI0_SCL = 4u,
  TWI0_SDA = 5u,
  USART0_RX = 6u,
  USART0_TX = 7u,
  USART1_RX = 8u,
  USART1_TX = 9u,
};

enum class RouteKind : std::uint8_t {
  peripheral_mux = 0u,
};

template<PinId Pin, PeripheralSignal Signal>
struct PinAssignmentValid : std::false_type {};

template<>
struct PinAssignmentValid<PinId::PA7, PeripheralSignal::SPI0_CS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA5, PeripheralSignal::SPI0_MISO> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA4, PeripheralSignal::SPI0_MOSI> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA6, PeripheralSignal::SPI0_SCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA3, PeripheralSignal::TWI0_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA2, PeripheralSignal::TWI0_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA1, PeripheralSignal::USART0_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA0, PeripheralSignal::USART0_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PC1, PeripheralSignal::USART1_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PC0, PeripheralSignal::USART1_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
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

inline constexpr std::array<PinAssignmentEntry, 10> kPinAssignments = {{
  {PinId::PA7, PeripheralSignal::SPI0_CS, RouteKind::peripheral_mux, 0u},
  {PinId::PA5, PeripheralSignal::SPI0_MISO, RouteKind::peripheral_mux, 0u},
  {PinId::PA4, PeripheralSignal::SPI0_MOSI, RouteKind::peripheral_mux, 0u},
  {PinId::PA6, PeripheralSignal::SPI0_SCK, RouteKind::peripheral_mux, 0u},
  {PinId::PA3, PeripheralSignal::TWI0_SCL, RouteKind::peripheral_mux, 0u},
  {PinId::PA2, PeripheralSignal::TWI0_SDA, RouteKind::peripheral_mux, 0u},
  {PinId::PA1, PeripheralSignal::USART0_RX, RouteKind::peripheral_mux, 0u},
  {PinId::PA0, PeripheralSignal::USART0_TX, RouteKind::peripheral_mux, 0u},
  {PinId::PC1, PeripheralSignal::USART1_RX, RouteKind::peripheral_mux, 0u},
  {PinId::PC0, PeripheralSignal::USART1_TX, RouteKind::peripheral_mux, 0u},
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
