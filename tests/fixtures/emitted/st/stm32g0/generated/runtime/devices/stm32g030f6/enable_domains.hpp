#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "clock_bindings.hpp"
#include "clock_graph.hpp"
#include "peripheral_instances.hpp"
#include "register_fields.hpp"
#include "registers.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g030f6 {
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
  {EnableDomainId::gate_adc1, PeripheralId::ADC1, ClockGateId::gate_adc1, ClockNodeId::clock_node_rcc_apbenr2, RegisterId::none, FieldId::none},
  {EnableDomainId::gate_dma1, PeripheralId::DMA1, ClockGateId::gate_dma1, ClockNodeId::clock_node_rcc_ahbenr, RegisterId::register_rcc_ahbenr, FieldId::field_rcc_ahbenr_dma1en},
  {EnableDomainId::gate_dmamux1, PeripheralId::DMAMUX1, ClockGateId::gate_dmamux1, ClockNodeId::clock_node_rcc_ahbenr, RegisterId::register_rcc_ahbenr, FieldId::field_rcc_ahbenr_dma1en},
  {EnableDomainId::gate_gpioa, PeripheralId::GPIOA, ClockGateId::gate_gpioa, ClockNodeId::clock_node_rcc_iopenr, RegisterId::register_rcc_iopenr, FieldId::field_rcc_iopenr_gpioaen},
  {EnableDomainId::gate_i2c1, PeripheralId::I2C1, ClockGateId::gate_i2c1, ClockNodeId::clock_node_rcc_apbenr1, RegisterId::register_rcc_apbenr1, FieldId::none},
  {EnableDomainId::gate_spi1, PeripheralId::SPI1, ClockGateId::gate_spi1, ClockNodeId::clock_node_rcc_apbenr2, RegisterId::none, FieldId::none},
  {EnableDomainId::gate_tim1, PeripheralId::TIM1, ClockGateId::gate_tim1, ClockNodeId::clock_node_rcc_apbenr2, RegisterId::none, FieldId::none},
  {EnableDomainId::gate_usart2, PeripheralId::USART2, ClockGateId::gate_usart2, ClockNodeId::clock_node_rcc_apbenr1, RegisterId::register_rcc_apbenr1, FieldId::field_rcc_apbenr1_usart2en},
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
struct EnableDomainTraits<EnableDomainId::gate_adc1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::ADC1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_adc1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_apbenr2;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::ADC1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_adc1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_dma1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::DMA1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_dma1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_ahbenr;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahbenr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahbenr_dma1en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::DMA1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_dma1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_dmamux1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::DMAMUX1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_dmamux1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_ahbenr;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahbenr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahbenr_dma1en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::DMAMUX1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_dmamux1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_gpioa> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIOA;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpioa;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_iopenr;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_iopenr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_iopenr_gpioaen;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::GPIOA> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_gpioa;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_i2c1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::I2C1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_i2c1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_apbenr1;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apbenr1;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::I2C1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_i2c1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_spi1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_apbenr2;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::SPI1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_spi1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_tim1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::TIM1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_tim1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_apbenr2;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::TIM1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_tim1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_usart2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::USART2;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usart2;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_apbenr1;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apbenr1;
  static constexpr FieldId kFieldId = FieldId::field_rcc_apbenr1_usart2en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::USART2> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_usart2;
};

}
}
}
}
}
}
