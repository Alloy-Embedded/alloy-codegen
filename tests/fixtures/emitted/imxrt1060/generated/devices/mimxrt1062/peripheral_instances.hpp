#pragma once

#include <array>
#include <cstdint>
#include "../../clock_tree_lite.hpp"
#include "../../runtime_semantics.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
enum class PeripheralId : std::uint16_t {
  CCM,
  GPIO1,
  GPIO4,
  LPI2C1,
  LPSPI1,
  LPUART1,
  LPUART3,
};

struct PeripheralInstanceDescriptor {
  PeripheralId peripheral_id;
  PeripheralClassId peripheral_class_id;
  BackendSchemaId schema_id;
  int instance;
  std::uintptr_t base_address;
  ClockGateId clock_gate_id;
  ResetId reset_id;
  ClockSelectorId selector_id;
  std::uint16_t interrupt_binding_offset;
  std::uint16_t interrupt_binding_count;
  std::uint16_t dma_binding_offset;
  std::uint16_t dma_binding_count;
  std::uint16_t capability_overlay_offset;
  std::uint16_t capability_overlay_count;
  int register_count;
};
inline constexpr std::array<PeripheralInstanceDescriptor, 7> kPeripheralInstances = {{
  {PeripheralId::CCM, PeripheralClassId::class_ccm, BackendSchemaId::schema_alloy_ccm_nxp_ccm, 0, 0x400FC000u, ClockGateId::none, ResetId::none, ClockSelectorId::none, 0u, 0u, 0u, 0u, 0u, 0u, 10},
  {PeripheralId::GPIO1, PeripheralClassId::class_gpio, BackendSchemaId::schema_alloy_gpio_nxp_imxrt_gpio_v1, 1, 0x401B8000u, ClockGateId::mimxrt1062_gate_gpio1, ResetId::none, ClockSelectorId::none, 0u, 0u, 0u, 0u, 0u, 2u, 3},
  {PeripheralId::GPIO4, PeripheralClassId::class_gpio, BackendSchemaId::schema_alloy_gpio_nxp_imxrt_gpio_v1, 4, 0x401C4000u, ClockGateId::mimxrt1062_gate_gpio4, ResetId::none, ClockSelectorId::none, 0u, 0u, 0u, 0u, 2u, 2u, 3},
  {PeripheralId::LPI2C1, PeripheralClassId::class_lpi2c1, BackendSchemaId::schema_alloy_lpi2c1_nxp_lpi2c_v1, 0, 0x403F0000u, ClockGateId::mimxrt1062_gate_lpi2c1, ResetId::none, ClockSelectorId::mimxrt1062_selector_lpi2c_root, 0u, 1u, 0u, 0u, 4u, 2u, 0},
  {PeripheralId::LPSPI1, PeripheralClassId::class_spi, BackendSchemaId::schema_alloy_spi_nxp_lpspi_v1, 1, 0x40394000u, ClockGateId::mimxrt1062_gate_lpspi1, ResetId::none, ClockSelectorId::mimxrt1062_selector_lpspi_root, 1u, 1u, 0u, 0u, 6u, 2u, 0},
  {PeripheralId::LPUART1, PeripheralClassId::class_uart, BackendSchemaId::schema_alloy_uart_nxp_lpuart_v1, 1, 0x40184000u, ClockGateId::mimxrt1062_gate_lpuart1, ResetId::none, ClockSelectorId::mimxrt1062_selector_lpuart_root, 2u, 1u, 0u, 0u, 8u, 2u, 4},
  {PeripheralId::LPUART3, PeripheralClassId::class_uart, BackendSchemaId::schema_alloy_uart_nxp_lpuart_v1, 3, 0x4018C000u, ClockGateId::mimxrt1062_gate_lpuart3, ResetId::none, ClockSelectorId::none, 3u, 1u, 0u, 0u, 0u, 0u, 4},
}};
}
}
}
}
}
