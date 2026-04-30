#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f405rg {
template<PeripheralId Peripheral, std::uint16_t VectorSlot>
struct InterruptSlotValid : std::false_type {};

template<>
struct InterruptSlotValid<PeripheralId::DMA1, 27u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 11u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA2, 72u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 56u;
};

template<>
struct InterruptSlotValid<PeripheralId::OTG_FS, 83u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 67u;
};

template<>
struct InterruptSlotValid<PeripheralId::USART1, 53u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 37u;
};

template<>
struct InterruptSlotValid<PeripheralId::USART2, 54u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 38u;
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

inline constexpr std::array<InterruptSlotEntry, 5> kInterruptSlots = {{
  {PeripheralId::DMA1, 27u, 11u},
  {PeripheralId::DMA2, 72u, 56u},
  {PeripheralId::OTG_FS, 83u, 67u},
  {PeripheralId::USART1, 53u, 37u},
  {PeripheralId::USART2, 54u, 38u},
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
