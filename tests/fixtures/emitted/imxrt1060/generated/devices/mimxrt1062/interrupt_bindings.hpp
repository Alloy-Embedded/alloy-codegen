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
  none,
  interrupt_binding_lpi2c1_lpi2c1,
  interrupt_binding_lpspi1_lpspi1,
  interrupt_binding_lpuart1_lpuart1,
  interrupt_binding_lpuart3_lpuart3,
};

enum class InterruptId : std::uint16_t {
  none,
  LPI2C1,
  LPSPI1,
  LPUART1,
  LPUART3,
};

enum class InterruptSymbolId : std::uint16_t {
  none,
  LPI2C1_IRQHandler,
  LPSPI1_IRQHandler,
  LPUART1_IRQHandler,
  LPUART3_IRQHandler,
};

enum class InterruptSharedGroupId : std::uint16_t {
  none,
};

enum class InterruptAliasId : std::uint16_t {
  none,
  LPI2C1_IRQHandler,
  LPSPI1_IRQHandler,
  LPUART1_IRQHandler,
  LPUART3_IRQHandler,
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
  {InterruptBindingId::interrupt_binding_lpi2c1_lpi2c1, PeripheralId::LPI2C1, InterruptId::LPI2C1, 28, 44, InterruptSymbolId::LPI2C1_IRQHandler, InterruptSharedGroupId::none, 0u, 1u},
  {InterruptBindingId::interrupt_binding_lpspi1_lpspi1, PeripheralId::LPSPI1, InterruptId::LPSPI1, 32, 48, InterruptSymbolId::LPSPI1_IRQHandler, InterruptSharedGroupId::none, 1u, 1u},
  {InterruptBindingId::interrupt_binding_lpuart1_lpuart1, PeripheralId::LPUART1, InterruptId::LPUART1, 20, 36, InterruptSymbolId::LPUART1_IRQHandler, InterruptSharedGroupId::none, 2u, 1u},
  {InterruptBindingId::interrupt_binding_lpuart3_lpuart3, PeripheralId::LPUART3, InterruptId::LPUART3, 22, 38, InterruptSymbolId::LPUART3_IRQHandler, InterruptSharedGroupId::none, 3u, 1u},
}};

struct InterruptBindingAlias {
  InterruptBindingId binding_id;
  InterruptAliasId alias_id;
};
inline constexpr std::array<InterruptBindingAlias, 4> kInterruptBindingAliases = {{
  {InterruptBindingId::interrupt_binding_lpi2c1_lpi2c1, InterruptAliasId::LPI2C1_IRQHandler},
  {InterruptBindingId::interrupt_binding_lpspi1_lpspi1, InterruptAliasId::LPSPI1_IRQHandler},
  {InterruptBindingId::interrupt_binding_lpuart1_lpuart1, InterruptAliasId::LPUART1_IRQHandler},
  {InterruptBindingId::interrupt_binding_lpuart3_lpuart3, InterruptAliasId::LPUART3_IRQHandler},
}};
}
}
}
}
}
