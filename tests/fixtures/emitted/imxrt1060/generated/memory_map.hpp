#pragma once

#include <cstddef>
#include <cstdint>

namespace nxp {
namespace imxrt1060 {
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
  {"mimxrt1062", "OCRAM", "ram", 0x20200000u, 1048576u, "read-write", "volatile-target,copy-target,zero-target,stack-target"},
};
}
}
}
