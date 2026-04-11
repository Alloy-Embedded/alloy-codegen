#pragma once

#include <array>

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace ip {
struct IpBlockDescriptor {
  const char* ip_name;
  const char* ip_version;
  const char* peripheral_class;
  const char* backend_schema_id;
  const char* register_profile;
  const char* signal_roles;
};
inline constexpr IpBlockDescriptor kIpBlock = {
  "lpi2c1",
  "lpi2c-v1",
  "lpi2c1",
  "alloy.lpi2c1.nxp-lpi2c-v1",
  "lpi2c1:lpi2c-v1",
  "scl,sda",
};

struct CapabilityDescriptor {
  const char* capability_id;
  const char* scope;
  const char* peripheral_class;
  const char* name;
  const char* value;
  const char* ip_name;
  const char* ip_version;
  const char* peripheral;
  const char* package;
};
inline constexpr std::array<CapabilityDescriptor, 2> kCapabilities = {{
  {"capability:lpi2c1:lpi2c-v1:scl", "ip-block", "lpi2c1", "signal-role", "scl", "lpi2c1", "lpi2c-v1", nullptr, nullptr},
  {"capability:lpi2c1:lpi2c-v1:sda", "ip-block", "lpi2c1", "signal-role", "sda", "lpi2c1", "lpi2c-v1", nullptr, nullptr},
}};
}
}
}
}
