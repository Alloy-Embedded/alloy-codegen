#pragma once

#include <array>
#include <cstdint>
#include "runtime_refs.hpp"
namespace nxp {
namespace imxrt1060 {
namespace generated {
enum class InterruptMapId : std::uint16_t {
  none,
  mimxrt1062_LPUART1,
  mimxrt1062_LPUART3,
  mimxrt1062_LPI2C1,
  mimxrt1062_LPSPI1,
};

enum class InterruptMapSymbolId : std::uint16_t {
  none,
  LPUART1_IRQHandler,
  LPUART3_IRQHandler,
  LPI2C1_IRQHandler,
  LPSPI1_IRQHandler,
};

enum class InterruptMapSharedGroupId : std::uint16_t {
  none,
};

enum class InterruptMapAliasId : std::uint16_t {
  none,
  LPUART1_IRQHandler,
  LPUART3_IRQHandler,
  LPI2C1_IRQHandler,
  LPSPI1_IRQHandler,
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
  {DeviceRefId::mimxrt1062, InterruptMapId::mimxrt1062_LPUART1, 20, PeripheralRefId::mimxrt1062_LPUART1, InterruptMapSharedGroupId::none, 2u, 1u, 36, InterruptMapSymbolId::LPUART1_IRQHandler},
  {DeviceRefId::mimxrt1062, InterruptMapId::mimxrt1062_LPUART3, 22, PeripheralRefId::mimxrt1062_LPUART3, InterruptMapSharedGroupId::none, 3u, 1u, 38, InterruptMapSymbolId::LPUART3_IRQHandler},
  {DeviceRefId::mimxrt1062, InterruptMapId::mimxrt1062_LPI2C1, 28, PeripheralRefId::mimxrt1062_LPI2C1, InterruptMapSharedGroupId::none, 0u, 1u, 44, InterruptMapSymbolId::LPI2C1_IRQHandler},
  {DeviceRefId::mimxrt1062, InterruptMapId::mimxrt1062_LPSPI1, 32, PeripheralRefId::mimxrt1062_LPSPI1, InterruptMapSharedGroupId::none, 1u, 1u, 48, InterruptMapSymbolId::LPSPI1_IRQHandler},
};

struct InterruptAliasRef {
  InterruptMapId interrupt_id;
  InterruptMapAliasId alias_id;
};
inline constexpr std::array<InterruptAliasRef, 4> kInterruptAliases = {{
  {InterruptMapId::mimxrt1062_LPUART1, InterruptMapAliasId::LPUART1_IRQHandler},
  {InterruptMapId::mimxrt1062_LPUART3, InterruptMapAliasId::LPUART3_IRQHandler},
  {InterruptMapId::mimxrt1062_LPI2C1, InterruptMapAliasId::LPI2C1_IRQHandler},
  {InterruptMapId::mimxrt1062_LPSPI1, InterruptMapAliasId::LPSPI1_IRQHandler},
}};
}
}
}
