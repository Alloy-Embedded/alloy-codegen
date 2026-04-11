#pragma once

#include <array>
#include <cstdint>
#include "peripheral_instances.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace devices {
namespace stm32g071rb {
enum class DmaBindingId : std::uint16_t {
  dma_binding_usart1_rx_dma1_dma1_ch1,
  dma_binding_usart1_tx_dma1_dma1_ch2,
};

struct DmaBindingDescriptor {
  DmaBindingId binding_id;
  PeripheralId peripheral_id;
  const char* peripheral_name;
  const char* signal_name;
  const char* controller_name;
  const char* request_line;
  const char* route_id;
  const char* conflict_group;
};
inline constexpr std::array<DmaBindingDescriptor, 2> kDmaBindings = {{
  {DmaBindingId::dma_binding_usart1_rx_dma1_dma1_ch1, PeripheralId::USART1, "USART1", "RX", "DMA1", "DMA1_CH1", "dma-route:dma1:dma1-ch1:usart1:rx", nullptr},
  {DmaBindingId::dma_binding_usart1_tx_dma1_dma1_ch2, PeripheralId::USART1, "USART1", "TX", "DMA1", "DMA1_CH2", "dma-route:dma1:dma1-ch2:usart1:tx", nullptr},
}};
}
}
}
}
}
