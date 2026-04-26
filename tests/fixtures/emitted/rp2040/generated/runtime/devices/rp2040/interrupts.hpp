#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
enum class InterruptId : std::uint16_t {
  none,
  ADC_IRQ_FIFO,
  CLOCKS_IRQ,
  DMA_IRQ_0,
  DMA_IRQ_1,
  I2C0_IRQ,
  I2C1_IRQ,
  IO_IRQ_BANK0,
  PIO0_IRQ_0,
  PIO0_IRQ_1,
  PIO1_IRQ_0,
  PIO1_IRQ_1,
  PWM_IRQ_WRAP,
  RTC_IRQ,
  SPI0_IRQ,
  SPI1_IRQ,
  TIMER_IRQ_0,
  TIMER_IRQ_1,
  TIMER_IRQ_2,
  TIMER_IRQ_3,
  UART0_IRQ,
  UART1_IRQ,
  USBCTRL_IRQ,
};

struct InterruptDescriptor {
  InterruptId interrupt_id;
  PeripheralId peripheral_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptDescriptor, 13> kInterruptDescriptors = {{
  {InterruptId::ADC_IRQ_FIFO, PeripheralId::ADC, 22u, 38u},
  {InterruptId::DMA_IRQ_0, PeripheralId::DMA, 11u, 27u},
  {InterruptId::DMA_IRQ_1, PeripheralId::DMA, 12u, 28u},
  {InterruptId::PWM_IRQ_WRAP, PeripheralId::PWM, 4u, 20u},
  {InterruptId::RTC_IRQ, PeripheralId::RTC, 25u, 41u},
  {InterruptId::SPI0_IRQ, PeripheralId::SPI0, 18u, 34u},
  {InterruptId::SPI1_IRQ, PeripheralId::SPI1, 19u, 35u},
  {InterruptId::TIMER_IRQ_0, PeripheralId::TIMER, 0u, 16u},
  {InterruptId::TIMER_IRQ_1, PeripheralId::TIMER, 1u, 17u},
  {InterruptId::TIMER_IRQ_2, PeripheralId::TIMER, 2u, 18u},
  {InterruptId::TIMER_IRQ_3, PeripheralId::TIMER, 3u, 19u},
  {InterruptId::UART0_IRQ, PeripheralId::UART0, 20u, 36u},
  {InterruptId::UART1_IRQ, PeripheralId::UART1, 21u, 37u},
}};
}
}
}
}
}
}
