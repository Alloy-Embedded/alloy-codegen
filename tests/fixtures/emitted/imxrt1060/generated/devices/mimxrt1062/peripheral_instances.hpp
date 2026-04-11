#pragma once

#include <array>
#include <cstdint>

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
enum class PeripheralId : std::uint16_t {
  GPIO1,
  GPIO4,
  LPI2C1,
  LPSPI1,
  LPUART1,
  LPUART3,
};

struct PeripheralInstanceDescriptor {
  PeripheralId peripheral_id;
  const char* name;
  const char* ip_name;
  const char* ip_version;
  const char* backend_schema_id;
  int instance;
  std::uintptr_t base_address;
  const char* rcc_enable_signal;
  const char* rcc_reset_signal;
  const char* clock_gate_id;
  const char* reset_id;
  const char* selector_id;
  const char* interrupt_names;
  const char* capability_overlay_ids;
  int register_count;
};
inline constexpr std::array<PeripheralInstanceDescriptor, 6> kPeripheralInstances = {{
  {PeripheralId::GPIO1, "GPIO1", "gpio", "imxrt-gpio-v1", "alloy.gpio.nxp-imxrt-gpio-v1", 1, 0x401B8000u, "CCM_CCGR1.CG13", nullptr, "gate:gpio1", nullptr, nullptr, "", "capability-instance:gpio1:bga196:io00,capability-instance:gpio1:bga196:io01", 3},
  {PeripheralId::GPIO4, "GPIO4", "gpio", "imxrt-gpio-v1", "alloy.gpio.nxp-imxrt-gpio-v1", 4, 0x401C4000u, "CCM_CCGR3.CG13", nullptr, "gate:gpio4", nullptr, nullptr, "", "capability-instance:gpio4:bga196:io00,capability-instance:gpio4:bga196:io01", 3},
  {PeripheralId::LPI2C1, "LPI2C1", "lpi2c1", "lpi2c-v1", "alloy.lpi2c1.nxp-lpi2c-v1", 0, 0x403F0000u, "CCM_CCGR2.CG2", nullptr, "gate:lpi2c1", nullptr, "selector:lpi2c-root", "LPI2C1", "capability-instance:lpi2c1:bga196:scl,capability-instance:lpi2c1:bga196:sda", 0},
  {PeripheralId::LPSPI1, "LPSPI1", "lpspi", "lpspi-v1", "alloy.spi.nxp-lpspi-v1", 1, 0x40394000u, "CCM_CCGR1.CG0", nullptr, "gate:lpspi1", nullptr, "selector:lpspi-root", "LPSPI1", "capability-instance:lpspi1:bga196:cs,capability-instance:lpspi1:bga196:sck", 0},
  {PeripheralId::LPUART1, "LPUART1", "lpuart", "lpuart-v1", "alloy.uart.nxp-lpuart-v1", 1, 0x40184000u, "CCM_CCGR5.CG12", nullptr, "gate:lpuart1", nullptr, "selector:lpuart-root", "LPUART1", "capability-instance:lpuart1:bga196:rx,capability-instance:lpuart1:bga196:tx", 4},
  {PeripheralId::LPUART3, "LPUART3", "lpuart", "lpuart-v1", "alloy.uart.nxp-lpuart-v1", 3, 0x4018C000u, "CCM_CCGR0.CG6", nullptr, "gate:lpuart3", nullptr, nullptr, "LPUART3", "", 4},
}};
}
}
}
}
}
