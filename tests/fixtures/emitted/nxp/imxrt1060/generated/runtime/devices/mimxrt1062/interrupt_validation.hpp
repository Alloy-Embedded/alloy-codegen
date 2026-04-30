#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
template<PeripheralId Peripheral, std::uint16_t VectorSlot>
struct InterruptSlotValid : std::false_type {};

template<>
struct InterruptSlotValid<PeripheralId::LPSPI1, 48u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 32u;
};

template<>
struct InterruptSlotValid<PeripheralId::LPUART1, 36u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 20u;
};

template<>
struct InterruptSlotValid<PeripheralId::LPUART3, 38u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 22u;
};

template<PeripheralId Peripheral, std::uint16_t VectorSlot>
concept ValidInterruptSlot = InterruptSlotValid<Peripheral, VectorSlot>::value;

namespace detail {
template<PeripheralId Peripheral, std::uint16_t VectorSlot>
inline constexpr bool kInvalidInterruptSlot = false;
}  // namespace detail

struct InterruptSlotEntry {
  PeripheralId peripheral;
  std::uint16_t vector_slot;
  std::uint16_t irq_line;
};

inline constexpr std::array<InterruptSlotEntry, 3> kInterruptSlots = {{
  {PeripheralId::LPSPI1, 48u, 32u},
  {PeripheralId::LPUART1, 36u, 20u},
  {PeripheralId::LPUART3, 38u, 22u},
}};

constexpr bool is_valid_interrupt_slot(PeripheralId peripheral, std::uint16_t vector_slot) noexcept {
  for (auto const& entry : kInterruptSlots) {
    if (entry.peripheral == peripheral && entry.vector_slot == vector_slot) {
      return true;
    }
  }
  return false;
}
}
}
}
}
}
}
