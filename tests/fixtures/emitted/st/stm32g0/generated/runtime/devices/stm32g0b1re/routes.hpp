#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "clock_bindings.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"
#include "register_fields.hpp"
#include "registers.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g0b1re {
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
  candidate_pa11_fdcan1_rx,
  candidate_pa12_fdcan1_tx,
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
struct RouteTraits<PinId::PA11, PeripheralId::FDCAN1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa11_fdcan1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbenr1, FieldId::field_rcc_apbenr1_fdcanen, PinId::none, ClockGateId::gate_fdcan1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbrstr1, FieldId::field_rcc_apbrstr1_fdcanrst, PinId::none, ClockGateId::none, ResetId::reset_fdcan1, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA11, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::PA12, PeripheralId::FDCAN1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa12_fdcan1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbenr1, FieldId::field_rcc_apbenr1_fdcanen, PinId::none, ClockGateId::gate_fdcan1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbrstr1, FieldId::field_rcc_apbrstr1_fdcanrst, PinId::none, ClockGateId::none, ResetId::reset_fdcan1, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA12, ClockGateId::none, ResetId::none, 3},
  }};
};

inline constexpr std::array<RouteDescriptor, 2> kRuntimeRoutes = {{
  {RouteId::candidate_pa11_fdcan1_rx, PinId::PA11, PeripheralId::FDCAN1, SignalId::signal_rx, RouteKindId::route_kind_alternate_function},
  {RouteId::candidate_pa12_fdcan1_tx, PinId::PA12, PeripheralId::FDCAN1, SignalId::signal_tx, RouteKindId::route_kind_alternate_function},
}};

template<PinId Pin, PeripheralId Peripheral, SignalId Signal>
inline auto apply_route() noexcept -> void {
  static_assert(RouteTraits<Pin, Peripheral, Signal>::kPresent, "");
}

template<>
inline auto apply_route<PinId::PA11, PeripheralId::FDCAN1, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4002103Cu) |=(std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x4002102Cu) &= ~(std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000000u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000000u) & ~(std::uint32_t{0x3} << 22)) | (std::uint32_t{0x2} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000024u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000024u) & ~(std::uint32_t{0xF} << 12)) | (std::uint32_t{0x3} << 12);
}

template<>
inline auto apply_route<PinId::PA12, PeripheralId::FDCAN1, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4002103Cu) |=(std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x4002102Cu) &= ~(std::uint32_t{1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000000u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000000u) & ~(std::uint32_t{0x3} << 24)) | (std::uint32_t{0x2} << 24);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000024u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000024u) & ~(std::uint32_t{0xF} << 16)) | (std::uint32_t{0x3} << 16);
}

enum class ConnectionGroupId : std::uint16_t {
  none,
  group_fdcan1_lqfp64_tx_rx,
};

template<PeripheralId Peripheral, SignalId... Signals>
struct ConnectionGroupTraits {
  static constexpr bool kPresent = false;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::none;
  static constexpr std::array<RouteId, 0> kRoutes = {};
};

template<>
struct ConnectionGroupTraits<PeripheralId::FDCAN1, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_fdcan1_lqfp64_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pa11_fdcan1_rx,
    RouteId::candidate_pa12_fdcan1_tx,
  }};
};

struct ConnectionGroupDescriptor {
  ConnectionGroupId group_id;
  PeripheralId peripheral_id;
  std::uint16_t route_count;
};
inline constexpr std::array<ConnectionGroupDescriptor, 1> kRuntimeConnectionGroups = {{
  {ConnectionGroupId::group_fdcan1_lqfp64_tx_rx, PeripheralId::FDCAN1, 2u},
}};

}
}
}
}
}
}
