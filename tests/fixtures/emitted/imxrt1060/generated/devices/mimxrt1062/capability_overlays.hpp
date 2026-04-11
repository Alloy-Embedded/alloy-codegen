#pragma once

#include <array>

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
struct CapabilityOverlayDescriptor {
  const char* capability_id;
  const char* scope;
  const char* peripheral_class;
  const char* name;
  const char* value;
  const char* ip_name;
  const char* ip_version;
  const char* peripheral;
  const char* package_name;
};
inline constexpr std::array<CapabilityOverlayDescriptor, 10> kCapabilityOverlays = {{
  {"capability-instance:gpio1:bga196:io00", "instance-overlay", "gpio", "available-signal", "io00", "gpio", "imxrt-gpio-v1", "GPIO1", "bga196"},
  {"capability-instance:gpio1:bga196:io01", "instance-overlay", "gpio", "available-signal", "io01", "gpio", "imxrt-gpio-v1", "GPIO1", "bga196"},
  {"capability-instance:gpio4:bga196:io00", "instance-overlay", "gpio", "available-signal", "io00", "gpio", "imxrt-gpio-v1", "GPIO4", "bga196"},
  {"capability-instance:gpio4:bga196:io01", "instance-overlay", "gpio", "available-signal", "io01", "gpio", "imxrt-gpio-v1", "GPIO4", "bga196"},
  {"capability-instance:lpi2c1:bga196:scl", "instance-overlay", "lpi2c1", "available-signal", "scl", "lpi2c1", "lpi2c-v1", "LPI2C1", "bga196"},
  {"capability-instance:lpi2c1:bga196:sda", "instance-overlay", "lpi2c1", "available-signal", "sda", "lpi2c1", "lpi2c-v1", "LPI2C1", "bga196"},
  {"capability-instance:lpspi1:bga196:cs", "instance-overlay", "spi", "available-signal", "cs", "lpspi", "lpspi-v1", "LPSPI1", "bga196"},
  {"capability-instance:lpspi1:bga196:sck", "instance-overlay", "spi", "available-signal", "sck", "lpspi", "lpspi-v1", "LPSPI1", "bga196"},
  {"capability-instance:lpuart1:bga196:rx", "instance-overlay", "uart", "available-signal", "rx", "lpuart", "lpuart-v1", "LPUART1", "bga196"},
  {"capability-instance:lpuart1:bga196:tx", "instance-overlay", "uart", "available-signal", "tx", "lpuart", "lpuart-v1", "LPUART1", "bga196"},
}};
}
}
}
}
}
