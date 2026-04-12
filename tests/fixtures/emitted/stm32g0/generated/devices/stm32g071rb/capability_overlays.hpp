#pragma once

#include <array>
#include <cstdint>
#include "../../runtime_refs.hpp"
#include "../../runtime_semantics.hpp"
#include "peripheral_instances.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace devices {
namespace stm32g071rb {
struct CapabilityOverlayDescriptor {
  CapabilityId capability_id;
  CapabilityScopeId scope_id;
  PeripheralClassId peripheral_class_id;
  CapabilityKeyId capability_key_id;
  IpBlockId ip_block_id;
  PeripheralId peripheral_id;
  PackageRefId package_id;
};
inline constexpr std::array<CapabilityOverlayDescriptor, 2> kCapabilityOverlays = {{
  {CapabilityId::capability_id_capability_instance_usart1_lqfp64_rx, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_uart, CapabilityKeyId::capability_available_signal_rx, IpBlockId::ip_block_usart_usart_v3_1, PeripheralId::USART1, PackageRefId::stm32g071rb_lqfp64},
  {CapabilityId::capability_id_capability_instance_usart1_lqfp64_tx, CapabilityScopeId::capability_scope_instance_overlay, PeripheralClassId::class_uart, CapabilityKeyId::capability_available_signal_tx, IpBlockId::ip_block_usart_usart_v3_1, PeripheralId::USART1, PackageRefId::stm32g071rb_lqfp64},
}};
}
}
}
}
}
