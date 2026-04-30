#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "../../types.hpp"
#include "peripheral_instances.hpp"
#include "pins.hpp"

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70n21b {
enum class PeripheralSignal : std::uint16_t {
  AFEC0_AD0 = 0u,
  AFEC0_AD1 = 1u,
  AFEC0_AD10 = 2u,
  AFEC0_AD2 = 3u,
  AFEC0_AD5 = 4u,
  AFEC0_AD6 = 5u,
  AFEC0_AD7 = 6u,
  AFEC0_AD8 = 7u,
  AFEC0_AD9 = 8u,
  AFEC0_ADTRG = 9u,
  AFEC1_AD0 = 10u,
  AFEC1_ADTRG = 11u,
  DACC_DAC0 = 12u,
  DACC_DAC1 = 13u,
  DACC_DATRG = 14u,
  EFC_ERASE = 15u,
  GMAC_GCOL = 16u,
  GMAC_GCRS = 17u,
  GMAC_GMDC = 18u,
  GMAC_GMDIO = 19u,
  GMAC_GRX0 = 20u,
  GMAC_GRX1 = 21u,
  GMAC_GRX2 = 22u,
  GMAC_GRX3 = 23u,
  GMAC_GRXCK = 24u,
  GMAC_GRXDV = 25u,
  GMAC_GRXER = 26u,
  GMAC_GTSUCOMP = 27u,
  GMAC_GTX0 = 28u,
  GMAC_GTX1 = 29u,
  GMAC_GTX2 = 30u,
  GMAC_GTX3 = 31u,
  GMAC_GTXCK = 32u,
  GMAC_GTXEN = 33u,
  GMAC_GTXER = 34u,
  GPIOA_PIODC0 = 35u,
  GPIOA_PIODC1 = 36u,
  GPIOA_PIODC2 = 37u,
  GPIOA_PIODC3 = 38u,
  GPIOA_PIODC4 = 39u,
  GPIOA_PIODC5 = 40u,
  GPIOA_PIODC6 = 41u,
  GPIOA_PIODC7 = 42u,
  GPIOA_PIODCCLK = 43u,
  GPIOA_PIODCEN1 = 44u,
  GPIOA_PIODCEN2 = 45u,
  HSMCI_MCCDA = 46u,
  HSMCI_MCCK = 47u,
  HSMCI_MCDA0 = 48u,
  HSMCI_MCDA1 = 49u,
  HSMCI_MCDA2 = 50u,
  HSMCI_MCDA3 = 51u,
  I2SC0_CK = 52u,
  I2SC0_DI0 = 53u,
  I2SC0_DO0 = 54u,
  I2SC0_MCK = 55u,
  I2SC0_WS = 56u,
  ISI_D0 = 57u,
  ISI_D1 = 58u,
  ISI_D10 = 59u,
  ISI_D11 = 60u,
  ISI_D2 = 61u,
  ISI_D3 = 62u,
  ISI_D4 = 63u,
  ISI_D5 = 64u,
  ISI_D6 = 65u,
  ISI_D7 = 66u,
  ISI_D8 = 67u,
  ISI_D9 = 68u,
  ISI_HSYNC = 69u,
  ISI_PCK = 70u,
  ISI_VSYNC = 71u,
  MCAN0_CANRX0 = 72u,
  MCAN0_CANTX0 = 73u,
  MCAN1_CANRX1 = 74u,
  MCAN1_CANTX1 = 75u,
  PMC_PCK0 = 76u,
  PMC_PCK1 = 77u,
  PMC_PCK2 = 78u,
  PMC_XIN = 79u,
  PMC_XIN32 = 80u,
  PMC_XOUT = 81u,
  PMC_XOUT32 = 82u,
  PWM0_PWMEXTRG0 = 83u,
  PWM0_PWMEXTRG1 = 84u,
  PWM0_PWMFI0 = 85u,
  PWM0_PWMFI1 = 86u,
  PWM0_PWMFI2 = 87u,
  PWM0_PWMH0 = 88u,
  PWM0_PWMH1 = 89u,
  PWM0_PWMH2 = 90u,
  PWM0_PWMH3 = 91u,
  PWM0_PWML0 = 92u,
  PWM0_PWML1 = 93u,
  PWM0_PWML2 = 94u,
  PWM0_PWML3 = 95u,
  PWM1_PWMEXTRG0 = 96u,
  PWM1_PWMEXTRG1 = 97u,
  PWM1_PWMFI0 = 98u,
  PWM1_PWMFI1 = 99u,
  PWM1_PWMFI2 = 100u,
  PWM1_PWMH0 = 101u,
  PWM1_PWMH1 = 102u,
  PWM1_PWMH2 = 103u,
  PWM1_PWMH3 = 104u,
  PWM1_PWML0 = 105u,
  PWM1_PWML1 = 106u,
  PWM1_PWML2 = 107u,
  PWM1_PWML3 = 108u,
  QSPI_QCS = 109u,
  QSPI_QIO0 = 110u,
  QSPI_QIO1 = 111u,
  QSPI_QIO2 = 112u,
  QSPI_QIO3 = 113u,
  QSPI_QSCK = 114u,
  RTC_RTCOUT0 = 115u,
  RTC_RTCOUT1 = 116u,
  SPI0_MISO = 117u,
  SPI0_MOSI = 118u,
  SPI0_NPCS0 = 119u,
  SPI0_NPCS1 = 120u,
  SPI0_NPCS2 = 121u,
  SPI0_NPCS3 = 122u,
  SPI0_SPCK = 123u,
  SSC_RD = 124u,
  SSC_RF = 125u,
  SSC_RK = 126u,
  SSC_TD = 127u,
  SSC_TF = 128u,
  SSC_TK = 129u,
  SUPC_WKUP0 = 130u,
  SUPC_WKUP1 = 131u,
  SUPC_WKUP10 = 132u,
  SUPC_WKUP11 = 133u,
  SUPC_WKUP12 = 134u,
  SUPC_WKUP13 = 135u,
  SUPC_WKUP2 = 136u,
  SUPC_WKUP3 = 137u,
  SUPC_WKUP4 = 138u,
  SUPC_WKUP5 = 139u,
  SUPC_WKUP6 = 140u,
  SUPC_WKUP7 = 141u,
  SUPC_WKUP8 = 142u,
  SUPC_WKUP9 = 143u,
  TC0_TCLK0 = 144u,
  TC0_TCLK1 = 145u,
  TC0_TIOA0 = 146u,
  TC0_TIOA1 = 147u,
  TC0_TIOA2 = 148u,
  TC0_TIOB0 = 149u,
  TC0_TIOB1 = 150u,
  TC0_TIOB2 = 151u,
  TC3_TCLK11 = 152u,
  TC3_TIOA11 = 153u,
  TC3_TIOB11 = 154u,
  TWIHS0_TWCK0 = 155u,
  TWIHS0_TWD0 = 156u,
  TWIHS1_TWCK1 = 157u,
  TWIHS1_TWD1 = 158u,
  TWIHS2_TWCK2 = 159u,
  TWIHS2_TWD2 = 160u,
  UART0_URXD0 = 161u,
  UART0_UTXD0 = 162u,
  UART1_URXD1 = 163u,
  UART1_UTXD1 = 164u,
  UART2_URXD2 = 165u,
  UART2_UTXD2 = 166u,
  UART3_URXD3 = 167u,
  UART3_UTXD3 = 168u,
  UART4_URXD4 = 169u,
  UART4_UTXD4 = 170u,
  USART0_CTS0 = 171u,
  USART0_DCD0 = 172u,
  USART0_DSR0 = 173u,
  USART0_DTR0 = 174u,
  USART0_RI0 = 175u,
  USART0_RTS0 = 176u,
  USART0_RXD0 = 177u,
  USART0_SCK0 = 178u,
  USART0_TXD0 = 179u,
  USART1_CTS1 = 180u,
  USART1_DCD1 = 181u,
  USART1_DSR1 = 182u,
  USART1_DTR1 = 183u,
  USART1_LONCOL1 = 184u,
  USART1_RTS1 = 185u,
  USART1_RXD1 = 186u,
  USART1_SCK1 = 187u,
  USART1_TXD1 = 188u,
  USART2_CTS2 = 189u,
  USART2_DCD2 = 190u,
  USART2_DSR2 = 191u,
  USART2_DTR2 = 192u,
  USART2_RI2 = 193u,
  USART2_RTS2 = 194u,
  USART2_RXD2 = 195u,
  USART2_SCK2 = 196u,
  USART2_TXD2 = 197u,
};

enum class RouteKind : std::uint8_t {
  peripheral_mux = 0u,
};

template<PinId Pin, PeripheralSignal Signal>
struct PinAssignmentValid : std::false_type {};

template<>
struct PinAssignmentValid<PinId::PD30, PeripheralSignal::AFEC0_AD0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA21, PeripheralSignal::AFEC0_AD1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PB0, PeripheralSignal::AFEC0_AD10> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PB3, PeripheralSignal::AFEC0_AD2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PB2, PeripheralSignal::AFEC0_AD5> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA17, PeripheralSignal::AFEC0_AD6> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA18, PeripheralSignal::AFEC0_AD7> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA19, PeripheralSignal::AFEC0_AD8> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA20, PeripheralSignal::AFEC0_AD9> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA8, PeripheralSignal::AFEC0_ADTRG> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PB1, PeripheralSignal::AFEC1_AD0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PD9, PeripheralSignal::AFEC1_ADTRG> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PB13, PeripheralSignal::DACC_DAC0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PD0, PeripheralSignal::DACC_DAC1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA2, PeripheralSignal::DACC_DATRG> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PB12, PeripheralSignal::EFC_ERASE> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PD13, PeripheralSignal::GMAC_GCOL> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD10, PeripheralSignal::GMAC_GCRS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD8, PeripheralSignal::GMAC_GMDC> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD9, PeripheralSignal::GMAC_GMDIO> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD5, PeripheralSignal::GMAC_GRX0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD6, PeripheralSignal::GMAC_GRX1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD11, PeripheralSignal::GMAC_GRX2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD12, PeripheralSignal::GMAC_GRX3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD14, PeripheralSignal::GMAC_GRXCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD4, PeripheralSignal::GMAC_GRXDV> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD7, PeripheralSignal::GMAC_GRXER> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PB1, PeripheralSignal::GMAC_GTSUCOMP> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PB12, PeripheralSignal::GMAC_GTSUCOMP> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD11, PeripheralSignal::GMAC_GTSUCOMP> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD20, PeripheralSignal::GMAC_GTSUCOMP> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD2, PeripheralSignal::GMAC_GTX0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD3, PeripheralSignal::GMAC_GTX1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD15, PeripheralSignal::GMAC_GTX2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD16, PeripheralSignal::GMAC_GTX3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD0, PeripheralSignal::GMAC_GTXCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD1, PeripheralSignal::GMAC_GTXEN> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD17, PeripheralSignal::GMAC_GTXER> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA3, PeripheralSignal::GPIOA_PIODC0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA4, PeripheralSignal::GPIOA_PIODC1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA5, PeripheralSignal::GPIOA_PIODC2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA9, PeripheralSignal::GPIOA_PIODC3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA10, PeripheralSignal::GPIOA_PIODC4> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA11, PeripheralSignal::GPIOA_PIODC5> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA12, PeripheralSignal::GPIOA_PIODC6> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA13, PeripheralSignal::GPIOA_PIODC7> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA22, PeripheralSignal::GPIOA_PIODCCLK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA14, PeripheralSignal::GPIOA_PIODCEN1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA21, PeripheralSignal::GPIOA_PIODCEN2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA28, PeripheralSignal::HSMCI_MCCDA> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PA25, PeripheralSignal::HSMCI_MCCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PA30, PeripheralSignal::HSMCI_MCDA0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PA31, PeripheralSignal::HSMCI_MCDA1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PA26, PeripheralSignal::HSMCI_MCDA2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PA27, PeripheralSignal::HSMCI_MCDA3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PA1, PeripheralSignal::I2SC0_CK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PA16, PeripheralSignal::I2SC0_DI0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PA30, PeripheralSignal::I2SC0_DO0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PA0, PeripheralSignal::I2SC0_MCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PA15, PeripheralSignal::I2SC0_WS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD22, PeripheralSignal::ISI_D0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD21, PeripheralSignal::ISI_D1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD30, PeripheralSignal::ISI_D10> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD31, PeripheralSignal::ISI_D11> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PB3, PeripheralSignal::ISI_D2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PA9, PeripheralSignal::ISI_D3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA5, PeripheralSignal::ISI_D4> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD11, PeripheralSignal::ISI_D5> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD12, PeripheralSignal::ISI_D6> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PA27, PeripheralSignal::ISI_D7> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD27, PeripheralSignal::ISI_D8> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD28, PeripheralSignal::ISI_D9> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD24, PeripheralSignal::ISI_HSYNC> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PA24, PeripheralSignal::ISI_PCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD25, PeripheralSignal::ISI_VSYNC> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PB3, PeripheralSignal::MCAN0_CANRX0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PB2, PeripheralSignal::MCAN0_CANTX0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD28, PeripheralSignal::MCAN1_CANRX1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD12, PeripheralSignal::MCAN1_CANTX1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PB12, PeripheralSignal::PMC_PCK0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PB13, PeripheralSignal::PMC_PCK0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA17, PeripheralSignal::PMC_PCK1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA21, PeripheralSignal::PMC_PCK1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA18, PeripheralSignal::PMC_PCK2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA3, PeripheralSignal::PMC_PCK2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PA31, PeripheralSignal::PMC_PCK2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PB3, PeripheralSignal::PMC_PCK2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD31, PeripheralSignal::PMC_PCK2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PB9, PeripheralSignal::PMC_XIN> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA7, PeripheralSignal::PMC_XIN32> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PB8, PeripheralSignal::PMC_XOUT> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA8, PeripheralSignal::PMC_XOUT32> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA10, PeripheralSignal::PWM0_PWMEXTRG0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA22, PeripheralSignal::PWM0_PWMEXTRG1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA9, PeripheralSignal::PWM0_PWMFI0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD8, PeripheralSignal::PWM0_PWMFI1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD9, PeripheralSignal::PWM0_PWMFI2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA0, PeripheralSignal::PWM0_PWMH0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA11, PeripheralSignal::PWM0_PWMH0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA23, PeripheralSignal::PWM0_PWMH0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PB0, PeripheralSignal::PWM0_PWMH0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD11, PeripheralSignal::PWM0_PWMH0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD20, PeripheralSignal::PWM0_PWMH0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA12, PeripheralSignal::PWM0_PWMH1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA2, PeripheralSignal::PWM0_PWMH1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA24, PeripheralSignal::PWM0_PWMH1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PB1, PeripheralSignal::PWM0_PWMH1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD21, PeripheralSignal::PWM0_PWMH1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA13, PeripheralSignal::PWM0_PWMH2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA25, PeripheralSignal::PWM0_PWMH2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PB4, PeripheralSignal::PWM0_PWMH2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD22, PeripheralSignal::PWM0_PWMH2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA14, PeripheralSignal::PWM0_PWMH3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA17, PeripheralSignal::PWM0_PWMH3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PA7, PeripheralSignal::PWM0_PWMH3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA1, PeripheralSignal::PWM0_PWML0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA19, PeripheralSignal::PWM0_PWML0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PB5, PeripheralSignal::PWM0_PWML0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD10, PeripheralSignal::PWM0_PWML0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD24, PeripheralSignal::PWM0_PWML0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA20, PeripheralSignal::PWM0_PWML1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PB12, PeripheralSignal::PWM0_PWML1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD25, PeripheralSignal::PWM0_PWML1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA16, PeripheralSignal::PWM0_PWML2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PA30, PeripheralSignal::PWM0_PWML2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PB13, PeripheralSignal::PWM0_PWML2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD26, PeripheralSignal::PWM0_PWML2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA15, PeripheralSignal::PWM0_PWML3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD27, PeripheralSignal::PWM0_PWML3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA30, PeripheralSignal::PWM1_PWMEXTRG0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA18, PeripheralSignal::PWM1_PWMEXTRG1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA21, PeripheralSignal::PWM1_PWMFI0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PA26, PeripheralSignal::PWM1_PWMFI1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PA28, PeripheralSignal::PWM1_PWMFI2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PA12, PeripheralSignal::PWM1_PWMH0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD1, PeripheralSignal::PWM1_PWMH0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA14, PeripheralSignal::PWM1_PWMH1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD3, PeripheralSignal::PWM1_PWMH1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA31, PeripheralSignal::PWM1_PWMH2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD5, PeripheralSignal::PWM1_PWMH2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA8, PeripheralSignal::PWM1_PWMH3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD7, PeripheralSignal::PWM1_PWMH3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA11, PeripheralSignal::PWM1_PWML0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD0, PeripheralSignal::PWM1_PWML0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA13, PeripheralSignal::PWM1_PWML1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD2, PeripheralSignal::PWM1_PWML1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA23, PeripheralSignal::PWM1_PWML2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD4, PeripheralSignal::PWM1_PWML2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA5, PeripheralSignal::PWM1_PWML3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD6, PeripheralSignal::PWM1_PWML3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA11, PeripheralSignal::QSPI_QCS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA13, PeripheralSignal::QSPI_QIO0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA12, PeripheralSignal::QSPI_QIO1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA17, PeripheralSignal::QSPI_QIO2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD31, PeripheralSignal::QSPI_QIO3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA14, PeripheralSignal::QSPI_QSCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PB0, PeripheralSignal::RTC_RTCOUT0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PB1, PeripheralSignal::RTC_RTCOUT1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PD20, PeripheralSignal::SPI0_MISO> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD21, PeripheralSignal::SPI0_MOSI> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PB2, PeripheralSignal::SPI0_NPCS0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PA31, PeripheralSignal::SPI0_NPCS1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD25, PeripheralSignal::SPI0_NPCS1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD12, PeripheralSignal::SPI0_NPCS2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD27, PeripheralSignal::SPI0_NPCS3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD22, PeripheralSignal::SPI0_SPCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA10, PeripheralSignal::SSC_RD> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD24, PeripheralSignal::SSC_RF> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA22, PeripheralSignal::SSC_RK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PB5, PeripheralSignal::SSC_TD> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD10, PeripheralSignal::SSC_TD> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD26, PeripheralSignal::SSC_TD> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PB0, PeripheralSignal::SSC_TF> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PB1, PeripheralSignal::SSC_TK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PA0, PeripheralSignal::SUPC_WKUP0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA1, PeripheralSignal::SUPC_WKUP1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA20, PeripheralSignal::SUPC_WKUP10> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA30, PeripheralSignal::SUPC_WKUP11> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PB3, PeripheralSignal::SUPC_WKUP12> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PB5, PeripheralSignal::SUPC_WKUP13> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA2, PeripheralSignal::SUPC_WKUP2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA4, PeripheralSignal::SUPC_WKUP3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA5, PeripheralSignal::SUPC_WKUP4> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PD28, PeripheralSignal::SUPC_WKUP5> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA9, PeripheralSignal::SUPC_WKUP6> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA11, PeripheralSignal::SUPC_WKUP7> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA14, PeripheralSignal::SUPC_WKUP8> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA19, PeripheralSignal::SUPC_WKUP9> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PA4, PeripheralSignal::TC0_TCLK0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA28, PeripheralSignal::TC0_TCLK1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA0, PeripheralSignal::TC0_TIOA0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA15, PeripheralSignal::TC0_TIOA1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA26, PeripheralSignal::TC0_TIOA2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA1, PeripheralSignal::TC0_TIOB0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA16, PeripheralSignal::TC0_TIOB1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA27, PeripheralSignal::TC0_TIOB2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD24, PeripheralSignal::TC3_TCLK11> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD21, PeripheralSignal::TC3_TIOA11> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD22, PeripheralSignal::TC3_TIOB11> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PA4, PeripheralSignal::TWIHS0_TWCK0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA3, PeripheralSignal::TWIHS0_TWD0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PB5, PeripheralSignal::TWIHS1_TWCK1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PB4, PeripheralSignal::TWIHS1_TWD1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD28, PeripheralSignal::TWIHS2_TWCK2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD27, PeripheralSignal::TWIHS2_TWD2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PA9, PeripheralSignal::UART0_URXD0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA10, PeripheralSignal::UART0_UTXD0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA5, PeripheralSignal::UART1_URXD1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PA4, PeripheralSignal::UART1_UTXD1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD26, PeripheralSignal::UART1_UTXD1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD25, PeripheralSignal::UART2_URXD2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD26, PeripheralSignal::UART2_UTXD2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD28, PeripheralSignal::UART3_URXD3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD30, PeripheralSignal::UART3_UTXD3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PD31, PeripheralSignal::UART3_UTXD3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD18, PeripheralSignal::UART4_URXD4> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD19, PeripheralSignal::UART4_UTXD4> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD3, PeripheralSignal::UART4_UTXD4> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PB2, PeripheralSignal::USART0_CTS0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD0, PeripheralSignal::USART0_DCD0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD2, PeripheralSignal::USART0_DSR0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD1, PeripheralSignal::USART0_DTR0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD3, PeripheralSignal::USART0_RI0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PB3, PeripheralSignal::USART0_RTS0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PB0, PeripheralSignal::USART0_RXD0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PB13, PeripheralSignal::USART0_SCK0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PB1, PeripheralSignal::USART0_TXD0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PA25, PeripheralSignal::USART1_CTS1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA26, PeripheralSignal::USART1_DCD1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA28, PeripheralSignal::USART1_DSR1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA27, PeripheralSignal::USART1_DTR1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA3, PeripheralSignal::USART1_LONCOL1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA24, PeripheralSignal::USART1_RTS1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA21, PeripheralSignal::USART1_RXD1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PA23, PeripheralSignal::USART1_SCK1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
};

template<>
struct PinAssignmentValid<PinId::PB4, PeripheralSignal::USART1_TXD1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD19, PeripheralSignal::USART2_CTS2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD4, PeripheralSignal::USART2_DCD2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD6, PeripheralSignal::USART2_DSR2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD5, PeripheralSignal::USART2_DTR2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD7, PeripheralSignal::USART2_RI2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PD18, PeripheralSignal::USART2_RTS2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD15, PeripheralSignal::USART2_RXD2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD17, PeripheralSignal::USART2_SCK2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD16, PeripheralSignal::USART2_TXD2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<PinId Pin, PeripheralSignal Signal>
concept ValidPinAssignment = PinAssignmentValid<Pin, Signal>::value;

struct PinAssignmentEntry {
  PinId pin;
  PeripheralSignal signal;
  RouteKind route_kind;
  std::uint8_t route_selector_index;
};

inline constexpr std::array<PinAssignmentEntry, 245> kPinAssignments = {{
  {PinId::PD30, PeripheralSignal::AFEC0_AD0, RouteKind::peripheral_mux, 101u},
  {PinId::PA21, PeripheralSignal::AFEC0_AD1, RouteKind::peripheral_mux, 101u},
  {PinId::PB0, PeripheralSignal::AFEC0_AD10, RouteKind::peripheral_mux, 101u},
  {PinId::PB3, PeripheralSignal::AFEC0_AD2, RouteKind::peripheral_mux, 101u},
  {PinId::PB2, PeripheralSignal::AFEC0_AD5, RouteKind::peripheral_mux, 101u},
  {PinId::PA17, PeripheralSignal::AFEC0_AD6, RouteKind::peripheral_mux, 101u},
  {PinId::PA18, PeripheralSignal::AFEC0_AD7, RouteKind::peripheral_mux, 101u},
  {PinId::PA19, PeripheralSignal::AFEC0_AD8, RouteKind::peripheral_mux, 101u},
  {PinId::PA20, PeripheralSignal::AFEC0_AD9, RouteKind::peripheral_mux, 101u},
  {PinId::PA8, PeripheralSignal::AFEC0_ADTRG, RouteKind::peripheral_mux, 1u},
  {PinId::PB1, PeripheralSignal::AFEC1_AD0, RouteKind::peripheral_mux, 101u},
  {PinId::PD9, PeripheralSignal::AFEC1_ADTRG, RouteKind::peripheral_mux, 2u},
  {PinId::PB13, PeripheralSignal::DACC_DAC0, RouteKind::peripheral_mux, 101u},
  {PinId::PD0, PeripheralSignal::DACC_DAC1, RouteKind::peripheral_mux, 101u},
  {PinId::PA2, PeripheralSignal::DACC_DATRG, RouteKind::peripheral_mux, 2u},
  {PinId::PB12, PeripheralSignal::EFC_ERASE, RouteKind::peripheral_mux, 101u},
  {PinId::PD13, PeripheralSignal::GMAC_GCOL, RouteKind::peripheral_mux, 0u},
  {PinId::PD10, PeripheralSignal::GMAC_GCRS, RouteKind::peripheral_mux, 0u},
  {PinId::PD8, PeripheralSignal::GMAC_GMDC, RouteKind::peripheral_mux, 0u},
  {PinId::PD9, PeripheralSignal::GMAC_GMDIO, RouteKind::peripheral_mux, 0u},
  {PinId::PD5, PeripheralSignal::GMAC_GRX0, RouteKind::peripheral_mux, 0u},
  {PinId::PD6, PeripheralSignal::GMAC_GRX1, RouteKind::peripheral_mux, 0u},
  {PinId::PD11, PeripheralSignal::GMAC_GRX2, RouteKind::peripheral_mux, 0u},
  {PinId::PD12, PeripheralSignal::GMAC_GRX3, RouteKind::peripheral_mux, 0u},
  {PinId::PD14, PeripheralSignal::GMAC_GRXCK, RouteKind::peripheral_mux, 0u},
  {PinId::PD4, PeripheralSignal::GMAC_GRXDV, RouteKind::peripheral_mux, 0u},
  {PinId::PD7, PeripheralSignal::GMAC_GRXER, RouteKind::peripheral_mux, 0u},
  {PinId::PB1, PeripheralSignal::GMAC_GTSUCOMP, RouteKind::peripheral_mux, 1u},
  {PinId::PB12, PeripheralSignal::GMAC_GTSUCOMP, RouteKind::peripheral_mux, 1u},
  {PinId::PD11, PeripheralSignal::GMAC_GTSUCOMP, RouteKind::peripheral_mux, 2u},
  {PinId::PD20, PeripheralSignal::GMAC_GTSUCOMP, RouteKind::peripheral_mux, 2u},
  {PinId::PD2, PeripheralSignal::GMAC_GTX0, RouteKind::peripheral_mux, 0u},
  {PinId::PD3, PeripheralSignal::GMAC_GTX1, RouteKind::peripheral_mux, 0u},
  {PinId::PD15, PeripheralSignal::GMAC_GTX2, RouteKind::peripheral_mux, 0u},
  {PinId::PD16, PeripheralSignal::GMAC_GTX3, RouteKind::peripheral_mux, 0u},
  {PinId::PD0, PeripheralSignal::GMAC_GTXCK, RouteKind::peripheral_mux, 0u},
  {PinId::PD1, PeripheralSignal::GMAC_GTXEN, RouteKind::peripheral_mux, 0u},
  {PinId::PD17, PeripheralSignal::GMAC_GTXER, RouteKind::peripheral_mux, 0u},
  {PinId::PA3, PeripheralSignal::GPIOA_PIODC0, RouteKind::peripheral_mux, 101u},
  {PinId::PA4, PeripheralSignal::GPIOA_PIODC1, RouteKind::peripheral_mux, 101u},
  {PinId::PA5, PeripheralSignal::GPIOA_PIODC2, RouteKind::peripheral_mux, 101u},
  {PinId::PA9, PeripheralSignal::GPIOA_PIODC3, RouteKind::peripheral_mux, 101u},
  {PinId::PA10, PeripheralSignal::GPIOA_PIODC4, RouteKind::peripheral_mux, 101u},
  {PinId::PA11, PeripheralSignal::GPIOA_PIODC5, RouteKind::peripheral_mux, 101u},
  {PinId::PA12, PeripheralSignal::GPIOA_PIODC6, RouteKind::peripheral_mux, 101u},
  {PinId::PA13, PeripheralSignal::GPIOA_PIODC7, RouteKind::peripheral_mux, 101u},
  {PinId::PA22, PeripheralSignal::GPIOA_PIODCCLK, RouteKind::peripheral_mux, 101u},
  {PinId::PA14, PeripheralSignal::GPIOA_PIODCEN1, RouteKind::peripheral_mux, 101u},
  {PinId::PA21, PeripheralSignal::GPIOA_PIODCEN2, RouteKind::peripheral_mux, 101u},
  {PinId::PA28, PeripheralSignal::HSMCI_MCCDA, RouteKind::peripheral_mux, 2u},
  {PinId::PA25, PeripheralSignal::HSMCI_MCCK, RouteKind::peripheral_mux, 3u},
  {PinId::PA30, PeripheralSignal::HSMCI_MCDA0, RouteKind::peripheral_mux, 2u},
  {PinId::PA31, PeripheralSignal::HSMCI_MCDA1, RouteKind::peripheral_mux, 2u},
  {PinId::PA26, PeripheralSignal::HSMCI_MCDA2, RouteKind::peripheral_mux, 2u},
  {PinId::PA27, PeripheralSignal::HSMCI_MCDA3, RouteKind::peripheral_mux, 2u},
  {PinId::PA1, PeripheralSignal::I2SC0_CK, RouteKind::peripheral_mux, 3u},
  {PinId::PA16, PeripheralSignal::I2SC0_DI0, RouteKind::peripheral_mux, 3u},
  {PinId::PA30, PeripheralSignal::I2SC0_DO0, RouteKind::peripheral_mux, 3u},
  {PinId::PA0, PeripheralSignal::I2SC0_MCK, RouteKind::peripheral_mux, 3u},
  {PinId::PA15, PeripheralSignal::I2SC0_WS, RouteKind::peripheral_mux, 3u},
  {PinId::PD22, PeripheralSignal::ISI_D0, RouteKind::peripheral_mux, 3u},
  {PinId::PD21, PeripheralSignal::ISI_D1, RouteKind::peripheral_mux, 3u},
  {PinId::PD30, PeripheralSignal::ISI_D10, RouteKind::peripheral_mux, 3u},
  {PinId::PD31, PeripheralSignal::ISI_D11, RouteKind::peripheral_mux, 3u},
  {PinId::PB3, PeripheralSignal::ISI_D2, RouteKind::peripheral_mux, 3u},
  {PinId::PA9, PeripheralSignal::ISI_D3, RouteKind::peripheral_mux, 1u},
  {PinId::PA5, PeripheralSignal::ISI_D4, RouteKind::peripheral_mux, 1u},
  {PinId::PD11, PeripheralSignal::ISI_D5, RouteKind::peripheral_mux, 3u},
  {PinId::PD12, PeripheralSignal::ISI_D6, RouteKind::peripheral_mux, 3u},
  {PinId::PA27, PeripheralSignal::ISI_D7, RouteKind::peripheral_mux, 3u},
  {PinId::PD27, PeripheralSignal::ISI_D8, RouteKind::peripheral_mux, 3u},
  {PinId::PD28, PeripheralSignal::ISI_D9, RouteKind::peripheral_mux, 3u},
  {PinId::PD24, PeripheralSignal::ISI_HSYNC, RouteKind::peripheral_mux, 3u},
  {PinId::PA24, PeripheralSignal::ISI_PCK, RouteKind::peripheral_mux, 3u},
  {PinId::PD25, PeripheralSignal::ISI_VSYNC, RouteKind::peripheral_mux, 3u},
  {PinId::PB3, PeripheralSignal::MCAN0_CANRX0, RouteKind::peripheral_mux, 0u},
  {PinId::PB2, PeripheralSignal::MCAN0_CANTX0, RouteKind::peripheral_mux, 0u},
  {PinId::PD28, PeripheralSignal::MCAN1_CANRX1, RouteKind::peripheral_mux, 1u},
  {PinId::PD12, PeripheralSignal::MCAN1_CANTX1, RouteKind::peripheral_mux, 1u},
  {PinId::PB12, PeripheralSignal::PMC_PCK0, RouteKind::peripheral_mux, 3u},
  {PinId::PB13, PeripheralSignal::PMC_PCK0, RouteKind::peripheral_mux, 1u},
  {PinId::PA17, PeripheralSignal::PMC_PCK1, RouteKind::peripheral_mux, 1u},
  {PinId::PA21, PeripheralSignal::PMC_PCK1, RouteKind::peripheral_mux, 1u},
  {PinId::PA18, PeripheralSignal::PMC_PCK2, RouteKind::peripheral_mux, 1u},
  {PinId::PA3, PeripheralSignal::PMC_PCK2, RouteKind::peripheral_mux, 2u},
  {PinId::PA31, PeripheralSignal::PMC_PCK2, RouteKind::peripheral_mux, 1u},
  {PinId::PB3, PeripheralSignal::PMC_PCK2, RouteKind::peripheral_mux, 1u},
  {PinId::PD31, PeripheralSignal::PMC_PCK2, RouteKind::peripheral_mux, 2u},
  {PinId::PB9, PeripheralSignal::PMC_XIN, RouteKind::peripheral_mux, 101u},
  {PinId::PA7, PeripheralSignal::PMC_XIN32, RouteKind::peripheral_mux, 101u},
  {PinId::PB8, PeripheralSignal::PMC_XOUT, RouteKind::peripheral_mux, 101u},
  {PinId::PA8, PeripheralSignal::PMC_XOUT32, RouteKind::peripheral_mux, 101u},
  {PinId::PA10, PeripheralSignal::PWM0_PWMEXTRG0, RouteKind::peripheral_mux, 1u},
  {PinId::PA22, PeripheralSignal::PWM0_PWMEXTRG1, RouteKind::peripheral_mux, 1u},
  {PinId::PA9, PeripheralSignal::PWM0_PWMFI0, RouteKind::peripheral_mux, 2u},
  {PinId::PD8, PeripheralSignal::PWM0_PWMFI1, RouteKind::peripheral_mux, 1u},
  {PinId::PD9, PeripheralSignal::PWM0_PWMFI2, RouteKind::peripheral_mux, 1u},
  {PinId::PA0, PeripheralSignal::PWM0_PWMH0, RouteKind::peripheral_mux, 0u},
  {PinId::PA11, PeripheralSignal::PWM0_PWMH0, RouteKind::peripheral_mux, 1u},
  {PinId::PA23, PeripheralSignal::PWM0_PWMH0, RouteKind::peripheral_mux, 1u},
  {PinId::PB0, PeripheralSignal::PWM0_PWMH0, RouteKind::peripheral_mux, 0u},
  {PinId::PD11, PeripheralSignal::PWM0_PWMH0, RouteKind::peripheral_mux, 1u},
  {PinId::PD20, PeripheralSignal::PWM0_PWMH0, RouteKind::peripheral_mux, 0u},
  {PinId::PA12, PeripheralSignal::PWM0_PWMH1, RouteKind::peripheral_mux, 1u},
  {PinId::PA2, PeripheralSignal::PWM0_PWMH1, RouteKind::peripheral_mux, 0u},
  {PinId::PA24, PeripheralSignal::PWM0_PWMH1, RouteKind::peripheral_mux, 1u},
  {PinId::PB1, PeripheralSignal::PWM0_PWMH1, RouteKind::peripheral_mux, 0u},
  {PinId::PD21, PeripheralSignal::PWM0_PWMH1, RouteKind::peripheral_mux, 0u},
  {PinId::PA13, PeripheralSignal::PWM0_PWMH2, RouteKind::peripheral_mux, 1u},
  {PinId::PA25, PeripheralSignal::PWM0_PWMH2, RouteKind::peripheral_mux, 1u},
  {PinId::PB4, PeripheralSignal::PWM0_PWMH2, RouteKind::peripheral_mux, 1u},
  {PinId::PD22, PeripheralSignal::PWM0_PWMH2, RouteKind::peripheral_mux, 0u},
  {PinId::PA14, PeripheralSignal::PWM0_PWMH3, RouteKind::peripheral_mux, 1u},
  {PinId::PA17, PeripheralSignal::PWM0_PWMH3, RouteKind::peripheral_mux, 2u},
  {PinId::PA7, PeripheralSignal::PWM0_PWMH3, RouteKind::peripheral_mux, 1u},
  {PinId::PA1, PeripheralSignal::PWM0_PWML0, RouteKind::peripheral_mux, 0u},
  {PinId::PA19, PeripheralSignal::PWM0_PWML0, RouteKind::peripheral_mux, 1u},
  {PinId::PB5, PeripheralSignal::PWM0_PWML0, RouteKind::peripheral_mux, 1u},
  {PinId::PD10, PeripheralSignal::PWM0_PWML0, RouteKind::peripheral_mux, 1u},
  {PinId::PD24, PeripheralSignal::PWM0_PWML0, RouteKind::peripheral_mux, 0u},
  {PinId::PA20, PeripheralSignal::PWM0_PWML1, RouteKind::peripheral_mux, 1u},
  {PinId::PB12, PeripheralSignal::PWM0_PWML1, RouteKind::peripheral_mux, 0u},
  {PinId::PD25, PeripheralSignal::PWM0_PWML1, RouteKind::peripheral_mux, 0u},
  {PinId::PA16, PeripheralSignal::PWM0_PWML2, RouteKind::peripheral_mux, 2u},
  {PinId::PA30, PeripheralSignal::PWM0_PWML2, RouteKind::peripheral_mux, 0u},
  {PinId::PB13, PeripheralSignal::PWM0_PWML2, RouteKind::peripheral_mux, 0u},
  {PinId::PD26, PeripheralSignal::PWM0_PWML2, RouteKind::peripheral_mux, 0u},
  {PinId::PA15, PeripheralSignal::PWM0_PWML3, RouteKind::peripheral_mux, 2u},
  {PinId::PD27, PeripheralSignal::PWM0_PWML3, RouteKind::peripheral_mux, 0u},
  {PinId::PA30, PeripheralSignal::PWM1_PWMEXTRG0, RouteKind::peripheral_mux, 1u},
  {PinId::PA18, PeripheralSignal::PWM1_PWMEXTRG1, RouteKind::peripheral_mux, 0u},
  {PinId::PA21, PeripheralSignal::PWM1_PWMFI0, RouteKind::peripheral_mux, 2u},
  {PinId::PA26, PeripheralSignal::PWM1_PWMFI1, RouteKind::peripheral_mux, 3u},
  {PinId::PA28, PeripheralSignal::PWM1_PWMFI2, RouteKind::peripheral_mux, 3u},
  {PinId::PA12, PeripheralSignal::PWM1_PWMH0, RouteKind::peripheral_mux, 2u},
  {PinId::PD1, PeripheralSignal::PWM1_PWMH0, RouteKind::peripheral_mux, 1u},
  {PinId::PA14, PeripheralSignal::PWM1_PWMH1, RouteKind::peripheral_mux, 2u},
  {PinId::PD3, PeripheralSignal::PWM1_PWMH1, RouteKind::peripheral_mux, 1u},
  {PinId::PA31, PeripheralSignal::PWM1_PWMH2, RouteKind::peripheral_mux, 3u},
  {PinId::PD5, PeripheralSignal::PWM1_PWMH2, RouteKind::peripheral_mux, 1u},
  {PinId::PA8, PeripheralSignal::PWM1_PWMH3, RouteKind::peripheral_mux, 0u},
  {PinId::PD7, PeripheralSignal::PWM1_PWMH3, RouteKind::peripheral_mux, 1u},
  {PinId::PA11, PeripheralSignal::PWM1_PWML0, RouteKind::peripheral_mux, 2u},
  {PinId::PD0, PeripheralSignal::PWM1_PWML0, RouteKind::peripheral_mux, 1u},
  {PinId::PA13, PeripheralSignal::PWM1_PWML1, RouteKind::peripheral_mux, 2u},
  {PinId::PD2, PeripheralSignal::PWM1_PWML1, RouteKind::peripheral_mux, 1u},
  {PinId::PA23, PeripheralSignal::PWM1_PWML2, RouteKind::peripheral_mux, 3u},
  {PinId::PD4, PeripheralSignal::PWM1_PWML2, RouteKind::peripheral_mux, 1u},
  {PinId::PA5, PeripheralSignal::PWM1_PWML3, RouteKind::peripheral_mux, 0u},
  {PinId::PD6, PeripheralSignal::PWM1_PWML3, RouteKind::peripheral_mux, 1u},
  {PinId::PA11, PeripheralSignal::QSPI_QCS, RouteKind::peripheral_mux, 0u},
  {PinId::PA13, PeripheralSignal::QSPI_QIO0, RouteKind::peripheral_mux, 0u},
  {PinId::PA12, PeripheralSignal::QSPI_QIO1, RouteKind::peripheral_mux, 0u},
  {PinId::PA17, PeripheralSignal::QSPI_QIO2, RouteKind::peripheral_mux, 0u},
  {PinId::PD31, PeripheralSignal::QSPI_QIO3, RouteKind::peripheral_mux, 0u},
  {PinId::PA14, PeripheralSignal::QSPI_QSCK, RouteKind::peripheral_mux, 0u},
  {PinId::PB0, PeripheralSignal::RTC_RTCOUT0, RouteKind::peripheral_mux, 101u},
  {PinId::PB1, PeripheralSignal::RTC_RTCOUT1, RouteKind::peripheral_mux, 101u},
  {PinId::PD20, PeripheralSignal::SPI0_MISO, RouteKind::peripheral_mux, 1u},
  {PinId::PD21, PeripheralSignal::SPI0_MOSI, RouteKind::peripheral_mux, 1u},
  {PinId::PB2, PeripheralSignal::SPI0_NPCS0, RouteKind::peripheral_mux, 3u},
  {PinId::PA31, PeripheralSignal::SPI0_NPCS1, RouteKind::peripheral_mux, 0u},
  {PinId::PD25, PeripheralSignal::SPI0_NPCS1, RouteKind::peripheral_mux, 1u},
  {PinId::PD12, PeripheralSignal::SPI0_NPCS2, RouteKind::peripheral_mux, 2u},
  {PinId::PD27, PeripheralSignal::SPI0_NPCS3, RouteKind::peripheral_mux, 1u},
  {PinId::PD22, PeripheralSignal::SPI0_SPCK, RouteKind::peripheral_mux, 1u},
  {PinId::PA10, PeripheralSignal::SSC_RD, RouteKind::peripheral_mux, 2u},
  {PinId::PD24, PeripheralSignal::SSC_RF, RouteKind::peripheral_mux, 1u},
  {PinId::PA22, PeripheralSignal::SSC_RK, RouteKind::peripheral_mux, 0u},
  {PinId::PB5, PeripheralSignal::SSC_TD, RouteKind::peripheral_mux, 3u},
  {PinId::PD10, PeripheralSignal::SSC_TD, RouteKind::peripheral_mux, 2u},
  {PinId::PD26, PeripheralSignal::SSC_TD, RouteKind::peripheral_mux, 1u},
  {PinId::PB0, PeripheralSignal::SSC_TF, RouteKind::peripheral_mux, 3u},
  {PinId::PB1, PeripheralSignal::SSC_TK, RouteKind::peripheral_mux, 3u},
  {PinId::PA0, PeripheralSignal::SUPC_WKUP0, RouteKind::peripheral_mux, 101u},
  {PinId::PA1, PeripheralSignal::SUPC_WKUP1, RouteKind::peripheral_mux, 101u},
  {PinId::PA20, PeripheralSignal::SUPC_WKUP10, RouteKind::peripheral_mux, 101u},
  {PinId::PA30, PeripheralSignal::SUPC_WKUP11, RouteKind::peripheral_mux, 101u},
  {PinId::PB3, PeripheralSignal::SUPC_WKUP12, RouteKind::peripheral_mux, 101u},
  {PinId::PB5, PeripheralSignal::SUPC_WKUP13, RouteKind::peripheral_mux, 101u},
  {PinId::PA2, PeripheralSignal::SUPC_WKUP2, RouteKind::peripheral_mux, 101u},
  {PinId::PA4, PeripheralSignal::SUPC_WKUP3, RouteKind::peripheral_mux, 101u},
  {PinId::PA5, PeripheralSignal::SUPC_WKUP4, RouteKind::peripheral_mux, 101u},
  {PinId::PD28, PeripheralSignal::SUPC_WKUP5, RouteKind::peripheral_mux, 101u},
  {PinId::PA9, PeripheralSignal::SUPC_WKUP6, RouteKind::peripheral_mux, 101u},
  {PinId::PA11, PeripheralSignal::SUPC_WKUP7, RouteKind::peripheral_mux, 101u},
  {PinId::PA14, PeripheralSignal::SUPC_WKUP8, RouteKind::peripheral_mux, 101u},
  {PinId::PA19, PeripheralSignal::SUPC_WKUP9, RouteKind::peripheral_mux, 101u},
  {PinId::PA4, PeripheralSignal::TC0_TCLK0, RouteKind::peripheral_mux, 1u},
  {PinId::PA28, PeripheralSignal::TC0_TCLK1, RouteKind::peripheral_mux, 1u},
  {PinId::PA0, PeripheralSignal::TC0_TIOA0, RouteKind::peripheral_mux, 1u},
  {PinId::PA15, PeripheralSignal::TC0_TIOA1, RouteKind::peripheral_mux, 1u},
  {PinId::PA26, PeripheralSignal::TC0_TIOA2, RouteKind::peripheral_mux, 1u},
  {PinId::PA1, PeripheralSignal::TC0_TIOB0, RouteKind::peripheral_mux, 1u},
  {PinId::PA16, PeripheralSignal::TC0_TIOB1, RouteKind::peripheral_mux, 1u},
  {PinId::PA27, PeripheralSignal::TC0_TIOB2, RouteKind::peripheral_mux, 1u},
  {PinId::PD24, PeripheralSignal::TC3_TCLK11, RouteKind::peripheral_mux, 2u},
  {PinId::PD21, PeripheralSignal::TC3_TIOA11, RouteKind::peripheral_mux, 2u},
  {PinId::PD22, PeripheralSignal::TC3_TIOB11, RouteKind::peripheral_mux, 2u},
  {PinId::PA4, PeripheralSignal::TWIHS0_TWCK0, RouteKind::peripheral_mux, 0u},
  {PinId::PA3, PeripheralSignal::TWIHS0_TWD0, RouteKind::peripheral_mux, 0u},
  {PinId::PB5, PeripheralSignal::TWIHS1_TWCK1, RouteKind::peripheral_mux, 0u},
  {PinId::PB4, PeripheralSignal::TWIHS1_TWD1, RouteKind::peripheral_mux, 0u},
  {PinId::PD28, PeripheralSignal::TWIHS2_TWCK2, RouteKind::peripheral_mux, 2u},
  {PinId::PD27, PeripheralSignal::TWIHS2_TWD2, RouteKind::peripheral_mux, 2u},
  {PinId::PA9, PeripheralSignal::UART0_URXD0, RouteKind::peripheral_mux, 0u},
  {PinId::PA10, PeripheralSignal::UART0_UTXD0, RouteKind::peripheral_mux, 0u},
  {PinId::PA5, PeripheralSignal::UART1_URXD1, RouteKind::peripheral_mux, 2u},
  {PinId::PA4, PeripheralSignal::UART1_UTXD1, RouteKind::peripheral_mux, 2u},
  {PinId::PD26, PeripheralSignal::UART1_UTXD1, RouteKind::peripheral_mux, 3u},
  {PinId::PD25, PeripheralSignal::UART2_URXD2, RouteKind::peripheral_mux, 2u},
  {PinId::PD26, PeripheralSignal::UART2_UTXD2, RouteKind::peripheral_mux, 2u},
  {PinId::PD28, PeripheralSignal::UART3_URXD3, RouteKind::peripheral_mux, 0u},
  {PinId::PD30, PeripheralSignal::UART3_UTXD3, RouteKind::peripheral_mux, 0u},
  {PinId::PD31, PeripheralSignal::UART3_UTXD3, RouteKind::peripheral_mux, 1u},
  {PinId::PD18, PeripheralSignal::UART4_URXD4, RouteKind::peripheral_mux, 2u},
  {PinId::PD19, PeripheralSignal::UART4_UTXD4, RouteKind::peripheral_mux, 2u},
  {PinId::PD3, PeripheralSignal::UART4_UTXD4, RouteKind::peripheral_mux, 2u},
  {PinId::PB2, PeripheralSignal::USART0_CTS0, RouteKind::peripheral_mux, 2u},
  {PinId::PD0, PeripheralSignal::USART0_DCD0, RouteKind::peripheral_mux, 3u},
  {PinId::PD2, PeripheralSignal::USART0_DSR0, RouteKind::peripheral_mux, 3u},
  {PinId::PD1, PeripheralSignal::USART0_DTR0, RouteKind::peripheral_mux, 3u},
  {PinId::PD3, PeripheralSignal::USART0_RI0, RouteKind::peripheral_mux, 3u},
  {PinId::PB3, PeripheralSignal::USART0_RTS0, RouteKind::peripheral_mux, 2u},
  {PinId::PB0, PeripheralSignal::USART0_RXD0, RouteKind::peripheral_mux, 2u},
  {PinId::PB13, PeripheralSignal::USART0_SCK0, RouteKind::peripheral_mux, 2u},
  {PinId::PB1, PeripheralSignal::USART0_TXD0, RouteKind::peripheral_mux, 2u},
  {PinId::PA25, PeripheralSignal::USART1_CTS1, RouteKind::peripheral_mux, 0u},
  {PinId::PA26, PeripheralSignal::USART1_DCD1, RouteKind::peripheral_mux, 0u},
  {PinId::PA28, PeripheralSignal::USART1_DSR1, RouteKind::peripheral_mux, 0u},
  {PinId::PA27, PeripheralSignal::USART1_DTR1, RouteKind::peripheral_mux, 0u},
  {PinId::PA3, PeripheralSignal::USART1_LONCOL1, RouteKind::peripheral_mux, 1u},
  {PinId::PA24, PeripheralSignal::USART1_RTS1, RouteKind::peripheral_mux, 0u},
  {PinId::PA21, PeripheralSignal::USART1_RXD1, RouteKind::peripheral_mux, 0u},
  {PinId::PA23, PeripheralSignal::USART1_SCK1, RouteKind::peripheral_mux, 0u},
  {PinId::PB4, PeripheralSignal::USART1_TXD1, RouteKind::peripheral_mux, 3u},
  {PinId::PD19, PeripheralSignal::USART2_CTS2, RouteKind::peripheral_mux, 1u},
  {PinId::PD4, PeripheralSignal::USART2_DCD2, RouteKind::peripheral_mux, 3u},
  {PinId::PD6, PeripheralSignal::USART2_DSR2, RouteKind::peripheral_mux, 3u},
  {PinId::PD5, PeripheralSignal::USART2_DTR2, RouteKind::peripheral_mux, 3u},
  {PinId::PD7, PeripheralSignal::USART2_RI2, RouteKind::peripheral_mux, 3u},
  {PinId::PD18, PeripheralSignal::USART2_RTS2, RouteKind::peripheral_mux, 1u},
  {PinId::PD15, PeripheralSignal::USART2_RXD2, RouteKind::peripheral_mux, 1u},
  {PinId::PD17, PeripheralSignal::USART2_SCK2, RouteKind::peripheral_mux, 1u},
  {PinId::PD16, PeripheralSignal::USART2_TXD2, RouteKind::peripheral_mux, 1u},
}};

constexpr bool is_valid_pin_assignment(PinId pin, PeripheralSignal signal) noexcept {
  for (auto const& entry : kPinAssignments) {
    if (entry.pin == pin && entry.signal == signal) {
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
