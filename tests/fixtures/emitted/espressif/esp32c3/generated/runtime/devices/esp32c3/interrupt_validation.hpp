#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace espressif {
namespace esp32c3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32c3 {
template<PeripheralId Peripheral, std::uint16_t VectorSlot>
struct InterruptSlotValid : std::false_type {};

template<>
struct InterruptSlotValid<PeripheralId::APB_SARADC, 59u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 43u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 60u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 44u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 61u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 45u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 62u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 46u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 71u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 55u;
};

template<>
struct InterruptSlotValid<PeripheralId::GPIO, 32u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 16u;
};

template<>
struct InterruptSlotValid<PeripheralId::GPIO, 33u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 17u;
};

template<>
struct InterruptSlotValid<PeripheralId::I2C0, 27u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 11u;
};

template<>
struct InterruptSlotValid<PeripheralId::I2C0, 45u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 29u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI0, 56u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 40u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI1, 34u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 18u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI2, 35u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 19u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART0, 37u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 21u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART1, 38u> : std::true_type {
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

inline constexpr std::array<InterruptSlotEntry, 14> kInterruptSlots = {{
  {PeripheralId::APB_SARADC, 59u, 43u},
  {PeripheralId::DMA, 60u, 44u},
  {PeripheralId::DMA, 61u, 45u},
  {PeripheralId::DMA, 62u, 46u},
  {PeripheralId::DMA, 71u, 55u},
  {PeripheralId::GPIO, 32u, 16u},
  {PeripheralId::GPIO, 33u, 17u},
  {PeripheralId::I2C0, 27u, 11u},
  {PeripheralId::I2C0, 45u, 29u},
  {PeripheralId::SPI0, 56u, 40u},
  {PeripheralId::SPI1, 34u, 18u},
  {PeripheralId::SPI2, 35u, 19u},
  {PeripheralId::UART0, 37u, 21u},
  {PeripheralId::UART1, 38u, 22u},
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
