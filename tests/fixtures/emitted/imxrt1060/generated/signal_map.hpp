#pragma once

namespace nxp {
namespace imxrt1060 {
namespace generated {
struct SignalDescriptor {
  const char* peripheral;
  const char* signal;
  const char* pin_name;
  int af_number;
};
inline constexpr SignalDescriptor kSignalMap[] = {
  {"GPIO1", "IO00", "GPIO_AD_B0_00", 5},
  {"GPIO1", "IO01", "GPIO_AD_B0_01", 5},
  {"GPIO4", "IO00", "GPIO_EMC_00", 5},
  {"GPIO4", "IO01", "GPIO_EMC_01", 5},
  {"LPI2C1", "SCL", "GPIO_AD_B0_00", 0},
  {"LPI2C1", "SDA", "GPIO_AD_B0_01", 0},
  {"LPSPI1", "PCS0", "GPIO_EMC_01", 2},
  {"LPSPI1", "SCK", "GPIO_EMC_00", 2},
  {"LPUART1", "RX", "GPIO_AD_B0_01", 2},
  {"LPUART1", "TX", "GPIO_AD_B0_00", 2},
};
}
}
}
