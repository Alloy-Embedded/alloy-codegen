#pragma once

#include <array>
#include <cstdint>
#include "runtime_refs.hpp"
#include "runtime_semantics.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
enum class RuntimeRefDomain : std::uint8_t {
  none,
  package,
  package_pad,
  peripheral,
  state,
  pin,
  constraint,
  selector,
  ip_block,
  capability,
  clock_gate,
  reset,
  register_ref,
  register_field_ref,
  integer,
  other,
};

struct RuntimeRef {
  RuntimeRefDomain domain;
  std::uint16_t index;
};

enum class SignalEndpointId : std::uint16_t {
  none,
  mimxrt1062_endpoint_gpio_io00,
  mimxrt1062_endpoint_gpio_io01,
  mimxrt1062_endpoint_lpi2c1_scl,
  mimxrt1062_endpoint_lpi2c1_sda,
  mimxrt1062_endpoint_spi_pcs0,
  mimxrt1062_endpoint_spi_sck,
  mimxrt1062_endpoint_uart_rx,
  mimxrt1062_endpoint_uart_tx,
};

struct SignalEndpointDescriptor {
  DeviceRefId device_id;
  SignalEndpointId endpoint_id;
  PeripheralClassId peripheral_class_id;
  SignalId signal_id;
  DirectionId direction_id;
};
inline constexpr std::array<SignalEndpointDescriptor, 8> kSignalEndpoints = {{
  {DeviceRefId::mimxrt1062, SignalEndpointId::mimxrt1062_endpoint_gpio_io00, PeripheralClassId::class_gpio, SignalId::signal_IO00, DirectionId::none},
  {DeviceRefId::mimxrt1062, SignalEndpointId::mimxrt1062_endpoint_gpio_io01, PeripheralClassId::class_gpio, SignalId::signal_IO01, DirectionId::none},
  {DeviceRefId::mimxrt1062, SignalEndpointId::mimxrt1062_endpoint_lpi2c1_scl, PeripheralClassId::class_lpi2c1, SignalId::signal_SCL, DirectionId::none},
  {DeviceRefId::mimxrt1062, SignalEndpointId::mimxrt1062_endpoint_lpi2c1_sda, PeripheralClassId::class_lpi2c1, SignalId::signal_SDA, DirectionId::direction_bidirectional},
  {DeviceRefId::mimxrt1062, SignalEndpointId::mimxrt1062_endpoint_spi_pcs0, PeripheralClassId::class_spi, SignalId::signal_PCS0, DirectionId::none},
  {DeviceRefId::mimxrt1062, SignalEndpointId::mimxrt1062_endpoint_spi_sck, PeripheralClassId::class_spi, SignalId::signal_SCK, DirectionId::direction_output},
  {DeviceRefId::mimxrt1062, SignalEndpointId::mimxrt1062_endpoint_uart_rx, PeripheralClassId::class_uart, SignalId::signal_RX, DirectionId::direction_input},
  {DeviceRefId::mimxrt1062, SignalEndpointId::mimxrt1062_endpoint_uart_tx, PeripheralClassId::class_uart, SignalId::signal_TX, DirectionId::direction_output},
}};

enum class RouteRequirementId : std::uint16_t {
  none,
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
  DeviceRefId device_id;
  RouteRequirementId requirement_id;
  RequirementKindId kind_id;
  RuntimeRef target_ref;
  RuntimeRef value_ref;
  int value_int;
};
inline constexpr std::array<RouteRequirementDescriptor, 21> kRouteRequirements = {{
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_ad_b0_00, RequirementKindId::requirement_kind_bonded_pin, {RuntimeRefDomain::pin, 1u}, {RuntimeRefDomain::package, 1u}, -1},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_ad_b0_01, RequirementKindId::requirement_kind_bonded_pin, {RuntimeRefDomain::pin, 2u}, {RuntimeRefDomain::package, 1u}, -1},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_emc_00, RequirementKindId::requirement_kind_bonded_pin, {RuntimeRefDomain::pin, 3u}, {RuntimeRefDomain::package, 1u}, -1},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_bonded_pin_bga196_gpio_emc_01, RequirementKindId::requirement_kind_bonded_pin, {RuntimeRefDomain::pin, 4u}, {RuntimeRefDomain::package, 1u}, -1},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_clock_enable_gpio1, RequirementKindId::requirement_kind_clock_enable, {RuntimeRefDomain::clock_gate, 1u}, {RuntimeRefDomain::integer, 0u}, 1},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_clock_enable_gpio4, RequirementKindId::requirement_kind_clock_enable, {RuntimeRefDomain::clock_gate, 2u}, {RuntimeRefDomain::integer, 0u}, 1},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_clock_enable_lpi2c1, RequirementKindId::requirement_kind_clock_enable, {RuntimeRefDomain::clock_gate, 3u}, {RuntimeRefDomain::integer, 0u}, 1},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_clock_enable_lpspi1, RequirementKindId::requirement_kind_clock_enable, {RuntimeRefDomain::clock_gate, 4u}, {RuntimeRefDomain::integer, 0u}, 1},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_clock_enable_lpuart1, RequirementKindId::requirement_kind_clock_enable, {RuntimeRefDomain::clock_gate, 5u}, {RuntimeRefDomain::integer, 0u}, 1},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_clock_enable_lpuart3, RequirementKindId::requirement_kind_clock_enable, {RuntimeRefDomain::clock_gate, 6u}, {RuntimeRefDomain::integer, 0u}, 1},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_package_bga196, RequirementKindId::requirement_kind_package, {RuntimeRefDomain::package, 1u}, {RuntimeRefDomain::state, 1u}, -1},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_00_gpio1_io00, RequirementKindId::requirement_kind_source_select, {RuntimeRefDomain::pin, 1u}, {RuntimeRefDomain::selector, 3u}, 5},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_00_lpi2c1_scl, RequirementKindId::requirement_kind_source_select, {RuntimeRefDomain::pin, 1u}, {RuntimeRefDomain::selector, 1u}, 0},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_00_lpuart1_tx, RequirementKindId::requirement_kind_source_select, {RuntimeRefDomain::pin, 1u}, {RuntimeRefDomain::selector, 2u}, 2},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_01_gpio1_io01, RequirementKindId::requirement_kind_source_select, {RuntimeRefDomain::pin, 2u}, {RuntimeRefDomain::selector, 3u}, 5},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_01_lpi2c1_sda, RequirementKindId::requirement_kind_source_select, {RuntimeRefDomain::pin, 2u}, {RuntimeRefDomain::selector, 1u}, 0},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_ad_b0_01_lpuart1_rx, RequirementKindId::requirement_kind_source_select, {RuntimeRefDomain::pin, 2u}, {RuntimeRefDomain::selector, 2u}, 2},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_emc_00_gpio4_io00, RequirementKindId::requirement_kind_source_select, {RuntimeRefDomain::pin, 3u}, {RuntimeRefDomain::selector, 3u}, 5},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_emc_00_lpspi1_sck, RequirementKindId::requirement_kind_source_select, {RuntimeRefDomain::pin, 3u}, {RuntimeRefDomain::selector, 2u}, 2},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_emc_01_gpio4_io01, RequirementKindId::requirement_kind_source_select, {RuntimeRefDomain::pin, 4u}, {RuntimeRefDomain::selector, 3u}, 5},
  {DeviceRefId::mimxrt1062, RouteRequirementId::mimxrt1062_requirement_source_select_gpio_emc_01_lpspi1_pcs0, RequirementKindId::requirement_kind_source_select, {RuntimeRefDomain::pin, 4u}, {RuntimeRefDomain::selector, 2u}, 2},
}};

enum class RouteOperationId : std::uint16_t {
  none,
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
  DeviceRefId device_id;
  RouteOperationId operation_id;
  OperationKindId kind_id;
  BackendSchemaId schema_id;
  RuntimeRef subject_ref;
  RuntimeRef target_ref;
  RuntimeRef value_ref;
  RegisterRefId register_id;
  RegisterFieldRefId register_field_id;
  int value_int;
};
inline constexpr std::array<RouteOperationDescriptor, 16> kRouteOperations = {{
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_clock_enable_gpio1, OperationKindId::operation_kind_set_bit, BackendSchemaId::schema_alloy_clock_nxp_generic_clock_v1, {RuntimeRefDomain::peripheral, 1u}, {RuntimeRefDomain::clock_gate, 1u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::none, RegisterFieldRefId::none, 1},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_clock_enable_gpio4, OperationKindId::operation_kind_set_bit, BackendSchemaId::schema_alloy_clock_nxp_generic_clock_v1, {RuntimeRefDomain::peripheral, 2u}, {RuntimeRefDomain::clock_gate, 2u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::none, RegisterFieldRefId::none, 1},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_clock_enable_lpi2c1, OperationKindId::operation_kind_set_bit, BackendSchemaId::schema_alloy_clock_nxp_generic_clock_v1, {RuntimeRefDomain::peripheral, 3u}, {RuntimeRefDomain::clock_gate, 3u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::none, RegisterFieldRefId::none, 1},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_clock_enable_lpspi1, OperationKindId::operation_kind_set_bit, BackendSchemaId::schema_alloy_clock_nxp_generic_clock_v1, {RuntimeRefDomain::peripheral, 4u}, {RuntimeRefDomain::clock_gate, 4u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::none, RegisterFieldRefId::none, 1},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_clock_enable_lpuart1, OperationKindId::operation_kind_set_bit, BackendSchemaId::schema_alloy_clock_nxp_generic_clock_v1, {RuntimeRefDomain::peripheral, 5u}, {RuntimeRefDomain::clock_gate, 5u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::none, RegisterFieldRefId::none, 1},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_clock_enable_lpuart3, OperationKindId::operation_kind_set_bit, BackendSchemaId::schema_alloy_clock_nxp_generic_clock_v1, {RuntimeRefDomain::peripheral, 6u}, {RuntimeRefDomain::clock_gate, 6u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::none, RegisterFieldRefId::none, 1},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_00_gpio1_io00, OperationKindId::operation_kind_write_selector, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, {RuntimeRefDomain::pin, 1u}, {RuntimeRefDomain::pin, 1u}, {RuntimeRefDomain::selector, 3u}, RegisterRefId::none, RegisterFieldRefId::none, 5},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_00_lpi2c1_scl, OperationKindId::operation_kind_write_selector, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, {RuntimeRefDomain::pin, 1u}, {RuntimeRefDomain::pin, 1u}, {RuntimeRefDomain::selector, 1u}, RegisterRefId::none, RegisterFieldRefId::none, 0},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_00_lpuart1_tx, OperationKindId::operation_kind_write_selector, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, {RuntimeRefDomain::pin, 1u}, {RuntimeRefDomain::pin, 1u}, {RuntimeRefDomain::selector, 2u}, RegisterRefId::none, RegisterFieldRefId::none, 2},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_01_gpio1_io01, OperationKindId::operation_kind_write_selector, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, {RuntimeRefDomain::pin, 2u}, {RuntimeRefDomain::pin, 2u}, {RuntimeRefDomain::selector, 3u}, RegisterRefId::none, RegisterFieldRefId::none, 5},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_01_lpi2c1_sda, OperationKindId::operation_kind_write_selector, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, {RuntimeRefDomain::pin, 2u}, {RuntimeRefDomain::pin, 2u}, {RuntimeRefDomain::selector, 1u}, RegisterRefId::none, RegisterFieldRefId::none, 0},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_route_gpio_ad_b0_01_lpuart1_rx, OperationKindId::operation_kind_write_selector, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, {RuntimeRefDomain::pin, 2u}, {RuntimeRefDomain::pin, 2u}, {RuntimeRefDomain::selector, 2u}, RegisterRefId::none, RegisterFieldRefId::none, 2},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_route_gpio_emc_00_gpio4_io00, OperationKindId::operation_kind_write_selector, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, {RuntimeRefDomain::pin, 3u}, {RuntimeRefDomain::pin, 3u}, {RuntimeRefDomain::selector, 3u}, RegisterRefId::none, RegisterFieldRefId::none, 5},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_route_gpio_emc_00_lpspi1_sck, OperationKindId::operation_kind_write_selector, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, {RuntimeRefDomain::pin, 3u}, {RuntimeRefDomain::pin, 3u}, {RuntimeRefDomain::selector, 2u}, RegisterRefId::none, RegisterFieldRefId::none, 2},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_route_gpio_emc_01_gpio4_io01, OperationKindId::operation_kind_write_selector, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, {RuntimeRefDomain::pin, 4u}, {RuntimeRefDomain::pin, 4u}, {RuntimeRefDomain::selector, 3u}, RegisterRefId::none, RegisterFieldRefId::none, 5},
  {DeviceRefId::mimxrt1062, RouteOperationId::mimxrt1062_operation_route_gpio_emc_01_lpspi1_pcs0, OperationKindId::operation_kind_write_selector, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, {RuntimeRefDomain::pin, 4u}, {RuntimeRefDomain::pin, 4u}, {RuntimeRefDomain::selector, 2u}, RegisterRefId::none, RegisterFieldRefId::none, 2},
}};

enum class ConnectionCandidateId : std::uint16_t {
  none,
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

enum class ConnectionConflictGroupId : std::uint16_t {
  none,
  conflict_gpio1_bga196_all_signals,
  conflict_gpio4_bga196_all_signals,
  conflict_lpi2c1_bga196_all_signals,
  conflict_lpspi1_bga196_sck_cs,
  conflict_lpuart1_bga196_tx_rx,
};

enum class ConnectionGroupId : std::uint16_t {
  none,
  mimxrt1062_group_gpio1_bga196_all_signals,
  mimxrt1062_group_gpio4_bga196_all_signals,
  mimxrt1062_group_lpi2c1_bga196_all_signals,
  mimxrt1062_group_lpspi1_bga196_sck_cs,
  mimxrt1062_group_lpuart1_bga196_tx_rx,
};

struct ConnectionCandidateDescriptor {
  DeviceRefId device_id;
  ConnectionCandidateId candidate_id;
  PinRefId pin_id;
  PeripheralRefId peripheral_id;
  SignalId signal_id;
  RouteKindId route_kind_id;
  SelectorRefId route_selector_id;
  ConnectionGroupId route_group_id;
  std::uint16_t requirement_offset;
  std::uint16_t requirement_count;
  std::uint16_t operation_offset;
  std::uint16_t operation_count;
  std::uint16_t capability_offset;
  std::uint16_t capability_count;
};
inline constexpr std::array<ConnectionCandidateDescriptor, 10> kConnectionCandidates = {{
  {DeviceRefId::mimxrt1062, ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_gpio1_io00, PinRefId::mimxrt1062_GPIO_AD_B0_00, PeripheralRefId::mimxrt1062_GPIO1, SignalId::signal_io00, RouteKindId::route_kind_iomuxc_mux, SelectorRefId::mimxrt1062_selector_5, ConnectionGroupId::mimxrt1062_group_gpio1_bga196_all_signals, 0u, 4u, 0u, 2u, 0u, 2u},
  {DeviceRefId::mimxrt1062, ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpi2c1_scl, PinRefId::mimxrt1062_GPIO_AD_B0_00, PeripheralRefId::mimxrt1062_LPI2C1, SignalId::signal_scl, RouteKindId::route_kind_iomuxc_mux, SelectorRefId::mimxrt1062_selector_0, ConnectionGroupId::mimxrt1062_group_lpi2c1_bga196_all_signals, 4u, 4u, 2u, 2u, 2u, 2u},
  {DeviceRefId::mimxrt1062, ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpuart1_tx, PinRefId::mimxrt1062_GPIO_AD_B0_00, PeripheralRefId::mimxrt1062_LPUART1, SignalId::signal_tx, RouteKindId::route_kind_iomuxc_mux, SelectorRefId::mimxrt1062_selector_2, ConnectionGroupId::mimxrt1062_group_lpuart1_bga196_tx_rx, 8u, 4u, 4u, 2u, 4u, 2u},
  {DeviceRefId::mimxrt1062, ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_gpio1_io01, PinRefId::mimxrt1062_GPIO_AD_B0_01, PeripheralRefId::mimxrt1062_GPIO1, SignalId::signal_io01, RouteKindId::route_kind_iomuxc_mux, SelectorRefId::mimxrt1062_selector_5, ConnectionGroupId::mimxrt1062_group_gpio1_bga196_all_signals, 12u, 4u, 6u, 2u, 6u, 2u},
  {DeviceRefId::mimxrt1062, ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpi2c1_sda, PinRefId::mimxrt1062_GPIO_AD_B0_01, PeripheralRefId::mimxrt1062_LPI2C1, SignalId::signal_sda, RouteKindId::route_kind_iomuxc_mux, SelectorRefId::mimxrt1062_selector_0, ConnectionGroupId::mimxrt1062_group_lpi2c1_bga196_all_signals, 16u, 4u, 8u, 2u, 8u, 2u},
  {DeviceRefId::mimxrt1062, ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpuart1_rx, PinRefId::mimxrt1062_GPIO_AD_B0_01, PeripheralRefId::mimxrt1062_LPUART1, SignalId::signal_rx, RouteKindId::route_kind_iomuxc_mux, SelectorRefId::mimxrt1062_selector_2, ConnectionGroupId::mimxrt1062_group_lpuart1_bga196_tx_rx, 20u, 4u, 10u, 2u, 10u, 2u},
  {DeviceRefId::mimxrt1062, ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_gpio4_io00, PinRefId::mimxrt1062_GPIO_EMC_00, PeripheralRefId::mimxrt1062_GPIO4, SignalId::signal_io00, RouteKindId::route_kind_iomuxc_mux, SelectorRefId::mimxrt1062_selector_5, ConnectionGroupId::mimxrt1062_group_gpio4_bga196_all_signals, 24u, 4u, 12u, 2u, 12u, 2u},
  {DeviceRefId::mimxrt1062, ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_lpspi1_sck, PinRefId::mimxrt1062_GPIO_EMC_00, PeripheralRefId::mimxrt1062_LPSPI1, SignalId::signal_sck, RouteKindId::route_kind_iomuxc_mux, SelectorRefId::mimxrt1062_selector_2, ConnectionGroupId::mimxrt1062_group_lpspi1_bga196_sck_cs, 28u, 4u, 14u, 2u, 14u, 2u},
  {DeviceRefId::mimxrt1062, ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_gpio4_io01, PinRefId::mimxrt1062_GPIO_EMC_01, PeripheralRefId::mimxrt1062_GPIO4, SignalId::signal_io01, RouteKindId::route_kind_iomuxc_mux, SelectorRefId::mimxrt1062_selector_5, ConnectionGroupId::mimxrt1062_group_gpio4_bga196_all_signals, 32u, 4u, 16u, 2u, 16u, 2u},
  {DeviceRefId::mimxrt1062, ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_lpspi1_pcs0, PinRefId::mimxrt1062_GPIO_EMC_01, PeripheralRefId::mimxrt1062_LPSPI1, SignalId::signal_pcs0, RouteKindId::route_kind_iomuxc_mux, SelectorRefId::mimxrt1062_selector_2, ConnectionGroupId::mimxrt1062_group_lpspi1_bga196_sck_cs, 36u, 4u, 18u, 2u, 18u, 2u},
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
  CapabilityRefId capability_id;
};
inline constexpr std::array<CandidateCapabilityRef, 20> kCandidateCapabilityRefs = {{
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_gpio1_io00, CapabilityRefId::mimxrt1062_capability_gpio_imxrt_gpio_v1_io00},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_gpio1_io00, CapabilityRefId::mimxrt1062_capability_instance_gpio1_bga196_io00},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpi2c1_scl, CapabilityRefId::mimxrt1062_capability_lpi2c1_lpi2c_v1_scl},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpi2c1_scl, CapabilityRefId::mimxrt1062_capability_instance_lpi2c1_bga196_scl},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpuart1_tx, CapabilityRefId::mimxrt1062_capability_lpuart_lpuart_v1_tx},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_00_lpuart1_tx, CapabilityRefId::mimxrt1062_capability_instance_lpuart1_bga196_tx},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_gpio1_io01, CapabilityRefId::mimxrt1062_capability_gpio_imxrt_gpio_v1_io01},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_gpio1_io01, CapabilityRefId::mimxrt1062_capability_instance_gpio1_bga196_io01},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpi2c1_sda, CapabilityRefId::mimxrt1062_capability_lpi2c1_lpi2c_v1_sda},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpi2c1_sda, CapabilityRefId::mimxrt1062_capability_instance_lpi2c1_bga196_sda},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpuart1_rx, CapabilityRefId::mimxrt1062_capability_lpuart_lpuart_v1_rx},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_ad_b0_01_lpuart1_rx, CapabilityRefId::mimxrt1062_capability_instance_lpuart1_bga196_rx},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_gpio4_io00, CapabilityRefId::mimxrt1062_capability_gpio_imxrt_gpio_v1_io00},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_gpio4_io00, CapabilityRefId::mimxrt1062_capability_instance_gpio4_bga196_io00},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_lpspi1_sck, CapabilityRefId::mimxrt1062_capability_lpspi_lpspi_v1_sck},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_00_lpspi1_sck, CapabilityRefId::mimxrt1062_capability_instance_lpspi1_bga196_sck},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_gpio4_io01, CapabilityRefId::mimxrt1062_capability_gpio_imxrt_gpio_v1_io01},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_gpio4_io01, CapabilityRefId::mimxrt1062_capability_instance_gpio4_bga196_io01},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_lpspi1_pcs0, CapabilityRefId::mimxrt1062_capability_lpspi_lpspi_v1_cs},
  {ConnectionCandidateId::mimxrt1062_candidate_gpio_emc_01_lpspi1_pcs0, CapabilityRefId::mimxrt1062_capability_instance_lpspi1_bga196_cs},
}};

struct ConnectionGroupDescriptor {
  DeviceRefId device_id;
  ConnectionGroupId group_id;
  PeripheralRefId peripheral_id;
  PackageRefId package_id;
  ConnectionConflictGroupId conflict_group_id;
  std::uint16_t signal_offset;
  std::uint16_t signal_count;
  std::uint16_t candidate_offset;
  std::uint16_t candidate_count;
};
inline constexpr std::array<ConnectionGroupDescriptor, 5> kConnectionGroups = {{
  {DeviceRefId::mimxrt1062, ConnectionGroupId::mimxrt1062_group_gpio1_bga196_all_signals, PeripheralRefId::mimxrt1062_GPIO1, PackageRefId::mimxrt1062_bga196, ConnectionConflictGroupId::conflict_gpio1_bga196_all_signals, 0u, 2u, 0u, 2u},
  {DeviceRefId::mimxrt1062, ConnectionGroupId::mimxrt1062_group_gpio4_bga196_all_signals, PeripheralRefId::mimxrt1062_GPIO4, PackageRefId::mimxrt1062_bga196, ConnectionConflictGroupId::conflict_gpio4_bga196_all_signals, 2u, 2u, 2u, 2u},
  {DeviceRefId::mimxrt1062, ConnectionGroupId::mimxrt1062_group_lpi2c1_bga196_all_signals, PeripheralRefId::mimxrt1062_LPI2C1, PackageRefId::mimxrt1062_bga196, ConnectionConflictGroupId::conflict_lpi2c1_bga196_all_signals, 4u, 2u, 4u, 2u},
  {DeviceRefId::mimxrt1062, ConnectionGroupId::mimxrt1062_group_lpspi1_bga196_sck_cs, PeripheralRefId::mimxrt1062_LPSPI1, PackageRefId::mimxrt1062_bga196, ConnectionConflictGroupId::conflict_lpspi1_bga196_sck_cs, 6u, 2u, 6u, 2u},
  {DeviceRefId::mimxrt1062, ConnectionGroupId::mimxrt1062_group_lpuart1_bga196_tx_rx, PeripheralRefId::mimxrt1062_LPUART1, PackageRefId::mimxrt1062_bga196, ConnectionConflictGroupId::conflict_lpuart1_bga196_tx_rx, 8u, 2u, 8u, 2u},
}};

struct ConnectionGroupSignalRef {
  ConnectionGroupId group_id;
  SignalId signal_id;
};
inline constexpr std::array<ConnectionGroupSignalRef, 10> kConnectionGroupSignals = {{
  {ConnectionGroupId::mimxrt1062_group_gpio1_bga196_all_signals, SignalId::signal_io00},
  {ConnectionGroupId::mimxrt1062_group_gpio1_bga196_all_signals, SignalId::signal_io01},
  {ConnectionGroupId::mimxrt1062_group_gpio4_bga196_all_signals, SignalId::signal_io00},
  {ConnectionGroupId::mimxrt1062_group_gpio4_bga196_all_signals, SignalId::signal_io01},
  {ConnectionGroupId::mimxrt1062_group_lpi2c1_bga196_all_signals, SignalId::signal_scl},
  {ConnectionGroupId::mimxrt1062_group_lpi2c1_bga196_all_signals, SignalId::signal_sda},
  {ConnectionGroupId::mimxrt1062_group_lpspi1_bga196_sck_cs, SignalId::signal_sck},
  {ConnectionGroupId::mimxrt1062_group_lpspi1_bga196_sck_cs, SignalId::signal_cs},
  {ConnectionGroupId::mimxrt1062_group_lpuart1_bga196_tx_rx, SignalId::signal_tx},
  {ConnectionGroupId::mimxrt1062_group_lpuart1_bga196_tx_rx, SignalId::signal_rx},
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
