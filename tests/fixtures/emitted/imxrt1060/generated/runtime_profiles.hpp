#pragma once

#include <array>

namespace nxp {
namespace imxrt1060 {
namespace generated {
struct RuntimeProfileDescriptor {
  const char* subsystem;
  const char* schema_id;
  const char* source_kind;
  const char* source_id;
};
inline constexpr std::array<RuntimeProfileDescriptor, 22> kRuntimeProfiles = {{
  {"gpio", "alloy.gpio.nxp-imxrt-gpio-v1", "peripheral", "GPIO1"},
  {"gpio", "alloy.gpio.nxp-imxrt-gpio-v1", "peripheral", "GPIO4"},
  {"lpi2c1", "alloy.lpi2c1.nxp-lpi2c-v1", "peripheral", "LPI2C1"},
  {"spi", "alloy.spi.nxp-lpspi-v1", "peripheral", "LPSPI1"},
  {"uart", "alloy.uart.nxp-lpuart-v1", "peripheral", "LPUART1"},
  {"uart", "alloy.uart.nxp-lpuart-v1", "peripheral", "LPUART3"},
  {"set-bit", "alloy.clock.nxp-generic-clock-v1", "route-operation", "operation:clock-enable:gpio1"},
  {"set-bit", "alloy.clock.nxp-generic-clock-v1", "route-operation", "operation:clock-enable:gpio4"},
  {"set-bit", "alloy.clock.nxp-generic-clock-v1", "route-operation", "operation:clock-enable:lpi2c1"},
  {"set-bit", "alloy.clock.nxp-generic-clock-v1", "route-operation", "operation:clock-enable:lpspi1"},
  {"set-bit", "alloy.clock.nxp-generic-clock-v1", "route-operation", "operation:clock-enable:lpuart1"},
  {"set-bit", "alloy.clock.nxp-generic-clock-v1", "route-operation", "operation:clock-enable:lpuart3"},
  {"write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "route-operation", "operation:route:gpio-ad-b0-00:gpio1:io00"},
  {"write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "route-operation", "operation:route:gpio-ad-b0-00:lpi2c1:scl"},
  {"write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "route-operation", "operation:route:gpio-ad-b0-00:lpuart1:tx"},
  {"write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "route-operation", "operation:route:gpio-ad-b0-01:gpio1:io01"},
  {"write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "route-operation", "operation:route:gpio-ad-b0-01:lpi2c1:sda"},
  {"write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "route-operation", "operation:route:gpio-ad-b0-01:lpuart1:rx"},
  {"write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "route-operation", "operation:route:gpio-emc-00:gpio4:io00"},
  {"write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "route-operation", "operation:route:gpio-emc-00:lpspi1:sck"},
  {"write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "route-operation", "operation:route:gpio-emc-01:gpio4:io01"},
  {"write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "route-operation", "operation:route:gpio-emc-01:lpspi1:pcs0"},
}};
}
}
}
