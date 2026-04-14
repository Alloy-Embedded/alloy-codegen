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
inline constexpr std::array<PeripheralBase, 9> kPeripheralBases = {{
  {PeripheralId::CCM, 0x400FC000u},
  {PeripheralId::CCM_ANALOG, 0x400D8000u},
  {PeripheralId::DCDC, 0x40080000u},
  {PeripheralId::GPIO1, 0x401B8000u},
  {PeripheralId::GPIO4, 0x401C4000u},
  {PeripheralId::LPI2C1, 0x403F0000u},
  {PeripheralId::LPSPI1, 0x40394000u},
  {PeripheralId::LPUART1, 0x40184000u},
  {PeripheralId::LPUART3, 0x4018C000u},
}};

enum class RegisterId : std::uint16_t {
  register_ccm_cacrr,
  register_ccm_cbcdr,
  register_ccm_cbcmr,
  register_ccm_cscdr1,
  register_ccm_cscdr2,
  register_ccm_cdhipr,
  register_ccm_ccgr0,
  register_ccm_ccgr1,
  register_ccm_ccgr2,
  register_ccm_ccgr3,
  register_ccm_ccgr5,
  register_ccm_ccgr6,
  register_ccm_ccgr7,
  register_ccm_analog_pll_arm,
  register_dcdc_reg0,
  register_dcdc_reg3,
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
inline constexpr std::array<RegisterDescriptor, 30> kRegisters = {{
  {RegisterId::register_ccm_cacrr, PeripheralId::CCM, 16u, AccessKindId::access_kind_read_write, 32},
  {RegisterId::register_ccm_cbcdr, PeripheralId::CCM, 20u, AccessKindId::access_kind_read_write, 32},
  {RegisterId::register_ccm_cbcmr, PeripheralId::CCM, 24u, AccessKindId::access_kind_read_write, 32},
  {RegisterId::register_ccm_cscdr1, PeripheralId::CCM, 36u, AccessKindId::access_kind_read_write, 32},
  {RegisterId::register_ccm_cscdr2, PeripheralId::CCM, 56u, AccessKindId::access_kind_read_write, 32},
  {RegisterId::register_ccm_cdhipr, PeripheralId::CCM, 72u, AccessKindId::access_kind_read_only, 32},
  {RegisterId::register_ccm_ccgr0, PeripheralId::CCM, 104u, AccessKindId::access_kind_read_write, 32},
  {RegisterId::register_ccm_ccgr1, PeripheralId::CCM, 108u, AccessKindId::access_kind_read_write, 32},
  {RegisterId::register_ccm_ccgr2, PeripheralId::CCM, 112u, AccessKindId::access_kind_read_write, 32},
  {RegisterId::register_ccm_ccgr3, PeripheralId::CCM, 116u, AccessKindId::access_kind_read_write, 32},
  {RegisterId::register_ccm_ccgr5, PeripheralId::CCM, 124u, AccessKindId::access_kind_read_write, 32},
  {RegisterId::register_ccm_ccgr6, PeripheralId::CCM, 128u, AccessKindId::access_kind_read_write, 32},
  {RegisterId::register_ccm_ccgr7, PeripheralId::CCM, 132u, AccessKindId::access_kind_read_write, 32},
  {RegisterId::register_ccm_analog_pll_arm, PeripheralId::CCM_ANALOG, 0u, AccessKindId::access_kind_read_write, 32},
  {RegisterId::register_dcdc_reg0, PeripheralId::DCDC, 0u, AccessKindId::access_kind_read_only, 32},
  {RegisterId::register_dcdc_reg3, PeripheralId::DCDC, 12u, AccessKindId::access_kind_read_write, 32},
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
