#pragma once

#include <array>
#include <cstdint>
#include "runtime_semantics.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
struct RuntimeProfileDescriptor {
  PeripheralClassId peripheral_class_id;
  BackendSchemaId schema_id;
  RuntimeProfileSourceKind source_kind;
  std::uint16_t source_index;
};
inline constexpr std::array<RuntimeProfileDescriptor, 18> kRuntimeProfiles = {{
  {PeripheralClassId::class_dma, BackendSchemaId::schema_alloy_dma_st_bdma_v1_0, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 0u},
  {PeripheralClassId::class_dma_router, BackendSchemaId::schema_alloy_dma_router_st_dmamux_v1_0, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 1u},
  {PeripheralClassId::class_gpio, BackendSchemaId::schema_alloy_gpio_st_stm32g07x_gpio_v1_0, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 2u},
  {PeripheralClassId::class_gpio, BackendSchemaId::schema_alloy_gpio_st_stm32g07x_gpio_v1_0, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 3u},
  {PeripheralClassId::class_rcc, BackendSchemaId::schema_alloy_rcc_st_rcc_g0_v1_0, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 4u},
  {PeripheralClassId::class_uart, BackendSchemaId::schema_alloy_uart_st_usart_v3_1, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 5u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 6u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 7u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 8u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 9u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 10u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 11u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 12u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 13u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 14u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_st_rcc_g0_v1_0, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 15u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 16u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_pinmux_stm32_af_v1, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 17u},
}};
}
}
}
