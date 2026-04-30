#pragma once

#include <array>
#include <cstdint>
#include "interrupts.hpp"
#include "startup.hpp"

extern "C" {
void Default_Handler();
void WIFI_MAC_IRQHandler() __attribute__((weak));
void WIFI_NMI_IRQHandler() __attribute__((weak));
void WIFI_BB_IRQHandler() __attribute__((weak));
void BT_MAC_IRQHandler() __attribute__((weak));
void BT_BB_IRQHandler() __attribute__((weak));
void BT_BB_NMI_IRQHandler() __attribute__((weak));
void RWBT_IRQHandler() __attribute__((weak));
void RWBLE_IRQHandler() __attribute__((weak));
void RWBT_NMI_IRQHandler() __attribute__((weak));
void RWBLE_NMI_IRQHandler() __attribute__((weak));
void UHCI0_IRQHandler() __attribute__((weak));
void UHCI1_IRQHandler() __attribute__((weak));
void TG0_T0_LEVEL_IRQHandler() __attribute__((weak));
void TG0_T1_LEVEL_IRQHandler() __attribute__((weak));
void TG0_WDT_LEVEL_IRQHandler() __attribute__((weak));
void TG0_LACT_LEVEL_IRQHandler() __attribute__((weak));
void TG1_T0_LEVEL_IRQHandler() __attribute__((weak));
void TG1_T1_LEVEL_IRQHandler() __attribute__((weak));
void TG1_WDT_LEVEL_IRQHandler() __attribute__((weak));
void TG1_LACT_LEVEL_IRQHandler() __attribute__((weak));
void GPIO_IRQHandler() __attribute__((weak));
void GPIO_NMI_IRQHandler() __attribute__((weak));
void FROM_CPU_INTR0_IRQHandler() __attribute__((weak));
void FROM_CPU_INTR1_IRQHandler() __attribute__((weak));
void FROM_CPU_INTR2_IRQHandler() __attribute__((weak));
void FROM_CPU_INTR3_IRQHandler() __attribute__((weak));
void SPI0_IRQHandler() __attribute__((weak));
void SPI1_IRQHandler() __attribute__((weak));
void SPI2_IRQHandler() __attribute__((weak));
void SPI3_IRQHandler() __attribute__((weak));
void I2S0_IRQHandler() __attribute__((weak));
void I2S1_IRQHandler() __attribute__((weak));
void UART0_IRQHandler() __attribute__((weak));
void UART1_IRQHandler() __attribute__((weak));
void UART2_IRQHandler() __attribute__((weak));
void SDIO_HOST_IRQHandler() __attribute__((weak));
void ETH_MAC_IRQHandler() __attribute__((weak));
void MCPWM0_IRQHandler() __attribute__((weak));
void MCPWM1_IRQHandler() __attribute__((weak));
void MCPWM2_IRQHandler() __attribute__((weak));
void MCPWM3_IRQHandler() __attribute__((weak));
void LEDC_IRQHandler() __attribute__((weak));
void EFUSE_IRQHandler() __attribute__((weak));
void TWAI0_IRQHandler() __attribute__((weak));
void RTC_CORE_IRQHandler() __attribute__((weak));
void RMT_IRQHandler() __attribute__((weak));
void PCNT_IRQHandler() __attribute__((weak));
void I2C_EXT0_IRQHandler() __attribute__((weak));
void I2C_EXT1_IRQHandler() __attribute__((weak));
void RSA_IRQHandler() __attribute__((weak));
void SPI1_DMA_IRQHandler() __attribute__((weak));
void SPI2_DMA_IRQHandler() __attribute__((weak));
void SPI3_DMA_IRQHandler() __attribute__((weak));
void WDT_IRQHandler() __attribute__((weak));
void TIMER1_IRQHandler() __attribute__((weak));
void TIMER2_IRQHandler() __attribute__((weak));
void TG0_T0_EDGE_IRQHandler() __attribute__((weak));
void TG0_T1_EDGE_IRQHandler() __attribute__((weak));
void TG0_WDT_EDGE_IRQHandler() __attribute__((weak));
void TG0_LACT_EDGE_IRQHandler() __attribute__((weak));
void TG1_T0_EDGE_IRQHandler() __attribute__((weak));
void TG1_T1_EDGE_IRQHandler() __attribute__((weak));
void TG1_WDT_EDGE_IRQHandler() __attribute__((weak));
void TG1_LACT_EDGE_IRQHandler() __attribute__((weak));
void MMU_IA_IRQHandler() __attribute__((weak));
void MPU_IA_IRQHandler() __attribute__((weak));
void CACHE_IA_IRQHandler() __attribute__((weak));
}

namespace espressif {
namespace esp32 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32_wroom32 {
struct InterruptStubDescriptor {
  InterruptId interrupt_id;
  StartupSymbolId symbol_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptStubDescriptor, 67> kInterruptStubs = {{
  {InterruptId::WIFI_MAC, StartupSymbolId::WIFI_MAC_IRQHandler, 0u, 16u},
  {InterruptId::WIFI_NMI, StartupSymbolId::WIFI_NMI_IRQHandler, 1u, 17u},
  {InterruptId::WIFI_BB, StartupSymbolId::WIFI_BB_IRQHandler, 2u, 18u},
  {InterruptId::BT_MAC, StartupSymbolId::BT_MAC_IRQHandler, 3u, 19u},
  {InterruptId::BT_BB, StartupSymbolId::BT_BB_IRQHandler, 4u, 20u},
  {InterruptId::BT_BB_NMI, StartupSymbolId::BT_BB_NMI_IRQHandler, 5u, 21u},
  {InterruptId::RWBT, StartupSymbolId::RWBT_IRQHandler, 6u, 22u},
  {InterruptId::RWBLE, StartupSymbolId::RWBLE_IRQHandler, 7u, 23u},
  {InterruptId::RWBT_NMI, StartupSymbolId::RWBT_NMI_IRQHandler, 8u, 24u},
  {InterruptId::RWBLE_NMI, StartupSymbolId::RWBLE_NMI_IRQHandler, 9u, 25u},
  {InterruptId::UHCI0, StartupSymbolId::UHCI0_IRQHandler, 12u, 28u},
  {InterruptId::UHCI1, StartupSymbolId::UHCI1_IRQHandler, 13u, 29u},
  {InterruptId::TG0_T0_LEVEL, StartupSymbolId::TG0_T0_LEVEL_IRQHandler, 14u, 30u},
  {InterruptId::TG0_T1_LEVEL, StartupSymbolId::TG0_T1_LEVEL_IRQHandler, 15u, 31u},
  {InterruptId::TG0_WDT_LEVEL, StartupSymbolId::TG0_WDT_LEVEL_IRQHandler, 16u, 32u},
  {InterruptId::TG0_LACT_LEVEL, StartupSymbolId::TG0_LACT_LEVEL_IRQHandler, 17u, 33u},
  {InterruptId::TG1_T0_LEVEL, StartupSymbolId::TG1_T0_LEVEL_IRQHandler, 18u, 34u},
  {InterruptId::TG1_T1_LEVEL, StartupSymbolId::TG1_T1_LEVEL_IRQHandler, 19u, 35u},
  {InterruptId::TG1_WDT_LEVEL, StartupSymbolId::TG1_WDT_LEVEL_IRQHandler, 20u, 36u},
  {InterruptId::TG1_LACT_LEVEL, StartupSymbolId::TG1_LACT_LEVEL_IRQHandler, 21u, 37u},
  {InterruptId::GPIO, StartupSymbolId::GPIO_IRQHandler, 22u, 38u},
  {InterruptId::GPIO_NMI, StartupSymbolId::GPIO_NMI_IRQHandler, 23u, 39u},
  {InterruptId::FROM_CPU_INTR0, StartupSymbolId::FROM_CPU_INTR0_IRQHandler, 24u, 40u},
  {InterruptId::FROM_CPU_INTR1, StartupSymbolId::FROM_CPU_INTR1_IRQHandler, 25u, 41u},
  {InterruptId::FROM_CPU_INTR2, StartupSymbolId::FROM_CPU_INTR2_IRQHandler, 26u, 42u},
  {InterruptId::FROM_CPU_INTR3, StartupSymbolId::FROM_CPU_INTR3_IRQHandler, 27u, 43u},
  {InterruptId::SPI0, StartupSymbolId::SPI0_IRQHandler, 28u, 44u},
  {InterruptId::SPI1, StartupSymbolId::SPI1_IRQHandler, 29u, 45u},
  {InterruptId::SPI2, StartupSymbolId::SPI2_IRQHandler, 30u, 46u},
  {InterruptId::SPI3, StartupSymbolId::SPI3_IRQHandler, 31u, 47u},
  {InterruptId::I2S0, StartupSymbolId::I2S0_IRQHandler, 32u, 48u},
  {InterruptId::I2S1, StartupSymbolId::I2S1_IRQHandler, 33u, 49u},
  {InterruptId::UART0, StartupSymbolId::UART0_IRQHandler, 34u, 50u},
  {InterruptId::UART1, StartupSymbolId::UART1_IRQHandler, 35u, 51u},
  {InterruptId::UART2, StartupSymbolId::UART2_IRQHandler, 36u, 52u},
  {InterruptId::SDIO_HOST, StartupSymbolId::SDIO_HOST_IRQHandler, 37u, 53u},
  {InterruptId::ETH_MAC, StartupSymbolId::ETH_MAC_IRQHandler, 38u, 54u},
  {InterruptId::MCPWM0, StartupSymbolId::MCPWM0_IRQHandler, 39u, 55u},
  {InterruptId::MCPWM1, StartupSymbolId::MCPWM1_IRQHandler, 40u, 56u},
  {InterruptId::MCPWM2, StartupSymbolId::MCPWM2_IRQHandler, 41u, 57u},
  {InterruptId::MCPWM3, StartupSymbolId::MCPWM3_IRQHandler, 42u, 58u},
  {InterruptId::LEDC, StartupSymbolId::LEDC_IRQHandler, 43u, 59u},
  {InterruptId::EFUSE, StartupSymbolId::EFUSE_IRQHandler, 44u, 60u},
  {InterruptId::TWAI0, StartupSymbolId::TWAI0_IRQHandler, 45u, 61u},
  {InterruptId::RTC_CORE, StartupSymbolId::RTC_CORE_IRQHandler, 46u, 62u},
  {InterruptId::RMT, StartupSymbolId::RMT_IRQHandler, 47u, 63u},
  {InterruptId::PCNT, StartupSymbolId::PCNT_IRQHandler, 48u, 64u},
  {InterruptId::I2C_EXT0, StartupSymbolId::I2C_EXT0_IRQHandler, 49u, 65u},
  {InterruptId::I2C_EXT1, StartupSymbolId::I2C_EXT1_IRQHandler, 50u, 66u},
  {InterruptId::RSA, StartupSymbolId::RSA_IRQHandler, 51u, 67u},
  {InterruptId::SPI1_DMA, StartupSymbolId::SPI1_DMA_IRQHandler, 52u, 68u},
  {InterruptId::SPI2_DMA, StartupSymbolId::SPI2_DMA_IRQHandler, 53u, 69u},
  {InterruptId::SPI3_DMA, StartupSymbolId::SPI3_DMA_IRQHandler, 54u, 70u},
  {InterruptId::WDT, StartupSymbolId::WDT_IRQHandler, 55u, 71u},
  {InterruptId::TIMER1, StartupSymbolId::TIMER1_IRQHandler, 56u, 72u},
  {InterruptId::TIMER2, StartupSymbolId::TIMER2_IRQHandler, 57u, 73u},
  {InterruptId::TG0_T0_EDGE, StartupSymbolId::TG0_T0_EDGE_IRQHandler, 58u, 74u},
  {InterruptId::TG0_T1_EDGE, StartupSymbolId::TG0_T1_EDGE_IRQHandler, 59u, 75u},
  {InterruptId::TG0_WDT_EDGE, StartupSymbolId::TG0_WDT_EDGE_IRQHandler, 60u, 76u},
  {InterruptId::TG0_LACT_EDGE, StartupSymbolId::TG0_LACT_EDGE_IRQHandler, 61u, 77u},
  {InterruptId::TG1_T0_EDGE, StartupSymbolId::TG1_T0_EDGE_IRQHandler, 62u, 78u},
  {InterruptId::TG1_T1_EDGE, StartupSymbolId::TG1_T1_EDGE_IRQHandler, 63u, 79u},
  {InterruptId::TG1_WDT_EDGE, StartupSymbolId::TG1_WDT_EDGE_IRQHandler, 64u, 80u},
  {InterruptId::TG1_LACT_EDGE, StartupSymbolId::TG1_LACT_EDGE_IRQHandler, 65u, 81u},
  {InterruptId::MMU_IA, StartupSymbolId::MMU_IA_IRQHandler, 66u, 82u},
  {InterruptId::MPU_IA, StartupSymbolId::MPU_IA_IRQHandler, 67u, 83u},
  {InterruptId::CACHE_IA, StartupSymbolId::CACHE_IA_IRQHandler, 68u, 84u},
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
struct InterruptStubTraits<InterruptId::WIFI_BB> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::WIFI_BB_IRQHandler;
  static constexpr std::uint16_t kLine = 2u;
  static constexpr std::uint16_t kVectorSlot = 18u;
};

template<>
struct InterruptStubTraits<InterruptId::BT_MAC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::BT_MAC_IRQHandler;
  static constexpr std::uint16_t kLine = 3u;
  static constexpr std::uint16_t kVectorSlot = 19u;
};

template<>
struct InterruptStubTraits<InterruptId::BT_BB> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::BT_BB_IRQHandler;
  static constexpr std::uint16_t kLine = 4u;
  static constexpr std::uint16_t kVectorSlot = 20u;
};

template<>
struct InterruptStubTraits<InterruptId::BT_BB_NMI> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::BT_BB_NMI_IRQHandler;
  static constexpr std::uint16_t kLine = 5u;
  static constexpr std::uint16_t kVectorSlot = 21u;
};

template<>
struct InterruptStubTraits<InterruptId::RWBT> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RWBT_IRQHandler;
  static constexpr std::uint16_t kLine = 6u;
  static constexpr std::uint16_t kVectorSlot = 22u;
};

template<>
struct InterruptStubTraits<InterruptId::RWBLE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RWBLE_IRQHandler;
  static constexpr std::uint16_t kLine = 7u;
  static constexpr std::uint16_t kVectorSlot = 23u;
};

template<>
struct InterruptStubTraits<InterruptId::RWBT_NMI> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RWBT_NMI_IRQHandler;
  static constexpr std::uint16_t kLine = 8u;
  static constexpr std::uint16_t kVectorSlot = 24u;
};

template<>
struct InterruptStubTraits<InterruptId::RWBLE_NMI> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RWBLE_NMI_IRQHandler;
  static constexpr std::uint16_t kLine = 9u;
  static constexpr std::uint16_t kVectorSlot = 25u;
};

template<>
struct InterruptStubTraits<InterruptId::UHCI0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UHCI0_IRQHandler;
  static constexpr std::uint16_t kLine = 12u;
  static constexpr std::uint16_t kVectorSlot = 28u;
};

template<>
struct InterruptStubTraits<InterruptId::UHCI1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UHCI1_IRQHandler;
  static constexpr std::uint16_t kLine = 13u;
  static constexpr std::uint16_t kVectorSlot = 29u;
};

template<>
struct InterruptStubTraits<InterruptId::TG0_T0_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG0_T0_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 14u;
  static constexpr std::uint16_t kVectorSlot = 30u;
};

template<>
struct InterruptStubTraits<InterruptId::TG0_T1_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG0_T1_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 15u;
  static constexpr std::uint16_t kVectorSlot = 31u;
};

template<>
struct InterruptStubTraits<InterruptId::TG0_WDT_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG0_WDT_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 16u;
  static constexpr std::uint16_t kVectorSlot = 32u;
};

template<>
struct InterruptStubTraits<InterruptId::TG0_LACT_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG0_LACT_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 17u;
  static constexpr std::uint16_t kVectorSlot = 33u;
};

template<>
struct InterruptStubTraits<InterruptId::TG1_T0_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG1_T0_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 18u;
  static constexpr std::uint16_t kVectorSlot = 34u;
};

template<>
struct InterruptStubTraits<InterruptId::TG1_T1_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG1_T1_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 19u;
  static constexpr std::uint16_t kVectorSlot = 35u;
};

template<>
struct InterruptStubTraits<InterruptId::TG1_WDT_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG1_WDT_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 20u;
  static constexpr std::uint16_t kVectorSlot = 36u;
};

template<>
struct InterruptStubTraits<InterruptId::TG1_LACT_LEVEL> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG1_LACT_LEVEL_IRQHandler;
  static constexpr std::uint16_t kLine = 21u;
  static constexpr std::uint16_t kVectorSlot = 37u;
};

template<>
struct InterruptStubTraits<InterruptId::GPIO> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::GPIO_IRQHandler;
  static constexpr std::uint16_t kLine = 22u;
  static constexpr std::uint16_t kVectorSlot = 38u;
};

template<>
struct InterruptStubTraits<InterruptId::GPIO_NMI> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::GPIO_NMI_IRQHandler;
  static constexpr std::uint16_t kLine = 23u;
  static constexpr std::uint16_t kVectorSlot = 39u;
};

template<>
struct InterruptStubTraits<InterruptId::FROM_CPU_INTR0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::FROM_CPU_INTR0_IRQHandler;
  static constexpr std::uint16_t kLine = 24u;
  static constexpr std::uint16_t kVectorSlot = 40u;
};

template<>
struct InterruptStubTraits<InterruptId::FROM_CPU_INTR1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::FROM_CPU_INTR1_IRQHandler;
  static constexpr std::uint16_t kLine = 25u;
  static constexpr std::uint16_t kVectorSlot = 41u;
};

template<>
struct InterruptStubTraits<InterruptId::FROM_CPU_INTR2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::FROM_CPU_INTR2_IRQHandler;
  static constexpr std::uint16_t kLine = 26u;
  static constexpr std::uint16_t kVectorSlot = 42u;
};

template<>
struct InterruptStubTraits<InterruptId::FROM_CPU_INTR3> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::FROM_CPU_INTR3_IRQHandler;
  static constexpr std::uint16_t kLine = 27u;
  static constexpr std::uint16_t kVectorSlot = 43u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI0_IRQHandler;
  static constexpr std::uint16_t kLine = 28u;
  static constexpr std::uint16_t kVectorSlot = 44u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI1_IRQHandler;
  static constexpr std::uint16_t kLine = 29u;
  static constexpr std::uint16_t kVectorSlot = 45u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI2_IRQHandler;
  static constexpr std::uint16_t kLine = 30u;
  static constexpr std::uint16_t kVectorSlot = 46u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI3> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI3_IRQHandler;
  static constexpr std::uint16_t kLine = 31u;
  static constexpr std::uint16_t kVectorSlot = 47u;
};

template<>
struct InterruptStubTraits<InterruptId::I2S0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::I2S0_IRQHandler;
  static constexpr std::uint16_t kLine = 32u;
  static constexpr std::uint16_t kVectorSlot = 48u;
};

template<>
struct InterruptStubTraits<InterruptId::I2S1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::I2S1_IRQHandler;
  static constexpr std::uint16_t kLine = 33u;
  static constexpr std::uint16_t kVectorSlot = 49u;
};

template<>
struct InterruptStubTraits<InterruptId::UART0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UART0_IRQHandler;
  static constexpr std::uint16_t kLine = 34u;
  static constexpr std::uint16_t kVectorSlot = 50u;
};

template<>
struct InterruptStubTraits<InterruptId::UART1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UART1_IRQHandler;
  static constexpr std::uint16_t kLine = 35u;
  static constexpr std::uint16_t kVectorSlot = 51u;
};

template<>
struct InterruptStubTraits<InterruptId::UART2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UART2_IRQHandler;
  static constexpr std::uint16_t kLine = 36u;
  static constexpr std::uint16_t kVectorSlot = 52u;
};

template<>
struct InterruptStubTraits<InterruptId::SDIO_HOST> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SDIO_HOST_IRQHandler;
  static constexpr std::uint16_t kLine = 37u;
  static constexpr std::uint16_t kVectorSlot = 53u;
};

template<>
struct InterruptStubTraits<InterruptId::ETH_MAC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::ETH_MAC_IRQHandler;
  static constexpr std::uint16_t kLine = 38u;
  static constexpr std::uint16_t kVectorSlot = 54u;
};

template<>
struct InterruptStubTraits<InterruptId::MCPWM0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::MCPWM0_IRQHandler;
  static constexpr std::uint16_t kLine = 39u;
  static constexpr std::uint16_t kVectorSlot = 55u;
};

template<>
struct InterruptStubTraits<InterruptId::MCPWM1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::MCPWM1_IRQHandler;
  static constexpr std::uint16_t kLine = 40u;
  static constexpr std::uint16_t kVectorSlot = 56u;
};

template<>
struct InterruptStubTraits<InterruptId::MCPWM2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::MCPWM2_IRQHandler;
  static constexpr std::uint16_t kLine = 41u;
  static constexpr std::uint16_t kVectorSlot = 57u;
};

template<>
struct InterruptStubTraits<InterruptId::MCPWM3> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::MCPWM3_IRQHandler;
  static constexpr std::uint16_t kLine = 42u;
  static constexpr std::uint16_t kVectorSlot = 58u;
};

template<>
struct InterruptStubTraits<InterruptId::LEDC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::LEDC_IRQHandler;
  static constexpr std::uint16_t kLine = 43u;
  static constexpr std::uint16_t kVectorSlot = 59u;
};

template<>
struct InterruptStubTraits<InterruptId::EFUSE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::EFUSE_IRQHandler;
  static constexpr std::uint16_t kLine = 44u;
  static constexpr std::uint16_t kVectorSlot = 60u;
};

template<>
struct InterruptStubTraits<InterruptId::TWAI0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TWAI0_IRQHandler;
  static constexpr std::uint16_t kLine = 45u;
  static constexpr std::uint16_t kVectorSlot = 61u;
};

template<>
struct InterruptStubTraits<InterruptId::RTC_CORE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RTC_CORE_IRQHandler;
  static constexpr std::uint16_t kLine = 46u;
  static constexpr std::uint16_t kVectorSlot = 62u;
};

template<>
struct InterruptStubTraits<InterruptId::RMT> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RMT_IRQHandler;
  static constexpr std::uint16_t kLine = 47u;
  static constexpr std::uint16_t kVectorSlot = 63u;
};

template<>
struct InterruptStubTraits<InterruptId::PCNT> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::PCNT_IRQHandler;
  static constexpr std::uint16_t kLine = 48u;
  static constexpr std::uint16_t kVectorSlot = 64u;
};

template<>
struct InterruptStubTraits<InterruptId::I2C_EXT0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::I2C_EXT0_IRQHandler;
  static constexpr std::uint16_t kLine = 49u;
  static constexpr std::uint16_t kVectorSlot = 65u;
};

template<>
struct InterruptStubTraits<InterruptId::I2C_EXT1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::I2C_EXT1_IRQHandler;
  static constexpr std::uint16_t kLine = 50u;
  static constexpr std::uint16_t kVectorSlot = 66u;
};

template<>
struct InterruptStubTraits<InterruptId::RSA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RSA_IRQHandler;
  static constexpr std::uint16_t kLine = 51u;
  static constexpr std::uint16_t kVectorSlot = 67u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI1_DMA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI1_DMA_IRQHandler;
  static constexpr std::uint16_t kLine = 52u;
  static constexpr std::uint16_t kVectorSlot = 68u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI2_DMA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI2_DMA_IRQHandler;
  static constexpr std::uint16_t kLine = 53u;
  static constexpr std::uint16_t kVectorSlot = 69u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI3_DMA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI3_DMA_IRQHandler;
  static constexpr std::uint16_t kLine = 54u;
  static constexpr std::uint16_t kVectorSlot = 70u;
};

template<>
struct InterruptStubTraits<InterruptId::WDT> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::WDT_IRQHandler;
  static constexpr std::uint16_t kLine = 55u;
  static constexpr std::uint16_t kVectorSlot = 71u;
};

template<>
struct InterruptStubTraits<InterruptId::TIMER1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TIMER1_IRQHandler;
  static constexpr std::uint16_t kLine = 56u;
  static constexpr std::uint16_t kVectorSlot = 72u;
};

template<>
struct InterruptStubTraits<InterruptId::TIMER2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TIMER2_IRQHandler;
  static constexpr std::uint16_t kLine = 57u;
  static constexpr std::uint16_t kVectorSlot = 73u;
};

template<>
struct InterruptStubTraits<InterruptId::TG0_T0_EDGE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG0_T0_EDGE_IRQHandler;
  static constexpr std::uint16_t kLine = 58u;
  static constexpr std::uint16_t kVectorSlot = 74u;
};

template<>
struct InterruptStubTraits<InterruptId::TG0_T1_EDGE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG0_T1_EDGE_IRQHandler;
  static constexpr std::uint16_t kLine = 59u;
  static constexpr std::uint16_t kVectorSlot = 75u;
};

template<>
struct InterruptStubTraits<InterruptId::TG0_WDT_EDGE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG0_WDT_EDGE_IRQHandler;
  static constexpr std::uint16_t kLine = 60u;
  static constexpr std::uint16_t kVectorSlot = 76u;
};

template<>
struct InterruptStubTraits<InterruptId::TG0_LACT_EDGE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG0_LACT_EDGE_IRQHandler;
  static constexpr std::uint16_t kLine = 61u;
  static constexpr std::uint16_t kVectorSlot = 77u;
};

template<>
struct InterruptStubTraits<InterruptId::TG1_T0_EDGE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG1_T0_EDGE_IRQHandler;
  static constexpr std::uint16_t kLine = 62u;
  static constexpr std::uint16_t kVectorSlot = 78u;
};

template<>
struct InterruptStubTraits<InterruptId::TG1_T1_EDGE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG1_T1_EDGE_IRQHandler;
  static constexpr std::uint16_t kLine = 63u;
  static constexpr std::uint16_t kVectorSlot = 79u;
};

template<>
struct InterruptStubTraits<InterruptId::TG1_WDT_EDGE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG1_WDT_EDGE_IRQHandler;
  static constexpr std::uint16_t kLine = 64u;
  static constexpr std::uint16_t kVectorSlot = 80u;
};

template<>
struct InterruptStubTraits<InterruptId::TG1_LACT_EDGE> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TG1_LACT_EDGE_IRQHandler;
  static constexpr std::uint16_t kLine = 65u;
  static constexpr std::uint16_t kVectorSlot = 81u;
};

template<>
struct InterruptStubTraits<InterruptId::MMU_IA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::MMU_IA_IRQHandler;
  static constexpr std::uint16_t kLine = 66u;
  static constexpr std::uint16_t kVectorSlot = 82u;
};

template<>
struct InterruptStubTraits<InterruptId::MPU_IA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::MPU_IA_IRQHandler;
  static constexpr std::uint16_t kLine = 67u;
  static constexpr std::uint16_t kVectorSlot = 83u;
};

template<>
struct InterruptStubTraits<InterruptId::CACHE_IA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CACHE_IA_IRQHandler;
  static constexpr std::uint16_t kLine = 68u;
  static constexpr std::uint16_t kVectorSlot = 84u;
};

}
}
}
}
}
}
