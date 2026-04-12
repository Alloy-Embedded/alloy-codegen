#pragma once

#include <array>
#include <cstdint>
#include "runtime_refs.hpp"
namespace st {
namespace stm32g0 {
namespace generated {
enum class InterruptMapId : std::uint16_t {
  none,
  stm32g071rb_RCC_CRS,
  stm32g071rb_DMA1_Channel1,
  stm32g071rb_DMA1_Channel2_3,
  stm32g071rb_USART1,
};

enum class InterruptMapSymbolId : std::uint16_t {
  none,
  RCC_CRS_IRQHandler,
  DMA1_Channel1_IRQHandler,
  DMA1_Channel2_3_IRQHandler,
  USART1_IRQHandler,
};

enum class InterruptMapSharedGroupId : std::uint16_t {
  none,
  interrupt_group_dma1,
};

enum class InterruptMapAliasId : std::uint16_t {
  none,
  RCC_CRS_IRQHandler,
  DMA1_Channel1_IRQHandler,
  DMA1_Channel2_3_IRQHandler,
  USART1_IRQHandler,
};

struct InterruptDescriptor {
  DeviceRefId device_id;
  InterruptMapId interrupt_id;
  int line;
  PeripheralRefId peripheral_id;
  InterruptMapSharedGroupId shared_group_id;
  std::uint16_t alias_offset;
  std::uint16_t alias_count;
  int vector_slot;
  InterruptMapSymbolId symbol_id;
};
inline constexpr InterruptDescriptor kInterruptMap[] = {
  {DeviceRefId::stm32g071rb, InterruptMapId::stm32g071rb_RCC_CRS, 4, PeripheralRefId::stm32g071rb_RCC, InterruptMapSharedGroupId::none, 2u, 1u, 20, InterruptMapSymbolId::RCC_CRS_IRQHandler},
  {DeviceRefId::stm32g071rb, InterruptMapId::stm32g071rb_DMA1_Channel1, 9, PeripheralRefId::stm32g071rb_DMA1, InterruptMapSharedGroupId::interrupt_group_dma1, 0u, 1u, 25, InterruptMapSymbolId::DMA1_Channel1_IRQHandler},
  {DeviceRefId::stm32g071rb, InterruptMapId::stm32g071rb_DMA1_Channel2_3, 10, PeripheralRefId::stm32g071rb_DMA1, InterruptMapSharedGroupId::interrupt_group_dma1, 1u, 1u, 26, InterruptMapSymbolId::DMA1_Channel2_3_IRQHandler},
  {DeviceRefId::stm32g071rb, InterruptMapId::stm32g071rb_USART1, 27, PeripheralRefId::stm32g071rb_USART1, InterruptMapSharedGroupId::none, 3u, 1u, 43, InterruptMapSymbolId::USART1_IRQHandler},
};

struct InterruptAliasRef {
  InterruptMapId interrupt_id;
  InterruptMapAliasId alias_id;
};
inline constexpr std::array<InterruptAliasRef, 4> kInterruptAliases = {{
  {InterruptMapId::stm32g071rb_RCC_CRS, InterruptMapAliasId::RCC_CRS_IRQHandler},
  {InterruptMapId::stm32g071rb_DMA1_Channel1, InterruptMapAliasId::DMA1_Channel1_IRQHandler},
  {InterruptMapId::stm32g071rb_DMA1_Channel2_3, InterruptMapAliasId::DMA1_Channel2_3_IRQHandler},
  {InterruptMapId::stm32g071rb_USART1, InterruptMapAliasId::USART1_IRQHandler},
}};
}
}
}
