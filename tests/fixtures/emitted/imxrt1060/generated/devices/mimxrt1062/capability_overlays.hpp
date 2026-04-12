#pragma once

#include <array>
#include <cstdint>
#include "../../runtime_refs.hpp"
#include "../../runtime_semantics.hpp"
#include "peripheral_instances.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
struct CapabilityOverlayDescriptor {
  CapabilityId capability_id;
  CapabilityScopeId scope_id;
  PeripheralClassId peripheral_class_id;
  CapabilityKeyId capability_key_id;
  IpBlockId ip_block_id;
  PeripheralId peripheral_id;
  PackageRefId package_id;
};
inline constexpr std::array<CapabilityOverlayDescriptor, 10> kCapabilityOverlays = {{
  {CapabilityId::capability_id_capability_instance_gpio1_bga196_io00, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_gpio, CapabilityKeyId::capability_available_signal_io00, IpBlockId::ip_block_gpio_imxrt_gpio_v1, PeripheralId::GPIO1, PackageRefId::mimxrt1062_bga196},
  {CapabilityId::capability_id_capability_instance_gpio1_bga196_io01, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_gpio, CapabilityKeyId::capability_available_signal_io01, IpBlockId::ip_block_gpio_imxrt_gpio_v1, PeripheralId::GPIO1, PackageRefId::mimxrt1062_bga196},
  {CapabilityId::capability_id_capability_instance_gpio4_bga196_io00, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_gpio, CapabilityKeyId::capability_available_signal_io00, IpBlockId::ip_block_gpio_imxrt_gpio_v1, PeripheralId::GPIO4, PackageRefId::mimxrt1062_bga196},
  {CapabilityId::capability_id_capability_instance_gpio4_bga196_io01, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_gpio, CapabilityKeyId::capability_available_signal_io01, IpBlockId::ip_block_gpio_imxrt_gpio_v1, PeripheralId::GPIO4, PackageRefId::mimxrt1062_bga196},
  {CapabilityId::capability_id_capability_instance_lpi2c1_bga196_scl, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_lpi2c1, CapabilityKeyId::capability_available_signal_scl, IpBlockId::ip_block_lpi2c1_lpi2c_v1, PeripheralId::LPI2C1, PackageRefId::mimxrt1062_bga196},
  {CapabilityId::capability_id_capability_instance_lpi2c1_bga196_sda, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_lpi2c1, CapabilityKeyId::capability_available_signal_sda, IpBlockId::ip_block_lpi2c1_lpi2c_v1, PeripheralId::LPI2C1, PackageRefId::mimxrt1062_bga196},
  {CapabilityId::capability_id_capability_instance_lpspi1_bga196_cs, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_spi, CapabilityKeyId::capability_available_signal_cs, IpBlockId::ip_block_lpspi_lpspi_v1, PeripheralId::LPSPI1, PackageRefId::mimxrt1062_bga196},
  {CapabilityId::capability_id_capability_instance_lpspi1_bga196_sck, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_spi, CapabilityKeyId::capability_available_signal_sck, IpBlockId::ip_block_lpspi_lpspi_v1, PeripheralId::LPSPI1, PackageRefId::mimxrt1062_bga196},
  {CapabilityId::capability_id_capability_instance_lpuart1_bga196_rx, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_uart, CapabilityKeyId::capability_available_signal_rx, IpBlockId::ip_block_lpuart_lpuart_v1, PeripheralId::LPUART1, PackageRefId::mimxrt1062_bga196},
  {CapabilityId::capability_id_capability_instance_lpuart1_bga196_tx, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_uart, CapabilityKeyId::capability_available_signal_tx, IpBlockId::ip_block_lpuart_lpuart_v1, PeripheralId::LPUART1, PackageRefId::mimxrt1062_bga196},
}};
}
}
}
}
}
