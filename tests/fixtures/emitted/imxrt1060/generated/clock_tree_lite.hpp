#pragma once

#include <array>

namespace nxp {
namespace imxrt1060 {
namespace generated {
struct ClockNodeDescriptor {
  const char* device;
  const char* node_id;
  const char* kind;
  const char* parent;
  const char* selector;
};
inline constexpr std::array<ClockNodeDescriptor, 11> kClockNodes = {{
  {"mimxrt1062", "clock-node:ccm-ccgr0", "ccm-domain", "clock-root", nullptr},
  {"mimxrt1062", "clock-node:ccm-ccgr1", "ccm-domain", "clock-root", nullptr},
  {"mimxrt1062", "clock-node:ccm-ccgr2", "ccm-domain", "clock-root", nullptr},
  {"mimxrt1062", "clock-node:ccm-ccgr3", "ccm-domain", "clock-root", nullptr},
  {"mimxrt1062", "clock-node:ccm-ccgr5", "ccm-domain", "clock-root", nullptr},
  {"mimxrt1062", "clock-node:lpi2c-root", "peripheral-root", "clock-root", "selector:lpi2c-root"},
  {"mimxrt1062", "clock-node:lpspi-root", "peripheral-root", "clock-root", "selector:lpspi-root"},
  {"mimxrt1062", "clock-node:lpuart-root", "peripheral-root", "clock-root", "selector:lpuart-root"},
  {"mimxrt1062", "clock-node:osc24m", "clock-source", "clock-root", nullptr},
  {"mimxrt1062", "clock-node:pll3-sw-clk", "pll-source", "clock-root", nullptr},
  {"mimxrt1062", "clock-root", "root", nullptr, nullptr},
}};

struct ClockSelectorDescriptor {
  const char* device;
  const char* selector_id;
  const char* parent_options;
  const char* register_target;
};
inline constexpr std::array<ClockSelectorDescriptor, 3> kClockSelectors = {{
  {"mimxrt1062", "selector:lpi2c-root", "clock-node:pll3-sw-clk,clock-node:osc24m", "CCM_CSCDR2.LPI2C_CLK_SEL"},
  {"mimxrt1062", "selector:lpspi-root", "clock-node:pll3-sw-clk,clock-node:osc24m", "CCM_CBCMR.LPSPI_CLK_SEL"},
  {"mimxrt1062", "selector:lpuart-root", "clock-node:pll3-sw-clk,clock-node:osc24m", "CCM_CSCDR1.UART_CLK_SEL"},
}};

struct ClockGateDescriptor {
  const char* device;
  const char* gate_id;
  const char* peripheral;
  const char* enable_signal;
  const char* parent_node;
};
inline constexpr std::array<ClockGateDescriptor, 6> kClockGates = {{
  {"mimxrt1062", "gate:gpio1", "GPIO1", "CCM_CCGR1.CG13", "clock-node:ccm-ccgr1"},
  {"mimxrt1062", "gate:gpio4", "GPIO4", "CCM_CCGR3.CG13", "clock-node:ccm-ccgr3"},
  {"mimxrt1062", "gate:lpi2c1", "LPI2C1", "CCM_CCGR2.CG2", "clock-node:lpi2c-root"},
  {"mimxrt1062", "gate:lpspi1", "LPSPI1", "CCM_CCGR1.CG0", "clock-node:lpspi-root"},
  {"mimxrt1062", "gate:lpuart1", "LPUART1", "CCM_CCGR5.CG12", "clock-node:lpuart-root"},
  {"mimxrt1062", "gate:lpuart3", "LPUART3", "CCM_CCGR0.CG6", "clock-node:ccm-ccgr0"},
}};

struct ResetDescriptor {
  const char* device;
  const char* reset_id;
  const char* peripheral;
  const char* reset_signal;
  const char* active_level;
};
inline constexpr std::array<ResetDescriptor, 0> kResets = {};

struct PeripheralClockBindingDescriptor {
  const char* device;
  const char* peripheral;
  const char* clock_gate_id;
  const char* reset_id;
  const char* selector_id;
};
inline constexpr std::array<PeripheralClockBindingDescriptor, 6> kPeripheralClockBindings = {{
  {"mimxrt1062", "GPIO1", "gate:gpio1", nullptr, nullptr},
  {"mimxrt1062", "GPIO4", "gate:gpio4", nullptr, nullptr},
  {"mimxrt1062", "LPI2C1", "gate:lpi2c1", nullptr, "selector:lpi2c-root"},
  {"mimxrt1062", "LPSPI1", "gate:lpspi1", nullptr, "selector:lpspi-root"},
  {"mimxrt1062", "LPUART1", "gate:lpuart1", nullptr, "selector:lpuart-root"},
  {"mimxrt1062", "LPUART3", "gate:lpuart3", nullptr, nullptr},
}};
}
}
}
