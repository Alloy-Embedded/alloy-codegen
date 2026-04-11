#pragma once

#include <array>

namespace st {
namespace stm32g0 {
namespace generated {
namespace devices {
namespace stm32g071rb {
struct CapabilityOverlayDescriptor {
  const char* capability_id;
  const char* scope;
  const char* peripheral_class;
  const char* name;
  const char* value;
  const char* ip_name;
  const char* ip_version;
  const char* peripheral;
  const char* package_name;
};
inline constexpr std::array<CapabilityOverlayDescriptor, 2> kCapabilityOverlays = {{
  {"capability-instance:usart1:lqfp64:rx", "instance-overlay", "uart", "available-signal", "rx", "usart", "usart_v3_1", "USART1", "lqfp64"},
  {"capability-instance:usart1:lqfp64:tx", "instance-overlay", "uart", "available-signal", "tx", "usart", "usart_v3_1", "USART1", "lqfp64"},
}};
}
}
}
}
}
