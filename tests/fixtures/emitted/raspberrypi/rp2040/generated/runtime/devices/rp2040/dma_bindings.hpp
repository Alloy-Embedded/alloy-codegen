#pragma once

#include <array>
#include <cstdint>
#include "../../types.hpp"
#include "peripheral_instances.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace rp2040 {
enum class DmaBindingId : std::uint16_t {
  none,
  dma_binding_adc_fifo_dma_adc,
  dma_binding_spi0_rx_dma_spi0_rx,
  dma_binding_spi0_tx_dma_spi0_tx,
  dma_binding_spi1_rx_dma_spi1_rx,
  dma_binding_spi1_tx_dma_spi1_tx,
  dma_binding_uart0_rx_dma_uart0_rx,
  dma_binding_uart0_tx_dma_uart0_tx,
  dma_binding_uart1_rx_dma_uart1_rx,
  dma_binding_uart1_tx_dma_uart1_tx,
};

enum class DmaControllerId : std::uint16_t {
  none,
  DMA,
};

enum class DmaRequestLineId : std::uint16_t {
  none,
  ADC,
  SPI0_RX,
  SPI0_TX,
  SPI1_RX,
  SPI1_TX,
  UART0_RX,
  UART0_TX,
  UART1_RX,
  UART1_TX,
};

enum class DmaRouteId : std::uint16_t {
  none,
  dma_route_dma_adc_adc_fifo,
  dma_route_dma_spi0_rx_spi0_rx,
  dma_route_dma_spi0_tx_spi0_tx,
  dma_route_dma_spi1_rx_spi1_rx,
  dma_route_dma_spi1_tx_spi1_tx,
  dma_route_dma_uart0_rx_uart0_rx,
  dma_route_dma_uart0_tx_uart0_tx,
  dma_route_dma_uart1_rx_uart1_rx,
  dma_route_dma_uart1_tx_uart1_tx,
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
struct BindingTraits<PeripheralId::ADC, SignalId::signal_FIFO> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_adc_fifo_dma_adc;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::ADC;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_adc_adc_fifo;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 36;
  static constexpr int kChannelSelector = -1;
};

template<>
struct BindingTraits<PeripheralId::SPI0, SignalId::signal_RX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_spi0_rx_dma_spi0_rx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::SPI0_RX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_spi0_rx_spi0_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 16;
  static constexpr int kChannelSelector = -1;
};

template<>
struct BindingTraits<PeripheralId::SPI0, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_spi0_tx_dma_spi0_tx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::SPI0_TX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_spi0_tx_spi0_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 17;
  static constexpr int kChannelSelector = -1;
};

template<>
struct BindingTraits<PeripheralId::SPI1, SignalId::signal_RX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_spi1_rx_dma_spi1_rx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::SPI1_RX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_spi1_rx_spi1_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 18;
  static constexpr int kChannelSelector = -1;
};

template<>
struct BindingTraits<PeripheralId::SPI1, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_spi1_tx_dma_spi1_tx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::SPI1_TX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_spi1_tx_spi1_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 19;
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
  static constexpr int kRequestValue = 21;
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
  static constexpr int kRequestValue = 20;
  static constexpr int kChannelSelector = -1;
};

template<>
struct BindingTraits<PeripheralId::UART1, SignalId::signal_RX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_uart1_rx_dma_uart1_rx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::UART1_RX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_uart1_rx_uart1_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 23;
  static constexpr int kChannelSelector = -1;
};

template<>
struct BindingTraits<PeripheralId::UART1, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_uart1_tx_dma_uart1_tx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::UART1_TX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_uart1_tx_uart1_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 22;
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
  static constexpr BackendSchemaId kSchemaId = BackendSchemaId::schema_alloy_dma_raspberrypi_rp2040_dma_v1;
  static constexpr int kChannelCount = 12;
  static constexpr int kRequestCount = 9;
};

inline constexpr std::array<DmaBindingDescriptor, 9> kDmaBindings = {{
  {DmaBindingId::dma_binding_adc_fifo_dma_adc, PeripheralId::ADC, SignalId::signal_FIFO, DmaControllerId::DMA, DmaRequestLineId::ADC, DmaRouteId::dma_route_dma_adc_adc_fifo, DmaConflictGroupId::none, -1, 36, -1},
  {DmaBindingId::dma_binding_spi0_rx_dma_spi0_rx, PeripheralId::SPI0, SignalId::signal_RX, DmaControllerId::DMA, DmaRequestLineId::SPI0_RX, DmaRouteId::dma_route_dma_spi0_rx_spi0_rx, DmaConflictGroupId::none, -1, 16, -1},
  {DmaBindingId::dma_binding_spi0_tx_dma_spi0_tx, PeripheralId::SPI0, SignalId::signal_TX, DmaControllerId::DMA, DmaRequestLineId::SPI0_TX, DmaRouteId::dma_route_dma_spi0_tx_spi0_tx, DmaConflictGroupId::none, -1, 17, -1},
  {DmaBindingId::dma_binding_spi1_rx_dma_spi1_rx, PeripheralId::SPI1, SignalId::signal_RX, DmaControllerId::DMA, DmaRequestLineId::SPI1_RX, DmaRouteId::dma_route_dma_spi1_rx_spi1_rx, DmaConflictGroupId::none, -1, 18, -1},
  {DmaBindingId::dma_binding_spi1_tx_dma_spi1_tx, PeripheralId::SPI1, SignalId::signal_TX, DmaControllerId::DMA, DmaRequestLineId::SPI1_TX, DmaRouteId::dma_route_dma_spi1_tx_spi1_tx, DmaConflictGroupId::none, -1, 19, -1},
  {DmaBindingId::dma_binding_uart0_rx_dma_uart0_rx, PeripheralId::UART0, SignalId::signal_RX, DmaControllerId::DMA, DmaRequestLineId::UART0_RX, DmaRouteId::dma_route_dma_uart0_rx_uart0_rx, DmaConflictGroupId::none, -1, 21, -1},
  {DmaBindingId::dma_binding_uart0_tx_dma_uart0_tx, PeripheralId::UART0, SignalId::signal_TX, DmaControllerId::DMA, DmaRequestLineId::UART0_TX, DmaRouteId::dma_route_dma_uart0_tx_uart0_tx, DmaConflictGroupId::none, -1, 20, -1},
  {DmaBindingId::dma_binding_uart1_rx_dma_uart1_rx, PeripheralId::UART1, SignalId::signal_RX, DmaControllerId::DMA, DmaRequestLineId::UART1_RX, DmaRouteId::dma_route_dma_uart1_rx_uart1_rx, DmaConflictGroupId::none, -1, 23, -1},
  {DmaBindingId::dma_binding_uart1_tx_dma_uart1_tx, PeripheralId::UART1, SignalId::signal_TX, DmaControllerId::DMA, DmaRequestLineId::UART1_TX, DmaRouteId::dma_route_dma_uart1_tx_uart1_tx, DmaConflictGroupId::none, -1, 22, -1},
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
