#pragma once

#include <array>
#include <cstdint>

namespace espressif {
namespace esp32c3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32c3 {
enum class ClockNodeId : std::uint16_t {
  none,
  clock_root,
  clock_node_pcr_i2c0_conf_reg,
  clock_node_pcr_spi2_conf_reg,
  clock_node_pcr_uart0_conf0_reg,
  clock_node_pcr_uart1_conf0_reg,
};

struct ClockDependencyDescriptor {
  ClockNodeId node_id;
  ClockNodeId parent_id;
};
inline constexpr std::array<ClockDependencyDescriptor, 5> kClockDependencies = {{
  {ClockNodeId::clock_node_pcr_i2c0_conf_reg, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_pcr_spi2_conf_reg, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_pcr_uart0_conf0_reg, ClockNodeId::clock_root},
  {ClockNodeId::clock_node_pcr_uart1_conf0_reg, ClockNodeId::clock_root},
  {ClockNodeId::clock_root, ClockNodeId::none},
}};
}
}
}
}
}
}
