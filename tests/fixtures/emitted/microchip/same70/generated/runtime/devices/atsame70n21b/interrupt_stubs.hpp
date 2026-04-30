#pragma once

#include <array>
#include <cstdint>
#include "interrupts.hpp"
#include "startup.hpp"

extern "C" {
void Default_Handler();
void SUPC_IRQHandler() __attribute__((weak));
void RSTC_IRQHandler() __attribute__((weak));
void RTC_IRQHandler() __attribute__((weak));
void RTT_IRQHandler() __attribute__((weak));
void WDT_IRQHandler() __attribute__((weak));
void PMC_IRQHandler() __attribute__((weak));
void EFC_IRQHandler() __attribute__((weak));
void UART0_IRQHandler() __attribute__((weak));
void UART1_IRQHandler() __attribute__((weak));
void PIOA_IRQHandler() __attribute__((weak));
void PIOB_IRQHandler() __attribute__((weak));
void USART0_IRQHandler() __attribute__((weak));
void USART1_IRQHandler() __attribute__((weak));
void USART2_IRQHandler() __attribute__((weak));
void PIOD_IRQHandler() __attribute__((weak));
void HSMCI_IRQHandler() __attribute__((weak));
void TWIHS0_IRQHandler() __attribute__((weak));
void TWIHS1_IRQHandler() __attribute__((weak));
void SPI0_IRQHandler() __attribute__((weak));
void SSC_IRQHandler() __attribute__((weak));
void TC0_IRQHandler() __attribute__((weak));
void TC1_IRQHandler() __attribute__((weak));
void TC2_IRQHandler() __attribute__((weak));
void TC3_IRQHandler() __attribute__((weak));
void TC4_IRQHandler() __attribute__((weak));
void TC5_IRQHandler() __attribute__((weak));
void AFEC0_IRQHandler() __attribute__((weak));
void DACC_IRQHandler() __attribute__((weak));
void PWM0_IRQHandler() __attribute__((weak));
void ICM_IRQHandler() __attribute__((weak));
void ACC_IRQHandler() __attribute__((weak));
void USBHS_IRQHandler() __attribute__((weak));
void MCAN0_INT0_IRQHandler() __attribute__((weak));
void MCAN0_INT1_IRQHandler() __attribute__((weak));
void MCAN1_INT0_IRQHandler() __attribute__((weak));
void MCAN1_INT1_IRQHandler() __attribute__((weak));
void GMAC_IRQHandler() __attribute__((weak));
void AFEC1_IRQHandler() __attribute__((weak));
void TWIHS2_IRQHandler() __attribute__((weak));
void QSPI_IRQHandler() __attribute__((weak));
void UART2_IRQHandler() __attribute__((weak));
void UART3_IRQHandler() __attribute__((weak));
void UART4_IRQHandler() __attribute__((weak));
void TC6_IRQHandler() __attribute__((weak));
void TC7_IRQHandler() __attribute__((weak));
void TC8_IRQHandler() __attribute__((weak));
void TC9_IRQHandler() __attribute__((weak));
void TC10_IRQHandler() __attribute__((weak));
void TC11_IRQHandler() __attribute__((weak));
void AES_IRQHandler() __attribute__((weak));
void TRNG_IRQHandler() __attribute__((weak));
void XDMAC_IRQHandler() __attribute__((weak));
void ISI_IRQHandler() __attribute__((weak));
void PWM1_IRQHandler() __attribute__((weak));
void FPU_IRQHandler() __attribute__((weak));
void RSWDT_IRQHandler() __attribute__((weak));
void CCW_IRQHandler() __attribute__((weak));
void CCF_IRQHandler() __attribute__((weak));
void GMAC_Q1_IRQHandler() __attribute__((weak));
void GMAC_Q2_IRQHandler() __attribute__((weak));
void IXC_IRQHandler() __attribute__((weak));
void I2SC0_IRQHandler() __attribute__((weak));
void GMAC_Q3_IRQHandler() __attribute__((weak));
void GMAC_Q4_IRQHandler() __attribute__((weak));
void GMAC_Q5_IRQHandler() __attribute__((weak));
}

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70n21b {
struct InterruptStubDescriptor {
  InterruptId interrupt_id;
  StartupSymbolId symbol_id;
  std::uint16_t line;
  std::uint16_t vector_slot;
};
inline constexpr std::array<InterruptStubDescriptor, 65> kInterruptStubs = {{
  {InterruptId::SUPC, StartupSymbolId::SUPC_IRQHandler, 0u, 16u},
  {InterruptId::RSTC, StartupSymbolId::RSTC_IRQHandler, 1u, 17u},
  {InterruptId::RTC, StartupSymbolId::RTC_IRQHandler, 2u, 18u},
  {InterruptId::RTT, StartupSymbolId::RTT_IRQHandler, 3u, 19u},
  {InterruptId::WDT, StartupSymbolId::WDT_IRQHandler, 4u, 20u},
  {InterruptId::PMC, StartupSymbolId::PMC_IRQHandler, 5u, 21u},
  {InterruptId::EFC, StartupSymbolId::EFC_IRQHandler, 6u, 22u},
  {InterruptId::UART0, StartupSymbolId::UART0_IRQHandler, 7u, 23u},
  {InterruptId::UART1, StartupSymbolId::UART1_IRQHandler, 8u, 24u},
  {InterruptId::PIOA, StartupSymbolId::PIOA_IRQHandler, 10u, 26u},
  {InterruptId::PIOB, StartupSymbolId::PIOB_IRQHandler, 11u, 27u},
  {InterruptId::USART0, StartupSymbolId::USART0_IRQHandler, 13u, 29u},
  {InterruptId::USART1, StartupSymbolId::USART1_IRQHandler, 14u, 30u},
  {InterruptId::USART2, StartupSymbolId::USART2_IRQHandler, 15u, 31u},
  {InterruptId::PIOD, StartupSymbolId::PIOD_IRQHandler, 16u, 32u},
  {InterruptId::HSMCI, StartupSymbolId::HSMCI_IRQHandler, 18u, 34u},
  {InterruptId::TWIHS0, StartupSymbolId::TWIHS0_IRQHandler, 19u, 35u},
  {InterruptId::TWIHS1, StartupSymbolId::TWIHS1_IRQHandler, 20u, 36u},
  {InterruptId::SPI0, StartupSymbolId::SPI0_IRQHandler, 21u, 37u},
  {InterruptId::SSC, StartupSymbolId::SSC_IRQHandler, 22u, 38u},
  {InterruptId::TC0, StartupSymbolId::TC0_IRQHandler, 23u, 39u},
  {InterruptId::TC1, StartupSymbolId::TC1_IRQHandler, 24u, 40u},
  {InterruptId::TC2, StartupSymbolId::TC2_IRQHandler, 25u, 41u},
  {InterruptId::TC3, StartupSymbolId::TC3_IRQHandler, 26u, 42u},
  {InterruptId::TC4, StartupSymbolId::TC4_IRQHandler, 27u, 43u},
  {InterruptId::TC5, StartupSymbolId::TC5_IRQHandler, 28u, 44u},
  {InterruptId::AFEC0, StartupSymbolId::AFEC0_IRQHandler, 29u, 45u},
  {InterruptId::DACC, StartupSymbolId::DACC_IRQHandler, 30u, 46u},
  {InterruptId::PWM0, StartupSymbolId::PWM0_IRQHandler, 31u, 47u},
  {InterruptId::ICM, StartupSymbolId::ICM_IRQHandler, 32u, 48u},
  {InterruptId::ACC, StartupSymbolId::ACC_IRQHandler, 33u, 49u},
  {InterruptId::USBHS, StartupSymbolId::USBHS_IRQHandler, 34u, 50u},
  {InterruptId::MCAN0_INT0, StartupSymbolId::MCAN0_INT0_IRQHandler, 35u, 51u},
  {InterruptId::MCAN0_INT1, StartupSymbolId::MCAN0_INT1_IRQHandler, 36u, 52u},
  {InterruptId::MCAN1_INT0, StartupSymbolId::MCAN1_INT0_IRQHandler, 37u, 53u},
  {InterruptId::MCAN1_INT1, StartupSymbolId::MCAN1_INT1_IRQHandler, 38u, 54u},
  {InterruptId::GMAC, StartupSymbolId::GMAC_IRQHandler, 39u, 55u},
  {InterruptId::AFEC1, StartupSymbolId::AFEC1_IRQHandler, 40u, 56u},
  {InterruptId::TWIHS2, StartupSymbolId::TWIHS2_IRQHandler, 41u, 57u},
  {InterruptId::QSPI, StartupSymbolId::QSPI_IRQHandler, 43u, 59u},
  {InterruptId::UART2, StartupSymbolId::UART2_IRQHandler, 44u, 60u},
  {InterruptId::UART3, StartupSymbolId::UART3_IRQHandler, 45u, 61u},
  {InterruptId::UART4, StartupSymbolId::UART4_IRQHandler, 46u, 62u},
  {InterruptId::TC6, StartupSymbolId::TC6_IRQHandler, 47u, 63u},
  {InterruptId::TC7, StartupSymbolId::TC7_IRQHandler, 48u, 64u},
  {InterruptId::TC8, StartupSymbolId::TC8_IRQHandler, 49u, 65u},
  {InterruptId::TC9, StartupSymbolId::TC9_IRQHandler, 50u, 66u},
  {InterruptId::TC10, StartupSymbolId::TC10_IRQHandler, 51u, 67u},
  {InterruptId::TC11, StartupSymbolId::TC11_IRQHandler, 52u, 68u},
  {InterruptId::AES, StartupSymbolId::AES_IRQHandler, 56u, 72u},
  {InterruptId::TRNG, StartupSymbolId::TRNG_IRQHandler, 57u, 73u},
  {InterruptId::XDMAC, StartupSymbolId::XDMAC_IRQHandler, 58u, 74u},
  {InterruptId::ISI, StartupSymbolId::ISI_IRQHandler, 59u, 75u},
  {InterruptId::PWM1, StartupSymbolId::PWM1_IRQHandler, 60u, 76u},
  {InterruptId::FPU, StartupSymbolId::FPU_IRQHandler, 61u, 77u},
  {InterruptId::RSWDT, StartupSymbolId::RSWDT_IRQHandler, 63u, 79u},
  {InterruptId::CCW, StartupSymbolId::CCW_IRQHandler, 64u, 80u},
  {InterruptId::CCF, StartupSymbolId::CCF_IRQHandler, 65u, 81u},
  {InterruptId::GMAC_Q1, StartupSymbolId::GMAC_Q1_IRQHandler, 66u, 82u},
  {InterruptId::GMAC_Q2, StartupSymbolId::GMAC_Q2_IRQHandler, 67u, 83u},
  {InterruptId::IXC, StartupSymbolId::IXC_IRQHandler, 68u, 84u},
  {InterruptId::I2SC0, StartupSymbolId::I2SC0_IRQHandler, 69u, 85u},
  {InterruptId::GMAC_Q3, StartupSymbolId::GMAC_Q3_IRQHandler, 71u, 87u},
  {InterruptId::GMAC_Q4, StartupSymbolId::GMAC_Q4_IRQHandler, 72u, 88u},
  {InterruptId::GMAC_Q5, StartupSymbolId::GMAC_Q5_IRQHandler, 73u, 89u},
}};

template<InterruptId Id>
struct InterruptStubTraits {
  static constexpr bool kPresent = false;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::none;
  static constexpr std::uint16_t kLine = 0xFFFFu;
  static constexpr std::uint16_t kVectorSlot = 0xFFFFu;
};

template<>
struct InterruptStubTraits<InterruptId::SUPC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SUPC_IRQHandler;
  static constexpr std::uint16_t kLine = 0u;
  static constexpr std::uint16_t kVectorSlot = 16u;
};

template<>
struct InterruptStubTraits<InterruptId::RSTC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RSTC_IRQHandler;
  static constexpr std::uint16_t kLine = 1u;
  static constexpr std::uint16_t kVectorSlot = 17u;
};

template<>
struct InterruptStubTraits<InterruptId::RTC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RTC_IRQHandler;
  static constexpr std::uint16_t kLine = 2u;
  static constexpr std::uint16_t kVectorSlot = 18u;
};

template<>
struct InterruptStubTraits<InterruptId::RTT> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RTT_IRQHandler;
  static constexpr std::uint16_t kLine = 3u;
  static constexpr std::uint16_t kVectorSlot = 19u;
};

template<>
struct InterruptStubTraits<InterruptId::WDT> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::WDT_IRQHandler;
  static constexpr std::uint16_t kLine = 4u;
  static constexpr std::uint16_t kVectorSlot = 20u;
};

template<>
struct InterruptStubTraits<InterruptId::PMC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::PMC_IRQHandler;
  static constexpr std::uint16_t kLine = 5u;
  static constexpr std::uint16_t kVectorSlot = 21u;
};

template<>
struct InterruptStubTraits<InterruptId::EFC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::EFC_IRQHandler;
  static constexpr std::uint16_t kLine = 6u;
  static constexpr std::uint16_t kVectorSlot = 22u;
};

template<>
struct InterruptStubTraits<InterruptId::UART0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UART0_IRQHandler;
  static constexpr std::uint16_t kLine = 7u;
  static constexpr std::uint16_t kVectorSlot = 23u;
};

template<>
struct InterruptStubTraits<InterruptId::UART1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UART1_IRQHandler;
  static constexpr std::uint16_t kLine = 8u;
  static constexpr std::uint16_t kVectorSlot = 24u;
};

template<>
struct InterruptStubTraits<InterruptId::PIOA> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::PIOA_IRQHandler;
  static constexpr std::uint16_t kLine = 10u;
  static constexpr std::uint16_t kVectorSlot = 26u;
};

template<>
struct InterruptStubTraits<InterruptId::PIOB> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::PIOB_IRQHandler;
  static constexpr std::uint16_t kLine = 11u;
  static constexpr std::uint16_t kVectorSlot = 27u;
};

template<>
struct InterruptStubTraits<InterruptId::USART0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::USART0_IRQHandler;
  static constexpr std::uint16_t kLine = 13u;
  static constexpr std::uint16_t kVectorSlot = 29u;
};

template<>
struct InterruptStubTraits<InterruptId::USART1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::USART1_IRQHandler;
  static constexpr std::uint16_t kLine = 14u;
  static constexpr std::uint16_t kVectorSlot = 30u;
};

template<>
struct InterruptStubTraits<InterruptId::USART2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::USART2_IRQHandler;
  static constexpr std::uint16_t kLine = 15u;
  static constexpr std::uint16_t kVectorSlot = 31u;
};

template<>
struct InterruptStubTraits<InterruptId::PIOD> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::PIOD_IRQHandler;
  static constexpr std::uint16_t kLine = 16u;
  static constexpr std::uint16_t kVectorSlot = 32u;
};

template<>
struct InterruptStubTraits<InterruptId::HSMCI> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::HSMCI_IRQHandler;
  static constexpr std::uint16_t kLine = 18u;
  static constexpr std::uint16_t kVectorSlot = 34u;
};

template<>
struct InterruptStubTraits<InterruptId::TWIHS0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TWIHS0_IRQHandler;
  static constexpr std::uint16_t kLine = 19u;
  static constexpr std::uint16_t kVectorSlot = 35u;
};

template<>
struct InterruptStubTraits<InterruptId::TWIHS1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TWIHS1_IRQHandler;
  static constexpr std::uint16_t kLine = 20u;
  static constexpr std::uint16_t kVectorSlot = 36u;
};

template<>
struct InterruptStubTraits<InterruptId::SPI0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SPI0_IRQHandler;
  static constexpr std::uint16_t kLine = 21u;
  static constexpr std::uint16_t kVectorSlot = 37u;
};

template<>
struct InterruptStubTraits<InterruptId::SSC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::SSC_IRQHandler;
  static constexpr std::uint16_t kLine = 22u;
  static constexpr std::uint16_t kVectorSlot = 38u;
};

template<>
struct InterruptStubTraits<InterruptId::TC0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TC0_IRQHandler;
  static constexpr std::uint16_t kLine = 23u;
  static constexpr std::uint16_t kVectorSlot = 39u;
};

template<>
struct InterruptStubTraits<InterruptId::TC1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TC1_IRQHandler;
  static constexpr std::uint16_t kLine = 24u;
  static constexpr std::uint16_t kVectorSlot = 40u;
};

template<>
struct InterruptStubTraits<InterruptId::TC2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TC2_IRQHandler;
  static constexpr std::uint16_t kLine = 25u;
  static constexpr std::uint16_t kVectorSlot = 41u;
};

template<>
struct InterruptStubTraits<InterruptId::TC3> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TC3_IRQHandler;
  static constexpr std::uint16_t kLine = 26u;
  static constexpr std::uint16_t kVectorSlot = 42u;
};

template<>
struct InterruptStubTraits<InterruptId::TC4> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TC4_IRQHandler;
  static constexpr std::uint16_t kLine = 27u;
  static constexpr std::uint16_t kVectorSlot = 43u;
};

template<>
struct InterruptStubTraits<InterruptId::TC5> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TC5_IRQHandler;
  static constexpr std::uint16_t kLine = 28u;
  static constexpr std::uint16_t kVectorSlot = 44u;
};

template<>
struct InterruptStubTraits<InterruptId::AFEC0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::AFEC0_IRQHandler;
  static constexpr std::uint16_t kLine = 29u;
  static constexpr std::uint16_t kVectorSlot = 45u;
};

template<>
struct InterruptStubTraits<InterruptId::DACC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::DACC_IRQHandler;
  static constexpr std::uint16_t kLine = 30u;
  static constexpr std::uint16_t kVectorSlot = 46u;
};

template<>
struct InterruptStubTraits<InterruptId::PWM0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::PWM0_IRQHandler;
  static constexpr std::uint16_t kLine = 31u;
  static constexpr std::uint16_t kVectorSlot = 47u;
};

template<>
struct InterruptStubTraits<InterruptId::ICM> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::ICM_IRQHandler;
  static constexpr std::uint16_t kLine = 32u;
  static constexpr std::uint16_t kVectorSlot = 48u;
};

template<>
struct InterruptStubTraits<InterruptId::ACC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::ACC_IRQHandler;
  static constexpr std::uint16_t kLine = 33u;
  static constexpr std::uint16_t kVectorSlot = 49u;
};

template<>
struct InterruptStubTraits<InterruptId::USBHS> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::USBHS_IRQHandler;
  static constexpr std::uint16_t kLine = 34u;
  static constexpr std::uint16_t kVectorSlot = 50u;
};

template<>
struct InterruptStubTraits<InterruptId::MCAN0_INT0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::MCAN0_INT0_IRQHandler;
  static constexpr std::uint16_t kLine = 35u;
  static constexpr std::uint16_t kVectorSlot = 51u;
};

template<>
struct InterruptStubTraits<InterruptId::MCAN0_INT1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::MCAN0_INT1_IRQHandler;
  static constexpr std::uint16_t kLine = 36u;
  static constexpr std::uint16_t kVectorSlot = 52u;
};

template<>
struct InterruptStubTraits<InterruptId::MCAN1_INT0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::MCAN1_INT0_IRQHandler;
  static constexpr std::uint16_t kLine = 37u;
  static constexpr std::uint16_t kVectorSlot = 53u;
};

template<>
struct InterruptStubTraits<InterruptId::MCAN1_INT1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::MCAN1_INT1_IRQHandler;
  static constexpr std::uint16_t kLine = 38u;
  static constexpr std::uint16_t kVectorSlot = 54u;
};

template<>
struct InterruptStubTraits<InterruptId::GMAC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::GMAC_IRQHandler;
  static constexpr std::uint16_t kLine = 39u;
  static constexpr std::uint16_t kVectorSlot = 55u;
};

template<>
struct InterruptStubTraits<InterruptId::AFEC1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::AFEC1_IRQHandler;
  static constexpr std::uint16_t kLine = 40u;
  static constexpr std::uint16_t kVectorSlot = 56u;
};

template<>
struct InterruptStubTraits<InterruptId::TWIHS2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TWIHS2_IRQHandler;
  static constexpr std::uint16_t kLine = 41u;
  static constexpr std::uint16_t kVectorSlot = 57u;
};

template<>
struct InterruptStubTraits<InterruptId::QSPI> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::QSPI_IRQHandler;
  static constexpr std::uint16_t kLine = 43u;
  static constexpr std::uint16_t kVectorSlot = 59u;
};

template<>
struct InterruptStubTraits<InterruptId::UART2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UART2_IRQHandler;
  static constexpr std::uint16_t kLine = 44u;
  static constexpr std::uint16_t kVectorSlot = 60u;
};

template<>
struct InterruptStubTraits<InterruptId::UART3> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UART3_IRQHandler;
  static constexpr std::uint16_t kLine = 45u;
  static constexpr std::uint16_t kVectorSlot = 61u;
};

template<>
struct InterruptStubTraits<InterruptId::UART4> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::UART4_IRQHandler;
  static constexpr std::uint16_t kLine = 46u;
  static constexpr std::uint16_t kVectorSlot = 62u;
};

template<>
struct InterruptStubTraits<InterruptId::TC6> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TC6_IRQHandler;
  static constexpr std::uint16_t kLine = 47u;
  static constexpr std::uint16_t kVectorSlot = 63u;
};

template<>
struct InterruptStubTraits<InterruptId::TC7> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TC7_IRQHandler;
  static constexpr std::uint16_t kLine = 48u;
  static constexpr std::uint16_t kVectorSlot = 64u;
};

template<>
struct InterruptStubTraits<InterruptId::TC8> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TC8_IRQHandler;
  static constexpr std::uint16_t kLine = 49u;
  static constexpr std::uint16_t kVectorSlot = 65u;
};

template<>
struct InterruptStubTraits<InterruptId::TC9> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TC9_IRQHandler;
  static constexpr std::uint16_t kLine = 50u;
  static constexpr std::uint16_t kVectorSlot = 66u;
};

template<>
struct InterruptStubTraits<InterruptId::TC10> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TC10_IRQHandler;
  static constexpr std::uint16_t kLine = 51u;
  static constexpr std::uint16_t kVectorSlot = 67u;
};

template<>
struct InterruptStubTraits<InterruptId::TC11> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TC11_IRQHandler;
  static constexpr std::uint16_t kLine = 52u;
  static constexpr std::uint16_t kVectorSlot = 68u;
};

template<>
struct InterruptStubTraits<InterruptId::AES> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::AES_IRQHandler;
  static constexpr std::uint16_t kLine = 56u;
  static constexpr std::uint16_t kVectorSlot = 72u;
};

template<>
struct InterruptStubTraits<InterruptId::TRNG> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::TRNG_IRQHandler;
  static constexpr std::uint16_t kLine = 57u;
  static constexpr std::uint16_t kVectorSlot = 73u;
};

template<>
struct InterruptStubTraits<InterruptId::XDMAC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::XDMAC_IRQHandler;
  static constexpr std::uint16_t kLine = 58u;
  static constexpr std::uint16_t kVectorSlot = 74u;
};

template<>
struct InterruptStubTraits<InterruptId::ISI> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::ISI_IRQHandler;
  static constexpr std::uint16_t kLine = 59u;
  static constexpr std::uint16_t kVectorSlot = 75u;
};

template<>
struct InterruptStubTraits<InterruptId::PWM1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::PWM1_IRQHandler;
  static constexpr std::uint16_t kLine = 60u;
  static constexpr std::uint16_t kVectorSlot = 76u;
};

template<>
struct InterruptStubTraits<InterruptId::FPU> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::FPU_IRQHandler;
  static constexpr std::uint16_t kLine = 61u;
  static constexpr std::uint16_t kVectorSlot = 77u;
};

template<>
struct InterruptStubTraits<InterruptId::RSWDT> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::RSWDT_IRQHandler;
  static constexpr std::uint16_t kLine = 63u;
  static constexpr std::uint16_t kVectorSlot = 79u;
};

template<>
struct InterruptStubTraits<InterruptId::CCW> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CCW_IRQHandler;
  static constexpr std::uint16_t kLine = 64u;
  static constexpr std::uint16_t kVectorSlot = 80u;
};

template<>
struct InterruptStubTraits<InterruptId::CCF> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::CCF_IRQHandler;
  static constexpr std::uint16_t kLine = 65u;
  static constexpr std::uint16_t kVectorSlot = 81u;
};

template<>
struct InterruptStubTraits<InterruptId::GMAC_Q1> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::GMAC_Q1_IRQHandler;
  static constexpr std::uint16_t kLine = 66u;
  static constexpr std::uint16_t kVectorSlot = 82u;
};

template<>
struct InterruptStubTraits<InterruptId::GMAC_Q2> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::GMAC_Q2_IRQHandler;
  static constexpr std::uint16_t kLine = 67u;
  static constexpr std::uint16_t kVectorSlot = 83u;
};

template<>
struct InterruptStubTraits<InterruptId::IXC> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::IXC_IRQHandler;
  static constexpr std::uint16_t kLine = 68u;
  static constexpr std::uint16_t kVectorSlot = 84u;
};

template<>
struct InterruptStubTraits<InterruptId::I2SC0> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::I2SC0_IRQHandler;
  static constexpr std::uint16_t kLine = 69u;
  static constexpr std::uint16_t kVectorSlot = 85u;
};

template<>
struct InterruptStubTraits<InterruptId::GMAC_Q3> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::GMAC_Q3_IRQHandler;
  static constexpr std::uint16_t kLine = 71u;
  static constexpr std::uint16_t kVectorSlot = 87u;
};

template<>
struct InterruptStubTraits<InterruptId::GMAC_Q4> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::GMAC_Q4_IRQHandler;
  static constexpr std::uint16_t kLine = 72u;
  static constexpr std::uint16_t kVectorSlot = 88u;
};

template<>
struct InterruptStubTraits<InterruptId::GMAC_Q5> {
  static constexpr bool kPresent = true;
  static constexpr StartupSymbolId kSymbolId = StartupSymbolId::GMAC_Q5_IRQHandler;
  static constexpr std::uint16_t kLine = 73u;
  static constexpr std::uint16_t kVectorSlot = 89u;
};

}
}
}
}
}
}
