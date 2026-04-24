#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1064 {
enum class PeripheralId : std::uint16_t {
  none,
  ADC1,
  ADC2,
  CAN1,
  CAN2,
  CAN3,
  DMA0,
  DMAMUX1,
  ENET,
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
  USB1,
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
  static constexpr std::uintptr_t kBaseAddress = 0x400C4000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x400C8000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x401D0000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x401D4000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x401D8000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x400E8000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x400EC000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::ENET> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_eth;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_eth_nxp_enet;
  static constexpr int kInstance = 0;
  static constexpr std::uintptr_t kBaseAddress = 0x402D8000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x401EC000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x401F0000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x40084000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x403DC000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x403E0000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x403E4000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x403E8000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x400BC000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralInstanceTraits<PeripheralId::USB1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralClassId kPeripheralClassId = PeripheralClassId::class_usb;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_usb_nxp_usb;
  static constexpr int kInstance = 1;
  static constexpr std::uintptr_t kBaseAddress = 0x402E0000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x400B8000u;
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
  static constexpr std::uintptr_t kBaseAddress = 0x400D0000u;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template <PeripheralId Id>
[[nodiscard]] constexpr std::uintptr_t peripheral_base() noexcept {
  static_assert(PeripheralInstanceTraits<Id>::kPresent);
  return PeripheralInstanceTraits<Id>::kBaseAddress;
}

inline constexpr std::array<PeripheralId, 24> kRuntimePeripherals = {{
  PeripheralId::ADC1,
  PeripheralId::ADC2,
  PeripheralId::CAN1,
  PeripheralId::CAN2,
  PeripheralId::CAN3,
  PeripheralId::DMA0,
  PeripheralId::DMAMUX1,
  PeripheralId::ENET,
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
  PeripheralId::USB1,
  PeripheralId::WDOG1,
  PeripheralId::WDOG2,
}};
}
}
}
}
}
}
