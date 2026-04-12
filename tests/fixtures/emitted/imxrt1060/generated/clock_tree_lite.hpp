#pragma once

#include <array>
#include "runtime_refs.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
enum class ClockNodeId : std::uint16_t {
  mimxrt1062_clock_node_ccm_ccgr0,
  mimxrt1062_clock_node_ccm_ccgr1,
  mimxrt1062_clock_node_ccm_ccgr2,
  mimxrt1062_clock_node_ccm_ccgr3,
  mimxrt1062_clock_node_ccm_ccgr5,
  mimxrt1062_clock_node_lpi2c_root,
  mimxrt1062_clock_node_lpspi_root,
  mimxrt1062_clock_node_lpuart_root,
  mimxrt1062_clock_node_osc24m,
  mimxrt1062_clock_node_pll3_sw_clk,
  mimxrt1062_clock_root,
};

enum class ClockSelectorId : std::uint16_t {
  none,
  mimxrt1062_selector_lpi2c_root,
  mimxrt1062_selector_lpspi_root,
  mimxrt1062_selector_lpuart_root,
};

enum class ClockGateId : std::uint16_t {
  none,
  mimxrt1062_gate_gpio1,
  mimxrt1062_gate_gpio4,
  mimxrt1062_gate_lpi2c1,
  mimxrt1062_gate_lpspi1,
  mimxrt1062_gate_lpuart1,
  mimxrt1062_gate_lpuart3,
};

enum class ResetId : std::uint16_t {
  none,
};

struct ClockNodeDescriptor {
  const char* device;
  ClockNodeId node_id;
  const char* node_name;
  const char* kind;
  int parent_index;
  int selector_index;
};
inline constexpr std::array<ClockNodeDescriptor, 11> kClockNodes = {{
  {"mimxrt1062", ClockNodeId::mimxrt1062_clock_node_ccm_ccgr0, "clock-node:ccm-ccgr0", "ccm-domain", 10, -1},
  {"mimxrt1062", ClockNodeId::mimxrt1062_clock_node_ccm_ccgr1, "clock-node:ccm-ccgr1", "ccm-domain", 10, -1},
  {"mimxrt1062", ClockNodeId::mimxrt1062_clock_node_ccm_ccgr2, "clock-node:ccm-ccgr2", "ccm-domain", 10, -1},
  {"mimxrt1062", ClockNodeId::mimxrt1062_clock_node_ccm_ccgr3, "clock-node:ccm-ccgr3", "ccm-domain", 10, -1},
  {"mimxrt1062", ClockNodeId::mimxrt1062_clock_node_ccm_ccgr5, "clock-node:ccm-ccgr5", "ccm-domain", 10, -1},
  {"mimxrt1062", ClockNodeId::mimxrt1062_clock_node_lpi2c_root, "clock-node:lpi2c-root", "peripheral-root", 10, 0},
  {"mimxrt1062", ClockNodeId::mimxrt1062_clock_node_lpspi_root, "clock-node:lpspi-root", "peripheral-root", 10, 1},
  {"mimxrt1062", ClockNodeId::mimxrt1062_clock_node_lpuart_root, "clock-node:lpuart-root", "peripheral-root", 10, 2},
  {"mimxrt1062", ClockNodeId::mimxrt1062_clock_node_osc24m, "clock-node:osc24m", "clock-source", 10, -1},
  {"mimxrt1062", ClockNodeId::mimxrt1062_clock_node_pll3_sw_clk, "clock-node:pll3-sw-clk", "pll-source", 10, -1},
  {"mimxrt1062", ClockNodeId::mimxrt1062_clock_root, "clock-root", "root", -1, -1},
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
inline constexpr std::array<ClockSelectorDescriptor, 3> kClockSelectors = {{
  {"mimxrt1062", ClockSelectorId::mimxrt1062_selector_lpi2c_root, "selector:lpi2c-root", 0u, 2u, "CCM_CSCDR2.LPI2C_CLK_SEL", "CCM", "CSCDR2", -1, RegisterRefId::none, RegisterFieldRefId::none},
  {"mimxrt1062", ClockSelectorId::mimxrt1062_selector_lpspi_root, "selector:lpspi-root", 2u, 2u, "CCM_CBCMR.LPSPI_CLK_SEL", "CCM", "CBCMR", -1, RegisterRefId::none, RegisterFieldRefId::none},
  {"mimxrt1062", ClockSelectorId::mimxrt1062_selector_lpuart_root, "selector:lpuart-root", 4u, 2u, "CCM_CSCDR1.UART_CLK_SEL", "CCM", "CSCDR1", -1, RegisterRefId::none, RegisterFieldRefId::none},
}};

struct ClockSelectorParentOption {
  ClockSelectorId selector_id;
  ClockNodeId parent_node_id;
};
inline constexpr std::array<ClockSelectorParentOption, 6> kClockSelectorParentOptions = {{
  {ClockSelectorId::mimxrt1062_selector_lpi2c_root, ClockNodeId::mimxrt1062_clock_node_pll3_sw_clk},
  {ClockSelectorId::mimxrt1062_selector_lpi2c_root, ClockNodeId::mimxrt1062_clock_node_osc24m},
  {ClockSelectorId::mimxrt1062_selector_lpspi_root, ClockNodeId::mimxrt1062_clock_node_pll3_sw_clk},
  {ClockSelectorId::mimxrt1062_selector_lpspi_root, ClockNodeId::mimxrt1062_clock_node_osc24m},
  {ClockSelectorId::mimxrt1062_selector_lpuart_root, ClockNodeId::mimxrt1062_clock_node_pll3_sw_clk},
  {ClockSelectorId::mimxrt1062_selector_lpuart_root, ClockNodeId::mimxrt1062_clock_node_osc24m},
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
inline constexpr std::array<ClockGateDescriptor, 6> kClockGates = {{
  {"mimxrt1062", ClockGateId::mimxrt1062_gate_gpio1, "gate:gpio1", "GPIO1", 1, "CCM_CCGR1.CG13", "CCM", "CCGR1", -1, RegisterRefId::none, RegisterFieldRefId::none},
  {"mimxrt1062", ClockGateId::mimxrt1062_gate_gpio4, "gate:gpio4", "GPIO4", 3, "CCM_CCGR3.CG13", "CCM", "CCGR3", -1, RegisterRefId::none, RegisterFieldRefId::none},
  {"mimxrt1062", ClockGateId::mimxrt1062_gate_lpi2c1, "gate:lpi2c1", "LPI2C1", 5, "CCM_CCGR2.CG2", "CCM", "CCGR2", -1, RegisterRefId::none, RegisterFieldRefId::none},
  {"mimxrt1062", ClockGateId::mimxrt1062_gate_lpspi1, "gate:lpspi1", "LPSPI1", 6, "CCM_CCGR1.CG0", "CCM", "CCGR1", -1, RegisterRefId::none, RegisterFieldRefId::none},
  {"mimxrt1062", ClockGateId::mimxrt1062_gate_lpuart1, "gate:lpuart1", "LPUART1", 7, "CCM_CCGR5.CG12", "CCM", "CCGR5", -1, RegisterRefId::none, RegisterFieldRefId::none},
  {"mimxrt1062", ClockGateId::mimxrt1062_gate_lpuart3, "gate:lpuart3", "LPUART3", 0, "CCM_CCGR0.CG6", "CCM", "CCGR0", -1, RegisterRefId::none, RegisterFieldRefId::none},
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
inline constexpr std::array<ResetDescriptor, 0> kResets = {};

struct PeripheralClockBindingDescriptor {
  const char* device;
  const char* peripheral;
  ClockGateId clock_gate_id;
  ResetId reset_id;
  ClockSelectorId selector_id;
};
inline constexpr std::array<PeripheralClockBindingDescriptor, 6> kPeripheralClockBindings = {{
  {"mimxrt1062", "GPIO1", ClockGateId::mimxrt1062_gate_gpio1, ResetId::none, ClockSelectorId::none},
  {"mimxrt1062", "GPIO4", ClockGateId::mimxrt1062_gate_gpio4, ResetId::none, ClockSelectorId::none},
  {"mimxrt1062", "LPI2C1", ClockGateId::mimxrt1062_gate_lpi2c1, ResetId::none, ClockSelectorId::mimxrt1062_selector_lpi2c_root},
  {"mimxrt1062", "LPSPI1", ClockGateId::mimxrt1062_gate_lpspi1, ResetId::none, ClockSelectorId::mimxrt1062_selector_lpspi_root},
  {"mimxrt1062", "LPUART1", ClockGateId::mimxrt1062_gate_lpuart1, ResetId::none, ClockSelectorId::mimxrt1062_selector_lpuart_root},
  {"mimxrt1062", "LPUART3", ClockGateId::mimxrt1062_gate_lpuart3, ResetId::none, ClockSelectorId::none},
}};
}
}
}
