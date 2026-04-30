#pragma once

#include <array>
#include <cstdint>
#include "interrupts.hpp"
#include "startup.hpp"

extern "C" {
void Default_Handler();
void DMA1_Stream0_IRQHandler() __attribute__((weak));
void DMA1_Stream5_IRQHandler() __attribute__((weak));
void DMA1_Stream6_IRQHandler() __attribute__((weak));
void USART1_IRQHandler() __attribute__((weak));
void USART2_IRQHandler() __attribute__((weak));
void DMA2_Stream0_IRQHandler() __attribute__((weak));
void OTG_FS_IRQHandler() __attribute__((weak));
}

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f401re {
struct InterruptStubDescriptor {
  InterruptId interrupt_id;
  StartupSymbolId symbol_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptStubDescriptor, 7> kInterruptStubs = {{
  {InterruptId::DMA1_Stream0, StartupSymbolId::DMA1_Stream0_IRQHandler, 11u, 27u},
  {InterruptId::DMA1_Stream5, StartupSymbolId::DMA1_Stream5_IRQHandler, 16u, 32u},
  {InterruptId::DMA1_Stream6, StartupSymbolId::DMA1_Stream6_IRQHandler, 17u, 33u},
  {InterruptId::USART1, StartupSymbolId::USART1_IRQHandler, 37u, 53u},
  {InterruptId::USART2, StartupSymbolId::USART2_IRQHandler, 38u, 54u},
  {InterruptId::DMA2_Stream0, StartupSymbolId::DMA2_Stream0_IRQHandler, 56u, 72u},
  {InterruptId::OTG_FS, StartupSymbolId::OTG_FS_IRQHandler, 67u, 83u},
}};

template<InterruptId Id>
struct InterruptStubTraits {
  static constexpr bool kPresent = false;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::none;
  static constexpr std::uint16_t kLine = 0xFFFFu;
  static constexpr std::uint16_t kVectorSlot = 0xFFFFu;
};

template<>
struct InterruptStubTraits<InterruptId::DMA1_Stream0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA1_Stream0_IRQHandler;
  static constexpr std::uint16_t kLine = 11u;
  static constexpr std::uint16_t kVectorSlot = 27u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA1_Stream5> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA1_Stream5_IRQHandler;
  static constexpr std::uint16_t kLine = 16u;
  static constexpr std::uint16_t kVectorSlot = 32u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA1_Stream6> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA1_Stream6_IRQHandler;
  static constexpr std::uint16_t kLine = 17u;
  static constexpr std::uint16_t kVectorSlot = 33u;
};

template<>
struct InterruptStubTraits<InterruptId::USART1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::USART1_IRQHandler;
  static constexpr std::uint16_t kLine = 37u;
  static constexpr std::uint16_t kVectorSlot = 53u;
};

template<>
struct InterruptStubTraits<InterruptId::USART2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::USART2_IRQHandler;
  static constexpr std::uint16_t kLine = 38u;
  static constexpr std::uint16_t kVectorSlot = 54u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA2_Stream0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA2_Stream0_IRQHandler;
  static constexpr std::uint16_t kLine = 56u;
  static constexpr std::uint16_t kVectorSlot = 72u;
};

template<>
struct InterruptStubTraits<InterruptId::OTG_FS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::OTG_FS_IRQHandler;
  static constexpr std::uint16_t kLine = 67u;
  static constexpr std::uint16_t kVectorSlot = 83u;
};

}
}
}
}
}
}
