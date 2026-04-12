#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include "runtime_refs.hpp"
#include "runtime_semantics.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
enum class MemoryRegionId : std::uint16_t {
  none,
  mimxrt1062_OCRAM,
};

struct MemoryDescriptor {
  DeviceRefId device_id;
  MemoryRegionId region_id;
  MemoryKindId kind_id;
  std::uintptr_t base_address;
  std::size_t size_bytes;
  AccessKindId access_id;
  std::uint16_t startup_role_offset;
  std::uint16_t startup_role_count;
};
inline constexpr MemoryDescriptor kMemoryMap[] = {
  {DeviceRefId::mimxrt1062, MemoryRegionId::mimxrt1062_OCRAM, MemoryKindId::memory_kind_ram, 0x20200000u, 1048576u, AccessKindId::access_kind_read_write, 0u, 4u},
};

struct MemoryStartupRoleRef {
  MemoryRegionId region_id;
  StartupRoleId startup_role_id;
};
inline constexpr std::array<MemoryStartupRoleRef, 4> kMemoryStartupRoles = {{
  {MemoryRegionId::mimxrt1062_OCRAM, StartupRoleId::startup_role_volatile_target},
  {MemoryRegionId::mimxrt1062_OCRAM, StartupRoleId::startup_role_copy_target},
  {MemoryRegionId::mimxrt1062_OCRAM, StartupRoleId::startup_role_zero_target},
  {MemoryRegionId::mimxrt1062_OCRAM, StartupRoleId::startup_role_stack_target},
}};
}
}
}
