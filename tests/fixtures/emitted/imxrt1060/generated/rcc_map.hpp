#pragma once

#include "clock_tree_lite.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
struct RccDescriptor {
  const char* device;
  const char* peripheral;
  ClockGateId gate_id;
  ResetId reset_id;
};
inline constexpr RccDescriptor kRccMap[] = {
  {"mimxrt1062", "GPIO1", ClockGateId::mimxrt1062_gate_gpio1, ResetId::none},
  {"mimxrt1062", "GPIO4", ClockGateId::mimxrt1062_gate_gpio4, ResetId::none},
  {"mimxrt1062", "LPI2C1", ClockGateId::mimxrt1062_gate_lpi2c1, ResetId::none},
  {"mimxrt1062", "LPSPI1", ClockGateId::mimxrt1062_gate_lpspi1, ResetId::none},
  {"mimxrt1062", "LPUART1", ClockGateId::mimxrt1062_gate_lpuart1, ResetId::none},
  {"mimxrt1062", "LPUART3", ClockGateId::mimxrt1062_gate_lpuart3, ResetId::none},
};
}
}
}
