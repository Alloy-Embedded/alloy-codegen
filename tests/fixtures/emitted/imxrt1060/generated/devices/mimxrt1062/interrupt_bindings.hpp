#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
enum class InterruptBindingId : std::uint16_t {
  interrupt_binding_lpi2c1_lpi2c1,
  interrupt_binding_lpspi1_lpspi1,
  interrupt_binding_lpuart1_lpuart1,
  interrupt_binding_lpuart3_lpuart3,
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
  {InterruptBindingId::interrupt_binding_lpi2c1_lpi2c1, PeripheralId::LPI2C1, "LPI2C1", "LPI2C1", 28, 44, "LPI2C1_IRQHandler", nullptr, 0u, 1u},
  {InterruptBindingId::interrupt_binding_lpspi1_lpspi1, PeripheralId::LPSPI1, "LPSPI1", "LPSPI1", 32, 48, "LPSPI1_IRQHandler", nullptr, 1u, 1u},
  {InterruptBindingId::interrupt_binding_lpuart1_lpuart1, PeripheralId::LPUART1, "LPUART1", "LPUART1", 20, 36, "LPUART1_IRQHandler", nullptr, 2u, 1u},
  {InterruptBindingId::interrupt_binding_lpuart3_lpuart3, PeripheralId::LPUART3, "LPUART3", "LPUART3", 22, 38, "LPUART3_IRQHandler", nullptr, 3u, 1u},
}};

struct InterruptBindingAlias {
  InterruptBindingId binding_id;
  const char* alias_name;
};
inline constexpr std::array<InterruptBindingAlias, 4> kInterruptBindingAliases = {{
  {InterruptBindingId::interrupt_binding_lpi2c1_lpi2c1, "LPI2C1_IRQHandler"},
  {InterruptBindingId::interrupt_binding_lpspi1_lpspi1, "LPSPI1_IRQHandler"},
  {InterruptBindingId::interrupt_binding_lpuart1_lpuart1, "LPUART1_IRQHandler"},
  {InterruptBindingId::interrupt_binding_lpuart3_lpuart3, "LPUART3_IRQHandler"},
}};
}
}
}
}
}
