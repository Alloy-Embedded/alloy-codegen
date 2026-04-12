#pragma once

#include <cstdint>

namespace st {
namespace stm32g0 {
namespace generated {
enum class IpBlockId : std::uint16_t {
  none,
  ip_block_dma_bdma_v1_0,
  ip_block_dmamux_dmamux_v1_0,
  ip_block_gpio_STM32G07x_gpio_v1_0,
  ip_block_rcc_rcc_g0_v1_0,
  ip_block_usart_usart_v3_1,
};

enum class CapabilityId : std::uint16_t {
  none,
  capability_id_capability_instance_usart1_lqfp64_rx,
  capability_id_capability_instance_usart1_lqfp64_tx,
  capability_id_capability_usart_usart_v3_1_rx,
  capability_id_capability_usart_usart_v3_1_tx,
};

enum class BackendSchemaId : std::uint16_t {
  none,
  schema_alloy_clock_st_rcc_g0_v1_0,
  schema_alloy_dma_router_st_dmamux_v1_0,
  schema_alloy_dma_st_bdma_v1_0,
  schema_alloy_gpio_st_stm32g07x_gpio_v1_0,
  schema_alloy_pinmux_stm32_af_v1,
  schema_alloy_rcc_st_rcc_g0_v1_0,
  schema_alloy_uart_st_usart_v3_1,
};

enum class PeripheralClassId : std::uint16_t {
  none,
  class_dma,
  class_dma_router,
  class_gpio,
  class_rcc,
  class_uart,
};

enum class CapabilityScopeId : std::uint16_t {
  none,
  capability_scope_instance_overlay,
  capability_scope_ip_block,
};

enum class CapabilityKeyId : std::uint16_t {
  none,
  capability_available_signal_rx,
  capability_available_signal_tx,
  capability_signal_role_rx,
  capability_signal_role_tx,
};

enum class RouteKindId : std::uint16_t {
  none,
  route_kind_alternate_function,
};

enum class RequirementKindId : std::uint16_t {
  none,
  requirement_kind_bonded_pin,
  requirement_kind_clock_enable,
  requirement_kind_package,
  requirement_kind_reset_release,
  requirement_kind_source_select,
};

enum class OperationKindId : std::uint16_t {
  none,
  operation_kind_clear_bit,
  operation_kind_set_bit,
  operation_kind_write_selector,
};

enum class OperationSubjectKindId : std::uint16_t {
  none,
  operation_subject_peripheral,
  operation_subject_pin,
};

enum class MemoryKindId : std::uint16_t {
  none,
  memory_kind_flash,
  memory_kind_sram,
};

enum class StartupKindId : std::uint16_t {
  none,
  startup_kind_copy_source_region,
  startup_kind_copy_target_region,
  startup_kind_initial_stack_pointer,
  startup_kind_vector_source_region,
  startup_kind_vector_table,
  startup_kind_zero_target_region,
};

enum class VectorKindId : std::uint16_t {
  none,
  vector_kind_external_interrupt,
  vector_kind_initial_stack_pointer,
  vector_kind_reserved,
  vector_kind_reset_handler,
  vector_kind_system_exception,
};

enum class PackagePadKindId : std::uint16_t {
  none,
  package_pad_kind_io,
};

enum class BondingStateId : std::uint16_t {
  none,
  bonding_state_bonded,
};

enum class ConstraintKindId : std::uint16_t {
  none,
};

enum class ActiveLevelId : std::uint16_t {
  none,
  active_level_high,
};

enum class CoreId : std::uint16_t {
  none,
  core_cortex_m0plus,
};

enum class PortId : std::uint16_t {
  none,
  port_A,
  port_B,
};

enum class PinFunctionId : std::uint16_t {
  none,
  pin_function_gpio,
  pin_function_usart1_rx,
  pin_function_usart1_tx,
};

enum class AccessKindId : std::uint16_t {
  none,
  access_kind_read_write,
  access_kind_rwx,
  access_kind_rx,
};

enum class ConstraintValueId : std::uint16_t {
  none,
};

enum class SignalId : std::uint16_t {
  none,
  signal_IN0,
  signal_IN1,
  signal_IN2,
  signal_IN3,
  signal_IN6,
  signal_IN7,
  signal_RX,
  signal_TX,
  signal_gpio,
  signal_rx,
  signal_tx,
  signal_usart1_rx,
  signal_usart1_tx,
};

enum class SignalRoleId : std::uint16_t {
  none,
  signal_role_rx,
  signal_role_tx,
};

enum class DirectionId : std::uint16_t {
  none,
  direction_input,
  direction_output,
};

enum class RegisterProfileId : std::uint16_t {
  none,
  register_profile_dma_bdma_v1_0,
  register_profile_dmamux_dmamux_v1_0,
  register_profile_gpio_STM32G07x_gpio_v1_0,
  register_profile_rcc_rcc_g0_v1_0,
  register_profile_usart_usart_v3_1,
};

enum class ClockNodeKindId : std::uint16_t {
  none,
  clock_node_kind_ahb_domain,
  clock_node_kind_apb_domain,
  clock_node_kind_gpio_domain,
  clock_node_kind_internal_oscillator,
  clock_node_kind_low_speed_source,
  clock_node_kind_root,
  clock_node_kind_system_source,
};

enum class RuntimeProfileSourceKind : std::uint16_t {
  none,
  runtime_profile_source_peripheral,
  runtime_profile_source_route_operation,
};

enum class StartupRoleId : std::uint16_t {
  none,
  startup_role_copy_source,
  startup_role_copy_target,
  startup_role_nonvolatile,
  startup_role_stack_target,
  startup_role_vector_source,
  startup_role_volatile_target,
  startup_role_zero_target,
};

}
}
}
