#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace pico {
enum class PeripheralSignal : std::uint16_t {
  ADC_CH0 = 0u,
  ADC_CH1 = 1u,
  ADC_CH2 = 2u,
  I2C0_SCL = 3u,
  I2C0_SDA = 4u,
  I2C1_SCL = 5u,
  I2C1_SDA = 6u,
  SPI0_CSN = 7u,
  SPI0_RX = 8u,
  SPI0_SCK = 9u,
  SPI0_TX = 10u,
  SPI1_CSN = 11u,
  SPI1_RX = 12u,
  SPI1_SCK = 13u,
  SPI1_TX = 14u,
  UART0_CTS = 15u,
  UART0_RTS = 16u,
  UART0_RX = 17u,
  UART0_TX = 18u,
  UART1_CTS = 19u,
  UART1_RTS = 20u,
  UART1_RX = 21u,
  UART1_TX = 22u,
};

enum class RouteKind : std::uint8_t {
  mux = 0u,
};

template<PinId Pin, PeripheralSignal Signal>
struct PinAssignmentValid : std::false_type {};

template<>
struct PinAssignmentValid<PinId::GP26, PeripheralSignal::ADC_CH0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::GP27, PeripheralSignal::ADC_CH1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::GP28, PeripheralSignal::ADC_CH2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::GP1, PeripheralSignal::I2C0_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP13, PeripheralSignal::I2C0_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP17, PeripheralSignal::I2C0_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP21, PeripheralSignal::I2C0_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP25, PeripheralSignal::I2C0_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP5, PeripheralSignal::I2C0_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP9, PeripheralSignal::I2C0_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP0, PeripheralSignal::I2C0_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP12, PeripheralSignal::I2C0_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP16, PeripheralSignal::I2C0_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP20, PeripheralSignal::I2C0_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP4, PeripheralSignal::I2C0_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP8, PeripheralSignal::I2C0_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP11, PeripheralSignal::I2C1_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP15, PeripheralSignal::I2C1_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP19, PeripheralSignal::I2C1_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP3, PeripheralSignal::I2C1_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP7, PeripheralSignal::I2C1_SCL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP10, PeripheralSignal::I2C1_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP14, PeripheralSignal::I2C1_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP18, PeripheralSignal::I2C1_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP2, PeripheralSignal::I2C1_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP22, PeripheralSignal::I2C1_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP6, PeripheralSignal::I2C1_SDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::GP1, PeripheralSignal::SPI0_CSN> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP17, PeripheralSignal::SPI0_CSN> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP21, PeripheralSignal::SPI0_CSN> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP5, PeripheralSignal::SPI0_CSN> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP0, PeripheralSignal::SPI0_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP16, PeripheralSignal::SPI0_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP20, PeripheralSignal::SPI0_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP4, PeripheralSignal::SPI0_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP18, PeripheralSignal::SPI0_SCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP2, PeripheralSignal::SPI0_SCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP22, PeripheralSignal::SPI0_SCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP6, PeripheralSignal::SPI0_SCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP19, PeripheralSignal::SPI0_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP3, PeripheralSignal::SPI0_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP7, PeripheralSignal::SPI0_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP13, PeripheralSignal::SPI1_CSN> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP25, PeripheralSignal::SPI1_CSN> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP9, PeripheralSignal::SPI1_CSN> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP12, PeripheralSignal::SPI1_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP8, PeripheralSignal::SPI1_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP10, PeripheralSignal::SPI1_SCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP14, PeripheralSignal::SPI1_SCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP11, PeripheralSignal::SPI1_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP15, PeripheralSignal::SPI1_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::GP14, PeripheralSignal::UART0_CTS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP18, PeripheralSignal::UART0_CTS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP2, PeripheralSignal::UART0_CTS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP15, PeripheralSignal::UART0_RTS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP19, PeripheralSignal::UART0_RTS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP3, PeripheralSignal::UART0_RTS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP1, PeripheralSignal::UART0_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP13, PeripheralSignal::UART0_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP17, PeripheralSignal::UART0_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP0, PeripheralSignal::UART0_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP12, PeripheralSignal::UART0_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP16, PeripheralSignal::UART0_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP10, PeripheralSignal::UART1_CTS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP22, PeripheralSignal::UART1_CTS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP6, PeripheralSignal::UART1_CTS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP11, PeripheralSignal::UART1_RTS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP7, PeripheralSignal::UART1_RTS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP21, PeripheralSignal::UART1_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP5, PeripheralSignal::UART1_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP9, PeripheralSignal::UART1_RX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP20, PeripheralSignal::UART1_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP25, PeripheralSignal::UART1_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP4, PeripheralSignal::UART1_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::GP8, PeripheralSignal::UART1_TX> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::mux;
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

inline constexpr std::array<PinAssignmentEntry, 75> kPinAssignments = {{
  {PinId::GP26, PeripheralSignal::ADC_CH0, RouteKind::mux, 0u},
  {PinId::GP27, PeripheralSignal::ADC_CH1, RouteKind::mux, 0u},
  {PinId::GP28, PeripheralSignal::ADC_CH2, RouteKind::mux, 0u},
  {PinId::GP1, PeripheralSignal::I2C0_SCL, RouteKind::mux, 3u},
  {PinId::GP13, PeripheralSignal::I2C0_SCL, RouteKind::mux, 3u},
  {PinId::GP17, PeripheralSignal::I2C0_SCL, RouteKind::mux, 3u},
  {PinId::GP21, PeripheralSignal::I2C0_SCL, RouteKind::mux, 3u},
  {PinId::GP25, PeripheralSignal::I2C0_SCL, RouteKind::mux, 3u},
  {PinId::GP5, PeripheralSignal::I2C0_SCL, RouteKind::mux, 3u},
  {PinId::GP9, PeripheralSignal::I2C0_SCL, RouteKind::mux, 3u},
  {PinId::GP0, PeripheralSignal::I2C0_SDA, RouteKind::mux, 3u},
  {PinId::GP12, PeripheralSignal::I2C0_SDA, RouteKind::mux, 3u},
  {PinId::GP16, PeripheralSignal::I2C0_SDA, RouteKind::mux, 3u},
  {PinId::GP20, PeripheralSignal::I2C0_SDA, RouteKind::mux, 3u},
  {PinId::GP4, PeripheralSignal::I2C0_SDA, RouteKind::mux, 3u},
  {PinId::GP8, PeripheralSignal::I2C0_SDA, RouteKind::mux, 3u},
  {PinId::GP11, PeripheralSignal::I2C1_SCL, RouteKind::mux, 3u},
  {PinId::GP15, PeripheralSignal::I2C1_SCL, RouteKind::mux, 3u},
  {PinId::GP19, PeripheralSignal::I2C1_SCL, RouteKind::mux, 3u},
  {PinId::GP3, PeripheralSignal::I2C1_SCL, RouteKind::mux, 3u},
  {PinId::GP7, PeripheralSignal::I2C1_SCL, RouteKind::mux, 3u},
  {PinId::GP10, PeripheralSignal::I2C1_SDA, RouteKind::mux, 3u},
  {PinId::GP14, PeripheralSignal::I2C1_SDA, RouteKind::mux, 3u},
  {PinId::GP18, PeripheralSignal::I2C1_SDA, RouteKind::mux, 3u},
  {PinId::GP2, PeripheralSignal::I2C1_SDA, RouteKind::mux, 3u},
  {PinId::GP22, PeripheralSignal::I2C1_SDA, RouteKind::mux, 3u},
  {PinId::GP6, PeripheralSignal::I2C1_SDA, RouteKind::mux, 3u},
  {PinId::GP1, PeripheralSignal::SPI0_CSN, RouteKind::mux, 1u},
  {PinId::GP17, PeripheralSignal::SPI0_CSN, RouteKind::mux, 1u},
  {PinId::GP21, PeripheralSignal::SPI0_CSN, RouteKind::mux, 1u},
  {PinId::GP5, PeripheralSignal::SPI0_CSN, RouteKind::mux, 1u},
  {PinId::GP0, PeripheralSignal::SPI0_RX, RouteKind::mux, 1u},
  {PinId::GP16, PeripheralSignal::SPI0_RX, RouteKind::mux, 1u},
  {PinId::GP20, PeripheralSignal::SPI0_RX, RouteKind::mux, 1u},
  {PinId::GP4, PeripheralSignal::SPI0_RX, RouteKind::mux, 1u},
  {PinId::GP18, PeripheralSignal::SPI0_SCK, RouteKind::mux, 1u},
  {PinId::GP2, PeripheralSignal::SPI0_SCK, RouteKind::mux, 1u},
  {PinId::GP22, PeripheralSignal::SPI0_SCK, RouteKind::mux, 1u},
  {PinId::GP6, PeripheralSignal::SPI0_SCK, RouteKind::mux, 1u},
  {PinId::GP19, PeripheralSignal::SPI0_TX, RouteKind::mux, 1u},
  {PinId::GP3, PeripheralSignal::SPI0_TX, RouteKind::mux, 1u},
  {PinId::GP7, PeripheralSignal::SPI0_TX, RouteKind::mux, 1u},
  {PinId::GP13, PeripheralSignal::SPI1_CSN, RouteKind::mux, 1u},
  {PinId::GP25, PeripheralSignal::SPI1_CSN, RouteKind::mux, 1u},
  {PinId::GP9, PeripheralSignal::SPI1_CSN, RouteKind::mux, 1u},
  {PinId::GP12, PeripheralSignal::SPI1_RX, RouteKind::mux, 1u},
  {PinId::GP8, PeripheralSignal::SPI1_RX, RouteKind::mux, 1u},
  {PinId::GP10, PeripheralSignal::SPI1_SCK, RouteKind::mux, 1u},
  {PinId::GP14, PeripheralSignal::SPI1_SCK, RouteKind::mux, 1u},
  {PinId::GP11, PeripheralSignal::SPI1_TX, RouteKind::mux, 1u},
  {PinId::GP15, PeripheralSignal::SPI1_TX, RouteKind::mux, 1u},
  {PinId::GP14, PeripheralSignal::UART0_CTS, RouteKind::mux, 2u},
  {PinId::GP18, PeripheralSignal::UART0_CTS, RouteKind::mux, 2u},
  {PinId::GP2, PeripheralSignal::UART0_CTS, RouteKind::mux, 2u},
  {PinId::GP15, PeripheralSignal::UART0_RTS, RouteKind::mux, 2u},
  {PinId::GP19, PeripheralSignal::UART0_RTS, RouteKind::mux, 2u},
  {PinId::GP3, PeripheralSignal::UART0_RTS, RouteKind::mux, 2u},
  {PinId::GP1, PeripheralSignal::UART0_RX, RouteKind::mux, 2u},
  {PinId::GP13, PeripheralSignal::UART0_RX, RouteKind::mux, 2u},
  {PinId::GP17, PeripheralSignal::UART0_RX, RouteKind::mux, 2u},
  {PinId::GP0, PeripheralSignal::UART0_TX, RouteKind::mux, 2u},
  {PinId::GP12, PeripheralSignal::UART0_TX, RouteKind::mux, 2u},
  {PinId::GP16, PeripheralSignal::UART0_TX, RouteKind::mux, 2u},
  {PinId::GP10, PeripheralSignal::UART1_CTS, RouteKind::mux, 2u},
  {PinId::GP22, PeripheralSignal::UART1_CTS, RouteKind::mux, 2u},
  {PinId::GP6, PeripheralSignal::UART1_CTS, RouteKind::mux, 2u},
  {PinId::GP11, PeripheralSignal::UART1_RTS, RouteKind::mux, 2u},
  {PinId::GP7, PeripheralSignal::UART1_RTS, RouteKind::mux, 2u},
  {PinId::GP21, PeripheralSignal::UART1_RX, RouteKind::mux, 2u},
  {PinId::GP5, PeripheralSignal::UART1_RX, RouteKind::mux, 2u},
  {PinId::GP9, PeripheralSignal::UART1_RX, RouteKind::mux, 2u},
  {PinId::GP20, PeripheralSignal::UART1_TX, RouteKind::mux, 2u},
  {PinId::GP25, PeripheralSignal::UART1_TX, RouteKind::mux, 2u},
  {PinId::GP4, PeripheralSignal::UART1_TX, RouteKind::mux, 2u},
  {PinId::GP8, PeripheralSignal::UART1_TX, RouteKind::mux, 2u},
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
