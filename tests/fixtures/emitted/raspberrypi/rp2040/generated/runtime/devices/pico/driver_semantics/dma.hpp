#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../dma_bindings.hpp"

namespace raspberrypi {
namespace rp2040 {
namespace generated {
namespace runtime {
namespace devices {
namespace pico {
namespace driver_semantics {
template<PeripheralId Peripheral, SignalId Signal>
struct DmaSemanticTraits {
  static constexpr bool kPresent = false;
  static constexpr DmaBindingId kBindingId = DmaBindingId::none;
  static constexpr DmaControllerId kControllerId = DmaControllerId::none;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::none;
  static constexpr DmaRouteId kRouteId = DmaRouteId::none;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::none;
  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::none;
  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = -1;
  static constexpr int kChannelSelector = -1;
  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = kInvalidIndexedFieldRef;
};

template<>
struct DmaSemanticTraits<PeripheralId::ADC, SignalId::signal_FIFO> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_adc_fifo_dma_adc;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::ADC;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_adc_adc_fifo;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::DMA;
  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::schema_alloy_dma_raspberrypi_rp2040_dma_v1;
  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 36;
  static constexpr int kChannelSelector = -1;
  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = kInvalidIndexedFieldRef;
};

template<>
struct DmaSemanticTraits<PeripheralId::SPI0, SignalId::signal_RX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_spi0_rx_dma_spi0_rx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::SPI0_RX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_spi0_rx_spi0_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::DMA;
  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::schema_alloy_dma_raspberrypi_rp2040_dma_v1;
  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 16;
  static constexpr int kChannelSelector = -1;
  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = kInvalidIndexedFieldRef;
};

template<>
struct DmaSemanticTraits<PeripheralId::SPI0, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_spi0_tx_dma_spi0_tx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::SPI0_TX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_spi0_tx_spi0_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::DMA;
  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::schema_alloy_dma_raspberrypi_rp2040_dma_v1;
  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 17;
  static constexpr int kChannelSelector = -1;
  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = kInvalidIndexedFieldRef;
};

template<>
struct DmaSemanticTraits<PeripheralId::SPI1, SignalId::signal_RX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_spi1_rx_dma_spi1_rx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::SPI1_RX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_spi1_rx_spi1_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::DMA;
  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::schema_alloy_dma_raspberrypi_rp2040_dma_v1;
  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 18;
  static constexpr int kChannelSelector = -1;
  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = kInvalidIndexedFieldRef;
};

template<>
struct DmaSemanticTraits<PeripheralId::SPI1, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_spi1_tx_dma_spi1_tx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::SPI1_TX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_spi1_tx_spi1_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::DMA;
  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::schema_alloy_dma_raspberrypi_rp2040_dma_v1;
  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 19;
  static constexpr int kChannelSelector = -1;
  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = kInvalidIndexedFieldRef;
};

template<>
struct DmaSemanticTraits<PeripheralId::UART0, SignalId::signal_RX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_uart0_rx_dma_uart0_rx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::UART0_RX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_uart0_rx_uart0_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::DMA;
  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::schema_alloy_dma_raspberrypi_rp2040_dma_v1;
  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 21;
  static constexpr int kChannelSelector = -1;
  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = kInvalidIndexedFieldRef;
};

template<>
struct DmaSemanticTraits<PeripheralId::UART0, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_uart0_tx_dma_uart0_tx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::UART0_TX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_uart0_tx_uart0_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::DMA;
  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::schema_alloy_dma_raspberrypi_rp2040_dma_v1;
  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 20;
  static constexpr int kChannelSelector = -1;
  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = kInvalidIndexedFieldRef;
};

template<>
struct DmaSemanticTraits<PeripheralId::UART1, SignalId::signal_RX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_uart1_rx_dma_uart1_rx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::UART1_RX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_uart1_rx_uart1_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::DMA;
  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::schema_alloy_dma_raspberrypi_rp2040_dma_v1;
  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 23;
  static constexpr int kChannelSelector = -1;
  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = kInvalidIndexedFieldRef;
};

template<>
struct DmaSemanticTraits<PeripheralId::UART1, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_uart1_tx_dma_uart1_tx;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::UART1_TX;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma_uart1_tx_uart1_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::DMA;
  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::schema_alloy_dma_raspberrypi_rp2040_dma_v1;
  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;
  static constexpr int kChannelIndex = -1;
  static constexpr int kRequestValue = 22;
  static constexpr int kChannelSelector = -1;
  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = kInvalidIndexedFieldRef;
};

inline constexpr std::array<PeripheralId, 9> kDmaSemanticPeripherals = {{
  PeripheralId::ADC,
  PeripheralId::SPI0,
  PeripheralId::SPI0,
  PeripheralId::SPI1,
  PeripheralId::SPI1,
  PeripheralId::UART0,
  PeripheralId::UART0,
  PeripheralId::UART1,
  PeripheralId::UART1,
}};

// complete-rp2040-semantics Phase D: per-controller DMA HW facts.
enum class RuntimeDmaCtrlId : std::uint8_t {
  None = 0,
  DMA = 1,
};

template<RuntimeDmaCtrlId Id>
struct DmaControllerHwTraits {
  static constexpr bool kPresent = false;
  static constexpr std::uint32_t kBaseAddress = 0u;
  static constexpr std::uint8_t kChannelCount = 0u;
  static constexpr std::uint32_t kMaxTransferCount = 0u;
  static constexpr bool kSupportsChaining = false;
  static constexpr bool kSupportsByteSwap = false;
  static constexpr std::array<std::uint32_t, 0> kIrqNumbers = {};
  static constexpr std::uint8_t kPriorityLevelCount = 0u;
  static constexpr std::array<std::uint8_t, 0> kSupportedBurstSizes = {};
  static constexpr std::array<std::uint8_t, 0> kSupportedDataWidths = {};
  static constexpr bool kSupportsCircular = false;
  static constexpr bool kSupportsDoubleBuffer = false;
  static constexpr bool kSupportsMemToMem = false;
  static constexpr bool kSupportsDescriptorChaining = false;
  static constexpr bool kSupportsScatterGather = false;
};

template<>
struct DmaControllerHwTraits<RuntimeDmaCtrlId::DMA> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x50000000u;
  static constexpr std::uint8_t kChannelCount = 12u;
  static constexpr std::uint32_t kMaxTransferCount = 0xffffffffu;
  static constexpr bool kSupportsChaining = true;
  static constexpr bool kSupportsByteSwap = true;
  static constexpr std::array<std::uint32_t, 2> kIrqNumbers = {{11u, 12u}};
  static constexpr std::uint8_t kPriorityLevelCount = 4u;
  static constexpr std::array<std::uint8_t, 3> kSupportedBurstSizes = {{1u, 2u, 4u}};
  static constexpr std::array<std::uint8_t, 3> kSupportedDataWidths = {{8u, 16u, 32u}};
  static constexpr bool kSupportsCircular = false;
  static constexpr bool kSupportsDoubleBuffer = false;
  static constexpr bool kSupportsMemToMem = true;
  static constexpr bool kSupportsDescriptorChaining = true;
  static constexpr bool kSupportsScatterGather = true;
};

}
}
}
}
}
}
}
