#pragma once

#include <array>
#include <cstdint>
#include "../../runtime_refs.hpp"
#include "../../runtime_semantics.hpp"
#include "peripheral_instances.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace devices {
namespace stm32g071rb {
inline constexpr DeviceRefId kDeviceId = DeviceRefId::stm32g071rb;
struct PeripheralBase {
  PeripheralId peripheral_id;
  std::uintptr_t address;
};
inline constexpr std::array<PeripheralBase, 6> kPeripheralBases = {{
  {PeripheralId::DMA1, 0x40020000u},
  {PeripheralId::DMAMUX1, 0x40020800u},
  {PeripheralId::GPIOA, 0x50000000u},
  {PeripheralId::GPIOB, 0x50000400u},
  {PeripheralId::RCC, 0x40021000u},
  {PeripheralId::USART1, 0x40013800u},
}};

enum class RegisterId : std::uint16_t {
  register_gpioa_moder,
  register_gpioa_afrl,
  register_gpioa_afrh,
  register_gpiob_moder,
  register_gpiob_afrl,
  register_gpiob_afrh,
  register_rcc_ioprstr,
  register_rcc_ahbrstr,
  register_rcc_apbrstr1,
  register_rcc_apbrstr2,
  register_rcc_iopenr,
  register_rcc_ahbenr,
  register_rcc_apbenr1,
  register_rcc_apbenr2,
  register_usart1_cr1,
  register_usart1_cr2,
  register_usart1_brr,
  register_usart1_isr,
  register_usart1_rdr,
  register_usart1_tdr,
};

struct RegisterDescriptor {
  RegisterId register_id;
  PeripheralId peripheral_id;
  std::uint32_t offset_bytes;
  AccessKindId access_id;
  int size_bits;
};
inline constexpr std::array<RegisterDescriptor, 20> kRegisters = {{
  {RegisterId::register_gpioa_moder, PeripheralId::GPIOA, 0u, AccessKindId::none, -1},
  {RegisterId::register_gpioa_afrl, PeripheralId::GPIOA, 32u, AccessKindId::none, -1},
  {RegisterId::register_gpioa_afrh, PeripheralId::GPIOA, 36u, AccessKindId::none, -1},
  {RegisterId::register_gpiob_moder, PeripheralId::GPIOB, 0u, AccessKindId::none, -1},
  {RegisterId::register_gpiob_afrl, PeripheralId::GPIOB, 32u, AccessKindId::none, -1},
  {RegisterId::register_gpiob_afrh, PeripheralId::GPIOB, 36u, AccessKindId::none, -1},
  {RegisterId::register_rcc_ioprstr, PeripheralId::RCC, 36u, AccessKindId::none, -1},
  {RegisterId::register_rcc_ahbrstr, PeripheralId::RCC, 40u, AccessKindId::none, -1},
  {RegisterId::register_rcc_apbrstr1, PeripheralId::RCC, 44u, AccessKindId::none, -1},
  {RegisterId::register_rcc_apbrstr2, PeripheralId::RCC, 48u, AccessKindId::none, -1},
  {RegisterId::register_rcc_iopenr, PeripheralId::RCC, 52u, AccessKindId::none, -1},
  {RegisterId::register_rcc_ahbenr, PeripheralId::RCC, 56u, AccessKindId::none, -1},
  {RegisterId::register_rcc_apbenr1, PeripheralId::RCC, 60u, AccessKindId::none, -1},
  {RegisterId::register_rcc_apbenr2, PeripheralId::RCC, 64u, AccessKindId::none, -1},
  {RegisterId::register_usart1_cr1, PeripheralId::USART1, 0u, AccessKindId::none, -1},
  {RegisterId::register_usart1_cr2, PeripheralId::USART1, 4u, AccessKindId::none, -1},
  {RegisterId::register_usart1_brr, PeripheralId::USART1, 12u, AccessKindId::none, -1},
  {RegisterId::register_usart1_isr, PeripheralId::USART1, 28u, AccessKindId::none, -1},
  {RegisterId::register_usart1_rdr, PeripheralId::USART1, 36u, AccessKindId::none, -1},
  {RegisterId::register_usart1_tdr, PeripheralId::USART1, 40u, AccessKindId::none, -1},
}};
}
}
}
}
}
