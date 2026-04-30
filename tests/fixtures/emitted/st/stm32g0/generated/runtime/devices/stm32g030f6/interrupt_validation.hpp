#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g030f6 {
template<PeripheralId Peripheral, std::uint16_t VectorSlot>
struct InterruptSlotValid : std::false_type {};

template<>
struct InterruptSlotValid<PeripheralId::DMA1, 25u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 9u;
};

template<>
struct InterruptSlotValid<PeripheralId::USART2, 44u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 28u;
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

inline constexpr std::array<InterruptSlotEntry, 2> kInterruptSlots = {{
  {PeripheralId::DMA1, 25u, 9u},
  {PeripheralId::USART2, 44u, 28u},
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
