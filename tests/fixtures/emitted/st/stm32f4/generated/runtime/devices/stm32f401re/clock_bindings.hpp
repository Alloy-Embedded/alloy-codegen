#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "peripheral_instances.hpp"
#include "registers.hpp"
#include "register_fields.hpp"

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f401re {
template<ClockGateId Id>
struct ClockGateTraits {
  static constexpr bool kPresent = false;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<>
struct ClockGateTraits<ClockGateId::gate_dma1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb1enr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb1enr_dma1en;
};

template<>
struct ClockGateTraits<ClockGateId::gate_dma2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb1enr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb1enr_dma2en;
};

template<>
struct ClockGateTraits<ClockGateId::gate_gpioa> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb1enr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb1enr_gpioaen;
};

template<>
struct ClockGateTraits<ClockGateId::gate_gpiob> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb1enr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb1enr_gpioben;
};

template<>
struct ClockGateTraits<ClockGateId::gate_otg_fs> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb2enr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb2enr_otgfsen;
};

template<>
struct ClockGateTraits<ClockGateId::gate_spi1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apb2enr;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<>
struct ClockGateTraits<ClockGateId::gate_tim1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apb2enr;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<>
struct ClockGateTraits<ClockGateId::gate_usart1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apb2enr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_apb2enr_usart1en;
};

template<>
struct ClockGateTraits<ClockGateId::gate_usart2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apb1enr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_apb1enr_usart2en;
};

template<ResetId Id>
struct ResetTraits {
  static constexpr bool kPresent = false;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr FieldId kFieldId = FieldId::none;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::none;
};

template<>
struct ResetTraits<ResetId::reset_dma1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb1rstr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb1rstr_dma1rst;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_dma2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb1rstr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb1rstr_dma2rst;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_gpioa> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb1rstr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb1rstr_gpioarst;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_gpiob> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb1rstr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb1rstr_gpiobrst;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_otg_fs> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_ahb2rstr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_ahb2rstr_otgfsrst;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_spi1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apb2rstr;
  static constexpr FieldId kFieldId = FieldId::none;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_tim1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apb2rstr;
  static constexpr FieldId kFieldId = FieldId::none;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_usart1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apb2rstr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_apb2rstr_usart1rst;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::active_level_high;
};

template<>
struct ResetTraits<ResetId::reset_usart2> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_rcc_apb1rstr;
  static constexpr FieldId kFieldId = FieldId::field_rcc_apb1rstr_usart2rst;
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
struct PeripheralClockBindingTraits<PeripheralId::ADC1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::DMA1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_dma1;
  static constexpr ResetId kResetId = ResetId::reset_dma1;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::DMA2> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_dma2;
  static constexpr ResetId kResetId = ResetId::reset_dma2;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::GPIOA> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpioa;
  static constexpr ResetId kResetId = ResetId::reset_gpioa;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::GPIOB> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpiob;
  static constexpr ResetId kResetId = ResetId::reset_gpiob;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::IWDG> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::OTG_FS> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_otg_fs;
  static constexpr ResetId kResetId = ResetId::reset_otg_fs;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::RTC> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
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
struct PeripheralClockBindingTraits<PeripheralId::TIM1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_tim1;
  static constexpr ResetId kResetId = ResetId::reset_tim1;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::USART1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usart1;
  static constexpr ResetId kResetId = ResetId::reset_usart1;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::USART2> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usart2;
  static constexpr ResetId kResetId = ResetId::reset_usart2;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

inline constexpr std::array<PeripheralId, 12> kClockBoundPeripherals = {{
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

template <auto> inline constexpr bool kClockBindingDependentFalse = false;

template <PeripheralId Id>
inline auto clock_enable() noexcept -> void {
  static_assert(kClockBindingDependentFalse<Id>, "");
}

template <PeripheralId Id>
inline auto clock_disable() noexcept -> void {
  static_assert(kClockBindingDependentFalse<Id>, "");
}

template <>
inline auto clock_enable<PeripheralId::DMA1>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x40023830u);
  *reg = *reg | (1u << 21);
}
template <>
inline auto clock_disable<PeripheralId::DMA1>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x40023830u);
  *reg = *reg & ~(1u << 21);
}

template <>
inline auto clock_enable<PeripheralId::DMA2>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x40023830u);
  *reg = *reg | (1u << 22);
}
template <>
inline auto clock_disable<PeripheralId::DMA2>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x40023830u);
  *reg = *reg & ~(1u << 22);
}

template <>
inline auto clock_enable<PeripheralId::GPIOA>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x40023830u);
  *reg = *reg | (1u << 0);
}
template <>
inline auto clock_disable<PeripheralId::GPIOA>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x40023830u);
  *reg = *reg & ~(1u << 0);
}

template <>
inline auto clock_enable<PeripheralId::GPIOB>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x40023830u);
  *reg = *reg | (1u << 1);
}
template <>
inline auto clock_disable<PeripheralId::GPIOB>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x40023830u);
  *reg = *reg & ~(1u << 1);
}

template <>
inline auto clock_enable<PeripheralId::OTG_FS>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x40023834u);
  *reg = *reg | (1u << 7);
}
template <>
inline auto clock_disable<PeripheralId::OTG_FS>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x40023834u);
  *reg = *reg & ~(1u << 7);
}

template <>
inline auto clock_enable<PeripheralId::USART1>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x40023844u);
  *reg = *reg | (1u << 4);
}
template <>
inline auto clock_disable<PeripheralId::USART1>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x40023844u);
  *reg = *reg & ~(1u << 4);
}

template <>
inline auto clock_enable<PeripheralId::USART2>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x40023840u);
  *reg = *reg | (1u << 17);
}
template <>
inline auto clock_disable<PeripheralId::USART2>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x40023840u);
  *reg = *reg & ~(1u << 17);
}

}
}
}
}
}
}
