#pragma once

#include <array>
#include <cstdint>
#include "../../runtime_semantics.hpp"
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

enum class DmaControllerId : std::uint16_t {
  none,
  DMA1,
};

enum class DmaRequestLineId : std::uint16_t {
  none,
  DMA1_CH1,
  DMA1_CH2,
};

enum class DmaRouteId : std::uint16_t {
  none,
  dma_route_dma1_dma1_ch1_usart1_rx,
  dma_route_dma1_dma1_ch2_usart1_tx,
};

enum class DmaConflictGroupId : std::uint16_t {
  none,
};

struct DmaBindingDescriptor {
  DmaBindingId binding_id;
  PeripheralId peripheral_id;
  SignalId signal_id;
  DmaControllerId controller_id;
  DmaRequestLineId request_line_id;
  DmaRouteId route_id;
  DmaConflictGroupId conflict_group_id;
};
inline constexpr std::array<DmaBindingDescriptor, 2> kDmaBindings = {{
  {DmaBindingId::dma_binding_usart1_rx_dma1_dma1_ch1, PeripheralId::USART1, SignalId::signal_RX, DmaControllerId::DMA1, DmaRequestLineId::DMA1_CH1, DmaRouteId::dma_route_dma1_dma1_ch1_usart1_rx, DmaConflictGroupId::none},
  {DmaBindingId::dma_binding_usart1_tx_dma1_dma1_ch2, PeripheralId::USART1, SignalId::signal_TX, DmaControllerId::DMA1, DmaRequestLineId::DMA1_CH2, DmaRouteId::dma_route_dma1_dma1_ch2_usart1_tx, DmaConflictGroupId::none},
}};
}
}
}
}
}
