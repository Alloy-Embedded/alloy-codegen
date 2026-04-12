#pragma once

#include <array>
#include "runtime_semantics.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
enum class DmaMapPeripheralId : std::uint16_t {
  none,
  USART1,
};

enum class DmaMapControllerId : std::uint16_t {
  none,
  DMA1,
};

enum class DmaMapRequestLineId : std::uint16_t {
  none,
  DMA1_CH1,
  DMA1_CH2,
};

struct DmaDescriptor {
  DmaMapPeripheralId peripheral_id;
  SignalId signal_id;
  DmaMapControllerId controller_id;
  DmaMapRequestLineId request_line_id;
};
inline constexpr std::array<DmaDescriptor, 2> kDmaMap = {{
  {DmaMapPeripheralId::USART1, SignalId::signal_RX, DmaMapControllerId::DMA1, DmaMapRequestLineId::DMA1_CH1},
  {DmaMapPeripheralId::USART1, SignalId::signal_TX, DmaMapControllerId::DMA1, DmaMapRequestLineId::DMA1_CH2},
}};
}
}
}
