#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace espressif {
namespace esp32s3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32s3 {
template<PeripheralId Peripheral, std::uint16_t VectorSlot>
struct InterruptSlotValid : std::false_type {};

template<>
struct InterruptSlotValid<PeripheralId::APB_SARADC, 81u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 65u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 82u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 66u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 83u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 67u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 84u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 68u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 85u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 69u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 86u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 70u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 87u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 71u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 88u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 72u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 89u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 73u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 90u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 74u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 91u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 75u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 100u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 84u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 109u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 93u;
};

template<>
struct InterruptSlotValid<PeripheralId::DMA, 114u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 98u;
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
struct InterruptSlotValid<PeripheralId::GPIO, 34u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 18u;
};

template<>
struct InterruptSlotValid<PeripheralId::GPIO, 35u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 19u;
};

template<>
struct InterruptSlotValid<PeripheralId::I2C0, 27u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 11u;
};

template<>
struct InterruptSlotValid<PeripheralId::I2C0, 58u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 42u;
};

template<>
struct InterruptSlotValid<PeripheralId::I2C1, 59u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 43u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI0, 76u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 60u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI1, 36u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 20u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI2, 37u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 21u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI2, 60u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 44u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI3, 38u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 22u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI3, 61u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 45u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART0, 43u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 27u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART1, 44u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 28u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART2, 45u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 29u;
};

template<>
struct InterruptSlotValid<PeripheralId::USB0, 54u> : std::true_type {
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

inline constexpr std::array<InterruptSlotEntry, 31> kInterruptSlots = {{
  {PeripheralId::APB_SARADC, 81u, 65u},
  {PeripheralId::DMA, 82u, 66u},
  {PeripheralId::DMA, 83u, 67u},
  {PeripheralId::DMA, 84u, 68u},
  {PeripheralId::DMA, 85u, 69u},
  {PeripheralId::DMA, 86u, 70u},
  {PeripheralId::DMA, 87u, 71u},
  {PeripheralId::DMA, 88u, 72u},
  {PeripheralId::DMA, 89u, 73u},
  {PeripheralId::DMA, 90u, 74u},
  {PeripheralId::DMA, 91u, 75u},
  {PeripheralId::DMA, 100u, 84u},
  {PeripheralId::DMA, 109u, 93u},
  {PeripheralId::DMA, 114u, 98u},
  {PeripheralId::GPIO, 32u, 16u},
  {PeripheralId::GPIO, 33u, 17u},
  {PeripheralId::GPIO, 34u, 18u},
  {PeripheralId::GPIO, 35u, 19u},
  {PeripheralId::I2C0, 27u, 11u},
  {PeripheralId::I2C0, 58u, 42u},
  {PeripheralId::I2C1, 59u, 43u},
  {PeripheralId::SPI0, 76u, 60u},
  {PeripheralId::SPI1, 36u, 20u},
  {PeripheralId::SPI2, 37u, 21u},
  {PeripheralId::SPI2, 60u, 44u},
  {PeripheralId::SPI3, 38u, 22u},
  {PeripheralId::SPI3, 61u, 45u},
  {PeripheralId::UART0, 43u, 27u},
  {PeripheralId::UART1, 44u, 28u},
  {PeripheralId::UART2, 45u, 29u},
  {PeripheralId::USB0, 54u, 38u},
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
