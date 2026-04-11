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
  "lpspi",
  "lpspi-v1",
  "spi",
  "alloy.spi.nxp-lpspi-v1",
  "lpspi:lpspi-v1",
  "cs,sck",
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
  {"capability:lpspi:lpspi-v1:cs", "ip-block", "spi", "signal-role", "cs", "lpspi", "lpspi-v1", nullptr, nullptr},
  {"capability:lpspi:lpspi-v1:sck", "ip-block", "spi", "signal-role", "sck", "lpspi", "lpspi-v1", nullptr, nullptr},
}};
}
}
}
}
