#pragma once

#include <array>
#include "runtime_refs.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
enum class ClockNodeId : std::uint16_t {
  stm32g071rb_clock_node_hsi16,
  stm32g071rb_clock_node_lse,
  stm32g071rb_clock_node_rcc_ahbenr,
  stm32g071rb_clock_node_rcc_apbenr2,
  stm32g071rb_clock_node_rcc_iopenr,
  stm32g071rb_clock_node_sysclk,
  stm32g071rb_clock_root,
};

enum class ClockSelectorId : std::uint16_t {
  none,
  stm32g071rb_selector_usart1_kernel,
};

enum class ClockGateId : std::uint16_t {
  none,
  stm32g071rb_gate_dma1,
  stm32g071rb_gate_dmamux1,
  stm32g071rb_gate_gpioa,
  stm32g071rb_gate_gpiob,
  stm32g071rb_gate_usart1,
};

enum class ResetId : std::uint16_t {
  none,
  stm32g071rb_reset_dma1,
  stm32g071rb_reset_dmamux1,
  stm32g071rb_reset_gpioa,
  stm32g071rb_reset_gpiob,
  stm32g071rb_reset_usart1,
};

struct ClockNodeDescriptor {
  const char* device;
  ClockNodeId node_id;
  const char* node_name;
  const char* kind;
  int parent_index;
  int selector_index;
};
inline constexpr std::array<ClockNodeDescriptor, 7> kClockNodes = {{
  {"stm32g071rb", ClockNodeId::stm32g071rb_clock_node_hsi16, "clock-node:hsi16", "internal-oscillator", 6, -1},
  {"stm32g071rb", ClockNodeId::stm32g071rb_clock_node_lse, "clock-node:lse", "low-speed-source", 6, -1},
  {"stm32g071rb", ClockNodeId::stm32g071rb_clock_node_rcc_ahbenr, "clock-node:rcc-ahbenr", "ahb-domain", 6, -1},
  {"stm32g071rb", ClockNodeId::stm32g071rb_clock_node_rcc_apbenr2, "clock-node:rcc-apbenr2", "apb-domain", 6, -1},
  {"stm32g071rb", ClockNodeId::stm32g071rb_clock_node_rcc_iopenr, "clock-node:rcc-iopenr", "gpio-domain", 6, -1},
  {"stm32g071rb", ClockNodeId::stm32g071rb_clock_node_sysclk, "clock-node:sysclk", "system-source", 6, -1},
  {"stm32g071rb", ClockNodeId::stm32g071rb_clock_root, "clock-root", "root", -1, -1},
}};

struct ClockSelectorDescriptor {
  const char* device;
  ClockSelectorId selector_id;
  const char* selector_name;
  std::uint16_t parent_option_offset;
  std::uint16_t parent_option_count;
  const char* register_target;
  const char* register_peripheral;
  const char* register_name;
  int register_offset;
  RegisterRefId register_id;
  RegisterFieldRefId register_field_id;
};
inline constexpr std::array<ClockSelectorDescriptor, 1> kClockSelectors = {{
  {"stm32g071rb", ClockSelectorId::stm32g071rb_selector_usart1_kernel, "selector:usart1-kernel", 0u, 4u, "RCC_CCIPR.USART1SEL", "RCC", "CCIPR", -1, RegisterRefId::none, RegisterFieldRefId::none},
}};

struct ClockSelectorParentOption {
  ClockSelectorId selector_id;
  ClockNodeId parent_node_id;
};
inline constexpr std::array<ClockSelectorParentOption, 4> kClockSelectorParentOptions = {{
  {ClockSelectorId::stm32g071rb_selector_usart1_kernel, ClockNodeId::stm32g071rb_clock_node_rcc_apbenr2},
  {ClockSelectorId::stm32g071rb_selector_usart1_kernel, ClockNodeId::stm32g071rb_clock_node_sysclk},
  {ClockSelectorId::stm32g071rb_selector_usart1_kernel, ClockNodeId::stm32g071rb_clock_node_hsi16},
  {ClockSelectorId::stm32g071rb_selector_usart1_kernel, ClockNodeId::stm32g071rb_clock_node_lse},
}};

struct ClockGateDescriptor {
  const char* device;
  ClockGateId gate_id;
  const char* gate_name;
  const char* peripheral;
  int parent_node_index;
  const char* enable_signal;
  const char* register_peripheral;
  const char* register_name;
  int register_offset;
  RegisterRefId register_id;
  RegisterFieldRefId register_field_id;
};
inline constexpr std::array<ClockGateDescriptor, 5> kClockGates = {{
  {"stm32g071rb", ClockGateId::stm32g071rb_gate_dma1, "gate:dma1", "DMA1", 2, "RCC_AHBENR.DMA1EN", "RCC", "AHBENR", 56, RegisterRefId::stm32g071rb_register_rcc_ahbenr, RegisterFieldRefId::none},
  {"stm32g071rb", ClockGateId::stm32g071rb_gate_dmamux1, "gate:dmamux1", "DMAMUX1", 2, "RCC_AHBENR.DMAMUX1EN", "RCC", "AHBENR", 56, RegisterRefId::stm32g071rb_register_rcc_ahbenr, RegisterFieldRefId::none},
  {"stm32g071rb", ClockGateId::stm32g071rb_gate_gpioa, "gate:gpioa", "GPIOA", 4, "RCC_IOPENR.GPIOAEN", "RCC", "IOPENR", 52, RegisterRefId::stm32g071rb_register_rcc_iopenr, RegisterFieldRefId::none},
  {"stm32g071rb", ClockGateId::stm32g071rb_gate_gpiob, "gate:gpiob", "GPIOB", 4, "RCC_IOPENR.GPIOBEN", "RCC", "IOPENR", 52, RegisterRefId::stm32g071rb_register_rcc_iopenr, RegisterFieldRefId::none},
  {"stm32g071rb", ClockGateId::stm32g071rb_gate_usart1, "gate:usart1", "USART1", 3, "RCC_APBENR2.USART1EN", "RCC", "APBENR2", 64, RegisterRefId::stm32g071rb_register_rcc_apbenr2, RegisterFieldRefId::none},
}};

struct ResetDescriptor {
  const char* device;
  ResetId reset_id;
  const char* reset_name;
  const char* peripheral;
  const char* reset_signal;
  const char* active_level;
  const char* register_peripheral;
  const char* register_name;
  int register_offset;
  RegisterRefId register_id;
  RegisterFieldRefId register_field_id;
};
inline constexpr std::array<ResetDescriptor, 5> kResets = {{
  {"stm32g071rb", ResetId::stm32g071rb_reset_dma1, "reset:dma1", "DMA1", "RCC_AHBRSTR.DMA1RST", "high", "RCC", "AHBRSTR", 40, RegisterRefId::stm32g071rb_register_rcc_ahbrstr, RegisterFieldRefId::none},
  {"stm32g071rb", ResetId::stm32g071rb_reset_dmamux1, "reset:dmamux1", "DMAMUX1", "RCC_AHBRSTR.DMAMUX1RST", "high", "RCC", "AHBRSTR", 40, RegisterRefId::stm32g071rb_register_rcc_ahbrstr, RegisterFieldRefId::none},
  {"stm32g071rb", ResetId::stm32g071rb_reset_gpioa, "reset:gpioa", "GPIOA", "RCC_IOPRSTR.GPIOARST", "high", "RCC", "IOPRSTR", 36, RegisterRefId::stm32g071rb_register_rcc_ioprstr, RegisterFieldRefId::none},
  {"stm32g071rb", ResetId::stm32g071rb_reset_gpiob, "reset:gpiob", "GPIOB", "RCC_IOPRSTR.GPIOBRST", "high", "RCC", "IOPRSTR", 36, RegisterRefId::stm32g071rb_register_rcc_ioprstr, RegisterFieldRefId::none},
  {"stm32g071rb", ResetId::stm32g071rb_reset_usart1, "reset:usart1", "USART1", "RCC_APBRSTR2.USART1RST", "high", "RCC", "APBRSTR2", 48, RegisterRefId::stm32g071rb_register_rcc_apbrstr2, RegisterFieldRefId::none},
}};

struct PeripheralClockBindingDescriptor {
  const char* device;
  const char* peripheral;
  ClockGateId clock_gate_id;
  ResetId reset_id;
  ClockSelectorId selector_id;
};
inline constexpr std::array<PeripheralClockBindingDescriptor, 5> kPeripheralClockBindings = {{
  {"stm32g071rb", "DMA1", ClockGateId::stm32g071rb_gate_dma1, ResetId::stm32g071rb_reset_dma1, ClockSelectorId::none},
  {"stm32g071rb", "DMAMUX1", ClockGateId::stm32g071rb_gate_dmamux1, ResetId::stm32g071rb_reset_dmamux1, ClockSelectorId::none},
  {"stm32g071rb", "GPIOA", ClockGateId::stm32g071rb_gate_gpioa, ResetId::stm32g071rb_reset_gpioa, ClockSelectorId::none},
  {"stm32g071rb", "GPIOB", ClockGateId::stm32g071rb_gate_gpiob, ResetId::stm32g071rb_reset_gpiob, ClockSelectorId::none},
  {"stm32g071rb", "USART1", ClockGateId::stm32g071rb_gate_usart1, ResetId::stm32g071rb_reset_usart1, ClockSelectorId::stm32g071rb_selector_usart1_kernel},
}};
}
}
}
