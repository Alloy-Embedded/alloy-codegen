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
  "gpio",
  "imxrt-gpio-v1",
  "gpio",
  "alloy.gpio.nxp-imxrt-gpio-v1",
  "gpio:imxrt-gpio-v1",
  "io00,io01",
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
  {"capability:gpio:imxrt-gpio-v1:io00", "ip-block", "gpio", "signal-role", "io00", "gpio", "imxrt-gpio-v1", nullptr, nullptr},
  {"capability:gpio:imxrt-gpio-v1:io01", "ip-block", "gpio", "signal-role", "io01", "gpio", "imxrt-gpio-v1", nullptr, nullptr},
}};
}
}
}
}
