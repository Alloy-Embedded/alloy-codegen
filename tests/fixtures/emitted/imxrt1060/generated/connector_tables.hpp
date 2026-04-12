#pragma once

#include <array>
#include <cstdint>

namespace nxp {
namespace imxrt1060 {
namespace generated {
enum class RuntimeRefDomain : std::uint8_t {
  none,
  package,
  state,
  pin,
  constraint,
  selector,
  clock_gate,
  reset,
  register_ref,
  register_field_ref,
  integer,
  other,
};

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

enum class RouteRequirementId : std::uint16_t {
  mimxrt1062_requirement_bonded_pin_bga196_gpio_ad_b0_00,
  mimxrt1062_requirement_bonded_pin_bga196_gpio_ad_b0_01,
  mimxrt1062_requirement_bonded_pin_bga196_gpio_emc_00,
  mimxrt1062_requirement_bonded_pin_bga196_gpio_emc_01,
  mimxrt1062_requirement_clock_enable_gpio1,
  mimxrt1062_requirement_clock_enable_gpio4,
  mimxrt1062_requirement_clock_enable_lpi2c1,
  mimxrt1062_requirement_clock_enable_lpspi1,
  mimxrt1062_requirement_clock_enable_lpuart1,
  mimxrt1062_requirement_clock_enable_lpuart3,
  mimxrt1062_requirement_package_bga196,
  mimxrt1062_requirement_source_select_gpio_ad_b0_00_gpio1_io00,
  mimxrt1062_requirement_source_select_gpio_ad_b0_00_lpi2c1_scl,
  mimxrt1062_requirement_source_select_gpio_ad_b0_00_lpuart1_tx,
  mimxrt1062_requirement_source_select_gpio_ad_b0_01_gpio1_io01,
  mimxrt1062_requirement_source_select_gpio_ad_b0_01_lpi2c1_sda,
  mimxrt1062_requirement_source_select_gpio_ad_b0_01_lpuart1_rx,
  mimxrt1062_requirement_source_select_gpio_emc_00_gpio4_io00,
  mimxrt1062_requirement_source_select_gpio_emc_00_lpspi1_sck,
  mimxrt1062_requirement_source_select_gpio_emc_01_gpio4_io01,
  mimxrt1062_requirement_source_select_gpio_emc_01_lpspi1_pcs0,
};

struct RouteRequirementDescriptor {
  const char* device;
  RouteRequirementId requirement_id;
  const char* requirement_name;
  const char* kind;
  RuntimeRefDomain target_ref_domain;
  std::uint16_t target_ref_index;
  RuntimeRefDomain value_ref_domain;
  std::uint16_t value_ref_index;
  int value_int;
  const char* diagnostic_target;
  const char* diagnostic_value;
};
inline constexpr std::array<RouteRequirementDescriptor, 21> kRouteRequirements = {{
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_ad_b0_00, "requirement:bonded-pin:bga196:gpio-ad-b0-00", "bonded-pin", RuntimeRefDomain::pin, 1u, RuntimeRefDomain::package, 1u, -1, "GPIO_AD_B0_00", "bga196"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_ad_b0_01, "requirement:bonded-pin:bga196:gpio-ad-b0-01", "bonded-pin", RuntimeRefDomain::pin, 2u, RuntimeRefDomain::package, 1u, -1, "GPIO_AD_B0_01", "bga196"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_emc_00, "requirement:bonded-pin:bga196:gpio-emc-00", "bonded-pin", RuntimeRefDomain::pin, 3u, RuntimeRefDomain::package, 1u, -1, "GPIO_EMC_00", "bga196"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_emc_01, "requirement:bonded-pin:bga196:gpio-emc-01", "bonded-pin", RuntimeRefDomain::pin, 4u, RuntimeRefDomain::package, 1u, -1, "GPIO_EMC_01", "bga196"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_clock_enable_gpio1, "requirement:clock-enable:gpio1", "clock-enable", RuntimeRefDomain::clock_gate, 1u, RuntimeRefDomain::integer, 0u, 1, "CCM_CCGR1.CG13", "1"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_clock_enable_gpio4, "requirement:clock-enable:gpio4", "clock-enable", RuntimeRefDomain::clock_gate, 2u, RuntimeRefDomain::integer, 0u, 1, "CCM_CCGR3.CG13", "1"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_clock_enable_lpi2c1, "requirement:clock-enable:lpi2c1", "clock-enable", RuntimeRefDomain::clock_gate, 3u, RuntimeRefDomain::integer, 0u, 1, "CCM_CCGR2.CG2", "1"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_clock_enable_lpspi1, "requirement:clock-enable:lpspi1", "clock-enable", RuntimeRefDomain::clock_gate, 4u, RuntimeRefDomain::integer, 0u, 1, "CCM_CCGR1.CG0", "1"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_clock_enable_lpuart1, "requirement:clock-enable:lpuart1", "clock-enable", RuntimeRefDomain::clock_gate, 5u, RuntimeRefDomain::integer, 0u, 1, "CCM_CCGR5.CG12", "1"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_clock_enable_lpuart3, "requirement:clock-enable:lpuart3", "clock-enable", RuntimeRefDomain::clock_gate, 6u, RuntimeRefDomain::integer, 0u, 1, "CCM_CCGR0.CG6", "1"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_package_bga196, "requirement:package:bga196", "package", RuntimeRefDomain::package, 1u, RuntimeRefDomain::state, 1u, -1, "bga196", "selected"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_00_gpio1_io00, "requirement:source-select:gpio-ad-b0-00:gpio1:io00", "source-select", RuntimeRefDomain::pin, 1u, RuntimeRefDomain::selector, 3u, 5, "pinmux.GPIO_AD_B0_00", "selector:5"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_00_lpi2c1_scl, "requirement:source-select:gpio-ad-b0-00:lpi2c1:scl", "source-select", RuntimeRefDomain::pin, 1u, RuntimeRefDomain::selector, 1u, 0, "pinmux.GPIO_AD_B0_00", "selector:0"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_00_lpuart1_tx, "requirement:source-select:gpio-ad-b0-00:lpuart1:tx", "source-select", RuntimeRefDomain::pin, 1u, RuntimeRefDomain::selector, 2u, 2, "pinmux.GPIO_AD_B0_00", "selector:2"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_01_gpio1_io01, "requirement:source-select:gpio-ad-b0-01:gpio1:io01", "source-select", RuntimeRefDomain::pin, 2u, RuntimeRefDomain::selector, 3u, 5, "pinmux.GPIO_AD_B0_01", "selector:5"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_01_lpi2c1_sda, "requirement:source-select:gpio-ad-b0-01:lpi2c1:sda", "source-select", RuntimeRefDomain::pin, 2u, RuntimeRefDomain::selector, 1u, 0, "pinmux.GPIO_AD_B0_01", "selector:0"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_01_lpuart1_rx, "requirement:source-select:gpio-ad-b0-01:lpuart1:rx", "source-select", RuntimeRefDomain::pin, 2u, RuntimeRefDomain::selector, 2u, 2, "pinmux.GPIO_AD_B0_01", "selector:2"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_source_select_gpio_emc_00_gpio4_io00, "requirement:source-select:gpio-emc-00:gpio4:io00", "source-select", RuntimeRefDomain::pin, 3u, RuntimeRefDomain::selector, 3u, 5, "pinmux.GPIO_EMC_00", "selector:5"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_source_select_gpio_emc_00_lpspi1_sck, "requirement:source-select:gpio-emc-00:lpspi1:sck", "source-select", RuntimeRefDomain::pin, 3u, RuntimeRefDomain::selector, 2u, 2, "pinmux.GPIO_EMC_00", "selector:2"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_source_select_gpio_emc_01_gpio4_io01, "requirement:source-select:gpio-emc-01:gpio4:io01", "source-select", RuntimeRefDomain::pin, 4u, RuntimeRefDomain::selector, 3u, 5, "pinmux.GPIO_EMC_01", "selector:5"},
  {"mimxrt1062", RouteRequirementId::mimxrt1062_requirement_source_select_gpio_emc_01_lpspi1_pcs0, "requirement:source-select:gpio-emc-01:lpspi1:pcs0", "source-select", RuntimeRefDomain::pin, 4u, RuntimeRefDomain::selector, 2u, 2, "pinmux.GPIO_EMC_01", "selector:2"},
}};

enum class RouteOperationId : std::uint16_t {
  mimxrt1062_operation_clock_enable_gpio1,
  mimxrt1062_operation_clock_enable_gpio4,
  mimxrt1062_operation_clock_enable_lpi2c1,
  mimxrt1062_operation_clock_enable_lpspi1,
  mimxrt1062_operation_clock_enable_lpuart1,
  mimxrt1062_operation_clock_enable_lpuart3,
  mimxrt1062_operation_route_gpio_ad_b0_00_gpio1_io00,
  mimxrt1062_operation_route_gpio_ad_b0_00_lpi2c1_scl,
  mimxrt1062_operation_route_gpio_ad_b0_00_lpuart1_tx,
  mimxrt1062_operation_route_gpio_ad_b0_01_gpio1_io01,
  mimxrt1062_operation_route_gpio_ad_b0_01_lpi2c1_sda,
  mimxrt1062_operation_route_gpio_ad_b0_01_lpuart1_rx,
  mimxrt1062_operation_route_gpio_emc_00_gpio4_io00,
  mimxrt1062_operation_route_gpio_emc_00_lpspi1_sck,
  mimxrt1062_operation_route_gpio_emc_01_gpio4_io01,
  mimxrt1062_operation_route_gpio_emc_01_lpspi1_pcs0,
};

struct RouteOperationDescriptor {
  const char* device;
  RouteOperationId operation_id;
  const char* operation_name;
  const char* kind;
  const char* schema_id;
  const char* subject_kind;
  const char* subject_id;
  RuntimeRefDomain target_ref_domain;
  std::uint16_t target_ref_index;
  RuntimeRefDomain value_ref_domain;
  std::uint16_t value_ref_index;
  const char* register_peripheral;
  const char* register_name;
  int register_offset;
  RegisterRefId register_id;
  RegisterFieldRefId register_field_id;
  int value_int;
  const char* diagnostic_target;
  const char* diagnostic_value;
};
inline constexpr std::array<RouteOperationDescriptor, 16> kRouteOperations = {{
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_clock_enable_gpio1, "operation:clock-enable:gpio1", "set-bit", "alloy.clock.nxp-generic-clock-v1", "peripheral", "GPIO1", RuntimeRefDomain::clock_gate, 1u, RuntimeRefDomain::integer, 0u, "CCM", "CCGR1", -1, RegisterRefId::none, RegisterFieldRefId::none, 1, "CCM_CCGR1.CG13", "1"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_clock_enable_gpio4, "operation:clock-enable:gpio4", "set-bit", "alloy.clock.nxp-generic-clock-v1", "peripheral", "GPIO4", RuntimeRefDomain::clock_gate, 2u, RuntimeRefDomain::integer, 0u, "CCM", "CCGR3", -1, RegisterRefId::none, RegisterFieldRefId::none, 1, "CCM_CCGR3.CG13", "1"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_clock_enable_lpi2c1, "operation:clock-enable:lpi2c1", "set-bit", "alloy.clock.nxp-generic-clock-v1", "peripheral", "LPI2C1", RuntimeRefDomain::clock_gate, 3u, RuntimeRefDomain::integer, 0u, "CCM", "CCGR2", -1, RegisterRefId::none, RegisterFieldRefId::none, 1, "CCM_CCGR2.CG2", "1"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_clock_enable_lpspi1, "operation:clock-enable:lpspi1", "set-bit", "alloy.clock.nxp-generic-clock-v1", "peripheral", "LPSPI1", RuntimeRefDomain::clock_gate, 4u, RuntimeRefDomain::integer, 0u, "CCM", "CCGR1", -1, RegisterRefId::none, RegisterFieldRefId::none, 1, "CCM_CCGR1.CG0", "1"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_clock_enable_lpuart1, "operation:clock-enable:lpuart1", "set-bit", "alloy.clock.nxp-generic-clock-v1", "peripheral", "LPUART1", RuntimeRefDomain::clock_gate, 5u, RuntimeRefDomain::integer, 0u, "CCM", "CCGR5", -1, RegisterRefId::none, RegisterFieldRefId::none, 1, "CCM_CCGR5.CG12", "1"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_clock_enable_lpuart3, "operation:clock-enable:lpuart3", "set-bit", "alloy.clock.nxp-generic-clock-v1", "peripheral", "LPUART3", RuntimeRefDomain::clock_gate, 6u, RuntimeRefDomain::integer, 0u, "CCM", "CCGR0", -1, RegisterRefId::none, RegisterFieldRefId::none, 1, "CCM_CCGR0.CG6", "1"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_00_gpio1_io00, "operation:route:gpio-ad-b0-00:gpio1:io00", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_AD_B0_00", RuntimeRefDomain::pin, 1u, RuntimeRefDomain::selector, 3u, nullptr, nullptr, -1, RegisterRefId::none, RegisterFieldRefId::none, 5, "pinmux.GPIO_AD_B0_00", "5"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_00_lpi2c1_scl, "operation:route:gpio-ad-b0-00:lpi2c1:scl", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_AD_B0_00", RuntimeRefDomain::pin, 1u, RuntimeRefDomain::selector, 1u, nullptr, nullptr, -1, RegisterRefId::none, RegisterFieldRefId::none, 0, "pinmux.GPIO_AD_B0_00", "0"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_00_lpuart1_tx, "operation:route:gpio-ad-b0-00:lpuart1:tx", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_AD_B0_00", RuntimeRefDomain::pin, 1u, RuntimeRefDomain::selector, 2u, nullptr, nullptr, -1, RegisterRefId::none, RegisterFieldRefId::none, 2, "pinmux.GPIO_AD_B0_00", "2"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_01_gpio1_io01, "operation:route:gpio-ad-b0-01:gpio1:io01", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_AD_B0_01", RuntimeRefDomain::pin, 2u, RuntimeRefDomain::selector, 3u, nullptr, nullptr, -1, RegisterRefId::none, RegisterFieldRefId::none, 5, "pinmux.GPIO_AD_B0_01", "5"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_01_lpi2c1_sda, "operation:route:gpio-ad-b0-01:lpi2c1:sda", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_AD_B0_01", RuntimeRefDomain::pin, 2u, RuntimeRefDomain::selector, 1u, nullptr, nullptr, -1, RegisterRefId::none, RegisterFieldRefId::none, 0, "pinmux.GPIO_AD_B0_01", "0"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_01_lpuart1_rx, "operation:route:gpio-ad-b0-01:lpuart1:rx", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_AD_B0_01", RuntimeRefDomain::pin, 2u, RuntimeRefDomain::selector, 2u, nullptr, nullptr, -1, RegisterRefId::none, RegisterFieldRefId::none, 2, "pinmux.GPIO_AD_B0_01", "2"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_route_gpio_emc_00_gpio4_io00, "operation:route:gpio-emc-00:gpio4:io00", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_EMC_00", RuntimeRefDomain::pin, 3u, RuntimeRefDomain::selector, 3u, nullptr, nullptr, -1, RegisterRefId::none, RegisterFieldRefId::none, 5, "pinmux.GPIO_EMC_00", "5"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_route_gpio_emc_00_lpspi1_sck, "operation:route:gpio-emc-00:lpspi1:sck", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_EMC_00", RuntimeRefDomain::pin, 3u, RuntimeRefDomain::selector, 2u, nullptr, nullptr, -1, RegisterRefId::none, RegisterFieldRefId::none, 2, "pinmux.GPIO_EMC_00", "2"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_route_gpio_emc_01_gpio4_io01, "operation:route:gpio-emc-01:gpio4:io01", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_EMC_01", RuntimeRefDomain::pin, 4u, RuntimeRefDomain::selector, 3u, nullptr, nullptr, -1, RegisterRefId::none, RegisterFieldRefId::none, 5, "pinmux.GPIO_EMC_01", "5"},
  {"mimxrt1062", RouteOperationId::mimxrt1062_operation_route_gpio_emc_01_lpspi1_pcs0, "operation:route:gpio-emc-01:lpspi1:pcs0", "write-selector", "alloy.pinmux.imxrt-iomuxc-v1", "pin", "GPIO_EMC_01", RuntimeRefDomain::pin, 4u, RuntimeRefDomain::selector, 2u, nullptr, nullptr, -1, RegisterRefId::none, RegisterFieldRefId::none, 2, "pinmux.GPIO_EMC_01", "2"},
}};

enum class ConnectionCandidateId : std::uint16_t {
  mimxrt1062_candidate_gpio_ad_b0_00_gpio1_io00,
  mimxrt1062_candidate_gpio_ad_b0_00_lpi2c1_scl,
  mimxrt1062_candidate_gpio_ad_b0_00_lpuart1_tx,
  mimxrt1062_candidate_gpio_ad_b0_01_gpio1_io01,
  mimxrt1062_candidate_gpio_ad_b0_01_lpi2c1_sda,
  mimxrt1062_candidate_gpio_ad_b0_01_lpuart1_rx,
  mimxrt1062_candidate_gpio_emc_00_gpio4_io00,
  mimxrt1062_candidate_gpio_emc_00_lpspi1_sck,
  mimxrt1062_candidate_gpio_emc_01_gpio4_io01,
  mimxrt1062_candidate_gpio_emc_01_lpspi1_pcs0,
};

struct ConnectionCandidateDescriptor {
  const char* device;
  ConnectionCandidateId candidate_id;
  const char* candidate_name;
  PinRefId pin_id;
  const char* pin;
  const char* peripheral;
  const char* signal;
  const char* route_kind;
  SelectorRefId route_selector_id;
  const char* diagnostic_route_selector;
  int route_group_index;
  std::uint16_t requirement_offset;
  std::uint16_t requirement_count;
  std::uint16_t operation_offset;
  std::uint16_t operation_count;
  std::uint16_t capability_offset;
  std::uint16_t capability_count;
};
inline constexpr std::array<ConnectionCandidateDescriptor, 10> kConnectionCandidates = {{
  {"mimxrt1062", ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_gpio1_io00, "candidate:gpio-ad-b0-00:gpio1:io00", PinRefId::mimxrt1062_GPIO_AD_B0_00, "GPIO_AD_B0_00", "GPIO1", "io00", "iomuxc-mux", SelectorRefId::mimxrt1062_selector_5, "selector:5", 0, 0u, 4u, 0u, 2u, 0u, 2u},
  {"mimxrt1062", ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpi2c1_scl, "candidate:gpio-ad-b0-00:lpi2c1:scl", PinRefId::mimxrt1062_GPIO_AD_B0_00, "GPIO_AD_B0_00", "LPI2C1", "scl", "iomuxc-mux", SelectorRefId::mimxrt1062_selector_0, "selector:0", 2, 4u, 4u, 2u, 2u, 2u, 2u},
  {"mimxrt1062", ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpuart1_tx, "candidate:gpio-ad-b0-00:lpuart1:tx", PinRefId::mimxrt1062_GPIO_AD_B0_00, "GPIO_AD_B0_00", "LPUART1", "tx", "iomuxc-mux", SelectorRefId::mimxrt1062_selector_2, "selector:2", 4, 8u, 4u, 4u, 2u, 4u, 2u},
  {"mimxrt1062", ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_gpio1_io01, "candidate:gpio-ad-b0-01:gpio1:io01", PinRefId::mimxrt1062_GPIO_AD_B0_01, "GPIO_AD_B0_01", "GPIO1", "io01", "iomuxc-mux", SelectorRefId::mimxrt1062_selector_5, "selector:5", 0, 12u, 4u, 6u, 2u, 6u, 2u},
  {"mimxrt1062", ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpi2c1_sda, "candidate:gpio-ad-b0-01:lpi2c1:sda", PinRefId::mimxrt1062_GPIO_AD_B0_01, "GPIO_AD_B0_01", "LPI2C1", "sda", "iomuxc-mux", SelectorRefId::mimxrt1062_selector_0, "selector:0", 2, 16u, 4u, 8u, 2u, 8u, 2u},
  {"mimxrt1062", ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpuart1_rx, "candidate:gpio-ad-b0-01:lpuart1:rx", PinRefId::mimxrt1062_GPIO_AD_B0_01, "GPIO_AD_B0_01", "LPUART1", "rx", "iomuxc-mux", SelectorRefId::mimxrt1062_selector_2, "selector:2", 4, 20u, 4u, 10u, 2u, 10u, 2u},
  {"mimxrt1062", ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_gpio4_io00, "candidate:gpio-emc-00:gpio4:io00", PinRefId::mimxrt1062_GPIO_EMC_00, "GPIO_EMC_00", "GPIO4", "io00", "iomuxc-mux", SelectorRefId::mimxrt1062_selector_5, "selector:5", 1, 24u, 4u, 12u, 2u, 12u, 2u},
  {"mimxrt1062", ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_lpspi1_sck, "candidate:gpio-emc-00:lpspi1:sck", PinRefId::mimxrt1062_GPIO_EMC_00, "GPIO_EMC_00", "LPSPI1", "sck", "iomuxc-mux", SelectorRefId::mimxrt1062_selector_2, "selector:2", 3, 28u, 4u, 14u, 2u, 14u, 2u},
  {"mimxrt1062", ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_gpio4_io01, "candidate:gpio-emc-01:gpio4:io01", PinRefId::mimxrt1062_GPIO_EMC_01, "GPIO_EMC_01", "GPIO4", "io01", "iomuxc-mux", SelectorRefId::mimxrt1062_selector_5, "selector:5", 1, 32u, 4u, 16u, 2u, 16u, 2u},
  {"mimxrt1062", ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_lpspi1_pcs0, "candidate:gpio-emc-01:lpspi1:pcs0", PinRefId::mimxrt1062_GPIO_EMC_01, "GPIO_EMC_01", "LPSPI1", "pcs0", "iomuxc-mux", SelectorRefId::mimxrt1062_selector_2, "selector:2", 3, 36u, 4u, 18u, 2u, 18u, 2u},
}};

struct CandidateRequirementRef {
  ConnectionCandidateId candidate_id;
  RouteRequirementId requirement_id;
};
inline constexpr std::array<CandidateRequirementRef, 40> kCandidateRequirementRefs = {{
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_gpio1_io00, RouteRequirementId::mimxrt1062_requirement_package_bga196},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_gpio1_io00, RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_ad_b0_00},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_gpio1_io00, RouteRequirementId::mimxrt1062_requirement_clock_enable_gpio1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_gpio1_io00, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_00_gpio1_io00},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpi2c1_scl, RouteRequirementId::mimxrt1062_requirement_package_bga196},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpi2c1_scl, RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_ad_b0_00},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpi2c1_scl, RouteRequirementId::mimxrt1062_requirement_clock_enable_lpi2c1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpi2c1_scl, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_00_lpi2c1_scl},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpuart1_tx, RouteRequirementId::mimxrt1062_requirement_package_bga196},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpuart1_tx, RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_ad_b0_00},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpuart1_tx, RouteRequirementId::mimxrt1062_requirement_clock_enable_lpuart1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpuart1_tx, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_00_lpuart1_tx},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_gpio1_io01, RouteRequirementId::mimxrt1062_requirement_package_bga196},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_gpio1_io01, RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_ad_b0_01},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_gpio1_io01, RouteRequirementId::mimxrt1062_requirement_clock_enable_gpio1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_gpio1_io01, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_01_gpio1_io01},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpi2c1_sda, RouteRequirementId::mimxrt1062_requirement_package_bga196},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpi2c1_sda, RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_ad_b0_01},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpi2c1_sda, RouteRequirementId::mimxrt1062_requirement_clock_enable_lpi2c1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpi2c1_sda, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_01_lpi2c1_sda},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpuart1_rx, RouteRequirementId::mimxrt1062_requirement_package_bga196},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpuart1_rx, RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_ad_b0_01},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpuart1_rx, RouteRequirementId::mimxrt1062_requirement_clock_enable_lpuart1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpuart1_rx, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_01_lpuart1_rx},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_gpio4_io00, RouteRequirementId::mimxrt1062_requirement_package_bga196},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_gpio4_io00, RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_emc_00},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_gpio4_io00, RouteRequirementId::mimxrt1062_requirement_clock_enable_gpio4},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_gpio4_io00, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_emc_00_gpio4_io00},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_lpspi1_sck, RouteRequirementId::mimxrt1062_requirement_package_bga196},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_lpspi1_sck, RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_emc_00},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_lpspi1_sck, RouteRequirementId::mimxrt1062_requirement_clock_enable_lpspi1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_lpspi1_sck, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_emc_00_lpspi1_sck},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_gpio4_io01, RouteRequirementId::mimxrt1062_requirement_package_bga196},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_gpio4_io01, RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_emc_01},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_gpio4_io01, RouteRequirementId::mimxrt1062_requirement_clock_enable_gpio4},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_gpio4_io01, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_emc_01_gpio4_io01},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_lpspi1_pcs0, RouteRequirementId::mimxrt1062_requirement_package_bga196},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_lpspi1_pcs0, RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_emc_01},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_lpspi1_pcs0, RouteRequirementId::mimxrt1062_requirement_clock_enable_lpspi1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_lpspi1_pcs0, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_emc_01_lpspi1_pcs0},
}};

struct CandidateOperationRef {
  ConnectionCandidateId candidate_id;
  RouteOperationId operation_id;
};
inline constexpr std::array<CandidateOperationRef, 20> kCandidateOperationRefs = {{
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_gpio1_io00, RouteOperationId::mimxrt1062_operation_clock_enable_gpio1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_gpio1_io00, RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_00_gpio1_io00},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpi2c1_scl, RouteOperationId::mimxrt1062_operation_clock_enable_lpi2c1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpi2c1_scl, RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_00_lpi2c1_scl},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpuart1_tx, RouteOperationId::mimxrt1062_operation_clock_enable_lpuart1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpuart1_tx, RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_00_lpuart1_tx},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_gpio1_io01, RouteOperationId::mimxrt1062_operation_clock_enable_gpio1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_gpio1_io01, RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_01_gpio1_io01},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpi2c1_sda, RouteOperationId::mimxrt1062_operation_clock_enable_lpi2c1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpi2c1_sda, RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_01_lpi2c1_sda},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpuart1_rx, RouteOperationId::mimxrt1062_operation_clock_enable_lpuart1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpuart1_rx, RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_01_lpuart1_rx},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_gpio4_io00, RouteOperationId::mimxrt1062_operation_clock_enable_gpio4},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_gpio4_io00, RouteOperationId::mimxrt1062_operation_route_gpio_emc_00_gpio4_io00},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_lpspi1_sck, RouteOperationId::mimxrt1062_operation_clock_enable_lpspi1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_lpspi1_sck, RouteOperationId::mimxrt1062_operation_route_gpio_emc_00_lpspi1_sck},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_gpio4_io01, RouteOperationId::mimxrt1062_operation_clock_enable_gpio4},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_gpio4_io01, RouteOperationId::mimxrt1062_operation_route_gpio_emc_01_gpio4_io01},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_lpspi1_pcs0, RouteOperationId::mimxrt1062_operation_clock_enable_lpspi1},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_lpspi1_pcs0, RouteOperationId::mimxrt1062_operation_route_gpio_emc_01_lpspi1_pcs0},
}};

struct CandidateCapabilityRef {
  ConnectionCandidateId candidate_id;
  const char* capability_id;
};
inline constexpr std::array<CandidateCapabilityRef, 20> kCandidateCapabilityRefs = {{
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_gpio1_io00, "capability:gpio:imxrt-gpio-v1:io00"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_gpio1_io00, "capability-instance:gpio1:bga196:io00"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpi2c1_scl, "capability:lpi2c1:lpi2c-v1:scl"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpi2c1_scl, "capability-instance:lpi2c1:bga196:scl"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpuart1_tx, "capability:lpuart:lpuart-v1:tx"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpuart1_tx, "capability-instance:lpuart1:bga196:tx"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_gpio1_io01, "capability:gpio:imxrt-gpio-v1:io01"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_gpio1_io01, "capability-instance:gpio1:bga196:io01"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpi2c1_sda, "capability:lpi2c1:lpi2c-v1:sda"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpi2c1_sda, "capability-instance:lpi2c1:bga196:sda"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpuart1_rx, "capability:lpuart:lpuart-v1:rx"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpuart1_rx, "capability-instance:lpuart1:bga196:rx"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_gpio4_io00, "capability:gpio:imxrt-gpio-v1:io00"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_gpio4_io00, "capability-instance:gpio4:bga196:io00"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_lpspi1_sck, "capability:lpspi:lpspi-v1:sck"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_lpspi1_sck, "capability-instance:lpspi1:bga196:sck"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_gpio4_io01, "capability:gpio:imxrt-gpio-v1:io01"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_gpio4_io01, "capability-instance:gpio4:bga196:io01"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_lpspi1_pcs0, "capability:lpspi:lpspi-v1:cs"},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_lpspi1_pcs0, "capability-instance:lpspi1:bga196:cs"},
}};

enum class ConnectionGroupId : std::uint16_t {
  mimxrt1062_group_gpio1_bga196_all_signals,
  mimxrt1062_group_gpio4_bga196_all_signals,
  mimxrt1062_group_lpi2c1_bga196_all_signals,
  mimxrt1062_group_lpspi1_bga196_sck_cs,
  mimxrt1062_group_lpuart1_bga196_tx_rx,
};

struct ConnectionGroupDescriptor {
  const char* device;
  ConnectionGroupId group_id;
  const char* group_name;
  const char* peripheral;
  PackageRefId package_id;
  const char* diagnostic_package_name;
  const char* conflict_group;
  std::uint16_t signal_offset;
  std::uint16_t signal_count;
  std::uint16_t candidate_offset;
  std::uint16_t candidate_count;
};
inline constexpr std::array<ConnectionGroupDescriptor, 5> kConnectionGroups = {{
  {"mimxrt1062", ConnectionGroupId::mimxrt1062_group_gpio1_bga196_all_signals, "group:gpio1:bga196:all-signals", "GPIO1", PackageRefId::mimxrt1062_bga196, "bga196", "conflict:gpio1:bga196:all-signals", 0u, 2u, 0u, 2u},
  {"mimxrt1062", ConnectionGroupId::mimxrt1062_group_gpio4_bga196_all_signals, "group:gpio4:bga196:all-signals", "GPIO4", PackageRefId::mimxrt1062_bga196, "bga196", "conflict:gpio4:bga196:all-signals", 2u, 2u, 2u, 2u},
  {"mimxrt1062", ConnectionGroupId::mimxrt1062_group_lpi2c1_bga196_all_signals, "group:lpi2c1:bga196:all-signals", "LPI2C1", PackageRefId::mimxrt1062_bga196, "bga196", "conflict:lpi2c1:bga196:all-signals", 4u, 2u, 4u, 2u},
  {"mimxrt1062", ConnectionGroupId::mimxrt1062_group_lpspi1_bga196_sck_cs, "group:lpspi1:bga196:sck-cs", "LPSPI1", PackageRefId::mimxrt1062_bga196, "bga196", "conflict:lpspi1:bga196:sck-cs", 6u, 2u, 6u, 2u},
  {"mimxrt1062", ConnectionGroupId::mimxrt1062_group_lpuart1_bga196_tx_rx, "group:lpuart1:bga196:tx-rx", "LPUART1", PackageRefId::mimxrt1062_bga196, "bga196", "conflict:lpuart1:bga196:tx-rx", 8u, 2u, 8u, 2u},
}};

struct ConnectionGroupSignalRef {
  ConnectionGroupId group_id;
  const char* signal_name;
};
inline constexpr std::array<ConnectionGroupSignalRef, 10> kConnectionGroupSignals = {{
  {ConnectionGroupId::mimxrt1062_group_gpio1_bga196_all_signals, "io00"},
  {ConnectionGroupId::mimxrt1062_group_gpio1_bga196_all_signals, "io01"},
  {ConnectionGroupId::mimxrt1062_group_gpio4_bga196_all_signals, "io00"},
  {ConnectionGroupId::mimxrt1062_group_gpio4_bga196_all_signals, "io01"},
  {ConnectionGroupId::mimxrt1062_group_lpi2c1_bga196_all_signals, "scl"},
  {ConnectionGroupId::mimxrt1062_group_lpi2c1_bga196_all_signals, "sda"},
  {ConnectionGroupId::mimxrt1062_group_lpspi1_bga196_sck_cs, "sck"},
  {ConnectionGroupId::mimxrt1062_group_lpspi1_bga196_sck_cs, "cs"},
  {ConnectionGroupId::mimxrt1062_group_lpuart1_bga196_tx_rx, "tx"},
  {ConnectionGroupId::mimxrt1062_group_lpuart1_bga196_tx_rx, "rx"},
}};

struct ConnectionGroupCandidateRef {
  ConnectionGroupId group_id;
  ConnectionCandidateId candidate_id;
};
inline constexpr std::array<ConnectionGroupCandidateRef, 10> kConnectionGroupCandidateRefs = {{
  {ConnectionGroupId::mimxrt1062_group_gpio1_bga196_all_signals, ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_gpio1_io00},
  {ConnectionGroupId::mimxrt1062_group_gpio1_bga196_all_signals, ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_gpio1_io01},
  {ConnectionGroupId::mimxrt1062_group_gpio4_bga196_all_signals, ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_gpio4_io00},
  {ConnectionGroupId::mimxrt1062_group_gpio4_bga196_all_signals, ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_gpio4_io01},
  {ConnectionGroupId::mimxrt1062_group_lpi2c1_bga196_all_signals, ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpi2c1_scl},
  {ConnectionGroupId::mimxrt1062_group_lpi2c1_bga196_all_signals, ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpi2c1_sda},
  {ConnectionGroupId::mimxrt1062_group_lpspi1_bga196_sck_cs, ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_lpspi1_sck},
  {ConnectionGroupId::mimxrt1062_group_lpspi1_bga196_sck_cs, ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_lpspi1_pcs0},
  {ConnectionGroupId::mimxrt1062_group_lpuart1_bga196_tx_rx, ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpuart1_tx},
  {ConnectionGroupId::mimxrt1062_group_lpuart1_bga196_tx_rx, ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpuart1_rx},
}};
}
}
}
