#pragma once

#include <array>
#include <cstdint>

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g0b1re {
enum class ClockNodeId : std::uint16_t {
  none,
  clock_root,
  clock_node_hsi16,
  clock_node_lse,
  clock_node_rcc_ahbenr,
  clock_node_rcc_apbenr1,
  clock_node_rcc_apbenr2,
  clock_node_rcc_iopenr,
  clock_node_sysclk,
};

struct ClockDependencyDescriptor {
  ClockNodeId node_id;
  ClockNodeId parent_id;
};
inline constexpr std::array<ClockDependencyDescriptor, 8> kClockDependencies = {{
  {ClockNodeId::clock_node_hsi16, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_lse, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_rcc_ahbenr, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_rcc_apbenr1, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_rcc_apbenr2, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_rcc_iopenr, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_sysclk, ClockNodeId::clock_root},
  {ClockNodeId::clock_root, ClockNodeId::none},
}};
}
}
}
}
}
}
