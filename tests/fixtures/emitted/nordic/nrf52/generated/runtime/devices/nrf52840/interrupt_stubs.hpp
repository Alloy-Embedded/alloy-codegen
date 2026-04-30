#pragma once

#include <array>
#include <cstdint>
#include "interrupts.hpp"
#include "startup.hpp"

extern "C" {
void Default_Handler();
void UART0_IRQ_IRQHandler() __attribute__((weak));
void I2C0_IRQ_IRQHandler() __attribute__((weak));
void TIMER0_IRQ_IRQHandler() __attribute__((weak));
void RTC0_IRQ_IRQHandler() __attribute__((weak));
void WDT0_IRQ_IRQHandler() __attribute__((weak));
}

namespace nordic {
namespace nrf52 {
namespace generated {
namespace runtime {
namespace devices {
namespace nrf52840 {
struct InterruptStubDescriptor {
  InterruptId interrupt_id;
  StartupSymbolId symbol_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptStubDescriptor, 5> kInterruptStubs = {{
  {InterruptId::UART0_IRQ, StartupSymbolId::UART0_IRQ_IRQHandler, 2u, 18u},
  {InterruptId::I2C0_IRQ, StartupSymbolId::I2C0_IRQ_IRQHandler, 3u, 19u},
  {InterruptId::TIMER0_IRQ, StartupSymbolId::TIMER0_IRQ_IRQHandler, 8u, 24u},
  {InterruptId::RTC0_IRQ, StartupSymbolId::RTC0_IRQ_IRQHandler, 11u, 27u},
  {InterruptId::WDT0_IRQ, StartupSymbolId::WDT0_IRQ_IRQHandler, 16u, 32u},
}};

template<InterruptId Id>
struct InterruptStubTraits {
  static constexpr bool kPresent = false;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::none;
  static constexpr std::uint16_t kLine = 0xFFFFu;
  static constexpr std::uint16_t kVectorSlot = 0xFFFFu;
};

template<>
struct InterruptStubTraits<InterruptId::UART0_IRQ> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UART0_IRQ_IRQHandler;
  static constexpr std::uint16_t kLine = 2u;
  static constexpr std::uint16_t kVectorSlot = 18u;
};

template<>
struct InterruptStubTraits<InterruptId::I2C0_IRQ> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::I2C0_IRQ_IRQHandler;
  static constexpr std::uint16_t kLine = 3u;
  static constexpr std::uint16_t kVectorSlot = 19u;
};

template<>
struct InterruptStubTraits<InterruptId::TIMER0_IRQ> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TIMER0_IRQ_IRQHandler;
  static constexpr std::uint16_t kLine = 8u;
  static constexpr std::uint16_t kVectorSlot = 24u;
};

template<>
struct InterruptStubTraits<InterruptId::RTC0_IRQ> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RTC0_IRQ_IRQHandler;
  static constexpr std::uint16_t kLine = 11u;
  static constexpr std::uint16_t kVectorSlot = 27u;
};

template<>
struct InterruptStubTraits<InterruptId::WDT0_IRQ> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::WDT0_IRQ_IRQHandler;
  static constexpr std::uint16_t kLine = 16u;
  static constexpr std::uint16_t kVectorSlot = 32u;
};

}
}
}
}
}
}
