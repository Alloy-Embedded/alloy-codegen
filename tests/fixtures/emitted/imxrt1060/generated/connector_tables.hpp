#pragma once

namespace nxp {
namespace imxrt1060 {
namespace generated {
struct SignalEndpointDescriptor {
  const char* device;
  const char* endpoint_id;
  const char* peripheral_class;
  const char* signal;
  const char* direction;
};
inline constexpr SignalEndpointDescriptor kSignalEndpoints[] = {
  {"mimxrt1062", "endpoint:gpio:io00", "gpio", "IO00", nullptr},
  {"mimxrt1062", "endpoint:gpio:io01", "gpio", "IO01", nullptr},
  {"mimxrt1062", "endpoint:lpi2c1:scl", "lpi2c1", "SCL", nullptr},
  {"mimxrt1062", "endpoint:lpi2c1:sda", "lpi2c1", "SDA", "bidirectional"},
  {"mimxrt1062", "endpoint:spi:pcs0", "spi", "PCS0", nullptr},
  {"mimxrt1062", "endpoint:spi:sck", "spi", "SCK", "output"},
  {"mimxrt1062", "endpoint:uart:rx", "uart", "RX", "input"},
  {"mimxrt1062", "endpoint:uart:tx", "uart", "TX", "output"},
};

struct RouteRequirementDescriptor {
  const char* device;
  const char* requirement_id;
  const char* kind;
  const char* target;
  const char* value;
};
inline constexpr RouteRequirementDescriptor kRouteRequirements[] = {
  {"mimxrt1062", "requirement:bonded-pin:bga196:gpio-ad-b0-00", "bonded-pin", "GPIO_AD_B0_00", "bga196"},
  {"mimxrt1062", "requirement:bonded-pin:bga196:gpio-ad-b0-01", "bonded-pin", "GPIO_AD_B0_01", "bga196"},
  {"mimxrt1062", "requirement:bonded-pin:bga196:gpio-emc-00", "bonded-pin", "GPIO_EMC_00", "bga196"},
  {"mimxrt1062", "requirement:bonded-pin:bga196:gpio-emc-01", "bonded-pin", "GPIO_EMC_01", "bga196"},
  {"mimxrt1062", "requirement:clock-enable:gpio1", "clock-enable", "CCM_CCGR1.CG13", "1"},
  {"mimxrt1062", "requirement:clock-enable:gpio4", "clock-enable", "CCM_CCGR3.CG13", "1"},
  {"mimxrt1062", "requirement:clock-enable:lpi2c1", "clock-enable", "CCM_CCGR2.CG2", "1"},
  {"mimxrt1062", "requirement:clock-enable:lpspi1", "clock-enable", "CCM_CCGR1.CG0", "1"},
  {"mimxrt1062", "requirement:clock-enable:lpuart1", "clock-enable", "CCM_CCGR5.CG12", "1"},
  {"mimxrt1062", "requirement:clock-enable:lpuart3", "clock-enable", "CCM_CCGR0.CG6", "1"},
  {"mimxrt1062", "requirement:package:bga196", "package", "bga196", "selected"},
  {"mimxrt1062", "requirement:source-select:gpio-ad-b0-00:gpio1:io00", "source-select", "pinmux.GPIO_AD_B0_00", "selector:5"},
  {"mimxrt1062", "requirement:source-select:gpio-ad-b0-00:lpi2c1:scl", "source-select", "pinmux.GPIO_AD_B0_00", "selector:0"},
  {"mimxrt1062", "requirement:source-select:gpio-ad-b0-00:lpuart1:tx", "source-select", "pinmux.GPIO_AD_B0_00", "selector:2"},
  {"mimxrt1062", "requirement:source-select:gpio-ad-b0-01:gpio1:io01", "source-select", "pinmux.GPIO_AD_B0_01", "selector:5"},
  {"mimxrt1062", "requirement:source-select:gpio-ad-b0-01:lpi2c1:sda", "source-select", "pinmux.GPIO_AD_B0_01", "selector:0"},
  {"mimxrt1062", "requirement:source-select:gpio-ad-b0-01:lpuart1:rx", "source-select", "pinmux.GPIO_AD_B0_01", "selector:2"},
  {"mimxrt1062", "requirement:source-select:gpio-emc-00:gpio4:io00", "source-select", "pinmux.GPIO_EMC_00", "selector:5"},
  {"mimxrt1062", "requirement:source-select:gpio-emc-00:lpspi1:sck", "source-select", "pinmux.GPIO_EMC_00", "selector:2"},
  {"mimxrt1062", "requirement:source-select:gpio-emc-01:gpio4:io01", "source-select", "pinmux.GPIO_EMC_01", "selector:5"},
  {"mimxrt1062", "requirement:source-select:gpio-emc-01:lpspi1:pcs0", "source-select", "pinmux.GPIO_EMC_01", "selector:2"},
};

struct RouteOperationDescriptor {
  const char* device;
  const char* operation_id;
  const char* kind;
  const char* schema_id;
  const char* subject_kind;
  const char* subject_id;
  const char* register_peripheral;
  const char* register_name;
  int register_offset;
  const char* target;
  const char* value;
  int value_int;
};
inline constexpr RouteOperationDescriptor kRouteOperations[] = {
  {"mimxrt1062", "operation:clock-enable:gpio1", "set-bit", "alloy.clock.nxp-generic-clock-v1", "peripheral", "GPIO1", nullptr, nullptr, -1, "CCM_CCGR1.CG13", "1", 1},
  {"mimxrt1062", "operation:clock-enable:gpio4", "set-bit", "alloy.clock.nxp-generic-clock-v1", "peripheral", "GPIO4", nullptr, nullptr, -1, "CCM_CCGR3.CG13", "1", 1},
  {"mimxrt1062", "operation:clock-enable:lpi2c1", "set-bit", "alloy.clock.nxp-generic-clock-v1", "peripheral", "LPI2C1", nullptr, nullptr, -1, "CCM_CCGR2.CG2", "1", 1},
  {"mimxrt1062", "operation:clock-enable:lpspi1", "set-bit", "alloy.clock.nxp-generic-clock-v1", "peripheral", "LPSPI1", nullptr, nullptr, -1, "CCM_CCGR1.CG0", "1", 1},
  {"mimxrt1062", "operation:clock-enable:lpuart1", "set-bit", "alloy.clock.nxp-generic-clock-v1", "peripheral", "LPUART1", nullptr, nullptr, -1, "CCM_CCGR5.CG12", "1", 1},
  {"mimxrt1062", "operation:clock-enable:lpuart3", "set-bit", "alloy.clock.nxp-generic-clock-v1", "peripheral", "LPUART3", nullptr, nullptr, -1, "CCM_CCGR0.CG6", "1", 1},
  {"mimxrt1062", "operation:route:gpio-ad-b0-00:gpio1:io00", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_AD_B0_00", nullptr, nullptr, -1, "pinmux.GPIO_AD_B0_00", "5", 5},
  {"mimxrt1062", "operation:route:gpio-ad-b0-00:lpi2c1:scl", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_AD_B0_00", nullptr, nullptr, -1, "pinmux.GPIO_AD_B0_00", "0", 0},
  {"mimxrt1062", "operation:route:gpio-ad-b0-00:lpuart1:tx", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_AD_B0_00", nullptr, nullptr, -1, "pinmux.GPIO_AD_B0_00", "2", 2},
  {"mimxrt1062", "operation:route:gpio-ad-b0-01:gpio1:io01", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_AD_B0_01", nullptr, nullptr, -1, "pinmux.GPIO_AD_B0_01", "5", 5},
  {"mimxrt1062", "operation:route:gpio-ad-b0-01:lpi2c1:sda", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_AD_B0_01", nullptr, nullptr, -1, "pinmux.GPIO_AD_B0_01", "0", 0},
  {"mimxrt1062", "operation:route:gpio-ad-b0-01:lpuart1:rx", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_AD_B0_01", nullptr, nullptr, -1, "pinmux.GPIO_AD_B0_01", "2", 2},
  {"mimxrt1062", "operation:route:gpio-emc-00:gpio4:io00", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_EMC_00", nullptr, nullptr, -1, "pinmux.GPIO_EMC_00", "5", 5},
  {"mimxrt1062", "operation:route:gpio-emc-00:lpspi1:sck", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_EMC_00", nullptr, nullptr, -1, "pinmux.GPIO_EMC_00", "2", 2},
  {"mimxrt1062", "operation:route:gpio-emc-01:gpio4:io01", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_EMC_01", nullptr, nullptr, -1, "pinmux.GPIO_EMC_01", "5", 5},
  {"mimxrt1062", "operation:route:gpio-emc-01:lpspi1:pcs0", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_EMC_01", nullptr, nullptr, -1, "pinmux.GPIO_EMC_01", "2", 2},
};

struct ConnectionCandidateDescriptor {
  const char* device;
  const char* candidate_id;
  const char* pin;
  const char* peripheral;
  const char* signal;
  const char* route_kind;
  const char* route_selector;
  const char* route_group_id;
  const char* requirement_ids;
  const char* operation_ids;
  const char* capability_ids;
};
inline constexpr ConnectionCandidateDescriptor kConnectionCandidates[] = {
  {"mimxrt1062", "candidate:gpio-ad-b0-00:gpio1:io00", "GPIO_AD_B0_00", "GPIO1", "io00", "iomuxc-mux", "selector:5", "group:gpio1:bga196:all-signals", "requirement:package:bga196,requirement:bonded-pin:bga196:gpio-ad-b0-00,requirement:clock-enable:gpio1,requirement:source-select:gpio-ad-b0-00:gpio1:io00", "operation:clock-enable:gpio1,operation:route:gpio-ad-b0-00:gpio1:io00", "capability:gpio:imxrt-gpio-v1:io00,capability-instance:gpio1:bga196:io00"},
  {"mimxrt1062", "candidate:gpio-ad-b0-00:lpi2c1:scl", "GPIO_AD_B0_00", "LPI2C1", "scl", "iomuxc-mux", "selector:0", "group:lpi2c1:bga196:all-signals", "requirement:package:bga196,requirement:bonded-pin:bga196:gpio-ad-b0-00,requirement:clock-enable:lpi2c1,requirement:source-select:gpio-ad-b0-00:lpi2c1:scl", "operation:clock-enable:lpi2c1,operation:route:gpio-ad-b0-00:lpi2c1:scl", "capability:lpi2c1:lpi2c-v1:scl,capability-instance:lpi2c1:bga196:scl"},
  {"mimxrt1062", "candidate:gpio-ad-b0-00:lpuart1:tx", "GPIO_AD_B0_00", "LPUART1", "tx", "iomuxc-mux", "selector:2", "group:lpuart1:bga196:tx-rx", "requirement:package:bga196,requirement:bonded-pin:bga196:gpio-ad-b0-00,requirement:clock-enable:lpuart1,requirement:source-select:gpio-ad-b0-00:lpuart1:tx", "operation:clock-enable:lpuart1,operation:route:gpio-ad-b0-00:lpuart1:tx", "capability:lpuart:lpuart-v1:tx,capability-instance:lpuart1:bga196:tx"},
  {"mimxrt1062", "candidate:gpio-ad-b0-01:gpio1:io01", "GPIO_AD_B0_01", "GPIO1", "io01", "iomuxc-mux", "selector:5", "group:gpio1:bga196:all-signals", "requirement:package:bga196,requirement:bonded-pin:bga196:gpio-ad-b0-01,requirement:clock-enable:gpio1,requirement:source-select:gpio-ad-b0-01:gpio1:io01", "operation:clock-enable:gpio1,operation:route:gpio-ad-b0-01:gpio1:io01", "capability:gpio:imxrt-gpio-v1:io01,capability-instance:gpio1:bga196:io01"},
  {"mimxrt1062", "candidate:gpio-ad-b0-01:lpi2c1:sda", "GPIO_AD_B0_01", "LPI2C1", "sda", "iomuxc-mux", "selector:0", "group:lpi2c1:bga196:all-signals", "requirement:package:bga196,requirement:bonded-pin:bga196:gpio-ad-b0-01,requirement:clock-enable:lpi2c1,requirement:source-select:gpio-ad-b0-01:lpi2c1:sda", "operation:clock-enable:lpi2c1,operation:route:gpio-ad-b0-01:lpi2c1:sda", "capability:lpi2c1:lpi2c-v1:sda,capability-instance:lpi2c1:bga196:sda"},
  {"mimxrt1062", "candidate:gpio-ad-b0-01:lpuart1:rx", "GPIO_AD_B0_01", "LPUART1", "rx", "iomuxc-mux", "selector:2", "group:lpuart1:bga196:tx-rx", "requirement:package:bga196,requirement:bonded-pin:bga196:gpio-ad-b0-01,requirement:clock-enable:lpuart1,requirement:source-select:gpio-ad-b0-01:lpuart1:rx", "operation:clock-enable:lpuart1,operation:route:gpio-ad-b0-01:lpuart1:rx", "capability:lpuart:lpuart-v1:rx,capability-instance:lpuart1:bga196:rx"},
  {"mimxrt1062", "candidate:gpio-emc-00:gpio4:io00", "GPIO_EMC_00", "GPIO4", "io00", "iomuxc-mux", "selector:5", "group:gpio4:bga196:all-signals", "requirement:package:bga196,requirement:bonded-pin:bga196:gpio-emc-00,requirement:clock-enable:gpio4,requirement:source-select:gpio-emc-00:gpio4:io00", "operation:clock-enable:gpio4,operation:route:gpio-emc-00:gpio4:io00", "capability:gpio:imxrt-gpio-v1:io00,capability-instance:gpio4:bga196:io00"},
  {"mimxrt1062", "candidate:gpio-emc-00:lpspi1:sck", "GPIO_EMC_00", "LPSPI1", "sck", "iomuxc-mux", "selector:2", "group:lpspi1:bga196:sck-cs", "requirement:package:bga196,requirement:bonded-pin:bga196:gpio-emc-00,requirement:clock-enable:lpspi1,requirement:source-select:gpio-emc-00:lpspi1:sck", "operation:clock-enable:lpspi1,operation:route:gpio-emc-00:lpspi1:sck", "capability:lpspi:lpspi-v1:sck,capability-instance:lpspi1:bga196:sck"},
  {"mimxrt1062", "candidate:gpio-emc-01:gpio4:io01", "GPIO_EMC_01", "GPIO4", "io01", "iomuxc-mux", "selector:5", "group:gpio4:bga196:all-signals", "requirement:package:bga196,requirement:bonded-pin:bga196:gpio-emc-01,requirement:clock-enable:gpio4,requirement:source-select:gpio-emc-01:gpio4:io01", "operation:clock-enable:gpio4,operation:route:gpio-emc-01:gpio4:io01", "capability:gpio:imxrt-gpio-v1:io01,capability-instance:gpio4:bga196:io01"},
  {"mimxrt1062", "candidate:gpio-emc-01:lpspi1:pcs0", "GPIO_EMC_01", "LPSPI1", "pcs0", "iomuxc-mux", "selector:2", "group:lpspi1:bga196:sck-cs", "requirement:package:bga196,requirement:bonded-pin:bga196:gpio-emc-01,requirement:clock-enable:lpspi1,requirement:source-select:gpio-emc-01:lpspi1:pcs0", "operation:clock-enable:lpspi1,operation:route:gpio-emc-01:lpspi1:pcs0", "capability:lpspi:lpspi-v1:cs,capability-instance:lpspi1:bga196:cs"},
};

struct ConnectionGroupDescriptor {
  const char* device;
  const char* group_id;
  const char* peripheral;
  const char* signals;
  const char* candidate_ids;
  const char* package_name;
  const char* conflict_group;
};
inline constexpr ConnectionGroupDescriptor kConnectionGroups[] = {
  {"mimxrt1062", "group:gpio1:bga196:all-signals", "GPIO1", "io00,io01", "candidate:gpio-ad-b0-00:gpio1:io00,candidate:gpio-ad-b0-01:gpio1:io01", "bga196", "conflict:gpio1:bga196:all-signals"},
  {"mimxrt1062", "group:gpio4:bga196:all-signals", "GPIO4", "io00,io01", "candidate:gpio-emc-00:gpio4:io00,candidate:gpio-emc-01:gpio4:io01", "bga196", "conflict:gpio4:bga196:all-signals"},
  {"mimxrt1062", "group:lpi2c1:bga196:all-signals", "LPI2C1", "scl,sda", "candidate:gpio-ad-b0-00:lpi2c1:scl,candidate:gpio-ad-b0-01:lpi2c1:sda", "bga196", "conflict:lpi2c1:bga196:all-signals"},
  {"mimxrt1062", "group:lpspi1:bga196:sck-cs", "LPSPI1", "sck,cs", "candidate:gpio-emc-00:lpspi1:sck,candidate:gpio-emc-01:lpspi1:pcs0", "bga196", "conflict:lpspi1:bga196:sck-cs"},
  {"mimxrt1062", "group:lpuart1:bga196:tx-rx", "LPUART1", "tx,rx", "candidate:gpio-ad-b0-00:lpuart1:tx,candidate:gpio-ad-b0-01:lpuart1:rx", "bga196", "conflict:lpuart1:bga196:tx-rx"},
};
}
}
}
