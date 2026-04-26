#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace microchip {
namespace avr_da {
namespace generated {
namespace runtime {
namespace devices {
namespace avr128da32 {
enum class PeripheralId : std::uint16_t {
  none,
  ADC0,
  SPI0,
  TCA0,
  TWI0,
  USART0,
  USART1,
};

enum class ClockGateId : std::uint16_t {
  none,
};

enum class ResetId : std::uint16_t {
  none,
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
struct PeripheralInstanceTraits<PeripheralId::ADC0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_adc_microchip_avr_da_adc_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x00000000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::SPI0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_microchip_avr_da_spi_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x000008C0u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::TCA0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_timer;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_timer_microchip_avr_da_tca_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x00000A00u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::TWI0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_i2c;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_i2c_microchip_avr_da_twi_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x000008A0u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::USART0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_avr_da_usart_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x00000800u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::USART1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_avr_da_usart_v1;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x00000820u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template <PeripheralId Id>
[[nodiscard]] constexpr std::uintptr_t peripheral_base() noexcept {
  static_assert(PeripheralInstanceTraits<Id>::kPresent);
  return PeripheralInstanceTraits<Id>::kBaseAddress;
}

inline constexpr std::array<PeripheralId, 6> kRuntimePeripherals = {{
  PeripheralId::ADC0,
  PeripheralId::SPI0,
  PeripheralId::TCA0,
  PeripheralId::TWI0,
  PeripheralId::USART0,
  PeripheralId::USART1,
}};
}
}
}
}
}
}
