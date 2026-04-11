#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
inline constexpr const char* kDevice = "mimxrt1062";
struct PeripheralBase {
  PeripheralId peripheral_id;
  const char* name;
  std::uintptr_t address;
};
inline constexpr std::array<PeripheralBase, 6> kPeripheralBases = {{
  {PeripheralId::GPIO1, "GPIO1", 0x401B8000u},
  {PeripheralId::GPIO4, "GPIO4", 0x401C4000u},
  {PeripheralId::LPI2C1, "LPI2C1", 0x403F0000u},
  {PeripheralId::LPSPI1, "LPSPI1", 0x40394000u},
  {PeripheralId::LPUART1, "LPUART1", 0x40184000u},
  {PeripheralId::LPUART3, "LPUART3", 0x4018C000u},
}};

struct RegisterDescriptor {
  PeripheralId peripheral_id;
  const char* peripheral_name;
  const char* register_name;
  std::uint32_t offset_bytes;
  const char* access;
  int size_bits;
};
inline constexpr std::array<RegisterDescriptor, 14> kRegisters = {{
  {PeripheralId::GPIO1, "GPIO1", "DR", 0u, nullptr, -1},
  {PeripheralId::GPIO1, "GPIO1", "GDIR", 4u, nullptr, -1},
  {PeripheralId::GPIO1, "GPIO1", "PSR", 8u, nullptr, -1},
  {PeripheralId::GPIO4, "GPIO4", "DR", 0u, nullptr, -1},
  {PeripheralId::GPIO4, "GPIO4", "GDIR", 4u, nullptr, -1},
  {PeripheralId::GPIO4, "GPIO4", "PSR", 8u, nullptr, -1},
  {PeripheralId::LPUART1, "LPUART1", "BAUD", 16u, nullptr, -1},
  {PeripheralId::LPUART1, "LPUART1", "STAT", 20u, nullptr, -1},
  {PeripheralId::LPUART1, "LPUART1", "CTRL", 24u, nullptr, -1},
  {PeripheralId::LPUART1, "LPUART1", "DATA", 28u, nullptr, -1},
  {PeripheralId::LPUART3, "LPUART3", "BAUD", 16u, nullptr, -1},
  {PeripheralId::LPUART3, "LPUART3", "STAT", 20u, nullptr, -1},
  {PeripheralId::LPUART3, "LPUART3", "CTRL", 24u, nullptr, -1},
  {PeripheralId::LPUART3, "LPUART3", "DATA", 28u, nullptr, -1},
}};
}
}
}
}
}
