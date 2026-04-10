#pragma once

namespace nxp {
namespace imxrt1060 {
namespace mimxrt1062 {
struct PinFunctionDescriptor {
  const char* pin_name;
  const char* function;
  const char* peripheral;
  const char* signal;
  int af_number;
};
inline constexpr PinFunctionDescriptor kPinFunctions[] = {
  {"GPIO_AD_B0_00", "lpi2c1_scl", "LPI2C1", "SCL", 0},
  {"GPIO_AD_B0_00", "lpuart1_tx", "LPUART1", "TX", 2},
  {"GPIO_AD_B0_00", "gpio1_io00", "GPIO1", "IO00", 5},
  {"GPIO_EMC_00", "lpspi1_sck", "LPSPI1", "SCK", 2},
  {"GPIO_EMC_00", "gpio4_io00", "GPIO4", "IO00", 5},
  {"GPIO_AD_B0_01", "lpi2c1_sda", "LPI2C1", "SDA", 0},
  {"GPIO_AD_B0_01", "lpuart1_rx", "LPUART1", "RX", 2},
  {"GPIO_AD_B0_01", "gpio1_io01", "GPIO1", "IO01", 5},
  {"GPIO_EMC_01", "lpspi1_pcs0", "LPSPI1", "PCS0", 2},
  {"GPIO_EMC_01", "gpio4_io01", "GPIO4", "IO01", 5},
};
}
}
}
