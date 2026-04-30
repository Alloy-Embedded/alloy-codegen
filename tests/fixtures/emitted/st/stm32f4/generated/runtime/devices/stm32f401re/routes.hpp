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
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f401re {
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
  candidate_pa10_usart1_rx,
  candidate_pa2_usart2_tx,
  candidate_pa3_usart2_rx,
  candidate_pa9_usart1_tx,
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
struct RouteTraits<PinId::PA10, PeripheralId::USART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa10_usart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_f4_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apb2enr, FieldId::field_rcc_apb2enr_usart1en, PinId::none, ClockGateId::gate_usart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_f4_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apb2rstr, FieldId::field_rcc_apb2rstr_usart1rst, PinId::none, ClockGateId::none, ResetId::reset_usart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA10, ClockGateId::none, ResetId::none, 7},
  }};
};

template<>
struct RouteTraits<PinId::PA2, PeripheralId::USART2, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa2_usart2_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_f4_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apb1enr, FieldId::field_rcc_apb1enr_usart2en, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_f4_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apb1rstr, FieldId::field_rcc_apb1rstr_usart2rst, PinId::none, ClockGateId::none, ResetId::reset_usart2, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA2, ClockGateId::none, ResetId::none, 7},
  }};
};

template<>
struct RouteTraits<PinId::PA3, PeripheralId::USART2, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa3_usart2_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_f4_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apb1enr, FieldId::field_rcc_apb1enr_usart2en, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_f4_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apb1rstr, FieldId::field_rcc_apb1rstr_usart2rst, PinId::none, ClockGateId::none, ResetId::reset_usart2, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA3, ClockGateId::none, ResetId::none, 7},
  }};
};

template<>
struct RouteTraits<PinId::PA9, PeripheralId::USART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa9_usart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_f4_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apb2enr, FieldId::field_rcc_apb2enr_usart1en, PinId::none, ClockGateId::gate_usart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_f4_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apb2rstr, FieldId::field_rcc_apb2rstr_usart1rst, PinId::none, ClockGateId::none, ResetId::reset_usart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA9, ClockGateId::none, ResetId::none, 7},
  }};
};

inline constexpr std::array<RouteDescriptor, 4> kRuntimeRoutes = {{
  {RouteId::candidate_pa10_usart1_rx, PinId::PA10, PeripheralId::USART1, SignalId::signal_rx, RouteKindId::route_kind_alternate_function},
  {RouteId::candidate_pa2_usart2_tx, PinId::PA2, PeripheralId::USART2, SignalId::signal_tx, RouteKindId::route_kind_alternate_function},
  {RouteId::candidate_pa3_usart2_rx, PinId::PA3, PeripheralId::USART2, SignalId::signal_rx, RouteKindId::route_kind_alternate_function},
  {RouteId::candidate_pa9_usart1_tx, PinId::PA9, PeripheralId::USART1, SignalId::signal_tx, RouteKindId::route_kind_alternate_function},
}};

template<PinId Pin, PeripheralId Peripheral, SignalId Signal>
inline auto apply_route() noexcept -> void {
  static_assert(RouteTraits<Pin, Peripheral, Signal>::kPresent, "");
}

template<>
inline auto apply_route<PinId::PA10, PeripheralId::USART1, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x40023844u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x40023824u) &= ~(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x40020000u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x40020000u) & ~(std::uint32_t{0x3} << 20)) | (std::uint32_t{0x2} << 20);
  *reinterpret_cast<volatile std::uint32_t*>(0x40020024u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x40020024u) & ~(std::uint32_t{0xF} << 8)) | (std::uint32_t{0x7} << 8);
}

template<>
inline auto apply_route<PinId::PA2, PeripheralId::USART2, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x40023840u) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x40023820u) &= ~(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x40020000u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x40020000u) & ~(std::uint32_t{0x3} << 4)) | (std::uint32_t{0x2} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x40020020u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x40020020u) & ~(std::uint32_t{0xF} << 8)) | (std::uint32_t{0x7} << 8);
}

template<>
inline auto apply_route<PinId::PA3, PeripheralId::USART2, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x40023840u) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x40023820u) &= ~(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x40020000u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x40020000u) & ~(std::uint32_t{0x3} << 6)) | (std::uint32_t{0x2} << 6);
  *reinterpret_cast<volatile std::uint32_t*>(0x40020020u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x40020020u) & ~(std::uint32_t{0xF} << 12)) | (std::uint32_t{0x7} << 12);
}

template<>
inline auto apply_route<PinId::PA9, PeripheralId::USART1, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x40023844u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x40023824u) &= ~(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x40020000u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x40020000u) & ~(std::uint32_t{0x3} << 18)) | (std::uint32_t{0x2} << 18);
  *reinterpret_cast<volatile std::uint32_t*>(0x40020024u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x40020024u) & ~(std::uint32_t{0xF} << 4)) | (std::uint32_t{0x7} << 4);
}

enum class ConnectionGroupId : std::uint16_t {
  none,
  group_usart1_lqfp64_tx_rx,
  group_usart2_lqfp64_tx_rx,
};

template<PeripheralId Peripheral, SignalId... Signals>
struct ConnectionGroupTraits {
  static constexpr bool kPresent = false;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::none;
  static constexpr std::array<RouteId, 0> kRoutes = {};
};

template<>
struct ConnectionGroupTraits<PeripheralId::USART1, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_usart1_lqfp64_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pa10_usart1_rx,
    RouteId::candidate_pa9_usart1_tx,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::USART2, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_usart2_lqfp64_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pa2_usart2_tx,
    RouteId::candidate_pa3_usart2_rx,
  }};
};

struct ConnectionGroupDescriptor {
  ConnectionGroupId group_id;
  PeripheralId peripheral_id;
  std::uint16_t route_count;
};
inline constexpr std::array<ConnectionGroupDescriptor, 2> kRuntimeConnectionGroups = {{
  {ConnectionGroupId::group_usart1_lqfp64_tx_rx, PeripheralId::USART1, 2u},
  {ConnectionGroupId::group_usart2_lqfp64_tx_rx, PeripheralId::USART2, 2u},
}};

}
}
}
}
}
}
