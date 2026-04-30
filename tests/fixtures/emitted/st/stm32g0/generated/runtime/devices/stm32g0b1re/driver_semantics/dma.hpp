#pragma once

#include <array>
#include <cstdint>
#include "common.hpp"
#include "../dma_bindings.hpp"

namespace st {
namespace stm32g0 {
namespace generated {
namespace runtime {
namespace devices {
namespace stm32g0b1re {
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
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_usart1_rx_dma1_dma1_ch1;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA1;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::DMA1_CH1;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma1_dma1_ch1_usart1_rx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::DMA1;
  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::DMAMUX1;
  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::schema_alloy_dma_st_bdma_v1_0;
  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::schema_alloy_dma_router_st_dmamux;
  static constexpr int kChannelIndex = 0;
  static constexpr int kRequestValue = 50;
  static constexpr int kChannelSelector = -1;
  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = RuntimeIndexedFieldRef{0x40020800u, 0u, 4u, 0u, 8u, 0u, true};
};

template<>
struct DmaSemanticTraits<PeripheralId::USART1, SignalId::signal_TX> {
  static constexpr bool kPresent = true;
  static constexpr DmaBindingId kBindingId = DmaBindingId::dma_binding_usart1_tx_dma1_dma1_ch2;
  static constexpr DmaControllerId kControllerId = DmaControllerId::DMA1;
  static constexpr DmaRequestLineId kRequestLineId = DmaRequestLineId::DMA1_CH2;
  static constexpr DmaRouteId kRouteId = DmaRouteId::dma_route_dma1_dma1_ch2_usart1_tx;
  static constexpr DmaConflictGroupId kConflictGroupId = DmaConflictGroupId::none;
  static constexpr PeripheralId kControllerPeripheralId = PeripheralId::DMA1;
  static constexpr PeripheralId kRouterPeripheralId = PeripheralId::DMAMUX1;
  static constexpr BackendSchemaId kControllerSchemaId = BackendSchemaId::schema_alloy_dma_st_bdma_v1_0;
  static constexpr BackendSchemaId kRouterSchemaId = BackendSchemaId::schema_alloy_dma_router_st_dmamux;
  static constexpr int kChannelIndex = 1;
  static constexpr int kRequestValue = 51;
  static constexpr int kChannelSelector = -1;
  static constexpr RuntimeIndexedFieldRef kRouteSelectorField = RuntimeIndexedFieldRef{0x40020800u, 0u, 4u, 0u, 8u, 0u, true};
};

inline constexpr std::array<PeripheralId, 2> kDmaSemanticPeripherals = {{
  PeripheralId::USART1,
  PeripheralId::USART1,
}};

// complete-rp2040-semantics Phase D: per-controller DMA HW facts.
enum class RuntimeDmaCtrlId : std::uint8_t {
  None = 0,
  DMA1 = 1,
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
  static constexpr std::uint32_t kBaseAddress = 0x40020000u;
  static constexpr std::uint8_t kChannelCount = 7u;
  static constexpr std::uint32_t kMaxTransferCount = 0x0000ffffu;
  static constexpr bool kSupportsChaining = false;
  static constexpr bool kSupportsByteSwap = false;
  static constexpr std::array<std::uint32_t, 2> kIrqNumbers = {{9u, 10u}};
  static constexpr std::uint8_t kPriorityLevelCount = 4u;
  static constexpr std::array<std::uint8_t, 1> kSupportedBurstSizes = {{1u}};
  static constexpr std::array<std::uint8_t, 3> kSupportedDataWidths = {{8u, 16u, 32u}};
  static constexpr bool kSupportsCircular = true;
  static constexpr bool kSupportsDoubleBuffer = false;
  static constexpr bool kSupportsMemToMem = true;
  static constexpr bool kSupportsDescriptorChaining = false;
  static constexpr bool kSupportsScatterGather = false;
};

}
}
}
}
}
}
}
