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
namespace esp32c3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32c3 {
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
  candidate_gpio10_spi2_cs,
  candidate_gpio20_uart0_rx,
  candidate_gpio21_uart0_tx,
  candidate_gpio2_spi2_miso,
  candidate_gpio4_uart1_tx,
  candidate_gpio5_uart1_rx,
  candidate_gpio6_spi2_sck,
  candidate_gpio7_spi2_mosi,
  candidate_gpio8_i2c0_sda,
  candidate_gpio9_i2c0_scl,
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
struct RouteTraits<PinId::GPIO10, PeripheralId::SPI2, SignalId::signal_cs> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio10_spi2_cs;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_espressif_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pcr_spi2_conf_reg, FieldId::field_pcr_spi2_conf_reg_spi2_clk_en, PinId::none, ClockGateId::gate_spi2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_espressif_iomatrix_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO10, ClockGateId::none, ResetId::none, 68},
  }};
};

template<>
struct RouteTraits<PinId::GPIO20, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio20_uart0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_espressif_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pcr_uart0_conf0_reg, FieldId::field_pcr_uart0_conf0_reg_uart0_clk_en, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_espressif_iomatrix_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO20, ClockGateId::none, ResetId::none, 6},
  }};
};

template<>
struct RouteTraits<PinId::GPIO21, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio21_uart0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_espressif_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pcr_uart0_conf0_reg, FieldId::field_pcr_uart0_conf0_reg_uart0_clk_en, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_espressif_iomatrix_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO21, ClockGateId::none, ResetId::none, 6},
  }};
};

template<>
struct RouteTraits<PinId::GPIO2, PeripheralId::SPI2, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio2_spi2_miso;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_espressif_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pcr_spi2_conf_reg, FieldId::field_pcr_spi2_conf_reg_spi2_clk_en, PinId::none, ClockGateId::gate_spi2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_espressif_iomatrix_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO2, ClockGateId::none, ResetId::none, 63},
  }};
};

template<>
struct RouteTraits<PinId::GPIO4, PeripheralId::UART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio4_uart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_espressif_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pcr_uart1_conf0_reg, FieldId::field_pcr_uart1_conf0_reg_uart1_clk_en, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_espressif_iomatrix_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO4, ClockGateId::none, ResetId::none, 9},
  }};
};

template<>
struct RouteTraits<PinId::GPIO5, PeripheralId::UART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio5_uart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_espressif_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pcr_uart1_conf0_reg, FieldId::field_pcr_uart1_conf0_reg_uart1_clk_en, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_espressif_iomatrix_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO5, ClockGateId::none, ResetId::none, 9},
  }};
};

template<>
struct RouteTraits<PinId::GPIO6, PeripheralId::SPI2, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio6_spi2_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_espressif_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pcr_spi2_conf_reg, FieldId::field_pcr_spi2_conf_reg_spi2_clk_en, PinId::none, ClockGateId::gate_spi2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_espressif_iomatrix_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO6, ClockGateId::none, ResetId::none, 63},
  }};
};

template<>
struct RouteTraits<PinId::GPIO7, PeripheralId::SPI2, SignalId::signal_mosi> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio7_spi2_mosi;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_espressif_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pcr_spi2_conf_reg, FieldId::field_pcr_spi2_conf_reg_spi2_clk_en, PinId::none, ClockGateId::gate_spi2, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_espressif_iomatrix_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO7, ClockGateId::none, ResetId::none, 64},
  }};
};

template<>
struct RouteTraits<PinId::GPIO8, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio8_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_espressif_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pcr_i2c0_conf_reg, FieldId::field_pcr_i2c0_conf_reg_i2c0_clk_en, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_espressif_iomatrix_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO8, ClockGateId::none, ResetId::none, 15},
  }};
};

template<>
struct RouteTraits<PinId::GPIO9, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gpio9_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_espressif_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_pcr_i2c0_conf_reg, FieldId::field_pcr_i2c0_conf_reg_i2c0_clk_en, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_pinmux_espressif_iomatrix_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GPIO9, ClockGateId::none, ResetId::none, 14},
  }};
};

inline constexpr std::array<RouteDescriptor, 10> kRuntimeRoutes = {{
  {RouteId::candidate_gpio10_spi2_cs, PinId::GPIO10, PeripheralId::SPI2, SignalId::signal_cs, RouteKindId::route_kind_mux},
  {RouteId::candidate_gpio20_uart0_rx, PinId::GPIO20, PeripheralId::UART0, SignalId::signal_rx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gpio21_uart0_tx, PinId::GPIO21, PeripheralId::UART0, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gpio2_spi2_miso, PinId::GPIO2, PeripheralId::SPI2, SignalId::signal_miso, RouteKindId::route_kind_mux},
  {RouteId::candidate_gpio4_uart1_tx, PinId::GPIO4, PeripheralId::UART1, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gpio5_uart1_rx, PinId::GPIO5, PeripheralId::UART1, SignalId::signal_rx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gpio6_spi2_sck, PinId::GPIO6, PeripheralId::SPI2, SignalId::signal_sck, RouteKindId::route_kind_mux},
  {RouteId::candidate_gpio7_spi2_mosi, PinId::GPIO7, PeripheralId::SPI2, SignalId::signal_mosi, RouteKindId::route_kind_mux},
  {RouteId::candidate_gpio8_i2c0_sda, PinId::GPIO8, PeripheralId::I2C0, SignalId::signal_sda, RouteKindId::route_kind_mux},
  {RouteId::candidate_gpio9_i2c0_scl, PinId::GPIO9, PeripheralId::I2C0, SignalId::signal_scl, RouteKindId::route_kind_mux},
}};

template<PinId Pin, PeripheralId Peripheral, SignalId Signal>
inline auto apply_route() noexcept -> void {
  static_assert(RouteTraits<Pin, Peripheral, Signal>::kPresent, "");
}

template<>
inline auto apply_route<PinId::GPIO10, PeripheralId::SPI2, SignalId::signal_cs>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x600A0014u) |=(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x6000902Cu) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x6000902Cu) & ~(std::uint32_t{0x7} << 12)) | (std::uint32_t{0x1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x6000457Cu) = std::uint32_t{0x44u};
}

template<>
inline auto apply_route<PinId::GPIO20, PeripheralId::UART0, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x600A0000u) |=(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x60009054u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x60009054u) & ~(std::uint32_t{0x7} << 12)) | (std::uint32_t{0x1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x600045A4u) = std::uint32_t{0x6u};
}

template<>
inline auto apply_route<PinId::GPIO21, PeripheralId::UART0, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x600A0000u) |=(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x60009058u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x60009058u) & ~(std::uint32_t{0x7} << 12)) | (std::uint32_t{0x1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x600045A8u) = std::uint32_t{0x6u};
}

template<>
inline auto apply_route<PinId::GPIO2, PeripheralId::SPI2, SignalId::signal_miso>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x600A0014u) |=(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x6000900Cu) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x6000900Cu) & ~(std::uint32_t{0x7} << 12)) | (std::uint32_t{0x1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x6000455Cu) = std::uint32_t{0x3Fu};
}

template<>
inline auto apply_route<PinId::GPIO4, PeripheralId::UART1, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x600A0008u) |=(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x60009014u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x60009014u) & ~(std::uint32_t{0x7} << 12)) | (std::uint32_t{0x1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x60004564u) = std::uint32_t{0x9u};
}

template<>
inline auto apply_route<PinId::GPIO5, PeripheralId::UART1, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x600A0008u) |=(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x60009018u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x60009018u) & ~(std::uint32_t{0x7} << 12)) | (std::uint32_t{0x1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x60004568u) = std::uint32_t{0x9u};
}

template<>
inline auto apply_route<PinId::GPIO6, PeripheralId::SPI2, SignalId::signal_sck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x600A0014u) |=(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x6000901Cu) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x6000901Cu) & ~(std::uint32_t{0x7} << 12)) | (std::uint32_t{0x1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x6000456Cu) = std::uint32_t{0x3Fu};
}

template<>
inline auto apply_route<PinId::GPIO7, PeripheralId::SPI2, SignalId::signal_mosi>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x600A0014u) |=(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x60009020u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x60009020u) & ~(std::uint32_t{0x7} << 12)) | (std::uint32_t{0x1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x60004570u) = std::uint32_t{0x40u};
}

template<>
inline auto apply_route<PinId::GPIO8, PeripheralId::I2C0, SignalId::signal_sda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x600A001Cu) |=(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x60009024u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x60009024u) & ~(std::uint32_t{0x7} << 12)) | (std::uint32_t{0x1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x60004574u) = std::uint32_t{0xFu};
}

template<>
inline auto apply_route<PinId::GPIO9, PeripheralId::I2C0, SignalId::signal_scl>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x600A001Cu) |=(std::uint32_t{1} << 1);
  *reinterpret_cast<volatile std::uint32_t*>(0x60009028u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x60009028u) & ~(std::uint32_t{0x7} << 12)) | (std::uint32_t{0x1} << 12);
  *reinterpret_cast<volatile std::uint32_t*>(0x60004578u) = std::uint32_t{0xEu};
}

enum class ConnectionGroupId : std::uint16_t {
  none,
  group_i2c0_qfn32_scl_sda,
  group_spi2_qfn32_sck_mosi_miso,
  group_uart0_qfn32_tx_rx,
  group_uart1_qfn32_tx_rx,
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
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_i2c0_qfn32_scl_sda;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_gpio8_i2c0_sda,
    RouteId::candidate_gpio9_i2c0_scl,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::SPI2, SignalId::signal_sck, SignalId::signal_mosi, SignalId::signal_miso> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_spi2_qfn32_sck_mosi_miso;
  static constexpr std::array<RouteId, 3> kRoutes = {{
    RouteId::candidate_gpio2_spi2_miso,
    RouteId::candidate_gpio6_spi2_sck,
    RouteId::candidate_gpio7_spi2_mosi,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::UART0, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_uart0_qfn32_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_gpio20_uart0_rx,
    RouteId::candidate_gpio21_uart0_tx,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::UART1, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_uart1_qfn32_tx_rx;
  static constexpr std::array<RouteId, 2> kRoutes = {{
    RouteId::candidate_gpio4_uart1_tx,
    RouteId::candidate_gpio5_uart1_rx,
  }};
};

struct ConnectionGroupDescriptor {
  ConnectionGroupId group_id;
  PeripheralId peripheral_id;
  std::uint16_t route_count;
};
inline constexpr std::array<ConnectionGroupDescriptor, 4> kRuntimeConnectionGroups = {{
  {ConnectionGroupId::group_i2c0_qfn32_scl_sda, PeripheralId::I2C0, 2u},
  {ConnectionGroupId::group_spi2_qfn32_sck_mosi_miso, PeripheralId::SPI2, 3u},
  {ConnectionGroupId::group_uart0_qfn32_tx_rx, PeripheralId::UART0, 2u},
  {ConnectionGroupId::group_uart1_qfn32_tx_rx, PeripheralId::UART1, 2u},
}};

}
}
}
}
}
}
