#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f405rg {
enum class InterruptId : std::uint16_t {
  none,
  DMA1_Stream0,
  DMA2_Stream0,
  OTG_FS,
  USART1,
  USART2,
};

struct InterruptDescriptor {
  InterruptId interrupt_id;
  PeripheralId peripheral_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptDescriptor, 5> kInterruptDescriptors = {{
  {InterruptId::DMA1_Stream0, PeripheralId::DMA1, 11u, 27u},
  {InterruptId::DMA2_Stream0, PeripheralId::DMA2, 56u, 72u},
  {InterruptId::OTG_FS, PeripheralId::OTG_FS, 67u, 83u},
  {InterruptId::USART1, PeripheralId::USART1, 37u, 53u},
  {InterruptId::USART2, PeripheralId::USART2, 38u, 54u},
}};
}
}
}
}
}
}
