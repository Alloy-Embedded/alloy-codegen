#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "peripheral_instances.hpp"
#include "registers.hpp"
#include "register_fields.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace pico {
template<ClockGateId Id>
struct ClockGateTraits {
  static constexpr bool kPresent = false;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<>
struct ClockGateTraits<ClockGateId::gate_adc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_adc;
};

template<>
struct ClockGateTraits<ClockGateId::gate_dma> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_dma;
};

template<>
struct ClockGateTraits<ClockGateId::gate_i2c0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_i2c0;
};

template<>
struct ClockGateTraits<ClockGateId::gate_i2c1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_i2c1;
};

template<>
struct ClockGateTraits<ClockGateId::gate_spi0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_spi0;
};

template<>
struct ClockGateTraits<ClockGateId::gate_spi1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_spi1;
};

template<>
struct ClockGateTraits<ClockGateId::gate_uart0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_uart0;
};

template<>
struct ClockGateTraits<ClockGateId::gate_uart1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_uart1;
};

template<ResetId Id>
struct ResetTraits {
  static constexpr bool kPresent = false;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr FieldId kFieldId = FieldId::none;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::none;
};

template<>
struct ResetTraits<ResetId::reset_adc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_adc;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_dma> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_dma;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_i2c0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_i2c0;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_i2c1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_i2c1;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_pwm> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_pwm;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_rtc> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_rtc;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_spi0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_spi0;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_spi1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_spi1;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_timer> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_timer;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_uart0> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_uart0;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_uart1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_resets_reset;
  static constexpr FieldId kFieldId = FieldId::field_resets_reset_uart1;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<ClockSelectorId Id>
struct ClockSelectorTraits {
  static constexpr bool kPresent = false;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<PeripheralId Id>
struct PeripheralClockBindingTraits {
  static constexpr bool kPresent = false;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::ADC> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_adc;
  static constexpr ResetId kResetId = ResetId::reset_adc;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::DMA> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_dma;
  static constexpr ResetId kResetId = ResetId::reset_dma;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::I2C0> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_i2c0;
  static constexpr ResetId kResetId = ResetId::reset_i2c0;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::I2C1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_i2c1;
  static constexpr ResetId kResetId = ResetId::reset_i2c1;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::PWM> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::reset_pwm;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::RTC> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::reset_rtc;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::SPI0> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi0;
  static constexpr ResetId kResetId = ResetId::reset_spi0;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::SPI1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi1;
  static constexpr ResetId kResetId = ResetId::reset_spi1;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::TIMER> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::reset_timer;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::UART0> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart0;
  static constexpr ResetId kResetId = ResetId::reset_uart0;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::UART1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart1;
  static constexpr ResetId kResetId = ResetId::reset_uart1;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::WATCHDOG> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

inline constexpr std::array<PeripheralId, 12> kClockBoundPeripherals = {{
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

template <auto> inline constexpr bool kClockBindingDependentFalse = false;

template <PeripheralId Id>
inline auto clock_enable() noexcept -> void {
  static_assert(kClockBindingDependentFalse<Id>, "");
}

template <PeripheralId Id>
inline auto clock_disable() noexcept -> void {
  static_assert(kClockBindingDependentFalse<Id>, "");
}

}
}
}
}
}
}
