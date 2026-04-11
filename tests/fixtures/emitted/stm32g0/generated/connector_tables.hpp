#pragma once

#include <array>
#include <cstdint>

namespace st {
namespace stm32g0 {
namespace generated {
enum class RuntimeRefKind : std::uint8_t {
  none,
  package,
  state,
  pin,
  constraint,
  selector,
  clock_gate,
  reset,
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
  {"stm32g071rb", "endpoint:gpio:in0", "gpio", "IN0", nullptr},
  {"stm32g071rb", "endpoint:gpio:in1", "gpio", "IN1", nullptr},
  {"stm32g071rb", "endpoint:gpio:in2", "gpio", "IN2", nullptr},
  {"stm32g071rb", "endpoint:gpio:in3", "gpio", "IN3", nullptr},
  {"stm32g071rb", "endpoint:gpio:in6", "gpio", "IN6", nullptr},
  {"stm32g071rb", "endpoint:gpio:in7", "gpio", "IN7", nullptr},
  {"stm32g071rb", "endpoint:uart:rx", "uart", "RX", "input"},
  {"stm32g071rb", "endpoint:uart:tx", "uart", "TX", "output"},
};

enum class RouteRequirementId : std::uint16_t {
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
  const char* device;
  RouteRequirementId requirement_id;
  const char* requirement_name;
  const char* kind;
  RuntimeRefKind target_ref_kind;
  const char* target_ref_id;
  RuntimeRefKind value_ref_kind;
  const char* value_ref_id;
  int value_int;
  const char* diagnostic_target;
  const char* diagnostic_value;
};
inline constexpr std::array<RouteRequirementDescriptor, 15> kRouteRequirements = {{
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_bonded_pin_lqfp64_pb6, "requirement:bonded-pin:lqfp64:pb6", "bonded-pin", RuntimeRefKind::pin, "PB6", RuntimeRefKind::package, "lqfp64", -1, "PB6", "lqfp64"},
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_bonded_pin_lqfp64_pb7, "requirement:bonded-pin:lqfp64:pb7", "bonded-pin", RuntimeRefKind::pin, "PB7", RuntimeRefKind::package, "lqfp64", -1, "PB7", "lqfp64"},
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_clock_enable_dma1, "requirement:clock-enable:dma1", "clock-enable", RuntimeRefKind::clock_gate, "gate:dma1", RuntimeRefKind::integer, nullptr, 1, "RCC_AHBENR.DMA1EN", "1"},
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_clock_enable_dmamux1, "requirement:clock-enable:dmamux1", "clock-enable", RuntimeRefKind::clock_gate, "gate:dmamux1", RuntimeRefKind::integer, nullptr, 1, "RCC_AHBENR.DMAMUX1EN", "1"},
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_clock_enable_gpioa, "requirement:clock-enable:gpioa", "clock-enable", RuntimeRefKind::clock_gate, "gate:gpioa", RuntimeRefKind::integer, nullptr, 1, "RCC_IOPENR.GPIOAEN", "1"},
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_clock_enable_gpiob, "requirement:clock-enable:gpiob", "clock-enable", RuntimeRefKind::clock_gate, "gate:gpiob", RuntimeRefKind::integer, nullptr, 1, "RCC_IOPENR.GPIOBEN", "1"},
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_clock_enable_usart1, "requirement:clock-enable:usart1", "clock-enable", RuntimeRefKind::clock_gate, "gate:usart1", RuntimeRefKind::integer, nullptr, 1, "RCC_APBENR2.USART1EN", "1"},
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_package_lqfp64, "requirement:package:lqfp64", "package", RuntimeRefKind::package, "lqfp64", RuntimeRefKind::state, "selected", -1, "lqfp64", "selected"},
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_reset_release_dma1, "requirement:reset-release:dma1", "reset-release", RuntimeRefKind::reset, "reset:dma1", RuntimeRefKind::integer, nullptr, 0, "RCC_AHBRSTR.DMA1RST", "0"},
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_reset_release_dmamux1, "requirement:reset-release:dmamux1", "reset-release", RuntimeRefKind::reset, "reset:dmamux1", RuntimeRefKind::integer, nullptr, 0, "RCC_AHBRSTR.DMAMUX1RST", "0"},
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_reset_release_gpioa, "requirement:reset-release:gpioa", "reset-release", RuntimeRefKind::reset, "reset:gpioa", RuntimeRefKind::integer, nullptr, 0, "RCC_IOPRSTR.GPIOARST", "0"},
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_reset_release_gpiob, "requirement:reset-release:gpiob", "reset-release", RuntimeRefKind::reset, "reset:gpiob", RuntimeRefKind::integer, nullptr, 0, "RCC_IOPRSTR.GPIOBRST", "0"},
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_reset_release_usart1, "requirement:reset-release:usart1", "reset-release", RuntimeRefKind::reset, "reset:usart1", RuntimeRefKind::integer, nullptr, 0, "RCC_APBRSTR2.USART1RST", "0"},
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_source_select_pb6_usart1_tx, "requirement:source-select:pb6:usart1:tx", "source-select", RuntimeRefKind::pin, "PB6", RuntimeRefKind::selector, "selector:0", 0, "pinmux.PB6", "selector:0"},
  {"stm32g071rb", RouteRequirementId::stm32g071rb_requirement_source_select_pb7_usart1_rx, "requirement:source-select:pb7:usart1:rx", "source-select", RuntimeRefKind::pin, "PB7", RuntimeRefKind::selector, "selector:0", 0, "pinmux.PB7", "selector:0"},
}};

enum class RouteOperationId : std::uint16_t {
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
  const char* device;
  RouteOperationId operation_id;
  const char* operation_name;
  const char* kind;
  const char* schema_id;
  const char* subject_kind;
  const char* subject_id;
  RuntimeRefKind target_ref_kind;
  const char* target_ref_id;
  RuntimeRefKind value_ref_kind;
  const char* value_ref_id;
  const char* register_peripheral;
  const char* register_name;
  int register_offset;
  const char* register_id;
  const char* register_field_id;
  int value_int;
  const char* diagnostic_target;
  const char* diagnostic_value;
};
inline constexpr std::array<RouteOperationDescriptor, 12> kRouteOperations = {{
  {"stm32g071rb", RouteOperationId::stm32g071rb_operation_clock_enable_dma1, "operation:clock-enable:dma1", "set-bit", "alloy.clock.st-rcc-g0-v1-0", "peripheral", "DMA1", RuntimeRefKind::clock_gate, "gate:dma1", RuntimeRefKind::integer, nullptr, "RCC", "AHBENR", 56, "register:rcc:ahbenr", nullptr, 1, "RCC_AHBENR.DMA1EN", "1"},
  {"stm32g071rb", RouteOperationId::stm32g071rb_operation_clock_enable_dmamux1, "operation:clock-enable:dmamux1", "set-bit", "alloy.clock.st-rcc-g0-v1-0", "peripheral", "DMAMUX1", RuntimeRefKind::clock_gate, "gate:dmamux1", RuntimeRefKind::integer, nullptr, "RCC", "AHBENR", 56, "register:rcc:ahbenr", nullptr, 1, "RCC_AHBENR.DMAMUX1EN", "1"},
  {"stm32g071rb", RouteOperationId::stm32g071rb_operation_clock_enable_gpioa, "operation:clock-enable:gpioa", "set-bit", "alloy.clock.st-rcc-g0-v1-0", "peripheral", "GPIOA", RuntimeRefKind::clock_gate, "gate:gpioa", RuntimeRefKind::integer, nullptr, "RCC", "IOPENR", 52, "register:rcc:iopenr", nullptr, 1, "RCC_IOPENR.GPIOAEN", "1"},
  {"stm32g071rb", RouteOperationId::stm32g071rb_operation_clock_enable_gpiob, "operation:clock-enable:gpiob", "set-bit", "alloy.clock.st-rcc-g0-v1-0", "peripheral", "GPIOB", RuntimeRefKind::clock_gate, "gate:gpiob", RuntimeRefKind::integer, nullptr, "RCC", "IOPENR", 52, "register:rcc:iopenr", nullptr, 1, "RCC_IOPENR.GPIOBEN", "1"},
  {"stm32g071rb", RouteOperationId::stm32g071rb_operation_clock_enable_usart1, "operation:clock-enable:usart1", "set-bit", "alloy.clock.st-rcc-g0-v1-0", "peripheral", "USART1", RuntimeRefKind::clock_gate, "gate:usart1", RuntimeRefKind::integer, nullptr, "RCC", "APBENR2", 64, "register:rcc:apbenr2", nullptr, 1, "RCC_APBENR2.USART1EN", "1"},
  {"stm32g071rb", RouteOperationId::stm32g071rb_operation_reset_release_dma1, "operation:reset-release:dma1", "clear-bit", "alloy.clock.st-rcc-g0-v1-0", "peripheral", "DMA1", RuntimeRefKind::reset, "reset:dma1", RuntimeRefKind::integer, nullptr, "RCC", "AHBRSTR", 40, "register:rcc:ahbrstr", nullptr, 0, "RCC_AHBRSTR.DMA1RST", "0"},
  {"stm32g071rb", RouteOperationId::stm32g071rb_operation_reset_release_dmamux1, "operation:reset-release:dmamux1", "clear-bit", "alloy.clock.st-rcc-g0-v1-0", "peripheral", "DMAMUX1", RuntimeRefKind::reset, "reset:dmamux1", RuntimeRefKind::integer, nullptr, "RCC", "AHBRSTR", 40, "register:rcc:ahbrstr", nullptr, 0, "RCC_AHBRSTR.DMAMUX1RST", "0"},
  {"stm32g071rb", RouteOperationId::stm32g071rb_operation_reset_release_gpioa, "operation:reset-release:gpioa", "clear-bit", "alloy.clock.st-rcc-g0-v1-0", "peripheral", "GPIOA", RuntimeRefKind::reset, "reset:gpioa", RuntimeRefKind::integer, nullptr, "RCC", "IOPRSTR", 36, "register:rcc:ioprstr", nullptr, 0, "RCC_IOPRSTR.GPIOARST", "0"},
  {"stm32g071rb", RouteOperationId::stm32g071rb_operation_reset_release_gpiob, "operation:reset-release:gpiob", "clear-bit", "alloy.clock.st-rcc-g0-v1-0", "peripheral", "GPIOB", RuntimeRefKind::reset, "reset:gpiob", RuntimeRefKind::integer, nullptr, "RCC", "IOPRSTR", 36, "register:rcc:ioprstr", nullptr, 0, "RCC_IOPRSTR.GPIOBRST", "0"},
  {"stm32g071rb", RouteOperationId::stm32g071rb_operation_reset_release_usart1, "operation:reset-release:usart1", "clear-bit", "alloy.clock.st-rcc-g0-v1-0", "peripheral", "USART1", RuntimeRefKind::reset, "reset:usart1", RuntimeRefKind::integer, nullptr, "RCC", "APBRSTR2", 48, "register:rcc:apbrstr2", nullptr, 0, "RCC_APBRSTR2.USART1RST", "0"},
  {"stm32g071rb", RouteOperationId::stm32g071rb_operation_route_pb6_usart1_tx, "operation:route:pb6:usart1:tx", "write-selector", "alloy.pinmux.stm32-af-v1", "pin", "PB6", RuntimeRefKind::pin, "PB6", RuntimeRefKind::selector, "selector:0", nullptr, nullptr, -1, nullptr, nullptr, 0, "pinmux.PB6", "0"},
  {"stm32g071rb", RouteOperationId::stm32g071rb_operation_route_pb7_usart1_rx, "operation:route:pb7:usart1:rx", "write-selector", "alloy.pinmux.stm32-af-v1", "pin", "PB7", RuntimeRefKind::pin, "PB7", RuntimeRefKind::selector, "selector:0", nullptr, nullptr, -1, nullptr, nullptr, 0, "pinmux.PB7", "0"},
}};

enum class ConnectionCandidateId : std::uint16_t {
  stm32g071rb_candidate_pb6_usart1_tx,
  stm32g071rb_candidate_pb7_usart1_rx,
};

struct ConnectionCandidateDescriptor {
  const char* device;
  ConnectionCandidateId candidate_id;
  const char* candidate_name;
  const char* pin;
  const char* peripheral;
  const char* signal;
  const char* route_kind;
  const char* route_selector;
  int route_group_index;
  std::uint16_t requirement_offset;
  std::uint16_t requirement_count;
  std::uint16_t operation_offset;
  std::uint16_t operation_count;
  std::uint16_t capability_offset;
  std::uint16_t capability_count;
};
inline constexpr std::array<ConnectionCandidateDescriptor, 2> kConnectionCandidates = {{
  {"stm32g071rb", ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx, "candidate:pb6:usart1:tx", "PB6", "USART1", "tx", "alternate-function", "selector:0", 0, 0u, 5u, 0u, 3u, 0u, 2u},
  {"stm32g071rb", ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx, "candidate:pb7:usart1:rx", "PB7", "USART1", "rx", "alternate-function", "selector:0", 0, 5u, 5u, 3u, 3u, 2u, 2u},
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
  const char* capability_id;
};
inline constexpr std::array<CandidateCapabilityRef, 4> kCandidateCapabilityRefs = {{
  {ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx, "capability:usart:usart-v3-1:tx"},
  {ConnectionCandidateId::stm32g071rb_candidate_pb6_usart1_tx, "capability-instance:usart1:lqfp64:tx"},
  {ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx, "capability:usart:usart-v3-1:rx"},
  {ConnectionCandidateId::stm32g071rb_candidate_pb7_usart1_rx, "capability-instance:usart1:lqfp64:rx"},
}};

enum class ConnectionGroupId : std::uint16_t {
  stm32g071rb_group_usart1_lqfp64_tx_rx,
};

struct ConnectionGroupDescriptor {
  const char* device;
  ConnectionGroupId group_id;
  const char* group_name;
  const char* peripheral;
  const char* package_name;
  const char* conflict_group;
  std::uint16_t signal_offset;
  std::uint16_t signal_count;
  std::uint16_t candidate_offset;
  std::uint16_t candidate_count;
};
inline constexpr std::array<ConnectionGroupDescriptor, 1> kConnectionGroups = {{
  {"stm32g071rb", ConnectionGroupId::stm32g071rb_group_usart1_lqfp64_tx_rx, "group:usart1:lqfp64:tx-rx", "USART1", "lqfp64", "conflict:usart1:lqfp64:tx-rx", 0u, 2u, 0u, 2u},
}};

struct ConnectionGroupSignalRef {
  ConnectionGroupId group_id;
  const char* signal_name;
};
inline constexpr std::array<ConnectionGroupSignalRef, 2> kConnectionGroupSignals = {{
  {ConnectionGroupId::stm32g071rb_group_usart1_lqfp64_tx_rx, "tx"},
  {ConnectionGroupId::stm32g071rb_group_usart1_lqfp64_tx_rx, "rx"},
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
