#pragma once

#include <array>

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
  {"capability:usart:usart-v3-1:rx", "ip-block", "uart", "signal-role", "rx", "usart", "usart_v3_1", nullptr, nullptr},
  {"capability:usart:usart-v3-1:tx", "ip-block", "uart", "signal-role", "tx", "usart", "usart_v3_1", nullptr, nullptr},
}};
}
}
}
}
