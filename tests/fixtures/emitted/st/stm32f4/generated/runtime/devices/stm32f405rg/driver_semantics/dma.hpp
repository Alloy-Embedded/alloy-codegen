#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../dma_bindings.hpp"

namespace st {
namespace stm32f4 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32f405rg {
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
struct DmaSemanticTraits<PeripheralId::USART1, SignalId::signal_RX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_usart1_rx_dma2_dma2_stream2;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA2;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::DMA2_STREAM2;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma2_dma2_stream2_usart1_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::DMA2;
  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::schema_alloy_dma_st_bdma_f4_v1_0;
  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;
  static constexpr int kChannelIndex = 2;
  static constexpr int kRequestValue = -1;
  static constexpr int kChannelSelector = 4;
  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = RuntimeIndexedFieldRef{0x40026400u, 16u, 24u, 25u, 3u, 0u, true};
};

template<>
struct DmaSemanticTraits<PeripheralId::USART1, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_usart1_tx_dma2_dma2_stream7;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA2;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::DMA2_STREAM7;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma2_dma2_stream7_usart1_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::DMA2;
  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::none;
  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::schema_alloy_dma_st_bdma_f4_v1_0;
  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::none;
  static constexpr int kChannelIndex = 7;
  static constexpr int kRequestValue = -1;
  static constexpr int kChannelSelector = 4;
  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = RuntimeIndexedFieldRef{0x40026400u, 16u, 24u, 25u, 3u, 0u, true};
};

inline constexpr std::array<PeripheralId, 2> kDmaSemanticPeripherals = {{
  PeripheralId::USART1,
  PeripheralId::USART1,
}};

// complete-rp2040-semantics Phase D: per-controller DMA HW facts.
enum class RuntimeDmaCtrlId : std::uint8_t {
  None = 0,
  DMA1 = 1,
  DMA2 = 2,
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
struct DmaControllerHwTraits<RuntimeDmaCtrlId::DMA1> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x40026000u;
  static constexpr std::uint8_t kChannelCount = 8u;
  static constexpr std::uint32_t kMaxTransferCount = 0x0000ffffu;
  static constexpr bool kSupportsChaining = false;
  static constexpr bool kSupportsByteSwap = false;
  static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{11u}};
  static constexpr std::uint8_t kPriorityLevelCount = 4u;
  static constexpr std::array<std::uint8_t, 4> kSupportedBurstSizes = {{1u, 4u, 8u, 16u}};
  static constexpr std::array<std::uint8_t, 3> kSupportedDataWidths = {{8u, 16u, 32u}};
  static constexpr bool kSupportsCircular = true;
  static constexpr bool kSupportsDoubleBuffer = true;
  static constexpr bool kSupportsMemToMem = true;
  static constexpr bool kSupportsDescriptorChaining = false;
  static constexpr bool kSupportsScatterGather = true;
};

template<>
struct DmaControllerHwTraits<RuntimeDmaCtrlId::DMA2> {
  static constexpr bool kPresent = true;
  static constexpr std::uint32_t kBaseAddress = 0x40026400u;
  static constexpr std::uint8_t kChannelCount = 8u;
  static constexpr std::uint32_t kMaxTransferCount = 0x0000ffffu;
  static constexpr bool kSupportsChaining = false;
  static constexpr bool kSupportsByteSwap = false;
  static constexpr std::array<std::uint32_t, 1> kIrqNumbers = {{56u}};
  static constexpr std::uint8_t kPriorityLevelCount = 4u;
  static constexpr std::array<std::uint8_t, 4> kSupportedBurstSizes = {{1u, 4u, 8u, 16u}};
  static constexpr std::array<std::uint8_t, 3> kSupportedDataWidths = {{8u, 16u, 32u}};
  static constexpr bool kSupportsCircular = true;
  static constexpr bool kSupportsDoubleBuffer = true;
  static constexpr bool kSupportsMemToMem = true;
  static constexpr bool kSupportsDescriptorChaining = false;
  static constexpr bool kSupportsScatterGather = true;
};

}
}
}
}
}
}
}
