#pragma once

#include <array>
#include <cstdint>
#include "runtime_refs.hpp"
#include "runtime_semantics.hpp"

namespace st {
namespace stm32g0 {
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
  stm32g071rb_endpoint_gpio_in0,
  stm32g071rb_endpoint_gpio_in1,
  stm32g071rb_endpoint_gpio_in2,
  stm32g071rb_endpoint_gpio_in3,
  stm32g071rb_endpoint_gpio_in6,
  stm32g071rb_endpoint_gpio_in7,
  stm32g071rb_endpoint_uart_rx,
  stm32g071rb_endpoint_uart_tx,
};

struct SignalEndpointDescriptor {
  DeviceRefId device_id;
  SignalEndpointId endpoint_id;
  PeripheralClassId peripheral_class_id;
  SignalId signal_id;
  DirectionId direction_id;
};
inline constexpr std::array<SignalEndpointDescriptor, 8> kSignalEndpoints = {{
  {DeviceRefId::stm32g071rb, SignalEndpointId::stm32g071rb_endpoint_gpio_in0, PeripheralClassId::class_gpio, SignalId::signal_IN0, DirectionId::none},
  {DeviceRefId::stm32g071rb, SignalEndpointId::stm32g071rb_endpoint_gpio_in1, PeripheralClassId::class_gpio, SignalId::signal_IN1, DirectionId::none},
  {DeviceRefId::stm32g071rb, SignalEndpointId::stm32g071rb_endpoint_gpio_in2, PeripheralClassId::class_gpio, SignalId::signal_IN2, DirectionId::none},
  {DeviceRefId::stm32g071rb, SignalEndpointId::stm32g071rb_endpoint_gpio_in3, PeripheralClassId::class_gpio, SignalId::signal_IN3, DirectionId::none},
  {DeviceRefId::stm32g071rb, SignalEndpointId::stm32g071rb_endpoint_gpio_in6, PeripheralClassId::class_gpio, SignalId::signal_IN6, DirectionId::none},
  {DeviceRefId::stm32g071rb, SignalEndpointId::stm32g071rb_endpoint_gpio_in7, PeripheralClassId::class_gpio, SignalId::signal_IN7, DirectionId::none},
  {DeviceRefId::stm32g071rb, SignalEndpointId::stm32g071rb_endpoint_uart_rx, PeripheralClassId::class_uart, SignalId::signal_RX, DirectionId::direction_input},
  {DeviceRefId::stm32g071rb, SignalEndpointId::stm32g071rb_endpoint_uart_tx, PeripheralClassId::class_uart, SignalId::signal_TX, DirectionId::direction_output},
}};

enum class RouteRequirementId : std::uint16_t {
  none,
  stm32g071rb_requirement_bonded_pin_lqfp64_pb6,
  stm32g071rb_requirement_bonded_pin_lqfp64_pb7,
  stm32g071rb_requirement_clock_enable_dma1,
  stm32g071rb_requirement_clock_enable_dmamux1,
  stm32g071rb_requirement_clock_enable_gpioa,
  stm32g071rb_requirement_clock_enable_gpiob,
  stm32g071rb_requirement_clock_enable_usart1,
  stm32g071rb_requirement_package_lqfp64,
  stm32g071rb_requirement_reset_release_dma1,
  stm32g071rb_requirement_reset_release_dmamux1,
  stm32g071rb_requirement_reset_release_gpioa,
  stm32g071rb_requirement_reset_release_gpiob,
  stm32g071rb_requirement_reset_release_usart1,
  stm32g071rb_requirement_source_select_pb6_usart1_tx,
  stm32g071rb_requirement_source_select_pb7_usart1_rx,
};

struct RouteRequirementDescriptor {
  DeviceRefId device_id;
  RouteRequirementId requirement_id;
  RequirementKindId kind_id;
  RuntimeRef target_ref;
  RuntimeRef value_ref;
  int value_int;
};
inline constexpr std::array<RouteRequirementDescriptor, 15> kRouteRequirements = {{
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_bonded_pin_lqfp64_pb6, RequirementKindId::requirement_kind_bonded_pin, {RuntimeRefDomain::pin, 5u}, {RuntimeRefDomain::package, 1u}, -1},
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_bonded_pin_lqfp64_pb7, RequirementKindId::requirement_kind_bonded_pin, {RuntimeRefDomain::pin, 6u}, {RuntimeRefDomain::package, 1u}, -1},
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_clock_enable_dma1, RequirementKindId::requirement_kind_clock_enable, {RuntimeRefDomain::clock_gate, 1u}, {RuntimeRefDomain::integer, 0u}, 1},
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_clock_enable_dmamux1, RequirementKindId::requirement_kind_clock_enable, {RuntimeRefDomain::clock_gate, 2u}, {RuntimeRefDomain::integer, 0u}, 1},
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_clock_enable_gpioa, RequirementKindId::requirement_kind_clock_enable, {RuntimeRefDomain::clock_gate, 3u}, {RuntimeRefDomain::integer, 0u}, 1},
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_clock_enable_gpiob, RequirementKindId::requirement_kind_clock_enable, {RuntimeRefDomain::clock_gate, 4u}, {RuntimeRefDomain::integer, 0u}, 1},
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_clock_enable_usart1, RequirementKindId::requirement_kind_clock_enable, {RuntimeRefDomain::clock_gate, 5u}, {RuntimeRefDomain::integer, 0u}, 1},
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_package_lqfp64, RequirementKindId::requirement_kind_package, {RuntimeRefDomain::package, 1u}, {RuntimeRefDomain::state, 1u}, -1},
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_reset_release_dma1, RequirementKindId::requirement_kind_reset_release, {RuntimeRefDomain::reset, 1u}, {RuntimeRefDomain::integer, 0u}, 0},
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_reset_release_dmamux1, RequirementKindId::requirement_kind_reset_release, {RuntimeRefDomain::reset, 2u}, {RuntimeRefDomain::integer, 0u}, 0},
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_reset_release_gpioa, RequirementKindId::requirement_kind_reset_release, {RuntimeRefDomain::reset, 3u}, {RuntimeRefDomain::integer, 0u}, 0},
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_reset_release_gpiob, RequirementKindId::requirement_kind_reset_release, {RuntimeRefDomain::reset, 4u}, {RuntimeRefDomain::integer, 0u}, 0},
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_reset_release_usart1, RequirementKindId::requirement_kind_reset_release, {RuntimeRefDomain::reset, 5u}, {RuntimeRefDomain::integer, 0u}, 0},
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_source_select_pb6_usart1_tx, RequirementKindId::requirement_kind_source_select, {RuntimeRefDomain::pin, 5u}, {RuntimeRefDomain::selector, 1u}, 0},
  {DeviceRefId::stm32g071rb, RouteRequirementId::stm32g071rb_requirement_source_select_pb7_usart1_rx, RequirementKindId::requirement_kind_source_select, {RuntimeRefDomain::pin, 6u}, {RuntimeRefDomain::selector, 1u}, 0},
}};

enum class RouteOperationId : std::uint16_t {
  none,
  stm32g071rb_operation_clock_enable_dma1,
  stm32g071rb_operation_clock_enable_dmamux1,
  stm32g071rb_operation_clock_enable_gpioa,
  stm32g071rb_operation_clock_enable_gpiob,
  stm32g071rb_operation_clock_enable_usart1,
  stm32g071rb_operation_reset_release_dma1,
  stm32g071rb_operation_reset_release_dmamux1,
  stm32g071rb_operation_reset_release_gpioa,
  stm32g071rb_operation_reset_release_gpiob,
  stm32g071rb_operation_reset_release_usart1,
  stm32g071rb_operation_route_pb6_usart1_tx,
  stm32g071rb_operation_route_pb7_usart1_rx,
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
inline constexpr std::array<RouteOperationDescriptor, 12> kRouteOperations = {{
  {DeviceRefId::stm32g071rb, RouteOperationId::stm32g071rb_operation_clock_enable_dma1, OperationKindId::operation_kind_set_bit, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, {RuntimeRefDomain::peripheral, 1u}, {RuntimeRefDomain::clock_gate, 1u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::stm32g071rb_register_rcc_ahbenr, RegisterFieldRefId::none, 1},
  {DeviceRefId::stm32g071rb, RouteOperationId::stm32g071rb_operation_clock_enable_dmamux1, OperationKindId::operation_kind_set_bit, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, {RuntimeRefDomain::peripheral, 2u}, {RuntimeRefDomain::clock_gate, 2u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::stm32g071rb_register_rcc_ahbenr, RegisterFieldRefId::none, 1},
  {DeviceRefId::stm32g071rb, RouteOperationId::stm32g071rb_operation_clock_enable_gpioa, OperationKindId::operation_kind_set_bit, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, {RuntimeRefDomain::peripheral, 3u}, {RuntimeRefDomain::clock_gate, 3u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::stm32g071rb_register_rcc_iopenr, RegisterFieldRefId::none, 1},
  {DeviceRefId::stm32g071rb, RouteOperationId::stm32g071rb_operation_clock_enable_gpiob, OperationKindId::operation_kind_set_bit, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, {RuntimeRefDomain::peripheral, 4u}, {RuntimeRefDomain::clock_gate, 4u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::stm32g071rb_register_rcc_iopenr, RegisterFieldRefId::none, 1},
  {DeviceRefId::stm32g071rb, RouteOperationId::stm32g071rb_operation_clock_enable_usart1, OperationKindId::operation_kind_set_bit, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, {RuntimeRefDomain::peripheral, 6u}, {RuntimeRefDomain::clock_gate, 5u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::stm32g071rb_register_rcc_apbenr2, RegisterFieldRefId::none, 1},
  {DeviceRefId::stm32g071rb, RouteOperationId::stm32g071rb_operation_reset_release_dma1, OperationKindId::operation_kind_clear_bit, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, {RuntimeRefDomain::peripheral, 1u}, {RuntimeRefDomain::reset, 1u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::stm32g071rb_register_rcc_ahbrstr, RegisterFieldRefId::none, 0},
  {DeviceRefId::stm32g071rb, RouteOperationId::stm32g071rb_operation_reset_release_dmamux1, OperationKindId::operation_kind_clear_bit, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, {RuntimeRefDomain::peripheral, 2u}, {RuntimeRefDomain::reset, 2u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::stm32g071rb_register_rcc_ahbrstr, RegisterFieldRefId::none, 0},
  {DeviceRefId::stm32g071rb, RouteOperationId::stm32g071rb_operation_reset_release_gpioa, OperationKindId::operation_kind_clear_bit, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, {RuntimeRefDomain::peripheral, 3u}, {RuntimeRefDomain::reset, 3u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::stm32g071rb_register_rcc_ioprstr, RegisterFieldRefId::none, 0},
  {DeviceRefId::stm32g071rb, RouteOperationId::stm32g071rb_operation_reset_release_gpiob, OperationKindId::operation_kind_clear_bit, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, {RuntimeRefDomain::peripheral, 4u}, {RuntimeRefDomain::reset, 4u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::stm32g071rb_register_rcc_ioprstr, RegisterFieldRefId::none, 0},
  {DeviceRefId::stm32g071rb, RouteOperationId::stm32g071rb_operation_reset_release_usart1, OperationKindId::operation_kind_clear_bit, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, {RuntimeRefDomain::peripheral, 6u}, {RuntimeRefDomain::reset, 5u}, {RuntimeRefDomain::integer, 0u}, RegisterRefId::stm32g071rb_register_rcc_apbrstr2, RegisterFieldRefId::none, 0},
  {DeviceRefId::stm32g071rb, RouteOperationId::stm32g071rb_operation_route_pb6_usart1_tx, OperationKindId::operation_kind_write_selector, BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, {RuntimeRefDomain::pin, 5u}, {RuntimeRefDomain::pin, 5u}, {RuntimeRefDomain::selector, 1u}, RegisterRefId::none, RegisterFieldRefId::none, 0},
  {DeviceRefId::stm32g071rb, RouteOperationId::stm32g071rb_operation_route_pb7_usart1_rx, OperationKindId::operation_kind_write_selector, BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, {RuntimeRefDomain::pin, 6u}, {RuntimeRefDomain::pin, 6u}, {RuntimeRefDomain::selector, 1u}, RegisterRefId::none, RegisterFieldRefId::none, 0},
}};

enum class ConnectionCandidateId : std::uint16_t {
  none,
  stm32g071rb_candidate_pb6_usart1_tx,
  stm32g071rb_candidate_pb7_usart1_rx,
};

enum class ConnectionConflictGroupId : std::uint16_t {
  none,
  conflict_usart1_lqfp64_tx_rx,
};

enum class ConnectionGroupId : std::uint16_t {
  none,
  stm32g071rb_group_usart1_lqfp64_tx_rx,
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
inline constexpr std::array<ConnectionCandidateDescriptor, 2> kConnectionCandidates = {{
  {DeviceRefId::stm32g071rb, ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx, PinRefId::stm32g071rb_PB6, PeripheralRefId::stm32g071rb_USART1, SignalId::signal_tx, RouteKindId::route_kind_alternate_function, SelectorRefId::stm32g071rb_selector_0, ConnectionGroupId::stm32g071rb_group_usart1_lqfp64_tx_rx, 0u, 5u, 0u, 3u, 0u, 2u},
  {DeviceRefId::stm32g071rb, ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx, PinRefId::stm32g071rb_PB7, PeripheralRefId::stm32g071rb_USART1, SignalId::signal_rx, RouteKindId::route_kind_alternate_function, SelectorRefId::stm32g071rb_selector_0, ConnectionGroupId::stm32g071rb_group_usart1_lqfp64_tx_rx, 5u, 5u, 3u, 3u, 2u, 2u},
}};

struct CandidateRequirementRef {
  ConnectionCandidateId candidate_id;
  RouteRequirementId requirement_id;
};
inline constexpr std::array<CandidateRequirementRef, 10> kCandidateRequirementRefs = {{
  {ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx, RouteRequirementId::stm32g071rb_requirement_package_lqfp64},
  {ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx, RouteRequirementId::stm32g071rb_requirement_bonded_pin_lqfp64_pb6},
  {ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx, RouteRequirementId::stm32g071rb_requirement_clock_enable_usart1},
  {ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx, RouteRequirementId::stm32g071rb_requirement_reset_release_usart1},
  {ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx, RouteRequirementId::stm32g071rb_requirement_source_select_pb6_usart1_tx},
  {ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx, RouteRequirementId::stm32g071rb_requirement_package_lqfp64},
  {ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx, RouteRequirementId::stm32g071rb_requirement_bonded_pin_lqfp64_pb7},
  {ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx, RouteRequirementId::stm32g071rb_requirement_clock_enable_usart1},
  {ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx, RouteRequirementId::stm32g071rb_requirement_reset_release_usart1},
  {ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx, RouteRequirementId::stm32g071rb_requirement_source_select_pb7_usart1_rx},
}};

struct CandidateOperationRef {
  ConnectionCandidateId candidate_id;
  RouteOperationId operation_id;
};
inline constexpr std::array<CandidateOperationRef, 6> kCandidateOperationRefs = {{
  {ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx, RouteOperationId::stm32g071rb_operation_clock_enable_usart1},
  {ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx, RouteOperationId::stm32g071rb_operation_reset_release_usart1},
  {ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx, RouteOperationId::stm32g071rb_operation_route_pb6_usart1_tx},
  {ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx, RouteOperationId::stm32g071rb_operation_clock_enable_usart1},
  {ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx, RouteOperationId::stm32g071rb_operation_reset_release_usart1},
  {ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx, RouteOperationId::stm32g071rb_operation_route_pb7_usart1_rx},
}};

struct CandidateCapabilityRef {
  ConnectionCandidateId candidate_id;
  CapabilityRefId capability_id;
};
inline constexpr std::array<CandidateCapabilityRef, 4> kCandidateCapabilityRefs = {{
  {ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx, CapabilityRefId::stm32g071rb_capability_usart_usart_v3_1_tx},
  {ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx, CapabilityRefId::stm32g071rb_capability_instance_usart1_lqfp64_tx},
  {ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx, CapabilityRefId::stm32g071rb_capability_usart_usart_v3_1_rx},
  {ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx, CapabilityRefId::stm32g071rb_capability_instance_usart1_lqfp64_rx},
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
inline constexpr std::array<ConnectionGroupDescriptor, 1> kConnectionGroups = {{
  {DeviceRefId::stm32g071rb, ConnectionGroupId::stm32g071rb_group_usart1_lqfp64_tx_rx, PeripheralRefId::stm32g071rb_USART1, PackageRefId::stm32g071rb_lqfp64, ConnectionConflictGroupId::conflict_usart1_lqfp64_tx_rx, 0u, 2u, 0u, 2u},
}};

struct ConnectionGroupSignalRef {
  ConnectionGroupId group_id;
  SignalId signal_id;
};
inline constexpr std::array<ConnectionGroupSignalRef, 2> kConnectionGroupSignals = {{
  {ConnectionGroupId::stm32g071rb_group_usart1_lqfp64_tx_rx, SignalId::signal_tx},
  {ConnectionGroupId::stm32g071rb_group_usart1_lqfp64_tx_rx, SignalId::signal_rx},
}};

struct ConnectionGroupCandidateRef {
  ConnectionGroupId group_id;
  ConnectionCandidateId candidate_id;
};
inline constexpr std::array<ConnectionGroupCandidateRef, 2> kConnectionGroupCandidateRefs = {{
  {ConnectionGroupId::stm32g071rb_group_usart1_lqfp64_tx_rx, ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx},
  {ConnectionGroupId::stm32g071rb_group_usart1_lqfp64_tx_rx, ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx},
}};
}
}
}
