#pragma once

#include <array>
#include <cstdint>
#include "runtime_semantics.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
enum class DeviceRefId : std::uint16_t {
  none,
  stm32g071rb,
};

enum class PeripheralRefId : std::uint16_t {
  none,
  stm32g071rb_DMA1,
  stm32g071rb_DMAMUX1,
  stm32g071rb_GPIOA,
  stm32g071rb_GPIOB,
  stm32g071rb_RCC,
  stm32g071rb_USART1,
};

enum class PackageRefId : std::uint16_t {
  none,
  stm32g071rb_lqfp64,
};

enum class PackagePadRefId : std::uint16_t {
  none,
  stm32g071rb_17,
  stm32g071rb_18,
  stm32g071rb_19,
  stm32g071rb_20,
  stm32g071rb_29,
  stm32g071rb_30,
};

enum class StateRefId : std::uint16_t {
  none,
  selected,
};

enum class PinRefId : std::uint16_t {
  none,
  stm32g071rb_PA0,
  stm32g071rb_PA1,
  stm32g071rb_PA2,
  stm32g071rb_PA3,
  stm32g071rb_PB6,
  stm32g071rb_PB7,
};

enum class ConstraintRefId : std::uint16_t {
  none,
};

enum class SelectorRefId : std::uint16_t {
  none,
  stm32g071rb_selector_0,
};

enum class IpBlockRefId : std::uint16_t {
  none,
  dma_bdma_v1_0,
  dmamux_dmamux_v1_0,
  gpio_STM32G07x_gpio_v1_0,
  rcc_rcc_g0_v1_0,
  usart_usart_v3_1,
};

enum class CapabilityRefId : std::uint16_t {
  none,
  stm32g071rb_capability_instance_usart1_lqfp64_rx,
  stm32g071rb_capability_instance_usart1_lqfp64_tx,
  stm32g071rb_capability_usart_usart_v3_1_rx,
  stm32g071rb_capability_usart_usart_v3_1_tx,
};

enum class RegisterRefId : std::uint16_t {
  none,
  stm32g071rb_register_gpioa_afrh,
  stm32g071rb_register_gpioa_afrl,
  stm32g071rb_register_gpioa_moder,
  stm32g071rb_register_gpiob_afrh,
  stm32g071rb_register_gpiob_afrl,
  stm32g071rb_register_gpiob_moder,
  stm32g071rb_register_rcc_ahbenr,
  stm32g071rb_register_rcc_ahbrstr,
  stm32g071rb_register_rcc_apbenr1,
  stm32g071rb_register_rcc_apbenr2,
  stm32g071rb_register_rcc_apbrstr1,
  stm32g071rb_register_rcc_apbrstr2,
  stm32g071rb_register_rcc_iopenr,
  stm32g071rb_register_rcc_ioprstr,
  stm32g071rb_register_usart1_brr,
  stm32g071rb_register_usart1_cr1,
  stm32g071rb_register_usart1_cr2,
  stm32g071rb_register_usart1_isr,
  stm32g071rb_register_usart1_rdr,
  stm32g071rb_register_usart1_tdr,
};

enum class RegisterFieldRefId : std::uint16_t {
  none,
  stm32g071rb_field_gpioa_moder_mode2,
  stm32g071rb_field_gpiob_moder_mode6,
  stm32g071rb_field_usart1_cr1_ue,
};

struct DeviceRefDescriptor {
  DeviceRefId device_id;
  PackageRefId selected_package_id;
  CoreId core_id;
};
inline constexpr std::array<DeviceRefDescriptor, 2> kDeviceRefs = {{
  {DeviceRefId::none, PackageRefId::none, CoreId::none},
  {DeviceRefId::stm32g071rb, PackageRefId::stm32g071rb_lqfp64, CoreId::core_cortex_m0plus},
}};

struct PeripheralRefDescriptor {
  PeripheralRefId peripheral_id;
  DeviceRefId device_id;
  PeripheralClassId peripheral_class_id;
};
inline constexpr std::array<PeripheralRefDescriptor, 7> kPeripheralRefs = {{
  {PeripheralRefId::none, DeviceRefId::none, PeripheralClassId::none},
  {PeripheralRefId::stm32g071rb_DMA1, DeviceRefId::stm32g071rb, PeripheralClassId::class_dma},
  {PeripheralRefId::stm32g071rb_DMAMUX1, DeviceRefId::stm32g071rb, PeripheralClassId::class_dma_router},
  {PeripheralRefId::stm32g071rb_GPIOA, DeviceRefId::stm32g071rb, PeripheralClassId::class_gpio},
  {PeripheralRefId::stm32g071rb_GPIOB, DeviceRefId::stm32g071rb, PeripheralClassId::class_gpio},
  {PeripheralRefId::stm32g071rb_RCC, DeviceRefId::stm32g071rb, PeripheralClassId::class_rcc},
  {PeripheralRefId::stm32g071rb_USART1, DeviceRefId::stm32g071rb, PeripheralClassId::class_uart},
}};

struct PackageRefDescriptor {
  PackageRefId package_id;
  DeviceRefId device_id;
};
inline constexpr std::array<PackageRefDescriptor, 2> kPackageRefs = {{
  {PackageRefId::none, DeviceRefId::none},
  {PackageRefId::stm32g071rb_lqfp64, DeviceRefId::stm32g071rb},
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
inline constexpr std::array<PackagePadRefDescriptor, 7> kPackagePadRefs = {{
  {PackagePadRefId::none, DeviceRefId::none, PackageRefId::none, PinRefId::none, -1, PackagePadKindId::none, BondingStateId::none},
  {PackagePadRefId::stm32g071rb_17, DeviceRefId::stm32g071rb, PackageRefId::stm32g071rb_lqfp64, PinRefId::stm32g071rb_PA0, 17, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded},
  {PackagePadRefId::stm32g071rb_18, DeviceRefId::stm32g071rb, PackageRefId::stm32g071rb_lqfp64, PinRefId::stm32g071rb_PA1, 18, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded},
  {PackagePadRefId::stm32g071rb_19, DeviceRefId::stm32g071rb, PackageRefId::stm32g071rb_lqfp64, PinRefId::stm32g071rb_PA2, 19, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded},
  {PackagePadRefId::stm32g071rb_20, DeviceRefId::stm32g071rb, PackageRefId::stm32g071rb_lqfp64, PinRefId::stm32g071rb_PA3, 20, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded},
  {PackagePadRefId::stm32g071rb_29, DeviceRefId::stm32g071rb, PackageRefId::stm32g071rb_lqfp64, PinRefId::stm32g071rb_PB6, 29, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded},
  {PackagePadRefId::stm32g071rb_30, DeviceRefId::stm32g071rb, PackageRefId::stm32g071rb_lqfp64, PinRefId::stm32g071rb_PB7, 30, PackagePadKindId::package_pad_kind_io, BondingStateId::bonding_state_bonded},
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
inline constexpr std::array<PinRefDescriptor, 7> kPinRefs = {{
  {PinRefId::none, DeviceRefId::none, PortId::none, -1},
  {PinRefId::stm32g071rb_PA0, DeviceRefId::stm32g071rb, PortId::port_A, 0},
  {PinRefId::stm32g071rb_PA1, DeviceRefId::stm32g071rb, PortId::port_A, 1},
  {PinRefId::stm32g071rb_PA2, DeviceRefId::stm32g071rb, PortId::port_A, 2},
  {PinRefId::stm32g071rb_PA3, DeviceRefId::stm32g071rb, PortId::port_A, 3},
  {PinRefId::stm32g071rb_PB6, DeviceRefId::stm32g071rb, PortId::port_B, 6},
  {PinRefId::stm32g071rb_PB7, DeviceRefId::stm32g071rb, PortId::port_B, 7},
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
inline constexpr std::array<SelectorRefDescriptor, 2> kSelectorRefs = {{
  {SelectorRefId::none, DeviceRefId::none, -1},
  {SelectorRefId::stm32g071rb_selector_0, DeviceRefId::stm32g071rb, 0},
}};

struct IpBlockRefDescriptor {
  IpBlockRefId ip_block_ref_id;
  IpBlockId ip_block_id;
  PeripheralClassId peripheral_class_id;
  BackendSchemaId schema_id;
  RegisterProfileId register_profile_id;
};
inline constexpr std::array<IpBlockRefDescriptor, 6> kIpBlockRefs = {{
  {IpBlockRefId::none, IpBlockId::none, PeripheralClassId::none, BackendSchemaId::none, RegisterProfileId::none},
  {IpBlockRefId::dma_bdma_v1_0, IpBlockId::ip_block_dma_bdma_v1_0, PeripheralClassId::class_dma, BackendSchemaId::schema_alloy_dma_st_bdma_v1_0, RegisterProfileId::register_profile_dma_bdma_v1_0},
  {IpBlockRefId::dmamux_dmamux_v1_0, IpBlockId::ip_block_dmamux_dmamux_v1_0, PeripheralClassId::class_dma_router, BackendSchemaId::schema_alloy_dma_router_st_dmamux_v1_0, RegisterProfileId::register_profile_dmamux_dmamux_v1_0},
  {IpBlockRefId::gpio_STM32G07x_gpio_v1_0, IpBlockId::ip_block_gpio_STM32G07x_gpio_v1_0, PeripheralClassId::class_gpio, BackendSchemaId::schema_alloy_gpio_st_stm32g07x_gpio_v1_0, RegisterProfileId::register_profile_gpio_STM32G07x_gpio_v1_0},
  {IpBlockRefId::rcc_rcc_g0_v1_0, IpBlockId::ip_block_rcc_rcc_g0_v1_0, PeripheralClassId::class_rcc, BackendSchemaId::schema_alloy_rcc_st_rcc_g0_v1_0, RegisterProfileId::register_profile_rcc_rcc_g0_v1_0},
  {IpBlockRefId::usart_usart_v3_1, IpBlockId::ip_block_usart_usart_v3_1, PeripheralClassId::class_uart, BackendSchemaId::schema_alloy_uart_st_usart_v3_1, RegisterProfileId::register_profile_usart_usart_v3_1},
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
inline constexpr std::array<CapabilityRefDescriptor, 5> kCapabilityRefs = {{
  {CapabilityRefId::none, DeviceRefId::none, CapabilityId::none, CapabilityScopeId::none, PeripheralClassId::none, CapabilityKeyId::none, IpBlockId::none, PackageRefId::none, PeripheralRefId::none},
  {CapabilityRefId::stm32g071rb_capability_instance_usart1_lqfp64_rx, DeviceRefId::stm32g071rb, CapabilityId::capability_id_capability_instance_usart1_lqfp64_rx, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_uart, CapabilityKeyId::capability_available_signal_rx, IpBlockId::ip_block_usart_usart_v3_1, PackageRefId::stm32g071rb_lqfp64, PeripheralRefId::stm32g071rb_USART1},
  {CapabilityRefId::stm32g071rb_capability_instance_usart1_lqfp64_tx, DeviceRefId::stm32g071rb, CapabilityId::capability_id_capability_instance_usart1_lqfp64_tx, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_uart, CapabilityKeyId::capability_available_signal_tx, IpBlockId::ip_block_usart_usart_v3_1, PackageRefId::stm32g071rb_lqfp64, PeripheralRefId::stm32g071rb_USART1},
  {CapabilityRefId::stm32g071rb_capability_usart_usart_v3_1_rx, DeviceRefId::stm32g071rb, CapabilityId::capability_id_capability_usart_usart_v3_1_rx, CapabilityScopeId::capability_scope_ip_block, PeripheralClassId::class_uart, CapabilityKeyId::capability_signal_role_rx, IpBlockId::ip_block_usart_usart_v3_1, PackageRefId::none, PeripheralRefId::none},
  {CapabilityRefId::stm32g071rb_capability_usart_usart_v3_1_tx, DeviceRefId::stm32g071rb, CapabilityId::capability_id_capability_usart_usart_v3_1_tx, CapabilityScopeId::capability_scope_ip_block, PeripheralClassId::class_uart, CapabilityKeyId::capability_signal_role_tx, IpBlockId::ip_block_usart_usart_v3_1, PackageRefId::none, PeripheralRefId::none},
}};

struct RegisterRefDescriptor {
  RegisterRefId register_id;
  DeviceRefId device_id;
  PeripheralRefId peripheral_id;
  std::uint32_t offset_bytes;
};
inline constexpr std::array<RegisterRefDescriptor, 21> kRegisterRefs = {{
  {RegisterRefId::none, DeviceRefId::none, PeripheralRefId::none, 0u},
  {RegisterRefId::stm32g071rb_register_gpioa_afrh, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_GPIOA, 36u},
  {RegisterRefId::stm32g071rb_register_gpioa_afrl, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_GPIOA, 32u},
  {RegisterRefId::stm32g071rb_register_gpioa_moder, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_GPIOA, 0u},
  {RegisterRefId::stm32g071rb_register_gpiob_afrh, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_GPIOB, 36u},
  {RegisterRefId::stm32g071rb_register_gpiob_afrl, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_GPIOB, 32u},
  {RegisterRefId::stm32g071rb_register_gpiob_moder, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_GPIOB, 0u},
  {RegisterRefId::stm32g071rb_register_rcc_ahbenr, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_RCC, 56u},
  {RegisterRefId::stm32g071rb_register_rcc_ahbrstr, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_RCC, 40u},
  {RegisterRefId::stm32g071rb_register_rcc_apbenr1, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_RCC, 60u},
  {RegisterRefId::stm32g071rb_register_rcc_apbenr2, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_RCC, 64u},
  {RegisterRefId::stm32g071rb_register_rcc_apbrstr1, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_RCC, 44u},
  {RegisterRefId::stm32g071rb_register_rcc_apbrstr2, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_RCC, 48u},
  {RegisterRefId::stm32g071rb_register_rcc_iopenr, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_RCC, 52u},
  {RegisterRefId::stm32g071rb_register_rcc_ioprstr, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_RCC, 36u},
  {RegisterRefId::stm32g071rb_register_usart1_brr, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_USART1, 12u},
  {RegisterRefId::stm32g071rb_register_usart1_cr1, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_USART1, 0u},
  {RegisterRefId::stm32g071rb_register_usart1_cr2, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_USART1, 4u},
  {RegisterRefId::stm32g071rb_register_usart1_isr, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_USART1, 28u},
  {RegisterRefId::stm32g071rb_register_usart1_rdr, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_USART1, 36u},
  {RegisterRefId::stm32g071rb_register_usart1_tdr, DeviceRefId::stm32g071rb, PeripheralRefId::stm32g071rb_USART1, 40u},
}};

struct RegisterFieldRefDescriptor {
  RegisterFieldRefId field_id;
  DeviceRefId device_id;
  RegisterRefId register_id;
  std::uint16_t bit_offset;
  std::uint16_t bit_width;
};
inline constexpr std::array<RegisterFieldRefDescriptor, 4> kRegisterFieldRefs = {{
  {RegisterFieldRefId::none, DeviceRefId::none, RegisterRefId::none, 0u, 0u},
  {RegisterFieldRefId::stm32g071rb_field_gpioa_moder_mode2, DeviceRefId::stm32g071rb, RegisterRefId::stm32g071rb_register_gpioa_moder, 4u, 2u},
  {RegisterFieldRefId::stm32g071rb_field_gpiob_moder_mode6, DeviceRefId::stm32g071rb, RegisterRefId::stm32g071rb_register_gpiob_moder, 12u, 2u},
  {RegisterFieldRefId::stm32g071rb_field_usart1_cr1_ue, DeviceRefId::stm32g071rb, RegisterRefId::stm32g071rb_register_usart1_cr1, 0u, 1u},
}};
}
}
}
