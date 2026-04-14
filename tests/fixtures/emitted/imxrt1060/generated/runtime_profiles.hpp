#pragma once

#include <array>
#include <cstdint>
#include "runtime_semantics.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
struct RuntimeProfileDescriptor {
  PeripheralClassId peripheral_class_id;
  BackendSchemaId schema_id;
  RuntimeProfileSourceKind source_kind;
  std::uint16_t source_index;
};
inline constexpr std::array<RuntimeProfileDescriptor, 25> kRuntimeProfiles = {{
  {PeripheralClassId::class_ccm, BackendSchemaId::schema_alloy_ccm_nxp_ccm, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 0u},
  {PeripheralClassId::class_ccm_analog, BackendSchemaId::schema_alloy_ccm_analog_nxp_ccm_analog, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 1u},
  {PeripheralClassId::class_dcdc, BackendSchemaId::schema_alloy_dcdc_nxp_dcdc, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 2u},
  {PeripheralClassId::class_gpio, BackendSchemaId::schema_alloy_gpio_nxp_imxrt_gpio_v1, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 3u},
  {PeripheralClassId::class_gpio, BackendSchemaId::schema_alloy_gpio_nxp_imxrt_gpio_v1, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 4u},
  {PeripheralClassId::class_lpi2c1, BackendSchemaId::schema_alloy_lpi2c1_nxp_lpi2c_v1, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 5u},
  {PeripheralClassId::class_spi, BackendSchemaId::schema_alloy_spi_nxp_lpspi_v1, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 6u},
  {PeripheralClassId::class_uart, BackendSchemaId::schema_alloy_uart_nxp_lpuart_v1, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 7u},
  {PeripheralClassId::class_uart, BackendSchemaId::schema_alloy_uart_nxp_lpuart_v1, RuntimeProfileSourceKind::runtime_profile_source_peripheral, 8u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_nxp_ccm, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 9u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_nxp_ccm, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 10u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_nxp_ccm, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 11u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_nxp_ccm, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 12u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_nxp_ccm, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 13u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_clock_nxp_ccm, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 14u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 15u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 16u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 17u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 18u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 19u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 20u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 21u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 22u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 23u},
  {PeripheralClassId::none, BackendSchemaId::schema_alloy_pinmux_imxrt_iomuxc_v1, RuntimeProfileSourceKind::runtime_profile_source_route_operation, 24u},
}};
}
}
}
