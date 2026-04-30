#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "clock_bindings.hpp"
#include "clock_graph.hpp"
#include "peripheral_instances.hpp"
#include "register_fields.hpp"
#include "registers.hpp"

namespace espressif {
namespace esp32s3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32s3 {
using EnableDomainId = ClockGateId;

struct EnableDomainDescriptor {
  EnableDomainId enable_domain_id;
  PeripheralId peripheral_id;
  ClockGateId clock_gate_id;
  ClockNodeId parent_clock_node_id;
  RegisterId register_id;
  FieldId field_id;
};
inline constexpr std::array<EnableDomainDescriptor, 7> kEnableDomains = {{
  {EnableDomainId::gate_i2c0, PeripheralId::I2C0, ClockGateId::gate_i2c0, ClockNodeId::clock_node_system_perip_clk_en0, RegisterId::register_system_perip_clk_en0, FieldId::field_system_perip_clk_en0_i2c_ext0_clk_en},
  {EnableDomainId::gate_i2c1, PeripheralId::I2C1, ClockGateId::gate_i2c1, ClockNodeId::clock_node_system_perip_clk_en0, RegisterId::register_system_perip_clk_en0, FieldId::field_system_perip_clk_en0_i2c_ext1_clk_en},
  {EnableDomainId::gate_spi2, PeripheralId::SPI2, ClockGateId::gate_spi2, ClockNodeId::clock_node_system_perip_clk_en0, RegisterId::register_system_perip_clk_en0, FieldId::field_system_perip_clk_en0_spi2_clk_en},
  {EnableDomainId::gate_spi3, PeripheralId::SPI3, ClockGateId::gate_spi3, ClockNodeId::clock_node_system_perip_clk_en0, RegisterId::register_system_perip_clk_en0, FieldId::field_system_perip_clk_en0_spi3_clk_en},
  {EnableDomainId::gate_uart0, PeripheralId::UART0, ClockGateId::gate_uart0, ClockNodeId::clock_node_system_perip_clk_en0, RegisterId::register_system_perip_clk_en0, FieldId::field_system_perip_clk_en0_uart_clk_en},
  {EnableDomainId::gate_uart1, PeripheralId::UART1, ClockGateId::gate_uart1, ClockNodeId::clock_node_system_perip_clk_en0, RegisterId::register_system_perip_clk_en0, FieldId::field_system_perip_clk_en0_uart1_clk_en},
  {EnableDomainId::gate_uart2, PeripheralId::UART2, ClockGateId::gate_uart2, ClockNodeId::clock_node_system_perip_clk_en1, RegisterId::register_system_perip_clk_en1, FieldId::field_system_perip_clk_en1_uart2_clk_en},
}};

template<EnableDomainId Id>
struct EnableDomainTraits {
  static constexpr bool kPresent = false;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::none;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<PeripheralId Id>
struct PeripheralEnableDomainTraits {
  static constexpr bool kPresent = false;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::none;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_i2c0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::I2C0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_i2c0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_system_perip_clk_en0;
  static constexpr RegisterId kRegisterId = RegisterId::register_system_perip_clk_en0;
  static constexpr FieldId kFieldId = FieldId::field_system_perip_clk_en0_i2c_ext0_clk_en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::I2C0> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_i2c0;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_i2c1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::I2C1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_i2c1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_system_perip_clk_en0;
  static constexpr RegisterId kRegisterId = RegisterId::register_system_perip_clk_en0;
  static constexpr FieldId kFieldId = FieldId::field_system_perip_clk_en0_i2c_ext1_clk_en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::I2C1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_i2c1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_spi2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI2;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi2;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_system_perip_clk_en0;
  static constexpr RegisterId kRegisterId = RegisterId::register_system_perip_clk_en0;
  static constexpr FieldId kFieldId = FieldId::field_system_perip_clk_en0_spi2_clk_en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::SPI2> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_spi2;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_spi3> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI3;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi3;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_system_perip_clk_en0;
  static constexpr RegisterId kRegisterId = RegisterId::register_system_perip_clk_en0;
  static constexpr FieldId kFieldId = FieldId::field_system_perip_clk_en0_spi3_clk_en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::SPI3> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_spi3;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_uart0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_system_perip_clk_en0;
  static constexpr RegisterId kRegisterId = RegisterId::register_system_perip_clk_en0;
  static constexpr FieldId kFieldId = FieldId::field_system_perip_clk_en0_uart_clk_en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::UART0> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_uart0;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_uart1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_system_perip_clk_en0;
  static constexpr RegisterId kRegisterId = RegisterId::register_system_perip_clk_en0;
  static constexpr FieldId kFieldId = FieldId::field_system_perip_clk_en0_uart1_clk_en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::UART1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_uart1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_uart2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART2;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart2;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_system_perip_clk_en1;
  static constexpr RegisterId kRegisterId = RegisterId::register_system_perip_clk_en1;
  static constexpr FieldId kFieldId = FieldId::field_system_perip_clk_en1_uart2_clk_en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::UART2> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_uart2;
};

}
}
}
}
}
}
