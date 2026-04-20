#pragma once

#include <array>
#include <cstdint>

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1064 {
enum class ClockNodeId : std::uint16_t {
  none,
  clock_root,
  clock_node_ccm_ccgr0,
  clock_node_ccm_ccgr1,
  clock_node_ccm_ccgr2,
  clock_node_ccm_ccgr3,
  clock_node_ccm_ccgr5,
  clock_node_lpi2c_root,
  clock_node_lpspi_root,
  clock_node_lpuart_root,
  clock_node_osc24m,
  clock_node_pll3_sw_clk,
};

struct ClockDependencyDescriptor {
  ClockNodeId node_id;
  ClockNodeId parent_id;
};
inline constexpr std::array<ClockDependencyDescriptor, 11> kClockDependencies = {{
  {ClockNodeId::clock_node_ccm_ccgr0, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_ccm_ccgr1, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_ccm_ccgr2, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_ccm_ccgr3, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_ccm_ccgr5, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_lpi2c_root, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_lpspi_root, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_lpuart_root, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_osc24m, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_pll3_sw_clk, ClockNodeId::clock_root},
  {ClockNodeId::clock_root, ClockNodeId::none},
}};
}
}
}
}
}
}
