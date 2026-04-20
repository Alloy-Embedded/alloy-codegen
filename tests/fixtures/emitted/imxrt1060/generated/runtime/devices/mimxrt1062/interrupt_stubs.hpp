#pragma once

#include <array>
#include <cstdint>
#include "interrupts.hpp"
#include "startup.hpp"

extern "C" {
void Default_Handler();
void LPUART1_IRQHandler() __attribute__((weak));
void LPUART3_IRQHandler() __attribute__((weak));
void LPI2C1_IRQHandler() __attribute__((weak));
void LPSPI1_IRQHandler() __attribute__((weak));
}

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
struct InterruptStubDescriptor {
  InterruptId interrupt_id;
  StartupSymbolId symbol_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptStubDescriptor, 4> kInterruptStubs = {{
  {InterruptId::LPUART1, StartupSymbolId::LPUART1_IRQHandler, 20u, 36u},
  {InterruptId::LPUART3, StartupSymbolId::LPUART3_IRQHandler, 22u, 38u},
  {InterruptId::LPI2C1, StartupSymbolId::LPI2C1_IRQHandler, 28u, 44u},
  {InterruptId::LPSPI1, StartupSymbolId::LPSPI1_IRQHandler, 32u, 48u},
}};

template<InterruptId Id>
struct InterruptStubTraits {
  static constexpr bool kPresent = false;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::none;
  static constexpr std::uint16_t kLine = 0xFFFFu;
  static constexpr std::uint16_t kVectorSlot = 0xFFFFu;
};

template<>
struct InterruptStubTraits<InterruptId::LPUART1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::LPUART1_IRQHandler;
  static constexpr std::uint16_t kLine = 20u;
  static constexpr std::uint16_t kVectorSlot = 36u;
};

template<>
struct InterruptStubTraits<InterruptId::LPUART3> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::LPUART3_IRQHandler;
  static constexpr std::uint16_t kLine = 22u;
  static constexpr std::uint16_t kVectorSlot = 38u;
};

template<>
struct InterruptStubTraits<InterruptId::LPI2C1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::LPI2C1_IRQHandler;
  static constexpr std::uint16_t kLine = 28u;
  static constexpr std::uint16_t kVectorSlot = 44u;
};

template<>
struct InterruptStubTraits<InterruptId::LPSPI1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::LPSPI1_IRQHandler;
  static constexpr std::uint16_t kLine = 32u;
  static constexpr std::uint16_t kVectorSlot = 48u;
};

}
}
}
}
}
}
