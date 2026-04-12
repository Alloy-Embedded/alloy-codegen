#pragma once

#include <array>
#include "runtime_semantics.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
enum class DmaMapPeripheralId : std::uint16_t {
  none,
};

enum class DmaMapControllerId : std::uint16_t {
  none,
};

enum class DmaMapRequestLineId : std::uint16_t {
  none,
};

struct DmaDescriptor {
  DmaMapPeripheralId peripheral_id;
  SignalId signal_id;
  DmaMapControllerId controller_id;
  DmaMapRequestLineId request_line_id;
};
inline constexpr std::array<DmaDescriptor, 0> kDmaMap = {};
}
}
}
