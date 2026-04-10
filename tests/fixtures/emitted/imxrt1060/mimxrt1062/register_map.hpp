#pragma once

#include <cstdint>

namespace nxp {
namespace imxrt1060 {
namespace mimxrt1062 {
inline constexpr const char* kDevice = "mimxrt1062";
struct PeripheralBase {
  const char* name;
  std::uintptr_t address;
};
inline constexpr PeripheralBase kPeripheralBases[] = {
  {"GPIO1", 0x401B8000u},
  {"GPIO4", 0x401C4000u},
  {"LPI2C1", 0x403F0000u},
  {"LPSPI1", 0x40394000u},
  {"LPUART1", 0x40184000u},
  {"LPUART3", 0x4018C000u},
};
}
}
}
