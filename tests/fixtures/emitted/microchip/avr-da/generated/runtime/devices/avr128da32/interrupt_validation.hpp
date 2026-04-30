#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
template<PeripheralId Peripheral, std::uint16_t VectorSlot>
struct InterruptSlotValid : std::false_type {};

template<>
struct InterruptSlotValid<PeripheralId::SPI0, 44u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 28u;
};

template<>
struct InterruptSlotValid<PeripheralId::TWI0, 42u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 26u;
};

template<>
struct InterruptSlotValid<PeripheralId::TWI0, 43u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 27u;
};

template<>
struct InterruptSlotValid<PeripheralId::USART0, 34u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 18u;
};

template<>
struct InterruptSlotValid<PeripheralId::USART0, 35u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 19u;
};

template<>
struct InterruptSlotValid<PeripheralId::USART0, 36u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 20u;
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

inline constexpr std::array<InterruptSlotEntry, 6> kInterruptSlots = {{
  {PeripheralId::SPI0, 44u, 28u},
  {PeripheralId::TWI0, 42u, 26u},
  {PeripheralId::TWI0, 43u, 27u},
  {PeripheralId::USART0, 34u, 18u},
  {PeripheralId::USART0, 35u, 19u},
  {PeripheralId::USART0, 36u, 20u},
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
