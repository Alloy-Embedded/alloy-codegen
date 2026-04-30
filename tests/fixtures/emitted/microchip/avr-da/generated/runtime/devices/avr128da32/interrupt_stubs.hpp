#pragma once

#include <array>
#include <cstdint>
#include "interrupts.hpp"
#include "startup.hpp"

extern "C" {
void Default_Handler();
void RESET_IRQHandler() __attribute__((weak));
void NMI_IRQHandler() __attribute__((weak));
void USART0_RXC_IRQHandler() __attribute__((weak));
void USART0_DRE_IRQHandler() __attribute__((weak));
void USART0_TXC_IRQHandler() __attribute__((weak));
void TWI0_TWIS_IRQHandler() __attribute__((weak));
void TWI0_TWIM_IRQHandler() __attribute__((weak));
void SPI0_INT_IRQHandler() __attribute__((weak));
}

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
struct InterruptStubDescriptor {
  InterruptId interrupt_id;
  StartupSymbolId symbol_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptStubDescriptor, 8> kInterruptStubs = {{
  {InterruptId::RESET, StartupSymbolId::RESET_IRQHandler, 0u, 16u},
  {InterruptId::NMI, StartupSymbolId::NMI_IRQHandler, 1u, 17u},
  {InterruptId::USART0_RXC, StartupSymbolId::USART0_RXC_IRQHandler, 18u, 34u},
  {InterruptId::USART0_DRE, StartupSymbolId::USART0_DRE_IRQHandler, 19u, 35u},
  {InterruptId::USART0_TXC, StartupSymbolId::USART0_TXC_IRQHandler, 20u, 36u},
  {InterruptId::TWI0_TWIS, StartupSymbolId::TWI0_TWIS_IRQHandler, 26u, 42u},
  {InterruptId::TWI0_TWIM, StartupSymbolId::TWI0_TWIM_IRQHandler, 27u, 43u},
  {InterruptId::SPI0_INT, StartupSymbolId::SPI0_INT_IRQHandler, 28u, 44u},
}};

template<InterruptId Id>
struct InterruptStubTraits {
  static constexpr bool kPresent = false;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::none;
  static constexpr std::uint16_t kLine = 0xFFFFu;
  static constexpr std::uint16_t kVectorSlot = 0xFFFFu;
};

template<>
struct InterruptStubTraits<InterruptId::RESET> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RESET_IRQHandler;
  static constexpr std::uint16_t kLine = 0u;
  static constexpr std::uint16_t kVectorSlot = 16u;
};

template<>
struct InterruptStubTraits<InterruptId::NMI> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::NMI_IRQHandler;
  static constexpr std::uint16_t kLine = 1u;
  static constexpr std::uint16_t kVectorSlot = 17u;
};

template<>
struct InterruptStubTraits<InterruptId::USART0_RXC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::USART0_RXC_IRQHandler;
  static constexpr std::uint16_t kLine = 18u;
  static constexpr std::uint16_t kVectorSlot = 34u;
};

template<>
struct InterruptStubTraits<InterruptId::USART0_DRE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::USART0_DRE_IRQHandler;
  static constexpr std::uint16_t kLine = 19u;
  static constexpr std::uint16_t kVectorSlot = 35u;
};

template<>
struct InterruptStubTraits<InterruptId::USART0_TXC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::USART0_TXC_IRQHandler;
  static constexpr std::uint16_t kLine = 20u;
  static constexpr std::uint16_t kVectorSlot = 36u;
};

template<>
struct InterruptStubTraits<InterruptId::TWI0_TWIS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TWI0_TWIS_IRQHandler;
  static constexpr std::uint16_t kLine = 26u;
  static constexpr std::uint16_t kVectorSlot = 42u;
};

template<>
struct InterruptStubTraits<InterruptId::TWI0_TWIM> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TWI0_TWIM_IRQHandler;
  static constexpr std::uint16_t kLine = 27u;
  static constexpr std::uint16_t kVectorSlot = 43u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI0_INT> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI0_INT_IRQHandler;
  static constexpr std::uint16_t kLine = 28u;
  static constexpr std::uint16_t kVectorSlot = 44u;
};

}
}
}
}
}
}
