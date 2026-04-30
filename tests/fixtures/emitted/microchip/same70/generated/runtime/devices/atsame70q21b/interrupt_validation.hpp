#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70q21b {
template<PeripheralId Peripheral, std::uint16_t VectorSlot>
struct InterruptSlotValid : std::false_type {};

template<>
struct InterruptSlotValid<PeripheralId::AFEC0, 45u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 29u;
};

template<>
struct InterruptSlotValid<PeripheralId::AFEC1, 56u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 40u;
};

template<>
struct InterruptSlotValid<PeripheralId::DACC, 46u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 30u;
};

template<>
struct InterruptSlotValid<PeripheralId::GMAC, 55u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 39u;
};

template<>
struct InterruptSlotValid<PeripheralId::GMAC, 82u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 66u;
};

template<>
struct InterruptSlotValid<PeripheralId::GMAC, 83u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 67u;
};

template<>
struct InterruptSlotValid<PeripheralId::GMAC, 87u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 71u;
};

template<>
struct InterruptSlotValid<PeripheralId::GMAC, 88u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 72u;
};

template<>
struct InterruptSlotValid<PeripheralId::GMAC, 89u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 73u;
};

template<>
struct InterruptSlotValid<PeripheralId::GPIOA, 26u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 10u;
};

template<>
struct InterruptSlotValid<PeripheralId::GPIOB, 27u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 11u;
};

template<>
struct InterruptSlotValid<PeripheralId::GPIOC, 28u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 12u;
};

template<>
struct InterruptSlotValid<PeripheralId::GPIOD, 32u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 16u;
};

template<>
struct InterruptSlotValid<PeripheralId::GPIOE, 33u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 17u;
};

template<>
struct InterruptSlotValid<PeripheralId::HSMCI, 34u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 18u;
};

template<>
struct InterruptSlotValid<PeripheralId::MCAN0, 51u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 35u;
};

template<>
struct InterruptSlotValid<PeripheralId::MCAN0, 52u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 36u;
};

template<>
struct InterruptSlotValid<PeripheralId::MCAN1, 53u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 37u;
};

template<>
struct InterruptSlotValid<PeripheralId::MCAN1, 54u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 38u;
};

template<>
struct InterruptSlotValid<PeripheralId::PWM0, 47u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 31u;
};

template<>
struct InterruptSlotValid<PeripheralId::PWM1, 76u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 60u;
};

template<>
struct InterruptSlotValid<PeripheralId::QSPI, 59u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 43u;
};

template<>
struct InterruptSlotValid<PeripheralId::RSWDT, 79u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 63u;
};

template<>
struct InterruptSlotValid<PeripheralId::RTC, 18u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 2u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI0, 37u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 21u;
};

template<>
struct InterruptSlotValid<PeripheralId::SPI1, 58u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 42u;
};

template<>
struct InterruptSlotValid<PeripheralId::TC0, 39u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 23u;
};

template<>
struct InterruptSlotValid<PeripheralId::TC0, 40u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 24u;
};

template<>
struct InterruptSlotValid<PeripheralId::TC0, 41u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 25u;
};

template<>
struct InterruptSlotValid<PeripheralId::TC1, 42u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 26u;
};

template<>
struct InterruptSlotValid<PeripheralId::TC1, 43u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 27u;
};

template<>
struct InterruptSlotValid<PeripheralId::TC1, 44u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 28u;
};

template<>
struct InterruptSlotValid<PeripheralId::TC2, 63u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 47u;
};

template<>
struct InterruptSlotValid<PeripheralId::TC2, 64u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 48u;
};

template<>
struct InterruptSlotValid<PeripheralId::TC2, 65u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 49u;
};

template<>
struct InterruptSlotValid<PeripheralId::TC3, 66u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 50u;
};

template<>
struct InterruptSlotValid<PeripheralId::TC3, 67u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 51u;
};

template<>
struct InterruptSlotValid<PeripheralId::TC3, 68u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 52u;
};

template<>
struct InterruptSlotValid<PeripheralId::TWIHS0, 35u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 19u;
};

template<>
struct InterruptSlotValid<PeripheralId::TWIHS1, 36u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 20u;
};

template<>
struct InterruptSlotValid<PeripheralId::TWIHS2, 57u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 41u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART0, 23u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 7u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART1, 24u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 8u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART2, 60u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 44u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART3, 61u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 45u;
};

template<>
struct InterruptSlotValid<PeripheralId::UART4, 62u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 46u;
};

template<>
struct InterruptSlotValid<PeripheralId::USART0, 29u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 13u;
};

template<>
struct InterruptSlotValid<PeripheralId::USART1, 30u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 14u;
};

template<>
struct InterruptSlotValid<PeripheralId::USART2, 31u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 15u;
};

template<>
struct InterruptSlotValid<PeripheralId::USBHS, 50u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 34u;
};

template<>
struct InterruptSlotValid<PeripheralId::WDT, 20u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 4u;
};

template<>
struct InterruptSlotValid<PeripheralId::XDMAC, 74u> : std::true_type {
  static constexpr std::uint16_t kIrqLine = 58u;
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

inline constexpr std::array<InterruptSlotEntry, 52> kInterruptSlots = {{
  {PeripheralId::AFEC0, 45u, 29u},
  {PeripheralId::AFEC1, 56u, 40u},
  {PeripheralId::DACC, 46u, 30u},
  {PeripheralId::GMAC, 55u, 39u},
  {PeripheralId::GMAC, 82u, 66u},
  {PeripheralId::GMAC, 83u, 67u},
  {PeripheralId::GMAC, 87u, 71u},
  {PeripheralId::GMAC, 88u, 72u},
  {PeripheralId::GMAC, 89u, 73u},
  {PeripheralId::GPIOA, 26u, 10u},
  {PeripheralId::GPIOB, 27u, 11u},
  {PeripheralId::GPIOC, 28u, 12u},
  {PeripheralId::GPIOD, 32u, 16u},
  {PeripheralId::GPIOE, 33u, 17u},
  {PeripheralId::HSMCI, 34u, 18u},
  {PeripheralId::MCAN0, 51u, 35u},
  {PeripheralId::MCAN0, 52u, 36u},
  {PeripheralId::MCAN1, 53u, 37u},
  {PeripheralId::MCAN1, 54u, 38u},
  {PeripheralId::PWM0, 47u, 31u},
  {PeripheralId::PWM1, 76u, 60u},
  {PeripheralId::QSPI, 59u, 43u},
  {PeripheralId::RSWDT, 79u, 63u},
  {PeripheralId::RTC, 18u, 2u},
  {PeripheralId::SPI0, 37u, 21u},
  {PeripheralId::SPI1, 58u, 42u},
  {PeripheralId::TC0, 39u, 23u},
  {PeripheralId::TC0, 40u, 24u},
  {PeripheralId::TC0, 41u, 25u},
  {PeripheralId::TC1, 42u, 26u},
  {PeripheralId::TC1, 43u, 27u},
  {PeripheralId::TC1, 44u, 28u},
  {PeripheralId::TC2, 63u, 47u},
  {PeripheralId::TC2, 64u, 48u},
  {PeripheralId::TC2, 65u, 49u},
  {PeripheralId::TC3, 66u, 50u},
  {PeripheralId::TC3, 67u, 51u},
  {PeripheralId::TC3, 68u, 52u},
  {PeripheralId::TWIHS0, 35u, 19u},
  {PeripheralId::TWIHS1, 36u, 20u},
  {PeripheralId::TWIHS2, 57u, 41u},
  {PeripheralId::UART0, 23u, 7u},
  {PeripheralId::UART1, 24u, 8u},
  {PeripheralId::UART2, 60u, 44u},
  {PeripheralId::UART3, 61u, 45u},
  {PeripheralId::UART4, 62u, 46u},
  {PeripheralId::USART0, 29u, 13u},
  {PeripheralId::USART1, 30u, 14u},
  {PeripheralId::USART2, 31u, 15u},
  {PeripheralId::USBHS, 50u, 34u},
  {PeripheralId::WDT, 20u, 4u},
  {PeripheralId::XDMAC, 74u, 58u},
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
