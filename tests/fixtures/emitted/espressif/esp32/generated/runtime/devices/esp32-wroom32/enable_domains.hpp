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
namespace esp32 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32_wroom32 {
using EnableDomainId = ClockGateId;

struct EnableDomainDescriptor {
  EnableDomainId enable_domain_id;
  PeripheralId peripheral_id;
  ClockGateId clock_gate_id;
  ClockNodeId parent_clock_node_id;
  RegisterId register_id;
  FieldId field_id;
};
inline constexpr std::array<EnableDomainDescriptor, 3> kEnableDomains = {{
  {EnableDomainId::gate_i2c0, PeripheralId::I2C0, ClockGateId::gate_i2c0, ClockNodeId::clock_node_dport_perip_clk_en, RegisterId::register_dport_perip_clk_en, FieldId::field_dport_perip_clk_en_i2c0_ext0_clk_en},
  {EnableDomainId::gate_spi0, PeripheralId::SPI0, ClockGateId::gate_spi0, ClockNodeId::clock_node_dport_perip_clk_en, RegisterId::register_dport_perip_clk_en, FieldId::field_dport_perip_clk_en_spi01_clk_en},
  {EnableDomainId::gate_uart0, PeripheralId::UART0, ClockGateId::gate_uart0, ClockNodeId::clock_node_dport_perip_clk_en, RegisterId::register_dport_perip_clk_en, FieldId::field_dport_perip_clk_en_uart_clk_en},
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
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_dport_perip_clk_en;
  static constexpr RegisterId kRegisterId = RegisterId::register_dport_perip_clk_en;
  static constexpr FieldId kFieldId = FieldId::field_dport_perip_clk_en_i2c0_ext0_clk_en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::I2C0> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_i2c0;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_spi0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_dport_perip_clk_en;
  static constexpr RegisterId kRegisterId = RegisterId::register_dport_perip_clk_en;
  static constexpr FieldId kFieldId = FieldId::field_dport_perip_clk_en_spi01_clk_en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::SPI0> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_spi0;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_uart0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_dport_perip_clk_en;
  static constexpr RegisterId kRegisterId = RegisterId::register_dport_perip_clk_en;
  static constexpr FieldId kFieldId = FieldId::field_dport_perip_clk_en_uart_clk_en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::UART0> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_uart0;
};

}
}
}
}
}
}
