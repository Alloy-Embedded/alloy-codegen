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
namespace stm32g0b1re {
template<PeripheralId Peripheral, std::uint16_t VectorSlot>
struct InterruptSlotValid : std::false_type {};

template<>
struct InterruptSlotValid<PeripheralId::DMA1, 25u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 9u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA1, 26u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 10u;
};

template<>
struct InterruptSlotValid<PeripheralId::FDCAN1, 35u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 19u;
};

template<>
struct InterruptSlotValid<PeripheralId::USART1, 43u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 27u;
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

inline constexpr std::array<InterruptSlotEntry, 4> kInterruptSlots = {{
  {PeripheralId::DMA1, 25u, 9u},
  {PeripheralId::DMA1, 26u, 10u},
  {PeripheralId::FDCAN1, 35u, 19u},
  {PeripheralId::USART1, 43u, 27u},
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
