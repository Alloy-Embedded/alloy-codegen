#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace nordic {
namespace nrf52 {
namespace generated {
namespace runtime {
namespace devices {
namespace nrf52840 {
enum class InterruptId : std::uint16_t {
  none,
  I2C0_IRQ,
  RTC0_IRQ,
  TIMER0_IRQ,
  UART0_IRQ,
  WDT0_IRQ,
};

struct InterruptDescriptor {
  InterruptId interrupt_id;
  PeripheralId peripheral_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptDescriptor, 5> kInterruptDescriptors = {{
  {InterruptId::I2C0_IRQ, PeripheralId::I2C0, 3u, 19u},
  {InterruptId::RTC0_IRQ, PeripheralId::RTC0, 11u, 27u},
  {InterruptId::TIMER0_IRQ, PeripheralId::TIMER0, 8u, 24u},
  {InterruptId::UART0_IRQ, PeripheralId::UART0, 2u, 18u},
  {InterruptId::WDT0_IRQ, PeripheralId::WDT0, 16u, 32u},
}};
}
}
}
}
}
}
