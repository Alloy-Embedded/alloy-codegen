#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70q21b {
enum class PeripheralId : std::uint16_t {
  none,
  AFEC0,
  AFEC1,
  DACC,
  GMAC,
  GPIOA,
  GPIOB,
  GPIOC,
  GPIOD,
  GPIOE,
  HSMCI,
  MCAN0,
  MCAN1,
  PWM0,
  PWM1,
  QSPI,
  RSWDT,
  RTC,
  SPI0,
  SPI1,
  TC0,
  TC1,
  TC2,
  TC3,
  TWIHS0,
  TWIHS1,
  TWIHS2,
  UART0,
  UART1,
  UART2,
  UART3,
  UART4,
  USART0,
  USART1,
  USART2,
  USBHS,
  WDT,
  XDMAC,
};

enum class ClockGateId : std::uint16_t {
  none,
  gate_afec0,
  gate_afec1,
  gate_dacc,
  gate_gmac,
  gate_gpioa,
  gate_gpiob,
  gate_gpioc,
  gate_gpiod,
  gate_gpioe,
  gate_hsmci,
  gate_mcan0,
  gate_mcan1,
  gate_pwm0,
  gate_pwm1,
  gate_qspi,
  gate_rswdt,
  gate_rtc,
  gate_spi0,
  gate_spi1,
  gate_tc0,
  gate_tc1,
  gate_tc2,
  gate_tc3,
  gate_twihs0,
  gate_twihs1,
  gate_twihs2,
  gate_uart0,
  gate_uart1,
  gate_uart2,
  gate_uart3,
  gate_uart4,
  gate_usart0,
  gate_usart1,
  gate_usart2,
  gate_usbhs,
  gate_wdt,
  gate_xdmac,
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
struct PeripheralInstanceTraits<PeripheralId::AFEC0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_adc_microchip_afec_s;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x4003C000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_afec0;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::AFEC1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_adc_microchip_afec_s;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40064000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_afec1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::DACC> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_dac;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dac_microchip_dacc_e;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40040000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_dacc;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::GMAC> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_eth;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_eth_microchip_gmac_s;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40050000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gmac;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::GPIOA> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpio_microchip_pio_v;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x400E0E00u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpioa;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::GPIOB> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpio_microchip_pio_v;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x400E1000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpiob;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::GPIOC> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpio_microchip_pio_v;
  static constexpr int kInstance = 2;
  static constexpr std::uintptr_t kBaseAddress = 0x400E1200u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpioc;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::GPIOD> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpio_microchip_pio_v;
  static constexpr int kInstance = 3;
  static constexpr std::uintptr_t kBaseAddress = 0x400E1400u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpiod;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::GPIOE> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpio_microchip_pio_v;
  static constexpr int kInstance = 4;
  static constexpr std::uintptr_t kBaseAddress = 0x400E1600u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpioe;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::HSMCI> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_sdmmc;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_hsmci_microchip_hsmci_r;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40000000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_hsmci;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::MCAN0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_can;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_can_microchip_mcan_n;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40030000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_mcan0;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::MCAN1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_can;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_can_microchip_mcan_n;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40034000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_mcan1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::PWM0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_pwm;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_pwm_microchip_pwm_y;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40020000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_pwm0;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::PWM1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_pwm;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_pwm_microchip_pwm_y;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x4005C000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_pwm1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::QSPI> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_qspi;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_qspi_microchip_qspi_j;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x4007C000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_qspi;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::RSWDT> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_watchdog;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_watchdog_microchip_rswdt_g;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x400E1900u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_rswdt;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::RTC> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_rtc;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_rtc_microchip_rtc_zb;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x400E1860u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_rtc;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::SPI0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_microchip_spi_zm;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40008000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi0;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::SPI1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_microchip_spi_zm;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40058000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::TC0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_timer;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_timer_microchip_tc_zl;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x4000C000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_tc0;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::TC1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_timer;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_timer_microchip_tc_zl;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40010000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_tc1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::TC2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_timer;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_timer_microchip_tc_zl;
  static constexpr int kInstance = 2;
  static constexpr std::uintptr_t kBaseAddress = 0x40014000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_tc2;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::TC3> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_timer;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_timer_microchip_tc_zl;
  static constexpr int kInstance = 3;
  static constexpr std::uintptr_t kBaseAddress = 0x40054000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_tc3;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::TWIHS0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_i2c;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_i2c_microchip_twihs_z;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40018000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_twihs0;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::TWIHS1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_i2c;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_i2c_microchip_twihs_z;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x4001C000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_twihs1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::TWIHS2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_i2c;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_i2c_microchip_twihs_z;
  static constexpr int kInstance = 2;
  static constexpr std::uintptr_t kBaseAddress = 0x40060000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_twihs2;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::UART0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_uart_r;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x400E0800u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart0;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::UART1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_uart_r;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x400E0A00u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::UART2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_uart_r;
  static constexpr int kInstance = 2;
  static constexpr std::uintptr_t kBaseAddress = 0x400E1A00u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart2;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::UART3> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_uart_r;
  static constexpr int kInstance = 3;
  static constexpr std::uintptr_t kBaseAddress = 0x400E1C00u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart3;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::UART4> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_uart_r;
  static constexpr int kInstance = 4;
  static constexpr std::uintptr_t kBaseAddress = 0x400E1E00u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart4;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::USART0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_usart_zw;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40024000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usart0;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::USART1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_usart_zw;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40028000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usart1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::USART2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_microchip_usart_zw;
  static constexpr int kInstance = 2;
  static constexpr std::uintptr_t kBaseAddress = 0x4002C000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usart2;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::USBHS> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_usb;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_usb_microchip_usbhs_g;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40038000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usbhs;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::WDT> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_watchdog;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_watchdog_microchip_wdt_n;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x400E1850u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_wdt;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::XDMAC> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_dma;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dma_microchip_xdmac_k;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40078000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_xdmac;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template <PeripheralId Id>
[[nodiscard]] constexpr std::uintptr_t peripheral_base() noexcept {
  static_assert(PeripheralInstanceTraits<Id>::kPresent);
  return PeripheralInstanceTraits<Id>::kBaseAddress;
}

inline constexpr std::array<PeripheralId, 37> kRuntimePeripherals = {{
  PeripheralId::AFEC0,
  PeripheralId::AFEC1,
  PeripheralId::DACC,
  PeripheralId::GMAC,
  PeripheralId::GPIOA,
  PeripheralId::GPIOB,
  PeripheralId::GPIOC,
  PeripheralId::GPIOD,
  PeripheralId::GPIOE,
  PeripheralId::HSMCI,
  PeripheralId::MCAN0,
  PeripheralId::MCAN1,
  PeripheralId::PWM0,
  PeripheralId::PWM1,
  PeripheralId::QSPI,
  PeripheralId::RSWDT,
  PeripheralId::RTC,
  PeripheralId::SPI0,
  PeripheralId::SPI1,
  PeripheralId::TC0,
  PeripheralId::TC1,
  PeripheralId::TC2,
  PeripheralId::TC3,
  PeripheralId::TWIHS0,
  PeripheralId::TWIHS1,
  PeripheralId::TWIHS2,
  PeripheralId::UART0,
  PeripheralId::UART1,
  PeripheralId::UART2,
  PeripheralId::UART3,
  PeripheralId::UART4,
  PeripheralId::USART0,
  PeripheralId::USART1,
  PeripheralId::USART2,
  PeripheralId::USBHS,
  PeripheralId::WDT,
  PeripheralId::XDMAC,
}};
}
}
}
}
}
}
