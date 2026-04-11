#pragma once

#include <array>

namespace st {
namespace stm32g0 {
namespace generated {
struct RuntimeProfileDescriptor {
  const char* subsystem;
  const char* schema_id;
  const char* source_kind;
  const char* source_id;
};
inline constexpr std::array<RuntimeProfileDescriptor, 18> kRuntimeProfiles = {{
  {"dma", "alloy.dma.st-bdma-v1-0", "peripheral", "DMA1"},
  {"dma-router", "alloy.dma-router.st-dmamux-v1-0", "peripheral", "DMAMUX1"},
  {"gpio", "alloy.gpio.st-stm32g07x-gpio-v1-0", "peripheral", "GPIOA"},
  {"gpio", "alloy.gpio.st-stm32g07x-gpio-v1-0", "peripheral", "GPIOB"},
  {"rcc", "alloy.rcc.st-rcc-g0-v1-0", "peripheral", "RCC"},
  {"uart", "alloy.uart.st-usart-v3-1", "peripheral", "USART1"},
  {"set-bit", "alloy.clock.st-rcc-g0-v1-0", "route-operation", "operation:clock-enable:dma1"},
  {"set-bit", "alloy.clock.st-rcc-g0-v1-0", "route-operation", "operation:clock-enable:dmamux1"},
  {"set-bit", "alloy.clock.st-rcc-g0-v1-0", "route-operation", "operation:clock-enable:gpioa"},
  {"set-bit", "alloy.clock.st-rcc-g0-v1-0", "route-operation", "operation:clock-enable:gpiob"},
  {"set-bit", "alloy.clock.st-rcc-g0-v1-0", "route-operation", "operation:clock-enable:usart1"},
  {"clear-bit", "alloy.clock.st-rcc-g0-v1-0", "route-operation", "operation:reset-release:dma1"},
  {"clear-bit", "alloy.clock.st-rcc-g0-v1-0", "route-operation", "operation:reset-release:dmamux1"},
  {"clear-bit", "alloy.clock.st-rcc-g0-v1-0", "route-operation", "operation:reset-release:gpioa"},
  {"clear-bit", "alloy.clock.st-rcc-g0-v1-0", "route-operation", "operation:reset-release:gpiob"},
  {"clear-bit", "alloy.clock.st-rcc-g0-v1-0", "route-operation", "operation:reset-release:usart1"},
  {"write-selector", "alloy.pinmux.stm32-af-v1", "route-operation", "operation:route:pb6:usart1:tx"},
  {"write-selector", "alloy.pinmux.stm32-af-v1", "route-operation", "operation:route:pb7:usart1:rx"},
}};
}
}
}
