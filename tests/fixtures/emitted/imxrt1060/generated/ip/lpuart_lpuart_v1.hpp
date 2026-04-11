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
  "lpuart",
  "lpuart-v1",
  "uart",
  "alloy.uart.nxp-lpuart-v1",
  "lpuart:lpuart-v1",
  "rx,tx",
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
  {"capability:lpuart:lpuart-v1:rx", "ip-block", "uart", "signal-role", "rx", "lpuart", "lpuart-v1", nullptr, nullptr},
  {"capability:lpuart:lpuart-v1:tx", "ip-block", "uart", "signal-role", "tx", "lpuart", "lpuart-v1", nullptr, nullptr},
}};
}
}
}
}
