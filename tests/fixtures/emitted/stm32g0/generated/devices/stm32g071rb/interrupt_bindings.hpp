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
  none,
  interrupt_binding_dma1_dma1_channel1,
  interrupt_binding_dma1_dma1_channel2_3,
  interrupt_binding_rcc_rcc_crs,
  interrupt_binding_usart1_usart1,
};

enum class InterruptId : std::uint16_t {
  none,
  DMA1_Channel1,
  DMA1_Channel2_3,
  RCC_CRS,
  USART1,
};

enum class InterruptSymbolId : std::uint16_t {
  none,
  DMA1_Channel1_IRQHandler,
  DMA1_Channel2_3_IRQHandler,
  RCC_CRS_IRQHandler,
  USART1_IRQHandler,
};

enum class InterruptSharedGroupId : std::uint16_t {
  none,
  interrupt_group_dma1,
};

enum class InterruptAliasId : std::uint16_t {
  none,
  DMA1_Channel1_IRQHandler,
  DMA1_Channel2_3_IRQHandler,
  RCC_CRS_IRQHandler,
  USART1_IRQHandler,
};

struct InterruptBindingDescriptor {
  InterruptBindingId binding_id;
  PeripheralId peripheral_id;
  InterruptId interrupt_id;
  int line;
  int vector_slot;
  InterruptSymbolId symbol_id;
  InterruptSharedGroupId shared_group_id;
  std::uint16_t alias_offset;
  std::uint16_t alias_count;
};
inline constexpr std::array<InterruptBindingDescriptor, 4> kInterruptBindings = {{
  {InterruptBindingId::interrupt_binding_dma1_dma1_channel1, PeripheralId::DMA1, InterruptId::DMA1_Channel1, 9, 25, InterruptSymbolId::DMA1_Channel1_IRQHandler, InterruptSharedGroupId::interrupt_group_dma1, 0u, 1u},
  {InterruptBindingId::interrupt_binding_dma1_dma1_channel2_3, PeripheralId::DMA1, InterruptId::DMA1_Channel2_3, 10, 26, InterruptSymbolId::DMA1_Channel2_3_IRQHandler, InterruptSharedGroupId::interrupt_group_dma1, 1u, 1u},
  {InterruptBindingId::interrupt_binding_rcc_rcc_crs, PeripheralId::RCC, InterruptId::RCC_CRS, 4, 20, InterruptSymbolId::RCC_CRS_IRQHandler, InterruptSharedGroupId::none, 2u, 1u},
  {InterruptBindingId::interrupt_binding_usart1_usart1, PeripheralId::USART1, InterruptId::USART1, 27, 43, InterruptSymbolId::USART1_IRQHandler, InterruptSharedGroupId::none, 3u, 1u},
}};

struct InterruptBindingAlias {
  InterruptBindingId binding_id;
  InterruptAliasId alias_id;
};
inline constexpr std::array<InterruptBindingAlias, 4> kInterruptBindingAliases = {{
  {InterruptBindingId::interrupt_binding_dma1_dma1_channel1, InterruptAliasId::DMA1_Channel1_IRQHandler},
  {InterruptBindingId::interrupt_binding_dma1_dma1_channel2_3, InterruptAliasId::DMA1_Channel2_3_IRQHandler},
  {InterruptBindingId::interrupt_binding_rcc_rcc_crs, InterruptAliasId::RCC_CRS_IRQHandler},
  {InterruptBindingId::interrupt_binding_usart1_usart1, InterruptAliasId::USART1_IRQHandler},
}};
}
}
}
}
}
