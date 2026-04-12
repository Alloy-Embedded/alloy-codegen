#pragma once

#include <array>
#include <cstdint>
#include "../runtime_semantics.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace ip {
struct IpBlockDescriptor {
  IpBlockId ip_block_id;
  PeripheralClassId peripheral_class_id;
  BackendSchemaId schema_id;
  RegisterProfileId register_profile_id;
  std::uint16_t signal_role_offset;
  std::uint16_t signal_role_count;
};
inline constexpr IpBlockDescriptor kIpBlock = {
  IpBlockId::ip_block_gpio_imxrt_gpio_v1,
  PeripheralClassId::class_gpio,
  BackendSchemaId::schema_alloy_gpio_nxp_imxrt_gpio_v1,
  RegisterProfileId::register_profile_gpio_imxrt_gpio_v1,
  0u,
  2u,
};

struct IpBlockSignalRoleRef {
  IpBlockId ip_block_id;
  SignalRoleId signal_role_id;
};
inline constexpr std::array<IpBlockSignalRoleRef, 2> kSignalRoles = {{
  {IpBlockId::ip_block_gpio_imxrt_gpio_v1, SignalRoleId::signal_role_io00},
  {IpBlockId::ip_block_gpio_imxrt_gpio_v1, SignalRoleId::signal_role_io01},
}};

struct CapabilityDescriptor {
  CapabilityId capability_id;
  CapabilityScopeId scope_id;
  PeripheralClassId peripheral_class_id;
  CapabilityKeyId capability_key_id;
  IpBlockId ip_block_id;
};
inline constexpr std::array<CapabilityDescriptor, 2> kCapabilities = {{
  {CapabilityId::capability_id_capability_gpio_imxrt_gpio_v1_io00, CapabilityScopeId::capability_scope_ip_block, PeripheralClassId::class_gpio, CapabilityKeyId::capability_signal_role_io00, IpBlockId::ip_block_gpio_imxrt_gpio_v1},
  {CapabilityId::capability_id_capability_gpio_imxrt_gpio_v1_io01, CapabilityScopeId::capability_scope_ip_block, PeripheralClassId::class_gpio, CapabilityKeyId::capability_signal_role_io01, IpBlockId::ip_block_gpio_imxrt_gpio_v1},
}};
}
}
}
}
