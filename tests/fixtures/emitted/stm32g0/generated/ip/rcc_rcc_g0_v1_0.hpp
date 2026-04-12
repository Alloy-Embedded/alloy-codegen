#pragma once

#include <array>
#include <cstdint>
#include "../runtime_semantics.hpp"

namespace st {
namespace stm32g0 {
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
  IpBlockId::ip_block_rcc_rcc_g0_v1_0,
  PeripheralClassId::class_rcc,
  BackendSchemaId::schema_alloy_rcc_st_rcc_g0_v1_0,
  RegisterProfileId::register_profile_rcc_rcc_g0_v1_0,
  0u,
  0u,
};

struct IpBlockSignalRoleRef {
  IpBlockId ip_block_id;
  SignalRoleId signal_role_id;
};
inline constexpr std::array<IpBlockSignalRoleRef, 0> kSignalRoles = {};

struct CapabilityDescriptor {
  CapabilityId capability_id;
  CapabilityScopeId scope_id;
  PeripheralClassId peripheral_class_id;
  CapabilityKeyId capability_key_id;
  IpBlockId ip_block_id;
};
inline constexpr std::array<CapabilityDescriptor, 0> kCapabilities = {};
}
}
}
}
