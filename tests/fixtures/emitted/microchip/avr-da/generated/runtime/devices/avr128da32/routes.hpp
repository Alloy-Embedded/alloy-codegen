#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "clock_bindings.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"
#include "register_fields.hpp"
#include "registers.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
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
  candidate_pa0_usart0_tx,
  candidate_pa1_usart0_rx,
  candidate_pa2_twi0_sda,
  candidate_pa3_twi0_scl,
  candidate_pa4_spi0_mosi,
  candidate_pa5_spi0_miso,
  candidate_pa6_spi0_sck,
  candidate_pa7_spi0_cs,
  candidate_pc0_usart1_tx,
  candidate_pc1_usart1_rx,
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
struct RouteTraits<PinId::PA0, PeripheralId::USART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa0_usart0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_avr_portmux_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA0, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA1, PeripheralId::USART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa1_usart0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_avr_portmux_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA1, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA2, PeripheralId::TWI0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa2_twi0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_avr_portmux_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA2, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA3, PeripheralId::TWI0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa3_twi0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_avr_portmux_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA3, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA4, PeripheralId::SPI0, SignalId::signal_mosi> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa4_spi0_mosi;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_avr_portmux_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA4, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA5, PeripheralId::SPI0, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa5_spi0_miso;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_avr_portmux_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA5, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA6, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa6_spi0_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_avr_portmux_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA6, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PA7, PeripheralId::SPI0, SignalId::signal_cs> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pa7_spi0_cs;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_avr_portmux_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PA7, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PC0, PeripheralId::USART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pc0_usart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_avr_portmux_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PC0, ClockGateId::none, ResetId::none, 0},
  }};
};

template<>
struct RouteTraits<PinId::PC1, PeripheralId::USART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_pc1_usart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_peripheral_mux;
  static constexpr std::array<RouteOperation, 1> kOperations = {{
    {BackendSchemaId::schema_alloy_pinmux_avr_portmux_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::PC1, ClockGateId::none, ResetId::none, 0},
  }};
};

inline constexpr std::array<RouteDescriptor, 10> kRuntimeRoutes = {{
  {RouteId::candidate_pa0_usart0_tx, PinId::PA0, PeripheralId::USART0, SignalId::signal_tx, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa1_usart0_rx, PinId::PA1, PeripheralId::USART0, SignalId::signal_rx, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa2_twi0_sda, PinId::PA2, PeripheralId::TWI0, SignalId::signal_sda, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa3_twi0_scl, PinId::PA3, PeripheralId::TWI0, SignalId::signal_scl, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa4_spi0_mosi, PinId::PA4, PeripheralId::SPI0, SignalId::signal_mosi, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa5_spi0_miso, PinId::PA5, PeripheralId::SPI0, SignalId::signal_miso, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa6_spi0_sck, PinId::PA6, PeripheralId::SPI0, SignalId::signal_sck, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pa7_spi0_cs, PinId::PA7, PeripheralId::SPI0, SignalId::signal_cs, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pc0_usart1_tx, PinId::PC0, PeripheralId::USART1, SignalId::signal_tx, RouteKindId::route_kind_peripheral_mux},
  {RouteId::candidate_pc1_usart1_rx, PinId::PC1, PeripheralId::USART1, SignalId::signal_rx, RouteKindId::route_kind_peripheral_mux},
}};

template<PinId Pin, PeripheralId Peripheral, SignalId Signal>
inline auto apply_route() noexcept -> void {
  static_assert(RouteTraits<Pin, Peripheral, Signal>::kPresent, "");
}

template<>
inline auto apply_route<PinId::PA0, PeripheralId::USART0, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x00000204u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x00000204u) & ~(std::uint32_t{0x3} << 0)) | (std::uint32_t{0x0u} << 0);
}

template<>
inline auto apply_route<PinId::PA1, PeripheralId::USART0, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x00000204u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x00000204u) & ~(std::uint32_t{0x3} << 0)) | (std::uint32_t{0x0u} << 0);
}

template<>
inline auto apply_route<PinId::PA2, PeripheralId::TWI0, SignalId::signal_sda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x0000020Au) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x0000020Au) & ~(std::uint32_t{0x3} << 0)) | (std::uint32_t{0x0u} << 0);
}

template<>
inline auto apply_route<PinId::PA3, PeripheralId::TWI0, SignalId::signal_scl>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x0000020Au) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x0000020Au) & ~(std::uint32_t{0x3} << 0)) | (std::uint32_t{0x0u} << 0);
}

template<>
inline auto apply_route<PinId::PA4, PeripheralId::SPI0, SignalId::signal_mosi>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x00000208u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x00000208u) & ~(std::uint32_t{0x3} << 0)) | (std::uint32_t{0x0u} << 0);
}

template<>
inline auto apply_route<PinId::PA5, PeripheralId::SPI0, SignalId::signal_miso>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x00000208u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x00000208u) & ~(std::uint32_t{0x3} << 0)) | (std::uint32_t{0x0u} << 0);
}

template<>
inline auto apply_route<PinId::PA6, PeripheralId::SPI0, SignalId::signal_sck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x00000208u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x00000208u) & ~(std::uint32_t{0x3} << 0)) | (std::uint32_t{0x0u} << 0);
}

template<>
inline auto apply_route<PinId::PA7, PeripheralId::SPI0, SignalId::signal_cs>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x00000208u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x00000208u) & ~(std::uint32_t{0x3} << 0)) | (std::uint32_t{0x0u} << 0);
}

template<>
inline auto apply_route<PinId::PC0, PeripheralId::USART1, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x00000204u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x00000204u) & ~(std::uint32_t{0x3} << 2)) | (std::uint32_t{0x0u} << 2);
}

template<>
inline auto apply_route<PinId::PC1, PeripheralId::USART1, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x00000204u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x00000204u) & ~(std::uint32_t{0x3} << 2)) | (std::uint32_t{0x0u} << 2);
}

enum class ConnectionGroupId : std::uint16_t {
  none,
  group_spi0_tqfp32_sck_mosi_miso,
  group_twi0_tqfp32_scl_sda,
  group_usart0_tqfp32_tx_rx,
  group_usart1_tqfp32_tx_rx,
};

template<PeripheralId Peripheral, SignalId... Signals>
struct ConnectionGroupTraits {
  static constexpr bool kPresent = false;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::none;
  static constexpr std::array<RouteId, 0> kRoutes = {};
};

template<>
struct ConnectionGroupTraits<PeripheralId::SPI0, SignalId::signal_sck, SignalId::signal_mosi, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_spi0_tqfp32_sck_mosi_miso;
  static constexpr std::array<RouteId, 3> kRoutes = {{
    RouteId::candidate_pa4_spi0_mosi,
    RouteId::candidate_pa5_spi0_miso,
    RouteId::candidate_pa6_spi0_sck,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::TWI0, SignalId::signal_scl, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_twi0_tqfp32_scl_sda;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pa2_twi0_sda,
    RouteId::candidate_pa3_twi0_scl,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::USART0, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_usart0_tqfp32_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pa0_usart0_tx,
    RouteId::candidate_pa1_usart0_rx,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::USART1, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_usart1_tqfp32_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_pc0_usart1_tx,
    RouteId::candidate_pc1_usart1_rx,
  }};
};

struct ConnectionGroupDescriptor {
  ConnectionGroupId group_id;
  PeripheralId peripheral_id;
  std::uint16_t route_count;
};
inline constexpr std::array<ConnectionGroupDescriptor, 4> kRuntimeConnectionGroups = {{
  {ConnectionGroupId::group_spi0_tqfp32_sck_mosi_miso, PeripheralId::SPI0, 3u},
  {ConnectionGroupId::group_twi0_tqfp32_scl_sda, PeripheralId::TWI0, 2u},
  {ConnectionGroupId::group_usart0_tqfp32_tx_rx, PeripheralId::USART0, 2u},
  {ConnectionGroupId::group_usart1_tqfp32_tx_rx, PeripheralId::USART1, 2u},
}};

}
}
}
}
}
}
