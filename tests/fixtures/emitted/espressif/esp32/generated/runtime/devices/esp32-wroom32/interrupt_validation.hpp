#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace espressif {
namespace esp32 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32_wroom32 {
template<PeripheralId Peripheral, std::uint16_t VectorSlot>
struct InterruptSlotValid : std::false_type {};

template<>
struct InterruptSlotValid<PeripheralId::GPIO, 38u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 22u;
};

template<>
struct InterruptSlotValid<PeripheralId::GPIO, 39u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 23u;
};

template<>
struct InterruptSlotValid<PeripheralId::I2C0, 65u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 49u;
};

template<>
struct InterruptSlotValid<PeripheralId::I2C1, 66u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 50u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI0, 44u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 28u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI1, 45u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 29u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI1, 68u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 52u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI2, 46u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 30u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI2, 69u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 53u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI3, 47u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 31u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI3, 70u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 54u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART0, 50u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 34u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART1, 51u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 35u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART2, 52u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 36u;
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
  {PeripheralId::GPIO, 38u, 22u},
  {PeripheralId::GPIO, 39u, 23u},
  {PeripheralId::I2C0, 65u, 49u},
  {PeripheralId::I2C1, 66u, 50u},
  {PeripheralId::SPI0, 44u, 28u},
  {PeripheralId::SPI1, 45u, 29u},
  {PeripheralId::SPI1, 68u, 52u},
  {PeripheralId::SPI2, 46u, 30u},
  {PeripheralId::SPI2, 69u, 53u},
  {PeripheralId::SPI3, 47u, 31u},
  {PeripheralId::SPI3, 70u, 54u},
  {PeripheralId::UART0, 50u, 34u},
  {PeripheralId::UART1, 51u, 35u},
  {PeripheralId::UART2, 52u, 36u},
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
