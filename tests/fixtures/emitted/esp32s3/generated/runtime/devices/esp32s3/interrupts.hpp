#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace espressif {
namespace esp32s3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32s3 {
enum class InterruptId : std::uint16_t {
  none,
  APB_ADC,
  ASSIST_DEBUG,
  BACKUP_PMS_VIOLATE,
  BT_BB,
  BT_BB_NMI,
  BT_MAC,
  CACHE_CORE0_ACS,
  CACHE_IA,
  CORE0_DRAM0_PMS,
  CORE0_IRAM0_PMS,
  CORE0_PIF_PMS,
  CORE0_PIF_PMS_SIZE,
  DCACHE_PRELOAD0,
  DCACHE_SYNC0,
  DMA_APBPERI_PMS,
  DMA_EXTMEM_REJECT,
  DMA_IN_CH0,
  DMA_IN_CH1,
  DMA_IN_CH2,
  DMA_IN_CH3,
  DMA_IN_CH4,
  DMA_OUT_CH0,
  DMA_OUT_CH1,
  DMA_OUT_CH2,
  DMA_OUT_CH3,
  DMA_OUT_CH4,
  EFUSE,
  FROM_CPU_INTR0,
  FROM_CPU_INTR1,
  FROM_CPU_INTR2,
  FROM_CPU_INTR3,
  GPIO,
  GPIO_INTR_2,
  GPIO_NMI,
  GPIO_NMI_2,
  I2C_EXT0,
  I2C_EXT1,
  I2C_MASTER,
  I2S0,
  I2S1,
  ICACHE_PRELOAD0,
  ICACHE_SYNC0,
  LCD_CAM,
  LEDC,
  MCPWM0,
  MCPWM1,
  PCNT,
  PERI_BACKUP,
  RMT,
  RSA,
  RTC_CORE,
  RWBLE,
  RWBLE_NMI,
  RWBT,
  RWBT_NMI,
  SDIO_HOST,
  SHA,
  SLC0,
  SLC1,
  SPI1,
  SPI2,
  SPI2_DMA,
  SPI3,
  SPI3_DMA,
  SPI_MEM_REJECT_CACHE,
  SYSTIMER_TARGET0,
  SYSTIMER_TARGET1,
  SYSTIMER_TARGET2,
  TG0_T0_LEVEL,
  TG0_T1_LEVEL,
  TG0_WDT_LEVEL,
  TG1_T0_LEVEL,
  TG1_T1_LEVEL,
  TG1_WDT_LEVEL,
  TIMER1,
  TIMER2,
  TWAI0,
  UART0,
  UART1,
  UART2,
  UHCI0,
  UHCI1,
  USB,
  USB_DEVICE,
  WDT,
  WIFI_BB,
  WIFI_MAC,
  WIFI_NMI,
  WIFI_PWR,
};

struct InterruptDescriptor {
  InterruptId interrupt_id;
  PeripheralId peripheral_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptDescriptor, 28> kInterruptDescriptors = {{
  {InterruptId::APB_ADC, PeripheralId::APB_SARADC, 65u, 81u},
  {InterruptId::DMA_IN_CH0, PeripheralId::DMA, 66u, 82u},
  {InterruptId::DMA_IN_CH1, PeripheralId::DMA, 67u, 83u},
  {InterruptId::DMA_IN_CH2, PeripheralId::DMA, 68u, 84u},
  {InterruptId::DMA_IN_CH3, PeripheralId::DMA, 69u, 85u},
  {InterruptId::DMA_IN_CH4, PeripheralId::DMA, 70u, 86u},
  {InterruptId::DMA_OUT_CH0, PeripheralId::DMA, 71u, 87u},
  {InterruptId::DMA_OUT_CH1, PeripheralId::DMA, 72u, 88u},
  {InterruptId::DMA_OUT_CH2, PeripheralId::DMA, 73u, 89u},
  {InterruptId::DMA_OUT_CH3, PeripheralId::DMA, 74u, 90u},
  {InterruptId::DMA_OUT_CH4, PeripheralId::DMA, 75u, 91u},
  {InterruptId::DMA_APBPERI_PMS, PeripheralId::DMA, 84u, 100u},
  {InterruptId::BACKUP_PMS_VIOLATE, PeripheralId::DMA, 93u, 109u},
  {InterruptId::DMA_EXTMEM_REJECT, PeripheralId::DMA, 98u, 114u},
  {InterruptId::GPIO, PeripheralId::GPIO, 16u, 32u},
  {InterruptId::GPIO_NMI, PeripheralId::GPIO, 17u, 33u},
  {InterruptId::GPIO_INTR_2, PeripheralId::GPIO, 18u, 34u},
  {InterruptId::GPIO_NMI_2, PeripheralId::GPIO, 19u, 35u},
  {InterruptId::SPI_MEM_REJECT_CACHE, PeripheralId::SPI0, 60u, 76u},
  {InterruptId::SPI1, PeripheralId::SPI1, 20u, 36u},
  {InterruptId::SPI2, PeripheralId::SPI2, 21u, 37u},
  {InterruptId::SPI2_DMA, PeripheralId::SPI2, 44u, 60u},
  {InterruptId::SPI3, PeripheralId::SPI3, 22u, 38u},
  {InterruptId::SPI3_DMA, PeripheralId::SPI3, 45u, 61u},
  {InterruptId::UART0, PeripheralId::UART0, 27u, 43u},
  {InterruptId::UART1, PeripheralId::UART1, 28u, 44u},
  {InterruptId::UART2, PeripheralId::UART2, 29u, 45u},
  {InterruptId::USB, PeripheralId::USB0, 38u, 54u},
}};
}
}
}
}
}
}
