#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f405rg {
enum class DmaBindingId : std::uint16_t {
  none,
  dma_binding_usart1_rx_dma2_dma2_stream2,
  dma_binding_usart1_tx_dma2_dma2_stream7,
};

enum class DmaControllerId : std::uint16_t {
  none,
  DMA2,
};

enum class DmaRequestLineId : std::uint16_t {
  none,
  DMA2_STREAM2,
  DMA2_STREAM7,
};

enum class DmaRouteId : std::uint16_t {
  none,
  dma_route_dma2_dma2_stream2_usart1_rx,
  dma_route_dma2_dma2_stream7_usart1_tx,
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
  std::int32_t channel_index;
  std::int32_t request_value;
  std::int32_t channel_selector;
};

template<PeripheralId Peripheral, SignalId Signal>
struct BindingTraits {
  static constexpr bool kPresent = false;
  static constexpr DmaBindingId kBindingId = DmaBindingId::none;
  static constexpr DmaControllerId kControllerId = DmaControllerId::none;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::none;
  static constexpr DmaRouteId kRouteId = DmaRouteId::none;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = -1;
  static constexpr int kChannelSelector = -1;
};

template<>
struct BindingTraits<PeripheralId::USART1, SignalId::signal_RX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_usart1_rx_dma2_dma2_stream2;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA2;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::DMA2_STREAM2;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma2_dma2_stream2_usart1_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = 2;
  static constexpr int kRequestValue = -1;
  static constexpr int kChannelSelector = 4;
};

template<>
struct BindingTraits<PeripheralId::USART1, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_usart1_tx_dma2_dma2_stream7;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA2;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::DMA2_STREAM7;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma2_dma2_stream7_usart1_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = 7;
  static constexpr int kRequestValue = -1;
  static constexpr int kChannelSelector = 4;
};

template<DmaControllerId Id>
struct ControllerTraits {
  static constexpr bool kPresent = false;
  static constexpr PeripheralId kPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::none;
  static constexpr int kChannelCount = -1;
  static constexpr int kRequestCount = -1;
};

template<>
struct ControllerTraits<DmaControllerId::DMA2> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::DMA2;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dma_st_bdma_f4_v1_0;
  static constexpr int kChannelCount = 8;
  static constexpr int kRequestCount = 2;
};

inline constexpr std::array<DmaBindingDescriptor, 2> kDmaBindings = {{
  {DmaBindingId::dma_binding_usart1_rx_dma2_dma2_stream2, PeripheralId::USART1, SignalId::signal_RX, DmaControllerId::DMA2, DmaRequestLineId::DMA2_STREAM2, DmaRouteId::dma_route_dma2_dma2_stream2_usart1_rx, DmaConflictGroupId::none, 2, -1, 4},
  {DmaBindingId::dma_binding_usart1_tx_dma2_dma2_stream7, PeripheralId::USART1, SignalId::signal_TX, DmaControllerId::DMA2, DmaRequestLineId::DMA2_STREAM7, DmaRouteId::dma_route_dma2_dma2_stream7_usart1_tx, DmaConflictGroupId::none, 7, -1, 4},
}};

inline constexpr std::array<DmaControllerId, 1> kDmaControllers = {{
  DmaControllerId::DMA2,
}};
}
}
}
}
}
}
