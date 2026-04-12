#pragma once

#include <array>
#include <cstdint>
#include "../../runtime_refs.hpp"
#include "../../runtime_semantics.hpp"
#include "peripheral_instances.hpp"

namespace nxp {
namespace imxrt1060 {
namespace generated {
namespace devices {
namespace mimxrt1062 {
inline constexpr DeviceRefId kDeviceId = DeviceRefId::mimxrt1062;
struct PeripheralBase {
  PeripheralId peripheral_id;
  std::uintptr_t address;
};
inline constexpr std::array<PeripheralBase, 6> kPeripheralBases = {{
  {PeripheralId::GPIO1, 0x401B8000u},
  {PeripheralId::GPIO4, 0x401C4000u},
  {PeripheralId::LPI2C1, 0x403F0000u},
  {PeripheralId::LPSPI1, 0x40394000u},
  {PeripheralId::LPUART1, 0x40184000u},
  {PeripheralId::LPUART3, 0x4018C000u},
}};

enum class RegisterId : std::uint16_t {
  register_gpio1_dr,
  register_gpio1_gdir,
  register_gpio1_psr,
  register_gpio4_dr,
  register_gpio4_gdir,
  register_gpio4_psr,
  register_lpuart1_baud,
  register_lpuart1_stat,
  register_lpuart1_ctrl,
  register_lpuart1_data,
  register_lpuart3_baud,
  register_lpuart3_stat,
  register_lpuart3_ctrl,
  register_lpuart3_data,
};

struct RegisterDescriptor {
  RegisterId register_id;
  PeripheralId peripheral_id;
  std::uint32_t offset_bytes;
  AccessKindId access_id;
  int size_bits;
};
inline constexpr std::array<RegisterDescriptor, 14> kRegisters = {{
  {RegisterId::register_gpio1_dr, PeripheralId::GPIO1, 0u, AccessKindId::none, -1},
  {RegisterId::register_gpio1_gdir, PeripheralId::GPIO1, 4u, AccessKindId::none, -1},
  {RegisterId::register_gpio1_psr, PeripheralId::GPIO1, 8u, AccessKindId::none, -1},
  {RegisterId::register_gpio4_dr, PeripheralId::GPIO4, 0u, AccessKindId::none, -1},
  {RegisterId::register_gpio4_gdir, PeripheralId::GPIO4, 4u, AccessKindId::none, -1},
  {RegisterId::register_gpio4_psr, PeripheralId::GPIO4, 8u, AccessKindId::none, -1},
  {RegisterId::register_lpuart1_baud, PeripheralId::LPUART1, 16u, AccessKindId::none, -1},
  {RegisterId::register_lpuart1_stat, PeripheralId::LPUART1, 20u, AccessKindId::none, -1},
  {RegisterId::register_lpuart1_ctrl, PeripheralId::LPUART1, 24u, AccessKindId::none, -1},
  {RegisterId::register_lpuart1_data, PeripheralId::LPUART1, 28u, AccessKindId::none, -1},
  {RegisterId::register_lpuart3_baud, PeripheralId::LPUART3, 16u, AccessKindId::none, -1},
  {RegisterId::register_lpuart3_stat, PeripheralId::LPUART3, 20u, AccessKindId::none, -1},
  {RegisterId::register_lpuart3_ctrl, PeripheralId::LPUART3, 24u, AccessKindId::none, -1},
  {RegisterId::register_lpuart3_data, PeripheralId::LPUART3, 28u, AccessKindId::none, -1},
}};
}
}
}
}
}
