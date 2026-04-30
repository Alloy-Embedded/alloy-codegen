#pragma once

#include <array>
#include <cstdint>

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f405rg {
enum class ClockNodeId : std::uint16_t {
  none,
  clock_root,
  clock_node_rcc_ahb1enr,
  clock_node_rcc_ahb2enr,
  clock_node_rcc_apb1enr,
  clock_node_rcc_apb2enr,
};

struct ClockDependencyDescriptor {
  ClockNodeId node_id;
  ClockNodeId parent_id;
};
inline constexpr std::array<ClockDependencyDescriptor, 5> kClockDependencies = {{
  {ClockNodeId::clock_node_rcc_ahb1enr, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_rcc_ahb2enr, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_rcc_apb1enr, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_rcc_apb2enr, ClockNodeId::clock_root},
  {ClockNodeId::clock_root, ClockNodeId::none},
}};
}
}
}
}
}
}
