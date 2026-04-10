#pragma once

#include <array>

namespace nxp {
namespace imxrt1060 {
namespace generated {
struct DmaDescriptor {
  const char* peripheral;
  const char* signal;
  const char* controller;
  const char* request_line;
};
inline constexpr std::array<DmaDescriptor, 0> kDmaMap = {};
}
}
}
