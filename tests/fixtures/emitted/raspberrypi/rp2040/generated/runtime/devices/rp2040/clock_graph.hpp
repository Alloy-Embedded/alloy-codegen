#pragma once

#include <array>
#include <cstdint>

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
enum class ClockNodeId : std::uint16_t {
  none,
  clock_root,
  clock_node_clk_ref,
  clock_node_clk_sys,
  clock_node_pll_sys,
  clock_node_pll_usb,
  clock_node_resets_reset,
  clock_node_rosc,
  clock_node_xosc,
};

struct ClockDependencyDescriptor {
  ClockNodeId node_id;
  ClockNodeId parent_id;
};
inline constexpr std::array<ClockDependencyDescriptor, 8> kClockDependencies = {{
  {ClockNodeId::clock_node_clk_ref, ClockNodeId::clock_node_xosc},
  {ClockNodeId::clock_node_clk_sys, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_pll_sys, ClockNodeId::clock_node_xosc},
  {ClockNodeId::clock_node_pll_usb, ClockNodeId::clock_node_xosc},
  {ClockNodeId::clock_node_resets_reset, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_rosc, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_xosc, ClockNodeId::clock_root},
  {ClockNodeId::clock_root, ClockNodeId::none},
}};
}
}
}
}
}
}
