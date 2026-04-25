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
namespace stm32g071rb {
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
  candidate_pa1_spi1_sck,
  candidate_pb6_usart1_tx,
  candidate_pb7_usart1_rx,
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
struct RouteTraits<PinId::PA1, PeripheralId::SPI1, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa1_spi1_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbenr2, FieldId::none, PinId::none, ClockGateId::gate_spi1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbrstr2, FieldId::none, PinId::none, ClockGateId::none, ResetId::reset_spi1, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA1, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PB6, PeripheralId::USART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb6_usart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbenr2, FieldId::field_rcc_apbenr2_usart1en, PinId::none, ClockGateId::gate_usart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbrstr2, FieldId::field_rcc_apbrstr2_usart1rst, PinId::none, ClockGateId::none, ResetId::reset_usart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB6, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PB7, PeripheralId::USART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pb7_usart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbenr2, FieldId::field_rcc_apbenr2_usart1en, PinId::none, ClockGateId::gate_usart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbrstr2, FieldId::field_rcc_apbrstr2_usart1rst, PinId::none, ClockGateId::none, ResetId::reset_usart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PB7, ClockGateId::none, ResetId::none, 0},
  }};
};

inline constexpr std::array<RouteDescriptor, 3> kRuntimeRoutes = {{
  {RouteId::candidate_pa1_spi1_sck, PinId::PA1, PeripheralId::SPI1, SignalId::signal_sck, RouteKindId::route_kind_alternate_function},
  {RouteId::candidate_pb6_usart1_tx, PinId::PB6, PeripheralId::USART1, SignalId::signal_tx, RouteKindId::route_kind_alternate_function},
  {RouteId::candidate_pb7_usart1_rx, PinId::PB7, PeripheralId::USART1, SignalId::signal_rx, RouteKindId::route_kind_alternate_function},
}};

template<PinId Pin, PeripheralId Peripheral, SignalId Signal>
inline auto apply_route() noexcept -> void {
  static_assert(RouteTraits<Pin, Peripheral, Signal>::kPresent, "");
}

template<>
inline auto apply_route<PinId::PA1, PeripheralId::SPI1, SignalId::signal_sck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x50000000u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000000u) & ~(std::uint32_t{0x3} << 2)) | (std::uint32_t{0x2} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000020u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000020u) & ~(std::uint32_t{0xF} << 4)) | (std::uint32_t{0x0} << 4);
}

template<>
inline auto apply_route<PinId::PB6, PeripheralId::USART1, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x40021040u) |=(std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x40021030u) &= ~(std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000400u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000400u) & ~(std::uint32_t{0x3} << 12)) | (std::uint32_t{0x2} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000420u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000420u) & ~(std::uint32_t{0xF} << 24)) | (std::uint32_t{0x0} << 24);
}

template<>
inline auto apply_route<PinId::PB7, PeripheralId::USART1, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x40021040u) |=(std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x40021030u) &= ~(std::uint32_t{1} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000400u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000400u) & ~(std::uint32_t{0x3} << 14)) | (std::uint32_t{0x2} << 14);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000420u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000420u) & ~(std::uint32_t{0xF} << 28)) | (std::uint32_t{0x0} << 28);
}

enum class ConnectionGroupId : std::uint16_t {
  none,
  group_usart1_lqfp64_tx_rx,
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
    RouteId::candidate_pb6_usart1_tx,
    RouteId::candidate_pb7_usart1_rx,
  }};
};

struct ConnectionGroupDescriptor {
  ConnectionGroupId group_id;
  PeripheralId peripheral_id;
  std::uint16_t route_count;
};
inline constexpr std::array<ConnectionGroupDescriptor, 1> kRuntimeConnectionGroups = {{
  {ConnectionGroupId::group_usart1_lqfp64_tx_rx, PeripheralId::USART1, 2u},
}};

}
}
}
}
}
}
