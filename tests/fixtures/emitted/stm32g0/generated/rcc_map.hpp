#pragma once

namespace st {
namespace stm32g0 {
namespace generated {
struct RccDescriptor {
  const char* peripheral;
  const char* enable_signal;
  const char* reset_signal;
};
inline constexpr RccDescriptor kRccMap[] = {
  {"DMA1", "RCC_AHBENR.DMA1EN", "RCC_AHBRSTR.DMA1RST"},
  {"DMAMUX1", "RCC_AHBENR.DMAMUX1EN", "RCC_AHBRSTR.DMAMUX1RST"},
  {"GPIOA", "RCC_IOPENR.GPIOAEN", "RCC_IOPRSTR.GPIOARST"},
  {"GPIOB", "RCC_IOPENR.GPIOBEN", "RCC_IOPRSTR.GPIOBRST"},
  {"USART1", "RCC_APBENR2.USART1EN", "RCC_APBRSTR2.USART1RST"},
};
}
}
}
