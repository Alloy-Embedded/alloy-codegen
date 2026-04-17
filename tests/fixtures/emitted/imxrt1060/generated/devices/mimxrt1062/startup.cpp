#include <cstdint>

#include "../../runtime/devices/mimxrt1062/startup.hpp"

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

void BusFault_Handler() __attribute__((weak));
void BusFault_Handler() {
    Default_Handler();
}

void DebugMon_Handler() __attribute__((weak));
void DebugMon_Handler() {
    Default_Handler();
}

void HardFault_Handler() __attribute__((weak));
void HardFault_Handler() {
    Default_Handler();
}

void LPI2C1_IRQHandler() __attribute__((weak));
void LPI2C1_IRQHandler() {
    Default_Handler();
}

void LPSPI1_IRQHandler() __attribute__((weak));
void LPSPI1_IRQHandler() {
    Default_Handler();
}

void LPUART1_IRQHandler() __attribute__((weak));
void LPUART1_IRQHandler() {
    Default_Handler();
}

void LPUART3_IRQHandler() __attribute__((weak));
void LPUART3_IRQHandler() {
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

void PendSV_Handler() __attribute__((weak));
void PendSV_Handler() {
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

void SVCall_Handler() __attribute__((weak));
void SVCall_Handler() {
    Default_Handler();
}

void SysTick_Handler() __attribute__((weak));
void SysTick_Handler() {
    Default_Handler();
}

void UsageFault_Handler() __attribute__((weak));
void UsageFault_Handler() {
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
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    LPUART1_IRQHandler,
    nullptr,
    LPUART3_IRQHandler,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    LPI2C1_IRQHandler,
    nullptr,
    nullptr,
    nullptr,
    LPSPI1_IRQHandler,
};
}
