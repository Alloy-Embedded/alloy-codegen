#pragma once

#include <array>
#include <cstdint>

namespace st {
namespace stm32g0 {
namespace generated {
namespace devices {
namespace stm32g071rb {
struct PeripheralInstanceDescriptor {
  const char* name;
  const char* ip_name;
  const char* ip_version;
  int instance;
  std::uintptr_t base_address;
  const char* rcc_enable_signal;
  const char* rcc_reset_signal;
  const char* clock_gate_id;
  const char* reset_id;
  const char* selector_id;
  const char* interrupt_names;
  const char* capability_overlay_ids;
};
inline constexpr std::array<PeripheralInstanceDescriptor, 6> kPeripheralInstances = {{
  {"DMA1", "dma", "bdma_v1_0", 1, 0x40020000u, "RCC_AHBENR.DMA1EN", "RCC_AHBRSTR.DMA1RST", "gate:dma1", "reset:dma1", nullptr, "DMA1_Channel1,DMA1_Channel2_3", ""},
  {"DMAMUX1", "dmamux", "dmamux_v1_0", 1, 0x40020800u, "RCC_AHBENR.DMAMUX1EN", "RCC_AHBRSTR.DMAMUX1RST", "gate:dmamux1", "reset:dmamux1", nullptr, "", ""},
  {"GPIOA", "gpio", "STM32G07x_gpio_v1_0", 0, 0x50000000u, "RCC_IOPENR.GPIOAEN", "RCC_IOPRSTR.GPIOARST", "gate:gpioa", "reset:gpioa", nullptr, "", ""},
  {"GPIOB", "gpio", "STM32G07x_gpio_v1_0", 1, 0x50000400u, "RCC_IOPENR.GPIOBEN", "RCC_IOPRSTR.GPIOBRST", "gate:gpiob", "reset:gpiob", nullptr, "", ""},
  {"RCC", "rcc", "rcc_g0_v1_0", 0, 0x40021000u, nullptr, nullptr, nullptr, nullptr, nullptr, "RCC_CRS", ""},
  {"USART1", "usart", "usart_v3_1", 1, 0x40013800u, "RCC_APBENR2.USART1EN", "RCC_APBRSTR2.USART1RST", "gate:usart1", "reset:usart1", "selector:usart1-kernel", "USART1", "capability-instance:usart1:lqfp64:rx,capability-instance:usart1:lqfp64:tx"},
}};
}
}
}
}
}
