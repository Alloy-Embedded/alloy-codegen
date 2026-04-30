#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f401re {
enum class PeripheralId : std::uint16_t {
  none,
  ADC1,
  DMA1,
  DMA2,
  GPIOA,
  GPIOB,
  IWDG,
  OTG_FS,
  RTC,
  SPI1,
  TIM1,
  USART1,
  USART2,
};

enum class ClockGateId : std::uint16_t {
  none,
  gate_dma1,
  gate_dma2,
  gate_gpioa,
  gate_gpiob,
  gate_otg_fs,
  gate_spi1,
  gate_tim1,
  gate_usart1,
  gate_usart2,
};

enum class ResetId : std::uint16_t {
  none,
  reset_dma1,
  reset_dma2,
  reset_gpioa,
  reset_gpiob,
  reset_otg_fs,
  reset_spi1,
  reset_tim1,
  reset_usart1,
  reset_usart2,
};

enum class ClockSelectorId : std::uint16_t {
  none,
};

template<PeripheralId Id>
struct PeripheralInstanceTraits {
  static constexpr bool kPresent = false;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr int kInstance = -1;
  static constexpr std::uintptr_t kBaseAddress = 0u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::ADC1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_adc_st_adc;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40012000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::DMA1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_dma;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dma_st_bdma_f4_v1_0;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40026000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_dma1;
  static constexpr ResetId kResetId = ResetId::reset_dma1;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::DMA2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_dma;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dma_st_bdma_f4_v1_0;
  static constexpr int kInstance = 2;
  static constexpr std::uintptr_t kBaseAddress = 0x40026400u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_dma2;
  static constexpr ResetId kResetId = ResetId::reset_dma2;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::GPIOA> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpio_st_stm32f4x_gpio_v1_0;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40020000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpioa;
  static constexpr ResetId kResetId = ResetId::reset_gpioa;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::GPIOB> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpio_st_stm32f4x_gpio_v1_0;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40020400u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpiob;
  static constexpr ResetId kResetId = ResetId::reset_gpiob;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::IWDG> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_watchdog;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_watchdog_st_iwdg;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40003000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::OTG_FS> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_usb;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_usb_st_otg_fs;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x50000000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_otg_fs;
  static constexpr ResetId kResetId = ResetId::reset_otg_fs;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::RTC> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_rtc;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_rtc_st_rtc;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40002800u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::SPI1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_st_spi;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40013000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi1;
  static constexpr ResetId kResetId = ResetId::reset_spi1;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::TIM1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_timer;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_timer_st_tim;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40010000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_tim1;
  static constexpr ResetId kResetId = ResetId::reset_tim1;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::USART1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_st_usart_f4_v1_0;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40011000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usart1;
  static constexpr ResetId kResetId = ResetId::reset_usart1;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::USART2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_st_usart_f4_v1_0;
  static constexpr int kInstance = 2;
  static constexpr std::uintptr_t kBaseAddress = 0x40004400u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usart2;
  static constexpr ResetId kResetId = ResetId::reset_usart2;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template <PeripheralId Id>
[[nodiscard]] constexpr std::uintptr_t peripheral_base() noexcept {
  static_assert(PeripheralInstanceTraits<Id>::kPresent);
  return PeripheralInstanceTraits<Id>::kBaseAddress;
}

inline constexpr std::array<PeripheralId, 12> kRuntimePeripherals = {{
  PeripheralId::ADC1,
  PeripheralId::DMA1,
  PeripheralId::DMA2,
  PeripheralId::GPIOA,
  PeripheralId::GPIOB,
  PeripheralId::IWDG,
  PeripheralId::OTG_FS,
  PeripheralId::RTC,
  PeripheralId::SPI1,
  PeripheralId::TIM1,
  PeripheralId::USART1,
  PeripheralId::USART2,
}};
}
}
}
}
}
}
