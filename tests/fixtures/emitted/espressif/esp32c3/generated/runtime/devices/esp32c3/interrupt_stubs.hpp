#pragma once

#include <array>
#include <cstdint>
#include "interrupts.hpp"
#include "startup.hpp"

extern "C" {
void Default_Handler();
void WIFI_MAC_IRQHandler() __attribute__((weak));
void WIFI_MAC_NMI_IRQHandler() __attribute__((weak));
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
void APB_CTRL_IRQHandler() __attribute__((weak));
void UHCI0_IRQHandler() __attribute__((weak));
void GPIO_IRQHandler() __attribute__((weak));
void GPIO_NMI_IRQHandler() __attribute__((weak));
void SPI1_IRQHandler() __attribute__((weak));
void SPI2_IRQHandler() __attribute__((weak));
void I2S0_IRQHandler() __attribute__((weak));
void UART0_IRQHandler() __attribute__((weak));
void UART1_IRQHandler() __attribute__((weak));
void LEDC_IRQHandler() __attribute__((weak));
void EFUSE_IRQHandler() __attribute__((weak));
void TWAI0_IRQHandler() __attribute__((weak));
void USB_DEVICE_IRQHandler() __attribute__((weak));
void RTC_CORE_IRQHandler() __attribute__((weak));
void RMT_IRQHandler() __attribute__((weak));
void I2C_EXT0_IRQHandler() __attribute__((weak));
void TIMER1_IRQHandler() __attribute__((weak));
void TIMER2_IRQHandler() __attribute__((weak));
void TG0_T0_LEVEL_IRQHandler() __attribute__((weak));
void TG0_WDT_LEVEL_IRQHandler() __attribute__((weak));
void TG1_T0_LEVEL_IRQHandler() __attribute__((weak));
void TG1_WDT_LEVEL_IRQHandler() __attribute__((weak));
void CACHE_IA_IRQHandler() __attribute__((weak));
void SYSTIMER_TARGET0_IRQHandler() __attribute__((weak));
void SYSTIMER_TARGET1_IRQHandler() __attribute__((weak));
void SYSTIMER_TARGET2_IRQHandler() __attribute__((weak));
void SPI_MEM_REJECT_CACHE_IRQHandler() __attribute__((weak));
void ICACHE_PRELOAD0_IRQHandler() __attribute__((weak));
void ICACHE_SYNC0_IRQHandler() __attribute__((weak));
void APB_ADC_IRQHandler() __attribute__((weak));
void DMA_CH0_IRQHandler() __attribute__((weak));
void DMA_CH1_IRQHandler() __attribute__((weak));
void DMA_CH2_IRQHandler() __attribute__((weak));
void RSA_IRQHandler() __attribute__((weak));
void AES_IRQHandler() __attribute__((weak));
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
void BAK_PMS_VIOLATE_IRQHandler() __attribute__((weak));
void CACHE_CORE0_ACS_IRQHandler() __attribute__((weak));
}

namespace espressif {
namespace esp32c3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32c3 {
struct InterruptStubDescriptor {
  InterruptId interrupt_id;
  StartupSymbolId symbol_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptStubDescriptor, 62> kInterruptStubs = {{
  {InterruptId::WIFI_MAC, StartupSymbolId::WIFI_MAC_IRQHandler, 0u, 16u},
  {InterruptId::WIFI_MAC_NMI, StartupSymbolId::WIFI_MAC_NMI_IRQHandler, 1u, 17u},
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
  {InterruptId::APB_CTRL, StartupSymbolId::APB_CTRL_IRQHandler, 14u, 30u},
  {InterruptId::UHCI0, StartupSymbolId::UHCI0_IRQHandler, 15u, 31u},
  {InterruptId::GPIO, StartupSymbolId::GPIO_IRQHandler, 16u, 32u},
  {InterruptId::GPIO_NMI, StartupSymbolId::GPIO_NMI_IRQHandler, 17u, 33u},
  {InterruptId::SPI1, StartupSymbolId::SPI1_IRQHandler, 18u, 34u},
  {InterruptId::SPI2, StartupSymbolId::SPI2_IRQHandler, 19u, 35u},
  {InterruptId::I2S0, StartupSymbolId::I2S0_IRQHandler, 20u, 36u},
  {InterruptId::UART0, StartupSymbolId::UART0_IRQHandler, 21u, 37u},
  {InterruptId::UART1, StartupSymbolId::UART1_IRQHandler, 22u, 38u},
  {InterruptId::LEDC, StartupSymbolId::LEDC_IRQHandler, 23u, 39u},
  {InterruptId::EFUSE, StartupSymbolId::EFUSE_IRQHandler, 24u, 40u},
  {InterruptId::TWAI0, StartupSymbolId::TWAI0_IRQHandler, 25u, 41u},
  {InterruptId::USB_DEVICE, StartupSymbolId::USB_DEVICE_IRQHandler, 26u, 42u},
  {InterruptId::RTC_CORE, StartupSymbolId::RTC_CORE_IRQHandler, 27u, 43u},
  {InterruptId::RMT, StartupSymbolId::RMT_IRQHandler, 28u, 44u},
  {InterruptId::I2C_EXT0, StartupSymbolId::I2C_EXT0_IRQHandler, 29u, 45u},
  {InterruptId::TIMER1, StartupSymbolId::TIMER1_IRQHandler, 30u, 46u},
  {InterruptId::TIMER2, StartupSymbolId::TIMER2_IRQHandler, 31u, 47u},
  {InterruptId::TG0_T0_LEVEL, StartupSymbolId::TG0_T0_LEVEL_IRQHandler, 32u, 48u},
  {InterruptId::TG0_WDT_LEVEL, StartupSymbolId::TG0_WDT_LEVEL_IRQHandler, 33u, 49u},
  {InterruptId::TG1_T0_LEVEL, StartupSymbolId::TG1_T0_LEVEL_IRQHandler, 34u, 50u},
  {InterruptId::TG1_WDT_LEVEL, StartupSymbolId::TG1_WDT_LEVEL_IRQHandler, 35u, 51u},
  {InterruptId::CACHE_IA, StartupSymbolId::CACHE_IA_IRQHandler, 36u, 52u},
  {InterruptId::SYSTIMER_TARGET0, StartupSymbolId::SYSTIMER_TARGET0_IRQHandler, 37u, 53u},
  {InterruptId::SYSTIMER_TARGET1, StartupSymbolId::SYSTIMER_TARGET1_IRQHandler, 38u, 54u},
  {InterruptId::SYSTIMER_TARGET2, StartupSymbolId::SYSTIMER_TARGET2_IRQHandler, 39u, 55u},
  {InterruptId::SPI_MEM_REJECT_CACHE, StartupSymbolId::SPI_MEM_REJECT_CACHE_IRQHandler, 40u, 56u},
  {InterruptId::ICACHE_PRELOAD0, StartupSymbolId::ICACHE_PRELOAD0_IRQHandler, 41u, 57u},
  {InterruptId::ICACHE_SYNC0, StartupSymbolId::ICACHE_SYNC0_IRQHandler, 42u, 58u},
  {InterruptId::APB_ADC, StartupSymbolId::APB_ADC_IRQHandler, 43u, 59u},
  {InterruptId::DMA_CH0, StartupSymbolId::DMA_CH0_IRQHandler, 44u, 60u},
  {InterruptId::DMA_CH1, StartupSymbolId::DMA_CH1_IRQHandler, 45u, 61u},
  {InterruptId::DMA_CH2, StartupSymbolId::DMA_CH2_IRQHandler, 46u, 62u},
  {InterruptId::RSA, StartupSymbolId::RSA_IRQHandler, 47u, 63u},
  {InterruptId::AES, StartupSymbolId::AES_IRQHandler, 48u, 64u},
  {InterruptId::SHA, StartupSymbolId::SHA_IRQHandler, 49u, 65u},
  {InterruptId::FROM_CPU_INTR0, StartupSymbolId::FROM_CPU_INTR0_IRQHandler, 50u, 66u},
  {InterruptId::FROM_CPU_INTR1, StartupSymbolId::FROM_CPU_INTR1_IRQHandler, 51u, 67u},
  {InterruptId::FROM_CPU_INTR2, StartupSymbolId::FROM_CPU_INTR2_IRQHandler, 52u, 68u},
  {InterruptId::FROM_CPU_INTR3, StartupSymbolId::FROM_CPU_INTR3_IRQHandler, 53u, 69u},
  {InterruptId::ASSIST_DEBUG, StartupSymbolId::ASSIST_DEBUG_IRQHandler, 54u, 70u},
  {InterruptId::DMA_APBPERI_PMS, StartupSymbolId::DMA_APBPERI_PMS_IRQHandler, 55u, 71u},
  {InterruptId::CORE0_IRAM0_PMS, StartupSymbolId::CORE0_IRAM0_PMS_IRQHandler, 56u, 72u},
  {InterruptId::CORE0_DRAM0_PMS, StartupSymbolId::CORE0_DRAM0_PMS_IRQHandler, 57u, 73u},
  {InterruptId::CORE0_PIF_PMS, StartupSymbolId::CORE0_PIF_PMS_IRQHandler, 58u, 74u},
  {InterruptId::CORE0_PIF_PMS_SIZE, StartupSymbolId::CORE0_PIF_PMS_SIZE_IRQHandler, 59u, 75u},
  {InterruptId::BAK_PMS_VIOLATE, StartupSymbolId::BAK_PMS_VIOLATE_IRQHandler, 60u, 76u},
  {InterruptId::CACHE_CORE0_ACS, StartupSymbolId::CACHE_CORE0_ACS_IRQHandler, 61u, 77u},
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
struct InterruptStubTraits<InterruptId::WIFI_MAC_NMI> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::WIFI_MAC_NMI_IRQHandler;
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
struct InterruptStubTraits<InterruptId::APB_CTRL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::APB_CTRL_IRQHandler;
  static constexpr std::uint16_t kLine = 14u;
  static constexpr std::uint16_t kVectorSlot = 30u;
};

template<>
struct InterruptStubTraits<InterruptId::UHCI0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UHCI0_IRQHandler;
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
struct InterruptStubTraits<InterruptId::SPI1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI1_IRQHandler;
  static constexpr std::uint16_t kLine = 18u;
  static constexpr std::uint16_t kVectorSlot = 34u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI2_IRQHandler;
  static constexpr std::uint16_t kLine = 19u;
  static constexpr std::uint16_t kVectorSlot = 35u;
};

template<>
struct InterruptStubTraits<InterruptId::I2S0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::I2S0_IRQHandler;
  static constexpr std::uint16_t kLine = 20u;
  static constexpr std::uint16_t kVectorSlot = 36u;
};

template<>
struct InterruptStubTraits<InterruptId::UART0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UART0_IRQHandler;
  static constexpr std::uint16_t kLine = 21u;
  static constexpr std::uint16_t kVectorSlot = 37u;
};

template<>
struct InterruptStubTraits<InterruptId::UART1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UART1_IRQHandler;
  static constexpr std::uint16_t kLine = 22u;
  static constexpr std::uint16_t kVectorSlot = 38u;
};

template<>
struct InterruptStubTraits<InterruptId::LEDC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::LEDC_IRQHandler;
  static constexpr std::uint16_t kLine = 23u;
  static constexpr std::uint16_t kVectorSlot = 39u;
};

template<>
struct InterruptStubTraits<InterruptId::EFUSE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::EFUSE_IRQHandler;
  static constexpr std::uint16_t kLine = 24u;
  static constexpr std::uint16_t kVectorSlot = 40u;
};

template<>
struct InterruptStubTraits<InterruptId::TWAI0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TWAI0_IRQHandler;
  static constexpr std::uint16_t kLine = 25u;
  static constexpr std::uint16_t kVectorSlot = 41u;
};

template<>
struct InterruptStubTraits<InterruptId::USB_DEVICE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::USB_DEVICE_IRQHandler;
  static constexpr std::uint16_t kLine = 26u;
  static constexpr std::uint16_t kVectorSlot = 42u;
};

template<>
struct InterruptStubTraits<InterruptId::RTC_CORE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RTC_CORE_IRQHandler;
  static constexpr std::uint16_t kLine = 27u;
  static constexpr std::uint16_t kVectorSlot = 43u;
};

template<>
struct InterruptStubTraits<InterruptId::RMT> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RMT_IRQHandler;
  static constexpr std::uint16_t kLine = 28u;
  static constexpr std::uint16_t kVectorSlot = 44u;
};

template<>
struct InterruptStubTraits<InterruptId::I2C_EXT0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::I2C_EXT0_IRQHandler;
  static constexpr std::uint16_t kLine = 29u;
  static constexpr std::uint16_t kVectorSlot = 45u;
};

template<>
struct InterruptStubTraits<InterruptId::TIMER1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TIMER1_IRQHandler;
  static constexpr std::uint16_t kLine = 30u;
  static constexpr std::uint16_t kVectorSlot = 46u;
};

template<>
struct InterruptStubTraits<InterruptId::TIMER2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TIMER2_IRQHandler;
  static constexpr std::uint16_t kLine = 31u;
  static constexpr std::uint16_t kVectorSlot = 47u;
};

template<>
struct InterruptStubTraits<InterruptId::TG0_T0_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG0_T0_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 32u;
  static constexpr std::uint16_t kVectorSlot = 48u;
};

template<>
struct InterruptStubTraits<InterruptId::TG0_WDT_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG0_WDT_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 33u;
  static constexpr std::uint16_t kVectorSlot = 49u;
};

template<>
struct InterruptStubTraits<InterruptId::TG1_T0_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG1_T0_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 34u;
  static constexpr std::uint16_t kVectorSlot = 50u;
};

template<>
struct InterruptStubTraits<InterruptId::TG1_WDT_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG1_WDT_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 35u;
  static constexpr std::uint16_t kVectorSlot = 51u;
};

template<>
struct InterruptStubTraits<InterruptId::CACHE_IA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CACHE_IA_IRQHandler;
  static constexpr std::uint16_t kLine = 36u;
  static constexpr std::uint16_t kVectorSlot = 52u;
};

template<>
struct InterruptStubTraits<InterruptId::SYSTIMER_TARGET0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SYSTIMER_TARGET0_IRQHandler;
  static constexpr std::uint16_t kLine = 37u;
  static constexpr std::uint16_t kVectorSlot = 53u;
};

template<>
struct InterruptStubTraits<InterruptId::SYSTIMER_TARGET1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SYSTIMER_TARGET1_IRQHandler;
  static constexpr std::uint16_t kLine = 38u;
  static constexpr std::uint16_t kVectorSlot = 54u;
};

template<>
struct InterruptStubTraits<InterruptId::SYSTIMER_TARGET2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SYSTIMER_TARGET2_IRQHandler;
  static constexpr std::uint16_t kLine = 39u;
  static constexpr std::uint16_t kVectorSlot = 55u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI_MEM_REJECT_CACHE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI_MEM_REJECT_CACHE_IRQHandler;
  static constexpr std::uint16_t kLine = 40u;
  static constexpr std::uint16_t kVectorSlot = 56u;
};

template<>
struct InterruptStubTraits<InterruptId::ICACHE_PRELOAD0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::ICACHE_PRELOAD0_IRQHandler;
  static constexpr std::uint16_t kLine = 41u;
  static constexpr std::uint16_t kVectorSlot = 57u;
};

template<>
struct InterruptStubTraits<InterruptId::ICACHE_SYNC0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::ICACHE_SYNC0_IRQHandler;
  static constexpr std::uint16_t kLine = 42u;
  static constexpr std::uint16_t kVectorSlot = 58u;
};

template<>
struct InterruptStubTraits<InterruptId::APB_ADC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::APB_ADC_IRQHandler;
  static constexpr std::uint16_t kLine = 43u;
  static constexpr std::uint16_t kVectorSlot = 59u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_CH0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_CH0_IRQHandler;
  static constexpr std::uint16_t kLine = 44u;
  static constexpr std::uint16_t kVectorSlot = 60u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_CH1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_CH1_IRQHandler;
  static constexpr std::uint16_t kLine = 45u;
  static constexpr std::uint16_t kVectorSlot = 61u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_CH2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_CH2_IRQHandler;
  static constexpr std::uint16_t kLine = 46u;
  static constexpr std::uint16_t kVectorSlot = 62u;
};

template<>
struct InterruptStubTraits<InterruptId::RSA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RSA_IRQHandler;
  static constexpr std::uint16_t kLine = 47u;
  static constexpr std::uint16_t kVectorSlot = 63u;
};

template<>
struct InterruptStubTraits<InterruptId::AES> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::AES_IRQHandler;
  static constexpr std::uint16_t kLine = 48u;
  static constexpr std::uint16_t kVectorSlot = 64u;
};

template<>
struct InterruptStubTraits<InterruptId::SHA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SHA_IRQHandler;
  static constexpr std::uint16_t kLine = 49u;
  static constexpr std::uint16_t kVectorSlot = 65u;
};

template<>
struct InterruptStubTraits<InterruptId::FROM_CPU_INTR0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::FROM_CPU_INTR0_IRQHandler;
  static constexpr std::uint16_t kLine = 50u;
  static constexpr std::uint16_t kVectorSlot = 66u;
};

template<>
struct InterruptStubTraits<InterruptId::FROM_CPU_INTR1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::FROM_CPU_INTR1_IRQHandler;
  static constexpr std::uint16_t kLine = 51u;
  static constexpr std::uint16_t kVectorSlot = 67u;
};

template<>
struct InterruptStubTraits<InterruptId::FROM_CPU_INTR2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::FROM_CPU_INTR2_IRQHandler;
  static constexpr std::uint16_t kLine = 52u;
  static constexpr std::uint16_t kVectorSlot = 68u;
};

template<>
struct InterruptStubTraits<InterruptId::FROM_CPU_INTR3> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::FROM_CPU_INTR3_IRQHandler;
  static constexpr std::uint16_t kLine = 53u;
  static constexpr std::uint16_t kVectorSlot = 69u;
};

template<>
struct InterruptStubTraits<InterruptId::ASSIST_DEBUG> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::ASSIST_DEBUG_IRQHandler;
  static constexpr std::uint16_t kLine = 54u;
  static constexpr std::uint16_t kVectorSlot = 70u;
};

template<>
struct InterruptStubTraits<InterruptId::DMA_APBPERI_PMS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DMA_APBPERI_PMS_IRQHandler;
  static constexpr std::uint16_t kLine = 55u;
  static constexpr std::uint16_t kVectorSlot = 71u;
};

template<>
struct InterruptStubTraits<InterruptId::CORE0_IRAM0_PMS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CORE0_IRAM0_PMS_IRQHandler;
  static constexpr std::uint16_t kLine = 56u;
  static constexpr std::uint16_t kVectorSlot = 72u;
};

template<>
struct InterruptStubTraits<InterruptId::CORE0_DRAM0_PMS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CORE0_DRAM0_PMS_IRQHandler;
  static constexpr std::uint16_t kLine = 57u;
  static constexpr std::uint16_t kVectorSlot = 73u;
};

template<>
struct InterruptStubTraits<InterruptId::CORE0_PIF_PMS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CORE0_PIF_PMS_IRQHandler;
  static constexpr std::uint16_t kLine = 58u;
  static constexpr std::uint16_t kVectorSlot = 74u;
};

template<>
struct InterruptStubTraits<InterruptId::CORE0_PIF_PMS_SIZE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CORE0_PIF_PMS_SIZE_IRQHandler;
  static constexpr std::uint16_t kLine = 59u;
  static constexpr std::uint16_t kVectorSlot = 75u;
};

template<>
struct InterruptStubTraits<InterruptId::BAK_PMS_VIOLATE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::BAK_PMS_VIOLATE_IRQHandler;
  static constexpr std::uint16_t kLine = 60u;
  static constexpr std::uint16_t kVectorSlot = 76u;
};

template<>
struct InterruptStubTraits<InterruptId::CACHE_CORE0_ACS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CACHE_CORE0_ACS_IRQHandler;
  static constexpr std::uint16_t kLine = 61u;
  static constexpr std::uint16_t kVectorSlot = 77u;
};

}
}
}
}
}
}
