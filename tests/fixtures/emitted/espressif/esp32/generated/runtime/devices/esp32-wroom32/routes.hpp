#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "clock_bindings.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"
#include "register_fields.hpp"
#include "registers.hpp"

namespace espressif {
namespace esp32 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32_wroom32 {
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
  candidate_gpio1_uart0_tx,
  candidate_gpio3_uart0_rx,
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
struct RouteTraits<PinId::GPIO1, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio1_uart0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_espressif_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_dport_perip_clk_en, FieldId::field_dport_perip_clk_en_uart_clk_en, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_espressif_iomatrix_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO1, ClockGateId::none, ResetId::none, 14},
  }};
};

template<>
struct RouteTraits<PinId::GPIO3, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio3_uart0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_espressif_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_dport_perip_clk_en, FieldId::field_dport_perip_clk_en_uart_clk_en, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_espressif_iomatrix_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO3, ClockGateId::none, ResetId::none, 14},
  }};
};

inline constexpr std::array<RouteDescriptor, 2> kRuntimeRoutes = {{
  {RouteId::candidate_gpio1_uart0_tx, PinId::GPIO1, PeripheralId::UART0, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gpio3_uart0_rx, PinId::GPIO3, PeripheralId::UART0, SignalId::signal_rx, RouteKindId::route_kind_mux},
}};

template<PinId Pin, PeripheralId Peripheral, SignalId Signal>
inline auto apply_route() noexcept -> void {
  static_assert(RouteTraits<Pin, Peripheral, Signal>::kPresent, "");
}

template<>
inline auto apply_route<PinId::GPIO1, PeripheralId::UART0, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x3FF000C0u) |=(std::uint32_t{1} << 2);
}

template<>
inline auto apply_route<PinId::GPIO3, PeripheralId::UART0, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x3FF000C0u) |=(std::uint32_t{1} << 2);
}

enum class ConnectionGroupId : std::uint16_t {
  none,
  group_uart0_wroom_32_tx_rx,
};

template<PeripheralId Peripheral, SignalId... Signals>
struct ConnectionGroupTraits {
  static constexpr bool kPresent = false;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::none;
  static constexpr std::array<RouteId, 0> kRoutes = {};
};

template<>
struct ConnectionGroupTraits<PeripheralId::UART0, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_uart0_wroom_32_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_gpio1_uart0_tx,
    RouteId::candidate_gpio3_uart0_rx,
  }};
};

struct ConnectionGroupDescriptor {
  ConnectionGroupId group_id;
  PeripheralId peripheral_id;
  std::uint16_t route_count;
};
inline constexpr std::array<ConnectionGroupDescriptor, 1> kRuntimeConnectionGroups = {{
  {ConnectionGroupId::group_uart0_wroom_32_tx_rx, PeripheralId::UART0, 2u},
}};

}
}
}
}
}
}
