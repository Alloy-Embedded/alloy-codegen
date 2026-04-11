#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
enum class DmaBindingId : std::uint16_t {
};

struct DmaBindingDescriptor {
  DmaBindingId binding_id;
  PeripheralId peripheral_id;
  const char* peripheral_name;
  const char* signal_name;
  const char* controller_name;
  const char* request_line;
  const char* route_id;
  const char* conflict_group;
};
inline constexpr std::array<DmaBindingDescriptor, 0> kDmaBindings = {};
}
}
}
}
}
