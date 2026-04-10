#pragma once

namespace st {
namespace stm32g0 {
namespace generated {
namespace ip {
struct IpBlockDescriptor {
  const char* ip_name;
  const char* ip_version;
  const char* peripheral_class;
  const char* register_profile;
  const char* signal_roles;
};
inline constexpr IpBlockDescriptor kIpBlock = {
  "usart",
  "usart_v3_1",
  "uart",
  "usart:usart_v3_1",
  "rx,tx",
};

struct CapabilityDescriptor {
  const char* capability_id;
  const char* peripheral_class;
  const char* name;
  const char* value;
};
inline constexpr CapabilityDescriptor kCapabilities[] = {
  {"capability:usart:usart-v3-1:rx", "uart", "signal-role", "rx"},
  {"capability:usart:usart-v3-1:tx", "uart", "signal-role", "tx"},
};
}
}
}
}
