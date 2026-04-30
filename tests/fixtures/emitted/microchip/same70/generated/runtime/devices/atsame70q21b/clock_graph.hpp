#pragma once

#include <array>
#include <cstdint>

namespace microchip {
namespace same70 {
namespace generated {
namespace runtime {
namespace devices {
namespace atsame70q21b {
enum class ClockNodeId : std::uint16_t {
  none,
  clock_root,
  clock_node_pmc,
};

struct ClockDependencyDescriptor {
  ClockNodeId node_id;
  ClockNodeId parent_id;
};
inline constexpr std::array<ClockDependencyDescriptor, 2> kClockDependencies = {{
  {ClockNodeId::clock_node_pmc, ClockNodeId::clock_root},
  {ClockNodeId::clock_root, ClockNodeId::none},
}};
}
}
}
}
}
}
