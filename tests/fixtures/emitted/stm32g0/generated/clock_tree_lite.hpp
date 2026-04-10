#pragma once

namespace st {
namespace stm32g0 {
namespace generated {
struct ClockNodeDescriptor {
  const char* device;
  const char* node_id;
  const char* kind;
  const char* parent;
  const char* selector;
};
inline constexpr ClockNodeDescriptor kClockNodes[] = {
  {"stm32g071rb", "clock-node:rcc-ahbenr", "ahb-domain", "clock-root", nullptr},
  {"stm32g071rb", "clock-node:rcc-apbenr2", "apb-domain", "clock-root", nullptr},
  {"stm32g071rb", "clock-node:rcc-iopenr", "gpio-domain", "clock-root", nullptr},
  {"stm32g071rb", "clock-root", "root", nullptr, nullptr},
};

struct ClockSelectorDescriptor {
  const char* device;
  const char* selector_id;
  const char* parent_options;
  const char* register_target;
};
inline constexpr ClockSelectorDescriptor kClockSelectors[] = {
};

struct ClockGateDescriptor {
  const char* device;
  const char* gate_id;
  const char* peripheral;
  const char* enable_signal;
  const char* parent_node;
};
inline constexpr ClockGateDescriptor kClockGates[] = {
  {"stm32g071rb", "gate:dma1", "DMA1", "RCC_AHBENR.DMA1EN", "clock-node:rcc-ahbenr"},
  {"stm32g071rb", "gate:dmamux1", "DMAMUX1", "RCC_AHBENR.DMAMUX1EN", "clock-node:rcc-ahbenr"},
  {"stm32g071rb", "gate:gpioa", "GPIOA", "RCC_IOPENR.GPIOAEN", "clock-node:rcc-iopenr"},
  {"stm32g071rb", "gate:gpiob", "GPIOB", "RCC_IOPENR.GPIOBEN", "clock-node:rcc-iopenr"},
  {"stm32g071rb", "gate:usart1", "USART1", "RCC_APBENR2.USART1EN", "clock-node:rcc-apbenr2"},
};

struct ResetDescriptor {
  const char* device;
  const char* reset_id;
  const char* peripheral;
  const char* reset_signal;
  const char* active_level;
};
inline constexpr ResetDescriptor kResets[] = {
  {"stm32g071rb", "reset:dma1", "DMA1", "RCC_AHBRSTR.DMA1RST", "high"},
  {"stm32g071rb", "reset:dmamux1", "DMAMUX1", "RCC_AHBRSTR.DMAMUX1RST", "high"},
  {"stm32g071rb", "reset:gpioa", "GPIOA", "RCC_IOPRSTR.GPIOARST", "high"},
  {"stm32g071rb", "reset:gpiob", "GPIOB", "RCC_IOPRSTR.GPIOBRST", "high"},
  {"stm32g071rb", "reset:usart1", "USART1", "RCC_APBRSTR2.USART1RST", "high"},
};

struct PeripheralClockBindingDescriptor {
  const char* device;
  const char* peripheral;
  const char* clock_gate_id;
  const char* reset_id;
  const char* selector_id;
};
inline constexpr PeripheralClockBindingDescriptor kPeripheralClockBindings[] = {
  {"stm32g071rb", "DMA1", "gate:dma1", "reset:dma1", nullptr},
  {"stm32g071rb", "DMAMUX1", "gate:dmamux1", "reset:dmamux1", nullptr},
  {"stm32g071rb", "GPIOA", "gate:gpioa", "reset:gpioa", nullptr},
  {"stm32g071rb", "GPIOB", "gate:gpiob", "reset:gpiob", nullptr},
  {"stm32g071rb", "USART1", "gate:usart1", "reset:usart1", nullptr},
};
}
}
}
