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
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f401re {
using EnableDomainId = ClockGateId;

struct EnableDomainDescriptor {
  EnableDomainId enable_domain_id;
  PeripheralId peripheral_id;
  ClockGateId clock_gate_id;
  ClockNodeId parent_clock_node_id;
  RegisterId register_id;
  FieldId field_id;
};
inline constexpr std::array<EnableDomainDescriptor, 9> kEnableDomains = {{
  {EnableDomainId::gate_dma1, PeripheralId::DMA1, ClockGateId::gate_dma1, ClockNodeId::clock_node_rcc_ahb1enr, RegisterId::register_rcc_ahb1enr, FieldId::field_rcc_ahb1enr_dma1en},
  {EnableDomainId::gate_dma2, PeripheralId::DMA2, ClockGateId::gate_dma2, ClockNodeId::clock_node_rcc_ahb1enr, RegisterId::register_rcc_ahb1enr, FieldId::field_rcc_ahb1enr_dma2en},
  {EnableDomainId::gate_gpioa, PeripheralId::GPIOA, ClockGateId::gate_gpioa, ClockNodeId::clock_node_rcc_ahb1enr, RegisterId::register_rcc_ahb1enr, FieldId::field_rcc_ahb1enr_gpioaen},
  {EnableDomainId::gate_gpiob, PeripheralId::GPIOB, ClockGateId::gate_gpiob, ClockNodeId::clock_node_rcc_ahb1enr, RegisterId::register_rcc_ahb1enr, FieldId::field_rcc_ahb1enr_gpioben},
  {EnableDomainId::gate_otg_fs, PeripheralId::OTG_FS, ClockGateId::gate_otg_fs, ClockNodeId::clock_node_rcc_ahb2enr, RegisterId::register_rcc_ahb2enr, FieldId::field_rcc_ahb2enr_otgfsen},
  {EnableDomainId::gate_spi1, PeripheralId::SPI1, ClockGateId::gate_spi1, ClockNodeId::clock_node_rcc_apb2enr, RegisterId::register_rcc_apb2enr, FieldId::none},
  {EnableDomainId::gate_tim1, PeripheralId::TIM1, ClockGateId::gate_tim1, ClockNodeId::clock_node_rcc_apb2enr, RegisterId::register_rcc_apb2enr, FieldId::none},
  {EnableDomainId::gate_usart1, PeripheralId::USART1, ClockGateId::gate_usart1, ClockNodeId::clock_node_rcc_apb2enr, RegisterId::register_rcc_apb2enr, FieldId::field_rcc_apb2enr_usart1en},
  {EnableDomainId::gate_usart2, PeripheralId::USART2, ClockGateId::gate_usart2, ClockNodeId::clock_node_rcc_apb1enr, RegisterId::register_rcc_apb1enr, FieldId::field_rcc_apb1enr_usart2en},
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
struct EnableDomainTraits<EnableDomainId::gate_dma1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::DMA1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_dma1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_ahb1enr;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb1enr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb1enr_dma1en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::DMA1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_dma1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_dma2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::DMA2;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_dma2;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_ahb1enr;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb1enr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb1enr_dma2en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::DMA2> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_dma2;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_gpioa> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIOA;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpioa;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_ahb1enr;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb1enr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb1enr_gpioaen;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::GPIOA> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_gpioa;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_gpiob> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIOB;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpiob;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_ahb1enr;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb1enr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb1enr_gpioben;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::GPIOB> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_gpiob;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_otg_fs> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::OTG_FS;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_otg_fs;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_ahb2enr;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb2enr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb2enr_otgfsen;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::OTG_FS> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_otg_fs;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_spi1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_apb2enr;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apb2enr;
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
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_apb2enr;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apb2enr;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::TIM1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_tim1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_usart1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::USART1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usart1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_apb2enr;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apb2enr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_apb2enr_usart1en;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::USART1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_usart1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_usart2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::USART2;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usart2;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_rcc_apb1enr;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apb1enr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_apb1enr_usart2en;
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
