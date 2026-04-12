#pragma once

#include "runtime_refs.hpp"
#include "clock_tree_lite.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
struct RccDescriptor {
  DeviceRefId device_id;
  PeripheralRefId peripheral_id;
  ClockGateId gate_id;
  ResetId reset_id;
};
inline constexpr RccDescriptor kRccMap[] = {
  {DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_GPIO1, ClockGateId::mimxrt1062_gate_gpio1, ResetId::none},
  {DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_GPIO4, ClockGateId::mimxrt1062_gate_gpio4, ResetId::none},
  {DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPI2C1, ClockGateId::mimxrt1062_gate_lpi2c1, ResetId::none},
  {DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPSPI1, ClockGateId::mimxrt1062_gate_lpspi1, ResetId::none},
  {DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPUART1, ClockGateId::mimxrt1062_gate_lpuart1, ResetId::none},
  {DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPUART3, ClockGateId::mimxrt1062_gate_lpuart3, ResetId::none},
};
}
}
}
