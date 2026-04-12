#pragma once

#include <array>
#include <cstdint>
#include "runtime_semantics.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
enum class DeviceRefId : std::uint16_t {
  none,
  mimxrt1062,
};

enum class PeripheralRefId : std::uint16_t {
  none,
  mimxrt1062_GPIO1,
  mimxrt1062_GPIO4,
  mimxrt1062_LPI2C1,
  mimxrt1062_LPSPI1,
  mimxrt1062_LPUART1,
  mimxrt1062_LPUART3,
};

enum class PackageRefId : std::uint16_t {
  none,
  mimxrt1062_bga196,
};

enum class PackagePadRefId : std::uint16_t {
  none,
  mimxrt1062_GPIO_AD_B0_00,
  mimxrt1062_GPIO_AD_B0_01,
  mimxrt1062_GPIO_EMC_00,
  mimxrt1062_GPIO_EMC_01,
};

enum class StateRefId : std::uint16_t {
  none,
  selected,
};

enum class PinRefId : std::uint16_t {
  none,
  mimxrt1062_GPIO_AD_B0_00,
  mimxrt1062_GPIO_AD_B0_01,
  mimxrt1062_GPIO_EMC_00,
  mimxrt1062_GPIO_EMC_01,
};

enum class ConstraintRefId : std::uint16_t {
  none,
};

enum class SelectorRefId : std::uint16_t {
  none,
  mimxrt1062_selector_0,
  mimxrt1062_selector_2,
  mimxrt1062_selector_5,
};

enum class IpBlockRefId : std::uint16_t {
  none,
  gpio_imxrt_gpio_v1,
  lpi2c1_lpi2c_v1,
  lpspi_lpspi_v1,
  lpuart_lpuart_v1,
};

enum class CapabilityRefId : std::uint16_t {
  none,
  mimxrt1062_capability_instance_gpio1_bga196_io00,
  mimxrt1062_capability_instance_gpio1_bga196_io01,
  mimxrt1062_capability_instance_gpio4_bga196_io00,
  mimxrt1062_capability_instance_gpio4_bga196_io01,
  mimxrt1062_capability_instance_lpi2c1_bga196_scl,
  mimxrt1062_capability_instance_lpi2c1_bga196_sda,
  mimxrt1062_capability_instance_lpspi1_bga196_cs,
  mimxrt1062_capability_instance_lpspi1_bga196_sck,
  mimxrt1062_capability_instance_lpuart1_bga196_rx,
  mimxrt1062_capability_instance_lpuart1_bga196_tx,
  mimxrt1062_capability_gpio_imxrt_gpio_v1_io00,
  mimxrt1062_capability_gpio_imxrt_gpio_v1_io01,
  mimxrt1062_capability_lpi2c1_lpi2c_v1_scl,
  mimxrt1062_capability_lpi2c1_lpi2c_v1_sda,
  mimxrt1062_capability_lpspi_lpspi_v1_cs,
  mimxrt1062_capability_lpspi_lpspi_v1_sck,
  mimxrt1062_capability_lpuart_lpuart_v1_rx,
  mimxrt1062_capability_lpuart_lpuart_v1_tx,
};

enum class RegisterRefId : std::uint16_t {
  none,
  mimxrt1062_register_gpio1_dr,
  mimxrt1062_register_gpio1_gdir,
  mimxrt1062_register_gpio1_psr,
  mimxrt1062_register_gpio4_dr,
  mimxrt1062_register_gpio4_gdir,
  mimxrt1062_register_gpio4_psr,
  mimxrt1062_register_lpuart1_baud,
  mimxrt1062_register_lpuart1_ctrl,
  mimxrt1062_register_lpuart1_data,
  mimxrt1062_register_lpuart1_stat,
  mimxrt1062_register_lpuart3_baud,
  mimxrt1062_register_lpuart3_ctrl,
  mimxrt1062_register_lpuart3_data,
  mimxrt1062_register_lpuart3_stat,
};

enum class RegisterFieldRefId : std::uint16_t {
  none,
  mimxrt1062_field_gpio1_dr_data,
  mimxrt1062_field_gpio4_dr_data,
  mimxrt1062_field_lpuart1_baud_sbr,
  mimxrt1062_field_lpuart3_baud_sbr,
};

struct DeviceRefDescriptor {
  DeviceRefId device_id;
  PackageRefId selected_package_id;
  CoreId core_id;
};
inline constexpr std::array<DeviceRefDescriptor, 2> kDeviceRefs = {{
  {DeviceRefId::none, PackageRefId::none, CoreId::none},
  {DeviceRefId::mimxrt1062, PackageRefId::mimxrt1062_bga196, CoreId::core_cortex_m7f},
}};

struct PeripheralRefDescriptor {
  PeripheralRefId peripheral_id;
  DeviceRefId device_id;
  PeripheralClassId peripheral_class_id;
};
inline constexpr std::array<PeripheralRefDescriptor, 7> kPeripheralRefs = {{
  {PeripheralRefId::none, DeviceRefId::none, PeripheralClassId::none},
  {PeripheralRefId::mimxrt1062_GPIO1, DeviceRefId::mimxrt1062, PeripheralClassId::class_gpio},
  {PeripheralRefId::mimxrt1062_GPIO4, DeviceRefId::mimxrt1062, PeripheralClassId::class_gpio},
  {PeripheralRefId::mimxrt1062_LPI2C1, DeviceRefId::mimxrt1062, PeripheralClassId::class_lpi2c1},
  {PeripheralRefId::mimxrt1062_LPSPI1, DeviceRefId::mimxrt1062, PeripheralClassId::class_spi},
  {PeripheralRefId::mimxrt1062_LPUART1, DeviceRefId::mimxrt1062, PeripheralClassId::class_uart},
  {PeripheralRefId::mimxrt1062_LPUART3, DeviceRefId::mimxrt1062, PeripheralClassId::class_uart},
}};

struct PackageRefDescriptor {
  PackageRefId package_id;
  DeviceRefId device_id;
};
inline constexpr std::array<PackageRefDescriptor, 2> kPackageRefs = {{
  {PackageRefId::none, DeviceRefId::none},
  {PackageRefId::mimxrt1062_bga196, DeviceRefId::mimxrt1062},
}};

struct PackagePadRefDescriptor {
  PackagePadRefId package_pad_id;
  DeviceRefId device_id;
  PackageRefId package_id;
  PinRefId bonded_pin_id;
  int physical_index;
  PackagePadKindId pad_kind_id;
  BondingStateId bonding_state_id;
};
inline constexpr std::array<PackagePadRefDescriptor, 5> kPackagePadRefs = {{
  {PackagePadRefId::none, DeviceRefId::none, PackageRefId::none, PinRefId::none, -1, PackagePadKindId::none, BondingStateId::none},
  {PackagePadRefId::mimxrt1062_GPIO_AD_B0_00, DeviceRefId::mimxrt1062, PackageRefId::mimxrt1062_bga196, PinRefId::mimxrt1062_GPIO_AD_B0_00, -1, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded},
  {PackagePadRefId::mimxrt1062_GPIO_AD_B0_01, DeviceRefId::mimxrt1062, PackageRefId::mimxrt1062_bga196, PinRefId::mimxrt1062_GPIO_AD_B0_01, -1, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded},
  {PackagePadRefId::mimxrt1062_GPIO_EMC_00, DeviceRefId::mimxrt1062, PackageRefId::mimxrt1062_bga196, PinRefId::mimxrt1062_GPIO_EMC_00, -1, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded},
  {PackagePadRefId::mimxrt1062_GPIO_EMC_01, DeviceRefId::mimxrt1062, PackageRefId::mimxrt1062_bga196, PinRefId::mimxrt1062_GPIO_EMC_01, -1, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded},
}};

struct StateRefDescriptor {
  StateRefId state_id;
};
inline constexpr std::array<StateRefDescriptor, 2> kStateRefs = {{
  {StateRefId::none},
  {StateRefId::selected},
}};

struct PinRefDescriptor {
  PinRefId pin_id;
  DeviceRefId device_id;
  PortId port_id;
  int pin_number;
};
inline constexpr std::array<PinRefDescriptor, 5> kPinRefs = {{
  {PinRefId::none, DeviceRefId::none, PortId::none, -1},
  {PinRefId::mimxrt1062_GPIO_AD_B0_00, DeviceRefId::mimxrt1062, PortId::none, 0},
  {PinRefId::mimxrt1062_GPIO_AD_B0_01, DeviceRefId::mimxrt1062, PortId::none, 1},
  {PinRefId::mimxrt1062_GPIO_EMC_00, DeviceRefId::mimxrt1062, PortId::none, 0},
  {PinRefId::mimxrt1062_GPIO_EMC_01, DeviceRefId::mimxrt1062, PortId::none, 1},
}};

struct ConstraintRefDescriptor {
  ConstraintRefId constraint_id;
  DeviceRefId device_id;
  PinRefId pin_id;
  ConstraintKindId kind_id;
  ConstraintValueId value_id;
};
inline constexpr std::array<ConstraintRefDescriptor, 1> kConstraintRefs = {{
  {ConstraintRefId::none, DeviceRefId::none, PinRefId::none, ConstraintKindId::none, ConstraintValueId::none},
}};

struct SelectorRefDescriptor {
  SelectorRefId selector_id;
  DeviceRefId device_id;
  int selector_value;
};
inline constexpr std::array<SelectorRefDescriptor, 4> kSelectorRefs = {{
  {SelectorRefId::none, DeviceRefId::none, -1},
  {SelectorRefId::mimxrt1062_selector_0, DeviceRefId::mimxrt1062, 0},
  {SelectorRefId::mimxrt1062_selector_2, DeviceRefId::mimxrt1062, 2},
  {SelectorRefId::mimxrt1062_selector_5, DeviceRefId::mimxrt1062, 5},
}};

struct IpBlockRefDescriptor {
  IpBlockRefId ip_block_ref_id;
  IpBlockId ip_block_id;
  PeripheralClassId peripheral_class_id;
  BackendSchemaId schema_id;
  RegisterProfileId register_profile_id;
};
inline constexpr std::array<IpBlockRefDescriptor, 5> kIpBlockRefs = {{
  {IpBlockRefId::none, IpBlockId::none, PeripheralClassId::none, BackendSchemaId::none, RegisterProfileId::none},
  {IpBlockRefId::gpio_imxrt_gpio_v1, IpBlockId::ip_block_gpio_imxrt_gpio_v1, PeripheralClassId::class_gpio, BackendSchemaId::schema_alloy_gpio_nxp_imxrt_gpio_v1, RegisterProfileId::register_profile_gpio_imxrt_gpio_v1},
  {IpBlockRefId::lpi2c1_lpi2c_v1, IpBlockId::ip_block_lpi2c1_lpi2c_v1, PeripheralClassId::class_lpi2c1, BackendSchemaId::schema_alloy_lpi2c1_nxp_lpi2c_v1, RegisterProfileId::register_profile_lpi2c1_lpi2c_v1},
  {IpBlockRefId::lpspi_lpspi_v1, IpBlockId::ip_block_lpspi_lpspi_v1, PeripheralClassId::class_spi, BackendSchemaId::schema_alloy_spi_nxp_lpspi_v1, RegisterProfileId::register_profile_lpspi_lpspi_v1},
  {IpBlockRefId::lpuart_lpuart_v1, IpBlockId::ip_block_lpuart_lpuart_v1, PeripheralClassId::class_uart, BackendSchemaId::schema_alloy_uart_nxp_lpuart_v1, RegisterProfileId::register_profile_lpuart_lpuart_v1},
}};

struct CapabilityRefDescriptor {
  CapabilityRefId capability_ref_id;
  DeviceRefId device_id;
  CapabilityId capability_id;
  CapabilityScopeId scope_id;
  PeripheralClassId peripheral_class_id;
  CapabilityKeyId capability_key_id;
  IpBlockId ip_block_id;
  PackageRefId package_id;
  PeripheralRefId peripheral_id;
};
inline constexpr std::array<CapabilityRefDescriptor, 19> kCapabilityRefs = {{
  {CapabilityRefId::none, DeviceRefId::none, CapabilityId::none, CapabilityScopeId::none, PeripheralClassId::none, CapabilityKeyId::none, IpBlockId::none, PackageRefId::none, PeripheralRefId::none},
  {CapabilityRefId::mimxrt1062_capability_instance_gpio1_bga196_io00, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_instance_gpio1_bga196_io00, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_gpio, CapabilityKeyId::capability_available_signal_io00, IpBlockId::ip_block_gpio_imxrt_gpio_v1, PackageRefId::mimxrt1062_bga196, PeripheralRefId::mimxrt1062_GPIO1},
  {CapabilityRefId::mimxrt1062_capability_instance_gpio1_bga196_io01, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_instance_gpio1_bga196_io01, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_gpio, CapabilityKeyId::capability_available_signal_io01, IpBlockId::ip_block_gpio_imxrt_gpio_v1, PackageRefId::mimxrt1062_bga196, PeripheralRefId::mimxrt1062_GPIO1},
  {CapabilityRefId::mimxrt1062_capability_instance_gpio4_bga196_io00, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_instance_gpio4_bga196_io00, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_gpio, CapabilityKeyId::capability_available_signal_io00, IpBlockId::ip_block_gpio_imxrt_gpio_v1, PackageRefId::mimxrt1062_bga196, PeripheralRefId::mimxrt1062_GPIO4},
  {CapabilityRefId::mimxrt1062_capability_instance_gpio4_bga196_io01, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_instance_gpio4_bga196_io01, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_gpio, CapabilityKeyId::capability_available_signal_io01, IpBlockId::ip_block_gpio_imxrt_gpio_v1, PackageRefId::mimxrt1062_bga196, PeripheralRefId::mimxrt1062_GPIO4},
  {CapabilityRefId::mimxrt1062_capability_instance_lpi2c1_bga196_scl, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_instance_lpi2c1_bga196_scl, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_lpi2c1, CapabilityKeyId::capability_available_signal_scl, IpBlockId::ip_block_lpi2c1_lpi2c_v1, PackageRefId::mimxrt1062_bga196, PeripheralRefId::mimxrt1062_LPI2C1},
  {CapabilityRefId::mimxrt1062_capability_instance_lpi2c1_bga196_sda, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_instance_lpi2c1_bga196_sda, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_lpi2c1, CapabilityKeyId::capability_available_signal_sda, IpBlockId::ip_block_lpi2c1_lpi2c_v1, PackageRefId::mimxrt1062_bga196, PeripheralRefId::mimxrt1062_LPI2C1},
  {CapabilityRefId::mimxrt1062_capability_instance_lpspi1_bga196_cs, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_instance_lpspi1_bga196_cs, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_spi, CapabilityKeyId::capability_available_signal_cs, IpBlockId::ip_block_lpspi_lpspi_v1, PackageRefId::mimxrt1062_bga196, PeripheralRefId::mimxrt1062_LPSPI1},
  {CapabilityRefId::mimxrt1062_capability_instance_lpspi1_bga196_sck, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_instance_lpspi1_bga196_sck, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_spi, CapabilityKeyId::capability_available_signal_sck, IpBlockId::ip_block_lpspi_lpspi_v1, PackageRefId::mimxrt1062_bga196, PeripheralRefId::mimxrt1062_LPSPI1},
  {CapabilityRefId::mimxrt1062_capability_instance_lpuart1_bga196_rx, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_instance_lpuart1_bga196_rx, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_uart, CapabilityKeyId::capability_available_signal_rx, IpBlockId::ip_block_lpuart_lpuart_v1, PackageRefId::mimxrt1062_bga196, PeripheralRefId::mimxrt1062_LPUART1},
  {CapabilityRefId::mimxrt1062_capability_instance_lpuart1_bga196_tx, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_instance_lpuart1_bga196_tx, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_uart, CapabilityKeyId::capability_available_signal_tx, IpBlockId::ip_block_lpuart_lpuart_v1, PackageRefId::mimxrt1062_bga196, PeripheralRefId::mimxrt1062_LPUART1},
  {CapabilityRefId::mimxrt1062_capability_gpio_imxrt_gpio_v1_io00, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_gpio_imxrt_gpio_v1_io00, CapabilityScopeId::capability_scope_ip_block, PeripheralClassId::class_gpio, CapabilityKeyId::capability_signal_role_io00, IpBlockId::ip_block_gpio_imxrt_gpio_v1, PackageRefId::none, PeripheralRefId::none},
  {CapabilityRefId::mimxrt1062_capability_gpio_imxrt_gpio_v1_io01, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_gpio_imxrt_gpio_v1_io01, CapabilityScopeId::capability_scope_ip_block, PeripheralClassId::class_gpio, CapabilityKeyId::capability_signal_role_io01, IpBlockId::ip_block_gpio_imxrt_gpio_v1, PackageRefId::none, PeripheralRefId::none},
  {CapabilityRefId::mimxrt1062_capability_lpi2c1_lpi2c_v1_scl, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_lpi2c1_lpi2c_v1_scl, CapabilityScopeId::capability_scope_ip_block, PeripheralClassId::class_lpi2c1, CapabilityKeyId::capability_signal_role_scl, IpBlockId::ip_block_lpi2c1_lpi2c_v1, PackageRefId::none, PeripheralRefId::none},
  {CapabilityRefId::mimxrt1062_capability_lpi2c1_lpi2c_v1_sda, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_lpi2c1_lpi2c_v1_sda, CapabilityScopeId::capability_scope_ip_block, PeripheralClassId::class_lpi2c1, CapabilityKeyId::capability_signal_role_sda, IpBlockId::ip_block_lpi2c1_lpi2c_v1, PackageRefId::none, PeripheralRefId::none},
  {CapabilityRefId::mimxrt1062_capability_lpspi_lpspi_v1_cs, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_lpspi_lpspi_v1_cs, CapabilityScopeId::capability_scope_ip_block, PeripheralClassId::class_spi, CapabilityKeyId::capability_signal_role_cs, IpBlockId::ip_block_lpspi_lpspi_v1, PackageRefId::none, PeripheralRefId::none},
  {CapabilityRefId::mimxrt1062_capability_lpspi_lpspi_v1_sck, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_lpspi_lpspi_v1_sck, CapabilityScopeId::capability_scope_ip_block, PeripheralClassId::class_spi, CapabilityKeyId::capability_signal_role_sck, IpBlockId::ip_block_lpspi_lpspi_v1, PackageRefId::none, PeripheralRefId::none},
  {CapabilityRefId::mimxrt1062_capability_lpuart_lpuart_v1_rx, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_lpuart_lpuart_v1_rx, CapabilityScopeId::capability_scope_ip_block, PeripheralClassId::class_uart, CapabilityKeyId::capability_signal_role_rx, IpBlockId::ip_block_lpuart_lpuart_v1, PackageRefId::none, PeripheralRefId::none},
  {CapabilityRefId::mimxrt1062_capability_lpuart_lpuart_v1_tx, DeviceRefId::mimxrt1062, CapabilityId::capability_id_capability_lpuart_lpuart_v1_tx, CapabilityScopeId::capability_scope_ip_block, PeripheralClassId::class_uart, CapabilityKeyId::capability_signal_role_tx, IpBlockId::ip_block_lpuart_lpuart_v1, PackageRefId::none, PeripheralRefId::none},
}};

struct RegisterRefDescriptor {
  RegisterRefId register_id;
  DeviceRefId device_id;
  PeripheralRefId peripheral_id;
  std::uint32_t offset_bytes;
};
inline constexpr std::array<RegisterRefDescriptor, 15> kRegisterRefs = {{
  {RegisterRefId::none, DeviceRefId::none, PeripheralRefId::none, 0u},
  {RegisterRefId::mimxrt1062_register_gpio1_dr, DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_GPIO1, 0u},
  {RegisterRefId::mimxrt1062_register_gpio1_gdir, DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_GPIO1, 4u},
  {RegisterRefId::mimxrt1062_register_gpio1_psr, DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_GPIO1, 8u},
  {RegisterRefId::mimxrt1062_register_gpio4_dr, DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_GPIO4, 0u},
  {RegisterRefId::mimxrt1062_register_gpio4_gdir, DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_GPIO4, 4u},
  {RegisterRefId::mimxrt1062_register_gpio4_psr, DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_GPIO4, 8u},
  {RegisterRefId::mimxrt1062_register_lpuart1_baud, DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPUART1, 16u},
  {RegisterRefId::mimxrt1062_register_lpuart1_ctrl, DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPUART1, 24u},
  {RegisterRefId::mimxrt1062_register_lpuart1_data, DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPUART1, 28u},
  {RegisterRefId::mimxrt1062_register_lpuart1_stat, DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPUART1, 20u},
  {RegisterRefId::mimxrt1062_register_lpuart3_baud, DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPUART3, 16u},
  {RegisterRefId::mimxrt1062_register_lpuart3_ctrl, DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPUART3, 24u},
  {RegisterRefId::mimxrt1062_register_lpuart3_data, DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPUART3, 28u},
  {RegisterRefId::mimxrt1062_register_lpuart3_stat, DeviceRefId::mimxrt1062, PeripheralRefId::mimxrt1062_LPUART3, 20u},
}};

struct RegisterFieldRefDescriptor {
  RegisterFieldRefId field_id;
  DeviceRefId device_id;
  RegisterRefId register_id;
  std::uint16_t bit_offset;
  std::uint16_t bit_width;
};
inline constexpr std::array<RegisterFieldRefDescriptor, 5> kRegisterFieldRefs = {{
  {RegisterFieldRefId::none, DeviceRefId::none, RegisterRefId::none, 0u, 0u},
  {RegisterFieldRefId::mimxrt1062_field_gpio1_dr_data, DeviceRefId::mimxrt1062, RegisterRefId::mimxrt1062_register_gpio1_dr, 0u, 32u},
  {RegisterFieldRefId::mimxrt1062_field_gpio4_dr_data, DeviceRefId::mimxrt1062, RegisterRefId::mimxrt1062_register_gpio4_dr, 0u, 32u},
  {RegisterFieldRefId::mimxrt1062_field_lpuart1_baud_sbr, DeviceRefId::mimxrt1062, RegisterRefId::mimxrt1062_register_lpuart1_baud, 0u, 13u},
  {RegisterFieldRefId::mimxrt1062_field_lpuart3_baud_sbr, DeviceRefId::mimxrt1062, RegisterRefId::mimxrt1062_register_lpuart3_baud, 0u, 13u},
}};
}
}
}
