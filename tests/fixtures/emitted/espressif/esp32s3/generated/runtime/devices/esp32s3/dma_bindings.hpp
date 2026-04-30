#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace espressif {
namespace esp32s3 {
namespace generated {
namespace runtime {
namespace devices {
namespace esp32s3 {
enum class DmaBindingId : std::uint16_t {
  none,
  dma_binding_apb_saradc_data_dma_adc,
  dma_binding_spi2_rx_dma_spi2_rx,
  dma_binding_spi2_tx_dma_spi2_tx,
  dma_binding_uart0_rx_dma_uart0_rx,
  dma_binding_uart0_tx_dma_uart0_tx,
};

enum class DmaControllerId : std::uint16_t {
  none,
  DMA,
};

enum class DmaRequestLineId : std::uint16_t {
  none,
  ADC,
  SPI2_RX,
  SPI2_TX,
  UART0_RX,
  UART0_TX,
};

enum class DmaRouteId : std::uint16_t {
  none,
  dma_route_dma_adc_apb_saradc_data,
  dma_route_dma_spi2_rx_spi2_rx,
  dma_route_dma_spi2_tx_spi2_tx,
  dma_route_dma_uart0_rx_uart0_rx,
  dma_route_dma_uart0_tx_uart0_tx,
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
struct BindingTraits<PeripheralId::APB_SARADC, SignalId::signal_DATA> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_apb_saradc_data_dma_adc;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::ADC;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_adc_apb_saradc_data;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 13;
  static constexpr int kChannelSelector = -1;
};

template<>
struct BindingTraits<PeripheralId::SPI2, SignalId::signal_RX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_spi2_rx_dma_spi2_rx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::SPI2_RX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_spi2_rx_spi2_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 2;
  static constexpr int kChannelSelector = -1;
};

template<>
struct BindingTraits<PeripheralId::SPI2, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_spi2_tx_dma_spi2_tx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::SPI2_TX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_spi2_tx_spi2_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 3;
  static constexpr int kChannelSelector = -1;
};

template<>
struct BindingTraits<PeripheralId::UART0, SignalId::signal_RX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_uart0_rx_dma_uart0_rx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::UART0_RX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_uart0_rx_uart0_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 0;
  static constexpr int kChannelSelector = -1;
};

template<>
struct BindingTraits<PeripheralId::UART0, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_uart0_tx_dma_uart0_tx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::UART0_TX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_uart0_tx_uart0_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 1;
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
struct ControllerTraits<DmaControllerId::DMA> {
  static constexpr bool kPresent = true;
  static constexpr PeripheralId kPeripheralId = PeripheralId::DMA;
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dma_espressif_esp32s3_gdma_v1;
  static constexpr int kChannelCount = 5;
  static constexpr int kRequestCount = 5;
};

inline constexpr std::array<DmaBindingDescriptor, 5> kDmaBindings = {{
  {DmaBindingId::dma_binding_apb_saradc_data_dma_adc, PeripheralId::APB_SARADC, SignalId::signal_DATA, DmaControllerId::DMA, DmaRequestLineId::ADC, DmaRouteId::dma_route_dma_adc_apb_saradc_data, DmaConflictGroupId::none, -1, 13, -1},
  {DmaBindingId::dma_binding_spi2_rx_dma_spi2_rx, PeripheralId::SPI2, SignalId::signal_RX, DmaControllerId::DMA, DmaRequestLineId::SPI2_RX, DmaRouteId::dma_route_dma_spi2_rx_spi2_rx, DmaConflictGroupId::none, -1, 2, -1},
  {DmaBindingId::dma_binding_spi2_tx_dma_spi2_tx, PeripheralId::SPI2, SignalId::signal_TX, DmaControllerId::DMA, DmaRequestLineId::SPI2_TX, DmaRouteId::dma_route_dma_spi2_tx_spi2_tx, DmaConflictGroupId::none, -1, 3, -1},
  {DmaBindingId::dma_binding_uart0_rx_dma_uart0_rx, PeripheralId::UART0, SignalId::signal_RX, DmaControllerId::DMA, DmaRequestLineId::UART0_RX, DmaRouteId::dma_route_dma_uart0_rx_uart0_rx, DmaConflictGroupId::none, -1, 0, -1},
  {DmaBindingId::dma_binding_uart0_tx_dma_uart0_tx, PeripheralId::UART0, SignalId::signal_TX, DmaControllerId::DMA, DmaRequestLineId::UART0_TX, DmaRouteId::dma_route_dma_uart0_tx_uart0_tx, DmaConflictGroupId::none, -1, 1, -1},
}};

inline constexpr std::array<DmaControllerId, 1> kDmaControllers = {{
  DmaControllerId::DMA,
}};
}
}
}
}
}
}
