#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g071rb {
enum class DmaBindingId : std::uint16_t {
  none,
  dma_binding_spi1_rx_dma1_dmamux_req_016,
  dma_binding_spi1_tx_dma1_dmamux_req_017,
  dma_binding_usart1_rx_dma1_dma1_ch1,
  dma_binding_usart1_tx_dma1_dma1_ch2,
};

enum class DmaControllerId : std::uint16_t {
  none,
  DMA1,
};

enum class DmaRequestLineId : std::uint16_t {
  none,
  DMAMUX_REQ_016,
  DMAMUX_REQ_017,
  DMA1_CH1,
  DMA1_CH2,
};

enum class DmaRouteId : std::uint16_t {
  none,
  dma_route_dma1_dmamux_req_016_spi1_rx,
  dma_route_dma1_dmamux_req_017_spi1_tx,
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
struct BindingTraits<PeripheralId::SPI1, SignalId::signal_RX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_spi1_rx_dma1_dmamux_req_016;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA1;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::DMAMUX_REQ_016;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma1_dmamux_req_016_spi1_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 16;
  static constexpr int kChannelSelector = -1;
};

template<>
struct BindingTraits<PeripheralId::SPI1, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_spi1_tx_dma1_dmamux_req_017;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA1;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::DMAMUX_REQ_017;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma1_dmamux_req_017_spi1_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 17;
  static constexpr int kChannelSelector = -1;
};

template<>
struct BindingTraits<PeripheralId::USART1, SignalId::signal_RX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_usart1_rx_dma1_dma1_ch1;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA1;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::DMA1_CH1;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma1_dma1_ch1_usart1_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = 0;
  static constexpr int kRequestValue = 50;
  static constexpr int kChannelSelector = -1;
};

template<>
struct BindingTraits<PeripheralId::USART1, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_usart1_tx_dma1_dma1_ch2;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA1;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::DMA1_CH2;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma1_dma1_ch2_usart1_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = 1;
  static constexpr int kRequestValue = 51;
  static constexpr int kChannelSelector = -1;
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
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dma_st_bdma_v1_0;
  static constexpr int kChannelCount = 7;
  static constexpr int kRequestCount = 4;
};

inline constexpr std::array<DmaBindingDescriptor, 4> kDmaBindings = {{
  {DmaBindingId::dma_binding_spi1_rx_dma1_dmamux_req_016, PeripheralId::SPI1, SignalId::signal_RX, DmaControllerId::DMA1, DmaRequestLineId::DMAMUX_REQ_016, DmaRouteId::dma_route_dma1_dmamux_req_016_spi1_rx, DmaConflictGroupId::none, -1, 16, -1},
  {DmaBindingId::dma_binding_spi1_tx_dma1_dmamux_req_017, PeripheralId::SPI1, SignalId::signal_TX, DmaControllerId::DMA1, DmaRequestLineId::DMAMUX_REQ_017, DmaRouteId::dma_route_dma1_dmamux_req_017_spi1_tx, DmaConflictGroupId::none, -1, 17, -1},
  {DmaBindingId::dma_binding_usart1_rx_dma1_dma1_ch1, PeripheralId::USART1, SignalId::signal_RX, DmaControllerId::DMA1, DmaRequestLineId::DMA1_CH1, DmaRouteId::dma_route_dma1_dma1_ch1_usart1_rx, DmaConflictGroupId::none, 0, 50, -1},
  {DmaBindingId::dma_binding_usart1_tx_dma1_dma1_ch2, PeripheralId::USART1, SignalId::signal_TX, DmaControllerId::DMA1, DmaRequestLineId::DMA1_CH2, DmaRouteId::dma_route_dma1_dma1_ch2_usart1_tx, DmaConflictGroupId::none, 1, 51, -1},
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
