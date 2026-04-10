#pragma once

#include <cstddef>
#include <cstdint>

namespace st {
namespace stm32g0 {
namespace generated {
struct MemoryDescriptor {
  const char* device;
  const char* name;
  const char* kind;
  std::uintptr_t base_address;
  std::size_t size_bytes;
  const char* access;
  const char* startup_roles;
};
inline constexpr MemoryDescriptor kMemoryMap[] = {
  {"stm32g071rb", "flash", "flash", 0x08000000u, 131072u, "rx", "nonvolatile,copy-source,vector-source"},
  {"stm32g071rb", "sram", "sram", 0x20000000u, 36864u, "rwx", "volatile-target,copy-target,zero-target,stack-target"},
};
}
}
}
