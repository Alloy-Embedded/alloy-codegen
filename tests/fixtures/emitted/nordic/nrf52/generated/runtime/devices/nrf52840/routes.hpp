#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "clock_bindings.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"
#include "register_fields.hpp"
#include "registers.hpp"

namespace nordic {
namespace nrf52 {
namespace generated {
namespace runtime {
namespace devices {
namespace nrf52840 {
struct RouteOperation {
  BackendSchemaId schema_id;
  OperationKindId kind_id;
  OperationSubjectKindId subject_kind_id;
  RegisterId register_id;
  FieldId field_id;
  PinId pin_id;
  ClockGateId clock_gate_id;
  ResetId reset_id;
  int value_int;
};

enum class RouteId : std::uint16_t {
  none,
  candidate_p0_06_uart0_tx,
  candidate_p0_08_uart0_rx,
  candidate_p0_19_spi0_sck,
  candidate_p0_20_spi0_mosi,
  candidate_p0_21_spi0_miso,
  candidate_p0_26_i2c0_sda,
  candidate_p0_27_i2c0_scl,
};

struct RouteDescriptor {
  RouteId route_id;
  PinId pin_id;
  PeripheralId peripheral_id;
  SignalId signal_id;
  RouteKindId route_kind_id;
};

template<PinId Pin, PeripheralId Peripheral, SignalId Signal>
struct RouteTraits {
  static constexpr bool kPresent = false;
  static constexpr RouteId kRouteId = RouteId::none;
  static constexpr RouteKindId kRouteKindId = RouteKindId::none;
  static constexpr std::array<RouteOperation, 0> kOperations = {};
};

template<>
struct RouteTraits<PinId::P0_06, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_p0_06_uart0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_nordic_generic_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::P0_06, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::P0_08, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_p0_08_uart0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_nordic_generic_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::P0_08, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::P0_19, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_p0_19_spi0_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_nordic_generic_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::P0_19, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::P0_20, PeripheralId::SPI0, SignalId::signal_mosi> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_p0_20_spi0_mosi;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_nordic_generic_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::P0_20, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::P0_21, PeripheralId::SPI0, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_p0_21_spi0_miso;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_nordic_generic_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::P0_21, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::P0_26, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_p0_26_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_nordic_generic_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::P0_26, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::P0_27, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_p0_27_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_nordic_generic_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::P0_27, ClockGateId::none, ResetId::none, 0},
  }};
};

inline constexpr std::array<RouteDescriptor, 7> kRuntimeRoutes = {{
  {RouteId::candidate_p0_06_uart0_tx, PinId::P0_06, PeripheralId::UART0, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_p0_08_uart0_rx, PinId::P0_08, PeripheralId::UART0, SignalId::signal_rx, RouteKindId::route_kind_mux},
  {RouteId::candidate_p0_19_spi0_sck, PinId::P0_19, PeripheralId::SPI0, SignalId::signal_sck, RouteKindId::route_kind_mux},
  {RouteId::candidate_p0_20_spi0_mosi, PinId::P0_20, PeripheralId::SPI0, SignalId::signal_mosi, RouteKindId::route_kind_mux},
  {RouteId::candidate_p0_21_spi0_miso, PinId::P0_21, PeripheralId::SPI0, SignalId::signal_miso, RouteKindId::route_kind_mux},
  {RouteId::candidate_p0_26_i2c0_sda, PinId::P0_26, PeripheralId::I2C0, SignalId::signal_sda, RouteKindId::route_kind_mux},
  {RouteId::candidate_p0_27_i2c0_scl, PinId::P0_27, PeripheralId::I2C0, SignalId::signal_scl, RouteKindId::route_kind_mux},
}};

template<PinId Pin, PeripheralId Peripheral, SignalId Signal>
inline auto apply_route() noexcept -> void {
  static_assert(RouteTraits<Pin, Peripheral, Signal>::kPresent, "");
}

enum class ConnectionGroupId : std::uint16_t {
  none,
  group_i2c0_aqfn73_scl_sda,
  group_spi0_aqfn73_sck_mosi_miso,
  group_uart0_aqfn73_tx_rx,
};

template<PeripheralId Peripheral, SignalId... Signals>
struct ConnectionGroupTraits {
  static constexpr bool kPresent = false;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::none;
  static constexpr std::array<RouteId, 0> kRoutes = {};
};

template<>
struct ConnectionGroupTraits<PeripheralId::I2C0, SignalId::signal_scl, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_i2c0_aqfn73_scl_sda;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_p0_26_i2c0_sda,
    RouteId::candidate_p0_27_i2c0_scl,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::SPI0, SignalId::signal_sck, SignalId::signal_mosi, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_spi0_aqfn73_sck_mosi_miso;
  static constexpr std::array<RouteId, 3> kRoutes = {{
    RouteId::candidate_p0_19_spi0_sck,
    RouteId::candidate_p0_20_spi0_mosi,
    RouteId::candidate_p0_21_spi0_miso,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::UART0, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_uart0_aqfn73_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_p0_06_uart0_tx,
    RouteId::candidate_p0_08_uart0_rx,
  }};
};

struct ConnectionGroupDescriptor {
  ConnectionGroupId group_id;
  PeripheralId peripheral_id;
  std::uint16_t route_count;
};
inline constexpr std::array<ConnectionGroupDescriptor, 3> kRuntimeConnectionGroups = {{
  {ConnectionGroupId::group_i2c0_aqfn73_scl_sda, PeripheralId::I2C0, 2u},
  {ConnectionGroupId::group_spi0_aqfn73_sck_mosi_miso, PeripheralId::SPI0, 3u},
  {ConnectionGroupId::group_uart0_aqfn73_tx_rx, PeripheralId::UART0, 2u},
}};

}
}
}
}
}
}
