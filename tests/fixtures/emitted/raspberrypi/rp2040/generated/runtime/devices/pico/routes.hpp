#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "clock_bindings.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"
#include "register_fields.hpp"
#include "registers.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace pico {
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
  candidate_gp0_i2c0_sda,
  candidate_gp0_spi0_rx,
  candidate_gp0_uart0_tx,
  candidate_gp10_i2c1_sda,
  candidate_gp10_spi1_sck,
  candidate_gp10_uart1_cts,
  candidate_gp11_i2c1_scl,
  candidate_gp11_spi1_tx,
  candidate_gp11_uart1_rts,
  candidate_gp12_i2c0_sda,
  candidate_gp12_spi1_rx,
  candidate_gp12_uart0_tx,
  candidate_gp13_i2c0_scl,
  candidate_gp13_spi1_csn,
  candidate_gp13_uart0_rx,
  candidate_gp14_i2c1_sda,
  candidate_gp14_spi1_sck,
  candidate_gp14_uart0_cts,
  candidate_gp15_i2c1_scl,
  candidate_gp15_spi1_tx,
  candidate_gp15_uart0_rts,
  candidate_gp16_i2c0_sda,
  candidate_gp16_spi0_rx,
  candidate_gp16_uart0_tx,
  candidate_gp17_i2c0_scl,
  candidate_gp17_spi0_csn,
  candidate_gp17_uart0_rx,
  candidate_gp18_i2c1_sda,
  candidate_gp18_spi0_sck,
  candidate_gp18_uart0_cts,
  candidate_gp19_i2c1_scl,
  candidate_gp19_spi0_tx,
  candidate_gp19_uart0_rts,
  candidate_gp1_i2c0_scl,
  candidate_gp1_spi0_csn,
  candidate_gp1_uart0_rx,
  candidate_gp20_i2c0_sda,
  candidate_gp20_spi0_rx,
  candidate_gp20_uart1_tx,
  candidate_gp21_i2c0_scl,
  candidate_gp21_spi0_csn,
  candidate_gp21_uart1_rx,
  candidate_gp22_i2c1_sda,
  candidate_gp22_spi0_sck,
  candidate_gp22_uart1_cts,
  candidate_gp25_i2c0_scl,
  candidate_gp25_spi1_csn,
  candidate_gp25_uart1_tx,
  candidate_gp26_adc_ch0,
  candidate_gp27_adc_ch1,
  candidate_gp28_adc_ch2,
  candidate_gp2_i2c1_sda,
  candidate_gp2_spi0_sck,
  candidate_gp2_uart0_cts,
  candidate_gp3_i2c1_scl,
  candidate_gp3_spi0_tx,
  candidate_gp3_uart0_rts,
  candidate_gp4_i2c0_sda,
  candidate_gp4_spi0_rx,
  candidate_gp4_uart1_tx,
  candidate_gp5_i2c0_scl,
  candidate_gp5_spi0_csn,
  candidate_gp5_uart1_rx,
  candidate_gp6_i2c1_sda,
  candidate_gp6_spi0_sck,
  candidate_gp6_uart1_cts,
  candidate_gp7_i2c1_scl,
  candidate_gp7_spi0_tx,
  candidate_gp7_uart1_rts,
  candidate_gp8_i2c0_sda,
  candidate_gp8_spi1_rx,
  candidate_gp8_uart1_tx,
  candidate_gp9_i2c0_scl,
  candidate_gp9_spi1_csn,
  candidate_gp9_uart1_rx,
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
struct RouteTraits<PinId::GP0, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp0_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::none, ResetId::reset_i2c0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP0, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP0, PeripheralId::SPI0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp0_spi0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP0, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP0, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp0_uart0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::none, ResetId::reset_uart0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP0, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP10, PeripheralId::I2C1, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp10_i2c1_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::gate_i2c1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::none, ResetId::reset_i2c1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP10, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP10, PeripheralId::SPI1, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp10_spi1_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::gate_spi1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::none, ResetId::reset_spi1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP10, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP10, PeripheralId::UART1, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp10_uart1_cts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::none, ResetId::reset_uart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP10, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP11, PeripheralId::I2C1, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp11_i2c1_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::gate_i2c1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::none, ResetId::reset_i2c1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP11, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP11, PeripheralId::SPI1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp11_spi1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::gate_spi1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::none, ResetId::reset_spi1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP11, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP11, PeripheralId::UART1, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp11_uart1_rts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::none, ResetId::reset_uart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP11, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP12, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp12_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::none, ResetId::reset_i2c0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP12, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP12, PeripheralId::SPI1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp12_spi1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::gate_spi1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::none, ResetId::reset_spi1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP12, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP12, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp12_uart0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::none, ResetId::reset_uart0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP12, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP13, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp13_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::none, ResetId::reset_i2c0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP13, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP13, PeripheralId::SPI1, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp13_spi1_csn;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::gate_spi1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::none, ResetId::reset_spi1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP13, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP13, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp13_uart0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::none, ResetId::reset_uart0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP13, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP14, PeripheralId::I2C1, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp14_i2c1_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::gate_i2c1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::none, ResetId::reset_i2c1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP14, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP14, PeripheralId::SPI1, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp14_spi1_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::gate_spi1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::none, ResetId::reset_spi1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP14, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP14, PeripheralId::UART0, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp14_uart0_cts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::none, ResetId::reset_uart0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP14, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP15, PeripheralId::I2C1, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp15_i2c1_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::gate_i2c1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::none, ResetId::reset_i2c1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP15, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP15, PeripheralId::SPI1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp15_spi1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::gate_spi1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::none, ResetId::reset_spi1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP15, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP15, PeripheralId::UART0, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp15_uart0_rts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::none, ResetId::reset_uart0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP15, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP16, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp16_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::none, ResetId::reset_i2c0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP16, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP16, PeripheralId::SPI0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp16_spi0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP16, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP16, PeripheralId::UART0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp16_uart0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::none, ResetId::reset_uart0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP16, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP17, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp17_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::none, ResetId::reset_i2c0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP17, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP17, PeripheralId::SPI0, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp17_spi0_csn;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP17, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP17, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp17_uart0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::none, ResetId::reset_uart0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP17, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP18, PeripheralId::I2C1, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp18_i2c1_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::gate_i2c1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::none, ResetId::reset_i2c1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP18, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP18, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp18_spi0_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP18, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP18, PeripheralId::UART0, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp18_uart0_cts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::none, ResetId::reset_uart0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP18, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP19, PeripheralId::I2C1, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp19_i2c1_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::gate_i2c1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::none, ResetId::reset_i2c1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP19, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP19, PeripheralId::SPI0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp19_spi0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP19, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP19, PeripheralId::UART0, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp19_uart0_rts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::none, ResetId::reset_uart0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP19, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP1, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp1_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::none, ResetId::reset_i2c0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP1, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP1, PeripheralId::SPI0, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp1_spi0_csn;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP1, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP1, PeripheralId::UART0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp1_uart0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::none, ResetId::reset_uart0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP1, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP20, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp20_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::none, ResetId::reset_i2c0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP20, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP20, PeripheralId::SPI0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp20_spi0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP20, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP20, PeripheralId::UART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp20_uart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::none, ResetId::reset_uart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP20, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP21, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp21_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::none, ResetId::reset_i2c0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP21, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP21, PeripheralId::SPI0, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp21_spi0_csn;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP21, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP21, PeripheralId::UART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp21_uart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::none, ResetId::reset_uart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP21, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP22, PeripheralId::I2C1, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp22_i2c1_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::gate_i2c1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::none, ResetId::reset_i2c1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP22, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP22, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp22_spi0_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP22, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP22, PeripheralId::UART1, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp22_uart1_cts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::none, ResetId::reset_uart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP22, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP25, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp25_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::none, ResetId::reset_i2c0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP25, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP25, PeripheralId::SPI1, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp25_spi1_csn;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::gate_spi1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::none, ResetId::reset_spi1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP25, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP25, PeripheralId::UART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp25_uart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::none, ResetId::reset_uart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP25, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP26, PeripheralId::ADC, SignalId::signal_ch0> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp26_adc_ch0;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_adc, PinId::none, ClockGateId::gate_adc, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_adc, PinId::none, ClockGateId::none, ResetId::reset_adc, 0},
  }};
};

template<>
struct RouteTraits<PinId::GP27, PeripheralId::ADC, SignalId::signal_ch1> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp27_adc_ch1;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_adc, PinId::none, ClockGateId::gate_adc, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_adc, PinId::none, ClockGateId::none, ResetId::reset_adc, 0},
  }};
};

template<>
struct RouteTraits<PinId::GP28, PeripheralId::ADC, SignalId::signal_ch2> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp28_adc_ch2;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 2> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_adc, PinId::none, ClockGateId::gate_adc, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_adc, PinId::none, ClockGateId::none, ResetId::reset_adc, 0},
  }};
};

template<>
struct RouteTraits<PinId::GP2, PeripheralId::I2C1, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp2_i2c1_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::gate_i2c1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::none, ResetId::reset_i2c1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP2, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP2, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp2_spi0_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP2, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP2, PeripheralId::UART0, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp2_uart0_cts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::none, ResetId::reset_uart0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP2, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP3, PeripheralId::I2C1, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp3_i2c1_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::gate_i2c1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::none, ResetId::reset_i2c1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP3, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP3, PeripheralId::SPI0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp3_spi0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP3, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP3, PeripheralId::UART0, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp3_uart0_rts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::gate_uart0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0, PinId::none, ClockGateId::none, ResetId::reset_uart0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP3, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP4, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp4_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::none, ResetId::reset_i2c0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP4, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP4, PeripheralId::SPI0, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp4_spi0_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP4, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP4, PeripheralId::UART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp4_uart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::none, ResetId::reset_uart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP4, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP5, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp5_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::none, ResetId::reset_i2c0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP5, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP5, PeripheralId::SPI0, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp5_spi0_csn;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP5, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP5, PeripheralId::UART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp5_uart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::none, ResetId::reset_uart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP5, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP6, PeripheralId::I2C1, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp6_i2c1_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::gate_i2c1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::none, ResetId::reset_i2c1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP6, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP6, PeripheralId::SPI0, SignalId::signal_sck> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp6_spi0_sck;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP6, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP6, PeripheralId::UART1, SignalId::signal_cts> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp6_uart1_cts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::none, ResetId::reset_uart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP6, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP7, PeripheralId::I2C1, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp7_i2c1_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::gate_i2c1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1, PinId::none, ClockGateId::none, ResetId::reset_i2c1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP7, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP7, PeripheralId::SPI0, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp7_spi0_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::gate_spi0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0, PinId::none, ClockGateId::none, ResetId::reset_spi0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP7, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP7, PeripheralId::UART1, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp7_uart1_rts;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::none, ResetId::reset_uart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP7, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP8, PeripheralId::I2C0, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp8_i2c0_sda;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::none, ResetId::reset_i2c0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP8, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP8, PeripheralId::SPI1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp8_spi1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::gate_spi1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::none, ResetId::reset_spi1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP8, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP8, PeripheralId::UART1, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp8_uart1_tx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::none, ResetId::reset_uart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP8, ClockGateId::none, ResetId::none, 2},
  }};
};

template<>
struct RouteTraits<PinId::GP9, PeripheralId::I2C0, SignalId::signal_scl> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp9_i2c0_scl;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::gate_i2c0, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0, PinId::none, ClockGateId::none, ResetId::reset_i2c0, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP9, ClockGateId::none, ResetId::none, 3},
  }};
};

template<>
struct RouteTraits<PinId::GP9, PeripheralId::SPI1, SignalId::signal_csn> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp9_spi1_csn;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::gate_spi1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1, PinId::none, ClockGateId::none, ResetId::reset_spi1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP9, ClockGateId::none, ResetId::none, 1},
  }};
};

template<>
struct RouteTraits<PinId::GP9, PeripheralId::UART1, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr RouteId kRouteId = RouteId::candidate_gp9_uart1_rx;
  static constexpr RouteKindId kRouteKindId = RouteKindId::route_kind_mux;
  static constexpr std::array<RouteOperation, 3> kOperations = {{
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_set_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::gate_uart1, ResetId::none, 1},
    {BackendSchemaId::schema_alloy_clock_raspberrypi_generic_clock_v1, OperationKindId::operation_kind_clear_bit, OperationSubjectKindId::operation_subject_peripheral, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1, PinId::none, ClockGateId::none, ResetId::reset_uart1, 0},
    {BackendSchemaId::schema_alloy_pinmux_rp2040_funcsel_v1, OperationKindId::operation_kind_write_selector, OperationSubjectKindId::operation_subject_pin, RegisterId::none, FieldId::none, PinId::GP9, ClockGateId::none, ResetId::none, 2},
  }};
};

inline constexpr std::array<RouteDescriptor, 75> kRuntimeRoutes = {{
  {RouteId::candidate_gp0_i2c0_sda, PinId::GP0, PeripheralId::I2C0, SignalId::signal_sda, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp0_spi0_rx, PinId::GP0, PeripheralId::SPI0, SignalId::signal_rx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp0_uart0_tx, PinId::GP0, PeripheralId::UART0, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp10_i2c1_sda, PinId::GP10, PeripheralId::I2C1, SignalId::signal_sda, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp10_spi1_sck, PinId::GP10, PeripheralId::SPI1, SignalId::signal_sck, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp10_uart1_cts, PinId::GP10, PeripheralId::UART1, SignalId::signal_cts, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp11_i2c1_scl, PinId::GP11, PeripheralId::I2C1, SignalId::signal_scl, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp11_spi1_tx, PinId::GP11, PeripheralId::SPI1, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp11_uart1_rts, PinId::GP11, PeripheralId::UART1, SignalId::signal_rts, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp12_i2c0_sda, PinId::GP12, PeripheralId::I2C0, SignalId::signal_sda, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp12_spi1_rx, PinId::GP12, PeripheralId::SPI1, SignalId::signal_rx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp12_uart0_tx, PinId::GP12, PeripheralId::UART0, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp13_i2c0_scl, PinId::GP13, PeripheralId::I2C0, SignalId::signal_scl, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp13_spi1_csn, PinId::GP13, PeripheralId::SPI1, SignalId::signal_csn, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp13_uart0_rx, PinId::GP13, PeripheralId::UART0, SignalId::signal_rx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp14_i2c1_sda, PinId::GP14, PeripheralId::I2C1, SignalId::signal_sda, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp14_spi1_sck, PinId::GP14, PeripheralId::SPI1, SignalId::signal_sck, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp14_uart0_cts, PinId::GP14, PeripheralId::UART0, SignalId::signal_cts, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp15_i2c1_scl, PinId::GP15, PeripheralId::I2C1, SignalId::signal_scl, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp15_spi1_tx, PinId::GP15, PeripheralId::SPI1, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp15_uart0_rts, PinId::GP15, PeripheralId::UART0, SignalId::signal_rts, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp16_i2c0_sda, PinId::GP16, PeripheralId::I2C0, SignalId::signal_sda, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp16_spi0_rx, PinId::GP16, PeripheralId::SPI0, SignalId::signal_rx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp16_uart0_tx, PinId::GP16, PeripheralId::UART0, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp17_i2c0_scl, PinId::GP17, PeripheralId::I2C0, SignalId::signal_scl, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp17_spi0_csn, PinId::GP17, PeripheralId::SPI0, SignalId::signal_csn, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp17_uart0_rx, PinId::GP17, PeripheralId::UART0, SignalId::signal_rx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp18_i2c1_sda, PinId::GP18, PeripheralId::I2C1, SignalId::signal_sda, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp18_spi0_sck, PinId::GP18, PeripheralId::SPI0, SignalId::signal_sck, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp18_uart0_cts, PinId::GP18, PeripheralId::UART0, SignalId::signal_cts, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp19_i2c1_scl, PinId::GP19, PeripheralId::I2C1, SignalId::signal_scl, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp19_spi0_tx, PinId::GP19, PeripheralId::SPI0, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp19_uart0_rts, PinId::GP19, PeripheralId::UART0, SignalId::signal_rts, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp1_i2c0_scl, PinId::GP1, PeripheralId::I2C0, SignalId::signal_scl, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp1_spi0_csn, PinId::GP1, PeripheralId::SPI0, SignalId::signal_csn, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp1_uart0_rx, PinId::GP1, PeripheralId::UART0, SignalId::signal_rx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp20_i2c0_sda, PinId::GP20, PeripheralId::I2C0, SignalId::signal_sda, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp20_spi0_rx, PinId::GP20, PeripheralId::SPI0, SignalId::signal_rx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp20_uart1_tx, PinId::GP20, PeripheralId::UART1, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp21_i2c0_scl, PinId::GP21, PeripheralId::I2C0, SignalId::signal_scl, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp21_spi0_csn, PinId::GP21, PeripheralId::SPI0, SignalId::signal_csn, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp21_uart1_rx, PinId::GP21, PeripheralId::UART1, SignalId::signal_rx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp22_i2c1_sda, PinId::GP22, PeripheralId::I2C1, SignalId::signal_sda, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp22_spi0_sck, PinId::GP22, PeripheralId::SPI0, SignalId::signal_sck, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp22_uart1_cts, PinId::GP22, PeripheralId::UART1, SignalId::signal_cts, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp25_i2c0_scl, PinId::GP25, PeripheralId::I2C0, SignalId::signal_scl, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp25_spi1_csn, PinId::GP25, PeripheralId::SPI1, SignalId::signal_csn, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp25_uart1_tx, PinId::GP25, PeripheralId::UART1, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp26_adc_ch0, PinId::GP26, PeripheralId::ADC, SignalId::signal_ch0, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp27_adc_ch1, PinId::GP27, PeripheralId::ADC, SignalId::signal_ch1, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp28_adc_ch2, PinId::GP28, PeripheralId::ADC, SignalId::signal_ch2, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp2_i2c1_sda, PinId::GP2, PeripheralId::I2C1, SignalId::signal_sda, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp2_spi0_sck, PinId::GP2, PeripheralId::SPI0, SignalId::signal_sck, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp2_uart0_cts, PinId::GP2, PeripheralId::UART0, SignalId::signal_cts, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp3_i2c1_scl, PinId::GP3, PeripheralId::I2C1, SignalId::signal_scl, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp3_spi0_tx, PinId::GP3, PeripheralId::SPI0, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp3_uart0_rts, PinId::GP3, PeripheralId::UART0, SignalId::signal_rts, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp4_i2c0_sda, PinId::GP4, PeripheralId::I2C0, SignalId::signal_sda, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp4_spi0_rx, PinId::GP4, PeripheralId::SPI0, SignalId::signal_rx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp4_uart1_tx, PinId::GP4, PeripheralId::UART1, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp5_i2c0_scl, PinId::GP5, PeripheralId::I2C0, SignalId::signal_scl, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp5_spi0_csn, PinId::GP5, PeripheralId::SPI0, SignalId::signal_csn, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp5_uart1_rx, PinId::GP5, PeripheralId::UART1, SignalId::signal_rx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp6_i2c1_sda, PinId::GP6, PeripheralId::I2C1, SignalId::signal_sda, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp6_spi0_sck, PinId::GP6, PeripheralId::SPI0, SignalId::signal_sck, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp6_uart1_cts, PinId::GP6, PeripheralId::UART1, SignalId::signal_cts, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp7_i2c1_scl, PinId::GP7, PeripheralId::I2C1, SignalId::signal_scl, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp7_spi0_tx, PinId::GP7, PeripheralId::SPI0, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp7_uart1_rts, PinId::GP7, PeripheralId::UART1, SignalId::signal_rts, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp8_i2c0_sda, PinId::GP8, PeripheralId::I2C0, SignalId::signal_sda, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp8_spi1_rx, PinId::GP8, PeripheralId::SPI1, SignalId::signal_rx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp8_uart1_tx, PinId::GP8, PeripheralId::UART1, SignalId::signal_tx, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp9_i2c0_scl, PinId::GP9, PeripheralId::I2C0, SignalId::signal_scl, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp9_spi1_csn, PinId::GP9, PeripheralId::SPI1, SignalId::signal_csn, RouteKindId::route_kind_mux},
  {RouteId::candidate_gp9_uart1_rx, PinId::GP9, PeripheralId::UART1, SignalId::signal_rx, RouteKindId::route_kind_mux},
}};

template<PinId Pin, PeripheralId Peripheral, SignalId Signal>
inline auto apply_route() noexcept -> void {
  static_assert(RouteTraits<Pin, Peripheral, Signal>::kPresent, "");
}

template<>
inline auto apply_route<PinId::GP0, PeripheralId::I2C0, SignalId::signal_sda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x40014004u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x40014004u) & ~std::uint32_t{0x1F}) | std::uint32_t{0x3u};
}

template<>
inline auto apply_route<PinId::GP0, PeripheralId::SPI0, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x40014004u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x40014004u) & ~std::uint32_t{0x1F}) | std::uint32_t{0x1u};
}

template<>
inline auto apply_route<PinId::GP0, PeripheralId::UART0, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x40014004u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x40014004u) & ~std::uint32_t{0x1F}) | std::uint32_t{0x2u};
}

template<>
inline auto apply_route<PinId::GP10, PeripheralId::I2C1, SignalId::signal_sda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::GP10, PeripheralId::SPI1, SignalId::signal_sck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 17);
}

template<>
inline auto apply_route<PinId::GP10, PeripheralId::UART1, SignalId::signal_cts>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 23);
}

template<>
inline auto apply_route<PinId::GP11, PeripheralId::I2C1, SignalId::signal_scl>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::GP11, PeripheralId::SPI1, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 17);
}

template<>
inline auto apply_route<PinId::GP11, PeripheralId::UART1, SignalId::signal_rts>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 23);
}

template<>
inline auto apply_route<PinId::GP12, PeripheralId::I2C0, SignalId::signal_sda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::GP12, PeripheralId::SPI1, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 17);
}

template<>
inline auto apply_route<PinId::GP12, PeripheralId::UART0, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 22);
}

template<>
inline auto apply_route<PinId::GP13, PeripheralId::I2C0, SignalId::signal_scl>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::GP13, PeripheralId::SPI1, SignalId::signal_csn>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 17);
}

template<>
inline auto apply_route<PinId::GP13, PeripheralId::UART0, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 22);
}

template<>
inline auto apply_route<PinId::GP14, PeripheralId::I2C1, SignalId::signal_sda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::GP14, PeripheralId::SPI1, SignalId::signal_sck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 17);
}

template<>
inline auto apply_route<PinId::GP14, PeripheralId::UART0, SignalId::signal_cts>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 22);
}

template<>
inline auto apply_route<PinId::GP15, PeripheralId::I2C1, SignalId::signal_scl>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::GP15, PeripheralId::SPI1, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 17);
}

template<>
inline auto apply_route<PinId::GP15, PeripheralId::UART0, SignalId::signal_rts>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 22);
}

template<>
inline auto apply_route<PinId::GP16, PeripheralId::I2C0, SignalId::signal_sda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::GP16, PeripheralId::SPI0, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::GP16, PeripheralId::UART0, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 22);
}

template<>
inline auto apply_route<PinId::GP17, PeripheralId::I2C0, SignalId::signal_scl>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::GP17, PeripheralId::SPI0, SignalId::signal_csn>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::GP17, PeripheralId::UART0, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 22);
}

template<>
inline auto apply_route<PinId::GP18, PeripheralId::I2C1, SignalId::signal_sda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::GP18, PeripheralId::SPI0, SignalId::signal_sck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::GP18, PeripheralId::UART0, SignalId::signal_cts>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 22);
}

template<>
inline auto apply_route<PinId::GP19, PeripheralId::I2C1, SignalId::signal_scl>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::GP19, PeripheralId::SPI0, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::GP19, PeripheralId::UART0, SignalId::signal_rts>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 22);
}

template<>
inline auto apply_route<PinId::GP1, PeripheralId::I2C0, SignalId::signal_scl>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x4001400Cu) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x4001400Cu) & ~std::uint32_t{0x1F}) | std::uint32_t{0x3u};
}

template<>
inline auto apply_route<PinId::GP1, PeripheralId::SPI0, SignalId::signal_csn>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4001400Cu) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x4001400Cu) & ~std::uint32_t{0x1F}) | std::uint32_t{0x1u};
}

template<>
inline auto apply_route<PinId::GP1, PeripheralId::UART0, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x4001400Cu) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x4001400Cu) & ~std::uint32_t{0x1F}) | std::uint32_t{0x2u};
}

template<>
inline auto apply_route<PinId::GP20, PeripheralId::I2C0, SignalId::signal_sda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::GP20, PeripheralId::SPI0, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::GP20, PeripheralId::UART1, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 23);
}

template<>
inline auto apply_route<PinId::GP21, PeripheralId::I2C0, SignalId::signal_scl>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::GP21, PeripheralId::SPI0, SignalId::signal_csn>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::GP21, PeripheralId::UART1, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 23);
}

template<>
inline auto apply_route<PinId::GP22, PeripheralId::I2C1, SignalId::signal_sda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::GP22, PeripheralId::SPI0, SignalId::signal_sck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::GP22, PeripheralId::UART1, SignalId::signal_cts>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 23);
}

template<>
inline auto apply_route<PinId::GP25, PeripheralId::I2C0, SignalId::signal_scl>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::GP25, PeripheralId::SPI1, SignalId::signal_csn>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 17);
}

template<>
inline auto apply_route<PinId::GP25, PeripheralId::UART1, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 23);
}

template<>
inline auto apply_route<PinId::GP26, PeripheralId::ADC, SignalId::signal_ch0>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 0);
}

template<>
inline auto apply_route<PinId::GP27, PeripheralId::ADC, SignalId::signal_ch1>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 0);
}

template<>
inline auto apply_route<PinId::GP28, PeripheralId::ADC, SignalId::signal_ch2>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 0);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 0);
}

template<>
inline auto apply_route<PinId::GP2, PeripheralId::I2C1, SignalId::signal_sda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x40014014u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x40014014u) & ~std::uint32_t{0x1F}) | std::uint32_t{0x3u};
}

template<>
inline auto apply_route<PinId::GP2, PeripheralId::SPI0, SignalId::signal_sck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x40014014u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x40014014u) & ~std::uint32_t{0x1F}) | std::uint32_t{0x1u};
}

template<>
inline auto apply_route<PinId::GP2, PeripheralId::UART0, SignalId::signal_cts>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x40014014u) = 
      (*reinterpret_cast<volatile std::uint32_t*>(0x40014014u) & ~std::uint32_t{0x1F}) | std::uint32_t{0x2u};
}

template<>
inline auto apply_route<PinId::GP3, PeripheralId::I2C1, SignalId::signal_scl>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::GP3, PeripheralId::SPI0, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::GP3, PeripheralId::UART0, SignalId::signal_rts>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 22);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 22);
}

template<>
inline auto apply_route<PinId::GP4, PeripheralId::I2C0, SignalId::signal_sda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::GP4, PeripheralId::SPI0, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::GP4, PeripheralId::UART1, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 23);
}

template<>
inline auto apply_route<PinId::GP5, PeripheralId::I2C0, SignalId::signal_scl>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::GP5, PeripheralId::SPI0, SignalId::signal_csn>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::GP5, PeripheralId::UART1, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 23);
}

template<>
inline auto apply_route<PinId::GP6, PeripheralId::I2C1, SignalId::signal_sda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::GP6, PeripheralId::SPI0, SignalId::signal_sck>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::GP6, PeripheralId::UART1, SignalId::signal_cts>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 23);
}

template<>
inline auto apply_route<PinId::GP7, PeripheralId::I2C1, SignalId::signal_scl>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 4);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 4);
}

template<>
inline auto apply_route<PinId::GP7, PeripheralId::SPI0, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 16);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 16);
}

template<>
inline auto apply_route<PinId::GP7, PeripheralId::UART1, SignalId::signal_rts>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 23);
}

template<>
inline auto apply_route<PinId::GP8, PeripheralId::I2C0, SignalId::signal_sda>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::GP8, PeripheralId::SPI1, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 17);
}

template<>
inline auto apply_route<PinId::GP8, PeripheralId::UART1, SignalId::signal_tx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 23);
}

template<>
inline auto apply_route<PinId::GP9, PeripheralId::I2C0, SignalId::signal_scl>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 3);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 3);
}

template<>
inline auto apply_route<PinId::GP9, PeripheralId::SPI1, SignalId::signal_csn>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 17);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 17);
}

template<>
inline auto apply_route<PinId::GP9, PeripheralId::UART1, SignalId::signal_rx>() noexcept -> void {
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) |=(std::uint32_t{1} << 23);
  *reinterpret_cast<volatile std::uint32_t*>(0x4000C000u) &= ~(std::uint32_t{1} << 23);
}

enum class ConnectionGroupId : std::uint16_t {
  none,
  group_adc_pico_all_signals,
  group_i2c0_pico_scl_sda,
  group_i2c1_pico_scl_sda,
  group_spi0_pico_all_signals,
  group_spi1_pico_all_signals,
  group_uart0_pico_tx_rx,
  group_uart0_pico_tx_rx_cts_rts,
  group_uart1_pico_tx_rx,
  group_uart1_pico_tx_rx_cts_rts,
};

template<PeripheralId Peripheral, SignalId... Signals>
struct ConnectionGroupTraits {
  static constexpr bool kPresent = false;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::none;
  static constexpr std::array<RouteId, 0> kRoutes = {};
};

template<>
struct ConnectionGroupTraits<PeripheralId::ADC, SignalId::signal_ch0, SignalId::signal_ch1, SignalId::signal_ch2> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_adc_pico_all_signals;
  static constexpr std::array<RouteId, 3> kRoutes = {{
    RouteId::candidate_gp26_adc_ch0,
    RouteId::candidate_gp27_adc_ch1,
    RouteId::candidate_gp28_adc_ch2,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::I2C0, SignalId::signal_scl, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_i2c0_pico_scl_sda;
  static constexpr std::array<RouteId, 13> kRoutes = {{
    RouteId::candidate_gp0_i2c0_sda,
    RouteId::candidate_gp12_i2c0_sda,
    RouteId::candidate_gp13_i2c0_scl,
    RouteId::candidate_gp16_i2c0_sda,
    RouteId::candidate_gp17_i2c0_scl,
    RouteId::candidate_gp1_i2c0_scl,
    RouteId::candidate_gp20_i2c0_sda,
    RouteId::candidate_gp21_i2c0_scl,
    RouteId::candidate_gp25_i2c0_scl,
    RouteId::candidate_gp4_i2c0_sda,
    RouteId::candidate_gp5_i2c0_scl,
    RouteId::candidate_gp8_i2c0_sda,
    RouteId::candidate_gp9_i2c0_scl,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::I2C1, SignalId::signal_scl, SignalId::signal_sda> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_i2c1_pico_scl_sda;
  static constexpr std::array<RouteId, 11> kRoutes = {{
    RouteId::candidate_gp10_i2c1_sda,
    RouteId::candidate_gp11_i2c1_scl,
    RouteId::candidate_gp14_i2c1_sda,
    RouteId::candidate_gp15_i2c1_scl,
    RouteId::candidate_gp18_i2c1_sda,
    RouteId::candidate_gp19_i2c1_scl,
    RouteId::candidate_gp22_i2c1_sda,
    RouteId::candidate_gp2_i2c1_sda,
    RouteId::candidate_gp3_i2c1_scl,
    RouteId::candidate_gp6_i2c1_sda,
    RouteId::candidate_gp7_i2c1_scl,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::SPI0, SignalId::signal_csn, SignalId::signal_rx, SignalId::signal_sck, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_spi0_pico_all_signals;
  static constexpr std::array<RouteId, 15> kRoutes = {{
    RouteId::candidate_gp0_spi0_rx,
    RouteId::candidate_gp16_spi0_rx,
    RouteId::candidate_gp17_spi0_csn,
    RouteId::candidate_gp18_spi0_sck,
    RouteId::candidate_gp19_spi0_tx,
    RouteId::candidate_gp1_spi0_csn,
    RouteId::candidate_gp20_spi0_rx,
    RouteId::candidate_gp21_spi0_csn,
    RouteId::candidate_gp22_spi0_sck,
    RouteId::candidate_gp2_spi0_sck,
    RouteId::candidate_gp3_spi0_tx,
    RouteId::candidate_gp4_spi0_rx,
    RouteId::candidate_gp5_spi0_csn,
    RouteId::candidate_gp6_spi0_sck,
    RouteId::candidate_gp7_spi0_tx,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::SPI1, SignalId::signal_csn, SignalId::signal_rx, SignalId::signal_sck, SignalId::signal_tx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_spi1_pico_all_signals;
  static constexpr std::array<RouteId, 9> kRoutes = {{
    RouteId::candidate_gp10_spi1_sck,
    RouteId::candidate_gp11_spi1_tx,
    RouteId::candidate_gp12_spi1_rx,
    RouteId::candidate_gp13_spi1_csn,
    RouteId::candidate_gp14_spi1_sck,
    RouteId::candidate_gp15_spi1_tx,
    RouteId::candidate_gp25_spi1_csn,
    RouteId::candidate_gp8_spi1_rx,
    RouteId::candidate_gp9_spi1_csn,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::UART0, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_uart0_pico_tx_rx;
  static constexpr std::array<RouteId, 6> kRoutes = {{
    RouteId::candidate_gp0_uart0_tx,
    RouteId::candidate_gp12_uart0_tx,
    RouteId::candidate_gp13_uart0_rx,
    RouteId::candidate_gp16_uart0_tx,
    RouteId::candidate_gp17_uart0_rx,
    RouteId::candidate_gp1_uart0_rx,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::UART0, SignalId::signal_tx, SignalId::signal_rx, SignalId::signal_cts, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_uart0_pico_tx_rx_cts_rts;
  static constexpr std::array<RouteId, 12> kRoutes = {{
    RouteId::candidate_gp0_uart0_tx,
    RouteId::candidate_gp12_uart0_tx,
    RouteId::candidate_gp13_uart0_rx,
    RouteId::candidate_gp14_uart0_cts,
    RouteId::candidate_gp15_uart0_rts,
    RouteId::candidate_gp16_uart0_tx,
    RouteId::candidate_gp17_uart0_rx,
    RouteId::candidate_gp18_uart0_cts,
    RouteId::candidate_gp19_uart0_rts,
    RouteId::candidate_gp1_uart0_rx,
    RouteId::candidate_gp2_uart0_cts,
    RouteId::candidate_gp3_uart0_rts,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::UART1, SignalId::signal_tx, SignalId::signal_rx> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_uart1_pico_tx_rx;
  static constexpr std::array<RouteId, 7> kRoutes = {{
    RouteId::candidate_gp20_uart1_tx,
    RouteId::candidate_gp21_uart1_rx,
    RouteId::candidate_gp25_uart1_tx,
    RouteId::candidate_gp4_uart1_tx,
    RouteId::candidate_gp5_uart1_rx,
    RouteId::candidate_gp8_uart1_tx,
    RouteId::candidate_gp9_uart1_rx,
  }};
};

template<>
struct ConnectionGroupTraits<PeripheralId::UART1, SignalId::signal_tx, SignalId::signal_rx, SignalId::signal_cts, SignalId::signal_rts> {
  static constexpr bool kPresent = true;
  static constexpr ConnectionGroupId kGroupId = ConnectionGroupId::group_uart1_pico_tx_rx_cts_rts;
  static constexpr std::array<RouteId, 12> kRoutes = {{
    RouteId::candidate_gp10_uart1_cts,
    RouteId::candidate_gp11_uart1_rts,
    RouteId::candidate_gp20_uart1_tx,
    RouteId::candidate_gp21_uart1_rx,
    RouteId::candidate_gp22_uart1_cts,
    RouteId::candidate_gp25_uart1_tx,
    RouteId::candidate_gp4_uart1_tx,
    RouteId::candidate_gp5_uart1_rx,
    RouteId::candidate_gp6_uart1_cts,
    RouteId::candidate_gp7_uart1_rts,
    RouteId::candidate_gp8_uart1_tx,
    RouteId::candidate_gp9_uart1_rx,
  }};
};

struct ConnectionGroupDescriptor {
  ConnectionGroupId group_id;
  PeripheralId peripheral_id;
  std::uint16_t route_count;
};
inline constexpr std::array<ConnectionGroupDescriptor, 9> kRuntimeConnectionGroups = {{
  {ConnectionGroupId::group_adc_pico_all_signals, PeripheralId::ADC, 3u},
  {ConnectionGroupId::group_i2c0_pico_scl_sda, PeripheralId::I2C0, 13u},
  {ConnectionGroupId::group_i2c1_pico_scl_sda, PeripheralId::I2C1, 11u},
  {ConnectionGroupId::group_spi0_pico_all_signals, PeripheralId::SPI0, 15u},
  {ConnectionGroupId::group_spi1_pico_all_signals, PeripheralId::SPI1, 9u},
  {ConnectionGroupId::group_uart0_pico_tx_rx, PeripheralId::UART0, 6u},
  {ConnectionGroupId::group_uart0_pico_tx_rx_cts_rts, PeripheralId::UART0, 12u},
  {ConnectionGroupId::group_uart1_pico_tx_rx, PeripheralId::UART1, 7u},
  {ConnectionGroupId::group_uart1_pico_tx_rx_cts_rts, PeripheralId::UART1, 12u},
}};

}
}
}
}
}
}
