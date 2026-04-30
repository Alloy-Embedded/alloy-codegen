#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "clock_bindings.hpp"
#include "clock_graph.hpp"
#include "peripheral_instances.hpp"
#include "register_fields.hpp"
#include "registers.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70n21b {
using EnableDomainId = ClockGateId;

struct EnableDomainDescriptor {
  EnableDomainId enable_domain_id;
  PeripheralId peripheral_id;
  ClockGateId clock_gate_id;
  ClockNodeId parent_clock_node_id;
  RegisterId register_id;
  FieldId field_id;
};
inline constexpr std::array<EnableDomainDescriptor, 34> kEnableDomains = {{
  {EnableDomainId::gate_afec0, PeripheralId::AFEC0, ClockGateId::gate_afec0, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid29},
  {EnableDomainId::gate_afec1, PeripheralId::AFEC1, ClockGateId::gate_afec1, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid40},
  {EnableDomainId::gate_dacc, PeripheralId::DACC, ClockGateId::gate_dacc, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid30},
  {EnableDomainId::gate_gmac, PeripheralId::GMAC, ClockGateId::gate_gmac, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid39},
  {EnableDomainId::gate_gpioa, PeripheralId::GPIOA, ClockGateId::gate_gpioa, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid10},
  {EnableDomainId::gate_gpiob, PeripheralId::GPIOB, ClockGateId::gate_gpiob, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid11},
  {EnableDomainId::gate_gpiod, PeripheralId::GPIOD, ClockGateId::gate_gpiod, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid16},
  {EnableDomainId::gate_hsmci, PeripheralId::HSMCI, ClockGateId::gate_hsmci, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid18},
  {EnableDomainId::gate_mcan0, PeripheralId::MCAN0, ClockGateId::gate_mcan0, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid35},
  {EnableDomainId::gate_mcan1, PeripheralId::MCAN1, ClockGateId::gate_mcan1, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid37},
  {EnableDomainId::gate_pwm0, PeripheralId::PWM0, ClockGateId::gate_pwm0, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid31},
  {EnableDomainId::gate_pwm1, PeripheralId::PWM1, ClockGateId::gate_pwm1, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid60},
  {EnableDomainId::gate_qspi, PeripheralId::QSPI, ClockGateId::gate_qspi, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid43},
  {EnableDomainId::gate_rswdt, PeripheralId::RSWDT, ClockGateId::gate_rswdt, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::none},
  {EnableDomainId::gate_rtc, PeripheralId::RTC, ClockGateId::gate_rtc, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::none},
  {EnableDomainId::gate_spi0, PeripheralId::SPI0, ClockGateId::gate_spi0, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid21},
  {EnableDomainId::gate_tc0, PeripheralId::TC0, ClockGateId::gate_tc0, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid23},
  {EnableDomainId::gate_tc1, PeripheralId::TC1, ClockGateId::gate_tc1, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid26},
  {EnableDomainId::gate_tc2, PeripheralId::TC2, ClockGateId::gate_tc2, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid47},
  {EnableDomainId::gate_tc3, PeripheralId::TC3, ClockGateId::gate_tc3, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid50},
  {EnableDomainId::gate_twihs0, PeripheralId::TWIHS0, ClockGateId::gate_twihs0, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid19},
  {EnableDomainId::gate_twihs1, PeripheralId::TWIHS1, ClockGateId::gate_twihs1, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid20},
  {EnableDomainId::gate_twihs2, PeripheralId::TWIHS2, ClockGateId::gate_twihs2, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid41},
  {EnableDomainId::gate_uart0, PeripheralId::UART0, ClockGateId::gate_uart0, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid7},
  {EnableDomainId::gate_uart1, PeripheralId::UART1, ClockGateId::gate_uart1, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid8},
  {EnableDomainId::gate_uart2, PeripheralId::UART2, ClockGateId::gate_uart2, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid44},
  {EnableDomainId::gate_uart3, PeripheralId::UART3, ClockGateId::gate_uart3, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid45},
  {EnableDomainId::gate_uart4, PeripheralId::UART4, ClockGateId::gate_uart4, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid46},
  {EnableDomainId::gate_usart0, PeripheralId::USART0, ClockGateId::gate_usart0, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid13},
  {EnableDomainId::gate_usart1, PeripheralId::USART1, ClockGateId::gate_usart1, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid14},
  {EnableDomainId::gate_usart2, PeripheralId::USART2, ClockGateId::gate_usart2, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::field_pmc_pcer0_pid15},
  {EnableDomainId::gate_usbhs, PeripheralId::USBHS, ClockGateId::gate_usbhs, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid34},
  {EnableDomainId::gate_wdt, PeripheralId::WDT, ClockGateId::gate_wdt, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer0, FieldId::none},
  {EnableDomainId::gate_xdmac, PeripheralId::XDMAC, ClockGateId::gate_xdmac, ClockNodeId::clock_node_pmc, RegisterId::register_pmc_pcer1, FieldId::field_pmc_pcer1_pid58},
}};

template<EnableDomainId Id>
struct EnableDomainTraits {
  static constexpr bool kPresent = false;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr ClockGateId kClockGateId = ClockGateId::none;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::none;
  static constexpr RegisterId kRegisterId = RegisterId::none;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<PeripheralId Id>
struct PeripheralEnableDomainTraits {
  static constexpr bool kPresent = false;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::none;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_afec0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::AFEC0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_afec0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid29;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::AFEC0> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_afec0;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_afec1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::AFEC1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_afec1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer1_pid40;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::AFEC1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_afec1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_dacc> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::DACC;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_dacc;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid30;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::DACC> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_dacc;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_gmac> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GMAC;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gmac;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer1_pid39;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::GMAC> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_gmac;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_gpioa> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIOA;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpioa;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid10;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::GPIOA> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_gpioa;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_gpiob> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIOB;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpiob;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid11;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::GPIOB> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_gpiob;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_gpiod> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::GPIOD;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_gpiod;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid16;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::GPIOD> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_gpiod;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_hsmci> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::HSMCI;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_hsmci;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid18;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::HSMCI> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_hsmci;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_mcan0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::MCAN0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_mcan0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer1_pid35;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::MCAN0> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_mcan0;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_mcan1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::MCAN1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_mcan1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer1_pid37;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::MCAN1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_mcan1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_pwm0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::PWM0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_pwm0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid31;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::PWM0> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_pwm0;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_pwm1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::PWM1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_pwm1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer1_pid60;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::PWM1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_pwm1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_qspi> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::QSPI;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_qspi;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer1_pid43;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::QSPI> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_qspi;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_rswdt> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::RSWDT;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_rswdt;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::RSWDT> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_rswdt;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_rtc> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::RTC;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_rtc;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::RTC> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_rtc;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_spi0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::SPI0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_spi0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid21;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::SPI0> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_spi0;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_tc0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::TC0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_tc0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid23;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::TC0> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_tc0;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_tc1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::TC1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_tc1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid26;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::TC1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_tc1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_tc2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::TC2;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_tc2;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer1_pid47;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::TC2> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_tc2;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_tc3> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::TC3;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_tc3;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer1_pid50;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::TC3> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_tc3;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_twihs0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::TWIHS0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_twihs0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid19;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::TWIHS0> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_twihs0;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_twihs1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::TWIHS1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_twihs1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid20;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::TWIHS1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_twihs1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_twihs2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::TWIHS2;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_twihs2;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer1_pid41;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::TWIHS2> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_twihs2;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_uart0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid7;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::UART0> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_uart0;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_uart1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid8;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::UART1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_uart1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_uart2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART2;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart2;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer1_pid44;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::UART2> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_uart2;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_uart3> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART3;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart3;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer1_pid45;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::UART3> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_uart3;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_uart4> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::UART4;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_uart4;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer1_pid46;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::UART4> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_uart4;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_usart0> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::USART0;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usart0;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid13;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::USART0> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_usart0;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_usart1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::USART1;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usart1;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid14;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::USART1> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_usart1;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_usart2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::USART2;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usart2;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer0_pid15;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::USART2> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_usart2;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_usbhs> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::USBHS;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_usbhs;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer1_pid34;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::USBHS> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_usbhs;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_wdt> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::WDT;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_wdt;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer0;
  static constexpr FieldId kFieldId = FieldId::none;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::WDT> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_wdt;
};

template<>
struct EnableDomainTraits<EnableDomainId::gate_xdmac> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::XDMAC;
  static constexpr ClockGateId kClockGateId = ClockGateId::gate_xdmac;
  static constexpr ClockNodeId kParentClockNodeId = ClockNodeId::clock_node_pmc;
  static constexpr RegisterId kRegisterId = RegisterId::register_pmc_pcer1;
  static constexpr FieldId kFieldId = FieldId::field_pmc_pcer1_pid58;
};

template<>
struct PeripheralEnableDomainTraits<PeripheralId::XDMAC> {
  static constexpr bool kPresent = true;
  static constexpr EnableDomainId kEnableDomainId = EnableDomainId::gate_xdmac;
};

}
}
}
}
}
}
