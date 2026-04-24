#include <cstdint>

#include "../../runtime/devices/esp32s3/startup.hpp"

// ESP32-S3 / Xtensa LX7 single-core-perspective startup.
//   * The ROM bootloader owns VECBASE and initial stack setup.
//   * This generated file provides BSS/data init, C++ ctor dispatch,
//     main() entry, and weak peripheral IRQ stubs.
//   * core-1 bring-up and inter-core primitives are intentionally
//     NOT modelled in this first-cut bootstrap.

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

void APB_ADC_IRQHandler() __attribute__((weak));
void APB_ADC_IRQHandler() {
    Default_Handler();
}

void ASSIST_DEBUG_IRQHandler() __attribute__((weak));
void ASSIST_DEBUG_IRQHandler() {
    Default_Handler();
}

void BACKUP_PMS_VIOLATE_IRQHandler() __attribute__((weak));
void BACKUP_PMS_VIOLATE_IRQHandler() {
    Default_Handler();
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

void CACHE_CORE0_ACS_IRQHandler() __attribute__((weak));
void CACHE_CORE0_ACS_IRQHandler() {
    Default_Handler();
}

void CACHE_IA_IRQHandler() __attribute__((weak));
void CACHE_IA_IRQHandler() {
    Default_Handler();
}

void CORE0_DRAM0_PMS_IRQHandler() __attribute__((weak));
void CORE0_DRAM0_PMS_IRQHandler() {
    Default_Handler();
}

void CORE0_IRAM0_PMS_IRQHandler() __attribute__((weak));
void CORE0_IRAM0_PMS_IRQHandler() {
    Default_Handler();
}

void CORE0_PIF_PMS_IRQHandler() __attribute__((weak));
void CORE0_PIF_PMS_IRQHandler() {
    Default_Handler();
}

void CORE0_PIF_PMS_SIZE_IRQHandler() __attribute__((weak));
void CORE0_PIF_PMS_SIZE_IRQHandler() {
    Default_Handler();
}

void DCACHE_PRELOAD0_IRQHandler() __attribute__((weak));
void DCACHE_PRELOAD0_IRQHandler() {
    Default_Handler();
}

void DCACHE_SYNC0_IRQHandler() __attribute__((weak));
void DCACHE_SYNC0_IRQHandler() {
    Default_Handler();
}

void DMA_APBPERI_PMS_IRQHandler() __attribute__((weak));
void DMA_APBPERI_PMS_IRQHandler() {
    Default_Handler();
}

void DMA_EXTMEM_REJECT_IRQHandler() __attribute__((weak));
void DMA_EXTMEM_REJECT_IRQHandler() {
    Default_Handler();
}

void DMA_IN_CH0_IRQHandler() __attribute__((weak));
void DMA_IN_CH0_IRQHandler() {
    Default_Handler();
}

void DMA_IN_CH1_IRQHandler() __attribute__((weak));
void DMA_IN_CH1_IRQHandler() {
    Default_Handler();
}

void DMA_IN_CH2_IRQHandler() __attribute__((weak));
void DMA_IN_CH2_IRQHandler() {
    Default_Handler();
}

void DMA_IN_CH3_IRQHandler() __attribute__((weak));
void DMA_IN_CH3_IRQHandler() {
    Default_Handler();
}

void DMA_IN_CH4_IRQHandler() __attribute__((weak));
void DMA_IN_CH4_IRQHandler() {
    Default_Handler();
}

void DMA_OUT_CH0_IRQHandler() __attribute__((weak));
void DMA_OUT_CH0_IRQHandler() {
    Default_Handler();
}

void DMA_OUT_CH1_IRQHandler() __attribute__((weak));
void DMA_OUT_CH1_IRQHandler() {
    Default_Handler();
}

void DMA_OUT_CH2_IRQHandler() __attribute__((weak));
void DMA_OUT_CH2_IRQHandler() {
    Default_Handler();
}

void DMA_OUT_CH3_IRQHandler() __attribute__((weak));
void DMA_OUT_CH3_IRQHandler() {
    Default_Handler();
}

void DMA_OUT_CH4_IRQHandler() __attribute__((weak));
void DMA_OUT_CH4_IRQHandler() {
    Default_Handler();
}

void EFUSE_IRQHandler() __attribute__((weak));
void EFUSE_IRQHandler() {
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

void GPIO_INTR_2_IRQHandler() __attribute__((weak));
void GPIO_INTR_2_IRQHandler() {
    Default_Handler();
}

void GPIO_IRQHandler() __attribute__((weak));
void GPIO_IRQHandler() {
    Default_Handler();
}

void GPIO_NMI_2_IRQHandler() __attribute__((weak));
void GPIO_NMI_2_IRQHandler() {
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

void I2C_MASTER_IRQHandler() __attribute__((weak));
void I2C_MASTER_IRQHandler() {
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

void ICACHE_PRELOAD0_IRQHandler() __attribute__((weak));
void ICACHE_PRELOAD0_IRQHandler() {
    Default_Handler();
}

void ICACHE_SYNC0_IRQHandler() __attribute__((weak));
void ICACHE_SYNC0_IRQHandler() {
    Default_Handler();
}

void LCD_CAM_IRQHandler() __attribute__((weak));
void LCD_CAM_IRQHandler() {
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

void PCNT_IRQHandler() __attribute__((weak));
void PCNT_IRQHandler() {
    Default_Handler();
}

void PERI_BACKUP_IRQHandler() __attribute__((weak));
void PERI_BACKUP_IRQHandler() {
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

void SHA_IRQHandler() __attribute__((weak));
void SHA_IRQHandler() {
    Default_Handler();
}

void SLC0_IRQHandler() __attribute__((weak));
void SLC0_IRQHandler() {
    Default_Handler();
}

void SLC1_IRQHandler() __attribute__((weak));
void SLC1_IRQHandler() {
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

void SPI_MEM_REJECT_CACHE_IRQHandler() __attribute__((weak));
void SPI_MEM_REJECT_CACHE_IRQHandler() {
    Default_Handler();
}

void SYSTIMER_TARGET0_IRQHandler() __attribute__((weak));
void SYSTIMER_TARGET0_IRQHandler() {
    Default_Handler();
}

void SYSTIMER_TARGET1_IRQHandler() __attribute__((weak));
void SYSTIMER_TARGET1_IRQHandler() {
    Default_Handler();
}

void SYSTIMER_TARGET2_IRQHandler() __attribute__((weak));
void SYSTIMER_TARGET2_IRQHandler() {
    Default_Handler();
}

void TG0_T0_LEVEL_IRQHandler() __attribute__((weak));
void TG0_T0_LEVEL_IRQHandler() {
    Default_Handler();
}

void TG0_T1_LEVEL_IRQHandler() __attribute__((weak));
void TG0_T1_LEVEL_IRQHandler() {
    Default_Handler();
}

void TG0_WDT_LEVEL_IRQHandler() __attribute__((weak));
void TG0_WDT_LEVEL_IRQHandler() {
    Default_Handler();
}

void TG1_T0_LEVEL_IRQHandler() __attribute__((weak));
void TG1_T0_LEVEL_IRQHandler() {
    Default_Handler();
}

void TG1_T1_LEVEL_IRQHandler() __attribute__((weak));
void TG1_T1_LEVEL_IRQHandler() {
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

void USB_DEVICE_IRQHandler() __attribute__((weak));
void USB_DEVICE_IRQHandler() {
    Default_Handler();
}

void USB_IRQHandler() __attribute__((weak));
void USB_IRQHandler() {
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

void WIFI_PWR_IRQHandler() __attribute__((weak));
void WIFI_PWR_IRQHandler() {
    Default_Handler();
}

// Reset_Handler runs after the ESP32-S3 ROM bootloader has
// transferred control to the application image.  VECBASE,
// stack, and cache have already been set up by ROM code.
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

// Informational vector table — not used by the ESP32-S3 ROM,
// which routes exceptions through VECBASE in ROM.  Kept for
// debugger symbol-resolution parity with ARM/RISC-V emitters.
#if defined(ALLOY_CODEGEN_HOST_SMOKE)
__attribute__((used))
#else
__attribute__((section(".xtensa_vectors_info"), used))
#endif
void (*const _vectors_info[])() = {
    Reset_Handler,
};
}
