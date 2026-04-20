#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1064 {
enum class InterruptId : std::uint16_t {
  none,
  LPI2C1,
  LPSPI1,
  LPUART1,
  LPUART3,
};

struct InterruptDescriptor {
  InterruptId interrupt_id;
  PeripheralId peripheral_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptDescriptor, 3> kInterruptDescriptors = {{
  {InterruptId::LPSPI1, PeripheralId::LPSPI1, 32u, 48u},
  {InterruptId::LPUART1, PeripheralId::LPUART1, 20u, 36u},
  {InterruptId::LPUART3, PeripheralId::LPUART3, 22u, 38u},
}};
}
}
}
}
}
}
