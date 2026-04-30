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
namespace stm32f401re {
enum class DmaBindingId : std::uint16_t {
  none,
  dma_binding_usart2_rx_dma1_dma1_stream5,
  dma_binding_usart2_tx_dma1_dma1_stream6,
};

enum class DmaControllerId : std::uint16_t {
  none,
  DMA1,
};

enum class DmaRequestLineId : std::uint16_t {
  none,
  DMA1_STREAM5,
  DMA1_STREAM6,
};

enum class DmaRouteId : std::uint16_t {
  none,
  dma_route_dma1_dma1_stream5_usart2_rx,
  dma_route_dma1_dma1_stream6_usart2_tx,
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
struct BindingTraits<PeripheralId::USART2, SignalId::signal_RX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_usart2_rx_dma1_dma1_stream5;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA1;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::DMA1_STREAM5;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma1_dma1_stream5_usart2_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = 5;
  static constexpr int kRequestValue = -1;
  static constexpr int kChannelSelector = 4;
};

template<>
struct BindingTraits<PeripheralId::USART2, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_usart2_tx_dma1_dma1_stream6;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA1;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::DMA1_STREAM6;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma1_dma1_stream6_usart2_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = 6;
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
struct ControllerTraits<DmaControllerId::DMA1> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::DMA1;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dma_st_bdma_f4_v1_0;
  static constexpr int kChannelCount = 8;
  static constexpr int kRequestCount = 2;
};

inline constexpr std::array<DmaBindingDescriptor, 2> kDmaBindings = {{
  {DmaBindingId::dma_binding_usart2_rx_dma1_dma1_stream5, PeripheralId::USART2, SignalId::signal_RX, DmaControllerId::DMA1, DmaRequestLineId::DMA1_STREAM5, DmaRouteId::dma_route_dma1_dma1_stream5_usart2_rx, DmaConflictGroupId::none, 5, -1, 4},
  {DmaBindingId::dma_binding_usart2_tx_dma1_dma1_stream6, PeripheralId::USART2, SignalId::signal_TX, DmaControllerId::DMA1, DmaRequestLineId::DMA1_STREAM6, DmaRouteId::dma_route_dma1_dma1_stream6_usart2_tx, DmaConflictGroupId::none, 6, -1, 4},
}};

inline constexpr std::array<DmaControllerId, 1> kDmaControllers = {{
  DmaControllerId::DMA1,
}};
}
}
}
}
}
}
