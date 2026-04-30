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
namespace stm32g030f6 {
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
  candidate_pa0_usart2_cts,
  candidate_pa1_usart2_rts,
  candidate_pa2_usart2_tx,
  candidate_pa3_usart2_rx,
  candidate_pa4_spi1_nss,
  candidate_pa5_spi1_sck,
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
struct RouteTraits<PinId::PA0, PeripheralId::USART2, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa0_usart2_cts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbenr1, FieldId::field_rcc_apbenr1_usart2en, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbrstr1, FieldId::field_rcc_apbrstr1_usart2rst, PinId::none, ClockGateId::none, ResetId::reset_usart2, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA0, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA1, PeripheralId::USART2, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa1_usart2_rts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbenr1, FieldId::field_rcc_apbenr1_usart2en, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbrstr1, FieldId::field_rcc_apbrstr1_usart2rst, PinId::none, ClockGateId::none, ResetId::reset_usart2, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA1, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA2, PeripheralId::USART2, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa2_usart2_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbenr1, FieldId::field_rcc_apbenr1_usart2en, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbrstr1, FieldId::field_rcc_apbrstr1_usart2rst, PinId::none, ClockGateId::none, ResetId::reset_usart2, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA2, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA3, PeripheralId::USART2, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa3_usart2_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbenr1, FieldId::field_rcc_apbenr1_usart2en, PinId::none, ClockGateId::gate_usart2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_rcc_apbrstr1, FieldId::field_rcc_apbrstr1_usart2rst, PinId::none, ClockGateId::none, ResetId::reset_usart2, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA3, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::PA4, PeripheralId::SPI1, SignalId::signal_nss> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa4_spi1_nss;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::none, FieldId::none, PinId::none, ClockGateId::gate_spi1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::none, FieldId::none, PinId::none, ClockGateId::none, ResetId::reset_spi1, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA4, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA5, PeripheralId::SPI1, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa5_spi1_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_alternate_function;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::none, FieldId::none, PinId::none, ClockGateId::gate_spi1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::none, FieldId::none, PinId::none, ClockGateId::none, ResetId::reset_spi1, 0},
    {BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA5, ClockGateId::none, ResetId::none, 0},
  }};
};

inline constexpr std::array<RouteDescriptor, 6> kRuntimeRoutes = {{
  {RouteId::candidate_pa0_usart2_cts, PinId::PA0, PeripheralId::USART2, SignalId::signal_cts, RouteKindId::route_kind_alternate_function},
  {RouteId::candidate_pa1_usart2_rts, PinId::PA1, PeripheralId::USART2, SignalId::signal_rts, RouteKindId::route_kind_alternate_function},
  {RouteId::candidate_pa2_usart2_tx, PinId::PA2, PeripheralId::USART2, SignalId::signal_tx, RouteKindId::route_kind_alternate_function},
  {RouteId::candidate_pa3_usart2_rx, PinId::PA3, PeripheralId::USART2, SignalId::signal_rx, RouteKindId::route_kind_alternate_function},
  {RouteId::candidate_pa4_spi1_nss, PinId::PA4, PeripheralId::SPI1, SignalId::signal_nss, RouteKindId::route_kind_alternate_function},
  {RouteId::candidate_pa5_spi1_sck, PinId::PA5, PeripheralId::SPI1, SignalId::signal_sck, RouteKindId::route_kind_alternate_function},
}};

template<PinId Pin, PeripheralId Peripheral, SignalId Signal>
inline auto apply_route() noexcept -> void {
  static_assert(RouteTraits<Pin, Peripheral, Signal>::kPresent, "");
}

template<>
inline auto apply_route<PinId::PA0, PeripheralId::USART2, SignalId::signal_cts>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4002103Cu) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x4002102Cu) &= ~(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000000u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000000u) & ~(std::uint32_t{0x3} << 0)) | (std::uint32_t{0x2} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000020u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000020u) & ~(std::uint32_t{0xF} << 0)) | (std::uint32_t{0x1} << 0);
}

template<>
inline auto apply_route<PinId::PA1, PeripheralId::USART2, SignalId::signal_rts>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4002103Cu) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x4002102Cu) &= ~(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000000u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000000u) & ~(std::uint32_t{0x3} << 2)) | (std::uint32_t{0x2} << 2);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000020u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000020u) & ~(std::uint32_t{0xF} << 4)) | (std::uint32_t{0x1} << 4);
}

template<>
inline auto apply_route<PinId::PA2, PeripheralId::USART2, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4002103Cu) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x4002102Cu) &= ~(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000000u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000000u) & ~(std::uint32_t{0x3} << 4)) | (std::uint32_t{0x2} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000020u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000020u) & ~(std::uint32_t{0xF} << 8)) | (std::uint32_t{0x1} << 8);
}

template<>
inline auto apply_route<PinId::PA3, PeripheralId::USART2, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4002103Cu) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x4002102Cu) &= ~(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000000u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000000u) & ~(std::uint32_t{0x3} << 6)) | (std::uint32_t{0x2} << 6);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000020u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000020u) & ~(std::uint32_t{0xF} << 12)) | (std::uint32_t{0x1} << 12);
}

template<>
inline auto apply_route<PinId::PA4, PeripheralId::SPI1, SignalId::signal_nss>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x50000000u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000000u) & ~(std::uint32_t{0x3} << 8)) | (std::uint32_t{0x2} << 8);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000020u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000020u) & ~(std::uint32_t{0xF} << 16)) | (std::uint32_t{0x0} << 16);
}

template<>
inline auto apply_route<PinId::PA5, PeripheralId::SPI1, SignalId::signal_sck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x50000000u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000000u) & ~(std::uint32_t{0x3} << 10)) | (std::uint32_t{0x2} << 10);
  *reinterpret_cast<volatile std::uint32_t*>(0x50000020u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x50000020u) & ~(std::uint32_t{0xF} << 20)) | (std::uint32_t{0x0} << 20);
}

enum class ConnectionGroupId : std::uint16_t {
  none,
  group_spi1_tssop20_all_signals,
  group_usart2_tssop20_tx_rx,
  group_usart2_tssop20_tx_rx_cts_rts,
};

template<PeripheralId Peripheral, SignalId... Signals>
struct ConnectionGroupTraits {
  static constexpr bool kPresent = false;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::none;
  static constexpr std::array<RouteId, 0> kRoutes = {};
};

template<>
struct ConnectionGroupTraits<PeripheralId::SPI1, SignalId::signal_nss, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_spi1_tssop20_all_signals;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pa4_spi1_nss,
    RouteId::candidate_pa5_spi1_sck,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::USART2, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_usart2_tssop20_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pa2_usart2_tx,
    RouteId::candidate_pa3_usart2_rx,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::USART2, SignalId::signal_tx, SignalId::signal_rx, SignalId::signal_cts, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_usart2_tssop20_tx_rx_cts_rts;
  static constexpr std::array<RouteId, 4> kRoutes = {{
    RouteId::candidate_pa0_usart2_cts,
    RouteId::candidate_pa1_usart2_rts,
    RouteId::candidate_pa2_usart2_tx,
    RouteId::candidate_pa3_usart2_rx,
  }};
};

struct ConnectionGroupDescriptor {
  ConnectionGroupId group_id;
  PeripheralId peripheral_id;
  std::uint16_t route_count;
};
inline constexpr std::array<ConnectionGroupDescriptor, 3> kRuntimeConnectionGroups = {{
  {ConnectionGroupId::group_spi1_tssop20_all_signals, PeripheralId::SPI1, 2u},
  {ConnectionGroupId::group_usart2_tssop20_tx_rx, PeripheralId::USART2, 2u},
  {ConnectionGroupId::group_usart2_tssop20_tx_rx_cts_rts, PeripheralId::USART2, 4u},
}};

}
}
}
}
}
}
