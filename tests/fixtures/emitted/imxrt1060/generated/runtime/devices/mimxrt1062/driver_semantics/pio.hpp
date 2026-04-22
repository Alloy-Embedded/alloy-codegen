#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace runtime {
namespace devices {
namespace mimxrt1062 {
namespace driver_semantics {
template<PeripheralId Id>
struct PioSemanticTraits {
  static constexpr bool kPresent = false;
};

inline constexpr std::array<PeripheralId, 0> kPioSemanticPeripherals = {};
}
}
}
}
}
}
}
