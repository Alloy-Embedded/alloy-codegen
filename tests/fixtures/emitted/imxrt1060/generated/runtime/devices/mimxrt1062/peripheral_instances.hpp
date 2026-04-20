#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
enum class PeripheralId : std::uint16_t {
  none,
  ADC1,
  ADC2,
  CAN1,
  CAN2,
  CAN3,
  DMA0,
  DMAMUX1,
  GPIO1,
  GPIO4,
  GPT1,
  GPT2,
  LPSPI1,
  LPUART1,
  LPUART3,
  PIT,
  PWM1,
  PWM2,
  PWM3,
  PWM4,
  RTWDOG,
  WDOG1,
  WDOG2,
};

enum class ClockGateId : std::uint16_t {
  none,
  gate_gpio1,
  gate_gpio4,
  gate_lpspi1,
  gate_lpuart1,
  gate_lpuart3,
};

enum class ResetId : std::uint16_t {
  none,
};

enum class ClockSelectorId : std::uint16_t {
  none,
  selector_lpspi_root,
  selector_lpuart_root,
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
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_adc_nxp_adc;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x400C5000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::ADC2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_adc;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_adc_nxp_adc;
  static constexpr int kInstance = 2;
  static constexpr std::uintptr_t kBaseAddress = 0x400C9000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::CAN1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_can;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_can_nxp_can;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x401CF800u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::CAN2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_can;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_can_nxp_can;
  static constexpr int kInstance = 2;
  static constexpr std::uintptr_t kBaseAddress = 0x401D3800u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::CAN3> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_can;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_can_nxp_can;
  static constexpr int kInstance = 3;
  static constexpr std::uintptr_t kBaseAddress = 0x401D7800u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::DMA0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_dma;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dma_nxp_dma;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x400E9000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::DMAMUX1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_dma_router;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dma_router_nxp_dmamux;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x400ED000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::GPIO1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpio_nxp_imxrt_gpio_v1;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x401B8000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpio1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::GPIO4> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_gpio;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpio_nxp_imxrt_gpio_v1;
  static constexpr int kInstance = 4;
  static constexpr std::uintptr_t kBaseAddress = 0x401C4000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpio4;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::GPT1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_timer;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpt_nxp_gpt;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x401EB800u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::GPT2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_timer;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_gpt_nxp_gpt;
  static constexpr int kInstance = 2;
  static constexpr std::uintptr_t kBaseAddress = 0x401EF800u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::LPSPI1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_spi;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_spi_nxp_lpspi_v1;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40394000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_lpspi1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::selector_lpspi_root;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::LPUART1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_nxp_lpuart_v1;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x40184000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_lpuart1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::selector_lpuart_root;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::LPUART3> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_uart;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_uart_nxp_lpuart_v1;
  static constexpr int kInstance = 3;
  static constexpr std::uintptr_t kBaseAddress = 0x4018C000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_lpuart3;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::PIT> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_timer;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_pit_nxp_pit;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x40085000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::PWM1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_pwm;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_pwm_nxp_pwm;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x403DE800u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::PWM2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_pwm;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_pwm_nxp_pwm;
  static constexpr int kInstance = 2;
  static constexpr std::uintptr_t kBaseAddress = 0x403E2800u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::PWM3> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_pwm;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_pwm_nxp_pwm;
  static constexpr int kInstance = 3;
  static constexpr std::uintptr_t kBaseAddress = 0x403E6800u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::PWM4> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_pwm;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_pwm_nxp_pwm;
  static constexpr int kInstance = 4;
  static constexpr std::uintptr_t kBaseAddress = 0x403EA800u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::RTWDOG> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_watchdog;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_watchdog_nxp_rtwdog;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x400BD000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::WDOG1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_watchdog;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_watchdog_nxp_wdog;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x400B9000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::WDOG2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_watchdog;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_watchdog_nxp_wdog;
  static constexpr int kInstance = 2;
  static constexpr std::uintptr_t kBaseAddress = 0x400D1000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

inline constexpr std::array<PeripheralId, 22> kRuntimePeripherals = {{
  PeripheralId::ADC1,
  PeripheralId::ADC2,
  PeripheralId::CAN1,
  PeripheralId::CAN2,
  PeripheralId::CAN3,
  PeripheralId::DMA0,
  PeripheralId::DMAMUX1,
  PeripheralId::GPIO1,
  PeripheralId::GPIO4,
  PeripheralId::GPT1,
  PeripheralId::GPT2,
  PeripheralId::LPSPI1,
  PeripheralId::LPUART1,
  PeripheralId::LPUART3,
  PeripheralId::PIT,
  PeripheralId::PWM1,
  PeripheralId::PWM2,
  PeripheralId::PWM3,
  PeripheralId::PWM4,
  PeripheralId::RTWDOG,
  PeripheralId::WDOG1,
  PeripheralId::WDOG2,
}};
}
}
}
}
}
}
