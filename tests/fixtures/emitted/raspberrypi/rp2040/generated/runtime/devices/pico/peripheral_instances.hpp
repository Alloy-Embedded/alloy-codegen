#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace pico {
enum class PeripheralId : std::uint16_t {
  none,
  ADC,
  DMA,
  I2C0,
  I2C1,
  PWM,
  RTC,
  SPI0,
  SPI1,
  TIMER,
  UART0,
  UART1,
  WATCHDOG,
};

enum class ClockGateId : std::uint16_t {
  none,
  gate_adc,
  gate_dma,
  gate_i2c0,
  gate_i2c1,
  gate_spi0,
  gate_spi1,
  gate_uart0,
  gate_uart1,
};

enum class ResetId : std::uint16_t {
  none,
  reset_adc,
  reset_dma,
  reset_i2c0,
  reset_i2c1,
  reset_pwm,
  reset_rtc,
  reset_spi0,
  reset_spi1,
  reset_timer,
  reset_uart0,
  reset_uart1,
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
struct PeripheralInstanceTraits<PeripheralId::ADC> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_adc_raspberrypi_rp2040_adc_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x4004C000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_adc;
  static constexpr ResetId kResetId = ResetId::reset_adc;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::DMA> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_dma;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dma_raspberrypi_rp2040_dma_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x50000000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_dma;
  static constexpr ResetId kResetId = ResetId::reset_dma;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::I2C0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_i2c;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_i2c_raspberrypi_rp2040_i2c_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40044000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_i2c0;
  static constexpr ResetId kResetId = ResetId::reset_i2c0;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::I2C1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_i2c;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_i2c_raspberrypi_rp2040_i2c_v1;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40048000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_i2c1;
  static constexpr ResetId kResetId = ResetId::reset_i2c1;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::PWM> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_pwm;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_pwm_raspberrypi_rp2040_pwm_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40050000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::reset_pwm;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::RTC> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_rtc;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_rtc_raspberrypi_rp2040_rtc_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x4005C000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::reset_rtc;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::SPI0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_raspberrypi_rp2040_spi_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x4003C000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi0;
  static constexpr ResetId kResetId = ResetId::reset_spi0;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::SPI1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_raspberrypi_rp2040_spi_v1;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40040000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi1;
  static constexpr ResetId kResetId = ResetId::reset_spi1;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::TIMER> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_timer;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_timer_raspberrypi_rp2040_timer_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40054000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::reset_timer;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::UART0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_raspberrypi_rp2040_uart_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40034000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart0;
  static constexpr ResetId kResetId = ResetId::reset_uart0;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::UART1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_raspberrypi_rp2040_uart_v1;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40038000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart1;
  static constexpr ResetId kResetId = ResetId::reset_uart1;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::WATCHDOG> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_watchdog;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_watchdog_raspberrypi_rp2040_watchdog_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40058000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template <PeripheralId Id>
[[nodiscard]] constexpr std::uintptr_t peripheral_base() noexcept {
  static_assert(PeripheralInstanceTraits<Id>::kPresent);
  return PeripheralInstanceTraits<Id>::kBaseAddress;
}

inline constexpr std::array<PeripheralId, 12> kRuntimePeripherals = {{
  PeripheralId::ADC,
  PeripheralId::DMA,
  PeripheralId::I2C0,
  PeripheralId::I2C1,
  PeripheralId::PWM,
  PeripheralId::RTC,
  PeripheralId::SPI0,
  PeripheralId::SPI1,
  PeripheralId::TIMER,
  PeripheralId::UART0,
  PeripheralId::UART1,
  PeripheralId::WATCHDOG,
}};
}
}
}
}
}
}
