#pragma once

#include <array>
#include <cstdint>
#include "../../clock_tree_lite.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace devices {
namespace stm32g071rb {
enum class PeripheralId : std::uint16_t {
  DMA1,
  DMAMUX1,
  GPIOA,
  GPIOB,
  RCC,
  USART1,
};

struct PeripheralInstanceDescriptor {
  PeripheralId peripheral_id;
  const char* name;
  const char* ip_name;
  const char* ip_version;
  const char* backend_schema_id;
  int instance;
  std::uintptr_t base_address;
  ClockGateId clock_gate_id;
  ResetId reset_id;
  ClockSelectorId selector_id;
  std::uint16_t interrupt_binding_offset;
  std::uint16_t interrupt_binding_count;
  std::uint16_t dma_binding_offset;
  std::uint16_t dma_binding_count;
  std::uint16_t capability_overlay_offset;
  std::uint16_t capability_overlay_count;
  int register_count;
};
inline constexpr std::array<PeripheralInstanceDescriptor, 6> kPeripheralInstances = {{
  {PeripheralId::DMA1, "DMA1", "dma", "bdma_v1_0", "alloy.dma.st-bdma-v1-0", 1, 0x40020000u, ClockGateId::stm32g071rb_gate_dma1, ResetId::stm32g071rb_reset_dma1, ClockSelectorId::none, 0u, 2u, 0u, 0u, 0u, 0u, 0},
  {PeripheralId::DMAMUX1, "DMAMUX1", "dmamux", "dmamux_v1_0", "alloy.dma-router.st-dmamux-v1-0", 1, 0x40020800u, ClockGateId::stm32g071rb_gate_dmamux1, ResetId::stm32g071rb_reset_dmamux1, ClockSelectorId::none, 0u, 0u, 0u, 0u, 0u, 0u, 0},
  {PeripheralId::GPIOA, "GPIOA", "gpio", "STM32G07x_gpio_v1_0", "alloy.gpio.st-stm32g07x-gpio-v1-0", 0, 0x50000000u, ClockGateId::stm32g071rb_gate_gpioa, ResetId::stm32g071rb_reset_gpioa, ClockSelectorId::none, 0u, 0u, 0u, 0u, 0u, 0u, 3},
  {PeripheralId::GPIOB, "GPIOB", "gpio", "STM32G07x_gpio_v1_0", "alloy.gpio.st-stm32g07x-gpio-v1-0", 1, 0x50000400u, ClockGateId::stm32g071rb_gate_gpiob, ResetId::stm32g071rb_reset_gpiob, ClockSelectorId::none, 0u, 0u, 0u, 0u, 0u, 0u, 3},
  {PeripheralId::RCC, "RCC", "rcc", "rcc_g0_v1_0", "alloy.rcc.st-rcc-g0-v1-0", 0, 0x40021000u, ClockGateId::none, ResetId::none, ClockSelectorId::none, 2u, 1u, 0u, 0u, 0u, 0u, 8},
  {PeripheralId::USART1, "USART1", "usart", "usart_v3_1", "alloy.uart.st-usart-v3-1", 1, 0x40013800u, ClockGateId::stm32g071rb_gate_usart1, ResetId::stm32g071rb_reset_usart1, ClockSelectorId::stm32g071rb_selector_usart1_kernel, 3u, 1u, 0u, 2u, 0u, 2u, 6},
}};
}
}
}
}
}
