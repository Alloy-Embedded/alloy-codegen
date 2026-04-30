#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70q21b {
template<PeripheralId Peripheral, ClockGateId Source>
struct ClockSourceValid : std::false_type {};

template<>
struct ClockSourceValid<PeripheralId::AFEC0, ClockGateId::gate_afec0> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::AFEC1, ClockGateId::gate_afec1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::DACC, ClockGateId::gate_dacc> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::GMAC, ClockGateId::gate_gmac> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::GPIOA, ClockGateId::gate_gpioa> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::GPIOB, ClockGateId::gate_gpiob> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::GPIOC, ClockGateId::gate_gpioc> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::GPIOD, ClockGateId::gate_gpiod> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::GPIOE, ClockGateId::gate_gpioe> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::HSMCI, ClockGateId::gate_hsmci> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::MCAN0, ClockGateId::gate_mcan0> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::MCAN1, ClockGateId::gate_mcan1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::PWM0, ClockGateId::gate_pwm0> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::PWM1, ClockGateId::gate_pwm1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::QSPI, ClockGateId::gate_qspi> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::RSWDT, ClockGateId::gate_rswdt> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::RTC, ClockGateId::gate_rtc> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::SPI0, ClockGateId::gate_spi0> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::SPI1, ClockGateId::gate_spi1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::TC0, ClockGateId::gate_tc0> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::TC1, ClockGateId::gate_tc1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::TC2, ClockGateId::gate_tc2> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::TC3, ClockGateId::gate_tc3> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::TWIHS0, ClockGateId::gate_twihs0> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::TWIHS1, ClockGateId::gate_twihs1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::TWIHS2, ClockGateId::gate_twihs2> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::UART0, ClockGateId::gate_uart0> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::UART1, ClockGateId::gate_uart1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::UART2, ClockGateId::gate_uart2> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::UART3, ClockGateId::gate_uart3> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::UART4, ClockGateId::gate_uart4> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::USART0, ClockGateId::gate_usart0> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::USART1, ClockGateId::gate_usart1> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::USART2, ClockGateId::gate_usart2> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::USBHS, ClockGateId::gate_usbhs> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::WDT, ClockGateId::gate_wdt> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct ClockSourceValid<PeripheralId::XDMAC, ClockGateId::gate_xdmac> : std::true_type {
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<PeripheralId Peripheral, ClockGateId Source>
concept ValidClockSource = ClockSourceValid<Peripheral, Source>::value;

namespace detail {
template<PeripheralId Peripheral, ClockGateId Source>
inline constexpr bool kInvalidClockSource = false;
}  // namespace detail

struct ClockSourceEntry {
  PeripheralId peripheral;
  ClockGateId source;
  ClockSelectorId selector;
};

inline constexpr std::array<ClockSourceEntry, 37> kClockSources = {{
  {PeripheralId::AFEC0, ClockGateId::gate_afec0, ClockSelectorId::none},
  {PeripheralId::AFEC1, ClockGateId::gate_afec1, ClockSelectorId::none},
  {PeripheralId::DACC, ClockGateId::gate_dacc, ClockSelectorId::none},
  {PeripheralId::GMAC, ClockGateId::gate_gmac, ClockSelectorId::none},
  {PeripheralId::GPIOA, ClockGateId::gate_gpioa, ClockSelectorId::none},
  {PeripheralId::GPIOB, ClockGateId::gate_gpiob, ClockSelectorId::none},
  {PeripheralId::GPIOC, ClockGateId::gate_gpioc, ClockSelectorId::none},
  {PeripheralId::GPIOD, ClockGateId::gate_gpiod, ClockSelectorId::none},
  {PeripheralId::GPIOE, ClockGateId::gate_gpioe, ClockSelectorId::none},
  {PeripheralId::HSMCI, ClockGateId::gate_hsmci, ClockSelectorId::none},
  {PeripheralId::MCAN0, ClockGateId::gate_mcan0, ClockSelectorId::none},
  {PeripheralId::MCAN1, ClockGateId::gate_mcan1, ClockSelectorId::none},
  {PeripheralId::PWM0, ClockGateId::gate_pwm0, ClockSelectorId::none},
  {PeripheralId::PWM1, ClockGateId::gate_pwm1, ClockSelectorId::none},
  {PeripheralId::QSPI, ClockGateId::gate_qspi, ClockSelectorId::none},
  {PeripheralId::RSWDT, ClockGateId::gate_rswdt, ClockSelectorId::none},
  {PeripheralId::RTC, ClockGateId::gate_rtc, ClockSelectorId::none},
  {PeripheralId::SPI0, ClockGateId::gate_spi0, ClockSelectorId::none},
  {PeripheralId::SPI1, ClockGateId::gate_spi1, ClockSelectorId::none},
  {PeripheralId::TC0, ClockGateId::gate_tc0, ClockSelectorId::none},
  {PeripheralId::TC1, ClockGateId::gate_tc1, ClockSelectorId::none},
  {PeripheralId::TC2, ClockGateId::gate_tc2, ClockSelectorId::none},
  {PeripheralId::TC3, ClockGateId::gate_tc3, ClockSelectorId::none},
  {PeripheralId::TWIHS0, ClockGateId::gate_twihs0, ClockSelectorId::none},
  {PeripheralId::TWIHS1, ClockGateId::gate_twihs1, ClockSelectorId::none},
  {PeripheralId::TWIHS2, ClockGateId::gate_twihs2, ClockSelectorId::none},
  {PeripheralId::UART0, ClockGateId::gate_uart0, ClockSelectorId::none},
  {PeripheralId::UART1, ClockGateId::gate_uart1, ClockSelectorId::none},
  {PeripheralId::UART2, ClockGateId::gate_uart2, ClockSelectorId::none},
  {PeripheralId::UART3, ClockGateId::gate_uart3, ClockSelectorId::none},
  {PeripheralId::UART4, ClockGateId::gate_uart4, ClockSelectorId::none},
  {PeripheralId::USART0, ClockGateId::gate_usart0, ClockSelectorId::none},
  {PeripheralId::USART1, ClockGateId::gate_usart1, ClockSelectorId::none},
  {PeripheralId::USART2, ClockGateId::gate_usart2, ClockSelectorId::none},
  {PeripheralId::USBHS, ClockGateId::gate_usbhs, ClockSelectorId::none},
  {PeripheralId::WDT, ClockGateId::gate_wdt, ClockSelectorId::none},
  {PeripheralId::XDMAC, ClockGateId::gate_xdmac, ClockSelectorId::none},
}};

constexpr bool is_valid_clock_source(PeripheralId peripheral, ClockGateId source) noexcept {
  for (auto const& entry : kClockSources) {
    if (entry.peripheral == peripheral && entry.source == source) {
      return true;
    }
  }
  return false;
}
}
}
}
}
}
}
