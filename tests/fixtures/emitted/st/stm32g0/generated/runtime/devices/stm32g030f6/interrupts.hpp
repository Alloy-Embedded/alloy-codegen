#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g030f6 {
enum class InterruptId : std::uint16_t {
  none,
  DMA1_Channel1,
  RCC_CRS,
  USART2,
};

struct InterruptDescriptor {
  InterruptId interrupt_id;
  PeripheralId peripheral_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptDescriptor, 2> kInterruptDescriptors = {{
  {InterruptId::DMA1_Channel1, PeripheralId::DMA1, 9u, 25u},
  {InterruptId::USART2, PeripheralId::USART2, 28u, 44u},
}};
}
}
}
}
}
}
