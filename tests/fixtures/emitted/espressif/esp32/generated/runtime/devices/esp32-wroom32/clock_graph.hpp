#pragma once

#include <array>
#include <cstdint>

namespace espressif {
namespace esp32 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32_wroom32 {
enum class ClockNodeId : std::uint16_t {
  none,
  clock_root,
  clock_node_dport_perip_clk_en,
};

struct ClockDependencyDescriptor {
  ClockNodeId node_id;
  ClockNodeId parent_id;
};
inline constexpr std::array<ClockDependencyDescriptor, 2> kClockDependencies = {{
  {ClockNodeId::clock_node_dport_perip_clk_en, ClockNodeId::clock_root},
  {ClockNodeId::clock_root, ClockNodeId::none},
}};
}
}
}
}
}
}
