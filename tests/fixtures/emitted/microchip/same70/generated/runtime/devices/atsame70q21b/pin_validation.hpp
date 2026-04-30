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
namespace atsame70q21b {
enum class PeripheralSignal : std::uint16_t {
  AFEC0_AD0 = 0u,
  AFEC0_AD1 = 1u,
  AFEC0_AD10 = 2u,
  AFEC0_AD2 = 3u,
  AFEC0_AD3 = 4u,
  AFEC0_AD4 = 5u,
  AFEC0_AD5 = 6u,
  AFEC0_AD6 = 7u,
  AFEC0_AD7 = 8u,
  AFEC0_AD8 = 9u,
  AFEC0_AD9 = 10u,
  AFEC0_ADTRG = 11u,
  AFEC1_AD0 = 12u,
  AFEC1_AD1 = 13u,
  AFEC1_AD10 = 14u,
  AFEC1_AD11 = 15u,
  AFEC1_AD2 = 16u,
  AFEC1_AD3 = 17u,
  AFEC1_AD4 = 18u,
  AFEC1_AD5 = 19u,
  AFEC1_AD6 = 20u,
  AFEC1_AD7 = 21u,
  AFEC1_AD8 = 22u,
  AFEC1_AD9 = 23u,
  AFEC1_ADTRG = 24u,
  DACC_DAC0 = 25u,
  DACC_DAC1 = 26u,
  DACC_DATRG = 27u,
  EFC_ERASE = 28u,
  GMAC_GCOL = 29u,
  GMAC_GCRS = 30u,
  GMAC_GMDC = 31u,
  GMAC_GMDIO = 32u,
  GMAC_GRX0 = 33u,
  GMAC_GRX1 = 34u,
  GMAC_GRX2 = 35u,
  GMAC_GRX3 = 36u,
  GMAC_GRXCK = 37u,
  GMAC_GRXDV = 38u,
  GMAC_GRXER = 39u,
  GMAC_GTSUCOMP = 40u,
  GMAC_GTX0 = 41u,
  GMAC_GTX1 = 42u,
  GMAC_GTX2 = 43u,
  GMAC_GTX3 = 44u,
  GMAC_GTXCK = 45u,
  GMAC_GTXEN = 46u,
  GMAC_GTXER = 47u,
  GPIOA_PIODC0 = 48u,
  GPIOA_PIODC1 = 49u,
  GPIOA_PIODC2 = 50u,
  GPIOA_PIODC3 = 51u,
  GPIOA_PIODC4 = 52u,
  GPIOA_PIODC5 = 53u,
  GPIOA_PIODC6 = 54u,
  GPIOA_PIODC7 = 55u,
  GPIOA_PIODCCLK = 56u,
  GPIOA_PIODCEN1 = 57u,
  GPIOA_PIODCEN2 = 58u,
  HSMCI_MCCDA = 59u,
  HSMCI_MCCK = 60u,
  HSMCI_MCDA0 = 61u,
  HSMCI_MCDA1 = 62u,
  HSMCI_MCDA2 = 63u,
  HSMCI_MCDA3 = 64u,
  I2SC0_CK = 65u,
  I2SC0_DI0 = 66u,
  I2SC0_DO0 = 67u,
  I2SC0_MCK = 68u,
  I2SC0_WS = 69u,
  I2SC1_CK = 70u,
  I2SC1_DI0 = 71u,
  I2SC1_DO0 = 72u,
  I2SC1_MCK = 73u,
  I2SC1_WS = 74u,
  ISI_D0 = 75u,
  ISI_D1 = 76u,
  ISI_D10 = 77u,
  ISI_D11 = 78u,
  ISI_D2 = 79u,
  ISI_D3 = 80u,
  ISI_D4 = 81u,
  ISI_D5 = 82u,
  ISI_D6 = 83u,
  ISI_D7 = 84u,
  ISI_D8 = 85u,
  ISI_D9 = 86u,
  ISI_HSYNC = 87u,
  ISI_PCK = 88u,
  ISI_VSYNC = 89u,
  MCAN0_CANRX0 = 90u,
  MCAN0_CANTX0 = 91u,
  MCAN1_CANRX1 = 92u,
  MCAN1_CANTX1 = 93u,
  PMC_PCK0 = 94u,
  PMC_PCK1 = 95u,
  PMC_PCK2 = 96u,
  PMC_XIN = 97u,
  PMC_XIN32 = 98u,
  PMC_XOUT = 99u,
  PMC_XOUT32 = 100u,
  PWM0_PWMEXTRG0 = 101u,
  PWM0_PWMEXTRG1 = 102u,
  PWM0_PWMFI0 = 103u,
  PWM0_PWMFI1 = 104u,
  PWM0_PWMFI2 = 105u,
  PWM0_PWMH0 = 106u,
  PWM0_PWMH1 = 107u,
  PWM0_PWMH2 = 108u,
  PWM0_PWMH3 = 109u,
  PWM0_PWML0 = 110u,
  PWM0_PWML1 = 111u,
  PWM0_PWML2 = 112u,
  PWM0_PWML3 = 113u,
  PWM1_PWMEXTRG0 = 114u,
  PWM1_PWMEXTRG1 = 115u,
  PWM1_PWMFI0 = 116u,
  PWM1_PWMFI1 = 117u,
  PWM1_PWMFI2 = 118u,
  PWM1_PWMH0 = 119u,
  PWM1_PWMH1 = 120u,
  PWM1_PWMH2 = 121u,
  PWM1_PWMH3 = 122u,
  PWM1_PWML0 = 123u,
  PWM1_PWML1 = 124u,
  PWM1_PWML2 = 125u,
  PWM1_PWML3 = 126u,
  QSPI_QCS = 127u,
  QSPI_QIO0 = 128u,
  QSPI_QIO1 = 129u,
  QSPI_QIO2 = 130u,
  QSPI_QIO3 = 131u,
  QSPI_QSCK = 132u,
  RTC_RTCOUT0 = 133u,
  RTC_RTCOUT1 = 134u,
  SPI0_MISO = 135u,
  SPI0_MOSI = 136u,
  SPI0_NPCS0 = 137u,
  SPI0_NPCS1 = 138u,
  SPI0_NPCS2 = 139u,
  SPI0_NPCS3 = 140u,
  SPI0_SPCK = 141u,
  SPI1_MISO = 142u,
  SPI1_MOSI = 143u,
  SPI1_NPCS0 = 144u,
  SPI1_NPCS1 = 145u,
  SPI1_NPCS2 = 146u,
  SPI1_NPCS3 = 147u,
  SPI1_SPCK = 148u,
  SSC_RD = 149u,
  SSC_RF = 150u,
  SSC_RK = 151u,
  SSC_TD = 152u,
  SSC_TF = 153u,
  SSC_TK = 154u,
  SUPC_WKUP0 = 155u,
  SUPC_WKUP1 = 156u,
  SUPC_WKUP10 = 157u,
  SUPC_WKUP11 = 158u,
  SUPC_WKUP12 = 159u,
  SUPC_WKUP13 = 160u,
  SUPC_WKUP2 = 161u,
  SUPC_WKUP3 = 162u,
  SUPC_WKUP4 = 163u,
  SUPC_WKUP5 = 164u,
  SUPC_WKUP6 = 165u,
  SUPC_WKUP7 = 166u,
  SUPC_WKUP8 = 167u,
  SUPC_WKUP9 = 168u,
  TC0_TCLK0 = 169u,
  TC0_TCLK1 = 170u,
  TC0_TCLK2 = 171u,
  TC0_TIOA0 = 172u,
  TC0_TIOA1 = 173u,
  TC0_TIOA2 = 174u,
  TC0_TIOB0 = 175u,
  TC0_TIOB1 = 176u,
  TC0_TIOB2 = 177u,
  TC1_TCLK3 = 178u,
  TC1_TCLK4 = 179u,
  TC1_TCLK5 = 180u,
  TC1_TIOA3 = 181u,
  TC1_TIOA4 = 182u,
  TC1_TIOA5 = 183u,
  TC1_TIOB3 = 184u,
  TC1_TIOB4 = 185u,
  TC1_TIOB5 = 186u,
  TC2_TCLK6 = 187u,
  TC2_TCLK7 = 188u,
  TC2_TCLK8 = 189u,
  TC2_TIOA6 = 190u,
  TC2_TIOA7 = 191u,
  TC2_TIOA8 = 192u,
  TC2_TIOB6 = 193u,
  TC2_TIOB7 = 194u,
  TC2_TIOB8 = 195u,
  TC3_TCLK10 = 196u,
  TC3_TCLK11 = 197u,
  TC3_TCLK9 = 198u,
  TC3_TIOA10 = 199u,
  TC3_TIOA11 = 200u,
  TC3_TIOA9 = 201u,
  TC3_TIOB10 = 202u,
  TC3_TIOB11 = 203u,
  TC3_TIOB9 = 204u,
  TWIHS0_TWCK0 = 205u,
  TWIHS0_TWD0 = 206u,
  TWIHS1_TWCK1 = 207u,
  TWIHS1_TWD1 = 208u,
  TWIHS2_TWCK2 = 209u,
  TWIHS2_TWD2 = 210u,
  UART0_URXD0 = 211u,
  UART0_UTXD0 = 212u,
  UART1_URXD1 = 213u,
  UART1_UTXD1 = 214u,
  UART2_URXD2 = 215u,
  UART2_UTXD2 = 216u,
  UART3_URXD3 = 217u,
  UART3_UTXD3 = 218u,
  UART4_URXD4 = 219u,
  UART4_UTXD4 = 220u,
  USART0_CTS0 = 221u,
  USART0_DCD0 = 222u,
  USART0_DSR0 = 223u,
  USART0_DTR0 = 224u,
  USART0_RI0 = 225u,
  USART0_RTS0 = 226u,
  USART0_RXD0 = 227u,
  USART0_SCK0 = 228u,
  USART0_TXD0 = 229u,
  USART1_CTS1 = 230u,
  USART1_DCD1 = 231u,
  USART1_DSR1 = 232u,
  USART1_DTR1 = 233u,
  USART1_LONCOL1 = 234u,
  USART1_RI1 = 235u,
  USART1_RTS1 = 236u,
  USART1_RXD1 = 237u,
  USART1_SCK1 = 238u,
  USART1_TXD1 = 239u,
  USART2_CTS2 = 240u,
  USART2_DCD2 = 241u,
  USART2_DSR2 = 242u,
  USART2_DTR2 = 243u,
  USART2_RI2 = 244u,
  USART2_RTS2 = 245u,
  USART2_RXD2 = 246u,
  USART2_SCK2 = 247u,
  USART2_TXD2 = 248u,
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
struct PinAssignmentValid<PinId::PE5, PeripheralSignal::AFEC0_AD3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PE4, PeripheralSignal::AFEC0_AD4> : std::true_type {
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
struct PinAssignmentValid<PinId::PC13, PeripheralSignal::AFEC1_AD1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PE3, PeripheralSignal::AFEC1_AD10> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PE0, PeripheralSignal::AFEC1_AD11> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PC15, PeripheralSignal::AFEC1_AD2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PC12, PeripheralSignal::AFEC1_AD3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PC29, PeripheralSignal::AFEC1_AD4> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PC30, PeripheralSignal::AFEC1_AD5> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PC31, PeripheralSignal::AFEC1_AD6> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PC26, PeripheralSignal::AFEC1_AD7> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PC27, PeripheralSignal::AFEC1_AD8> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 101u;
};

template<>
struct PinAssignmentValid<PinId::PC0, PeripheralSignal::AFEC1_AD9> : std::true_type {
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
struct PinAssignmentValid<PinId::PA20, PeripheralSignal::I2SC1_CK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PE2, PeripheralSignal::I2SC1_DI0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PE1, PeripheralSignal::I2SC1_DO0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PA19, PeripheralSignal::I2SC1_MCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 3u;
};

template<>
struct PinAssignmentValid<PinId::PE0, PeripheralSignal::I2SC1_WS> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
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
struct PinAssignmentValid<PinId::PC12, PeripheralSignal::MCAN1_CANRX1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PC14, PeripheralSignal::MCAN1_CANTX1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD12, PeripheralSignal::MCAN1_CANTX1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PA6, PeripheralSignal::PMC_PCK0> : std::true_type {
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
struct PinAssignmentValid<PinId::PC19, PeripheralSignal::PWM0_PWMH2> : std::true_type {
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
struct PinAssignmentValid<PinId::PC13, PeripheralSignal::PWM0_PWMH3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC21, PeripheralSignal::PWM0_PWMH3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD23, PeripheralSignal::PWM0_PWMH3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
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
struct PinAssignmentValid<PinId::PC0, PeripheralSignal::PWM0_PWML0> : std::true_type {
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
struct PinAssignmentValid<PinId::PC1, PeripheralSignal::PWM0_PWML1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC18, PeripheralSignal::PWM0_PWML1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
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
struct PinAssignmentValid<PinId::PC2, PeripheralSignal::PWM0_PWML2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC20, PeripheralSignal::PWM0_PWML2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
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
struct PinAssignmentValid<PinId::PC15, PeripheralSignal::PWM0_PWML3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC22, PeripheralSignal::PWM0_PWML3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC3, PeripheralSignal::PWM0_PWML3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
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
struct PinAssignmentValid<PinId::PC26, PeripheralSignal::SPI1_MISO> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PC27, PeripheralSignal::SPI1_MOSI> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PC25, PeripheralSignal::SPI1_NPCS0> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PC28, PeripheralSignal::SPI1_NPCS1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD0, PeripheralSignal::SPI1_NPCS1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PC29, PeripheralSignal::SPI1_NPCS2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD1, PeripheralSignal::SPI1_NPCS2> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PC30, PeripheralSignal::SPI1_NPCS3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PD2, PeripheralSignal::SPI1_NPCS3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PC24, PeripheralSignal::SPI1_SPCK> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
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
struct PinAssignmentValid<PinId::PA29, PeripheralSignal::TC0_TCLK2> : std::true_type {
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
struct PinAssignmentValid<PinId::PC25, PeripheralSignal::TC1_TCLK3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC28, PeripheralSignal::TC1_TCLK4> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC31, PeripheralSignal::TC1_TCLK5> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC23, PeripheralSignal::TC1_TIOA3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC26, PeripheralSignal::TC1_TIOA4> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC29, PeripheralSignal::TC1_TIOA5> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC24, PeripheralSignal::TC1_TIOB3> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC27, PeripheralSignal::TC1_TIOB4> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC30, PeripheralSignal::TC1_TIOB5> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC7, PeripheralSignal::TC2_TCLK6> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC10, PeripheralSignal::TC2_TCLK7> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC14, PeripheralSignal::TC2_TCLK8> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC5, PeripheralSignal::TC2_TIOA6> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC8, PeripheralSignal::TC2_TIOA7> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC11, PeripheralSignal::TC2_TIOA8> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC6, PeripheralSignal::TC2_TIOB6> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC9, PeripheralSignal::TC2_TIOB7> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PC12, PeripheralSignal::TC2_TIOB8> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PE5, PeripheralSignal::TC3_TCLK10> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD24, PeripheralSignal::TC3_TCLK11> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PE2, PeripheralSignal::TC3_TCLK9> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PE3, PeripheralSignal::TC3_TIOA10> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD21, PeripheralSignal::TC3_TIOA11> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PE0, PeripheralSignal::TC3_TIOA9> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PE4, PeripheralSignal::TC3_TIOB10> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
};

template<>
struct PinAssignmentValid<PinId::PD22, PeripheralSignal::TC3_TIOB11> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 2u;
};

template<>
struct PinAssignmentValid<PinId::PE1, PeripheralSignal::TC3_TIOB9> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 1u;
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
struct PinAssignmentValid<PinId::PA6, PeripheralSignal::UART1_UTXD1> : std::true_type {
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
struct PinAssignmentValid<PinId::PA29, PeripheralSignal::USART1_RI1> : std::true_type {
  static constexpr RouteKind kRouteKind = RouteKind::peripheral_mux;
  static constexpr std::uint8_t kRouteSelectorIndex = 0u;
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

inline constexpr std::array<PinAssignmentEntry, 314> kPinAssignments = {{
  {PinId::PD30, PeripheralSignal::AFEC0_AD0, RouteKind::peripheral_mux, 101u},
  {PinId::PA21, PeripheralSignal::AFEC0_AD1, RouteKind::peripheral_mux, 101u},
  {PinId::PB0, PeripheralSignal::AFEC0_AD10, RouteKind::peripheral_mux, 101u},
  {PinId::PB3, PeripheralSignal::AFEC0_AD2, RouteKind::peripheral_mux, 101u},
  {PinId::PE5, PeripheralSignal::AFEC0_AD3, RouteKind::peripheral_mux, 101u},
  {PinId::PE4, PeripheralSignal::AFEC0_AD4, RouteKind::peripheral_mux, 101u},
  {PinId::PB2, PeripheralSignal::AFEC0_AD5, RouteKind::peripheral_mux, 101u},
  {PinId::PA17, PeripheralSignal::AFEC0_AD6, RouteKind::peripheral_mux, 101u},
  {PinId::PA18, PeripheralSignal::AFEC0_AD7, RouteKind::peripheral_mux, 101u},
  {PinId::PA19, PeripheralSignal::AFEC0_AD8, RouteKind::peripheral_mux, 101u},
  {PinId::PA20, PeripheralSignal::AFEC0_AD9, RouteKind::peripheral_mux, 101u},
  {PinId::PA8, PeripheralSignal::AFEC0_ADTRG, RouteKind::peripheral_mux, 1u},
  {PinId::PB1, PeripheralSignal::AFEC1_AD0, RouteKind::peripheral_mux, 101u},
  {PinId::PC13, PeripheralSignal::AFEC1_AD1, RouteKind::peripheral_mux, 101u},
  {PinId::PE3, PeripheralSignal::AFEC1_AD10, RouteKind::peripheral_mux, 101u},
  {PinId::PE0, PeripheralSignal::AFEC1_AD11, RouteKind::peripheral_mux, 101u},
  {PinId::PC15, PeripheralSignal::AFEC1_AD2, RouteKind::peripheral_mux, 101u},
  {PinId::PC12, PeripheralSignal::AFEC1_AD3, RouteKind::peripheral_mux, 101u},
  {PinId::PC29, PeripheralSignal::AFEC1_AD4, RouteKind::peripheral_mux, 101u},
  {PinId::PC30, PeripheralSignal::AFEC1_AD5, RouteKind::peripheral_mux, 101u},
  {PinId::PC31, PeripheralSignal::AFEC1_AD6, RouteKind::peripheral_mux, 101u},
  {PinId::PC26, PeripheralSignal::AFEC1_AD7, RouteKind::peripheral_mux, 101u},
  {PinId::PC27, PeripheralSignal::AFEC1_AD8, RouteKind::peripheral_mux, 101u},
  {PinId::PC0, PeripheralSignal::AFEC1_AD9, RouteKind::peripheral_mux, 101u},
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
  {PinId::PA20, PeripheralSignal::I2SC1_CK, RouteKind::peripheral_mux, 3u},
  {PinId::PE2, PeripheralSignal::I2SC1_DI0, RouteKind::peripheral_mux, 2u},
  {PinId::PE1, PeripheralSignal::I2SC1_DO0, RouteKind::peripheral_mux, 2u},
  {PinId::PA19, PeripheralSignal::I2SC1_MCK, RouteKind::peripheral_mux, 3u},
  {PinId::PE0, PeripheralSignal::I2SC1_WS, RouteKind::peripheral_mux, 2u},
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
  {PinId::PC12, PeripheralSignal::MCAN1_CANRX1, RouteKind::peripheral_mux, 2u},
  {PinId::PC14, PeripheralSignal::MCAN1_CANTX1, RouteKind::peripheral_mux, 2u},
  {PinId::PD12, PeripheralSignal::MCAN1_CANTX1, RouteKind::peripheral_mux, 1u},
  {PinId::PA6, PeripheralSignal::PMC_PCK0, RouteKind::peripheral_mux, 1u},
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
  {PinId::PC19, PeripheralSignal::PWM0_PWMH2, RouteKind::peripheral_mux, 1u},
  {PinId::PD22, PeripheralSignal::PWM0_PWMH2, RouteKind::peripheral_mux, 0u},
  {PinId::PA14, PeripheralSignal::PWM0_PWMH3, RouteKind::peripheral_mux, 1u},
  {PinId::PA17, PeripheralSignal::PWM0_PWMH3, RouteKind::peripheral_mux, 2u},
  {PinId::PA7, PeripheralSignal::PWM0_PWMH3, RouteKind::peripheral_mux, 1u},
  {PinId::PC13, PeripheralSignal::PWM0_PWMH3, RouteKind::peripheral_mux, 1u},
  {PinId::PC21, PeripheralSignal::PWM0_PWMH3, RouteKind::peripheral_mux, 1u},
  {PinId::PD23, PeripheralSignal::PWM0_PWMH3, RouteKind::peripheral_mux, 0u},
  {PinId::PA1, PeripheralSignal::PWM0_PWML0, RouteKind::peripheral_mux, 0u},
  {PinId::PA19, PeripheralSignal::PWM0_PWML0, RouteKind::peripheral_mux, 1u},
  {PinId::PB5, PeripheralSignal::PWM0_PWML0, RouteKind::peripheral_mux, 1u},
  {PinId::PC0, PeripheralSignal::PWM0_PWML0, RouteKind::peripheral_mux, 1u},
  {PinId::PD10, PeripheralSignal::PWM0_PWML0, RouteKind::peripheral_mux, 1u},
  {PinId::PD24, PeripheralSignal::PWM0_PWML0, RouteKind::peripheral_mux, 0u},
  {PinId::PA20, PeripheralSignal::PWM0_PWML1, RouteKind::peripheral_mux, 1u},
  {PinId::PB12, PeripheralSignal::PWM0_PWML1, RouteKind::peripheral_mux, 0u},
  {PinId::PC1, PeripheralSignal::PWM0_PWML1, RouteKind::peripheral_mux, 1u},
  {PinId::PC18, PeripheralSignal::PWM0_PWML1, RouteKind::peripheral_mux, 1u},
  {PinId::PD25, PeripheralSignal::PWM0_PWML1, RouteKind::peripheral_mux, 0u},
  {PinId::PA16, PeripheralSignal::PWM0_PWML2, RouteKind::peripheral_mux, 2u},
  {PinId::PA30, PeripheralSignal::PWM0_PWML2, RouteKind::peripheral_mux, 0u},
  {PinId::PB13, PeripheralSignal::PWM0_PWML2, RouteKind::peripheral_mux, 0u},
  {PinId::PC2, PeripheralSignal::PWM0_PWML2, RouteKind::peripheral_mux, 1u},
  {PinId::PC20, PeripheralSignal::PWM0_PWML2, RouteKind::peripheral_mux, 1u},
  {PinId::PD26, PeripheralSignal::PWM0_PWML2, RouteKind::peripheral_mux, 0u},
  {PinId::PA15, PeripheralSignal::PWM0_PWML3, RouteKind::peripheral_mux, 2u},
  {PinId::PC15, PeripheralSignal::PWM0_PWML3, RouteKind::peripheral_mux, 1u},
  {PinId::PC22, PeripheralSignal::PWM0_PWML3, RouteKind::peripheral_mux, 1u},
  {PinId::PC3, PeripheralSignal::PWM0_PWML3, RouteKind::peripheral_mux, 1u},
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
  {PinId::PC26, PeripheralSignal::SPI1_MISO, RouteKind::peripheral_mux, 2u},
  {PinId::PC27, PeripheralSignal::SPI1_MOSI, RouteKind::peripheral_mux, 2u},
  {PinId::PC25, PeripheralSignal::SPI1_NPCS0, RouteKind::peripheral_mux, 2u},
  {PinId::PC28, PeripheralSignal::SPI1_NPCS1, RouteKind::peripheral_mux, 2u},
  {PinId::PD0, PeripheralSignal::SPI1_NPCS1, RouteKind::peripheral_mux, 2u},
  {PinId::PC29, PeripheralSignal::SPI1_NPCS2, RouteKind::peripheral_mux, 2u},
  {PinId::PD1, PeripheralSignal::SPI1_NPCS2, RouteKind::peripheral_mux, 2u},
  {PinId::PC30, PeripheralSignal::SPI1_NPCS3, RouteKind::peripheral_mux, 2u},
  {PinId::PD2, PeripheralSignal::SPI1_NPCS3, RouteKind::peripheral_mux, 2u},
  {PinId::PC24, PeripheralSignal::SPI1_SPCK, RouteKind::peripheral_mux, 2u},
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
  {PinId::PA29, PeripheralSignal::TC0_TCLK2, RouteKind::peripheral_mux, 1u},
  {PinId::PA0, PeripheralSignal::TC0_TIOA0, RouteKind::peripheral_mux, 1u},
  {PinId::PA15, PeripheralSignal::TC0_TIOA1, RouteKind::peripheral_mux, 1u},
  {PinId::PA26, PeripheralSignal::TC0_TIOA2, RouteKind::peripheral_mux, 1u},
  {PinId::PA1, PeripheralSignal::TC0_TIOB0, RouteKind::peripheral_mux, 1u},
  {PinId::PA16, PeripheralSignal::TC0_TIOB1, RouteKind::peripheral_mux, 1u},
  {PinId::PA27, PeripheralSignal::TC0_TIOB2, RouteKind::peripheral_mux, 1u},
  {PinId::PC25, PeripheralSignal::TC1_TCLK3, RouteKind::peripheral_mux, 1u},
  {PinId::PC28, PeripheralSignal::TC1_TCLK4, RouteKind::peripheral_mux, 1u},
  {PinId::PC31, PeripheralSignal::TC1_TCLK5, RouteKind::peripheral_mux, 1u},
  {PinId::PC23, PeripheralSignal::TC1_TIOA3, RouteKind::peripheral_mux, 1u},
  {PinId::PC26, PeripheralSignal::TC1_TIOA4, RouteKind::peripheral_mux, 1u},
  {PinId::PC29, PeripheralSignal::TC1_TIOA5, RouteKind::peripheral_mux, 1u},
  {PinId::PC24, PeripheralSignal::TC1_TIOB3, RouteKind::peripheral_mux, 1u},
  {PinId::PC27, PeripheralSignal::TC1_TIOB4, RouteKind::peripheral_mux, 1u},
  {PinId::PC30, PeripheralSignal::TC1_TIOB5, RouteKind::peripheral_mux, 1u},
  {PinId::PC7, PeripheralSignal::TC2_TCLK6, RouteKind::peripheral_mux, 1u},
  {PinId::PC10, PeripheralSignal::TC2_TCLK7, RouteKind::peripheral_mux, 1u},
  {PinId::PC14, PeripheralSignal::TC2_TCLK8, RouteKind::peripheral_mux, 1u},
  {PinId::PC5, PeripheralSignal::TC2_TIOA6, RouteKind::peripheral_mux, 1u},
  {PinId::PC8, PeripheralSignal::TC2_TIOA7, RouteKind::peripheral_mux, 1u},
  {PinId::PC11, PeripheralSignal::TC2_TIOA8, RouteKind::peripheral_mux, 1u},
  {PinId::PC6, PeripheralSignal::TC2_TIOB6, RouteKind::peripheral_mux, 1u},
  {PinId::PC9, PeripheralSignal::TC2_TIOB7, RouteKind::peripheral_mux, 1u},
  {PinId::PC12, PeripheralSignal::TC2_TIOB8, RouteKind::peripheral_mux, 1u},
  {PinId::PE5, PeripheralSignal::TC3_TCLK10, RouteKind::peripheral_mux, 1u},
  {PinId::PD24, PeripheralSignal::TC3_TCLK11, RouteKind::peripheral_mux, 2u},
  {PinId::PE2, PeripheralSignal::TC3_TCLK9, RouteKind::peripheral_mux, 1u},
  {PinId::PE3, PeripheralSignal::TC3_TIOA10, RouteKind::peripheral_mux, 1u},
  {PinId::PD21, PeripheralSignal::TC3_TIOA11, RouteKind::peripheral_mux, 2u},
  {PinId::PE0, PeripheralSignal::TC3_TIOA9, RouteKind::peripheral_mux, 1u},
  {PinId::PE4, PeripheralSignal::TC3_TIOB10, RouteKind::peripheral_mux, 1u},
  {PinId::PD22, PeripheralSignal::TC3_TIOB11, RouteKind::peripheral_mux, 2u},
  {PinId::PE1, PeripheralSignal::TC3_TIOB9, RouteKind::peripheral_mux, 1u},
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
  {PinId::PA6, PeripheralSignal::UART1_UTXD1, RouteKind::peripheral_mux, 2u},
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
  {PinId::PA29, PeripheralSignal::USART1_RI1, RouteKind::peripheral_mux, 0u},
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
