#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace espressif {
namespace esp32 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32 {
enum class InterruptId : std::uint16_t {
  none,
  BT_BB,
  BT_BB_NMI,
  BT_MAC,
  CACHE_IA,
  EFUSE,
  ETH_MAC,
  FROM_CPU_INTR0,
  FROM_CPU_INTR1,
  FROM_CPU_INTR2,
  FROM_CPU_INTR3,
  GPIO,
  GPIO_NMI,
  I2C_EXT0,
  I2C_EXT1,
  I2S0,
  I2S1,
  LEDC,
  MCPWM0,
  MCPWM1,
  MCPWM2,
  MCPWM3,
  MMU_IA,
  MPU_IA,
  PCNT,
  RMT,
  RSA,
  RTC_CORE,
  RWBLE,
  RWBLE_NMI,
  RWBT,
  RWBT_NMI,
  SDIO_HOST,
  SPI0,
  SPI1,
  SPI1_DMA,
  SPI2,
  SPI2_DMA,
  SPI3,
  SPI3_DMA,
  TG0_LACT_EDGE,
  TG0_LACT_LEVEL,
  TG0_T0_EDGE,
  TG0_T0_LEVEL,
  TG0_T1_EDGE,
  TG0_T1_LEVEL,
  TG0_WDT_EDGE,
  TG0_WDT_LEVEL,
  TG1_LACT_EDGE,
  TG1_LACT_LEVEL,
  TG1_T0_EDGE,
  TG1_T0_LEVEL,
  TG1_T1_EDGE,
  TG1_T1_LEVEL,
  TG1_WDT_EDGE,
  TG1_WDT_LEVEL,
  TIMER1,
  TIMER2,
  TWAI0,
  UART0,
  UART1,
  UART2,
  UHCI0,
  UHCI1,
  WDT,
  WIFI_BB,
  WIFI_MAC,
  WIFI_NMI,
};

struct InterruptDescriptor {
  InterruptId interrupt_id;
  PeripheralId peripheral_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptDescriptor, 14> kInterruptDescriptors = {{
  {InterruptId::GPIO, PeripheralId::GPIO, 22u, 38u},
  {InterruptId::GPIO_NMI, PeripheralId::GPIO, 23u, 39u},
  {InterruptId::I2C_EXT0, PeripheralId::I2C0, 49u, 65u},
  {InterruptId::I2C_EXT1, PeripheralId::I2C1, 50u, 66u},
  {InterruptId::SPI0, PeripheralId::SPI0, 28u, 44u},
  {InterruptId::SPI1, PeripheralId::SPI1, 29u, 45u},
  {InterruptId::SPI1_DMA, PeripheralId::SPI1, 52u, 68u},
  {InterruptId::SPI2, PeripheralId::SPI2, 30u, 46u},
  {InterruptId::SPI2_DMA, PeripheralId::SPI2, 53u, 69u},
  {InterruptId::SPI3, PeripheralId::SPI3, 31u, 47u},
  {InterruptId::SPI3_DMA, PeripheralId::SPI3, 54u, 70u},
  {InterruptId::UART0, PeripheralId::UART0, 34u, 50u},
  {InterruptId::UART1, PeripheralId::UART1, 35u, 51u},
  {InterruptId::UART2, PeripheralId::UART2, 36u, 52u},
}};
}
}
}
}
}
}
