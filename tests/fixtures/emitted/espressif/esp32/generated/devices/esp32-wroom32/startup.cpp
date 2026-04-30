#include <cstdint>

#include "../../runtime/devices/esp32-wroom32/startup.hpp"

// Dual-core Xtensa control plane (ESP32 LX6 / ESP32-S3 LX7):
//   * The ROM bootloader owns PRO_CPU's VECBASE and initial stack setup.
//   * This generated file provides BSS/data init, C++ ctor dispatch,
//     main() entry, weak peripheral IRQ stubs, AND APP_CPU bring-up.
//   * Per-core vector tables are exposed for inspection and for linker
//     scripts that map them into the per-core VECBASE regions.
//   * Inter-core synchronization (IPI senders, spinlocks, queues) is
//     intentionally NOT modelled here — applications layer those on top
//     via esp-idf or a hand-rolled IPC layer.

extern "C" {
#if defined(ALLOY_CODEGEN_HOST_SMOKE)
std::uint32_t __stack_top = 0u;
std::uint32_t __stack_top_cpu1 = 0u;
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
extern std::uint32_t __stack_top_cpu1;
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

// Weak hook applications can override to run code on APP_CPU after
// bring_up_app_cpu() releases it.  The default empty implementation
// returns immediately, after which Reset_Handler_CPU1 falls into
// Default_Handler.
void app_main_cpu1() __attribute__((weak));
void app_main_cpu1() {}

[[noreturn]] void Default_Handler() {
    while (true) {}
}

void BT_BB_IRQHandler() __attribute__((weak));
void BT_BB_IRQHandler() {
    Default_Handler();
}

void BT_BB_NMI_IRQHandler() __attribute__((weak));
void BT_BB_NMI_IRQHandler() {
    Default_Handler();
}

void BT_MAC_IRQHandler() __attribute__((weak));
void BT_MAC_IRQHandler() {
    Default_Handler();
}

void CACHE_IA_IRQHandler() __attribute__((weak));
void CACHE_IA_IRQHandler() {
    Default_Handler();
}

void EFUSE_IRQHandler() __attribute__((weak));
void EFUSE_IRQHandler() {
    Default_Handler();
}

void ETH_MAC_IRQHandler() __attribute__((weak));
void ETH_MAC_IRQHandler() {
    Default_Handler();
}

void FROM_CPU_INTR0_IRQHandler() __attribute__((weak));
void FROM_CPU_INTR0_IRQHandler() {
    Default_Handler();
}

void FROM_CPU_INTR1_IRQHandler() __attribute__((weak));
void FROM_CPU_INTR1_IRQHandler() {
    Default_Handler();
}

void FROM_CPU_INTR2_IRQHandler() __attribute__((weak));
void FROM_CPU_INTR2_IRQHandler() {
    Default_Handler();
}

void FROM_CPU_INTR3_IRQHandler() __attribute__((weak));
void FROM_CPU_INTR3_IRQHandler() {
    Default_Handler();
}

void GPIO_IRQHandler() __attribute__((weak));
void GPIO_IRQHandler() {
    Default_Handler();
}

void GPIO_NMI_IRQHandler() __attribute__((weak));
void GPIO_NMI_IRQHandler() {
    Default_Handler();
}

void I2C_EXT0_IRQHandler() __attribute__((weak));
void I2C_EXT0_IRQHandler() {
    Default_Handler();
}

void I2C_EXT1_IRQHandler() __attribute__((weak));
void I2C_EXT1_IRQHandler() {
    Default_Handler();
}

void I2S0_IRQHandler() __attribute__((weak));
void I2S0_IRQHandler() {
    Default_Handler();
}

void I2S1_IRQHandler() __attribute__((weak));
void I2S1_IRQHandler() {
    Default_Handler();
}

void LEDC_IRQHandler() __attribute__((weak));
void LEDC_IRQHandler() {
    Default_Handler();
}

void MCPWM0_IRQHandler() __attribute__((weak));
void MCPWM0_IRQHandler() {
    Default_Handler();
}

void MCPWM1_IRQHandler() __attribute__((weak));
void MCPWM1_IRQHandler() {
    Default_Handler();
}

void MCPWM2_IRQHandler() __attribute__((weak));
void MCPWM2_IRQHandler() {
    Default_Handler();
}

void MCPWM3_IRQHandler() __attribute__((weak));
void MCPWM3_IRQHandler() {
    Default_Handler();
}

void MMU_IA_IRQHandler() __attribute__((weak));
void MMU_IA_IRQHandler() {
    Default_Handler();
}

void MPU_IA_IRQHandler() __attribute__((weak));
void MPU_IA_IRQHandler() {
    Default_Handler();
}

void PCNT_IRQHandler() __attribute__((weak));
void PCNT_IRQHandler() {
    Default_Handler();
}

void RMT_IRQHandler() __attribute__((weak));
void RMT_IRQHandler() {
    Default_Handler();
}

void RSA_IRQHandler() __attribute__((weak));
void RSA_IRQHandler() {
    Default_Handler();
}

void RTC_CORE_IRQHandler() __attribute__((weak));
void RTC_CORE_IRQHandler() {
    Default_Handler();
}

void RWBLE_IRQHandler() __attribute__((weak));
void RWBLE_IRQHandler() {
    Default_Handler();
}

void RWBLE_NMI_IRQHandler() __attribute__((weak));
void RWBLE_NMI_IRQHandler() {
    Default_Handler();
}

void RWBT_IRQHandler() __attribute__((weak));
void RWBT_IRQHandler() {
    Default_Handler();
}

void RWBT_NMI_IRQHandler() __attribute__((weak));
void RWBT_NMI_IRQHandler() {
    Default_Handler();
}

void SDIO_HOST_IRQHandler() __attribute__((weak));
void SDIO_HOST_IRQHandler() {
    Default_Handler();
}

void SPI0_IRQHandler() __attribute__((weak));
void SPI0_IRQHandler() {
    Default_Handler();
}

void SPI1_DMA_IRQHandler() __attribute__((weak));
void SPI1_DMA_IRQHandler() {
    Default_Handler();
}

void SPI1_IRQHandler() __attribute__((weak));
void SPI1_IRQHandler() {
    Default_Handler();
}

void SPI2_DMA_IRQHandler() __attribute__((weak));
void SPI2_DMA_IRQHandler() {
    Default_Handler();
}

void SPI2_IRQHandler() __attribute__((weak));
void SPI2_IRQHandler() {
    Default_Handler();
}

void SPI3_DMA_IRQHandler() __attribute__((weak));
void SPI3_DMA_IRQHandler() {
    Default_Handler();
}

void SPI3_IRQHandler() __attribute__((weak));
void SPI3_IRQHandler() {
    Default_Handler();
}

void TG0_LACT_EDGE_IRQHandler() __attribute__((weak));
void TG0_LACT_EDGE_IRQHandler() {
    Default_Handler();
}

void TG0_LACT_LEVEL_IRQHandler() __attribute__((weak));
void TG0_LACT_LEVEL_IRQHandler() {
    Default_Handler();
}

void TG0_T0_EDGE_IRQHandler() __attribute__((weak));
void TG0_T0_EDGE_IRQHandler() {
    Default_Handler();
}

void TG0_T0_LEVEL_IRQHandler() __attribute__((weak));
void TG0_T0_LEVEL_IRQHandler() {
    Default_Handler();
}

void TG0_T1_EDGE_IRQHandler() __attribute__((weak));
void TG0_T1_EDGE_IRQHandler() {
    Default_Handler();
}

void TG0_T1_LEVEL_IRQHandler() __attribute__((weak));
void TG0_T1_LEVEL_IRQHandler() {
    Default_Handler();
}

void TG0_WDT_EDGE_IRQHandler() __attribute__((weak));
void TG0_WDT_EDGE_IRQHandler() {
    Default_Handler();
}

void TG0_WDT_LEVEL_IRQHandler() __attribute__((weak));
void TG0_WDT_LEVEL_IRQHandler() {
    Default_Handler();
}

void TG1_LACT_EDGE_IRQHandler() __attribute__((weak));
void TG1_LACT_EDGE_IRQHandler() {
    Default_Handler();
}

void TG1_LACT_LEVEL_IRQHandler() __attribute__((weak));
void TG1_LACT_LEVEL_IRQHandler() {
    Default_Handler();
}

void TG1_T0_EDGE_IRQHandler() __attribute__((weak));
void TG1_T0_EDGE_IRQHandler() {
    Default_Handler();
}

void TG1_T0_LEVEL_IRQHandler() __attribute__((weak));
void TG1_T0_LEVEL_IRQHandler() {
    Default_Handler();
}

void TG1_T1_EDGE_IRQHandler() __attribute__((weak));
void TG1_T1_EDGE_IRQHandler() {
    Default_Handler();
}

void TG1_T1_LEVEL_IRQHandler() __attribute__((weak));
void TG1_T1_LEVEL_IRQHandler() {
    Default_Handler();
}

void TG1_WDT_EDGE_IRQHandler() __attribute__((weak));
void TG1_WDT_EDGE_IRQHandler() {
    Default_Handler();
}

void TG1_WDT_LEVEL_IRQHandler() __attribute__((weak));
void TG1_WDT_LEVEL_IRQHandler() {
    Default_Handler();
}

void TIMER1_IRQHandler() __attribute__((weak));
void TIMER1_IRQHandler() {
    Default_Handler();
}

void TIMER2_IRQHandler() __attribute__((weak));
void TIMER2_IRQHandler() {
    Default_Handler();
}

void TWAI0_IRQHandler() __attribute__((weak));
void TWAI0_IRQHandler() {
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

void UHCI0_IRQHandler() __attribute__((weak));
void UHCI0_IRQHandler() {
    Default_Handler();
}

void UHCI1_IRQHandler() __attribute__((weak));
void UHCI1_IRQHandler() {
    Default_Handler();
}

void WDT_IRQHandler() __attribute__((weak));
void WDT_IRQHandler() {
    Default_Handler();
}

void WIFI_BB_IRQHandler() __attribute__((weak));
void WIFI_BB_IRQHandler() {
    Default_Handler();
}

void WIFI_MAC_IRQHandler() __attribute__((weak));
void WIFI_MAC_IRQHandler() {
    Default_Handler();
}

void WIFI_NMI_IRQHandler() __attribute__((weak));
void WIFI_NMI_IRQHandler() {
    Default_Handler();
}

// PRO_CPU entry — runs after the ROM bootloader transfers control to
// the application image.  VECBASE, stack, and cache have already been
// set up by ROM code for this core.
[[noreturn]] void Reset_Handler() {
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

// APP_CPU entry — invoked after bring_up_app_cpu() releases the second
// core.  Static init has already been performed by PRO_CPU; this entry
// only dispatches into the optional weak app_main_cpu1() hook and then
// stops.  Applications that want richer cpu1 behaviour override that
// hook (e.g. by linking against esp-idf or providing their own).
[[noreturn]] void Reset_Handler_CPU1() {
    app_main_cpu1();
    Default_Handler();
}

// Application-callable bring-up routine.  Not invoked from
// Reset_Handler; PRO_CPU calls this when it wants APP_CPU running.
void bring_up_app_cpu() {
#if defined(ALLOY_CODEGEN_HOST_SMOKE)
    // Host smoke: registers don't exist in this address space.
    return;
#else
    // ESP32 classic: write DPORT.APPCPU_CTRL_B bit 0 (APPCPU_CLKGATE_EN)
    // to release APP_CPU from reset.  ROM has already pointed APP_CPU's
    // VECBASE at the application image; this just unholds it.
    auto* const dport_appcpu_ctrl_b = reinterpret_cast<volatile std::uint32_t*>(
        0x3FF0'0030u);
    *dport_appcpu_ctrl_b = 1u;
#endif
}

// Per-core vector tables.  Xtensa uses VECBASE per core; linker scripts
// for real targets place these in distinct sections so each core's
// VECBASE points to its own table.  Host smoke builds keep the symbols
// reachable for inspection but skip the section attribute.
#if defined(ALLOY_CODEGEN_HOST_SMOKE)
__attribute__((used))
#else
__attribute__((section(".xtensa_vectors_cpu0"), used))
#endif
void (*const _vectors_cpu0[])() = {
    Reset_Handler,
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
    WIFI_MAC_IRQHandler,
    WIFI_NMI_IRQHandler,
    WIFI_BB_IRQHandler,
    BT_MAC_IRQHandler,
    BT_BB_IRQHandler,
    BT_BB_NMI_IRQHandler,
    RWBT_IRQHandler,
    RWBLE_IRQHandler,
    RWBT_NMI_IRQHandler,
    RWBLE_NMI_IRQHandler,
    nullptr,
    nullptr,
    UHCI0_IRQHandler,
    UHCI1_IRQHandler,
    TG0_T0_LEVEL_IRQHandler,
    TG0_T1_LEVEL_IRQHandler,
    TG0_WDT_LEVEL_IRQHandler,
    TG0_LACT_LEVEL_IRQHandler,
    TG1_T0_LEVEL_IRQHandler,
    TG1_T1_LEVEL_IRQHandler,
    TG1_WDT_LEVEL_IRQHandler,
    TG1_LACT_LEVEL_IRQHandler,
    GPIO_IRQHandler,
    GPIO_NMI_IRQHandler,
    FROM_CPU_INTR0_IRQHandler,
    FROM_CPU_INTR1_IRQHandler,
    FROM_CPU_INTR2_IRQHandler,
    FROM_CPU_INTR3_IRQHandler,
    SPI0_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    SPI3_IRQHandler,
    I2S0_IRQHandler,
    I2S1_IRQHandler,
    UART0_IRQHandler,
    UART1_IRQHandler,
    UART2_IRQHandler,
    SDIO_HOST_IRQHandler,
    ETH_MAC_IRQHandler,
    MCPWM0_IRQHandler,
    MCPWM1_IRQHandler,
    MCPWM2_IRQHandler,
    MCPWM3_IRQHandler,
    LEDC_IRQHandler,
    EFUSE_IRQHandler,
    TWAI0_IRQHandler,
    RTC_CORE_IRQHandler,
    RMT_IRQHandler,
    PCNT_IRQHandler,
    I2C_EXT0_IRQHandler,
    I2C_EXT1_IRQHandler,
    RSA_IRQHandler,
    SPI1_DMA_IRQHandler,
    SPI2_DMA_IRQHandler,
    SPI3_DMA_IRQHandler,
    WDT_IRQHandler,
    TIMER1_IRQHandler,
    TIMER2_IRQHandler,
    TG0_T0_EDGE_IRQHandler,
    TG0_T1_EDGE_IRQHandler,
    TG0_WDT_EDGE_IRQHandler,
    TG0_LACT_EDGE_IRQHandler,
    TG1_T0_EDGE_IRQHandler,
    TG1_T1_EDGE_IRQHandler,
    TG1_WDT_EDGE_IRQHandler,
    TG1_LACT_EDGE_IRQHandler,
    MMU_IA_IRQHandler,
    MPU_IA_IRQHandler,
    CACHE_IA_IRQHandler,
};

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
__attribute__((used))
#else
__attribute__((section(".xtensa_vectors_cpu1"), used))
#endif
void (*const _vectors_cpu1[])() = {
    nullptr,
};
}
