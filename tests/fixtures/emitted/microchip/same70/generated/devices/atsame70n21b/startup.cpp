#include <cstdint>

#include "../../runtime/devices/atsame70n21b/startup.hpp"

extern "C" {
#if defined(ALLOY_CODEGEN_HOST_SMOKE)
std::uint32_t __stack_top = 0u;
std::uint32_t _sidata = 0u;
std::uint32_t _sdata = 0u;
std::uint32_t _edata = 0u;
std::uint32_t _sbss = 0u;
std::uint32_t _ebss = 0u;
using InitFn = void (*)();
InitFn __init_array_start[] = {nullptr};
InitFn __init_array_end[] = {nullptr};
#else
extern std::uint32_t __stack_top;
extern std::uint32_t _sidata;
extern std::uint32_t _sdata;
extern std::uint32_t _edata;
extern std::uint32_t _sbss;
extern std::uint32_t _ebss;
extern void (*__init_array_start[])();
extern void (*__init_array_end[])();
#endif
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmain"
#endif
#if defined(ALLOY_CODEGEN_HOST_SMOKE)
int alloy_codegen_host_smoke_entry();
#else
int main();
#endif
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#if defined(ALLOY_CODEGEN_HOST_SMOKE)
int alloy_codegen_host_smoke_entry() {
    return 0;
}
#endif
void SystemInit() __attribute__((weak));
void SystemInit() {}

__attribute__((noreturn)) void Default_Handler() {
    while (true) {
#if defined(__arm__) || defined(__thumb__)
        __asm__ volatile("wfi");
#endif
    }
}

void ACC_IRQHandler() __attribute__((weak));
void ACC_IRQHandler() {
    Default_Handler();
}

void AES_IRQHandler() __attribute__((weak));
void AES_IRQHandler() {
    Default_Handler();
}

void AFEC0_IRQHandler() __attribute__((weak));
void AFEC0_IRQHandler() {
    Default_Handler();
}

void AFEC1_IRQHandler() __attribute__((weak));
void AFEC1_IRQHandler() {
    Default_Handler();
}

void BusFault_Handler() __attribute__((weak));
void BusFault_Handler() {
    Default_Handler();
}

void CCF_IRQHandler() __attribute__((weak));
void CCF_IRQHandler() {
    Default_Handler();
}

void CCW_IRQHandler() __attribute__((weak));
void CCW_IRQHandler() {
    Default_Handler();
}

void DACC_IRQHandler() __attribute__((weak));
void DACC_IRQHandler() {
    Default_Handler();
}

void DebugMon_Handler() __attribute__((weak));
void DebugMon_Handler() {
    Default_Handler();
}

void EFC_IRQHandler() __attribute__((weak));
void EFC_IRQHandler() {
    Default_Handler();
}

void FPU_IRQHandler() __attribute__((weak));
void FPU_IRQHandler() {
    Default_Handler();
}

void GMAC_IRQHandler() __attribute__((weak));
void GMAC_IRQHandler() {
    Default_Handler();
}

void GMAC_Q1_IRQHandler() __attribute__((weak));
void GMAC_Q1_IRQHandler() {
    Default_Handler();
}

void GMAC_Q2_IRQHandler() __attribute__((weak));
void GMAC_Q2_IRQHandler() {
    Default_Handler();
}

void GMAC_Q3_IRQHandler() __attribute__((weak));
void GMAC_Q3_IRQHandler() {
    Default_Handler();
}

void GMAC_Q4_IRQHandler() __attribute__((weak));
void GMAC_Q4_IRQHandler() {
    Default_Handler();
}

void GMAC_Q5_IRQHandler() __attribute__((weak));
void GMAC_Q5_IRQHandler() {
    Default_Handler();
}

void HSMCI_IRQHandler() __attribute__((weak));
void HSMCI_IRQHandler() {
    Default_Handler();
}

void HardFault_Handler() __attribute__((weak));
void HardFault_Handler() {
    Default_Handler();
}

void I2SC0_IRQHandler() __attribute__((weak));
void I2SC0_IRQHandler() {
    Default_Handler();
}

void ICM_IRQHandler() __attribute__((weak));
void ICM_IRQHandler() {
    Default_Handler();
}

void ISI_IRQHandler() __attribute__((weak));
void ISI_IRQHandler() {
    Default_Handler();
}

void IXC_IRQHandler() __attribute__((weak));
void IXC_IRQHandler() {
    Default_Handler();
}

void MCAN0_INT0_IRQHandler() __attribute__((weak));
void MCAN0_INT0_IRQHandler() {
    Default_Handler();
}

void MCAN0_INT1_IRQHandler() __attribute__((weak));
void MCAN0_INT1_IRQHandler() {
    Default_Handler();
}

void MCAN1_INT0_IRQHandler() __attribute__((weak));
void MCAN1_INT0_IRQHandler() {
    Default_Handler();
}

void MCAN1_INT1_IRQHandler() __attribute__((weak));
void MCAN1_INT1_IRQHandler() {
    Default_Handler();
}

void MemManage_Handler() __attribute__((weak));
void MemManage_Handler() {
    Default_Handler();
}

void NMI_Handler() __attribute__((weak));
void NMI_Handler() {
    Default_Handler();
}

void PIOA_IRQHandler() __attribute__((weak));
void PIOA_IRQHandler() {
    Default_Handler();
}

void PIOB_IRQHandler() __attribute__((weak));
void PIOB_IRQHandler() {
    Default_Handler();
}

void PIOD_IRQHandler() __attribute__((weak));
void PIOD_IRQHandler() {
    Default_Handler();
}

void PMC_IRQHandler() __attribute__((weak));
void PMC_IRQHandler() {
    Default_Handler();
}

void PWM0_IRQHandler() __attribute__((weak));
void PWM0_IRQHandler() {
    Default_Handler();
}

void PWM1_IRQHandler() __attribute__((weak));
void PWM1_IRQHandler() {
    Default_Handler();
}

void PendSV_Handler() __attribute__((weak));
void PendSV_Handler() {
    Default_Handler();
}

void QSPI_IRQHandler() __attribute__((weak));
void QSPI_IRQHandler() {
    Default_Handler();
}

void RSTC_IRQHandler() __attribute__((weak));
void RSTC_IRQHandler() {
    Default_Handler();
}

void RSWDT_IRQHandler() __attribute__((weak));
void RSWDT_IRQHandler() {
    Default_Handler();
}

void RTC_IRQHandler() __attribute__((weak));
void RTC_IRQHandler() {
    Default_Handler();
}

void RTT_IRQHandler() __attribute__((weak));
void RTT_IRQHandler() {
    Default_Handler();
}

void Reserved_Handler_10() __attribute__((weak));
void Reserved_Handler_10() {
    Default_Handler();
}

void Reserved_Handler_13() __attribute__((weak));
void Reserved_Handler_13() {
    Default_Handler();
}

void Reserved_Handler_7() __attribute__((weak));
void Reserved_Handler_7() {
    Default_Handler();
}

void Reserved_Handler_8() __attribute__((weak));
void Reserved_Handler_8() {
    Default_Handler();
}

void Reserved_Handler_9() __attribute__((weak));
void Reserved_Handler_9() {
    Default_Handler();
}

void SPI0_IRQHandler() __attribute__((weak));
void SPI0_IRQHandler() {
    Default_Handler();
}

void SSC_IRQHandler() __attribute__((weak));
void SSC_IRQHandler() {
    Default_Handler();
}

void SUPC_IRQHandler() __attribute__((weak));
void SUPC_IRQHandler() {
    Default_Handler();
}

void SVCall_Handler() __attribute__((weak));
void SVCall_Handler() {
    Default_Handler();
}

void SysTick_Handler() __attribute__((weak));
void SysTick_Handler() {
    Default_Handler();
}

void TC0_IRQHandler() __attribute__((weak));
void TC0_IRQHandler() {
    Default_Handler();
}

void TC10_IRQHandler() __attribute__((weak));
void TC10_IRQHandler() {
    Default_Handler();
}

void TC11_IRQHandler() __attribute__((weak));
void TC11_IRQHandler() {
    Default_Handler();
}

void TC1_IRQHandler() __attribute__((weak));
void TC1_IRQHandler() {
    Default_Handler();
}

void TC2_IRQHandler() __attribute__((weak));
void TC2_IRQHandler() {
    Default_Handler();
}

void TC3_IRQHandler() __attribute__((weak));
void TC3_IRQHandler() {
    Default_Handler();
}

void TC4_IRQHandler() __attribute__((weak));
void TC4_IRQHandler() {
    Default_Handler();
}

void TC5_IRQHandler() __attribute__((weak));
void TC5_IRQHandler() {
    Default_Handler();
}

void TC6_IRQHandler() __attribute__((weak));
void TC6_IRQHandler() {
    Default_Handler();
}

void TC7_IRQHandler() __attribute__((weak));
void TC7_IRQHandler() {
    Default_Handler();
}

void TC8_IRQHandler() __attribute__((weak));
void TC8_IRQHandler() {
    Default_Handler();
}

void TC9_IRQHandler() __attribute__((weak));
void TC9_IRQHandler() {
    Default_Handler();
}

void TRNG_IRQHandler() __attribute__((weak));
void TRNG_IRQHandler() {
    Default_Handler();
}

void TWIHS0_IRQHandler() __attribute__((weak));
void TWIHS0_IRQHandler() {
    Default_Handler();
}

void TWIHS1_IRQHandler() __attribute__((weak));
void TWIHS1_IRQHandler() {
    Default_Handler();
}

void TWIHS2_IRQHandler() __attribute__((weak));
void TWIHS2_IRQHandler() {
    Default_Handler();
}

void UART0_IRQHandler() __attribute__((weak));
void UART0_IRQHandler() {
    Default_Handler();
}

void UART1_IRQHandler() __attribute__((weak));
void UART1_IRQHandler() {
    Default_Handler();
}

void UART2_IRQHandler() __attribute__((weak));
void UART2_IRQHandler() {
    Default_Handler();
}

void UART3_IRQHandler() __attribute__((weak));
void UART3_IRQHandler() {
    Default_Handler();
}

void UART4_IRQHandler() __attribute__((weak));
void UART4_IRQHandler() {
    Default_Handler();
}

void USART0_IRQHandler() __attribute__((weak));
void USART0_IRQHandler() {
    Default_Handler();
}

void USART1_IRQHandler() __attribute__((weak));
void USART1_IRQHandler() {
    Default_Handler();
}

void USART2_IRQHandler() __attribute__((weak));
void USART2_IRQHandler() {
    Default_Handler();
}

void USBHS_IRQHandler() __attribute__((weak));
void USBHS_IRQHandler() {
    Default_Handler();
}

void UsageFault_Handler() __attribute__((weak));
void UsageFault_Handler() {
    Default_Handler();
}

void WDT_IRQHandler() __attribute__((weak));
void WDT_IRQHandler() {
    Default_Handler();
}

void XDMAC_IRQHandler() __attribute__((weak));
void XDMAC_IRQHandler() {
    Default_Handler();
}

__attribute__((noreturn)) void Reset_Handler() {
    auto* copy_source = &_sidata;
    auto* copy_target = &_sdata;
    while (copy_target < &_edata) {
        *copy_target++ = *copy_source++;
    }
    auto* zero_target = &_sbss;
    while (zero_target < &_ebss) {
        *zero_target++ = 0u;
    }
    SystemInit();
    for (auto ctor = __init_array_start; ctor < __init_array_end; ++ctor) {
        if (*ctor != nullptr) {
            (*ctor)();
        }
    }
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmain"
#endif
#if defined(ALLOY_CODEGEN_HOST_SMOKE)
    static_cast<void>(alloy_codegen_host_smoke_entry());
#else
    static_cast<void>(main());
#endif
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
__attribute__((used))
#else
__attribute__((section(".isr_vector"), used))
#endif
void (*const _vectors[])() = {
    reinterpret_cast<void (*)()>(&__stack_top),
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    Reserved_Handler_7,
    Reserved_Handler_8,
    Reserved_Handler_9,
    Reserved_Handler_10,
    SVCall_Handler,
    DebugMon_Handler,
    Reserved_Handler_13,
    PendSV_Handler,
    SysTick_Handler,
    SUPC_IRQHandler,
    RSTC_IRQHandler,
    RTC_IRQHandler,
    RTT_IRQHandler,
    WDT_IRQHandler,
    PMC_IRQHandler,
    EFC_IRQHandler,
    UART0_IRQHandler,
    UART1_IRQHandler,
    nullptr,
    PIOA_IRQHandler,
    PIOB_IRQHandler,
    nullptr,
    USART0_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    PIOD_IRQHandler,
    nullptr,
    HSMCI_IRQHandler,
    TWIHS0_IRQHandler,
    TWIHS1_IRQHandler,
    SPI0_IRQHandler,
    SSC_IRQHandler,
    TC0_IRQHandler,
    TC1_IRQHandler,
    TC2_IRQHandler,
    TC3_IRQHandler,
    TC4_IRQHandler,
    TC5_IRQHandler,
    AFEC0_IRQHandler,
    DACC_IRQHandler,
    PWM0_IRQHandler,
    ICM_IRQHandler,
    ACC_IRQHandler,
    USBHS_IRQHandler,
    MCAN0_INT0_IRQHandler,
    MCAN0_INT1_IRQHandler,
    MCAN1_INT0_IRQHandler,
    MCAN1_INT1_IRQHandler,
    GMAC_IRQHandler,
    AFEC1_IRQHandler,
    TWIHS2_IRQHandler,
    nullptr,
    QSPI_IRQHandler,
    UART2_IRQHandler,
    UART3_IRQHandler,
    UART4_IRQHandler,
    TC6_IRQHandler,
    TC7_IRQHandler,
    TC8_IRQHandler,
    TC9_IRQHandler,
    TC10_IRQHandler,
    TC11_IRQHandler,
    nullptr,
    nullptr,
    nullptr,
    AES_IRQHandler,
    TRNG_IRQHandler,
    XDMAC_IRQHandler,
    ISI_IRQHandler,
    PWM1_IRQHandler,
    FPU_IRQHandler,
    nullptr,
    RSWDT_IRQHandler,
    CCW_IRQHandler,
    CCF_IRQHandler,
    GMAC_Q1_IRQHandler,
    GMAC_Q2_IRQHandler,
    IXC_IRQHandler,
    I2SC0_IRQHandler,
    nullptr,
    GMAC_Q3_IRQHandler,
    GMAC_Q4_IRQHandler,
    GMAC_Q5_IRQHandler,
};
}
