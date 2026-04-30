#pragma once

#include <array>
#include <cstdint>

namespace nordic {
namespace nrf52 {
namespace generated {
namespace runtime {
namespace devices {
namespace nrf52840 {
enum class ClockNodeId : std::uint16_t {
  none,
  clock_root,
};

struct ClockDependencyDescriptor {
  ClockNodeId node_id;
  ClockNodeId parent_id;
};
inline constexpr std::array<ClockDependencyDescriptor, 1> kClockDependencies = {{
  {ClockNodeId::clock_root, ClockNodeId::none},
}};
}
}
}
}
}
}
