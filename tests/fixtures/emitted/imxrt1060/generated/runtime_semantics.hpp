#pragma once

#include <cstdint>

namespace nxp {
namespace imxrt1060 {
namespace generated {
enum class IpBlockId : std::uint16_t {
  none,
  ip_block_gpio_imxrt_gpio_v1,
  ip_block_lpi2c1_lpi2c_v1,
  ip_block_lpspi_lpspi_v1,
  ip_block_lpuart_lpuart_v1,
};

enum class CapabilityId : std::uint16_t {
  none,
  capability_id_capability_instance_gpio1_bga196_io00,
  capability_id_capability_instance_gpio1_bga196_io01,
  capability_id_capability_instance_gpio4_bga196_io00,
  capability_id_capability_instance_gpio4_bga196_io01,
  capability_id_capability_instance_lpi2c1_bga196_scl,
  capability_id_capability_instance_lpi2c1_bga196_sda,
  capability_id_capability_instance_lpspi1_bga196_cs,
  capability_id_capability_instance_lpspi1_bga196_sck,
  capability_id_capability_instance_lpuart1_bga196_rx,
  capability_id_capability_instance_lpuart1_bga196_tx,
  capability_id_capability_gpio_imxrt_gpio_v1_io00,
  capability_id_capability_gpio_imxrt_gpio_v1_io01,
  capability_id_capability_lpi2c1_lpi2c_v1_scl,
  capability_id_capability_lpi2c1_lpi2c_v1_sda,
  capability_id_capability_lpspi_lpspi_v1_cs,
  capability_id_capability_lpspi_lpspi_v1_sck,
  capability_id_capability_lpuart_lpuart_v1_rx,
  capability_id_capability_lpuart_lpuart_v1_tx,
};

enum class BackendSchemaId : std::uint16_t {
  none,
  schema_alloy_ccm_nxp_ccm,
  schema_alloy_ccm_analog_nxp_ccm_analog,
  schema_alloy_clock_nxp_ccm,
  schema_alloy_dcdc_nxp_dcdc,
  schema_alloy_gpio_nxp_imxrt_gpio_v1,
  schema_alloy_lpi2c1_nxp_lpi2c_v1,
  schema_alloy_pinmux_imxrt_iomuxc_v1,
  schema_alloy_spi_nxp_lpspi_v1,
  schema_alloy_uart_nxp_lpuart_v1,
};

enum class PeripheralClassId : std::uint16_t {
  none,
  class_ccm,
  class_ccm_analog,
  class_dcdc,
  class_gpio,
  class_lpi2c1,
  class_spi,
  class_uart,
};

enum class CapabilityScopeId : std::uint16_t {
  none,
  capability_scope_instance_overlay,
  capability_scope_ip_block,
};

enum class CapabilityKeyId : std::uint16_t {
  none,
  capability_available_signal_cs,
  capability_available_signal_io00,
  capability_available_signal_io01,
  capability_available_signal_rx,
  capability_available_signal_sck,
  capability_available_signal_scl,
  capability_available_signal_sda,
  capability_available_signal_tx,
  capability_signal_role_cs,
  capability_signal_role_io00,
  capability_signal_role_io01,
  capability_signal_role_rx,
  capability_signal_role_sck,
  capability_signal_role_scl,
  capability_signal_role_sda,
  capability_signal_role_tx,
};

enum class RouteKindId : std::uint16_t {
  none,
  route_kind_iomuxc_mux,
};

enum class RequirementKindId : std::uint16_t {
  none,
  requirement_kind_bonded_pin,
  requirement_kind_clock_enable,
  requirement_kind_package,
  requirement_kind_source_select,
};

enum class OperationKindId : std::uint16_t {
  none,
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
  memory_kind_ram,
};

enum class StartupKindId : std::uint16_t {
  none,
  startup_kind_copy_target_region,
  startup_kind_initial_stack_pointer,
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
};

enum class CoreId : std::uint16_t {
  none,
  core_cortex_m7f,
};

enum class PortId : std::uint16_t {
  none,
};

enum class PinFunctionId : std::uint16_t {
  none,
  pin_function_gpio1_io00,
  pin_function_gpio1_io01,
  pin_function_gpio4_io00,
  pin_function_gpio4_io01,
  pin_function_lpi2c1_scl,
  pin_function_lpi2c1_sda,
  pin_function_lpspi1_pcs0,
  pin_function_lpspi1_sck,
  pin_function_lpuart1_rx,
  pin_function_lpuart1_tx,
};

enum class AccessKindId : std::uint16_t {
  none,
  access_kind_read_only,
  access_kind_read_write,
};

enum class ConstraintValueId : std::uint16_t {
  none,
};

enum class SignalId : std::uint16_t {
  none,
  signal_IO00,
  signal_IO01,
  signal_PCS0,
  signal_RX,
  signal_SCK,
  signal_SCL,
  signal_SDA,
  signal_TX,
  signal_cs,
  signal_gpio1_io00,
  signal_gpio1_io01,
  signal_gpio4_io00,
  signal_gpio4_io01,
  signal_io00,
  signal_io01,
  signal_lpi2c1_scl,
  signal_lpi2c1_sda,
  signal_lpspi1_pcs0,
  signal_lpspi1_sck,
  signal_lpuart1_rx,
  signal_lpuart1_tx,
  signal_pcs0,
  signal_rx,
  signal_sck,
  signal_scl,
  signal_sda,
  signal_tx,
};

enum class SignalRoleId : std::uint16_t {
  none,
  signal_role_cs,
  signal_role_io00,
  signal_role_io01,
  signal_role_rx,
  signal_role_sck,
  signal_role_scl,
  signal_role_sda,
  signal_role_tx,
};

enum class DirectionId : std::uint16_t {
  none,
  direction_bidirectional,
  direction_input,
  direction_output,
};

enum class RegisterProfileId : std::uint16_t {
  none,
  register_profile_gpio_imxrt_gpio_v1,
  register_profile_lpi2c1_lpi2c_v1,
  register_profile_lpspi_lpspi_v1,
  register_profile_lpuart_lpuart_v1,
};

enum class ClockNodeKindId : std::uint16_t {
  none,
  clock_node_kind_ccm_domain,
  clock_node_kind_clock_source,
  clock_node_kind_peripheral_root,
  clock_node_kind_pll_source,
  clock_node_kind_root,
};

enum class RuntimeProfileSourceKind : std::uint16_t {
  none,
  runtime_profile_source_peripheral,
  runtime_profile_source_route_operation,
};

enum class StartupRoleId : std::uint16_t {
  none,
  startup_role_copy_target,
  startup_role_stack_target,
  startup_role_volatile_target,
  startup_role_zero_target,
};

}
}
}
