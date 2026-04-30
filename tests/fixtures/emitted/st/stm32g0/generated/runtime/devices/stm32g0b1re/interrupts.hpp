#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g0b1re {
enum class InterruptId : std::uint16_t {
  none,
  DMA1_Channel1,
  DMA1_Channel2_3,
  FDCAN1_IT0,
  RCC_CRS,
  USART1,
};

struct InterruptDescriptor {
  InterruptId interrupt_id;
  PeripheralId peripheral_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptDescriptor, 4> kInterruptDescriptors = {{
  {InterruptId::DMA1_Channel1, PeripheralId::DMA1, 9u, 25u},
  {InterruptId::DMA1_Channel2_3, PeripheralId::DMA1, 10u, 26u},
  {InterruptId::FDCAN1_IT0, PeripheralId::FDCAN1, 19u, 35u},
  {InterruptId::USART1, PeripheralId::USART1, 27u, 43u},
}};
}
}
}
}
}
}
