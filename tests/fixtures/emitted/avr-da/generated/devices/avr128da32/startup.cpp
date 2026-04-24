#include <cstdint>

#include "../../runtime/devices/avr128da32/startup.hpp"

// AVR startup contract:
//   * avr-libc's crt<chip>.o owns the reset vector (__vector_0) and the
//     .vectors section; this file supplies only the weak peripheral
//     handlers so unhandled interrupts trap cleanly.
//   * Each entry is also aliased to the IR's canonical
//     <NAME>_IRQHandler symbol so application code that references
//     either convention resolves without link errors.

#if defined(ALLOY_CODEGEN_HOST_SMOKE)
// Host smoke build: provide stubs for the symbols the rest of the
// runtime headers expect, but do not emit AVR-specific attributes.
extern "C" {
int alloy_codegen_host_smoke_entry();
int alloy_codegen_host_smoke_entry() {
    return 0;
}
}
#elif defined(__AVR__)
extern "C" {

// Default trap — avr-libc supplies __bad_interrupt but we keep a local
// symbol so the weak aliases below have a single target to point at.
[[noreturn]] void Default_Handler() {
    while (true) {}
}

void __vector_18() __attribute__((weak, alias("Default_Handler")));
void USART0_RXC_IRQHandler() __attribute__((weak, alias("__vector_18")));
void __vector_19() __attribute__((weak, alias("Default_Handler")));
void USART0_DRE_IRQHandler() __attribute__((weak, alias("__vector_19")));
void __vector_20() __attribute__((weak, alias("Default_Handler")));
void USART0_TXC_IRQHandler() __attribute__((weak, alias("__vector_20")));
void __vector_26() __attribute__((weak, alias("Default_Handler")));
void TWI0_TWIS_IRQHandler() __attribute__((weak, alias("__vector_26")));
void __vector_27() __attribute__((weak, alias("Default_Handler")));
void TWI0_TWIM_IRQHandler() __attribute__((weak, alias("__vector_27")));
void __vector_28() __attribute__((weak, alias("Default_Handler")));
void SPI0_INT_IRQHandler() __attribute__((weak, alias("__vector_28")));

}  // extern "C"
#else
// Non-AVR target build: nothing to emit — avr-libc's crt0 is
// AVR-specific and irrelevant when cross-compiling on the host.
#endif
