#pragma once

#include <array>
#include <cstdint>

namespace espressif {
namespace esp32s3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32s3 {
enum class ClockNodeId : std::uint16_t {
  none,
  clock_root,
  clock_node_system_perip_clk_en0,
  clock_node_system_perip_clk_en1,
};

struct ClockDependencyDescriptor {
  ClockNodeId node_id;
  ClockNodeId parent_id;
};
inline constexpr std::array<ClockDependencyDescriptor, 3> kClockDependencies = {{
  {ClockNodeId::clock_node_system_perip_clk_en0, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_system_perip_clk_en1, ClockNodeId::clock_root},
  {ClockNodeId::clock_root, ClockNodeId::none},
}};
}
}
}
}
}
}
