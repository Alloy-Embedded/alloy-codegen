#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace pico {
template<PeripheralId Peripheral, std::uint16_t VectorSlot>
struct InterruptSlotValid : std::false_type {};

template<>
struct InterruptSlotValid<PeripheralId::ADC, 38u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 22u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 27u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 11u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 28u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 12u;
};

template<>
struct InterruptSlotValid<PeripheralId::I2C0, 39u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 23u;
};

template<>
struct InterruptSlotValid<PeripheralId::I2C1, 40u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 24u;
};

template<>
struct InterruptSlotValid<PeripheralId::PWM, 20u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 4u;
};

template<>
struct InterruptSlotValid<PeripheralId::RTC, 41u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 25u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI0, 34u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 18u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI1, 35u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 19u;
};

template<>
struct InterruptSlotValid<PeripheralId::TIMER, 16u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 0u;
};

template<>
struct InterruptSlotValid<PeripheralId::TIMER, 17u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 1u;
};

template<>
struct InterruptSlotValid<PeripheralId::TIMER, 18u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 2u;
};

template<>
struct InterruptSlotValid<PeripheralId::TIMER, 19u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 3u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART0, 36u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 20u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART1, 37u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 21u;
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

inline constexpr std::array<InterruptSlotEntry, 15> kInterruptSlots = {{
  {PeripheralId::ADC, 38u, 22u},
  {PeripheralId::DMA, 27u, 11u},
  {PeripheralId::DMA, 28u, 12u},
  {PeripheralId::I2C0, 39u, 23u},
  {PeripheralId::I2C1, 40u, 24u},
  {PeripheralId::PWM, 20u, 4u},
  {PeripheralId::RTC, 41u, 25u},
  {PeripheralId::SPI0, 34u, 18u},
  {PeripheralId::SPI1, 35u, 19u},
  {PeripheralId::TIMER, 16u, 0u},
  {PeripheralId::TIMER, 17u, 1u},
  {PeripheralId::TIMER, 18u, 2u},
  {PeripheralId::TIMER, 19u, 3u},
  {PeripheralId::UART0, 36u, 20u},
  {PeripheralId::UART1, 37u, 21u},
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
