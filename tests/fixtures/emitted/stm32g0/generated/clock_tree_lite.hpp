#pragma once

#include <array>
#include "runtime_refs.hpp"
#include "runtime_semantics.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
enum class ClockNodeId : std::uint16_t {
  none,
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
  DeviceRefId device_id;
  ClockNodeId node_id;
  ClockNodeKindId kind_id;
  ClockNodeId parent_node_id;
  ClockSelectorId selector_id;
};
inline constexpr std::array<ClockNodeDescriptor, 7> kClockNodes = {{
  {DeviceRefId::stm32g071rb, ClockNodeId::stm32g071rb_clock_node_hsi16, ClockNodeKindId::clock_node_kind_internal_oscillator, ClockNodeId::stm32g071rb_clock_root, ClockSelectorId::none},
  {DeviceRefId::stm32g071rb, ClockNodeId::stm32g071rb_clock_node_lse, ClockNodeKindId::clock_node_kind_low_speed_source, ClockNodeId::stm32g071rb_clock_root, ClockSelectorId::none},
  {DeviceRefId::stm32g071rb, ClockNodeId::stm32g071rb_clock_node_rcc_ahbenr, ClockNodeKindId::clock_node_kind_ahb_domain, ClockNodeId::stm32g071rb_clock_root, ClockSelectorId::none},
  {DeviceRefId::stm32g071rb, ClockNodeId::stm32g071rb_clock_node_rcc_apbenr2, ClockNodeKindId::clock_node_kind_apb_domain, ClockNodeId::stm32g071rb_clock_root, ClockSelectorId::none},
  {DeviceRefId::stm32g071rb, ClockNodeId::stm32g071rb_clock_node_rcc_iopenr, ClockNodeKindId::clock_node_kind_gpio_domain, ClockNodeId::stm32g071rb_clock_root, ClockSelectorId::none},
  {DeviceRefId::stm32g071rb, ClockNodeId::stm32g071rb_clock_node_sysclk, ClockNodeKindId::clock_node_kind_system_source, ClockNodeId::stm32g071rb_clock_root, ClockSelectorId::none},
  {DeviceRefId::stm32g071rb, ClockNodeId::stm32g071rb_clock_root, ClockNodeKindId::clock_node_kind_root, ClockNodeId::none, ClockSelectorId::none},
}};

struct ClockSelectorDescriptor {
  DeviceRefId device_id;
  ClockSelectorId selector_id;
  std::uint16_t parent_option_offset;
  std::uint16_t parent_option_count;
  RegisterRefId register_id;
  RegisterFieldRefId register_field_id;
};
inline constexpr std::array<ClockSelectorDescriptor, 1> kClockSelectors = {{
  {DeviceRefId::stm32g071rb, ClockSelectorId::stm32g071rb_selector_usart1_kernel, 0u, 4u, RegisterRefId::none, RegisterFieldRefId::none},
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
  DeviceRefId device_id;
  ClockGateId gate_id;
  PeripheralRefId peripheral_id;
  ClockNodeId parent_node_id;
  RegisterRefId register_id;
  RegisterFieldRefId register_field_id;
};
inline constexpr std::array<ClockGateDescriptor, 5> kClockGates = {{
  {DeviceRefId::stm32g071rb, ClockGateId::stm32g071rb_gate_dma1, PeripheralRefId::stm32g071rb_DMA1, ClockNodeId::stm32g071rb_clock_node_rcc_ahbenr, RegisterRefId::stm32g071rb_register_rcc_ahbenr, RegisterFieldRefId::none},
  {DeviceRefId::stm32g071rb, ClockGateId::stm32g071rb_gate_dmamux1, PeripheralRefId::stm32g071rb_DMAMUX1, ClockNodeId::stm32g071rb_clock_node_rcc_ahbenr, RegisterRefId::stm32g071rb_register_rcc_ahbenr, RegisterFieldRefId::none},
  {DeviceRefId::stm32g071rb, ClockGateId::stm32g071rb_gate_gpioa, PeripheralRefId::stm32g071rb_GPIOA, ClockNodeId::stm32g071rb_clock_node_rcc_iopenr, RegisterRefId::stm32g071rb_register_rcc_iopenr, RegisterFieldRefId::none},
  {DeviceRefId::stm32g071rb, ClockGateId::stm32g071rb_gate_gpiob, PeripheralRefId::stm32g071rb_GPIOB, ClockNodeId::stm32g071rb_clock_node_rcc_iopenr, RegisterRefId::stm32g071rb_register_rcc_iopenr, RegisterFieldRefId::none},
  {DeviceRefId::stm32g071rb, ClockGateId::stm32g071rb_gate_usart1, PeripheralRefId::stm32g071rb_USART1, ClockNodeId::stm32g071rb_clock_node_rcc_apbenr2, RegisterRefId::stm32g071rb_register_rcc_apbenr2, RegisterFieldRefId::none},
}};

struct ResetDescriptor {
  DeviceRefId device_id;
  ResetId reset_id;
  PeripheralRefId peripheral_id;
  ActiveLevelId active_level_id;
  RegisterRefId register_id;
  RegisterFieldRefId register_field_id;
};
inline constexpr std::array<ResetDescriptor, 5> kResets = {{
  {DeviceRefId::stm32g071rb, ResetId::stm32g071rb_reset_dma1, PeripheralRefId::stm32g071rb_DMA1, ActiveLevelId::active_level_high, RegisterRefId::stm32g071rb_register_rcc_ahbrstr, RegisterFieldRefId::none},
  {DeviceRefId::stm32g071rb, ResetId::stm32g071rb_reset_dmamux1, PeripheralRefId::stm32g071rb_DMAMUX1, ActiveLevelId::active_level_high, RegisterRefId::stm32g071rb_register_rcc_ahbrstr, RegisterFieldRefId::none},
  {DeviceRefId::stm32g071rb, ResetId::stm32g071rb_reset_gpioa, PeripheralRefId::stm32g071rb_GPIOA, ActiveLevelId::active_level_high, RegisterRefId::stm32g071rb_register_rcc_ioprstr, RegisterFieldRefId::none},
  {DeviceRefId::stm32g071rb, ResetId::stm32g071rb_reset_gpiob, PeripheralRefId::stm32g071rb_GPIOB, ActiveLevelId::active_level_high, RegisterRefId::stm32g071rb_register_rcc_ioprstr, RegisterFieldRefId::none},
  {DeviceRefId::stm32g071rb, ResetId::stm32g071rb_reset_usart1, PeripheralRefId::stm32g071rb_USART1, ActiveLevelId::active_level_high, RegisterRefId::stm32g071rb_register_rcc_apbrstr2, RegisterFieldRefId::none},
}};

struct PeripheralClockBindingDescriptor {
  DeviceRefId device_id;
  PeripheralRefId peripheral_id;
  ClockGateId clock_gate_id;
  ResetId reset_id;
  ClockSelectorId selector_id;
};
inline constexpr std::array<PeripheralClockBindingDescriptor, 5> kPeripheralClockBindings = {{
  {DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_DMA1, ClockGateId::stm32g071rb_gate_dma1, ResetId::stm32g071rb_reset_dma1, ClockSelectorId::none},
  {DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_DMAMUX1, ClockGateId::stm32g071rb_gate_dmamux1, ResetId::stm32g071rb_reset_dmamux1, ClockSelectorId::none},
  {DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_GPIOA, ClockGateId::stm32g071rb_gate_gpioa, ResetId::stm32g071rb_reset_gpioa, ClockSelectorId::none},
  {DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_GPIOB, ClockGateId::stm32g071rb_gate_gpiob, ResetId::stm32g071rb_reset_gpiob, ClockSelectorId::none},
  {DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_USART1, ClockGateId::stm32g071rb_gate_usart1, ResetId::stm32g071rb_reset_usart1, ClockSelectorId::stm32g071rb_selector_usart1_kernel},
}};
}
}
}
