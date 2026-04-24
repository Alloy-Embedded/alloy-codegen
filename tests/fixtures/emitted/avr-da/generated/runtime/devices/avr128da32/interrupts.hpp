#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
enum class InterruptId : std::uint16_t {
  none,
  NMI,
  RESET,
  SPI0_INT,
  TWI0_TWIM,
  TWI0_TWIS,
  USART0_DRE,
  USART0_RXC,
  USART0_TXC,
};

struct InterruptDescriptor {
  InterruptId interrupt_id;
  PeripheralId peripheral_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptDescriptor, 6> kInterruptDescriptors = {{
  {InterruptId::SPI0_INT, PeripheralId::SPI0, 28u, 44u},
  {InterruptId::TWI0_TWIS, PeripheralId::TWI0, 26u, 42u},
  {InterruptId::TWI0_TWIM, PeripheralId::TWI0, 27u, 43u},
  {InterruptId::USART0_RXC, PeripheralId::USART0, 18u, 34u},
  {InterruptId::USART0_DRE, PeripheralId::USART0, 19u, 35u},
  {InterruptId::USART0_TXC, PeripheralId::USART0, 20u, 36u},
}};
}
}
}
}
}
}
