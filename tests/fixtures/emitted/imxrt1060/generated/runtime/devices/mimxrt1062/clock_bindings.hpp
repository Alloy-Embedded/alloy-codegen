#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "peripheral_instances.hpp"
#include "registers.hpp"
#include "register_fields.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
template<ClockGateId Id>
struct ClockGateTraits {
  static constexpr bool kPresent = false;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<>
struct ClockGateTraits<ClockGateId::gate_gpio1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr1;
  static constexpr FieldId kFieldId = FieldId::field_ccm_ccgr1_cg13;
};

template<>
struct ClockGateTraits<ClockGateId::gate_gpio4> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr3;
  static constexpr FieldId kFieldId = FieldId::field_ccm_ccgr3_cg13;
};

template<>
struct ClockGateTraits<ClockGateId::gate_lpspi1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr1;
  static constexpr FieldId kFieldId = FieldId::field_ccm_ccgr1_cg0;
};

template<>
struct ClockGateTraits<ClockGateId::gate_lpuart1> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr5;
  static constexpr FieldId kFieldId = FieldId::field_ccm_ccgr5_cg12;
};

template<>
struct ClockGateTraits<ClockGateId::gate_lpuart3> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_ccgr0;
  static constexpr FieldId kFieldId = FieldId::field_ccm_ccgr0_cg6;
};

template<ResetId Id>
struct ResetTraits {
  static constexpr bool kPresent = false;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr FieldId kFieldId = FieldId::none;
  static constexpr ActiveLevelId kActiveLevelId = ActiveLevelId::none;
};

template<ClockSelectorId Id>
struct ClockSelectorTraits {
  static constexpr bool kPresent = false;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<>
struct ClockSelectorTraits<ClockSelectorId::selector_lpspi_root> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_cbcmr;
  static constexpr FieldId kFieldId = FieldId::field_ccm_cbcmr_lpspi_clk_sel;
};

template<>
struct ClockSelectorTraits<ClockSelectorId::selector_lpuart_root> {
  static constexpr bool kPresent = true;
  static constexpr RegisterId kRegisterId = RegisterId::register_ccm_cscdr1;
  static constexpr FieldId kFieldId = FieldId::field_ccm_cscdr1_uart_clk_sel;
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
struct PeripheralClockBindingTraits<PeripheralId::ADC2> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::CAN1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::CAN2> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::CAN3> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::DMA0> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::DMAMUX1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::ENET> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::GPIO1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpio1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::GPIO4> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpio4;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::GPT1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::GPT2> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::LPSPI1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_lpspi1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::selector_lpspi_root;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::LPUART1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_lpuart1;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::selector_lpuart_root;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::LPUART3> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_lpuart3;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::PIT> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::PWM1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::PWM2> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::PWM3> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::PWM4> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::RTWDOG> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::USB1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::WDOG1> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

template<>
struct PeripheralClockBindingTraits<PeripheralId::WDOG2> {
  static constexpr bool kPresent = true;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ResetId kResetId = ResetId::none;
  static constexpr ClockSelectorId kSelectorId = ClockSelectorId::none;
};

inline constexpr std::array<PeripheralId, 24> kClockBoundPeripherals = {{
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
inline auto clock_enable<PeripheralId::GPIO1>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x400FC06Cu);
  *reg = *reg | (1u << 26);
}
template <>
inline auto clock_disable<PeripheralId::GPIO1>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x400FC06Cu);
  *reg = *reg & ~(1u << 26);
}

template <>
inline auto clock_enable<PeripheralId::GPIO4>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x400FC074u);
  *reg = *reg | (1u << 26);
}
template <>
inline auto clock_disable<PeripheralId::GPIO4>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x400FC074u);
  *reg = *reg & ~(1u << 26);
}

template <>
inline auto clock_enable<PeripheralId::LPSPI1>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x400FC06Cu);
  *reg = *reg | (1u << 0);
}
template <>
inline auto clock_disable<PeripheralId::LPSPI1>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x400FC06Cu);
  *reg = *reg & ~(1u << 0);
}

template <>
inline auto clock_enable<PeripheralId::LPUART1>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x400FC07Cu);
  *reg = *reg | (1u << 24);
}
template <>
inline auto clock_disable<PeripheralId::LPUART1>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x400FC07Cu);
  *reg = *reg & ~(1u << 24);
}

template <>
inline auto clock_enable<PeripheralId::LPUART3>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x400FC068u);
  *reg = *reg | (1u << 12);
}
template <>
inline auto clock_disable<PeripheralId::LPUART3>() noexcept -> void {
  auto* reg = reinterpret_cast<volatile std::uint32_t*>(0x400FC068u);
  *reg = *reg & ~(1u << 12);
}

}
}
}
}
}
}
