#include <cstdint>

#include "../../runtime/devices/rp2040/startup.hpp"

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
/* Boot stage-2 placeholder (256 bytes). Replace with a pico-sdk boot2 for your
   flash chip (e.g. boot2_w25q080.S). */
#if defined(__arm__) || defined(__thumb__)
__attribute__((section(".boot2"), used))
static const unsigned char __boot2_placeholder[256] = {0};
#endif

void SystemInit() __attribute__((weak));
void SystemInit() {}

void xip_init() __attribute__((weak));
void xip_init() {}

__attribute__((noreturn)) void Default_Handler() {
    while (true) {
#if defined(__arm__) || defined(__thumb__)
        __asm__ volatile("wfi");
#endif
    }
}

void ADC_IRQ_FIFO_IRQHandler() __attribute__((weak));
void ADC_IRQ_FIFO_IRQHandler() {
    Default_Handler();
}

void CLOCKS_IRQ_IRQHandler() __attribute__((weak));
void CLOCKS_IRQ_IRQHandler() {
    Default_Handler();
}

void DMA_IRQ_0_IRQHandler() __attribute__((weak));
void DMA_IRQ_0_IRQHandler() {
    Default_Handler();
}

void DMA_IRQ_1_IRQHandler() __attribute__((weak));
void DMA_IRQ_1_IRQHandler() {
    Default_Handler();
}

void HardFault_Handler() __attribute__((weak));
void HardFault_Handler() {
    Default_Handler();
}

void I2C0_IRQ_IRQHandler() __attribute__((weak));
void I2C0_IRQ_IRQHandler() {
    Default_Handler();
}

void I2C1_IRQ_IRQHandler() __attribute__((weak));
void I2C1_IRQ_IRQHandler() {
    Default_Handler();
}

void IO_IRQ_BANK0_IRQHandler() __attribute__((weak));
void IO_IRQ_BANK0_IRQHandler() {
    Default_Handler();
}

void NMI_Handler() __attribute__((weak));
void NMI_Handler() {
    Default_Handler();
}

void PIO0_IRQ_0_IRQHandler() __attribute__((weak));
void PIO0_IRQ_0_IRQHandler() {
    Default_Handler();
}

void PIO0_IRQ_1_IRQHandler() __attribute__((weak));
void PIO0_IRQ_1_IRQHandler() {
    Default_Handler();
}

void PIO1_IRQ_0_IRQHandler() __attribute__((weak));
void PIO1_IRQ_0_IRQHandler() {
    Default_Handler();
}

void PIO1_IRQ_1_IRQHandler() __attribute__((weak));
void PIO1_IRQ_1_IRQHandler() {
    Default_Handler();
}

void PWM_IRQ_WRAP_IRQHandler() __attribute__((weak));
void PWM_IRQ_WRAP_IRQHandler() {
    Default_Handler();
}

void PendSV_Handler() __attribute__((weak));
void PendSV_Handler() {
    Default_Handler();
}

void RTC_IRQ_IRQHandler() __attribute__((weak));
void RTC_IRQ_IRQHandler() {
    Default_Handler();
}

void Reserved_Handler_10() __attribute__((weak));
void Reserved_Handler_10() {
    Default_Handler();
}

void Reserved_Handler_12() __attribute__((weak));
void Reserved_Handler_12() {
    Default_Handler();
}

void Reserved_Handler_13() __attribute__((weak));
void Reserved_Handler_13() {
    Default_Handler();
}

void Reserved_Handler_4() __attribute__((weak));
void Reserved_Handler_4() {
    Default_Handler();
}

void Reserved_Handler_5() __attribute__((weak));
void Reserved_Handler_5() {
    Default_Handler();
}

void Reserved_Handler_6() __attribute__((weak));
void Reserved_Handler_6() {
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

void SPI0_IRQ_IRQHandler() __attribute__((weak));
void SPI0_IRQ_IRQHandler() {
    Default_Handler();
}

void SPI1_IRQ_IRQHandler() __attribute__((weak));
void SPI1_IRQ_IRQHandler() {
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

void TIMER_IRQ_0_IRQHandler() __attribute__((weak));
void TIMER_IRQ_0_IRQHandler() {
    Default_Handler();
}

void TIMER_IRQ_1_IRQHandler() __attribute__((weak));
void TIMER_IRQ_1_IRQHandler() {
    Default_Handler();
}

void TIMER_IRQ_2_IRQHandler() __attribute__((weak));
void TIMER_IRQ_2_IRQHandler() {
    Default_Handler();
}

void TIMER_IRQ_3_IRQHandler() __attribute__((weak));
void TIMER_IRQ_3_IRQHandler() {
    Default_Handler();
}

void UART0_IRQ_IRQHandler() __attribute__((weak));
void UART0_IRQ_IRQHandler() {
    Default_Handler();
}

void UART1_IRQ_IRQHandler() __attribute__((weak));
void UART1_IRQ_IRQHandler() {
    Default_Handler();
}

void USBCTRL_IRQ_IRQHandler() __attribute__((weak));
void USBCTRL_IRQ_IRQHandler() {
    Default_Handler();
}

__attribute__((noreturn)) void Reset_Handler() {
    // XIP flash initialisation must run before .data copy (RP2040 XIP).
    // Single-core-perspective: core 1 is not started in this generated startup.
    xip_init();
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
    Reserved_Handler_4,
    Reserved_Handler_5,
    Reserved_Handler_6,
    Reserved_Handler_7,
    Reserved_Handler_8,
    Reserved_Handler_9,
    Reserved_Handler_10,
    SVCall_Handler,
    Reserved_Handler_12,
    Reserved_Handler_13,
    PendSV_Handler,
    SysTick_Handler,
    TIMER_IRQ_0_IRQHandler,
    TIMER_IRQ_1_IRQHandler,
    TIMER_IRQ_2_IRQHandler,
    TIMER_IRQ_3_IRQHandler,
    PWM_IRQ_WRAP_IRQHandler,
    USBCTRL_IRQ_IRQHandler,
    nullptr,
    PIO0_IRQ_0_IRQHandler,
    PIO0_IRQ_1_IRQHandler,
    PIO1_IRQ_0_IRQHandler,
    PIO1_IRQ_1_IRQHandler,
    DMA_IRQ_0_IRQHandler,
    DMA_IRQ_1_IRQHandler,
    IO_IRQ_BANK0_IRQHandler,
    nullptr,
    nullptr,
    nullptr,
    CLOCKS_IRQ_IRQHandler,
    SPI0_IRQ_IRQHandler,
    SPI1_IRQ_IRQHandler,
    UART0_IRQ_IRQHandler,
    UART1_IRQ_IRQHandler,
    ADC_IRQ_FIFO_IRQHandler,
    I2C0_IRQ_IRQHandler,
    I2C1_IRQ_IRQHandler,
    RTC_IRQ_IRQHandler,
};
}
