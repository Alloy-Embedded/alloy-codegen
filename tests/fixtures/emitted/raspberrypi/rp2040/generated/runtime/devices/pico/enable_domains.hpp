#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "clock_bindings.hpp"
#include "clock_graph.hpp"
#include "peripheral_instances.hpp"
#include "register_fields.hpp"
#include "registers.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace pico {
using EnableDomainId = ClockGateId;

struct EnableDomainDescriptor {
  EnableDomainId enable_domain_id;
  PeripheralId peripheral_id;
  ClockGateId clock_gate_id;
  ClockNodeId parent_clock_node_id;
  RegisterId register_id;
  FieldId field_id;
};
inline constexpr std::array<EnableDomainDescriptor, 8> kEnableDomains = {{
  {EnableDomainId::gate_adc, PeripheralId::ADC, ClockGateId::gate_adc, ClockNodeId::clock_node_resets_reset, RegisterId::register_resets_reset, FieldId::field_resets_reset_adc},
  {EnableDomainId::gate_dma, PeripheralId::DMA, ClockGateId::gate_dma, ClockNodeId::clock_node_resets_reset, RegisterId::register_resets_reset, FieldId::field_resets_reset_dma},
  {EnableDomainId::gate_i2c0, PeripheralId::I2C0, ClockGateId::gate_i2c0, ClockNodeId::clock_node_resets_reset, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c0},
  {EnableDomainId::gate_i2c1, PeripheralId::I2C1, ClockGateId::gate_i2c1, ClockNodeId::clock_node_resets_reset, RegisterId::register_resets_reset, FieldId::field_resets_reset_i2c1},
  {EnableDomainId::gate_spi0, PeripheralId::SPI0, ClockGateId::gate_spi0, ClockNodeId::clock_node_resets_reset, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi0},
  {EnableDomainId::gate_spi1, PeripheralId::SPI1, ClockGateId::gate_spi1, ClockNodeId::clock_node_resets_reset, RegisterId::register_resets_reset, FieldId::field_resets_reset_spi1},
  {EnableDomainId::gate_uart0, PeripheralId::UART0, ClockGateId::gate_uart0, ClockNodeId::clock_node_resets_reset, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart0},
  {EnableDomainId::gate_uart1, PeripheralId::UART1, ClockGateId::gate_uart1, ClockNodeId::clock_node_resets_reset, RegisterId::register_resets_reset, FieldId::field_resets_reset_uart1},
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
struct EnableDomainTraits<EnableDomainId::gate_adc> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::ADC;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_adc;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_resets_reset;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_adc;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::ADC> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_adc;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_dma> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::DMA;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_dma;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_resets_reset;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_dma;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::DMA> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_dma;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_i2c0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::I2C0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_i2c0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_resets_reset;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_i2c0;
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
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_resets_reset;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_i2c1;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::I2C1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_i2c1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_spi0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_resets_reset;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_spi0;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::SPI0> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_spi0;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_spi1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_resets_reset;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_spi1;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::SPI1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_spi1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_uart0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_resets_reset;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_uart0;
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
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_resets_reset;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_uart1;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::UART1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_uart1;
};

}
}
}
}
}
}
