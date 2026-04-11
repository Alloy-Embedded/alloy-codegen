#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace devices {
namespace stm32g071rb {
enum class InterruptBindingId : std::uint16_t {
  interrupt_binding_dma1_dma1_channel1,
  interrupt_binding_dma1_dma1_channel2_3,
  interrupt_binding_rcc_rcc_crs,
  interrupt_binding_usart1_usart1,
};

struct InterruptBindingDescriptor {
  InterruptBindingId binding_id;
  PeripheralId peripheral_id;
  const char* peripheral_name;
  const char* interrupt_name;
  int line;
  int vector_slot;
  const char* symbol_name;
  const char* shared_group;
  std::uint16_t alias_offset;
  std::uint16_t alias_count;
};
inline constexpr std::array<InterruptBindingDescriptor, 4> kInterruptBindings = {{
  {InterruptBindingId::interrupt_binding_dma1_dma1_channel1, PeripheralId::DMA1, "DMA1", "DMA1_Channel1", 9, 25, "DMA1_Channel1_IRQHandler", "interrupt-group:dma1", 0u, 1u},
  {InterruptBindingId::interrupt_binding_dma1_dma1_channel2_3, PeripheralId::DMA1, "DMA1", "DMA1_Channel2_3", 10, 26, "DMA1_Channel2_3_IRQHandler", "interrupt-group:dma1", 1u, 1u},
  {InterruptBindingId::interrupt_binding_rcc_rcc_crs, PeripheralId::RCC, "RCC", "RCC_CRS", 4, 20, "RCC_CRS_IRQHandler", nullptr, 2u, 1u},
  {InterruptBindingId::interrupt_binding_usart1_usart1, PeripheralId::USART1, "USART1", "USART1", 27, 43, "USART1_IRQHandler", nullptr, 3u, 1u},
}};

struct InterruptBindingAlias {
  InterruptBindingId binding_id;
  const char* alias_name;
};
inline constexpr std::array<InterruptBindingAlias, 4> kInterruptBindingAliases = {{
  {InterruptBindingId::interrupt_binding_dma1_dma1_channel1, "DMA1_Channel1_IRQHandler"},
  {InterruptBindingId::interrupt_binding_dma1_dma1_channel2_3, "DMA1_Channel2_3_IRQHandler"},
  {InterruptBindingId::interrupt_binding_rcc_rcc_crs, "RCC_CRS_IRQHandler"},
  {InterruptBindingId::interrupt_binding_usart1_usart1, "USART1_IRQHandler"},
}};
}
}
}
}
}
