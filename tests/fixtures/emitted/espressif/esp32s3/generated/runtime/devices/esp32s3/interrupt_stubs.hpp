#pragma once

#include <array>
#include <cstdint>
#include "interrupts.hpp"
#include "startup.hpp"

extern "C" {
void Default_Handler();
void WIFI_MAC_IRQHandler() __attribute__((weak));
void WIFI_NMI_IRQHandler() __attribute__((weak));
void WIFI_PWR_IRQHandler() __attribute__((weak));
void WIFI_BB_IRQHandler() __attribute__((weak));
void BT_MAC_IRQHandler() __attribute__((weak));
void BT_BB_IRQHandler() __attribute__((weak));
void BT_BB_NMI_IRQHandler() __attribute__((weak));
void RWBT_IRQHandler() __attribute__((weak));
void RWBLE_IRQHandler() __attribute__((weak));
void RWBT_NMI_IRQHandler() __attribute__((weak));
void RWBLE_NMI_IRQHandler() __attribute__((weak));
void I2C_MASTER_IRQHandler() __attribute__((weak));
void SLC0_IRQHandler() __attribute__((weak));
void SLC1_IRQHandler() __attribute__((weak));
void UHCI0_IRQHandler() __attribute__((weak));
void UHCI1_IRQHandler() __attribute__((weak));
void GPIO_IRQHandler() __attribute__((weak));
void GPIO_NMI_IRQHandler() __attribute__((weak));
void GPIO_INTR_2_IRQHandler() __attribute__((weak));
void GPIO_NMI_2_IRQHandler() __attribute__((weak));
void SPI1_IRQHandler() __attribute__((weak));
void SPI2_IRQHandler() __attribute__((weak));
void SPI3_IRQHandler() __attribute__((weak));
void LCD_CAM_IRQHandler() __attribute__((weak));
void I2S0_IRQHandler() __attribute__((weak));
void I2S1_IRQHandler() __attribute__((weak));
void UART0_IRQHandler() __attribute__((weak));
void UART1_IRQHandler() __attribute__((weak));
void UART2_IRQHandler() __attribute__((weak));
void SDIO_HOST_IRQHandler() __attribute__((weak));
void MCPWM0_IRQHandler() __attribute__((weak));
void MCPWM1_IRQHandler() __attribute__((weak));
void LEDC_IRQHandler() __attribute__((weak));
void EFUSE_IRQHandler() __attribute__((weak));
void TWAI0_IRQHandler() __attribute__((weak));
void USB_IRQHandler() __attribute__((weak));
void RTC_CORE_IRQHandler() __attribute__((weak));
void RMT_IRQHandler() __attribute__((weak));
void PCNT_IRQHandler() __attribute__((weak));
void I2C_EXT0_IRQHandler() __attribute__((weak));
void I2C_EXT1_IRQHandler() __attribute__((weak));
void SPI2_DMA_IRQHandler() __attribute__((weak));
void SPI3_DMA_IRQHandler() __attribute__((weak));
void WDT_IRQHandler() __attribute__((weak));
void TIMER1_IRQHandler() __attribute__((weak));
void TIMER2_IRQHandler() __attribute__((weak));
void TG0_T0_LEVEL_IRQHandler() __attribute__((weak));
void TG0_T1_LEVEL_IRQHandler() __attribute__((weak));
void TG0_WDT_LEVEL_IRQHandler() __attribute__((weak));
void TG1_T0_LEVEL_IRQHandler() __attribute__((weak));
void TG1_T1_LEVEL_IRQHandler() __attribute__((weak));
void TG1_WDT_LEVEL_IRQHandler() __attribute__((weak));
void CACHE_IA_IRQHandler() __attribute__((weak));
void SYSTIMER_TARGET0_IRQHandler() __attribute__((weak));
void SYSTIMER_TARGET1_IRQHandler() __attribute__((weak));
void SYSTIMER_TARGET2_IRQHandler() __attribute__((weak));
void SPI_MEM_REJECT_CACHE_IRQHandler() __attribute__((weak));
void DCACHE_PRELOAD0_IRQHandler() __attribute__((weak));
void ICACHE_PRELOAD0_IRQHandler() __attribute__((weak));
void DCACHE_SYNC0_IRQHandler() __attribute__((weak));
void ICACHE_SYNC0_IRQHandler() __attribute__((weak));
void APB_ADC_IRQHandler() __attribute__((weak));
void DMA_IN_CH0_IRQHandler() __attribute__((weak));
void DMA_IN_CH1_IRQHandler() __attribute__((weak));
void DMA_IN_CH2_IRQHandler() __attribute__((weak));
void DMA_IN_CH3_IRQHandler() __attribute__((weak));
void DMA_IN_CH4_IRQHandler() __attribute__((weak));
void DMA_OUT_CH0_IRQHandler() __attribute__((weak));
void DMA_OUT_CH1_IRQHandler() __attribute__((weak));
void DMA_OUT_CH2_IRQHandler() __attribute__((weak));
void DMA_OUT_CH3_IRQHandler() __attribute__((weak));
void DMA_OUT_CH4_IRQHandler() __attribute__((weak));
void RSA_IRQHandler() __attribute__((weak));
void SHA_IRQHandler() __attribute__((weak));
void FROM_CPU_INTR0_IRQHandler() __attribute__((weak));
void FROM_CPU_INTR1_IRQHandler() __attribute__((weak));
void FROM_CPU_INTR2_IRQHandler() __attribute__((weak));
void FROM_CPU_INTR3_IRQHandler() __attribute__((weak));
void ASSIST_DEBUG_IRQHandler() __attribute__((weak));
void DMA_APBPERI_PMS_IRQHandler() __attribute__((weak));
void CORE0_IRAM0_PMS_IRQHandler() __attribute__((weak));
void CORE0_DRAM0_PMS_IRQHandler() __attribute__((weak));
void CORE0_PIF_PMS_IRQHandler() __attribute__((weak));
void CORE0_PIF_PMS_SIZE_IRQHandler() __attribute__((weak));
void CORE1_IRAM0_PMS_IRQHandler() __attribute__((weak));
void CORE1_DRAM0_PMS_IRQHandler() __attribute__((weak));
void CORE1_PIF_PMS_IRQHandler() __attribute__((weak));
void CORE1_PIF_PMS_SIZE_IRQHandler() __attribute__((weak));
void BACKUP_PMS_VIOLATE_IRQHandler() __attribute__((weak));
void CACHE_CORE0_ACS_IRQHandler() __attribute__((weak));
void CACHE_CORE1_ACS_IRQHandler() __attribute__((weak));
void USB_DEVICE_IRQHandler() __attribute__((weak));
void PERI_BACKUP_IRQHandler() __attribute__((weak));
void DMA_EXTMEM_REJECT_IRQHandler() __attribute__((weak));
}

namespace espressif {
namespace esp32s3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32s3 {
struct InterruptStubDescriptor {
  InterruptId interrupt_id;
  StartupSymbolId symbol_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptStubDescriptor, 94> kInterruptStubs = {{
  {InterruptId::WIFI_MAC, StartupSymbolId::WIFI_MAC_IRQHandler, 0u, 16u},
  {InterruptId::WIFI_NMI, StartupSymbolId::WIFI_NMI_IRQHandler, 1u, 17u},
  {InterruptId::WIFI_PWR, StartupSymbolId::WIFI_PWR_IRQHandler, 2u, 18u},
  {InterruptId::WIFI_BB, StartupSymbolId::WIFI_BB_IRQHandler, 3u, 19u},
  {InterruptId::BT_MAC, StartupSymbolId::BT_MAC_IRQHandler, 4u, 20u},
  {InterruptId::BT_BB, StartupSymbolId::BT_BB_IRQHandler, 5u, 21u},
  {InterruptId::BT_BB_NMI, StartupSymbolId::BT_BB_NMI_IRQHandler, 6u, 22u},
  {InterruptId::RWBT, StartupSymbolId::RWBT_IRQHandler, 7u, 23u},
  {InterruptId::RWBLE, StartupSymbolId::RWBLE_IRQHandler, 8u, 24u},
  {InterruptId::RWBT_NMI, StartupSymbolId::RWBT_NMI_IRQHandler, 9u, 25u},
  {InterruptId::RWBLE_NMI, StartupSymbolId::RWBLE_NMI_IRQHandler, 10u, 26u},
  {InterruptId::I2C_MASTER, StartupSymbolId::I2C_MASTER_IRQHandler, 11u, 27u},
  {InterruptId::SLC0, StartupSymbolId::SLC0_IRQHandler, 12u, 28u},
  {InterruptId::SLC1, StartupSymbolId::SLC1_IRQHandler, 13u, 29u},
  {InterruptId::UHCI0, StartupSymbolId::UHCI0_IRQHandler, 14u, 30u},
  {InterruptId::UHCI1, StartupSymbolId::UHCI1_IRQHandler, 15u, 31u},
  {InterruptId::GPIO, StartupSymbolId::GPIO_IRQHandler, 16u, 32u},
  {InterruptId::GPIO_NMI, StartupSymbolId::GPIO_NMI_IRQHandler, 17u, 33u},
  {InterruptId::GPIO_INTR_2, StartupSymbolId::GPIO_INTR_2_IRQHandler, 18u, 34u},
  {InterruptId::GPIO_NMI_2, StartupSymbolId::GPIO_NMI_2_IRQHandler, 19u, 35u},
  {InterruptId::SPI1, StartupSymbolId::SPI1_IRQHandler, 20u, 36u},
  {InterruptId::SPI2, StartupSymbolId::SPI2_IRQHandler, 21u, 37u},
  {InterruptId::SPI3, StartupSymbolId::SPI3_IRQHandler, 22u, 38u},
  {InterruptId::LCD_CAM, StartupSymbolId::LCD_CAM_IRQHandler, 24u, 40u},
  {InterruptId::I2S0, StartupSymbolId::I2S0_IRQHandler, 25u, 41u},
  {InterruptId::I2S1, StartupSymbolId::I2S1_IRQHandler, 26u, 42u},
  {InterruptId::UART0, StartupSymbolId::UART0_IRQHandler, 27u, 43u},
  {InterruptId::UART1, StartupSymbolId::UART1_IRQHandler, 28u, 44u},
  {InterruptId::UART2, StartupSymbolId::UART2_IRQHandler, 29u, 45u},
  {InterruptId::SDIO_HOST, StartupSymbolId::SDIO_HOST_IRQHandler, 30u, 46u},
  {InterruptId::MCPWM0, StartupSymbolId::MCPWM0_IRQHandler, 31u, 47u},
  {InterruptId::MCPWM1, StartupSymbolId::MCPWM1_IRQHandler, 32u, 48u},
  {InterruptId::LEDC, StartupSymbolId::LEDC_IRQHandler, 35u, 51u},
  {InterruptId::EFUSE, StartupSymbolId::EFUSE_IRQHandler, 36u, 52u},
  {InterruptId::TWAI0, StartupSymbolId::TWAI0_IRQHandler, 37u, 53u},
  {InterruptId::USB, StartupSymbolId::USB_IRQHandler, 38u, 54u},
  {InterruptId::RTC_CORE, StartupSymbolId::RTC_CORE_IRQHandler, 39u, 55u},
  {InterruptId::RMT, StartupSymbolId::RMT_IRQHandler, 40u, 56u},
  {InterruptId::PCNT, StartupSymbolId::PCNT_IRQHandler, 41u, 57u},
  {InterruptId::I2C_EXT0, StartupSymbolId::I2C_EXT0_IRQHandler, 42u, 58u},
  {InterruptId::I2C_EXT1, StartupSymbolId::I2C_EXT1_IRQHandler, 43u, 59u},
  {InterruptId::SPI2_DMA, StartupSymbolId::SPI2_DMA_IRQHandler, 44u, 60u},
  {InterruptId::SPI3_DMA, StartupSymbolId::SPI3_DMA_IRQHandler, 45u, 61u},
  {InterruptId::WDT, StartupSymbolId::WDT_IRQHandler, 47u, 63u},
  {InterruptId::TIMER1, StartupSymbolId::TIMER1_IRQHandler, 48u, 64u},
  {InterruptId::TIMER2, StartupSymbolId::TIMER2_IRQHandler, 49u, 65u},
  {InterruptId::TG0_T0_LEVEL, StartupSymbolId::TG0_T0_LEVEL_IRQHandler, 50u, 66u},
  {InterruptId::TG0_T1_LEVEL, StartupSymbolId::TG0_T1_LEVEL_IRQHandler, 51u, 67u},
  {InterruptId::TG0_WDT_LEVEL, StartupSymbolId::TG0_WDT_LEVEL_IRQHandler, 52u, 68u},
  {InterruptId::TG1_T0_LEVEL, StartupSymbolId::TG1_T0_LEVEL_IRQHandler, 53u, 69u},
  {InterruptId::TG1_T1_LEVEL, StartupSymbolId::TG1_T1_LEVEL_IRQHandler, 54u, 70u},
  {InterruptId::TG1_WDT_LEVEL, StartupSymbolId::TG1_WDT_LEVEL_IRQHandler, 55u, 71u},
  {InterruptId::CACHE_IA, StartupSymbolId::CACHE_IA_IRQHandler, 56u, 72u},
  {InterruptId::SYSTIMER_TARGET0, StartupSymbolId::SYSTIMER_TARGET0_IRQHandler, 57u, 73u},
  {InterruptId::SYSTIMER_TARGET1, StartupSymbolId::SYSTIMER_TARGET1_IRQHandler, 58u, 74u},
  {InterruptId::SYSTIMER_TARGET2, StartupSymbolId::SYSTIMER_TARGET2_IRQHandler, 59u, 75u},
  {InterruptId::SPI_MEM_REJECT_CACHE, StartupSymbolId::SPI_MEM_REJECT_CACHE_IRQHandler, 60u, 76u},
  {InterruptId::DCACHE_PRELOAD0, StartupSymbolId::DCACHE_PRELOAD0_IRQHandler, 61u, 77u},
  {InterruptId::ICACHE_PRELOAD0, StartupSymbolId::ICACHE_PRELOAD0_IRQHandler, 62u, 78u},
  {InterruptId::DCACHE_SYNC0, StartupSymbolId::DCACHE_SYNC0_IRQHandler, 63u, 79u},
  {InterruptId::ICACHE_SYNC0, StartupSymbolId::ICACHE_SYNC0_IRQHandler, 64u, 80u},
  {InterruptId::APB_ADC, StartupSymbolId::APB_ADC_IRQHandler, 65u, 81u},
  {InterruptId::DMA_IN_CH0, StartupSymbolId::DMA_IN_CH0_IRQHandler, 66u, 82u},
  {InterruptId::DMA_IN_CH1, StartupSymbolId::DMA_IN_CH1_IRQHandler, 67u, 83u},
  {InterruptId::DMA_IN_CH2, StartupSymbolId::DMA_IN_CH2_IRQHandler, 68u, 84u},
  {InterruptId::DMA_IN_CH3, StartupSymbolId::DMA_IN_CH3_IRQHandler, 69u, 85u},
  {InterruptId::DMA_IN_CH4, StartupSymbolId::DMA_IN_CH4_IRQHandler, 70u, 86u},
  {InterruptId::DMA_OUT_CH0, StartupSymbolId::DMA_OUT_CH0_IRQHandler, 71u, 87u},
  {InterruptId::DMA_OUT_CH1, StartupSymbolId::DMA_OUT_CH1_IRQHandler, 72u, 88u},
  {InterruptId::DMA_OUT_CH2, StartupSymbolId::DMA_OUT_CH2_IRQHandler, 73u, 89u},
  {InterruptId::DMA_OUT_CH3, StartupSymbolId::DMA_OUT_CH3_IRQHandler, 74u, 90u},
  {InterruptId::DMA_OUT_CH4, StartupSymbolId::DMA_OUT_CH4_IRQHandler, 75u, 91u},
  {InterruptId::RSA, StartupSymbolId::RSA_IRQHandler, 76u, 92u},
  {InterruptId::SHA, StartupSymbolId::SHA_IRQHandler, 77u, 93u},
  {InterruptId::FROM_CPU_INTR0, StartupSymbolId::FROM_CPU_INTR0_IRQHandler, 79u, 95u},
  {InterruptId::FROM_CPU_INTR1, StartupSymbolId::FROM_CPU_INTR1_IRQHandler, 80u, 96u},
  {InterruptId::FROM_CPU_INTR2, StartupSymbolId::FROM_CPU_INTR2_IRQHandler, 81u, 97u},
  {InterruptId::FROM_CPU_INTR3, StartupSymbolId::FROM_CPU_INTR3_IRQHandler, 82u, 98u},
  {InterruptId::ASSIST_DEBUG, StartupSymbolId::ASSIST_DEBUG_IRQHandler, 83u, 99u},
  {InterruptId::DMA_APBPERI_PMS, StartupSymbolId::DMA_APBPERI_PMS_IRQHandler, 84u, 100u},
  {InterruptId::CORE0_IRAM0_PMS, StartupSymbolId::CORE0_IRAM0_PMS_IRQHandler, 85u, 101u},
  {InterruptId::CORE0_DRAM0_PMS, StartupSymbolId::CORE0_DRAM0_PMS_IRQHandler, 86u, 102u},
  {InterruptId::CORE0_PIF_PMS, StartupSymbolId::CORE0_PIF_PMS_IRQHandler, 87u, 103u},
  {InterruptId::CORE0_PIF_PMS_SIZE, StartupSymbolId::CORE0_PIF_PMS_SIZE_IRQHandler, 88u, 104u},
  {InterruptId::CORE1_IRAM0_PMS, StartupSymbolId::CORE1_IRAM0_PMS_IRQHandler, 89u, 105u},
  {InterruptId::CORE1_DRAM0_PMS, StartupSymbolId::CORE1_DRAM0_PMS_IRQHandler, 90u, 106u},
  {InterruptId::CORE1_PIF_PMS, StartupSymbolId::CORE1_PIF_PMS_IRQHandler, 91u, 107u},
  {InterruptId::CORE1_PIF_PMS_SIZE, StartupSymbolId::CORE1_PIF_PMS_SIZE_IRQHandler, 92u, 108u},
  {InterruptId::BACKUP_PMS_VIOLATE, StartupSymbolId::BACKUP_PMS_VIOLATE_IRQHandler, 93u, 109u},
  {InterruptId::CACHE_CORE0_ACS, StartupSymbolId::CACHE_CORE0_ACS_IRQHandler, 94u, 110u},
  {InterruptId::CACHE_CORE1_ACS, StartupSymbolId::CACHE_CORE1_ACS_IRQHandler, 95u, 111u},
  {InterruptId::USB_DEVICE, StartupSymbolId::USB_DEVICE_IRQHandler, 96u, 112u},
  {InterruptId::PERI_BACKUP, StartupSymbolId::PERI_BACKUP_IRQHandler, 97u, 113u},
  {InterruptId::DMA_EXTMEM_REJECT, StartupSymbolId::DMA_EXTMEM_REJECT_IRQHandler, 98u, 114u},
}};

template<InterruptId Id>
struct InterruptStubTraits {
  static constexpr bool kPresent = false;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::none;
  static constexpr std::uint16_t kLine = 0xFFFFu;
  static constexpr std::uint16_t kVectorSlot = 0xFFFFu;
};

template<>
struct InterruptStubTraits<InterruptId::WIFI_MAC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::WIFI_MAC_IRQHandler;
  static constexpr std::uint16_t kLine = 0u;
  static constexpr std::uint16_t kVectorSlot = 16u;
};

template<>
struct InterruptStubTraits<InterruptId::WIFI_NMI> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::WIFI_NMI_IRQHandler;
  static constexpr std::uint16_t kLine = 1u;
  static constexpr std::uint16_t kVectorSlot = 17u;
};

template<>
struct InterruptStubTraits<InterruptId::WIFI_PWR> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::WIFI_PWR_IRQHandler;
  static constexpr std::uint16_t kLine = 2u;
  static constexpr std::uint16_t kVectorSlot = 18u;
};

template<>
struct InterruptStubTraits<InterruptId::WIFI_BB> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::WIFI_BB_IRQHandler;
  static constexpr std::uint16_t kLine = 3u;
  static constexpr std::uint16_t kVectorSlot = 19u;
};

template<>
struct InterruptStubTraits<InterruptId::BT_MAC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::BT_MAC_IRQHandler;
  static constexpr std::uint16_t kLine = 4u;
  static constexpr std::uint16_t kVectorSlot = 20u;
};

template<>
struct InterruptStubTraits<InterruptId::BT_BB> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::BT_BB_IRQHandler;
  static constexpr std::uint16_t kLine = 5u;
  static constexpr std::uint16_t kVectorSlot = 21u;
};

template<>
struct InterruptStubTraits<InterruptId::BT_BB_NMI> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::BT_BB_NMI_IRQHandler;
  static constexpr std::uint16_t kLine = 6u;
  static constexpr std::uint16_t kVectorSlot = 22u;
};

template<>
struct InterruptStubTraits<InterruptId::RWBT> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RWBT_IRQHandler;
  static constexpr std::uint16_t kLine = 7u;
  static constexpr std::uint16_t kVectorSlot = 23u;
};

template<>
struct InterruptStubTraits<InterruptId::RWBLE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RWBLE_IRQHandler;
  static constexpr std::uint16_t kLine = 8u;
  static constexpr std::uint16_t kVectorSlot = 24u;
};

template<>
struct InterruptStubTraits<InterruptId::RWBT_NMI> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RWBT_NMI_IRQHandler;
  static constexpr std::uint16_t kLine = 9u;
  static constexpr std::uint16_t kVectorSlot = 25u;
};

template<>
struct InterruptStubTraits<InterruptId::RWBLE_NMI> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RWBLE_NMI_IRQHandler;
  static constexpr std::uint16_t kLine = 10u;
  static constexpr std::uint16_t kVectorSlot = 26u;
};

template<>
struct InterruptStubTraits<InterruptId::I2C_MASTER> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::I2C_MASTER_IRQHandler;
  static constexpr std::uint16_t kLine = 11u;
  static constexpr std::uint16_t kVectorSlot = 27u;
};

template<>
struct InterruptStubTraits<InterruptId::SLC0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SLC0_IRQHandler;
  static constexpr std::uint16_t kLine = 12u;
  static constexpr std::uint16_t kVectorSlot = 28u;
};

template<>
struct InterruptStubTraits<InterruptId::SLC1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SLC1_IRQHandler;
  static constexpr std::uint16_t kLine = 13u;
  static constexpr std::uint16_t kVectorSlot = 29u;
};

template<>
struct InterruptStubTraits<InterruptId::UHCI0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UHCI0_IRQHandler;
  static constexpr std::uint16_t kLine = 14u;
  static constexpr std::uint16_t kVectorSlot = 30u;
};

template<>
struct InterruptStubTraits<InterruptId::UHCI1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UHCI1_IRQHandler;
  static constexpr std::uint16_t kLine = 15u;
  static constexpr std::uint16_t kVectorSlot = 31u;
};

template<>
struct InterruptStubTraits<InterruptId::GPIO> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::GPIO_IRQHandler;
  static constexpr std::uint16_t kLine = 16u;
  static constexpr std::uint16_t kVectorSlot = 32u;
};

template<>
struct InterruptStubTraits<InterruptId::GPIO_NMI> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::GPIO_NMI_IRQHandler;
  static constexpr std::uint16_t kLine = 17u;
  static constexpr std::uint16_t kVectorSlot = 33u;
};

template<>
struct InterruptStubTraits<InterruptId::GPIO_INTR_2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::GPIO_INTR_2_IRQHandler;
  static constexpr std::uint16_t kLine = 18u;
  static constexpr std::uint16_t kVectorSlot = 34u;
};

template<>
struct InterruptStubTraits<InterruptId::GPIO_NMI_2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::GPIO_NMI_2_IRQHandler;
  static constexpr std::uint16_t kLine = 19u;
  static constexpr std::uint16_t kVectorSlot = 35u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI1_IRQHandler;
  static constexpr std::uint16_t kLine = 20u;
  static constexpr std::uint16_t kVectorSlot = 36u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI2_IRQHandler;
  static constexpr std::uint16_t kLine = 21u;
  static constexpr std::uint16_t kVectorSlot = 37u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI3> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI3_IRQHandler;
  static constexpr std::uint16_t kLine = 22u;
  static constexpr std::uint16_t kVectorSlot = 38u;
};

template<>
struct InterruptStubTraits<InterruptId::LCD_CAM> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::LCD_CAM_IRQHandler;
  static constexpr std::uint16_t kLine = 24u;
  static constexpr std::uint16_t kVectorSlot = 40u;
};

template<>
struct InterruptStubTraits<InterruptId::I2S0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::I2S0_IRQHandler;
  static constexpr std::uint16_t kLine = 25u;
  static constexpr std::uint16_t kVectorSlot = 41u;
};

template<>
struct InterruptStubTraits<InterruptId::I2S1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::I2S1_IRQHandler;
  static constexpr std::uint16_t kLine = 26u;
  static constexpr std::uint16_t kVectorSlot = 42u;
};

template<>
struct InterruptStubTraits<InterruptId::UART0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UART0_IRQHandler;
  static constexpr std::uint16_t kLine = 27u;
  static constexpr std::uint16_t kVectorSlot = 43u;
};

template<>
struct InterruptStubTraits<InterruptId::UART1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UART1_IRQHandler;
  static constexpr std::uint16_t kLine = 28u;
  static constexpr std::uint16_t kVectorSlot = 44u;
};

template<>
struct InterruptStubTraits<InterruptId::UART2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UART2_IRQHandler;
  static constexpr std::uint16_t kLine = 29u;
  static constexpr std::uint16_t kVectorSlot = 45u;
};

template<>
struct InterruptStubTraits<InterruptId::SDIO_HOST> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SDIO_HOST_IRQHandler;
  static constexpr std::uint16_t kLine = 30u;
  static constexpr std::uint16_t kVectorSlot = 46u;
};

template<>
struct InterruptStubTraits<InterruptId::MCPWM0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::MCPWM0_IRQHandler;
  static constexpr std::uint16_t kLine = 31u;
  static constexpr std::uint16_t kVectorSlot = 47u;
};

template<>
struct InterruptStubTraits<InterruptId::MCPWM1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::MCPWM1_IRQHandler;
  static constexpr std::uint16_t kLine = 32u;
  static constexpr std::uint16_t kVectorSlot = 48u;
};

template<>
struct InterruptStubTraits<InterruptId::LEDC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::LEDC_IRQHandler;
  static constexpr std::uint16_t kLine = 35u;
  static constexpr std::uint16_t kVectorSlot = 51u;
};

template<>
struct InterruptStubTraits<InterruptId::EFUSE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::EFUSE_IRQHandler;
  static constexpr std::uint16_t kLine = 36u;
  static constexpr std::uint16_t kVectorSlot = 52u;
};

template<>
struct InterruptStubTraits<InterruptId::TWAI0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TWAI0_IRQHandler;
  static constexpr std::uint16_t kLine = 37u;
  static constexpr std::uint16_t kVectorSlot = 53u;
};

template<>
struct InterruptStubTraits<InterruptId::USB> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::USB_IRQHandler;
  static constexpr std::uint16_t kLine = 38u;
  static constexpr std::uint16_t kVectorSlot = 54u;
};

template<>
struct InterruptStubTraits<InterruptId::RTC_CORE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RTC_CORE_IRQHandler;
  static constexpr std::uint16_t kLine = 39u;
  static constexpr std::uint16_t kVectorSlot = 55u;
};

template<>
struct InterruptStubTraits<InterruptId::RMT> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RMT_IRQHandler;
  static constexpr std::uint16_t kLine = 40u;
  static constexpr std::uint16_t kVectorSlot = 56u;
};

template<>
struct InterruptStubTraits<InterruptId::PCNT> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::PCNT_IRQHandler;
  static constexpr std::uint16_t kLine = 41u;
  static constexpr std::uint16_t kVectorSlot = 57u;
};

template<>
struct InterruptStubTraits<InterruptId::I2C_EXT0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::I2C_EXT0_IRQHandler;
  static constexpr std::uint16_t kLine = 42u;
  static constexpr std::uint16_t kVectorSlot = 58u;
};

template<>
struct InterruptStubTraits<InterruptId::I2C_EXT1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::I2C_EXT1_IRQHandler;
  static constexpr std::uint16_t kLine = 43u;
  static constexpr std::uint16_t kVectorSlot = 59u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI2_DMA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI2_DMA_IRQHandler;
  static constexpr std::uint16_t kLine = 44u;
  static constexpr std::uint16_t kVectorSlot = 60u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI3_DMA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI3_DMA_IRQHandler;
  static constexpr std::uint16_t kLine = 45u;
  static constexpr std::uint16_t kVectorSlot = 61u;
};

template<>
struct InterruptStubTraits<InterruptId::WDT> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::WDT_IRQHandler;
  static constexpr std::uint16_t kLine = 47u;
  static constexpr std::uint16_t kVectorSlot = 63u;
};

template<>
struct InterruptStubTraits<InterruptId::TIMER1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TIMER1_IRQHandler;
  static constexpr std::uint16_t kLine = 48u;
  static constexpr std::uint16_t kVectorSlot = 64u;
};

template<>
struct InterruptStubTraits<InterruptId::TIMER2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TIMER2_IRQHandler;
  static constexpr std::uint16_t kLine = 49u;
  static constexpr std::uint16_t kVectorSlot = 65u;
};

template<>
struct InterruptStubTraits<InterruptId::TG0_T0_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG0_T0_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 50u;
  static constexpr std::uint16_t kVectorSlot = 66u;
};

template<>
struct InterruptStubTraits<InterruptId::TG0_T1_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG0_T1_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 51u;
  static constexpr std::uint16_t kVectorSlot = 67u;
};

template<>
struct InterruptStubTraits<InterruptId::TG0_WDT_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG0_WDT_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 52u;
  static constexpr std::uint16_t kVectorSlot = 68u;
};

template<>
struct InterruptStubTraits<InterruptId::TG1_T0_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG1_T0_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 53u;
  static constexpr std::uint16_t kVectorSlot = 69u;
};

template<>
struct InterruptStubTraits<InterruptId::TG1_T1_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG1_T1_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 54u;
  static constexpr std::uint16_t kVectorSlot = 70u;
};

template<>
struct InterruptStubTraits<InterruptId::TG1_WDT_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG1_WDT_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 55u;
  static constexpr std::uint16_t kVectorSlot = 71u;
};

template<>
struct InterruptStubTraits<InterruptId::CACHE_IA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CACHE_IA_IRQHandler;
  static constexpr std::uint16_t kLine = 56u;
  static constexpr std::uint16_t kVectorSlot = 72u;
};

template<>
struct InterruptStubTraits<InterruptId::SYSTIMER_TARGET0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SYSTIMER_TARGET0_IRQHandler;
  static constexpr std::uint16_t kLine = 57u;
  static constexpr std::uint16_t kVectorSlot = 73u;
};

template<>
struct InterruptStubTraits<InterruptId::SYSTIMER_TARGET1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SYSTIMER_TARGET1_IRQHandler;
  static constexpr std::uint16_t kLine = 58u;
  static constexpr std::uint16_t kVectorSlot = 74u;
};

template<>
struct InterruptStubTraits<InterruptId::SYSTIMER_TARGET2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SYSTIMER_TARGET2_IRQHandler;
  static constexpr std::uint16_t kLine = 59u;
  static constexpr std::uint16_t kVectorSlot = 75u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI_MEM_REJECT_CACHE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI_MEM_REJECT_CACHE_IRQHandler;
  static constexpr std::uint16_t kLine = 60u;
  static constexpr std::uint16_t kVectorSlot = 76u;
};

template<>
struct InterruptStubTraits<InterruptId::DCACHE_PRELOAD0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DCACHE_PRELOAD0_IRQHandler;
  static constexpr std::uint16_t kLine = 61u;
  static constexpr std::uint16_t kVectorSlot = 77u;
};

template<>
struct InterruptStubTraits<InterruptId::ICACHE_PRELOAD0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::ICACHE_PRELOAD0_IRQHandler;
  static constexpr std::uint16_t kLine = 62u;
  static constexpr std::uint16_t kVectorSlot = 78u;
};

template<>
struct InterruptStubTraits<InterruptId::DCACHE_SYNC0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DCACHE_SYNC0_IRQHandler;
  static constexpr std::uint16_t kLine = 63u;
  static constexpr std::uint16_t kVectorSlot = 79u;
};

template<>
struct InterruptStubTraits<InterruptId::ICACHE_SYNC0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::ICACHE_SYNC0_IRQHandler;
  static constexpr std::uint16_t kLine = 64u;
  static constexpr std::uint16_t kVectorSlot = 80u;
};

template<>
struct InterruptStubTraits<InterruptId::APB_ADC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::APB_ADC_IRQHandler;
  static constexpr std::uint16_t kLine = 65u;
  static constexpr std::uint16_t kVectorSlot = 81u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_IN_CH0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_IN_CH0_IRQHandler;
  static constexpr std::uint16_t kLine = 66u;
  static constexpr std::uint16_t kVectorSlot = 82u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_IN_CH1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_IN_CH1_IRQHandler;
  static constexpr std::uint16_t kLine = 67u;
  static constexpr std::uint16_t kVectorSlot = 83u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_IN_CH2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_IN_CH2_IRQHandler;
  static constexpr std::uint16_t kLine = 68u;
  static constexpr std::uint16_t kVectorSlot = 84u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_IN_CH3> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_IN_CH3_IRQHandler;
  static constexpr std::uint16_t kLine = 69u;
  static constexpr std::uint16_t kVectorSlot = 85u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_IN_CH4> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_IN_CH4_IRQHandler;
  static constexpr std::uint16_t kLine = 70u;
  static constexpr std::uint16_t kVectorSlot = 86u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_OUT_CH0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_OUT_CH0_IRQHandler;
  static constexpr std::uint16_t kLine = 71u;
  static constexpr std::uint16_t kVectorSlot = 87u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_OUT_CH1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_OUT_CH1_IRQHandler;
  static constexpr std::uint16_t kLine = 72u;
  static constexpr std::uint16_t kVectorSlot = 88u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_OUT_CH2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_OUT_CH2_IRQHandler;
  static constexpr std::uint16_t kLine = 73u;
  static constexpr std::uint16_t kVectorSlot = 89u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_OUT_CH3> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_OUT_CH3_IRQHandler;
  static constexpr std::uint16_t kLine = 74u;
  static constexpr std::uint16_t kVectorSlot = 90u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_OUT_CH4> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_OUT_CH4_IRQHandler;
  static constexpr std::uint16_t kLine = 75u;
  static constexpr std::uint16_t kVectorSlot = 91u;
};

template<>
struct InterruptStubTraits<InterruptId::RSA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RSA_IRQHandler;
  static constexpr std::uint16_t kLine = 76u;
  static constexpr std::uint16_t kVectorSlot = 92u;
};

template<>
struct InterruptStubTraits<InterruptId::SHA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SHA_IRQHandler;
  static constexpr std::uint16_t kLine = 77u;
  static constexpr std::uint16_t kVectorSlot = 93u;
};

template<>
struct InterruptStubTraits<InterruptId::FROM_CPU_INTR0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::FROM_CPU_INTR0_IRQHandler;
  static constexpr std::uint16_t kLine = 79u;
  static constexpr std::uint16_t kVectorSlot = 95u;
};

template<>
struct InterruptStubTraits<InterruptId::FROM_CPU_INTR1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::FROM_CPU_INTR1_IRQHandler;
  static constexpr std::uint16_t kLine = 80u;
  static constexpr std::uint16_t kVectorSlot = 96u;
};

template<>
struct InterruptStubTraits<InterruptId::FROM_CPU_INTR2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::FROM_CPU_INTR2_IRQHandler;
  static constexpr std::uint16_t kLine = 81u;
  static constexpr std::uint16_t kVectorSlot = 97u;
};

template<>
struct InterruptStubTraits<InterruptId::FROM_CPU_INTR3> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::FROM_CPU_INTR3_IRQHandler;
  static constexpr std::uint16_t kLine = 82u;
  static constexpr std::uint16_t kVectorSlot = 98u;
};

template<>
struct InterruptStubTraits<InterruptId::ASSIST_DEBUG> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::ASSIST_DEBUG_IRQHandler;
  static constexpr std::uint16_t kLine = 83u;
  static constexpr std::uint16_t kVectorSlot = 99u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_APBPERI_PMS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_APBPERI_PMS_IRQHandler;
  static constexpr std::uint16_t kLine = 84u;
  static constexpr std::uint16_t kVectorSlot = 100u;
};

template<>
struct InterruptStubTraits<InterruptId::CORE0_IRAM0_PMS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CORE0_IRAM0_PMS_IRQHandler;
  static constexpr std::uint16_t kLine = 85u;
  static constexpr std::uint16_t kVectorSlot = 101u;
};

template<>
struct InterruptStubTraits<InterruptId::CORE0_DRAM0_PMS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CORE0_DRAM0_PMS_IRQHandler;
  static constexpr std::uint16_t kLine = 86u;
  static constexpr std::uint16_t kVectorSlot = 102u;
};

template<>
struct InterruptStubTraits<InterruptId::CORE0_PIF_PMS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CORE0_PIF_PMS_IRQHandler;
  static constexpr std::uint16_t kLine = 87u;
  static constexpr std::uint16_t kVectorSlot = 103u;
};

template<>
struct InterruptStubTraits<InterruptId::CORE0_PIF_PMS_SIZE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CORE0_PIF_PMS_SIZE_IRQHandler;
  static constexpr std::uint16_t kLine = 88u;
  static constexpr std::uint16_t kVectorSlot = 104u;
};

template<>
struct InterruptStubTraits<InterruptId::CORE1_IRAM0_PMS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CORE1_IRAM0_PMS_IRQHandler;
  static constexpr std::uint16_t kLine = 89u;
  static constexpr std::uint16_t kVectorSlot = 105u;
};

template<>
struct InterruptStubTraits<InterruptId::CORE1_DRAM0_PMS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CORE1_DRAM0_PMS_IRQHandler;
  static constexpr std::uint16_t kLine = 90u;
  static constexpr std::uint16_t kVectorSlot = 106u;
};

template<>
struct InterruptStubTraits<InterruptId::CORE1_PIF_PMS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CORE1_PIF_PMS_IRQHandler;
  static constexpr std::uint16_t kLine = 91u;
  static constexpr std::uint16_t kVectorSlot = 107u;
};

template<>
struct InterruptStubTraits<InterruptId::CORE1_PIF_PMS_SIZE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CORE1_PIF_PMS_SIZE_IRQHandler;
  static constexpr std::uint16_t kLine = 92u;
  static constexpr std::uint16_t kVectorSlot = 108u;
};

template<>
struct InterruptStubTraits<InterruptId::BACKUP_PMS_VIOLATE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::BACKUP_PMS_VIOLATE_IRQHandler;
  static constexpr std::uint16_t kLine = 93u;
  static constexpr std::uint16_t kVectorSlot = 109u;
};

template<>
struct InterruptStubTraits<InterruptId::CACHE_CORE0_ACS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CACHE_CORE0_ACS_IRQHandler;
  static constexpr std::uint16_t kLine = 94u;
  static constexpr std::uint16_t kVectorSlot = 110u;
};

template<>
struct InterruptStubTraits<InterruptId::CACHE_CORE1_ACS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CACHE_CORE1_ACS_IRQHandler;
  static constexpr std::uint16_t kLine = 95u;
  static constexpr std::uint16_t kVectorSlot = 111u;
};

template<>
struct InterruptStubTraits<InterruptId::USB_DEVICE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::USB_DEVICE_IRQHandler;
  static constexpr std::uint16_t kLine = 96u;
  static constexpr std::uint16_t kVectorSlot = 112u;
};

template<>
struct InterruptStubTraits<InterruptId::PERI_BACKUP> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::PERI_BACKUP_IRQHandler;
  static constexpr std::uint16_t kLine = 97u;
  static constexpr std::uint16_t kVectorSlot = 113u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_EXTMEM_REJECT> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_EXTMEM_REJECT_IRQHandler;
  static constexpr std::uint16_t kLine = 98u;
  static constexpr std::uint16_t kVectorSlot = 114u;
};

}
}
}
}
}
}
