#pragma once

#include <array>
#include <cstdint>
#include "../../runtime_semantics.hpp"
#include "peripheral_instances.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
enum class DmaBindingId : std::uint16_t {
};

enum class DmaControllerId : std::uint16_t {
  none,
};

enum class DmaRequestLineId : std::uint16_t {
  none,
};

enum class DmaRouteId : std::uint16_t {
  none,
};

enum class DmaConflictGroupId : std::uint16_t {
  none,
};

struct DmaBindingDescriptor {
  DmaBindingId binding_id;
  PeripheralId peripheral_id;
  SignalId signal_id;
  DmaControllerId controller_id;
  DmaRequestLineId request_line_id;
  DmaRouteId route_id;
  DmaConflictGroupId conflict_group_id;
};
inline constexpr std::array<DmaBindingDescriptor, 0> kDmaBindings = {};
}
}
}
}
}
