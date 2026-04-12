#pragma once

#include <array>
#include "runtime_refs.hpp"
#include "runtime_semantics.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
enum class ClockNodeId : std::uint16_t {
  none,
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
  DeviceRefId device_id;
  ClockNodeId node_id;
  ClockNodeKindId kind_id;
  ClockNodeId parent_node_id;
  ClockSelectorId selector_id;
};
inline constexpr std::array<ClockNodeDescriptor, 11> kClockNodes = {{
  {DeviceRefId::mimxrt1062, ClockNodeId::mimxrt1062_clock_node_ccm_ccgr0, ClockNodeKindId::clock_node_kind_ccm_domain, ClockNodeId::mimxrt1062_clock_root, ClockSelectorId::none},
  {DeviceRefId::mimxrt1062, ClockNodeId::mimxrt1062_clock_node_ccm_ccgr1, ClockNodeKindId::clock_node_kind_ccm_domain, ClockNodeId::mimxrt1062_clock_root, ClockSelectorId::none},
  {DeviceRefId::mimxrt1062, ClockNodeId::mimxrt1062_clock_node_ccm_ccgr2, ClockNodeKindId::clock_node_kind_ccm_domain, ClockNodeId::mimxrt1062_clock_root, ClockSelectorId::none},
  {DeviceRefId::mimxrt1062, ClockNodeId::mimxrt1062_clock_node_ccm_ccgr3, ClockNodeKindId::clock_node_kind_ccm_domain, ClockNodeId::mimxrt1062_clock_root, ClockSelectorId::none},
  {DeviceRefId::mimxrt1062, ClockNodeId::mimxrt1062_clock_node_ccm_ccgr5, ClockNodeKindId::clock_node_kind_ccm_domain, ClockNodeId::mimxrt1062_clock_root, ClockSelectorId::none},
  {DeviceRefId::mimxrt1062, ClockNodeId::mimxrt1062_clock_node_lpi2c_root, ClockNodeKindId::clock_node_kind_peripheral_root, ClockNodeId::mimxrt1062_clock_root, ClockSelectorId::mimxrt1062_selector_lpi2c_root},
  {DeviceRefId::mimxrt1062, ClockNodeId::mimxrt1062_clock_node_lpspi_root, ClockNodeKindId::clock_node_kind_peripheral_root, ClockNodeId::mimxrt1062_clock_root, ClockSelectorId::mimxrt1062_selector_lpspi_root},
  {DeviceRefId::mimxrt1062, ClockNodeId::mimxrt1062_clock_node_lpuart_root, ClockNodeKindId::clock_node_kind_peripheral_root, ClockNodeId::mimxrt1062_clock_root, ClockSelectorId::mimxrt1062_selector_lpuart_root},
  {DeviceRefId::mimxrt1062, ClockNodeId::mimxrt1062_clock_node_osc24m, ClockNodeKindId::clock_node_kind_clock_source, ClockNodeId::mimxrt1062_clock_root, ClockSelectorId::none},
  {DeviceRefId::mimxrt1062, ClockNodeId::mimxrt1062_clock_node_pll3_sw_clk, ClockNodeKindId::clock_node_kind_pll_source, ClockNodeId::mimxrt1062_clock_root, ClockSelectorId::none},
  {DeviceRefId::mimxrt1062, ClockNodeId::mimxrt1062_clock_root, ClockNodeKindId::clock_node_kind_root, ClockNodeId::none, ClockSelectorId::none},
}};

struct ClockSelectorDescriptor {
  DeviceRefId device_id;
  ClockSelectorId selector_id;
  std::uint16_t parent_option_offset;
  std::uint16_t parent_option_count;
  RegisterRefId register_id;
  RegisterFieldRefId register_field_id;
};
inline constexpr std::array<ClockSelectorDescriptor, 3> kClockSelectors = {{
  {DeviceRefId::mimxrt1062, ClockSelectorId::mimxrt1062_selector_lpi2c_root, 0u, 2u, RegisterRefId::mimxrt1062_register_ccm_cscdr2, RegisterFieldRefId::mimxrt1062_field_ccm_cscdr2_lpi2c_clk_sel},
  {DeviceRefId::mimxrt1062, ClockSelectorId::mimxrt1062_selector_lpspi_root, 2u, 2u, RegisterRefId::mimxrt1062_register_ccm_cbcmr, RegisterFieldRefId::mimxrt1062_field_ccm_cbcmr_lpspi_clk_sel},
  {DeviceRefId::mimxrt1062, ClockSelectorId::mimxrt1062_selector_lpuart_root, 4u, 2u, RegisterRefId::mimxrt1062_register_ccm_cscdr1, RegisterFieldRefId::mimxrt1062_field_ccm_cscdr1_uart_clk_sel},
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
  DeviceRefId device_id;
  ClockGateId gate_id;
  PeripheralRefId peripheral_id;
  ClockNodeId parent_node_id;
  RegisterRefId register_id;
  RegisterFieldRefId register_field_id;
};
inline constexpr std::array<ClockGateDescriptor, 6> kClockGates = {{
  {DeviceRefId::mimxrt1062, ClockGateId::mimxrt1062_gate_gpio1, PeripheralRefId::mimxrt1062_GPIO1, ClockNodeId::mimxrt1062_clock_node_ccm_ccgr1, RegisterRefId::mimxrt1062_register_ccm_ccgr1, RegisterFieldRefId::mimxrt1062_field_ccm_ccgr1_cg13},
  {DeviceRefId::mimxrt1062, ClockGateId::mimxrt1062_gate_gpio4, PeripheralRefId::mimxrt1062_GPIO4, ClockNodeId::mimxrt1062_clock_node_ccm_ccgr3, RegisterRefId::mimxrt1062_register_ccm_ccgr3, RegisterFieldRefId::mimxrt1062_field_ccm_ccgr3_cg13},
  {DeviceRefId::mimxrt1062, ClockGateId::mimxrt1062_gate_lpi2c1, PeripheralRefId::mimxrt1062_LPI2C1, ClockNodeId::mimxrt1062_clock_node_lpi2c_root, RegisterRefId::mimxrt1062_register_ccm_ccgr2, RegisterFieldRefId::mimxrt1062_field_ccm_ccgr2_cg2},
  {DeviceRefId::mimxrt1062, ClockGateId::mimxrt1062_gate_lpspi1, PeripheralRefId::mimxrt1062_LPSPI1, ClockNodeId::mimxrt1062_clock_node_lpspi_root, RegisterRefId::mimxrt1062_register_ccm_ccgr1, RegisterFieldRefId::mimxrt1062_field_ccm_ccgr1_cg0},
  {DeviceRefId::mimxrt1062, ClockGateId::mimxrt1062_gate_lpuart1, PeripheralRefId::mimxrt1062_LPUART1, ClockNodeId::mimxrt1062_clock_node_lpuart_root, RegisterRefId::mimxrt1062_register_ccm_ccgr5, RegisterFieldRefId::mimxrt1062_field_ccm_ccgr5_cg12},
  {DeviceRefId::mimxrt1062, ClockGateId::mimxrt1062_gate_lpuart3, PeripheralRefId::mimxrt1062_LPUART3, ClockNodeId::mimxrt1062_clock_node_ccm_ccgr0, RegisterRefId::mimxrt1062_register_ccm_ccgr0, RegisterFieldRefId::mimxrt1062_field_ccm_ccgr0_cg6},
}};

struct ResetDescriptor {
  DeviceRefId device_id;
  ResetId reset_id;
  PeripheralRefId peripheral_id;
  ActiveLevelId active_level_id;
  RegisterRefId register_id;
  RegisterFieldRefId register_field_id;
};
inline constexpr std::array<ResetDescriptor, 0> kResets = {};

struct PeripheralClockBindingDescriptor {
  DeviceRefId device_id;
  PeripheralRefId peripheral_id;
  ClockGateId clock_gate_id;
  ResetId reset_id;
  ClockSelectorId selector_id;
};
inline constexpr std::array<PeripheralClockBindingDescriptor, 6> kPeripheralClockBindings = {{
  {DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_GPIO1, ClockGateId::mimxrt1062_gate_gpio1, ResetId::none, ClockSelectorId::none},
  {DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_GPIO4, ClockGateId::mimxrt1062_gate_gpio4, ResetId::none, ClockSelectorId::none},
  {DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPI2C1, ClockGateId::mimxrt1062_gate_lpi2c1, ResetId::none, ClockSelectorId::mimxrt1062_selector_lpi2c_root},
  {DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPSPI1, ClockGateId::mimxrt1062_gate_lpspi1, ResetId::none, ClockSelectorId::mimxrt1062_selector_lpspi_root},
  {DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPUART1, ClockGateId::mimxrt1062_gate_lpuart1, ResetId::none, ClockSelectorId::mimxrt1062_selector_lpuart_root},
  {DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPUART3, ClockGateId::mimxrt1062_gate_lpuart3, ResetId::none, ClockSelectorId::none},
}};
}
}
}
