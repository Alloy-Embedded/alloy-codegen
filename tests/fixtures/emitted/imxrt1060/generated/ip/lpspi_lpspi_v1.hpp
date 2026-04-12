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
  IpBlockId::ip_block_lpspi_lpspi_v1,
  PeripheralClassId::class_spi,
  BackendSchemaId::schema_alloy_spi_nxp_lpspi_v1,
  RegisterProfileId::register_profile_lpspi_lpspi_v1,
  0u,
  2u,
};

struct IpBlockSignalRoleRef {
  IpBlockId ip_block_id;
  SignalRoleId signal_role_id;
};
inline constexpr std::array<IpBlockSignalRoleRef, 2> kSignalRoles = {{
  {IpBlockId::ip_block_lpspi_lpspi_v1, SignalRoleId::signal_role_cs},
  {IpBlockId::ip_block_lpspi_lpspi_v1, SignalRoleId::signal_role_sck},
}};

struct CapabilityDescriptor {
  CapabilityId capability_id;
  CapabilityScopeId scope_id;
  PeripheralClassId peripheral_class_id;
  CapabilityKeyId capability_key_id;
  IpBlockId ip_block_id;
};
inline constexpr std::array<CapabilityDescriptor, 2> kCapabilities = {{
  {CapabilityId::capability_id_capability_lpspi_lpspi_v1_cs, CapabilityScopeId::capability_scope_ip_block, PeripheralClassId::class_spi, CapabilityKeyId::capability_signal_role_cs, IpBlockId::ip_block_lpspi_lpspi_v1},
  {CapabilityId::capability_id_capability_lpspi_lpspi_v1_sck, CapabilityScopeId::capability_scope_ip_block, PeripheralClassId::class_spi, CapabilityKeyId::capability_signal_role_sck, IpBlockId::ip_block_lpspi_lpspi_v1},
}};
}
}
}
}
