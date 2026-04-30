#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace nordic {
namespace nrf52 {
namespace generated {
namespace runtime {
namespace devices {
namespace nrf52840 {
template<PeripheralId Peripheral, std::uint16_t VectorSlot>
struct InterruptSlotValid : std::false_type {};

template<>
struct InterruptSlotValid<PeripheralId::I2C0, 19u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 3u;
};

template<>
struct InterruptSlotValid<PeripheralId::RTC0, 27u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 11u;
};

template<>
struct InterruptSlotValid<PeripheralId::TIMER0, 24u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 8u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART0, 18u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 2u;
};

template<>
struct InterruptSlotValid<PeripheralId::WDT0, 32u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 16u;
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
  {PeripheralId::I2C0, 19u, 3u},
  {PeripheralId::RTC0, 27u, 11u},
  {PeripheralId::TIMER0, 24u, 8u},
  {PeripheralId::UART0, 18u, 2u},
  {PeripheralId::WDT0, 32u, 16u},
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
