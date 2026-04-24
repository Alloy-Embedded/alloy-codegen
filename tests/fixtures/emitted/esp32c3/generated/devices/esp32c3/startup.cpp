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

void AES_IRQHandler() __attribute__((weak, interrupt));
void AES_IRQHandler() {
    Default_Handler();
}

void APB_ADC_IRQHandler() __attribute__((weak, interrupt));
void APB_ADC_IRQHandler() {
    Default_Handler();
}

void APB_CTRL_IRQHandler() __attribute__((weak, interrupt));
void APB_CTRL_IRQHandler() {
    Default_Handler();
}

void ASSIST_DEBUG_IRQHandler() __attribute__((weak, interrupt));
void ASSIST_DEBUG_IRQHandler() {
    Default_Handler();
}

void BAK_PMS_VIOLATE_IRQHandler() __attribute__((weak, interrupt));
void BAK_PMS_VIOLATE_IRQHandler() {
    Default_Handler();
}

void BT_BB_IRQHandler() __attribute__((weak, interrupt));
void BT_BB_IRQHandler() {
    Default_Handler();
}

void BT_BB_NMI_IRQHandler() __attribute__((weak, interrupt));
void BT_BB_NMI_IRQHandler() {
    Default_Handler();
}

void BT_MAC_IRQHandler() __attribute__((weak, interrupt));
void BT_MAC_IRQHandler() {
    Default_Handler();
}

void CACHE_CORE0_ACS_IRQHandler() __attribute__((weak, interrupt));
void CACHE_CORE0_ACS_IRQHandler() {
    Default_Handler();
}

void CACHE_IA_IRQHandler() __attribute__((weak, interrupt));
void CACHE_IA_IRQHandler() {
    Default_Handler();
}

void CORE0_DRAM0_PMS_IRQHandler() __attribute__((weak, interrupt));
void CORE0_DRAM0_PMS_IRQHandler() {
    Default_Handler();
}

void CORE0_IRAM0_PMS_IRQHandler() __attribute__((weak, interrupt));
void CORE0_IRAM0_PMS_IRQHandler() {
    Default_Handler();
}

void CORE0_PIF_PMS_IRQHandler() __attribute__((weak, interrupt));
void CORE0_PIF_PMS_IRQHandler() {
    Default_Handler();
}

void CORE0_PIF_PMS_SIZE_IRQHandler() __attribute__((weak, interrupt));
void CORE0_PIF_PMS_SIZE_IRQHandler() {
    Default_Handler();
}

void DMA_APBPERI_PMS_IRQHandler() __attribute__((weak, interrupt));
void DMA_APBPERI_PMS_IRQHandler() {
    Default_Handler();
}

void DMA_CH0_IRQHandler() __attribute__((weak, interrupt));
void DMA_CH0_IRQHandler() {
    Default_Handler();
}

void DMA_CH1_IRQHandler() __attribute__((weak, interrupt));
void DMA_CH1_IRQHandler() {
    Default_Handler();
}

void DMA_CH2_IRQHandler() __attribute__((weak, interrupt));
void DMA_CH2_IRQHandler() {
    Default_Handler();
}

void EFUSE_IRQHandler() __attribute__((weak, interrupt));
void EFUSE_IRQHandler() {
    Default_Handler();
}

void FROM_CPU_INTR0_IRQHandler() __attribute__((weak, interrupt));
void FROM_CPU_INTR0_IRQHandler() {
    Default_Handler();
}

void FROM_CPU_INTR1_IRQHandler() __attribute__((weak, interrupt));
void FROM_CPU_INTR1_IRQHandler() {
    Default_Handler();
}

void FROM_CPU_INTR2_IRQHandler() __attribute__((weak, interrupt));
void FROM_CPU_INTR2_IRQHandler() {
    Default_Handler();
}

void FROM_CPU_INTR3_IRQHandler() __attribute__((weak, interrupt));
void FROM_CPU_INTR3_IRQHandler() {
    Default_Handler();
}

void GPIO_IRQHandler() __attribute__((weak, interrupt));
void GPIO_IRQHandler() {
    Default_Handler();
}

void GPIO_NMI_IRQHandler() __attribute__((weak, interrupt));
void GPIO_NMI_IRQHandler() {
    Default_Handler();
}

void I2C_EXT0_IRQHandler() __attribute__((weak, interrupt));
void I2C_EXT0_IRQHandler() {
    Default_Handler();
}

void I2C_MASTER_IRQHandler() __attribute__((weak, interrupt));
void I2C_MASTER_IRQHandler() {
    Default_Handler();
}

void I2S0_IRQHandler() __attribute__((weak, interrupt));
void I2S0_IRQHandler() {
    Default_Handler();
}

void ICACHE_PRELOAD0_IRQHandler() __attribute__((weak, interrupt));
void ICACHE_PRELOAD0_IRQHandler() {
    Default_Handler();
}

void ICACHE_SYNC0_IRQHandler() __attribute__((weak, interrupt));
void ICACHE_SYNC0_IRQHandler() {
    Default_Handler();
}

void LEDC_IRQHandler() __attribute__((weak, interrupt));
void LEDC_IRQHandler() {
    Default_Handler();
}

void RMT_IRQHandler() __attribute__((weak, interrupt));
void RMT_IRQHandler() {
    Default_Handler();
}

void RSA_IRQHandler() __attribute__((weak, interrupt));
void RSA_IRQHandler() {
    Default_Handler();
}

void RTC_CORE_IRQHandler() __attribute__((weak, interrupt));
void RTC_CORE_IRQHandler() {
    Default_Handler();
}

void RWBLE_IRQHandler() __attribute__((weak, interrupt));
void RWBLE_IRQHandler() {
    Default_Handler();
}

void RWBLE_NMI_IRQHandler() __attribute__((weak, interrupt));
void RWBLE_NMI_IRQHandler() {
    Default_Handler();
}

void RWBT_IRQHandler() __attribute__((weak, interrupt));
void RWBT_IRQHandler() {
    Default_Handler();
}

void RWBT_NMI_IRQHandler() __attribute__((weak, interrupt));
void RWBT_NMI_IRQHandler() {
    Default_Handler();
}

void SHA_IRQHandler() __attribute__((weak, interrupt));
void SHA_IRQHandler() {
    Default_Handler();
}

void SLC0_IRQHandler() __attribute__((weak, interrupt));
void SLC0_IRQHandler() {
    Default_Handler();
}

void SLC1_IRQHandler() __attribute__((weak, interrupt));
void SLC1_IRQHandler() {
    Default_Handler();
}

void SPI1_IRQHandler() __attribute__((weak, interrupt));
void SPI1_IRQHandler() {
    Default_Handler();
}

void SPI2_IRQHandler() __attribute__((weak, interrupt));
void SPI2_IRQHandler() {
    Default_Handler();
}

void SPI_MEM_REJECT_CACHE_IRQHandler() __attribute__((weak, interrupt));
void SPI_MEM_REJECT_CACHE_IRQHandler() {
    Default_Handler();
}

void SYSTIMER_TARGET0_IRQHandler() __attribute__((weak, interrupt));
void SYSTIMER_TARGET0_IRQHandler() {
    Default_Handler();
}

void SYSTIMER_TARGET1_IRQHandler() __attribute__((weak, interrupt));
void SYSTIMER_TARGET1_IRQHandler() {
    Default_Handler();
}

void SYSTIMER_TARGET2_IRQHandler() __attribute__((weak, interrupt));
void SYSTIMER_TARGET2_IRQHandler() {
    Default_Handler();
}

void TG0_T0_LEVEL_IRQHandler() __attribute__((weak, interrupt));
void TG0_T0_LEVEL_IRQHandler() {
    Default_Handler();
}

void TG0_WDT_LEVEL_IRQHandler() __attribute__((weak, interrupt));
void TG0_WDT_LEVEL_IRQHandler() {
    Default_Handler();
}

void TG1_T0_LEVEL_IRQHandler() __attribute__((weak, interrupt));
void TG1_T0_LEVEL_IRQHandler() {
    Default_Handler();
}

void TG1_WDT_LEVEL_IRQHandler() __attribute__((weak, interrupt));
void TG1_WDT_LEVEL_IRQHandler() {
    Default_Handler();
}

void TIMER1_IRQHandler() __attribute__((weak, interrupt));
void TIMER1_IRQHandler() {
    Default_Handler();
}

void TIMER2_IRQHandler() __attribute__((weak, interrupt));
void TIMER2_IRQHandler() {
    Default_Handler();
}

void TWAI0_IRQHandler() __attribute__((weak, interrupt));
void TWAI0_IRQHandler() {
    Default_Handler();
}

void UART0_IRQHandler() __attribute__((weak, interrupt));
void UART0_IRQHandler() {
    Default_Handler();
}

void UART1_IRQHandler() __attribute__((weak, interrupt));
void UART1_IRQHandler() {
    Default_Handler();
}

void UHCI0_IRQHandler() __attribute__((weak, interrupt));
void UHCI0_IRQHandler() {
    Default_Handler();
}

void USB_DEVICE_IRQHandler() __attribute__((weak, interrupt));
void USB_DEVICE_IRQHandler() {
    Default_Handler();
}

void WIFI_BB_IRQHandler() __attribute__((weak, interrupt));
void WIFI_BB_IRQHandler() {
    Default_Handler();
}

void WIFI_MAC_IRQHandler() __attribute__((weak, interrupt));
void WIFI_MAC_IRQHandler() {
    Default_Handler();
}

void WIFI_MAC_NMI_IRQHandler() __attribute__((weak, interrupt));
void WIFI_MAC_NMI_IRQHandler() {
    Default_Handler();
}

void WIFI_PWR_IRQHandler() __attribute__((weak, interrupt));
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
