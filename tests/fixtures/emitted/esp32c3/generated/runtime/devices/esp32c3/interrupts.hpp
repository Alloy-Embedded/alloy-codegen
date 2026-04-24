#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace espressif {
namespace esp32c3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32c3 {
enum class InterruptId : std::uint16_t {
  none,
  AES,
  APB_ADC,
  APB_CTRL,
  ASSIST_DEBUG,
  BAK_PMS_VIOLATE,
  BT_BB,
  BT_BB_NMI,
  BT_MAC,
  CACHE_CORE0_ACS,
  CACHE_IA,
  CORE0_DRAM0_PMS,
  CORE0_IRAM0_PMS,
  CORE0_PIF_PMS,
  CORE0_PIF_PMS_SIZE,
  DMA_APBPERI_PMS,
  DMA_CH0,
  DMA_CH1,
  DMA_CH2,
  EFUSE,
  FROM_CPU_INTR0,
  FROM_CPU_INTR1,
  FROM_CPU_INTR2,
  FROM_CPU_INTR3,
  GPIO,
  GPIO_NMI,
  I2C_EXT0,
  I2C_MASTER,
  I2S0,
  ICACHE_PRELOAD0,
  ICACHE_SYNC0,
  LEDC,
  RMT,
  RSA,
  RTC_CORE,
  RWBLE,
  RWBLE_NMI,
  RWBT,
  RWBT_NMI,
  SHA,
  SLC0,
  SLC1,
  SPI1,
  SPI2,
  SPI_MEM_REJECT_CACHE,
  SYSTIMER_TARGET0,
  SYSTIMER_TARGET1,
  SYSTIMER_TARGET2,
  TG0_T0_LEVEL,
  TG0_WDT_LEVEL,
  TG1_T0_LEVEL,
  TG1_WDT_LEVEL,
  TIMER1,
  TIMER2,
  TWAI0,
  UART0,
  UART1,
  UHCI0,
  USB_DEVICE,
  WIFI_BB,
  WIFI_MAC,
  WIFI_MAC_NMI,
  WIFI_PWR,
};

struct InterruptDescriptor {
  InterruptId interrupt_id;
  PeripheralId peripheral_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptDescriptor, 12> kInterruptDescriptors = {{
  {InterruptId::APB_ADC, PeripheralId::APB_SARADC, 43u, 59u},
  {InterruptId::DMA_CH0, PeripheralId::DMA, 44u, 60u},
  {InterruptId::DMA_CH1, PeripheralId::DMA, 45u, 61u},
  {InterruptId::DMA_CH2, PeripheralId::DMA, 46u, 62u},
  {InterruptId::DMA_APBPERI_PMS, PeripheralId::DMA, 55u, 71u},
  {InterruptId::GPIO, PeripheralId::GPIO, 16u, 32u},
  {InterruptId::GPIO_NMI, PeripheralId::GPIO, 17u, 33u},
  {InterruptId::SPI_MEM_REJECT_CACHE, PeripheralId::SPI0, 40u, 56u},
  {InterruptId::SPI1, PeripheralId::SPI1, 18u, 34u},
  {InterruptId::SPI2, PeripheralId::SPI2, 19u, 35u},
  {InterruptId::UART0, PeripheralId::UART0, 21u, 37u},
  {InterruptId::UART1, PeripheralId::UART1, 22u, 38u},
}};
}
}
}
}
}
}
