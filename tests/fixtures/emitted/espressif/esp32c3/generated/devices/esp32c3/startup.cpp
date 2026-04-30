#include <cstdint>

#include "../../runtime/devices/esp32c3/startup.hpp"

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

[[noreturn]] void Default_Handler() {
    while (true) {}
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void AES_IRQHandler() __attribute__((weak));
#else
void AES_IRQHandler() __attribute__((weak, interrupt));
#endif
void AES_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void APB_ADC_IRQHandler() __attribute__((weak));
#else
void APB_ADC_IRQHandler() __attribute__((weak, interrupt));
#endif
void APB_ADC_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void APB_CTRL_IRQHandler() __attribute__((weak));
#else
void APB_CTRL_IRQHandler() __attribute__((weak, interrupt));
#endif
void APB_CTRL_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void ASSIST_DEBUG_IRQHandler() __attribute__((weak));
#else
void ASSIST_DEBUG_IRQHandler() __attribute__((weak, interrupt));
#endif
void ASSIST_DEBUG_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void BAK_PMS_VIOLATE_IRQHandler() __attribute__((weak));
#else
void BAK_PMS_VIOLATE_IRQHandler() __attribute__((weak, interrupt));
#endif
void BAK_PMS_VIOLATE_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void BT_BB_IRQHandler() __attribute__((weak));
#else
void BT_BB_IRQHandler() __attribute__((weak, interrupt));
#endif
void BT_BB_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void BT_BB_NMI_IRQHandler() __attribute__((weak));
#else
void BT_BB_NMI_IRQHandler() __attribute__((weak, interrupt));
#endif
void BT_BB_NMI_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void BT_MAC_IRQHandler() __attribute__((weak));
#else
void BT_MAC_IRQHandler() __attribute__((weak, interrupt));
#endif
void BT_MAC_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void CACHE_CORE0_ACS_IRQHandler() __attribute__((weak));
#else
void CACHE_CORE0_ACS_IRQHandler() __attribute__((weak, interrupt));
#endif
void CACHE_CORE0_ACS_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void CACHE_IA_IRQHandler() __attribute__((weak));
#else
void CACHE_IA_IRQHandler() __attribute__((weak, interrupt));
#endif
void CACHE_IA_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void CORE0_DRAM0_PMS_IRQHandler() __attribute__((weak));
#else
void CORE0_DRAM0_PMS_IRQHandler() __attribute__((weak, interrupt));
#endif
void CORE0_DRAM0_PMS_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void CORE0_IRAM0_PMS_IRQHandler() __attribute__((weak));
#else
void CORE0_IRAM0_PMS_IRQHandler() __attribute__((weak, interrupt));
#endif
void CORE0_IRAM0_PMS_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void CORE0_PIF_PMS_IRQHandler() __attribute__((weak));
#else
void CORE0_PIF_PMS_IRQHandler() __attribute__((weak, interrupt));
#endif
void CORE0_PIF_PMS_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void CORE0_PIF_PMS_SIZE_IRQHandler() __attribute__((weak));
#else
void CORE0_PIF_PMS_SIZE_IRQHandler() __attribute__((weak, interrupt));
#endif
void CORE0_PIF_PMS_SIZE_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void DMA_APBPERI_PMS_IRQHandler() __attribute__((weak));
#else
void DMA_APBPERI_PMS_IRQHandler() __attribute__((weak, interrupt));
#endif
void DMA_APBPERI_PMS_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void DMA_CH0_IRQHandler() __attribute__((weak));
#else
void DMA_CH0_IRQHandler() __attribute__((weak, interrupt));
#endif
void DMA_CH0_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void DMA_CH1_IRQHandler() __attribute__((weak));
#else
void DMA_CH1_IRQHandler() __attribute__((weak, interrupt));
#endif
void DMA_CH1_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void DMA_CH2_IRQHandler() __attribute__((weak));
#else
void DMA_CH2_IRQHandler() __attribute__((weak, interrupt));
#endif
void DMA_CH2_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void EFUSE_IRQHandler() __attribute__((weak));
#else
void EFUSE_IRQHandler() __attribute__((weak, interrupt));
#endif
void EFUSE_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void FROM_CPU_INTR0_IRQHandler() __attribute__((weak));
#else
void FROM_CPU_INTR0_IRQHandler() __attribute__((weak, interrupt));
#endif
void FROM_CPU_INTR0_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void FROM_CPU_INTR1_IRQHandler() __attribute__((weak));
#else
void FROM_CPU_INTR1_IRQHandler() __attribute__((weak, interrupt));
#endif
void FROM_CPU_INTR1_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void FROM_CPU_INTR2_IRQHandler() __attribute__((weak));
#else
void FROM_CPU_INTR2_IRQHandler() __attribute__((weak, interrupt));
#endif
void FROM_CPU_INTR2_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void FROM_CPU_INTR3_IRQHandler() __attribute__((weak));
#else
void FROM_CPU_INTR3_IRQHandler() __attribute__((weak, interrupt));
#endif
void FROM_CPU_INTR3_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void GPIO_IRQHandler() __attribute__((weak));
#else
void GPIO_IRQHandler() __attribute__((weak, interrupt));
#endif
void GPIO_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void GPIO_NMI_IRQHandler() __attribute__((weak));
#else
void GPIO_NMI_IRQHandler() __attribute__((weak, interrupt));
#endif
void GPIO_NMI_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void I2C_EXT0_IRQHandler() __attribute__((weak));
#else
void I2C_EXT0_IRQHandler() __attribute__((weak, interrupt));
#endif
void I2C_EXT0_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void I2C_MASTER_IRQHandler() __attribute__((weak));
#else
void I2C_MASTER_IRQHandler() __attribute__((weak, interrupt));
#endif
void I2C_MASTER_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void I2S0_IRQHandler() __attribute__((weak));
#else
void I2S0_IRQHandler() __attribute__((weak, interrupt));
#endif
void I2S0_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void ICACHE_PRELOAD0_IRQHandler() __attribute__((weak));
#else
void ICACHE_PRELOAD0_IRQHandler() __attribute__((weak, interrupt));
#endif
void ICACHE_PRELOAD0_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void ICACHE_SYNC0_IRQHandler() __attribute__((weak));
#else
void ICACHE_SYNC0_IRQHandler() __attribute__((weak, interrupt));
#endif
void ICACHE_SYNC0_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void LEDC_IRQHandler() __attribute__((weak));
#else
void LEDC_IRQHandler() __attribute__((weak, interrupt));
#endif
void LEDC_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void RMT_IRQHandler() __attribute__((weak));
#else
void RMT_IRQHandler() __attribute__((weak, interrupt));
#endif
void RMT_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void RSA_IRQHandler() __attribute__((weak));
#else
void RSA_IRQHandler() __attribute__((weak, interrupt));
#endif
void RSA_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void RTC_CORE_IRQHandler() __attribute__((weak));
#else
void RTC_CORE_IRQHandler() __attribute__((weak, interrupt));
#endif
void RTC_CORE_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void RWBLE_IRQHandler() __attribute__((weak));
#else
void RWBLE_IRQHandler() __attribute__((weak, interrupt));
#endif
void RWBLE_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void RWBLE_NMI_IRQHandler() __attribute__((weak));
#else
void RWBLE_NMI_IRQHandler() __attribute__((weak, interrupt));
#endif
void RWBLE_NMI_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void RWBT_IRQHandler() __attribute__((weak));
#else
void RWBT_IRQHandler() __attribute__((weak, interrupt));
#endif
void RWBT_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void RWBT_NMI_IRQHandler() __attribute__((weak));
#else
void RWBT_NMI_IRQHandler() __attribute__((weak, interrupt));
#endif
void RWBT_NMI_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void SHA_IRQHandler() __attribute__((weak));
#else
void SHA_IRQHandler() __attribute__((weak, interrupt));
#endif
void SHA_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void SLC0_IRQHandler() __attribute__((weak));
#else
void SLC0_IRQHandler() __attribute__((weak, interrupt));
#endif
void SLC0_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void SLC1_IRQHandler() __attribute__((weak));
#else
void SLC1_IRQHandler() __attribute__((weak, interrupt));
#endif
void SLC1_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void SPI1_IRQHandler() __attribute__((weak));
#else
void SPI1_IRQHandler() __attribute__((weak, interrupt));
#endif
void SPI1_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void SPI2_IRQHandler() __attribute__((weak));
#else
void SPI2_IRQHandler() __attribute__((weak, interrupt));
#endif
void SPI2_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void SPI_MEM_REJECT_CACHE_IRQHandler() __attribute__((weak));
#else
void SPI_MEM_REJECT_CACHE_IRQHandler() __attribute__((weak, interrupt));
#endif
void SPI_MEM_REJECT_CACHE_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void SYSTIMER_TARGET0_IRQHandler() __attribute__((weak));
#else
void SYSTIMER_TARGET0_IRQHandler() __attribute__((weak, interrupt));
#endif
void SYSTIMER_TARGET0_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void SYSTIMER_TARGET1_IRQHandler() __attribute__((weak));
#else
void SYSTIMER_TARGET1_IRQHandler() __attribute__((weak, interrupt));
#endif
void SYSTIMER_TARGET1_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void SYSTIMER_TARGET2_IRQHandler() __attribute__((weak));
#else
void SYSTIMER_TARGET2_IRQHandler() __attribute__((weak, interrupt));
#endif
void SYSTIMER_TARGET2_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void TG0_T0_LEVEL_IRQHandler() __attribute__((weak));
#else
void TG0_T0_LEVEL_IRQHandler() __attribute__((weak, interrupt));
#endif
void TG0_T0_LEVEL_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void TG0_WDT_LEVEL_IRQHandler() __attribute__((weak));
#else
void TG0_WDT_LEVEL_IRQHandler() __attribute__((weak, interrupt));
#endif
void TG0_WDT_LEVEL_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void TG1_T0_LEVEL_IRQHandler() __attribute__((weak));
#else
void TG1_T0_LEVEL_IRQHandler() __attribute__((weak, interrupt));
#endif
void TG1_T0_LEVEL_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void TG1_WDT_LEVEL_IRQHandler() __attribute__((weak));
#else
void TG1_WDT_LEVEL_IRQHandler() __attribute__((weak, interrupt));
#endif
void TG1_WDT_LEVEL_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void TIMER1_IRQHandler() __attribute__((weak));
#else
void TIMER1_IRQHandler() __attribute__((weak, interrupt));
#endif
void TIMER1_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void TIMER2_IRQHandler() __attribute__((weak));
#else
void TIMER2_IRQHandler() __attribute__((weak, interrupt));
#endif
void TIMER2_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void TWAI0_IRQHandler() __attribute__((weak));
#else
void TWAI0_IRQHandler() __attribute__((weak, interrupt));
#endif
void TWAI0_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void UART0_IRQHandler() __attribute__((weak));
#else
void UART0_IRQHandler() __attribute__((weak, interrupt));
#endif
void UART0_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void UART1_IRQHandler() __attribute__((weak));
#else
void UART1_IRQHandler() __attribute__((weak, interrupt));
#endif
void UART1_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void UHCI0_IRQHandler() __attribute__((weak));
#else
void UHCI0_IRQHandler() __attribute__((weak, interrupt));
#endif
void UHCI0_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void USB_DEVICE_IRQHandler() __attribute__((weak));
#else
void USB_DEVICE_IRQHandler() __attribute__((weak, interrupt));
#endif
void USB_DEVICE_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void WIFI_BB_IRQHandler() __attribute__((weak));
#else
void WIFI_BB_IRQHandler() __attribute__((weak, interrupt));
#endif
void WIFI_BB_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void WIFI_MAC_IRQHandler() __attribute__((weak));
#else
void WIFI_MAC_IRQHandler() __attribute__((weak, interrupt));
#endif
void WIFI_MAC_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void WIFI_MAC_NMI_IRQHandler() __attribute__((weak));
#else
void WIFI_MAC_NMI_IRQHandler() __attribute__((weak, interrupt));
#endif
void WIFI_MAC_NMI_IRQHandler() {
    Default_Handler();
}

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
void WIFI_PWR_IRQHandler() __attribute__((weak));
#else
void WIFI_PWR_IRQHandler() __attribute__((weak, interrupt));
#endif
void WIFI_PWR_IRQHandler() {
    Default_Handler();
}

// Reset_Handler is the RISC-V entry point invoked by the ROM bootloader.
// It initialises the stack, clears BSS, copies initialised data, runs
// C++ constructors, then calls main().
[[noreturn]] void Reset_Handler() {
    // Initialise stack pointer.
#if !defined(ALLOY_CODEGEN_HOST_SMOKE)
    __asm__ volatile(
        "la sp, __stack_top\n"
    );
#endif
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

// RISC-V vectored CLIC interrupt table.  mtvec is set to the base of
// _vectors[] with MODE=1 (vectored) by the ROM bootloader or early startup.
#if defined(ALLOY_CODEGEN_HOST_SMOKE)
__attribute__((used))
#else
__attribute__((section(".isr_vector"), used))
#endif
void (*const _vectors[])() = {
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
    WIFI_MAC_NMI_IRQHandler,
    WIFI_PWR_IRQHandler,
    WIFI_BB_IRQHandler,
    BT_MAC_IRQHandler,
    BT_BB_IRQHandler,
    BT_BB_NMI_IRQHandler,
    RWBT_IRQHandler,
    RWBLE_IRQHandler,
    RWBT_NMI_IRQHandler,
    RWBLE_NMI_IRQHandler,
    I2C_MASTER_IRQHandler,
    SLC0_IRQHandler,
    SLC1_IRQHandler,
    APB_CTRL_IRQHandler,
    UHCI0_IRQHandler,
    GPIO_IRQHandler,
    GPIO_NMI_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    I2S0_IRQHandler,
    UART0_IRQHandler,
    UART1_IRQHandler,
    LEDC_IRQHandler,
    EFUSE_IRQHandler,
    TWAI0_IRQHandler,
    USB_DEVICE_IRQHandler,
    RTC_CORE_IRQHandler,
    RMT_IRQHandler,
    I2C_EXT0_IRQHandler,
    TIMER1_IRQHandler,
    TIMER2_IRQHandler,
    TG0_T0_LEVEL_IRQHandler,
    TG0_WDT_LEVEL_IRQHandler,
    TG1_T0_LEVEL_IRQHandler,
    TG1_WDT_LEVEL_IRQHandler,
    CACHE_IA_IRQHandler,
    SYSTIMER_TARGET0_IRQHandler,
    SYSTIMER_TARGET1_IRQHandler,
    SYSTIMER_TARGET2_IRQHandler,
    SPI_MEM_REJECT_CACHE_IRQHandler,
    ICACHE_PRELOAD0_IRQHandler,
    ICACHE_SYNC0_IRQHandler,
    APB_ADC_IRQHandler,
    DMA_CH0_IRQHandler,
    DMA_CH1_IRQHandler,
    DMA_CH2_IRQHandler,
    RSA_IRQHandler,
    AES_IRQHandler,
    SHA_IRQHandler,
    FROM_CPU_INTR0_IRQHandler,
    FROM_CPU_INTR1_IRQHandler,
    FROM_CPU_INTR2_IRQHandler,
    FROM_CPU_INTR3_IRQHandler,
    ASSIST_DEBUG_IRQHandler,
    DMA_APBPERI_PMS_IRQHandler,
    CORE0_IRAM0_PMS_IRQHandler,
    CORE0_DRAM0_PMS_IRQHandler,
    CORE0_PIF_PMS_IRQHandler,
    CORE0_PIF_PMS_SIZE_IRQHandler,
    BAK_PMS_VIOLATE_IRQHandler,
    CACHE_CORE0_ACS_IRQHandler,
};
}
