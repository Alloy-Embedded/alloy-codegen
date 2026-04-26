#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace espressif {
namespace esp32s3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32s3 {
enum class PeripheralId : std::uint16_t {
  none,
  APB_SARADC,
  DMA,
  GPIO,
  I2C0,
  I2C1,
  SENS,
  SPI0,
  SPI1,
  SPI2,
  SPI3,
  UART0,
  UART1,
  UART2,
  USB0,
};

enum class ClockGateId : std::uint16_t {
  none,
  gate_i2c0,
  gate_i2c1,
  gate_spi2,
  gate_spi3,
  gate_uart0,
  gate_uart1,
  gate_uart2,
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
struct PeripheralInstanceTraits<PeripheralId::APB_SARADC> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_adc_espressif_esp32s3_saradc_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x60040000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::DMA> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_dma;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dma_espressif_esp32s3_gdma_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x6003F000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::GPIO> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpio_espressif_esp32s3_gpio_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x60004000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::I2C0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_i2c;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_i2c_espressif_esp32s3_i2c_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x60013000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_i2c0;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::I2C1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_i2c;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_i2c_espressif_esp32s3_i2c_v1;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x60027000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_i2c1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::SENS> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_adc_espressif_sens;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x60008800u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::SPI0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_espressif_spi;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x60003000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::SPI1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_espressif_spi;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x60002000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::SPI2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_espressif_esp32s3_spi_v1;
  static constexpr int kInstance = 2;
  static constexpr std::uintptr_t kBaseAddress = 0x60024000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi2;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::SPI3> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_espressif_esp32s3_spi_v1;
  static constexpr int kInstance = 3;
  static constexpr std::uintptr_t kBaseAddress = 0x60025000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi3;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::UART0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_espressif_esp32s3_uart_v1;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x60000000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart0;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::UART1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_espressif_esp32s3_uart_v1;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x60010000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::UART2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_espressif_esp32s3_uart_v1;
  static constexpr int kInstance = 2;
  static constexpr std::uintptr_t kBaseAddress = 0x6002E000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart2;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::USB0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_usb;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_usb_espressif_usb;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x60080000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template <PeripheralId Id>
[[nodiscard]] constexpr std::uintptr_t peripheral_base() noexcept {
  static_assert(PeripheralInstanceTraits<Id>::kPresent);
  return PeripheralInstanceTraits<Id>::kBaseAddress;
}

inline constexpr std::array<PeripheralId, 14> kRuntimePeripherals = {{
  PeripheralId::APB_SARADC,
  PeripheralId::DMA,
  PeripheralId::GPIO,
  PeripheralId::I2C0,
  PeripheralId::I2C1,
  PeripheralId::SENS,
  PeripheralId::SPI0,
  PeripheralId::SPI1,
  PeripheralId::SPI2,
  PeripheralId::SPI3,
  PeripheralId::UART0,
  PeripheralId::UART1,
  PeripheralId::UART2,
  PeripheralId::USB0,
}};
}
}
}
}
}
}
